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

/* Zone used for header/footer. */
#define _GC_OBJ_ZONE    gcvZONE_HARDWARE

#define SPLIT_RECT              1

#if SPLIT_RECT

typedef enum __SPLIT_RECT_MODE
{
    SPLIT_RECT_MODE_NONE,
    SPLIT_RECT_MODE_COLUMN,
    SPLIT_RECT_MODE_LINE
} SPLIT_RECT_MODE;

#define SPLIT_COLUMN            4
#define SPLIT_COLUMN_WIDTH      (1 << SPLIT_COLUMN)
#define SPLIT_COLUMN_WIDTH_MASK (~(SPLIT_COLUMN_WIDTH - 1))
#endif

/******************************************************************************
 *
 *  deRop3
 *
 *  Perform the specified raster operation on 32-bit data.
 *
 *  Input parameters:
 *
 *      gctUINT8 Rop3
 *          Raster operation code.
 *
 *      gctUINT32 Destination
 *          Destination pixel value.
 *
 *      gctUINT32 Source
 *          Source pixel values.
 *
 *      gctUINT32 Pattern
 *          Pattern value.
 *
 *  Return value:
 *
 *      gctUINT32
 *          32-bit result.
 *
 */
static gctUINT32 _Rop3(
    gctUINT8 Rop3,
    gctUINT32 Source,
    gctUINT32 Pattern,
    gctUINT32 Destination
    )
{
    gctUINT32 i;
    gctUINT32 result = 0;

    for (i = 0; i < 32; i++)
    {
        /* Extract data bits. */
        gctUINT32 sourceBit      = Source      & 1;
        gctUINT32 patternBit     = Pattern     & 1;
        gctUINT32 destinationBit = Destination & 1;

        /* Construct rop bit index. */
        gctUINT32 index
            = (sourceBit  << 1)
            | (patternBit << 2)
            | destinationBit;

        /* Determine the result bit. */
        gctUINT32 resultBit = (Rop3 >> index) & 1;

        /* Set the result. */
        result |= (resultBit << i);

        /* Advance to the next bit. */
        Source      >>= 1;
        Pattern     >>= 1;
        Destination >>= 1;
    }

    return result;
}

/*******************************************************************************
**
**  _RenderRectangle
**
**  2D software renderer.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gce2D_COMMAND Command
**          2D engine command to be executed.
**
**      gctUINT32 RectCount
**          Number of destination rectangles to be operated on.
**
**      gcsRECT_PTR DestRect
**          Pointer to an array of destination rectangles.
**
**      gctUINT32 FgRop
**      gctUINT32 BgRop
**          Foreground and background ROP codes.
**
**  OUTPUT:
**
**      Nothing .
*/
static gceSTATUS _RenderRectangle(
    IN gcoHARDWARE Hardware,
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command,
    IN gctUINT32 RectCount,
    IN gcsRECT_PTR DestRect
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x Command=%d RectCount=%u DestRect=0x%x",
                  Hardware, Command, RectCount, DestRect);

    /* Verify arguments. */
    gcmDEBUG_VERIFY_ARGUMENT(DestRect != gcvNULL);

    do
    {
        gctINT32 initSrcLeft, initTrgLeft;
        gctUINT srcPixelSize, trgPixelSize;
        gctUINT srcStep, trgStep;
        gctINT32 x, y;
        gctINT32 width, height;
        gctUINT8_PTR srcLinePtr;
        gctUINT8_PTR trgLinePtr;
        gcsSURF_FORMAT_INFO_PTR srcFormat[2];
        gcsSURF_FORMAT_INFO_PTR intFormat[2];
        gcsSURF_FORMAT_INFO_PTR trgFormat[2];
        gctUINT32 srcColorMask;
        gctUINT32 transparentColor;
        gctBOOL srcOddStart, trgOddStart;
        gctUINT32 srcPixel[2] = {0};
        gctUINT32 trgPixel[2] = {0};
        gcs2D_MULTI_SOURCE_PTR curSrc = &State->multiSrc[State->currentSrcIndex];
        gctUINT32 FgRop = curSrc->fgRop;
        gctUINT32 BgRop = curSrc->bgRop;
        gcsSURF_INFO_PTR srcSurface = &curSrc->srcSurface;
        gcsRECT_PTR sourceRect = &curSrc->srcRect;

        /* Only limited support for now. */
        if ((Command != gcv2D_BLT) ||
            (RectCount != 1))
        {
            gcmERR_BREAK(gcvSTATUS_NOT_SUPPORTED);
        }

        /* Commit any commands buffer and stall. */
        gcmERR_BREAK(gcoHARDWARE_Commit());
        gcmERR_BREAK(gcoHARDWARE_Stall());

        /* Get format specifics. */
        gcmERR_BREAK(gcoSURF_QueryFormat(
            srcSurface->format, srcFormat
            ));

        gcmERR_BREAK(gcoSURF_QueryFormat(
            gcvSURF_A8R8G8B8, intFormat
            ));

        gcmERR_BREAK(gcoSURF_QueryFormat(
            State->dstSurface.format, trgFormat
            ));

        /* Determine the initial source and target left coordinates. */
        initSrcLeft = srcFormat[0]->interleaved
            ? ~1 & sourceRect->left
            :      sourceRect->left;

        initTrgLeft = trgFormat[0]->interleaved
            ? ~1 & DestRect->left
            :      DestRect->left;

        /* Determine odd start flags. */
        srcOddStart = 1 & sourceRect->left;
        trgOddStart = 1 & DestRect->left;

        /* Determine pixel sizes. */
        srcPixelSize = srcFormat[0]->bitsPerPixel / 8;
        trgPixelSize = trgFormat[0]->bitsPerPixel / 8;

        /* Determine horizontal steps. */
        srcStep = srcFormat[0]->interleaved
            ? srcPixelSize * 2
            : srcPixelSize;

        trgStep = trgFormat[0]->interleaved
            ? trgPixelSize * 2
            : trgPixelSize;

        /* Compute the rectangle size. */
        width  = DestRect->right  - DestRect->left;
        height = DestRect->bottom - DestRect->top;

        /* Compute initial position. */
        srcLinePtr
            = ((gctUINT8_PTR) srcSurface->node.logical)
            + sourceRect->top * srcSurface->stride
            + initSrcLeft * srcPixelSize;

        trgLinePtr
            = ((gctUINT8_PTR) State->dstSurface.node.logical)
            + DestRect->top * State->dstSurface.stride
            + initTrgLeft * trgPixelSize;

        /* Commpute source pixel mask. */
        gcmERR_BREAK(gcoSURF_ComputeColorMask(srcFormat[0], &srcColorMask));

        /* Determine the transparency color. */
        transparentColor = curSrc->srcColorKeyLow & srcColorMask;

        /* Loop through pixels one at a time. */
        for (y = 0; (y < height) && gcmIS_SUCCESS(status); y++)
        {
            gctUINT8_PTR srcPixelPtr = srcLinePtr;
            gctUINT8_PTR trgPixelPtr = trgLinePtr;

            /* Determine initial even/odd. */
            gctBOOL srcOdd = srcFormat[0]->interleaved && srcOddStart;
            gctBOOL trgOdd = trgFormat[0]->interleaved && trgOddStart;

            for (x = 0; x < width; x++)
            {
                gctBOOL transparent = gcvFALSE;

                gctUINT32 convSrcPixel = 0;
                gctUINT32 resultPixel;
                gctUINT8 rop;

                /* Read the source and destination pixels. */
                if (!srcOdd || srcOddStart)
                {
                    gcmERR_BREAK(gcoHARDWARE_ConvertPixel(
                        srcPixelPtr, &srcPixel[0], 0, 0,
                        srcFormat[0], srcFormat[0],
                        gcvNULL, gcvNULL
                        ));

                    if (srcFormat[0]->interleaved)
                    {
                        gcmERR_BREAK(gcoHARDWARE_ConvertPixel(
                            srcPixelPtr, &srcPixel[1], 0, 0,
                            srcFormat[1], srcFormat[1],
                            gcvNULL, gcvNULL
                            ));
                    }
                }

                if (!trgOdd || trgOddStart)
                {
                    gcmERR_BREAK(gcoHARDWARE_ConvertPixel(
                        trgPixelPtr, &trgPixel[0], 0, 0,
                        trgFormat[0], intFormat[0],
                        gcvNULL, gcvNULL
                        ));

                    if (trgFormat[0]->interleaved)
                    {
                        gcmERR_BREAK(gcoHARDWARE_ConvertPixel(
                            trgPixelPtr, &trgPixel[1], 0, 0,
                            trgFormat[1], intFormat[0],
                            gcvNULL, gcvNULL
                            ));
                    }
                }

                /* Determine transparency. */
                if (curSrc->srcTransparency == gcv2D_KEYED)
                {
                    transparent = ((srcPixel[srcOdd] & srcColorMask) == transparentColor)
                        ? gcvTRUE
                        : gcvFALSE;
                }

                /* Determine the ROP code to be used. */
                rop = transparent ? (gctUINT8) BgRop : (gctUINT8) FgRop;

                /* Convert the source pixel to the intermediate format. */
                gcmERR_BREAK(gcoHARDWARE_ConvertPixel(
                    &srcPixel[srcOdd],
                    &convSrcPixel,
                    0, 0,
                    srcFormat[srcOdd],
                    intFormat[0],
                    gcvNULL, gcvNULL
                    ));

                /* Perform ROP. */
                resultPixel = _Rop3(rop, convSrcPixel, 0, trgPixel[trgOdd]);

                /* Write the result back. */
                gcmERR_BREAK(gcoHARDWARE_ConvertPixel(
                    &resultPixel,
                    trgPixelPtr,
                    0, 0,
                    intFormat[0],
                    trgFormat[trgOdd],
                    gcvNULL, gcvNULL
                    ));

                /* Advance to the next pixel. */
                if (!srcFormat[0]->interleaved || srcOdd)
                    srcPixelPtr += srcStep;

                if (!trgFormat[0]->interleaved || trgOdd)
                    trgPixelPtr += trgStep;

                /* Update the odd flags. */
                srcOdd = (srcOdd + srcFormat[0]->interleaved) & 1;
                trgOdd = (trgOdd + trgFormat[0]->interleaved) & 1;
            }

            /* Advance to the next line. */
            srcLinePtr += srcSurface->stride;
            trgLinePtr += State->dstSurface.stride;
        }

        /* Dump the results. */
        gcmDUMP_BUFFER(gcvNULL,
                       "memory",
                       State->dstSurface.node.physical,
                       State->dstSurface.node.logical,
                       0,
                       State->dstSurface.node.size);
    }
    while (gcvFALSE);

    /* Return status. */
    gcmFOOTER_NO();
    return status;
}

/******************************************************************************
 *
 *  _IsValidRect
 *
 *  Chech whether the rect is valid for HW operation.
 *
 *  Input parameters:
 *
 *      gcsRECT_PTR Rect
 *
 *  Return value:
 *
 *      gctBOOL
 *          gcvTRUE if valid; or else gcvFALSE.
 *
 */
static gctBOOL _IsValidRect(const gcsRECT_PTR Rect)
{
    return ((Rect->left   >= 0)
         && (Rect->top    >= 0)
         && (Rect->left   < Rect->right)
         && (Rect->top    < Rect->bottom)
         && (Rect->right  <= 65535)
         && (Rect->bottom <= 65535));
}

static gctUINT32 s_2DCacheFlushCmd[] =
{
    0x08050480, 0x00000000,
    0x00000020, 0x00000010,
    0x04000004, 0x00000000,
    0x0804048a, 0x00000000,
    0x00000020, 0x00000010,
    0x00002004, 0x00000000,
    0x08030497, 0x0030cccc,
    0x00000000, 0x00100002,
    0x0801049f, 0x00000000,
    0x080104af, 0x00000cc0,
    0x080204b4, 0x00000000,
    0x00000000, 0x00000000,
    0x20000100, 0x00000000,
    0x00000000, 0x00010001
};

#define BUFFER_SIZE_OF_2D_CACHE_FLUSH gcmCOUNTOF(s_2DCacheFlushCmd)

static gceSTATUS _Append2DCacheFlush(IN gcoHARDWARE Hardware)
{
    gceSTATUS status;

    if (Hardware->hw2DCacheFlushSurf == gcvNULL)
    {
        gcmONERROR(gcoHARDWARE_Get2DTempSurface(
            16, 4, gcvSURF_R5G6B5, &Hardware->hw2DCacheFlushSurf));

        s_2DCacheFlushCmd[1] = Hardware->hw2DCacheFlushSurf->node.physical;
        s_2DCacheFlushCmd[7] = s_2DCacheFlushCmd[1] + 0x40;
    }

    if (Hardware->hw2DCmdBuffer != gcvNULL)
    {
        gcoOS_MemCopy(
            Hardware->hw2DCmdBuffer + Hardware->hw2DCmdIndex,
            s_2DCacheFlushCmd,
            gcmSIZEOF(s_2DCacheFlushCmd));
    }

    Hardware->hw2DCmdIndex += BUFFER_SIZE_OF_2D_CACHE_FLUSH;

    /* Success. */
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    return status;
}

static gctUINT _ReserveBufferSize(
    IN gcoHARDWARE Hardware,
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command
    )
{
    gctUINT srcMask = 0, srcCurrent = 0, i;
    gctBOOL usePattern = gcvFALSE, usePallete = gcvFALSE;
    gcs2D_MULTI_SOURCE_PTR src;
    gctUINT size;

    if (Command == gcv2D_MULTI_SOURCE_BLT)
    {
        srcMask = State->srcMask;
    }
    else
    {
        srcMask = 1 << State->currentSrcIndex;
    }

    for (i = 0; i < gcdMULTI_SOURCE_NUM; i++)
    {
        gctBOOL source, pattern;

        if (!(srcMask & (1 << i)))
        {
            continue;
        }

        src = State->multiSrc + i;

        /* Determine the resource usage. */
        gcoHARDWARE_Get2DResourceUsage(
            src->fgRop, src->bgRop,
            src->srcTransparency,
            &source, &pattern, gcvNULL
            );

        if (source)
        {
            usePallete = usePallete || (src->srcSurface.format == gcvSURF_INDEX8);
            srcCurrent++;
        }

        usePattern |= pattern;
    }

    size =
        /* common states. */
        50
        /* pattern. */
        + (usePattern ? 10 : 0)
        /* source. */
        + ((srcCurrent > 0) ? (68 * srcCurrent) : 24)
        /* pallete. */
        + (usePallete ? 258 : 0)
        /* tail. */
        + 12;

    if (Hardware->hw2DAppendCacheFlush == gcvTRUE)
    {
        size += BUFFER_SIZE_OF_2D_CACHE_FLUSH;
    }

    return size;
}

gceSTATUS gcoHARDWARE_Reset2DCmdBuffer(
    IN gcoHARDWARE Hardware,
    IN gctBOOL CleanCmd)
{
    gcmHEADER_ARG("Hardware=0x%x, CleanCmd=%d",
                    Hardware, CleanCmd);

    if (CleanCmd)
    {
        /* Clean command buffer. */
        if (Hardware->hw2DCmdBuffer != gcvNULL)
        {

            Hardware->hw2DCmdIndex = 0;

            /* Fill redundant buffer with NOP */
            if (Hardware->hw2DCmdSize > Hardware->hw2DCmdIndex)
            {
                gcmVERIFY_OK(gcoHARDWARE_2DAppendNop(Hardware));
            }

            gcmASSERT(Hardware->hw2DCmdSize == Hardware->hw2DCmdIndex);
        }
    }

    Hardware->hw2DCmdBuffer = gcvNULL;
    Hardware->hw2DCmdIndex = Hardware->hw2DCmdSize = 0;

    /* Return the status. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

static gceSTATUS gcoHARDWARE_Set2DState(
    IN gcoHARDWARE Hardware,
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command
    )
{
    gceSTATUS status;
    gceSURF_FORMAT dstFormat;
    gctUINT32 command, format, swizzle, isYUVformat, endian, destConfig;
    gctBOOL useSource, useDest, usePattern;
    gcs2D_MULTI_SOURCE_PTR src;
    gctUINT8 fgRop, bgRop;
    gctBOOL flushCache = gcvTRUE, setPattern = gcvTRUE, uploadPaletteTable = gcvTRUE;
    gctUINT srcMask = 0, srcCurrent = 0, i;
    gctBOOL multiSrcRot = gcvFALSE;
    gctBOOL multiSrcNoneLinear = gcvFALSE;
    gctUINT32 dstBpp;

    gcmHEADER_ARG("Hardware=0x%x State=%x Command=0x%x",
                    Hardware, State, Command);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

    /* Convert the command. */
    gcmONERROR(gcoHARDWARE_TranslateCommand(
        Command, &command
        ));

    dstFormat = State->dstSurface.format;

    /* Convert the format. */
    gcmONERROR(gcoHARDWARE_TranslateDestinationFormat(
        dstFormat, &format, &swizzle, &isYUVformat
        ));

    /* Set endian control */
    endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)));

    /* Compute bits per pixel. */
    gcmONERROR(gcoHARDWARE_ConvertFormat(dstFormat,
                                         &dstBpp,
                                         gcvNULL));

    if (Hardware->bigEndian)
    {
        if (dstBpp == 16)
        {
            endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)));
        }
    }

    /*******************************************************************
    ** Set the destination configuration register.
    */
    destConfig =
        ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:12) - (0 ? 15:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:12) - (0 ? 15:12) + 1))))))) << (0 ? 15:12))) | (((gctUINT32) ((gctUINT32) (command) & ((gctUINT32) ((((1 ? 15:12) - (0 ? 15:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:12) - (0 ? 15:12) + 1))))))) << (0 ? 15:12)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16))) | (((gctUINT32) ((gctUINT32) (swizzle) & ((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | (((gctUINT32) ((gctUINT32) (format) & ((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0)))
        | endian;

    switch (State->dstSurface.tiling)
    {
    case gcvLINEAR:
        destConfig |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)));
        break;

    case gcvTILED:
        destConfig |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)));
        break;

    case gcvMINORTILED:
        destConfig |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)))
                    | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26)));
        break;

    default:
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    /*******************************************************************
    ** Select 2D pipe.
    */
    if (Hardware->hw3DEngine)
    {
        /* Flush the 3D pipe. */
        gcmONERROR(gcoHARDWARE_Load2DState32(Hardware,
                                      0x0380C,
                                      ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)))
                                      | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:1) - (0 ? 1:1) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:1) - (0 ? 1:1) + 1))))))) << (0 ? 1:1))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 1:1) - (0 ? 1:1) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:1) - (0 ? 1:1) + 1))))))) << (0 ? 1:1)))
                                      ));

        gcmONERROR(gcoHARDWARE_Load2DState32(Hardware,
                                      0x03808,
                                      ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8))) | (((gctUINT32) (0x07 & ((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8)))
                                      | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0)))
                                      ));

        if (Hardware->hw2DCmdBuffer != gcvNULL)
        {
            Hardware->hw2DCmdBuffer[Hardware->hw2DCmdIndex] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x09 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)));
            Hardware->hw2DCmdIndex += 1;

            Hardware->hw2DCmdBuffer[Hardware->hw2DCmdIndex] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8))) | (((gctUINT32) (0x07 & ((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8)))
                              | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0)));
            Hardware->hw2DCmdIndex += 1;
        }
        else
        {
            Hardware->hw2DCmdIndex += 2;
        }
    }

    gcmONERROR(gcoHARDWARE_Load2DState32(
        Hardware,
        0x03800,
        ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) ((gctUINT32) (gcvPIPE_2D) & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)))
        ));


    if (Command == gcv2D_STRETCH)
    {
        /* Set stretch factors. */
        gcmONERROR(gcoHARDWARE_SetStretchFactors(
            Hardware,
            State->horFactor,
            State->verFactor
            ));

        destConfig |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 24:24) - (0 ? 24:24) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 24:24) - (0 ? 24:24) + 1))))))) << (0 ? 24:24))) | (((gctUINT32) ((gctUINT32) (Hardware->hw2DEnableGDIStretch ? 0x1 : 0x0) & ((gctUINT32) ((((1 ? 24:24) - (0 ? 24:24) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 24:24) - (0 ? 24:24) + 1))))))) << (0 ? 24:24)));
    }

    if (Hardware->hw2DDEEnhance1)
    {
        /* Enable new walker.*/
        destConfig |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 29:29) - (0 ? 29:29) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 29:29) - (0 ? 29:29) + 1))))))) << (0 ? 29:29))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 29:29) - (0 ? 29:29) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 29:29) - (0 ? 29:29) + 1))))))) << (0 ? 29:29)));

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01324,
              ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (3) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (3) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)))
            ));

        destConfig = ((((gctUINT32) (destConfig)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1))))))) << (0 ? 28:28))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1))))))) << (0 ? 28:28)));

        destConfig = ((((gctUINT32) (destConfig)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 27:27) - (0 ? 27:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 27:27) - (0 ? 27:27) + 1))))))) << (0 ? 27:27))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 27:27) - (0 ? 27:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 27:27) - (0 ? 27:27) + 1))))))) << (0 ? 27:27)));
    }

    gcmONERROR(gcoHARDWARE_Load2DState32(
        Hardware,
        0x01234,
        destConfig
        ));

    /* Set target surface */
    gcmONERROR(gcoHARDWARE_SetTarget(
        Hardware,
        &State->dstSurface
        ));

    if (isYUVformat && (Command == gcv2D_MULTI_SOURCE_BLT))
    {
        gcmONERROR(gcoHARDWARE_SetMultiTarget(
            Hardware,
            &State->dstSurface,
            State->multiSrc[State->currentSrcIndex].srcSurface.format
            ));
    }
    else
    {
        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x0130C,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0)))));
    }

    /* Set target color key range. */
    gcmONERROR(gcoHARDWARE_SetTargetColorKeyRange(
        Hardware,
        State->dstColorKeyLow,
        State->dstColorKeyHigh
        ));

    gcmONERROR(gcoHARDWARE_SetClipping(
        Hardware,
        &State->clipRect));

    if (Command == gcv2D_CLEAR)
    {
        /* Set clear color. */
        gcmONERROR(gcoHARDWARE_Set2DClearColor(
            Hardware,
            State->clearColor,
            dstFormat
            ));

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x012BC,
            ((((gctUINT32) (((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))))) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0))) | (((gctUINT32) ((gctUINT32) (0x0) & ((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0)))
            ));
     }

    /* Set mirror state. */
    gcmONERROR(gcoHARDWARE_SetBitBlitMirror(
        Hardware,
        State->horMirror,
        State->verMirror
        ));

    /* Set 2D dithering. */
    gcmONERROR(gcoHARDWARE_SetDither2D(
        Hardware,
        State->dither
        ));

    if (Command == gcv2D_MULTI_SOURCE_BLT)
    {
        srcMask = State->srcMask;

        multiSrcRot = (State->dstSurface.rotation == gcvSURF_270_DEGREE)
            || (State->dstSurface.rotation == gcvSURF_90_DEGREE);

        multiSrcNoneLinear = State->dstSurface.tiling != gcvLINEAR;
    }
    else
    {
        srcMask = 1 << State->currentSrcIndex;
    }

    for (i = 0; i < gcdMULTI_SOURCE_NUM; i++)
    {
        if (!(srcMask & (1 << i)))
        {
            continue;
        }

        src = State->multiSrc + i;

        fgRop = src->fgRop;
        bgRop = src->bgRop;

        /* Determine the resource usage. */
        gcoHARDWARE_Get2DResourceUsage(
            fgRop, bgRop,
            src->srcTransparency,
            &useSource, &usePattern, &useDest
            );

        if (flushCache)
        {
            /*******************************************************************
            ** Chips with byte write capability don't fetch the destiantion
            ** if it's not needed for the current operation. If the primitive(s)
            ** that follow overlap with the previous primitive causing a cache
            ** hit and they happen to use the destination to ROP with, it will
            ** cause corruption since the destination was not fetched in the
            ** first place.
            **
            ** Currently the hardware does not track this kind of case so we
            ** have to flush whenever we see a use of source or destination.
            */

            /* Flush 2D cache if needed. */
            if ((Hardware->byteWrite && (useSource || useDest))
                || Hardware->bigEndian)
            {
                /* Flush the current pipe. */
                gcmONERROR(gcoHARDWARE_Load2DState32(
                                              Hardware,
                                              0x0380C,
                                              ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)))));

                flushCache = gcvFALSE;
            }
        }

        if (usePattern && setPattern)
        {
            setPattern = gcvFALSE;

            switch (State->brushType)
            {
            case gcv2D_PATTERN_SOLID:
                gcmONERROR(gcoHARDWARE_LoadSolidColorPattern(
                    Hardware,
                    State->brushColorConvert,
                    State->brushFgColor,
                    State->brushMask,
                    dstFormat
                    ));
                break;

            case gcv2D_PATTERN_MONO:
                gcmONERROR(gcoHARDWARE_LoadMonochromePattern(
                    Hardware,
                    State->brushOriginX,
                    State->brushOriginY,
                    State->brushColorConvert,
                    State->brushFgColor,
                    State->brushBgColor,
                    State->brushBits,
                    State->brushMask,
                    dstFormat
                    ));
                break;

            case gcv2D_PATTERN_COLOR:
                gcmONERROR(gcoHARDWARE_LoadColorPattern(
                    Hardware,
                    State->brushOriginX,
                    State->brushOriginY,
                    State->brushAddress,
                    State->brushFormat,
                    State->brushMask
                    ));
                break;

            default:
                gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
            }
        }

        /* the old src registers. */
        if (Command != gcv2D_MULTI_SOURCE_BLT)
        {
            /* Set transparency mode */
            gcmONERROR(gcoHARDWARE_SetTransparencyModesEx(
                Hardware,
                src->srcTransparency,
                src->dstTransparency,
                src->patTransparency,
                fgRop,
                bgRop,
                src->enableDFBColorKeyMode
                ));

            /*******************************************************************
            ** Setup ROP.
            */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x0125C,
                  ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x3 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8))) | (((gctUINT32) ((gctUINT32) (bgRop) & ((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:0) - (0 ? 7:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:0) - (0 ? 7:0) + 1))))))) << (0 ? 7:0))) | (((gctUINT32) ((gctUINT32) (fgRop) & ((gctUINT32) ((((1 ? 7:0) - (0 ? 7:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:0) - (0 ? 7:0) + 1))))))) << (0 ? 7:0)))
                ));

            /* Set target global color. */
            gcmONERROR(gcoHARDWARE_SetTargetGlobalColor(
                Hardware,
                src->dstGlobalColor
                ));

            if (useSource)
            {
                if (Command == gcv2D_CLEAR)
                {
                    gcmONERROR(gcoHARDWARE_Load2DState32(
                        Hardware,
                        0x0120C,
                        ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)))
                        ));
                }
                else
                {
                    gctUINT32 transparency;

                    /* Load the palette for Index8 source. */
                    if (src->srcSurface.format == gcvSURF_INDEX8)
                    {
                        gcmONERROR(gcoHARDWARE_LoadPalette(
                            Hardware,
                            State->paletteFirstIndex,
                            State->paletteIndexCount,
                            State->paletteTable,
                            State->paletteConvert,
                            dstFormat,
                            &State->paletteProgram,
                            &State->paletteConvertFormat
                            ));
                    }

                    /* Set src global color for A8 source. */
                    if (src->srcSurface.format == gcvSURF_A8)
                    {
                        gcmONERROR(gcoHARDWARE_SetSourceGlobalColor(
                            Hardware,
                            src->srcGlobalColor
                            ));
                    }

                    /* Use the src rect for the parameter setting stage */
                    gcmONERROR(gcoHARDWARE_SetSource(
                        Hardware,
                        &src->srcRect
                        ));

                    /* Get PE 1.0 transparency from new transparency modes. */
                    gcmONERROR(gcoHARDWARE_TranslateTransparencies(
                        Hardware,
                        src->srcTransparency,
                        src->dstTransparency,
                        src->patTransparency,
                        &transparency
                        ));

                    switch (src->srcType)
                    {
                    case gcv2D_SOURCE_MONO:
                        gcmONERROR(gcoHARDWARE_SetMonochromeSource(
                            Hardware,
                            (gctUINT8)src->srcMonoTransparencyColor,
                            src->srcMonoPack,
                            src->srcRelativeCoord,
                            src->srcFgColor,
                            src->srcBgColor,
                            src->srcColorConvert,
                            dstFormat,
                            src->srcStream,
                            transparency
                            ));
                        break;

                    case gcv2D_SOURCE_MASKED:
                        gcmONERROR(gcoHARDWARE_SetMaskedSource(
                            Hardware,
                            &src->srcSurface,
                            src->srcRelativeCoord,
                            src->srcMonoPack,
                            transparency
                            ));
                        break;

                    case gcv2D_SOURCE_COLOR:
                        gcmONERROR(gcoHARDWARE_SetColorSource(
                            Hardware,
                            &src->srcSurface,
                            src->srcRelativeCoord,
                            transparency,
                            src->srcYUVMode
                            ));

                        if (Hardware->hw2DDEEnhance1
                            && ((Command == gcv2D_BLT)
                            || (Command == gcv2D_STRETCH)))
                        {
                            gctUINT32 power2BlockWidth = 3;
                            gctUINT32 power2BlockHeight = 3;
                            gctUINT32 srcBpp;

                            gcmONERROR(gcoHARDWARE_ConvertFormat(
                                src->srcSurface.format,
                                &srcBpp,
                                gcvNULL));

                            if ((srcBpp == 16) || (srcBpp == 12))
                            {
                                power2BlockHeight = 5;
                            }
                            else if (srcBpp == 32)
                            {
                                power2BlockHeight = 4;
                            }

                            if ((dstBpp == 16) || (dstBpp == 12))
                            {
                                power2BlockWidth = 5;
                            }
                            else if (dstBpp == 32)
                            {
                                power2BlockWidth = 4;
                            }

                            /* Config block size. */
                            if ((power2BlockWidth != 3) || (power2BlockHeight != 3))
                            {
                                gcmONERROR(gcoHARDWARE_Load2DState32(
                                    Hardware,
                                    0x01324,
                                      ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (power2BlockWidth) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                                    | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (power2BlockHeight) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)))
                                    ));
                            }

                            /* Config quad. */
                            if ((State->dstSurface.rotation == gcvSURF_90_DEGREE)
                                || (State->dstSurface.rotation == gcvSURF_270_DEGREE)
                                || (src->srcSurface.rotation == gcvSURF_90_DEGREE)
                                || (src->srcSurface.rotation == gcvSURF_270_DEGREE))
                            {
                                destConfig = ((((gctUINT32) (destConfig)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 27:27) - (0 ? 27:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 27:27) - (0 ? 27:27) + 1))))))) << (0 ? 27:27))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 27:27) - (0 ? 27:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 27:27) - (0 ? 27:27) + 1))))))) << (0 ? 27:27)));

                                if (Command == gcv2D_BLT)
                                {
                                    destConfig = ((((gctUINT32) (destConfig)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1))))))) << (0 ? 28:28))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1))))))) << (0 ? 28:28)));
                                }

                                /* Overwrite dest config for new walker quad.*/
                                gcmONERROR(gcoHARDWARE_Load2DState32(
                                    Hardware,
                                    0x01234,
                                    ((((gctUINT32) (destConfig)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1))))))) << (0 ? 28:28))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 28:28) - (0 ? 28:28) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:28) - (0 ? 28:28) + 1))))))) << (0 ? 28:28)))
                                    ));
                            }
                        }
                        /* Set src color key range */
                        if (src->srcTransparency == gcv2D_KEYED)
                        {
                            gcmONERROR(gcoHARDWARE_SetSourceColorKeyRange(
                                Hardware,
                                src->srcColorKeyLow,
                                src->srcColorKeyHigh,
                                gcvTRUE,
                                src->srcSurface.format
                                ));
                        }
                        break;

                    default:
                        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
                    }
                }
            }

            if (src->enableAlpha)
            {
                /* Set alphablend states */
                gcmONERROR(gcoHARDWARE_EnableAlphaBlend(
                    Hardware,
                    src->srcAlphaMode,
                    src->dstAlphaMode,
                    src->srcGlobalAlphaMode,
                    src->dstGlobalAlphaMode,
                    src->srcFactorMode,
                    src->dstFactorMode,
                    src->srcColorMode,
                    src->dstColorMode,
                    (gctUINT8)(src->srcGlobalColor >> 24),
                    (gctUINT8)(src->dstGlobalColor >> 24)
                    ));
            }
            else
            {
                gcmONERROR(gcoHARDWARE_DisableAlphaBlend(Hardware));
            }

            /* Set multiply modes. */
            gcmONERROR(gcoHARDWARE_SetMultiplyModes(
                Hardware,
                src->srcPremultiplyMode,
                src->dstPremultiplyMode,
                src->srcPremultiplyGlobalMode,
                src->dstDemultiplyMode,
                src->srcGlobalColor
                ));
        }
        /* the multi src registers. */
        else
        {
            /* Load the palette for Index8 source.
               It is shared by all the multi source. */
            if (uploadPaletteTable
                && (src->srcSurface.format == gcvSURF_INDEX8))
            {
                gcmONERROR(gcoHARDWARE_LoadPalette(
                    Hardware,
                    State->paletteFirstIndex,
                    State->paletteIndexCount,
                    State->paletteTable,
                    State->paletteConvert,
                    dstFormat,
                    &State->paletteProgram,
                    &State->paletteConvertFormat
                    ));

                uploadPaletteTable = gcvFALSE;
            }

            if (Hardware->hw2DNewFeature0)
            {
                /* 8x source setting. */
                gcmONERROR(gcoHARDWARE_SetMultiSourceEx(
                    Hardware,
                    srcCurrent,
                    i,
                    State
                    ));
            }
            else
            {
                /* 4x source setting. */
                gcmONERROR(gcoHARDWARE_SetMultiSource(
                    Hardware,
                    srcCurrent,
                    i,
                    State
                    ));
            }

            if (!multiSrcRot)
            {
                multiSrcRot = (src->srcSurface.rotation == gcvSURF_270_DEGREE)
                     || (src->srcSurface.rotation == gcvSURF_90_DEGREE);
            }

            if (!multiSrcNoneLinear)
            {
                multiSrcNoneLinear = src->srcSurface.tiling != gcvLINEAR;
            }
        }

        srcCurrent++;
    }

    if (Command == gcv2D_MULTI_SOURCE_BLT)
    {
        gctUINT8 horBlk, verBlk;

        if (multiSrcNoneLinear)
        {
            horBlk = 0x1;
            verBlk = 0x4;
        }
        else if (multiSrcRot)
        {
            horBlk = 0x0;
            verBlk = 0x5;
        }
        else
        {
            horBlk = 0x3;
            verBlk = 0x0;
        }

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01308,
            ((((gctUINT32) (0x00000000)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0))) | (((gctUINT32) ((gctUINT32) (srcCurrent - 1) & ((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0)))
            | ((((gctUINT32) (0x00000000)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 10:8) - (0 ? 10:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 10:8) - (0 ? 10:8) + 1))))))) << (0 ? 10:8))) | (((gctUINT32) ((gctUINT32) (horBlk) & ((gctUINT32) ((((1 ? 10:8) - (0 ? 10:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 10:8) - (0 ? 10:8) + 1))))))) << (0 ? 10:8)))
            | ((((gctUINT32) (0x00000000)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 18:16) - (0 ? 18:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 18:16) - (0 ? 18:16) + 1))))))) << (0 ? 18:16))) | (((gctUINT32) ((gctUINT32) (verBlk) & ((gctUINT32) ((((1 ? 18:16) - (0 ? 18:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 18:16) - (0 ? 18:16) + 1))))))) << (0 ? 18:16)))
            ));
    }

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

gceSTATUS gcoHARDWARE_End2DFrame(
    IN gcoHARDWARE Hardware,
    IN gctBOOL SourceFlush)
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Hardware=0x%x",
                    Hardware);

    if (SourceFlush && (Hardware->hw2DAppendCacheFlush == gcvTRUE))
    {
        gcmONERROR(_Append2DCacheFlush(Hardware));
    }

    /* Flush the Tile cache if available. */
    if (Hardware->hw2DOPF)
    {
        gcmONERROR(gcoHARDWARE_Load2DState32(
                    Hardware,
                    0x01650,
                    ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)))));
    }

    /* Flush the 2D pipe. */
    gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x0380C,
                ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)))));

    /* Semaphore & Stall. */
    gcmONERROR(gcoHARDWARE_Load2DState32(Hardware,
                                  0x03808,
                                  ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8))) | (((gctUINT32) (0x07 & ((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8)))
                                  | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0)))
                                  ));

    if (Hardware->hw2DCmdBuffer != gcvNULL)
    {
        Hardware->hw2DCmdBuffer[Hardware->hw2DCmdIndex] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x09 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)));
        Hardware->hw2DCmdIndex += 1;

        Hardware->hw2DCmdBuffer[Hardware->hw2DCmdIndex] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8))) | (((gctUINT32) (0x07 & ((gctUINT32) ((((1 ? 12:8) - (0 ? 12:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:8) - (0 ? 12:8) + 1))))))) << (0 ? 12:8)))
                          | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0)));
        Hardware->hw2DCmdIndex += 1;
    }
    else
    {
        Hardware->hw2DCmdIndex += 2;
    }


    if (Hardware->hw2DCmdBuffer != gcvNULL)
    {
        if (Hardware->hw2DCmdSize < Hardware->hw2DCmdIndex)
        {
            /* Fatal error: full all the buffer with NOP */
            gcmONERROR(gcvSTATUS_OUT_OF_MEMORY);
        }

        /* Fill redundant buffer with NOP */
        if (Hardware->hw2DCmdSize > Hardware->hw2DCmdIndex)
        {
            gcmONERROR(gcoHARDWARE_2DAppendNop(Hardware));
        }

        gcmASSERT(Hardware->hw2DCmdSize == Hardware->hw2DCmdIndex);
    }

OnError:

    /* Return the status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_Get2DResourceUsage
**
**  Determines the usage of 2D resources (source/pattern/destination).
**
**  INPUT:
**
**      gctUINT8 FgRop
**      gctUINT8 BgRop
**          Foreground and background ROP codes.
**
**      gctUINT32 SrcTransparency
**          Current source transparency mode in hardware encoding.
**
**  OUTPUT:
**
**      gctBOOL_PTR UseSource
**      gctBOOL_PTR UsePattern
**      gctBOOL_PTR UseDestination
**          Resource usage flags to be determined and returned.
**          gcvNULL is allowed for the unwanted flags.
**
*/
void gcoHARDWARE_Get2DResourceUsage(
    IN gctUINT8 FgRop,
    IN gctUINT8 BgRop,
    IN gce2D_TRANSPARENCY SrcTransparency,
    OUT gctBOOL_PTR UseSource,
    OUT gctBOOL_PTR UsePattern,
    OUT gctBOOL_PTR UseDestination
    )
{
    gcmHEADER_ARG("FgRop=%x BgRop=%x SrcTransparency=%d "
                    "UseSource=0x%x UsePattern=0x%x UseDestination=0x%x",
                    FgRop, BgRop, SrcTransparency,
                    UseSource, UsePattern, UseDestination);

    /* Determine whether we need the source for the operation. */
    if (UseSource != gcvNULL)
    {
        if (SrcTransparency == gcv2D_KEYED)
        {
            *UseSource = gcvTRUE;
        }
        else
        {
            /* Determine whether this is target only operation. */
            gctBOOL targetOnly
                =  ((FgRop == 0x00) && (BgRop == 0x00))     /* Blackness.    */
                || ((FgRop == 0x55) && (BgRop == 0x55))     /* Invert.       */
                || ((FgRop == 0xAA) && (BgRop == 0xAA))     /* No operation. */
                || ((FgRop == 0xFF) && (BgRop == 0xFF));    /* Whiteness.    */

            *UseSource
                = !targetOnly
                && ((((FgRop >> 2) & 0x33) != (FgRop & 0x33))
                ||  (((BgRop >> 2) & 0x33) != (BgRop & 0x33)));
        }
    }

    /* Determine whether we need the pattern for the operation. */
    if (UsePattern != gcvNULL)
    {
        *UsePattern
            =  (((FgRop >> 4) & 0x0F) != (FgRop & 0x0F))
            || (((BgRop >> 4) & 0x0F) != (BgRop & 0x0F));
    }

    /* Determine whether we need the destiantion for the operation. */
    if (UseDestination != gcvNULL)
    {
        *UseDestination
            =  (((FgRop >> 1) & 0x55) != (FgRop & 0x55))
            || (((BgRop >> 1) & 0x55) != (BgRop & 0x55));
    }

    gcmFOOTER_NO();
}

/*******************************************************************************
**
**  gco2D_GetMaximumDataCount
**
**  Retrieve the maximum number of 32-bit data chunks for a single DE command.
**
**  INPUT:
**
**      Nothing
**
**  OUTPUT:
**
**      gctUINT32
**          Data count value.
*/
gctUINT32 gco2D_GetMaximumDataCount(
    void
    )
{
    gctUINT32 result;

    gcmHEADER();

    result = ((gctUINT32) ((((1 ? 26:16) - (0 ? 26:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:16) - (0 ? 26:16) + 1)))));

    gcmFOOTER_ARG("return=%d", result);
    return result;
}

/*******************************************************************************
**
**  gco2D_GetMaximumRectCount
**
**  Retrieve the maximum number of rectangles, that can be passed in a single DE command.
**
**  INPUT:
**
**      Nothing
**
**  OUTPUT:
**
**      gctUINT32
**          Rectangle count value.
*/
gctUINT32 gco2D_GetMaximumRectCount(
    void
    )
{
    gctUINT32 result;

    gcmHEADER();

    result = ((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1)))));

    gcmFOOTER_ARG("return=%d", result);
    return result;
}

/*******************************************************************************
**
**  gco2D_GetPixelAlignment
**
**  Returns the pixel alignment of the surface.
**
**  INPUT:
**
**      gceSURF_FORMAT Format
**          Pixel format.
**
**  OUTPUT:
**
**      gcsPOINT_PTR Alignment
**          Pointer to the pixel alignment values.
*/
gceSTATUS gco2D_GetPixelAlignment(
    gceSURF_FORMAT Format,
    gcsPOINT_PTR Alignment
    )
{
    gceSTATUS status;
    const gctUINT32 BITS_PER_CACHELINE = 64 * 8;

    gcmHEADER_ARG("Format=%d Alignment=0x%x", Format, Alignment);

    /* Verify the argument. */
    gcmDEBUG_VERIFY_ARGUMENT(Alignment != gcvNULL);

    do
    {
        /* Get format's specifics. */
        gcsSURF_FORMAT_INFO_PTR format[2];
        gcmERR_BREAK(gcoSURF_QueryFormat(Format, format));

        /* Determine horizontal alignment. */
        Alignment->x = BITS_PER_CACHELINE / format[0]->bitsPerPixel;

        /* Vertical alignment for GC600 is simple. */
        Alignment->y = 1;
    }
    while (gcvFALSE);

    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Set2DClearColor
**
**  Set 2D clear color.
**  For PE 2.0, the color is specified in A8R8G8B8 format.
**  For older PE, the color is specified in destination format.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gctUINT32 Color
**          32-bit clear color value.
**
**      gctBOOL ColorConvert
**          If set to gcvTRUE, the 32-bit values in the table are assumed to be
**          in ARGB8 format and will be converted by the hardware to the
**          destination format as needed.
**          If set to gcvFALSE, the 32-bit values in the table are assumed to be
**          preconverted to the destination format.
**
**  OUTPUT:
**
**      gceSTATUS
**          Returns gcvSTATUS_OK if successful.
*/
gceSTATUS gcoHARDWARE_Set2DClearColor(
    IN gcoHARDWARE Hardware,
    IN gctUINT32 Color,
    IN gceSURF_FORMAT DstFormat
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x Color=%x DstFormat=%d",
                    Hardware, Color, DstFormat);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

    if (Hardware->hw2DEngine && !Hardware->sw2DEngine)
    {
        if (Hardware->hw2DPE20)
        {
            /* LoadState(AQDE_CLEAR_PIXEL_VALUE_LOW, 1), LoColor. */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x012C0,
                Color
                ));
        }
        else
        {
            /* Convert color in to destination format. */
            gcmONERROR(gcoHARDWARE_ColorConvertFromARGB8(
                DstFormat,
                1,
                &Color,
                &Color
                ));

            /* LoadState(AQDE_CLEAR_BYTE_MASK, 1), 0xFF. */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01268,
                ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:0) - (0 ? 7:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:0) - (0 ? 7:0) + 1))))))) << (0 ? 7:0))) | (((gctUINT32) ((gctUINT32) (~0) & ((gctUINT32) ((((1 ? 7:0) - (0 ? 7:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:0) - (0 ? 7:0) + 1))))))) << (0 ? 7:0)))
                ));

            /* LoadState(AQDE_CLEAR_PIXEL_VALUE_LOW, 1), LoColor. */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01270,
                Color
                ));

            /* LoadState(AQDE_CLEAR_PIXEL_VALUE_HIGH, 1), HiColor. */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01274,
                Color
                ));
        }
    }
    else
    {
        /* 2D clear is not currently supported by the software renderer. */
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

OnError:
    /* Return result. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_SetBitBlitMirror
**
**  Enable/disable 2D BitBlt mirrorring.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gctBOOL HorizontalMirror
**          Horizontal mirror enable flag.
**
**      gctBOOL VerticalMirror
**          Vertical mirror enable flag.
**
**  OUTPUT:
**
**      gceSTATUS
**          Returns gcvSTATUS_OK if successful.
*/
gceSTATUS gcoHARDWARE_SetBitBlitMirror(
    IN gcoHARDWARE Hardware,
    IN gctBOOL HorizontalMirror,
    IN gctBOOL VerticalMirror
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x HorizontalMirror=%d VerticalMirror=%d",
                    Hardware, HorizontalMirror, VerticalMirror);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

    do
    {
        if (Hardware->hw2DEngine && !Hardware->sw2DEngine)
        {
            gctUINT32 mirror;
            gctUINT32 config;

            if (Hardware->mirrorExtension)
            {
                /* Determine the mirror value. */
                if (HorizontalMirror)
                {
                    if (VerticalMirror)
                    {
                        mirror = 0x3;
                    }
                    else
                    {
                        mirror = 0x1;
                    }
                }
                else
                {
                    if (VerticalMirror)
                    {
                        mirror = 0x2;
                    }
                    else
                    {
                        mirror = 0x0;
                    }
                }

                if (Hardware->shadowRotAngleReg)
                {
                    config = ((((gctUINT32) (Hardware->rotAngleRegShadow)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16))) | (((gctUINT32) ((gctUINT32) (mirror) & ((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16)));

                    /* Save the shadow value. */
                    Hardware->rotAngleRegShadow = config;
                }
                else
                {
                    /* Enable the mirror. */
                    config = ((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 19:19) - (0 ? 19:19) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 19:19) - (0 ? 19:19) + 1))))))) << (0 ? 19:19))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 19:19) - (0 ? 19:19) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 19:19) - (0 ? 19:19) + 1))))))) << (0 ? 19:19)));

                    /* Configure the mirror. */
                    config = ((((gctUINT32) (config)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16))) | (((gctUINT32) ((gctUINT32) (mirror) & ((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16)));
                }

                /* Set mirror configuration. */
                gcmONERROR(gcoHARDWARE_Load2DState32(
                    Hardware,
                    0x012BC,
                    config
                    ));
            }
            else
            {
                /* Determine the mirror value. */
                if (HorizontalMirror)
                {
                    if (VerticalMirror)
                    {
                        mirror = 0x3;
                    }
                    else
                    {
                        mirror = 0x1;
                    }
                }
                else
                {
                    if (VerticalMirror)
                    {
                        mirror = 0x2;
                    }
                    else
                    {
                        mirror = 0x0;
                    }
                }

                /* Configure the mirror. */
                config
                    = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) ((gctUINT32) (((mirror == 0x0) ? 0x0 : 0x1)) & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)))
                    | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 5:4) - (0 ? 5:4) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 5:4) - (0 ? 5:4) + 1))))))) << (0 ? 5:4))) | (((gctUINT32) ((gctUINT32) (mirror) & ((gctUINT32) ((((1 ? 5:4) - (0 ? 5:4) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 5:4) - (0 ? 5:4) + 1))))))) << (0 ? 5:4)));

                /* Set mirror configuration. */
                gcmONERROR(gcoHARDWARE_Load2DState32(
                    Hardware,
                    0x0126C,
                    config
                    ));
            }
        }
        else
        {
            /* 2D clear is not currently supported by the software renderer. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }
    while (gcvFALSE);

    /* Success. */
    gcmFOOTER();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

static int _DrawRectangle(gctUINT32_PTR memory, gcsRECT_PTR SrcRect, gcsRECT_PTR DestRect)
{
    int size = 0;

    if (SrcRect)
    {
        /* 0x01210 */
        memory[size++] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                  | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (2) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16)))
                  | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (0x01210 >> 2) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));

        /* 0x01210 */
        memory[size++]
            = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (SrcRect->left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (SrcRect->top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));

        gcmDUMP(gcvNULL,
                "@[state 0x%04X 0x%08X]",
                0x0484, memory[size - 1]);

        /* 0x01214 */
        memory[size++]
            = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (SrcRect->right  - SrcRect->left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (SrcRect->bottom - SrcRect->top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));

        gcmDUMP(gcvNULL,
                "@[state 0x%04X 0x%08X]",
                0x0485, memory[size - 1]);

        size++;
    }

    /* StartDE(RectCount). */
    memory[size++]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x04 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8)));
    size++;

    /* Append the rectangle. */
    memory[size++]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (DestRect->left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (DestRect->top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));
    memory[size++]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (DestRect->right) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (DestRect->bottom) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));

    gcmDUMP(gcvNULL, "@[draw2d 1 0x00000000");
    gcmDUMP(gcvNULL,
            "  %d,%d %d,%d",
            DestRect->left, DestRect->top,
            DestRect->right, DestRect->bottom);
    gcmDUMP(gcvNULL, "] -- draw2d");

    /*******************************************************************
    ** Program 3 dummy state load at addr 0x0001.
    */
    memory[size++] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                   | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16)))
                   | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (0x00004 >> 2) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));

    memory[size++] = 0;

    memory[size++] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                   | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16)))
                   | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (0x00004 >> 2) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));

    memory[size++] = 0;

    memory[size++] = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x01 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                   | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 25:16) - (0 ? 25:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 25:16) - (0 ? 25:16) + 1))))))) << (0 ? 25:16)))
                   | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (0x00004 >> 2) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)));

    memory[size++] = 0;

    return size;
}

#if SPLIT_RECT
static SPLIT_RECT_MODE
_PreSplitRectangle(
    IN gcs2D_State_PTR State,
    IN gcoHARDWARE Hardware,
    IN gcsRECT_PTR DestRect,
    IN gctUINT32 DestRectCount,
    OUT gctUINT32_PTR CmdSize)
{
    gctBOOL useSrc = gcvFALSE, useBrush = gcvFALSE, swap = gcvFALSE;
    gceSURF_ROTATION rot;
    gctUINT32 i;
    gctUINT32 rectNum = 0;
    SPLIT_RECT_MODE smode = SPLIT_RECT_MODE_NONE;
    gctBOOL hMirror = State->horMirror;
    gctBOOL vMirror = State->verMirror;

    gcoHARDWARE_Get2DResourceUsage(
        State->multiSrc[State->currentSrcIndex].fgRop,
        State->multiSrc[State->currentSrcIndex].bgRop,
        State->multiSrc[State->currentSrcIndex].srcTransparency,
        &useSrc, &useBrush, gcvNULL
        );

    if (!Hardware->fullBitBlitRotation
        || Hardware->hw2DDEEnhance1
        || !useSrc || useBrush)
    {
        return SPLIT_RECT_MODE_NONE;
    }

    Hardware->srcRot = rot =
        State->multiSrc[State->currentSrcIndex].srcSurface.rotation;
    Hardware->dstRot = State->dstSurface.rotation;
    Hardware->horMirror = State->horMirror;
    Hardware->verMirror = State->verMirror;
    Hardware->clipRect = State->clipRect;
    Hardware->srcRelated = State->multiSrc[State->currentSrcIndex].srcRelativeCoord;

    if (State->dstSurface.rotation == gcvSURF_FLIP_X)
    {
        hMirror = !hMirror;
    }
    else if (State->dstSurface.rotation == gcvSURF_FLIP_Y)
    {
        vMirror = !vMirror;
    }

    if (rot == gcvSURF_FLIP_X)
    {
        hMirror = !hMirror;
        rot = gcvSURF_0_DEGREE;
    }
    else if (rot == gcvSURF_FLIP_Y)
    {
        vMirror = !vMirror;
        rot = gcvSURF_0_DEGREE;
    }

    if (gcmIS_SUCCESS(gcsRECT_RelativeRotation(State->dstSurface.rotation, &rot)))
    {
        if ((rot == gcvSURF_90_DEGREE) || (rot == gcvSURF_270_DEGREE))
        {
            smode = SPLIT_RECT_MODE_COLUMN;
        }
        else
        {
            if (Hardware->mmuVersion || (!(State->dstSurface.node.physical & 0x80000000)
                && !(State->multiSrc[State->currentSrcIndex].srcSurface.node.physical & 0x80000000)))
            {
                return SPLIT_RECT_MODE_NONE;
            }

            smode = SPLIT_RECT_MODE_LINE;
        }
    }
    else
    {
        return SPLIT_RECT_MODE_NONE;
    }

    if ((State->dstSurface.rotation == gcvSURF_90_DEGREE)
        || (State->dstSurface.rotation == gcvSURF_270_DEGREE))
    {
        gctBOOL tmp = hMirror;
        hMirror = vMirror;
        vMirror = tmp;

        swap = gcvTRUE;
    }

    for (i = 0; i < DestRectCount; i++)
    {
        if (smode == SPLIT_RECT_MODE_COLUMN)
        {
            if (swap)
            {
                rectNum += ((DestRect[i].bottom - DestRect[i].top) >> SPLIT_COLUMN) + 2;
            }
            else
            {
                rectNum += ((DestRect[i].right - DestRect[i].left) >> SPLIT_COLUMN) + 2;
            }
        }
        else
        {
            if (swap)
            {
                rectNum += DestRect[i].right - DestRect[i].left;
            }
            else
            {
                rectNum += DestRect[i].bottom - DestRect[i].top;
            }
        }
    }

    if (rectNum * 14 > (gcdCMD_BUFFER_SIZE >> 1))
    {
        return SPLIT_RECT_MODE_NONE;
    }

    State->dstSurface.rotation = gcvSURF_0_DEGREE;
    State->multiSrc[State->currentSrcIndex].srcSurface.rotation = rot;
    State->horMirror = hMirror;
    State->verMirror = vMirror;
    State->clipRect.left = 0;
    State->clipRect.top = 0;
    State->clipRect.right = 0x7FFF;
    State->clipRect.bottom = 0x7FFF;
    State->multiSrc[State->currentSrcIndex].srcRelativeCoord = gcvFALSE;

    *CmdSize = rectNum * 14;

    return smode;
}

static int _SplitRectangle(
    gcs2D_State_PTR State,
    gcoHARDWARE Hardware,
    SPLIT_RECT_MODE Mode,
    gctUINT32_PTR Memory,
    gcsRECT_PTR SrcRect,
    gcsRECT_PTR DestRect)
{
    gctINT32 n, size = 0;
    gcsRECT srcRect, dstRect;

    dstRect.left = gcmMAX(DestRect->left, Hardware->clipRect.left);
    dstRect.top = gcmMAX(DestRect->top, Hardware->clipRect.top);
    dstRect.right = gcmMIN(DestRect->right, Hardware->clipRect.right);
    dstRect.bottom = gcmMIN(DestRect->bottom, Hardware->clipRect.bottom);

    if (Hardware->srcRelated)
    {
        srcRect.left = SrcRect->left + dstRect.left;
        srcRect.top = SrcRect->top + dstRect.top;
    }
    else
    {
        srcRect.left = SrcRect->left + dstRect.left - DestRect->left;
        srcRect.top = SrcRect->top + dstRect.top - DestRect->top;
    }

    srcRect.right = dstRect.right - dstRect.left + srcRect.left;
    srcRect.bottom = dstRect.bottom - dstRect.top + srcRect.top;

    if (Hardware->dstRot == gcvSURF_FLIP_X)
    {
        n = dstRect.left;
        dstRect.left = State->dstSurface.alignedWidth - dstRect.right;
        dstRect.right = State->dstSurface.alignedWidth - n;
    }
    else if (Hardware->dstRot == gcvSURF_FLIP_Y)
    {
        n = dstRect.top;
        dstRect.top = State->dstSurface.alignedHeight - dstRect.bottom;
        dstRect.bottom = State->dstSurface.alignedHeight - n;
    }

    if (Hardware->srcRot == gcvSURF_FLIP_X)
    {
        n = srcRect.left;
        srcRect.left = State->multiSrc[State->currentSrcIndex].srcSurface.alignedWidth - srcRect.right;
        srcRect.right = State->multiSrc[State->currentSrcIndex].srcSurface.alignedWidth - n;
    }
    else if (Hardware->srcRot == gcvSURF_FLIP_Y)
    {
        n = srcRect.top;
        srcRect.top = State->multiSrc[State->currentSrcIndex].srcSurface.alignedHeight - srcRect.bottom;
        srcRect.bottom = State->multiSrc[State->currentSrcIndex].srcSurface.alignedHeight - n;
    }

    if (gcvSTATUS_OK != gcsRECT_Rotate(
            &dstRect,
            Hardware->dstRot,
            State->dstSurface.rotation,
            State->dstSurface.alignedWidth,
            State->dstSurface.alignedHeight))
    {
        return 0;
    }

    if (gcvSTATUS_OK != gcsRECT_Rotate(
            &srcRect,
            Hardware->srcRot,
            State->multiSrc[State->currentSrcIndex].srcSurface.rotation,
            State->multiSrc[State->currentSrcIndex].srcSurface.alignedWidth,
            State->multiSrc[State->currentSrcIndex].srcSurface.alignedHeight))
    {
        return 0;
    }

    if (Mode == SPLIT_RECT_MODE_COLUMN)
    {
        gctINT32 dLeft = dstRect.left;
        gctINT32 dRight = dstRect.right;
        gctINT32 sLeft = srcRect.left;
        gctINT32 sRight = srcRect.right;

        n = (gcmALIGN(dRight, SPLIT_COLUMN_WIDTH) - (dLeft & SPLIT_COLUMN_WIDTH_MASK)) / SPLIT_COLUMN_WIDTH;

        while (n > 0)
        {
            dstRect.right = gcmMIN(dRight, (dstRect.left + SPLIT_COLUMN_WIDTH) & SPLIT_COLUMN_WIDTH_MASK);

            if (State->horMirror)
            {
                srcRect.right = dLeft + sRight - dstRect.left;
                srcRect.left = srcRect.right - (dstRect.right - dstRect.left);
            }
            else
            {
                srcRect.left = dstRect.left - dLeft + sLeft;
                srcRect.right = srcRect.left + dstRect.right - dstRect.left;
            }

            size += _DrawRectangle(Memory + size, &srcRect, &dstRect);

            dstRect.left = dstRect.right;
            --n;
        }
    }
    else
    {
        n = dstRect.bottom - dstRect.top;

        while (n > 0)
        {
            dstRect.bottom = dstRect.top + 1;

            if (State->verMirror)
            {
                srcRect.top = srcRect.bottom - 1;
            }
            else
            {
                srcRect.bottom = srcRect.top + 1;
            }

            size += _DrawRectangle(Memory + size, &srcRect, &dstRect);

            ++dstRect.top;

            if (State->verMirror)
            {
                --srcRect.bottom;
            }
            else
            {
                ++srcRect.top;
            }

            --n;
        }
    }

    return size;
}
#endif

/*******************************************************************************
**
**  gcoHARDWARE_StartDE
**
**  Start a DE command for one or more source and destination rectangles.
**
**  INPUT:
**
**      gce2D_COMMAND Command
**          2D engine command to be executed.
**
**      gctUINT32 SrcRectCount
**          Set as 1, for single source rectangle.
**          Set as DestRectCount, if each blit has its own source rectangle.
**
**      gcsRECT_PTR SrcRect
**          Pointer to an array of source rectangles.
**
**      gctUINT32 DestRectCount
**          Number of destination rectangles to be operated on.
**
**      gcsRECT_PTR DestRect
**          Pointer to an array of destination rectangles.
**
**      gctUINT32 FgRop
**      gctUINT32 BgRop
**          Foreground and background ROP codes.
**
**  OUTPUT:
**
**      gceSTATUS
**          Returns gcvSTATUS_OK if successful.
*/
gceSTATUS gcoHARDWARE_StartDE(
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command,
    IN gctUINT32 SrcRectCount,
    IN gcsRECT_PTR SrcRect,
    IN gctUINT32 DestRectCount,
    IN gcsRECT_PTR DestRect
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcoHARDWARE hardware = gcvNULL;
#if SPLIT_RECT
    SPLIT_RECT_MODE smode = SPLIT_RECT_MODE_NONE;
#endif

    gcmHEADER_ARG("State=0x%x Command=0x%x SrcRectCount=%d "
                    "SrcRect=0x%x DestRectCount=%d DestRect=0x%x "
                    "FgRop=%x BgRop=%x",
                    State, Command, SrcRectCount,
                    SrcRect, DestRectCount, DestRect);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    if ((DestRectCount < 1) || (DestRect == gcvNULL)
        || ((Command != gcv2D_CLEAR) && (Command != gcv2D_BLT)
            && (Command != gcv2D_STRETCH) && (Command != gcv2D_MULTI_SOURCE_BLT))
        || ((!SrcRect || ((SrcRectCount != DestRectCount)))
            && (SrcRect || SrcRectCount != 0)))
    {
        gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
    }

    do
    {
        gctUINT32 idx;

        /* Validate rectangle coordinates. */
        if (SrcRect)
        {
            for (idx = 0; idx < SrcRectCount; idx++)
            {
                if (!_IsValidRect(SrcRect + idx))
                {
                    gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
                }
            }
        }

        for (idx = 0; idx < DestRectCount; idx++)
        {
            if (!_IsValidRect(DestRect + idx))
            {
                gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
            }
        }

        if (hardware->hw2DEngine && !hardware->sw2DEngine)
        {
            gctUINT32 loopCount = 0;
            gcoCMDBUF reserve;
            gctUINT32_PTR memory = gcvNULL;
            gctUINT32 dataSize = DestRectCount * ((SrcRect == gcvNULL) ? 10 : 14);

#if SPLIT_RECT
            if (Command == gcv2D_BLT)
            {
                smode = _PreSplitRectangle(State, hardware, DestRect, DestRectCount, &dataSize);
            }
#endif
            hardware->hw2DCmdBuffer = gcvNULL;
            hardware->hw2DCmdSize = 0;
            hardware->hw2DCmdIndex = _ReserveBufferSize(hardware, State, Command);

            if (hardware->hw2DCmdIndex)
            {
                hardware->hw2DCmdIndex += dataSize;
            }

            while (hardware->hw2DCmdBuffer == gcvNULL)
            {
                if (hardware->hw2DCmdIndex)
                {
                    gcmONERROR(gcoBUFFER_Reserve(
                        hardware->buffer,
                        hardware->hw2DCmdIndex * gcmSIZEOF(gctUINT32),
                        gcvTRUE,
                        &reserve
                        ));

                    hardware->hw2DCmdBuffer = gcmUINT64_TO_PTR(reserve->lastReserve);
                    hardware->hw2DCmdSize = hardware->hw2DCmdIndex;
                    hardware->hw2DCmdIndex = 0;
                }

            gcmONERROR(gcoHARDWARE_Set2DState(hardware, State, Command));

            /*******************************************************************
            ** Allocate and configure StartDE command buffer.
            */

            if (SrcRect == gcvNULL)
            {
                if (hardware->hw2DCmdBuffer != gcvNULL)
                {
                memory = hardware->hw2DCmdBuffer + hardware->hw2DCmdIndex;
                do
                {
#if SPLIT_RECT
                    if (smode != SPLIT_RECT_MODE_NONE)
                    {
                        memory += _SplitRectangle(
                            State,
                            hardware,
                            smode,
                            memory,
                            &State->multiSrc[State->currentSrcIndex].srcRect,
                            DestRect);
                    }
                    else
#endif
                    {
                        /* Draw a dest rectangle. */
                        memory += _DrawRectangle(memory, gcvNULL, DestRect);
                    }

                    DestRectCount --;
                    DestRect ++;
                    loopCount++;
                }
                while (DestRectCount && loopCount < MAX_LOOP_COUNT);
                }

                hardware->hw2DCmdIndex +=
                    (!memory) ? dataSize
                    : (memory - hardware->hw2DCmdBuffer - hardware->hw2DCmdIndex);
            }
            else
            {
                /* Force to draw one rectange at a time. */
                if (hardware->hw2DCmdBuffer != gcvNULL)
                {
                memory = hardware->hw2DCmdBuffer + hardware->hw2DCmdIndex;
                do
                {
#if SPLIT_RECT
                    /* Program source rectangle for each destination rectangle. */
                    if (smode != SPLIT_RECT_MODE_NONE)
                    {
                        memory += _SplitRectangle(
                            State,
                            hardware,
                            smode,
                            memory,
                            SrcRect,
                            DestRect);
                    }
                    else
#endif
                    {
                        memory += _DrawRectangle(memory, SrcRect, DestRect);
                    }

                    /* Move to next SrcRect and DestRect. */
                    SrcRect++;
                    DestRect++;
                    loopCount++;
                }
                while (--DestRectCount && loopCount < MAX_LOOP_COUNT);
                }

                hardware->hw2DCmdIndex +=
                    (!memory) ? dataSize
                    : (memory - hardware->hw2DCmdBuffer - hardware->hw2DCmdIndex);
            }

            gcmONERROR(gcoHARDWARE_End2DFrame(
                hardware,
                gcvTRUE
                ));
            }
        }
        else
        {
            /* Call software renderer. */
            gcmONERROR(_RenderRectangle(
                hardware,
                State,
                Command,
                DestRectCount,
                DestRect
                ));
        }
    }
    while (gcvFALSE);

OnError:

#if SPLIT_RECT
    if (smode != SPLIT_RECT_MODE_NONE && hardware!= gcvNULL)
    {
        State->multiSrc[State->currentSrcIndex].srcSurface.rotation
            = hardware->srcRot;
        State->dstSurface.rotation = hardware->dstRot;
        State->horMirror = hardware->horMirror;
        State->verMirror = hardware->verMirror;
        State->clipRect = hardware->clipRect;
        State->multiSrc[State->currentSrcIndex].srcRelativeCoord = hardware->srcRelated;
    }
#endif

    if (hardware != gcvNULL)
    {
        if (hardware->hw2DEngine && !hardware->sw2DEngine)
        {
            /* Reset command buffer. */
            gcoHARDWARE_Reset2DCmdBuffer(hardware, gcmIS_ERROR(status));
        }
    }

    /* Return result. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_StartDELine
**
**  Start a DE command to draw one or more Lines, with a common or
**  individual color.
**
**  INPUT:
**
**      gce2D_COMMAND Command
**          2D engine command to be executed.
**
**      gctUINT32 RectCount
**          Number of destination rectangles to be operated on.
**
**      gcsRECT_PTR DestRect
**          Pointer to an array of destination rectangles.
**
**      gctUINT32 ColorCount
**          Set as 0, if using brush.
**          Set as 1, if single color for all lines.
**          Set as LineCount, if each line has its own color.
**
**      gctUINT32_PTR Color32
**          Source color array in A8R8G8B8 format.
**
**      gctUINT32 FgRop
**      gctUINT32 BgRop
**          Foreground and background ROP codes.
**
**  OUTPUT:
**
**      gceSTATUS
**          Returns gcvSTATUS_OK if successful.
*/
gceSTATUS gcoHARDWARE_StartDELine(
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command,
    IN gctUINT32 LineCount,
    IN gcsRECT_PTR DestRect,
    IN gctUINT32 ColorCount,
    IN gctUINT32_PTR Color32
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcoHARDWARE hardware = gcvNULL;

    gcmHEADER_ARG("Command=0x%x LineCount=%d "
                    "DestRect=0x%x ColorCount=%d Color32=%x",
                    Command, LineCount,
                    DestRect, ColorCount, Color32);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);
    gcmASSERT((ColorCount == 1) || (ColorCount == 0) || (ColorCount == LineCount));
    gcmASSERT(LineCount);

    do
    {
        gctUINT32 idx;

        /* Validate line coordinates. */
        for (idx = 0; idx < LineCount; idx++)
        {
            if ((DestRect[idx].left < 0)
                || (DestRect[idx].top < 0)
                || (DestRect[idx].right < 0)
                || (DestRect[idx].bottom < 0)
                || (DestRect[idx].left > 65535)
                || (DestRect[idx].top > 65535)
                || (DestRect[idx].right > 65535)
                || (DestRect[idx].bottom > 65535))
            {
                gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
            }
        }

        if (hardware->hw2DEngine && !hardware->sw2DEngine)
        {
            gctUINT32 i, maxLineCount, leftLineCount;
            gctUINT32 colorConfig[2], lastProgrammedColor = 0;
            gcoCMDBUF reserve;
            gctUINT32_PTR memory;
            gcsRECT_PTR currentDestRect;
            gctUINT32 loopCount = 0;

            hardware->hw2DCmdBuffer = gcvNULL;
            hardware->hw2DCmdSize = 0;
            hardware->hw2DCmdIndex = _ReserveBufferSize(hardware, State, Command);

            if (hardware->hw2DCmdIndex)
            {
                hardware->hw2DCmdIndex += (LineCount + ColorCount) * 4;
            }

            while (hardware->hw2DCmdBuffer == gcvNULL)
            {
                if (hardware->hw2DCmdIndex)
                {
                    gcmONERROR(gcoBUFFER_Reserve(
                        hardware->buffer,
                        hardware->hw2DCmdIndex * gcmSIZEOF(gctUINT32),
                        gcvTRUE,
                        &reserve
                        ));

                    hardware->hw2DCmdBuffer = gcmUINT64_TO_PTR(reserve->lastReserve);
                    hardware->hw2DCmdSize = hardware->hw2DCmdIndex;
                    hardware->hw2DCmdIndex = 0;
                }
            gcmONERROR(gcoHARDWARE_Set2DState(hardware, State, Command));

            /*******************************************************************
            ** Allocate and configure StartDE command buffer.  Subdivide into
            ** multiple commands if leftLineCount exceeds maxLineCount.
            */

            maxLineCount = gco2D_GetMaximumRectCount();
            leftLineCount = LineCount;
            currentDestRect = DestRect;

            if (ColorCount)
            {
                /* Set last programmed color different from *Color32,
                   so that the first color always gets programmed. */
                lastProgrammedColor = *Color32 + 1;
            }

            do
            {
                /* Render upto maxRectCount rectangles. */
                gctUINT32 lineCount = (leftLineCount < maxLineCount)
                                    ? leftLineCount
                                    : maxLineCount;

                /* Program color for each line. */
                if (ColorCount && (lastProgrammedColor != *Color32))
                {
                    /* Backgroud color. */
                    colorConfig[0] = *Color32;

                    /* Foreground color. */
                    colorConfig[1] = *Color32;

                    /* Save last programmed color. */
                    lastProgrammedColor = *Color32;

                    /* LoadState(AQDE_SRC_COLOR_BG, 2), BgColor, FgColor. */
                    gcmONERROR(gcoHARDWARE_Load2DState(
                        hardware,
                        0x01218, 2,
                        colorConfig
                        ));
                }

                /* Find the number of following lines with same color. */
                if (ColorCount > 1)
                {
                    gctUINT32 sameColoredLines = 1;

                    Color32++;

                    while (sameColoredLines < lineCount)
                    {
                        if (lastProgrammedColor != *Color32)
                        {
                            break;
                        }

                        Color32++;
                        sameColoredLines++;
                    }

                    lineCount = sameColoredLines;
                }

                if (hardware->hw2DCmdBuffer != gcvNULL)
                {
                memory = hardware->hw2DCmdBuffer + hardware->hw2DCmdIndex;
                /* StartDE(RectCount). */
                *memory++ = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x04 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                          | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8))) | (((gctUINT32) ((gctUINT32) (lineCount) & ((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8)));
                memory++;

                gcmDUMP(gcvNULL, "@[draw2d %u 0x00000000", lineCount);

                /* Append the rectangles. */
                for (i = 0; i < lineCount; i++)
                {
                    *memory++ = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (currentDestRect[i].left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                              | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (currentDestRect[i].top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));
                    *memory++ = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (currentDestRect[i].right) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                              | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (currentDestRect[i].bottom) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));

                    gcmDUMP(gcvNULL,
                            "  %d,%d %d,%d",
                            currentDestRect[i].left, currentDestRect[i].top,
                            currentDestRect[i].right, currentDestRect[i].bottom);
                }
                }
                hardware->hw2DCmdIndex += 2 + lineCount * 2;
                gcmDUMP(gcvNULL, "] -- draw2d");

                leftLineCount -= lineCount;
                currentDestRect += lineCount;
                loopCount++;
            }
            while (leftLineCount && loopCount < MAX_LOOP_COUNT);

            /*******************************************************************
            ** Program a dummy state load at addr 0x0001.
            */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                    hardware,
                    0x00004,
                    0x0
                    ));

            gcmONERROR(gcoHARDWARE_Load2DState32(
                    hardware,
                    0x00004,
                    0x0
                    ));

            gcmONERROR(gcoHARDWARE_End2DFrame(
                hardware,
                gcvTRUE
                ));
            }
        }
        else
        {
            /* Call software renderer. */
            gcmONERROR(_RenderRectangle(
                hardware,
                State,
                Command,
                LineCount,
                DestRect
                ));
        }
    }
    while (gcvFALSE);

OnError:

    if (hardware != gcvNULL)
    {
        if (hardware->hw2DEngine && !hardware->sw2DEngine)
        {
            /* Reset command buffer. */
            gcoHARDWARE_Reset2DCmdBuffer(hardware, gcmIS_ERROR(status));
        }
    }

    /* Return result. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_StartDEStream
**
**  Start a DE command with a monochrome stream source.
**
**  INPUT:
**
**      gcsRECT_PTR DestRect
**          Pointer to the destination rectangles.
**
**      gctUINT32 FgRop
**      gctUINT32 BgRop
**          Foreground and background ROP codes.
**
**      gctUINT32 StreamSize
**          Size of the stream in bytes.
**
**  OUTPUT:
**
**      gctPOINTER * StreamBits
**          Pointer to an allocated buffer for monochrome data.
*/
gceSTATUS gcoHARDWARE_StartDEStream(
    IN gcs2D_State_PTR State,
    IN gcsRECT_PTR DestRect,
    IN gctUINT32 StreamSize,
    OUT gctPOINTER * StreamBits
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcoHARDWARE hardware = gcvNULL;

    gcmHEADER_ARG("DestRect=0x%x StreamSize=%d StreamBits=0x%x",
                  DestRect, StreamSize, StreamBits);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(DestRect != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(StreamBits != gcvNULL);

    do
    {
        if (!_IsValidRect(DestRect))
        {
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }

        if (hardware->hw2DEngine && !hardware->sw2DEngine)
        {
            gctUINT32 dataCount;
            gcoCMDBUF reserve;
            gctUINT32_PTR memory;
            gctUINT32 dataSize = (2 + 2) * sizeof(gctUINT32) + StreamSize;/* Determine the command size. */

            hardware->hw2DCmdBuffer = gcvNULL;
            hardware->hw2DCmdSize = 0;
            hardware->hw2DCmdIndex = _ReserveBufferSize(hardware, State, gcv2D_BLT);

            if (hardware->hw2DCmdIndex)
            {
                hardware->hw2DCmdIndex += gcmALIGN(dataSize, 8) >> 2;
            }

            while (hardware->hw2DCmdBuffer == gcvNULL)
            {
                if (hardware->hw2DCmdIndex)
                {
                    gcmONERROR(gcoBUFFER_Reserve(
                        hardware->buffer,
                        hardware->hw2DCmdIndex * gcmSIZEOF(gctUINT32),
                        gcvTRUE,
                        &reserve
                        ));

                    hardware->hw2DCmdBuffer = gcmUINT64_TO_PTR(reserve->lastReserve);
                    hardware->hw2DCmdSize = hardware->hw2DCmdIndex;
                    hardware->hw2DCmdIndex = 0;
                }

            gcmONERROR(gcoHARDWARE_Set2DState(hardware, State, gcv2D_BLT));

            /*******************************************************************
            ** Allocate and configure StartDE command buffer.
            */
            if (hardware->hw2DCmdBuffer != gcvNULL)
            {
            memory = hardware->hw2DCmdBuffer + hardware->hw2DCmdIndex;
            /* Determine the data count. */
            dataCount = StreamSize >> 2;

            /* StartDE(DataCount). */
            *memory++
                = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27))) | (((gctUINT32) (0x04 & ((gctUINT32) ((((1 ? 31:27) - (0 ? 31:27) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:27) - (0 ? 31:27) + 1))))))) << (0 ? 31:27)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8))) | (((gctUINT32) ((gctUINT32) (1) & ((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 26:16) - (0 ? 26:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:16) - (0 ? 26:16) + 1))))))) << (0 ? 26:16))) | (((gctUINT32) ((gctUINT32) (dataCount) & ((gctUINT32) ((((1 ? 26:16) - (0 ? 26:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:16) - (0 ? 26:16) + 1))))))) << (0 ? 26:16)));
            *memory++
                = 0;

            gcmDUMP(gcvNULL, "@[prim2d 1 0x%08X", dataCount);

            /* Append the rectangle. */
            *memory++
                = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (DestRect->left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (DestRect->top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));
            *memory++
                = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (DestRect->right) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (DestRect->bottom) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));

            gcmDUMP(gcvNULL, "  %d,%d %d,%d",
                    DestRect->left, DestRect->top,
                    DestRect->right, DestRect->bottom);

            /* Set the stream location. */
            *StreamBits = memory;
            }
            hardware->hw2DCmdIndex += gcmALIGN(dataSize, 8) >> 2;

            /*******************************************************************
            ** Program a dummy state load at addr 0x0001.
            */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                    hardware,
                    0x00004,
                    0x0
                    ));

            gcmONERROR(gcoHARDWARE_Load2DState32(
                    hardware,
                    0x00004,
                    0x0
                    ));

            gcmONERROR(gcoHARDWARE_End2DFrame(
                hardware,
                gcvTRUE
                ));
            }
        }
        else
        {
            /* Monochrome operations are not currently supported. */
            gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
        }
    }
    while (gcvFALSE);

OnError:

    if (hardware != gcvNULL)
    {
        if (hardware->hw2DEngine && !hardware->sw2DEngine)
        {
            /* Reset command buffer. */
            gcoHARDWARE_Reset2DCmdBuffer(hardware, gcmIS_ERROR(status));
        }
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}


/*******************************************************************************
**
**  gcoHARDWARE_TranslateCommand
**
**  Translate API 2D command to its hardware value.
**
**  INPUT:
**
**      gce2D_COMMAND APIValue
**          API value.
**
**  OUTPUT:
**
**      gctUINT32 * HwValue
**          Corresponding hardware value.
*/
gceSTATUS gcoHARDWARE_TranslateCommand(
    IN gce2D_COMMAND APIValue,
    OUT gctUINT32 * HwValue
    )
{
    gcmHEADER_ARG("APIValue=%d HwValue=0x%x", APIValue, HwValue);

    /* Dispatch on command. */
    switch (APIValue)
    {
    case gcv2D_CLEAR:
        *HwValue = 0x0;
        break;

    case gcv2D_LINE:
        *HwValue = 0x1;
        break;

    case gcv2D_BLT:
        *HwValue = 0x2;
        break;

    case gcv2D_STRETCH:
        *HwValue = 0x4;
        break;

    case gcv2D_HOR_FILTER:
        *HwValue = 0x5;
        break;

    case gcv2D_VER_FILTER:
        *HwValue = 0x6;
        break;

    case gcv2D_MULTI_SOURCE_BLT:
        *HwValue = 0x8;
        break;

    default:
        /* Not supported. */
        gcmFOOTER_ARG("status=%d", gcvSTATUS_NOT_SUPPORTED);
        return gcvSTATUS_NOT_SUPPORTED;
    }

    /* Success. */
    gcmFOOTER_ARG("*HwValue=%d", *HwValue);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoHARDWARE_Clear2D
**
**  Clear one or more rectangular areas.
**
**  INPUT:
**
**      gctUINT32 RectCount
**          The number of rectangles to draw. The array of line positions
**          pointed to by Position parameter must have at least RectCount
**          positions.
**
**      gcsRECT_PTR Rect
**          Points to an array of positions in (x0, y0)-(x1, y1) format.
**
**      gctUINT32 Color
**          32-bit clear color value.
**
**      gctBOOL ColorConvert
**          If set to gcvTRUE, the 32-bit values in the table are assumed to be
**          in ARGB8 format and will be converted by the hardware to the
**          destination format as needed.
**          If set to gcvFALSE, the 32-bit values in the table are assumed to be
**          preconverted to the destination format.
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
gcoHARDWARE_Clear2D(
    IN gcs2D_State_PTR State,
    IN gctUINT32 RectCount,
    IN gcsRECT_PTR Rect
    )
{
    gcoHARDWARE hardware;
    gceSTATUS status;
    gctUINT8 fgRop = 0, bgRop = 0;

    gcmHEADER_ARG("RectCount=%d Rect=0x%x",
                  RectCount, Rect);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    if (!hardware->hw2DPE20)
    {
        fgRop = State->multiSrc[State->currentSrcIndex].fgRop;
        bgRop = State->multiSrc[State->currentSrcIndex].bgRop;
        State->multiSrc[State->currentSrcIndex].fgRop = 0x0;
        State->multiSrc[State->currentSrcIndex].bgRop = 0x0;
    }

    if (Rect == gcvNULL)
    {
        /* Has target surface been set?. */
        if (State->dstSurface.type == gcvSURF_TYPE_UNKNOWN)
        {
            gcmONERROR(gcvSTATUS_INVALID_OBJECT);
        }

        /* Use target rectangle as clear rectangle. */
        Rect = &State->dstSurface.rect;
    }

    /* Kick off 2D engine. */
    gcmONERROR(gcoHARDWARE_StartDE(
        State, gcv2D_CLEAR, 0, gcvNULL, RectCount, Rect
        ));

    if (!hardware->hw2DPE20)
    {
        State->multiSrc[State->currentSrcIndex].fgRop = fgRop;
        State->multiSrc[State->currentSrcIndex].bgRop = bgRop;
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Line2DEx
**
**  Draw one or more Bresenham lines using solid color(s).
**
**  INPUT:
**
**      gctUINT32 LineCount
**          The number of lines to draw. The array of line positions pointed
**          to by Position parameter must have at least LineCount positions.
**
**      gcsRECT_PTR Position
**          Points to an array of positions in (x0, y0)-(x1, y1) format.
**
**      gctUINT32 ColorCount
**          Set as 1, if single color for all lines.
**          Set as LineCount, if each line has its own color.
**
**      gctUINT32_PTR Color32
**          Source color array in A8R8G8B8 format.
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
gcoHARDWARE_Line2DEx(
    IN gcs2D_State_PTR State,
    IN gctUINT32 LineCount,
    IN gcsRECT_PTR Position,
    IN gctUINT32 ColorCount,
    IN gctUINT32_PTR Color32
    )
{
    gceSTATUS status;
    /*gcoHARDWARE hardware;*/
    gcs2D_State_PTR state;
    gce2D_SOURCE type;
    gctBOOL stream;
    gcsRECT rect;

    gcmHEADER_ARG("LineCount=%d Position=0x%x "
                  "ColorCount=%d Color32=0x%x",
                  LineCount, Position,
                  ColorCount, Color32);

    /*gcmGETHARDWARE(hardware);*/

    /* Verify the arguments. */
    /*gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);*/
    gcmASSERT((ColorCount == 1) || (ColorCount == LineCount));

    /* Backup user setting. */
    state  = (gcs2D_State_PTR) State;
    type   = state->multiSrc[state->currentSrcIndex].srcType;
    stream = state->multiSrc[state->currentSrcIndex].srcStream;
    rect   = state->multiSrc[state->currentSrcIndex].srcRect;

    /* Set the solid color using a monochrome stream. */
    state->multiSrc[state->currentSrcIndex].srcType = gcv2D_SOURCE_MONO;
    state->multiSrc[state->currentSrcIndex].srcStream = gcvFALSE;
    state->multiSrc[state->currentSrcIndex].srcRect.left = 0;
    state->multiSrc[state->currentSrcIndex].srcRect.right = 0;
    state->multiSrc[state->currentSrcIndex].srcRect.top = 0;
    state->multiSrc[state->currentSrcIndex].srcRect.bottom = 0;

    /* Kick off 2D engine. */
    gcmONERROR(gcoHARDWARE_StartDELine(
        State, gcv2D_LINE, LineCount, Position, ColorCount, Color32
        ));

    /* revert user setting. */
    state->multiSrc[state->currentSrcIndex].srcType = type;
    state->multiSrc[state->currentSrcIndex].srcStream = stream;
    state->multiSrc[state->currentSrcIndex].srcRect = rect;

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_MonoBlit
**
**  Monochrome blit.
**
**  INPUT:
**
**      gctPOINTER StreamBits
**          Pointer to the monochrome bitmap.
**
**      gcsPOINT_PTR StreamSize
**          Size of the monochrome bitmap in pixels.
**
**      gcsRECT_PTR StreamRect
**          Bounding rectangle of the area within the bitmap to render.
**
**      gceSURF_MONOPACK SrcStreamPack
**          Source bitmap packing.
**
**      gceSURF_MONOPACK DestStreamPack
**          Packing of the bitmap in the command stream.
**
**      gcsRECT_PTR DestRect
**          Pointer to an array of destination rectangles.
**
**      gctUINT32 FgRop
**          Foreground and background ROP codes.
**
**      gctUINT32 BgRop
**          Background ROP to use with transparent pixels.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_MonoBlit(
    IN gcs2D_State_PTR State,
    IN gctPOINTER StreamBits,
    IN gcsPOINT_PTR StreamSize,
    IN gcsRECT_PTR StreamRect,
    IN gceSURF_MONOPACK SrcStreamPack,
    IN gceSURF_MONOPACK DestStreamPack,
    IN gcsRECT_PTR DestRect
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;
    gctUINT32 srcStreamWidth, srcStreamHeight;
    gctUINT32 destStreamWidth, destStreamHeight;
    gctUINT32 srcPackWidth, srcPackHeight;
    gctUINT32 destPackWidth, destPackHeight;
    gctUINT32 destStreamSize;
    gctUINT32_PTR buffer;
    gctPOINTER pointer;

    gcmHEADER_ARG("StreamBits=0x%x StreamSize=%d StreamRect=0x%x "
                    "SrcStreamPack=%d DestStreamPack=%d DestRect=0x%x",
                    StreamBits, StreamSize, StreamRect,
                    SrcStreamPack, DestStreamPack, DestRect);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Verify the arguments. */
    gcmDEBUG_VERIFY_ARGUMENT(StreamBits != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(StreamRect != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(StreamSize != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(DestRect != gcvNULL);

    /* Get stream pack sizes. */
    gcmONERROR(gco2D_GetPackSize(
        SrcStreamPack,
        &srcPackWidth,
        &srcPackHeight
        ));

    gcmONERROR(gco2D_GetPackSize(
        DestStreamPack,
        &destPackWidth,
        &destPackHeight
        ));

    /* Determine the size of the stream. */
    destStreamWidth  = StreamRect->right  - StreamRect->left;
    destStreamHeight = StreamRect->bottom - StreamRect->top;

    /* Align the height, verify alignment of the width. */
    gcmASSERT((destStreamWidth & (destPackWidth - 1)) == 0);
    destStreamHeight = gcmALIGN(destStreamHeight, destPackHeight);

    /* Determine the size of the stream in bytes and in 32-bitters. */
    destStreamSize = (destStreamWidth * destStreamHeight) >> 3;
    gcmASSERT((destStreamSize & 3) == 0);

    /* Determine the size of the source stream in pixels. */
    srcStreamWidth  = gcmALIGN(StreamSize->x, srcPackWidth);
    srcStreamHeight = gcmALIGN(StreamSize->y, srcPackHeight);

    /* Call lower layer to form a StartDE command. */
    gcmONERROR(gcoHARDWARE_StartDEStream(
        State,
        DestRect,
        destStreamSize,
        &pointer
        ));

    buffer = pointer;

    /* Same packing and entire stream? */
    if ((SrcStreamPack   == DestStreamPack) &&
        (srcStreamWidth  == destStreamWidth) &&
        (srcStreamHeight == destStreamHeight) &&
        (StreamRect->left == 0) &&
        (StreamRect->top == 0))
    {
        gcmASSERT(
            (StreamRect->left == 0) && (StreamRect->top == 0)
            );

        gcoOS_MemCopy(
            buffer,
            StreamBits,
            destStreamSize
            );
    }
    else
    {
        gctUINT8_PTR srcStream;
        gctUINT8_PTR dstStream;

        /* Compute the offset into the source stream in bits/pixels. */
        gctUINT32 srcOffset = (SrcStreamPack == gcvSURF_UNPACKED)
            ?  StreamRect->top * srcStreamWidth + StreamRect->left
            : (StreamRect->left & ~(srcPackWidth - 1)) * srcStreamHeight +
              (StreamRect->left &  (srcPackWidth - 1)) +
               StreamRect->top  *   srcPackWidth;

        /* Adjust to get the offset in bytes. */
        gcmASSERT((srcOffset & 7) == 0);
        srcOffset >>= 3;

        /* Set stream bases. */
        srcStream = (gctUINT8_PTR) StreamBits + srcOffset;
        dstStream = (gctUINT8_PTR) buffer;

        /* Same packing? */
        if ((SrcStreamPack == DestStreamPack) &&
            ((StreamRect->left & (srcPackWidth - 1)) == 0))
        {
            gctUINT32 count;
            gctUINT32 passCount;
            gctUINT32 step;
            gctUINT32 copySize;
            gctUINT32 srcStride;

            /* Must be pack aligned. */
            gcmASSERT((srcOffset       & ((srcPackWidth >> 3) - 1)) == 0);
            gcmASSERT((srcStreamWidth  & (srcPackWidth       - 1)) == 0);
            gcmASSERT((destStreamWidth & (destPackWidth      - 1)) == 0);

            if (DestStreamPack == gcvSURF_UNPACKED)
            {
                srcStride = srcStreamWidth  >> 3;
                copySize  = destStreamWidth >> 3;

                /* One line at a time. */
                step      = 1;
                passCount = destStreamHeight;
            }
            else
            {
                srcStride = (srcPackWidth  * srcStreamHeight)  >> 3;
                copySize  = (destPackWidth * destStreamHeight) >> 3;

                /* One packed column at a time. */
                step      = destPackWidth;
                passCount = destStreamWidth;
            }

            for (count = 0; count < passCount; count += step)
            {
                gcoOS_MemCopy(dstStream, srcStream, copySize);
                srcStream += srcStride;
                dstStream += copySize;
            }
        }
        else
        {
            gctUINT32 destX, destY;

            gctUINT8_PTR srcLine = srcStream;
            gctUINT8_PTR destLine = dstStream;

            gctUINT32 srcLineStep, destLineStep;
            gctUINT32 srcByteIntStep, srcByteExtStep;
            gctUINT32 destByteIntStep, destByteExtStep;

            if (SrcStreamPack == gcvSURF_UNPACKED)
            {
                srcByteIntStep = srcByteExtStep = 1;
                srcLineStep    = srcStreamWidth >> 3;
            }
            else
            {
                srcByteIntStep = 1;
                srcByteExtStep = ((srcPackWidth * srcStreamHeight) - srcPackWidth + 8) >> 3;
                srcLineStep    = srcPackWidth >> 3;
            }

            if (DestStreamPack == gcvSURF_UNPACKED)
            {
                destByteIntStep = destByteExtStep = 1;
                destLineStep    = destStreamWidth >> 3;
            }
            else
            {
                destByteIntStep = 1;
                destByteExtStep = ((destPackWidth * destStreamHeight) - destPackWidth + 8) >> 3;
                destLineStep    = destPackWidth >> 3;
            }

            for (destY = 0; destY < destStreamHeight; destY++)
            {
                gctUINT32 srcX;
                gctUINT8_PTR srcByte  = srcLine;
                gctUINT8_PTR destByte = destLine;

                for (srcX = StreamRect->left, destX = 0;
                     destX < destStreamWidth;)
                {
                    /* Copy the current byte. */
                    *destByte = *srcByte;

                    /* Advance the coordinates. */
                    srcX  += 8;
                    destX += 8;

                    /* Advance the pointers. */
                    srcByte += ((srcX % srcPackWidth) == 0)
                        ? srcByteExtStep
                        : srcByteIntStep;

                    destByte += ((destX % destPackWidth) == 0)
                        ? destByteExtStep
                        : destByteIntStep;
                }

                /* Advance the pointers. */
                srcLine  += srcLineStep;
                destLine += destLineStep;
            }
        }

        /* Reverse the bit order for big Endian */
        if (hardware->bigEndian)
        {
            gctUINT i;
            gctUINT32_PTR p = (gctUINT32_PTR)buffer;

            for (i = 0; i < destStreamSize / sizeof(gctUINT32); i++)
            {
                gctUINT8_PTR p2 = (gctUINT8_PTR)&p[i];

                p[i] = ((gctUINT32)p2[3] << 24)
                        + ((gctUINT32)p2[2] << 16)
                        + ((gctUINT32)p2[1] << 8)
                        + (gctUINT32)p2[0];
            }
        }
    }

#if gcdDUMP
    gcmDUMP_DATA(gcvNULL, "prim2D", buffer, destStreamSize);
#endif

    /* Commit the data. */
    gcmONERROR(gcoHARDWARE_Commit());

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}


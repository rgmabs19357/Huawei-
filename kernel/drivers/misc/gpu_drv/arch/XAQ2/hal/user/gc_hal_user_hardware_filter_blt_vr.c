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


#include "gc_hal_user.h"

/******************************************************************************\
***************************** Filter Blit Defines *****************************
\******************************************************************************/

typedef enum
{
    gceFILTER_BLIT_TYPE_VERTICAL,
    gceFILTER_BLIT_TYPE_HORIZONTAL,
    gceFILTER_BLIT_TYPE_ONE_PASS,
}
gceFILTER_BLIT_TYPE;

/******************************************************************************\
********************************* Support Code *********************************
\******************************************************************************/

/*******************************************************************************
**
**  _SincFilter
**
**  Sinc filter function.
**
**  INPUT:
**
**      gctFLOAT x
**          x coordinate.
**
**      gctINT32 radius
**          Radius of the filter.
**
**  OUTPUT:
**
**      Nothing.
**
**  RETURN:
**
**      gctFLOAT
**          Function value at x.
*/
static gctFLOAT _SincFilter(
    gctFLOAT x,
    gctINT32 radius
    )
{
    gctFLOAT pit, pitd, f1, f2, result;
    gctFLOAT fRadius = gcoMATH_Int2Float(radius);

    if (x == 0.0f)
    {
        result = 1.0f;
    }
    else if ((x < -fRadius) || (x > fRadius))
    {
        result = 0.0f;
    }
    else
    {
        pit  = gcoMATH_Multiply(gcdPI, x);
        pitd = gcoMATH_Divide(pit, fRadius);

        f1 = gcoMATH_Divide(gcoMATH_Sine(pit), pit);
        f2 = gcoMATH_Divide(gcoMATH_Sine(pitd), pitd);

        result = gcoMATH_Multiply(f1, f2);
    }

    return result;
}

/*******************************************************************************
**
**  _CalculateSyncTable
**
**  Calculate weight array for sync filter.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to a gcoHARDWARE object.
**
**      gctUINT8 KernelSize
**          New kernel size.
**
**      gctUINT32 SrcSize
**          The size in pixels of a source dimension (width or height).
**
**      gctUINT32 DestSize
**          The size in pixels of a destination dimension (width or height).
**
**  OUTPUT:
**
**      gcsFILTER_BLIT_ARRAY_PTR KernelInfo
**          Updated kernel structure and table.
*/
static gceSTATUS _CalculateSyncTable(
    IN gcoHARDWARE Hardware,
    IN gctUINT8 KernelSize,
    IN gctUINT32 SrcSize,
    IN gctUINT32 DestSize,
    OUT gcsFILTER_BLIT_ARRAY_PTR KernelInfo
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Hardware=0x%x KernelSize=%u SrcSize=%u DestSize=%u "
                  "KernelInfo=0x%x",
                  Hardware, KernelSize, SrcSize, DestSize, KernelInfo);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(KernelInfo != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(KernelInfo->filterType == gcvFILTER_SYNC);
    gcmDEBUG_VERIFY_ARGUMENT(SrcSize != 0);
    gcmDEBUG_VERIFY_ARGUMENT(DestSize != 0);

    do
    {
        gctUINT32 scaleFactor;
        gctFLOAT fScale;
        gctINT kernelHalf;
        gctFLOAT fSubpixelStep;
        gctFLOAT fSubpixelOffset;
        gctUINT32 subpixelPos;
        gctINT kernelPos;
        gctINT padding;
        gctUINT16_PTR kernelArray;
        gctPOINTER pointer = gcvNULL;

        /* Compute the scale factor. */
        scaleFactor = gcoHARDWARE_GetStretchFactor(SrcSize, DestSize);

        /* Same kernel size and ratio as before? */
        if ((KernelInfo->kernelSize  == KernelSize) &&
            (KernelInfo->scaleFactor == scaleFactor))
        {
            break;
        }

        /* Allocate the array if not allocated yet. */
        if (KernelInfo->kernelStates == gcvNULL)
        {
            /* Allocate the array. */
            gcmERR_BREAK(
                gcoOS_Allocate(gcvNULL,
                               gcvKERNELSTATES,
                               &pointer));

            KernelInfo->kernelStates = pointer;
        }

        /* Store new parameters. */
        KernelInfo->kernelSize  = KernelSize;
        KernelInfo->scaleFactor = scaleFactor;

        /* Compute the scale factor. */
        fScale = gcoMATH_DivideFromUInteger(DestSize, SrcSize);

        /* Adjust the factor for magnification. */
        if (fScale > 1.0f)
        {
            fScale = 1.0f;
        }

        /* Calculate the kernel half. */
        kernelHalf = (gctINT) (KernelInfo->kernelSize >> 1);

        /* Calculate the subpixel step. */
        fSubpixelStep = gcoMATH_Divide(1.0f,
                                       gcoMATH_Int2Float(gcvSUBPIXELCOUNT));

        /* Init the subpixel offset. */
        fSubpixelOffset = 0.5f;

        /* Determine kernel padding size. */
        padding = (gcvMAXKERNELSIZE - KernelInfo->kernelSize) / 2;

        /* Set initial kernel array pointer. */
        kernelArray = (gctUINT16_PTR) (KernelInfo->kernelStates + 1);

        /* Loop through each subpixel. */
        for (subpixelPos = 0; subpixelPos < gcvSUBPIXELLOADCOUNT; subpixelPos++)
        {
            /* Define a temporary set of weights. */
            gctFLOAT fSubpixelSet[gcvMAXKERNELSIZE];

            /* Init the sum of all weights for the current subpixel. */
            gctFLOAT fWeightSum = 0.0f;
            gctUINT16 weightSum = 0;
            gctINT16 adjustCount, adjustFrom;
            gctINT16 adjustment;

            /* Compute weights. */
            for (kernelPos = 0; kernelPos < gcvMAXKERNELSIZE; kernelPos++)
            {
                /* Determine the current index. */
                gctINT index = kernelPos - padding;

                /* Pad with zeros. */
                if ((index < 0) || (index >= KernelInfo->kernelSize))
                {
                    fSubpixelSet[kernelPos] = 0.0f;
                }
                else
                {
                    if (KernelInfo->kernelSize == 1)
                    {
                        fSubpixelSet[kernelPos] = 1.0f;
                    }
                    else
                    {
                        /* Compute the x position for filter function. */
                        gctFLOAT fX =
                            gcoMATH_Multiply(
                                gcoMATH_Add(
                                    gcoMATH_Int2Float(index - kernelHalf),
                                    fSubpixelOffset),
                                fScale);

                        /* Compute the weight. */
                        fSubpixelSet[kernelPos] = _SincFilter(fX, kernelHalf);
                    }

                    /* Update the sum of weights. */
                    fWeightSum = gcoMATH_Add(fWeightSum,
                                             fSubpixelSet[kernelPos]);
                }
            }

            /* Adjust weights so that the sum will be 1.0. */
            for (kernelPos = 0; kernelPos < gcvMAXKERNELSIZE; kernelPos++)
            {
                /* Normalize the current weight. */
                gctFLOAT fWeight = gcoMATH_Divide(fSubpixelSet[kernelPos],
                                                  fWeightSum);

                /* Convert the weight to fixed point and store in the table. */
                if (fWeight == 0.0f)
                {
                    kernelArray[kernelPos] = 0x0000;
                }
                else if (fWeight >= 1.0f)
                {
                    kernelArray[kernelPos] = 0x4000;
                }
                else if (fWeight <= -1.0f)
                {
                    kernelArray[kernelPos] = 0xC000;
                }
                else
                {
                    kernelArray[kernelPos] = (gctINT16)
                        gcoMATH_Multiply(fWeight, 16384.0f);
                }

                weightSum += kernelArray[kernelPos];
            }

            /* Adjust the fixed point coefficients. */
            adjustCount = 0x4000 - weightSum;
            if (adjustCount < 0)
            {
                adjustCount = -adjustCount;
                adjustment = -1;
            }
            else
            {
                adjustment = 1;
            }

            adjustFrom = (gcvMAXKERNELSIZE - adjustCount) / 2;

            for (kernelPos = 0; kernelPos < adjustCount; kernelPos++)
            {
                kernelArray[adjustFrom + kernelPos] += adjustment;
            }

            kernelArray += gcvMAXKERNELSIZE;

            /* Advance to the next subpixel. */
            fSubpixelOffset = gcoMATH_Add(fSubpixelOffset, -fSubpixelStep);
        }

        KernelInfo->kernelChanged = gcvTRUE;
    }
    while (gcvFALSE);

    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  _CalculateBlurTable
**
**  Calculate weight array for blur filter.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to a gcoHARDWARE object.
**
**      gctUINT8 KernelSize
**          New kernel size.
**
**      gctUINT32 SrcSize
**          The size in pixels of a source dimension (width or height).
**
**      gctUINT32 DestSize
**          The size in pixels of a destination dimension (width or height).
**
**  OUTPUT:
**
**      gcsFILTER_BLIT_ARRAY_PTR KernelInfo
**          Updated kernel structure and table.
*/
static gceSTATUS _CalculateBlurTable(
    IN gcoHARDWARE Hardware,
    IN gctUINT8 KernelSize,
    IN gctUINT32 SrcSize,
    IN gctUINT32 DestSize,
    OUT gcsFILTER_BLIT_ARRAY_PTR KernelInfo
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    gcmHEADER_ARG("Hardware=0x%x KernelSize=%u SrcSize=%u DestSize=%u "
                  "KernelInfo=0x%x",
                  Hardware, KernelSize, SrcSize, DestSize, KernelInfo);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(KernelInfo != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(KernelInfo->filterType == gcvFILTER_BLUR);
    gcmDEBUG_VERIFY_ARGUMENT(SrcSize != 0);
    gcmDEBUG_VERIFY_ARGUMENT(DestSize != 0);

    do
    {
        gctUINT32 scaleFactor;
        gctUINT32 subpixelPos;
        gctINT kernelPos;
        gctINT padding;
        gctUINT16_PTR kernelArray;
        gctPOINTER pointer = gcvNULL;

        /* Compute the scale factor. */
        scaleFactor = gcoHARDWARE_GetStretchFactor(SrcSize, DestSize);

        /* Same kernel size and ratio as before? */
        if ((KernelInfo->kernelSize  == KernelSize) &&
            (KernelInfo->scaleFactor == scaleFactor))
        {
            break;
        }

        /* Allocate the array if not allocated yet. */
        if (KernelInfo->kernelStates == gcvNULL)
        {
            /* Allocate the array. */
            gcmERR_BREAK(
                gcoOS_Allocate(gcvNULL,
                               gcvKERNELSTATES,
                               &pointer));

            KernelInfo->kernelStates = pointer;
        }

        /* Store new parameters. */
        KernelInfo->kernelSize  = KernelSize;
        KernelInfo->scaleFactor = scaleFactor;

        /* Determine kernel padding size. */
        padding = (gcvMAXKERNELSIZE - KernelInfo->kernelSize) / 2;

        /* Set initial kernel array pointer. */
        kernelArray = (gctUINT16_PTR) (KernelInfo->kernelStates + 1);

        /* Loop through each subpixel. */
        for (subpixelPos = 0; subpixelPos < gcvSUBPIXELLOADCOUNT; subpixelPos++)
        {
            /* Compute weights. */
            for (kernelPos = 0; kernelPos < gcvMAXKERNELSIZE; kernelPos++)
            {
                /* Determine the current index. */
                gctINT index = kernelPos - padding;

                /* Pad with zeros. */
                if ((index < 0) || (index >= KernelInfo->kernelSize))
                {
                    *kernelArray++ = 0x0000;
                }
                else
                {
                    if (KernelInfo->kernelSize == 1)
                    {
                        *kernelArray++ = 0x4000;
                    }
                    else
                    {
                        gctFLOAT fWeight;

                        /* Compute the weight. */
                        fWeight = gcoMATH_Divide(
                            1.0f,
                            gcoMATH_UInt2Float(KernelInfo->kernelSize));
                        *kernelArray++ = (gctINT16) gcoMATH_Multiply(fWeight,
                                                                     16384.0f);
                    }
                }
            }
        }

        KernelInfo->kernelChanged = gcvTRUE;
    }
    while (gcvFALSE);

    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  _LoadKernel
**
**  Program kernel size and kernel weight table.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gcsFILTER_BLIT_ARRAY_PTR Kernel
**          Pointer to kernel array info structure.
**
**  OUTPUT:
**
**      Nothing.
*/
static gceSTATUS _LoadKernel(
    IN gcoHARDWARE Hardware,
    IN gceFILTER_BLIT_KERNEL type,
    IN gcsFILTER_BLIT_ARRAY_PTR Kernel
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x Kernel=0x%x", Hardware, Kernel);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(type < gcvFILTER_BLIT_KERNEL_NUM);
    gcmDEBUG_VERIFY_ARGUMENT(Hardware->loadedKernel[type].kernelAddress != (gctUINT32) ~0);

    do
    {
        /* LoadState(AQDE_FILTER_KERNEL) */
        gcmERR_BREAK(gcoHARDWARE_Load2DState(
            Hardware,
            Hardware->loadedKernel[type].kernelAddress, gcvWEIGHTSTATECOUNT,
            Kernel->kernelStates + 1
            ));

        status = gcvSTATUS_OK;
    }
    while (gcvFALSE);

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  _SetVideoSource
**
**  Program video source registers.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gcsSURF_INFO_PTR Surface
**          Pointer to the source surface descriptor.
**
**      gctUINT32 Address
**      gctUINT32 Stride
**      gctUINT32 UAddress
**      gctUINT32 UStride
**      gctUINT32 VAddress
**      gctUINT32 VStride
**          Addresses and strides of the source.
**
**      gceSURF_FORMAT Format
**          Source surface format.
**
**      gcsRECT_PTR Rect
**          Source image rectangle.
**
**      gcsPOINT_PTR Origin
**          Source origin within the image rectangle.
**
**  OUTPUT:
**
**      Nothing.
*/
static gceSTATUS _SetVideoSource(
    IN gcoHARDWARE Hardware,
    IN gcsSURF_INFO_PTR Surface,
    IN gcsRECT_PTR Rect,
    IN gcsPOINT_PTR Origin,
    IN gce2D_YUV_COLOR_MODE Mode
    )
{
    gceSTATUS status;
    gctUINT32 rotated, config = 0, configEx = 0;
    gctUINT32 memory[4];
    gctUINT32 format, swizzle, isYUVformat;
    gctUINT32 rgbaSwizzle, uvSwizzle;
    gctUINT32 endian;
    gctBOOL cacheMode;

    /* Check the rotation capability. */
    if (!Hardware->fullFilterBlitRotation &&
        Surface->rotation != gcvSURF_0_DEGREE)
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    rotated = gcvFALSE;

    /* Load AQDE_SRC_ROTATION_CONFIG_Address. */
    gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01208,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Surface->alignedWidth) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1))))))) << (0 ? 16:16))) | (((gctUINT32) ((gctUINT32) (rotated) & ((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1))))))) << (0 ? 16:16)))
            ));

    /*--------------------------------------------------------------------*/
    memory[0] = Surface->node.physical;
    memory[1] = Surface->stride;

    gcmONERROR(gcoHARDWARE_Load2DState(
        Hardware,
        0x01200,
        2,
        memory
        ));

    /*--------------------------------------------------------------------*/
    gcmONERROR(gcoHARDWARE_TranslateSourceFormat(
        Hardware, Surface->format, &format, &swizzle, &isYUVformat
        ));

    /* Set endian control */
    endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:30) - (0 ? 31:30) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:30) - (0 ? 31:30) + 1))))))) << (0 ? 31:30))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 31:30) - (0 ? 31:30) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:30) - (0 ? 31:30) + 1))))))) << (0 ? 31:30)));

    if (Hardware->bigEndian)
    {
        gctUINT32 bpp;

        /* Compute bits per pixel. */
        gcmONERROR(gcoHARDWARE_ConvertFormat(Surface->format,
                                             &bpp,
                                             gcvNULL));

        if (bpp == 16)
        {
            endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:30) - (0 ? 31:30) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:30) - (0 ? 31:30) + 1))))))) << (0 ? 31:30))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 31:30) - (0 ? 31:30) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:30) - (0 ? 31:30) + 1))))))) << (0 ? 31:30)));
        }
        else if (bpp == 32)
        {
            endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:30) - (0 ? 31:30) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:30) - (0 ? 31:30) + 1))))))) << (0 ? 31:30))) | (((gctUINT32) (0x2 & ((gctUINT32) ((((1 ? 31:30) - (0 ? 31:30) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:30) - (0 ? 31:30) + 1))))))) << (0 ? 31:30)));
        }
    }

    /* Determine color swizzle. */
    if (isYUVformat)
    {
        rgbaSwizzle = 0x0;
        uvSwizzle   = swizzle;
    }
    else
    {
        rgbaSwizzle = swizzle;
        uvSwizzle   = 0x0;
    }

    switch (Surface->tiling)
    {
    case gcvLINEAR:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7)));

        configEx = 0x00000000;

        break;

    case gcvTILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7)));

        configEx = 0x00000000;

        break;

    case gcvSUPERTILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7)));

        configEx = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)));

        break;

    case gcvMULTI_TILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7)));

        configEx = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)));

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01304,
            Surface->node.physical2
            ));

        break;

    case gcvMULTI_SUPERTILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7)));

        configEx = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)))
                 | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)));

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01304,
            Surface->node.physical2
            ));

        break;

    case gcvMINORTILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7)));

        configEx = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)));

        break;

    default:
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    gcmONERROR(gcoHARDWARE_SetSourceTileStatus(
        Hardware,
        0,
        Surface,
        &cacheMode
        ));

    gcmONERROR(gcoHARDWARE_Load2DState32(
        Hardware,
        0x01300,
        cacheMode ? ((((gctUINT32) (configEx)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1))))))) << (0 ? 12:12))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1))))))) << (0 ? 12:12)))
                  : ((((gctUINT32) (configEx)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1))))))) << (0 ? 12:12))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1))))))) << (0 ? 12:12)))
        ));

    config |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:0) - (0 ? 3:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:0) - (0 ? 3:0) + 1))))))) << (0 ? 3:0))) | (((gctUINT32) ((gctUINT32) (format) & ((gctUINT32) ((((1 ? 3:0) - (0 ? 3:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:0) - (0 ? 3:0) + 1))))))) << (0 ? 3:0)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 28:24) - (0 ? 28:24) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:24) - (0 ? 28:24) + 1))))))) << (0 ? 28:24))) | (((gctUINT32) ((gctUINT32) (format) & ((gctUINT32) ((((1 ? 28:24) - (0 ? 28:24) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 28:24) - (0 ? 28:24) + 1))))))) << (0 ? 28:24)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) ((gctUINT32) (rgbaSwizzle) & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)))
            | endian;

    if (Hardware->hw2D420L2Cache)
    {
        if (((Surface->format == gcvSURF_YV12)
            || (Surface->format == gcvSURF_I420))
            && ((Surface->rotation == gcvSURF_90_DEGREE)
            || (Surface->rotation == gcvSURF_270_DEGREE)))
        {
            config |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 29:29) - (0 ? 29:29) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 29:29) - (0 ? 29:29) + 1))))))) << (0 ? 29:29))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 29:29) - (0 ? 29:29) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 29:29) - (0 ? 29:29) + 1))))))) << (0 ? 29:29)));
        }
    }

    gcmONERROR(gcoHARDWARE_Load2DState32(
        Hardware,
        0x0120C,
        config
        ));

    uvSwizzle = (((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:4) - (0 ? 4:4) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:4) - (0 ? 4:4) + 1))))))) << (0 ? 4:4))) | (((gctUINT32) ((gctUINT32) (uvSwizzle) & ((gctUINT32) ((((1 ? 4:4) - (0 ? 4:4) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:4) - (0 ? 4:4) + 1))))))) << (0 ? 4:4))) &((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 7:7) - (0 ? 7:7) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:7) - (0 ? 7:7) + 1))))))) << (0 ? 7:7))));
    uvSwizzle = (Mode == gcv2D_YUV_601)?
        ((((gctUINT32) (uvSwizzle)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)))
        : ((((gctUINT32) (uvSwizzle)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)));
    uvSwizzle = ((((gctUINT32) (uvSwizzle)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)));

    /* Load source UV swizzle and YUV mode state. */
    gcmONERROR(gcoHARDWARE_Load2DState32(
        Hardware,
        0x012D8,
        uvSwizzle
        ));

    /*--------------------------------------------------------------------*/
    memory[0] = Surface->node.physical2;
    memory[1] = Surface->uStride;
    memory[2] = Surface->node.physical3;
    memory[3] = Surface->vStride;

    gcmONERROR(gcoHARDWARE_Load2DState(
        Hardware,
        0x01284,
        4,
        memory
        ));

    /*--------------------------------------------------------------------*/
    memory[0]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Rect->left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (Rect->top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));
    memory[1]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Rect->right) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (Rect->bottom) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));
    memory[2] = Origin->x;
    memory[3] = Origin->y;

    gcmONERROR(gcoHARDWARE_Load2DState(
        Hardware,
        0x01298,
        4,
        memory
        ));

    if (Hardware->fullFilterBlitRotation)
    {
        gctUINT32 srcRot = 0;
        gctUINT32 value;

        gcmONERROR(gcoHARDWARE_TranslateSourceRotation(Surface->rotation, &srcRot));

        /* Load source height. */
        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x012B8,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Surface->alignedHeight) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
            ));

        /* 0x012BC */
        if (Hardware->shadowRotAngleReg)
        {
            value = ((((gctUINT32) (Hardware->rotAngleRegShadow)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0))) | (((gctUINT32) ((gctUINT32) (srcRot) & ((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0)));

            /* Save the shadow value. */
            Hardware->rotAngleRegShadow = value;
        }
        else
        {
            /* Enable src mask. */
            value = ((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)));

            /* Set src rotation. */
            value = ((((gctUINT32) (value)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0))) | (((gctUINT32) ((gctUINT32) (srcRot) & ((gctUINT32) ((((1 ? 2:0) - (0 ? 2:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 2:0) - (0 ? 2:0) + 1))))))) << (0 ? 2:0)));
        }

        gcmONERROR(gcoHARDWARE_Load2DState32(
                    Hardware,
                    0x012BC,
                    value
                    ));
    }

    /* Success. */
    return gcvSTATUS_OK;

OnError:
    /* Return the error. */
    return status;
}

/*******************************************************************************
**
**  _SetVideoDestination
**
**  Program video destination registers.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gcsSURF_INFO_PTR Surface
**          Pointer to the destination surface descriptor.
**
**      gcsRECT_PTR Rect
**          Destination image rectangle.
**
**  OUTPUT:
**
**      Nothing.
*/
static gceSTATUS _SetVideoDestination(
    IN gcoHARDWARE Hardware,
    IN gcsSURF_INFO_PTR Surface,
    IN gcsRECT_PTR Rect
    )
{
    gceSTATUS status;
    gctUINT32 rotated, config = 0;
    gctUINT32 memory[2];
    gctUINT32 format, swizzle, isYUVformat;
    gctUINT32 endian;

    /* Check the rotation capability. */
    if (!Hardware->fullFilterBlitRotation &&
        Surface->rotation != gcvSURF_0_DEGREE)
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    rotated = gcvFALSE;

    /* Load AQDE_DEST_ROTATION_CONFIG_Address. */
    gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01230,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Surface->alignedWidth) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
                | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1))))))) << (0 ? 16:16))) | (((gctUINT32) ((gctUINT32) (rotated) & ((gctUINT32) ((((1 ? 16:16) - (0 ? 16:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 16:16) - (0 ? 16:16) + 1))))))) << (0 ? 16:16)))
            ));

    /*--------------------------------------------------------------------*/
    memory[0] = Surface->node.physical;
    memory[1] = Surface->stride;

    gcmONERROR(gcoHARDWARE_Load2DState(
        Hardware,
        0x01228,
        2,
        memory
        ));

    /*--------------------------------------------------------------------*/
    gcmONERROR(gcoHARDWARE_TranslateDestinationFormat(
        Surface->format, &format, &swizzle, &isYUVformat
        ));

    /* Set endian control */
    endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)));

    if (Hardware->bigEndian)
    {
        gctUINT32 bpp;

        /* Flush the current pipe. */
        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x0380C,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3)))
            ));

        /* Compute bits per pixel. */
        gcmONERROR(gcoHARDWARE_ConvertFormat(Surface->format,
                                             &bpp,
                                             gcvNULL));

        if (bpp == 16)
        {
            endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)));
        }
        else if (bpp == 32)
        {
            endian = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x2 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)));
        }
    }

    endian |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16))) | (((gctUINT32) ((gctUINT32) (swizzle) & ((gctUINT32) ((((1 ? 17:16) - (0 ? 17:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 17:16) - (0 ? 17:16) + 1))))))) << (0 ? 17:16)));

    switch (Surface->tiling)
    {
    case gcvLINEAR:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)));
        break;

    case gcvTILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x1  & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)));
        break;

    case gcvMINORTILED:
        config = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8)))
               | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 26:26) - (0 ? 26:26) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 26:26) - (0 ? 26:26) + 1))))))) << (0 ? 26:26)));
        break;

    default:
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    config |= ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | (((gctUINT32) ((gctUINT32) (format) & ((gctUINT32) ((((1 ? 4:0) - (0 ? 4:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 4:0) - (0 ? 4:0) + 1))))))) << (0 ? 4:0))) | endian;

    gcmONERROR(gcoHARDWARE_Load2DState32(
        Hardware,
        0x01234,
        config
        ));

    /*--------------------------------------------------------------------*/
    memory[0]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Rect->left) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (Rect->top) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));
    memory[1]
        = ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Rect->right) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
        | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16))) | (((gctUINT32) ((gctUINT32) (Rect->bottom) & ((gctUINT32) ((((1 ? 31:16) - (0 ? 31:16) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:16) - (0 ? 31:16) + 1))))))) << (0 ? 31:16)));

    gcmONERROR(gcoHARDWARE_Load2DState(
        Hardware,
        0x012A8,
        2,
        memory
        ));

    if (Hardware->fullFilterBlitRotation)
    {
        gctUINT32 dstRot = 0;
        gctUINT32 value;

        gcmONERROR(gcoHARDWARE_TranslateDestinationRotation(Surface->rotation, &dstRot));

        /* Load target height. */
        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x012B4,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0))) | (((gctUINT32) ((gctUINT32) (Surface->alignedHeight) & ((gctUINT32) ((((1 ? 15:0) - (0 ? 15:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:0) - (0 ? 15:0) + 1))))))) << (0 ? 15:0)))
            ));

        /* 0x012BC */
        if (Hardware->shadowRotAngleReg)
        {
            value = ((((gctUINT32) (Hardware->rotAngleRegShadow)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 5:3) - (0 ? 5:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 5:3) - (0 ? 5:3) + 1))))))) << (0 ? 5:3))) | (((gctUINT32) ((gctUINT32) (dstRot) & ((gctUINT32) ((((1 ? 5:3) - (0 ? 5:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 5:3) - (0 ? 5:3) + 1))))))) << (0 ? 5:3)));

            /* Save the shadow value. */
            Hardware->rotAngleRegShadow = value;
        }
        else
        {
            /* Enable dst mask. */
            value = ((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 9:9) - (0 ? 9:9) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 9:9) - (0 ? 9:9) + 1))))))) << (0 ? 9:9))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 9:9) - (0 ? 9:9) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 9:9) - (0 ? 9:9) + 1))))))) << (0 ? 9:9)));

            /* Set dst rotation. */
            value = ((((gctUINT32) (value)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 5:3) - (0 ? 5:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 5:3) - (0 ? 5:3) + 1))))))) << (0 ? 5:3))) | (((gctUINT32) ((gctUINT32) (dstRot) & ((gctUINT32) ((((1 ? 5:3) - (0 ? 5:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 5:3) - (0 ? 5:3) + 1))))))) << (0 ? 5:3)));
        }

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x012BC,
            value
            ));
    }

    gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x0130C,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0)))));

    /* Success. */
    return gcvSTATUS_OK;

OnError:
    /* Return status. */
    return status;
}

/*******************************************************************************
**
**  _StartVR
**
**  Start video raster engine.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gctBOOL Horizontal
**          Set to gcvTRUE to start horizontal blit.
**          Set to gcvFALSE to start vertical blit.
**
**  OUTPUT:
**
**      Nothing.
*/
static gceSTATUS _StartVR(
    IN gcoHARDWARE Hardware,
    IN gcs2D_State_PTR State,
    IN gceFILTER_BLIT_TYPE type,
    IN gcsFILTER_BLIT_ARRAY_PTR HorKernel,
    IN gcsFILTER_BLIT_ARRAY_PTR VerKernel,
    IN gcsSURF_INFO_PTR SrcSurface,
    IN gcsRECT_PTR SrcRect,
    IN gcsPOINT_PTR SrcOrigin,
    IN gcsSURF_INFO_PTR DstSurface,
    IN gcsRECT_PTR DstRect,
    IN gctBOOL PrePass
    )
{
    gceSTATUS status = gcvSTATUS_OK;

    do
    {
        gcs2D_MULTI_SOURCE_PTR curSrc = &State->multiSrc[State->currentSrcIndex];
        gctUINT32 blitType = 0;

        Hardware->hw2DCmdBuffer = gcvNULL;
        Hardware->hw2DCmdSize = 0;
        Hardware->hw2DCmdIndex = (type == gceFILTER_BLIT_TYPE_ONE_PASS)? 250 : 170;

        if (SrcSurface->format == gcvSURF_INDEX8)
        {
            Hardware->hw2DCmdIndex += gcmALIGN(State->paletteIndexCount + 1, 2);
        }

        while (Hardware->hw2DCmdBuffer == gcvNULL)
        {
            if (Hardware->hw2DCmdIndex)
            {
                gcoCMDBUF reserve;

                gcmONERROR(gcoBUFFER_Reserve(
                    Hardware->buffer,
                    Hardware->hw2DCmdIndex * gcmSIZEOF(gctUINT32),
                    gcvTRUE,
                    &reserve
                    ));

                Hardware->hw2DCmdBuffer = gcmUINT64_TO_PTR(reserve->lastReserve);
                Hardware->hw2DCmdSize = Hardware->hw2DCmdIndex;
                Hardware->hw2DCmdIndex = 0;
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

        /* Set alphablend states: if filter plus alpha is not supported, make
           sure the alphablend is disabled.
        */
        if (!PrePass && curSrc->enableAlpha)
        {
            if (Hardware->dither2DandAlphablendFilter == gcvFALSE)
            {
                gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
            }

            /* Set alphablend states */
            gcmONERROR(gcoHARDWARE_EnableAlphaBlend(
                    Hardware,
                    curSrc->srcAlphaMode,
                    curSrc->dstAlphaMode,
                    curSrc->srcGlobalAlphaMode,
                    curSrc->dstGlobalAlphaMode,
                    curSrc->srcFactorMode,
                    curSrc->dstFactorMode,
                    curSrc->srcColorMode,
                    curSrc->dstColorMode,
                    (gctUINT8)(curSrc->srcGlobalColor >> 24),
                    (gctUINT8)(curSrc->dstGlobalColor >> 24)
                    ));
        }
        else
        {
            /* LoadState(AQDE_ALPHA_CONTROL, AlphaOff). */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x0127C,
                ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1))))))) << (0 ? 0:0)))));
        }

        /* Set mirror state. */
        if (!PrePass)
        {
            if ((!Hardware->mirrorExtension) && (State->horMirror || State->verMirror))
            {
                gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
            }

            gcmONERROR(gcoHARDWARE_SetBitBlitMirror(
                Hardware,
                State->horMirror,
                State->verMirror
                ));

            /* Set multiply modes. */
            gcmONERROR(gcoHARDWARE_SetMultiplyModes(
                Hardware,
                curSrc->srcPremultiplyMode,
                curSrc->dstPremultiplyMode,
                curSrc->srcPremultiplyGlobalMode,
                curSrc->dstDemultiplyMode,
                curSrc->srcGlobalColor
                ));
        }
        else
        {
            gcmONERROR(gcoHARDWARE_SetBitBlitMirror(
                Hardware,
                gcvFALSE,
                gcvFALSE
                ));

            /* Disable multiply. */
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x012D0,
                0x00000000));
        }

        /* Set 2D dithering. */
        gcmONERROR(gcoHARDWARE_SetDither2D(
            Hardware,
            State->dither
            ));

        switch (type)
        {
        case gceFILTER_BLIT_TYPE_VERTICAL:
            blitType = 0x1;

            gcmONERROR(_LoadKernel(
                Hardware,
                gcvFILTER_BLIT_KERNEL_UNIFIED,
                VerKernel
                ));

            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01224,
                VerKernel->scaleFactor
                ));

            {
                gcsSURF_FORMAT_INFO_PTR srcFormat[2], dstFormat[2];
                gctUINT32 configEx;
                gcmONERROR(gcoSURF_QueryFormat(DstSurface->format, dstFormat));
                gcmONERROR(gcoSURF_QueryFormat(SrcSurface->format, srcFormat));

                if ((SrcSurface->rotation == gcvSURF_90_DEGREE || SrcSurface->rotation == gcvSURF_270_DEGREE
                    || DstSurface->rotation == gcvSURF_90_DEGREE || DstSurface->rotation == gcvSURF_270_DEGREE)
                    && (srcFormat[0]->bitsPerPixel != 32 || dstFormat[0]->bitsPerPixel != 32 ))
                {
                    configEx = (((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) | (((gctUINT32) (0x1 & ((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) &  ((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) );
                }
                else
                {
                    configEx = (((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) &  ((((gctUINT32) (~0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) );
                }

                gcmONERROR(gcoHARDWARE_Load2DState32(
                    Hardware,
                    0x012E4,
                    configEx
                    ));
            }
            break;

        case gceFILTER_BLIT_TYPE_HORIZONTAL:
            blitType = 0x0;

            gcmONERROR(_LoadKernel(
                Hardware,
                gcvFILTER_BLIT_KERNEL_UNIFIED,
                HorKernel
                ));

            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01220,
                HorKernel->scaleFactor
                ));

            break;

        case gceFILTER_BLIT_TYPE_ONE_PASS:
            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x012E4,
                ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 8:8) - (0 ? 8:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 8:8) - (0 ? 8:8) + 1))))))) << (0 ? 8:8))) |
                ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:4) - (0 ? 7:4) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:4) - (0 ? 7:4) + 1))))))) << (0 ? 7:4))) | (((gctUINT32) ((gctUINT32) (gcmMAX(HorKernel->kernelSize, VerKernel->kernelSize)) & ((gctUINT32) ((((1 ? 7:4) - (0 ? 7:4) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:4) - (0 ? 7:4) + 1))))))) << (0 ? 7:4)))
                ));

            blitType = 0x2;

            /* Uploading two kernel tables. */
            gcmONERROR(_LoadKernel(
                Hardware,
                gcvFILTER_BLIT_KERNEL_HORIZONTAL,
                HorKernel
                ));

            gcmONERROR(_LoadKernel(
                Hardware,
                gcvFILTER_BLIT_KERNEL_VERTICAL,
                VerKernel
                ));

            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01220,
                HorKernel->scaleFactor
                ));

            gcmONERROR(gcoHARDWARE_Load2DState32(
                Hardware,
                0x01224,
                VerKernel->scaleFactor
                ));

            break;

        default:
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }

        if (SrcSurface->format == gcvSURF_INDEX8)
        {
            gcmONERROR(gcoHARDWARE_LoadPalette(
                Hardware,
                State->paletteFirstIndex,
                State->paletteIndexCount,
                State->paletteTable,
                State->paletteConvert,
                DstSurface->format,
                &State->paletteProgram,
                &State->paletteConvertFormat
                ));
        }

        /* Set source. */
        gcmERR_BREAK(_SetVideoSource(
            Hardware,
            SrcSurface,
            SrcRect,
            SrcOrigin,
            curSrc->srcYUVMode
            ));

        /* Set destination. */
        gcmERR_BREAK(_SetVideoDestination(
            Hardware,
            DstSurface,
            DstRect
            ));

        /*******************************************************************
        ** Setup ROP.
        */

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x0125C,
              ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20))) | (((gctUINT32) (0x2 & ((gctUINT32) ((((1 ? 21:20) - (0 ? 21:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 21:20) - (0 ? 21:20) + 1))))))) << (0 ? 21:20)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8))) | (((gctUINT32) ((gctUINT32) (0xCC) & ((gctUINT32) ((((1 ? 15:8) - (0 ? 15:8) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 15:8) - (0 ? 15:8) + 1))))))) << (0 ? 15:8)))
            | ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 7:0) - (0 ? 7:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:0) - (0 ? 7:0) + 1))))))) << (0 ? 7:0))) | (((gctUINT32) ((gctUINT32) (0xCC) & ((gctUINT32) ((((1 ? 7:0) - (0 ? 7:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 7:0) - (0 ? 7:0) + 1))))))) << (0 ? 7:0)))
            ));

        gcmONERROR(gcoHARDWARE_Load2DState32(
            Hardware,
            0x01294,
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) | (((gctUINT32) (0x0 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1))))))) << (0 ? 3:3))) |
            ((((gctUINT32) (0)) & ~(((gctUINT32) (((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0))) | (((gctUINT32) ((gctUINT32) (blitType) & ((gctUINT32) ((((1 ? 1:0) - (0 ? 1:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 1:0) - (0 ? 1:0) + 1))))))) << (0 ? 1:0)))
            ));

        gcmONERROR(gcoHARDWARE_End2DFrame(
            Hardware,
            gcvFALSE
            ));
        }
    }
    while (gcvFALSE);

OnError:

    gcoHARDWARE_Reset2DCmdBuffer(Hardware, gcmIS_ERROR(status));

    /* Return status. */
    return status;
}

/******************************************************************************\
****************************** gcoHARDWARE API Code *****************************
\******************************************************************************/

/*******************************************************************************
**
**  gcoHARDWARE_FreeFilterBuffer
**
**  Frees the temporary buffer allocated by filter blit operation.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS gcoHARDWARE_FreeFilterBuffer(
    IN gcoHARDWARE Hardware
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gctUINT i;

    gcmHEADER_ARG("Hardware=0x%x", Hardware);

    gcmGETHARDWARE(Hardware);

    for (i = 0; i < gcdTEMP_SURFACE_NUMBER; i += 1)
    {
        if (Hardware->temp2DSurf[i] != gcvNULL)
        {
            if (Hardware->temp2DSurf[i]->node.valid)
            {
                gcmONERROR(gcoHARDWARE_Unlock(
                    &Hardware->temp2DSurf[i]->node,
                    gcvSURF_BITMAP
                    ));
            }

            /* Free the video memory by event. */
            gcmONERROR(gcoHARDWARE_ScheduleVideoMemory(&Hardware->temp2DSurf[i]->node));

            gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, Hardware->temp2DSurf[i]));
        }
    }

OnError:

    /* Return status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_FilterBlit
**
**  Filter blit.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an gcoHARDWARE object.
**
**      gcsSURF_INFO_PTR SrcSurface
**          Pointer to the source surface descriptor.
**
**      gcsSURF_INFO_PTR DestSurface
**          Pointer to the destination surface descriptor.
**
**      gcsRECT_PTR SrcRect
**          Coorinates of the entire source image.
**
**      gcsRECT_PTR DestRect
**          Coorinates of the entire destination image.
**
**      gcsRECT_PTR DestSubRect
**          Coordinates of a sub area within the destination to render.
**          The coordinates are relative to the coordinates represented
**          by DestRect. If DestSubRect is gcvNULL, the complete image will
**          be rendered based on DestRect.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS gcoHARDWARE_FilterBlit(
    IN gcs2D_State_PTR State,
    IN gcsSURF_INFO_PTR SrcSurface,
    IN gcsSURF_INFO_PTR DestSurface,
    IN gcsRECT_PTR SrcRect,
    IN gcsRECT_PTR DestRect,
    IN gcsRECT_PTR DestSubRect
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;
    gcsSURF_INFO_PTR tempSurf = gcvNULL;
    gcsPOINT srcRectSize;
    gcsPOINT destRectSize;

    gctBOOL horPass = gcvFALSE;
    gctBOOL verPass = gcvFALSE;

    gcsSURF_FORMAT_INFO_PTR srcFormat[2];

    gcsRECT ssRect, dRect, sRect, dsRect;

    gcsFILTER_BLIT_ARRAY_PTR horKernel = gcvNULL;
    gcsFILTER_BLIT_ARRAY_PTR verKernel = gcvNULL;

    gceSURF_ROTATION srcRot = gcvSURF_0_DEGREE, dstRot = gcvSURF_0_DEGREE;
    gctBOOL rev = gcvFALSE, vMirror = gcvFALSE, hMirror = gcvFALSE;

    gcmHEADER_ARG("SrcSurface=0x%x DestSurface=0x%x "
                    "SrcRect=0x%x DestRect=0x%x DestSubRect=0x%x",
                    SrcSurface, DestSurface,
                    SrcRect, DestRect, DestSubRect);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(SrcSurface != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(DestSurface != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(SrcRect != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(DestRect != gcvNULL);

/*----------------------------------------------------------------------------*/
/*------------------- Verify the presence of 2D hardware. --------------------*/

    /* Only supported with hardware 2D engine. */
    if (!hardware->hw2DEngine || hardware->sw2DEngine)
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    /* Determine final destination subrectangle. */
    if (DestSubRect != gcvNULL)
    {
        if (DestSubRect->left >= DestRect->right
            || DestSubRect->right > DestRect->right
            || DestSubRect->top >= DestRect->bottom
            || DestSubRect->bottom > DestRect->bottom)
        {
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }

        dsRect.left   = DestRect->left + DestSubRect->left;
        dsRect.top    = DestRect->top  + DestSubRect->top;
        dsRect.right  = DestRect->left + DestSubRect->right;
        dsRect.bottom = DestRect->top  + DestSubRect->bottom;
    }
    else
    {
        dsRect = *DestRect;
    }

/*----------------------------------------------------------------------------*/
/*------------------------- Rotation opimization. ----------------------------*/
    /* Determine temporary surface format. */
    gcmONERROR(gcoSURF_QueryFormat(SrcSurface->format, srcFormat));

    if (hardware->fullFilterBlitRotation
        && (hardware->mirrorExtension ||
            (DestSurface->rotation != gcvSURF_FLIP_X && DestSurface->rotation != gcvSURF_FLIP_Y
            && SrcSurface->rotation != gcvSURF_FLIP_X && SrcSurface->rotation != gcvSURF_FLIP_Y))
        && (State->newFilterType != gcvFILTER_USER))
    {
        gceSURF_ROTATION rot, rot2;
        gctUINT8 horKernelSize, verKernelSize;

        dstRot = DestSurface->rotation;
        srcRot = SrcSurface->rotation;
        hMirror = State->horMirror;
        vMirror = State->verMirror;
        rev = gcvTRUE;

        if (dstRot == gcvSURF_FLIP_X)
        {
            gctINT32 temp;

            dRect.left = DestSurface->alignedWidth - DestRect->right;
            dRect.right = DestSurface->alignedWidth - DestRect->left;
            dRect.top = DestRect->top;
            dRect.bottom = DestRect->bottom;

            temp = dsRect.left;
            dsRect.left = DestSurface->alignedWidth - dsRect.right;
            dsRect.right = DestSurface->alignedWidth - temp;

            State->horMirror = !State->horMirror;
            DestSurface->rotation = gcvSURF_0_DEGREE;
        }
        else if (dstRot == gcvSURF_FLIP_Y)
        {
            gctINT32 temp;

            dRect.left = DestRect->left;
            dRect.right = DestRect->right;
            dRect.top = DestSurface->alignedHeight - DestRect->bottom;
            dRect.bottom = DestSurface->alignedHeight - DestRect->top;

            temp = dsRect.top;
            dsRect.top = DestSurface->alignedHeight - dsRect.bottom;
            dsRect.bottom = DestSurface->alignedHeight - temp;

            State->verMirror = !State->verMirror;
            DestSurface->rotation = gcvSURF_0_DEGREE;
        }
        else
        {
            dRect = *DestRect;
        }

        if (srcRot == gcvSURF_FLIP_X)
        {
            sRect.left = SrcSurface->alignedWidth - SrcRect->right;
            sRect.right = SrcSurface->alignedWidth - SrcRect->left;
            sRect.top = SrcRect->top;
            sRect.bottom = SrcRect->bottom;

            State->horMirror = !State->horMirror;
            SrcSurface->rotation = gcvSURF_0_DEGREE;
        }
        else if (srcRot == gcvSURF_FLIP_Y)
        {
            sRect.left = SrcRect->left;
            sRect.right = SrcRect->right;
            sRect.top = SrcSurface->alignedHeight - SrcRect->bottom;
            sRect.bottom = SrcSurface->alignedHeight - SrcRect->top;

            State->verMirror = !State->verMirror;
            SrcSurface->rotation = gcvSURF_0_DEGREE;
        }
        else
        {
            sRect = *SrcRect;
        }

        horPass = (sRect.right - sRect.left) != (dRect.right - dRect.left);
        verPass = (sRect.bottom - sRect.top) != (dRect.bottom - dRect.top);

        if (State->newFilterType == gcvFILTER_BLUR)
        {
            horKernelSize = State->horBlurFilterKernel.kernelSize;
            verKernelSize = State->verBlurFilterKernel.kernelSize;
        }
        else
        {
            horKernelSize = State->horSyncFilterKernel.kernelSize;
            verKernelSize = State->verSyncFilterKernel.kernelSize;
        }

        rot2 = rot = DestSurface->rotation;
        gcmONERROR(gcsRECT_RelativeRotation(SrcSurface->rotation, &rot));
        gcmONERROR(gcsRECT_RelativeRotation(rot, &rot2));

        if ((horPass && verPass && (((srcFormat[0]->fmtClass == gcvFORMAT_CLASS_YUV)
            && (SrcSurface->format != gcvSURF_NV21)
            && (SrcSurface->format != gcvSURF_NV61))
            || (hardware->hw2DOPF && (horKernelSize == 5 || horKernelSize == 3)
            && (verKernelSize == 5 || verKernelSize == 3)))) ||
            ((rot == gcvSURF_90_DEGREE || rot == gcvSURF_270_DEGREE) &&
            ((horPass && !verPass && (rot2 == gcvSURF_90_DEGREE || rot2 == gcvSURF_270_DEGREE))
            || (!horPass && verPass && (rot2 == gcvSURF_0_DEGREE || rot2 == gcvSURF_180_DEGREE)))))
        {
            rot2 = gcvSURF_0_DEGREE;
        }
        else
        {
            rot = gcvSURF_0_DEGREE;
            rot2 = SrcSurface->rotation;
            gcmONERROR(gcsRECT_RelativeRotation(DestSurface->rotation, &rot2));
        }

        gcmONERROR(gcsRECT_Rotate(
            &sRect,
            SrcSurface->rotation,
            rot2,
            SrcSurface->alignedWidth,
            SrcSurface->alignedHeight));

        SrcSurface->rotation = rot2;

        rot2 = DestSurface->rotation;
        gcmONERROR(gcsRECT_RelativeRotation(rot, &rot2));
        if (rot2 == gcvSURF_90_DEGREE || rot2 == gcvSURF_270_DEGREE)
        {
            gctBOOL tmp = State->horMirror;
            State->horMirror = State->verMirror;
            State->verMirror = tmp;
        }

        gcmONERROR(gcsRECT_Rotate(
            &dRect,
            DestSurface->rotation,
            rot,
            DestSurface->alignedWidth,
            DestSurface->alignedHeight));

        gcmONERROR(gcsRECT_Rotate(
            &dsRect,
            DestSurface->rotation,
            rot,
            DestSurface->alignedWidth,
            DestSurface->alignedHeight));

        DestSurface->rotation = rot;
    }
    else
    {
        dRect = *DestRect;
        sRect = *SrcRect;
    }

/*----------------------------------------------------------------------------*/
/*------------------------- Compute rectangle sizes. -------------------------*/

    gcmONERROR(gcsRECT_Width(&sRect, &srcRectSize.x));
    gcmONERROR(gcsRECT_Height(&sRect, &srcRectSize.y));
    gcmONERROR(gcsRECT_Width(&dRect, &destRectSize.x));
    gcmONERROR(gcsRECT_Height(&dRect, &destRectSize.y));

/*----------------------------------------------------------------------------*/
/*--------------------------- Update kernel arrays. --------------------------*/

    if (State->newFilterType == gcvFILTER_SYNC)
    {
        horPass = (srcRectSize.x != destRectSize.x);
        verPass = (srcRectSize.y != destRectSize.y);

        if (!verPass && !horPass)
        {
            if(SrcSurface->rotation == gcvSURF_90_DEGREE || SrcSurface->rotation == gcvSURF_270_DEGREE
            || DestSurface->rotation == gcvSURF_90_DEGREE || DestSurface->rotation == gcvSURF_270_DEGREE)
            {
                verPass = gcvTRUE;
            }
            else
            {
                horPass = gcvTRUE;
            }
        }

        /* Set the proper kernel array for sync filter. */
        horKernel = &State->horSyncFilterKernel;
        verKernel = &State->verSyncFilterKernel;

        /* Recompute the table if necessary. */
        gcmONERROR(_CalculateSyncTable(
            hardware,
            State->newHorKernelSize,
            srcRectSize.x,
            destRectSize.x,
            horKernel
            ));

        gcmONERROR(_CalculateSyncTable(
            hardware,
            State->newVerKernelSize,
            srcRectSize.y,
            destRectSize.y,
            verKernel
            ));
    }
    else if (State->newFilterType == gcvFILTER_BLUR)
    {
        /* Always do both passes for blur. */
        horPass = verPass = gcvTRUE;

        /* Set the proper kernel array for blur filter. */
        horKernel = &State->horBlurFilterKernel;
        verKernel = &State->verBlurFilterKernel;

        /* Recompute the table if necessary. */
        gcmONERROR(_CalculateBlurTable(
            hardware,
            State->newHorKernelSize,
            srcRectSize.x,
            destRectSize.x,
            horKernel
            ));

        gcmONERROR(_CalculateBlurTable(
            hardware,
            State->newVerKernelSize,
            srcRectSize.y,
            destRectSize.y,
            verKernel
            ));
    }
    else if (State->newFilterType == gcvFILTER_USER)
    {
        gctUINT32 scaleFactor;

        /* Do the pass(es) according to user settings. */
        horPass = State->horUserFilterPass;
        verPass = State->verUserFilterPass;

        /* Set the proper kernel array for user defined filter. */
        horKernel = &State->horUserFilterKernel;
        verKernel = &State->verUserFilterKernel;

        /* Set the kernel size and scale factors. */
        scaleFactor = gcoHARDWARE_GetStretchFactor(srcRectSize.x, destRectSize.x);
        horKernel->kernelSize  = State->newHorKernelSize;
        horKernel->scaleFactor = scaleFactor;

        scaleFactor = gcoHARDWARE_GetStretchFactor(srcRectSize.y, destRectSize.y);
        verKernel->kernelSize  = State->newVerKernelSize;
        verKernel->scaleFactor = scaleFactor;
    }
    else
    {
        gcmTRACE_ZONE(gcvLEVEL_ERROR, gcvZONE_HARDWARE, "Unknown filter type");
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

/*----------------------------------------------------------------------------*/
/*------------------- Determine the source sub rectangle. --------------------*/

    /* Compute the source sub rectangle that exactly represents
       the destination sub rectangle. */
    ssRect.left = dsRect.left - dRect.left;
    ssRect.right = dsRect.right - dRect.left;
    ssRect.top = dsRect.top - dRect.top;
    ssRect.bottom = dsRect.bottom - dRect.top;

    if (State->specialFilterMirror)
    {
        gctINT32 tmp;

        if (State->horMirror)
        {
            tmp = ssRect.left;
            ssRect.left = destRectSize.x - ssRect.right;
            ssRect.right = destRectSize.x - tmp;
        }

        if (State->verMirror)
        {
            tmp = ssRect.top;
            ssRect.top = destRectSize.y - ssRect.bottom;
            ssRect.bottom = destRectSize.y - tmp;
        }
    }

    ssRect.left *= horKernel->scaleFactor;
    ssRect.top *= verKernel->scaleFactor;
    ssRect.right
        = (ssRect.right - 1)
        * horKernel->scaleFactor + (1 << 16);
    ssRect.bottom
        = (ssRect.bottom - 1)
        * verKernel->scaleFactor + (1 << 16);

    if (!hardware->hw2DEnableGDIStretch)
    {
        /*  Before rendering each destination pixel, the HW will select the
            corresponding source center pixel to apply the kernel around.
            To make this process precise we need to add 0.5 to source initial
            coordinates here; this will make HW pick the next source pixel if
            the fraction is equal or greater then 0.5. */
        ssRect.left   += 0x00008000;
        ssRect.top    += 0x00008000;
        ssRect.right  += 0x00008000;
        ssRect.bottom += 0x00008000;
    }

/*----------------------------------------------------------------------------*/
/*------------------------- Do the one pass blit. ----------------------------*/

    if (hardware->hw2DOPF
        && horPass && verPass
        && (horKernel->kernelSize == 5 || horKernel->kernelSize == 3)
        && (verKernel->kernelSize == 5 || verKernel->kernelSize == 3)
        && (SrcSurface->rotation == gcvSURF_0_DEGREE))
    {
        /* Determine the source origin. */
        gcsPOINT srcOrigin;

        srcOrigin.x = (sRect.left << 16) + ssRect.left;
        srcOrigin.y = (sRect.top  << 16) + ssRect.top;

        /* Start the blit. */
        gcmONERROR(_StartVR(
            hardware,
            State,
            gceFILTER_BLIT_TYPE_ONE_PASS,
            horKernel,
            verKernel,
            SrcSurface,
            &sRect,
            &srcOrigin,
            DestSurface,
            &dsRect,
            gcvFALSE));
    }

/*----------------------------------------------------------------------------*/
/*------------------ Do the blit with the temporary buffer. ------------------*/

    else if (horPass && verPass)
    {
        gctUINT32 horKernelHalf;
        gctUINT32 leftExtra;
        gctUINT32 rightExtra;
        gcsPOINT srcOrigin;
        gcsPOINT tmpRectSize;
        gcsSURF_FORMAT_INFO_PTR tempFormat[2];
        gcsPOINT tempAlignment;
        gctUINT32 tempHorCoordMask;
        gctUINT32 tempVerCoordMask;
        gcsPOINT tempOrigin;
        gcsRECT tempRect;
        gcsPOINT tmpBufRectSize;

        /* In partial filter blit cases, the vertical pass has to render
           more pixel information to the left and to the right of the
           temporary image so that the horizontal pass has its necessary
           kernel information on the edges of the image. */
        horKernelHalf = horKernel->kernelSize >> 1;

        leftExtra  = ssRect.left >> 16;
        rightExtra = srcRectSize.x - (ssRect.right >> 16);

        if (leftExtra > horKernelHalf)
            leftExtra = horKernelHalf;

        if (rightExtra > horKernelHalf)
            rightExtra = horKernelHalf;

        /* Determine the source origin. */
        srcOrigin.x = ((sRect.left - leftExtra) << 16) + ssRect.left;
        srcOrigin.y = (sRect.top << 16) + ssRect.top;

        /* Determine the size of the temporary image. */
        tmpRectSize.x
            = leftExtra
            + ((ssRect.right >> 16) - (ssRect.left >> 16))
            + rightExtra;

        tmpRectSize.y
            = dsRect.bottom - dsRect.top;

        /* Determine the destination origin. */
        tempRect.left = srcOrigin.x >> 16;
        tempRect.top  = 0;

        if (srcFormat[0]->fmtClass == gcvFORMAT_CLASS_YUV)
        {
            if (hardware->hw2DPE20 && (SrcSurface->rotation == gcvSURF_0_DEGREE)
                && (SrcSurface->format != gcvSURF_NV21)
                && (SrcSurface->format != gcvSURF_NV61))
            {
                if (SrcSurface->format == gcvSURF_UYVY)
                {
                    tempFormat[0] = srcFormat[0];
                    tempFormat[1] = srcFormat[1];
                }
                else
                {
                    gcmONERROR(gcoSURF_QueryFormat(gcvSURF_YUY2, tempFormat));
                }

                tmpRectSize.x = gcmALIGN(tmpRectSize.x, 2);
                tempRect.left = gcmALIGN(tempRect.left, 2);
            }
            else
            {
                gcmONERROR(gcoSURF_QueryFormat(DestSurface->format, tempFormat));
            }
        }
        else
        {
            if ((SrcSurface->format == gcvSURF_INDEX8) || (SrcSurface->format == gcvSURF_A8))
            {
                gcmONERROR(gcoSURF_QueryFormat(gcvSURF_A8R8G8B8, tempFormat));
            }
            else
            {
                tempFormat[0] = srcFormat[0];
                tempFormat[1] = srcFormat[1];
            }
        }

        gcmONERROR(gco2D_GetPixelAlignment(
            tempFormat[0]->format,
            &tempAlignment
            ));

        tempHorCoordMask = tempAlignment.x - 1;
        tempVerCoordMask = tempAlignment.y - 1;

        /* Align the temporary destination. */
        tempRect.left &= tempHorCoordMask;
        tempRect.top  &= tempVerCoordMask;

        /* Determine the bottom right corner of the destination. */
        tempRect.right  = tempRect.left + tmpRectSize.x;
        tempRect.bottom = tempRect.top  + tmpRectSize.y;

        /* Determine the source origin. */
        tempOrigin.x
            = ((leftExtra + tempRect.left) << 16)
            + (ssRect.left & 0xFFFF);
        tempOrigin.y
            = (tempRect.top << 16)
            + (ssRect.top & 0xFFFF);

        /* Determine the size of the temporaty surface. */
        tmpBufRectSize.x = gcmALIGN(tempRect.right, tempAlignment.x);
        tmpBufRectSize.y = gcmALIGN(tempRect.bottom, tempAlignment.y);

        /* Allocate the temporary buffer. */
        gcmONERROR(gcoHARDWARE_Get2DTempSurface(
            tmpBufRectSize.x,
            tmpBufRectSize.y,
            tempFormat[0]->format,
            &tempSurf
            ));

        /*******************************************************************
        ** Program the vertical pass.
        */

        gcmONERROR(_StartVR(
            hardware,
            State,
            gceFILTER_BLIT_TYPE_VERTICAL,
            gcvNULL,
            verKernel,
            SrcSurface,
            &sRect,
            &srcOrigin,
            tempSurf,
            &tempRect,
            gcvTRUE));

        /*******************************************************************
        ** Program the second pass.
        */
        if (hardware->fullFilterBlitRotation &&
            ((DestSurface->rotation == gcvSURF_90_DEGREE)
            || (DestSurface->rotation == gcvSURF_270_DEGREE)))
        {
            gceSURF_ROTATION rot;
            gctBOOL tmp = State->horMirror;

            State->horMirror = State->verMirror;
            State->verMirror = tmp;

            rot = tempSurf->rotation;
            gcmONERROR(gcsRECT_RelativeRotation(DestSurface->rotation, &rot));

            gcmONERROR(gcsRECT_Rotate(
                &tempRect,
                tempSurf->rotation,
                rot,
                tempSurf->alignedWidth,
                tempSurf->alignedHeight));

            if (rot == gcvSURF_90_DEGREE)
            {
                tempOrigin.x
                    = (tempRect.left << 16)
                    + (ssRect.top & 0xFFFF);

                tempOrigin.y
                    = ((rightExtra + tempRect.top) << 16)
                    + (ssRect.right & 0xFFFF);
            }
            else
            {
                tempOrigin.x
                    = (tempRect.left << 16)
                    + (ssRect.bottom & 0xFFFF);

                tempOrigin.y
                    = ((leftExtra + tempRect.top) << 16)
                    + (ssRect.left & 0xFFFF);
            }

            tempSurf->rotation = rot;

            gcmONERROR(gcsRECT_Rotate(
                &dsRect,
                DestSurface->rotation,
                gcvSURF_0_DEGREE,
                DestSurface->alignedWidth,
                DestSurface->alignedHeight));

            DestSurface->rotation = gcvSURF_0_DEGREE;

            gcmONERROR(_StartVR(
                hardware,
                State,
                gceFILTER_BLIT_TYPE_VERTICAL,
                gcvNULL,
                horKernel,
                tempSurf,
                &tempRect,
                &tempOrigin,
                DestSurface,
                &dsRect,
                gcvFALSE));
        }
        else
        {
            gcmONERROR(_StartVR(
                hardware,
                State,
                gceFILTER_BLIT_TYPE_HORIZONTAL,
                horKernel,
                gcvNULL,
                tempSurf,
                &tempRect,
                &tempOrigin,
                DestSurface,
                &dsRect,
                gcvFALSE));
        }
    }

/*----------------------------------------------------------------------------*/
/*---------------------------- One pass only blit. -------------------------*/

    else if (horPass || verPass)
    {
        /* Determine the source origin. */
        gcsPOINT srcOrigin;

        srcOrigin.x = (sRect.left << 16) + ssRect.left;
        srcOrigin.y = (sRect.top  << 16) + ssRect.top;

        /* Start the blit. */
        gcmONERROR(_StartVR(
            hardware,
            State,
            horPass ? gceFILTER_BLIT_TYPE_HORIZONTAL : gceFILTER_BLIT_TYPE_VERTICAL,
            horKernel,
            verKernel,
            SrcSurface,
            &sRect,
            &srcOrigin,
            DestSurface,
            &dsRect,
            gcvFALSE
            ));
    }
/*----------------------------------------------------------------------------*/
/*---------------------------- Should no be here. ----------------------------*/
    else
    {
        gcmTRACE_ZONE(gcvLEVEL_ERROR,
                      gcvZONE_HARDWARE,
                      "None of the passes is set."
                      );

        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

OnError:
    /* Unlock temporary. */
    if (tempSurf != gcvNULL)
    {
        gceSTATUS statusTemp;

        /* Unlock the temporary surface. */
        statusTemp = gcoHARDWARE_Put2DTempSurface(
            tempSurf
            );

        /* Update the returned status if it is gcvSTATUS_OK.
           Or else, keep last error status.
        */
        if (status == gcvSTATUS_OK)
        {
            status = statusTemp;
        }
    }

    if (rev)
    {
        DestSurface->rotation = dstRot;
        SrcSurface->rotation = srcRot;
        State->horMirror = hMirror;
        State->verMirror = vMirror;
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}

gceSTATUS gcoHARDWARE_MultiPlanarYUVConvert(
    IN gcsSURF_INFO_PTR SrcSurface,
    IN gcsSURF_INFO_PTR DestSurface,
    IN gcsRECT_PTR DestRect
    )
{
    gceSTATUS status;
    gcs2D_State state;
    gcoHARDWARE hardware;
    gcsSURF_INFO_PTR tempSurf = gcvNULL;
    gctUINT pass = 0;
    gcsRECT rect = {0, 0, 0, 0};

    gcmHEADER_ARG("SrcSurface=0x%x DestSurface=0x%x "
                    "SrcRect=0x%x DestRect=0x%x DestSubRect=0x%x",
                    SrcSurface, DestSurface,
                    DestRect);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);
    gcmDEBUG_VERIFY_ARGUMENT(SrcSurface != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(DestSurface != gcvNULL);
    gcmDEBUG_VERIFY_ARGUMENT(DestRect != gcvNULL);

    /* Only supported with hardware 2D engine. */
    if (!hardware->hw2DEngine || hardware->sw2DEngine)
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    switch (DestSurface->format)
    {
    case gcvSURF_I420:
    case gcvSURF_YV12:
        pass = 3;
        break;

    case gcvSURF_NV12:
    case gcvSURF_NV21:
        pass = 2;
        break;

    case gcvSURF_NV16:
    case gcvSURF_NV61:
        pass = 1;
        break;

    default:
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    rect.right = rect.left = DestRect->left;
    rect.top = DestRect->top;
    rect.right += (DestRect->right - DestRect->left) >> 1;
    rect.bottom = DestRect->bottom;

    gcoOS_ZeroMemory(&state, sizeof(state));

    state.dstSurface = *DestSurface;
    state.clipRect = rect;
    state.currentSrcIndex = 0;
    state.srcMask = 1;
    state.multiSrc[0].enableAlpha = gcvFALSE;
    state.multiSrc[0].srcRect = rect;
    state.multiSrc[0].srcTransparency = gcv2D_OPAQUE;
    state.multiSrc[0].dstTransparency = gcv2D_OPAQUE;
    state.multiSrc[0].patTransparency = gcv2D_OPAQUE;
    state.multiSrc[0].fgRop = 0xCC;
    state.multiSrc[0].bgRop = 0xCC;

    state.multiSrc[0].srcSurface = *SrcSurface;

    if (pass > 1)
    {
        /* Allocate the temporary buffer. */
        gcmONERROR(gcoHARDWARE_Get2DTempSurface(
            DestSurface->alignedWidth,
            DestSurface->alignedHeight,
            gcvSURF_R5G6B5,
            &tempSurf
            ));

        if (pass == 2)
        {
            state.dstSurface.node.physical2 = tempSurf->node.physical;
            state.dstSurface.uStride = tempSurf->stride;
        }
        else
        {
            state.dstSurface.node.physical2 = tempSurf->node.physical;
            state.dstSurface.node.physical3 =
                tempSurf->node.physical + (tempSurf->node.size >> 1);

            state.dstSurface.uStride = tempSurf->stride >> 1;
            state.dstSurface.vStride = tempSurf->stride >> 1;
        }
    }

    /* Start multi dest blit. */
    gcmONERROR(gcoHARDWARE_StartDE(
        &state,
        gcv2D_MULTI_SOURCE_BLT,
        0,
        gcvNULL,
        1,
        &rect
        ));

    if (pass > 1)
    {
        gcsFILTER_BLIT_ARRAY kernel;
        gcsPOINT srcOrigin = {0, 0};
        gcsRECT dstRect;
        static const gctUINT16 table[gcvKERNELSTATES + 2] = {
            0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0,
            0, 0, 0, 0, 0x2000, 0x2000, 0, 0, 0 };

        dstRect.top = dstRect.bottom = rect.top;
        dstRect.bottom += (rect.bottom - rect.top) >> 1;
        dstRect.left = rect.left;
        dstRect.right = rect.right;

        state.clipRect = rect;
        state.multiSrc[0].srcRect = rect;

        kernel.filterType = gcvFILTER_USER;
        kernel.kernelChanged = gcvTRUE;
        kernel.kernelSize = 9;
        kernel.scaleFactor = gcoHARDWARE_GetStretchFactor(rect.bottom - rect.top, dstRect.bottom - dstRect.top);
        kernel.kernelStates = (gctPOINTER)table;

        if (pass == 2)
        {
            state.multiSrc[0].srcSurface = *DestSurface;
            state.multiSrc[0].srcSurface.format = gcvSURF_RG16;
            state.multiSrc[0].srcSurface.node.physical = tempSurf->node.physical;
            state.multiSrc[0].srcSurface.stride = tempSurf->stride;
            state.multiSrc[0].srcSurface.alignedWidth >>= 1;

            state.dstSurface.format = gcvSURF_RG16;
            state.dstSurface.node.physical = DestSurface->node.physical2;
            state.dstSurface.stride = DestSurface->uStride;
            state.dstSurface.alignedWidth >>= 1;
            state.dstSurface.alignedHeight >>= 1;

            gcmONERROR(_StartVR(
                hardware,
                &state,
                gceFILTER_BLIT_TYPE_VERTICAL,
                gcvNULL,
                &kernel,
                &state.multiSrc[0].srcSurface,
                &rect,
                &srcOrigin,
                &state.dstSurface,
                &dstRect,
                gcvTRUE));
        }
        else
        {
            state.multiSrc[0].srcSurface = *DestSurface;
            state.multiSrc[0].srcSurface.format = gcvSURF_A8;
            state.multiSrc[0].srcSurface.node.physical = tempSurf->node.physical;
            state.multiSrc[0].srcSurface.stride = tempSurf->stride >> 1;
            state.multiSrc[0].srcSurface.alignedWidth >>= 1;

            state.dstSurface.format = gcvSURF_A8;
            state.dstSurface.node.physical = DestSurface->node.physical2;
            state.dstSurface.stride = DestSurface->uStride;
            state.dstSurface.alignedWidth >>= 1;
            state.dstSurface.alignedHeight >>= 1;

            gcmONERROR(_StartVR(
                hardware,
                &state,
                gceFILTER_BLIT_TYPE_VERTICAL,
                gcvNULL,
                &kernel,
                &state.multiSrc[0].srcSurface,
                &rect,
                &srcOrigin,
                &state.dstSurface,
                &dstRect,
                gcvTRUE));

            state.multiSrc[0].srcSurface.node.physical =
                tempSurf->node.physical + (tempSurf->node.size >> 1);
            state.multiSrc[0].srcSurface.stride = tempSurf->stride >> 1;

            state.dstSurface.node.physical = DestSurface->node.physical3;
            state.dstSurface.stride = DestSurface->vStride;

            gcmONERROR(_StartVR(
                hardware,
                &state,
                gceFILTER_BLIT_TYPE_VERTICAL,
                gcvNULL,
                &kernel,
                &state.multiSrc[0].srcSurface,
                &rect,
                &srcOrigin,
                &state.dstSurface,
                &dstRect,
                gcvTRUE));
        }
    }

OnError:
    /* Unlock temporary. */
    if (tempSurf != gcvNULL)
    {
        gceSTATUS statusTemp;

        /* Unlock the temporary surface. */
        statusTemp = gcoHARDWARE_Put2DTempSurface(
            tempSurf
            );

        /* Update the returned status if it is gcvSTATUS_OK.
           Or else, keep last error status.
        */
        if (status == gcvSTATUS_OK)
        {
            status = statusTemp;
        }
    }

    /* Return status. */
    gcmFOOTER();
    return status;
}



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


#ifndef __gc_hal_user_h_
#define __gc_hal_user_h_

#include "gc_hal.h"
#include "gc_hal_driver.h"
#include "gc_hal_enum.h"
#include "gc_hal_dump.h"
#include "gc_hal_base.h"
#include "gc_hal_raster.h"
#include "gc_hal_user_math.h"
#include "gc_hal_user_os_memory.h"
#include "gc_hal_user_debug.h"


#define OPT_VERTEX_ARRAY                  1

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************\
********************************* Private Macro ********************************
\******************************************************************************/

#define gcmGETFENCEENABLE(fenceEnable) \
{ \
    gcsTLS_PTR __tls__; \
    \
    gcoOS_GetTLS(&__tls__); \
    fenceEnable = __tls__ ? __tls__->fenceEnable : gcvFALSE; \
}
#define gcmENABLEFENCE() \
{ \
    gcsTLS_PTR __tls__; \
    \
    gcoOS_GetTLS(&__tls__); \
    if (__tls__); \
        __tls__->fenceEnable = gcvTRUE; \
}

#define gcmGETHARDWARE(Hardware) \
{ \
    gcsTLS_PTR __tls__; \
    \
    gcmONERROR(gcoOS_GetTLS(&__tls__)); \
    \
    if (__tls__->currentType == gcvHARDWARE_2D \
        && gcvSTATUS_TRUE == gcoHAL_QuerySeparated3D2D(gcvNULL) \
        ) \
    { \
        if (__tls__->hardware2D == gcvNULL) \
        { \
            gcmONERROR(gcoHARDWARE_Construct(gcPLS.hal, &__tls__->hardware2D)); \
            \
            gcmTRACE_ZONE( \
                gcvLEVEL_VERBOSE, gcvZONE_HARDWARE, \
                "%s(%d): hardware object 0x%08X constructed.\n", \
                __FUNCTION__, __LINE__, __tls__->hardware2D \
                ); \
        } \
        \
        Hardware = __tls__->hardware2D; \
    } \
    else \
    { \
        if (__tls__->hardware == gcvNULL) \
        { \
            gcmONERROR(gcoHARDWARE_Construct(gcPLS.hal, &__tls__->hardware)); \
            \
            gcmTRACE_ZONE( \
                gcvLEVEL_VERBOSE, gcvZONE_HARDWARE, \
                "%s(%d): hardware object 0x%08X constructed.\n", \
                __FUNCTION__, __LINE__, __tls__->hardware \
                ); \
        } \
        \
        Hardware = __tls__->hardware; \
    } \
}

#define gcmGETVGHARDWARE(Hardware) \
{ \
    gcsTLS_PTR __tls__; \
    gceSTATUS verifyStatus; \
    \
    verifyStatus = gcoOS_GetTLS(&__tls__); \
    if (gcmIS_ERROR(verifyStatus)) \
    { \
        gcmFOOTER_ARG("status = %d", verifyStatus); \
        return verifyStatus;                  \
    }                                   \
    \
    if (__tls__->vg == gcvNULL) \
    { \
        verifyStatus = gcoVGHARDWARE_Construct(gcPLS.hal, &__tls__->vg); \
        if (gcmIS_ERROR(verifyStatus))            \
        {                                   \
            gcmFOOTER_ARG("status = %d", verifyStatus); \
            return verifyStatus;                  \
        }                                   \
        \
        gcmTRACE_ZONE( \
            gcvLEVEL_VERBOSE, gcvZONE_HARDWARE, \
            "%s(%d): hardware object 0x%08X constructed.\n", \
            __FUNCTION__, __LINE__, __tls__->vg \
            ); \
    } \
    \
    Hardware = __tls__->vg; \
}

#define gcmGETCURRENTHARDWARE(hw) \
{ \
    gcmVERIFY_OK(gcoHAL_GetHardwareType(gcvNULL, &hw));\
    gcmASSERT(hw != gcvHARDWARE_INVALID);\
}


/******************************************************************************\
****************************** Object Declarations *****************************
\******************************************************************************/

typedef struct _gcoBUFFER *             gcoBUFFER;
typedef struct _gcs2D_State*            gcs2D_State_PTR;


/******************************************************************************\
******************************* gcoHARDWARE Object ******************************
\******************************************************************************/

/*----------------------------------------------------------------------------*/
/*----------------------------- gcoHARDWARE Common ----------------------------*/

/* Construct a new gcoHARDWARE object. */
gceSTATUS
gcoHARDWARE_Construct(
    IN gcoHAL Hal,
    OUT gcoHARDWARE * Hardware
    );

/* Destroy an gcoHARDWARE object. */
gceSTATUS
gcoHARDWARE_Destroy(
    IN gcoHARDWARE Hardware
    );

/* Query the identity of the hardware. */
gceSTATUS
gcoHARDWARE_QueryChipIdentity(
    OUT gceCHIPMODEL* ChipModel,
    OUT gctUINT32* ChipRevision,
    OUT gctUINT32* ChipFeatures,
    OUT gctUINT32* ChipMinorFeatures,
    OUT gctUINT32* ChipMinorFeatures1,
    OUT gctUINT32* ChipMinorFeatures2
    );

/* Verify whether the specified feature is available in hardware. */
gceSTATUS
gcoHARDWARE_IsFeatureAvailable(
    IN gceFEATURE Feature
    );

/* Query command buffer requirements. */
gceSTATUS
gcoHARDWARE_QueryCommandBuffer(
    OUT gctSIZE_T * Alignment,
    OUT gctSIZE_T * ReservedHead,
    OUT gctSIZE_T * ReservedTail
    );

/* Select a graphics pipe. */
gceSTATUS
gcoHARDWARE_SelectPipe(
    IN gcoHARDWARE Hardware,
    IN gcePIPE_SELECT Pipe
    );

/* Flush the current graphics pipe. */
gceSTATUS
gcoHARDWARE_FlushPipe(
    );


/* Load a number of load states. */
gceSTATUS
gcoHARDWARE_LoadState(
    IN gctUINT32 Address,
    IN gctSIZE_T Count,
    IN gctPOINTER States
    );


/* Commit the current command buffer. */
gceSTATUS
gcoHARDWARE_Commit(
    );

/* Stall the pipe. */
gceSTATUS
gcoHARDWARE_Stall(
    );


/* Query tile sizes. */
gceSTATUS
gcoHARDWARE_QueryTileSize(
    OUT gctINT32 * TileWidth2D,
    OUT gctINT32 * TileHeight2D,
    OUT gctINT32 * TileWidth3D,
    OUT gctINT32 * TileHeight3D,
    OUT gctUINT32 * StrideAlignment
    );


/* Lock a surface. */
gceSTATUS
gcoHARDWARE_Lock(
    IN gcsSURF_NODE_PTR Node,
    OUT gctUINT32 * Address,
    OUT gctPOINTER * Memory
    );

/* Unlock a surface. */
gceSTATUS
gcoHARDWARE_Unlock(
    IN gcsSURF_NODE_PTR Node,
    IN gceSURF_TYPE Type
    );

/* Call kernel for event. */
gceSTATUS
gcoHARDWARE_CallEvent(
    IN OUT gcsHAL_INTERFACE * Interface
    );

/* Schedule destruction for the specified video memory node. */
gceSTATUS
gcoHARDWARE_ScheduleVideoMemory(
    IN gcsSURF_NODE_PTR Node
    );

/* Allocate a temporary surface with specified parameters. */
gceSTATUS
gcoHARDWARE_AllocateTemporarySurface(
    IN gcoHARDWARE Hardware,
    IN gctUINT Width,
    IN gctUINT Height,
    IN gcsSURF_FORMAT_INFO_PTR Format,
    IN gceSURF_TYPE Type
    );

/* Free the temporary surface. */
gceSTATUS
gcoHARDWARE_FreeTemporarySurface(
    IN gctBOOL Synchronized
    );

/* Get a 2D temporary surface with specified parameters. */
gceSTATUS
gcoHARDWARE_Get2DTempSurface(
    IN gctUINT Width,
    IN gctUINT Height,
    IN gceSURF_FORMAT Format,
    OUT gcsSURF_INFO_PTR *SurfInfo
    );

/* Put back the 2D temporary surface from gcoHARDWARE_Get2DTempSurface. */
gceSTATUS
gcoHARDWARE_Put2DTempSurface(
    IN gcsSURF_INFO_PTR SurfInfo
    );


/* Convert RGB8 color value to YUV color space. */
void gcoHARDWARE_RGB2YUV(
    gctUINT8 R,
    gctUINT8 G,
    gctUINT8 B,
    gctUINT8_PTR Y,
    gctUINT8_PTR U,
    gctUINT8_PTR V
    );

/* Convert YUV color value to RGB8 color space. */
void gcoHARDWARE_YUV2RGB(
    gctUINT8 Y,
    gctUINT8 U,
    gctUINT8 V,
    gctUINT8_PTR R,
    gctUINT8_PTR G,
    gctUINT8_PTR B
    );

/* Convert an API format. */
gceSTATUS
gcoHARDWARE_ConvertFormat(
    IN gceSURF_FORMAT Format,
    OUT gctUINT32 * BitsPerPixel,
    OUT gctUINT32 * BytesPerTile
    );

/* Align size to tile boundary. */
gceSTATUS
gcoHARDWARE_AlignToTile(
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN OUT gctUINT32_PTR Width,
    IN OUT gctUINT32_PTR Height,
    OUT gctBOOL_PTR SuperTiled
    );

/* Align size compatible for all core in hardware. */
gceSTATUS
gcoHARDWARE_AlignToTileCompatible(
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN OUT gctUINT32_PTR Width,
    IN OUT gctUINT32_PTR Height,
    OUT gceTILING * Tiling,
    OUT gctBOOL_PTR SuperTiled
    );

gceSTATUS
gcoHARDWARE_QueryTileAlignment(
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    OUT gceSURF_ALIGNMENT * HAlignment,
    OUT gceSURF_ALIGNMENT * VAlignment
    );

gceSTATUS
gcoHARDWARE_SetDepthOnly(
    IN gctBOOL Enable
    );

gceSTATUS
gcoHARDWARE_QueryAlphaBlend(
    );


/*----------------------------------------------------------------------------*/
/*------------------------------- gcoHARDWARE 2D ------------------------------*/

/* Verifies whether 2D engine is available. */
gceSTATUS
gcoHARDWARE_Is2DAvailable(
    );

/* Translate API destination color format to its hardware value. */
gceSTATUS
gcoHARDWARE_TranslateDestinationFormat(
    IN gceSURF_FORMAT APIValue,
    OUT gctUINT32* HwValue,
    OUT gctUINT32* HwSwizzleValue,
    OUT gctUINT32* HwIsYUVValue
    );


/* Copy data into video memory. */
gceSTATUS
gcoHARDWARE_CopyData(
    IN gcsSURF_NODE_PTR Memory,
    IN gctUINT32 Offset,
    IN gctCONST_POINTER Buffer,
    IN gctSIZE_T Bytes
    );

/* Sets the software 2D renderer force flag. */
gceSTATUS
gcoHARDWARE_UseSoftware2D(
    IN gctBOOL Enable
    );

/* Clear one or more rectangular areas. */
gceSTATUS
gcoHARDWARE_Clear2D(
    IN gcs2D_State_PTR State,
    IN gctUINT32 RectCount,
    IN gcsRECT_PTR Rect
    );

/* Draw one or more Bresenham lines using solid color(s). */
gceSTATUS
gcoHARDWARE_Line2DEx(
    IN gcs2D_State_PTR State,
    IN gctUINT32 LineCount,
    IN gcsRECT_PTR Position,
    IN gctUINT32 ColorCount,
    IN gctUINT32_PTR Color32
    );

/* Determines the usage of 2D resources (source/pattern/destination). */
void
gcoHARDWARE_Get2DResourceUsage(
    IN gctUINT8 FgRop,
    IN gctUINT8 BgRop,
    IN gce2D_TRANSPARENCY Transparency,
    OUT gctBOOL_PTR UseSource,
    OUT gctBOOL_PTR UsePattern,
    OUT gctBOOL_PTR UseDestination
    );

/* Translate SURF API transparency mode to PE 2.0 transparency values. */
gceSTATUS
gcoHARDWARE_TranslateSurfTransparency(
    IN gceSURF_TRANSPARENCY APIValue,
    OUT gce2D_TRANSPARENCY* srcTransparency,
    OUT gce2D_TRANSPARENCY* dstTransparency,
    OUT gce2D_TRANSPARENCY* patTransparency
    );

gceSTATUS
gcoHARDWARE_ColorPackToARGB8(
    IN gceSURF_FORMAT Format,
    IN gctUINT32 Color,
    OUT gctUINT32_PTR Color32
    );

gceSTATUS
gcoHARDWARE_SetDither(
    IN gctBOOL Enable
    );

/* Calculate stretch factor. */
gctUINT32
gcoHARDWARE_GetStretchFactor(
    IN gctINT32 SrcSize,
    IN gctINT32 DestSize
    );

/* Calculate the stretch factors. */
gceSTATUS
gcoHARDWARE_GetStretchFactors(
    IN gcsRECT_PTR SrcRect,
    IN gcsRECT_PTR DestRect,
    OUT gctUINT32 * HorFactor,
    OUT gctUINT32 * VerFactor
    );

gceSTATUS gcoHARDWARE_SetGDIStretch(
    IN gctBOOL Enable
    );

/* Start a DE command. */
gceSTATUS
gcoHARDWARE_StartDE(
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command,
    IN gctUINT32 SrcRectCount,
    IN gcsRECT_PTR SrcRect,
    IN gctUINT32 DestRectCount,
    IN gcsRECT_PTR DestRect
    );

/* Start a DE command to draw one or more Lines,
   with a common or individual color. */
gceSTATUS
gcoHARDWARE_StartDELine(
    IN gcs2D_State_PTR State,
    IN gce2D_COMMAND Command,
    IN gctUINT32 RectCount,
    IN gcsRECT_PTR DestRect,
    IN gctUINT32 ColorCount,
    IN gctUINT32_PTR Color32
    );

/* Start a DE command with a monochrome stream. */
gceSTATUS
gcoHARDWARE_StartDEStream(
    IN gcs2D_State_PTR State,
    IN gcsRECT_PTR DestRect,
    IN gctUINT32 StreamSize,
    OUT gctPOINTER * StreamBits
    );

/* Frees the temporary buffer allocated by filter blit operation. */
gceSTATUS
gcoHARDWARE_FreeFilterBuffer(
    );

/* Filter blit. */
gceSTATUS
gcoHARDWARE_FilterBlit(
    IN gcs2D_State_PTR State,
    IN gcsSURF_INFO_PTR SrcSurface,
    IN gcsSURF_INFO_PTR DestSurface,
    IN gcsRECT_PTR SrcRect,
    IN gcsRECT_PTR DestRect,
    IN gcsRECT_PTR DestSubRect
    );

gceSTATUS gcoHARDWARE_MultiPlanarYUVConvert(
    IN gcsSURF_INFO_PTR SrcSurface,
    IN gcsSURF_INFO_PTR DestSurface,
    IN gcsRECT_PTR DestRect
    );

/* Monochrome blit. */
gceSTATUS
gcoHARDWARE_MonoBlit(
    IN gcs2D_State_PTR State,
    IN gctPOINTER StreamBits,
    IN gcsPOINT_PTR StreamSize,
    IN gcsRECT_PTR StreamRect,
    IN gceSURF_MONOPACK SrcStreamPack,
    IN gceSURF_MONOPACK DestStreamPack,
    IN gcsRECT_PTR DestRect
    );

/* Set the GPU clock cycles, after which the idle 2D engine
   will trigger a flush. */
gceSTATUS
gcoHARDWARE_SetAutoFlushCycles(
    IN gctUINT32 Cycles
    );

/******************************************************************************\
******************************** gcoBUFFER Object *******************************
\******************************************************************************/

/* Construct a new gcoBUFFER object. */
gceSTATUS
gcoBUFFER_Construct(
    IN gcoHAL Hal,
    IN gcoHARDWARE Hardware,
    IN gckCONTEXT Context,
    IN gctSIZE_T MaxSize,
    OUT gcoBUFFER * Buffer
    );

/* Destroy an gcoBUFFER object. */
gceSTATUS
gcoBUFFER_Destroy(
    IN gcoBUFFER Buffer
    );

/* Reserve space in a command buffer. */
gceSTATUS
gcoBUFFER_Reserve(
    IN gcoBUFFER Buffer,
    IN gctSIZE_T Bytes,
    IN gctBOOL Aligned,
    OUT gcoCMDBUF * Reserve
    );

/* Write data into the command buffer. */
gceSTATUS
gcoBUFFER_Write(
    IN gcoBUFFER Buffer,
    IN gctCONST_POINTER Data,
    IN gctSIZE_T Bytes,
    IN gctBOOL Aligned
    );

/* Doesn't have implementation */
/* Write 32-bit data into the command buffer. */
gceSTATUS
gcoBUFFER_Write32(
    IN gcoBUFFER Buffer,
    IN gctUINT32 Data,
    IN gctBOOL Aligned
    );
/* Doesn't have implementation */
/* Write 64-bit data into the command buffer. */
gceSTATUS
gcoBUFFER_Write64(
    IN gcoBUFFER Buffer,
    IN gctUINT64 Data,
    IN gctBOOL Aligned
    );

/* Commit the command buffer. */
gceSTATUS
gcoBUFFER_Commit(
    IN gcoBUFFER Buffer,
    IN gcePIPE_SELECT CurrentPipe,
    IN gcsSTATE_DELTA_PTR StateDelta,
    IN gcoQUEUE Queue
    );

/******************************************************************************\
******************************** gcoCMDBUF Object *******************************
\******************************************************************************/

typedef struct _gcsCOMMAND_INFO * gcsCOMMAND_INFO_PTR;

/* Construct a new gcoCMDBUF object. */
gceSTATUS
gcoCMDBUF_Construct(
    IN gcoOS Os,
    IN gcoHARDWARE Hardware,
    IN gctSIZE_T Bytes,
    IN gcsCOMMAND_INFO_PTR Info,
    OUT gcoCMDBUF * Buffer
    );

/* Destroy an gcoCMDBUF object. */
gceSTATUS
gcoCMDBUF_Destroy(
    IN gcoCMDBUF Buffer
    );

#ifdef LINUX
#define PENDING_FREED_MEMORY_SIZE_LIMIT     (4 * 1024 * 1024)
#endif

#if gcdSYNC
typedef enum _gceFENCE_STATUS
{
    gcvFENCE_DISABLE,
    gcvFENCE_GET,
    gcvFENCE_ENABLE,
}
gceFENCE_STATUS;
#endif

/******************************************************************************\
********************************* gcoHAL object *********************************
\******************************************************************************/

struct _gcoHAL
{
    gcsOBJECT               object;

    gcoDUMP                 dump;

#if VIVANTE_PROFILER
    gcsPROFILER             profiler;
#endif

    gcsATOM_PTR             reference;

#if gcdFRAME_DB
    gctINT                  frameDBIndex;
    gcsHAL_FRAME_INFO       frameDB[gcdFRAME_DB];
#endif

    gctINT32                chipCount;
    gceHARDWARE_TYPE        chipTypes[gcdCHIP_COUNT];
    gctBOOL                 separated3D2D;

    gctUINT32				timeOut;

    gcsUSER_DEBUG_OPTION    *userDebugOption;
};


/******************************************************************************\
********************************* gcoSURF object ********************************
\******************************************************************************/
#if gcdSYNC
typedef struct _gcsSYNC_CONTEXT
{
    gctUINT64               fenceID;
    gctUINT32               oqSlot;
    gctPOINTER              fence;
    gctBOOL                 mark;
    gcsSYNC_CONTEXT_PTR     next;
}
gcsSYNC_CONTEXT;
#endif

typedef struct _gcsSURF_NODE
{
    /* Surface memory pool. */
    gcePOOL                 pool;

    /* Lock count for the surface. */
    gctINT                  lockCount;

    /* If not zero, the node is locked in the kernel. */
    gctBOOL                 lockedInKernel;

    /* Locked hardware type */
    gceHARDWARE_TYPE        lockedHardwareType;

    /* Number of planes in the surface for planar format support. */
    gctUINT                 count;

    /* Node valid flag for the surface pointers. */
    gctBOOL                 valid;

    /* The physical addresses of the surface. */
    gctUINT32               physical;
    gctUINT32               physical2;
    gctUINT32               physical3;

    /* The logical addresses of the surface. */
    gctUINT8_PTR            logical;
    gctUINT8_PTR            logical2;
    gctUINT8_PTR            logical3;

    /* Linear size and filler for tile status. */
    gctSIZE_T               size;
    gctUINT32               filler;
    gctBOOL                 firstLock;

    union _gcuSURF_NODE_LIST
    {
        /* Allocated through HAL. */
        struct _gcsMEM_NODE_NORMAL
        {
            gctUINT64           node;
            gctBOOL             cacheable;
        }
        normal;

        /* Wrapped around user-allocated surface (gcvPOOL_USER). */
        struct _gcsMEM_NODE_WRAPPED
        {
            gctBOOL             logicalMapped;
            gctPOINTER          mappingInfo;
            gceHARDWARE_TYPE    mappingHardwareType;
        }
        wrapped;
    }
    u;
}
gcsSURF_NODE;

typedef struct _gcsSURF_INFO
{
    /* Type usage and format of surface. */
    gceSURF_TYPE            type;
    gceSURF_TYPE            hints;
    gceSURF_FORMAT          format;
    gceTILING               tiling;

    /* Surface size. */
    gcsRECT                 rect;
    gctUINT                 alignedWidth;
    gctUINT                 alignedHeight;
    gctBOOL                 is16Bit;
    gctSIZE_T               bitsPerPixel;

    /* Rotation flag. */
    gceSURF_ROTATION        rotation;
    gceORIENTATION          orientation;

    /* Dither flag. */
    gctBOOL                 dither;

    /* Surface stride and size. */
    gctUINT                 stride;
    gctUINT                 size;
    gctBOOL                 dirty;

    /* YUV planar surface parameters. */
    gctUINT                 uOffset;
    gctUINT                 vOffset;
    gctUINT                 uStride;
    gctUINT                 vStride;

    /* Video memory node for surface. */
    gcsSURF_NODE            node;

        /* Surface color type. */
    gceSURF_COLOR_TYPE      colorType;


    gctUINT                 offset;

    gceSURF_USAGE           usage;

    /* 2D related members. */
    gce2D_TILE_STATUS_CONFIG    tileStatusConfig;
    gceSURF_FORMAT              tileStatusFormat;
    gctUINT32                   tileStatusClearValue;
    gctUINT32                   tileStatusGpuAddress;

#if gcdSYNC
    gceFENCE_STATUS             fenceStatus;
    gcsSYNC_CONTEXT_PTR         fenceCtx;
#endif
}
gcsSURF_INFO;

struct _gcoSURF
{
    /* Object. */
    gcsOBJECT               object;

    /* Surface information structure. */
    struct _gcsSURF_INFO    info;

    /* Depth of the surface in planes. */
    gctUINT                 depth;


    /* Automatic stride calculation. */
    gctBOOL                 autoStride;

    /* User pointers for the surface wrapper. */
    gctPOINTER              logical;
    gctUINT32               physical;

    /* Reference count of surface. */
    gctINT32                referenceCount;
};

#define gcdMULTI_SOURCE_NUM 8

typedef struct _gcs2D_MULTI_SOURCE
{
    gce2D_SOURCE srcType;
    gcsSURF_INFO srcSurface;
    gceSURF_MONOPACK srcMonoPack;
    gctUINT32 srcMonoTransparencyColor;
    gctBOOL   srcColorConvert;
    gctUINT32 srcFgColor;
    gctUINT32 srcBgColor;
    gctUINT32 srcColorKeyLow;
    gctUINT32 srcColorKeyHigh;
    gctBOOL srcRelativeCoord;
    gctBOOL srcStream;
    gcsRECT srcRect;
    gce2D_YUV_COLOR_MODE srcYUVMode;

    gce2D_TRANSPARENCY srcTransparency;
    gce2D_TRANSPARENCY dstTransparency;
    gce2D_TRANSPARENCY patTransparency;

    gctBOOL enableDFBColorKeyMode;

    gctUINT8 fgRop;
    gctUINT8 bgRop;

    gctBOOL enableAlpha;
    gceSURF_PIXEL_ALPHA_MODE  srcAlphaMode;
    gceSURF_PIXEL_ALPHA_MODE  dstAlphaMode;
    gceSURF_GLOBAL_ALPHA_MODE srcGlobalAlphaMode;
    gceSURF_GLOBAL_ALPHA_MODE dstGlobalAlphaMode;
    gceSURF_BLEND_FACTOR_MODE srcFactorMode;
    gceSURF_BLEND_FACTOR_MODE dstFactorMode;
    gceSURF_PIXEL_COLOR_MODE  srcColorMode;
    gceSURF_PIXEL_COLOR_MODE  dstColorMode;
    gce2D_PIXEL_COLOR_MULTIPLY_MODE srcPremultiplyMode;
    gce2D_PIXEL_COLOR_MULTIPLY_MODE dstPremultiplyMode;
    gce2D_GLOBAL_COLOR_MULTIPLY_MODE srcPremultiplyGlobalMode;
    gce2D_PIXEL_COLOR_MULTIPLY_MODE dstDemultiplyMode;
    gctUINT32 srcGlobalColor;
    gctUINT32 dstGlobalColor;

} gcs2D_MULTI_SOURCE, *gcs2D_MULTI_SOURCE_PTR;

/* FilterBlt information. */
#define gcvMAXKERNELSIZE        9
#define gcvSUBPIXELINDEXBITS    5

#define gcvSUBPIXELCOUNT \
    (1 << gcvSUBPIXELINDEXBITS)

#define gcvSUBPIXELLOADCOUNT \
    (gcvSUBPIXELCOUNT / 2 + 1)

#define gcvWEIGHTSTATECOUNT \
    (((gcvSUBPIXELLOADCOUNT * gcvMAXKERNELSIZE + 1) & ~1) / 2)

#define gcvKERNELTABLESIZE \
    (gcvSUBPIXELLOADCOUNT * gcvMAXKERNELSIZE * sizeof(gctUINT16))

#define gcvKERNELSTATES \
    (gcmALIGN(gcvKERNELTABLESIZE + 4, 8))

typedef struct _gcsFILTER_BLIT_ARRAY
{
    gceFILTER_TYPE              filterType;
    gctUINT8                    kernelSize;
    gctUINT32                   scaleFactor;
    gctBOOL                     kernelChanged;
    gctUINT32_PTR               kernelStates;
}
gcsFILTER_BLIT_ARRAY;

typedef gcsFILTER_BLIT_ARRAY *  gcsFILTER_BLIT_ARRAY_PTR;

typedef struct _gcs2D_State
{
    gctUINT             currentSrcIndex;
    gcs2D_MULTI_SOURCE  multiSrc[gcdMULTI_SOURCE_NUM];
    gctUINT32           srcMask;

    /* dest info. */
    gcsSURF_INFO dstSurface;
    gctUINT32    dstColorKeyLow;
    gctUINT32    dstColorKeyHigh;

    gcsRECT      clipRect;

    /* brush info. */
    gce2D_PATTERN brushType;
    gctUINT32 brushOriginX;
    gctUINT32 brushOriginY;
    gctUINT32 brushColorConvert;
    gctUINT32 brushFgColor;
    gctUINT32 brushBgColor;
    gctUINT64 brushBits;
    gctUINT64 brushMask;
    gctUINT32 brushAddress;
    gceSURF_FORMAT brushFormat;

    /* Stretch factors. */
    gctUINT32 horFactor;
    gctUINT32 verFactor;

    /* Mirror. */
    gctBOOL horMirror;
    gctBOOL verMirror;

    /* Dithering enabled. */
    gctBOOL dither;

    /* Clear color. */
    gctUINT32 clearColor;

    /* Palette Table for source. */
    gctUINT32  paletteIndexCount;
    gctUINT32  paletteFirstIndex;
    gctBOOL    paletteConvert;
    gctBOOL    paletteProgram;
    gctPOINTER paletteTable;
    gceSURF_FORMAT paletteConvertFormat;


    /* Filter blit. */
    gceFILTER_TYPE              newFilterType;
    gctUINT8                    newHorKernelSize;
    gctUINT8                    newVerKernelSize;

    gctBOOL                     horUserFilterPass;
    gctBOOL                     verUserFilterPass;

    gcsFILTER_BLIT_ARRAY        horSyncFilterKernel;
    gcsFILTER_BLIT_ARRAY        verSyncFilterKernel;

    gcsFILTER_BLIT_ARRAY        horBlurFilterKernel;
    gcsFILTER_BLIT_ARRAY        verBlurFilterKernel;

    gcsFILTER_BLIT_ARRAY        horUserFilterKernel;
    gcsFILTER_BLIT_ARRAY        verUserFilterKernel;

    gctBOOL                     specialFilterMirror;

} gcs2D_State;

/******************************************************************************\
******************************** gcoQUEUE Object *******************************
\******************************************************************************/

/* Construct a new gcoQUEUE object. */
gceSTATUS
gcoQUEUE_Construct(
    IN gcoOS Os,
    OUT gcoQUEUE * Queue
    );

/* Destroy a gcoQUEUE object. */
gceSTATUS
gcoQUEUE_Destroy(
    IN gcoQUEUE Queue
    );

/* Append an event to a gcoQUEUE object. */
gceSTATUS
gcoQUEUE_AppendEvent(
    IN gcoQUEUE Queue,
    IN gcsHAL_INTERFACE * Interface
    );

/* Commit and event queue. */
gceSTATUS
gcoQUEUE_Commit(
    IN gcoQUEUE Queue
    );

/* Commit and event queue. */
gceSTATUS
gcoQUEUE_Free(
    IN gcoQUEUE Queue
    );


gceSTATUS
gcoOS_PrintStrVSafe(
    OUT gctSTRING String,
    IN gctSIZE_T StringSize,
    IN OUT gctUINT * Offset,
    IN gctCONST_STRING Format,
    IN gctARGUMENTS Arguments
    );

#ifdef __cplusplus
}
#endif

#endif /* __gc_hal_user_h_ */

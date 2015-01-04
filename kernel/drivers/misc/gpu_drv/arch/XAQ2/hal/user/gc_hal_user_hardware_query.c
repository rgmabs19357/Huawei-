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
#define _GC_OBJ_ZONE	gcvZONE_HARDWARE

/******************************************************************************\
****************************** gcoHARDWARE API Code *****************************
\******************************************************************************/

/*******************************************************************************
**
**	gcoHARDWARE_ConvertFormat
**
**	Convert an API format to hardware parameters.
**
**	INPUT:
**
**		gceSURF_FORMAT Format
**			API format to convert.
**
**	OUTPUT:
**
**		gctUINT32_PTR BitsPerPixel
**			Pointer to a variable that will hold the number of bits per pixel.
**
**		gctUINT32_PTR BytesPerTile
**			Pointer to a variable that will hold the number of bytes per tile.
*/
gceSTATUS gcoHARDWARE_ConvertFormat(
	IN gceSURF_FORMAT Format,
	OUT gctUINT32_PTR BitsPerPixel,
	OUT gctUINT32_PTR BytesPerTile
	)
{
	gctUINT32 bitsPerPixel = 0;
	gctUINT32 bytesPerTile = 0;
    gceSTATUS status;
	gcoHARDWARE hardware;

	gcmHEADER_ARG("Format=%d BitsPerPixel=0x%x BytesPerTile=0x%x",
				  Format, BitsPerPixel, BytesPerTile);

    gcmGETHARDWARE(hardware);

	/* Dispatch on format. */
	switch (Format)
	{
	case gcvSURF_INDEX8:
	case gcvSURF_A8:
	case gcvSURF_L8:
	case gcvSURF_R8:
		/* 8-bpp format. */
		bitsPerPixel  = 8;
		bytesPerTile  = (8 * 4 * 4) / 8;
		break;

	case gcvSURF_YV12:
	case gcvSURF_I420:
	case gcvSURF_NV12:
	case gcvSURF_NV21:
		/* 12-bpp planar YUV formats. */
		bitsPerPixel  = 12;
		bytesPerTile  = (12 * 4 * 4) / 8;
		break;

	case gcvSURF_A8L8:

    case gcvSURF_X8R8:
	case gcvSURF_G8R8:
	case gcvSURF_A8R8:

	case gcvSURF_X4R4G4B4:
	case gcvSURF_A4R4G4B4:

    case gcvSURF_R4G4B4X4:
    case gcvSURF_R4G4B4A4:

    case gcvSURF_X4B4G4R4:
    case gcvSURF_A4B4G4R4:

    case gcvSURF_B4G4R4X4:
    case gcvSURF_B4G4R4A4:

    case gcvSURF_X1R5G5B5:
	case gcvSURF_A1R5G5B5:

    case gcvSURF_R5G5B5X1:
    case gcvSURF_R5G5B5A1:

    case gcvSURF_B5G5R5X1:
    case gcvSURF_B5G5R5A1:

    case gcvSURF_X1B5G5R5:
    case gcvSURF_A1B5G5R5:

    case gcvSURF_R5G6B5:
    case gcvSURF_B5G6R5:

	case gcvSURF_YUY2:
	case gcvSURF_UYVY:
	case gcvSURF_YVYU:
	case gcvSURF_VYUY:
	case gcvSURF_NV16:
	case gcvSURF_NV61:
	case gcvSURF_D16:

	case gcvSURF_R16:
	case gcvSURF_A16:
	case gcvSURF_L16:

	case gcvSURF_R16F:
	case gcvSURF_A16F:
	case gcvSURF_L16F:

		/* 16-bpp format. */
		bitsPerPixel  = 16;
		bytesPerTile  = (16 * 4 * 4) / 8;
		break;

	case gcvSURF_X8R8G8B8:
	case gcvSURF_A8R8G8B8:
	case gcvSURF_X8B8G8R8:
	case gcvSURF_A8B8G8R8:
    case gcvSURF_R8G8B8X8:

    case gcvSURF_R8G8B8A8:

    case gcvSURF_B8G8R8X8:

    case gcvSURF_B8G8R8A8:

    case gcvSURF_X2B10G10R10:
    case gcvSURF_A2B10G10R10:

	case gcvSURF_D24X8:
	case gcvSURF_D24S8:
	case gcvSURF_D32:

	case gcvSURF_X16R16F:
	case gcvSURF_G16R16F:
	case gcvSURF_A16R16F:
	case gcvSURF_A16L16F:

    case gcvSURF_R32:
    case gcvSURF_A32:
	case gcvSURF_L32:

    case gcvSURF_R32F:
    case gcvSURF_A32F:
	case gcvSURF_L32F:

		/* 32-bpp format. */
		bitsPerPixel  = 32;
		bytesPerTile  = (32 * 4 * 4) / 8;
		break;

    case gcvSURF_X8G8R8:
    case gcvSURF_B8G8R8:
        {
		    /* Invalid format. */
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }
        break;

    case gcvSURF_X16G16R16:
    case gcvSURF_B16G16R16:
    case gcvSURF_X16G16R16F:
    case gcvSURF_B16G16R16F:
        {
		    /* Invalid format. */
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }
        break;

    case gcvSURF_X16B16G16R16:
    case gcvSURF_A16B16G16R16:
    case gcvSURF_X16B16G16R16F:
    case gcvSURF_A16B16G16R16F:

    case gcvSURF_X32R32:
    case gcvSURF_G32R32:
    case gcvSURF_A32R32:
    case gcvSURF_X32R32F:
    case gcvSURF_G32R32F:
    case gcvSURF_A32R32F:
        {
		    /* Invalid format. */
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }
        break;

    case gcvSURF_X32G32R32:
    case gcvSURF_B32G32R32:
    case gcvSURF_X32G32R32F:
    case gcvSURF_B32G32R32F:
        {
		    /* Invalid format. */
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }
        break;

    case gcvSURF_X32B32G32R32:
    case gcvSURF_A32B32G32R32:
    case gcvSURF_X32B32G32R32F:
    case gcvSURF_A32B32G32R32F:
        {
		    /* Invalid format. */
            gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
        }
        break;

	case gcvSURF_DXT1:
	case gcvSURF_ETC1:
        bitsPerPixel = 4;
        bytesPerTile = (4 * 4 * 4) / 8;
		break;

	case gcvSURF_DXT2:
	case gcvSURF_DXT3:
	case gcvSURF_DXT4:
	case gcvSURF_DXT5:
        bitsPerPixel = 8;
        bytesPerTile = (8 * 4 * 4) / 8;
		break;

    case gcvSURF_R11_EAC:
    case gcvSURF_SIGNED_R11_EAC:
    case gcvSURF_RG11_EAC:
    case gcvSURF_SIGNED_RG11_EAC:
    case gcvSURF_RGB8_ETC2:
    case gcvSURF_SRGB8_ETC2:
    case gcvSURF_RGB8_PUNCHTHROUGH_ALPHA1_ETC2:
    case gcvSURF_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2:
        bitsPerPixel = 4;
        bytesPerTile = (4 * 4 * 4) / 8;
        break;

    case gcvSURF_RGBA8_ETC2_EAC:
    case gcvSURF_SRGB8_ALPHA8_ETC2_EAC:
        bitsPerPixel = 8;
        bytesPerTile = (8 * 4 * 4) / 8;
        break;

	default:
		/* Invalid format. */
        gcmONERROR(gcvSTATUS_INVALID_ARGUMENT);
	}

	/* Set the result. */
	if (BitsPerPixel != gcvNULL)
	{
		* BitsPerPixel = bitsPerPixel;
	}

	if (BytesPerTile != gcvNULL)
	{
		* BytesPerTile = bytesPerTile;
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
**  gcoHARDWARE_QueryChipIdentity
**
**  Query the identity of the hardware.
**
**  INPUT:
**
**  OUTPUT:
**
**      gceCHIPMODEL* ChipModel
**          If 'ChipModel' is not gcvNULL, the variable it points to will
**          receive the model of the chip.
**
**      gctUINT32* ChipRevision
**          If 'ChipRevision' is not gcvNULL, the variable it points to will
**          receive the revision of the chip.
**
**      gctUINT32* ChipFeatures
**          If 'ChipFeatures' is not gcvNULL, the variable it points to will
**          receive the feature set of the chip.
**
**      gctUINT32 * ChipMinorFeatures
**          If 'ChipMinorFeatures' is not gcvNULL, the variable it points to
**          will receive the minor feature set of the chip.
**
**      gctUINT32 * ChipMinorFeatures1
**          If 'ChipMinorFeatures1' is not gcvNULL, the variable it points to
**          will receive the minor feature set 1 of the chip.
**
*/
gceSTATUS gcoHARDWARE_QueryChipIdentity(
    OUT gceCHIPMODEL* ChipModel,
    OUT gctUINT32* ChipRevision,
    OUT gctUINT32* ChipFeatures,
    OUT gctUINT32* ChipMinorFeatures,
    OUT gctUINT32* ChipMinorFeatures1,
    OUT gctUINT32* ChipMinorFeatures2
    )
{
    gceSTATUS status = gcvSTATUS_OK;
	gcoHARDWARE hardware;

    gcmHEADER_ARG("ChipModel=0x%x ChipRevision=0x%x "
                    "ChipFeatures=0x%x ChipMinorFeatures=0x%x ChipMinorFeatures1=0x%x",
                    ChipModel, ChipRevision,
                    ChipFeatures, ChipMinorFeatures, ChipMinorFeatures1);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    /* Return chip model. */
    if (ChipModel != gcvNULL)
    {
        *ChipModel = hardware->chipModel;
    }

    /* Return revision number. */
    if (ChipRevision != gcvNULL)
    {
        *ChipRevision = hardware->chipRevision;
    }

    /* Return feature set. */
    if (ChipFeatures != gcvNULL)
    {
        *ChipFeatures = hardware->chipFeatures;
    }

    /* Return minor feature set. */
    if (ChipMinorFeatures != gcvNULL)
    {
        *ChipMinorFeatures = hardware->chipMinorFeatures;
    }

    /* Return minor feature set 1. */
    if (ChipMinorFeatures1 != gcvNULL)
    {
        *ChipMinorFeatures1 = hardware->chipMinorFeatures1;
    }

    /* Return minor feature set 1. */
    if (ChipMinorFeatures2 != gcvNULL)
    {
        *ChipMinorFeatures2 = hardware->chipMinorFeatures2;
    }

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**	gcoHARDWARE_QueryCommandBuffer
**
**	Query the command buffer alignment and number of reserved bytes.
**
**	INPUT:
**
**		gcoHARDWARE Harwdare
**			Pointer to an gcoHARDWARE object.
**
**	OUTPUT:
**
**		gctSIZE_T * Alignment
**			Pointer to a variable receiving the alignment for each command.
**
**		gctSIZE_T * ReservedHead
**			Pointer to a variable receiving the number of reserved bytes at the
**          head of each command buffer.
**
**		gctSIZE_T * ReservedTail
**			Pointer to a variable receiving the number of bytes reserved at the
**          tail of each command buffer.
*/
gceSTATUS gcoHARDWARE_QueryCommandBuffer(
    OUT gctSIZE_T * Alignment,
    OUT gctSIZE_T * ReservedHead,
    OUT gctSIZE_T * ReservedTail
    )
{
	gcmHEADER_ARG("Alignment=0x%x ReservedHead=0x%x ReservedTail=0x%x",
				  Alignment, ReservedHead, ReservedTail);

    if (Alignment != gcvNULL)
    {
        /* Align every 8 bytes. */
        *Alignment = 8;
    }

    if (ReservedHead != gcvNULL)
    {
        /* Reserve space for SelectPipe. */
        *ReservedHead = 32;
    }

    if (ReservedTail != gcvNULL)
    {
        /* Reserve space for Link(). */
        *ReservedTail = 8;
    }

    /* Success. */
	gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gcoHARDWARE_AlignToTile
**
**  Align the specified width and height to tile boundaries.
**
**  INPUT:
**
**      gceSURF_TYPE Type
**          Type of alignment.
**
**      gctUINT32 * Width
**          Pointer to the width to be aligned.  If 'Width' is gcvNULL, no width
**          will be aligned.
**
**      gctUINT32 * Height
**          Pointer to the height to be aligned.  If 'Height' is gcvNULL, no height
**          will be aligned.
**
**  OUTPUT:
**
**      gctUINT32 * Width
**          Pointer to a variable that will receive the aligned width.
**
**      gctUINT32 * Height
**          Pointer to a variable that will receive the aligned height.
**
**      gctBOOL_PTR SuperTiled
**          Pointer to a variable that receives the super-tiling flag for the
**          surface.
*/
gceSTATUS
gcoHARDWARE_AlignToTile(
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN OUT gctUINT32_PTR Width,
    IN OUT gctUINT32_PTR Height,
    OUT gctBOOL_PTR SuperTiled
    )
{
    gceSTATUS status;
    gctBOOL superTiled = gcvFALSE;
    gctUINT32 xAlignment, yAlignment;
    gctBOOL hAlignmentAvailable = gcvFALSE;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Type=%d Format=0x%x Width=0x%x Height=0x%x",
                  Type, Format, Width, Height);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);


    /* Compute alignment factors. */
    /* Change gcoHARDWARE_QueryTileAlignment, if this is changed. */
    xAlignment = superTiled ? 64
               : ((Type == gcvSURF_TEXTURE) && !hAlignmentAvailable) ? 4
               : 16;

    yAlignment = superTiled ? 64 : 4;

    if (((Type & ~gcvSURF_NO_TILE_STATUS) == gcvSURF_RENDER_TARGET)
     || ((Type & ~gcvSURF_NO_TILE_STATUS) == gcvSURF_DEPTH)
     || (Type == gcvSURF_TILE_STATUS))
    {
        yAlignment *= hardware->pixelPipes;
    }

    if (Width != gcvNULL)
    {
        /* Align the width. */
        *Width = gcmALIGN(*Width, xAlignment);
    }

    if (Height != gcvNULL)
    {
        /* Align the height. */
        *Height = gcmALIGN(*Height, yAlignment);
    }

    if (SuperTiled != gcvNULL)
    {
        /* Copy the super tiling. */
        *SuperTiled = superTiled;
    }

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_AlignToTileCompatible
**
**  Align the specified width and height to compatible size for all cores exist
**  in this hardware.
**
**  INPUT:
**
**      gceSURF_TYPE Type
**          Type of alignment.
**
**      gctUINT32 * Width
**          Pointer to the width to be aligned.  If 'Width' is gcvNULL, no width
**          will be aligned.
**
**      gctUINT32 * Height
**          Pointer to the height to be aligned.  If 'Height' is gcvNULL, no height
**          will be aligned.
**
**  OUTPUT:
**
**      gctUINT32 * Width
**          Pointer to a variable that will receive the aligned width.
**
**      gctUINT32 * Height
**          Pointer to a variable that will receive the aligned height.
**
**      gceTILING * Tiling
**          Pointer to a variable that receives the detailed tiling info.
**
**      gctBOOL_PTR SuperTiled
**          Pointer to a variable that receives the super-tiling flag for the
**          surface.
*/
gceSTATUS
gcoHARDWARE_AlignToTileCompatible(
    IN gceSURF_TYPE Type,
    IN gceSURF_FORMAT Format,
    IN OUT gctUINT32_PTR Width,
    IN OUT gctUINT32_PTR Height,
    OUT gceTILING * Tiling,
    OUT gctBOOL_PTR SuperTiled
    )
{
    gceSTATUS status;
    gctBOOL superTiled = gcvFALSE;
    gceTILING tiling;
    gctUINT32 xAlignment, yAlignment;
    gctBOOL hAlignmentAvailable = gcvFALSE;
    gcsTLS_PTR tls;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Type=%d Format=0x%x Width=0x%x Height=0x%x",
                  Type, Format, Width, Height);

    gcmONERROR(
        gcoOS_GetTLS(&tls));

    /* Always take 3D hardware. */
    hardware = tls->hardware;

    if (hardware == gcvNULL)
    {
        /* Save previous hardware type. */
        gceHARDWARE_TYPE prevType = tls->currentType;

        /* Set to 3D hardwawre. */
        tls->currentType = gcvHARDWARE_3D;

        /* Construct hardware. */
        status = gcoHARDWARE_Construct(gcPLS.hal, &tls->hardware);

        /* Set back to previous type. */
        tls->currentType = prevType;

        /* Break if error. */
        gcmONERROR(status);

        /* Get hardware. */
        hardware = tls->hardware;
    }

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    switch (Type)
    {
    case gcvSURF_RENDER_TARGET_NO_TILE_STATUS:
    case gcvSURF_DEPTH_NO_TILE_STATUS:
        /*
         * TODO: Is this always the render into texture case?
         * Tile alignment for render into texture. If supertiled texture and
         * supertiled render target are both supported, use super tile
         * alignment. Otherwise tile alignment is taken.
         */
        superTiled = ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 3:3) & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1)))))) == (0x1 & ((gctUINT32) ((((1 ? 3:3) - (0 ? 3:3) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 3:3) - (0 ? 3:3) + 1)))))))
                  && ((((gctUINT32) (hardware->chipMinorFeatures)) >> (0 ? 12:12) & ((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1)))))) == (0x1 & ((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1)))))));

        if (hardware->pixelPipes > 1)
        {
            superTiled = gcvTRUE;
        }

        /* Compute alignment factors. */
        xAlignment = superTiled ? 64 : 16;
        yAlignment = superTiled ? (64 * hardware->pixelPipes)
            : (4 * hardware->pixelPipes);

        if (hardware->pixelPipes > 1)
        {
            tiling = superTiled ? gcvMULTI_SUPERTILED : gcvMULTI_TILED;
        }
        else
        {
            tiling = superTiled ? gcvSUPERTILED : gcvTILED;
        }

        break;

    case gcvSURF_RENDER_TARGET:
    case gcvSURF_DEPTH:


        /* Compute alignment factors. */
        xAlignment = superTiled ? 64 : 16;
        yAlignment = superTiled ? (64 * hardware->pixelPipes)
            : (4 * hardware->pixelPipes);

        if (hardware->pixelPipes > 1)
        {
            tiling = superTiled ? gcvMULTI_SUPERTILED : gcvMULTI_TILED;
        }
        else
        {
            tiling = superTiled ? gcvSUPERTILED : gcvTILED;
        }

        break;

    case gcvSURF_TEXTURE:
        /* Only 4x4 tiled texture here. */
        /* Textures can be better aligned. */

        xAlignment = superTiled ? 64 : hAlignmentAvailable ? 16 : 4;
        yAlignment = superTiled ? 64 : 4;
        tiling     = superTiled ? gcvSUPERTILED : gcvTILED;

        /* Need to be aligned for resolve. */
        yAlignment *= hardware->pixelPipes;
        break;

    default:
        xAlignment = 16;
        yAlignment = 4 * hardware->pixelPipes;
        tiling     = gcvLINEAR;
    }

    if (Width != gcvNULL)
    {
        /* Align the width. */
        *Width = gcmALIGN(*Width, xAlignment);
    }

    if (Height != gcvNULL)
    {
        /* Align the height. */
        *Height = gcmALIGN(*Height, yAlignment);
    }

    if (Tiling != gcvNULL)
    {
        /* Copy the tiling. */
        *Tiling = tiling;
    }

    if (SuperTiled != gcvNULL)
    {
        /* Copy the super tiling. */
        *SuperTiled = superTiled;
    }

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}



/*******************************************************************************
**
**	gcoHARDWARE_QueryTileSize
**
**	Query the tile sizes.
**
**	INPUT:
**
**		Nothing.
**
**	OUTPUT:
**
**		gctINT32 * TileWidth2D
**			Pointer to a variable receiving the width in pixels per 2D tile.  If
**			the 2D is working in linear space, the width will be 1.  If there is
**			no 2D, the width will be 0.
**
**		gctINT32 * TileHeight2D
**			Pointer to a variable receiving the height in pixels per 2D tile.
**			If the 2D is working in linear space, the height will be 1.  If
**			there is no 2D, the height will be 0.
**
**		gctINT32 * TileWidth3D
**			Pointer to a variable receiving the width in pixels per 3D tile.  If
**			the 3D is working in linear space, the width will be 1.  If there is
**			no 3D, the width will be 0.
**
**		gctINT32 * TileHeight3D
**			Pointer to a variable receiving the height in pixels per 3D tile.
**			If the 3D is working in linear space, the height will be 1.  If
**			there is no 3D, the height will be 0.
**
**		gctUINT32 * Stride
**			Pointer to  variable receiving the stride requirement for all modes.
*/
gceSTATUS gcoHARDWARE_QueryTileSize(
	OUT gctINT32 * TileWidth2D,
	OUT gctINT32 * TileHeight2D,
	OUT gctINT32 * TileWidth3D,
	OUT gctINT32 * TileHeight3D,
	OUT gctUINT32 * Stride
	)
{
	gcmHEADER_ARG("TileWidth2D=0x%x TileHeight2D=0x%x TileWidth3D=0x%x "
					"TileHeight3D=0x%x Stride=0x%x",
					TileWidth2D, TileHeight2D, TileWidth3D,
					TileHeight3D, Stride);

	if (TileWidth2D != gcvNULL)
	{
		/* 1 pixel per 2D tile (linear). */
		*TileWidth2D = 1;
	}

	if (TileHeight2D != gcvNULL)
	{
		/* 1 pixel per 2D tile (linear). */
		*TileHeight2D = 1;
	}

	if (TileWidth3D != gcvNULL)
	{
		/* 4 pixels per 3D tile for now. */
		*TileWidth3D = 4;
	}

	if (TileHeight3D != gcvNULL)
	{
		/* 4 lines per 3D tile. */
		*TileHeight3D = 4;
	}

	if (Stride != gcvNULL)
	{
		/* 64-byte stride requirement. */
		*Stride = 64;
	}

	/* Success. */
	gcmFOOTER_NO();
	return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gcoHARDWARE_IsFeatureAvailable
**
**  Verifies whether the specified feature is available in hardware.
**
**  INPUT:
**
**      gceFEATURE Feature
**          Feature to be verified.
*/
gceSTATUS
gcoHARDWARE_IsFeatureAvailable(
    IN gceFEATURE Feature
    )
{
    gceSTATUS status;
    gctBOOL available = gcvFALSE;
    gcoHARDWARE hardware;

    gcmHEADER_ARG("Feature=%d", Feature);

    gcmGETHARDWARE(hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(hardware, gcvOBJ_HARDWARE);

    switch (Feature)
    {
    /* Generic features. */
    case gcvFEATURE_PIPE_2D:
        available = hardware->hw2DEngine;
        break;

    case gcvFEATURE_PIPE_3D:
        available = gcvFALSE;
        break;

    case gcvFEATURE_FULL_DIRECTFB:
        available = hardware->hw2DFullDFB;
        break;

    case gcvFEATURE_2D_TILING:
        /* Fall through. */
    case gcvFEATURE_2D_YUV_BLIT:
        available = hardware->hw2DOPF;
        break;

    case gcvFEATURE_2D_MULTI_SOURCE_BLT:
        available = hardware->hw2DMultiSrcBlit;
        break;

    case gcvFEATURE_2D_MULTI_SOURCE_BLT_EX:
    case gcvFEATURE_2D_MINOR_TILING:
    case gcvFEATURE_2D_YUV_SEPARATE_STRIDE:
        available = hardware->hw2DNewFeature0;
        break;

    case gcvFEATURE_2D_FILTERBLIT_PLUS_ALPHABLEND:
        /* Fall through. */
    case gcvFEATURE_2D_DITHER:
        available = hardware->dither2DandAlphablendFilter;
        break;

    case gcvFEATURE_2D_A8_TARGET:
        available =
            ((((gctUINT32) (hardware->chipMinorFeatures)) >> (0 ? 29:29) & ((gctUINT32) ((((1 ? 29:29) - (0 ? 29:29) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 29:29) - (0 ? 29:29) + 1)))))) == (0x1 & ((gctUINT32) ((((1 ? 29:29) - (0 ? 29:29) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 29:29) - (0 ? 29:29) + 1)))))))
            || ((((gctUINT32) (hardware->chipMinorFeatures2)) >> (0 ? 22:22) & ((gctUINT32) ((((1 ? 22:22) - (0 ? 22:22) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 22:22) - (0 ? 22:22) + 1)))))) == (0x1 & ((gctUINT32) ((((1 ? 22:22) - (0 ? 22:22) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 22:22) - (0 ? 22:22) + 1)))))));
        break;

    case gcvFEATURE_2D_FILTERBLIT_FULLROTATION:
        available = hardware->fullFilterBlitRotation;
        break;

    case gcvFEATURE_2D_BITBLIT_FULLROTATION:
        available = hardware->fullBitBlitRotation;
        break;

    case gcvFEATURE_YUV420_SCALER:
        available = ((((gctUINT32) (hardware->chipFeatures)) >> (0 ? 6:6) & ((gctUINT32) ((((1 ? 6:6) - (0 ? 6:6) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 6:6) - (0 ? 6:6) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 6:6) - (0 ? 6:6) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 6:6) - (0 ? 6:6) + 1)))))));
        break;

    case gcvFEATURE_2DPE20:
        available = hardware->hw2DPE20;
        break;

    case gcvFEATURE_2D_NO_COLORBRUSH_INDEX8:
        available = hardware->hw2DNoIndex8_Brush;
        break;

    /* Filter Blit. */
    case gcvFEATURE_SCALER:
        available = ((((gctUINT32) (hardware->chipFeatures)) >> (0 ? 20:20) & ((gctUINT32) ((((1 ? 20:20) - (0 ? 20:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 20:20) - (0 ? 20:20) + 1)))))) == (0x0  & ((gctUINT32) ((((1 ? 20:20) - (0 ? 20:20) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 20:20) - (0 ? 20:20) + 1)))))));
        break;

    /* Rotation stall fix. */
    case gcvFEATURE_2D_ROTATION_STALL_FIX:
        available = ((((gctUINT32) (hardware->chipMinorFeatures3)) >> (0 ? 0:0) & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 0:0) - (0 ? 0:0) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 0:0) - (0 ? 0:0) + 1)))))));
        break;

    /* Load/Store L1 cache hang fix. */
    case gcvFEATURE_BUG_FIXES10:
        available = ((((gctUINT32) (hardware->chipMinorFeatures3)) >> (0 ? 10:10) & ((gctUINT32) ((((1 ? 10:10) - (0 ? 10:10) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 10:10) - (0 ? 10:10) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 10:10) - (0 ? 10:10) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 10:10) - (0 ? 10:10) + 1)))))));
        break;

    case gcvFEATURE_BUG_FIXES11:
        available = ((((gctUINT32) (hardware->chipMinorFeatures3)) >> (0 ? 12:12) & ((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 12:12) - (0 ? 12:12) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 12:12) - (0 ? 12:12) + 1)))))));
        break;

    case gcvFEATURE_2D_FC_SOURCE:
        available = ((((gctUINT32) (hardware->chipMinorFeatures3)) >> (0 ? 23:23) & ((gctUINT32) ((((1 ? 23:23) - (0 ? 23:23) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 23:23) - (0 ? 23:23) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 23:23) - (0 ? 23:23) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 23:23) - (0 ? 23:23) + 1)))))));
        break;


    case gcvFEATURE_2D_MIRROR_EXTENSION:
        available = hardware->mirrorExtension;
        break;

    case gcvFEATURE_ELEMENT_INDEX_UINT:
        available = ((((gctUINT32) (hardware->chipFeatures)) >> (0 ? 31:31) & ((gctUINT32) ((((1 ? 31:31) - (0 ? 31:31) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:31) - (0 ? 31:31) + 1)))))) == (0x1  & ((gctUINT32) ((((1 ? 31:31) - (0 ? 31:31) + 1) == 32) ? ~0 : (~(~0 << ((1 ? 31:31) - (0 ? 31:31) + 1)))))));
        break;

    default:
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    status = available
        ? gcvSTATUS_TRUE
        : gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

/*******************************************************************************
**
**  gcoHARDWARE_Is2DAvailable
**
**  Verifies whether 2D engine is available.
**
**  INPUT:
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_Is2DAvailable(
    )
{
    gceSTATUS status;
    gcoHARDWARE hardware;

    gcmHEADER();

    gcmGETHARDWARE(hardware);

    status = hardware->hw2DEngine
        ? gcvSTATUS_TRUE
        : gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}




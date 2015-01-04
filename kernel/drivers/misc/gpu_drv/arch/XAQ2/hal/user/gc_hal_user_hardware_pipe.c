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


/*
 * $RCSfile: gc_hal_user_hardware_pipe.c,v $
 *
 * Pipe select code for architecture dependent user HAL layers.
 *
 * Written by Frido Garritsen
 *
 *
 */

#include "gc_hal_user_hardware_precomp.h"

/* Zone used for header/footer. */
#define _GC_OBJ_ZONE    gcvZONE_HARDWARE

/******************************************************************************\
****************************** gcoHARDWARE API Code *****************************
\******************************************************************************/

/*******************************************************************************
**
**  gcoHARDWARE_SelectPipe
**
**  Select the current pipe for this hardare context.
**
**  INPUT:
**
**      gcoHARDWARE Hardware
**          Pointer to an AQHARWDARE object.
**
**      gcePIPE_SELECT Pipe
**          Pipe to select.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gcoHARDWARE_SelectPipe(
    IN gcoHARDWARE Hardware,
    IN gcePIPE_SELECT Pipe
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Hardware=0x%x Pipe=%d", Hardware, Pipe);

    gcmGETHARDWARE(Hardware);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

    /* Is 2D pipe present? */
    if ((Pipe == gcvPIPE_2D) && !Hardware->hw2DEngine)
    {
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

    /* Don't do anything if the pipe has already been selected. */
    if (Hardware->currentPipe != Pipe)
    {
        /* Not supposed to be pipe switching in NO_3D driver. */
        gcmONERROR(gcvSTATUS_NOT_SUPPORTED);
    }

OnError:
    /* Return status. */
    gcmFOOTER();
    return status;
}


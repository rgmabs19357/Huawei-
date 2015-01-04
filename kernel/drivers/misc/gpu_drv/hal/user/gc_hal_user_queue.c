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
**  Architecture independent event queue management.
**
*/

#include "gc_hal_user_precomp.h"
#include "gc_hal_user_buffer.h"

/* Zone used for header/footer. */
#define _GC_OBJ_ZONE    gcvZONE_BUFFER


gceSTATUS
gcoQUEUE_Construct(
    IN gcoOS Os,
    OUT gcoQUEUE * Queue
    )
{
    gcoQUEUE queue = gcvNULL;
    gceSTATUS status;
    gctPOINTER pointer = gcvNULL;

    gcmHEADER();

    /* Verify the arguments. */
    gcmVERIFY_ARGUMENT(Queue != gcvNULL);

    /* Create the queue. */
    gcmONERROR(
        gcoOS_Allocate(gcvNULL,
                       gcmSIZEOF(struct _gcoQUEUE),
                       &pointer));
    queue = pointer;

    /* Initialize the object. */
    queue->object.type = gcvOBJ_QUEUE;

    /* Nothing in the queue yet. */
    queue->head = queue->tail = gcvNULL;

    queue->recordCount = 0;

    queue->freeList = gcvNULL;

    /* Return gcoQUEUE pointer. */
    *Queue = queue;

    /* Success. */
    gcmFOOTER_ARG("*Queue=0x%x", *Queue);
    return gcvSTATUS_OK;

OnError:
    if (queue != gcvNULL)
    {
        /* Roll back. */
        gcmVERIFY_OK(gcmOS_SAFE_FREE(gcvNULL, queue));
    }

    /* Return the status. */
    gcmFOOTER();
    return status;
}

gceSTATUS
gcoQUEUE_Destroy(
    IN gcoQUEUE Queue
    )
{
    gceSTATUS status;

    gcmHEADER_ARG("Queue=0x%x", Queue);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Queue, gcvOBJ_QUEUE);

    /* Free any records in the queue. */
    while (Queue->head != gcvNULL)
    {
        gcsQUEUE_PTR record;

        /* Unlink the first record from the queue. */
        record      = Queue->head;
        Queue->head = gcmUINT64_TO_PTR(record->next);

        gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, record));
    }

    /* Free any records in the free list. */
    while (Queue->freeList != gcvNULL)
    {
        gcsQUEUE_PTR record;

        /* Unlink the first record from the queue. */
        record          = Queue->freeList;
        Queue->freeList = gcmUINT64_TO_PTR(record->next);

        gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, record));
    }

    /* Free the queue. */
    gcmONERROR(gcmOS_SAFE_FREE(gcvNULL, Queue));

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

gceSTATUS
gcoQUEUE_AppendEvent(
    IN gcoQUEUE Queue,
    IN gcsHAL_INTERFACE * Interface
    )
{
    gceSTATUS status;
    gcsQUEUE_PTR record = gcvNULL;
    gctPOINTER pointer = gcvNULL;

    gcmHEADER_ARG("Queue=0x%x Interface=0x%x", Queue, Interface);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Queue, gcvOBJ_QUEUE);
    gcmVERIFY_ARGUMENT(Interface != gcvNULL);

    /* Allocate record. */
    /* Check if we have records on the free list. */
    if (Queue->freeList != gcvNULL)
    {
        /* Allocate from hte free list. */
        record          = Queue->freeList;
        Queue->freeList = gcmUINT64_TO_PTR(record->next);
    }
    else
    {
        gcmONERROR(gcoOS_Allocate(gcvNULL,
                       gcmSIZEOF(gcsQUEUE),
                                  &pointer));
        record = pointer;
    }

    /* Initialize record. */
    record->next  = 0;
    gcoOS_MemCopy(&record->iface, Interface, gcmSIZEOF(record->iface));

    if (Queue->head == gcvNULL)
    {
        /* Initialize queue. */
        Queue->head = record;
    }
    else
    {
        /* Append record to end of queue. */
        Queue->tail->next = gcmPTR_TO_UINT64(record);
    }

    /* Mark end of queue. */
    Queue->tail = record;

    /* update count */
    Queue->recordCount++;

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    if (pointer != gcvNULL)
    {
        /* Put record on free list. */
        record->next    = gcmPTR_TO_UINT64(Queue->freeList);
        Queue->freeList = record;
    }

    /* Return the status. */
    gcmFOOTER();
    return status;
}

gceSTATUS
gcoQUEUE_Free(
    IN gcoQUEUE Queue
    )
{
    gcmHEADER_ARG("Queue=0x%x", Queue);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Queue, gcvOBJ_QUEUE);

    /* Free any records in the queue. */
    while (Queue->head != gcvNULL)
    {
        gcsQUEUE_PTR record;

        /* Unlink the first record from the queue. */
        record      = Queue->head;
        Queue->head = gcmUINT64_TO_PTR(record->next);

        /* Put record on free list. */
        record->next    = gcmPTR_TO_UINT64(Queue->freeList);
        Queue->freeList = record;
    }

    /* Update count */
    Queue->recordCount = 0;

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;
}

gceSTATUS
gcoQUEUE_Commit(
    IN gcoQUEUE Queue
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcsHAL_INTERFACE iface;

    gcmHEADER_ARG("Queue=0x%x", Queue);

    /* Verify the arguments. */
    gcmVERIFY_OBJECT(Queue, gcvOBJ_QUEUE);

    if (Queue->head != gcvNULL)
    {
        /* Initialize event commit command. */
        iface.command       = gcvHAL_EVENT_COMMIT;
        iface.u.Event.queue = gcmPTR_TO_UINT64(Queue->head);

        /* Send command to kernel. */
        gcmONERROR(
            gcoOS_DeviceControl(gcvNULL,
                                IOCTL_GCHAL_INTERFACE,
                                &iface, gcmSIZEOF(iface),
                                &iface, gcmSIZEOF(iface)));

        /* Test for error. */
        gcmONERROR(iface.status);

        /* Free any records in the queue. */
        gcmONERROR(gcoQUEUE_Free(Queue));
    }

    /* Success. */
    gcmFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmFOOTER();
    return status;
}

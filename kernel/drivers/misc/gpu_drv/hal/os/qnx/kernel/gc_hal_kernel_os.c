/****************************************************************************
*
*    Copyright (C) 2005 - 2013 by Vivante Corp.
*
*    This program is free software; you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation; either version 2 of the license, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not write to the Free Software
*    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
*****************************************************************************/


#include "gc_hal_kernel_qnx.h"

#include <signal.h>
#include <fastmemcpy.h>
#include <sys/time.h>
#include <sys/slog.h>
#include <semaphore.h>
#include <screen/gpu.h>
#include <errno.h>

/* for ARM_PTE_... */
#include <arm/mmu.h>

/* TODO: Redefined. Put in common header. */
#define GC_HAL_QNX_PULSEVAL_SIGNAL  (_PULSE_CODE_MINAVAIL+1)

#define USE_VMALLOC 0

#define _GC_OBJ_ZONE gcvZONE_OS

/*******************************************************************************
***** Version Signature *******************************************************/

const char * _PLATFORM = "\n\0$PLATFORM$QNX$\n";

#define MEMORY_LOCK(os) \
    gcmkVERIFY_OK(gckOS_AcquireMutex( \
                                (os), \
                                (os)->memoryLock, \
                                gcvINFINITE))

#define MEMORY_UNLOCK(os) \
    gcmkVERIFY_OK(gckOS_ReleaseMutex((os), (os)->memoryLock))

#define MEMORY_MAP_LOCK(os) \
    gcmkVERIFY_OK(gckOS_AcquireMutex( \
                                (os), \
                                (os)->memoryMapLock, \
                                gcvINFINITE))

#define MEMORY_MAP_UNLOCK(os) \
    gcmkVERIFY_OK(gckOS_ReleaseMutex((os), (os)->memoryMapLock))

/******************************************************************************\
********************************** Structures **********************************
\******************************************************************************/

struct _gckOS
{
    /* Object. */
    gcsOBJECT                   object;

    /* Heap. */
    gckHEAP                     heap;

    /* Pointer to device */
    gckGALDEVICE                device;

    /* Memory management */
    gctPOINTER                  memoryLock;
    gctPOINTER                  memoryMapLock;
    gctPOINTER                  mempoolBaseAddress;
    gctPOINTER                  mempoolBasePAddress;
    gctUINT32                   mempoolPageSize;

    gctUINT32                   baseAddress;

    /* Debug lock. */
    gctPOINTER                  debugLock;
};


typedef struct _gcskSIGNAL
{
    /* Signaled state. */
    gctBOOL         state;

    /* Manual reset flag. */
    gctBOOL         reset;

    /* Mutex. */
    pthread_mutex_t mutex;

    /* Condition. */
    pthread_cond_t  cond;
}
gcskSIGNAL;

typedef struct _gcskSIGNAL *    gcskSIGNAL_PTR;

typedef struct _gcsOSTIMER
{
    gckOS               os;
    gctPOINTER          mutex;
    gctPOINTER          sema;
    gctTIMERFUNCTION    func;
    gctPOINTER          data;
    gctUINT64           dueTime;
    pthread_t           tid;
    gctBOOL             quit;
}
gcsOSTIMER;

typedef struct _gcsOSTIMER * gcsOSTIMER_PTR;

typedef struct _gcskATOM
{
    gctINT32            counter;
    pthread_mutex_t     mutex;
} gcskATOM;

typedef struct _gcskATOM * gcskATOM_PTR;

/******************************************************************************\
******************************* Private Functions ******************************
\******************************************************************************/

static void *_KernelTimerThread(void *data)
{
    gcsOSTIMER_PTR timer = (gcsOSTIMER_PTR)data;
    gctUINT64 current = 0;
    gctBOOL trigger = gcvFALSE;
    gctBOOL stopped = gcvFALSE;

    while (1)
    {
Continue:
        gckOS_AcquireSemaphore(timer->os, timer->sema);

        while (1)
        {
            if (timer->quit)
            {
                goto Exit;
            }

            gckOS_GetTime(&current);

            gckOS_AcquireMutex(timer->os, timer->mutex, gcvINFINITE);

            if (timer->dueTime == -1)
            {
                stopped = gcvTRUE;
            }
            else if (current >= timer->dueTime)
            {
                timer->dueTime = -1;
                trigger = gcvTRUE;
            }

            gckOS_ReleaseMutex(timer->os, timer->mutex);

            if (stopped)
            {
                stopped = gcvFALSE;
                goto Continue;
            }

            if (trigger)
            {
                (timer->func)(timer->data);
                trigger = gcvFALSE;
                goto Continue;
            }

            gckOS_Delay(timer->os, 10);
        }
    }

Exit:
    return 0;
}

/*******************************************************************************
**
**  gckOS_Construct
**
**  Construct a new gckOS object.
**
**  INPUT:
**
**      gctPOINTER Context
**          Pointer to the gckGALDEVICE class.
**
**  OUTPUT:
**
**      gckOS * Os
**          Pointer to a variable that will hold the pointer to the gckOS object.
*/
gceSTATUS
gckOS_Construct(
    IN gctPOINTER Context,
    OUT gckOS * Os
    )
{
    gckOS os;
    gceSTATUS status;

    gcmkHEADER_ARG("Context=0x%X", Context);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Os != gcvNULL);

    /* Allocate the gckOS object. */
    os = (gckOS) malloc(gcmSIZEOF(struct _gckOS));

    if (os == gcvNULL)
    {
        /* Out of memory. */
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_MEMORY);
        return gcvSTATUS_OUT_OF_MEMORY;
    }

    /* Zero the memory. */
    gckOS_ZeroMemory(os, gcmSIZEOF(struct _gckOS));

    /* Initialize the gckOS object. */
    os->object.type = gcvOBJ_OS;

    /* Set device device. */
    os->device = Context;

    /* IMPORTANT! No heap yet. */
    os->heap = gcvNULL;

    /* Initialize the memory lock. */
    gcmkONERROR(gckOS_CreateMutex(os, &os->memoryLock));
    gcmkONERROR(gckOS_CreateMutex(os, &os->memoryMapLock));

    /* Create debug lock mutex. */
    gcmkONERROR(gckOS_CreateMutex(os, &os->debugLock));

    /* Create the gckHEAP object. */
    gcmkONERROR(gckHEAP_Construct(os, gcdHEAP_SIZE, &os->heap));

    /* Find the base address of the physical memory. */
    os->baseAddress = os->device->baseAddress;

    gcmkTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_OS,
                  "Physical base address set to 0x%08X.\n",
                  os->baseAddress);

    os->mempoolBaseAddress = (gctPOINTER) drv_mempool_get_baseAddress();
    os->mempoolBasePAddress = (gctPOINTER) drv_mempool_get_basePAddress();
    os->mempoolPageSize = drv_mempool_get_page_size();

    /* Return pointer to the gckOS object. */
    *Os = os;

    /* Success. */
    gcmkFOOTER_ARG("*Os=0x%X", *Os);
    return gcvSTATUS_OK;

OnError:
    if (os->heap != gcvNULL)
    {
        gcmkVERIFY_OK(
            gckHEAP_Destroy(os->heap));
    }

    if (os->memoryMapLock != gcvNULL)
    {
        gcmkVERIFY_OK(
            gckOS_DeleteMutex(os, os->memoryMapLock));
    }

    if (os->memoryLock != gcvNULL)
    {
        gcmkVERIFY_OK(
            gckOS_DeleteMutex(os, os->memoryLock));
    }

    if (os->debugLock != gcvNULL)
    {
        gcmkVERIFY_OK(
            gckOS_DeleteMutex(os, os->debugLock));
    }

    free(os);

    /* Return the error. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_Destroy
**
**  Destroy an gckOS object.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object that needs to be destroyed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_Destroy(
    IN gckOS Os
    )
{
    gckHEAP heap;

    gcmkHEADER_ARG("Os=0x%X", Os);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    if (Os->heap != gcvNULL)
    {
        /* Mark gckHEAP as gone. */
        heap     = Os->heap;
        Os->heap = gcvNULL;

        /* Destroy the gckHEAP object. */
        gcmkVERIFY_OK(gckHEAP_Destroy(heap));
    }

    /* Destroy the memory lock. */
    gcmkVERIFY_OK(gckOS_DeleteMutex(Os, Os->memoryMapLock));
    gcmkVERIFY_OK(gckOS_DeleteMutex(Os, Os->memoryLock));

    /* Destroy debug lock mutex. */
    gcmkVERIFY_OK(gckOS_DeleteMutex(Os, Os->debugLock));

    /* Mark the gckOS object as unknown. */
    Os->object.type = gcvOBJ_UNKNOWN;

    /* Free the gckOS object. */
    free(Os);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_Allocate
**
**  Allocate memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIZE_T Bytes
**          Number of bytes to allocate.
**
**  OUTPUT:
**
**      gctPOINTER * Memory
**          Pointer to a variable that will hold the allocated memory location.
*/
gceSTATUS
gckOS_Allocate(
    IN gckOS Os,
    IN gctSIZE_T Bytes,
    OUT gctPOINTER * Memory
    )
{
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%X Bytes=%lu", Os, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Bytes > 0);
    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);

    /* Do we have a heap? */
    if (Os->heap != gcvNULL)
    {
        /* Allocate from the heap. */
        gcmkONERROR(gckHEAP_Allocate(Os->heap, Bytes, Memory));
    }
    else
    {
        gcmkONERROR(gckOS_AllocateMemory(Os, Bytes, Memory));
    }

    /* Success. */
    gcmkFOOTER_ARG("*Memory=0x%X", *Memory);
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_Free
**
**  Free allocated memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Memory
**          Pointer to memory allocation to free.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_Free(
    IN gckOS Os,
    IN gctPOINTER Memory
    )
{
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%X Memory=0x%X", Os, Memory);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);

    /* Do we have a heap? */
    if (Os->heap != gcvNULL)
    {
        /* Free from the heap. */
        gcmkONERROR(gckHEAP_Free(Os->heap, Memory));
    }
    else
    {
        gcmkONERROR(gckOS_FreeMemory(Os, Memory));
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}
/*******************************************************************************
**
**  gckOS_AllocateMemory
**
**  Allocate memory wrapper.
**
**  INPUT:
**
**      gctSIZE_T Bytes
**          Number of bytes to allocate.
**
**  OUTPUT:
**
**      gctPOINTER * Memory
**          Pointer to a variable that will hold the allocated memory location.
*/
gceSTATUS
gckOS_AllocateMemory(
    IN gckOS Os,
    IN gctSIZE_T Bytes,
    OUT gctPOINTER * Memory
    )
{
    gctPOINTER memory;
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%X Bytes=%lu", Os, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Bytes > 0);
    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);

    memory = (gctPOINTER) calloc(1, Bytes);

    if (memory == gcvNULL)
    {
        /* Out of memory. */
        gcmkONERROR(gcvSTATUS_OUT_OF_MEMORY);
    }

    /* Return pointer to the memory allocation. */
    *Memory = memory;

    /* Success. */
    gcmkFOOTER_ARG("*Memory=0x%X", *Memory);
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_FreeMemory
**
**  Free allocated memory wrapper.
**
**  INPUT:
**
**      gctPOINTER Memory
**          Pointer to memory allocation to free.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_FreeMemory(
    IN gckOS Os,
    IN gctPOINTER Memory
    )
{
    gcmkHEADER_ARG("Memory=0x%X", Memory);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);

    /* Free the memory from the OS pool. */
    free(Memory);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_MapMemory
**
**  Map physical memory into the current process.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Start of physical address memory.
**
**      gctSIZE_T Bytes
**          Number of bytes to map.
**
**  OUTPUT:
**
**      gctPOINTER * Memory
**          Pointer to a variable that will hold the logical address of the
**          mapped memory.
*/
gceSTATUS
gckOS_MapMemory(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctSIZE_T Bytes,
    OUT gctPOINTER * Logical
    )
{
    gcmkHEADER_ARG("Os=0x%X Physical=0x%X Bytes=%lu", Os, Physical, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != 0);
    gcmkVERIFY_ARGUMENT(Bytes > 0);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "Enter gckOS_MapMemory\n");

    MEMORY_LOCK(Os);

    /* Map physical address. */
    *Logical = mmap64(0,
        Bytes,
        PROT_READ | PROT_WRITE | PROT_NOCACHE,
        MAP_PHYS | MAP_SHARED,
        NOFD,
        (off_t)Physical);

    MEMORY_UNLOCK(Os);

    if (*Logical == MAP_FAILED)
    {
        gcmkTRACE_ZONE(gcvLEVEL_ERROR,
            gcvZONE_OS,
            "gckOS_MapMemory: mmap error: %s\n",
            strerror(errno));

        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_MEMORY);
        return gcvSTATUS_OUT_OF_MEMORY;
    }

    gcmkTRACE_ZONE(gcvLEVEL_ERROR, gcvZONE_OS,
                "gckOS_MapMemory: User Mapped address for 0x%x is 0x%x\n",
                (gctUINT32)Physical,
                (gctUINT32)*Logical);

    gcmkFOOTER_ARG("*Logical=0x%X", *Logical);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_UnmapMemory
**
**  Unmap physical memory out of the current process.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Start of physical address memory.
**
**      gctSIZE_T Bytes
**          Number of bytes to unmap.
**
**      gctPOINTER Memory
**          Pointer to a previously mapped memory region.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UnmapMemory(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctSIZE_T Bytes,
    IN gctPOINTER Logical
    )
{
    gcmkHEADER_ARG("Os=0x%X Physical=0x%X Bytes=%lu Logical=0x%X",
                   Os, Physical, Bytes, Logical);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != 0);
    gcmkVERIFY_ARGUMENT(Bytes > 0);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in gckOS_UnmapMemory\n");

    if (Logical)
    {
        gctUINT32 res;
        gcmkTRACE_ZONE(gcvLEVEL_VERBOSE,
            gcvZONE_OS,
            "[gckOS_UnmapMemory] Logical: 0x%x\n",
            Logical
            );

        MEMORY_LOCK(Os);

        res = munmap(Logical, Bytes);

        MEMORY_UNLOCK(Os);

        if (res == -1)
        {
            gcmkTRACE_ZONE(gcvLEVEL_ERROR,
                gcvZONE_OS,
                "gckOS_UnmapMemory: munmap error: %s\n",
                strerror(errno));

            gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
            return gcvSTATUS_INVALID_ARGUMENT;
        }
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_UnmapUserLogical
**
**  Unmap user logical memory out of physical memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Start of physical address memory.
**
**      gctSIZE_T Bytes
**          Number of bytes to unmap.
**
**      gctPOINTER Memory
**          Pointer to a previously mapped memory region.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UnmapUserLogical(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctSIZE_T Bytes,
    IN gctPOINTER Logical
    )
{
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_AllocateNonPagedMemory
**
**  Allocate a number of pages from non-paged memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctBOOL InUserSpace
**          gcvTRUE if the pages need to be mapped into user space.
**
**      gctSIZE_T * Bytes
**          Pointer to a variable that holds the number of bytes to allocate.
**
**  OUTPUT:
**
**      gctSIZE_T * Bytes
**          Pointer to a variable that hold the number of bytes allocated.
**
**      gctPHYS_ADDR * Physical
**          Pointer to a variable that will hold the physical address of the
**          allocation.
**
**      gctPOINTER * Logical
**          Pointer to a variable that will hold the logical address of the
**          allocation.
*/
gceSTATUS
gckOS_AllocateNonPagedMemory(
    IN gckOS Os,
    IN gctBOOL InUserSpace,
    IN OUT gctSIZE_T * Bytes,
    OUT gctPHYS_ADDR * Physical,
    OUT gctPOINTER * Logical
    )
{
    gcmkHEADER_ARG("Os=0x%X InUserSpace=%d Bytes=%d Physical=0x%X Logical=0x%X Memory=0x%X", Os, InUserSpace, *Bytes, Physical, Logical);

    if (InUserSpace)
    {
        gctUINT32 pid;

        gcmkVERIFY_OK(gckOS_GetProcessID(&pid));

        /* TODO: Make a separate OS call for allocating from shared memory pool. */
        *Logical = drv_shmpool_alloc_contiguous((gctUINT32)pid, *Bytes, 0x1);
        if (*Logical == gcvNULL)
        {
            gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocateNonPagedMemory: Out of memory.");

            *Bytes = 0;
            gcmkFOOTER_NO();
            return gcvSTATUS_OUT_OF_RESOURCES;
        }

        /* Used to distinguish from memory allocated in kernel space. */
        *((gctUINT32*)Physical) = 0;
    }
    else
    {
        drv_mempool_alloc_contiguous(*Bytes, Physical, Logical);

        if (*Physical == gcvNULL || *Logical == gcvNULL)
        {
            gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocateNonPagedMemory: Out of memory.");

            *Bytes = 0;
            gcmkFOOTER_NO();
            return gcvSTATUS_OUT_OF_RESOURCES;
        }
    }

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocateNonPagedMemory: "
                "Bytes->0x%x, Logical->0x%x Physical->0x%x\n",
                (gctUINT32)*Bytes,
                *Logical,
                *Physical);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_FreeNonPagedMemory
**
**  Free previously allocated and mapped pages from non-paged memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIZE_T Bytes
**          Number of bytes allocated.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocated memory.
**
**      gctPOINTER Logical
**          Logical address of the allocated memory.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS gckOS_FreeNonPagedMemory(
    IN gckOS Os,
    IN gctSIZE_T Bytes,
    IN gctPHYS_ADDR Physical,
    IN gctPOINTER Logical
    )
{
    gcmkHEADER_ARG("Os=0x%X Bytes=%lu Physical=0x%X Logical=0x%X",
                   Os, Bytes, Physical, Logical);

    int rc;

    if (Physical)
    {
        rc = drv_mempool_free(Logical);
    }
    else
    {
        rc = drv_shmpool_free(Logical);
    }

    if (rc == -1)
    {
        gcmkTRACE_ZONE(gcvLEVEL_INFO,
                    gcvZONE_OS,
                    "gckOS_FreeNonPagedMemory: "
                    "Unmap Failed Logical->0x%x, Bytes->%d, Physical->0x%x\n",
                    (gctUINT32)Logical,
                    Bytes,
                    (gctUINT32)Physical);
        return gcvSTATUS_INVALID_ARGUMENT;
    }

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_FreeNonPagedMemory: "
                "Logical->0x%x Physical->0x%x\n",
                (gctUINT32)Logical,
                (gctUINT32)Physical);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_ReadRegister
**
**  Read data from a register.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctUINT32 Address
**          Address of register.
**
**  OUTPUT:
**
**      gctUINT32 * Data
**          Pointer to a variable that receives the data read from the register.
*/
gceSTATUS
gckOS_ReadRegister(
    IN gckOS Os,
    IN gctUINT32 Address,
    OUT gctUINT32 * Data
    )
{
    return gckOS_ReadRegisterEx(Os, gcvCORE_MAJOR, Address, Data);
}

gceSTATUS
gckOS_ReadRegisterEx(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctUINT32 Address,
    OUT gctUINT32 * Data
    )
{
    gcmkHEADER_ARG("Os=0x%X Core=%d Address=0x%X", Os, Core, Address);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Data != gcvNULL);

    *Data = (gctUINT32)in32((uintptr_t) ((gctUINT8 *)Os->device->registerBases[Core] + Address));

    /* Success. */
    gcmkFOOTER_ARG("*Data=0x%08x", *Data);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_WriteRegister
**
**  Write data to a register.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctUINT32 Address
**          Address of register.
**
**      gctUINT32 Data
**          Data for register.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_WriteRegister(
    IN gckOS Os,
    IN gctUINT32 Address,
    IN gctUINT32 Data
    )
{
    return gckOS_WriteRegisterEx(Os, gcvCORE_MAJOR, Address, Data);
}

gceSTATUS
gckOS_WriteRegisterEx(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctUINT32 Address,
    IN gctUINT32 Data
    )
{
    gcmkHEADER_ARG("Os=0x%X Core=%d Address=0x%X Data=0x%08x", Os, Core, Address, Data);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_WriteRegister: "
                "Writing to physical address [%x] = %x\n",
                (gctUINT8 *)Os->device->registerBases[Core],
                Data);

    out32((uintptr_t) ((gctUINT8 *)Os->device->registerBases[Core] + Address), (uint32_t)Data);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_GetPageSize
**
**  Get the system's page size.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**  OUTPUT:
**
**      gctSIZE_T * PageSize
**          Pointer to a variable that will receive the system's page size.
*/
gceSTATUS gckOS_GetPageSize(
    IN gckOS Os,
    OUT gctSIZE_T * PageSize
    )
{
    gcmkHEADER_ARG("Os=0x%X", Os);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(PageSize != gcvNULL);

    /* Return the page size. */
    *PageSize = (gctSIZE_T) __PAGESIZE;

    /* Success. */
    gcmkFOOTER_ARG("*PageSize=%u", *PageSize);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_GetLogicalAddressProcess
**
**  Get the physical system address of a corresponding virtual address for a
**  given process.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Logical
**          Logical address.
**
**      gctUINT ProcessID
**          Procedd ID.
**
**  OUTPUT:
**
**      gctUINT32 * Address
**          Poinetr to a variable that receives the 32-bit physical adress.
*/
gceSTATUS
gckOS_GetLogicalAddressProcess(
    IN gckOS Os,
    IN gctUINT ProcessID,
    IN gctUINT32 Address,
    OUT gctPOINTER *Logical
    )
{
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%X, ProcessID=%u, Address=%u", Os, ProcessID, Address);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);

    gcmkONERROR(drv_shmpool_mem_map(ProcessID, Address, Logical));

    gcmkFOOTER_ARG("*Logical=%x", *Logical);
    return gcvSTATUS_OK;

OnError:
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_GetPhysicalAddress
**
**  Get the physical system address of a corresponding virtual address.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Logical
**          Logical address.
**
**  OUTPUT:
**
**      gctUINT32 * Address
**          Pointer to a variable that receives the 32-bit physical adress.
*/
gceSTATUS
gckOS_GetPhysicalAddress(
    IN gckOS Os,
    IN gctPOINTER Logical,
    OUT gctUINT32 * Address
    )
{
    gctUINT32 res;
    off64_t address;

    gcmkHEADER_ARG("Os=0x%X Logical=0x%X", Os, Logical);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Address != gcvNULL);

    if ( drv_mempool_mem_offset(Logical, Address) != gcvSTATUS_OK)
    {
        gctUINT32 pid;

        gckOS_GetProcessID(&pid);

        if ( drv_shmpool_mem_offset(pid, Logical, Address) != gcvSTATUS_OK)
        {
            MEMORY_LOCK(Os);

            res = mem_offset64(Logical, NOFD, 1, &address, gcvNULL);

            if (res == -1)
            {
                MEMORY_UNLOCK(Os);

                gcmkTRACE_ZONE(gcvLEVEL_INFO,
                            gcvZONE_OS,
                            "gckOS_GetPhysicalAddress: "
                            "Unable to get physical address for 0x%x\n",
                            (gctUINT32)Logical);

                slogf(
                        _SLOG_SETCODE(1, 0),
                        _SLOG_CRITICAL,
                        "GALcore: %s: Unable to get paddr for 0x%x (errno=%d)",
                        __FUNCTION__, (gctUINT32)Logical, errno);

                *Address = 0;
                gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
                return gcvSTATUS_INVALID_ARGUMENT;
            }

            gcmkASSERT((address & 0xFFFFFFFF00000000ull) == 0);

            *Address = (gctUINT32)address;

            MEMORY_UNLOCK(Os);
        }
    }


    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                    gcvZONE_OS,
                    "gckOS_GetPhysicalAddress: Logical->0x%x Physical->0x%x\n",
                    (gctUINT32)Logical,
                    (gctUINT32)*Address);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_GetPhysicalAddressProcess
**
**  Get the physical system address of a corresponding virtual address for a
**  given process.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Logical
**          Logical address.
**
**      gctUINT ProcessID
**          Process ID.
**
**  OUTPUT:
**
**      gctUINT32 * Address
**          Poinetr to a variable that receives the 32-bit physical adress.
*/
gceSTATUS
gckOS_GetPhysicalAddressProcess(
    IN gckOS Os,
    IN gctPOINTER Logical,
    IN gctUINT ProcessID,
    OUT gctUINT32 * Address
    )
{
    return gckOS_GetPhysicalAddress(Os, Logical, Address);
}

/*******************************************************************************
**
**  gckOS_MapPhysical
**
**  Map a physical address into kernel space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctUINT32 Physical
**          Physical address of the memory to map.
**
**      gctSIZE_T Bytes
**          Number of bytes to map.
**
**  OUTPUT:
**
**      gctPOINTER * Logical
**          Pointer to a variable that receives the base address of the mapped
**          memory.
*/
gceSTATUS
gckOS_MapPhysical(
    IN gckOS Os,
    IN gctUINT32 Physical,
    IN gctSIZE_T Bytes,
    OUT gctPOINTER * Logical
    )
{
    gctUINT32 physical = Physical;

    gcmkHEADER_ARG("Os=0x%X Physical=0x%X Bytes=%lu", Os, Physical, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Bytes > 0);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);

    MEMORY_LOCK(Os);

    /* Map physical address. */
    *Logical = mmap64(0,
        Bytes,
        PROT_READ | PROT_WRITE | PROT_NOCACHE,
        MAP_PHYS | MAP_SHARED | MAP_NOINIT,
        NOFD,
        (off_t)physical);

    MEMORY_UNLOCK(Os);

    if (*Logical == MAP_FAILED)
    {
        gcmkTRACE_ZONE(gcvLEVEL_ERROR,
            gcvZONE_OS,
            "gckOS_MapMemory: mmap error: %s\n",
            strerror(errno));

        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_MEMORY);
        return gcvSTATUS_OUT_OF_MEMORY;
    }

    gcmkTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_OS,
                  "gckOS_MapPhysical: "
                  "Physical->0x%X Bytes->0x%X Logical->0x%X\n",
                  (gctUINT32) Physical,
                  (gctUINT32) Bytes,
                  (gctUINT32) *Logical);

    /* Success. */
    gcmkFOOTER_ARG("*Logical=0x%X", *Logical);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_UnmapPhysical
**
**  Unmap a previously mapped memory region from kernel memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Logical
**          Pointer to the base address of the memory to unmap.
**
**      gctSIZE_T Bytes
**          Number of bytes to unmap.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UnmapPhysical(
    IN gckOS Os,
    IN gctPOINTER Logical,
    IN gctSIZE_T Bytes
    )
{
    gctUINT32 res;

    gcmkHEADER_ARG("Os=0x%X Logical=0x%X Bytes=%lu", Os, Logical, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);
    gcmkVERIFY_ARGUMENT(Bytes > 0);

    MEMORY_LOCK(Os);

    res = munmap(Logical, Bytes);

    MEMORY_UNLOCK(Os);

    if (res == -1)
    {
        gcmkTRACE_ZONE(gcvLEVEL_ERROR,
            gcvZONE_OS,
            "gckOS_UnmapMemory: munmap error: %s\n",
            strerror(errno));

        gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
        return gcvSTATUS_INVALID_ARGUMENT;
    }

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                    gcvZONE_OS,
                    "gckOS_UnmapPhysical: "
                    "Logical->0x%x Bytes->0x%x\n",
                    (gctUINT32)Logical,
                    (gctUINT32)Bytes);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_CreateMutex
**
**  Create a new mutex.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**  OUTPUT:
**
**      gctPOINTER * Mutex
**          Pointer to a variable that will hold a pointer to the mutex.
*/
gceSTATUS
gckOS_CreateMutex(
    IN gckOS Os,
    OUT gctPOINTER * Mutex
    )
{
    pthread_mutexattr_t mattr;
    int rc;

    gcmkHEADER_ARG("Os=0x%X", Os);

    /* Validate the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Mutex != gcvNULL);

    /* Allocate a FAST_MUTEX structure. */
    *Mutex = (gctPOINTER) malloc(sizeof(pthread_mutex_t));
    if (*Mutex == gcvNULL)
    {
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_MEMORY);
        return gcvSTATUS_OUT_OF_MEMORY;
    }

    /* Initialize the mutex. */
    rc = pthread_mutexattr_init(&mattr);
    if (rc != EOK)
    {
        free(*Mutex);
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_RESOURCES);
        return gcvSTATUS_OUT_OF_RESOURCES;
    }

    rc = pthread_mutexattr_settype(&mattr, PTHREAD_MUTEX_RECURSIVE);
    if (rc != EOK)
    {
        pthread_mutexattr_destroy(&mattr);
        free(*Mutex);
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_RESOURCES);
        return gcvSTATUS_OUT_OF_RESOURCES;
    }

    rc = pthread_mutex_init((pthread_mutex_t *)(*Mutex), &mattr);
    if (rc != EOK)
    {
        pthread_mutexattr_destroy(&mattr);
        free(*Mutex);
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_OUT_OF_RESOURCES);
        return gcvSTATUS_OUT_OF_RESOURCES;
    }

    /* We do not need the attribute any more. */
    pthread_mutexattr_destroy(&mattr);

    /* Return status. */
    gcmkFOOTER_ARG("*Mutex=0x%X", *Mutex);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_DeleteMutex
**
**  Delete a mutex.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Mutex
**          Pointer to the mute to be deleted.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_DeleteMutex(
    IN gckOS Os,
    IN gctPOINTER Mutex
    )
{
    gctUINT32 res;

    gcmkHEADER_ARG("Os=0x%X Mutex=0x%X", Os, Mutex);

    /* Validate the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Mutex != gcvNULL);

    res = pthread_mutex_destroy((pthread_mutex_t *)(Mutex));

    if (res != EOK)
    {
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
        return gcvSTATUS_INVALID_ARGUMENT;
    }

    /* Delete the fast mutex. */
    free(Mutex);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_AcquireMutex
**
**  Acquire a mutex.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Mutex
**          Pointer to the mutex to be acquired.
**
**      gctUINT32 Timeout
**          Timeout value specified in milliseconds.
**          Specify the value of gcvINFINITE to keep the thread suspended
**          until the mutex has been acquired.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AcquireMutex(
    IN gckOS Os,
    IN gctPOINTER Mutex,
    IN gctUINT32 Timeout
    )
{
    gcmkHEADER_ARG("Os=0x%X Mutex=0x%0x Timeout=%u", Os, Mutex, Timeout);

    /* Validate the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Mutex != gcvNULL);

    if (Timeout == gcvINFINITE)
    {
        if (pthread_mutex_lock((pthread_mutex_t *) Mutex) != EOK)
        {
            gcmkFOOTER_NO();
            return gcvSTATUS_TIMEOUT;
        }

        /* Success. */
        gcmkFOOTER_NO();
        return gcvSTATUS_OK;
    }

    /* Advance the timeout. */
    Timeout += 1;

    for (;;)
    {
        /* Try to acquire the fast mutex. */
        if (!pthread_mutex_trylock((pthread_mutex_t *) Mutex))
        {
            /* Success. */
            gcmkFOOTER_NO();
            return gcvSTATUS_OK;
        }

        if (Timeout-- == 0)
        {
            break;
        }

        /* Wait for 1 millisecond. */
        gcmkVERIFY_OK(gckOS_Delay(Os, 1));
    }

    /* Timeout. */
    gcmkFOOTER_ARG("status=%d", gcvSTATUS_TIMEOUT);
    return gcvSTATUS_TIMEOUT;
}

/*******************************************************************************
**
**  gckOS_ReleaseMutex
**
**  Release an acquired mutex.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Mutex
**          Pointer to the mutex to be released.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_ReleaseMutex(
    IN gckOS Os,
    IN gctPOINTER Mutex
    )
{
    gcmkHEADER_ARG("Os=%p Mutex=%p", Os, Mutex);

    /* Validate the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Mutex != gcvNULL);

    /* Release the fast mutex. */
    pthread_mutex_unlock((pthread_mutex_t *) Mutex);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_AtomicExchange
**
**  Atomically exchange a pair of 32-bit values.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      IN OUT gctINT32_PTR Target
**          Pointer to the 32-bit value to exchange.
**
**      IN gctINT32 NewValue
**          Specifies a new value for the 32-bit value pointed to by Target.
**
**      OUT gctINT32_PTR OldValue
**          The old value of the 32-bit value pointed to by Target.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AtomicExchange(
    IN gckOS Os,
    IN OUT gctUINT32_PTR Target,
    IN gctUINT32 NewValue,
    OUT gctUINT32_PTR OldValue
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=0x%X Target=0x%X NewValue=%u", Os, Target, NewValue);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    atom = (gcskATOM_PTR)Target;

    if (pthread_mutex_lock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Exchange the pair of 32-bit values. */
    *OldValue = atom->counter;
    atom->counter = NewValue;

    if (pthread_mutex_unlock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Success. */
    gcmkFOOTER_ARG("*OldValue=%u", *OldValue);
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_AtomicExchangePtr
**
**  Atomically exchange a pair of pointers.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      IN OUT gctPOINTER * Target
**          Pointer to the 32-bit value to exchange.
**
**      IN gctPOINTER NewValue
**          Specifies a new value for the pointer pointed to by Target.
**
**      OUT gctPOINTER * OldValue
**          The old value of the pointer pointed to by Target.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AtomicExchangePtr(
    IN gckOS Os,
    IN OUT gctPOINTER * Target,
    IN gctPOINTER NewValue,
    OUT gctPOINTER * OldValue
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=0x%X Target=0x%X NewValue=0x%X", Os, Target, NewValue);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    atom = (gcskATOM_PTR)Target;

    if (pthread_mutex_lock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Exchange the pair of pointers. */
    *OldValue = (gctPOINTER)atom->counter;
    atom->counter = (gctINT32)NewValue;

    if (pthread_mutex_unlock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Success. */
    gcmkFOOTER_ARG("*OldValue=0x%X", *OldValue);
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

#if gcdSMP

#error Do not use them for now!

/*******************************************************************************
**
**  gckOS_AtomicSetMask
**
**  Atomically set mask to Atom
**
**  INPUT:
**      IN OUT gctPOINTER Atom
**          Pointer to the atom to set.
**
**      IN gctUINT32 Mask
**          Mask to set.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AtomSetMask(
    IN gctPOINTER Atom,
    IN gctUINT32 Mask
    )
{
    gcmkHEADER_ARG("Atom=0x%X Mask=0x%0x", Atom, Mask);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    atomic_set(Atom, Mask);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_AtomClearMask
**
**  Atomically clear mask from Atom
**
**  INPUT:
**      IN OUT gctPOINTER Atom
**          Pointer to the atom to clear.
**
**      IN gctUINT32 Mask
**          Mask to clear.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AtomClearMask(
    IN gctPOINTER Atom,
    IN gctUINT32 Mask
    )
{
    gcmkHEADER_ARG("Atom=0x%X Mask=0x%0x", Atom, Mask);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    atomic_clr((volatile gctUINT32_PTR)Atom, Mask);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}
#endif

/*******************************************************************************
**
**  gckOS_AtomConstruct
**
**  Create an atom.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**  OUTPUT:
**
**      gctPOINTER * Atom
**          Pointer to a variable receiving the constructed atom.
*/
gceSTATUS
gckOS_AtomConstruct(
    IN gckOS Os,
    OUT gctPOINTER* Atom
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom = gcvNULL;

    gcmkHEADER_ARG("Os=0x%X", Os);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    /* Allocate memory for the atom. */
    gcmkONERROR(gckOS_Allocate(Os,
                               gcmSIZEOF(*atom),
                               (gctPOINTER *) &atom));

    gcmkONERROR(gckOS_ZeroMemory(atom, gcmSIZEOF(*atom)));

    /* Create the mutex. */
    if (pthread_mutex_init(&atom->mutex, gcvNULL) != EOK)
    {
        gcmkONERROR(gcvSTATUS_OUT_OF_RESOURCES);
    }

    /* Initialize the atom. */
    atom->counter = 0;

    /* Return pointer to atom. */
    *Atom = atom;

    /* Success. */
    gcmkFOOTER_ARG("*Atom=0x%0x Value=0x%0x", *Atom, atom->counter);
    return gcvSTATUS_OK;

OnError:
    if (atom != gcvNULL)
    {
        gcmkOS_SAFE_FREE(Os, atom);
    }

    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_AtomDestroy
**
**  Destroy an atom.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**      gctPOINTER Atom
**          Pointer to the atom to destroy.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AtomDestroy(
    IN gckOS Os,
    IN gctPOINTER Atom
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=0x%X Atom=0x%0x", Os, Atom);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    atom = (gcskATOM_PTR)Atom;

    pthread_mutex_destroy(&atom->mutex);

    /* Free the atom. */
    gcmkONERROR(gcmkOS_SAFE_FREE(Os, Atom));

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_AtomGet
**
**  Get the 32-bit value protected by an atom.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**      gctPOINTER Atom
**          Pointer to the atom.
**
**  OUTPUT:
**
**      gctINT32_PTR Value
**          Pointer to a variable the receives the value of the atom.
*/
gceSTATUS
gckOS_AtomGet(
    IN gckOS Os,
    IN gctPOINTER Atom,
    OUT gctINT32_PTR Value
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=0x%X Atom=0x%0x Value=0x%0x", Os, Atom, Value);

    atom = (gcskATOM_PTR)Atom;

    if (pthread_mutex_lock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    *Value = atom->counter;

    if (pthread_mutex_unlock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    gcmkFOOTER_ARG("Value=0x%0x", gcmOPT_VALUE(Value));
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_AtomSet
**
**  Set the 32-bit value protected by an atom.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**      gctPOINTER Atom
**          Pointer to the atom.
**
**      gctINT32 Value
**          The value of the atom.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AtomSet(
    IN gckOS Os,
    IN gctPOINTER Atom,
    IN gctINT32 Value
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=0x%X Atom=0x%0x Value=%d", Os, Atom);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    atom = (gcskATOM_PTR)Atom;

    if (pthread_mutex_lock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    atom->counter = Value;

    if (pthread_mutex_unlock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Success. */
    gcmkFOOTER_ARG("Value=0x%0x", Value);
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_AtomIncrement
**
**  Atomically increment the 32-bit integer value inside an atom.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**      gctPOINTER Atom
**          Pointer to the atom.
**
**  OUTPUT:
**
**      gctINT32_PTR Value
**          Pointer to a variable that receives the original value of the atom.
*/
gceSTATUS
gckOS_AtomIncrement(
    IN gckOS Os,
    IN gctPOINTER Atom,
    OUT gctINT32_PTR OldValue
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=%p Atom=%p", Os, Atom);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    atom = (gcskATOM_PTR)Atom;

    if (pthread_mutex_lock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    if (OldValue != gcvNULL)
    {
        /* Return the original value to the caller. */
        *OldValue = atom->counter;
    }

    /* Increment the atom's counter. */
    atom->counter++;

    if (pthread_mutex_unlock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Success. */
    gcmkFOOTER_ARG("*OldValue=%d", gcmOPT_VALUE(OldValue));
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/* Decrement an atom. */
gceSTATUS
gckOS_AtomDecrement(
    gckOS Os,
    gctPOINTER Atom,
    gctINT32_PTR OldValue
    )
{
    gceSTATUS status;
    gcskATOM_PTR atom;

    gcmkHEADER_ARG("Os=%p Atom=%p", Os, Atom);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Atom != gcvNULL);

    atom = (gcskATOM_PTR)Atom;

    if (pthread_mutex_lock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    if (OldValue != gcvNULL)
    {
        /* Return the original value to the caller. */
        *OldValue = atom->counter;
    }

    /* Decrement the atom's counter. */
    atom->counter--;

    if (pthread_mutex_unlock(&atom->mutex) != EOK)
    {
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Success. */
    gcmkFOOTER_ARG("*OldValue=%d", gcmOPT_VALUE(OldValue));
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_Delay
**
**  Delay execution of the current thread for a number of milliseconds.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctUINT32 Delay
**          Delay to sleep, specified in milliseconds.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_Delay(
    IN gckOS Os,
    IN gctUINT32 Delay
    )
{
    /* Schedule delay. */
    delay(Delay);

    /* Success. */
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_GetTicks
**
**  Get the number of milliseconds since the system started.
**
**  INPUT:
**
**  OUTPUT:
**
**      gctUINT32_PTR Time
**          Pointer to a variable to get time.
**
*/
gceSTATUS
gckOS_GetTicks(
    OUT gctUINT32_PTR Time
    )
{
    struct timeval tv;
    gcmkHEADER();

    /* Return the time of day in milliseconds. */
    gettimeofday(&tv, 0);
    *Time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);

    gcmkFOOTER_NO();

    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_TicksAfter
**
**  Compare time values got from gckOS_GetTicks.
**
**  INPUT:
**      gctUINT32 Time1
**          First time value to be compared.
**
**      gctUINT32 Time2
**          Second time value to be compared.
**
**  OUTPUT:
**
**      gctBOOL_PTR IsAfter
**          Pointer to a variable to result.
**
*/
gceSTATUS
gckOS_TicksAfter(
    IN gctUINT32 Time1,
    IN gctUINT32 Time2,
    OUT gctBOOL_PTR IsAfter
    )
{
    gcmkHEADER();

    *IsAfter = (Time2 < Time1);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_GetTime
**
**  Get the number of microseconds since the system started.
**
**  INPUT:
**
**  OUTPUT:
**
**      gctUINT64_PTR Time
**          Pointer to a variable to get time.
**
*/
gceSTATUS
gckOS_GetTime(
    OUT gctUINT64_PTR Time
    )
{
    struct timespec tv;

    gcmkHEADER();

    clock_gettime(CLOCK_MONOTONIC, &tv);

    *Time  = tv.tv_sec;
    *Time *= 1000000;
    *Time += (tv.tv_nsec / 1000);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_CreateTimer
**
**  Create a software timer.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctTIMERFUNCTION Function.
**          Pointer to a call back function which will be called when timer is
**          expired.
**
**      gctPOINTER Data.
**          Private data which will be passed to call back function.
**
**  OUTPUT:
**
**      gctPOINTER * Timer
**          Pointer to a variable receiving the created timer.
*/
gceSTATUS
gckOS_CreateTimer(
    IN gckOS Os,
    IN gctTIMERFUNCTION Function,
    IN gctPOINTER Data,
    OUT gctPOINTER * Timer
    )
{
    gceSTATUS status;
    gcsOSTIMER_PTR pointer;
    gctINT ret;

    gcmkHEADER_ARG("Os=0x%X Function=0x%X Data=0x%X", Os, Function, Data);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Timer != gcvNULL);

    /* Allocate the structure. */
    gcmkONERROR(gckOS_Allocate(Os, sizeof(gcsOSTIMER), (gctPOINTER)&pointer));

    pointer->quit    = gcvFALSE;
    pointer->dueTime = -1;
    pointer->func    = Function;
    pointer->data    = Data;
    pointer->os      = Os;

    /* Create the mutex. */
    status = gckOS_CreateMutex(Os, &pointer->mutex);
    if (gcmIS_ERROR(status))
    {
        gckOS_Free(Os, (gctPOINTER)pointer);
        goto OnError;
    }

    /* Create the semaphore. */
    status = gckOS_CreateSemaphore(Os, &pointer->sema);
    if (gcmIS_ERROR(status))
    {
        gckOS_DeleteMutex(Os, pointer->mutex);
        gckOS_Free(Os, (gctPOINTER)pointer);
        goto OnError;
    }

    gckOS_AcquireSemaphore(Os, pointer->sema);

    /* Start the timer thread. */
    ret = pthread_create(&pointer->tid, gcvNULL, _KernelTimerThread, pointer);
    if (EOK != ret)
    {
        gckOS_DestroySemaphore(Os, pointer->sema);
        gckOS_DeleteMutex(Os, pointer->mutex);
        gckOS_Free(Os, (gctPOINTER)pointer);
        gcmkONERROR(gcvSTATUS_OUT_OF_RESOURCES);
    }

    pthread_setname_np(pointer->tid, "Timer Thread");

    *Timer = (gctPOINTER)pointer;

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_DestroyTimer
**
**  Destory a software timer.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Timer
**          Pointer to the timer to be destoryed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_DestroyTimer(
    IN gckOS Os,
    IN gctPOINTER Timer
    )
{
    gcsOSTIMER_PTR timer;

    gcmkHEADER_ARG("Os=0x%X Timer=0x%X", Os, Timer);

    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Timer != gcvNULL);

    timer = (gcsOSTIMER_PTR)Timer;

    timer->quit = gcvTRUE;

    gckOS_ReleaseSemaphore(Os, timer->sema);

    pthread_join(timer->tid, gcvNULL);

    gckOS_DeleteMutex(Os, timer->mutex);
    gckOS_Free(Os, (gctPOINTER)timer);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_StartTimer
**
**  Schedule a software timer.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Timer
**          Pointer to the timer to be scheduled.
**
**      gctUINT32 Delay
**          Delay in milliseconds.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_StartTimer(
    IN gckOS Os,
    IN gctPOINTER Timer,
    IN gctUINT32 Delay
    )
{
    gcsOSTIMER_PTR timer;
    gctUINT64 current;

    gcmkHEADER_ARG("Os=0x%X Timer=0x%X Delay=%u", Os, Timer, Delay);

    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Timer != gcvNULL);
    gcmkVERIFY_ARGUMENT(Delay != 0);

    timer = (gcsOSTIMER_PTR)Timer;

    gckOS_GetTime(&current);

    gckOS_AcquireMutex(Os, timer->mutex, gcvINFINITE);

    timer->dueTime = current + (Delay * 1000);

    gckOS_ReleaseMutex(Os, timer->mutex);

    gckOS_ReleaseSemaphore(Os, timer->sema);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_StopTimer
**
**  Cancel a unscheduled timer.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Timer
**          Pointer to the timer to be cancel.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_StopTimer(
    IN gckOS Os,
    IN gctPOINTER Timer
    )
{
    gcsOSTIMER_PTR timer;

    gcmkHEADER_ARG("Os=0x%X Timer=0x%X", Os, Timer);

    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Timer != gcvNULL);

    timer = (gcsOSTIMER_PTR)Timer;

    gckOS_AcquireMutex(Os, timer->mutex, gcvINFINITE);

    timer->dueTime = -1;

    gckOS_ReleaseMutex(Os, timer->mutex);

    gckOS_ReleaseSemaphore(Os, timer->sema);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_MemoryBarrier
**
**  Make sure the CPU has executed everything up to this point and the data got
**  written to the specified pointer.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Address
**          Address of memory that needs to be barriered.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_MemoryBarrier(
    IN gckOS Os,
    IN gctPOINTER Address
    )
{
    gcmkHEADER_ARG("Os=0x%X Address=0x%X", Os, Address);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    __asm__ __volatile__ ("dsb");

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_AllocatePagedMemory
**
**  Allocate memory from the paged pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIZE_T Bytes
**          Number of bytes to allocate.
**
**  OUTPUT:
**
**      gctPHYS_ADDR * Physical
**          Pointer to a variable that receives the physical address of the
**          memory allocation.
*/
gceSTATUS
gckOS_AllocatePagedMemory(
    IN gckOS Os,
    IN gctSIZE_T Bytes,
    OUT gctPHYS_ADDR * Physical
    )
{
    return gckOS_AllocatePagedMemoryEx(Os, gcvFALSE, Bytes, Physical);
}

/*******************************************************************************
**
**  gckOS_AllocatePagedMemoryEx
**
**  Allocate memory from the paged pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctBOOL Contiguous
**          Need contiguous memory or not.
**
**      gctSIZE_T Bytes
**          Number of bytes to allocate.
**
**  OUTPUT:
**
**      gctPHYS_ADDR * Physical
**          Pointer to a variable that receives the physical address of the
**          memory allocation.
*/
gceSTATUS
gckOS_AllocatePagedMemoryEx(
    IN gckOS Os,
    IN gctBOOL Contiguous,
    IN gctSIZE_T Bytes,
    OUT gctPHYS_ADDR * Physical
    )
{
    int rc, fd, shm_ctl_flags = SHMCTL_ANON | SHMCTL_LAZYWRITE;
    gceSTATUS status;
    gctBOOL acquired = gcvFALSE;

    gcmkHEADER_ARG("Os=0x%X Contiguous=%d Bytes=%lu", Os, Contiguous, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Bytes > 0);
    gcmkVERIFY_ARGUMENT(Physical != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in gckOS_AllocatePagedMemory\n");

    if (Contiguous)
    {
        shm_ctl_flags |= SHMCTL_PHYS;
    }

    /* Lock down, to avoid opening same shm file twice. */
    MEMORY_LOCK(Os);
    acquired = gcvTRUE;

    fd = drv_create_shm_object();
    if (fd == -1) {
        printf("shm_open failed. error %s\n", strerror( errno ) );
        gcmkONERROR(gcvSTATUS_GENERIC_IO);
    }

    /* Special flags for this shm, to make it write buffered. */
    /* Virtual memory doesn't need to be physically contiguous. */
    /* Allocations would be page aligned. */
    rc = shm_ctl_special(fd,
                         shm_ctl_flags,
                         0,
                         Bytes,
                         ARM_PTE_RW | ARM_PTE_B);
    if (rc == -1) {
        printf("shm_ctl_special failed. error %s\n", strerror( errno ) );
        close(fd);
        gcmkONERROR(gcvSTATUS_OUT_OF_MEMORY);
    }

    /* Use the fd as the handle for the physical memory just allocated. */
    *Physical = (gctPHYS_ADDR) fd;
    MEMORY_UNLOCK(Os);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocatePagedMemory: "
                "Bytes->0x%x, Physical->0x%x\n",
                (gctUINT32)Bytes,
                (gctUINT32)*Physical);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    if (acquired)
    {
        MEMORY_UNLOCK(Os);
    }

    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_FreePagedMemory
**
**  Free memory allocated from the paged pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocation.
**
**      gctSIZE_T Bytes
**          Number of bytes of the allocation.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_FreePagedMemory(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctSIZE_T Bytes
    )
{
    int rc;

    gcmkHEADER_ARG("Os=0x%X Physical=0x%X Bytes=%lu", Os, Physical, Bytes);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != gcvNULL);
    gcmkVERIFY_ARGUMENT(Bytes > 0);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in gckOS_FreePagedMemory\n");

    rc = close((gctINT)Physical);
    if ( rc == -1 )
    {
        printf("gckOS_FreePagedMemory failed. error: %s\n", strerror( errno ) );
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_GENERIC_IO);
        return gcvSTATUS_GENERIC_IO;
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_LockPages
**
**  Lock memory allocated from the paged pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocation.
**
**      gctSIZE_T Bytes
**          Number of bytes of the allocation.
**
**      gctBOOL Cacheable
**          Cache mode of mapping.
**
**  OUTPUT:
**
**      gctPOINTER * Logical
**          Pointer to a variable that receives the address of the mapped
**          memory.
**
**      gctSIZE_T * PageCount
**          Pointer to a variable that receives the number of pages required for
**          the page table according to the GPU page size.
*/
gceSTATUS
gckOS_LockPages(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctSIZE_T Bytes,
    IN gctBOOL Cacheable,
    OUT gctPOINTER * Logical,
    OUT gctSIZE_T * PageCount
    )
{
    void* addr;
    gctUINT32 pid = 0;
    gctUINT32 prot = PROT_READ | PROT_WRITE;

    gcmkHEADER_ARG("Os=0x%X Physical=0x%X Bytes=%lu", Os, Physical, Logical);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != gcvNULL);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);
    gcmkVERIFY_ARGUMENT(PageCount != gcvNULL);
    gcmkVERIFY_ARGUMENT(Bytes > 0);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in gckOS_LockPages\n");

    if (!Cacheable)
    {
        prot |= PROT_NOCACHE;
    }

    gcmkVERIFY_OK(gckOS_GetProcessID(&pid));

    /* Map this memory inside user and galcore. */
    addr = mmap64_join(pid,
                       0,
                       Bytes,
                       prot,
                       MAP_SHARED,
                       (int)Physical,
                       0);

    if (addr == MAP_FAILED)
    {
        printf("gckOS_LockPages: couldn't map memory of size %d, pid: %d [errno %s]",
                (gctUINT32)Bytes, pid, strerror( errno ) );
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_GENERIC_IO);
        return gcvSTATUS_GENERIC_IO;
    }

    /* TODO: MLOCK may or may not be needed!. */
    mlock((void*)addr, Bytes);

    *Logical = (gctPOINTER)addr;
    *PageCount = (gcmALIGN(Bytes, __PAGESIZE)) / __PAGESIZE;

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_LockPages: "
                "gctPHYS_ADDR->0x%x Bytes->0x%x Logical->0x%x pid->%d\n",
                (gctUINT32)Physical,
                (gctUINT32)Bytes,
                (gctUINT32)*Logical,
                pid);

    /* Success. */
    gcmkFOOTER_ARG("*Logical=0x%X *PageCount=%lu", *Logical, *PageCount);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_MapPages
**
**  Map paged memory into a page table.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocation.
**
**      gctSIZE_T PageCount
**          Number of pages required for the physical address.
**
**      gctPOINTER PageTable
**          Pointer to the page table to fill in.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_MapPages(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T PageCount,
    IN gctPOINTER PageTable
    )
{
    return gckOS_MapPagesEx(Os,
                            gcvCORE_MAJOR,
                            Physical,
                            Logical,
                            PageCount,
                            PageTable);
}

gceSTATUS
gckOS_MapPagesEx(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctPHYS_ADDR Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T PageCount,
    IN gctPOINTER PageTable
    )
{
    gctUINT32* table;
    gctPOINTER addr;
    size_t contigLen = 0;
    off64_t offset;
    gctUINT32 bytes;
    int rc;

    gcmkHEADER_ARG("Os=0x%X Core=%d Physical=0x%X PageCount=%u PageTable=0x%X",
                   Os, Core, Physical, PageCount, PageTable);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != gcvNULL);
    gcmkVERIFY_ARGUMENT(PageCount > 0);
    gcmkVERIFY_ARGUMENT(PageTable != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in %s\n", __FUNCTION__);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "%s: "
                "Physical->0x%x PageCount->0x%x Logical->0x%x\n",
                __FUNCTION__,
                (gctUINT32)Physical,
                (gctUINT32)PageCount,
                (gctUINT32)Logical);

    addr = Logical;
    table = (gctUINT32 *)PageTable;
    bytes = PageCount * __PAGESIZE;

    /* Try to get the user pages so DMA can happen. */
    while (PageCount > 0)
    {
        /* fd should be NOFD here, to get physical address. */
        rc = mem_offset64( addr, NOFD, bytes, &offset, &contigLen);
        if (rc == -1) {
            printf("%s: mem_offset64 failed: %s\n", __FUNCTION__, strerror( errno ) );
            printf("address: %x, bytes: %d\n", (gctUINT32)addr, bytes);
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_GENERIC_IO);
            return gcvSTATUS_GENERIC_IO;
        }

        gcmkASSERT(contigLen > 0);

        while(contigLen > 0)
        {
            *table++ = (gctUINT32) offset;
            offset += 4096;
            addr += 4096;
            contigLen = contigLen > 4096 ? contigLen - 4096 : 0;
            bytes -= 4096;
            PageCount--;
        }
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_MapPagesPeer
**
**  Map paged memory from a peer into a page table.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctUINT32 Pid
**          Process id of the peer.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocation.
**
**      gctSIZE_T PageCount
**          Number of pages required for the physical address.
**
**      gctPOINTER PageTable
**          Pointer to the page table to fill in.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_MapPagesPeer(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctUINT32 Pid,
    IN gctPHYS_ADDR Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T PageCount,
    IN gctPOINTER PageTable
    )
{
    gctUINT32* table;
    gctUINT32 addr;
    size_t contigLen = 0;
    off64_t offset;
    gctINT32 bytes;
    int rc;

    gcmkHEADER_ARG("Os=0x%X Core=%d Physical=0x%X Logical=0x%X PageCount=%u PageTable=0x%X",
                   Os, Core, Physical, Logical, PageCount, PageTable);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != gcvNULL);
    gcmkVERIFY_ARGUMENT(PageCount > 0);
    gcmkVERIFY_ARGUMENT(PageTable != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in gckOS_MapPagesPeer\n");

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_MapPagesPeer: "
                "Physical->0x%x PageCount->0x%x Logical->0x%x\n",
                (gctUINT32)Physical,
                (gctUINT32)PageCount,
                (gctUINT32)Logical);

    addr = (gctUINT32)Logical;
    table = (gctUINT32 *)PageTable;
    bytes = PageCount * __PAGESIZE;

    /* Try to get the user pages so DMA can happen. */
    while (PageCount > 0)
    {
        /* fd should be NOFD here, to get physical address. */
        rc = mem_offset64_peer( Pid, (uintptr_t)addr, bytes, &offset, &contigLen);
        if (rc == -1) {
            printf("gckOS_MapPagesPeer: mem_offset failed: %s\n", strerror( errno ) );
            printf("address: %x, bytes: %d\n", (gctUINT32)addr, bytes);
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_GENERIC_IO);
            return gcvSTATUS_GENERIC_IO;
        }

        gcmkASSERT(contigLen > 0);

        while(contigLen > 0)
        {
            {
                gckMMU_SetPage(Os->device->kernels[Core]->mmu,
                               (gctUINT32)offset, table++);
            }
            offset += 4096;
            addr += 4096;
            contigLen = contigLen > 4096 ? contigLen - 4096 : 0;
            bytes -= 4096;
            PageCount--;
        }
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gckOS_UnlockPages
**
**  Unlock memory allocated from the paged pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocation.
**
**      gctSIZE_T Bytes
**          Number of bytes of the allocation.
**
**      gctPOINTER Logical
**          Address of the mapped memory.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UnlockPages(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctSIZE_T Bytes,
    IN gctPOINTER Logical
    )
{
    int rc_peer, rc_self;
    gctUINT32 pid;

    gcmkHEADER_ARG("Os=0x%X Physical=0x%X Bytes=%u Logical=0x%X",
                   Os, Physical, Bytes, Logical);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Physical != gcvNULL);
    gcmkVERIFY_ARGUMENT(Logical != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "in gckOS_UnlockPages\n");

    gcmkVERIFY_OK(gckOS_GetProcessID(&pid));

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_UnlockPages: "
                "Physical->0x%x Bytes->0x%x Logical->0x%x Pid->0x%x\n",
                (gctUINT32)Physical,
                (gctUINT32)Bytes,
                (gctUINT32)Logical,
                (gctUINT32)pid);

    rc_self = munmap((void*)Logical, Bytes);

    rc_peer = munmap_peer(pid, (void*)Logical, Bytes);

    if (rc_peer == -1 || rc_self == -1)
    {
        gcmkTRACE(gcvLEVEL_ERROR, "%s(%d): rc_self=%d, rc_peer=%d.",
                __FUNCTION__, __LINE__, rc_self, rc_peer);
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gckOS_AllocateContiguous
**
**  Allocate memory from the contiguous pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctBOOL InUserSpace
**          gcvTRUE if the pages need to be mapped into user space.
**
**      gctSIZE_T * Bytes
**          Pointer to the number of bytes to allocate.
**
**  OUTPUT:
**
**      gctSIZE_T * Bytes
**          Pointer to a variable that receives the number of bytes allocated.
**
**      gctPHYS_ADDR * Physical
**          Pointer to a variable that receives the physical address of the
**          memory allocation.
**
**      gctPOINTER * Logical
**          Pointer to a variable that receives the logical address of the
**          memory allocation.
*/
gceSTATUS
gckOS_AllocateContiguous(
    IN gckOS Os,
    IN gctBOOL InUserSpace,
    IN OUT gctSIZE_T * Bytes,
    OUT gctPHYS_ADDR * Physical,
    OUT gctPOINTER * Logical
    )
{
    if (InUserSpace)
    {
        gctUINT32 pid;

        gcmkVERIFY_OK(gckOS_GetProcessID(&pid));

        /* TODO: Make a separate OS call for allocating from shared memory pool. */
        *Logical = drv_shmpool_alloc_contiguous((gctUINT32)pid, *Bytes, 0x0); /*non-cacheable */
        if (*Logical == gcvNULL)
        {
            gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocateContiguous: Out of memory.");

            *Bytes = 0;
            return gcvSTATUS_OUT_OF_RESOURCES;
        }

        /* Used to distinguish from memory allocated in kernel space. */
        *((gctUINT32*)Physical) = 0;
    }
    else
    {
        drv_mempool_alloc_contiguous(*Bytes, Physical, Logical);

        if (*Physical == gcvNULL || *Logical == gcvNULL)
        {
            gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocateContiguous: Out of memory.");

            *Bytes = 0;
            return gcvSTATUS_OUT_OF_RESOURCES;
        }
    }

    gcmkTRACE_ZONE(gcvLEVEL_INFO,
                gcvZONE_OS,
                "gckOS_AllocateContiguous: "
                "Bytes->0x%x, Logical->0x%x Physical->0x%x\n",
                (gctUINT32)*Bytes,
                *Logical,
                *Physical);

    /* Success. */
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_FreeContiguous
**
**  Free memory allocated from the contiguous pool.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPHYS_ADDR Physical
**          Physical address of the allocation.
**
**      gctPOINTER Logical
**          Logicval address of the allocation.
**
**      gctSIZE_T Bytes
**          Number of bytes of the allocation.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_FreeContiguous(
    IN gckOS Os,
    IN gctPHYS_ADDR Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T Bytes
    )
{
    /* Same of non-paged memory for now. */
    return gckOS_FreeNonPagedMemory(Os, Bytes, Physical, Logical);
}


/*******************************************************************************
**
**  gckOS_MapUserPointer
**
**  Map a pointer from the user process into the kernel address space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Pointer
**          Pointer in user process space that needs to be mapped.
**
**      gctSIZE_T Size
**          Number of bytes that need to be mapped.
**
**  OUTPUT:
**
**      gctPOINTER * KernelPointer
**          Pointer to a variable receiving the mapped pointer in kernel address
**          space.
*/
gceSTATUS
gckOS_MapUserPointer(
    IN gckOS Os,
    IN gctPOINTER Pointer,
    IN gctSIZE_T Size,
    OUT gctPOINTER * KernelPointer
    )
{
    /* A pointer is assumed to be allocated from its shared memory object.
       Which is mapped by both user and kernel at the same virtual address. */
    /* TODO: Check if Pointer is a valid pointer? */
    *KernelPointer = Pointer;

    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_UnmapUserPointer
**
**  Unmap a user process pointer from the kernel address space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Pointer
**          Pointer in user process space that needs to be unmapped.
**
**      gctSIZE_T Size
**          Number of bytes that need to be unmapped.
**
**      gctPOINTER KernelPointer
**          Pointer in kernel address space that needs to be unmapped.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UnmapUserPointer(
    IN gckOS Os,
    IN gctPOINTER Pointer,
    IN gctSIZE_T Size,
    IN gctPOINTER KernelPointer
    )
{
    /* Nothing to unmap. */
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_QueryNeedCopy
**
**  Query whether the memory can be accessed or mapped directly or it has to be
**  copied.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctUINT32 ProcessID
**          Process ID of the current process.
**
**  OUTPUT:
**
**      gctBOOL_PTR NeedCopy
**          Pointer to a boolean receiving gcvTRUE if the memory needs a copy or
**          gcvFALSE if the memory can be accessed or mapped dircetly.
*/
gceSTATUS
gckOS_QueryNeedCopy(
    IN gckOS Os,
    IN gctUINT32 ProcessID,
    OUT gctBOOL_PTR NeedCopy
    )
{
    gcmkHEADER_ARG("Os=0x%X ProcessID=%d", Os, ProcessID);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(NeedCopy != gcvNULL);

    /* No need to copy data. */
    *NeedCopy = gcvFALSE;

    /* Success. */
    gcmkFOOTER_ARG("*NeedCopy=%d", *NeedCopy);
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_CopyFromUserData
**
**  Copy data from user to kernel memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER KernelPointer
**          Pointer to kernel memory.
**
**      gctPOINTER Pointer
**          Pointer to user memory.
**
**      gctSIZE_T Size
**          Number of bytes to copy.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_CopyFromUserData(
    IN gckOS Os,
    IN gctPOINTER KernelPointer,
    IN gctPOINTER Pointer,
    IN gctSIZE_T Size
    )
{
    gcmkHEADER_ARG("Os=0x%X KernelPointer=0x%X Pointer=0x%X Size=%lu",
                   Os, KernelPointer, Pointer, Size);

    gcmkASSERT(gcvFALSE);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_CopyToUserData
**
**  Copy data from kernel to user memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER KernelPointer
**          Pointer to kernel memory.
**
**      gctPOINTER Pointer
**          Pointer to user memory.
**
**      gctSIZE_T Size
**          Number of bytes to copy.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_CopyToUserData(
    IN gckOS Os,
    IN gctPOINTER KernelPointer,
    IN gctPOINTER Pointer,
    IN gctSIZE_T Size
    )
{
    gcmkHEADER_ARG("Os=0x%X KernelPointer=0x%X Pointer=0x%X Size=%lu",
                   Os, KernelPointer, Pointer, Size);

    gcmkASSERT(gcvFALSE);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_MapUserPhysical
**
**  Map a physical address from the user process into the kernel address space.
**  The physical address should be obtained by user from gckOS_AllocateNonPagedMemory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      IN gctPHYS_ADDR Phys,
**          Physical address of memory that needs to be mapped.
**
**  OUTPUT:
**
**      gctPHYS_ADDR * KernelPointer
**          Pointer to a variable receiving the mapped pointer in kernel address
**          space.
*/
gceSTATUS
gckOS_MapUserPhysical(
    IN gckOS Os,
    IN gctPHYS_ADDR Phys,
    OUT gctPHYS_ADDR * KernelPointer
    )
{
    /* A gctPHYS_ADDR is assumed to be allocated from physical memory pool. */
    /* Dont call this function for pointers already in kernel space. */
    printf("ERROR: %s Not supported.\n", __FUNCTION__);
    *KernelPointer = (gctPHYS_ADDR)0xDEADBEEF;

    return gcvSTATUS_NOT_SUPPORTED;
}


/*******************************************************************************
**
**  gckOS_WriteMemory
**
**  Write data to a memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctPOINTER Address
**          Address of the memory to write to.
**
**      gctUINT32 Data
**          Data for register.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_WriteMemory(
    IN gckOS Os,
    IN gctPOINTER Address,
    IN gctUINT32 Data
    )
{
    gcmkHEADER_ARG("Os=0x%X Address=0x%X Data=%u", Os, Address, Data);

    /* Verify the arguments. */
    gcmkVERIFY_ARGUMENT(Address != gcvNULL);

    /* Write memory. */
    *(gctUINT32 *)Address = Data;

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}


/*******************************************************************************
**
**  gckOS_MapUserMemory
**
**  Lock down a user buffer and return an DMA'able address to be used by the
**  hardware to access it.
**
**  INPUT:
**
**      gctPOINTER Memory
**          Pointer to memory to lock down.
**
**      gctSIZE_T Size
**          Size in bytes of the memory to lock down.
**
**  OUTPUT:
**
**      gctPOINTER * Info
**          Pointer to variable receiving the information record required by
**          gckOS_UnmapUserMemory.
**
**      gctUINT32_PTR Address
**          Pointer to a variable that will receive the address DMA'able by the
**          hardware.
*/
gceSTATUS
gckOS_MapUserMemory(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctPOINTER Memory,
    IN gctUINT32 Physical,
    IN gctSIZE_T Size,
    OUT gctPOINTER * Info,
    OUT gctUINT32_PTR Address
    )
{
    gceSTATUS status;
    gctSIZE_T pageCount, pageShift;
    gctPOINTER pageTable = NULL;
    gctUINT32 address;
    gctUINT32 start, end, memory;
    gctUINT32 pid = 0;

    gcmkHEADER_ARG("Os=0x%X Core=%d Memory=0x%X Size=%lu", Os, Core, Memory, Size);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);
    gcmkVERIFY_ARGUMENT(Size > 0);
    gcmkVERIFY_ARGUMENT(Info != gcvNULL);
    gcmkVERIFY_ARGUMENT(Address != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_VERBOSE,
        gcvZONE_OS,
        "[gckOS_MapUserMemory] enter.\n"
        );

    if (__PAGESIZE == 4096)
    {
        pageShift = 12;
    }
    else
    {
        /* Only page size 4096 supported. */
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_NOT_SUPPORTED);
        return gcvSTATUS_NOT_SUPPORTED;
    }

    gcmkVERIFY_OK(gckOS_GetProcessID(&pid));

    do
    {
        memory = ((gctUINT32) Memory) & ~(__PAGESIZE - 1);
        Size += ((gctUINT32)Memory - memory);

        /* Get the number of required pages. */
        end = (memory + Size + __PAGESIZE - 1) >> pageShift;
        start = memory >> pageShift;
        pageCount = end - start;

        gcmkTRACE_ZONE(gcvLEVEL_INFO,
            gcvZONE_OS,
            "[gckOS_MapUserMemory] pageCount: %d.",
            pageCount
            );

        /* Invalid argument. */
        if (pageCount <= 0)
        {
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
            return gcvSTATUS_INVALID_ARGUMENT;
        }

        /* Overflow. */
        if ((memory + Size) < memory)
        {
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
            return gcvSTATUS_INVALID_ARGUMENT;
        }

        MEMORY_MAP_LOCK(Os);

        /* Flush the data cache. */
        gckOS_MemoryBarrier(Os, Memory);

        /* Allocate pages inside the page table. */
        {
            gcmkERR_BREAK(gckMMU_AllocatePages(Os->device->kernels[Core]->mmu,
                                              pageCount * (__PAGESIZE/4096),
                                              &pageTable,
                                              &address));
        }

        /* Fill the page table. */
        gcmkERR_BREAK(gckOS_MapPagesPeer(Os,
                                         Core,
                                         pid,
                                         (gctPHYS_ADDR)~0,
                                         (gctPOINTER)memory,
                                         pageCount,
                                         pageTable));

        {
            gcmkERR_BREAK(gckMMU_Flush(Os->device->kernels[Core]->mmu));
        }

        /* Save pointer to page table. */
        *Info = pageTable;

        *Address = address + ((gctUINT32)Memory & (__PAGESIZE - 1) );

        gcmkTRACE_ZONE(gcvLEVEL_INFO,
            gcvZONE_OS,
            "[gckOS_MapUserMemory] Address: 0x%x.",
            *Address
            );

        /* Success. */
        status = gcvSTATUS_OK;
    }
    while (gcvFALSE);

    if (gcmIS_ERROR(status))
    {
        gcmkTRACE_ZONE(gcvLEVEL_ERROR,
            gcvZONE_OS,
            "[gckOS_MapUserMemory] error occured: %d.",
            status
            );

        if (pageTable != gcvNULL)
        {
            {
                gckMMU_FreePages(Os->device->kernels[Core]->mmu,
                        pageTable,
                        pageCount);
            }
        }
    }

    MEMORY_MAP_UNLOCK(Os);

    gcmkTRACE_ZONE(gcvLEVEL_VERBOSE,
        gcvZONE_OS,
        "[gckOS_MapUserMemory] leave.\n"
        );

    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_UnmapUserMemory
**
**  Unlock a user buffer and that was previously locked down by
**  gckOS_MapUserMemory.
**
**  INPUT:
**
**      gctPOINTER Memory
**          Pointer to memory to unlock.
**
**      gctSIZE_T Size
**          Size in bytes of the memory to unlock.
**
**      gctPOINTER Info
**          Information record returned by gckOS_MapUserMemory.
**
**      gctUINT32_PTR Address
**          The address returned by gckOS_MapUserMemory.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UnmapUserMemory(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctPOINTER Memory,
    IN gctSIZE_T Size,
    IN gctPOINTER Info,
    IN gctUINT32 Address
    )
{
    gceSTATUS status;
    gctUINT32 memory, start, end;
    gctSIZE_T pageCount, pageShift;

    gcmkHEADER_ARG("Os=0x%X Core=%d Memory=0x%X Size=%lu Info=0x%X Address0x%08x",
                   Os, Core, Memory, Size, Info, Address);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);
    gcmkVERIFY_ARGUMENT(Size > 0);
    gcmkVERIFY_ARGUMENT(Info != gcvNULL);

    gcmkTRACE_ZONE(gcvLEVEL_VERBOSE,
        gcvZONE_OS,
        "[gckOS_UnmapUserMemory] enter.\n"
        );

    if (__PAGESIZE == 4096)
    {
        pageShift = 12;
    }
    else
    {
        /* Only page size 4096 supported. */
        gcmkFOOTER_ARG("status=%d", gcvSTATUS_NOT_SUPPORTED);
        return gcvSTATUS_NOT_SUPPORTED;
    }

    do
    {
        /* Invalid page array. */
        if (Info == gcvNULL)
        {
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
            return gcvSTATUS_INVALID_ARGUMENT;
        }

        memory = (gctUINT32) Memory;
        end = (memory + Size + __PAGESIZE - 1) >> pageShift;
        start = memory >> pageShift;
        pageCount = end - start;

        /* Overflow. */
        if ((memory + Size) < memory)
        {
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
            return gcvSTATUS_INVALID_ARGUMENT;
        }

        /* Invalid argument. */
        if (pageCount <= 0)
        {
            gcmkFOOTER_ARG("status=%d", gcvSTATUS_INVALID_ARGUMENT);
            return gcvSTATUS_INVALID_ARGUMENT;
        }

        gcmkTRACE_ZONE(gcvLEVEL_INFO,
            gcvZONE_OS,
            "[gckOS_UnmapUserMemory] memory: 0x%x, pageCount: %d, pageTable: 0x%x.",
            memory,
            pageCount,
            Info
            );

        MEMORY_MAP_LOCK(Os);

        /* Free the pages from the MMU. */
        {
            gcmkERR_BREAK(gckMMU_FreePages(Os->device->kernels[Core]->mmu,
                        Info,
                        pageCount * (__PAGESIZE/4096)
                        ));
        }

        /* Flush the data cache. */
        gckOS_MemoryBarrier(Os, Memory);

        /* Success. */
        status = gcvSTATUS_OK;
    }
    while (gcvFALSE);

    MEMORY_MAP_UNLOCK(Os);

    /* Return the status. */
    return status;

}




/*******************************************************************************
**
**  gckOS_GetBaseAddress
**
**  Get the base address for the physical memory.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**  OUTPUT:
**
**      gctUINT32_PTR BaseAddress
**          Pointer to a variable that will receive the base address.
*/
gceSTATUS
gckOS_GetBaseAddress(
    IN gckOS Os,
    OUT gctUINT32_PTR BaseAddress
    )
{
    gcmkHEADER_ARG("Os=0x%X", Os);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(BaseAddress != gcvNULL);

    /* Return base address. */
    *BaseAddress = Os->baseAddress;

    /* Success. */
    gcmkFOOTER_ARG("*BaseAddress=0x%08x", *BaseAddress);
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_SuspendInterrupt(
    IN gckOS Os
    )
{
    return gckOS_SuspendInterruptEx(Os, gcvCORE_MAJOR);
}

gceSTATUS
gckOS_SuspendInterruptEx(
    IN gckOS Os,
    IN gceCORE Core
    )
{
    gcmkHEADER_ARG("Os=0x%X Core=%d", Os, Core);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    InterruptLock(&Os->device->isrLock);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_ResumeInterrupt(
    IN gckOS Os
    )
{
    return gckOS_ResumeInterruptEx(Os, gcvCORE_MAJOR);
}

gceSTATUS
gckOS_ResumeInterruptEx(
    IN gckOS Os,
    IN gceCORE Core
    )
{
    gcmkHEADER_ARG("Os=0x%X Core=%d", Os, Core);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    InterruptUnlock(&Os->device->isrLock);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_NotifyIdle(
    IN gckOS Os,
    IN gctBOOL Idle
    )
{
    /* TODO */
    return gcvSTATUS_OK;
}

/* Perform a memory copy. */
gceSTATUS
gckOS_MemCopy(
        IN gctPOINTER Destination,
        IN gctCONST_POINTER Source,
        IN gctSIZE_T Bytes
        )
{
    gcmkHEADER_ARG("Destination=0x%X Source=0x%X Bytes=%lu",
                   Destination, Source, Bytes);

    gcmkVERIFY_ARGUMENT(Destination != gcvNULL);
    gcmkVERIFY_ARGUMENT(Source != gcvNULL);
    gcmkVERIFY_ARGUMENT(Bytes > 0);

    fast_mem_cpy(Destination, Source, Bytes);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_ZeroMemory(
    IN gctPOINTER Memory,
    IN gctSIZE_T Bytes
    )
{
    gcmkHEADER_ARG("Memory=0x%X Bytes=%lu", Memory, Bytes);

    gcmkVERIFY_ARGUMENT(Memory != gcvNULL);
    gcmkVERIFY_ARGUMENT(Bytes > 0);

    memset(Memory, 0, Bytes);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

int
memmgr_peer_sendnc(pid_t pid, int coid, void *smsg, size_t sbytes, void *rmsg, size_t rbytes )
{
    mem_peer_t  peer;
    iov_t       siov[2];
    int         rc;

    peer.i.type = _MEM_PEER;
    peer.i.peer_msg_len = sizeof(peer);
    peer.i.pid = pid;

    SETIOV(siov + 0, &peer, sizeof peer);
    SETIOV(siov + 1, smsg, sbytes);

    do {
        rc = MsgSendvsnc(coid, siov, 2, rmsg, rbytes);
    } while (rc == -1 && errno == EINTR);

    return rc;
}

void *
_mmap2_peer(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off64_t off,
        unsigned align, unsigned pre_load, void **base, size_t *size) {
    mem_map_t msg;

    msg.i.type = _MEM_MAP;
    msg.i.zero = 0;
    msg.i.addr = (uintptr_t)addr;
    msg.i.len = len;
    msg.i.prot = prot;
    msg.i.flags = flags;
    msg.i.fd = fd;
    msg.i.offset = off;
    msg.i.align = align;
    msg.i.preload = pre_load;
    msg.i.reserved1 = 0;
    if (memmgr_peer_sendnc(pid, MEMMGR_COID, &msg.i, sizeof msg.i, &msg.o, sizeof msg.o) == -1) {
        return MAP_FAILED;
    }
    if (base) {
        *base = (void *)(uintptr_t)msg.o.real_addr;
    }
    if (size) {
        *size = msg.o.real_size;
    }
    return (void *)(uintptr_t)msg.o.addr;
}

void *
mmap64_peer(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off64_t off) {
    return _mmap2_peer(pid, addr, len, prot, flags, fd, off, 0, 0, 0, 0);
}

int
munmap_flags_peer(pid_t pid, void *addr, size_t len, unsigned flags) {
    mem_ctrl_t msg;

    msg.i.type = _MEM_CTRL;
    msg.i.subtype = _MEM_CTRL_UNMAP;
    msg.i.addr = (uintptr_t)addr;
    msg.i.len = len;
    msg.i.flags = flags;
    return memmgr_peer_sendnc(pid, MEMMGR_COID, &msg.i, sizeof msg.i, 0, 0);
}

int
munmap_peer(pid_t pid, void *addr, size_t len) {
    return munmap_flags_peer(pid, addr, len, 0);
}

int
mem_offset64_peer(pid_t pid, const uintptr_t addr, size_t len,
                off64_t *offset, size_t *contig_len) {
    int rc;

    struct _peer_mem_off {
        struct _mem_peer peer;
        struct _mem_offset msg;
    };
    typedef union {
        struct _peer_mem_off i;
        struct _mem_offset_reply o;
    } memoffset_peer_t;
    memoffset_peer_t msg;

    msg.i.peer.type = _MEM_PEER;
    msg.i.peer.peer_msg_len = sizeof(msg.i.peer);
    msg.i.peer.pid = pid;
    msg.i.peer.reserved1 = 0;

    msg.i.msg.type = _MEM_OFFSET;
    msg.i.msg.subtype = _MEM_OFFSET_PHYS;
    msg.i.msg.addr = addr;
    msg.i.msg.reserved = -1;
    msg.i.msg.len = len;

    do {
        rc = MsgSendnc(MEMMGR_COID, &msg.i, sizeof msg.i, &msg.o, sizeof msg.o);
    } while (rc == -1 && errno == EINTR);

    if (rc == -1) {
        return -1;
    }

    *offset = msg.o.offset;
    *contig_len = msg.o.size;

    return 0;
}

#if defined(__X86__)
#define CPU_VADDR_SERVER_HINT 0x30000000u
#elif defined(__ARM__)
#define CPU_VADDR_SERVER_HINT 0x20000000u
#else
#error NO CPU SOUP FOR YOU!
#endif

/*
 * map the object into both client and server at the same virtual address
 */
void *
mmap64_join(pid_t pid, void *addr, size_t len, int prot, int flags, int fd, off64_t off) {
    void *svaddr, *cvaddr = MAP_FAILED;
    uintptr_t hint = (uintptr_t)addr;
    uintptr_t start_hint = hint;

    if ( hint == (uintptr_t)0 )
    {
        hint = (uintptr_t)CPU_VADDR_SERVER_HINT;
    }

    do {
        svaddr = mmap64( (void *)hint, len, prot, flags, fd, off );
        if ( svaddr == MAP_FAILED ) {
            printf("%s:%d\n", __FUNCTION__, __LINE__);
            break;
        }
        if ( svaddr == cvaddr ) {
            return svaddr;
        }

        cvaddr = mmap64_peer( pid, svaddr, len, prot, MAP_FIXED | flags, fd, off );
        if ( cvaddr == MAP_FAILED ) {
            break;
        }
        if ( svaddr == cvaddr ) {
            return svaddr;
        }

        if ( munmap( svaddr, len ) == -1 ) {
            svaddr = MAP_FAILED;
            break;
        }

        svaddr = mmap64( cvaddr, len, prot, flags, fd, off );
        if ( svaddr == MAP_FAILED ) {
            break;
        }
        if ( svaddr == cvaddr ) {
            return svaddr;
        }

        if ( munmap( svaddr, len ) == -1 ) {
            svaddr = MAP_FAILED;
            break;
        }
        if ( munmap_peer( pid, cvaddr, len ) == -1 ) {
            cvaddr = MAP_FAILED;
            break;
        }
        hint += __PAGESIZE;

    } while(hint != start_hint); /* do we really want to wrap all the way */

    if ( svaddr != MAP_FAILED ) {
        munmap( svaddr, len );
    }
    if ( cvaddr != MAP_FAILED ) {
        munmap_peer( pid, cvaddr, len );
    }

    return MAP_FAILED;
}

/*******************************************************************************
**  gckOS_CacheClean
**
**  Clean the cache for the specified addresses.  The GPU is going to need the
**  data.  If the system is allocating memory as non-cachable, this function can
**  be ignored.
**
**  ARGUMENTS:
**
**      gckOS Os
**          Pointer to gckOS object.
**
**      gctUINT32 ProcessID
**          Process ID Logical belongs.
**
**      gctPHYS_ADDR Handle
**          Physical address handle.  If gcvNULL it is video memory.
**
**      gctPOINTER Physical
**          Physical address to flush.
**
**      gctPOINTER Logical
**          Logical address to flush.
**
**      gctSIZE_T Bytes
**          Size of the address range in bytes to flush.
*/
gceSTATUS
gckOS_CacheClean(
    IN gckOS Os,
    IN gctUINT32 ProcessID,
    IN gctPHYS_ADDR Handle,
    IN gctPOINTER Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T Bytes
    )
{
    __asm__ __volatile__ ("dsb");
    return gcvSTATUS_OK;
}

/*******************************************************************************
**  gckOS_CacheFlush
**
**  Flush the cache for the specified addresses.  The GPU is going to need the
**  data.  If the system is allocating memory as non-cachable, this function can
**  be ignored.
**
**  ARGUMENTS:
**
**      gckOS Os
**          Pointer to gckOS object.
**
**      gctUINT32 ProcessID
**          Process ID Logical belongs.
**
**      gctPHYS_ADDR Handle
**          Physical address handle.  If gcvNULL it is video memory.
**
**      gctPOINTER Logical
**          Logical address to flush.
**
**      gctSIZE_T Bytes
**          Size of the address range in bytes to flush.
*/
gceSTATUS
gckOS_CacheFlush(
    IN gckOS Os,
    IN gctUINT32 ProcessID,
    IN gctPHYS_ADDR Handle,
    IN gctPOINTER Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T Bytes
    )
{
    __asm__ __volatile__ ("dsb");
    return gcvSTATUS_OK;
}

/*******************************************************************************
**  gckOS_CacheInvalidate
**
**  Flush the cache for the specified addresses and invalidate the lines as
**  well.  The GPU is going to need and modify the data.  If the system is
**  allocating memory as non-cachable, this function can be ignored.
**
**  ARGUMENTS:
**
**      gckOS Os
**          Pointer to gckOS object.
**
**      gctUINT32 ProcessID
**          Process ID Logical belongs.
**
**      gctPHYS_ADDR Handle
**          Physical address handle.  If gcvNULL it is video memory.
**
**      gctPOINTER Logical
**          Logical address to flush.
**
**      gctSIZE_T Bytes
**          Size of the address range in bytes to flush.
*/
gceSTATUS
gckOS_CacheInvalidate(
    IN gckOS Os,
    IN gctUINT32 ProcessID,
    IN gctPHYS_ADDR Handle,
    IN gctPOINTER Physical,
    IN gctPOINTER Logical,
    IN gctSIZE_T Bytes
    )
{
    __asm__ __volatile__ ("dsb");

    return gcvSTATUS_OK;
}

/*******************************************************************************
********************************* Broadcasting *********************************
*******************************************************************************/

/*******************************************************************************
**
**  gckOS_Broadcast
**
**  System hook for broadcast events from the kernel driver.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gckHARDWARE Hardware
**          Pointer to the gckHARDWARE object.
**
**      gceBROADCAST Reason
**          Reason for the broadcast.  Can be one of the following values:
**
**              gcvBROADCAST_GPU_IDLE
**                  Broadcasted when the kernel driver thinks the GPU might be
**                  idle.  This can be used to handle power management.
**
**              gcvBROADCAST_GPU_COMMIT
**                  Broadcasted when any client process commits a command
**                  buffer.  This can be used to handle power management.
**
**              gcvBROADCAST_GPU_STUCK
**                  Broadcasted when the kernel driver hits the timeout waiting
**                  for the GPU.
**
**              gcvBROADCAST_FIRST_PROCESS
**                  First process is trying to connect to the kernel.
**
**              gcvBROADCAST_LAST_PROCESS
**                  Last process has detached from the kernel.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_Broadcast(
    IN gckOS Os,
    IN gckHARDWARE Hardware,
    IN gceBROADCAST Reason
    )
{
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%X Hardware=0x%X Reason=%d", Os, Hardware, Reason);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_OBJECT(Hardware, gcvOBJ_HARDWARE);

    switch (Reason)
    {
    case gcvBROADCAST_FIRST_PROCESS:
        gcmkTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_OS, "First process has attached");
        break;

    case gcvBROADCAST_LAST_PROCESS:
        gcmkTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_OS, "Last process has detached");

        /* Put GPU OFF. */
        gcmkONERROR(
            gckHARDWARE_SetPowerManagementState(Hardware,
                                                gcvPOWER_OFF_BROADCAST));
        break;

    case gcvBROADCAST_GPU_IDLE:
        gcmkTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_OS, "GPU idle.");

        /* Put GPU IDLE. */
        gcmkONERROR(
            gckHARDWARE_SetPowerManagementState(Hardware,
                                                gcvPOWER_IDLE_BROADCAST));

        /* Add idle process DB. */
        gcmkONERROR(gckKERNEL_AddProcessDB(Hardware->kernel,
                                           1,
                                           gcvDB_IDLE,
                                           gcvNULL, gcvNULL, 0));
        break;

    case gcvBROADCAST_GPU_COMMIT:
        gcmkTRACE_ZONE(gcvLEVEL_INFO, gcvZONE_OS, "COMMIT has arrived.");

        /* Add busy process DB. */
        gcmkONERROR(gckKERNEL_AddProcessDB(Hardware->kernel,
                                           0,
                                           gcvDB_IDLE,
                                           gcvNULL, gcvNULL, 0));

        /* Put GPU ON. */
        gcmkONERROR(
            gckHARDWARE_SetPowerManagementState(Hardware, gcvPOWER_ON_AUTO));
        break;

    case gcvBROADCAST_GPU_STUCK:
        gcmkTRACE_N(gcvLEVEL_ERROR, 0, "gcvBROADCAST_GPU_STUCK\n");
        gcmkONERROR(gckHARDWARE_DumpGPUState(Hardware));
        gcmkONERROR(gckKERNEL_Recovery(Hardware->kernel));
        break;

    case gcvBROADCAST_AXI_BUS_ERROR:
        gcmkTRACE_N(gcvLEVEL_ERROR, 0, "gcvBROADCAST_AXI_BUS_ERROR\n");
        gcmkONERROR(gckHARDWARE_DumpGPUState(Hardware));
        gcmkONERROR(gckKERNEL_Recovery(Hardware->kernel));
        break;
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_BroadcastHurry
**
**  The GPU is running too slow.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gckHARDWARE Hardware
**          Pointer to the gckHARDWARE object.
**
**      gctUINT Urgency
**          The higher the number, the higher the urgency to speed up the GPU.
**          The maximum value is defined by the gcdDYNAMIC_EVENT_THRESHOLD.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_BroadcastHurry(
    IN gckOS Os,
    IN gckHARDWARE Hardware,
    IN gctUINT Urgency
    )
{
    gcmkHEADER_ARG("Os=0x%x Hardware=0x%x Urgency=%u", Os, Hardware, Urgency);

    /* Do whatever you need to do to speed up the GPU now. */

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_BroadcastCalibrateSpeed
**
**  Calibrate the speed of the GPU.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gckHARDWARE Hardware
**          Pointer to the gckHARDWARE object.
**
**      gctUINT Idle, Time
**          Idle/Time will give the percentage the GPU is idle, so you can use
**          this to calibrate the working point of the GPU.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_BroadcastCalibrateSpeed(
    IN gckOS Os,
    IN gckHARDWARE Hardware,
    IN gctUINT Idle,
    IN gctUINT Time
    )
{
    gcmkHEADER_ARG("Os=0x%x Hardware=0x%x Idle=%u Time=%u",
                   Os, Hardware, Idle, Time);

    /* Do whatever you need to do to callibrate the GPU speed. */

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
********************************** Semaphores **********************************
*******************************************************************************/

/*******************************************************************************
**
**  gckOS_CreateSemaphore
**
**  Create a semaphore.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**  OUTPUT:
**
**      gctPOINTER * Semaphore
**          Pointer to the variable that will receive the created semaphore.
*/
gceSTATUS
gckOS_CreateSemaphore(
    IN gckOS Os,
    OUT gctPOINTER * Semaphore
    )
{
    gceSTATUS status;
    sem_t *sem = gcvNULL;

    gcmkHEADER_ARG("Os=0x%X", Os);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Semaphore != gcvNULL);

    /* Allocate the semaphore structure. */
    gcmkONERROR(
        gckOS_Allocate(Os, gcmSIZEOF(*sem), (gctPOINTER *) &sem));

    /* Initialize the semaphore. */
    if (sem_init(sem, 0, 1) != 0)
    {
        gckOS_Free(Os, sem);
        gcmkONERROR(gcvSTATUS_OUT_OF_RESOURCES);
    }

    /* Return to caller. */
    *Semaphore = (gctPOINTER) sem;

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_AcquireSemaphore
**
**  Acquire a semaphore.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Semaphore
**          Pointer to the semaphore thet needs to be acquired.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_AcquireSemaphore(
    IN gckOS Os,
    IN gctPOINTER Semaphore
    )
{
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%08X Semaphore=0x%08X", Os, Semaphore);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Semaphore != gcvNULL);

    /* Acquire the semaphore. */
    if (sem_wait((sem_t *)Semaphore))
    {
        gcmkONERROR(gcvSTATUS_TIMEOUT);
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_TryAcquireSemaphore
**
**  Try to acquire a semaphore.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Semaphore
**          Pointer to the semaphore thet needs to be acquired.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_TryAcquireSemaphore(
    IN gckOS Os,
    IN gctPOINTER Semaphore
    )
{
    gceSTATUS status;
    int rc;

    gcmkHEADER_ARG("Os=0x%x", Os);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Semaphore != gcvNULL);

    /* Acquire the semaphore. */
    rc = sem_trywait((sem_t *)Semaphore);
    if ((0 != rc) && (EAGAIN != rc))
    {
        /* Timeout. */
        status = gcvSTATUS_TIMEOUT;
        gcmkFOOTER();
        return status;
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_ReleaseSemaphore
**
**  Release a previously acquired semaphore.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Semaphore
**          Pointer to the semaphore thet needs to be released.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_ReleaseSemaphore(
    IN gckOS Os,
    IN gctPOINTER Semaphore
    )
{
    gcmkHEADER_ARG("Os=0x%X Semaphore=0x%X", Os, Semaphore);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Semaphore != gcvNULL);

    /* Release the semaphore. */
    sem_post((sem_t *)Semaphore);

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_DestroySemaphore
**
**  Destroy a semaphore.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to the gckOS object.
**
**      gctPOINTER Semaphore
**          Pointer to the semaphore thet needs to be destroyed.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_DestroySemaphore(
    IN gckOS Os,
    IN gctPOINTER Semaphore
    )
{
    gceSTATUS status;

    gcmkHEADER_ARG("Os=0x%X Semaphore=0x%X", Os, Semaphore);

     /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Semaphore != gcvNULL);

    sem_destroy((sem_t *)Semaphore);

    /* Free the sempahore structure. */
    gcmkONERROR(gckOS_Free(Os, Semaphore));

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;

OnError:
    /* Return the status. */
    gcmkFOOTER();
    return status;
}

/*******************************************************************************
**
**  gckOS_GetProcessID
**
**  Get current process ID.
**
**  INPUT:
**
**      Nothing.
**
**  OUTPUT:
**
**      gctUINT32_PTR ProcessID
**          Pointer to the variable that receives the process ID.
*/
gceSTATUS
gckOS_GetProcessID(
    OUT gctUINT32_PTR ProcessID
    )
{
    /* Get process ID. */
    *ProcessID = drv_get_user_pid();

    if (0 == *ProcessID)
    {
        /* Return Kernel PID. */
        *ProcessID = getpid();
    }

    /* Success. */
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_GetThreadID
**
**  Get current thread ID.
**
**  INPUT:
**
**      Nothing.
**
**  OUTPUT:
**
**      gctUINT32_PTR ThreadID
**          Pointer to the variable that receives the thread ID.
*/
gceSTATUS
gckOS_GetThreadID(
    OUT gctUINT32_PTR ThreadID
    )
{
    /* Get thread ID. */
    if (ThreadID != gcvNULL)
    {
        *ThreadID = drv_get_user_tid();
    }

    /* Success. */
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_SetGPUPower
**
**  Set the power of the GPU on or off.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**      gckCORE Core
**          GPU whose power is set.
**
**      gctBOOL Clock
**          gcvTRUE to turn on the clock, or gcvFALSE to turn off the clock.
**
**      gctBOOL Power
**          gcvTRUE to turn on the power, or gcvFALSE to turn off the power.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_SetGPUPower(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctBOOL Clock,
    IN gctBOOL Power
    )
{
    gcmkHEADER_ARG("Os=0x%X Core=%d Clock=%d Power=%d", Os, Core, Clock, Power);

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_ResetGPU
**
**  Reset the GPU.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to a gckOS object.
**
**      gckCORE Core
**          GPU whose power is set.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_ResetGPU(
    IN gckOS Os,
    IN gceCORE Core
    )
{
    gcmkHEADER_ARG("Os=0x%X Core=%d", Os, Core);

    /* TODO: Put your code here. */

    gcmkFOOTER_NO();
    return gcvSTATUS_NOT_SUPPORTED;
}

/*----------------------------------------------------------------------------*/
/*----- Profile --------------------------------------------------------------*/

gceSTATUS
gckOS_GetProfileTick(
    OUT gctUINT64_PTR Tick
    )
{
    struct timespec ts;

    gcmkHEADER();

    clock_gettime(CLOCK_MONOTONIC, &ts);

    *Tick = ts.tv_nsec + ts.tv_sec * 1000000000ULL;

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_QueryProfileTickRate(
    OUT gctUINT64_PTR TickRate
    )
{
    *TickRate = 0;

    return gcvSTATUS_NOT_SUPPORTED;
}

gctUINT32
gckOS_ProfileToMS(
    IN gctUINT64 Ticks
    )
{
    gctUINT64 rem = Ticks;
    gctUINT64 b = 1000000;
    gctUINT64 res, d = 1;
    gctUINT32 high = rem >> 32;

    /* Reduce the thing a bit first */
    res = 0;
    if (high >= 1000000)
    {
        high /= 1000000;
        res   = (gctUINT64) high << 32;
        rem  -= (gctUINT64) (high * 1000000) << 32;
    }

    while (((gctINT64) b > 0) && (b < rem))
    {
        b <<= 1;
        d <<= 1;
    }

    do
    {
        if (rem >= b)
        {
            rem -= b;
            res += d;
        }

        b >>= 1;
        d >>= 1;
    }
    while (d);

    return (gctUINT32) res;
}

/******************************************************************************\
******************************* Signal Management ******************************
\******************************************************************************/

#undef _GC_OBJ_ZONE
#define _GC_OBJ_ZONE    gcvZONE_SIGNAL

/*******************************************************************************
**
**  gckOS_CreateSignal
**
**  Create a new signal.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctBOOL ManualReset
**          If set to gcvTRUE, gckOS_Signal with gcvFALSE must be called in
**          order to set the signal to nonsignaled state.
**          If set to gcvFALSE, the signal will automatically be set to
**          nonsignaled state by gckOS_WaitSignal function.
**
**  OUTPUT:
**
**      gctSIGNAL * Signal
**          Pointer to a variable receiving the created gctSIGNAL.
*/
gceSTATUS
gckOS_CreateSignal(
    IN gckOS Os,
    IN gctBOOL ManualReset,
    OUT gctSIGNAL * Signal
    )
{
    gcskSIGNAL_PTR signal;
    pthread_condattr_t cattr;
    int rc;

    gcmkHEADER_ARG("Os=0x%X ManualReset=%d", Os, ManualReset);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Signal != gcvNULL);

    /* Create an event structure. */
    signal = (gcskSIGNAL_PTR) calloc(1, sizeof(gcskSIGNAL));
    if (signal == gcvNULL)
    {
        goto fail_01;
    }

    signal->reset = ManualReset;

    /* Initialize the mutex. */
    rc = pthread_mutex_init(&signal->mutex, gcvNULL);
    if (rc != EOK)
    {
        goto fail_02;
    }

    /* Initialize the condition. */
    rc = pthread_condattr_init(&cattr);
    if (rc != EOK)
    {
        goto fail_03;
    }

    rc = pthread_condattr_setclock(&cattr, CLOCK_MONOTONIC);
    if (rc != EOK)
    {
        goto fail_04;
    }

    rc = pthread_cond_init(&signal->cond, &cattr);
    if (rc != EOK)
    {
        goto fail_04;
    }

    /* We do not need the attribute any more. */
    pthread_condattr_destroy(&cattr);

    *Signal = (gctSIGNAL) signal;

    gcmkFOOTER_ARG("*Signal=0x%X", *Signal);
    return gcvSTATUS_OK;

fail_04:
    pthread_condattr_destroy(&cattr);
fail_03:
    pthread_mutex_destroy(&signal->mutex);
fail_02:
    free(signal);
fail_01:
    gcmkFOOTER_NO();
    return gcvSTATUS_OUT_OF_RESOURCES;
}

/*******************************************************************************
**
**  gckOS_DestroySignal
**
**  Destroy a signal.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIGNAL Signal
**          Pointer to the gctSIGNAL.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_DestroySignal(
    IN gckOS Os,
    IN gctSIGNAL Signal
    )
{
    gceSTATUS status = gcvSTATUS_OK;
    gcskSIGNAL_PTR signal;

    gcmkHEADER_ARG("Os=0x%X Signal=0x%X", Os, Signal);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Signal != gcvNULL);

    signal = (gcskSIGNAL_PTR) Signal;

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Signal != gcvNULL);

    if (signal != gcvNULL)
    {
        pthread_mutex_destroy(&signal->mutex);
        pthread_cond_destroy(&signal->cond);
        free(signal);
    }

    /* Success. */
    gcmkFOOTER_NO();
    return status;
}

/*******************************************************************************
**
**  gckOS_Signal
**
**  Set a state of the specified signal.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIGNAL Signal
**          Pointer to the gctSIGNAL.
**
**      gctBOOL State
**          If gcvTRUE, the signal will be set to signaled state.
**          If gcvFALSE, the signal will be set to nonsignaled state.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_Signal(
    IN gckOS Os,
    IN gctSIGNAL Signal,
    IN gctBOOL State
    )
{
    gcskSIGNAL_PTR signal;

    gcmkHEADER_ARG("Os=0x%X Signal=0x%X State=%d", Os, Signal, State);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Signal != gcvNULL);

    /* Cast the handle to the signal structure. */
    signal = (gcskSIGNAL_PTR) Signal;

    /* Acquire the mutex. */
    if (pthread_mutex_lock(&signal->mutex))
    {
        gcmkFOOTER_NO();
        return gcvSTATUS_GENERIC_IO;
    }

    /* Set the state. */
    signal->state = State;

    /* If the state is signaled, notify all waiting threads. */
    if (State && pthread_cond_broadcast(&signal->cond))
    {
        gcmkTRACE(gcvLEVEL_WARNING,
                 "%s(%d): pthread_cond_broadcast failed (%d).",
                 __FUNCTION__, __LINE__, errno);

        gcmkFOOTER_NO();
        return gcvSTATUS_GENERIC_IO;
    }

    /* Release the mutex. */
    if (pthread_mutex_unlock(&signal->mutex))
    {
        gcmkTRACE(gcvLEVEL_ERROR,
                 "%s(%d): pthread_mutex_unlock failed (%d).",
                 __FUNCTION__, __LINE__, errno);

        gcmkFOOTER_NO();
        return gcvSTATUS_GENERIC_IO;
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_UserSignal
**
**  Set the specified signal which is owned by a process to signaled state.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIGNAL Signal
**          Pointer to the gctSIGNAL.
**
**      gctHANDLE Process
**          Handle of process owning the signal.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_UserSignal(
    IN gckOS Os,
    IN gctSIGNAL Signal,
    IN gctINT Rcvid,
    IN gctINT Coid
    )
{
    gctINT rc;
    struct sigevent event;

    gcmkHEADER_ARG("Os=0x%x Signal=0x%x Rcvid=%d Coid=%d", Os, Signal, Rcvid, Coid);

    /* TODO: Shouldn't hard code the priority. */
    SIGEV_PULSE_INIT(&event, Coid, 21, GC_HAL_QNX_PULSEVAL_SIGNAL, Signal);

    rc = MsgDeliverEvent_r(Rcvid, &event);
    if (rc != EOK)
    {
        gcmkTRACE(gcvLEVEL_ERROR,
                 "%s(%d): MsgDeliverEvent failed (%d) error:%s.",
                 __FUNCTION__, __LINE__, rc, strerror(rc));
    }

    gcmkTRACE(gcvLEVEL_INFO,
             "%s(%d): Sent signal to (receive ID = %d, connect ID = %d).",
             __FUNCTION__, __LINE__, Rcvid, Coid);

    /* Return status. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_WaitSignal
**
**  Wait for a signal to become signaled.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIGNAL Signal
**          Pointer to the gctSIGNAL.
**
**      gctUINT32 Wait
**          Number of milliseconds to wait.
**          Pass the value of gcvINFINITE for an infinite wait.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_WaitSignal(
    IN gckOS Os,
    IN gctSIGNAL Signal,
    IN gctUINT32 Wait
    )
{
    gcskSIGNAL_PTR signal;
    gctINT result;

    gcmkHEADER_ARG("Os=0x%x Signal=0x%x Wait=%d", Os, Signal, Wait);

    /* Verify the arguments. */
    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);
    gcmkVERIFY_ARGUMENT(Signal != gcvNULL);

    /* Cast the handle to the signal structure. */
    signal = (gcskSIGNAL_PTR) Signal;

    /* Acquire the mutex. */
    if ((result = pthread_mutex_lock(&signal->mutex)) == EOK)
    {
        /* See if we have to wait for the signal. */
        if (!signal->state)
        {
            if (Wait == 0)
            {
                /* User just wants to check the signal state. */
                result = ETIMEDOUT;
            }

            else if (Wait == gcvINFINITE)
            {
                /* Wait forever. */
                result = pthread_cond_wait(&signal->cond, &signal->mutex);
            }
            else
            {
                struct timespec timeout;
                gctUINT64 nanos;

                /* Get current time. */
                if (clock_gettime(CLOCK_MONOTONIC, &timeout))
                {
                    result = 1;
                }
                else
                {
                    /* Compute absolute time. */
                    nanos  = Wait;
                    nanos *= 1000000ULL;
                    nanos += timespec2nsec(&timeout);
                    nsec2timespec(&timeout, nanos);

                    /* Wait until either the condition is set or time out. */
                    result = pthread_cond_timedwait(&signal->cond,
                                                    &signal->mutex,
                                                    &timeout);
                }
            }
        }

        /* Release the mutex. */
        if (pthread_mutex_unlock(&signal->mutex))
        {
            gcmkFOOTER_NO();
            return gcvSTATUS_GENERIC_IO;
        }
    }

    if (result == ETIMEDOUT)
    {
        /* Time out. */
        gcmkFOOTER_NO();
        return gcvSTATUS_TIMEOUT;
    }

    else if (result != 0)
    {
        /* Some other error. */
        gcmkFOOTER_NO();
        return gcvSTATUS_GENERIC_IO;
    }

    /* See if we need to reset the signal. */
    if (!signal->reset)
    {
        /* Acquire the mutex. */
        if (pthread_mutex_lock(&signal->mutex))
        {
            gcmkTRACE(gcvLEVEL_ERROR,
                     "%s(%d): pthread_mutex_lock failed (%d).",
                     __FUNCTION__, __LINE__, errno);

            /* Error. */
            gcmkFOOTER_NO();
            return gcvSTATUS_GENERIC_IO;
        }
        else
        {
            /* Clear the state. */
            signal->state = gcvFALSE;

            /* Release the mutex. */
            if (pthread_mutex_unlock(&signal->mutex))
            {
                gcmkTRACE(gcvLEVEL_ERROR,
                         "%s(%d): pthread_mutex_unlock failed (%d).",
                         __FUNCTION__, __LINE__, errno);

                /* Error. */
                gcmkFOOTER_NO();
                return gcvSTATUS_GENERIC_IO;
            }
        }
    }

    /* Success. */
    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}

/*******************************************************************************
**
**  gckOS_MapSignal
**
**  Map a signal in to the current process space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctSIGNAL Signal
**          Pointer to tha gctSIGNAL to map.
**
**      gctHANDLE Process
**          Handle of process owning the signal.
**
**  OUTPUT:
**
**      gctSIGNAL * MappedSignal
**          Pointer to a variable receiving the mapped gctSIGNAL.
*/
gceSTATUS
gckOS_MapSignal(
    IN gckOS Os,
    IN gctSIGNAL Signal,
    IN gctHANDLE Process,
    OUT gctSIGNAL * MappedSignal
    )
{
    printf("ERROR: %s Not supported.\n", __FUNCTION__);
    return gcvSTATUS_NOT_SUPPORTED;
}

/*******************************************************************************
**
**  gckOS_CreateUserSignal
**
**  Create a new signal to be used in the user space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctBOOL ManualReset
**          If set to gcvTRUE, gckOS_Signal with gcvFALSE must be called in
**          order to set the signal to nonsignaled state.
**          If set to gcvFALSE, the signal will automatically be set to
**          nonsignaled state by gckOS_WaitSignal function.
**
**  OUTPUT:
**
**      gctINT * SignalID
**          Pointer to a variable receiving the created signal's ID.
*/
gceSTATUS
gckOS_CreateUserSignal(
    IN gckOS Os,
    IN gctBOOL ManualReset,
    OUT gctINT * SignalID
    )
{
    gcmkASSERT(0);
    return gcvSTATUS_NOT_SUPPORTED;
}

/*******************************************************************************
**
**  gckOS_DestroyUserSignal
**
**  Destroy a signal to be used in the user space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctINT SignalID
**          The signal's ID.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_DestroyUserSignal(
    IN gckOS Os,
    IN gctINT SignalID
    )
{
    gcmkASSERT(0);
    return gcvSTATUS_NOT_SUPPORTED;
}

/*******************************************************************************
**
**  gckOS_WaitUserSignal
**
**  Wait for a signal used in the user mode to become signaled.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctINT SignalID
**          Signal ID.
**
**      gctUINT32 Wait
**          Number of milliseconds to wait.
**          Pass the value of gcvINFINITE for an infinite wait.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_WaitUserSignal(
    IN gckOS Os,
    IN gctINT SignalID,
    IN gctUINT32 Wait
    )
{
    gcmkASSERT(0);
    return gcvSTATUS_NOT_SUPPORTED;
}

/*******************************************************************************
**
**  gckOS_SignalUserSignal
**
**  Set a state of the specified signal to be used in the user space.
**
**  INPUT:
**
**      gckOS Os
**          Pointer to an gckOS object.
**
**      gctINT SignalID
**          SignalID.
**
**      gctBOOL State
**          If gcvTRUE, the signal will be set to signaled state.
**          If gcvFALSE, the signal will be set to nonsignaled state.
**
**  OUTPUT:
**
**      Nothing.
*/
gceSTATUS
gckOS_SignalUserSignal(
    IN gckOS Os,
    IN gctINT SignalID,
    IN gctBOOL State
    )
{
    gcmkASSERT(0);
    return gcvSTATUS_NOT_SUPPORTED;
}

gceSTATUS
gckOS_SignalQueryHardware(
    IN gckOS Os,
    IN gctSIGNAL Signal,
    OUT gckHARDWARE * Hardware
    )
{
    return gcvSTATUS_NOT_SUPPORTED;
}

gceSTATUS
gckOS_SignalSetHardware(
    IN gckOS Os,
    IN gctSIGNAL Signal,
    IN gckHARDWARE Hardware
    )
{
    return gcvSTATUS_NOT_SUPPORTED;
}

gceSTATUS
gckOS_DumpCallStack(
    IN gckOS Os
    )
{
    gcmkHEADER_ARG("Os=0x%X", Os);

    gcmkVERIFY_OBJECT(Os, gcvOBJ_OS);

    /* TODO */

    gcmkFOOTER_NO();
    return gcvSTATUS_OK;
}
gceSTATUS
gckOS_GetProcessNameByPid(
    IN gctINT Pid,
    IN gctSIZE_T Length,
    OUT gctUINT8_PTR String
    )
{
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_PrepareGPUFrequency(
    IN gckOS Os,
    IN gceCORE Core
    )
{
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_FinishGPUFrequency(
    IN gckOS Os,
    IN gceCORE Core
    )
{
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_QueryGPUFrequency(
    IN gckOS Os,
    IN gceCORE Core,
    OUT gctUINT32 * Frequency,
    OUT gctUINT8 * Scale
    )
{
    return gcvSTATUS_OK;
}

gceSTATUS
gckOS_SetGPUFrequency(
    IN gckOS Os,
    IN gceCORE Core,
    IN gctUINT8 Scale
    )
{
    return gcvSTATUS_OK;
}


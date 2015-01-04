/*
 * include/linux/hisi_ion.h
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _LINUX_HISI_ION_H
#define _LINUX_HISI_ION_H

//#include <linux/types.h>
#include <linux/ion.h>
#include <asm/ioctl.h>

//heap mask for all used type id
enum HISI_ION_HEAP_ID {
	HISI_ION_HEAP_CAMERA_ID = 1,
	HISI_ION_HEAP_GRALLOC_ID,	
	HISI_ION_HEAP_OVERLAY_ID,
	HISI_ION_HEAP_SYS_ID,
	HISI_ION_HEAP_SYS_CONTIG_ID,
	HISI_ION_HEAP_DMA_ID,	
};

//ion sync type
enum ION_MSYNC_TYPE {
	IMSYNC_DEV_TO_READ = 0,
	IMSYNC_DEV_TO_WRITE = 1,
	IMSYNC_DEV_TO_RW = 2,
	IMSYNC_BUF_TYPES_MASK = 3,
	IMSYNC_BUF_TYPES_NUM = 4,
	IMSYNC_SYNC_FOR_DEV = 0x10000,
	IMSYNC_SYNC_FOR_CPU = 0x20000,
};

struct ion_msync_data {
	enum ION_MSYNC_TYPE dir;
	int fd_buffer;
	size_t size;
	off_t offset;
};


//struct used for get phys addr of contig heap
struct ion_phys_data {
	int fd_buffer;
	unsigned long phys;
	size_t size;
};

struct ion_flush_cache_data{
	int fd_buffer;
};

#define ION_IS_CACHED(__flags) ((__flags) & ION_FLAG_CACHED)

/*struct ion_flush_data - data passed to ion for flushing caches
 *
 *@handle: handle with data to flush
 *@fd: fd to flush
 *@vaddr: userspace virtual address mapped with mmap
 *@offset: offset into the handle to flush
 *@length: length of handle to flush
 *
 *Performs cache operations on the handle. If p is the start address
 *of the handle, p + offset through p + offset + length will have
 *the cache operations performed
 */
struct ion_flush_data{
	struct ion_handle *handle;
	int fd;
	void *vaddr;
	unsigned int offset;
	unsigned int length;
};


//user command add for additional use
enum ION_HISI_CUSTOM_CMD {
	ION_HISI_CUSTOM_MSYNC,
	ION_HISI_CUSTOM_PHYS,
	ION_HISI_CUSTOM_FLUSH_CACHE
};

#define ION_IOC_HISI_MAGIC 'H'
/**
 *DOC: ION_IOC_FLUSH_ALL_CACHES - flush all the caches pf L1 and L2
 *
 *flush all the caches pf L1 and L2
 */
#define ION_IOC_FLUSH_ALL_CACHES _IOWR(ION_IOC_HISI_MAGIC, 3, \
				struct ion_flush_data)

extern unsigned long g_ion_free_size;
extern int get_cma_type(void);

#endif /* _LINUX_ION_H */

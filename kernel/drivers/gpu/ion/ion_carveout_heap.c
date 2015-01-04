/*
 * drivers/gpu/ion/ion_carveout_heap.c
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
#include <linux/spinlock.h>

#include <linux/err.h>
#include <linux/genalloc.h>
#include <linux/io.h>
#include <linux/ion.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include "ion_priv.h"

#include <asm/mach/map.h>
#include <linux/hisi_ion.h>
#include <linux/debugfs.h>
static long *g_buf;
static unsigned int g_size;
static struct gen_pool_chunk *g_chunk;
unsigned long g_ion_free_size = 0;
unsigned long g_ion_total_size = 0;


struct ion_carveout_heap {
	struct ion_heap heap;
	struct gen_pool *pool;
	ion_phys_addr_t base;
};

void get_ion_size(void)
{
	printk(KERN_ERR "g_ion_total_size:%lu \n", g_ion_total_size);
	printk(KERN_ERR "g_ion_free_size: %lu \n", g_ion_free_size);	
}

ion_phys_addr_t ion_carveout_last_allocate(struct ion_heap *heap,
				      unsigned long size,
				      unsigned long align)
{
	struct ion_carveout_heap *carveout_heap =
		container_of(heap, struct ion_carveout_heap, heap);
	unsigned long offset = gen_pool_last_alloc(carveout_heap->pool, size);

	if (!offset)
		return ION_CARVEOUT_ALLOCATE_FAIL;

	
	return offset;
}

ion_phys_addr_t ion_carveout_allocate(struct ion_heap *heap,
				      unsigned long size,
				      unsigned long align)
{
	struct ion_carveout_heap *carveout_heap =
		container_of(heap, struct ion_carveout_heap, heap);
	unsigned long offset = gen_pool_alloc(carveout_heap->pool, size);

	if (!offset)
		return ION_CARVEOUT_ALLOCATE_FAIL;
	
	return offset;
}

void ion_carveout_free(struct ion_heap *heap, ion_phys_addr_t addr,
		       unsigned long size)
{
	struct ion_carveout_heap *carveout_heap =
		container_of(heap, struct ion_carveout_heap, heap);

	if (addr == ION_CARVEOUT_ALLOCATE_FAIL)
		return;
	gen_pool_free(carveout_heap->pool, addr, size);	
	g_ion_free_size = g_ion_free_size + size;
	if(g_ion_free_size > g_ion_total_size)
	{
		g_ion_free_size = g_ion_total_size;
	}
}

static int ion_carveout_heap_phys(struct ion_heap *heap,
				  struct ion_buffer *buffer,
				  ion_phys_addr_t *addr, size_t *len)
{
	*addr = buffer->priv_phys;
	*len = buffer->size;
	return 0;
}

static int ion_carveout_heap_allocate(struct ion_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long size, unsigned long align,
				      unsigned long flags)
{
	if (buffer->flags & ION_FLAG_ALLOC_FROM_LAST) {
		buffer->priv_phys = ion_carveout_last_allocate(heap, size, align);
	} else {
		buffer->priv_phys = ion_carveout_allocate(heap, size, align);
	}
	if(buffer->priv_phys != ION_CARVEOUT_ALLOCATE_FAIL)
	{
		g_ion_free_size = g_ion_free_size - size;
	}
	return buffer->priv_phys == ION_CARVEOUT_ALLOCATE_FAIL ? -ENOMEM : 0;
}

static void ion_carveout_heap_free(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;

	ion_carveout_free(heap, buffer->priv_phys, buffer->size);
	buffer->priv_phys = ION_CARVEOUT_ALLOCATE_FAIL;	
}

struct sg_table *ion_carveout_heap_map_dma(struct ion_heap *heap,
					      struct ion_buffer *buffer)
{
	struct sg_table *table;
	int ret;

	table = kzalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table)
		return ERR_PTR(-ENOMEM);
	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret) {
		kfree(table);
		return ERR_PTR(ret);
	}
	sg_set_page(table->sgl, phys_to_page(buffer->priv_phys), buffer->size,
		    0);
	return table;
}

void ion_carveout_heap_unmap_dma(struct ion_heap *heap,
				 struct ion_buffer *buffer)
{
	sg_free_table(buffer->sg_table);
	kfree(buffer->sg_table);
}

void *ion_carveout_heap_map_kernel(struct ion_heap *heap,
				   struct ion_buffer *buffer)
{
	printk(KERN_ERR "%s: enter\n", __FUNCTION__);
	if (buffer->flags & ION_FLAG_CACHED)
		return mem_remap(buffer->priv_phys, buffer->size);
	else
		return mem_remap_nocache(buffer->priv_phys, buffer->size);
}



void ion_carveout_heap_unmap_kernel(struct ion_heap *heap,
				    struct ion_buffer *buffer)
{
	printk(KERN_ERR "%s: enter\n", __FUNCTION__);
	mem_unmap(buffer->vaddr);
	buffer->vaddr = NULL;
	return;
}

int ion_carveout_heap_map_user(struct ion_heap *heap, struct ion_buffer *buffer,
			       struct vm_area_struct *vma)
{
	if((buffer->flags  & ION_FLAG_CACHED) == 0)
	{
		vma->vm_page_prot = pgprot_writecombine(vma->vm_page_prot);
	}
		
	return remap_pfn_range(vma, vma->vm_start,
			       __phys_to_pfn(buffer->priv_phys) + vma->vm_pgoff,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}

static struct ion_heap_ops carveout_heap_ops = {
	.allocate = ion_carveout_heap_allocate,
	.free = ion_carveout_heap_free,
	.map_dma = ion_carveout_heap_map_dma,
	.unmap_dma = ion_carveout_heap_unmap_dma,
	.phys = ion_carveout_heap_phys,
	.map_user = ion_carveout_heap_map_user,
	.map_kernel = ion_carveout_heap_map_kernel,
	.unmap_kernel = ion_carveout_heap_unmap_kernel,
};

#ifdef CONFIG_DEBUG_FS

static int ion_overlay_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
	ssize_t value_ret= 0;

	memset(g_buf, 0, g_size);
	memcpy(g_buf, &(g_chunk->bits[0]), g_size);

	value_ret = simple_read_from_buffer(user_buf, count, ppos, g_buf, g_size);

	return value_ret;
}

static const struct file_operations ion_overlay_list_fops = {
	.read =     ion_overlay_read,
};
#endif

struct ion_heap *ion_carveout_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_carveout_heap *carveout_heap;

	carveout_heap = kzalloc(sizeof(struct ion_carveout_heap), GFP_KERNEL);
	if (!carveout_heap)
		return ERR_PTR(-ENOMEM);
	
	carveout_heap->pool = gen_pool_create(12, -1);
	if (!carveout_heap->pool) {
		kfree(carveout_heap);
		return ERR_PTR(-ENOMEM);
	}
	carveout_heap->base = heap_data->base;
	gen_pool_add(carveout_heap->pool, carveout_heap->base, heap_data->size,
		     -1);
	carveout_heap->heap.ops = &carveout_heap_ops;
	carveout_heap->heap.type = ION_HEAP_TYPE_CARVEOUT;

	g_ion_free_size = g_ion_free_size + heap_data->size;
	g_ion_total_size = g_ion_total_size + heap_data->size;
#ifdef CONFIG_DEBUG_FS
	if (HISI_ION_HEAP_OVERLAY_ID == heap_data->id) {
		struct list_head *_chunk;

		debugfs_create_file("ion_overlay", 0644, NULL, NULL,
				 &ion_overlay_list_fops);

		g_size = (((heap_data->size)>>12)+8-1)/8;
		g_buf = kmalloc(g_size, GFP_KERNEL);
		memset(g_buf, 0, g_size);

		read_lock(&carveout_heap->pool->lock);
		list_for_each(_chunk, &carveout_heap->pool->chunks) {
			g_chunk = list_entry(_chunk, struct gen_pool_chunk, next_chunk);    
		}
		read_unlock(&carveout_heap->pool->lock);
	}

#endif

	return &carveout_heap->heap;
}

void ion_carveout_heap_destroy(struct ion_heap *heap)
{
	struct ion_carveout_heap *carveout_heap =
	     container_of(heap, struct  ion_carveout_heap, heap);

	gen_pool_destroy(carveout_heap->pool);
	kfree(carveout_heap);
	carveout_heap = NULL;
}

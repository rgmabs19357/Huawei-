/*
 * drivers/gpu/exynos/exynos_ion.c
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
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

#include <linux/err.h>
//#include <linux/ion.h>
#include <linux/platform_device.h>
#include <linux/mm.h>
//#include <linux/cma.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/bitops.h>
#include <linux/pagemap.h>
#include <linux/dma-mapping.h>

#include <asm/pgtable.h>
#include <linux/hisi_ion.h>
#include "../ion_priv.h"

struct ion_device *k3v2_ion_device;

static int num_heaps;
static struct ion_heap **heaps;
static struct device *k3v2_ion_dev;

/* IMBUFS stands for "InterMediate BUFfer Storage" */
#define IMBUFS_SHIFT	4
#define IMBUFS_ENTRIES	(1 << IMBUFS_SHIFT)//16
#define IMBUFS_MASK	(IMBUFS_ENTRIES - 1)	/* masking lower bits *///0x0F
#define MAX_LV0IMBUFS	IMBUFS_ENTRIES//16 = number of level0 buffers, it count by pages in orders
#define MAX_LV1IMBUFS	(IMBUFS_ENTRIES + IMBUFS_ENTRIES * IMBUFS_ENTRIES)//16+16*16 = number of level1 buffers
#define MAX_IMBUFS	(MAX_LV1IMBUFS + (IMBUFS_ENTRIES << (IMBUFS_SHIFT * 2)))//16+16*16 +16<<8 = 272 + 4096 = max buffers

#define LV1IDX(lv1base)		((lv1base) >> IMBUFS_SHIFT)// phys>>4 means get the phys addr in specified oders?
#define LV2IDX1(lv2base)	((lv2base) >> (IMBUFS_SHIFT * 2))// phys>>8
#define LV2IDX2(lv2base)	(((lv2base) >> (IMBUFS_SHIFT)) & IMBUFS_MASK)// phys>>4
//orders: 12+8, 12+4, 12, 0
//what it means? buffer to be allocated least size 32k/8k/4k???
#if 0 //qijiwen
static int orders[] = {PAGE_SHIFT + 8, PAGE_SHIFT + 4, PAGE_SHIFT, 0};

//judge which InterMediate BUFfer to use according to idx(which means the pages have allocated)
static inline phys_addr_t *get_imbufs(int idx,
		phys_addr_t *lv0imbufs, phys_addr_t **lv1pimbufs,
		phys_addr_t ***lv2ppimbufs)
{
	if (idx < MAX_LV0IMBUFS) {
		return lv0imbufs;
	} else if (idx < MAX_LV1IMBUFS) {
		idx -= MAX_LV0IMBUFS;
		return lv1pimbufs[LV1IDX(idx)];
	} else if (idx < MAX_IMBUFS) {
		idx -= MAX_LV1IMBUFS;
		return lv2ppimbufs[LV2IDX1(idx)][LV2IDX2(idx)];
	}
	return NULL;
}

static inline phys_addr_t *get_imbufs_4free(int idx,
		phys_addr_t *lv0imbufs, phys_addr_t **lv1pimbufs,
		phys_addr_t ***lv2ppimbufs)
{
	if (idx < MAX_LV0IMBUFS) {
		return lv0imbufs;
	} else if (idx < MAX_LV1IMBUFS) {
		phys_addr_t *imbufs;
		idx -= MAX_LV0IMBUFS;
		imbufs = lv1pimbufs[LV1IDX(idx)];
		if (LV1IDX(idx) == 0)
			kfree(lv1pimbufs);
		return imbufs;
	} else if (idx < MAX_IMBUFS) {
		int baseidx;
		phys_addr_t *imbufs;
		baseidx = idx - MAX_LV1IMBUFS;
		imbufs = lv2ppimbufs[LV2IDX1(baseidx)][LV2IDX2(baseidx)];
		if (LV2IDX2(baseidx) == 0) {
			kfree(lv2ppimbufs[LV2IDX1(baseidx)]);
			if (LV2IDX1(baseidx) == 0)
				kfree(lv2ppimbufs);
		}
		return imbufs;

	}
	return NULL;
}

static int ion_k3v2_heap_allocate(struct ion_heap *heap,
		struct ion_buffer *buffer,
				     unsigned long size, unsigned long align,
				     unsigned long flags)
{
	int *cur_order = orders;
	int alloc_chunks;
	int ret = 0;
	phys_addr_t *im_phys_bufs;
	phys_addr_t **pim_phys_bufs = NULL;
	phys_addr_t ***ppim_phys_bufs = NULL;
	phys_addr_t *cur_bufs = NULL;
	int copied = 0;
	struct scatterlist *sgl;
	struct sg_table *sgtable;

	//分配16个im_phys_bufs
	im_phys_bufs = kzalloc(sizeof(*im_phys_bufs) * IMBUFS_ENTRIES,
				GFP_KERNEL);
	if (!im_phys_bufs)
		return -ENOMEM;

	alloc_chunks = 0;

	//size&&12+8||12+4||12||0
	//oder数组中分别为32k, 16k, 4k, 0
	//size&&0x10100为true?  order[0]
	//size&&0x10000为true?  order[1]
	//size&&0x01100为true?  order[2]
	//size&&0x00000为true?  order[3]
	while (size && *cur_order) {
		struct page *page;

		//根据要分配的size来确定oder
		//size与2^8/2^4/2^0 pages大小比较
		//64x4K/16x4K/4k
		if (size < (1 << *cur_order)) {
			cur_order++;
			continue;
		}

		//分配cur_order-PAGE_SHIFT个page页, allocate order is 8/4/0
		//which means each time 2^8/2^4/2^0 pages are allocated.
		page = alloc_pages(GFP_HIGHUSER | __GFP_COMP |
						__GFP_NOWARN | __GFP_NORETRY,
						*cur_order - PAGE_SHIFT);
		//if alloc not success, decrease the order,and do it agian.
		if (!page) {
			cur_order++;
			continue;
		}

		//for the first time, alloc_chunks=0, which means first if cond not satisfied, it goto
		//the second if cond. at this time, cur_bufs point to im_phys_bufs, then the allocate
		//page is stored in im_phys_bufs.
		if (alloc_chunks & IMBUFS_MASK) {
			cur_bufs++;
		} else if (alloc_chunks < MAX_LV0IMBUFS) {
			cur_bufs = im_phys_bufs;
		} else if (alloc_chunks < MAX_LV1IMBUFS) {
			int lv1idx = LV1IDX(alloc_chunks - MAX_LV0IMBUFS);

			if (!pim_phys_bufs) {
				pim_phys_bufs = kzalloc(
					sizeof(*pim_phys_bufs) * IMBUFS_ENTRIES,
					GFP_KERNEL);
				if (!pim_phys_bufs)
					break;
			}

			if (!pim_phys_bufs[lv1idx]) {
				pim_phys_bufs[lv1idx] = kzalloc(
					sizeof(*cur_bufs) * IMBUFS_ENTRIES,
					GFP_KERNEL);
				if (!pim_phys_bufs[lv1idx])
					break;
			}

			cur_bufs = pim_phys_bufs[lv1idx];
		} else if (alloc_chunks < MAX_IMBUFS) {
			phys_addr_t **pcur_bufs;
			int lv2base = alloc_chunks - MAX_LV1IMBUFS;

			if (!ppim_phys_bufs) {
				ppim_phys_bufs = kzalloc(
					sizeof(*ppim_phys_bufs) * IMBUFS_ENTRIES
					, GFP_KERNEL);
				if (!ppim_phys_bufs)
					break;
			}

			if (!ppim_phys_bufs[LV2IDX1(lv2base)]) {
				ppim_phys_bufs[LV2IDX1(lv2base)] = kzalloc(
					sizeof(*pcur_bufs) * IMBUFS_ENTRIES,
					GFP_KERNEL);
				if (!ppim_phys_bufs[LV2IDX1(lv2base)])
					break;
			}
			pcur_bufs = ppim_phys_bufs[LV2IDX1(lv2base)];

			if (!pcur_bufs[LV2IDX2(lv2base)]) {
				pcur_bufs[LV2IDX2(lv2base)] = kzalloc(
					sizeof(*cur_bufs) * IMBUFS_ENTRIES,
					GFP_KERNEL);
				if (!pcur_bufs[LV2IDX2(lv2base)])
					break;
			}
			cur_bufs = pcur_bufs[LV2IDX2(lv2base)];
		} else {
			break;
		}
		//change page to phys addr according to specified PAGE_SHIFT
		//when it has done, it also stored the phys page to im_phys_bufs/pim_phys_bufs/ppim_phys_bufs
		*cur_bufs = page_to_phys(page) | *cur_order;

		//size - 32k/16k/12k
		size = size - (1 << *cur_order);
		//buffer that have allocated count increase
		alloc_chunks++;
	}

	if (size) {
		ret = -ENOMEM;
		goto alloc_error;
	}

	//init a sgtable for scartterlist
	sgtable = kmalloc(sizeof(*sgtable), GFP_KERNEL);
	if (!sgtable) {
		ret = -ENOMEM;
		goto alloc_error;
	}

	//put the allocated pages to the sgtable according to how many pages alloced.
	if (sg_alloc_table(sgtable, alloc_chunks, GFP_KERNEL)) {
		ret = -ENOMEM;
		kfree(sgtable);
		goto alloc_error;
	}


	sgl = sgtable->sgl;
	//set the allocated pages to scaterllist while alloc_chunks-->0
	while (copied < alloc_chunks) {
		int i;
		//get the buffer that store the phys addr of pages.
		cur_bufs = get_imbufs(copied, im_phys_bufs, pim_phys_bufs,
								ppim_phys_bufs);
		BUG_ON(!cur_bufs);
		for (i = 0; (i < IMBUFS_ENTRIES) && cur_bufs[i]; i++) {
			phys_addr_t phys;
			int order;

			phys = cur_bufs[i];
			order = phys & ~PAGE_MASK;
			sg_set_page(sgl, phys_to_page(phys), 1 << order, 0);
			sgl = sg_next(sgl);
			copied++;
		}
	}

	buffer->priv_virt = sgtable;
	buffer->flags = flags;

alloc_error:
	alloc_chunks = (alloc_chunks + (IMBUFS_ENTRIES - 1)) & ~IMBUFS_MASK;
	while (alloc_chunks) {
		int i;
		cur_bufs = get_imbufs_4free(alloc_chunks - 1, im_phys_bufs,
				pim_phys_bufs, ppim_phys_bufs);
		if (unlikely(ret)) {
			for (i = 0; (i < IMBUFS_ENTRIES) && cur_bufs[i]; i++) {
				phys_addr_t phys;
				int gfp_order;

				phys = cur_bufs[i];
				gfp_order = (phys & ~PAGE_MASK) - PAGE_SHIFT;
				phys = phys & PAGE_MASK;
				__free_pages(phys_to_page(phys), gfp_order);
			}
		}

		kfree(cur_bufs);
		alloc_chunks -= IMBUFS_ENTRIES;
	}

	return ret;
}

static void ion_k3v2_heap_free(struct ion_buffer *buffer)
{
	struct scatterlist *sg;
	int i;
	struct sg_table *sgtable = buffer->priv_virt;

	for_each_sg(sgtable->sgl, sg, sgtable->orig_nents, i)
		__free_pages(sg_page(sg), __ffs(sg_dma_len(sg)) - PAGE_SHIFT);

	sg_free_table(sgtable);
	kfree(sgtable);
}

static struct scatterlist *ion_k3v2_heap_map_dma(struct ion_heap *heap,
					    struct ion_buffer *buffer)
{
	return ((struct sg_table *)buffer->priv_virt)->sgl;
}

static void ion_k3v2_heap_unmap_dma(struct ion_heap *heap,
			       struct ion_buffer *buffer)
{
}

static void *ion_k3v2_heap_map_kernel(struct ion_heap *heap,
				 struct ion_buffer *buffer)
{
	struct page **pages, **tmp_pages;
	struct sg_table *sgt;
	struct scatterlist *sgl;
	int num_pages = buffer->size >> PAGE_SHIFT;
	int i;
	void *vaddr;

	sgt = buffer->priv_virt;

	pages = vmalloc(sizeof(*pages) * (buffer->size >> PAGE_SHIFT));
	if (!pages)
		return NULL;

	tmp_pages = pages;
	for_each_sg(sgt->sgl, sgl, sgt->orig_nents, i) {
		struct page *page = sg_page(sgl);
		int n;

		for (n = sg_dma_len(sgl) >> PAGE_SHIFT; n > 0; n--)
			*(tmp_pages++) = page++;

	}

	vaddr = vmap(pages, num_pages, VM_USERMAP | VM_MAP, PAGE_KERNEL);

	vfree(pages);

	return vaddr + offset_in_page(sg_phys(sgt->sgl));
}

static void ion_k3v2_heap_unmap_kernel(struct ion_heap *heap,
				  struct ion_buffer *buffer)
{
	vunmap(buffer->vaddr);
}

static int ion_k3v2_heap_map_user(struct ion_heap *heap,
			struct ion_buffer *buffer, struct vm_area_struct *vma)
{
	struct sg_table *sgt = buffer->priv_virt;
	struct scatterlist *sgl;
	unsigned long pgoff;
	int i;
	unsigned long start;
	int map_pages;

	if (buffer->kmap_cnt)
		return remap_vmalloc_range(vma, buffer->vaddr, vma->vm_pgoff);

	pgoff = vma->vm_pgoff;
	start = vma->vm_start;
	map_pages = (vma->vm_end - vma->vm_start) >> PAGE_SHIFT;
	vma->vm_flags |= VM_RESERVED;

	for_each_sg(sgt->sgl, sgl, sgt->orig_nents, i) {
		unsigned long sg_pgnum = sg_dma_len(sgl) >> PAGE_SHIFT;

		if (sg_pgnum <= pgoff) {
			pgoff -= sg_pgnum;
		} else {
			struct page *page = sg_page(sgl) + pgoff;
			int i;

			sg_pgnum -= pgoff;

			for (i = 0; (map_pages > 0) && (i < sg_pgnum); i++) {
				int ret;
				ret = vm_insert_page(vma, start, page);
				if (ret)
					return ret;
				start += PAGE_SIZE;
				page++;
				map_pages--;
			}

			pgoff = 0;

			if (map_pages == 0)
				break;
		}
	}

	return 0;
}

#if 0 //qijiwen
static struct ion_heap_ops vmheap_ops = {
	.allocate = ion_k3v2_heap_allocate,
	.free = ion_k3v2_heap_free,
	.map_dma = ion_k3v2_heap_map_dma,
	.unmap_dma = ion_k3v2_heap_unmap_dma,
	.map_kernel = ion_k3v2_heap_map_kernel,
	.unmap_kernel = ion_k3v2_heap_unmap_kernel,
	.map_user = ion_k3v2_heap_map_user,
};

static struct ion_heap *ion_k3v2_heap_create(struct ion_platform_heap *unused)
{
	struct ion_heap *heap;

	heap = kzalloc(sizeof(struct ion_heap), GFP_KERNEL);
	if (!heap)
		return ERR_PTR(-ENOMEM);
	heap->ops = &vmheap_ops;
	heap->type = ION_HEAP_TYPE_K3V2;
	return heap;
}
#endif

static void ion_k3v2_heap_destroy(struct ion_heap *heap)
{
	kfree(heap);
}

static int ion_k3v2_user_heap_allocate(struct ion_heap *heap,
					   struct ion_buffer *buffer,
					   unsigned long len,
					   unsigned long align,
					   unsigned long flags)
{
	unsigned long start = align;
	size_t last_size = 0;
	struct page **pages;
	int nr_pages;
	int ret = 0, i;
	off_t start_off;
	struct sg_table *sgtable;
	struct scatterlist *sgl;

	last_size = (start + len) & ~PAGE_MASK;
	if (last_size == 0)
		last_size = PAGE_SIZE;

	start_off = offset_in_page(start);

	start = round_down(start, PAGE_SIZE);

	nr_pages = PFN_DOWN(PAGE_ALIGN(len + start_off));

	pages = kzalloc(nr_pages * sizeof(*pages), GFP_KERNEL);
	if (!pages)
		return -ENOMEM;

	ret = get_user_pages_fast(start, nr_pages,
				flags & ION_HISI_WRITE_MASK, pages);

	if (ret < 0)
		goto err_get_pages;

	if (ret != nr_pages) {
		nr_pages = ret;
		ret = -EFAULT;
		goto err_smaller_pages;
	}

	sgtable = kmalloc(sizeof(*sgtable), GFP_KERNEL);
	if (!sgtable) {
		ret = -ENOMEM;
		goto err_alloc_sgtable;
	}

	ret = sg_alloc_table(sgtable, nr_pages, GFP_KERNEL);
	if (ret)
		goto err_alloc_sglist;

	sgl = sgtable->sgl;

	sg_set_page(sgl, pages[0],
			(nr_pages == 1) ? len : PAGE_SIZE - start_off,
			start_off);

	sgl = sg_next(sgl);

	/* nr_pages == 1 if sgl == NULL here */
	for (i = 1; i < (nr_pages - 1); i++) {
		sg_set_page(sgl, pages[i], PAGE_SIZE, 0);
		sgl = sg_next(sgl);
	}

	if (sgl)
		sg_set_page(sgl, pages[i], last_size, 0);

	buffer->priv_virt = sgtable;
	buffer->flags = flags;

	kfree(pages);
	return 0;

err_alloc_sglist:
	sg_free_table(sgtable);
	kfree(sgtable);
err_alloc_sgtable:
err_smaller_pages:
	for (i = 0; i < nr_pages; i++)
		put_page(pages[i]);
err_get_pages:
	kfree(pages);

	return ret;
}

static void ion_k3v2_user_heap_free(struct ion_buffer *buffer)
{
	struct scatterlist *sg;
	int i;
	struct sg_table *sgtable = buffer->priv_virt;

	if (buffer->flags & ION_HISI_WRITE_MASK) {
		for_each_sg(sgtable->sgl, sg, sgtable->orig_nents, i) {
			set_page_dirty_lock(sg_page(sg));
			put_page(sg_page(sg));
		}
	} else {
		for_each_sg(sgtable->sgl, sg, sgtable->orig_nents, i)
			put_page(sg_page(sg));
	}

	sg_free_table(sgtable);
	kfree(sgtable);
}

static struct ion_heap_ops user_heap_ops = {
	.allocate = ion_k3v2_user_heap_allocate,
	.free = ion_k3v2_user_heap_free,
	.map_dma = ion_k3v2_heap_map_dma,
	.unmap_dma = ion_k3v2_heap_unmap_dma,
	.map_kernel = ion_k3v2_heap_map_kernel,
	.unmap_kernel = ion_k3v2_heap_unmap_kernel,
};

#if 0 //qijiwen
static struct ion_heap *ion_k3v2_user_heap_create(
					struct ion_platform_heap *unused)
{
	struct ion_heap *heap;

	heap = kzalloc(sizeof(struct ion_heap), GFP_KERNEL);
	if (!heap)
		return ERR_PTR(-ENOMEM);
	heap->ops = &user_heap_ops;
	heap->type = ION_HEAP_TYPE_K3V2_USER;
	return heap;
}
#endif

static void ion_k3v2_user_heap_destroy(struct ion_heap *heap)
{
	kfree(heap);
}

static enum dma_data_direction ion_msync_dir_table[IMSYNC_BUF_TYPES_NUM] = {
	DMA_TO_DEVICE,
	DMA_FROM_DEVICE,
	DMA_BIDIRECTIONAL,
};

static long ion_k3v2_heap_msync(struct ion_client *client,
		struct ion_handle *handle, off_t offset, size_t size, long dir)
{
	struct ion_buffer *buffer;
	struct scatterlist *sg, *tsg;
	int nents = 0;
	int ret = 0;

	buffer = ion_share(client, handle);
	if (IS_ERR(buffer))
		return PTR_ERR(buffer);

	if ((offset + size) > buffer->size)
		return -EINVAL;

	sg = ion_map_dma(client, handle);
	if (IS_ERR(sg))
		return PTR_ERR(sg);

	while (sg && (offset >= sg_dma_len(sg))) {
		offset -= sg_dma_len(sg);
		sg = sg_next(sg);
	}

	size += offset;

	if (!sg)
		goto err_buf_sync;

	tsg = sg;
	while (tsg && (size > sg_dma_len(tsg))) {
		size -= sg_dma_len(tsg);
		nents++;
		tsg = sg_next(tsg);
	}

	if (tsg && size)
		nents++;

	/* TODO: exclude offset in the first entry and remainder of the
	   last entry. */
	if (dir & IMSYNC_SYNC_FOR_CPU)
		dma_sync_sg_for_cpu(NULL, sg, nents,
			ion_msync_dir_table[dir & IMSYNC_BUF_TYPES_MASK]);
	else if (dir & IMSYNC_SYNC_FOR_DEV)
		dma_sync_sg_for_device(NULL, sg, nents,
			ion_msync_dir_table[dir & IMSYNC_BUF_TYPES_MASK]);

err_buf_sync:
	ion_unmap_dma(client, handle);
	return ret;
}
#endif

static int check_vaddr_bounds(unsigned long start, unsigned long end)
{
	struct mm_struct *mm = current->active_mm;
	struct vm_area_struct *vma;
	int ret = 1;

	if(end < start)
		goto out;

	down_read(&mm->mmap_sem);
	vma = find_vma(mm, start);
	if(vma && vma->vm_start < end){
		if(start < vma->vm_start)
			goto out_up;
		if(end > vma->vm_end)
			goto out_up;
		ret = 0;
	}
	out_up:
		up_read(&mm->mmap_sem);
	out:
		return ret;
}

static long k3v2_heap_ioctl(struct ion_client *client, unsigned int cmd,
				unsigned long arg)
{
	int ret = 0;

	switch (cmd) {
	#if 0 //qijiwen
	case ION_HISI_CUSTOM_MSYNC:
	{
		struct ion_msync_data data;
		struct ion_handle *handle;

		if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
			return -EFAULT;

		if ((data.offset + data.size) < data.offset)
			return -EINVAL;

		handle = ion_import_fd(client, data.fd_buffer);
		if (IS_ERR(handle))
		{
			ion_free(client, handle);
			return PTR_ERR(handle);
		}
		ret = ion_k3v2_heap_msync(client, handle, data.offset,
						data.size, data.dir);
		ion_free(client, handle);
		break;
	}
	#endif
	case ION_HISI_CUSTOM_PHYS:
	{
		struct ion_phys_data data;
		struct ion_handle *handle;

		if (copy_from_user(&data, (void __user *)arg,
				sizeof(data))) {
			return -EFAULT;
		}

		handle = ion_import_dma_buf(client, data.fd_buffer);

		if (IS_ERR(handle)) {
			pr_err("%s %d : handle 0x%p phy 0x%lx size 0x%x fd 0x%x\n", __FUNCTION__,
				__LINE__, handle, data.phys, data.size, data.fd_buffer);
			return PTR_ERR(handle);
		}
		ret = ion_phys(client, handle, &data.phys, &data.size);
		if (ret)
		{
			ion_free(client, handle);
			return ret;
        }
		if (copy_to_user((void __user *)arg, &data, sizeof(data)))
		{
			ion_free(client, handle);
			return -EFAULT;
		}
		ion_free(client, handle);

		break;
	}
	#if 0 //qijiwen
	case ION_HISI_CUSTOM_FLUSH_CACHE:
	{
#if 1
		int phys,vaddr, size;
		struct ion_flush_cache_data data;
		struct ion_handle *handle;
		if (copy_from_user(&data, (void __user *)arg, sizeof(data)))
			return -EFAULT;

		handle = ion_import_fd(client, data.fd_buffer);
		if (IS_ERR(handle))
		{
			ion_free(client, handle);
			return PTR_ERR(handle);
		}
#endif
		ion_flush_cache(client, handle);
		ion_free(client, handle);
		break;
	}
	#endif

        case ION_IOC_FLUSH_ALL_CACHES:
        {
            struct ion_flush_data data;
            unsigned long long start, end;
            if(copy_from_user(&data, (void __user*)arg,
                            sizeof(struct ion_flush_data)))
            return -EFAULT;

             start = (unsigned long ) data.vaddr;
             end = (unsigned long ) data.vaddr + data.length;

            if(check_vaddr_bounds(start, end)){
                pr_err("%s: virtual address %p is out of bounds\n",
                                    __func__, data.vaddr);
                return -EINVAL;
            }

            /*flush L1 cache */
            flush_all_cpu_caches();
            /*flush L2 cache*/
            outer_flush_all();
        }
        break;
	default:
		return -ENOTTY;
	}

	return ret;
}

static struct ion_heap *__ion_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_heap *heap = NULL;

	#if 0 //qijiwen
	switch (heap_data->type) {
	case ION_HEAP_TYPE_K3V2:
		heap = ion_k3v2_heap_create(heap_data);
		break;
	//case ION_HEAP_TYPE_K3V2_CONTIG:
	//	heap = ion_k3v2_contig_heap_create(heap_data);
	//	break;
	case ION_HEAP_TYPE_K3V2_USER:
		heap = ion_k3v2_user_heap_create(heap_data);
		break;
	default:
		return ion_heap_create(heap_data);
	}
	#else
	return ion_heap_create(heap_data);
	#endif

	if (IS_ERR_OR_NULL(heap)) {
		pr_err("%s: error creating heap %s type %d base %lu size %u\n",
		       __func__, heap_data->name, heap_data->type,
		       heap_data->base, heap_data->size);
		return ERR_PTR(-EINVAL);
	}

	heap->name = heap_data->name;
	heap->id = heap_data->id;

	return heap;
}

void __ion_heap_destroy(struct ion_heap *heap)
{
	if (!heap)
		return;

	#if 0 //qijiwen
	switch (heap->type) {
	case ION_HEAP_TYPE_K3V2:
		ion_k3v2_heap_destroy(heap);
		break;
	//case ION_HEAP_TYPE_K3V2_CONTIG:
	//	ion_k3v2_contig_heap_destroy(heap);
	//	break;
	case ION_HEAP_TYPE_K3V2_USER:
		ion_k3v2_user_heap_destroy(heap);
		break;
	default:
		ion_heap_destroy(heap);
	}
	#else
	ion_heap_destroy(heap);
	#endif
}

static int k3v2_ion_probe(struct platform_device *pdev)
{
	struct ion_platform_data *pdata = pdev->dev.platform_data;
	int err;
	int i;

	num_heaps = pdata->nr;

	heaps = kzalloc(sizeof(struct ion_heap *) * pdata->nr, GFP_KERNEL);
	if (!heaps)
		return -ENOMEM;

	k3v2_ion_device = ion_device_create(&k3v2_heap_ioctl);
	if (IS_ERR_OR_NULL(k3v2_ion_device)) {
		kfree(heaps);
		return PTR_ERR(k3v2_ion_device);
	}

	/* create the heaps as specified in the board file */
	for (i = 0; i < num_heaps; i++) {
		struct ion_platform_heap *heap_data = &pdata->heaps[i];

		heaps[i] = __ion_heap_create(heap_data);
		if (IS_ERR_OR_NULL(heaps[i])) {
			err = PTR_ERR(heaps[i]);
			goto err;
		}
		ion_device_add_heap(k3v2_ion_device, heaps[i]);
		pr_info("%s: adding heap %s of type %d with %lx@%x\n",
            __func__, heap_data->name, heap_data->type,
            heap_data->base, heap_data->size);
	}
	platform_set_drvdata(pdev, k3v2_ion_device);

	k3v2_ion_dev = &pdev->dev;
    printk("k3v2_ion_probe success");
	return 0;
err:
	for (i = 0; i < num_heaps; i++) {
		if (heaps[i])
			ion_heap_destroy(heaps[i]);
	}
	kfree(heaps);
	return err;
}

static int k3v2_ion_remove(struct platform_device *pdev)
{
	struct ion_device *idev = platform_get_drvdata(pdev);
	int i;

	ion_device_destroy(idev);
	for (i = 0; i < num_heaps; i++)
		__ion_heap_destroy(heaps[i]);
	kfree(heaps);
	return 0;
}

static struct platform_driver ion_driver = {
	.probe = k3v2_ion_probe,
	.remove = k3v2_ion_remove,
	.driver = { .name = "ion-k3v2" }
};

static int __init ion_init(void)
{
    printk("============ion_init\n");
    return platform_driver_register(&ion_driver);
}

static void __exit ion_exit(void)
{
    platform_driver_unregister(&ion_driver);
}

module_init(ion_init);
module_exit(ion_exit);


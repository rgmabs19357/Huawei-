/*
 * Block driver for media (i.e., flash cards)
 *
 * Copyright 2002 Hewlett-Packard Company
 * Copyright 2005-2008 Pierre Ossman
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 *
 * HEWLETT-PACKARD COMPANY MAKES NO WARRANTIES, EXPRESSED OR IMPLIED,
 * AS TO THE USEFULNESS OR CORRECTNESS OF THIS CODE OR ITS
 * FITNESS FOR ANY PARTICULAR PURPOSE.
 *
 * Many thanks to Alessandro Rubini and Jonathan Corbet!
 *
 * Author:  Andrew Christian
 *          28 May 2002
 */
#include <linux/moduleparam.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/hdreg.h>
#include <linux/kdev_t.h>
#include <linux/blkdev.h>
#include <linux/mutex.h>
#include <linux/scatterlist.h>
#include <linux/string_helpers.h>
#include <linux/delay.h>
#include <linux/capability.h>
#include <linux/compat.h>
#include <linux/time.h>
#include <linux/atomic.h>

#include <linux/mmc/core.h>
#include <linux/mmc/ioctl.h>
#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>

#include <asm/system.h>
#include <asm/uaccess.h>
#include <asm/setup.h>

#include <mach/irqs.h>

#include "queue.h"
#include <linux/mmc/mshci.h>

/*
 * There is one mmc_blk_data per slot.
 */
struct mmc_blk_data {
	spinlock_t	lock;
	struct gendisk	*disk;
	struct mmc_queue queue;
	struct list_head part;

	unsigned int	flags;
#define MMC_BLK_CMD23			(1 << 0)	/* Can do SET_BLOCK_COUNT for multiblock */
#define MMC_BLK_REL_WR			(1 << 1)	/* MMC Reliable write support */
#define MMC_BLK_PACKED_CMD	(1<<2)    /* eMMC4.5 packed command */

	unsigned int	usage;
	unsigned int	read_only;
	unsigned int	part_type;
	unsigned int	name_idx;

	/*
	 * Only set in main mmc_blk_data associated
	 * with mmc_card with mmc_set_drvdata, and keeps
	 * track of the current selected device partition.
	 */
	unsigned int	part_curr;
	struct device_attribute force_ro;
};


struct mmc_blk_request {
	struct mmc_request	mrq;
	struct mmc_command	sbc;
	struct mmc_command	cmd;
	struct mmc_command	stop;
	struct mmc_data		data;
};


int emmc_packed_block_packed_debug = 1;
int emmc_packed_block_packed_detail_debug = 0;

module_param(emmc_packed_block_packed_debug, int, 0644);
module_param(emmc_packed_block_packed_detail_debug, int, 0644);

void dump_packed_info(struct packed_cmd_info *info, struct scatterlist *sg, int sg_len) {

    int i;
	if (emmc_packed_block_packed_detail_debug) {
	    if (info->hdr->rw == PACKED_CMD_HDR_READ)
	        printk(">>>> packed read: ");
	    else
	        printk(">>>> packed write: ");

	    printk("info->packed_read_nr = %d,", info->packed_read_nr);
      	printk("info->packed_read_sectors = %d,", info->packed_read_sectors);
   	    printk("info->packed_write_nr = %d,", info->packed_write_nr);
   	    printk("info->packed_write_sectors = %d,", info->packed_write_sectors);
   	    printk("info->sg_len = %d\n", info->sg_len);

	    for (i=0; i<info->hdr->num_entries; i++) {
	   		printk("args %d, 0x%p, 0x%p\n", i, (void *)info->hdr->args[i][0],  (void *)info->hdr->args[i][1]);
  		}
	}

	if (emmc_packed_block_packed_detail_debug) {
    	struct scatterlist *entry;
	   	for_each_sg(sg, entry, sg_len, i) {
	    	printk("sg info %d: virt=0x%p, offset=%u, length=%u\n", i, page_address(sg_page(entry)), entry->offset, entry->length);
    	}
    }

}

int send_command_23(struct mmc_card *card, int arg)
{
		int err;

		struct mmc_command cmd = {0};

		cmd.opcode = MMC_SET_BLOCK_COUNT;
		cmd.arg =  arg;
		cmd.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;

		err = mmc_wait_for_cmd(card->host, &cmd, 0);

		if (err) {
			printk("send cmd23 err = %d, arg = 0x%p\n", err, (void *)arg);

		} else if (emmc_packed_block_packed_detail_debug) {
   			printk("send cmd23 send success, arg = 0x%p\n", (void *)arg);

		}

		return err;
}


int send_command_25(struct mmc_card *card, int arg, int blocks, struct scatterlist *sg, unsigned sg_len)
{
	struct mmc_blk_request brq;

	memset(&brq, 0, sizeof(brq));
	brq.mrq.cmd = &brq.cmd;
	brq.mrq.data = &brq.data;

	brq.cmd.arg = arg;
	brq.cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	brq.cmd.opcode = MMC_WRITE_MULTIPLE_BLOCK;

	brq.data.flags |= MMC_DATA_WRITE;
	brq.data.blksz = 512;
	brq.data.blocks = blocks;

	mmc_set_data_timeout(&brq.data, card);

	brq.data.sg = sg;
	brq.data.sg_len = sg_len;

	mmc_wait_for_req(card->host, &brq.mrq);

	if (brq.sbc.error || brq.cmd.error || brq.stop.error)  {
		printk("send cmd25 error\n");
		return 1;
	}

	if (brq.data.error) {
		printk("send cmd 25 data error: %d transferring data, cmd response %#x, card status %#x\n",
			brq.data.error,
			brq.cmd.resp[0], brq.stop.resp[0]);
		return brq.data.error;
	}

	return 0;
}


int send_command_18(struct mmc_card *card, int arg, int blocks, struct scatterlist *sg, unsigned sg_len)
{

	struct mmc_blk_request brq;


    memset(&brq, 0, sizeof(brq));
	brq.mrq.cmd = &brq.cmd;
	brq.mrq.data = &brq.data;

	/* cmd18 */
	brq.cmd.arg = arg; /* cmd18 start sector = start sector of first read request*/
	brq.cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_ADTC;
	brq.cmd.opcode = MMC_READ_MULTIPLE_BLOCK;

	brq.data.flags |= MMC_DATA_READ;
	brq.data.blksz = 512;
	brq.data.blocks = blocks;

	mmc_set_data_timeout(&brq.data, card);

	brq.data.sg = sg;
	brq.data.sg_len = sg_len;

	mmc_wait_for_req(card->host, &brq.mrq);

	if (brq.sbc.error || brq.cmd.error || brq.stop.error) {
		printk("send cmd18 error\n");
		return 1;
	}

	if (brq.data.error) {
		printk("send cmd18 data error: %d transferring data, cmd response %#x, card status %#x\n",
			brq.data.error,
			brq.cmd.resp[0], brq.stop.resp[0]);
		return brq.data.error;
	}

	return 0;
}

int mmc_blk_issue_packed_rw_rq(struct mmc_queue *mq, struct scatterlist *end_sg) {
	
	int err;

	struct request *req;

	struct packed_cmd_info *info = &mq->packed_cmd_info;
	struct packed_cmd_hdr *hdr = info->hdr;
	struct mmc_card *card = mq->card;
	struct mmc_blk_data *md;

	/*last packed request*/
	info->cur_sg = end_sg;

	dump_packed_info(info, mq->sg, info->sg_len+1);

	if (hdr->rw == PACKED_CMD_HDR_READ) {
		/*
	 	 *  packed read requests, cmd23->cmd25->cmd23->cmd18
		 */

		/* cmd23 set block count = 1,  represents packed command header. */
		err = send_command_23(card, 1|CMD23_ARG_PACKED);
		if (err)
		    return err;

        /* cmd25 start sector = start sector of first read request, blocks = 1*/
		err = send_command_25(card, blk_rq_pos(info->packed_read_requests[0]), 1, mq->sg, 1);
		if (err)
		    return err;

        /* cmd23 set block count = sum sectors of all read request */
		err = send_command_23(card, info->packed_read_sectors| CMD23_ARG_PACKED);
        if (err)
            return err;

        /* cmd18 start sector = start sector of first read request, blocks = all read requests blocks sum*/
        err = send_command_18(card, blk_rq_pos(info->packed_read_requests[0]), info->packed_read_sectors, sg_next(mq->sg), info->sg_len);
        if (err)
            return err;

		if (emmc_packed_block_packed_debug)
    		printk("packed read  ok, request num = %d, all sectors = %d\n", info->packed_read_nr, info->packed_read_sectors);

		/* all requests process ok, notify ok*/
		md = container_of(mq, struct mmc_blk_data, queue);
		spin_lock_irq(&md->lock);
		for_each_packed_rw_request(info, req, READ) {
			__blk_end_request(req, 0, blk_rq_bytes(req));
		}
		spin_unlock_irq(&md->lock);

	} else {
		/* cmd23 set block count = sum sectors of all writes request and 1 packed command header*/
		err = send_command_23(card, (info->packed_write_sectors+1)|CMD23_ARG_PACKED);
		if (err)
		   return err;

        /*
          cmd25
          start sector = start sector of first write request
          blocks = all write requests sum sectors + 1 (packed header)
        */
		err = send_command_25(card, blk_rq_pos(info->packed_write_requests[0]), info->packed_write_sectors+1, mq->sg, info->sg_len+1);
		if (err)
    		return err;

		if (emmc_packed_block_packed_debug)
    		printk("packed write ok, request num = %d, all sectors = %d\n", info->packed_write_nr, info->packed_write_sectors);

		/* all requests process ok, notify ok*/
		md = container_of(mq, struct mmc_blk_data, queue);
		spin_lock_irq(&md->lock);
		for_each_packed_rw_request(info, req, WRITE) {
			__blk_end_request(req, 0, blk_rq_bytes(req));
		}
		spin_unlock_irq(&md->lock);

	}

	return 0;
}


/*
    adapt to mmc core code convention. return 1 ok and return 0 error.
    if has error return 0, do_packed_rw_requests will process requests again use normal mode.
*/
int mmc_blk_issue_packed_rq(struct mmc_queue *mq, struct request *req)
{
	struct packed_cmd_info *info = &mq->packed_cmd_info;
	struct packed_cmd_hdr *hdr = info->hdr;
	struct page *page = virt_to_page(hdr);
	int nsegs;
	struct scatterlist *end_sg;


    if (emmc_packed_block_packed_detail_debug)
    	printk(">>>> mmc_blk_issue_packed_rq() sector=%lu, count=%u\n", blk_rq_pos(req), blk_rq_sectors(req));

	/*first packed request*/
	if (req->cmd_flags & REQ_PACKED_START) {
	    /* must clear packed header first or some emmc4.5 card will not work normal*/
		memset(hdr, 0, 512);

        if (emmc_packed_block_packed_detail_debug)
	    	printk("first packed request\n");

		hdr->version = 1; /* always 1 */
		hdr->rw = (rq_data_dir(req) == READ) ? PACKED_CMD_HDR_READ : PACKED_CMD_HDR_WRITE;
		hdr->num_entries = 0;

		page = virt_to_page(hdr);
		sg_set_page(mq->sg, page, PACKED_CMD_HDR_SIZE, 0);

		/*clear end sg last flag*/
		mq->sg->page_link &= ~0x02;
		info->cur_sg = mq->sg+1;
		info->sg_len = 0;
	}

	/*
 	 * arg[x][0] is cmd23 arg. request sector count
	 * arg[x][1] is cmd18/25 arg.request start sector number
  	 */
	hdr->args[hdr->num_entries][0] = blk_rq_sectors(req);
	hdr->args[hdr->num_entries][1] = blk_rq_pos(req);
	hdr->num_entries++;

	nsegs = blk_rq_map_sg(mq->queue, req, info->cur_sg);
	end_sg = sg_last(info->cur_sg, nsegs);
	if (!end_sg) {
		printk(KERN_ERR "end_sg is NULL !\n");
		return 0;
	}
	info->sg_len += nsegs;

	/*not last packed request*/
	if (!(req->cmd_flags & REQ_PACKED_END))  {
		/*clear end sg last flag*/
		end_sg->page_link &= ~0x02;
		info->cur_sg = sg_next(end_sg);
		return 1;
	}

    if (emmc_packed_block_packed_detail_debug)
    	printk("end packed request\n");

    /* end packed request, do it*/
    if (mmc_blk_issue_packed_rw_rq(mq, end_sg))
        return 0;

	return 1;
}
EXPORT_SYMBOL(mmc_blk_issue_packed_rq);

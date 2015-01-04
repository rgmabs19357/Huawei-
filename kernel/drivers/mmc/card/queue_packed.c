/*
 *  linux/drivers/mmc/card/queue.c
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright 2006-2007 Pierre Ossman
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/blkdev.h>
#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/scatterlist.h>

#include <linux/mmc/card.h>
#include <linux/mmc/host.h>
#include "queue.h"


int emmc_packed_read_enable = 1;
int emmc_packed_write_enable = 1;
int emmc_packed_queue_packed_debug = 0;
int emmc_packed_request_threshold = 5;

module_param(emmc_packed_read_enable, int, 0644);
module_param(emmc_packed_write_enable, int, 0644);
module_param(emmc_packed_queue_packed_debug, int, 0644);
module_param(emmc_packed_request_threshold, int, 0644);

void do_packed_rw_requests(struct mmc_queue *mq, int rw) {
	struct packed_cmd_info *info = &mq->packed_cmd_info;
	struct request *req;

	int error = 0;

	/* process packed command request */
	start_packed_request(info, rw)->cmd_flags |= REQ_PACKED_START;
	end_packed_request(info, rw)->cmd_flags |= REQ_PACKED_END;

	for_each_packed_rw_request(info, req, rw) {
		req->cmd_flags |= REQ_PACKED;
		mq->req = req;
		if (!mq->issue_fn(mq, req))
			error = 1;
	}

	/* if packed command request process error, process with normal flow */
	if (error) {
		printk("do_packed_rw_requests() packed process error\n");
		start_packed_request(info, rw)->cmd_flags &= ~REQ_PACKED_START;
		end_packed_request(info, rw)->cmd_flags &= ~REQ_PACKED_END;

		for_each_packed_rw_request(info, req, rw) {
    		req->cmd_flags &= ~REQ_PACKED;
			mq->req = req;
			mq->issue_fn(mq, req);
		}
	}

}



void __do_packed_requests(struct mmc_queue *mq) {

	struct packed_cmd_info *info = &mq->packed_cmd_info;
	int i;

	/* process all packed read requests */
	if (emmc_packed_read_enable && info->packed_read_nr >= MIN_PACKED_CMD_READS)
		do_packed_rw_requests(mq, READ);
	else {
		for (i=0; i<info->packed_read_nr; i++) {
			mq->req = info->packed_read_requests[i];
			mq->issue_fn(mq, info->packed_read_requests[i]);
		}
	}

	/* process all unpacked requests */
	for (i=0; i<info->unpacked_nr; i++) {
		mq->req = info->unpacked_requests[i];
		mq->issue_fn(mq, info->unpacked_requests[i]);
	}

	/* process all packed write requests */
	if (emmc_packed_write_enable && info->packed_write_nr >= MIN_PACKED_CMD_WRITES)
    	do_packed_rw_requests(mq, WRITE);
    else {
		for (i=0; i<info->packed_write_nr; i++) {
			mq->req = info->packed_write_requests[i];
			mq->issue_fn(mq, info->packed_write_requests[i]);
		}
	}
}


/*sort requests to packed read,write and unpacked requests and process*/
int do_packed_requests(struct mmc_queue *mq) {

	struct packed_cmd_info *info = &mq->packed_cmd_info;
	struct request *req;
	unsigned int max_packed_sectors = mq->queue->limits.max_hw_sectors - 1;
	int read_write_overflow = 0;

	int has_request = 0;

	if (emmc_packed_queue_packed_debug)
	    printk("do_packed_requests start, nr_sorted = %d\n", mq->queue->nr_sorted);

	info->packed_read_nr = 0;
	info->packed_write_nr = 0;
	info->unpacked_nr = 0;
	info->packed_read_sectors = 0;
	info->packed_write_sectors = 0;

	/*mmc_queue must set MMC_QUEUE_PACKED_CMD flag*/
	if (!(mq->flags & MMC_QUEUE_PACKED_CMD))
		return RET_PACKED_UNHANDLED;

	/*
	    request queue request num must reach MIN_PACKED_CMD_THRESHOLD
	*/
	if (mq->queue->nr_sorted < emmc_packed_request_threshold)
		    return RET_PACKED_UNHANDLED;


	/* bounce dma can't use packed command*/
	if (mq->bounce_buf) {
		mq->flags &= ~MMC_QUEUE_PACKED_CMD;
		return RET_PACKED_UNHANDLED;
	}

    //emmc host max request size = 1M, but request has a default soft max limit = 512K
    //so for packed requests sum size should less than 1M(max_hw_sectors = 2048)
    //one sector reservered for emmc packed command header
	max_packed_sectors = mq->queue->limits.max_hw_sectors - 1;
	read_write_overflow = 0;

    //must get request queue lock first before invode blk_fecth_request
	spin_lock_irq(mq->queue->queue_lock);

	/* get request form queue and sort to packed read, write and unpacked array */
	while ((req = blk_fetch_request(mq->queue))) {
		has_request = 1;
		if (rq_packed_read(req)) {
		    if(info->packed_read_sectors + blk_rq_sectors(req) > max_packed_sectors) {
		        read_write_overflow = 1;
                goto unpacked_request;
		    }
			info->packed_read_requests[info->packed_read_nr++] = req;
			info->packed_read_sectors += blk_rq_sectors(req);
			if (emmc_packed_queue_packed_debug)
			    printk("get a read request, sector = %lu, count = %u\n", blk_rq_pos(req), blk_rq_sectors(req));

		} else if (rq_packed_write(req)) {
		    if (info->packed_write_sectors + blk_rq_sectors(req) > max_packed_sectors){
		        read_write_overflow = 1;
                goto unpacked_request;
		    }
			info->packed_write_requests[info->packed_write_nr++] = req;
			info->packed_write_sectors += blk_rq_sectors(req);
	    	if (emmc_packed_queue_packed_debug)
    			printk("get a write request,  sector = %lu, count = %u\n", blk_rq_pos(req), blk_rq_sectors(req));

		} else {
unpacked_request:
			info->unpacked_requests[info->unpacked_nr++] = req;
			if (emmc_packed_queue_packed_debug)
			    printk("get a unpacked request, sector = %lu, count = %u\n", blk_rq_pos(req), blk_rq_sectors(req));
		}

        if (read_write_overflow){
         /*
            printk("do_packed_requests(), read write size overflow: info->packed_read_nr %d, info->packed_write_nr %d,  info->unpacked_nr %d, read sectors %d, write sectros %d\n", info->packed_read_nr, info->packed_write_nr,  info->unpacked_nr, info->packed_read_sectors, info->packed_write_sectors);
          */
            break;
         }

		/* if request reached capacity, break*/
		if (info->packed_read_nr >= info->packed_read_capacity || \
		    info->packed_write_nr >= info->packed_write_capacity || \
		    info->unpacked_nr >= MIN_PACKED_CMD_THRESHOLD) {
		    	printk("do_packed_requests(), capcity num overflow: info->packed_read_nr %d, info->packed_write_nr %d,  info->unpacked_nr %d, read sectors %d, write sectros %d\n", info->packed_read_nr, info->packed_write_nr,  info->unpacked_nr, info->packed_read_sectors, info->packed_write_sectors);
			    break;
		}
	}

    //release request queue lock
	spin_unlock_irq(mq->queue->queue_lock);

	if (!has_request) {
		return RET_PACKED_UNHANDLED;
	}

	__do_packed_requests(mq);

	return RET_PACKED_HANDLED;
}


EXPORT_SYMBOL(do_packed_requests);

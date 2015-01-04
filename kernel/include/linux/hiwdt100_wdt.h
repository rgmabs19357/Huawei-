/*
 * include/linux/ashmem.h
 *
 * Copyright 2008 Google Inc.
 * Author: Robert Love
 *
 * This file is dual licensed.  It may be redistributed and/or modified
 * under the terms of the Apache 2.0 License OR version 2 of the GNU
 * General Public License.
 */

#ifndef _LINUX_HIWDT100_WDT_H
#define _LINUX_HIWDT100_WDT_H

#include <linux/types.h>
#include <linux/clk.h>

/*hiwdt100 driver private data*/
struct hiwdt100_wdt_platform_data
{
	phys_addr_t iobase;     /*watchdog register physical address*/
	size_t size;            /*watchdog register space size*/
	unsigned int irq;       /*irq number*/
    char *clk_name;         /*clock name*/
};

int early_hiwdt100_init(phys_addr_t membase, char *clk_name);

#endif	/* _LINUX_ASHMEM_H */

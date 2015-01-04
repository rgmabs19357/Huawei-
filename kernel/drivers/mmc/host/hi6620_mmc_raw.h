/*
 * linux/drivers/mmc/host/k3v2_mmc_raw.h
 *
 * Raw k3v2 mmc controller driver
 *
 * Copyright (C) 2011 Hisilicon
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 */
typedef volatile struct _descriptor_
{
    /*Bits in IDMAC DES0 Descriptor*/
    volatile unsigned int reserved1              :  1;
    volatile unsigned int disable_interrupt      :  1;
    volatile unsigned int last_descriptor        :  1;
    volatile unsigned int first_descriptor       :  1;
    volatile unsigned int second_address_chained :  1;
    volatile unsigned int end_ring               :  1;
    volatile unsigned int reserved2              : 24;
    volatile unsigned int card_error             :  1;
    volatile unsigned int own                    :  1;
    /*Bits in IDMAC DES1 Descriptor*/
    volatile unsigned int buffer1_size           : 13;
    volatile unsigned int buffer2_size           : 13;
    volatile unsigned int reserved3              :  6;
    /*Bits in IDMAC DES2 Descriptor*/
    volatile unsigned int address_pointer1       : 32;
    /*Bits in IDMAC DES3 Descriptor*/
    volatile unsigned int address_pointer2       : 32;
}IDMA_DESCRIPTOR;


extern int raw_mmc_panic_probe(struct raw_hd_struct *rhd, int type);
extern int raw_mmc_panic_write(struct raw_hd_struct *rhd, char *buf,
		unsigned int offset, unsigned int len);
extern int raw_mmc_panic_erase(struct raw_hd_struct *rhd, unsigned int offset,
		unsigned int len);
extern int k3v2_mmc_raw_read(char *buf, sector_t start_sect, unsigned int block_nums);
extern int k3v2_mmc_raw_write(char *buf, sector_t start_sect, unsigned int block_nums);
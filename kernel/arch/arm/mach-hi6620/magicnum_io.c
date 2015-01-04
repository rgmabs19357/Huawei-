/*
 * hisilicon magicnum io for double backup sram flag, magicnum_io.c
 *
 * Author: liuhailong
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 */

#include <asm/io.h>

/*change num to magicnum and double backup sram flag*/
void magicnum_writel(unsigned long num, unsigned long addr1, unsigned long addr2) {
    unsigned long magicnum = num | (num<<8) | (num<<16) | ((0xFF-num)<<24);
    writel(magicnum, addr1);
    writel(magicnum, addr2);
}

/*change num to magicnum and double backup sram flag*/
void __magicnum_writel(unsigned long num, unsigned long addr1, unsigned long addr2) {
    unsigned long magicnum = num | (num<<8) | (num<<16) | ((0xFF-num)<<24);
    __raw_writel(magicnum, addr1);
    __raw_writel(magicnum, addr2);
}
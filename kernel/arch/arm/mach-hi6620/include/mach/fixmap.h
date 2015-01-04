#ifndef _MACH_FIXMAP_H
#define _MACH_FIXMAP_H

#include <mach/platform.h>
#include <asm/memory.h>

/*
the fix map address space :

0xf400,0000 ~ 0xff00,0000

*/

/*  */

#define REG_BASE_VIRT             (0xf4000000)

#define REG_BASE_A9PRI_VIRT       (0xF6800000) /* 0xf6800000 ~ 0xf6bfffff */

#define REG_BASE_L2CC_VIRT        (0xF6C00000) /* 0xf6c00000 ~ 0xf6cfffff */

#define REG_BASE_IOC_OFF_VIRT     (0xF7010000) /* 0xf7010000 ~ 0xf7010fff */
#define REG_BASE_SECENG_VIRT 	  (0xF7080000)

#define REG_BASE_SC_OFF_VIRT      (0xF711A000) /* 0xf711a000 ~ 0xf711bfff */

#define REG_BASE_PMCTRL_VIRT      (0xF711C000) /* 0xf711c000 ~ 0xf711cfff */

#define REG_BASE_IPF_VIRT         (0xF7340000) /* 0xf3400000 ~ 0xf3400fff */

#define REG_BASE_WD0_VIRT      (0xF7401000) /* 0xf7401000 ~ 0xf7401fff */

#define REG_BASE_TIMER0_VIRT      (0xF7405000) /* 0xf7405000 ~ 0xf7405fff */

#define REG_BASE_TIMER3_VIRT      (0xF7408000) /* 0xf7408000 ~ 0xf7408fff */

#define REG_BASE_TIMER4_VIRT      (0xF7409000) /* 0xf7409000 ~ 0xf7409fff */

#define REG_BASE_SC_ON_VIRT       (0xF7410000) /* 0xf7410000 ~ 0xf7411fff */

#define REG_BASE_IPC_NS_VIRT      (0xf7500000) /* 0xf7500000 ~ 0xf753ffff */

#define REG_BASE_SRAM_ON_VIRT     (0xF7600000) /* 0xf7600000 ~ 0xf7603fff */

#define REG_BASE_SRAM_OFF_VIRT    (0xf7700000) /* 0xf7700000 ~ 0xf773ffff */

#define REG_BASE_IOC_ON_VIRT      (0xF8001000) /* 0xf8001000 ~ 0xf8001fff */

#endif


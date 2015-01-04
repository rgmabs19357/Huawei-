/*
 * arch/arm/mach-k3v2/headsmp.S
 *
 *  Copyright (c) 2011 Hisilicon co.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>
#include <linux/init.h>
#include  <mach/pwrctrl/pwrctrl_sleepasm.h>

        .section ".text.head", "ax"
	__CPUINIT

/*
 * K3v2 specific entry point for secondary CPUs.  This provides
 * a "holding pen" into which all secondary cores are held until we're
 * ready for them to initialise.
 */
ENTRY(k3v2_secondary_startup)
	mrc	p15, 0, r0, c0, c0, 5
	and	r0, r0, #15
	adr	r4, 1f
	ldmia	r4, {r5, r6}
	sub	r4, r4, r5
	add	r6, r6, r4
pen:	ldr	r7, [r6]
	cmp	r7, r0
	bne	pen

        MOV r2, #0
        MRC p15, 0, r2, c0, c0, 5
        AND r2, r2, #0x03

        MOV r0,#8
        MUL r2,r2,r0
        LDR r0,=(ACPU_SCU_BASE)
        ADD r0,r0,#8
        LDR r1,[r0]
        MOV r3,#3
        LSL r3,r3,r2
        BIC r1,r1,r3
        STR r1,[r0]
        
	/*
	 * we've been released from the holding pen: secondary_stack
	 * should now contain the SVC stack for this core
	 */
	b	secondary_startup

1:	.long	.
	.long	pen_release

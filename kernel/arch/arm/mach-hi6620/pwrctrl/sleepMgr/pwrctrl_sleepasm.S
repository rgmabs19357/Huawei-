/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_sleepasm.s
  版 本 号   : 初稿
  作    者   : 刘永富 56193
  生成日期   : 2012年7月25日
  最近修改   :
  功能描述   : 低功耗底层模块
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月25日
    作    者   : 刘永富 56193
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  <mach/pwrctrl/pwrctrl_sleepasm.h>
#include "pwrctrl_multi_memcfg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#define _ACPU_GET_CORE_ID(r0)   \
        MOV r0, #0                  ;\
        MRC p15, 0, r0, c0, c0, 5   ;/*@ Read CPU MPIDR*/                        \
        AND r0, r0, #0x03           ;/*@ Mask off, leaving the CPU ID field*/    \

/*****************************************************************************
 函 数 名  : pwrctrl_asm_mem_copy
 功能描述  : 内存copy
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_asm_mem_copy)
        STMFD  sp!, {r0-r10, r14}

        ;/* Copy awake code to sram base addr */
        ADRL   r0, pwrctrl_asm_wake_entry
        LDR    r1, =PWRCTRL_ACPU_ASM_MEM_VADDR
        LDR    r2, =pwrctrl_asm_code_end_flag
        ADD    r2,r2,#PWRCTRL_ASM_CODE_COPY_OFFSET
CopyLoop:
        LDMIA  r0!, {r3-r10}
        STMIA  r1!, {r3-r10}
        CMP    r0,      r2
        BCC    CopyLoop

        LDMFD    sp!, {r0-r10, pc}




/*****************************************************************************
 函 数 名  : pwrctrl_arm_init
 功能描述  : ARM 的初始化(使能arm wfi 后关时钟)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_arm_init)
        STMFD   sp!, {r0-r3,r14}

        /*配置arm A9 wfi 进入低功耗状态*/
        MRC p15,0,r0,c15,c0,0
        ORR r0,r0,#1        /*enable dynamic clock gating,bit 0*/
        MCR p15,0,r0,c15,c0,0

        /*配置scu IC STANDBY BIT6, scu STANDBY BIT5*/
        LDR     r1,=ACPU_SCU_BASE
        LDR     r0,[r1]
        ORR     r0,r0,#(BIT(5)|BIT(6))
        STR     r0,[r1]

        LDMFD   sp!, {r0-r3,pc}
    .ltorg



/*****************************************************************************
 函 数 名  : pwrctrl_arm_sleep
 功能描述  : ARM 进入wfi接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_arm_sleep)
        DSB
        WFI
        MOV pc, lr
    .ltorg

/*****************************************************************************
 函 数 名  : pwrctrl_arm_dmb
 功能描述  : dmb 操作
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_arm_dmb)
        DMB
        MOV pc, lr
    .ltorg

/*****************************************************************************
 函 数 名  : pwrctrl_cache_clear
 功能描述  : cache clear(flush & invalidate)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_cache_clear)
        STMFD   sp!, {r0-r11,r14}
        /*_CORTEX_AR_ENTIRE_DATA_CACHE_OP(c14)*/
        LDMFD   sp!, {r0-r11,pc}

    .ltorg






/*****************************************************************************
 函 数 名  : pwrctrl_asm_deep_sleep_entry
 功能描述  : 休眠入口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年7月30日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_asm_deep_sleep_entry)

    STMFD   sp!, {r0 - r12, lr}

    LDR r1, =PWRCTRL_ACPU_ASM_MEM_VADDR
    ADRL r2,pwrctrl_asm_wake_entry
    ADR  r3,pwrctrl_asm_deep_sleep_entry2
    SUB r3,r3,r2
    ADD r1,r1,r3
    MOV pc,r1           /*跳转到sram执行*/

    .ltorg
pwrctrl_asm_wake_entry:
        /*w00176398 add for record boot stage*/
    	LDR     r1,=MEMORY_AXI_CORE_BOOT_STAGE_ADDR
    	MOV    r0,#0x1
    	STR     r0,[r1]
        /*查询ACPU0进入低功耗阶段刷L2CACHE标志，若未设置，则跳过刷L2CACHE*/
        LDR r0, =PWRCTRL_ACPU0_L2CACHE_FLUSH_FLAG
        LDR r1, [r0]
        LDR r2, =L2CACHE_REFSH_START
        TEQ r1, r2
        BNE no_flush

        BL flush_l2cache

no_flush:
        BL pwrctrl_asm_wake_entry2
        .ltorg


flush_l2cache:

        /*设置寄存器0xF6C007BC为0xffff，刷L2CACHE*/
        LDR r1, =PWRCTRL_ACPU0_L2CACHE_CLEAN_WAY
        LDR r2, =0xffff
        STR r2, [r1]

        /*查看寄存器是否写入*/
wait_loop1:
        LDR r1, =PWRCTRL_ACPU0_L2CACHE_CLEAN_WAY
        LDR r2, [r1]
        LDR r3, =0xffff
        TST r2, r3
        BNE wait_loop1

        /*cache_sync*/
        LDR r1, =PWRCTRL_ACPU0_L2CACHE_CACHE_SYNC
        LDR r2, =0x0
        STR r2, [r1]

        /*等待sync完成*/
wait_loop2:
        LDR r1, =PWRCTRL_ACPU0_L2CACHE_CACHE_SYNC
        LDR r2, [r1]
        TST r2, #0x1
        BNE wait_loop2

        /*设置ACPU0进入低功耗阶段标志，供MCU查询*/
        LDR r0, =PWRCTRL_ACPU0_L2CACHE_FLUSH_FLAG
        LDR r3, =L2CACHE_REFSH_DONE
        STR r3, [r0]

        B .

/*****************************************************************************
 函 数 名  : pwrctrl_asm_mmu_para_bak
 功能描述  : NA
 输入参数  : r0, bak Addr
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_asm_mmu_para_bak)
        STMFD   sp!, {r0-r11,r14}

        MRC     p15, 0, r1, c3, c0, 0   @ domain access control reg
        MRC     p15, 0, r2, c1, c0, 1   @ actlr
        MRC     p15, 0, r3, c1, c0, 0   @ ctlr
        STM     r0!, {r1-r3}

        LDMFD   sp!, {r0-r11,pc}

/*****************************************************************************
 函 数 名  : pwrctrl_asm_mmu_para_restore
 功能描述  : NA
 输入参数  : r0, bak Addr
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_asm_mmu_para_restore)
        STMFD   sp!, {r0-r11,r14}

        LDM     r0!, {r1-r3}
        MCR     p15, 0, r1, c3, c0, 0   @ domain access control reg
        MCR     p15, 0, r2, c1, c0, 1   @ actlr
        MCR     p15, 0, r3, c1, c0, 0   @ ctlr

        LDMFD   sp!, {r0-r11,pc}

/*****************************************************************************
 函 数 名  : pwrctrl_asm_cache_clean
 功能描述  : cache clean/invalid
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年8月25日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
_ARM_FUNCTION_CALLED_FROM_C(pwrctrl_asm_cache_clean)
        STMFD   sp!, {r0-r11,r14}
    /**
    now invalid and clean l1 cache, ARM defined operation
    Used Register: R0/R1/R2/R3/R4/R5/R7/R9/R10
    **/
#if 0
clean_inv_l1:                       @ cache-v7.S routine used here
        dmb                             @ ensure ordering with previous accesses
        mrc     p15, 1, r0, c0, c0, 1   @ read clidr
        ands    r3, r0, #0x7000000      @ extract loc from clidr
        mov     r3, r3, lsr #23         @ left align loc bit field
        beq     finished                @ if loc is 0, then no need to clean
        mov     r10, #0                 @ start clean at cache level 0
loop1:
        add     r2, r10, r10, lsr #1    @ work out 3x current cache level
        mov     r1, r0, lsr r2          @ extract cache type bits from clidr
        and     r1, r1, #7              @ mask bits for current cache only
        cmp     r1, #2                  @ see what cache we have at this level
        blt     skip                    @ skip if no cache, or just i-cache
        mcr     p15, 2, r10, c0, c0, 0  @ select current cache level in cssr
        isb                             @ isb to sych the new cssr&csidr
        mrc     p15, 1, r1, c0, c0, 0   @ read the new csidr
        and     r2, r1, #7              @ extract the length of the cache lines
        add     r2, r2, #4              @ add 4 (line length offset)
        ldr     r4, =0x3ff
        ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
        clz     r5, r4                  @ find bit position way size increment
        ldr     r7, =0x7fff
        ands    r7, r7, r1, lsr #13     @ extract max number of the index size
loop2:
        mov     r9, r4                  @ create working copy of max way size
loop3:
        orr     r11, r10, r9, lsl r5    @ factor way and cache number into r11
        orr     r11, r11, r7, lsl r2    @ factor index number into r11
        mcr     p15, 0, r11, c7, c14, 2 @ clean & invalidate by set/way
        subs    r9, r9, #1              @ decrement the way
        bge     loop3
        subs    r7, r7, #1              @ decrement the index
        bge     loop2
skip:
        add     r10, r10, #2            @ increment cache number
        cmp     r3, r10
        bgt     loop1
finished:
        mov     r10, #0                 @ swith back to cache level 0
        mcr     p15, 2, r10, c0, c0, 0  @ select current cache level in cssr
        dsb
        isb
#endif


        /*cache clear -- way by 4*way*/
        /*cache clear*/
        MOV   r1, #0
        MCR   p15,2,r1,c0,c0,0          /* clear the CSSELR (select L1 Dcache)*/
        ISB
        MRC   p15,1,r7,c0,c0,0          /*read CCSIDR for L1 cache parameters*/

        MOV   r3,r7                     /* extract the CCSIDR.LineSize bit field*/
        AND  r3,r3,#0x7
        ADD   r3, r3, #4
        /*extract the CCSIDR.NSETS bit field*/
        MOV     r4,r7
        LDR     r1,=0x7FFF
        AND     r4,r1,r4, LSR #13
        /*extract the CCSIDR.ASSOC bit field*/
        MOV     r5,r7
        LDR     r1,=0x3ff
        AND     r5,r1 ,r5, LSR  #3

        CMP      r5,#3                  /* Cortex-A9 optimisation (known size)*/
        CMPEQ    r3,#5
        BNE      xlabel_generic1_pd
        LDR     r1,=0x40000000
        ADD    r2, r1, r4, LSL #5
        LDR     r1,=0x80000000
        ADD    r3, r1, r4, LSL #5
        LDR     r1,=0xC0000000
        ADD    r4, r1, r4, LSL #5
        LDR    r1,=0x3FE0

    xlabel_optloop1_pd:
        MCR      p15,0,r1,c7,c14,2
        DSB
        MCR      p15,0,r2,c7,c14,2
        DSB
        MCR      p15,0,r3,c7,c14,2
        DSB
        MCR      p15,0,r4,c7,c14,2
        DSB
        SUBS     r1,r1,#0x20
        SUB      r2,r2,#0x20
        SUB      r3,r3,#0x20
        SUB      r4,r4,#0x20
        BPL      xlabel_optloop1_pd
    	ISB
        DSB
    xlabel_generic1_pd:
        CLZ r6, r5                  /* r6 is the bit position of the way size*/
                                    /* increment */

        mov     r0, #0
        mcr     p15, 0, r0, c7, c1, 0   @ ICIALLUIS
        mcr     p15, 0, r0, c7, c1, 6   @ BPIALLIS
        mcr     p15, 0, r0, c8, c3, 0

        /***
        After clean and invalid cache, we need disable
        D-Cache immediately
        ***/

        /* now Clean and Invalid D-Cache, and Disable Cache */
        mov     r0, #0
        mcr     p15, 0, r0, c7, c5, 4   @ Flush prefetch buffer
        mcr     p15, 0, r0, c7, c5, 6   @ Invalidate branch predictor array
        mcr     p15, 0, r0, c8, c5, 0   @ Invalidate instruction TLB
        mcr     p15, 0, r0, c8, c6, 0   @ Invalidate data TLB
        /*BTAC Flush*/
        MCR     p15, 0, r7, c7, c5, 6
        DSB
        ISB

        mov r0, #0
        mcr p15, 0, r0, c1, c0, 1       @ A9 exit coherency now

        _ACPU_GET_CORE_ID(r2)
        MOV r0,#8
        MUL r2,r2,r0

        LDR r0,=(ACPU_SCU_BASE)
        ADD r0,r0,#8        
        LDR r1,[r0]
        MOV r3,#3
        LSL r3,r3,r2
        ORR r1,r1,r3      
        STR r1,[r0]        

        DSB
        ISB

        MOV   r0, #0
        MRC   p15, 0, r0, c1, c0, 0
        BIC   r0, r0, #(0x1<<12)        /* */
        BIC   r0, r0, #(0x1<<11)        /* */
        BIC   r0, r0, #(0x1<<2)         /* Data Cache Disable  */
        MCR   p15, 0, r0, c1, c0, 0

        LDMFD   sp!, {r0-r11,pc}


/*****************************************************************************
 函 数 名  : pwrctrl_asm_deep_sleep_entry2
 功能描述  : 休眠入口2
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
pwrctrl_asm_deep_sleep_entry2:

        /*w00176398 add for record boot stage*/
    	LDR     r1,=MEMORY_AXI_CORE_BOOT_STAGE_ADDR
    	MOV    r0,#0x6
    	STR     r0,[r1]

        /*debug flg*/
        LDR    r0,=PWRCTRL_ACPU_ASM_DEBUG_FLAG_VA
        LDR    r1, [r0]
        LDR    r0,=PWRCTRL_ACPU_DLOOP_SLEEP
        CMP    r0, r1
        BEQ    .

        _ACPU_GET_CORE_ID(r0)
        LDR     r1, =PWRCTRL_ASM_CORE_AREA_OFFSET
        MUL     r0, r1, r0
        LDR     r1, =PWRCTRL_ACPU_ASM_D_C0_MMU_PARA_VA
        ADD     r0, r0, r1
        BL      pwrctrl_asm_mmu_para_bak

        BL      pwrctrl_asm_cache_clean

        /* disable mmu :bic bit 0 */
        MRC     p15, 0, r0, c1, c0, 0
        BIC     r0, r0, #0x01
        MCR     p15, 0, r0, c1, c0, 0

        NOP
        NOP
        NOP

        /*debug flg*/
        LDR    r0,=PWRCTRL_ACPU_ASM_DEBUG_FLAG_ADDR
        LDR    r1, [r0]
        LDR    r0,=PWRCTRL_ACPU_DLOOP_SLEEP_MMU_DIS
        CMP    r0, r1
        BEQ    .

        /* backup arm regiest*/
        /*保存AARM寄存器到SRAM*/
        _ACPU_GET_CORE_ID(r0)
        LDR     r1, =PWRCTRL_ASM_CORE_AREA_OFFSET
        MUL     r0, r1, r0
        LDR     r1, =PWRCTRL_ACPU_ASM_D_ARM_PARA_AD
        ADD     r0, r0, r1
#if 0
        _ACPU_GET_CORE_ID(r0)
        CMP     r0, #0
        BEQ    master_core_reg_bakup
#endif
        /*save sp*/
        SUB     r0,r0,#4
        STR     sp,[r0]
        ADD     r0, r0, #4
master_core_reg_bakup:
        ADD     r0,r0,#0x04
        STMIA   r0!,{r1-r12}

       /*save svc mode registers*/
       /*enter svc mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_SVC32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        MRS r1,spsr
        STMIA r0!,{r1,r13,r14}

       /*save firq mode registers*/
       /*enter firq mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_FIQ32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        MRS r1,spsr
        STMIA r0!,{r1,r8-r14}



       /*save irq mode registers*/
       /*enter irq mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_IRQ32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        MRS r1,spsr
        STMIA r0!,{r1,r13,r14}

       /*save undefine mode registers*/
       /*enter undefine mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_UNDEF32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        MRS r1,spsr
        STMIA r0!,{r1,r13,r14}

       /*save abort mode registers*/
       /*enter abort mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_ABORT32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        MRS r1,spsr
        STMIA r0!,{r1,r13,r14}

       /*save system mode registers*/
       /*enter system mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_SYSTEM32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        MRS r1,spsr
        STMIA r0!,{r13,r14}

        ;/* save co-cpu register ??*/
        MRC    p15, 2, r1, c0, c0, 0
        MRC    p15, 0, r2, c1, c0, 1
        MRC    p15, 0, r3, c1, c0, 0
        MRC    p15, 0, r4, c1, c0, 2
        MRC    p15, 0, r5, c2, c1, 0
        STMIA   r0!, {r1-r5}

        MRC     p15,0,r5,c1,c1,1    /*SDER*/
        MRC     p15,0,r6,c1,c1,2    /*NSACR*/
        MRC     p15,0,r7,c12,c0,1   /*MVBAR*/
        STMIA   r0!, {r5-r7}

        MRC     p15,0,r5,c2,c0,0      /*TTBR0*/
        MRC     p15,0,r6,c2,c0,1      /*TTBR1*/
        MRC     p15,0,r7,c2,c0,2      /*TTBCR*/
        STMIA   r0!, {r5-r7}

        MRC     p15,0,r4,c3,c0,0      /*DACR*/
        MRC     p15,0,r5,c7,c4,0      /*PAR*/
        MRC     p15,0,r6,c10,c2,0     /*PRRR*/
        MRC     p15,0,r7,c10,c2,1     /*NMRR*/
        STMIA   r0!, {r4-r7}

        ;/*back to SVC mode , no interupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_SVC32 |I_BIT |F_BIT
        MSR cpsr_c, r2

        ;/*save current addr in*/
        MOV     r2,r0
        _ACPU_GET_CORE_ID(r0)
        LDR     r1, =PWRCTRL_ASM_CORE_AREA_OFFSET
        MUL     r0, r1, r0
        LDR     r1, =PWRCTRL_ACPU_ASM_D_ARM_PARA_AD
        ADD     r0, r0, r1
        STR     r2,[r0]

        /*slave core go wfi,wait pwr down*/
        _ACPU_GET_CORE_ID(r0)
        CMP     r0, #0
        BNE     wfi_entry


        /*屏蔽GIC中断*/
        /*配置ACPU寄存器屏蔽所有中断*/
        LDR r1,=ACPU_GIC_ICDDCR
        LDR r2,=0
        STR r2,[r1]

        LDR r1,=ACPU_GIC_ICDICER
        LDR r2,=0xFFFFFFFF
        STR r2,[r1]
        STR r2,[r1,#0x04]
        STR r2,[r1,#0x08]
        STR r2,[r1,#0x0C]
        STR r2,[r1,#0x10]

        LDR r1,=ACPU_GIC_ICCICR
        LDR r2,[r1,#0x0c]
        STR r2,[r1,#0x10]

        /*master core: send ipc*/
        /*写IPC发中断给MCU,只将相应的中断位置1*/
        LDR     r2, = PWRCTRL_ACPU_PD_IPC_REG
        LDR     r1, [r2]
        ORR     r1, r1, #PWRCTRL_ACPU_PD_IPC_BIT
        STR     r1,[r2]

wfi_entry:
        /*记录 wfi COUNT*/
        _ACPU_GET_CORE_ID(r0)
        LDR     r1,=EXCH_ACPU_CORE_INFO_OFFSET
        MUL     r0,r1,r0
        LDR     r1,=EXCH_ACPU_CORE_PWC_ASM_ADDR
        LDR     r1,[r1]
        ADD     r0, r1, r0

        LDR     r1,[r0,#0x20]
        ADD     r1,r1,#0x1
        STR     r1,[r0,#0x20]
        ;/*记录 wfi 时间*/
        LDR     r1, =PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR
        LDR     r1, [r1]
        LDR     r1, [r1]
        STR     r1, [r0,#0x24]

	 LDR r1,=ACPU_GIC_ICCICR
        LDR r2,=0
        STR r2,[r1]

        LDR r1,=ACPU_GIC_ICDDCR
        LDR r2,=0
        STR r2,[r1,#0x80]
        /*w00176398 add for record boot stage*/
    	LDR     r1,=MEMORY_AXI_CORE_BOOT_STAGE_ADDR
    	MOV    r0,#0x7
    	STR     r0,[r1]
        DSB
wfi_loop:
        WFI
	B wfi_loop

        /*DARK HOLE*/
        /*记录 WFI COUNT*/
        /*LDR     r1,=EXCH_ACPU_CORE_INFO_OFFSET
        MUL     r0,r1,r7
        LDR     r1,=EXCH_ACPU_CORE_PWC_ASM_ADDR
        LDR     r1,[r1]
        ADD     r0, r1, r0*/

        LDR     r1,[r0,#0x28]
        ADD     r1,r1,#0x1
        STR     r1,[r0,#0x28]
        ;/*记录 WFI RETURN 时间*/
        LDR     r1, =PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR
        LDR     r1, [r1]
        LDR     r1, [r1]
        STR     r1, [r0,#0x2c]

        /*RETURE WAKE UP*/
        B       pwrctrl_asm_wake_entry2

        .ltorg



/*****************************************************************************
 函 数 名  : pwrctrl_asm_wake_entry2
 功能描述  : 唤醒入口2
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无

 修改历史      :
  1.日    期   : 2012年8月23日
    作    者   : 刘永富 56193
    修改内容   : 新生成函数

*****************************************************************************/
pwrctrl_asm_wake_entry2:

        MOV    r3,pc
        LDR    r2,=0x0000FFFF
        AND    r3,r3,r2
        LDR    r0,=PWRCTRL_ACPU_ASM_SPACE_ADDR
        LDR    r1,=0xFFFF0000
        AND    r0,r1,r0
        ORR    r3,r3,r0

        ADRL   r2,pwrctrl_asm_wake_entry2
        ADRL   r1,pwrctrl_asm_wake_entry3
        SUB    r1,r1,r2
        ADD    r3,r1,r3

        MOV    pc,r3                    /*jump to sram_on*/

pwrctrl_asm_wake_entry3:
        NOP
        NOP
        NOP
        NOP

        _ACPU_GET_CORE_ID(r0)
        CMP     r0, #0
        BNE    cache_invalid
        
        /*配置scu invalidate duplicate tag ram*/
        LDR     r1,=ACPU_SCU_BASE
        LDR     r0,[r1,#0xc]
        LDR     r4,=0xffff
        ORR     r0,r0,r4
        STR     r0,[r1,#0xc]

cache_invalid:
        mov     r0, #0                  /* set up for MCR */
        /*BTAC Invalide*/
        MCR  p15, 0, r0, c7, c5, 6
        ISB
        DSB

        /*
    	 * disable MMU stuff and caches
    	 */
    	mrc     p15, 0, r0, c1, c0, 0
    	bic     r0, r0, #0x00002000     /* clear bits 13 (--V-) */
    	bic     r0, r0, #0x00001000     /* clear bits 12 (--I$-) */
    	bic     r0, r0, #0x00000007     /* clear bits 2:0 (-CAM) */
    	orr     r0, r0, #0x00000002     /* set bit 1 (--A-) Align */
    	orr     r0, r0, #0x00000800     /* set bit 12 (Z---) BTB */
    	mcr     p15, 0, r0, c1, c0, 0

        /********************* Invalid L1-Cache start*****************/
        mov     r0, #0                  /* set up for MCR */
        mcr     p15, 0, r0, c7, c5, 0   /* invalidate icache */

        /*copy form ccore start*/
        /*cache invalide --  by 4*way pararel*/
        /*cache invalider*/
        MOV   r1, #0
        MCR   p15,2,r1,c0,c0,0          /* clear the CSSELR (select L1 Dcache)*/
        ISB
        MRC   p15,1,r7,c0,c0,0          /*read CCSIDR for L1 cache parameters*/

        MOV   r3,r7                     /* extract the CCSIDR.LineSize bit field*/
        AND  r3,r3,#0x7
        ADD   r3, r3, #4
        /*extract the CCSIDR.NSETS bit field*/
        MOV     r4,r7
        LDR     r1,=0x7FFF
        AND     r4,r1,r4, LSR #13
        /*extract the CCSIDR.ASSOC bit field*/
        MOV     r5,r7
        LDR     r1,=0x3ff
        AND     r5,r1 ,r5, LSR  #3

        CMP      r5,#3                  /* Cortex-A9 optimisation (known size)*/
        CMPEQ    r3,#5
        BNE      xlabel_generic1
        LDR     r1,=0x40000000
        ADD    r2, r1, r4, LSL #5
        LDR     r1,=0x80000000
        ADD    r3, r1, r4, LSL #5
        LDR     r1,=0xC0000000
        ADD    r4, r1, r4, LSL #5
        LDR    r1,=0x3FE0

    xlabel_optloop1:
        MCR      p15,0,r1,c7,c6,2
        DSB
        MCR      p15,0,r2,c7,c6,2
        DSB
        MCR      p15,0,r3,c7,c6,2
        DSB
        MCR      p15,0,r4,c7,c6,2
        DSB
        SUBS     r1,r1,#0x20
        SUB      r2,r2,#0x20
        SUB      r3,r3,#0x20
        SUB      r4,r4,#0x20
        BPL      xlabel_optloop1
    	ISB
        DSB
    xlabel_generic1:
        CLZ r6, r5                      /* r6 is the bit position of the way size*/
                                        /* increment */

         mov     r0, #0                 /* set up for MCR */
         mcr     p15, 0, r0, c8, c7, 0  /* invalidate TLBs */
#if 0
         mcr     p15, 0, r0, c8, c3, 0  /* invalidate unify TLB inner share */
         mcr     p15, 0, r0, c8, c5, 0  /* invalidate I$ TLBs */
         mcr     p15, 0, r0, c8, c6, 0  /* invalidate D$ TLBs */
#endif

#if 0

        mov     r3,#0x0
        mcr     p15, 2, r3, c0, c0, 0    @select L1 Data-cache
        mrc     p15, 1, r3, c0, c0, 0    @Read Current Cache Size Identification Register

        ldr     r1,=0x1ff
        and     r3, r1, r3, LSR #13      @r3 = number of sets in cache
        mov     r0,#0x0
way_loop:
        mov     r1, #0x0                 @r1 -> set counter
set_loop:
        mov     r2, r0, LSL #30
        orr     r2, r1, LSL #5           @r2->set/way cache-op format
        mcr     p15, 0, r2, c7, c6, 2    @Invalid Line descript by r2
        add     r1, r1, #1               @increment set counter

        cmp     r1, r3                   @check if last set is reached...
        ble     set_loop                 @if not continue set_loop
        add     r0,r0, #1                @else increment way counter

        cmp     r0,#4                    @check if last way is reached
        blt     way_loop                 @if not,continue way_loop

        DSB
        ISB
#endif
        /********************* Invalid L1-Cache end*****************/

#if 1
    	/* enable L1/L2 Prefetch in ACTRL, for each CPU */
    	/*
    	mrc	p15, 0, r0, c1, c0, 1
    	ORR	r0,r0,#0x6
    	mcr	p15, 0, r0, c1, c0, 1
    	*/

    	/* enable dynamic clock gating & set max_clk_latency */
    	mrc     p15, 0, r0, c15, c0, 0
    	/*bic     r0, r0, #0x00000700*/     /* clear bits 8:10 (max_clk_latency) */
    	orr     r0, r0, #0x00000001     /* set bit 1 dynamic clock gating */
    	mcr     p15, 0, r0, c15, c0, 0
#endif

        _ACPU_GET_CORE_ID(r0)
        CMP     r0, #0
        BEQ    register_resume

        /* save cpu id */
        MOv     r2, r0

    	/* Set GIC */
    	/* Get the address of the GIC */
    	MRC		p15, 4,	r0, c15, c0, 0	@Read periph base address      (see DE593076)
    	ADD		r0, r0,	#0x1000		@Add GIC offset	to base	address
#if 0
    	/* Enable the GIC */
    	LDR		r1, [r0]		@ Read the GICs Enable	Register  (ICDDCR)
    	ORR		r1, r1,	#0x03		@ Set bit 0, the enable	bit
    	STR		r1, [r0]		@ Read the GICs Enable	Register  (ICDDCR)
#endif
    	/* set sec or not*/
    	LDR		r1, [r0]		@ Read the GICs security settings Register  (ICPISR)
	LDR		r1, =0x0
    	STR		r1, [r0, #0x80]		@ Write the GICs security	Register  (ICPISR)

    	/* Enable interrupt source 0->15 */
    	LDR		r1, =0x0000FFFF		@ Load mask
    	STR		r1, [r0, #0x100]	@ Write	enable set register

    	/* Set priority	of interrupt source 0->16 to 0x0 (highest priority) */
    	MOV		r1, #0x00
    	STR		r1, [r0, #0x400]	@ Sources 00-03
    	STR		r1, [r0, #0x404]	@ Sources 04-07
    	STR		r1, [r0, #0x408]	@ Sources 08-11
    	STR		r1, [r0, #0x40C]	@ Sources 12-15

    	/* Enable the Processor	Interface */
    	MRC		p15, 4,	r0, c15, c0, 0	@ Re-Read periph base address
    	LDR		r1, [r0, #0x100]	@ Read the Processor Interface Control register
    	ORR		r1, r1,	#0x3		@ Bit 0: Enables secure	interrupts, Bit	1: Enables Non-Secure interrupts
	MOV 		r1, #0x3
    	STR		r1, [r0, #0x100]	@ Write	the Processor Interface	Control	register

    	/* Set the Processor's Priority	Mask */
    	MOV		r1, #0x1F
    	STR		r1, [r0, #0x0104]	@ Write	the Priority Mask register
    	/*w00176398 add for record boot stage*/
    	LDR     r1,=MEMORY_AXI_CORE_BOOT_STAGE_ADDR
    	MOV    r0,#0x2
    	STR     r0,[r1]
wfi_wait:
        /* WFI */
    	NOP
    	NOP
    	NOP


register_resume:

        /*debug flg*/
        LDR    r0,=PWRCTRL_ACPU_ASM_DEBUG_FLAG_ADDR
        LDR    r1, [r0]
        LDR    r0,=PWRCTRL_ACPU_DLOOP_WAKE
        CMP    r0, r1
        BEQ    .

        _ACPU_GET_CORE_ID(r0)
        LDR     r1,=EXCH_ACPU_CORE_INFO_OFFSET
        MUL     r0,r1,r0
        LDR     r1,=EXCH_ACPU_CORE_PWC_ASM_ADDR
        LDR     r1,[r1]
        ADD     r0, r1, r0

        ;/*记录 唤醒时间*/
        LDR     r1, =PWRCTRL_ACPU_ASM_SLICE_BAK_ADDR
        LDR     r1, [r1]
        LDR     r1, [r1]
        STR     r1, [r0,#0x18]

        /*restore arm*/
        /*恢复ARM寄存器*/
        _ACPU_GET_CORE_ID(r0)
        LDR     r1, =PWRCTRL_ASM_CORE_AREA_OFFSET
        MUL     r0, r1, r0
        LDR     r1, =PWRCTRL_ACPU_ASM_D_ARM_PARA_AD
        ADD     r0, r0, r1
#if 0
        _ACPU_GET_CORE_ID(r0)
        CMP     r0, #0
        BEQ    master_core_restore
#endif
        /*restore sp*/
        SUB     r0, r0, #4
        LDR     sp,[r0]
        ADD     r0, r0, #4
master_core_restore:

        LDR     r0,[r0]

        LDMDB   r0!, {r4-r7}
        MCR     p15,0,r4,c3,c0,0   /*DACR*/
        MCR     p15,0,r5,c7,c4,0   /*PAR*/
        MCR     p15,0,r6,c10,c2,0  /*PRRR*/
        MCR     p15,0,r7,c10,c2,1  /*NMRR*/

        LDMDB   r0!, {r5-r7}
        MCR     p15,0,r5,c2,c0,0   /*TTBR0*/
        MCR     p15,0,r6,c2,c0,1   /*TTBR1*/
        MCR     p15,0,r7,c2,c0,2   /*TTBCR*/

        LDMDB   r0!, {r5-r7}       /*SCR.NS bit (r4) clear from MMU_SAVE*/
        MCR     p15,0,r5,c1,c1,1   /*SDER*/
        MCR     p15,0,r6,c1,c1,2   /*NSACR*/
        MCR     p15,0,r7,c12,c0,1  /* MVBAR*/

        MOV    r5,r0/*save r0*/
        _ACPU_GET_CORE_ID(r0)
        CMP     r0, #0
        BEQ    master_core_continue

secondary_jmp:
        _ACPU_GET_CORE_ID(r2)
        MOV r0,#8
        MUL r2,r2,r0

        LDR r0,=(ACPU_SCU_BASE)
        ADD r0,r0,#8
        LDR r1,[r0]
        MOV r3,#3
        LSL r3,r3,r2
        BIC r1,r1,r3
        STR r1,[r0]
        
        /*MMU enalbe*/
        _ACPU_GET_CORE_ID(r0)
        LDR     r1, =PWRCTRL_ASM_CORE_AREA_OFFSET
        MUL     r0, r1, r0
        LDR     r1, =PWRCTRL_ACPU_ASM_D_C0_MMU_PARA_AD
        ADD     r0, r0, r1

        LDM     r0!, {r1-r3}
        MCR     p15, 0, r1, c3, c0, 0   @ domain access control reg
    	ORR	    r2,r2,#0x6  /*enable pli pld*/
        MCR     p15, 0, r2, c1, c0, 1   @ actlr
        MCR     p15, 0, r3, c1, c0, 0   @ ctlr
        /*w00176398 add for record boot stage*/
    	LDR     r1,=MEMORY_AXI_CORE_BOOT_STAGE_ADDR
    	MOV    r0,#0x3
    	STR     r0,[r1]

    	LDR		r1, =MEMORY_AXI_SEC_CORE_BOOT_ADDR
    	LDR     pc, [r1]

master_core_continue:
        MOV     r0,r5/*restore r0*/
        ;/* Resume co-cpu register */
        LDMDB   r0!, {r1-r5}
        MCR     p15, 2, r1, c0, c0, 0
        ISB
        MCR     p15, 0, r2, c1, c0, 1
        ISB
        MCR     p15, 0, r3, c1, c0, 0
        ISB
        MCR     p15, 0, r4, c1, c0, 2
        ISB
        MCR     p15, 0, r5, c2, c1, 0
        ISB

       /*resume system mode registers*/
       /*enter system mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_SYSTEM32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        LDMDB r0!,{r13,r14}

       /*resume abort mode registers*/
       /*enter abort mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_ABORT32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        LDMDB r0!,{r1,r13,r14}
        MSR spsr_cxsf,r1

       /*resume undefine  mode registers*/
       /*enter undefine mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_UNDEF32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        LDMDB r0!,{r1,r13,r14}
        MSR spsr_cxsf,r1

       /*resume irq  mode registers*/
       /*enter irq mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_IRQ32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        LDMDB r0!,{r1,r13,r14}
        MSR spsr_cxsf,r1

       /*resume fiq  mode registers*/
       /*enter fiq mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_FIQ32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        LDMDB r0!,{r1,r8-r14}
        MSR spsr_cxsf,r1

       /*resume svc  mode registers*/
       /*enter svc mode no interrupts*/
        MRS r2,cpsr
        BIC r2,r2,#MODE_MASK
        ORR r2,r2, #MODE_SVC32 |I_BIT |F_BIT
        MSR cpsr_c, r2
        LDMDB r0!,{r1,r13,r14}
        MSR spsr_cxsf,r1
        LDMDB r0!,{r1-r12}


        /*配置arm A9 wfi 进入低功耗状态*/
        MRC p15,0,r0,c15,c0,0
        ORR r0,r0,#1          /*enable dynamic clock gating,bit 0*/
        MCR p15,0,r0,c15,c0,0

        /*配置IC STANDBY BIT6, scu STANDBY BIT5*/
        LDR r0, =ACPU_SCU_BASE
        LDR r1,[r0]
        ORR r1,r1,#(0x3<<5)
        STR r1,[r0]


        /*MMU enalbe*/
        _ACPU_GET_CORE_ID(r0)
        LDR     r1, =PWRCTRL_ASM_CORE_AREA_OFFSET
        MUL     r0, r1, r0
        LDR     r1, =PWRCTRL_ACPU_ASM_D_C0_MMU_PARA_AD
        ADD     r0, r0, r1

        /*BL      pwrctrl_asm_mmu_para_restore*/   /*sp(r13) not ready*/
        LDM     r0!, {r1-r3}
        MCR     p15, 0, r1, c3, c0, 0   @ domain access control reg
        MCR     p15, 0, r2, c1, c0, 1   @ actlr
        MCR     p15, 0, r3, c1, c0, 0   @ ctlr

        NOP
        LDMFD   sp!, {r0 -r12, pc}      /*return to C*/



/***************************************************************************/
        LDR    r0,=PWRCTRL_ASM_LINK_MAGIC1
        LDR    r1,=PWRCTRL_ASM_LINK_MAGIC2

    .ltorg

/*asm end flg*/
pwrctrl_asm_code_end_flag:



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

1:	.long	.
	.long	pen_release


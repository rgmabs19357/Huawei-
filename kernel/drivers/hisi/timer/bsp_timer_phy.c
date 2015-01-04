/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : BSP_TIMER_PHY.c
  版 本 号   : 初稿
  作    者   : 蔡喜 220237
  生成日期   : 2013年3月30日
  最近修改   :
  功能描述   : 提供Timer寄存器控制功能
  函数列表   :
              timer_32bit_count_set
              timer_input_clk_get
              timer_int_clear
              timer_int_mask
              timer_int_status_get
              timer_int_unmask
              timer_load_get
              timer_load_set
              timer_raw_int_status_get
              timer_start
              timer_stop
              timer_sys_ctrl_set
              timer_value_get
              timer_is_running
  修改历史   :
  1.日    期   : 2013年3月30日
    作    者   : 蔡喜 220237
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "soc_baseaddr_interface.h"
#include "soc_timer_interface.h"
#include "DrvInterface.h"
#include "bsp_timer_phy.h"
#include <linux/spinlock.h>
#include "bsp_ao_sctrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 全局变量定义 
*****************************************************************************/
 /*对timer控制寄存器的使能位读写互斥保护*/
extern spinlock_t timer_en_lock;

/* 划分到A核的所有Timer的基地址 */
BSP_U32 pulTimerBase[TIMER_TOTAL_NUM + CCORE_TIMER_EXP] = {0};

#ifdef _DRV_LLT_
SOC_TIMER_TIMERN_CONTROL_UNION   g_SOC_TIMER_TIMERN_CONTROL_UNION;
SOC_TIMER_TIMERN_INTCLR_UNION   g_SOC_TIMER_TIMERN_INTCLR_UNION;
SOC_TIMER_TIMERN_RIS_UNION   g_SOC_TIMER_TIMERN_RIS_UNION;
SOC_TIMER_TIMERN_MIS_UNION   g_SOC_TIMER_TIMERN_MIS_UNION;
BSP_U32 g_SCtrl_TIMER_EN1_REG;
BSP_U32 g_SCtrl_TIMER_EN0_REG;
#define SOC_SCTRL_SC_TIMER_EN1_ADDR(base)  &g_SCtrl_TIMER_EN1_REG
#define SOC_SCTRL_SC_TIMER_EN0_ADDR(base)  &g_SCtrl_TIMER_EN0_REG
#define TIMER_MIS_REG(base)    (&g_SOC_TIMER_TIMERN_MIS_UNION)
#define TIMER_RIS_REG(base)    (&g_SOC_TIMER_TIMERN_RIS_UNION)
#define TIMER_INTC_REG(base)    (&g_SOC_TIMER_TIMERN_INTCLR_UNION)
#endif



/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : timer_find_phy_id
 功能描述  : 根据传入的逻辑timer ID, 转换为物理timer ID, 该物理ID为该核能访问的有效timer ID
 输入参数  : ucTimerId        Timer ID
 输出参数  : 无
 返 回 值  :   成功:返回相应的物理timerID
                          失败:返回-1
 调用函数  :
 被调函数  :

*****************************************************************************/
BSP_S32 timer_find_phy_id (BSP_U8 timerID)
{
    BSP_S32 ret = 0;
    switch (timerID)
    {
        case TIMER_ACPU_SYSTEM_ID:
            ret = TIMER_ACPU_SYSTEM_ID_PHY;
            break;
        case TIMER_ACPU_FREE_RUN:
            ret = TIMER_ACPU_FREE_RUN_PHY;
            break;
        case TIMER_ACPU_OSA_ID:
            ret = TIMER_ACPU_OSA_ID_PHY;
            break;
        case TIMER_ACPU_SOFTTIMER_ID:
            ret = TIMER_ACPU_SOFTTIMER_ID_PHY;
            break;

        case TIMER_ACPU_IDLE_ID:
            ret = TIMER_ACPU_IDLE_ID_PHY;
            break;
        case TIMER_ACPU_OM_TCXO_ID:
            ret = TIMER_ACPU_OM_TCXO_ID_PHY;
            break;
        /* 目前只为TIMER_CCPU_CPUVIEW_ID配权限，使其可以读取c核timer17的value值 */
        case TIMER_CCPU_CPUVIEW_ID:
            ret = TIMER_TOTAL_NUM + 0;      
            break;
            
        default:
            ret = -1;    
            break;
    }
    return ret;
}

/*****************************************************************************
 函 数 名  : timer_load_set
 功能描述  : 写寄存器Timer Load函数
 输入参数  : ucTimerId        Timer ID
             ulValue          待写入的LOAD寄存器的数据
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID timer_load_set(BSP_U8 ucTimerId, BSP_U32 ulValue)
{
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG =
        (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[ucTimerId]);

    /* 置cntl寄存器为32位计数模式，默认为16位计数 */
    pTIMER_CNTL_REG->reg.timersize = SET_BIT_WIHT_TRUE;

    /* 将ulValue写入load寄存器 */
    TIMER_REG_WRITE(TIMER_LOAD_REG(pulTimerBase[ucTimerId]), ulValue);
}

/*****************************************************************************
 函 数 名  : timer_load_get
 功能描述  : 读寄存器Timer Load函数
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_U32 timer_load_get(BSP_U8 timerId)
{
    BSP_U32 result;
    TIMER_REG_READ(TIMER_LOAD_REG(pulTimerBase[timerId]), result);

    return result;
}

/*****************************************************************************
 函 数 名  : timer_value_get
 功能描述  : 获取定时器当前值
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_U32 timer_value_get(BSP_U8 timerId)
{
    BSP_U32 result;
    TIMER_REG_READ(TIMER_VALUE_REG(pulTimerBase[timerId]), result);

    return result;
}

/*****************************************************************************
 函 数 名  : timer_is_running
 功能描述  : 通过读控制寄存器判断timer是否在运行
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_OK    该timer已使能
             BSP_ERROR 该timer没有被使能
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月30日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 timer_is_running(BSP_U8 timerId)
{
    /* 依据定时器timerId，读取寄存器TIMERN_CONTROL[7] */
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG = (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[timerId]);
    if (SET_BIT_WIHT_TRUE == pTIMER_CNTL_REG->reg.timeren)
    {
        return BSP_OK;
    }
     
    return BSP_ERROR;
}

/*****************************************************************************
 函 数 名  : timer_start
 功能描述  : 定时器使能操作函数
 输入参数  : timerId：
             mode：1表示已周期模式启动 0表示以单次模式启动
 输出参数  : 无
 返 回 值  : BSP_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID timer_start(BSP_U8 timerId, BSP_U32 mode)
{
    unsigned long flags;
    unsigned long base = IO_ADDRESS(REG_BASE_SC_ON);
    BSP_U8 dualTimerId = (BSP_U8)timerId/2;

    /* 对定时器timerId，写寄存器TIMERN_CONTROL[7]，配置定时器停止 */
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG =
        (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[timerId]);

    /*对timer控制寄存器的使能位读写互斥保护*/
    spin_lock_irqsave(&timer_en_lock, flags);
    
    /*使能dualt-timer的总线和工作时钟*/
    /*SC_PERIPH_CLKEN4 写1有效，写0无效*/
    TIMER_REG_WRITE(SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(base), SET_BITS_WIHT_TRUETRUE<<(2*dualTimerId+1));

    pTIMER_CNTL_REG->reg.timeren = SET_BIT_WIHT_FALSE;

    if (mode)
    {
        /* 对定时器timerId，写寄存器TIMERN_CONTROL[0~1]和TIMERN_CONTROL[5,6,7]，
           配置定时器为32bit计数、周期模式且使能 */
        pTIMER_CNTL_REG->reg.oneshot = SET_BIT_WIHT_FALSE;
        pTIMER_CNTL_REG->reg.timersize = SET_BIT_WIHT_TRUE;
        pTIMER_CNTL_REG->reg.intenable = SET_BIT_WIHT_TRUE;
        pTIMER_CNTL_REG->reg.timermode = SET_BIT_WIHT_TRUE;
        pTIMER_CNTL_REG->reg.timeren = SET_BIT_WIHT_TRUE;
    }
    else
    {
        /* 对定时器timerId，写寄存器TIMERN_CONTROL[0~1]和TIMERN_CONTROL[5,7]，
           配置定时器为32bit计数、单次模式且使能 */
        pTIMER_CNTL_REG->reg.oneshot = SET_BIT_WIHT_TRUE;
        pTIMER_CNTL_REG->reg.timersize = SET_BIT_WIHT_TRUE;
        pTIMER_CNTL_REG->reg.intenable = SET_BIT_WIHT_TRUE;
        pTIMER_CNTL_REG->reg.timeren = SET_BIT_WIHT_TRUE;
    }

    spin_unlock_irqrestore(&timer_en_lock, flags);
}

/*****************************************************************************
 函 数 名  : timer_stop
 功能描述  : 中断停止操作函数
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID timer_stop(BSP_U8 timerId)
{
    unsigned long flags;

   

    /* 对定时器timerId，写寄存器TIMERN_CONTROL[7]，配置定时器停止 */
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG =
          (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[timerId]);

    /*计算同dual-timer的另一个timerId*/
    BSP_U8 another_timerId = (timerId % 2) ? (timerId-1):(timerId+1);

    /*对timer控制寄存器的使能位读写互斥保护*/
    spin_lock_irqsave(&timer_en_lock, flags);

    pTIMER_CNTL_REG->reg.timeren = SET_BIT_WIHT_FALSE;

    /*判断同dualt-timer的另一个timer的使能状态*/
    if (BSP_OK != timer_is_running(another_timerId))
    {
        /*如果未使能，关闭此dual-timer的总线和工作时钟*/
        /*TIMER_REG_WRITE(SOC_AO_SCTRL_SC_PERIPH_CLKDIS4_ADDR(base), SET_BITS_WIHT_TRUETRUE<<(2*dualTimerId+1));*/
    }

    spin_unlock_irqrestore(&timer_en_lock, flags);
}

/*****************************************************************************
 函 数 名  : timer_int_mask
 功能描述  : 中断屏蔽函数
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID timer_int_mask(BSP_U8 timerId)
{
    /* 对定时器timerId，写寄存器TIMERN_CONTROL[5]，配置为中断屏蔽状态 */
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG =
        (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[timerId]);
    pTIMER_CNTL_REG->reg.intenable = SET_BIT_WIHT_FALSE;
}

/*****************************************************************************
 函 数 名  : timer_int_unmask
 功能描述  : 中断解屏蔽函数
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID timer_int_unmask(BSP_U8 timerId)
{
    /* 对定时器timerId，写寄存器TIMERN_CONTROL[5]，配置为中断解屏蔽状态 */
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG =
        (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[timerId]);
    pTIMER_CNTL_REG->reg.intenable = SET_BIT_WIHT_TRUE;
}

/*****************************************************************************
 函 数 名  : timer_int_clear
 功能描述  : 清定时器中断操作函数
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID timer_int_clear(BSP_U8 timerId)
{
    /* 对定时器timerId，写寄存器TIMERN_INTCLR[0]清除中断 */
    SOC_TIMER_TIMERN_INTCLR_UNION *pTIMER_INTC_REG =
        (SOC_TIMER_TIMERN_INTCLR_UNION *)TIMER_INTC_REG(pulTimerBase[timerId]);
    pTIMER_INTC_REG->reg.timern_intclr = SET_BIT_WIHT_TRUE;
}

/*****************************************************************************
 函 数 名  : timer_int_status_get
 功能描述  : 获取屏蔽后的计数器中断状态
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_U32    其中，0：未产生中断     1：已产生中断
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_U32 timer_int_status_get(BSP_U8 timerId)
{
    /* 对定时器timerId，读寄存器TIMERN_MIS[0]，并返回该值 */
    SOC_TIMER_TIMERN_MIS_UNION *pTIMER_MIS_REG =
        (SOC_TIMER_TIMERN_MIS_UNION *)TIMER_MIS_REG(pulTimerBase[timerId]);

    return(pTIMER_MIS_REG->reg.timernmis);
}

/*****************************************************************************
 函 数 名  : timer_raw_int_status_get
 功能描述  : 获取计数器的原始中断状态
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_U32 timer_raw_int_status_get(BSP_U8 timerId)
{
    /* 对定时器timerId，读寄存器TIMERN_RIS[0]，并返回该值 */
    SOC_TIMER_TIMERN_RIS_UNION *pTIMER_RIS_REG =
        (SOC_TIMER_TIMERN_RIS_UNION *)TIMER_RIS_REG(pulTimerBase[timerId]);

    return(pTIMER_RIS_REG->reg.timernris);
}

/*****************************************************************************
 函 数 名  : timer_32bit_count_set
 功能描述  : 设定寄存器32-bit计数模式
 输入参数  : timerId：
 输出参数  : 无
 返 回 值  : BSP_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_VOID  timer_32bit_count_set(BSP_U8 timerId)
{
    /* 对定时器timerId，写寄存器TIMERN_CONTROL[1]，配置为32-bit模式 */
    SOC_TIMER_TIMERN_CONTROL_UNION *pTIMER_CNTL_REG =
        (SOC_TIMER_TIMERN_CONTROL_UNION *)TIMER_CNTL_REG(pulTimerBase[timerId]);
    pTIMER_CNTL_REG->reg.timersize = SET_BIT_WIHT_TRUE;
}

/*****************************************************************************
 函 数 名  : timer_input_clk_get
 功能描述  : 获取定时器的工作时钟频率值。
 输入参数  : timerId：物理ID
 输出参数  : 无
 返 回 值  : BSP_ U32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_U32 timer_input_clk_get(BSP_U8 timerId)
{
    switch (timerId)
    {
        /* Timer时钟频率为32KHz */
        case TIMER_ACPU_OSA_ID_PHY:
        case TIMER_ACPU_SOFTTIMER_ID_PHY:
        case TIMER_ACPU_IDLE_ID_PHY:
        case TIMER_ACPU_OM_TCXO_ID_PHY:
            return SLEEP_CLK_FREQ;

        /* Timer时钟频率为19.2MHz */
        case TIMER_ACPU_SYSTEM_ID_PHY:
        case TIMER_ACPU_FREE_RUN_PHY:
            return TCXO_CLK_FREQ;

        default:
            return BSP_FALSE;
    }
}


/*****************************************************************************
 函 数 名  : timer_sys_ctrl_en0_set
 功能描述  : 针对Timer0~3 设置系统控制器SC_TIMER_EN0
 输入参数  : 
 输出参数  : 无
 返 回 值  : BSP_S32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月18日
    作    者   :  
    修改内容   : 新生成函数

*****************************************************************************/
BSP_S32 timer_sys_ctrl_set(void)
{
    BSP_U32 *pSCtrl_TIMER_EN0_REG = (BSP_U32 *)(IO_ADDRESS(AOSCTRL_SC_TIMER_EN0));
    BSP_U32 *pSCtrl_TIMER_EN1_REG = (BSP_U32 *)(IO_ADDRESS(AOSCTRL_SC_TIMER_EN1));
    SOC_AO_SCTRL_SC_TIMER_EN0_UNION SCtrl_TIMER_EN0_REG;
    SOC_AO_SCTRL_SC_TIMER_EN1_UNION SCtrl_TIMER_EN1_REG;

    /* 设置timer2,3 */
    SCtrl_TIMER_EN0_REG.value = 0;
    SCtrl_TIMER_EN0_REG.reg.timer_en0_5acpu_dualtimer1_en0 = TIMER_32K;
    SCtrl_TIMER_EN0_REG.reg.timer_en0_msk_5acpu_dualtimer1_en0 = SET_BITS_WIHT_TRUETRUE;
    
    SCtrl_TIMER_EN0_REG.reg.timer_en0_7acpu_dualtimer1_en1 = TIMER_32K;
    SCtrl_TIMER_EN0_REG.reg.timer_en0_msk_7acpu_dualtimer1_en1 = SET_BITS_WIHT_TRUETRUE;

    *pSCtrl_TIMER_EN0_REG = SCtrl_TIMER_EN0_REG.value;
   

    SCtrl_TIMER_EN1_REG.value = 0;
    SCtrl_TIMER_EN1_REG.reg.timer_en1_9acpu_dualtimer6_en0 = TIMER_32K;
    SCtrl_TIMER_EN1_REG.reg.timer_en1_msk_9acpu_dualtimer6_en0 = SET_BITS_WIHT_TRUETRUE;

    SCtrl_TIMER_EN1_REG.reg.timer_en1_11acpu_dualtimer6_en1 = TIMER_32K;
    SCtrl_TIMER_EN1_REG.reg.timer_en1_msk_11acpu_dualtimer6_en1 = SET_BITS_WIHT_TRUETRUE;

    *pSCtrl_TIMER_EN1_REG = SCtrl_TIMER_EN1_REG.value;

    return BSP_OK;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


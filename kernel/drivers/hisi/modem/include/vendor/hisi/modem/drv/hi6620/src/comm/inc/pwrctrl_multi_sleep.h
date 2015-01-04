/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : pwrctrl_multi_sleep.h
  版 本 号   : 初稿
  生成日期   : 2012年9月6日
  最近修改   :
  功能描述   : 低功耗多核公共的头文件，睡眠相关
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月6日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include  "pwrctrl_multi_def.h"
#include  "soc_baseaddr_interface.h"
#include  "soc_ao_sctrl_interface.h"


#ifndef __PWRCTRL_MULTI_SLEEP_H__
#define __PWRCTRL_MULTI_SLEEP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define PWC_VOTE_STAT_LOCK          (0xA1)   /*投票不允许单板睡*/
#define PWC_VOTE_STAT_UNLOCK        (0xA0)   /*去投票允许单板睡*/
#define PWC_VOTE_MODULE_SLEEP_SOFT  (0x50)   /*软件投票*/
#define PWC_VOTE_MODULE_SLEEP_HW    (0x51)   /*硬件投票*/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
typedef enum tagPWC_SC_RESERVED28_ID_E
{
    PWC_PD_SRAMBAK_RESTORE_ID_BIT      =    (0x1 << 0),

    PWC_SC_RESERVED28_ID_MAX           =    (0x1 << 31)
}PWC_SC_RESERVED28_ID_E;

typedef enum tagPWC_PD_MOUDLE_ID_E
{
    /*详细bit定义参考sc寄存器SC_MTCMOS_STAT0，SC_MTCMOS_STAT1*/
    PWC_PD_ID_PERI          = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_0peri_START,
    PWC_PD_ID_G3D           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_1g3d_START,
    PWC_PD_ID_G2D           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_2g2d_START,
    PWC_PD_ID_EDC0          = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_3edc0_START,
    PWC_PD_ID_EDC1          = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_4edc1_START,
    PWC_PD_ID_ISP           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_5isp_START,
    PWC_PD_ID_ENC           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_6enc_START,
    PWC_PD_ID_DEC           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_7dec_START,

    PWC_PD_ID_HIFI          = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_8hifi_START,
    PWC_PD_ID_VPP           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_9vpp_START,
    PWC_PD_ID_BBE           = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_10dspbbe_START,
    PWC_PD_ID_DDRCTRL       = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_11ddrctrl_START,
    PWC_PD_ID_BBP2C         = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_12bbpcommtop2c_gbbp1_START,
    PWC_PD_ID_BBP2D         = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_13bbpcommtop2d_gbbp2_START,
    PWC_PD_ID_BBP3          = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_14ltebbptop_START,  /*Lbbp*/
    PWC_PD_ID_BBP2B         = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_15bbpcommtop2b_bbpcomm2_START,
    PWC_PD_ID_BBP2A         = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_16bbpcommtop2a_bbpcomm1_START,
    PWC_PD_ID_BBP1B         = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_17bbpcommtop1b_wtdbbp2_START,
    PWC_PD_ID_BBP1A         = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_18bbpcommtop1a_wtdbbp1_START,
    PWC_PD_ID_TCXO0_AFC_MSK = SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo0_afc_high_z_msk_START,
    PWC_PD_ID_TCXO1_AFC_MSK = SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo1_afc_high_z_msk_START,
    PWC_PD_ID_TCXO0_AFC     = SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo0_afc_high_z_START,
    PWC_PD_ID_TCXO1_AFC     = SOC_AO_SCTRL_SC_ALWAYSON_SYS_CTRL4_tcxo1_afc_high_z_START,
    PWC_PD_ID_ABBANA        = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_19abbana_START,     /*没有该分区，与外设一起下*/
    PWC_PD_ID_USBPHY        = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_20usbphy_START,
    PWC_PD_ID_RESERVE1      = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_21reserved_START,
    PWC_PD_ID_CS0PHY        = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_22cs0phy_START,
    PWC_PD_ID_RESERVE2      = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_23reserved_START,
    PWC_PD_ID_CS2PHY        = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_24cs2phy_START,
    PWC_PD_ID_DSIPHY        = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_25dsiphy_START,
    PWC_PD_ID_HDMIPHY       = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_26hdmiphy_START,
    PWC_PD_ID_DDRPHY        = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_27ddrphy_START,
    PWC_PD_ID_reserved      ,
    PWC_PD_ID_TSENSOR0      = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_29tsensor0_START,
    PWC_PD_ID_TSENSOR1      = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_30tsensor1_START,
    PWC_PD_ID_RESERVE3      = SOC_AO_SCTRL_SC_PW_EN0_pw_en0_31reserved_START,

    PWC_PD_ID_ACPU0         = 32 + SOC_AO_SCTRL_SC_PW_EN1_pw_en1_0acpu0_START,      /*需要单独处理，流程有特殊要求*/
    PWC_PD_ID_ACPU1         = 32 + SOC_AO_SCTRL_SC_PW_EN1_pw_en1_1acpu1_START,
    PWC_PD_ID_ACPU2         = 32 + SOC_AO_SCTRL_SC_PW_EN1_pw_en1_2acpu2_START,
    PWC_PD_ID_ACPU3         = 32 + SOC_AO_SCTRL_SC_PW_EN1_pw_en1_3acpu3_START,
    PWC_PD_ID_CM3MEM        = 32 + SOC_AO_SCTRL_SC_PW_EN1_pw_en1_4cm3mem_START,
    PWC_PD_ID_CCPU          = 32 + SOC_AO_SCTRL_SC_PW_EN1_pw_en1_5mcpu_START,       /*需要单独处理，流程有特殊要求*/

    PWC_PD_ID_BUTT          = 38

} PWC_PD_MOUDLE_ID;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct PWC_EXC_SLEEP_CORE_LOG_STRU_S
{
    u32_t  SleepCount;         //+0X0
    u32_t  WakeCount;          //+0X4
    u32_t  SleepSliceTime;     //+0X8
    u32_t  WakeSliceTime;      //+0Xc

    u32_t  WfiFailCount;       //+0X10
    u32_t  WfiFailSliceTime;   //+0X14
    u32_t  status;             //+0X18
    u32_t  wakesrcIPC;         //+0X1c

    u32_t  wakesrc0;           //+0x20
    u32_t  wakesrc1;           //+0x24

}PWC_MCU_EXC_SLEEP_CORE_LOG_STRU;

typedef struct
{
    void* p;
    u32_t size;
} PWC_MCU_EXC_DFS_LOG_NODE_STRU;

typedef struct PWC_MCU_EXC_LOG_STRU_S
{

    PWC_MCU_EXC_SLEEP_CORE_LOG_STRU  ccpu;
    PWC_MCU_EXC_SLEEP_CORE_LOG_STRU  acpu0;
    PWC_MCU_EXC_SLEEP_CORE_LOG_STRU  hifi;
    PWC_MCU_EXC_SLEEP_CORE_LOG_STRU  peri;

    u32_t mcuNxtSchTimeId;
    u32_t mcuNxtSchTimeValue;

    u32_t mcuVoteMap;
    u32_t mcuHWVoteMap;
    s32_t mcuCanDeepSleepRet;

    PWC_MCU_EXC_DFS_LOG_NODE_STRU  dfs_log_node[64];

}PWC_MCU_EXC_LOG_STRU;

typedef struct PWRCTRL_CCPU_EXC_LOG_STRU_S
{

    u32_t  cSleepCount;         /*+0X0*/
    u32_t  cWakeCount;          /*+0X4*/

    u32_t  cSleepMgrSliceTime;  /*+0X8*/
    u32_t  cSleepSliceTime;       /*+0XC*/
    u32_t  cWakeSliceTime;      /*+0X10*/
    u32_t  cWakeMgrSliceTime;   /*+0X14*/

    u32_t  cSleepIpcCount;      /*+0X18*/
    u32_t  cSleepIpcSliceTime;  /*+0X1C*/
    u32_t  cWfiRetCount;        /*+0X20*/
    u32_t  cWfiRetSliceTime;    /*+0X24*/

    u32_t   cNxtSchTimeId;
    u32_t   cNxtSchTimeValue;

    u32_t   cVoteMap;
    u32_t   cHWVoteMap;
    s32_t   cCanDeepSleepRet;

    u32_t   reserved[29];

}PWRCTRL_CCPU_EXC_LOG_STRU;


typedef struct PWC_VOTE_LOG_STRU_S
{
    u32_t voteStat:8;     /*PWC_VOTE_STAT_LOCK 或者 PWC_VOTE_STAT_UNLOCK*/
    u32_t voteModuleId:8; /*PWC_VOTE_MODULE_SLEEP_SOFT 或者 PWC_VOTE_MODULE_SLEEP_HW*/
    u32_t reserved:8;     /*保留*/
    u32_t clientId:8;     /*含义为PWC_CLIENT_ID_E的低1个字节*/
    u32_t voteMap;        /*软件投票值或者硬件投票值*/
    u32_t taskId;         /*此次投票的任务ID*/
    u32_t slice;          /*此次投票的slice时间值*/
}PWC_VOTE_LOG_STRU;     /*该结构体大小为16个字节*/


typedef struct ST_STORE_ADDR_INFO_S
{
    u32_t ulStartAddr;            /*需要备份的寄存器地址信息*/
    u32_t ulLength;               /*内容长度，需要4字节对齐,单位32bit*/
} ST_STORE_REG_ADDR_INFO;

typedef struct ST_STORE_BIT_ADDR_INFO_S
{
    u32_t ulAddr;               /*需要备份的寄存器地址信息*/
    u32_t ulToAddr;             /*恢复地址,单位32bit*/
    u32_t ulMask;               /*恢复屏蔽,单位32bit*/
    u32_t ulSetMask;            /*特殊写使能,单位32bit*/
} ST_STORE_BIT_ADDR_INFO;


typedef struct ST_VOTE_HW_INFO_S
{
    u32_t voteEn;                   /*唤醒投票，即禁止睡眠*/
    u32_t voteDis;                  /*睡眠投票，即允许睡眠*/
    u32_t voteStat;                 /*投票状态寄存器，屏蔽前*/
    u32_t voteSleepMsk;             /*睡眠投票屏蔽*/
    u32_t voteWakeMsk;              /*唤醒投票屏蔽*/
    u32_t voteSleepStat;            /*投票状态寄存器，屏蔽后*/
    u32_t voteWakeStat;             /*投票状态寄存器，屏蔽后*/
} ST_VOTE_HW_INFO;

typedef struct ST_SYSCTRL_INT_INFO_S
{
    u32_t intEnStat;                /*唤醒投票，即禁止睡眠*/
    u32_t intStatR;                 /*睡眠投票，即允许睡眠*/
    u32_t intStatM;                 /*投票状态寄存器，屏蔽前*/
    u32_t intClr;                   /*睡眠投票屏蔽*/
    u32_t intEn0;                   /*唤醒投票屏蔽*/
    u32_t intDis0;                  /*投票状态寄存器，屏蔽后*/
} ST_SYSCTRL_INT_HW_INFO;

typedef struct ST_SET_BIT_ADDR_INFO_S
{
    u32_t ulAddr;               /*需要配置的寄存器地址信息*/
    u32_t ulMask;               /*屏蔽位,单位32bit*/
    u32_t ulvalue;              /*要写入的值,单位32bit*/
} ST_SET_BIT_ADDR_INFO;
/*****************************************************************************
  7 UNION定义
*****************************************************************************/
typedef enum tagPWC_TELE_SLEEP_MODE_ID_E
{
    /*BIT0-7 HW*/
    PWRCTRL_TELE_INVALID = -1,
    PWRCTRL_TELE_CCPU      = 0,
    PWRCTRL_TELE_PERI      = 1,
    PWRCTRL_TELE_ACPU      = 2,
    PWRCTRL_TELE_REV0      = 3,
    PWRCTRL_TELE_REV1      = 4,
    PWRCTRL_TELE_REV2      = 5
} PWC_TELE_SLEEP_MODE_ID_E;

typedef enum tagPWC_TELE_SLEEP_CLIENT_ID_E
{
    /*BIT0-7 HW*/
    PWRCTRL_TELE_CLIENT_INVALID    = -1,
    PWRCTRL_TELE_SLEEP_CSIGHT0      = 0,
    PWRCTRL_TELE_SLEEP_CSIGHT1      = 1,
    PWRCTRL_TELE_SLEEP_IPF          = 2,
    PWRCTRL_TELE_SLEEP_SOCP         = 3,

    /* Test */
    PWRCTRL_TELE_CLIENT_BUTT        = 32
} PWC_TELE_SLEEP_CLIENT_ID_E;



/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/












#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_multi_sleep.h */

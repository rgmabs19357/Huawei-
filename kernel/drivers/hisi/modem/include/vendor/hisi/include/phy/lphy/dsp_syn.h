

/*****************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

*****************************************************************************
  文 件 名   : dsp_syn.h
  版 本 号   : V1.0
  生成日期   : 2011年8月13日
  功能描述   : 该文件定义了V7R1综合测试和DSP的头文件。
  修改历史   :
  1.日    期 : 2011年8月13日
    修改内容 : 创建文件，

*****************************************************************************/
#ifndef __DSP_SYN_H__
#define __DSP_SYN_H__

#undef UINT32
#define  UINT32 unsigned long
#undef INT32
#define  INT32 long
#undef INT16
#define   INT16 short
#undef UINT16
#define UINT16 unsigned short
#undef UINT8
#define UINT8 unsigned char
#undef INT8
#define INT8 unsigned char

/* DSP CT 命令范围[0x00010000,0x00010F00)*/
/* CT命令定义必须为：(0x00010000=<DSP CMDID<0x00010F00)*/

/* ^SSYNC 非信令综测设置单板同步状态*/
#define OM_PHY_SYN_SSYNC_SET_REQ             (0x10200)
#define PHY_OM_SYN_SSYNC_SET_CNF             (0x10200)

/* ^SSYNC 非信令综测查询单板同步状态*/
#define OM_PHY_SYN_SSYNC_RD_REQ              (0x10201)
#define PHY_OM_SYN_SSYNC_IND              (0x10201)

/* ^STXBW 非信令综测设置发射带宽*/
#define OM_PHY_SYN_STXBW_SET_REQ             (0x10202)
#define PHY_OM_SYN_STXBW_SET_CNF             (0x10202)

/* ^SSUBFRAME 非信令综测设置子帧配比*/
#define OM_PHY_SYN_SSUBFRAME_SET_REQ           (0x10204)
#define PHY_OM_SYN_SSUBFRAME_SET_CNF           (0x10204)

/* ^STXCHAN 非信令综测设置上行发射信道*/
#define OM_PHY_SYN_STXCHAN_SET_REQ           (0x10205)
#define PHY_OM_SYN_STXCHAN_SET_CNF           (0x10205)

/*^SPARA*/
/*非信令综测设置信道参数*/
#define OM_PHY_SYN_SPARA_SET_REQ           (0x1020F)
#define PHY_OM_SYN_SPARA_SET_CNF           (0x1020F)

#define OM_PHY_SYN_SPARA_RD_REQ             (0x10210)
#define PHY_OM_SYN_SPARA_RD_CNF             (0x10210)

/*^SSEGNUM非信令综测设置segment数量*/
#define OM_PHY_SYN_SSEGNUM_SET_REQ           (0x10211)
#define PHY_OM_SYN_SSEGNUM_SET_CNF           (0x10211)

#define OM_PHY_SYN_SSEGNUM_RD_REQ            (0x10212)
#define PHY_OM_SYN_SSEGNUM_RD_CNF            (0x10212)

/* ^STXMODUS 非信令综测设置调制方式*/
#define OM_PHY_SYN_STXMODUS_SET_REQ          (0x10206)
#define PHY_OM_SYN_STXMODUS_SET_CNF          (0x10206)

/* ^STXRBNUMS 非信令综测设置RB数量*/
#define OM_PHY_SYN_STXRBNUMS_SET_REQ         (0x10207)
#define PHY_OM_SYN_STXRBNUMS_SET_CNF         (0x10207)

/* ^STXRBPOSS 非信令综测设置RB位置*/
#define OM_PHY_SYN_STXRBPOSS_SET_REQ         (0x10208)
#define PHY_OM_SYN_STXRBPOSS_SET_CNF         (0x10208)

/* ^STXPOWS 非信令综测设置发射功率*/
#define OM_PHY_SYN_STXPOWS_SET_REQ           (0x10209)
#define PHY_OM_SYN_STXPOWS_SET_CNF           (0x10209)

/* ^STXCHANTYPES 非信令综测设置信道类型*/
#define OM_PHY_SYN_STXCHANTYPES_SET_REQ      (0x1020A)
#define PHY_OM_SYN_STXCHANTYPES_SET_CNF      (0x1020A)

/* ^SSEGLEN 非信令综测设置SEGMENT长度*/
#define OM_PHY_SYN_SSEGLEN_SET_REQ          (0x1020B)
#define PHY_OM_SYN_SSEGLEN_SET_CNF          (0x1020B)

/*^SRXPOW非信令综测接收测试的功率设置*/
/*#define OM_PHY_SYN_SRXPOW_SET_REQ          (0x10213)*/
/*#define PHY_OM_SYN_SRXPOW_SET_CNF          (0x10213)*/
/*#define OM_PHY_SYN_SRXPOW_RD_REQ           (0x10214)*/
/*#define PHY_OM_SYN_SRXPOW_RD_CNF           (0x10214)*/

/*^SRXSUBFRA非信令综测接收测试的子帧数量*/
#define OM_PHY_SYN_SRXSUBFRA_SET_REQ          (0x10215)
#define PHY_OM_SYN_SRXSUBFRA_SET_CNF          (0x10215)
#define OM_PHY_SYN_SRXSUBFRA_RD_REQ           (0x10216)
#define PHY_OM_SYN_SRXSUBFRA_RD_CNF           (0x10216)

/*^SRXBLER非信令综测接收测试查询误码率*/
#define OM_PHY_SYN_SRXBLER_RD_REQ           (0x10217)
#define PHY_OM_SYN_SRXBLER_RD_CNF           (0x10217)

/*查询 TDS 下行 BER 结果*/
#define OM_PHY_SYN_SRXBER_RD_REQ           (0x10218)
#define PHY_OM_SYN_SRXBER_RD_CNF           (0x10218)
/* ^SSTART 非信令综测启动发射并状态查询*/
#define OM_PHY_SYN_SSTART_SET_REQ            (0x1020C)
#define PHY_OM_SYN_SSTART_SET_CNF            (0x1020C)

/* ^SSTART 非信令综测状态查询*/
#define OM_PHY_SYN_SSTART_RD_REQ             (0x1020D)
#define PHY_OM_SYN_SSTART_RD_CNF             (0x1020D)

/* ^SSTOP 非信令综测停止上行发射*/
#define OM_PHY_SYN_SSTOP_SET_REQ             (0x1020E)
#define PHY_OM_SYN_SSTOP_SET_CNF             (0x1020E)

#define OM_PHY_SYN_SRXSET_SET_REQ            (0x10213)
#define PHY_OM_SYN_SRXSET_SET_CNF            (0x10213)
#define OM_PHY_BT_FPOW_SET_REQ                (0x10214)
#define PHY_OM_BT_FPOW_SET_CNF                (0x10214)
/*****************************************************************************
 描述 : 非信令综测设置单板同步状态
 在调试状态下触发UE与综测仪（MT8820C/CMW500）的同步过程，若同步成功直接返回OK，否则返回ERROR。
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSYNC_SET_REQ,PHY_OM_SYN_SSYNC_SET_CNF
 REQ  : OM_PHY_SYN_SSYNC_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSYNC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;     /* 消息标识 */
    UINT16 usMode;      /* MODE TDD：1；FDD：0*/
    UINT16 usBand;      /* LTE频段信息，取值范围1～50，如7代表Band7*/
    UINT16 usUlchannel; /* 上行同步信道，取值范围0～65535*/
    UINT16 usDlchannel; /* 下行同步信道，取值范围0～65535*/
} OM_PHY_SYN_SSYNC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSYNC_SET_CNF_STRU;

/*****************************************************************************
 描述 : 非信令综测查询单板同步状态
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSYNC_RD_REQ,PHY_OM_SYN_SSYNC_RD_CNF
 REQ  : OM_PHY_SYN_SSYNC_RD_REQ_STRU
 CNF  : PHY_OM_SYN_SSYNC_RD_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
/*DSP主动上报*/
typedef struct
{
    UINT32 ulMsgId;
    
    /* UE与综测仪同步状态 */
		/* 0	已经同步成功*/
		/* 1	未同步或同步失败*/
    UINT32 ulStatus;
} PHY_OM_SYN_SSYNC_RPT_IND_STRU;


/*****************************************************************************
 描述 : ^STXBW 非信令综测设置发射带宽
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXBW_SET_REQ,PHY_OM_SYN_STXBW_SET_CNF
 REQ  : OM_PHY_SYN_STXBW_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXBW_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    /* 置综测测试上行发射带宽的列表，取值范围0~5，默认值为0*/
    /* 0	1.4M*/
    /* 1	3M*/
    /* 2	5M*/
    /* 3	10M*/
    /* 4	15M*/
    /* 5	20M*/
    UINT16 usBandwide; 
    UINT16 usRsv;
} OM_PHY_SYN_STXBW_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXBW_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SCONFIG 非信令综测设置子帧配比
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SCONFIG_SET_REQ,PHY_OM_SYN_SCONFIG_SET_CNF
 REQ  : OM_PHY_SYN_SCONFIG_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SCONFIG_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    /* RTT通过usFrameNumer/usFrameDeno,计算子帧配比usFrameNumer=7，usFrameDeno=6，*/
    /* usFrameNumer/usFrameDeno=7/6*/
    UINT16 usSubFrameAssign; 
    UINT16 usSubFramePattern;
} OM_PHY_SYN_SSUBFRAME_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSUBFRAME_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^STXCHAN 非信令综测
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXCHAN_SET_REQ,PHY_OM_SYN_STXCHAN_SET_CNF
 REQ  : OM_PHY_SYN_STXCHAN_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXCHAN_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    /* 上行同步信道，取值范围0～65535*/
    UINT16 usUlchannel ; 
    UINT16 usRsv;
} OM_PHY_SYN_STXCHAN_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXCHAN_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SPARA 非信令综测设置子帧配比
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 
 ID   : 
 REQ  : 
 CNF  : 
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
	UINT32 ulMsgId;
	/*设置参数类型，取值范围0~32*/
	UINT16 usType;
	/*设置参数值，取值范围0~65535*/
	UINT16 usValue;

} OM_PHY_SYN_SPARA_SET_REQ_STRU;
typedef struct
{
	UINT32 ulMsgId;

} PHY_OM_SYN_SPARA_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^SSEGNUM 非信令综测设置SEGMENT的数量
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 
 ID   : 
 REQ  : 
 CNF  : 
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSegNum;
	UINT16 usReserved;

} OM_PHY_SYN_SSEGNUM_SET_REQ_STRU;
typedef struct
{
	UINT32 ulMsgId;

} PHY_OM_SYN_SSEGNUM_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^STXMODUS 非信令综测设置调制方式
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXMODUS_SET_REQ,PHY_OM_SYN_STXMODUS_SET_CNF
 REQ  : OM_PHY_SYN_STXMODUS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXMODUS_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    /* 设置综测测试调制方式的数量，取值范围0~50，默认值为0*/
    UINT16 usModulution_num  ; 
	UINT16 usRsv;
    
    /* 设置综测测试调试方式列表，取值范围0~2，默认值为0*/
    /* （其中0代表QPSK，1代表16QAM，2代表64QAM）*/
    UINT16  usModulation_list [256];
    
} OM_PHY_SYN_STXMODUS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXMODUS_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^STXRBNUMS 非信令综测设置RB数量
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 
 ID   : 
 REQ  : 
 CNF  : 
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /* 设置综测测试上行发射RB的数量，取值范围0~50，默认值为0*/
    UINT16 usRb_num;
	UINT16 usRsv;
	/* 设置综测测试上行发射RB的列表，取值范围1~100，默认值1*/
    UINT16 usrb_list[256];  
} OM_PHY_SYN_STXRBNUMS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXRBNUMS_SET_CNF_STRU;


/*****************************************************************************
 描述 : ^STXRBPOSS 非信令综测设置RB位置
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）及RB数量（^SRBNUMS）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXRBPOSS_SET_REQ,PHY_OM_SYN_STXRBPOSS_SET_CNF
 REQ  : OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXRBPOSS_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    UINT16 usRbpos_num; /* 设置综测测试上行发射RB位置的数量，取值范围0~50，默认值为0*/
	UINT16 usRsv;

	UINT16 usrbpos_list[256];  /* 设置综测测试上行发射RB位置的列表，取值范围0~99，默认值为0*/
} OM_PHY_SYN_STXRBPOSS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXRBPOSS_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^STXPOWS 非信令综测设置发射功率
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXPOWS_SET_REQ,PHY_OM_SYN_STXPOWS_SET_CNF
 REQ  : OM_PHY_SYN_STXPOWS_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXPOWS_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    UINT16 ulPow_num;   /* 设置综测测试上行发射RB位置的数量，取值范围0~50，默认值为0*/
	UINT16 usRsv;

	INT16 slPow_list[256];  /* 设置综测测试上行发射RB位置的列表，取值范围0~99，默认值为0*/
} OM_PHY_SYN_STXPOWS_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXPOWS_SET_CNF_STRU;


/*****************************************************************************
 描述 : ^STXCHANTYPES 非信令综测设置信道类型
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_STXCHANTYPES_SET_REQ,PHY_OM_SYN_STXCHANTYPES_SET_CNF
 REQ  : OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU
 CNF  : PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    
    UINT16 usType_num; /* 设置综测测试上行发射信道的数量，取值范围0~50，默认值为0*/
    UINT16 usRsv;   
		/* 0	PUSCH*/
		/* 1	PUCCH*/
		/* 2	PRACH*/
    UINT16 usType_list[256];/*	设置综测测试上行发射信道的列表，取值范围0~2*/
} OM_PHY_SYN_STXCHANTYPES_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_STXCHANTYPES_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SSEGLEN 非信令综测设置SEGMENT长度
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 该命令需要在设置非信令综测同步（^SSYNC）后执行。(MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_SSEGMENT_SET_REQ,PHY_OM_SYN_SSEGMENT_SET_CNF
 REQ  : OM_PHY_SYN_SSEGMENT_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSEGMENT_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /* 10	10ms*/
    /* 20	20ms*/
	/* 50	50ms*/
	/* 100	100ms*/
    UINT16 usSegment_Len; /* 设置综测测试上行发射信道的数量，取值范围0~50，默认值为0*/
    

    UINT16 usReserved;
} OM_PHY_SYN_SSEGLEN_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSEGLEN_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SRXPOW 非信令综测接收测试的功率设置
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 
 
 
 ID  : 
 REQ : 
 CNF : 
 IND : NA
 说明 :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSwitch;
	INT16  sPower;
	UINT16 usMod;
	UINT16 usRBNum;
	UINT16 usRBPos;
	UINT16 usRsv;

}OM_PHY_SYN_SRXSET_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SRXSET_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SRXSUBFRA 非信令综测接收测试的子帧数量
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 
 
 
 ID  : 
 REQ : 
 CNF : 
 IND : NA
 说明 :
*****************************************************************************/
typedef struct
{
	UINT32 ulMsgId;
	UINT16 usSubFrameNum;
	UINT16 usReserved;

}OM_PHY_SYN_SRXSUBFRA_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SRXSUBFRA_SET_CNF_STRU;
/*****************************************************************************
 描述 : ^SRXBLER 非信令综测接收测试查询误码率
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 
 
 
 ID  : 
 REQ : 
 CNF : 
 IND : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulBler;
	INT16  sSnr;
	UINT16 usRsv;
} PHY_OM_SYN_SRXMEAS_RPT_IND_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulBersum;
	UINT32 ulBerErr;
	UINT32 usRsv;
} PHY_OM_SYN_SRXMEAS_TDS_RPT_IND_STRU;
/* end_added by s00184745 for bt tds nosig 20130516 */
/*****************************************************************************
 描述 : ^SSTART 非信令综测启动发射并状态查询
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 调试状态下启动sequence方式的非信令综测。
 该命令需要在设置AT^SSYNC、AT^SMODUS、AT^STXBWS、AT^SPOWS、AT^SCHANS、AT^SSEGMENT命令后执行。其它模式下返回错误码。
 (MSP可以加简单判断，初步实现可以先不加入)
 ID   : OM_PHY_SYN_SSTART_SET_REQ,PHY_OM_SYN_SSTART_SET_CNF
 REQ  : OM_PHY_SYN_SSTART_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSTART_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTART_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSTART_SET_CNF_STRU;

/*****************************************************************************
 描述 : ^SSTART? 非信令综测状态查询,该状态必须请求RTT返回
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSTART_RD_REQ,PHY_OM_SYN_SSTART_RD_CNF
 REQ  : OM_PHY_SYN_SSTART_RD_REQ_STRU
 CNF  : PHY_OM_SYN_SSTART_RD_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
#if 0
typedef struct
{
    UINT32 ulMsgId;
	
	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTART_RD_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
    
    /* 0	执行完成*/
    /* 1	正在执行*/
    /* 2	未执行*/
    UINT16 usStatus; /* 非信令综测状态*/
    
    UINT16 usRsv;
} PHY_OM_SYN_SSTART_RD_CNF_STRU;
#endif
/*****************************************************************************
 描述 : ^SSTOP 非信令综测停止上行发射
 ^TMODE=7下使用，若在非TMODE=7的情况下MSP直接返回错误码。
 ID   : OM_PHY_SYN_SSTOP_SET_REQ,PHY_OM_SYN_SSTOP_SET_CNF
 REQ  : OM_PHY_SYN_SSTOP_SET_REQ_STRU
 CNF  : PHY_OM_SYN_SSTOP_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	
	UINT16 usType;
	UINT16 usRsv;
} OM_PHY_SYN_SSTOP_SET_REQ_STRU;

/* 返回则认为成功*/
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_SSTOP_SET_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;	
	INT16  usPower;
	UINT16 usRsv;
} OM_PHY_SYN_FPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_SYN_FPOW_SET_CNF_STRU;
#endif

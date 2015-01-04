

/*****************************************************************************
 特殊说明：
    1、该文件是MSP友情协助DSP完成，各种名称对应到文档中提供的源于
    2、命名规则FOLLOW文档所给规则
    3、后续维护是DSP维护

*****************************************************************************
*****************************************************************************

                  版权所有 (C), 2001-2012, 华为技术有限公司

*****************************************************************************
  文 件 名   : dsp_ct_ex.h
  版 本 号   : V1.0
  生成日期   : 2010年12月13日
  功能描述   : 该文件定义了V1R1 C00中CT，MSP和DSP交互的原语及其参数和描述。
  修改历史   :
  1.日    期 : 2010年12月13日
    修改内容 : 创建文件

*****************************************************************************/
#ifndef __DSP_CT_EX_H__
#define __DSP_CT_EX_H__

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
#define OM_PHY_CT_F_FREQ_SET_REQ         (0x10120)
#define PHY_OM_CT_F_FREQ_SET_CNF         (0x10120)

#define OM_PHY_CT_F_TXPOW_SET_REQ        (0X10130)
#define PHY_OM_CT_F_TXPOW_SET_CNF        (0X10130)

#define OM_PHY_CT_F_AAGC_SET_REQ         (0X10140)
#define PHY_OM_CT_F_AAGC_SET_CNF         (0X10140)

#define PHY_OM_CT_F_MEAS_RSSI_IND        (0X10150)

#define PHY_OM_CT_F_MEAS_CMTMS_IND       (0X10160)

#define OM_PHY_CT_F_PA_SET_REQ           (0X10170)
#define PHY_OM_CT_F_PA_SET_CNF           (0X10170)

#define OM_PHY_CT_F_SEGMENT_SET_REQ      (0X10180)
#define PHY_OM_CT_F_SEGMENT_SET_CNF      (0X10180)

#define OM_PHY_CT_F_TXWAVE_SET_REQ       (0X10190)
#define PHY_OM_CT_F_TXWAVE_SET_CNF       (0X10190)

#define OM_PHY_CT_F_TRIGGER_SET_REQ      (0X101A0)
#define PHY_OM_CT_F_TRIGGER_SET_CNF      (0X101A0)

#define OM_PHY_CT_F_TRIGGER_RD_REQ       (0X101B0)
#define PHY_OM_CT_F_TRIGGER_RD_CNF       (0X101B0)


#define OM_PHY_CT_F_FBLK_SET_REQ         (0X101C0)
#define PHY_OM_CT_F_FBLK_SET_CNF         (0X101C0)

#define OM_PHY_CT_F_FIPSTART_SET_REQ     (0X101D0)
#define PHY_OM_CT_F_FIPSTART_SET_CNF     (0X101D0)
#define PHY_OM_CT_F_MEAS_IP2_IND          (0X101E0)

#define OM_PHY_CT_F_MAX_POWER_SET_REQ           (0X101f0)
#define PHY_OM_CT_F_MAX_POWER_SET_CNF           (0X101f0)

#define OM_PHY_CT_F_PA_POWER_SET_REQ           (0X101f4)
#define PHY_OM_CT_F_PA_POWER_SET_CNF           (0X101f4)

#define OM_PHY_LTESCINFO_RD_REQ          (0X101C2)
#define PHY_OM_LTESCINFO_RD_CNF          (0X101C2)

#define OM_PHY_CT_F_BANDSW_SET_REQ             (0X101F5)
#define PHY_OM_CT_F_BANDSW_SET_CNF             (0X101F5)


#define OM_PHY_BT_TEMP_DISPATCH_REQ        (0x10340)
#define PHY_OM_BT_TEMP_DISPATCH_CNF        (0x10340)

#define OM_PHY_CT_F_FPDMS_REQ              (0X101F6)
#define PHY_OM_CT_F_FPDMS_CNF              (0X101F6)

/*AT^FPDMS*/
typedef struct
{
   UINT32 ulMsgId;
   UINT32 ulIsEnable;
}OM_PHY_CT_F_FPDMS_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_OM_CT_F_FPDMS_SET_CNF_STRU;

/*TEMP*/
typedef struct
{
   UINT32 ulMsgId;
   UINT16 usTempVal;
   UINT16 usRsv;
}OM_PHY_BT_TEMP_DISPATCH_REQ_STRU;
/*****************************************************************************
AT^BANDSW
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usMode;
	UINT16 usBand;
}OM_PHY_CT_F_BANDSW_SET_REQ_STRU;
typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_BANDSW_SET_CNF_STRU;



/*****************************************************************************
 描述 : 当前发射通道打开。
        则认为是下行频点。MSP须将AT^FCHANS命令中的信道号根据36.101协议规定查表转为实际频点值，
        转换过程参考附录4。
 ID   : OM_PHY_CT_F_FREQ_SET_REQ,PHY_OM_CT_F_FREQ_SET_CNF
 REQ  : OM_PHY_CT_F_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
#define CT_F_FREQ_UL_LIST_MAX_NUM 32
#define CT_F_FREQ_DL_LIST_MAX_NUM 32
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识*/
    UINT32 ulMode;                       /* MODE TDD：7；FDD：6*/
    UINT16 usUlListNum; /* 上行设置的个数，对应ausUlFreqInfo，最多16个*/
    UINT16 usDlListNum; /* 下行设置的个数，对应ausDlFreqInfo，最多16个*/

    /* 频点信息，*/
    /* 频栅间隔100Khz，如配置值26200对应频点2.62GHz*/
    UINT16 ausUlFreqInfo[CT_F_FREQ_UL_LIST_MAX_NUM];       /* 上行频点信息*/
    UINT16 ausDlFreqInfo[CT_F_FREQ_DL_LIST_MAX_NUM];       /* 下行频点信息*/
} OM_PHY_CT_F_FREQ_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_FREQ_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置上行发射功率。RTT收到该原语后应立即改变上行发射功率
 ID   : OM_PHY_CT_F_TXPOW_SET_REQ,PHY_OM_CT_F_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_F_TXPOW_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXPOW_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
#define CT_POWER_SET_MAX_NUM             (30)
typedef struct
{
    UINT32 ulMsgId;                          /* 消息标识 */

    /* 单位：dBm*/
    UINT16 usTxPowerNum;                     /* 指定在asTxPower的个数*/
    UINT16 usRsv;
    /* 发射功率列表，以空格分割，每个值的长度为一个字 ，单位为dBm*/
    INT16  ausTxPower[CT_POWER_SET_MAX_NUM];  /*上行发射功率*/
} OM_PHY_CT_F_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXPOW_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置RFIC的AAGC总增益，用于下行AGC表的校准，单位为dB。
      RTT收到该原语后将RFIC的总增益立即改为原语指示的增益值。
 ID   : OM_PHY_CT_F_AAGC_SET_REQ,PHY_OM_F_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_F_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_AAGC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

#define CT_F_AAGC_SET_MAX_NUM    (30)
typedef struct
{
    UINT32 ulMsgId;                               /* 消息标识*/
    UINT16 usAagcNum;
    UINT16 usRsv;

    /*取值范围0～255，其中Hi6910的范围为151-234。*/
    UINT8 aucAAGCValue[CT_F_AAGC_SET_MAX_NUM];    /* AAGC增益值*/
} OM_PHY_CT_F_AAGC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_AAGC_SET_CNF_STRU;

/*****************************************************************************
 描述 :
 ID   : PHY_OM_CT_F_MEAS_RSSI_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_F_MEAS_RSSI_IND_STRU
 说明 :
*****************************************************************************/
#define POW_MAX_NUM             (30)
#define FREQ_MAX_NUM            (16)

typedef struct
{
    /* AT指令集-装备定义:*/
    /*  个值采用正值表示，精确到0.125dBm定制值信息，取值范围为160~880。*/
    /*  如果当前的RSSI值为-85.125dBm，范围值为-85.125dbm*(-1)/0.125dbm = 681*/

    INT16  sRxANT1RSSI;
    INT16  sRxANT2RSSI;
} CT_F_ANT_RSSI_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 usFreqNum;
    UINT16 usPowNum;

    CT_F_ANT_RSSI_STRU  astRxANTRSSI[FREQ_MAX_NUM][POW_MAX_NUM];
} PHY_OM_CT_F_MEAS_RSSI_IND_STRU;

/*****************************************************************************
 描述 :
 ID   : PHY_OM_CT_F_MEAS_CMTMS_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_F_MEAS_CMTMS_IND_STRU
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32  ulMsgId;
    UINT16  usCmtmsNum; 					     /* 温度值数量，取值范围为0～16*/
    UINT16  usRsv;

    UINT16  ausCmtms[FREQ_MAX_NUM]; /* 温度值列表，取值范围为0～256，若温度值数量为0则没有温度值列表*/

} PHY_OM_CT_F_MEAS_CMTMS_IND_STRU;


/*****************************************************************************
 描述 : 指示RTT设置PA
 ID   : OM_PHY_CT_F_PA_SET_REQ,PHY_OM_CT_F_PA_SET_CNF
 REQ  : OM_PHY_CT_F_PA_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
#define CT_F_PA_SET_MAX_NUM   (30)
typedef struct
{
    UINT32 ulMsgId;
    UINT16 usLevelNum;
    UINT16 usRsv;
    UINT8 aucLvlList[CT_F_PA_SET_MAX_NUM];
} OM_PHY_CT_F_PA_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_PA_SET_CNF_STRU;


/*****************************************************************************
 描述 : 指示RTT设置SEGMENT
 ID   : OM_PHY_CT_F_SEGMENT_SET_REQ,PHY_OM_CT_F_SEGMENT_SET_CNF
 REQ  : OM_PHY_CT_F_SEGMENT_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_SEGMENT_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16 usSegment;                    /* 10,20毫秒 */
    UINT16 measOffset;                   /* 表示测量起始位置偏移，单位ms，取值范围0~20，无默认值*/
	UINT16 measLen;                      /* 表示测量长度，单位ms，取值范围0~20，无默认值 */
    UINT16 usRsv;
} OM_PHY_CT_F_SEGMENT_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_SEGMENT_SET_CNF_STRU;

/*****************************************************************************
 描述 : 指示RTT设置发射波形
 ID   : OM_PHY_CT_F_TXWAVE_SET_REQ,PHY_OM_CT_F_TXWAVE_SET_CNF
 REQ  : OM_PHY_CT_F_TXWAVE_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXWAVE_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0    CW波型*/
    /* 1    LTE波型*/
    UINT16 usWaveType;

    UINT16 usRsv;
} OM_PHY_CT_F_TXWAVE_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXWAVE_SET_CNF_STRU;

/*****************************************************************************
 描述 : 启动快速校准TRIGGER及后续校准流程
 ID   : OM_PHY_CT_F_TRIGGER_SET_REQ,PHY_OM_CT_F_TRIGGER_SET_CNF 设置ID
        OM_PHY_CT_F_TRIGGER_RD_REQ,PHY_OM_CT_F_TRIGGER_RD_CNF   查询ID
 REQ  : OM_PHY_CT_F_TRIGGER_SET_REQ_STRU OM_PHY_CT_F_TRIGGER_RD_REQ_STRU
 CNF  : PHY_OM_CT_F_TRIGGER_SET_CNF_STRU PHY_OM_CT_F_TRIGGER_RD_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0    发送通道校准*/
    /* 1    接收通道校准（接收默认为双通道）*/
    /* 2    发射/接收通道同时校准（接收默认为双通道）*/
    UINT8 ucType;

    UINT8 padding[3];
} OM_PHY_CT_F_TRIGGER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TRIGGER_SET_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_F_TRIGGER_RD_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;

    /* 0    发送通道校准*/
    /* 1    接收通道校准（接收默认为双通道）*/
    /* 2    发射/接收通道同时校准（接收默认为双通道）*/
    UINT8 ucType;

    /* 快速校准状态*/
    /* 0    未启动或执行完毕*/
    /* 1    执行中*/
    UINT8 ucStatus;

    UINT8 ucRsv[2];
} PHY_OM_CT_F_TRIGGER_RD_CNF_STRU;

/*BLOCKING*/
typedef struct
{
    UINT32 ulMsgId;
	UINT16 usIsBLKMode;
	UINT16 usRsv;
}OM_PHY_CT_F_BLK_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_OM_CT_F_BLK_SET_CNF_STRU;

/*IP2*/
typedef struct
{
    UINT32 ulMsgId;       /*消息标识*/
    UINT16 usBand;        /*IP2校准band值*/
    UINT16 usRsv;
} OM_PHY_CT_F_IP2START_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;       /*消息标识*/
} PHY_OM_CT_F_IP2START_CNF_STRU;


typedef struct
{
    UINT32 ulMsgId;       /*消息标识*/
    INT16 ulIP2Value1;     /*IP2校准结果1*/
    INT16 ulIP2Value2;     /*IP2校准结果2*/
} PHY_OM_CT_F_MEAS_IP2_IND_STRU;
/*PHY_OM_CT_F_MEAS_IP2_IND_STRU*/

/*****************************************************************************
 描述 : MAXPOWER校准请求
 ID   : OM_PHY_CT_F_MAX_POWER_REQ,PHY_OM_CT_F_MAX_POWER_CNF
 REQ  : OM_PHY_CT_F_MAX_POWER_REQ_STRU
 CNF  : PHY_OM_CT_F_MAX_POWER_CNF_STRU
 IND  : NAN
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识*/
    UINT16 usPaLevelNum;                 /*需要校准的PA 档位数目0-4*/
    UINT16 usPaReduceGain;               /*新增20111029；0-20*/
} OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识*/
} PHY_OM_CT_F_MAX_POWER_SET_CNF_STRU;

/*****************************************************************************
 描述 : PAPOWER设置
 ID   : OM_PHY_CT_F_PA_POWER_SET_REQ,PHY_OM_CT_F_PA_POWER_SET_CNF
 REQ  : OM_PHY_CT_F_PA_POWER_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_POWER_SET_CNF_STRU
 IND  : NAN
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识*/
    UINT16 usPaLevelNum;
    UINT16 usRsv;
    INT16 asMaxPwrList[4];              /*校准后的MAXPOWER值*/
} OM_PHY_CT_F_PA_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识*/
} PHY_OM_CT_F_PA_POWER_SET_CNF_STRU;

/*****************************************************************************
 描述 : 8.6	服务小区信息查询命令^LTESCINFO
 ID   : OM_PHY_RD_LTESCINFO_REQ_STRU,OM_PHY_RD_LTESCINFO_CNF_STRU   查询ID
 REQ  : OM_PHY_RD_LTESCINFO_REQ_STRU
 CNF  : OM_PHY_RD_LTESCINFO_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_RD_LTESCINFO_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;

    UINT16 usCid;     /* 物理小区ID,取值范围：0 ~ 503 ，65535表示没有获取到当前服务小区ID*/

    INT16  usDlSinr ; /* 下行链路信噪比,取值范围：-20 ~ 30*/
    UINT16 usDlBw ;   /* LTE downlink bandwidth*/

    UINT8  ucNumAnt;  /* 当前天线个数,0~4*/
    UINT8  ucRsv;
} PHY_OM_RD_LTESCINFO_CNF_STRU;

#endif



/*****************************************************************************
 特殊说明：
    1、该文件是MSP友情协助DSP完成，各种名称对应到沈秀勇所提供的原语
    2、命名规则FOLLOW DSP文档所给规则
    3、后续维护是DSP维护
    4、是否加入返回ERR_CODE待文档评审完毕，我＝目前按照原文档
*****************************************************************************/

#ifndef __DSP_CT_H__
#define __DSP_CT_H__

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

/* DSP CT 命令范围[0x00010000,0x00010F00) */
/* CT命令定义必须为：(0x00010000=<DSP CMDID<0x00010F00) */

/*^FCALIIP2S IDs*/
#define OM_PHY_CT_F_CALIIP2_SET_REQ (0x10220)
#define PHY_OM_CT_F_CALIIP2_SET_CNF (0x10220)
#define PHY_OM_CT_F_CALIIP2_IND (0x10221)

/*^FCALIDCOCS IDs*/
#define OM_PHY_CT_F_CALIDCOCS_SET_REQ (0x10230)
#define PHY_OM_CT_F_CALIDCOCS_SET_CNF (0x10230)
#define PHY_OM_CT_F_CALIDCOCS_IND (0x10231)

/*^FCALITXIQ IDs*/
#define OM_PHY_CT_F_CALITXIQ_SET_REQ (0x10240)
#define PHY_OM_CT_F_CALITXIQ_SET_CNF (0x10240)
#define PHY_OM_CT_F_CALITXIQ_IND (0x10241)

/*^FGAINSTATES IDs*/
#define OM_PHY_CT_F_GAINSTATE_SET_REQ (0x10250)
#define PHY_OM_CT_F_GAINSTATE_SET_CNF (0x10250)

/*^FDBBATTS IDs*/
#define OM_PHY_CT_F_DBBATT_SET_REQ (0x10260)
#define PHY_OM_CT_F_DBBATT_SET_CNF (0x10260)

/*^FBBATTS IDs*/
#define OM_PHY_CT_F_BBATT_SET_REQ (0x10270)
#define PHY_OM_CT_F_BBATT_SET_CNF (0x10270)

#define OM_PHY_CT_TEST_MODE_REQ                      0X10000
#define PHY_OM_CT_TEST_MODE_CNF                      0X10000
#define OM_PHY_CT_TXON_REQ                           0X10020
#define PHY_OM_CT_TXON_CNF                           0X10020
#define OM_PHY_CT_FREQ_SET_REQ                       0X10040
#define PHY_OM_CT_FREQ_SET_CNF                       0X10040
#define OM_PHY_CT_TXPOW_SET_REQ                      0X10060
#define PHY_OM_CT_TXPOW_SET_CNF                      0X10060
#define OM_PHY_CT_VCTCXO_SET_REQ                     0X10080
#define PHY_OM_CT_VCTCXO_SET_CNF                     0X10080
#define OM_PHY_CT_RXON_REQ                           0X100A0
#define PHY_OM_CT_RXON_CNF                           0X100A0
#define OM_PHY_CT_RXANT_SET_REQ                      0X100C0
#define PHY_OM_CT_RXANT_SET_CNF                      0X100C0
#define OM_PHY_CT_AAGC_SET_REQ                       0X100E0
#define PHY_OM_CT_AAGC_SET_CNF                       0X100E0
#define OM_PHY_CT_MEAS_RSSI_REQ                      0X10100
#define PHY_OM_CT_MEAS_RSSI_CNF                      0X10100
#define PHY_OM_CT_RSSI_IND                           0X10110
#define OM_PHY_CT_VOLTAGE_REQ                        0X10111
#define PHY_OM_CT_VOLTAGE_CNF                        0X10111

#define PHY_OM_FAGC_CNF                              0X10112
#define OM_PHY_FAGC_REQ                              0X10112

#define OM_PHY_CT_TSELRF_SET_REQ                     0x10115
#define PHY_OM_CT_TSELRF_SET_CNF                     0x10115

#define OM_PHY_CT_FWAVE_SET_REQ                     0x10116
#define PHY_OM_CT_FWAVE_SET_CNF                     0x10116

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

#define OM_PHY_CT_F_BLK_REQ               (0x101c0)
#define PHY_OM_CT_F_BLK_CNF               (0x101c0)

#define OM_PHY_CT_F_IP2START_REQ          (0x101d0)
#define PHY_OM_CT_F_IP2START_CNF          (0x101d0)

#define PHY_OM_CT_F_IP2_IND               (0x101e0)

#define OM_PHY_CT_F_MAX_POWER_SET_REQ           (0X101f0)
#define PHY_OM_CT_F_MAX_POWER_SET_CNF           (0X101f0)

#define OM_PHY_CT_F_PA_POWER_SET_REQ           (0X101f4)
#define PHY_OM_CT_F_PA_POWER_SET_CNF           (0X101f4)

#define OM_PHY_CT_F_BANDSW_SET_REQ           (0X101f5)
#define PHY_OM_CT_F_BANDSW_SET_CNF           (0X101f5)
#define OM_PHY_CT_F_FDMS_REQ                 (0X101f6)
#define PHY_OM_CT_F_FDMS_CNF                 (0X101f6)
#define CT_F_PA_SET_MAX_NUM              (30)
#define CT_F_POWER_MAX_NUM               (30)
#define CT_F_AAGC_SET_MAX_NUM            (30)
#define CT_F_FREQ_MAX_NUM                (16)
#define CT_F_FREQ_UL_LIST_MAX_NUM        (32)
#define CT_F_FREQ_DL_LIST_MAX_NUM        (32)

#define CT_F_MAX_PA_LEVEL                4

#define CT_F_NOT_START                   0
#define CT_F_READY                       1
#define CT_F_RUNNING                     2
#define CT_F_COMPLETE                    3
#define CT_F_CW_WAVE                     0
#define CT_F_LTE_WAVE                    1
#define CT_F_FDD                         6
#define CT_F_TDD                         7
#define CT_F_MODE_OFFSET                 6
#define CT_F_ONLY_TX                     0
#define CT_F_ONLY_RX                     1
#define CT_F_BOTH_TXRX                   2
#define CT_F_PA_MAX_PWR                3

#define CT_F_HIGH_BAND                    2
#define CT_F_MID_BAND                     1
#define CT_F_LOW_BAND                     0

#define CT_MAX_PWR_CALIBRATE_RUNNING            1
#define CT_MAX_PWR_CALIBRATE_COMPLETE           0

#define CT_MAX_FREQ_NUM                                 16

#define CT_F_PA_OFF                          0
#define CT_F_PA_ON                           1

#define CT_TXEN_OFF                          0
#define CT_TXEN_ON                           1

#define CT_FORCE_TX_OFF                          0
#define CT_FORCE_TX_ON                           1


#define OM_CT_PRIM_NUM                       (23 + 6)

#define BAND_3     3
#define BAND_7     7
#define BAND_20     20
#define BAND_38     38
#define BAND_40     40
#define BAND_41     41

#define     CT_NULL                        (LPHY_NULL)
#define     CT_TRUE                        (LPHY_TRUE)
#define     CT_FALSE                       (LPHY_FALSE)
#define     CT_ERROR                       1

#define   CT_TX_OFF                       0
#define   CT_TX_ON                        1
#define   CT_TX_AFC                       2

#define   CT_F_RX_SYNC_TIME              5

#define   CT_MAX_ANT_NUM                    2
#define   CT_ANT0                           0
#define   CT_ANT1                           1

#define   CT_BIT0                           0x1
#define   CT_BIT1                           0x2

//#define CT_DSP_UP_MAILBOX_MSG_LEN ((LPHY_MAILBOX_CT_UP_SIZE - sizeof(MAIL_BOX_HEAD_STRU))/4)
#define CT_TX_SIN_WAVE_DATA_LEN   32


/*IP2校准支持最大频点数*/
#define CT_F_CALIIP2_MAX_CHAN_NUM 4

/*DCOC校准，AGC档位个数*/
#define CT_F_CALIIP2_CALIDCOCS_AGC_NUM 16

/*GainState参数最大个数*/
#define CT_F_GAINSTATE_MAX_NUM  60 

/*DBB衰减参数最大个数*/
#define CT_F_DBBATT_MAX_NUM CT_F_GAINSTATE_MAX_NUM  

/*BB衰减参数最大个数*/
#define CT_F_BBATT_MAX_NUM_CT CT_F_GAINSTATE_MAX_NUM 



/****************************************************************************************************
描述:   IP2校准，用于^FCALIIP2S
ID:     OM_PHY_CT_F_CALIIP2_SET_REQ,      PHY_OM_CT_F_CALIIP2_SET_CNF,      PHY_OM_CT_F_CALIIP2_IND
结构:   OM_PHY_CT_F_CALIIP2_SET_REQ_STRU, PHY_OM_CT_F_CALIIP2_SET_CNF_STRU, PHY_OM_CT_F_CALIIP2_IND_STU
******************************************************************************************************/
typedef struct  
{
	UINT32 ulMsgId;
	UINT16 usChanNum;
	UINT16 usRsv;
	UINT16 usChan[CT_F_CALIIP2_MAX_CHAN_NUM];
}OM_PHY_CT_F_CALIIP2_SET_REQ_STRU;

typedef struct  
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIIP2_SET_CNF_STRU;

typedef struct 
{ 
	UINT32 ulMsgId;
	UINT16 usChanNum;
	UINT16 usRsv;
	UINT16 usMain_I_DivOff[CT_F_CALIIP2_MAX_CHAN_NUM];
	UINT16 usMain_Q_DivOff[CT_F_CALIIP2_MAX_CHAN_NUM];
	UINT16 usMain_I_DivOn[CT_F_CALIIP2_MAX_CHAN_NUM];
	UINT16 usMain_Q_DivOn[CT_F_CALIIP2_MAX_CHAN_NUM];
	UINT16 usDiv_I[CT_F_CALIIP2_MAX_CHAN_NUM];
	UINT16 usDiv_Q[CT_F_CALIIP2_MAX_CHAN_NUM];
}PHY_OM_CT_F_CALIIP2_IND_STRU;

/****************************************************************************************************
描述:   DCOC校准，用于^FCALIDCOCS
ID:     OM_PHY_CT_F_CALIDCOCS_SET_REQ,      PHY_OM_CT_F_CALIDCOCS_SET_CNF,      PHY_OM_CT_F_CALIDCOCS_IND
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_IND_STRU
******************************************************************************************************/
typedef struct  
{
	UINT32 ulMsgId;
	UINT16 usChannel;
	UINT16 usRsv;
}OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU;

typedef struct  
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU;

typedef struct 
{ 
    UINT32 ulMsgId;
    UINT16 usNOBLK_ANT0_I[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT0_Q[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT0_I[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT0_Q[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT1_I[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usNOBLK_ANT1_Q[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT1_I[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
    UINT16 usBLK_ANT1_Q[CT_F_CALIIP2_CALIDCOCS_AGC_NUM];
}PHY_OM_CT_F_CALIDCOCS_IND_STRU;

/****************************************************************************************************
描述:   TXIQ校准，用于^FTXIQ
ID:     OM_PHY_CT_F_CALITXIQ_SET_REQ,       PHY_OM_CT_F_CALITXIQ_SET_CNF,       PHY_OM_CT_F_CALITXIQ_IND
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU, PHY_OM_CT_F_CALIDCOCS_IND_STRU
******************************************************************************************************/
typedef struct  
{
	UINT32 ulMsgId;
	UINT16 usChannel;
	UINT16 usRsv;
}OM_PHY_CT_F_CALITXIQ_SET_REQ_STRU;

typedef struct  
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_CALITXIQ_SET_CNF_STRU;

typedef struct 
{ 
	UINT32 ulMsgId;
	UINT16 usAmplitude;
	UINT16 usPhase;
	UINT16 usDCI;
	UINT16 usDCQ;
}PHY_OM_CT_F_CALITXIQ_IND_STRU;

/****************************************************************************************************
描述:   设置GainState参数，用于^FGAINSTATES
ID:     OM_PHY_CT_F_GAINSTATE_SET_REQ,       PHY_OM_CT_F_GAINSTATE_SET_CNF   
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU
******************************************************************************************************/
typedef struct  
{
	UINT32 ulMsgId;
	UINT16 usGainStateNum;
	UINT16 usRsv;
	UINT16 usGainState[CT_F_GAINSTATE_MAX_NUM];
}OM_PHY_CT_F_GAINSTATE_SET_REQ_STRU;

typedef struct  
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_GAINSTATE_SET_CNF_STRU;

/****************************************************************************************************
描述:   设置DBB衰减参数，用于^FDBBATTS
ID:     OM_PHY_CT_F_DBBATT_SET_REQ,         PHY_OM_CT_F_DBBATT_SET_CNF   
结构:   OM_PHY_CT_F_CALIDCOCS_SET_REQ_STRU, PHY_OM_CT_F_CALIDCOCS_SET_CNF_STRU
******************************************************************************************************/
typedef struct  
{
	UINT32 ulMsgId;
	UINT16 usDbbAttNum;
	UINT16 usRsv;
	UINT16 usDbbAtt[CT_F_DBBATT_MAX_NUM];
}OM_PHY_CT_F_DBBATT_SET_REQ_STRU;

typedef struct  
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_DBBATT_SET_CNF_STRU;

/****************************************************************************************************
描述:   设置BB衰减参数，用于^FBBATTS
ID:     OM_PHY_CT_F_BBATT_SET_REQ,      PHY_OM_CT_F_BBATT_SET_CNF   
结构:   OM_PHY_CT_F_BBATT_SET_REQ_STRU, PHY_OM_CT_F_BBATT_SET_CNF_STRU
******************************************************************************************************/
typedef struct  
{
	UINT32 ulMsgId;
	UINT16 usBbAttNum;
	UINT16 usRsv;
	UINT16 usBbAtt[CT_F_BBATT_MAX_NUM_CT];
}OM_PHY_CT_F_BBATT_SET_REQ_STRU;

typedef struct  
{
	UINT32 ulMsgId;
}PHY_OM_CT_F_BBATT_SET_CNF_STRU;



/*****************************************************************************
 描述 : MSP收到AT^TMODE命令后判断为非信令模式时下发该原语告知RTT，
        AT命令里其它模式不下发本原语
 ID   : OM_PHY_CT_TEST_MODE_REQ,PHY_OM_CT_TEST_MODE_CNF
 REQ  : OM_PHY_CT_TEST_MODE_REQ_STRU
 CNF  : PHY_OM_CT_TEST_MODE_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;
    /*  1:非信令普通校准  */
    /*  6:非信令快速校准  */
    UINT16 usTMode;     /* 模式配置  */
    UINT16 usRsv;
} OM_PHY_CT_TEST_MODE_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TEST_MODE_CNF_STRU;


/*****************************************************************************
 描述 : 指示物理层打开上行通道。RTT收到该原语上行通道必须一直打开，直至MSP通过本原语关闭上行。
 ID   : OM_PHY_CT_TXON_REQ,PHY_OM_CT_TXON_CNF
 REQ  : OM_PHY_CT_TXON_REQ_STRU
 CNF  : PHY_OM_CT_TXON_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0:表示关闭发射机  */
	/* 1:表示打开发射机，包括基带调制和RF发射通道  */
    /* 2:表示只打开RFIC Transmitter和PA ，BB调制通道不打开，用于VCTCXO校准  */
    UINT16 usTxType;                     /*Tx打开类型*/
    UINT16 usRsv;
} OM_PHY_CT_TXON_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TXON_CNF_STRU;

/*****************************************************************************
 描述 : 若当前发射通道打开（Tx类型为1或2），则RTT认为本原语配置上行频点，若发射通道关闭，
        则认为是下行频点。MSP须将AT^FCHAN命令中的信道号根据36.101协议规定查表转为实际频点值，
        转换过程参考附录4。
 ID   : OM_PHY_CT_FREQ_SET_REQ,PHY_OM_CT_FREQ_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 频点信息  */
    /* 频栅间隔100Khz，如配置值26200对应频点2.62GHz  */
    UINT16 usFreqInfo;                   /*频点信息*/
    UINT16 usULMode;                     /*FDD:6     TDD:7*/
} OM_PHY_CT_FREQ_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FREQ_SET_CNF_STRU;


/*****************************************************************************
 描述 : 配置上行发射功率。RTT收到该原语后应立即改变上行发射功率
 ID   : OM_PHY_CT_TXPOW_SET_REQ,PHY_OM_CT_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 单位：dBm  */
    INT16  sTxPower;                     /*上行发射功率*/
    UINT16 usRsv;
} OM_PHY_CT_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TXPOW_SET_CNF_STRU;

/*****************************************************************************
 描述 : 配置上行发射功率。RTT收到该原语后应立即改变上行发射功率
 ID   : OM_PHY_CT_VCTCXO_SET_REQ,PHY_OM_CT_VCTCXO_SET_CNF
 REQ  : OM_PHY_CT_FREQ_SET_REQ_STRU
 CNF  : PHY_OM_CT_FREQ_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* VCTCXO控制电压		[0,65535]  */
    UINT16 usVctcxoCtrl;                 /*Vctcxo控制字*/
    UINT16 usRsv;
} OM_PHY_CT_VCTCXO_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_VCTCXO_SET_CNF_STRU;

/*****************************************************************************
 描述 : 指示打开物理层接收机。由于物理层在进入非信令模式已打开接收双通道，
        此处收到原语后不做接收处理，直接返回CNF原语
 ID   : OM_PHY_CT_RXON_REQ,PHY_OM_CT_RXON_CNF
 REQ  : OM_PHY_CT_RXON_REQ_STRU
 CNF  : PHY_OM_CT_RXON_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_RXON_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_RXON_CNF_STRU;

/*****************************************************************************
 描述 : 配置RX通道。RTT收到该原语后选定需要进行RSSI折算和上报的接收通道。
      注意RTT在非信令模式下Rx双通道都一直打开。若本原语指示关闭双通道，
      RTT不做任何处理。
 ID   : OM_PHY_CT_RXANT_SET_REQ,PHY_OM_CT_RXANT_SET_CNF
 REQ  : OM_PHY_CT_RXANT_SET_REQ_STRU
 CNF  : PHY_OM_CT_RXANT_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* 0:关闭双通道  */
    /* 1:只打开通道1 */
    /* 2:只打开通道2 */
    /* 3:打开双通道  */
    UINT16 usRxAntType;                  /* RX通道选择 */
    UINT16 usRsv;
} OM_PHY_CT_RXANT_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_RXANT_SET_CNF_STRU;

/*****************************************************************************
AT^TSELRF
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT8  ucPath;
    UINT8  ucGroup;
    UINT16 usRsv;
} OM_PHY_CT_TSELRF_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_TSELRF_SET_CNF_STRU;

/*****************************************************************************
AT^FWAVE
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16 usType;                       /*0:表示continues wave信号*/
    INT16 usPower;                       /*2300:23db*/
} OM_PHY_CT_FWAVE_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_FWAVE_SET_CNF_STRU;
/*****************************************************************************
 描述 : 配置RFIC的AAGC总增益，用于下行AGC表的校准，单位为dB。
      RTT收到该原语后将RFIC的总增益立即改为原语指示的增益值。
 ID   : OM_PHY_CT_AAGC_SET_REQ,PHY_OM_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_AAGC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */

    /* [0,127]	单位:dB。  */
    UINT16 usAAGCValue;                  /* AAGC增益值 */
    UINT16 usRsv;
} OM_PHY_CT_AAGC_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_AAGC_SET_CNF_STRU;

/*****************************************************************************
 描述 :指示RTT启动物理层RSSI测量，用于下行AGC表的校准。RTT收到该原语后启动RSSI
       测量，完成后通过PHY_OM_CT_RSSI_IND原语上报对应RX通道的RSSI测量结果
 ID   : OM_PHY_CT_MEAS_RSSI_REQ,PHY_OM_CT_MEAS_RSSI_CNF
 REQ  : OM_PHY_CT_MEAS_RSSI_REQ_STRU
 CNF  : PHY_OM_CT_MEAS_RSSI_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_MEAS_RSSI_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_MEAS_RSSI_CNF_STRU;
/*****************************************************************************
 描述 :指示启动物理层热敏电阻电压测量，
 ID   :
 REQ  : OM_PHY_CT_VOLTAGE_REQ_STRU
 CNF  : PHY_OM_CT_VOLTAGE_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_CT_VOLTAGE_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT32 ulVoltage;
} PHY_OM_CT_VOLTAGE_CNF_STRU;

/*****************************************************************************
 描述 :指示RTT启动物理层RSSI测量，用于下行AGC表的校准。RTT收到该原语后启动RSSI
       测量，完成后通过PHY_OM_CT_RSSI_IND原语上报对应RX通道的RSSI测量结果
 ID   : PHY_OM_CT_RSSI_IND
 REQ  : NA
 CNF  : NA
 IND  : PHY_OM_CT_RSSI_IND_STRU
 说明 : 
*****************************************************************************/ 

/* usRxANT1ValidFlag	Rx通道1有效标志		[0,1]	0:Rx通道1无效，sRxANT1RSSI值无效*/
/* 1:Rx通道1有效，sRxANT1RSSI值有效*/
/* sRxANT1RSSI	Rx通道1的RSSI		[-110*8,-20*8]	单位:1/8dBm，只在usRxANT1ValidFlag=1有效*/
/* usRxANT2ValidFlag	Rx通道2有效标志		[0,1]	0:Rx通道2无效，sRxANT2RSSI值无效*/
/* 1:Rx通道2有效，sRxANT2RSSI值有效*/
/* sRxANT2RSSI	Rx通道2的RSSI		[-110*8,-20*8]	单位:1/8dBm，只在usRxANT2ValidFlag=1有效*/
typedef struct
{
    UINT32  ulMsgId;
    UINT16  usRxANT1ValidFlag;
    UINT16  usRxANT1RSSI;
    UINT16  usRxANT2ValidFlag;
    UINT16  usRxANT2RSSI;
} PHY_OM_CT_RSSI_IND_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_FAGC_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    INT16 sRsrp;
    INT16 sRsv;
} PHY_OM_FAGC_CNF_STRU;


/*DSP与MSP约定的原语结构*/
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
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT32 ulMode;                       /* MODE TDD：7；FDD：6  */
    UINT16 usUlFreqNum; /* 上行设置的个数，对应ausUlFreqInfo，最多16个  */
    UINT16 usDlFreqNum; /* 下行设置的个数，对应ausDlFreqInfo，最多16个  */

    /* 频点信息，  */
    /* 频栅间隔100Khz，如配置值26200对应频点2.62GHz  */
    UINT16 ausUlFreqInfo[CT_F_FREQ_UL_LIST_MAX_NUM];       /* 上行频点信息  */
    UINT16 ausDlFreqInfo[CT_F_FREQ_DL_LIST_MAX_NUM];       /* 下行频点信息  */
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
typedef struct
{
    UINT32 ulMsgId;                          /* 消息标识 */

    /* 单位：dBm  */
    UINT16 usTxPowerNum;                     /* 指定在asTxPower的个数  */
    UINT16 usRsv;
    /* 发射功率列表，以空格分割，每个值的长度为一个字 ，单位为dBm
    INT16  asTxPower[CT_F_POWER_MAX_NUM];  /*上行发射功率*/
} OM_PHY_CT_F_TXPOW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_TXPOW_SET_CNF_STRU;

/*****************************************************************************
 描述 : 配置使能APT标志
 ID   : OM_PHY_CT_F_TXPOW_SET_REQ,PHY_OM_CT_F_TXPOW_SET_CNF
 REQ  : OM_PHY_CT_F_TXPOW_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_TXPOW_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                          /* 消息标识 */
    UINT32 ulAptEnbFlg;                      /*指示APT是否使能*/
} OM_PHY_CT_F_FDMS_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
} PHY_OM_CT_F_FDMS_CNF_STRU;

/*****************************************************************************
 描述 : 配置RFIC的AAGC总增益，用于下行AGC表的校准，单位为dB。
      RTT收到该原语后将RFIC的总增益立即改为原语指示的增益值。
 ID   : OM_PHY_CT_F_AAGC_SET_REQ,PHY_OM_F_CT_AAGC_SET_CNF
 REQ  : OM_PHY_CT_F_AAGC_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_AAGC_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16 usAagcNum;
    UINT16 usRsv;

    /*取值范围0～255，其中Hi6910的范围为151-234。  */
    UINT8 aucAAGCValue[CT_F_AAGC_SET_MAX_NUM];                  /* AAGC增益值 */
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
typedef struct
{
    /*
    AT指令集-装备定义:
    每个值采用正值表示，精确到0.125dBm定制值信息，取值范围为160~880。
    如果当前的RSSI值为-85.125dBm，范围值为-85.125dbm*(-1)/0.125dbm = 681
    */
    INT16  sRxAnt1Rssi;
    INT16  sRxAnt2Rssi;
} CT_F_RSSI_STRU;

typedef struct
{
    UINT32 ulMsgId;
    UINT16 usFreqNum;
    UINT16 usPowNum;

    CT_F_RSSI_STRU  astRxRssi[CT_F_FREQ_MAX_NUM][CT_F_POWER_MAX_NUM];
} PHY_OM_CT_F_MEAS_RSSI_IND_STRU;

/*****************************************************************************
 描述 : 指示RTT设置PA
 ID   : OM_PHY_CT_F_PA_SET_REQ,PHY_OM_CT_F_PA_SET_CNF
 REQ  : OM_PHY_CT_F_PA_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_PA_SET_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16 usLevelNum;
    UINT16 usRsv;
    UINT8  aucLvlList[CT_F_PA_SET_MAX_NUM];
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
    UINT16 usMeasOffset;                   /* 表示测量起始位置偏移，单位ms，取值范围0~20，无默认值*/
    UINT16 usMeasLen;                      /* 表示测量长度，单位ms，取值范围0~20，无默认值 */
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

    /* 0    CW波型  */
    /* 1    LTE波型  */
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

    /* 0    发送通道校准  */
    /* 1    接收通道校准（接收默认为双通道）  */
    /* 2    发射/接收通道同时校准（接收默认为双通道）  */
    UINT8 ucType;

    UINT8 ucRsv[3];
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

    /* 0    发送通道校准  */
    /* 1    接收通道校准（接收默认为双通道）  */
    /* 2    发射/接收通道同时校准（接收默认为双通道）  */
    UINT8 ucType;

    /* 快速校准状态  */
    /* 0    未启动或执行完毕  */
    /* 1    执行中  */
    UINT8 ucStatus;

    UINT8 ucRsv[2];
} PHY_OM_CT_F_TRIGGER_RD_CNF_STRU;

/*****************************************************************************
 描述 : 查询设置AGC的BLK场景状态
 ID   : OM_PHY_CT_F_BLK_REQ,PHY_OM_CT_F_BLK_CNF       
 REQ  : OM_PHY_CT_F_BLK_REQ_STRU
 CNF  : PHY_OM_CT_F_BLK_CNF_STRU
 IND  : NA
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识   */

    /* 0    BLOCKING 场景  */
    /* 1    NOBLOCKING 场景  */
    UINT16 usISBLKMode;                 /*场景配置   */    
    UINT16 usRsv;
} OM_PHY_CT_F_BLK_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识  */
} PHY_OM_CT_F_BLK_CNF_STRU;


/*****************************************************************************
 描述 : IP2校准
 ID   : OM_PHY_CT_F_IP2START_REQ,PHY_OM_CT_F_IP2START_CNF, PHY_OM_CT_F_IP2START_IND      
 REQ  : OM_PHY_CT_F_IP2START_REQ_STRU
 CNF  : PHY_OM_CT_F_IP2START_CNF_STRU
 IND  : PHY_OM_CT_F_IP2_IND_STRU
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识   */
    UINT16 usBand;                 /* IP2校准band值  */
    UINT16 usRsv;
} OM_PHY_CT_F_IP2START_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识  */
} PHY_OM_CT_F_IP2START_CNF_STRU;


typedef struct
{
    UINT32 ulMsgId;       /*消息标识  */
    INT16 ulIP2Value1;     /*IP2校准结果1  */
    INT16 ulIP2Value2;     /*IP2校准结果2  */
} PHY_OM_CT_F_IP2_IND_STRU;

/*****************************************************************************
 描述 : MAXPOWER校准请求
 ID   : OM_PHY_CT_F_MAX_POWER_SET_REQ,PHY_OM_CT_F_MAX_POWER_SET_CNF     
 REQ  : OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU
 CNF  : PHY_OM_CT_F_MAX_POWER_SET_CNF_STRU
 IND  : NAN
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识   */
    UINT16 usPaLevelNum;                 /*需要校准的PA 档位数目  */
    UINT16 usPaReduceGain;               /*PA回退的档位  */
} OM_PHY_CT_F_MAX_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识  */
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
    UINT32 ulMsgId;                      /* 消息标识   */
    UINT16 usMode;                       /*TDD:7 FDD:6  */
    UINT16 usBand;                       /*band值3 7 20 38 40 41  */
} OM_PHY_CT_F_BANDSW_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识  */
} PHY_OM_CT_F_BANDSW_SET_CNF_STRU;
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
    UINT32 ulMsgId;                      /* 消息标识   */
    UINT16 usPaLevelNum;                /*PA档位数目  */
    UINT16 usRsv;
    INT16 asMaxPwrList[4];              /*校准后的MAXPOWER值  */
} OM_PHY_CT_F_PA_POWER_SET_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;                      /*消息标识  */
} PHY_OM_CT_F_PA_POWER_SET_CNF_STRU;

typedef struct
{
    UINT32 ulMsgId;
}PHY_MSP_CT_SINGLE_CNF_STRU;
typedef struct
{
    UINT16 usCtTestModeFlg;/*测试模式标记 0: 测试模式不使能 1: 测试模式使能*/
    UINT16 usTxTestMode1Flg;/*发送测试模式1使能标记*/
    UINT16 usTXModeFlg;     /*TX发送标记 0:TX未打开 1:TX打开,为改变频率使用*/
    UINT16 usFreq;
    UINT16 usRxBW;
    UINT16 usAGC;
    UINT16 usTxFreq;
    UINT16 usTxBW;
    UINT16 usTxPow;
    UINT16 usRxAntType;/*1:通道1 ；2:通道2 ;3:通道1,2  */
    INT16  sMeasSbNum;
    UINT16 usMeasTask;
    UINT16 usTxPowChangeFlg;
    INT16  sTxPowSbNum;
    UINT16 usTxType;
    UINT16 usVoltageGetFlg;
} DSP_CT_CTRL_INFO_STRU;

/*DSP自定义数据结构*/
typedef struct
{
    UINT16 usWave;                                 /* CW波：0， LTE波：1  */
    UINT16 usSegment;                              /* 发送单一功率时长，单位ms  */

    UINT16 usFreqNum;
    UINT16 ausFreqList[CT_F_FREQ_MAX_NUM];

    UINT16 usPowerNum;
    INT16  asPowerValue[CT_F_POWER_MAX_NUM];

    UINT16 usGainNum;
    UINT16 usGainState[CT_F_GAINSTATE_MAX_NUM];

    INT16  usBbAtt;
    UINT16 usDbbAtt;
    
    UINT16 usPaNum;
    UINT8  aucPaLevel[CT_F_POWER_MAX_NUM];
    UINT32 ulAptEnbFlg;
}CT_F_TX_PARA_STRU;

typedef struct
{
    UINT16 usSegment;                              /*接收单一功率时长，单位ms  */
    UINT16 usMeasOffset;                           /*RSSI测量时刻偏移  */
    UINT16 usMeasTime;                             /*测量时长  */

    UINT16 usFreqNum;
    UINT16 ausFreqList[CT_F_FREQ_MAX_NUM];

    UINT16  usGainNum;
	UINT16  usRsv;
    UINT8  aucRfGain[CT_F_POWER_MAX_NUM];        /*RF增益  */
    UINT16  aucRfControlWord[CT_F_POWER_MAX_NUM];        /*RF 控制字  */
    INT16   aucAagcGain[CT_MAX_ANT_NUM][CT_F_POWER_MAX_NUM];       
}CT_F_RX_PARA_STRU;

typedef struct
{
    UINT16 usTddFddSel;                            /*FDD:6, TDD:7  */
    UINT16 usTxRxSel;                              /*只校TX:0,只校RX: 1,TX RX同时校：2  */
    CT_F_TX_PARA_STRU stTxPara;
    CT_F_RX_PARA_STRU stRxPara;
    UINT16 usBand;
    UINT16 usRsv;
}CT_F_PARA_STRU;

typedef struct
{
    UINT16 usSubFrameCnt;                          /*已测试的子帧计数  */
    UINT16 usSegmentCnt;                           /*校准完成的功率计数  */
    UINT16 usSequenceCnt;                          /*校准完成的频点计数  */
}CT_F_CNT_STRU;

typedef struct
{
    UINT16        usTempReadFlag;                  /*一次温度读取完成标志  */
    UINT16        usTxStatus;                      /*完成：0，正在校准：1  */
    UINT16        usTxSwitchedFlag;                /*已经切换一次标志  */
    CT_F_CNT_STRU stTxCnt;
    UINT16        usTxFreqStatus;                 /*当前校准频点是否有效  */

    UINT16        usRxStatus;                      /*完成：0，正在校准：1
    UINT16        usRxSyncInd;                     /*未与仪器同步上：0,同步上：1  */
    UINT16        usRxSwitchedFlag;                /*已经切换一次标志  */
    CT_F_CNT_STRU stRxCnt;
    UINT16        usRxIsBlk;                       /*Rx快速校准时的情境模式  0:noblocking   1:blocking  */
    UINT16        usIP2Band;                       /*IP2 band值  */
    UINT16        usRFICStatus;
    UINT16        usWaitCnt;
    UINT16        usMaxPwrInd;                    /*指示正在进行max Power校准 此校准会复用Tx校准的数据结构  */
    UINT16        usPaReduceGain;                 /*校准maxpower时PA回退的档位  */
    UINT16        usIp2CalStatus;
    UINT16        usDcocsCalStatus;
    UINT16        usTxiqCalStatus;
}CT_F_CTRL_STRU;

typedef struct
{
    UINT16 usTxPowerSwitchCnt;
    UINT16 usTxFreqSwitchCnt;
    UINT16 usTxSubFrameCnt;
    UINT16 usRxPowerSwitchCnt;
    UINT16 usRxFreqSwitchCnt;
    UINT16 usRxSubFrameCnt;
}CT_F_DEBUG_STRU;

typedef struct
{
	UINT8 usTmodeError;/*校准模式错误*/
	UINT8 usSetPaLevelError;/*设置PA时档位参数错误*/
	UINT8 usUpMailBoxFullError;/*上报邮箱满了*/
	UINT8 usPaSwitchTypeError;/*切换PA 目标状态参数错误*/
	UINT8 usPaSwitchBandError;/*切换PA band不支持*/
	UINT8 usTxTypeError;/*不等于CT_TX_ON CT_TX_OFF CT_TX_AFC*/
	UINT8 usRsv[2];
}CT_F_ERROR_TYPE_STRU;

   
typedef struct
{
    UINT32  ulMsgId;
    UINT16  usTempNum;                  /* 温度值个数  */
    UINT16  usType;                         /* TX: 0  RX: 1 TXRX: 2  */
    UINT16  ausVol4Temp[CT_F_FREQ_MAX_NUM]; /* 以电压表征的温度值  */
}PHY_OM_CT_F_MEAS_CMTMS_IND_STRU;


typedef struct
{
    UINT32 enMsgId;
    UINT16 usOpId;
    UINT8  aucRsv[2];
}LMAC_PHY_TEMP_REQ_STRU;

typedef struct
{
    UINT32 enMsgId;
    UINT16 usOpId;
    INT16  sCurrentTemp;
}LMAC_PHY_TEMP_IND_STRU;

typedef struct
{
    UINT16 usOpId;
    UINT16 usReq;
    INT16  sTemp;
    UINT16 usVol;
}UL_MAC_GET_TEMP_STRU;

typedef struct
{
    UINT32 ulMsgID;
    void (*pfFunc)(UINT32*);
    UINT32 ulCount;
}OM_CT_PRIMITIVE_STRU;

/* CT上报邮箱结构体定义 */
//typedef struct
//{
//    MAIL_BOX_HEAD_STRU MailBoxHead;         /* 邮箱头*/
//    UINT32             aMessage[CT_DSP_UP_MAILBOX_MSG_LEN]; /* 消息帧,用于存储原语和该原语长度  */
//} CT_DSP_UP_MAIL_BOX_STRU;

#endif

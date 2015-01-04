

/*****************************************************************************
 特殊说明：
    1、该文件是MSP友情协助DSP完成，各种名称对应到沈秀勇所提供的原语
    2、命名规则FOLLOW DSP文档所给规则
    3、后续维护是DSP维护
    4、是否加入返回ERR_CODE待文档评审完毕，我＝目前按照原文档
*****************************************************************************
*****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

*****************************************************************************
  文 件 名   : dsp_ct.h
  版 本 号   : V1.0 
  生成日期   : 2008年07月07日
  功能描述   : 该文件定义了DD800中CT，MSP和DSP交互的原语及其参数和描述。
  修改历史   : 
  1.日    期 : 2008年07月07日
    修改内容 : 创建文件 

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

/* DSP CT 命令范围[0x00010000,0x00010F00)*/
/* CT命令定义必须为：(0x00010000=<DSP CMDID<0x00010F00)*/
#define OM_PHY_CT_TEST_MODE_REQ		                 0X10000
#define PHY_OM_CT_TEST_MODE_CNF		                 0X10000
#define OM_PHY_CT_TXON_REQ	                         0X10020
#define PHY_OM_CT_TXON_CNF		                     0X10020
#define OM_PHY_CT_FREQ_SET_REQ	                     0X10040
#define PHY_OM_CT_FREQ_SET_CNF		                 0X10040
#define OM_PHY_CT_TXPOW_SET_REQ	                     0X10060
#define PHY_OM_CT_TXPOW_SET_CNF		                 0X10060
#define OM_PHY_CT_VCTCXO_SET_REQ	                 0X10080
#define PHY_OM_CT_VCTCXO_SET_CNF		             0X10080
#define OM_PHY_CT_RXON_REQ	                         0X100A0
#define PHY_OM_CT_RXON_CNF		                     0X100A0
#define OM_PHY_CT_RXANT_SET_REQ	                     0X100C0
#define PHY_OM_CT_RXANT_SET_CNF		                 0X100C0
#define OM_PHY_CT_AAGC_SET_REQ	                     0X100E0
#define PHY_OM_CT_AAGC_SET_CNF		                 0X100E0
#define OM_PHY_CT_MEAS_RSSI_REQ	                     0X10100
#define PHY_OM_CT_MEAS_RSSI_CNF		                 0X10100
#define PHY_OM_CT_RSSI_IND		                     0X10110

/* 温度获取接口*/
#define OM_PHY_CT_VOLTAGE_REQ		                 0X10111
#define PHY_OM_CT_VOLTAGE_CNF		                 0X10111

/* AT^FAGC*/
#define OM_PHY_FAGC_REQ		                         0X10112
#define PHY_OM_FAGC_CNF		                         0X10112

#define OM_PHY_CT_FPA_SET_REQ                        0x10113 /*AT^FPA*/
#define PHY_OM_CT_FPA_SET_CNF                        0x10113

#define OM_PHY_CT_FDAC_SET_REQ                       0x10114 /*AT^FDAC*/
#define PHY_OM_CT_FDAC_SET_CNF                       0x10114


#define OM_PHY_CT_TSELRF_SET_REQ                     0x10115 /*AT^TSELRF*/
#define PHY_OM_CT_TSELRF_SET_CNF                     0x10115
 
/* 工控打开原语*/
/* 对应 Polaris V100R001 全系统和装备版本合一方案自肖军*/
/* 不归属CT命令*/
#define OM_PHY_POWER_CONFIG_REQ                      0x0053
#define PHY_OM_POWER_CONFIG_CNF                      0x0053


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
    
    /*1: 非信令普通校准模式*/
    /*6：非信令快速校准模式*/
    UINT16 usTMode;     /* 模式配置*/
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
    
    /* 0:表示关闭发射机*/
	  /* 1:表示打开发射机，包括基带调制和RF发射通道*/
    /* 2:表示只打开RFIC Transmitter和PA ，BB调制通道不打开，用于VCTCXO校准*/
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
    
    /* 频点信息，*/
    /* 频栅间隔100Khz，如配置值26200对应频点2.62GHz*/
    UINT16 usFreqInfo;                   /*频点信息*/
    UINT16 usMode;    /*6,FDD;7,TDD */
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

    /* 单位：dBm*/
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

    /* VCTCXO控制电压		[0,65535]*/
    UINT16 usVctcxoCtrl;                 /*Vctcxo控制字*/
    UINT16 usRsv;                        
} OM_PHY_CT_VCTCXO_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;  
} PHY_OM_CT_VCTCXO_SET_CNF_STRU;

/*****************************************************************************/

/*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT8  ucLevel;
    UINT8  ucPading[3];
                      
} OM_PHY_CT_FPA_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;  
} PHY_OM_CT_FPA_SET_CNF_STRU;


/*****************************************************************************

*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
    UINT16  usApc;
    UINT16  usRsv;
                      
} OM_PHY_CT_FDAC_SET_REQ_STRU;


typedef struct
{
    UINT32 ulMsgId;  
} PHY_OM_CT_FDAC_SET_CNF_STRU;


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

    /* 0:关闭双通道*/
    /* 1:只打开通道1*/
    /* 2:只打开通道2*/
    /* 3:打开双通道*/
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

    /* [0,127]	单位:dB。*/
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
    UINT32 ulMsgId;  
    UINT16 usRxANT1ValidFlag;
    INT16  sRxANT1RSSI;
    UINT16 usRxANT2ValidFlag;
    INT16  sRxANT2RSSI;
} PHY_OM_CT_RSSI_IND_STRU;

/* OM_PHY_POWER_CONFIG_REQ*/
/* PHY_OM_POWER_CONFIG_CNF*/
typedef struct
{
    UINT32 ulPuschPwrCtrlSwitch :2; /*0：关闭功控 1：打开功控/关闭闭环  3：打开功控/打开闭环 2：功控打桩BT时，配3*/
    UINT32 ulPucchPwrCtrlSwitch :2; /*0：关闭功控 1：打开功控/关闭闭环  3：打开功控/打开闭环 2：功控打桩BT时，配3*/
    UINT32 ulSrsPwrCtrlSwitch   :2; /*0：关掉功控 1：打开功控 2：功率打桩 其它无效 BT时，配1*/
    UINT32 ulPrachPwrCtrlSwitch :2; /*0：关掉功控 1：打开功控 2：功率打桩 其它无效BT时，配1*/
    UINT32 ulFreqCmpnstSwitch :1;   /*0：关掉频率补偿 1:打开频率补偿BT时，配1*/
    UINT32 ulTempCmpnstSwitch :1;   /*0：关掉温度补偿 1:打开温度补偿BT时，配1*/
    UINT32 ulSpare :22;
}PHY_OM_UPLINK_PWR_CTRL_STRU;

typedef struct
{
    UINT32 ulMsgId;
    PHY_OM_UPLINK_PWR_CTRL_STRU stulPwrCtrlFlag;
    INT16  sPucchTxPower;
    INT16  sPuschTxPower;
    INT16  sSrsTxPower;
    INT16  sPrachTxPower;
}OM_PHY_POWER_CONFIG_REQ_STRU;

/*****************************************************************************
 描述 : AGC查询
 ID   : OM_PHY_FAGC_REQ,PHY_OM_FAGC_CNF
 REQ  : OM_PHY_FAGC_REQ_STRU
 CNF  : PHY_OM_FAGC_CNF_STRU
 说明 :
*****************************************************************************/
typedef struct
{
    UINT32 ulMsgId;                      /* 消息标识 */
} OM_PHY_FAGC_REQ_STRU;

typedef struct
{
    UINT32 ulMsgId;
    INT16 sRsrp;
    INT16 sRsv;
} PHY_OM_FAGC_CNF_STRU;


#endif

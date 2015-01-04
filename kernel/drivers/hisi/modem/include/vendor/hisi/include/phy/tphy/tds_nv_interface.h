/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tds_nv_interface.h
  版 本 号   : 初稿
  生成日期   : 2013年3月25日
  最近修改   :
  功能描述   : TDS nv 头文件
  函数列表   :

  修改历史   :
  1.日    期   : 2013年3月25日
    修改内容   : 创建文件

*****************************************************************************

******************************************************************************/
#ifndef __TDS_NV_INTERFACE_H__
#define __TDS_NV_INTERFACE_H__

#ifdef __cplusplus
extern "C" {
#endif


#ifndef LPS_RTT
#include "vos.h"
#else
#include "type_define.h"
#endif

#include "tds_dsp_equip_interface.h"

#define RFIC_VERSION_V210               (210)

#define TDS_RF_SUPPORT_BAND_NUM  	  		 2
/* BEGIN: Added by w00180842, 2013/8/29   PN:tuner*/
#define TDS_TUNER_SUPPORT_SENSOR_NUM  	  	 8
#define TDS_TUNER_DAC_MAX                    6
#define TDS_TUNER_CONTROL_MAX                4
#define TDS_TUNER_CMD_MAX      (TDS_TUNER_DAC_MAX + TDS_TUNER_CONTROL_MAX)
/* END:   Added by w00180842, 2013/8/29 */
/*前端相关NV begin*/
/*天线开关bitmap*/
typedef enum
{
    TDS_ANTSEL_INDEX_RX0    = 0x0000000,
    TDS_ANTSEL_INDEX_RX1    = 0x1000000,
    TDS_ANTSEL_INDEX_TX     = 0x2000000,
    TDS_ANTSEL_INDEX_3      = 0x3000000
}TDS_ANTSEL_INDEX_ENUM;


typedef struct
{
    UINT16 usRxMainLnaSel; //射频主通道LNA选择
    UINT16 usRxDvtyLnaSel;
    UINT16 usTxLnaSel;
    UINT16 usResv;
}TDS_RF_PRIVATE_CHANNEL_CFG_STRU;


typedef struct
{
    UINT32 ulAbb0RstBitMap;
    UINT32 ulAbb0RxAEnBitMap;
    UINT32 ulAbb0RxBEnBitMap;
    UINT32 ulAbb0TxEnBitMap;
    UINT32 ulRxABSwapBitMap;
    UINT32 ulRssiCalBitMap;
    UINT32 ulAdOn1BitMap;

}TDS_ABB_LINECTRL_BITMAP_STRU;


typedef struct
{
    UINT16 usCoreSel;    //接收通道Core选择
    UINT16 usDivider;    //接收通道分频选择
    //UINT16 usTxCoreSel;
    //UINT16 usTxDivider;
}TDS_RF_PRIVATE_CORE_DIV_CFG_STRU;
typedef enum
{
    TDS_RF_CH0,
    TDS_RF_CH1,
}TDS_RF_CH_SEL_ENUM;
typedef UINT16 TDS_RF_CH_SEL_ENUM_UINT16;


typedef struct
{
    UINT16 usRfRxOnAdvanceTime;
    UINT16 usRfTxOnAdvanceTime;
    UINT16 usFreqSWAdvanceTime;
    UINT16 usFirRxEnAdvanceTime;
    UINT16 usFirTxEnAdvanceTime;
    UINT16 usMidAdvanceTime;
    UINT16 usABBAdOnAdvanceTime;
    UINT16 usABBDaOnAdvanceTime;
    UINT16 usPaEnAdvanceTime;
    UINT16 usTxEnAdvanceTime;
    UINT16 usAntSelAdvanceTime;
    TDS_RF_CH_SEL_ENUM_UINT16 enChannelSel;
}TDS_NV_RF_ADVANCE_TIME_STU;

typedef struct
{
    UINT32 ulAntSelCfg0;
    UINT32 ulAntSelCfg1;
    UINT32 ulAntSelCfg2;
    UINT32 ulAntSelCfg3;
}TDS_ANTSEL_ALLOT_STRU;

typedef struct
{

    UINT8  aucPaVal[4];/*支持的pa档位的配置值 默认数组0 1 2代表高中低*/
}TDS_PA_LEVEL_STRU;


/*线控生效配置bitmap，该map根据硬件连接而确定*/
typedef struct
{
    UINT32 aulCtuPaMaxConfig[8];
    UINT32 ulBandNumSupt;  //支持band数目
    UINT32 aulBandList[TDS_RF_SUPPORT_BAND_NUM];     //支持band列表
    UINT32 aulPaEnAllot[TDS_RF_SUPPORT_BAND_NUM]; /*pa en 映射的bit位置*/
    UINT32 aulPaAtt0Allot[TDS_RF_SUPPORT_BAND_NUM];/*pa att0 映射的bit位置*/
    UINT32 aulPaAtt1Allot[TDS_RF_SUPPORT_BAND_NUM];/*pa att1 映射的bit位置*/
    TDS_PA_LEVEL_STRU astPaVal[TDS_RF_SUPPORT_BAND_NUM];/*不同ｂａｎｄ不同档位的真值*/
    TDS_ANTSEL_ALLOT_STRU astAntSelAllot[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_LINECTRL_ALLOT_BY_HARDWARE_STRU;

typedef struct
{
    UINT16      ulRficVersion;    //单板形态 备用
    UINT16      ulBandNumSupt;  //支持band数目
    UINT16      aulBandList[TDS_RF_SUPPORT_BAND_NUM];     //支持band列表
    TDS_RF_PRIVATE_CHANNEL_CFG_STRU  astRfChanCfg[TDS_RF_SUPPORT_BAND_NUM];//射频通道配置
    TDS_RF_PRIVATE_CORE_DIV_CFG_STRU astRfCoreAndDivSel[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_RFIC_CFG_STRU;
/*前端相关NV end*/


    /* rx tx  nv  start   */
typedef struct
{
    TDS_BAND_COMMON_PARA_STRU astCommon[TDS_RF_SUPPORT_BAND_NUM];
    TDS_BAND_RXPATH_PARA_STRU astRxPara[TDS_RF_SUPPORT_BAND_NUM];
    TDS_BAND_TXPATH_PARA_STRU astTxPara[TDS_RF_SUPPORT_BAND_NUM];
}TDS_NV_RXTX_PARA_STRU;

    /* rx tx nv end   */
     
/* BEGIN: Added by w00180842, 2013/8/16   PN:tuner*/
    
 /*MIPI写命令格式如下
31--29  001  ---->指令类型
28--25  0111 ---->SLAVE ADDRESS
24--22  010  ---->cmd
21--17         ---->addr 例如0x1c,0x00等
16                ---->17--24的校验位
15--8           ---->配置的数据
7                  ---->15---8的校验位
6--0             ---->保留位
 aulControlCfgPara[i] 需按照上述BIT位全部写入
 usDacCmd    15--0依次对应上述 31--16BIT位写入
 ausDacData[j][k]15---0依次对应上述15--0BIT位写入
 */
typedef struct 
{
    UINT16 usDacCmd;
    UINT16 usRev;
    UINT16 ausDacData[TDS_RF_SUPPORT_BAND_NUM][TDS_TUNER_SUPPORT_SENSOR_NUM];//BAND顺序与BAND列表相同
}TDS_TUNER_DAC_CFG_PARA_STRU;
typedef struct 
{
    UINT16 usDacCfgNum;//必须与ox00寄存器中DAC使能的个数一致
    UINT16 usRev;
    TDS_TUNER_DAC_CFG_PARA_STRU stDacCfgPara[TDS_TUNER_DAC_MAX];
}TDS_TUNER_DAC_CFG_STRU;
 typedef struct 
 {
     UINT16 usControlCfgNum;//最大值为4，SLEEP MODE 目前默认配置一个(0x1c)，activeMODE 默认配置3个
     UINT16 usRev;
     UINT32 aulControlCfgPara[TDS_TUNER_CONTROL_MAX];//配置时从0--5依次配置，0-->0x1c, 1-->0x10, 2-->0x0，其他依次放置
 }TDS_TUNER_CONTROL_CFG_STRU;
typedef struct 
{
    TDS_TUNER_CONTROL_CFG_STRU stControlCfg;
    TDS_TUNER_DAC_CFG_STRU stDacCfg;
}TDS_TUNER_MIPI_ACTIVE_MODE_CMD_STRU;
typedef struct 
{
    TDS_TUNER_CONTROL_CFG_STRU stControlCfg;
}TDS_TUNER_MIPI_SLEEP_MODE_CMD_STRU;
typedef struct 
{
    UINT16 usTunerValidFlag;//1--支持   0--不支持
    UINT16 usCfgTimeAdv;//时间提前量
    UINT16 usRev;
    UINT16 usBandNum;//支持的BAND数
    UINT16 ausBandList[TDS_RF_SUPPORT_BAND_NUM];//BAND列表
    TDS_TUNER_MIPI_SLEEP_MODE_CMD_STRU stSleepModeCfg;
    TDS_TUNER_MIPI_ACTIVE_MODE_CMD_STRU stActiveModeCfg;
}TDS_NV_TUNER_PARA_STRU;

typedef struct
{
    UINT16 usTdsDrxIdleEnableFlag;
    UINT16 usTdsDrxSwitch32kTime;
    UINT16 usTdsClkMeasParaIndex;
    UINT16 usTdsPresyncStartGate;
    UINT16 usTdsDrxIdleWaitTaskTime;
    UINT16 usTdsDrxIdleClkMeasStubFlag;
    UINT16 usTdsDrxIdleSleepStubFlag;
    UINT16 usTdsDrxSlaveEnableFlag;
    UINT16 usRsvd[4];
}TDS_NV_DRX_PARA_STRU;

typedef struct
{
    TDS_NV_RFIC_CFG_STRU stRficCfg;
    TDS_NV_LINECTRL_ALLOT_BY_HARDWARE_STRU stLineCtrlMapped;
    TDS_NV_RF_ADVANCE_TIME_STU stTdsTimer;
    TDS_NV_RXTX_PARA_STRU stRxTxPara;
    /* BEGIN: Added by w00180842, 2013/8/16   PN:tuner*/
    TDS_NV_TUNER_PARA_STRU stTunerPara;
    /* END:   Added by w00180842, 2013/8/16 */
    /* BEGIN: Added by x00228734, 2013/9/30*/
    TDS_NV_DRX_PARA_STRU stTdsDrxPara;
    /* END: Added by x00228734, 2013/9/30*/
    UINT16 usVctcxoInit;
    UINT16 usResv;
}TDS_NV_STRU;

/*私有nv*/
typedef struct
{
    UINT32 ulRes;
}TDS_NV_PRIVATE_STRU;

typedef struct
{
    UINT16      usCurrBand;
    UINT16      usLineCfgIndex;    //单板形态 备用
    UINT16      usRfCfgIndex;  //支持band数目
    UINT16      usResv;
}TDS_NV_INDEX_STRU;


extern TDS_NV_STRU * gpstTdsV9NvPara;
extern TDS_NV_INDEX_STRU            gstNvCfgInd;

TDS_BAND_TXPATH_PARA_STRU * TDS_GetTxNv(void);
TDS_PA_LEVEL_THRE_STRU * TDS_GetPaTreNv(void);
TDS_BAND_RXPATH_PARA_STRU * TDS_GetRxNv(void);
TDS_TEMPERATURE_SENSOR_STRU * TDS_GetSensorNv(void);
TDS_AGC_BAND_PARA_STRU * TDS_GetAgcBandNv(void);
/*begin: z00165872 ct*/
UINT16  TDS_GetRxMainLnaSel(UINT32 ulBandIdx);
UINT16  TDS_GetRxDvtyLnaSel(UINT32 ulBandIdx);
UINT16  TDS_GetTxLnaSel(UINT32 ulBandIdx);
TDS_RF_PRIVATE_CORE_DIV_CFG_STRU*  TDS_GetCoreDivCfg(UINT32 ulBandIdx);
TDS_RF_TXIQ_CAL_STRU* TDS_GetTxiqFromNv(void);
UINT16 TDS_GetDcocComFromNv(UINT16 usGainCode);
TDS_NV_TUNER_PARA_STRU * TDS_GetTunerNv(void);
TDS_NV_DRX_PARA_STRU * TDS_GetTdsDrxNv(void);
static inline TDS_RF_CH_SEL_ENUM_UINT16 TDS_MEAS_GetTdsCtuChNum(void)
{
    return gpstTdsV9NvPara->stTdsTimer.enChannelSel;
}
/*end: z00165872 ct*/
#ifdef __cplusplus
}/*end of extern C*/
#endif
#endif


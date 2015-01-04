/*****************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

*****************************************************************************
  文 件 名   : msp_cfg.h
  版 本 号   : V1.0
  生成日期   : 2008年07月07日
  功能描述   : 配置相关接口.
  函数列表   : CFG_Init
               CFG_GetDaigCfgTable
  修改历史   :
  1.日    期 : 2008年07月07日
    修改内容 : 创建文件
  2.日    期 : 2009年03月17日
    修改内容 : 添加CFG_DIAG_RAM_SWITCH数据结构定义.

*****************************************************************************/

#ifndef __MSP_CFG_H__
#define __MSP_CFG_H__

#include "vos.h"


#define L4A_AUTHDATA_UNDEFIEND               (0)
#define L4A_AUTHDATA_DEFIEND                 (1)

#define L4A_AUTHDATA_MAX_USERNAME_LEN        (127)
#define L4A_AUTHDATA_MAX_PASSWORD_LEN        (127)

#define L4A_AUTHDATA_AUTHTYPE_NONE           (0)
#define L4A_AUTHDATA_AUTHTYPE_PAP            (1)
#define L4A_AUTHDATA_AUTHTYPE_CHAP           (2)
#define L4A_AUTHDATA_AUTHTYPE_BUTT           (0xFF)

typedef struct
{
    VOS_UINT32 ulSocpDelayWriteFlg;/* SOCP延迟写入功能启动标记 */
    VOS_UINT32 ulGuSocpLevel;      /* GU SOCP目的BUFFER发送水线 */
    VOS_UINT32 ulLSocpLevel;       /* L SOCP目的BUFFER发送水线 */
    VOS_UINT32 ulTimeOutValue;     /* SOCP目的BUFFER的超时时间 */
}NV_SOCP_LOG_CFG_STRU;

/*NV项的ID定义*/
typedef enum
{
    EN_NV_ID_AUTHORITY_VER = 0xD009,    /*  一键式升级鉴权版本号*/
    EN_NV_ID_AUTHORITY_TYPE = 0xD00a,  /*一键式升级缱绻类型*/

    EN_NV_ID_MSP_AUTHDATA_1 = 0xD00b,   /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_2 = 0xD00c,   /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_3 = 0xD00d,   /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_4 = 0xD00e,   /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_5 = 0xD00f,   /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_6 = 0xD010,  /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_7 = 0xD011,  /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_8 = 0xD012,  /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_9 = 0xD013,  /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_10 = 0xD014, /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_11 = 0xD015, /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_12 = 0xD016, /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_13 = 0xD017, /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_14 = 0xD018, /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_15 = 0xD019, /* ^AUTHDATA*/
    EN_NV_ID_MSP_AUTHDATA_16 = 0xD01a, /* ^AUTHDATA*/
    EN_NV_ID_MSP_CSIM        = 0xD003, /* +CRSM*/
    EN_NV_ID_RSRP_CFG        = 0xD004,
	EN_NV_ID_ECIO_CFG        = 0xD005,
    EN_NV_ID_RSCP_CFG        = 0xD006,
    EN_NV_ID_FLASH_LESS_MID_THRED = 0xD007,

    EN_NV_ID_AGENT_FLAG = 0xD008,

    EN_NV_ID_PWC_SWITCH = 0xD10B,

    EN_NV_ID_SOCP_LOG_CFG = 0xD009,
    EN_NV_ID_TMODE_RAT       = 0xD0EF,
 	EN_NV_ID_IMEI                       = 0,
    EN_NV_ID_BOARD_PLATFORM  = 0xE514,
    EN_NV_ID_SYS_TIME        = 0xD101,
	
	EN_NV_ID_CURC_RPT_INIT = 50025,

	EN_NV_ID_UDP_TYPE					=0xE517,
    NV_ID_TDS_TX_PA_POWER_BAND_A        = 0xF8f0,
    NV_ID_TDS_TX_APC_COMP_BAND_A        = 0xF8f1,
    NV_ID_TDS_TX_APC_FREQ_COMP_BAND_A   = 0xF8f2,
    NV_ID_TDS_RX_AGC_COMP_BAND_A        = 0xF8f3,
    NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_A   = 0xF8f4,
    NV_ID_TDS_TX_PA_POWER_BAND_E        = 0xF8f5,
    NV_ID_TDS_TX_APC_COMP_BAND_E        = 0xF8f6,
    NV_ID_TDS_TX_APC_FREQ_COMP_BAND_E   = 0xF8f7,
    NV_ID_TDS_RX_AGC_COMP_BAND_E        = 0xF8f8,
    NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_E   = 0xF8f9,
    NV_ID_TDS_TX_PA_POWER_BAND_F        = 0xF8fa,
    NV_ID_TDS_TX_APC_COMP_BAND_F        = 0xF8fb,
    NV_ID_TDS_TX_APC_FREQ_COMP_BAND_F   = 0xF8fc,
    NV_ID_TDS_RX_AGC_COMP_BAND_F        = 0xF8fd,
    NV_ID_TDS_RX_AGC_FREQ_COMP_BAND_F   = 0xF8fe,
    EN_NV_ID_END    = 0XFFFF

} MSP_NV_ITEM_ID_ENUM;

typedef struct
{
   VOS_INT16 ssLevel[4];
   VOS_INT16 ssValue[4];
}NV_ITEM_RSRP_CFG_STRU;

typedef struct
{
    VOS_INT16 ssLevel[4];
    VOS_INT16 ssValue[4];
}NV_ITEM_ECIO_CFG_STRU;

typedef struct
{
   VOS_INT16 ssLevel[4];
   VOS_INT16 ssValue[4];
}NV_ITEM_RSCP_CFG_STRU;
typedef struct
{
    VOS_UINT16 usURCSWT;
    VOS_UINT16 usPeriod;
}NV_ITEM_MSP_URC_STRU;

typedef struct
{
    VOS_UINT8 aucBuildTime[32];
    VOS_UINT8 aucSwVer[32];
}NV_ITEM_SW_VER_STRU;

typedef struct
{
    VOS_UINT32 ulTmodeRat;
}NV_ITEM_TMODE_RAT_STRU;

typedef struct
{
    VOS_UINT32 ulAgentFlag; /*：1，路测 0 非路测*/
	VOS_UINT8 ulRandData[256];  /*鉴权随机数校验码*/
}NV_ITEM_AGENT_FLAG_STRU;

typedef struct PWC_SWITCH_STRU
{
    VOS_UINT deepsleep  :1; /*bit 0*/
    VOS_UINT lightsleep :1; /*bit 1*/
    VOS_UINT dfs        :1; /*bit 2*/
    VOS_UINT hifi       :1; /*bit 3*/
    VOS_UINT drxAbb     :1; /*bit 4*/
    VOS_UINT drxZspCore :1; /*bit 5*/
    VOS_UINT drxZspPll  :1; /*bit 6*/
    VOS_UINT drxWLBbpPll :1; /*bit 7*/
    VOS_UINT drxGBbpPll :1; /*bit 8*/
    VOS_UINT drxRf      :1; /*bit 9*/
    VOS_UINT drxPa      :1; /*bit 10*/
    VOS_UINT drxGuBbpPd :1; /*bit11*/
	VOS_UINT drxDspPd   :1; /*bit12*/
	VOS_UINT drxLBbpPd  :1; /*bit13*/
    VOS_UINT drxPmuEco  :1; /*bit14*/
	VOS_UINT drxBbpTest :1; /*bit15*/
    VOS_UINT mntn       :1; /*bit 16*/
    VOS_UINT bugChk     :1; /*bit 17*/
	VOS_UINT reserved1   :14; /*bit 18-31*/

}NV_ITEM_PWC_SWITCH_STRU;


typedef struct
{
    VOS_UINT32 UdpValue;
}NV_UDP_TYPE_STRU;



#endif /* __MSP_CFG_H__*/


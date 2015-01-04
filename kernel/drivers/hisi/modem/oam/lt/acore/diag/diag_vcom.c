/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_vcom.c
  Description     :
  History         :
     1.y00228784       2013-7-25   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "diag_port.h"

VOS_VOID diag_VcomInfo_Init(VOS_VOID)
{
	/*VCOM CTRL*/
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_CTRL].ucChanStat        = ACM_EVT_DEV_SUSPEND;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_CTRL].ucHdlcFlag        = EN_HDLC_DATA;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_CTRL].ulCodeDesChanId   = SOCP_CODER_DST_LOM_CNF;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_CTRL].ulDecodeSrcChanId = SOCP_DECODER_SRC_LOM;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_CTRL].ulRecivBufLen     = 0;
    g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_CTRL].slPortHandle      = UDI_INVALID_HANDLE;

	/*VCOM IND*/
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_APP].ucChanStat         = ACM_EVT_DEV_SUSPEND;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_APP].ucHdlcFlag         = EN_HDLC_DATA;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_APP].ulCodeDesChanId    = SOCP_CODER_DST_LOM_IND;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_APP].ulDecodeSrcChanId  = 0;
	g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_APP].ulRecivBufLen      = 0;
    g_diagPort[EN_DIAG_VCOM_BEABER_DIAG_APP].slPortHandle       = UDI_INVALID_HANDLE;

}


VOS_UINT32 diag_VcomWriteSync(DIAG_PORT_PHY_BEAR_ENUM enPort,
                                 APP_VCOM_DEV_INDEX_UINT8 enDevIndex,
                                 VOS_UINT8 *pucDataBuf,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;

    diag_TraceDebug(pucDataBuf, ulLen);

    ulRet = APP_VCOM_Send(enDevIndex,pucDataBuf,ulLen);
    if(ulRet)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_APPVCOM_SEND_ERR,ulRet,0,0);
    }
    SCM_RlsDestBuf(DIAG_PORT_GET_CODE_DES(enPort),ulLen);

    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_VcomRead
 Description     : 注册给TAF的回调函数，用于读取VCOM口下发的数据
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Y00228784      2013-7-25  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_VcomRead(VOS_UINT8 ucDevIndex, VOS_UINT8 *pData, VOS_UINT32 uslength)
{
    VOS_INT32 ulRet = ERR_MSP_SUCCESS;
    if((ucDevIndex != DIAG_APPVCOM_CHAN_CTRL)||(NULL == pData)||(0 == uslength))
    {
        diag_printf("[%s]:INVALID PARAMETER ! ucDevIndex :0x%x,uslength :0x%x\n",__FUNCTION__,ucDevIndex,uslength);
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_APPVCOM_READ_ERR,0, uslength, 1);
        return ERR_MSP_INVALID_PARAMETER;
    }
    diag_TraceDebug(pData, uslength);

    /*设置当前物理通道及通道连接状态*/
    DIAG_PORT_PORT_SWITCH(EN_DIAG_VCOM_BEABER_DIAG_CTRL);

    ulRet = SCM_SendDecoderSrc(SOCP_DECODER_SRC_LOM,pData,uslength);
    if(ulRet != ERR_MSP_SUCCESS)
    {
        diag_printf("[%s]:SCM_SendDecoderSrc fail ! ulRet :0x%x\n",__FUNCTION__,ulRet);
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_APPVCOM_READ_ERR,ulRet, 0, 2);
        return ulRet;
    }
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 Function Name   : diag_VcomInit
 Description     : HISC通道初始化
 Input           :VOS_VOID
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Y00228784      2013-7-25  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_VcomInit(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_VCOM_EXT)
    diag_VcomInfo_Init();
    /*注册APP VCOM读回调*/
    APP_VCOM_RegDataCallback(DIAG_APPVCOM_CHAN_CTRL, diag_VcomRead);
    DIAG_PORT_INIT_STATE_SWITCH(EN_DIAG_VCOM_BEABER_DIAG_CTRL,EN_PORT_INIT_SUCC);
    DIAG_PORT_INIT_STATE_SWITCH(EN_DIAG_VCOM_BEABER_DIAG_APP,EN_PORT_INIT_SUCC);
    return ERR_MSP_SUCCESS;
#endif

    return ERR_MSP_SUCCESS;

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif





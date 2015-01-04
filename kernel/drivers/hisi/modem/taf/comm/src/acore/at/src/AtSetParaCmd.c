/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : AtSetParaCmd.c
  Version      : V100R001
  Date         : 2005-04-19
  Description  : ��C�ļ�������---ģ���ʵ��


  Function List:

  History      :

   1.��    ��   : 2009��10��28��
     �޸�����   : AT2D15641, STK���ŷ�����Ҫ֧�ֳ����ŵķֶη��͹���

************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "DrvInterface.h"
#include "ATCmdProc.h"
#include "AtInputProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "PppInterface.h"
#include "AtMsgPrint.h"
#include "Taf_MmiStrParse.h"
#include "siappstk.h"
#include "siapppih.h"
#include "siapppb.h"
#include "omrl.h"
#include "AtPhyInterface.h"
#include "AtDataProc.h"
#include "AtInputProc.h"
#include "TafDrvAgent.h"
#include "MnCommApi.h"
#include "AtCmdMsgProc.h"
#include "UsimmApi.h"
#include "AtRabmInterface.h"
#include "AtSndMsg.h"
#include "AtDeviceCmd.h"
#include "AtRnicInterface.h"
#include "AtTafAgentInterface.h"
#include "TafAgentInterface.h"
#include "spysystem.h"
#include "ipcmailboxinterface.h"

#include "AtMtaInterface.h"
#include "phyoaminterface.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "omnvinterface.h"

#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"
#include "msp_cfg.h"
#include "at_common.h"
#include "gen_msg.h"
/* ADD by c64416 for V9R1/V7R1 AT, 2013/09/18 begin */
#include "at_lte_common.h"
/* ADD by c64416 for V9R1/V7R1 AT, 2013/09/18 end */
#endif
#include "MnCallApi.h"
#include "AtCtx.h"
#include "AppVcApi.h"
#include "AtImsaInterface.h"

#if (FEATURE_ON == FEATURE_AGPS)
#if (VOS_OS_VER == VOS_LINUX)
#include <linux/clk.h>
#else
#include <LinuxStub.h>
#endif
#endif

#include "AtCmdSimProc.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_SETPARACMD_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
AT_SET_PORT_PARA_MAP_STRU    g_astSetPortParaMap[AT_SETPORT_DEV_MAP_LEN]
                                = {{"A1", AT_DEV_CDROM,        "CDROM"        },
                                   {"A2", AT_DEV_SD,           "SD"           },
                                   {"A3", AT_DEV_RNDIS,        "RNDIS"        },
                                   {"A",  AT_DEV_BLUE_TOOTH,   "BLUE TOOTH"   },
                                   {"B",  AT_DEV_FINGER_PRINT, "FINGER PRINT" },
                                   {"D",  AT_DEV_MMS,          "MMS"          },
#if(FEATURE_ON == FEATURE_LTE)
                                   {"E",  AT_DEV_PC_VOICE,     "3G PC VOICE"  },
                                   {"1",  AT_DEV_MODEM,        "3G MODEM"     },
                                   {"2",  AT_DEV_PCUI,         "3G PCUI"      },
                                   {"3",  AT_DEV_DIAG,         "3G DIAG"      },
#else
                                   {"E",  AT_DEV_PC_VOICE,     "PC VOICE"     },
                                   {"1",  AT_DEV_MODEM,        "MODEM"        },
                                   {"2",  AT_DEV_PCUI,         "PCUI"         },
                                   {"3",  AT_DEV_DIAG,         "DIAG"         },
#endif
                                   {"4",  AT_DEV_PCSC,         "PCSC"         },
#if(FEATURE_ON == FEATURE_LTE)
                                   {"5",  AT_DEV_GPS,          "3G GPS"       },
#else
                                   {"5",  AT_DEV_GPS,          "GPS"          },
#endif
                                   {"6",  AT_DEV_GPS_CONTROL,  "GPS CONTROL"  },
                                   {"7",  AT_DEV_NDIS,         "3G NDIS"      },
                                   {"16", AT_DEV_NCM,          "NCM"          },
                                   {"10",AT_DEV_4G_MODEM,      "4G MODEM"        },
                                   {"11",AT_DEV_4G_NDIS,       "4G NDIS"         },
                                   {"12",AT_DEV_4G_PCUI,       "4G PCUI"         },
                                   {"13",AT_DEV_4G_DIAG,       "4G DIAG"         },
                                   {"14",AT_DEV_4G_GPS,        "4G GPS"          },
                                   {"15",AT_DEV_4G_PCVOICE,    "4G PCVOICE"      },
                                   {"FF", AT_DEV_NONE,         "NO FIRST PORT"}
                                  };

TAF_UINT8                               gucSTKCmdQualify    =0x0;

/*AT/OMͨ������·����*/
TAF_UINT8                               gucAtOmIndex        = AT_MAX_CLIENT_NUM;

/*��¼��ѯ�����������*/
TAF_UINT32                              gulErrType          = 1;


/*NAS�յ�APP�·�NDIS���������slice*/
VOS_UINT32                              g_ulRcvAppNdisdupSlice;

VOS_BOOL                                g_bSetFlg = VOS_FALSE;

VOS_UINT32                              g_ulWifiFreq;
VOS_UINT32                              g_ulWifiRate;
VOS_UINT32                              g_ulWifiMode;
VOS_INT32                               g_lWifiPower;
#if(FEATURE_ON == FEATURE_LTE)
VOS_UINT32                              g_ulWifiRF = 0xffffffff;
AT_TMODE_RAT_FLAG_STRU g_stTmodeRat = {0};
VOS_UINT32 g_ulTmodeNum             = 0;
VOS_UINT32 g_ulGuTmodeCnfNum        = 0;
VOS_UINT32 g_ulLteOnly              = 0;
VOS_UINT32 g_ulGuOnly               = 0;
VOS_UINT32 g_ulLteIsSend2Dsp        = 0;

#endif
VOS_UINT                                g_ulUcastWifiRxPkts;
VOS_UINT                                g_ulMcastWifiRxPkts;

/* WIFI nģʽWL���������ֵΪ0~7����8�� */
#define AT_WIFI_N_RATE_NUM              (8)

/* +CLCK�������CLASS��Service Type Code��Ӧ�� */
AT_CLCK_CLASS_SERVICE_TBL_STRU          g_astClckClassServiceTbl[] = {
    {AT_CLCK_PARA_CLASS_VOICE,                      TAF_SS_TELE_SERVICE,        TAF_ALL_SPEECH_TRANSMISSION_SERVICES_TSCODE},
    {AT_CLCK_PARA_CLASS_DATA,                       TAF_SS_BEARER_SERVICE,      TAF_ALL_BEARERSERVICES_BSCODE},
    {AT_CLCK_PARA_CLASS_FAX,                        TAF_SS_TELE_SERVICE,        TAF_ALL_FACSIMILE_TRANSMISSION_SERVICES_TSCODE},
    {AT_CLCK_PARA_CLASS_VOICE_FAX,                  TAF_SS_TELE_SERVICE,        TAF_ALL_TELESERVICES_EXEPTSMS_TSCODE},
    {AT_CLCK_PARA_CLASS_VOICE_DATA_FAX,             TAF_SS_TELE_SERVICE,        TAF_ALL_TELESERVICES_EXEPTSMS_TSCODE},
    {AT_CLCK_PARA_CLASS_SMS,                        TAF_SS_TELE_SERVICE,        TAF_ALL_SMS_SERVICES_TSCODE},
    {AT_CLCK_PARA_CLASS_VOICE_FAX_SMS,              TAF_SS_TELE_SERVICE,        TAF_ALL_TELESERVICES_TSCODE},
    {AT_CLCK_PARA_CLASS_VOICE_DATA_FAX_SMS,         TAF_SS_TELE_SERVICE,        TAF_ALL_TELESERVICES_TSCODE},
    {AT_CLCK_PARA_CLASS_DATA_SYNC,                  TAF_SS_BEARER_SERVICE,      TAF_ALL_DATA_CIRCUIT_SYNCHRONOUS_BSCODE},
    {AT_CLCK_PARA_CLASS_DATA_ASYNC,                 TAF_SS_BEARER_SERVICE,      TAF_ALL_DATA_CIRCUIT_ASYNCHRONOUS_BSCODE},
    {AT_CLCK_PARA_CLASS_DATA_PKT,                   TAF_SS_BEARER_SERVICE,      TAF_ALL_DATAPDS_SERVICES_BSCODE},
    {AT_CLCK_PARA_CLASS_DATA_SYNC_PKT,              TAF_SS_BEARER_SERVICE,      TAF_ALL_SYNCHRONOUS_SERVICES_BSCODE},
    {AT_CLCK_PARA_CLASS_DATA_PAD,                   TAF_SS_BEARER_SERVICE,      TAF_ALL_PADACCESSCA_SERVICES_BSCODE},
    {AT_CLCK_PARA_CLASS_DATA_ASYNC_PAD,             TAF_SS_BEARER_SERVICE,      TAF_ALL_ASYNCHRONOUS_SERVICES_BSCODE},
    {AT_CLCK_PARA_CLASS_DATA_SYNC_ASYNC_PKT_PKT,    TAF_SS_BEARER_SERVICE,      TAF_ALL_BEARERSERVICES_BSCODE},
};

MTA_BODY_SAR_STATE_ENUM_UINT16          g_enAtBodySarState = MTA_BODY_SAR_OFF;

/*****************************************************************************
   3 ��������������
*****************************************************************************/

#ifndef _PS_COMPILE_EDGE_ADAPT_MOIRI_B073_
extern void       TTF_SetGcfTestFlag(VOS_UINT32 ulGctTestFlag);
#endif

extern VOS_VOID GU_OamCtrlPortInit(VOS_VOID);

#if (VOS_WIN32 == VOS_OS_VER)
/* ���TAF�Ļط����� */
#ifndef __PS_WIN32_RECUR__
VOS_VOID NAS_MMA_SndNVData(VOS_VOID);
VOS_UINT32 NAS_MSG_SndOutsideContextData_Part1(VOS_VOID);
VOS_UINT32 NAS_MSG_SndOutsideContextData_Part2(VOS_VOID);
VOS_UINT32 NAS_MSG_SndOutsideContextData_Part3(VOS_VOID);
#endif

extern VOS_UINT32 NAS_SetLteRplmnId(TAF_PLMN_ID_STRU *pstPlmnId);

extern  VOS_UINT32 NAS_SetTinType(VOS_UINT8  ucTinType);
extern VOS_UINT32 NAS_SetPsBearerIsrFlg(VOS_UINT8  ucNsapi,VOS_UINT8  ucPdpIsrFlg,VOS_UINT8 ucPdpStatus);

extern VOS_UINT32 NAS_SetPsRegContainDrx(VOS_UINT8 ucDrx);
extern  VOS_UINT32 NAS_SetLteImsSupportFlag(VOS_UINT8 ucLteImsSupportFlg, VOS_UINT8 ucLteEmsSupportFlg);
extern  VOS_UINT32 NAS_SetImsCapabilitySupportFlag(
    VOS_UINT8                           ucVoiceCallOnImsSupportFlg,
    VOS_UINT8                           ucVideoCallOnImsSupportFlg,
    VOS_UINT8                           ucSmsOnImsSupportFlg
);
extern  VOS_UINT32 NAS_SetPreferDomain(VOS_UINT8 ucVoiceDomain, VOS_UINT8 ucSmsDomain);

extern VOS_UINT32 NAS_SetImsRoaming(VOS_UINT8 ucImsRoamingFlag);
extern VOS_UINT32 NAS_SetRedialCfg(
    VOS_UINT8                           ucCallRedialImsToCs,
    VOS_UINT8                           ucSmsRedialImsToCs,
    VOS_UINT8                           ucSsRedialImsToCs,
    VOS_UINT8                           ucCallRedialCsToIms,
    VOS_UINT8                           ucSmsRedialCsToIms,
    VOS_UINT8                           ucSsRedialCsToIms
);

extern  VOS_UINT32 NAS_SetImsVoiceInterSysLauEnable(VOS_UINT8 ucLauFlag);
extern  VOS_UINT32 NAS_SetImsVoiceMMEnableFlg(VOS_UINT8 ucMMFlag);

extern  VOS_UINT32 NAS_SetHighRatHPLMNSearchActiveFlg(VOS_UINT8 ucFlag);

extern VOS_UINT32 NAS_SetImsUssd(VOS_UINT8 ucImsUssdFlag);
#endif


/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

VOS_UINT32 At_SetSecuBootPara(VOS_UINT8 ucIndex)
{

    if ((1 != gucAtParaIndex)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (SECURE_ENABLE != gastAtParaList[0].ulParaValue)
    {
        return AT_ERROR;
    }

    /* ֻ������Ӳ�����ܵ�����£��������� */
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SECUBOOT_SET_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SECUBOOT_SET;           /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}

/******************************************************************************
 Function:      AT_CtrlGetPDPAuthType
 Description:    ��ȡPC���õ�PDP�������ж�Ӧ���͵�����
 Calls:
 Data Accessed:
 Data Updated:
 Input:
                 usTotalLen     PDP�������ڴ泤��
 Output:
 Return:        0   no auth
                1   pap
                2   chap
 Others:
   1.Date        : 2009-08-03
    Modification: Created function
******************************************************************************/
PPP_AUTH_TYPE_ENUM_UINT8 AT_CtrlGetPDPAuthType(
    VOS_UINT32                          Value,
    VOS_UINT16                          usTotalLen
)
{

    /*��ȡ��֤����*/
    if (0 == usTotalLen)
    {
        return PPP_NO_AUTH_TYPE;
    }
    else
    {
        if(1 == Value)
        {
            return PPP_PAP_AUTH_TYPE;
        }
        else
        {
            return PPP_CHAP_AUTH_TYPE;
        }
    }
}
TAF_UINT32 At_SsPrint2Class(TAF_SS_BASIC_SERVICE_STRU *pBsService,TAF_UINT8 ucClass)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulItemsNum;

    ulItemsNum = sizeof(g_astClckClassServiceTbl) / sizeof(AT_CLCK_CLASS_SERVICE_TBL_STRU);

    /* �����д��ӦClass�ķ������ͼ������� */
    for (ulLoop = 0; ulLoop < ulItemsNum; ulLoop++)
    {
        if (g_astClckClassServiceTbl[ulLoop].enClass == ucClass)
        {
            pBsService->BsType = g_astClckClassServiceTbl[ulLoop].enServiceType;
            pBsService->BsServiceCode = g_astClckClassServiceTbl[ulLoop].enServiceCode;
            return AT_SUCCESS;
        }
    }

    return AT_FAILURE;
}

/*****************************************************************************
 Prototype      : At_SsPrint2Code
 Description    :
 Input          : ucClass --- SSA��Code
 Output         : ---
 Return Value   : ulRtn������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_VOID At_SsPrint2Code(TAF_SS_CODE *pSsCode,TAF_UINT8 ucType)
{
    switch(ucType)
    {
    case AT_CLCK_AO_TYPE:
        *pSsCode = TAF_BAOC_SS_CODE;
        break;

    case AT_CLCK_OI_TYPE:
        *pSsCode = TAF_BOIC_SS_CODE;
        break;

    case AT_CLCK_OX_TYPE:
        *pSsCode = TAF_BOICEXHC_SS_CODE;
        break;

    case AT_CLCK_AI_TYPE:
        *pSsCode = TAF_BAIC_SS_CODE;
        break;

    case AT_CLCK_IR_TYPE:
        *pSsCode = TAF_BICROAM_SS_CODE;
        break;

    case AT_CLCK_AB_TYPE:
        *pSsCode = TAF_ALL_BARRING_SS_CODE;
        break;

    case AT_CLCK_AG_TYPE:
        *pSsCode = TAF_BARRING_OF_OUTGOING_CALLS_SS_CODE;
        break;

    default:
        *pSsCode = TAF_BARRING_OF_INCOMING_CALLS_SS_CODE;
        break;
    }
}

#if ( VOS_WIN32 == VOS_OS_VER )
/*****************************************************************************
 �� �� ��  : AT_ReadValueFromNvim
 ��������  : ��ȡNV��ֵ
 �������  : const NV_ID_ENUM_U16 enNVItemType
             VOS_VOID *pData
             VOS_UINT16 usDataLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��10��23��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_ReadValueFromNvim(
    const NV_ID_ENUM_U16                enNVItemType,
    VOS_VOID                           *pData,
    VOS_UINT32                          usDataLen,
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulRst;
    ulRst = NV_ReadEx(enModemId, enNVItemType, pData, usDataLen);
    switch ( ulRst)
    {
        case NV_OK :
            return AT_OK;
        case NV_ID_NOT_EXIST:
        case NV_BUFFER_TOO_LONG :
            return AT_CME_INCORRECT_PARAMETERS;
        default:
            return AT_ERROR ;
    }
}
#endif

TAF_UINT32 At_AsciiNum2HexString(TAF_UINT8 *pucSrc, TAF_UINT16 *pusSrcLen)
{
    TAF_UINT16 usChkLen = 0;
    TAF_UINT16 usTmp = 0;
    TAF_UINT8  ucLeft = 0;
    TAF_UINT16 usSrcLen = *pusSrcLen;
    TAF_UINT8 *pucDst = pucSrc;

    /* ��������������ֽ��򷵻ش��� */
    if(0 != (usSrcLen % 2))
    {
        return AT_FAILURE;
    }

    while(usChkLen < usSrcLen)
    {
        if( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            ucLeft = (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            ucLeft = (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return AT_FAILURE;
        }

        pucDst[usTmp] = 0xf0 & (ucLeft << 4);
        usChkLen += 1;

        if( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            pucDst[usTmp] |= pucSrc[usChkLen] - '0';
        }
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            pucDst[usTmp] |= (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            pucDst[usTmp] |= (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return AT_FAILURE;
        }

        usChkLen += 1;
        usTmp += 1;
    }

    *pusSrcLen = usSrcLen / 2;
    return AT_SUCCESS;
}
/*****************************************************************************
 Prototype      : At_AsciiString2HexText
 Description    : ���16������ת������
 Input          : nptr --- �ַ���
 Output         :
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_AsciiString2HexText(SI_STK_TEXT_STRING_STRU *pTextStr,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucTmp = 0;
    TAF_UINT8  ucLeft = 0;
    TAF_UINT8 *pucDst = pTextStr->pucText;

    if(usSrcLen < 2)
    {
        return AT_FAILURE;
    }

    while(usChkLen < usSrcLen)
    {
        if( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            ucLeft = (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            ucLeft = (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return AT_FAILURE;
        }

        pucDst[ucTmp] = 0xf0 & (ucLeft << 4);

        usChkLen += 1;

        if( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            pucDst[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return AT_FAILURE;
        }

        usChkLen += 1;

        ucTmp += 1;
    }

    pTextStr->ucLen = ucTmp;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_AsciiString2HexSimple
 Description    : ���16������ת������
 Input          : nptr --- �ַ���
 Output         :
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_AsciiString2HexSimple(TAF_UINT8 *pTextStr,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucTmp = 0;
    TAF_UINT8  ucLeft = 0;
    TAF_UINT8 *pucDst = pTextStr;

    if(usSrcLen == 0)
    {
        return AT_FAILURE;
    }

    while(usChkLen < usSrcLen)
    {
        if ( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        else if ( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            ucLeft = (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        else if ( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            ucLeft = (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return AT_FAILURE;
        }

        pucDst[ucTmp] = 0xf0 & (ucLeft << 4);

        usChkLen += 1;

        if ( (pucSrc[usChkLen] >= '0') && (pucSrc[usChkLen] <= '9') ) /* the number is 0-9 */
        {
            pucDst[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        else if ( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') ) /* the number is 0-9 */
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        else if ( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') ) /* the number is 0-9 */
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return AT_FAILURE;
        }

        usChkLen += 1;

        ucTmp += 1;
    }

    return AT_SUCCESS;
}

/* Del At_AbortCmdProc */

/*****************************************************************************
 Prototype      : At_AsciiNum2BcdNum
 Description    : �����ִ�ASCII���ʽת����BCD�룬pucDst�ĳ��ȱ�����pucSrc��һ������
 Input          : pucDst   --- Ŀ���ִ�
                  usDstLen --- Ŀ���ִ�����
                  pucSrc   --- Դ�ִ�
                  usSrcLen --- Դ�ִ�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_AsciiNum2BcdNum (TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucTmp = 0;
    TAF_UINT8  ucBcdCode;

    for(usChkLen = 0; usChkLen < usSrcLen; usChkLen++)
    {
        ucTmp = usChkLen % 2;   /* �жϸߵ�λ */

        if ((pucSrc[usChkLen] >= 0x30) && (pucSrc[usChkLen] <= 0x39)) /* the number is 0-9 */
        {
            ucBcdCode = pucSrc[usChkLen] - 0x30;
        }
        else if ('*' == pucSrc[usChkLen])
        {
            ucBcdCode = 0x0a;
        }
        else if ('#' == pucSrc[usChkLen])
        {
            ucBcdCode = 0x0b;
        }
        else if (('a' == pucSrc[usChkLen])
              || ('b' == pucSrc[usChkLen])
              || ('c' == pucSrc[usChkLen]))
        {
            ucBcdCode = (VOS_UINT8)((pucSrc[usChkLen] - 'a') + 0x0c);
        }
        else
        {
            return AT_FAILURE;
        }

        ucTmp = usChkLen % 2;   /* �жϸߵ�λ */
        if(0 == ucTmp)
        {
            pucDst[usChkLen/2] = ucBcdCode;   /* ��λ */
        }
        else
        {
            pucDst[usChkLen/2] |= (TAF_UINT8)(ucBcdCode << 4);   /* ��λ */
        }
    }

    if(1 == (usSrcLen % 2))
    {
        pucDst[usSrcLen/2] |= 0xf0; /* ��λ */
    }

    return AT_SUCCESS;
}
/*****************************************************************************
 Prototype      : At_AsciiNum2Num
 Description    : �����ִ�ASCII���ʽת����BCD�룬pucDst�ĳ��ȱ�����pucSrc��һ������
 Input          : pucDst   --- Ŀ���ִ�
                  usDstLen --- Ŀ���ִ�����
                  pucSrc   --- Դ�ִ�
                  usSrcLen --- Դ�ִ�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_AsciiNum2Num (TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usChkLen = 0;

    for(usChkLen = 0; usChkLen < usSrcLen; usChkLen++)
    {

        if( (pucSrc[usChkLen] >= 0x30) && (pucSrc[usChkLen] <= 0x39) ) /* the number is 0-9 */
        {
                pucDst[usChkLen] = pucSrc[usChkLen] - 0x30;   /* ��λ */
        }
        else
        {
            return AT_FAILURE;
        }
    }

    return AT_SUCCESS;
}

TAF_UINT32 At_CheckDialString(TAF_UINT8 *pData, TAF_UINT16 usLen)
{
    TAF_UINT16 usCount = 0;
    TAF_UINT8 *pTmp = pData;

    if ('+' == *pTmp)
    {
        pTmp++;
        usCount++;
    }

    while(usCount++ < usLen)
    {
        if ((*pTmp >= '0') && (*pTmp <= '9'))
        {
        }
        else if ((*pTmp >= 'a') && (*pTmp <= 'c'))
        {
        }
        else if ((*pTmp >= 'A') && (*pTmp <= 'C'))
        {
        }
        else if (('*' == *pTmp) || ('#' == *pTmp))
        {
        }
        else
        {
            return AT_FAILURE;
        }
        pTmp++;
    }
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_CheckPBString
 Description    : �Ƚϡ�ƥ�䲦���ַ�
 Input          :
 Output         :
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-05-30
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_CheckPBString(TAF_UINT8 *pData, TAF_UINT16 *pusLen)
{
    TAF_UINT16 usCount = 0;
    TAF_UINT8 *pTmp = pData;
    TAF_UINT8  usInvalidNum = 0;

    while(usCount++ < *pusLen)
    {
        if(('(' == *pTmp)||(')' == *pTmp)||('-' == *pTmp)||('"' == *pTmp))
        {
            VOS_MemCpy(pTmp, pTmp+1, *pusLen - usCount);
            usInvalidNum++;
        }
        else
        {
            pTmp++;
        }
    }

    usCount = 0;
    pTmp = pData;
    *pusLen -= usInvalidNum;

    while(usCount++ < *pusLen)
    {
        if(!( (('0' <= *pTmp) && ('9' >= *pTmp))
           || ('*' == *pTmp) || ('#' == *pTmp) || ('?' == *pTmp)
           || (',' == *pTmp) || ('P' == *pTmp) || ('p' == *pTmp)))
        {
            return AT_FAILURE;
        }
        pTmp++;
    }
    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_CheckNumLen
 Description    :
 Input          :
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32  At_CheckNumLen(TAF_UINT16 usMax,TAF_UINT16 usLen)
{
    /* ������������ֱ�ӷ��ش��� */
    if(AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        if((usMax * 4) < usLen)
        {
            return AT_FAILURE;
        }
    }
    else
    {
        if(usMax < usLen)
        {
            return AT_FAILURE;
        }
    }
    return AT_SUCCESS;
}
TAF_UINT32  At_CheckUssdNumLen(
    VOS_UINT8                           ucIndex,
    TAF_SS_DATA_CODING_SCHEME           dcs,
    TAF_UINT16                          usLen
)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);




    if(AT_USSD_NON_TRAN_MODE == pstSsCtx->usUssdTransMode)
    {
        if(TAF_SS_MAX_USSDSTRING_LEN < usLen)
        {
            return AT_FAILURE;
        }
    }
    else
    {
        if((TAF_SS_MAX_USS_CHAR * 2) < usLen)
        {
            return AT_FAILURE;
        }

    }

    return AT_SUCCESS;
}
TAF_UINT32 At_UnicodeTransferTo81CalcLength(const TAF_UINT8 *pucData,
                                            TAF_UINT16      usLen,
                                            TAF_UINT16      *pusBaseCode,
                                            TAF_UINT16      *pusDstLen)
{
    TAF_UINT16      usUnicodeChar;
    TAF_UINT16      usBaseCode = 0;
    TAF_UINT16      usIndex;
    TAF_BOOL        bIsBaseSet = TAF_FALSE;
    TAF_UINT16      usDstLen = 0;
    TAF_UINT8       aucGsmData[2];
    TAF_UINT16      usGsmDataLen = 0;

    /* �����������ֵ */
    *pusDstLen = 0;
    *pusBaseCode = 0;

    for (usIndex = 0; usIndex < (usLen >> 1); usIndex++)
    {
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));

        pucData += 2;

        /* �������GSM��UCS�Ļ���������չ�� */
        if (AT_SUCCESS == At_OneUnicodeToGsm(usUnicodeChar, aucGsmData, &usGsmDataLen))
        {
            usDstLen += usGsmDataLen;

            continue;
        }

        /* 81�����õ�8����15bit���б��룬��0hhh hhhh hXXX XXXX����˵�16bitΪ1һ�����ܽ���81���� */
        if (0 != (usUnicodeChar & 0x8000))
        {
            AT_ERR_LOG("At_UnicodeTransferTo81CalcLength error: no16 bit is 1");

            return AT_FAILURE;
        }

        if (TAF_FALSE == bIsBaseSet)
        {
            /* ȡ��һ��UCS2�ĵ�8����15bit��ΪBaseCode��BaseCode����7λ��Ϊ��ַ�� */
            bIsBaseSet = TAF_TRUE;
            usBaseCode = usUnicodeChar & AT_PB_81_CODE_BASE_POINTER;
        }
        else
        {
            if (usBaseCode != (usUnicodeChar & AT_PB_81_CODE_BASE_POINTER))
            {
                AT_ERR_LOG("At_UnicodeTransferTo81CalcLength error: code base error");

               return AT_FAILURE;
            }
        }

        usDstLen++;
    }

    /* �ܽ���81���룬���ػ������81�����ܳ��� */
    *pusBaseCode = usBaseCode;
    *pusDstLen   = usDstLen + AT_PB_81CODE_HEADER_LEN;

    return AT_SUCCESS;
}
TAF_UINT32 At_UnicodeTransferTo82CalcLength(const TAF_UINT8 *pucData,
                                            TAF_UINT16      usLen,
                                            TAF_UINT16      *pusBaseCode,
                                            TAF_UINT16      *pusDstLen)
{
    TAF_UINT16      usUnicodeChar;
    TAF_UINT16      usIndex;
    TAF_BOOL        bIsBaseSet = TAF_FALSE;
    TAF_UINT16      us82BaseHigh = 0;
    TAF_UINT16      us82BaseLow = 0;
    TAF_UINT16      usDstLen = 0;
    TAF_UINT8       aucGsmData[2];
    TAF_UINT16      usGsmDataLen = 0;

    /* �����������ֵ */
    *pusDstLen = 0;
    *pusBaseCode = 0;

    for (usIndex = 0; usIndex < (usLen >> 1); usIndex++)
    {
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));

        pucData += 2;

        /* �������GSM��UCS�Ļ���������չ�� */
        if (AT_SUCCESS == At_OneUnicodeToGsm(usUnicodeChar, aucGsmData, &usGsmDataLen))
        {
            usDstLen += usGsmDataLen;

            continue;
        }


        if (TAF_FALSE == bIsBaseSet)
        {
            bIsBaseSet = TAF_TRUE;
            us82BaseHigh = usUnicodeChar;
            us82BaseLow  = usUnicodeChar;
        }
        else
        {
            if (usUnicodeChar < us82BaseLow)
            {
                us82BaseLow = usUnicodeChar;
            }

            if (usUnicodeChar > us82BaseHigh)
            {
                us82BaseHigh = usUnicodeChar;
            }

            /* UCS2���������������С�����ֵ����127�Ͳ��ܽ���82���� */
            if (AT_PB_GSM7_CODE_MAX_VALUE < (us82BaseHigh - us82BaseLow))
            {
                 AT_ERR_LOG("At_UnicodeTransferTo82CalcLength error: code base error");

                return AT_FAILURE;
            }
        }

        usDstLen++;
    }

    /* �ܽ���82���룬���ػ������82�����ܳ��� */
    *pusBaseCode = us82BaseLow;
    *pusDstLen   = usDstLen + AT_PB_82CODE_HEADER_LEN;

    return AT_SUCCESS;
}


TAF_UINT32 At_UnicodeTransferTo81(const TAF_UINT8 *pucData,
                                  TAF_UINT16      usLen,
                                  TAF_UINT16      usCodeBase,
                                  TAF_UINT8       *pucDest)
{
    TAF_UINT16      usUnicodeChar;
    TAF_UINT16      i;
    TAF_UINT8       aucGsmData[2];
    TAF_UINT16      usGsmDataLen = 0;
    TAF_UINT16      usDstLen     = AT_PB_81CODE_HEADER_LEN;

    for (i = 0; i < (usLen >> 1); i++)
    {
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));

        pucData += 2;

        /* �������GSM��UCS�Ļ���������չ�� */
        if (AT_SUCCESS == At_OneUnicodeToGsm(usUnicodeChar, aucGsmData, &usGsmDataLen))
        {
            VOS_MemCpy((pucDest + usDstLen), aucGsmData, usGsmDataLen);
            usDstLen += usGsmDataLen;

            continue;
        }

        /* �ݴ����� */
        if ((usCodeBase | (usUnicodeChar & AT_PB_GSM7_CODE_MAX_VALUE)) == usUnicodeChar)
        {
            /* תΪ81�ı��뷽ʽ */
            pucDest[usDstLen++] =(TAF_UINT8)( AT_PB_CODE_NO8_BIT | (usUnicodeChar & AT_PB_GSM7_CODE_MAX_VALUE));
        }
        else
        {
            AT_ERR_LOG("At_UnicodeTransferTo81 error");

            return AT_FAILURE;
        }
    }

    /* ����81����header��Ϣ */
    pucDest[0] = SI_PB_ALPHATAG_TYPE_UCS2_81;
    pucDest[1] = (TAF_UINT8)(usDstLen - AT_PB_81CODE_HEADER_LEN);
    pucDest[2] = (TAF_UINT8)((usCodeBase & AT_PB_81_CODE_BASE_POINTER)>>7);

    return AT_SUCCESS;
}


TAF_UINT32 At_UnicodeTransferTo82(const TAF_UINT8 *pucData,
                                  TAF_UINT16      usLen,
                                  TAF_UINT16      usCodeBase,
                                  TAF_UINT8       *pucDest)
{
    TAF_UINT16      usUnicodeChar;
    TAF_UINT16      i;
    TAF_UINT8       aucGsmData[2];
    TAF_UINT16      usGsmDataLen = 0;
    TAF_UINT16      usDstLen     = AT_PB_82CODE_HEADER_LEN;

    for (i = 0; i < (usLen >> 1); i++)
    {
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));

        pucData += 2;

        /* �������GSM��UCS�Ļ���������չ�� */
        if (AT_SUCCESS == At_OneUnicodeToGsm(usUnicodeChar, aucGsmData, &usGsmDataLen))
        {
            VOS_MemCpy(pucDest + usDstLen, aucGsmData, usGsmDataLen);
            usDstLen += usGsmDataLen;

            continue;
        }

        /* �ݴ����� */
        if ((usUnicodeChar - usCodeBase) <= AT_PB_GSM7_CODE_MAX_VALUE)
        {
            /* תΪ82�ı��뷽ʽ */
            pucDest[usDstLen++] = ((TAF_UINT8)(usUnicodeChar - usCodeBase)) |  AT_PB_CODE_NO8_BIT;
        }
        else
        {
            AT_ERR_LOG("At_UnicodeTransferTo81 error");

            return AT_FAILURE;
        }
    }

    /* ����82����header��Ϣ */
    pucDest[0] = SI_PB_ALPHATAG_TYPE_UCS2_82;
    pucDest[1] = (TAF_UINT8)(usDstLen - AT_PB_82CODE_HEADER_LEN);
    pucDest[2] = (TAF_UINT8)((usCodeBase & 0xff00)>> 8);
    pucDest[3] = (TAF_UINT8)(usCodeBase & 0x00ff);

    return AT_SUCCESS;
}


TAF_UINT32 At_Gsm7BitFormat(TAF_UINT8   *pucSrc,
                            TAF_UINT16  usSrcLen,
                            TAF_UINT8   *pucDst,
                            TAF_UINT16  *pusDstLen)
{
   TAF_UINT16       usIndex;

   for (usIndex = 0; usIndex < usSrcLen; usIndex++)
   {
        /* GSMģʽ��������������0x7fʱ��ʾ�û������к��зǷ��ַ� */
        if (AT_PB_GSM7_CODE_MAX_VALUE < pucSrc[usIndex])
        {
            return AT_FAILURE;
        }

        pucDst[usIndex] = pucSrc[usIndex];
   }

   *pusDstLen = usSrcLen;

   return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_UnicodePrint2Unicode
 Description    : ascii��unicode��ת��
 Input          : pData --- �ַ���
                  pLen  --- ���ȵ�ַ
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_UnicodePrint2Unicode(TAF_UINT8 *pData,TAF_UINT16 *pLen)
{
    TAF_UINT8 *pCheck   = pData;
    TAF_UINT8 *pWrite   = pData;
    TAF_UINT8 *pRead    = pData;
    TAF_UINT16 usLen    = 0;
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucHigh   = 0;
    TAF_UINT8  ucLow    = 0;

    /* �ַ���Ϊ'0'-'9','a'-'f','A'-'F' */
    while( usChkLen++ < *pLen )
    {
        if( (*pCheck >= '0') && (*pCheck <= '9') )
        {
            *pCheck = *pCheck - '0';
        }
        else if( (*pCheck >= 'a') && (*pCheck <= 'f') )
        {
            *pCheck = (*pCheck - 'a') + 10;
        }
        else if( (*pCheck >= 'A') && (*pCheck <= 'F') )
        {
            *pCheck = (*pCheck - 'A') + 10;
        }
        else
        {
            return AT_FAILURE;
        }
        pCheck++;
    }

    while(usLen < *pLen)                    /* �жϽ�β */
    {
        ucHigh = *pRead++;                  /* ��λ */
        usLen++;
        ucLow  = *pRead++;                  /* ��λ */
        usLen++;

        *pWrite++ = (TAF_UINT8)(ucHigh * 16) + ucLow;    /* д��UNICODE��һ���ֽ� */
    }

    *pLen = usLen >> 1;
    return AT_SUCCESS;
}
/*****************************************************************************
 Prototype      : At_UnicodePrint2Ascii
 Description    : CSCS����,�����ֵ�Unicode��ӡת����Ascii
 Input          : pucDst   --- Ŀ���ִ�
                  pucSrc   --- Դ�ִ�
                  usSrcLen --- Դ�ִ�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_UnicodePrint2Ascii(TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT8 *pWrite   = pucDst;
    TAF_UINT8 *pRead    = pucSrc;
    TAF_UINT8  aucTmp[4];
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucIndex = 0;

    /* ÿ4���ַ�����ת��һ��ASCII�� */
    if(0 != (usSrcLen % 4))
    {
        return AT_FAILURE;
    }

    /* �����ʱ���� */
    PS_MEM_SET(aucTmp,0x00,4);

    /* �ַ���Ϊ'0'-'9','a'-'f','A'-'F' */
    while( usChkLen++ < usSrcLen )
    {
        if( (*pRead >= '0') && (*pRead <= '9') )
        {
            aucTmp[ucIndex++] = *pRead - '0';
        }
        else if( (*pRead >= 'a') && (*pRead <= 'f') )
        {
            aucTmp[ucIndex++] = (*pRead - 'a') + 10;
        }
        else if( (*pRead >= 'A') && (*pRead <= 'F') )
        {
            aucTmp[ucIndex++] = (*pRead - 'A') + 10;
        }
        else
        {
            return AT_FAILURE;
        }

        /* ÿ�ĸ��ַ��ó�һ���ַ� */
        if(4 == ucIndex)
        {
            /* �������������� */
            if((0 != aucTmp[0]) || (0 != aucTmp[1]))
            {
                return AT_FAILURE;
            }

            *pWrite++ = (TAF_UINT8)(aucTmp[2] * 16) + aucTmp[3];    /* д��һ���ֽ� */
            if(AT_FAILURE == At_CheckDialNum(*(pWrite-1)))
            {
                return AT_FAILURE;
            }
            /* ���¿�ʼ */
            ucIndex = 0;
        }

        /* ��һ���ַ� */
        pRead++;
    }

    return AT_SUCCESS;
}


TAF_UINT32 At_CheckNameUCS2Code(TAF_UINT8 *pucData, TAF_UINT16 *pusLen)
{
    TAF_UINT8 ucAlphType = *pucData;
    TAF_UINT16 usAlphLen = *(pucData+1);

    if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == ucAlphType) && (((*pusLen-1)%2) == 0))
    {
        /* 80���룬���˱���ֽ����೤�ȱ���Ϊż���ֽ� */
        return AT_SUCCESS;
    }

    if ((SI_PB_ALPHATAG_TYPE_UCS2_81 == ucAlphType) && ((*pusLen-3) >= usAlphLen))
    {
        /* 81���룬ʵ���ַ����ȱ�����������г����ֽڵ�ֵ */
        *pusLen = usAlphLen + 3;
        return AT_SUCCESS;
    }

    if ((SI_PB_ALPHATAG_TYPE_UCS2_82 == ucAlphType) && ((*pusLen-4) >= usAlphLen))
    {
        /* 82���룬ͬ�ϣ������ǻ�ַ��2���ֽ� */
        *pusLen = usAlphLen + 4;
        return AT_SUCCESS;
    }

    return AT_FAILURE;

}

/*****************************************************************************
 �� �� ��  : AT_PhSendRestoreFactParm
 ��������  : E5��̬ʱ���ָ��û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��23��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PhSendRestoreFactParm( VOS_VOID )
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;

    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        if (AT_APP_USER == gastAtClientTab[i].UserType)
        {
            break;
        }
    }

    /* δ�ҵ�E5 User,�����ϱ� */
    if ( i >= AT_MAX_CLIENT_NUM )
    {
        return ;
    }

    usLength = 0;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s",gaucAtCrLf);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "^FACTORY");
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s",gaucAtCrLf);

    At_SendResultData((VOS_UINT8)i,pgucAtSndCodeAddr,usLength);
}

/*****************************************************************************
 �� �� ��  : AT_PhSendRestoreFactParmNoReset
 ��������  : E5��̬ʱ���ָ��û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��03��23��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_PhSendRestoreFactParmNoReset( VOS_VOID )
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;

    for(i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        if (AT_APP_USER == gastAtClientTab[i].UserType)
        {
            break;
        }
    }

    /* δ�ҵ�E5 User,�����ϱ� */
    if ( i >= AT_MAX_CLIENT_NUM )
    {
        return ;
    }

    usLength = 0;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s",gaucAtCrLf);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "^NORSTFACT");
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                     "%s",gaucAtCrLf);

    At_SendResultData((VOS_UINT8)i,pgucAtSndCodeAddr,usLength);
}


/*****************************************************************************
 Prototype      : At_SetNumTypePara
 Description    : ����UNICODE����ASCII���͵ĺ���
 Input          : pucDst   --- Ŀ���ִ�
                  pucSrc   --- Դ�ִ�
                  usSrcLen --- Դ�ִ�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetNumTypePara(TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT32                          ulRet;
    TAF_UINT16                          usAsciiStrLen;

    if(AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        ulRet = At_UnicodePrint2Ascii(pucDst,pucSrc,usSrcLen);
        if (AT_SUCCESS != ulRet)
        {
            return ulRet;
        }
    }
    else
    {
        PS_MEM_CPY(pucDst,pucSrc,usSrcLen);
    }

    usAsciiStrLen = (TAF_UINT16)VOS_StrLen((TAF_CHAR *)pucDst);
    if(AT_SUCCESS == At_CheckDialString(pucDst, usAsciiStrLen))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}


TAF_UINT32 At_UpdateMsgRcvAct(
    TAF_UINT8                           ucIndex,
    AT_CSMS_MSG_VERSION_ENUM_U8         ucCsmsVersion,
    AT_CNMI_MT_TYPE                     CnmiMtType,
    AT_CNMI_DS_TYPE                     CnmiDsType
)
{
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvPath;
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvSmAct[AT_CNMI_MT_TYPE_MAX] = {MN_MSG_RCVMSG_ACT_STORE,
                                                                           MN_MSG_RCVMSG_ACT_STORE,
                                                                           MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK,
                                                                           MN_MSG_RCVMSG_ACT_STORE};
    MN_MSG_RCVMSG_ACT_ENUM_U8           enRcvStaRptAct[AT_CNMI_DS_TYPE_MAX] = {MN_MSG_RCVMSG_ACT_STORE,
                                                                               MN_MSG_RCVMSG_ACT_TRANSFER_AND_ACK,
                                                                               MN_MSG_RCVMSG_ACT_STORE};

    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if ((CnmiMtType >= AT_CNMI_MT_TYPE_MAX)
     || (CnmiDsType >= AT_CNMI_DS_TYPE_MAX))
    {
        return AT_ERROR;
    }

    PS_MEM_CPY(&stRcvPath, &(pstSmsCtx->stCpmsInfo.stRcvPath), sizeof(stRcvPath));
    if (AT_CSMS_MSG_VERSION_PHASE2_PLUS == ucCsmsVersion)
    {
        enRcvSmAct[2] = MN_MSG_RCVMSG_ACT_TRANSFER_ONLY;
        enRcvStaRptAct[1] = MN_MSG_RCVMSG_ACT_TRANSFER_ONLY;
    }

    stRcvPath.enRcvSmAct        = enRcvSmAct[CnmiMtType];
    stRcvPath.enRcvStaRptAct    = enRcvStaRptAct[CnmiDsType];
    stRcvPath.enSmsServVersion  = ucCsmsVersion;

    PS_MEM_SET(stRcvPath.aucReserve1, 0, sizeof(stRcvPath.aucReserve1));


    /* ��CNMI���õ�MT type���ʹ����TAF,��<MT>=3���յ�CLASS3����ʱ�򣬰���CMT��ʽ�ϱ� */
    stRcvPath.enCnmiMtType      = CnmiMtType;

    if (MN_ERR_NO_ERROR != MN_MSG_SetRcvMsgPath(gastAtClientTab[ucIndex].usClientId,
                                                gastAtClientTab[ucIndex].opId,
                                                &stRcvPath))
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_ReadActiveMessage
 ��������  : ��NVIM�л�ȡ������Ų���
 �������  : MODEM_ID_ENUM_UINT16                enModemId
             MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessage  ������Ų�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 MN_ERR_NO_ERROR �������ɹ���������д����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��22��
    �޸�����   : �����ɺ��� ����C��MN_MSG_ReadActiveMessage��ֲ��A��

  2.��    ��   : 2013��3��4��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_ReadActiveMessage(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessage
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucActiveMessageInfo;
    VOS_UINT8                          *pucEvaluate;

    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        AT_WARN_LOG("AT_ReadActiveMessage : fail to alloc memory . ");
        return MN_ERR_NOMEM;
    }

    ulRet = NV_ReadEx(enModemId,
                      en_NV_Item_SMS_ActiveMessage_Para,
                      pucActiveMessageInfo,
                      MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_ReadActiveMessage : fail to read NVIM . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucActiveMessageInfo);
        return MN_ERR_CLASS_SMS_NVIM;
    }

    pucEvaluate                         = pucActiveMessageInfo;

    pstActiveMessage->enActiveStatus    = *pucEvaluate;
    pucEvaluate++;

    pstActiveMessage->enMsgCoding       = *pucEvaluate;
    pucEvaluate++;

    pstActiveMessage->stUrl.ulLen       = *pucEvaluate;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen      |= *pucEvaluate << 8;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen      |= *pucEvaluate << 16;
    pucEvaluate++;
    pstActiveMessage->stUrl.ulLen      |= *pucEvaluate << 24;
    pucEvaluate++;

    if (pstActiveMessage->stUrl.ulLen > MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN)
    {
        AT_WARN_LOG("AT_ReadActiveMessage : fail to read NVIM . ");
        pstActiveMessage->stUrl.ulLen = MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN;
    }

    PS_MEM_CPY(pstActiveMessage->stUrl.aucUrl,
               pucEvaluate,
               (VOS_UINT16)pstActiveMessage->stUrl.ulLen);

    PS_MEM_FREE(WUEPS_PID_AT, pucActiveMessageInfo);
    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : AT_SetRstriggerPara
 ��������  : ���ü�����Ų���
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��15��
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��3��4��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 AT_SetRstriggerPara(
    TAF_UINT8                           ucIndex
)
{
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessage;
    MN_MSG_ACTIVE_MESSAGE_STRU          stOrgActiveMessage;
    TAF_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    /* ������� ��
       ����Ϊ0����AT_CME_INCORRECT_PARAMETERS
       ����Ϊ2����AT_TOO_MANY_PARA
    */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_SetRstriggerPara: Get modem id fail.");
        return AT_ERROR;
    }

    ulRet = AT_ReadActiveMessage(enModemId, &stOrgActiveMessage);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_LOG1("AT_SetRstriggerPara: fail to get active message information , cause is %d",
                ulRet);
        return AT_ERROR;
    }

    /*URL:�û�û������URL,�򱣳�NVIM�е�URL����;�����û����õ�URL����NVIM������*/
    if (2 == gucAtParaIndex)
    {
        if (gastAtParaList[1].usParaLen > MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN)
        {
            stActiveMessage.stUrl.ulLen = MN_MSG_ACTIVE_MESSAGE_MAX_URL_LEN;
        }
        else
        {
            stActiveMessage.stUrl.ulLen = gastAtParaList[1].usParaLen;
        }
        PS_MEM_CPY(stActiveMessage.stUrl.aucUrl,
                   gastAtParaList[1].aucPara,
                   (VOS_UINT16)stActiveMessage.stUrl.ulLen);

        stActiveMessage.enMsgCoding    = MN_MSG_MSG_CODING_8_BIT;
    }
    else
    {
        PS_MEM_CPY(&stActiveMessage.stUrl, &stOrgActiveMessage.stUrl, sizeof(stActiveMessage.stUrl));
        stActiveMessage.enMsgCoding    = stOrgActiveMessage.enMsgCoding;
    }

    /*ACTIVE STATUS:*/
    stActiveMessage.enActiveStatus = (MN_MSG_ACTIVE_MESSAGE_STATUS_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /*����AT_WriteActiveMessageд������ŵļ���״̬��URL��Ϣ��NVIM��*/
    ulRet = AT_WriteActiveMessage(enModemId, &stOrgActiveMessage, &stActiveMessage);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return AT_ERROR;
    }

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_SetCsmsPara
 Description    : +CSMS=<service>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2008��04��18��
    �޸����� : CM�Ż�
  2.��    ��   : 2013��2��22��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCsmsPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* �������: �˴�����ھɴ������޸ģ���ȷ�� */
    if ((gucAtParaIndex != 1)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = At_UpdateMsgRcvAct(ucIndex,
                                (AT_CSMS_MSG_VERSION_ENUM_U8)gastAtParaList[0].ulParaValue,
                                pstSmsCtx->stCnmiType.CnmiMtType,
                                pstSmsCtx->stCnmiType.CnmiDsType);

    if (AT_OK != ulRet)
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSMS_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */

}
TAF_UINT32 At_SetCgsmsPara(TAF_UINT8 ucIndex)
{
    AT_NVIM_SEND_DOMAIN_STRU            stSendDomain;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    enModemId = MODEM_ID_0;
    ulLength  = 0;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        /*->f62575*/
        gastAtParaList[0].ulParaValue = MN_MSG_SEND_DOMAIN_CS;
        /*<-f62575*/
    }
/*->f62575*/

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_SetCgsmsPara:Get modem id fail");
        return AT_ERROR;
    }

    pstSmsCtx = AT_GetModemSmsCtxAddrFromModemId(enModemId);

    pstSmsCtx->stCgsmsSendDomain.enSendDomain = (AT_CGSMS_SEND_DOMAIN_ENUM_U8)gastAtParaList[0].ulParaValue;

    /* ����CGSMSʱ,���NVIM���Ѿ�����,��Э���еĶ���Ĭ��ֵ�޸�ΪNV��Ӧ��ֵ */
    if (VOS_TRUE  == pstSmsCtx->stCgsmsSendDomain.ucActFlg)
    {
        PS_MEM_SET(&stSendDomain,0,sizeof(stSendDomain));
        NV_GetLength(en_NV_Item_SMS_SEND_DOMAIN, &ulLength);
        if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_SMS_SEND_DOMAIN, &stSendDomain, ulLength))
        {
            if ( (stSendDomain.ucSendDomain == At_SendDomainProtoToNvim(pstSmsCtx->stCgsmsSendDomain.enSendDomain))
                && (stSendDomain.ucActFlg == pstSmsCtx->stCgsmsSendDomain.ucActFlg) )
            {
                AT_INFO_LOG("At_SetCgsmsPara():The content to write is same as NV's");
                return AT_OK;
            }
        }
        stSendDomain.ucSendDomain = (VOS_UINT8)At_SendDomainProtoToNvim(pstSmsCtx->stCgsmsSendDomain.enSendDomain);
        stSendDomain.ucActFlg = pstSmsCtx->stCgsmsSendDomain.ucActFlg;

        NV_GetLength(en_NV_Item_SMS_SEND_DOMAIN, &ulLength);
        if (NV_OK != NV_WriteEx(enModemId, en_NV_Item_SMS_SEND_DOMAIN, &stSendDomain, ulLength))
        {
            AT_INFO_LOG("At_SetCgsmsPara():ERROR: en_NV_Item_SMS_SEND_DOMAIN wirte failed");
            return AT_ERROR;
        }
    }
    return AT_OK;
/*<-f62575*/
}

/*****************************************************************************
 �� �� ��  : At_GetSmsStorage
 ��������  : ��ȡMN����Ŵ洢����
 �������  : VOS_UINT8 ucIndex                          �û�����
             MN_MSG_MEM_STORE_ENUM_U8 enMemReadorDelete ���Ŷ�ȡ��ɾ�������Ĵ洢����
             MN_MSG_MEM_STORE_ENUM_U8 enMemSendorWrite  ����д���Ͳ����Ĵ洢����
             MN_MSG_MEM_STORE_ENUM_U8 enMemRcv          ���Ž��ղ����Ĵ洢����
 �������  : ��
 �� �� ֵ  : AT_OK    ���ͻ�ȡ�洢����������Ϣ�ɹ�
             AT_ERROR ���ͻ�ȡ�洢����������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��18��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_GetSmsStorage(
    VOS_UINT8                           ucIndex,
    MN_MSG_MEM_STORE_ENUM_U8            enMemReadorDelete,
    MN_MSG_MEM_STORE_ENUM_U8            enMemSendorWrite,
    MN_MSG_MEM_STORE_ENUM_U8            enMemRcv
)
{
    MN_MSG_GET_STORAGE_STATUS_PARM_STRU stMemParm;

    if ((MN_MSG_MEM_STORE_SIM == enMemReadorDelete)
     || (MN_MSG_MEM_STORE_SIM == enMemSendorWrite)
     || (MN_MSG_MEM_STORE_SIM == enMemRcv))
    {
        stMemParm.enMem1Store = MN_MSG_MEM_STORE_SIM;
        gastAtClientTab[ucIndex].AtSmsData.bWaitForUsimStorageStatus = VOS_TRUE;
    }
    else
    {
        stMemParm.enMem1Store = MN_MSG_MEM_STORE_NONE;
        gastAtClientTab[ucIndex].AtSmsData.bWaitForUsimStorageStatus = VOS_FALSE;
    }

#if (NAS_FEATURE_SMS_NVIM_SMSEXIST == FEATURE_ON)
    if ((MN_MSG_MEM_STORE_NV == enMemReadorDelete)
     || (MN_MSG_MEM_STORE_NV == enMemSendorWrite)
     || (MN_MSG_MEM_STORE_NV == enMemRcv))
    {
        stMemParm.enMem2Store = MN_MSG_MEM_STORE_NV;
        gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus = VOS_TRUE;
    }
    else
    {
        stMemParm.enMem2Store = MN_MSG_MEM_STORE_NONE;
        gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus = VOS_FALSE;
    }
#else
    stMemParm.enMem2Store = MN_MSG_MEM_STORE_NONE;
    gastAtClientTab[ucIndex].AtSmsData.bWaitForNvStorageStatus = VOS_FALSE;
#endif

    if (MN_ERR_NO_ERROR != MN_MSG_GetStorageStatus(gastAtClientTab[ucIndex].usClientId,
                                                   gastAtClientTab[ucIndex].opId,
                                                   &stMemParm))
    {
        return AT_ERROR;
    }

    return AT_OK;
}


TAF_UINT32 At_SetCpmsPara(TAF_UINT8 ucIndex)
{
    MN_MSG_SET_RCVMSG_PATH_PARM_STRU    stRcvPath;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stRcvPath, 0, sizeof(MN_MSG_SET_RCVMSG_PATH_PARM_STRU));
    /* ������� */
    if ((gucAtParaIndex > 3)
     || (0 == gucAtParaIndex)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    pstSmsCtx->stCpmsInfo.enTmpMemReadorDelete = (MN_MSG_MEM_STORE_ENUM_U8)(gastAtParaList[0].ulParaValue + 1);

    if (0 != gastAtParaList[1].usParaLen)
    {
        pstSmsCtx->stCpmsInfo.enTmpMemSendorWrite = (MN_MSG_MEM_STORE_ENUM_U8)(gastAtParaList[1].ulParaValue + 1);
    }
    else
    {
        pstSmsCtx->stCpmsInfo.enTmpMemSendorWrite = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    }

    /* ִ��������� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    PS_MEM_CPY(&stRcvPath, &(pstSmsCtx->stCpmsInfo.stRcvPath), sizeof(stRcvPath));


    /* ��CNMI���õ�MT type���ʹ����TAF,��<MT>=3���յ�CLASS3����ʱ�򣬰���CMT��ʽ�ϱ� */
    stRcvPath.enCnmiMtType = pstSmsCtx->stCnmiType.CnmiMtType;

    if (0 != gastAtParaList[2].usParaLen)
    {
        stRcvPath.enStaRptMemStore = (MN_MSG_MEM_STORE_ENUM_U8)(gastAtParaList[2].ulParaValue + 1);
        stRcvPath.enSmMemStore = (MN_MSG_MEM_STORE_ENUM_U8)(gastAtParaList[2].ulParaValue + 1);
    }

    if ((MN_MSG_MEM_STORE_NV == pstSmsCtx->stCpmsInfo.enTmpMemReadorDelete)
     || (MN_MSG_MEM_STORE_NV == pstSmsCtx->stCpmsInfo.enTmpMemSendorWrite)
     || (MN_MSG_MEM_STORE_NV == stRcvPath.enSmMemStore))
    {
#if (NAS_FEATURE_SMS_NVIM_SMSEXIST != FEATURE_ON)
        return AT_ERROR;
#else
        if (MN_MSG_ME_STORAGE_ENABLE != pstSmsCtx->enMsgMeStorageStatus)
        {
            return AT_ERROR;
        }
#endif
    }

    if (MN_ERR_NO_ERROR != MN_MSG_SetRcvMsgPath(gastAtClientTab[ucIndex].usClientId,
                                                gastAtClientTab[ucIndex].opId,
                                                &stRcvPath))
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].AtSmsData.bWaitForCpmsSetRsp = TAF_TRUE;

    if (AT_OK != At_GetSmsStorage(ucIndex,
                                  pstSmsCtx->stCpmsInfo.enTmpMemReadorDelete,
                                  pstSmsCtx->stCpmsInfo.enTmpMemSendorWrite,
                                  stRcvPath.enSmMemStore))
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMS_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */

}

/*****************************************************************************
 Prototype      : At_SetCmgfPara
 Description    : +CMGF=[<mode>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
 2.��    �� : 2008��04��18��
   �޸����� : CM�Ż�
  3.��    ��   : 2013��2��20��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmgfPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if ((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
     || (gucAtParaIndex > 1))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ����Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        gastAtParaList[0].ulParaValue = AT_CMGF_MSG_FORMAT_PDU;
    }

    pstSmsCtx->enCmgfMsgFormat = (AT_CMGF_MSG_FORMAT_ENUM_U8)gastAtParaList[0].ulParaValue;
    return AT_OK;
}
/*end add by zhoujun40661 2006-10-24 for CNMA*/

/*****************************************************************************
 �� �� ��  : At_SetCscaPara
 ��������  : +CSCA=<sca>[,<tosca>]
 �������  : TAF_UINT8 ucIndex  �û�����
 �������  : ��
 �� �� ֵ  : TAF_UINT32 ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    �� : 2008��04��18��
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��25��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCscaPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8                           aucAsciiNum[MN_MAX_ASCII_ADDRESS_NUM + 2];   /*array  of ASCII Num*/
    TAF_UINT8                           ucScaType;
    TAF_UINT32                          ulRet;
    MN_MSG_WRITE_SRV_PARAM_STRU         stServParm;
    TAF_UINT8                          *pucNum;                                /*ָ��ʵ�ʺ��루������+�ţ���ָ��*/
    MN_MSG_SRV_PARAM_STRU               stParmInUsim;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen)
     || (gucAtParaIndex > 2))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ���<sca>���������ֱ�ӷ��ش��� */
    if (AT_FAILURE == At_CheckNumLen((MN_MAX_ASCII_ADDRESS_NUM + 1), gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    PS_MEM_SET(aucAsciiNum, 0x00, sizeof(aucAsciiNum));
    /* ����<sca> , ��UCS2��ת����ASCII��*/
    ulRet = At_SetNumTypePara(aucAsciiNum, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);
    if (AT_SUCCESS != ulRet)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    ucScaType = (TAF_UINT8)At_GetCodeType(aucAsciiNum[0]);
    if (AT_MSG_INTERNAL_ISDN_ADDR_TYPE == ucScaType)
    {
        pucNum = &aucAsciiNum[1];
    }
    else
    {
        pucNum = aucAsciiNum;
    }

    /* ����<tosca> */
    if (0 != gastAtParaList[1].usParaLen)
    {
        if (AT_MSG_INTERNAL_ISDN_ADDR_TYPE == ucScaType)
        {
            if (ucScaType != ((TAF_UINT8)gastAtParaList[1].ulParaValue))
            {
                return AT_CMS_OPERATION_NOT_ALLOWED;
            }
        }
        else
        {
            ucScaType = (TAF_UINT8)gastAtParaList[1].ulParaValue;
        }
    }

    /* ִ��������� */
    PS_MEM_CPY(&stParmInUsim, &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim), sizeof(stParmInUsim));

    stParmInUsim.ucParmInd &= ~MN_MSG_SRV_PARM_MASK_SC_ADDR;
    stParmInUsim.stScAddr.addrType = ucScaType;
    ulRet = AT_AsciiNumberToBcd((TAF_CHAR *)pucNum,
                                stParmInUsim.stScAddr.aucBcdNum,
                                &stParmInUsim.stScAddr.ucBcdLen);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return AT_ERROR;
    }
    stServParm.enMemStore = MN_MSG_MEM_STORE_SIM;
    stServParm.enWriteMode = MN_MSG_WRITE_MODE_REPLACE;
    stServParm.ulIndex = AT_CSCA_CSMP_STORAGE_INDEX;
    PS_MEM_CPY(&stServParm.stSrvParm, &stParmInUsim, sizeof(stServParm.stSrvParm));
    gastAtClientTab[ucIndex].opId = opId;
    if (MN_ERR_NO_ERROR == MN_MSG_WriteSrvParam(gastAtClientTab[ucIndex].usClientId, opId, &stServParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCA_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetCsmpPara
 Description    : +CSMP=[<fo>[,<vp>[,<pid>[,<dcs>]]]]
                  b7  b6   b5   b4   b3  b2  b1  b0
                  RP  UDHI SRR  VPF      RD  MTI
                  0   0    0    2        1   2
                  ע��: �������������ʱ�޷���������Ĳ����������������Ҫ���ÿ�������ĺϷ���
                  <vp>����Ǿ���ʱ�䣬����BCD��
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
  3. ��    ��   : 2007��04��04��
     �޸�����   : ���ⵥ��:A32D10081
  4. ��    �� : 2008��04��18��
     �޸����� : CM�Ż�
  5.��    ��   : 2013��2��25��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCsmpPara(TAF_UINT8 ucIndex)
{
    MN_MSG_WRITE_SRV_PARAM_STRU         stServParm;
    MN_MSG_SRV_PARAM_STRU               stParmInUsim;
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if ((AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
     || (gucAtParaIndex > 4))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ����<fo> */
    if(0 != gastAtParaList[0].usParaLen)
    {
        ulRet = At_ParseCsmpFo(&(pstSmsCtx->stCscaCsmpInfo.ucTmpFo));
        if (AT_SUCCESS != ulRet)
        {
            return ulRet;
        }
    }
    else
    {
        pstSmsCtx->stCscaCsmpInfo.ucTmpFo = pstSmsCtx->stCscaCsmpInfo.ucFo;
    }

    PS_MEM_CPY(&stParmInUsim, &(pstSmsCtx->stCscaCsmpInfo.stParmInUsim), sizeof(stParmInUsim));

    /* ����<vp> */
    ulRet =  At_ParseCsmpVp(ucIndex, &(pstSmsCtx->stCscaCsmpInfo.stTmpVp));
    if (AT_SUCCESS != ulRet)
    {
        return ulRet;
    }

    /* ����<pid> */
    if(0 != gastAtParaList[2].usParaLen)
    {
        /* ע��: gastAtParaList[2].ulParaValue��ʱ��δδת����������������������� */
        if(AT_FAILURE == At_Auc2ul(gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen,&gastAtParaList[2].ulParaValue))
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if(gastAtParaList[2].ulParaValue <= 255)
        {
            stParmInUsim.ucParmInd &= ~MN_MSG_SRV_PARM_MASK_PID;
            stParmInUsim.ucPid = (TAF_UINT8)gastAtParaList[2].ulParaValue;
        }
        else
        {
            AT_NORM_LOG("At_SetCsmpPara: unsupport VP type.");
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }

    /* ����<dcs> */
    if(0 != gastAtParaList[3].usParaLen)
    {
        /* ע��: gastAtParaList[3].ulParaValue��ʱ��δδת����������������������� */
        if(AT_FAILURE == At_Auc2ul(gastAtParaList[3].aucPara,gastAtParaList[3].usParaLen,&gastAtParaList[3].ulParaValue))
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if(gastAtParaList[3].ulParaValue <= 255)
        {
            stParmInUsim.ucParmInd &= ~MN_MSG_SRV_PARM_MASK_DCS;
            stParmInUsim.ucDcs = (TAF_UINT8)gastAtParaList[3].ulParaValue;
        }
        else
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }

    /* ִ��������� */
    stServParm.enMemStore = MN_MSG_MEM_STORE_SIM;
    stServParm.enWriteMode = MN_MSG_WRITE_MODE_REPLACE;
    stServParm.ulIndex = AT_CSCA_CSMP_STORAGE_INDEX;
    PS_MEM_CPY(&stServParm.stSrvParm, &stParmInUsim, sizeof(stServParm.stSrvParm));
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_WriteSrvParam(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId, &stServParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSMP_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetCsdhPara
 Description    : +CSDH=[<show>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��22��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCsdhPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSmsCtx->ucCsdhType = (AT_CSDH_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSmsCtx->ucCsdhType = AT_CSDH_NOT_SHOW_TYPE;
    }
    return AT_OK;
}
TAF_UINT32 At_SetCnmiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ��������ȱʡ�������� */
    /* �����������������������в���ֵΪĬ��ֵ */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        pstSmsCtx->stCnmiType.CnmiTmpModeType = AT_CNMI_MODE_BUFFER_TYPE;
        pstSmsCtx->stCnmiType.CnmiTmpMtType   = AT_CNMI_MT_NO_SEND_TYPE;
        pstSmsCtx->stCnmiType.CnmiTmpBmType   = AT_CNMI_BM_NO_SEND_TYPE;
        pstSmsCtx->stCnmiType.CnmiTmpDsType   = AT_CNMI_DS_NO_SEND_TYPE;
        pstSmsCtx->stCnmiType.CnmiTmpBfrType  = AT_CNMI_BFR_SEND_TYPE;
    }

    if (AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType)
    {
        /* ���������������������������Ϊ0�Ҳ��ܳ������������� */
        if ((0 == gucAtParaIndex)
         || (gucAtParaIndex > 5))
        {
            return AT_CMS_OPERATION_NOT_SUPPORTED;
        }

        /* ����������������û�δ���õĲ��������޸� */
        pstSmsCtx->stCnmiType.CnmiTmpModeType = pstSmsCtx->stCnmiType.CnmiModeType;
        pstSmsCtx->stCnmiType.CnmiTmpMtType   = pstSmsCtx->stCnmiType.CnmiMtType;
        pstSmsCtx->stCnmiType.CnmiTmpBmType   = pstSmsCtx->stCnmiType.CnmiBmType;
        pstSmsCtx->stCnmiType.CnmiTmpDsType   = pstSmsCtx->stCnmiType.CnmiDsType;
        pstSmsCtx->stCnmiType.CnmiTmpBfrType  = pstSmsCtx->stCnmiType.CnmiBfrType;

        if (0 != gastAtParaList[0].usParaLen)
        {
            pstSmsCtx->stCnmiType.CnmiTmpModeType = (AT_CNMI_MODE_TYPE)gastAtParaList[0].ulParaValue;
        }

        if (0 != gastAtParaList[1].usParaLen)
        {
            pstSmsCtx->stCnmiType.CnmiTmpMtType = (AT_CNMI_MT_TYPE)gastAtParaList[1].ulParaValue;
        }

        if (0 != gastAtParaList[2].usParaLen)
        {
            pstSmsCtx->stCnmiType.CnmiTmpBmType = (AT_CNMI_BM_TYPE)gastAtParaList[2].ulParaValue;
            if ( ( AT_CNMI_BM_CBM_TYPE != pstSmsCtx->stCnmiType.CnmiTmpBmType )
               && (AT_CNMI_BM_NO_SEND_TYPE != pstSmsCtx->stCnmiType.CnmiTmpBmType ))
            {
                return AT_CMS_OPERATION_NOT_SUPPORTED;
            }
        }

        if (0 != gastAtParaList[3].usParaLen)
        {
            pstSmsCtx->stCnmiType.CnmiTmpDsType = (AT_CNMI_DS_TYPE)gastAtParaList[3].ulParaValue;
        }

        if (0 != gastAtParaList[4].usParaLen)
        {
            pstSmsCtx->stCnmiType.CnmiTmpBfrType = (AT_CNMI_BFR_TYPE)gastAtParaList[4].ulParaValue;
        }

        if ((AT_CNMI_MODE_BUFFER_TYPE == pstSmsCtx->stCnmiType.CnmiTmpModeType)
         || (AT_CNMI_MODE_SEND_OR_BUFFER_TYPE == pstSmsCtx->stCnmiType.CnmiTmpModeType))
        {
            if ((AT_CNMI_MT_CMT_TYPE == pstSmsCtx->stCnmiType.CnmiTmpMtType)
             || (AT_CNMI_MT_CLASS3_TYPE == pstSmsCtx->stCnmiType.CnmiTmpMtType))
            {
                return AT_CMS_OPERATION_NOT_SUPPORTED;
            }

            if (AT_CNMI_DS_CDS_TYPE == pstSmsCtx->stCnmiType.CnmiTmpDsType)
            {
                return AT_CMS_OPERATION_NOT_SUPPORTED;
            }

        }
    }

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = At_UpdateMsgRcvAct(ucIndex,
                               pstSmsCtx->enCsmsMsgVersion,
                               pstSmsCtx->stCnmiType.CnmiTmpMtType,
                               pstSmsCtx->stCnmiType.CnmiTmpDsType);
    if (AT_OK != ulRet)
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNMI_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
}

TAF_UINT32 At_SetCmglPara(TAF_UINT8 ucIndex)
{
    MN_MSG_LIST_PARM_STRU               stListParm;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if ((AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType) && (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stListParm,0x00,sizeof(stListParm));

    stListParm.ucIsFirstTimeReq = VOS_TRUE;

    /* ����<stat> */
    if (0 != gastAtParaList[0].usParaLen)
    {
        stListParm.enStatus = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        stListParm.enStatus = (TAF_UINT8)MN_MSG_STATUS_MT_NOT_READ;
    }

    /* ���ö�ȡ�洢�� */
    stListParm.enMemStore = pstSmsCtx->stCpmsInfo.enMemReadorDelete;

    if(0 == pstSmsCtx->ucParaCmsr)
    {
        stListParm.bChangeFlag = TAF_TRUE;
    }
    else
    {
        stListParm.bChangeFlag = TAF_FALSE;
        if(gucAtParaIndex > 1)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }

    /* ִ��������� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_List(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId,&stListParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGL_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCmgrPara
 Description    : TEXT: +CMGR=<index>[,<chg>]
                  PDU : +CMGR=<index>[,<chg>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2008��04��18��
    �޸����� : CM�Ż�
  3.��    ��   : 2013��2��22��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmgrPara(TAF_UINT8 ucIndex)
{
    MN_MSG_READ_PARM_STRU               stReadParm;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stReadParm,0x00,sizeof(stReadParm));

    /* �������� */
    stReadParm.ulIndex = gastAtParaList[0].ulParaValue;

    /* ���ö�ȡ�洢�� */
    stReadParm.enMemStore = pstSmsCtx->stCpmsInfo.enMemReadorDelete;

    if(0 == pstSmsCtx->ucParaCmsr)
    {
        stReadParm.bChangeFlag = TAF_TRUE;
    }
    else
    {
        stReadParm.bChangeFlag = TAF_FALSE;
        if(gucAtParaIndex > 1)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }

    /* ִ��������� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if(MN_ERR_NO_ERROR == MN_MSG_Read(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId, &stReadParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGR_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*begin add by zhoujun40661 2006-10-10 for cnma*/
/*****************************************************************************
 Prototype      : At_SetCnmaPara
 Description    : +CNMA[=<n>[,<length>[<CR> PDU is given<ctrl-Z/ESC>]]]
                  +CNMA
 Input          :
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2008��04��18��
    �޸����� : CM�Ż�
  3.��    ��   : 2013��2��20��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCnmaPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32                          ulRet;
    TAF_BOOL                            bRpAck              = TAF_TRUE;
    MN_MSG_SEND_ACK_PARM_STRU           *pstAckParm;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (gucAtParaIndex > 2)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&gastAtClientTab[ucIndex].AtSmsData, 0x00, sizeof(gastAtClientTab[ucIndex].AtSmsData));
    if (AT_CMGF_MSG_FORMAT_TEXT == pstSmsCtx->enCmgfMsgFormat)    /* TEXT��ʽ */
    {
        if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }
    else    /* PDU��ʽ */
    {
        if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
        {
            if(0 == gastAtParaList[0].usParaLen)
            {
                return AT_CMS_OPERATION_NOT_ALLOWED;
            }
            else
            {
                /* ����<n> */
                gastAtClientTab[ucIndex].AtSmsData.ucCnmaType = (TAF_UINT8)gastAtParaList[0].ulParaValue;
            }

            /*ֻ�в���<n>,�����Ƿ���RP-ACK��RP-ERROR*/
            if ((0 != gastAtParaList[1].usParaLen)
             && (0 != gastAtParaList[1].ulParaValue))
            {
                if (0 == gastAtClientTab[ucIndex].AtSmsData.ucCnmaType)
                {
                    return AT_ERROR;
                }

                /* ����<length> */
                if (gastAtParaList[1].ulParaValue > AT_MSG_MAX_TPDU_LEN)
                {
                    AT_NORM_LOG("At_SetCnmaPara: the length of PDU is not support.");
                    return AT_CMS_OPERATION_NOT_ALLOWED;    /* �����ִ�̫�� */
                }

                gastAtClientTab[ucIndex].AtSmsData.ucPduLen = (TAF_UINT8)gastAtParaList[1].ulParaValue;
                At_SetMode(ucIndex,AT_CMD_MODE,AT_SMS_MODE);         /* �л�Ϊ����ģʽ */
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNMA_PDU_SET;
                return AT_WAIT_SMS_INPUT;   /* ������ʾ������������״̬ */
            }
            else
            {
                if (2 == gastAtClientTab[ucIndex].AtSmsData.ucCnmaType)
                {
                    bRpAck = TAF_FALSE;
                }
            }
        }
    }

    /*CMGF�������ı���ʽ, ��CNMA�޲�������CNMA������<length>Ϊ0*/
    pstAckParm = At_GetAckMsgMem();
    PS_MEM_SET(pstAckParm, 0x00, sizeof(MN_MSG_SEND_ACK_PARM_STRU));

    if (TAF_TRUE == bRpAck)
    {
        pstAckParm->bRpAck = TAF_TRUE;
        pstAckParm->stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ACK;
    }
    else
    {
        pstAckParm->bRpAck = TAF_FALSE;
        pstAckParm->enRpCause = MN_MSG_RP_CAUSE_PROTOCOL_ERR_UNSPECIFIED;
        pstAckParm->stTsRawData.enTpduType = MN_MSG_TPDU_DELIVER_RPT_ERR;
        pstAckParm->stTsRawData.ulLen = 2;
        pstAckParm->stTsRawData.aucData[0] = 0;
        pstAckParm->stTsRawData.aucData[1] = 0xff;
    }

    /* ִ��������� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_SendAck(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId, pstAckParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNMA_TEXT_SET;
        ulRet = AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        ulRet = AT_ERROR;
    }

    return ulRet;
}

/*end add by zhoujun40661 2006-10-10 for cnma*/
/*****************************************************************************
 Prototype      : At_SetCmgsPara
 Description    : TEXT: +CMGS=<da>[,<toda>]<CR>text is entered<ctrl-Z/ESC>
                  PDU : +CMGS=<length><CR>PDU is given<ctrl-Z/ESC>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2008��04��18��
    �޸����� : CM�Ż�
  3.��    ��   : 2013��2��20��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmgsPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8                           ucSmSFormat;
    TAF_UINT32                          ulRet;

    ucSmSFormat = AT_GetModemSmsCtxAddrFromClientId(ucIndex)->enCmgfMsgFormat;

    /* ������飬���<da>�������<length>�����ڣ�ֱ�ӷ��ش��� */
    if (0 == gastAtParaList[0].usParaLen )
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&gastAtClientTab[ucIndex].AtSmsData,0x00,sizeof(gastAtClientTab[ucIndex].AtSmsData));

    if (AT_CMGF_MSG_FORMAT_TEXT == ucSmSFormat)    /* TEXT��ʽ������� */
    {
        if (gucAtParaIndex > 2)  /* �������� */
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        /* �������� */
        /* ����<da> <toda>*/
        ulRet = At_GetAsciiOrBcdAddr(gastAtParaList[0].aucPara,
                                     gastAtParaList[0].usParaLen,
                                     (TAF_UINT8)gastAtParaList[1].ulParaValue,
                                     gastAtParaList[1].usParaLen,
                                     &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                                     TAF_NULL_PTR);
        if ((AT_OK != ulRet)
         || (0 == gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr.ulLen))
        {
            AT_NORM_LOG("At_SetCmgsPara: no da.");
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }


    }
    else    /* PDU��ʽ������� */
    {
        if (gucAtParaIndex > 1)  /* �������� */
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
        /* ����<length> */
        gastAtClientTab[ucIndex].AtSmsData.ucPduLen = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }

    At_SetMode(ucIndex,AT_CMD_MODE,AT_SMS_MODE);         /* �л�Ϊ����ģʽ */
    /* ���õ�ǰ�������� */
    if (AT_CMGF_MSG_FORMAT_TEXT == ucSmSFormat)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGS_TEXT_SET;
    }
    else
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGS_PDU_SET;
    }
    return AT_WAIT_SMS_INPUT;   /* ������ʾ������������״̬ */
}

/*****************************************************************************
 Prototype      : At_SetCmssPara
 Description    : TEXT: +CMSS=<index>[,<da>[,<toda>]]
                  PDU : +CMSS=<index>[,<da>[,<toda>]]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2008��04��18��
    �޸����� : CM�Ż�
  3.��    ��   : 2013��2��22��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmssPara(TAF_UINT8 ucIndex)
{
    MN_MSG_SEND_FROMMEM_PARM_STRU       stSendFromMemParm;
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������飬���<index>�����ڣ�ֱ�ӷ��ش��� */
    if ((0 == gastAtParaList[0].usParaLen)
     || (gucAtParaIndex > 3))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ����<da> */
    ulRet = At_GetAsciiOrBcdAddr(gastAtParaList[1].aucPara,
                                 gastAtParaList[1].usParaLen,
                                 (TAF_UINT8)gastAtParaList[2].ulParaValue,
                                 gastAtParaList[2].usParaLen,
                                 VOS_NULL_PTR,
                                 &stSendFromMemParm.stDestAddr);
    if (AT_OK != ulRet)
    {
        return AT_ERROR;
    }

    stSendFromMemParm.enDomain = pstSmsCtx->stCgsmsSendDomain.enSendDomain;
    /* ���÷��ʹ洢�� */
    stSendFromMemParm.enMemStore = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    stSendFromMemParm.ulIndex = gastAtParaList[0].ulParaValue;

    /* ִ��������� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_SendFromMem(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId, &stSendFromMemParm))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMSS_SET;
        gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = 1;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetCmgwPara
 Description    : TEXT: +CMGW[=<oa/da>[,<tooa/toda>[,<stat>]]]<CR>text is entered<ctrl-Z/ESC>
                  PDU : +CMGW=<length>[,<stat>]<CR>PDU is given<ctrl-Z/ESC>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
  3.��    �� : 2008��04��18��
    �޸����� : CM�Ż���
  4.��    ��   : 2013��2��25��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmgwPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8                           ucSmSFormat;
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    ucSmSFormat = pstSmsCtx->enCmgfMsgFormat;

    /* ��ʼ�� */
    PS_MEM_SET(&gastAtClientTab[ucIndex].AtSmsData,0x00,sizeof(gastAtClientTab[ucIndex].AtSmsData));
    if (AT_CMGF_MSG_FORMAT_TEXT == ucSmSFormat)    /* TEXT��ʽ������� */
    {
        /* ������� */
        if ((AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType)
         && (0 == gastAtParaList[0].usParaLen))
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if (gucAtParaIndex > 3)  /* �������� */
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        /* ����<oa/da> */
        ulRet = At_GetAsciiOrBcdAddr(gastAtParaList[0].aucPara,
                                     gastAtParaList[0].usParaLen,
                                     (TAF_UINT8)gastAtParaList[1].ulParaValue,
                                     gastAtParaList[1].usParaLen,
                                     &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                                     TAF_NULL_PTR);
        if (AT_OK != ulRet)
        {
            return ulRet;
        }

        /* ����<stat> */
        if (0 != gastAtParaList[2].usParaLen)
        {
            gastAtClientTab[ucIndex].AtSmsData.SmState = (TAF_UINT8)gastAtParaList[2].ulParaValue;
        }
        else
        {
            gastAtClientTab[ucIndex].AtSmsData.SmState = MN_MSG_STATUS_MO_NOT_SENT;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGW_TEXT_SET;
    }
    else    /* PDU��ʽ������� */
    {
        /* ������� */
        if (0 == gastAtParaList[0].usParaLen)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if (gucAtParaIndex > 2)  /* �������� */
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if (gastAtParaList[0].ulParaValue > AT_MSG_MAX_TPDU_LEN)
        {
            AT_NORM_LOG("At_SendPduMsgOrCmd: invalid tpdu data length.");
            return AT_ERROR;
        }
        gastAtClientTab[ucIndex].AtSmsData.ucPduLen = (TAF_UINT8)gastAtParaList[0].ulParaValue;

        /* ����<stat> */
        if (0 != gastAtParaList[1].usParaLen)
        {
            gastAtClientTab[ucIndex].AtSmsData.SmState = (TAF_UINT8)gastAtParaList[1].ulParaValue;
        }
        else
        {
            gastAtClientTab[ucIndex].AtSmsData.SmState = MN_MSG_STATUS_MO_NOT_SENT;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGW_PDU_SET;
    }

    if ((MN_MSG_STATUS_MT_NOT_READ != gastAtClientTab[ucIndex].AtSmsData.SmState)
     && (MN_MSG_STATUS_MT_READ != gastAtClientTab[ucIndex].AtSmsData.SmState)
     && (MN_MSG_STATUS_MO_NOT_SENT != gastAtClientTab[ucIndex].AtSmsData.SmState)
     && (MN_MSG_STATUS_MO_SENT != gastAtClientTab[ucIndex].AtSmsData.SmState))
    {
        AT_NORM_LOG("At_SetCmgwPara: invalid sm status.");
        return AT_ERROR;
    }

    At_SetMode(ucIndex,AT_CMD_MODE,AT_SMS_MODE);         /* �л�Ϊ����ģʽ */

    return AT_WAIT_SMS_INPUT;   /* ������ʾ������������״̬ */
}



TAF_UINT32 At_SetCmgdPara(TAF_UINT8 ucIndex)
{
    MN_MSG_DELETE_PARAM_STRU            stDelete;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    TAF_UINT32                          ulDeleteTypeIndex   = 0;
    TAF_UINT32                          ulDeleteTypes[5]    = {AT_MSG_DELETE_SINGLE,
                                                               AT_MSG_DELETE_READ,
                                                               (AT_MSG_DELETE_READ + AT_MSG_DELETE_SENT),
                                                               (AT_MSG_DELETE_READ + AT_MSG_DELETE_SENT + AT_MSG_DELETE_UNSENT),
                                                               AT_MSG_DELETE_ALL};
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);


    PS_MEM_SET(&stDelete, 0x00, sizeof(stDelete));


    /* ������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ����<index> */
    stDelete.ulIndex = gastAtParaList[0].ulParaValue;

    /* ����ɾ���洢�� */
    stDelete.enMemStore = pstSmsCtx->stCpmsInfo.enMemReadorDelete;

    /* ����<delflag> */
    if (0 != gastAtParaList[1].usParaLen)
    {
        ulDeleteTypeIndex = gastAtParaList[1].ulParaValue;
    }
    else
    {
        ulDeleteTypeIndex = 0;
    }

    gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes = (TAF_UINT8)ulDeleteTypes[ulDeleteTypeIndex];
    if (AT_MSG_DELETE_SINGLE == gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes)
    {
        if(0 == gastAtParaList[0].usParaLen)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }

    /* ִ��������� */
    ulRet = At_MsgDeleteCmdProc(ucIndex, opId, stDelete, gastAtClientTab[ucIndex].AtSmsData.ucMsgDeleteTypes);
    if (AT_OK != ulRet)
    {
        return ulRet;
    }

    gastAtClientTab[ucIndex].opId = opId;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGD_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
}


TAF_UINT32 At_SetCmgcPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8                           ucSmSFormat;
    TAF_UINT32                          ulRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    ucSmSFormat = pstSmsCtx->enCmgfMsgFormat;

    /* ��ʼ�� */
    PS_MEM_SET(&gastAtClientTab[ucIndex].AtSmsData,0x00,sizeof(gastAtClientTab[ucIndex].AtSmsData));

    if (AT_CMGF_MSG_FORMAT_TEXT == ucSmSFormat)    /* TEXT��ʽ*/
    {
        /* ���<ct>��<fo>�����ڣ�ֱ�ӷ��ش��� */
        if ((0 == gastAtParaList[1].usParaLen)
         || (0 == gastAtParaList[0].usParaLen))
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if (gucAtParaIndex > 6)  /* �������� */
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        /* ����<fo>.SRR */
        gastAtClientTab[ucIndex].AtSmsData.ucFo         = (TAF_UINT8)gastAtParaList[0].ulParaValue;

        /* ����<ct> */
        gastAtClientTab[ucIndex].AtSmsData.CommandType  = (TAF_UINT8)gastAtParaList[1].ulParaValue;

        /* ����<pid> */
        if (0 != gastAtParaList[2].usParaLen)
        {
            gastAtClientTab[ucIndex].AtSmsData.enPid    = (TAF_UINT8)gastAtParaList[2].ulParaValue;
        }
        else
        {
            gastAtClientTab[ucIndex].AtSmsData.enPid    = 0;
        }

        /* ����<mn> */
        if (0 == gastAtParaList[3].usParaLen)
        {
            gastAtClientTab[ucIndex].AtSmsData.ucMessageNumber  = 0;
        }
        else
        {
            gastAtClientTab[ucIndex].AtSmsData.ucMessageNumber  = (TAF_UINT8)gastAtParaList[3].ulParaValue;
        }

        /* ����<oa/da> */
        ulRet = At_GetAsciiOrBcdAddr(gastAtParaList[4].aucPara,
                                     gastAtParaList[4].usParaLen,
                                     (TAF_UINT8)gastAtParaList[5].ulParaValue,
                                     gastAtParaList[5].usParaLen,
                                     &gastAtClientTab[ucIndex].AtSmsData.stAsciiAddr,
                                     TAF_NULL_PTR);
        if (AT_OK != ulRet)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGC_TEXT_SET;
    }
    else    /* PDU��ʽ*/
    {
        /* ���<length>�����ڣ�ֱ�ӷ��ش��� */
        if (0 == gastAtParaList[0].usParaLen)
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        if (gucAtParaIndex > 1)  /* �������� */
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        gastAtClientTab[ucIndex].AtSmsData.ucPduLen = (TAF_UINT8)gastAtParaList[0].ulParaValue;
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGC_PDU_SET;
    }

    At_SetMode(ucIndex,AT_CMD_MODE,AT_SMS_MODE);         /* �л�Ϊ����ģʽ */

    return AT_WAIT_SMS_INPUT;   /* ������ʾ������������״̬ */
}
/*****************************************************************************
 Prototype      : At_SetCmstPara
 Description    : TEXT: ^CMST=<index>[,<da>[,<toda>]],<time>
                  PDU : ^CMST=<index>[,<da>[,<toda>]],<time>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
  3.��    �� : 2008��04��18��
    �޸����� : CM�Ż�
  4.��    ��   : 2013��2��22��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmstPara(TAF_UINT8 ucIndex)
{
    MN_MSG_SEND_FROMMEM_PARM_STRU       stSendFromMemParm;
    TAF_UINT32                          ulRet;
    TAF_UINT32                          ulLoop;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������飬���<index>�����ڣ�ֱ�ӷ��ش��� */
    if((0 == gastAtParaList[0].usParaLen)
    || (0 == gastAtParaList[3].usParaLen)
    || (gucAtParaIndex > 4)
    || (gastAtParaList[3].ulParaValue < 1))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ����<da> */
    ulRet = At_GetAsciiOrBcdAddr(gastAtParaList[1].aucPara,
                                 gastAtParaList[1].usParaLen,
                                 (TAF_UINT8)gastAtParaList[2].ulParaValue,
                                 gastAtParaList[2].usParaLen,
                                 VOS_NULL_PTR,
                                 &stSendFromMemParm.stDestAddr);
    if (AT_OK != ulRet)
    {
        return AT_ERROR;
    }

    stSendFromMemParm.enDomain = pstSmsCtx->stCgsmsSendDomain.enSendDomain;
    /* ���÷��ʹ洢�� */
    stSendFromMemParm.enMemStore = pstSmsCtx->stCpmsInfo.enMemSendorWrite;
    stSendFromMemParm.ulIndex = gastAtParaList[0].ulParaValue;

    /* ִ��������� */
    gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum = (TAF_UINT8)gastAtParaList[3].ulParaValue;
    for(ulLoop = 0; ulLoop < gastAtClientTab[ucIndex].AtSmsData.ucMsgSentSmNum; ulLoop++)
    {
        if(AT_SUCCESS != MN_MSG_SendFromMem(gastAtClientTab[ucIndex].usClientId, opId, &stSendFromMemParm))
        {
            return AT_ERROR;
        }
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMST_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
}

/*****************************************************************************
 �� �� ��  : At_SetCmStubPara
 ��������  : ���ò�����׮�������ݻ򴥷�׮����
             at^cmstub=<stubtype>,<Value>
             <stubtype>
             0: efsms�ļ�������
             1: efsms�ļ�����Ϊ1
             2: efsmss�����־���������
             3: efsmsp�ļ���ȡ����Ӧ��
             <Value>
             ����<stubtype>Ϊ1: efsms�ļ�����Ϊ1��<Value>����
                 0:     ������׮��
                 ���� : EFSMS������Ϊ<Value>ָ��������
             10: AT_SMS_PS_CONCATENATE_FLAG:                   PS�������������
                 0: Ĭ�Ϲر�PS������������ܣ�
                 1: ����PS������������ܣ�
             11: AT_SMS_STUB_SMS_AUTO_REPLY:
                 0: Ĭ�Ϲرն����Զ��ظ�׮���̣�
                 1: ���������Զ��ظ�׮���̣�
             ����<stubtype>Ϊ����׮���ͣ�<Value>
                 0: ������׮���̣�
                 1: ����׮���̣�
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��06��18��
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��10��28��
     �޸�����   : PC����׮���룻
  3.��    ��   : 2010��1��26��
    �޸�����   : ���ⵥ��AT2D16564
                 PS �������������δ���ã�����GCF������������Ҫ����AT ������
                 ��PS������������ܣ�������ԣ�
  4.��    ��   : 2010��01��26��
    �޸�����   : ���ⵥ��AT2D16565
                 �����Զ��ظ�׮ʧЧ���޸��Զ��ظ�׮��ʹ��������Զ��ظ����ܣ�
  5.��    ��   : 2011��10��3��
    �޸�����   : AT Project
    �漰C��ȫ�ֱ������»����C�˺����Ĳ����޸�Ϊͨ���첽��Ϣ���
  6.��    ��   : 2013��3��5��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 At_SetCmStubPara(VOS_UINT8 ucIndex)
{
    MN_MSG_STUB_MSG_STRU                stStubParam;
    VOS_UINT32                          ulRet;

    /* ����������: <stubtype>�����Ƿ���Ч��������������������2�� */
    if ((2 != gucAtParaIndex)
     || (0 == gastAtParaList[0].usParaLen)
     || (0 == gastAtParaList[1].usParaLen))
    {
        AT_LOG1("At_SetCmStubPara: invalid parameter.", gucAtParaIndex);
        AT_LOG1("At_SetCmStubPara: invalid parameter.", gastAtParaList[0].ulParaValue);
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* A���ܴ�����׮ֱ�Ӵ������˳�: �Զ��ظ����ܲ���Ҫ֪ͨC�� */
    if (MN_MSG_STUB_TYPE_SMS_AUTO_REPLY == gastAtParaList[0].ulParaValue)
    {
        AT_StubTriggerAutoReply(ucIndex, (VOS_UINT8)gastAtParaList[1].ulParaValue);
        return AT_OK;
    }

#if ( VOS_WIN32 == VOS_OS_VER )
    if (MN_MSG_STUB_TYPE_CLASS0_TAILOR == gastAtParaList[0].ulParaValue)
    {
        /* CLASS0����Ž��շ�ʽ�漰A�˺�C�������֣����Դ˴�����ֱ�ӷ��أ� */
        g_enClass0Tailor = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    }
#endif

    /* ��ҪC�˴�����׮: ������Ϣ��C�� */
    stStubParam.enStubType = (MN_MSG_STUB_TYPE_ENUM_U32)gastAtParaList[0].ulParaValue;
    stStubParam.ulValue    = gastAtParaList[1].ulParaValue;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_ReqStub(gastAtClientTab[ucIndex].usClientId,
                           gastAtClientTab[ucIndex].opId,
                           &stStubParam);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return ulRet;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMSTUB_SET;
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : At_SetCmmsPara
 ��������  : +CMMS=[<n>]
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��07��21��
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 At_SetCmmsPara(
    TAF_UINT8                           ucIndex
)
{
    MN_MSG_SET_LINK_CTRL_STRU     stSetParam;
    TAF_UINT32                          ulRet;
    MN_OPERATION_ID_T                   opId                = At_GetOpId();

    if (0 == gucAtParaIndex)
    {
        stSetParam.enRelayLinkCtrl = MN_MSG_LINK_CTRL_ENABLE;
    }
    else
    {
        stSetParam.enRelayLinkCtrl = (MN_MSG_LINK_CTRL_U8)gastAtParaList[0].ulParaValue;
    }

    ulRet = MN_MSG_SetLinkCtrl(gastAtClientTab[ucIndex].usClientId, opId, &stSetParam);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].opId = opId;
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMMS_SET;
    return AT_WAIT_ASYNC_RETURN;
}
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
VOS_UINT32 AT_ParseCbParm(
    VOS_UINT8                           *pucInPara,
    TAF_CBA_CBMI_RANGE_LIST_STRU        *pstCbRange
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          iLoop;
    VOS_UINT32                          ulParm_count;
    TAF_UINT8                           aucTemp[TAF_CBA_MAX_CBMID_RANGE_NUM];
    VOS_BOOL                            bRange;
    VOS_UINT32                          ulValue;

    pstCbRange->usCbmirNum      = 0;
    iLoop                       = 0;
    bRange                      = VOS_FALSE;
    ulParm_count                = 0;
    i                           = 0;

    while ( ( pucInPara[iLoop] != '\0' )
         && ( i < TAF_CBA_MAX_CBMID_RANGE_NUM))
    {
        i = 0;
        while ( ( pucInPara[iLoop] != ',' )
             && ( pucInPara[iLoop] != '-' )
             && ( pucInPara[iLoop] != '\0' ) )
        {
            aucTemp[i++] = pucInPara[iLoop++];
            if ( i >= 6 )
            {
                return VOS_ERR;
            }
        }

        aucTemp[i++] = '\0';

        if ( 0 == VOS_StrLen((VOS_CHAR*)aucTemp) )
        {
            return VOS_ERR;
        }

        if ( bRange )
        {
            if(AT_SUCCESS != At_Auc2ul(aucTemp,
                                        (VOS_UINT16)VOS_StrLen((VOS_CHAR*)aucTemp),
                                        &ulValue))
            {
                return VOS_ERR;
            }

            if ( ulValue > 0xFFFF )
            {
                return VOS_ERR;
            }

            if ( ulParm_count >= 1 )
            {
                pstCbRange->astCbmiRangeInfo[ulParm_count - 1].usMsgIdTo = (VOS_UINT16)ulValue;

                bRange = VOS_FALSE;
            }

        }
        else
        {
            if(AT_SUCCESS != At_Auc2ul(aucTemp,
                                       (VOS_UINT16)VOS_StrLen((VOS_CHAR*)aucTemp),
                                       &ulValue))
            {
                return VOS_ERR;
            }

            if ( ulValue > 0xFFFF )
            {
                return VOS_ERR;
            }

            pstCbRange->astCbmiRangeInfo[ulParm_count].usMsgIdFrom = (VOS_UINT16)ulValue;
            pstCbRange->astCbmiRangeInfo[ulParm_count].usMsgIdTo = (VOS_UINT16)ulValue;
            (pstCbRange->usCbmirNum)++;
            ulParm_count++;
        }

        if ( '-' == pucInPara[iLoop])
        {
            bRange = VOS_TRUE;
        }
        else if ( '\0' == pucInPara[iLoop] )
        {
            return VOS_OK;
        }
        else
        {
            bRange = VOS_FALSE;
        }

        iLoop++;

        if ( ulParm_count >= AT_MAX_CBS_MSGID_NUM )
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 AT_ProcCscbWithParm(
    TAF_UINT8                           ucIndex,
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList
)
{
    VOS_UINT32                          ulRet;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstDcssInfo;
    VOS_UINT32                          ulAppRet;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(pstCbmirList, 0x00, sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    ulRet = VOS_ERR;

    /* ���� <mids> ��Ч*/
    if ( gastAtParaList[1].usParaLen > 0 )
    {
        gastAtParaList[1].aucPara[gastAtParaList[1].usParaLen] = '\0';
        ulRet = AT_ParseCbParm(gastAtParaList[1].aucPara,pstCbmirList);
    }

    /* �������,MID�������,���һ�����Ϸ�,���򷵻س��� */
    if ( VOS_OK != ulRet )
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ���� <dcss> ��Ч*/
    if ( gastAtParaList[2].usParaLen > 0 )
    {
        pstDcssInfo = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                            sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

        if ( VOS_NULL == pstDcssInfo )
        {
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }

        gastAtParaList[2].aucPara[gastAtParaList[2].usParaLen] = '\0';
        ulRet = AT_ParseCbParm(gastAtParaList[2].aucPara,pstDcssInfo);
        if ( VOS_OK ==  ulRet)
        {
            PS_MEM_CPY(&(pstSmsCtx->stCbsDcssInfo),pstDcssInfo,sizeof(pstSmsCtx->stCbsDcssInfo));
        }
        else
        {
            PS_MEM_FREE(WUEPS_PID_AT, pstDcssInfo);
            return AT_CMS_OPERATION_NOT_ALLOWED;
        }
        PS_MEM_FREE(WUEPS_PID_AT, pstDcssInfo);
    }

    if( MN_MSG_CBMODE_ACCEPT  ==  gastAtParaList[0].ulParaValue)
    {
        ulAppRet = MN_MSG_AddCbMids(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 pstCbmirList);
    }
    else
    {
        ulAppRet = MN_MSG_DelCbMids(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 pstCbmirList);
    }

    ulRet = VOS_OK;
    /*ת��API���ý��*/
    if ( MN_ERR_NO_ERROR != ulAppRet )
    {
        ulRet = VOS_ERR;
    }

    if ( VOS_OK != ulRet )
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    return AT_OK;
}


TAF_UINT32 At_SetCscbPara(
    TAF_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRet;
    TAF_CBA_CBMI_RANGE_LIST_STRU       *pstCbmirList;
    VOS_UINT32                          ulApiRet;

    /* ���������������1,��ڶ�������������� */
    if (( gucAtParaIndex > 1 )
      && ( 0 == gastAtParaList[1].usParaLen ))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    pstCbmirList = (TAF_CBA_CBMI_RANGE_LIST_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT,
                        sizeof(TAF_CBA_CBMI_RANGE_LIST_STRU));

    if ( VOS_NULL_PTR == pstCbmirList )
    {
        AT_WARN_LOG("At_SetCscbPara: Fail to alloc memory.");
        return AT_CMS_ERROR_IN_MS;
    }

    gastAtClientTab[ucIndex].opId = At_GetOpId();

    ulRet = AT_OK;
    if ( ( 1 == gucAtParaIndex )
      && ( MN_MSG_CBMODE_ACCEPT  ==  gastAtParaList[0].ulParaValue))
    {
        /* ��ǰ������һ������,�����Ǽ�������CBS��Ϣ */
        pstCbmirList->usCbmirNum = 1;
        pstCbmirList->astCbmiRangeInfo[0].usMsgIdFrom = 0;
        pstCbmirList->astCbmiRangeInfo[0].usMsgIdTo = 0xFFFF;
        ulApiRet = MN_MSG_AddCbMids(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 pstCbmirList);

        /*ת��API���ý��*/
        if ( MN_ERR_NO_ERROR != ulApiRet )
        {
            ulRet = AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }
    else if ( ( 1 == gucAtParaIndex )
      && ( MN_MSG_CBMODE_REJECT  ==  gastAtParaList[0].ulParaValue ))
    {
        /* ��ǰ������һ������,������ȥ��������CBS��Ϣ */
        ulApiRet = MN_MSG_EmptyCbMids(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId);

        /*ת��API���ý��*/
        if ( MN_ERR_NO_ERROR != ulApiRet )
        {
            ulRet = AT_CMS_OPERATION_NOT_ALLOWED;
        }
    }
    else
    {
        /* �������в�������� */
        ulRet = AT_ProcCscbWithParm(ucIndex,pstCbmirList);
    }

    PS_MEM_FREE(WUEPS_PID_AT, pstCbmirList);

    if (AT_OK != ulRet)
    {
        return ulRet;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCB_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
}

#endif

/*****************************************************************************
 Prototype      : At_SetClipPara
 Description    : +CLIP=[<n>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��20��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetClipPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSsCtx->ucClipType = (AT_CLIP_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSsCtx->ucClipType = AT_CLIP_DISABLE_TYPE;
    }

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_SetClirPara
 Description    : +CLIR=[<n>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2006-11-27
    Modification: Created function ���ⵥA32D07303��
  2.Date        : 2007-05-30
    Modification: A32D11328
  3.��    ��   : 2013��2��20��
    �޸�����   : DSDA PHASE III
*************************************************************/
TAF_UINT32 At_SetClirPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        switch (gastAtParaList[0].ulParaValue)
        {
            case AT_CLIR_AS_SUBSCRIPT:
                pstSsCtx->ucClirType = AT_CLIR_AS_SUBSCRIPT;
                break;

            case AT_CLIR_INVOKE:
                pstSsCtx->ucClirType = AT_CLIR_INVOKE;
                break;

            case AT_CLIR_SUPPRESS:
                pstSsCtx->ucClirType = AT_CLIR_SUPPRESS;
                break;

            default:
                return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        pstSsCtx->ucClirType = AT_CLIR_AS_SUBSCRIPT;
    }
    return AT_OK;
}
VOS_UINT32 At_SetColpPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSsCtx->ucColpType = (AT_COLP_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSsCtx->ucColpType = AT_COLP_DISABLE_TYPE;
    }

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetCscsPara
 Description    : +CSCS=[<chset>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCscsPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        gucAtCscsType = (AT_CSCS_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        gucAtCscsType = AT_CSCS_IRA_CODE;
    }
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetCmeePara
 Description    : +CMEE=[<n>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCmeePara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        gucAtCmeeType = (AT_CMEE_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        gucAtCmeeType = AT_CMEE_ONLY_ERROR;
    }
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetCeerPara
 Description    : +CEER
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCeerPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,gastAtClientTab[ucIndex].ulCause);
    return AT_OK;
}

TAF_UINT32 At_SetCregPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU                  *pstNetCtx = VOS_NULL_PTR;

    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if (0 != gastAtParaList[0].usParaLen)
    {
        pstNetCtx->ucCregType   = (AT_CREG_TYPE)gastAtParaList[0].ulParaValue;
        stAtCmd.u.ucCregRptFlg  = (VOS_UINT8)gastAtParaList[0].ulParaValue;

        /* ����Ĭ��TAF_EVENT_INFO_CELL_SIGN+TAF_EVENT_INFO_CELL_ID + TAF_EVENT_INFO_CELL_BLER
           ���������ϱ����˴�������֪ͨ����㿪�������ϱ���Ŀǰû��ֹͣ��ֹͣ�˻�Ӱ��CSQ��ѯ*/
    }
    else
    {
        pstNetCtx->ucCregType   = AT_CREG_RESULT_CODE_NOT_REPORT_TYPE;
        stAtCmd.u.ucCregRptFlg  = AT_CREG_RESULT_CODE_NOT_REPORT_TYPE;
    }

    stAtCmd.enReqType = AT_MTA_SET_CREG_RPT_TYPE;

    /* ��MTA����+creg�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                      &stAtCmd,
                                      sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;
}

TAF_UINT32 At_SetCgregPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU                  *pstNetCtx = VOS_NULL_PTR;

    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstNetCtx->ucCgregType  = (AT_CGREG_TYPE)gastAtParaList[0].ulParaValue;
        stAtCmd.u.ucCgregRptFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

        /* ����Ĭ��TAF_EVENT_INFO_CELL_SIGN+TAF_EVENT_INFO_CELL_ID + TAF_EVENT_INFO_CELL_BLER
           ���������ϱ����˴�������֪ͨ����㿪�������ϱ���Ŀǰû��ֹͣ��ֹͣ�˻�Ӱ��CSQ��ѯ*/
    }
    else
    {
        pstNetCtx->ucCgregType  = AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE;
        stAtCmd.u.ucCgregRptFlg = AT_CGREG_RESULT_CODE_NOT_REPORT_TYPE;
    }

    stAtCmd.enReqType       = AT_MTA_SET_CGREG_RPT_TYPE;

    /* ��MTA����+cgreg�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;
}

#if(FEATURE_ON == FEATURE_LTE)

VOS_UINT32 AT_SetCeregPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU                  *pstNetCtx = VOS_NULL_PTR;

    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if (0 != gastAtParaList[0].usParaLen)
    {
        pstNetCtx->ucCeregType  = (AT_CEREG_TYPE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
        stAtCmd.u.ucCeregRptFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

        /* ����Ĭ��TAF_EVENT_INFO_CELL_SIGN+TAF_EVENT_INFO_CELL_ID + TAF_EVENT_INFO_CELL_BLER
           ���������ϱ����˴�������֪ͨ����㿪�������ϱ���Ŀǰû��ֹͣ��ֹͣ�˻�Ӱ��CSQ��ѯ*/
    }
    else
    {
        pstNetCtx->ucCeregType  = AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE;
        stAtCmd.u.ucCeregRptFlg = AT_CEREG_RESULT_CODE_NOT_REPORT_TYPE;
    }

    stAtCmd.enReqType       = AT_MTA_SET_CEREG_RPT_TYPE;

    /* ��MTA����+cgreg�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;
}

#endif

VOS_UINT32 At_SetClccPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϣ��C�˻�ȡ��ǰ����ͨ����Ϣ */
    ulRet = MN_CALL_GetCallInfos(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 0);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("At_SetClccPara: MN_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCC_SET;

    return AT_WAIT_ASYNC_RETURN;
}
VOS_UINT32 At_SetCpasPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_CPAS_STATUS_ENUM_U8              enCpas;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
      || (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv6State)
      || (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4v6State) )
    {
        enCpas = AT_CPAS_STATUS_RING;

        gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         enCpas);
        return AT_OK;
    }
    else if ( (AT_PDP_STATE_ACTED    == pstAppPdpEntity->enIpv4State)
           || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4State)
           || (AT_PDP_STATE_ACTED    == pstAppPdpEntity->enIpv6State)
           || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv6State)
           || (AT_PDP_STATE_ACTED    == pstAppPdpEntity->enIpv4v6State)
           || (AT_PDP_STATE_DEACTING == pstAppPdpEntity->enIpv4v6State) )

    {
        enCpas = AT_CPAS_STATUS_CALL_IN_PROGRESS;

        gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                                         "%s: %d",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                         enCpas);
        return AT_OK;
    }
    else
    {
        /* for pclint */
    }

    /* ����Ϣ��C�˻�ȡ��ǰ����ͨ����Ϣ */
    ulRet = MN_CALL_GetCallInfos(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 0);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_SetCpasPara: MN_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPAS_SET;

    return AT_WAIT_ASYNC_RETURN;


}
/*****************************************************************************
 Prototype      : At_SetCstaPara
 Description    : +CSTA=[<type>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCstaPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    g_enAtCstaNumType = (AT_CSTA_NUM_TYPE_ENUM_U8)gastAtParaList[0].ulParaValue;

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetCcugPara
 Description    : +CCUG=[<n>[,<index>[,<info>]]]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��21��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCcugPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    /* ����<n> */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSsCtx->stCcugCfg.bEnable = gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSsCtx->stCcugCfg.bEnable = 0;
    }

    /* ����<index> */
    if(0 != gastAtParaList[1].usParaLen)
    {
        if (10 == gastAtParaList[1].ulParaValue)
        {
            pstSsCtx->stCcugCfg.bIndexPresent = 0;
        }
        else
        {
            pstSsCtx->stCcugCfg.bIndexPresent = 1;
            pstSsCtx->stCcugCfg.ulIndex = (TAF_UINT8)gastAtParaList[1].ulParaValue;
        }
    }
    else
    {
        pstSsCtx->stCcugCfg.bIndexPresent = 0;
    }

    /* ����<info> */
    if(0 != gastAtParaList[2].usParaLen)
    {
        pstSsCtx->stCcugCfg.bSuppressPrefer = (gastAtParaList[2].ulParaValue & 0x02) >> 1;
        pstSsCtx->stCcugCfg.bSuppressOA     = gastAtParaList[2].ulParaValue & 0x01;
    }
    else
    {
        pstSsCtx->stCcugCfg.bSuppressPrefer = 0;
        pstSsCtx->stCcugCfg.bSuppressOA     = 0;
    }
    return AT_OK;
}
TAF_UINT32 At_SetCssnPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    MN_CALL_SET_CSSN_REQ_STRU           stCssnReq;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stCssnReq, 0, sizeof(stCssnReq));
    stCssnReq.ulActNum      = MN_CALL_MAX_CSSN_MSG_NUM;
    stCssnReq.aenSetType[0] = MN_CALL_SET_CSSN_DEACT;
    stCssnReq.aenSetType[1] = MN_CALL_SET_CSSN_DEACT;

    if(0 != gastAtParaList[0].usParaLen)
    {
        stCssnReq.aenSetType[0] = (MN_CALL_SET_CSSN_TYPE_ENUM_U32)gastAtParaList[0].ulParaValue;
    }

    if(0 != gastAtParaList[1].usParaLen)
    {
        stCssnReq.aenSetType[1] = (MN_CALL_SET_CSSN_TYPE_ENUM_U32)gastAtParaList[1].ulParaValue;
    }

    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_SET_CSSN_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   (MN_CALL_APP_REQ_PARM_UNION*)&stCssnReq);
    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSSN_SET;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
/*****************************************************************************
�� �� ��  : At_ParseSingleChldPara
��������  : ��������AT+CHLD����
�������  : TAF_UINT32                          ulParaValue
MN_CALL_SUPS_PARAM_STRU            *pstCallSupsCmd
�������  : ��
�� �� ֵ  : TAF_BOOL
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��20��
�޸�����   : �����ɺ���
2.��    ��   : 2012��03��03��
  �޸�����   : BalongV300R002 Build�Ż���Ŀ  :ɾ��NAS_FEATURE_CCBS��

*****************************************************************************/
TAF_BOOL At_ParseSingleChldPara(
    TAF_UINT32                          ulParaValue,
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsCmd
    )
{

    switch ( ulParaValue )
    {
    case 0:
        pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB;
        break;

    case 1:
        pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH;
        break;

    case 2:
        pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH;
        break;

    case 3:
        pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_BUILD_MPTY;
        break;

    case 4:
        pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_ECT;
        break;

    case 5:
       pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_ACT_CCBS;
       return AT_OK;

    default:
        return AT_ERROR;
    }
    return AT_OK;
}

/*****************************************************************************
�� �� ��  : At_ParseChldPara
��������  : ����AT+CHLD�������
�������  : TAF_UINT32                          ulParaValue
MN_CALL_SUPS_PARAM_STRU            *pstCallSupsCmd
�������  : ��
�� �� ֵ  : TAF_BOOL
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��20��
�޸�����   : �����ɺ���

*****************************************************************************/
TAF_BOOL At_ParseChldPara(
    TAF_UINT32                          ulParaValue,
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsCmd
    )
{
    TAF_BOOL                            bRetRst;
    TAF_UINT8                           ucTmp;

    ucTmp = (TAF_UINT8)(ulParaValue / 10);

    if (ulParaValue < 10)
    {
        bRetRst = At_ParseSingleChldPara(ulParaValue,pstCallSupsCmd);
    }
    else
    {
        switch(ucTmp)
        {
        case 1:
            pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_REL_CALL_X;
            pstCallSupsCmd->callId = (MN_CALL_ID_T)(ulParaValue % 10);
            bRetRst = AT_OK;
            break;

        case 2:
            pstCallSupsCmd->enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X;
            pstCallSupsCmd->callId = (MN_CALL_ID_T)(ulParaValue % 10);
            bRetRst = AT_OK;
            break;

        default:
            bRetRst = AT_ERROR;
            break;
        }
    }
    return bRetRst;
}

/*****************************************************************************
�� �� ��  : At_SetChldPara
��������  : ����AT+CHLD�������
�������  : TAF_UINT8 ucIndex
�������  : ��
�� �� ֵ  : TAF_UINT32
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��20��
�޸�����   : �����ɺ���
2.��    ��   : 2012��03��03��
  �޸�����   : BalongV300R002 Build�Ż���Ŀ  :ɾ��NAS_FEATURE_CCBS��

*****************************************************************************/
TAF_UINT32 At_SetChldPara(TAF_UINT8 ucIndex)
{
    MN_CALL_SUPS_PARAM_STRU             stCallChldParam;
    VOS_UINT32                          ulRst;


    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stCallChldParam,0,sizeof(stCallChldParam));

    ulRst = At_ParseChldPara(gastAtParaList[0].ulParaValue,&stCallChldParam);
    if (AT_ERROR == ulRst)
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS == MN_CALL_Sups(gastAtClientTab[ucIndex].usClientId,0, &stCallChldParam))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHLD_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_SetChupPara(VOS_UINT8 ucIndex)
{
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtParam;

    PS_MEM_SET(&stCallMgmtParam, 0x0, sizeof(stCallMgmtParam));

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCallMgmtParam.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ALL_CALL;
    if(AT_SUCCESS == MN_CALL_Sups(gastAtClientTab[ucIndex].usClientId, 0, &stCallMgmtParam))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHUP_SET;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_CheckDtmfKey(AT_PARSE_PARA_TYPE_STRU *pstAtPara)
{
    VOS_CHAR                            cKey;

    if ( 1 != pstAtPara->usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_SUCCESS != At_UpString(pstAtPara->aucPara, pstAtPara->usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    cKey = (VOS_CHAR)pstAtPara->aucPara[0];
    if (!( (('0' <= cKey) && ('9' >= cKey))
         || ('*' == cKey) || ('#' == cKey)
         || ('A' == cKey) || ('B' == cKey)
         || ('C' == cKey) || ('D' == cKey) ))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}


TAF_UINT32 At_SetVtsPara(TAF_UINT8 ucIndex)
{
    TAF_CALL_DTMF_PARAM_STRU            stDtmfParam;
    VOS_UINT32                          ulResult;

    /* �������͸������ */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ֵ��Ч�Լ�� */
    ulResult = AT_CheckDtmfKey(&gastAtParaList[0]);

    if (AT_SUCCESS != ulResult)
    {
        return ulResult;
    }

    /* ������ʼ�� */
    PS_MEM_SET(&stDtmfParam, 0, sizeof(stDtmfParam));

    /* ����START DTMF���� */
    stDtmfParam.cKey        = (VOS_CHAR)gastAtParaList[0].aucPara[0];
    stDtmfParam.usOnLength  = AT_VTS_DEFAULT_DTMF_LENGTH;

    stDtmfParam.usOffLength = 0;

    ulResult = TAF_CALL_SendDtmf(MN_CALL_APP_START_DTMF_REQ,
                                gastAtClientTab[ucIndex].usClientId,
                                gastAtClientTab[ucIndex].opId,
                                &stDtmfParam);

    if (VOS_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VTS_SET;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 At_CheckDtmfPara(VOS_VOID)
{

    /*������Ч�Լ��*/
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((gucAtParaIndex > 4)
     || (0 == gastAtParaList[2].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����DTMFʱ,��Ҫ������ckey,��Ҫ������ckey�Ƿ�Ϸ�
       ֹͣDTMFʱ,����Ҫ������ckey,����Ҫ������ckey�Ƿ�Ϸ� */
    if (AT_DTMF_STOP != gastAtParaList[2].ulParaValue)
    {
        if (AT_SUCCESS != AT_CheckDtmfKey(&gastAtParaList[1]))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    return AT_SUCCESS;
}



VOS_UINT32 At_SetDtmfPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    TAF_CALL_DTMF_PARAM_STRU            stDtmfParam;

    /*������Ч�Լ��*/
    ulResult = At_CheckDtmfPara();
    if (AT_SUCCESS != ulResult)
    {
        return ulResult;
    }

    PS_MEM_SET(&stDtmfParam, 0, sizeof(stDtmfParam));

    stDtmfParam.CallId  = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stDtmfParam.cKey    = (VOS_CHAR)gastAtParaList[1].aucPara[0];

    /* ���ʱ��Ϊ1����ʹ��Ĭ��DTMF��ʱ�� */
    if (AT_DTMF_START == gastAtParaList[2].ulParaValue)
    {
        stDtmfParam.usOnLength = AT_DTMF_DEFAULT_DTMF_LENGTH;
    }
    else
    {
        stDtmfParam.usOnLength = (VOS_UINT16)gastAtParaList[2].ulParaValue;
    }

    if ((0 == gastAtParaList[3].ulParaValue)
     || (gucAtParaIndex < 4))
    {
        stDtmfParam.usOffLength = 0;
    }
    else
    {
        stDtmfParam.usOffLength   = (VOS_UINT16)gastAtParaList[3].ulParaValue;

        if (stDtmfParam.usOffLength < AT_DTMF_MIN_DTMF_OFF_LENGTH)
        {
            /* offlengthȡֵΪ0����10ms-60000ms��С��10ms��osa�޷�����С��10ms��ʱ�������ز������� */
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    if (AT_DTMF_STOP != stDtmfParam.usOnLength)
    {
        ulResult = TAF_CALL_SendDtmf(MN_CALL_APP_START_DTMF_REQ,
                                    gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    &stDtmfParam);
    }
    else
    {
        ulResult = TAF_CALL_SendDtmf(MN_CALL_APP_STOP_DTMF_REQ,
                                    gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    &stDtmfParam);
    }

    if (VOS_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DTMF_SET;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/*****************************************************************************
 Prototype      : At_SetCrcPara
 Description    : +CRC=[<mode>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��25��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCrcPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSsCtx->ucCrcType = (AT_CRC_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSsCtx->ucCrcType = AT_CRC_DISABLE_TYPE;
    }

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetCbstPara
 Description    : +CBST=[<speed>[,<name>[,<ce>]]]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��21��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCbstPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSsCtx->stCbstDataCfg.enSpeed = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSsCtx->stCbstDataCfg.enSpeed = MN_CALL_CSD_SPD_64K_MULTI;
    }
    if(0 != gastAtParaList[1].usParaLen)
    {
        pstSsCtx->stCbstDataCfg.enName = (TAF_UINT8)gastAtParaList[1].ulParaValue;
    }
    else
    {
        pstSsCtx->stCbstDataCfg.enName = MN_CALL_CSD_NAME_SYNC_UDI;
    }
    if(0 != gastAtParaList[2].usParaLen)
    {
        pstSsCtx->stCbstDataCfg.enConnElem = (TAF_UINT8)gastAtParaList[2].ulParaValue;
    }
    else
    {
        pstSsCtx->stCbstDataCfg.enConnElem = MN_CALL_CSD_CE_T;
    }

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetCmodPara
 Description    : +CMOD=[<mode>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��21��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmodPara(TAF_UINT8 ucIndex)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    pstSsCtx->enCModType = (TAF_UINT8)gastAtParaList[0].ulParaValue;

    return AT_OK;

}
VOS_UINT32 At_SetCmmiPara(VOS_UINT8 ucIndex)
{
    VOS_BOOL                            inCall;
    MN_MMI_OPERATION_PARAM_STRU        *pMmiOpParam;
    VOS_CHAR                           *pcOutRestMmiStr;
    VOS_UINT32                          ulResult;
    AT_CMD_CURRENT_OPT_ENUM             enCmdCurrentOpt;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* û�к��д��ڵ���� */
    if (VOS_FALSE == pstCcCtx->ulCurIsExistCallFlag)
    {
        inCall = VOS_FALSE;
    }
    else
    {
        inCall = VOS_TRUE;
    }

    pMmiOpParam = (MN_MMI_OPERATION_PARAM_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(MN_MMI_OPERATION_PARAM_STRU));
    if(TAF_NULL_PTR == pMmiOpParam)
    {
        AT_WARN_LOG("At_SetCmmiPara Mem Alloc FAILURE");
        return AT_ERROR;
    }

    f_enClirOperate = MN_CALL_CLIR_AS_SUBS;

    pcOutRestMmiStr = (VOS_CHAR *)gastAtParaList[0].aucPara;
    pcOutRestMmiStr[gastAtParaList[0].usParaLen] = '\0';
    ulResult = MN_MmiStringParse((VOS_CHAR *)(gastAtParaList[0].aucPara), inCall, pMmiOpParam, &pcOutRestMmiStr);
    pMmiOpParam->ProcessUssdReq.DatacodingScheme = TAF_SS_7bit_LANGUAGE_UNSPECIFIED;

    if(MN_ERR_NO_ERROR == ulResult)
    {
        switch(pMmiOpParam->MmiOperationType)
        {
        case TAF_MMI_SUPPRESS_CLIR:
        case TAF_MMI_INVOKE_CLIR:

            if(TAF_MMI_SUPPRESS_CLIR == pMmiOpParam->MmiOperationType)
            {
                f_enClirOperate = MN_CALL_CLIR_SUPPRESS;
            }
            else
            {
                f_enClirOperate = MN_CALL_CLIR_INVOKE;
            }

            if((VOS_UINT16)(pcOutRestMmiStr - (VOS_CHAR *)(gastAtParaList[0].aucPara)) < gastAtParaList[0].usParaLen)
            {
                ulResult = MN_MmiStringParse(pcOutRestMmiStr, inCall, pMmiOpParam, &pcOutRestMmiStr);
            }
            else
            {
                PS_MEM_FREE(WUEPS_PID_AT, pMmiOpParam);
                return AT_CME_INCORRECT_PARAMETERS;
            }
            break;
        default :
            break;
        }
        if(MN_ERR_NO_ERROR != ulResult)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pMmiOpParam);
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* �������� */
        /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, begin */
        /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, end */

        /* ����TAF�ṩ�Ľӿڣ�����SS���� */
        enCmdCurrentOpt = At_GetMnOptType(pMmiOpParam->MmiOperationType);
        if(AT_CMD_INVALID == enCmdCurrentOpt)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pMmiOpParam);
            return AT_ERROR;
        }
        switch(enCmdCurrentOpt)
        {
            case AT_CMD_D_CS_VOICE_CALL_SET:
                if (VOS_OK != MN_CALL_Orig(gastAtClientTab[ucIndex].usClientId,
                    0,
                    &gastAtClientTab[ucIndex].AtCallInfo.CallId,
                    &(pMmiOpParam->MnCallOrig)))
                {
                    AT_WARN_LOG("At_SetCmmiPara: MN_CALL_Orig failed.");
                }
                break;
            case AT_CMD_CHLD_SET:
                if (VOS_OK != MN_CALL_Sups(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->MnCallSupsReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: MN_CALL_Sups failed.");
                }
                break;
            case AT_CMD_CPIN_UNBLOCK_SET:
                if (TAF_SUCCESS != Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->PinReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: Taf_PhonePinHandle failed.");
                }
                break;
            case AT_CMD_CPIN2_UNBLOCK_SET:
                if (TAF_SUCCESS != Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->PinReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: Taf_PhonePinHandle failed.");
                }
                break;
            case AT_CMD_CPIN_VERIFY_SET:
                if (TAF_SUCCESS != Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->PinReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: Taf_PhonePinHandle failed.");
                }

                break;
            case AT_CMD_CPIN2_VERIFY_SET:
                if (TAF_SUCCESS != Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->PinReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: Taf_PhonePinHandle failed.");
                }
                break;
            case AT_CMD_SS_REGISTER:
                if (TAF_SUCCESS != TAF_RegisterSSReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->RegisterSsReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_RegisterSSReq failed.");
                }
                break;
            case AT_CMD_SS_ERASE:
                if (TAF_SUCCESS != TAF_EraseSSReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->EraseSsReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_EraseSSReq failed.");
                }
                break;
            case AT_CMD_SS_ACTIVATE:
                if (TAF_SUCCESS != TAF_ActivateSSReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->ActivateSsReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_ActivateSSReq failed.");
                }
                break;
            case AT_CMD_SS_DEACTIVATE:
                if (TAF_SUCCESS != TAF_DeactivateSSReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->DeactivateSsReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_DeactivateSSReq failed.");
                }
                break;

             case AT_CMD_SS_DEACTIVE_CCBS:
                if (TAF_SUCCESS != TAF_EraseCCEntryReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->stCcbsEraseReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_EraseCCEntryReq failed.");
                }
                break;

            case AT_CMD_SS_INTERROGATE:
            case AT_CMD_SS_INTERROGATE_CCBS:
                if (TAF_SUCCESS != TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->InterrogateSsReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_DeactivateSSReq failed.");
                }
                break;
            case AT_CMD_SS_REGISTER_PSWD:
                if (TAF_SUCCESS != TAF_RegisterPasswordReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->RegPwdReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_InterrogateSSReq failed.");
                }
                break;
            /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, begin */
            /* ɾ��AT_CMD_SS_GET_PSWD ��֧ */
            /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, end */
            case AT_CMD_SS_USSD:
                if (TAF_SUCCESS != TAF_ProcessUnstructuredSSReq(gastAtClientTab[ucIndex].usClientId,0, &pMmiOpParam->ProcessUssdReq))
                {
                    AT_WARN_LOG("At_SetCmmiPara: TAF_ProcessUnstructuredSSReq failed.");
                }
                break;
            case AT_CMD_CLIP_READ:
                pstSsCtx->ucClipType = (AT_CLIP_TYPE)gastAtParaList[0].ulParaValue;
                PS_MEM_FREE(WUEPS_PID_AT, pMmiOpParam);
                return AT_OK;
            default:
                break;
        }
        gastAtClientTab[ucIndex].CmdCurrentOpt = enCmdCurrentOpt;
        PS_MEM_FREE(WUEPS_PID_AT, pMmiOpParam);
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        PS_MEM_FREE(WUEPS_PID_AT, pMmiOpParam);
        return AT_CME_INCORRECT_PARAMETERS;
    }
}



VOS_UINT32 AT_CheckApnFirstAndLastChar(
    VOS_UINT8                           ucApnCharacter
)
{
    if ( ! ( (('A' <= ucApnCharacter) && ('Z' >= ucApnCharacter))
          || (('0' <= ucApnCharacter) && ('9' >= ucApnCharacter)) ) )
    {
        AT_WARN_LOG("AT_CheckApnFirstAndLastChar: WARNING: Invalid begin/end character in APN.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_CheckApnFormat(
    VOS_UINT8                          *pucApn,
    VOS_UINT16                          usApnLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucApnCharacter;

    for ( i = 0 ; i < usApnLen; i++ )
    {
        /* ת��APN�ַ�Ϊ��д */
        ucApnCharacter = AT_UPCASE(pucApn[i]);

        /* ���APN�ַ���Ч�� */
        if ( ! ( (('A' <= ucApnCharacter) && ('Z' >= ucApnCharacter))
              || (('0' <= ucApnCharacter) && ('9' >= ucApnCharacter))
              || ('-' == ucApnCharacter)
              || ('.' == ucApnCharacter) ) )
        {
            AT_WARN_LOG("AT_CheckApn: WARNING: Invalid character in APN.");
            return VOS_ERR;
        }
    }

    /* ���APN��ʼ�ַ���Ч�� */
    ucApnCharacter = AT_UPCASE(pucApn[0]);
    if ( VOS_OK != AT_CheckApnFirstAndLastChar(ucApnCharacter) )
    {
        AT_WARN_LOG("AT_CheckApn: WARNING: Invalid begin/end character in APN.");
        return VOS_ERR;
    }

    /* ���APNĩβ�ַ���Ч�� */
    ucApnCharacter = AT_UPCASE(pucApn[usApnLen - 1]);
    if ( VOS_OK != AT_CheckApnFirstAndLastChar(ucApnCharacter) )
    {
        AT_WARN_LOG("AT_CheckApn: WARNING: Invalid begin/end character in APN.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_SetCgdcontPara(VOS_UINT8 ucIndex)
{
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpCxtInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stPdpCxtInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 10 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<CID> */
    stPdpCxtInfo.ucCid                  = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stPdpCxtInfo.ucDefined          = VOS_FALSE;
    }
    else
    {
        stPdpCxtInfo.ucDefined          = VOS_TRUE;

        /* ����<PDP_type> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            if ( gastAtParaList[1].ulParaValue < TAF_PDP_PPP )
            {
                stPdpCxtInfo.bitOpPdpType   = VOS_TRUE;

                /* IP:1, IPV6:2, IPV4V6:3, PPP:4 */
                stPdpCxtInfo.enPdpType  = (VOS_UINT8)(gastAtParaList[1].ulParaValue + 1);

                if ( (TAF_PDP_IPV6   == stPdpCxtInfo.enPdpType)
                  || (TAF_PDP_IPV4V6 == stPdpCxtInfo.enPdpType) )
                {
#if (FEATURE_ON == FEATURE_IPV6)
                    if (AT_IPV6_CAPABILITY_IPV4_ONLY == AT_GetIpv6Capability())
                    {
                        return AT_CME_INCORRECT_PARAMETERS;
                    }
#else
                    return AT_CME_INCORRECT_PARAMETERS;
#endif
                }
            }
        }
        /* �Ա��ն˵Ľ������<PDP_type>����Ϊ""(��������)ʱ,����ԭ�ȵ�ֵ��
           ��g_TafCidTab[ucCid].ucUsedָʾ�����ı�ɾ������ʹ��֮ǰ����������ֵ */

        /* ����<APN> */
        if ( gastAtParaList[2].usParaLen > TAF_MAX_APN_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ( 0 != gastAtParaList[2].usParaLen )
        {
            /* ��� */
            if ( VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                             gastAtParaList[2].usParaLen) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stPdpCxtInfo.bitOpApn       = VOS_TRUE;
            PS_MEM_CPY((VOS_CHAR*)stPdpCxtInfo.aucApn,
                       (VOS_CHAR*)gastAtParaList[2].aucPara,
                       gastAtParaList[2].usParaLen);
            stPdpCxtInfo.aucApn[gastAtParaList[2].usParaLen] = 0;
        }

        /* ����<PDP_addr> */
        /* ֻ����IPV4��IP ADDR��IPV6��ʹ�ô�AT�������õ�IP ADDR */
        if ( 0 != gastAtParaList[3].usParaLen )
        {
            if ( (TAF_PDP_IPV4 != (gastAtParaList[1].ulParaValue + 1))
              || (gastAtParaList[3].usParaLen > (TAF_MAX_IPV4_ADDR_STR_LEN - 1)) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stPdpCxtInfo.bitOpPdpAddr        = VOS_TRUE;
            stPdpCxtInfo.stPdpAddr.enPdpType = TAF_PDP_IPV4;

            /* ��IP��ַ�ַ���ת�������� */
            if ( VOS_OK != AT_Ipv4AddrAtoi((VOS_CHAR*)gastAtParaList[3].aucPara,
                                           (VOS_UINT8*)stPdpCxtInfo.stPdpAddr.aucIpv4Addr) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }

        /* ����<d_comp> */
        if ( 0 != gastAtParaList[4].usParaLen )
        {
            stPdpCxtInfo.bitOpPdpDcomp  = VOS_TRUE;
            stPdpCxtInfo.enPdpDcomp     = (VOS_UINT8)gastAtParaList[4].ulParaValue;
        }

        /* ����<h_comp> */
        if ( 0 != gastAtParaList[5].usParaLen )
        {
            stPdpCxtInfo.bitOpPdpHcomp  = VOS_TRUE;
            stPdpCxtInfo.enPdpHcomp     = (VOS_UINT8)gastAtParaList[5].ulParaValue;
        }

        /* ����<IPv4AddrAlloc> */
        if ( 0 != gastAtParaList[6].usParaLen )
        {
            stPdpCxtInfo.bitOpIpv4AddrAlloc = VOS_TRUE;
            stPdpCxtInfo.enIpv4AddrAlloc    = (VOS_UINT8)gastAtParaList[6].ulParaValue;
        }

        /* ����<Emergency Indication> */
        if ( 0 != gastAtParaList[7].usParaLen )
        {
            stPdpCxtInfo.bitOpEmergencyInd = VOS_TRUE;
            stPdpCxtInfo.enEmergencyFlg    = (VOS_UINT8)gastAtParaList[7].ulParaValue;
        }
        /* ����<P-CSCF_discovery> */
        if ( 0 != gastAtParaList[8].usParaLen )
        {
            stPdpCxtInfo.bitOpPcscfDiscovery = VOS_TRUE;
            stPdpCxtInfo.enPcscfDiscovery    = (VOS_UINT8)gastAtParaList[8].ulParaValue;
        }
        /* ����<IM_CN_Signalling_Flag_Ind> */
        if ( 0 != gastAtParaList[9].usParaLen )
        {
            stPdpCxtInfo.bitOpImCnSignalFlg = VOS_TRUE;
            stPdpCxtInfo.enImCnSignalFlg    = (VOS_UINT8)gastAtParaList[9].ulParaValue;
        }
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetPrimPdpContextInfo(WUEPS_PID_AT,
                                                gastAtClientTab[ucIndex].usClientId,
                                                0,
                                                &stPdpCxtInfo) )
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetCgdscontPara(VOS_UINT8 ucIndex)
{
    TAF_PDP_SEC_CONTEXT_EXT_STRU        stPdpCxtInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stPdpCxtInfo, 0x00, sizeof(TAF_PDP_SEC_CONTEXT_EXT_STRU));

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 4 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<s_cid> */
    stPdpCxtInfo.ucCid         = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stPdpCxtInfo.ucDefined          = VOS_FALSE;
    }
    else
    {
        stPdpCxtInfo.ucDefined          = VOS_TRUE;

        /* ����<p_cid> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            stPdpCxtInfo.bitOpLinkdCid = VOS_TRUE;
            stPdpCxtInfo.ucLinkdCid    = (VOS_UINT8)gastAtParaList[1].ulParaValue;

            if (stPdpCxtInfo.ucCid == stPdpCxtInfo.ucLinkdCid)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }
        else
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

#ifndef AT_OLNY_LTE_MODE
        /* ����<d_comp> */
        if ( 0 != gastAtParaList[2].usParaLen )
        {
            stPdpCxtInfo.bitOpPdpDcomp  = VOS_TRUE;
            stPdpCxtInfo.enPdpDcomp     = (VOS_UINT8)gastAtParaList[2].ulParaValue;
        }

        /* ����<h_comp> */
        if ( 0 != gastAtParaList[3].usParaLen )
        {
            stPdpCxtInfo.bitOpPdpHcomp  = VOS_TRUE;
            stPdpCxtInfo.enPdpHcomp     = (VOS_UINT8)gastAtParaList[3].ulParaValue;
        }
#endif
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetSecPdpContextInfo(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0,
                                               &stPdpCxtInfo) )
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCgeqreqPara(TAF_UINT8 ucIndex)
{
    TAF_UMTS_QOS_EXT_STRU               stUmtsQosInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stUmtsQosInfo, 0x00, sizeof(TAF_UMTS_QOS_EXT_STRU));

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 13 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<cid> */
    stUmtsQosInfo.ucCid                     = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stUmtsQosInfo.ucDefined             = VOS_FALSE;
    }
    else
    {
        stUmtsQosInfo.ucDefined             = VOS_TRUE;

        /* ����<Traffic class> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            stUmtsQosInfo.bitOpTrafficClass = VOS_TRUE;
            stUmtsQosInfo.ucTrafficClass    = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }

        /* ����<Maximum bitrate UL> */
        if ( 0 != gastAtParaList[2].usParaLen )
        {
            stUmtsQosInfo.bitOpMaxBitUl     = VOS_TRUE;
            stUmtsQosInfo.ulMaxBitUl        = gastAtParaList[2].ulParaValue;
        }

        /* ����<Maximum bitrate DL> */
        if ( 0 != gastAtParaList[3].usParaLen )
        {
            stUmtsQosInfo.bitOpMaxBitDl     = VOS_TRUE;
            stUmtsQosInfo.ulMaxBitDl        = gastAtParaList[3].ulParaValue;
        }

        /* ����<Guaranteed bitrate UL> */
        if ( 0 != gastAtParaList[4].usParaLen )
        {
            stUmtsQosInfo.bitOpGtdBitUl     = VOS_TRUE;
            stUmtsQosInfo.ulGtdBitUl        = gastAtParaList[4].ulParaValue;
        }

        /* ����<Guaranteed bitrate DL> */
        if ( 0 != gastAtParaList[5].usParaLen )
        {
            stUmtsQosInfo.bitOpGtdBitDl     = VOS_TRUE;
            stUmtsQosInfo.ulGtdBitDl        = gastAtParaList[5].ulParaValue;
        }

        /* ����<Delivery order> */
        if ( 0 != gastAtParaList[6].usParaLen )
        {
            stUmtsQosInfo.bitOpDeliverOrder = VOS_TRUE;
            stUmtsQosInfo.ucDeliverOrder    = (VOS_UINT8)gastAtParaList[6].ulParaValue;
        }

        /* ����<Maximum SDU size> */
        if ( 0 != gastAtParaList[7].usParaLen )
        {
            stUmtsQosInfo.bitOpMaxSduSize   = VOS_TRUE;
            stUmtsQosInfo.usMaxSduSize      = (VOS_UINT16)gastAtParaList[7].ulParaValue;
        }

        /* ����<SDU error ratio> */
        if ( 0 != gastAtParaList[8].usParaLen )
        {
            stUmtsQosInfo.bitOpSduErrRatio  = VOS_TRUE;
            stUmtsQosInfo.ucSduErrRatio     = (VOS_UINT8)gastAtParaList[8].ulParaValue;
        }

        /* ����<Residual bit error ratio> */
        if ( 0 != gastAtParaList[9].usParaLen )
        {
            stUmtsQosInfo.bitOpResidualBer  = VOS_TRUE;
            stUmtsQosInfo.ucResidualBer     = (VOS_UINT8)gastAtParaList[9].ulParaValue;
        }

        /* ����<Delivery of erroneous SDUs> */
        if ( 0 != gastAtParaList[10].usParaLen )
        {
            stUmtsQosInfo.bitOpDeliverErrSdu = VOS_TRUE;
            stUmtsQosInfo.ucDeliverErrSdu    = (VOS_UINT8)gastAtParaList[10].ulParaValue;
        }

        /* ����<Transfer delay> */
        if ( 0 != gastAtParaList[11].usParaLen )
        {
            stUmtsQosInfo.bitOpTransDelay   = VOS_TRUE;
            stUmtsQosInfo.usTransDelay      = (VOS_UINT16)gastAtParaList[11].ulParaValue;
        }

        /* ����<Traffic handling priority> */
        if ( 0 != gastAtParaList[12].usParaLen )
        {
            stUmtsQosInfo.bitOpTraffHandlePrior = VOS_TRUE;
            stUmtsQosInfo.ucTraffHandlePrior    = (VOS_UINT8)gastAtParaList[12].ulParaValue;
        }
    }

    /* ִ��������� */
    if(AT_CMD_CGEQREQ == g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex)
    {
        if ( VOS_OK != TAF_PS_SetUmtsQosInfo(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0, &stUmtsQosInfo) )
        {
            return AT_ERROR;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGEQREQ_SET;
    }
    else
    {
        if ( VOS_OK != TAF_PS_SetUmtsQosMinInfo(WUEPS_PID_AT,
                                                gastAtClientTab[ucIndex].usClientId,
                                                0, &stUmtsQosInfo) )
        {
            return AT_ERROR;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CGEQMIN_SET;

    }

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCgeqminPara(TAF_UINT8 ucIndex)
{
    return AT_SetCgeqreqPara(ucIndex);
}


TAF_UINT32 AT_SetCgpaddrPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCidIndex;
    TAF_CID_LIST_STRU                   stCidListInfo;
    VOS_UINT32                          ulIndex;

    /* ��ʼ�� */
    ulCidIndex  = 0;
    PS_MEM_SET(&stCidListInfo, 0x00, sizeof(TAF_CID_LIST_STRU));

    /* �������� */
    if ( gucAtParaIndex > TAF_MAX_CID )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulIndex = AT_MAX_PARA_NUMBER;
#else
    ulIndex = TAF_MAX_CID;
#endif

    /* �������� */
    if ( 0 != gucAtParaIndex )
    {
        for ( i = 0; i < ulIndex; i++ )
        {
            if ( 0 == gastAtParaList[i].usParaLen )
            {
                break;
            }
            else
            {
                ulCidIndex = gastAtParaList[i].ulParaValue;
            }

            /* ��CID��Ϊ�±�, ��Ƕ�Ӧ��CID */
            stCidListInfo.aucCid[ulCidIndex] = 1;
        }
    }
    else
    {
        for ( i = 1; i <= TAF_MAX_CID; i++ )
        {
            stCidListInfo.aucCid[i] = 1;
        }
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetPdpIpAddrInfo(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0, &stCidListInfo) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGPADDR_SET;

    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCgeqnegPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCidIndex;
    TAF_CID_LIST_STRU                   stCidListInfo;
    VOS_UINT32                          ulIndex;

    /* ��ʼ�� */
    ulCidIndex  = 0;
    PS_MEM_SET(&stCidListInfo, 0x00, sizeof(TAF_CID_LIST_STRU));

    /* �������� */
    if ( gucAtParaIndex > TAF_MAX_CID )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulIndex = AT_MAX_PARA_NUMBER;
#else
    ulIndex = TAF_MAX_CID;
#endif

    /* �������� */
    /* +CGEQNEG[=<cid>[,<cid>[,...]]] */
    if ( 0 != gucAtParaIndex )
    {
        for ( i = 0; i < ulIndex; i++ )
        {
            if ( 0 == gastAtParaList[i].usParaLen )
            {
                break;
            }
            else
            {
                ulCidIndex = gastAtParaList[i].ulParaValue;
            }

            /* ��CID��Ϊ�±�, ��Ƕ�Ӧ��CID */
            stCidListInfo.aucCid[ulCidIndex] = 1;
        }
    }
    else
    {
        for ( i = 1; i <= TAF_MAX_CID; i++ )
        {
            stCidListInfo.aucCid[i] = 1;
        }
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetDynamicUmtsQosInfo(WUEPS_PID_AT,
                                                gastAtClientTab[ucIndex].usClientId,
                                                0,
                                                &stCidListInfo) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQNEG_SET;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_SetCgcmodPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCidIndex;
    TAF_CID_LIST_STRU                   stCidListInfo;

    /* ��ʼ�� */
    ulCidIndex  = 0;
    PS_MEM_SET(&stCidListInfo, 0x00, sizeof(TAF_CID_LIST_STRU));

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( 0 != gucAtParaIndex )
    {
        for ( i = 0; i < AT_MAX_PARA_NUMBER; i++ )
        {
            if ( 0 == gastAtParaList[i].usParaLen )
            {
                break;
            }
            else
            {
                ulCidIndex = gastAtParaList[i].ulParaValue;
            }

            /* ��CID��Ϊ�±�, ��Ƕ�Ӧ��CID */
            stCidListInfo.aucCid[ulCidIndex] = VOS_TRUE;
        }
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_CallModify(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     &stCidListInfo) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCMOD_SET;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_SetCgactPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulCidIndex;
    TAF_CID_LIST_STATE_STRU             stCidListStateInfo;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    /* ��ʼ�� */
    ulCidIndex  = 0;
    PS_MEM_SET(&stCidListStateInfo, 0x00, sizeof(TAF_CID_LIST_STATE_STRU));

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex != 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* �������� */
    stCidListStateInfo.ucState  = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    for ( i = 0; i < (AT_MAX_PARA_NUMBER - 1); i++ )
    {
        if ( 0 == gastAtParaList[i + 1].usParaLen )
        {
            break;
        }
        else
        {
            ulCidIndex = gastAtParaList[i + 1].ulParaValue;

            /* ��ΪAP-Modem��̬���������Ƿ�ΪHSIC ATͨ���·���CGACT����
                ���Ѿ�������CID������ͨ����ӳ���ϵ�������򷵻�ERROR */
            if (VOS_TRUE == AT_CheckHsicUser(ucIndex))
            {
                if ((VOS_FALSE == pstPsModemCtx->astChannelCfg[ulCidIndex].ulUsed)
                  ||(UDI_INVAL_DEV_ID == (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[ulCidIndex].ulRmNetId))
                {
                    return AT_ERROR;
                }
            }
        }

        /* ��CID��Ϊ�±�, ��Ƕ�Ӧ��CID */
        stCidListStateInfo.aucCid[ulCidIndex] = 1;
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetPdpContextState(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0,
                                             &stCidListStateInfo) )
    {
        return AT_ERROR;
    }

    if ( 1 == stCidListStateInfo.ucState )
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_ORG_SET;
    }
    else
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_END_SET;
    }

    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCgansPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucRspType;
    TAF_PS_ANSWER_STRU                  stAnsInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stAnsInfo, 0x00, sizeof(TAF_PS_ANSWER_STRU));

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 3 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    ucRspType           = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ����<CID> */
    if ( 0 != gastAtParaList[2].usParaLen )
    {
        stAnsInfo.ucCid = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    }

    /* ���ans��չ��־ */
    if (AT_CMD_CGANS_EXT == g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex)
    {
        stAnsInfo.ucAnsExtFlg = VOS_TRUE;
    }
    else
    {
        stAnsInfo.ucAnsExtFlg = VOS_FALSE;
    }

    /* ִ��������� */
    if ( 1 == ucRspType )
    {
        if ( VOS_OK == TAF_PS_CallAnswer(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0,
                                         &stAnsInfo) )
        {
            /* ���õ�ǰ�������� */
            if (AT_CMD_CGANS_EXT == g_stParseContext[ucIndex].pstCmdElement->ulCmdIndex)
            {
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_EXT_SET;
            }
            else
            {
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_SET;
            }

            /* �������������״̬ */
            return AT_WAIT_ASYNC_RETURN;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        /* 0 --  �ܾ����緢��ļ���ָʾ */
        if ( VOS_OK == TAF_PS_CallHangup(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) )
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGANS_ANS_SET;

            /* �������������״̬ */
            return AT_WAIT_ASYNC_RETURN;
        }
        else
        {
            return AT_ERROR;
        }
    }
}


VOS_UINT32 AT_CountSpecCharInString(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen,
    VOS_UINT8                           ucChar
)
{
    VOS_UINT8                          *pucRead;
    VOS_UINT32                          ulChkLen;
    VOS_UINT32                          ulCount;

    if(VOS_NULL_PTR == pucData)
    {
        return 0;
    }

    pucRead                             = pucData;
    ulChkLen                            = 0;
    ulCount                             = 0;

    /* ��� */
    while( ulChkLen++ < usLen )
    {
        if(ucChar == *pucRead)
        {
            ulCount++;
        }
        pucRead++;
    }

    return ulCount;

}
VOS_UINT32 AT_FillTftIpv4Addr(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *ptrTmp;

    ulCount = 0;
    ptrTmp  = VOS_NULL_PTR;

    ulCount = AT_CountDigit(pucData, usLen, '.', 7);
    if ((0 == ulCount) || (0 == pucData[ulCount]))
    {
        return AT_FAILURE;
    }

    ulCount = AT_CountDigit(pucData, usLen, '.', 4);

    pstTftInfo->bitOpSrcIp = VOS_TRUE;
    pstTftInfo->stSourceIpaddr.enPdpType = TAF_PDP_IPV4;
    pstTftInfo->stSourceIpMask.enPdpType = TAF_PDP_IPV4;

    if ((usLen - ulCount) > TAF_MAX_IPV4_ADDR_STR_LEN)
    {
        return AT_FAILURE;
    }

    ptrTmp = (VOS_CHAR *)&(pucData[ulCount]);

    ulRet = AT_Ipv4AddrAtoi(ptrTmp, pstTftInfo->stSourceIpMask.aucIpv4Addr);
    if(VOS_OK != ulRet)
    {
        return AT_FAILURE;
    }

    if ((ulCount - 1) > TAF_MAX_IPV4_ADDR_STR_LEN)
    {
        return AT_FAILURE;
    }

    ptrTmp = (VOS_CHAR *)(pucData);
    ptrTmp[ulCount - 1] = '\0';

    ulRet = AT_Ipv4AddrAtoi(ptrTmp, pstTftInfo->stSourceIpaddr.aucIpv4Addr);
    if (VOS_OK != ulRet)
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;

}


VOS_UINT32 AT_FillTftIpv6Addr(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    VOS_UINT32                          ulCount;
    VOS_UINT32                          ulRet;
    VOS_CHAR                           *ptrTmp;

    ulCount = 0;
    ptrTmp  = VOS_NULL_PTR;

    ulCount = AT_CountDigit(pucData, usLen, '.', 31);
    if ((0 == ulCount) || (0 == pucData[ulCount]))
    {
        return AT_FAILURE;
    }

    ulCount = AT_CountDigit(pucData, usLen, '.', 16);

    pstTftInfo->bitOpSrcIp = VOS_TRUE;
    pstTftInfo->stSourceIpaddr.enPdpType = TAF_PDP_IPV6;
    pstTftInfo->stSourceIpMask.enPdpType = TAF_PDP_IPV6;

    if ((usLen - ulCount) > TAF_MAX_IPV6_ADDR_DOT_STR_LEN)
    {
        return AT_FAILURE;
    }

    ptrTmp = (VOS_CHAR *)&(pucData[ulCount]);

    ulRet = AT_Ipv6AddrAtoi(ptrTmp, pstTftInfo->stSourceIpMask.aucIpv6Addr);
    if(VOS_OK != ulRet)
    {
        return AT_FAILURE;
    }

    if ((ulCount - 1) > TAF_MAX_IPV6_ADDR_DOT_STR_LEN)
    {
        return AT_FAILURE;
    }

    ptrTmp = (VOS_CHAR *)(pucData);
    ptrTmp[ulCount - 1] = '\0';

    ulRet = AT_Ipv6AddrAtoi(ptrTmp, pstTftInfo->stSourceIpaddr.aucIpv6Addr);
    if (VOS_OK != ulRet)
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_FillTftIpAddr(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen,
    TAF_TFT_EXT_STRU                   *pstTftInfo
)
{
    VOS_UINT32                          ulCount;

    /* ��ȡ�����IP��ַ�а�����'.'�ĸ��� */
    ulCount = AT_CountSpecCharInString(pData, usLen, '.');

    /* �������ΪIPV4��ַ����ַ���������7��'.' */
    /* ����"10.140.23.144.255.255.255.0"��ǰ4����IPV4��ַ����4��Ϊ���� */
    if ((TAF_IPV4_ADDR_LEN * 2 - 1) == ulCount)
    {
        return (AT_FillTftIpv4Addr(pData, usLen, pstTftInfo));
    }
    /* �������ΪIPV6��ַ����ַ���������31��'.' */
    /* ����"32.8.0.2.0.2.0.1.0.2.0.1.0.3.21.111.255.255.255.255.255.255.255.255.255.255.255.255.255.255.255.255" */
    /* ǰ16��ΪIPV6��ַ����16��Ϊ���� */
#if (FEATURE_ON == FEATURE_IPV6)
    else if ((AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
           && ((TAF_IPV6_ADDR_LEN * 2 - 1) == ulCount))
    {
        return (AT_FillTftIpv6Addr(pData, usLen, pstTftInfo));
    }
#endif
    else
    {
        return AT_FAILURE;
    }
}


TAF_UINT32 AT_SetCgtftPara(TAF_UINT8 ucIndex)
{
    TAF_TFT_EXT_STRU                    stTftInfo;
    VOS_UINT32                          ulLow  = 0;
    VOS_UINT32                          ulHigh = 0;
    VOS_UINT32                          ulCount = 0;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    PS_MEM_SET(&stTftInfo, 0x00, sizeof(TAF_TFT_EXT_STRU));

    /* ���û��cid���򷵻�ʧ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������,<flow label (ipv6)>��֧�֣�<direction>Ҳ���ټ�� */
    if ( gucAtParaIndex > 11 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<cid> */
    stTftInfo.ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stTftInfo.ucDefined             = VOS_FALSE;
    }
    else
    {
        stTftInfo.ucDefined             = VOS_TRUE;

        /* ����<packet filter identifier> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            stTftInfo.bitOpPktFilterId  = 1;
            stTftInfo.ucPacketFilterId  = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }

        /* ����<evaluation precedence index> */
        if ( 0 != gastAtParaList[2].usParaLen )
        {
            stTftInfo.bitOpPrecedence   = 1;
            stTftInfo.ucPrecedence      = (VOS_UINT8)gastAtParaList[2].ulParaValue;
        }

        /* ����<source address and subnet mask> */
        if ( 0 != gastAtParaList[3].usParaLen )
        {
            ulRet = AT_FillTftIpAddr(gastAtParaList[3].aucPara,
                                     gastAtParaList[3].usParaLen,
                                     &stTftInfo);
            if (AT_FAILURE == ulRet)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }

        /* ����<protocol number (ipv4) / next header (ipv6)> */
        if(0 != gastAtParaList[4].usParaLen)
        {
            stTftInfo.bitOpProtocolId   = 1;
            stTftInfo.ucProtocolId      = (VOS_UINT8)gastAtParaList[4].ulParaValue;
        }

        /* ����<destination port range> */
        if(0 != gastAtParaList[5].usParaLen)
        {
            ulCount = AT_CountDigit(gastAtParaList[5].aucPara,gastAtParaList[5].usParaLen,'.',1);
            if((0 == ulCount) || (0 == gastAtParaList[5].aucPara[ulCount]))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stTftInfo.bitOpDestPortRange= 1;

            if(AT_FAILURE == atAuc2ul(gastAtParaList[5].aucPara,(VOS_UINT16)(ulCount-1),&ulLow))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            if(AT_FAILURE == atAuc2ul(&gastAtParaList[5].aucPara[ulCount],(VOS_UINT16)(gastAtParaList[5].usParaLen - ulCount),&ulHigh))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            if((ulLow > 65535) || (ulHigh > 65535) || (ulLow > ulHigh))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            else
            {
                stTftInfo.usHighDestPort = (VOS_UINT16)ulHigh;
                stTftInfo.usLowDestPort = (VOS_UINT16)ulLow;
            }
        }

        /* ����<source port range> */
        if(0 != gastAtParaList[6].usParaLen)
        {
            ulCount = AT_CountDigit(gastAtParaList[6].aucPara,gastAtParaList[6].usParaLen,'.',1);
            if((0 == ulCount) || (0 == gastAtParaList[6].aucPara[ulCount]))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stTftInfo.bitOpSrcPortRange = 1;

            if(AT_FAILURE == atAuc2ul(gastAtParaList[6].aucPara,(VOS_UINT16)(ulCount-1),&ulLow))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            if(AT_FAILURE == atAuc2ul(&gastAtParaList[6].aucPara[ulCount],(VOS_UINT16)(gastAtParaList[6].usParaLen - ulCount),&ulHigh))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            if((ulLow > 65535) || (ulHigh > 65535) || (ulLow > ulHigh))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            else
            {
                stTftInfo.usHighSourcePort = (VOS_UINT16)ulHigh;
                stTftInfo.usLowSourcePort = (VOS_UINT16)ulLow;
            }
        }

        /* ����<ipsec security parameter index (spi)> */
        if(0 != gastAtParaList[7].usParaLen)
        {
            stTftInfo.bitOpSpi = 1;
            /* ��Ҫ�����жϴ�С */
            if(gastAtParaList[7].usParaLen > 8) /*����FFFFFFFF */
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            if(AT_FAILURE == At_String2Hex(gastAtParaList[7].aucPara,gastAtParaList[7].usParaLen,&gastAtParaList[7].ulParaValue))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            stTftInfo.ulSecuParaIndex = gastAtParaList[7].ulParaValue;
        }

        /* ����<type of service (tos) (ipv4) and mask / traffic class (ipv6) and mask> */
        if(0 != gastAtParaList[8].usParaLen)
        {
            ulCount = AT_CountDigit(gastAtParaList[8].aucPara,gastAtParaList[8].usParaLen,'.',1);
            if((0 == ulCount) || (0 == gastAtParaList[8].aucPara[ulCount]))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stTftInfo.bitOpTosMask = 1;

            if(AT_FAILURE == atAuc2ul(gastAtParaList[8].aucPara,(VOS_UINT16)(ulCount-1),&ulLow))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            if(AT_FAILURE == atAuc2ul(&gastAtParaList[8].aucPara[ulCount],(VOS_UINT16)(gastAtParaList[8].usParaLen - ulCount),&ulHigh))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            if((ulLow > 255) || (ulHigh > 255))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
            else
            {
                stTftInfo.ucTypeOfServiceMask = (VOS_UINT8)ulHigh;
                stTftInfo.ucTypeOfService = (VOS_UINT8)ulLow;
            }
        }

        /* <flow label (ipv6)> */
        if(0 != gastAtParaList[9].usParaLen)
        {
            stTftInfo.bitOpFlowLable = 1;
            stTftInfo.ulFlowLable = gastAtParaList[9].ulParaValue;
        }

        /* <direction> */
        if(0 != gastAtParaList[10].usParaLen)
        {
            stTftInfo.bitOpDirection = 1;
            stTftInfo.ucDirection = (VOS_UINT8)gastAtParaList[10].ulParaValue;
        }
    }

    if ( VOS_OK != TAF_PS_SetTftInfo(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     &stTftInfo) )
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCgauthPara(TAF_UINT8 ucIndex)

{
    TAF_PDP_AUTH_EXT_STRU               stPdpAuthInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stPdpAuthInfo, 0x00, sizeof(TAF_PDP_AUTH_EXT_STRU));

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 4 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<cid> */
    stPdpAuthInfo.ucCid                 = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stPdpAuthInfo.ucDefined         = VOS_FALSE;
    }
    else
    {
        stPdpAuthInfo.ucDefined         = VOS_TRUE;

        /* ����<Auth> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            stPdpAuthInfo.bitOpAuth     = VOS_TRUE;
            stPdpAuthInfo.ucAuth        = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }

        /* ����<UserName> */
        if ( 0 != gastAtParaList[2].usParaLen )
        {
            /* ���<UserName>������ֱ�ӷ��ش��� */
            if ( gastAtParaList[2].usParaLen > TAF_MAX_PDP_AUTH_USERNAME_LEN )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stPdpAuthInfo.bitOpUserName = VOS_TRUE;
            PS_MEM_CPY((VOS_CHAR*)stPdpAuthInfo.aucUserName,
                       (VOS_CHAR*)gastAtParaList[2].aucPara,
                       gastAtParaList[2].usParaLen);
            stPdpAuthInfo.aucUserName[gastAtParaList[2].usParaLen] = 0;
        }

        /* ����<PassWord> */
        if ( 0 != gastAtParaList[3].usParaLen )
        {
            /* ���<PassWord>������ֱ�ӷ��ش��� */
            if ( gastAtParaList[3].usParaLen > TAF_MAX_PDP_AUTH_PASSCODE_LEN )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stPdpAuthInfo.bitOpPassword = VOS_TRUE;
            PS_MEM_CPY((VOS_CHAR*)stPdpAuthInfo.aucPassWord,
                       (VOS_CHAR*)gastAtParaList[3].aucPara,
                       gastAtParaList[3].usParaLen);
            stPdpAuthInfo.aucPassWord[gastAtParaList[3].usParaLen] = 0;
        }
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetPdpAuthInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0, &stPdpAuthInfo))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTH_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCgdnsPara(TAF_UINT8 ucIndex)
{
    TAF_PDP_DNS_EXT_STRU                stPdpDnsInfo;

    VOS_UINT8                           aucTempIpv4Addr[TAF_IPV4_ADDR_LEN];
    VOS_UINT32                          ulRslt;

    /* ��ʼ�� */
    PS_MEM_SET(&stPdpDnsInfo, 0x00, sizeof(TAF_PDP_DNS_EXT_STRU));

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 3 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<cid> */
    stPdpDnsInfo.ucCid                  = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stPdpDnsInfo.ucDefined          = VOS_FALSE;
    }
    else
    {
        stPdpDnsInfo.ucDefined          = VOS_TRUE;

        /* ����<PriDns> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            /* ���<PriDns>������ֱ�ӷ��ش��� */
            if ( gastAtParaList[1].usParaLen > (TAF_MAX_IPV4_ADDR_STR_LEN - 1) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }


            ulRslt = AT_Ipv4AddrAtoi((VOS_CHAR*)gastAtParaList[1].aucPara, &aucTempIpv4Addr[0]);

            if ( VOS_OK != ulRslt )
            {
               return AT_CME_INCORRECT_PARAMETERS;
            }


            stPdpDnsInfo.bitOpPrimDnsAddr = VOS_TRUE;
            PS_MEM_CPY(stPdpDnsInfo.aucPrimDnsAddr,
                       aucTempIpv4Addr,
                       TAF_IPV4_ADDR_LEN);
        }

        /* ����<SecDns> */
        if ( 0 != gastAtParaList[2].usParaLen )
        {
            /* ���<SecDns>������ֱ�ӷ��ش��� */
            if ( gastAtParaList[2].usParaLen > (TAF_MAX_IPV4_ADDR_STR_LEN - 1) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }


            /*�˴��洢�����ַ�����ʽ��DNS����ת�����������ʹ��*/
            ulRslt = AT_Ipv4AddrAtoi((VOS_CHAR*)gastAtParaList[2].aucPara, &aucTempIpv4Addr[0]);

            if ( VOS_OK != ulRslt )
            {
               return AT_CME_INCORRECT_PARAMETERS;
            }


            stPdpDnsInfo.bitOpSecDnsAddr = VOS_TRUE;
            PS_MEM_CPY(stPdpDnsInfo.aucSecDnsAddr,
                       aucTempIpv4Addr,
                       TAF_IPV4_ADDR_LEN);
        }
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetPdpDnsInfo(WUEPS_PID_AT,
                                        gastAtClientTab[ucIndex].usClientId,
                                        0, &stPdpDnsInfo) )
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_SetCgautoPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulAnsMode;

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<n> */
    ulAnsMode = gastAtParaList[0].ulParaValue;

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetAnsModeInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0,
                                         ulAnsMode) )
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/******************************************************************************
 ��������: atSetCgeqosPara
 ��������: +CGEQOS=[<cid> [,<QCI> [,<DL_GBR>, <UL_GBR> [,<DL_MBR>,<UL_MBR]]]]

 ����˵��:
   ulIndex [in] ...
                ...

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
******************************************************************************/
VOS_UINT32 atSetCgeqosPara(VOS_UINT8 ucIndex)
{
    TAF_EPS_QOS_EXT_STRU                stEpsQosInfo;

    PS_MEM_SET(&stEpsQosInfo, 0x00, sizeof(TAF_EPS_QOS_EXT_STRU));

    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( gucAtParaIndex > 6 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stEpsQosInfo.ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    if ( 0 != gastAtParaList[1].usParaLen )
    {
        stEpsQosInfo.bitOpQCI   = 1;
        stEpsQosInfo.ucQCI      = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    }

    if ( 0 != gastAtParaList[2].usParaLen )
    {
        stEpsQosInfo.bitOpDLGBR = 1;
        stEpsQosInfo.ulDLGBR    = gastAtParaList[2].ulParaValue;
    }

    if (0 != gastAtParaList[3].usParaLen )
    {
        stEpsQosInfo.bitOpULGBR = 1;
        stEpsQosInfo.ulULGBR    = gastAtParaList[3].ulParaValue;
    }

    if (0 != gastAtParaList[4].usParaLen )
    {
        stEpsQosInfo.bitOpDLMBR = 1;
        stEpsQosInfo.ulDLMBR= gastAtParaList[4].ulParaValue;
    }

    if (0 != gastAtParaList[5].usParaLen )
    {
        stEpsQosInfo.bitOpULMBR = 1;
        stEpsQosInfo.ulULMBR    = gastAtParaList[5].ulParaValue;
    }

    if ( VOS_OK != TAF_PS_SetEpsQosInfo(WUEPS_PID_AT,
                                        gastAtClientTab[ucIndex].usClientId,
                                        0,
                                        &stEpsQosInfo) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQOS_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/******************************************************************************
 ��������: atQryCgeqosPara
 ��������: +CGEQOS

 ����˵��:
   ulIndex [in] ...
                ...

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
******************************************************************************/
VOS_UINT32 atQryCgeqosPara(VOS_UINT8 ucIndex)
{
    if( VOS_OK != TAF_PS_GetEpsQosInfo(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId,0))
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQOS_READ;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


/******************************************************************************
 ��������: atSetCgeqosrdpPara
 ��������: +CGEQOSRDP=[<cid>]

 ����˵��:
   ulIndex [in] ...
                ...

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
******************************************************************************/
VOS_UINT32 atSetCgeqosrdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                   ucCid = 0;

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucCid = 0xff;
    }

    if ( VOS_OK != TAF_PS_GetDynamicEpsQosInfo(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0,
                                               ucCid) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQOSRDP_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/******************************************************************************
 ��������: atSetCgcontrdpPara
 ��������: +CGCONTRDP=[<p_cid>]

 ����˵��:
   ulIndex [in] ...
                ...

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
******************************************************************************/
VOS_UINT32 atSetCgcontrdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8   ucCid = 0;

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucCid = 0xff;
    }

    if( VOS_OK != TAF_PS_GetDynamicPrimPdpContextInfo(WUEPS_PID_AT,
                                                      gastAtClientTab[ucIndex].usClientId,
                                                      0, ucCid) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCONTRDP_SET;

    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */

}

/******************************************************************************
 ��������: atSetCgscontrdpPara
 ��������: +CGSCONTRDP=[<p_cid>]

 ����˵��:
   ulIndex [in] ...
                ...

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
******************************************************************************/
VOS_UINT32 atSetCgscontrdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8   ucCid = 0;

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucCid = 0xff;
    }

    if( VOS_OK != TAF_PS_GetDynamicSecPdpContextInfo(WUEPS_PID_AT,
                                                     gastAtClientTab[ucIndex].usClientId,
                                                     0,
                                                     ucCid) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGSCONTRDP_SET;

    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */

}

/******************************************************************************
 ��������: atSetCgtftrdpPara
 ��������: +CGTFTRDP=[<cid>]

 ����˵��:
   ulIndex [in] ...
                ...

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
******************************************************************************/
VOS_UINT32 atSetCgtftrdpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8   ucCid = 0;

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucCid = (VOS_UINT8)(gastAtParaList[0].ulParaValue);
    }
    else
    {
        ucCid = 0xff;
    }

    if( VOS_OK != TAF_PS_GetDynamicTftInfo(WUEPS_PID_AT,
                                           gastAtClientTab[ucIndex].usClientId,
                                           0,
                                           ucCid) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFTRDP_SET;

    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
}


VOS_UINT32 At_SetCsndPara(VOS_UINT8 ucIndex)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT8                           ucRabId;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSrcAddr;
    VOS_UINT32                          ulDestAddr;
    VOS_UINT16                          usDestPort;
    VOS_UINT16                          usSrcPort;
    VOS_UINT16                          usTotalLen;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulIpAddr;

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* RABID��Ч�Լ��[5,15] */
    ucRabId     = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    if (!AT_PS_IS_RABID_VALID(ucRabId))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����UDP���ĳ��� */
    usLength    = (VOS_UINT16)gastAtParaList[1].ulParaValue;
    usLength    = (usLength > 1400) ? (1400) : usLength;
    usTotalLen  = usLength + AT_IP_HDR_LEN + AT_UDP_HDR_LEN;

    /* �������㿽���ڴ� */
    pstImmZc    = IMM_ZcStaticAlloc(usTotalLen);
    if (VOS_NULL_PTR == pstImmZc)
    {
        AT_ERR_LOG("At_SetCsndPara: IMM_ZcStaticAlloc fail!");
        return AT_ERROR;
    }

    ulIpAddr    = AT_PS_GetIpAddrByRabId(ucIndex, ucRabId);
    ulSrcAddr   = ulIpAddr;
    ulDestAddr  = ulIpAddr + 1;
    usDestPort  = 9600;
    usSrcPort   = 9700;

    pucData     = (VOS_UINT8 *)IMM_ZcPut(pstImmZc, usTotalLen);
    if (VOS_NULL_PTR == pucData)
    {
        IMM_ZcFree(pstImmZc);

        AT_ERR_LOG("At_SetCsndPara: IMM_ZcPut fail!");

        return AT_ERROR;
    }

    /* ����UDPͷ */
    if (VOS_OK != AT_BuildUdpHdr((AT_UDP_PACKET_FORMAT_STRU *)pucData,
                                 usLength,
                                 ulSrcAddr,
                                 ulDestAddr,
                                 usSrcPort,
                                 usDestPort))
    {
        IMM_ZcFree(pstImmZc);

        AT_ERR_LOG("At_SetCsndPara: IMM_ZcPut fail!");

        return AT_ERROR;
    }

    enModemId       = MODEM_ID_0;
    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        IMM_ZcFree(pstImmZc);
        AT_ERR_LOG("At_SetCsndPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (MODEM_ID_0 != enModemId)
    {
        ucRabId    |= AT_PS_RABID_MODEM_1_MASK;
    }

    /* �����������ݰ� */
    if (VOS_OK != ADS_UL_SendPacket(pstImmZc, ucRabId))
    {
        IMM_ZcFree(pstImmZc);

        return AT_ERROR;
    }

    return AT_OK;
}
TAF_UINT32 At_SetCgdataPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulCidIndex;
    TAF_CID_LIST_STATE_STRU             stCidListStateInfo;

    /* ��ʼ�� */
    ulCidIndex  = 0;
    PS_MEM_SET(&stCidListStateInfo, 0x00, sizeof(TAF_CID_LIST_STATE_STRU));

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������, Ŀǰ���֧��һ��CID */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* <L2P>������ */

    /* �������� */
    stCidListStateInfo.ucState  = 1;

    if (0 == gastAtParaList[1].usParaLen)
    {
        ulCidIndex = 1;
    }
    else
    {
        ulCidIndex = gastAtParaList[1].ulParaValue;
    }

    /* ��CID��Ϊ�±�, ��Ƕ�Ӧ��CID */
    stCidListStateInfo.aucCid[ulCidIndex] = 1;


    /* ִ��������� */
    if (VOS_OK != TAF_PS_SetPdpContextState(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0,
                                            &stCidListStateInfo))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDATA_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
 Prototype      : At_SetCgattPara
 Description    : +CGATT=[<state>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCgattPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(0 == gastAtParaList[0].ulParaValue)
    {
        /* ִ��Detach���� */
        if(AT_SUCCESS == Taf_PhoneDetach(gastAtClientTab[ucIndex].usClientId, 0,TAF_PH_PS_OPERATE))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGATT_DETAACH_SET;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        /* ִ��Attach���� */
        if(AT_SUCCESS == Taf_PhoneAttach(gastAtClientTab[ucIndex].usClientId, 0,TAF_PH_PS_OPERATE))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGATT_ATTACH_SET;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }
    }
}

/*****************************************************************************
 Prototype      : At_SetCgcattPara
 Description    : +CGCATT=<state>,<mode>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_SetCgcattPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(0 == gastAtParaList[0].ulParaValue)
    {
        /* ִ��Detach���� */
        if(AT_SUCCESS == Taf_PhoneDetach(gastAtClientTab[ucIndex].usClientId, 0,(TAF_UINT8)gastAtParaList[1].ulParaValue))
        {
            /* ���õ�ǰ�������� */
            switch(gastAtParaList[1].ulParaValue)
            {
            case TAF_PH_PS_OPERATE:
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCATT_PS_DETAACH_SET;
                break;

            case TAF_PH_CS_OPERATE:
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCATT_CS_DETAACH_SET;
                break;

            default:
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCATT_PS_CS_DETAACH_SET;
                break;
            }
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }
    }
    else
    {
        /* ִ��Attach���� */
        if(AT_SUCCESS == Taf_PhoneAttach(gastAtClientTab[ucIndex].usClientId, 0,(TAF_UINT8)gastAtParaList[1].ulParaValue))
        {
            /* ���õ�ǰ�������� */
            switch(gastAtParaList[1].ulParaValue)
            {
            case TAF_PH_PS_OPERATE:
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCATT_PS_ATTACH_SET;
                break;

            case TAF_PH_CS_OPERATE:
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCATT_CS_ATTACH_SET;
                break;

            default:
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGCATT_PS_CS_ATTACH_SET;
                break;
            }
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }
    }
}
/*****************************************************************************
 �� �� ��  : At_SetCopsActPara
 ��������  : ����COPS�����н��뼼������
 �������  : usParaLen:��������
             ulParaValue:����ֵ
 �������  : penPhRat:���뼼��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��10��18��
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID At_SetCopsActPara(
    TAF_PH_RAT_TYPE_ENUM_UINT8         *penPhRat,
    VOS_UINT16                          usParaLen,
    VOS_UINT32                          ulParaValue
)
{
    /* �����������Ϊ0��ʹ����Чֵ */
    if (0 == usParaLen)
    {
        *penPhRat = TAF_PH_RAT_BUTT;

        return;
    }

    /* �����û�����Ĳ���ֵ,ת��ΪAT��MMA�Ľӿڶ���Ľ��뼼������ */
    if (AT_COPS_RAT_GSM == ulParaValue)
    {
        *penPhRat = TAF_PH_RAT_GSM;
    }
    else if (AT_COPS_RAT_WCDMA == ulParaValue)
    {
        *penPhRat = TAF_PH_RAT_WCDMA;
    }
#if(FEATURE_ON == FEATURE_LTE)
    else if (AT_COPS_RAT_LTE == ulParaValue)
    {
        *penPhRat = TAF_PH_RAT_LTE;
    }
#endif
    else
    {
        *penPhRat = TAF_PH_RAT_BUTT;
    }

    return;
}

VOS_UINT32 At_SetCopsPara(TAF_UINT8 ucIndex)
{
    TAF_PH_RAT_TYPE_ENUM_UINT8          enPhRat;
    VOS_UINT32                          ulRslt;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 4)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        gastAtParaList[0].ulParaValue = 0;
    }

    /* ����<mode> A32D07158
     * only in case of mode = 3(change the format), should the new format be saved.
     */
    /* ����<format> */
    if(0 != gastAtParaList[1].usParaLen)
    {
        /* ��ÿ�ν�������ʱ�������ǳɹ�����ʧ�ܣ�PLMNҪ�����û�ָ�������µĸ�ʽ��ʾҪ�������ʾ */
        pstNetCtx->ucCopsFormatType = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    }

    /* ����<AcT> */
    At_SetCopsActPara(&enPhRat, gastAtParaList[3].usParaLen, gastAtParaList[3].ulParaValue);

    /* ��ÿ�ν����ֶ�����ʱ�������ǳɹ�����ʧ�ܣ�PLMNҪ�����û�ָ�������µĸ�ʽ��ʾҪ�������ʾ */
    switch(gastAtParaList[0].ulParaValue)
    {
    case 0: /* automatic */
        if(AT_SUCCESS == Taf_PhonePlmnResel(gastAtClientTab[ucIndex].usClientId, 0,TAF_PLMN_RESELETION_AUTO))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_SET_AUTOMATIC;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }

    case 1: /* manual */


        ulRslt = TAF_PhonePlmnUserSel(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   gastAtParaList[2].usParaLen,
                                   gastAtParaList[2].aucPara,
                                   pstNetCtx->ucCopsFormatType,
                                   enPhRat);
        if (AT_OK == ulRslt)
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_SET_MANUAL;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }

    case 3: /* set only <format> */
        return AT_OK;
    default: /* manual/automatic */
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCgclassPara
 Description    : +CGCLASS=[<class>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2012��03��03��
   �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��NAS_FEATURE_AT_COMMAND_CGCLASS��
*****************************************************************************/
TAF_UINT32 At_SetCgclassPara(TAF_UINT8 ucIndex)
{
    TAF_PH_MS_CLASS_TYPE MsClass;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<class> */
    switch(gastAtParaList[0].ulParaValue)
    {
    case 0:
        MsClass = TAF_PH_MS_CLASS_A;
        break;

    case 1:
        MsClass = TAF_PH_MS_CLASS_B;
        break;

    case 2:
        MsClass = TAF_PH_MS_CLASS_CG;
        break;

    default:
        MsClass = TAF_PH_MS_CLASS_CC;
        break;
    }

    if (TAF_PH_MS_CLASS_A == MsClass)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }

}

TAF_UINT32 At_SetCfunPara(TAF_UINT8 ucIndex)
{
    TAF_PH_OP_MODE_STRU    PhModeSet;


    PS_MEM_SET(&PhModeSet, 0x00, sizeof(PhModeSet));

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    if ((2 == gucAtParaIndex) && (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    /* ����<fun> */
    if ( TAF_PH_MODE_NUM_MAX <= gastAtParaList[0].ulParaValue )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PhModeSet.CmdType = TAF_PH_CMD_SET;
    PhModeSet.PhMode = (TAF_UINT8)gastAtParaList[0].ulParaValue;

/* ���TAF�Ļط����� */
#if (VOS_WIN32 == VOS_OS_VER)
#ifndef __PS_WIN32_RECUR__
    /* NAS_MMA_SndNVData(); */

    NAS_MSG_SndOutsideContextData_Part1();
    NAS_MSG_SndOutsideContextData_Part2();
    NAS_MSG_SndOutsideContextData_Part3();
#endif
#endif
/* ���TAF�Ļط����� */

    if(AT_SUCCESS == Taf_DefPhMode(gastAtClientTab[ucIndex].usClientId, 0, PhModeSet))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFUN_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetCgmiPara
 Description    : +CGMI
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCgmiPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_MFR_ID_PARA,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGMI_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetCgmmPara
 Description    : +CGMM/+GMM
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCgmmPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_MODEL_ID_PARA,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGMM_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetCgmrPara
 Description    : +CGMR
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCgmrPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_REVISION_ID_PARA,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGMR_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_SetCgsnPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* AT����״̬��� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϣ ID_AT_MTA_CGSN_QRY_REQ �� MTA ������ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_CGSN_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGSN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_SetCimiPara(TAF_UINT8 ucIndex)
{
    TAF_AT_NVIM_CIMI_PORT_CFG_STRU      stCimiPortCfg;

    stCimiPortCfg.ulCimiPortCfg = 0;

    /* ����NV�����ò������������·���ͨ�������ж� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CIMI_PORT_CFG,
                         &stCimiPortCfg,
                         sizeof(stCimiPortCfg)))
    {
        stCimiPortCfg.ulCimiPortCfg  = 0;
    }

    /* ��ͨ����Ӧ��Bitλ��Ϊ0����ֱ�ӷ���AT_ERROR */
    if (0 != (stCimiPortCfg.ulCimiPortCfg & (1 << ucIndex)))
    {
        return AT_ERROR;
    }

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_IMSI_ID_PARA,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIMI_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetClipPara
 Description    : +CSQ
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCsqPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_RSSI_VALUE_PARA,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSQ_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 At_SetCbcPara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_SUPPORT == DRV_GET_BATTERY_SUPPORT() )
    {

        /* E5 ֱ�ӵ��������Ľӿ�ʵ�� */
        VOS_UINT8                           ucBcs;
        VOS_UINT8                           ucBcl;

        /* ������� */
        if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if (VOS_OK != DRV_CHG_GET_CBC_STATE(&ucBcs, &ucBcl))
        {
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        ucBcs, ucBcl);
        return AT_OK;

    }
    else
    {
        /* ������� */
        if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ִ��������� */
        if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_BATTERY_POWER_PARA,TAF_NULL_PTR))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBC_SET;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }

    }

}


VOS_UINT32 At_SetCpdwPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ulRst;

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ͨ����C CPU��TAF_MSG_MMA_MT_POWER_DOWN��Ϣ֪ͨMT�µ� */
    ulRst = AT_FillAndSndAppReqMsg( gastAtClientTab[ucIndex].usClientId,
                                  At_GetOpId(),
                                  TAF_MSG_MMA_MT_POWER_DOWN,
                                  VOS_NULL_PTR,
                                  0,
                                  I0_WUEPS_PID_MMA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_MT_POWER_DOWN;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}

TAF_UINT32 At_SetSnPara(TAF_UINT8 ucIndex)
{
    TAF_PH_SERIAL_NUM_STRU stSerialNum;
    TAF_UINT16            usLength = 0;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType)
    {
        return At_WriteSnPara(ucIndex);
    }
    /* ��NV�ж�ȡ Serial Num,�ϱ���ʾ������ */

    PS_MEM_SET(&stSerialNum, 0, sizeof(TAF_PH_SERIAL_NUM_STRU));

    usLength = TAF_SERIAL_NUM_NV_LEN;
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Serial_Num, stSerialNum.aucSerialNum, usLength))
    {
        AT_WARN_LOG("At_SetSnPara:WARNING:NVIM Read en_NV_Item_Serial_Num falied!");
        return AT_ERROR;
    }
    else
    {
        PS_MEM_SET((stSerialNum.aucSerialNum+TAF_SERIAL_NUM_LEN), 0, 4*sizeof(stSerialNum.aucSerialNum[0]));
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s:",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",stSerialNum.aucSerialNum);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_WriteSnPara(VOS_UINT8 ucIndex)
{
    TAF_PH_SERIAL_NUM_STRU              stSerialNum;

    /* ����������Ϊ1 */
    if (gucAtParaIndex != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ����������Ȳ�����16��ֱ�ӷ��ش��� */
    if (TAF_SERIAL_NUM_LEN != gastAtParaList[0].usParaLen)
    {
        return AT_SN_LENGTH_ERROR;
    }

    /* ��鵱ǰ�����Ƿ�Ϊ������ĸ�ַ���,������ֱ�ӷ��ش��� */
    if (AT_FAILURE == At_CheckNumCharString(gastAtParaList[0].aucPara,
                                            gastAtParaList[0].usParaLen))
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* �������õ�16λSN�������ṹ�����stSerialNum.aucSerialNum�� */
    PS_MEM_CPY(stSerialNum.aucSerialNum, gastAtParaList[0].aucPara, TAF_SERIAL_NUM_LEN);

    /* ��stSerialNum.aucSerialNum����λ���Ϊ0xFF */
    PS_MEM_SET((stSerialNum.aucSerialNum + TAF_SERIAL_NUM_LEN), 0xFF, (TAF_SERIAL_NUM_NV_LEN - TAF_SERIAL_NUM_LEN));

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Serial_Num,
                          stSerialNum.aucSerialNum,
                          TAF_SERIAL_NUM_NV_LEN))
    {
        AT_WARN_LOG("At_WriteSnPara:WARNING:NVIM Write en_NV_Item_Serial_Num failed!");
        return AT_DEVICE_OTHER_ERROR;
    }

    return AT_OK;
}
VOS_UINT32 At_SetHwVerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������ϢDRV_AGENT_HARDWARE_QRY��AT AGENT����������Ϣ�޲����ṹ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_HARDWARE_QRY,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_HARDWARE_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 At_SetFHVerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������ϢDRV_AGENT_FULL_HARDWARE_QRY��AT AGENT����������Ϣ�޲����ṹ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   DRV_AGENT_FULL_HARDWARE_QRY,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_FULL_HARDWARE_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;


}

/*****************************************************************************
 �� �� ��  : At_SetPfverPara
 ��������  : ^PFVER,����������ƽ̨�汾��
 �������  : VOS_UINT8 ucIndex  �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32         ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��18��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_SetPfverPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ����Ϣ��C�˻�ȡ���״̬�͵�ص��� */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_PFVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_SetPfverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PFVER_READ;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 At_SetCLACPara(VOS_UINT8 ucIndex)
{
    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    gstAtSendData.usBufLen = 0;

    /* �������֧�ֵĿ���ʾ��AT���� */
    AT_ClacCmdProc();

    return AT_OK;
}


TAF_UINT32 At_SetCpbsPara(TAF_UINT8 ucIndex)
{
    SI_PB_STORATE_TYPE  Storage = SI_PB_STORAGE_UNSPECIFIED;
    TAF_UINT32          i;

    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* VOS_StrCmp��Ҫ��ָ��ǿռ�飬�м�! */
    if(TAF_NULL_PTR == (TAF_CHAR*)gastAtStringTab[AT_STRING_SM].pucText)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(TAF_NULL_PTR == (TAF_CHAR*)gastAtStringTab[AT_STRING_ON].pucText)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(TAF_NULL_PTR == (TAF_CHAR*)gastAtStringTab[AT_STRING_EN].pucText)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(TAF_NULL_PTR == (TAF_CHAR*)gastAtStringTab[AT_STRING_FD].pucText)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(TAF_NULL_PTR == (TAF_CHAR*)gastAtStringTab[AT_STRING_BD].pucText)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    for(i = 0; i < gastAtParaList[0].usParaLen ; i++)
    {
        gastAtParaList[0].aucPara[i] = At_UpChar(gastAtParaList[0].aucPara[i]);
    }

    if(0 == VOS_StrCmp((TAF_CHAR*)gastAtStringTab[AT_STRING_ON].pucText,(TAF_CHAR*)gastAtParaList[0].aucPara))
    {
        Storage = SI_PB_STORAGE_ON;
    }
    else if(0 == VOS_StrCmp((TAF_CHAR*)gastAtStringTab[AT_STRING_SM].pucText,(TAF_CHAR*)gastAtParaList[0].aucPara))
    {
        Storage = SI_PB_STORAGE_SM;
    }
    else if(0 == VOS_StrCmp((TAF_CHAR*)gastAtStringTab[AT_STRING_FD].pucText,(TAF_CHAR*)gastAtParaList[0].aucPara))
    {
        Storage = SI_PB_STORAGE_FD;
    }
    else if(0 == VOS_StrCmp((TAF_CHAR*)gastAtStringTab[AT_STRING_EN].pucText,(TAF_CHAR*)gastAtParaList[0].aucPara))
    {
        Storage = SI_PB_STORAGE_EC;
    }
    else if(0 == VOS_StrCmp((TAF_CHAR*)gastAtStringTab[AT_STRING_BD].pucText,(TAF_CHAR*)gastAtParaList[0].aucPara))
    {
        Storage = SI_PB_STORAGE_BD;
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    /* ִ��������� */
    if(AT_SUCCESS == SI_PB_Set(gastAtClientTab[ucIndex].usClientId, 0, Storage))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBS_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCpbr2Para
 Description    : +CPBR=<index1>[,<index2>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2007��8��22��
    �޸�����   : ���ⵥA32D11418
  3.��    ��   : 2008��11��03��
    �޸�����   : PB��������
*****************************************************************************/
TAF_UINT32 At_SetCpbr2Para(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        gastAtParaList[1].ulParaValue = gastAtParaList[0].ulParaValue;
    }

    if (AT_SUCCESS == SI_PB_Read(gastAtClientTab[ucIndex].usClientId,
                                0, SI_PB_STORAGE_UNSPECIFIED,
                                (TAF_UINT16)gastAtParaList[0].ulParaValue,
                                (TAF_UINT16)gastAtParaList[1].ulParaValue))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBR2_SET;

        gulPBPrintTag = TAF_FALSE;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCpbrPara
 Description    : +CPBR=<index1>[,<index2>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2007��8��22��
    �޸�����   : ���ⵥA32D11418
  3.��    ��   : 2008��11��03��
    �޸�����   : PB��������
*****************************************************************************/
TAF_UINT32 At_SetCpbrPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        gastAtParaList[1].ulParaValue = gastAtParaList[0].ulParaValue;
    }

    if (AT_SUCCESS == SI_PB_Read(gastAtClientTab[ucIndex].usClientId,
                                0, SI_PB_STORAGE_UNSPECIFIED,
                                (TAF_UINT16)gastAtParaList[0].ulParaValue,
                                (TAF_UINT16)gastAtParaList[1].ulParaValue))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBR_SET;

        gulPBPrintTag = TAF_FALSE;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_PbDeleteProc(TAF_UINT8 ucIndex)
{
    /* ���AT+CPBW=,��AT+CPBW=0����� */
    if(0 == gastAtParaList[0].usParaLen || 0 == gastAtParaList[0].ulParaValue)
    {
        return AT_CME_INVALID_INDEX;
    }

    if(AT_SUCCESS == SI_PB_Delete(gastAtClientTab[ucIndex].usClientId,
                                  0, SI_PB_STORAGE_UNSPECIFIED,
                                  (TAF_UINT16)gastAtParaList[0].ulParaValue))

    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    AT_ERR_LOG("At_PbDeleteProc error: delete pb record failed");

    return AT_ERROR;
}
TAF_UINT32 At_SetCpbwPara(TAF_UINT8 ucIndex)
{
    SI_PB_RECORD_STRU   stRecords;
    TAF_UINT8           *pucNumber;
    TAF_UINT16          usLen;
    TAF_UINT16          usAlphaTagLength;
    TAF_UINT32          ulResult;
    TAF_UINT32          ulResultTemp;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)    /* ������� */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex > 5)/* �������� */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ֻ��һ������ʱΪɾ������ */
    if (1 == gucAtParaIndex)
    {
        ulResult = At_PbDeleteProc(ucIndex);

        return ulResult;
    }

    if((0 == gastAtParaList[1].usParaLen)&&(0 == gastAtParaList[3].usParaLen))
    {
        return AT_ERROR;
    }

    /* ȷ�ϱ������ͣ�UNICODE����ASCII�� */
    PS_MEM_SET(&stRecords, 0x00, sizeof(stRecords));/* ��ʼ�� */

    if((AT_CSCS_UCS2_CODE == gastAtParaList[4].ulParaValue) && (5 == gucAtParaIndex))
    {
        stRecords.AlphaTagType = AT_CSCS_UCS2_CODE;
    }
    else if((AT_CSCS_IRA_CODE == gastAtParaList[4].ulParaValue) && (5 == gucAtParaIndex))
    {
        stRecords.AlphaTagType = AT_CSCS_IRA_CODE;
    }
    else if(4 == gucAtParaIndex)
    {
        stRecords.AlphaTagType = AT_CSCS_IRA_CODE;
    }
    else
    {
        stRecords.AlphaTagType = AT_CSCS_IRA_CODE;
    }

    if(0 != gastAtParaList[0].usParaLen)/* ����<index> */
    {
        stRecords.Index = (TAF_UINT16)gastAtParaList[0].ulParaValue;
    }

    if(0 != gastAtParaList[1].usParaLen)/* ����<number> */
    {
        if('+' == gastAtParaList[1].aucPara[0])
        {
            pucNumber = gastAtParaList[1].aucPara   + 1;
            usLen     = gastAtParaList[1].usParaLen - 1;
        }
        else
        {
            pucNumber = gastAtParaList[1].aucPara;
            usLen     = gastAtParaList[1].usParaLen;
        }

        if(AT_FAILURE == At_CheckPBString(pucNumber,&usLen))
        {
            return AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING;
        }

        if(SI_PB_PHONENUM_MAX_LEN < usLen)
        {
            return AT_CME_TEXT_STRING_TOO_LONG;
        }

        PS_MEM_CPY(stRecords.Number, pucNumber, usLen);

        stRecords.NumberLength = (TAF_UINT8)usLen;
    }

    if(0 != gastAtParaList[2].usParaLen)/* ����<type> */
    {
        /* �������ʹ��޸� */
        stRecords.NumberType = (PB_NUMBER_TYPE_INTERNATIONAL == At_GetCodeType(gastAtParaList[1].aucPara[0]))
                              ? PB_NUMBER_TYPE_INTERNATIONAL : (TAF_UINT8)gastAtParaList[2].ulParaValue;
    }
    else
    {
        stRecords.NumberType = (TAF_UINT8)At_GetCodeType(gastAtParaList[1].aucPara[0]);
    }

    if(stRecords.NumberType < 128)
    {
        return AT_CME_INVALID_INDEX;
    }

    if(0 != gastAtParaList[3].usParaLen) /* ����<text> */
    {
        /* ��������AT�����Ѿ�ָʾ��UNICODE����Ҫ���б���ת����ASCII�� */
        usAlphaTagLength = gastAtParaList[3].usParaLen;


        if(AT_CSCS_UCS2_CODE == stRecords.AlphaTagType)
        {
            /* ��ASCIIλ��������UNICODE��ż���� */
            if ((usAlphaTagLength % 2) != 0)
            {
                return AT_ERROR;
            }

            if(AT_FAILURE == At_UnicodePrint2Unicode(gastAtParaList[3].aucPara,&usAlphaTagLength))
            {
                return AT_ERROR;
            }

            if (AT_FAILURE == At_CheckNameUCS2Code(gastAtParaList[3].aucPara, &usAlphaTagLength))
            {
                return AT_ERROR;
            }

            stRecords.AlphaTagType = gastAtParaList[3].aucPara[0];
        }

        /* ���յõ��������ֶεĳ��Ȳ��ܳ���TAF_PB_RECORD_STRU
           �ṹ�е���󳤶ȣ�����ᵼ�¶�ջ��� */
        if(usAlphaTagLength > SI_PB_ALPHATAG_MAX_LEN)
        {
            usAlphaTagLength = SI_PB_ALPHATAG_MAX_LEN;
        }


        PS_MEM_CPY(stRecords.AlphaTag, gastAtParaList[3].aucPara, usAlphaTagLength);

        stRecords.ucAlphaTagLength = (TAF_UINT8)usAlphaTagLength;
    }

    if(0 == gastAtParaList[0].usParaLen) /* ���� */
    {
        if( AT_SUCCESS == SI_PB_Add(gastAtClientTab[ucIndex].usClientId,
                                                0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }

        return AT_ERROR;
    }

    ulResult      = SI_PB_GetSPBFlag();
    ulResultTemp  = SI_PB_GetStorateType();

    if((1 == ulResult)&&(SI_PB_STORAGE_SM == ulResultTemp))
    {
        if ( AT_SUCCESS == SI_PB_SModify(gastAtClientTab[ucIndex].usClientId,
                                            0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
    }


    if (AT_SUCCESS == SI_PB_Modify(gastAtClientTab[ucIndex].usClientId,
                                   0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_CME_INCORRECT_PARAMETERS;

}
TAF_VOID At_PbIraToUnicode(TAF_UINT8  *pucSrc,
                           TAF_UINT16 usSrcLen,
                           TAF_UINT8  *pucDst,
                           TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUCS2;

    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        /* ��IRA��UNICODEת����� ��IRA�ַ�ת��Ϊunicode���� */
        usUCS2 = g_astIraToUnicode[pucSrc[usIndex]].usUnicode;
        *pucDst = (TAF_UINT8)(usUCS2 >> 8);
        pucDst++;
        *pucDst = (TAF_UINT8)usUCS2;
        pucDst++;
    }

    /* ת���󳤶�Ϊԭ����2�� */
    *pusDstLen = (TAF_UINT16)(usSrcLen << 1);

    return;
}


TAF_UINT32 At_OneUnicodeToGsm(TAF_UINT16 usSrc, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;

    /* ������������ΪA0A1ʱ����SIM������Ϊ1B40����ʱ�ϱ�Ϊ007C*/
    if (0x00A0 == usSrc)
    {
        AT_LOG1("At_OneUnicodeToGsm no found one unicode[0x%x] to gsm",usSrc);

        return AT_FAILURE;
    }

    /* ����GSM �� UNICODE������ */
    for(usIndex = 0; usIndex < AT_PB_GSM_MAX_NUM; usIndex++)
    {
        if(usSrc == g_astGsmToUnicode[usIndex].usUnicode)
        {
            *pucDst = g_astGsmToUnicode[usIndex].ucOctet;

            *pusDstLen = 1;

            return AT_SUCCESS;
        }
    }

    /* ����GSM �� UNICODE��չ�� */
    for(usIndex = 0; usIndex < AT_PB_GSM7EXT_MAX_NUM; usIndex++)
    {
        if(usSrc == g_astGsm7extToUnicode[usIndex].usUnicode)
        {
            *pucDst++ = AT_PB_GSM7EXT_SYMBOL;
            *pucDst = g_astGsm7extToUnicode[usIndex].ucOctet;

            *pusDstLen = 2;

            return AT_SUCCESS;
        }
    }

    /* δ���ҵ�ʱ����ʧ�� */
    *pusDstLen = 0;

    AT_LOG1("At_OneUnicodeToGsm no found one unicode[0x%x] to gsm",usSrc);

    return AT_FAILURE;
}


TAF_UINT32 At_UnicodeTransferToGsmCalcLength(TAF_UINT8  *pucSrc,
                                             TAF_UINT16 usSrcLen,
                                             TAF_UINT16 *pusDstLen)
{
     TAF_UINT16     usIndex;
     TAF_UINT16     usUnicodeChar;
     TAF_UINT8      aucGsmData[2];
     TAF_UINT16     usGsmDataLen;

     for (usIndex = 0; usIndex < (usSrcLen >> 1); usIndex++)
     {
        usUnicodeChar = (*pucSrc << 8) | (*(pucSrc + 1));

        /* �ж�UNICODE�Ƿ����ת��ΪGSM7BIT */
        if (AT_SUCCESS != At_OneUnicodeToGsm(usUnicodeChar, aucGsmData, &usGsmDataLen))
        {
            AT_ERR_LOG("At_UnicodeTransferToGsmCalcLength error");

            return AT_FAILURE;
        }

        pucSrc     += 2;

        *pusDstLen += usGsmDataLen;
     }

     return AT_SUCCESS;
}
TAF_VOID At_PbUnicodeParse(TAF_UINT8  *pucSrc,
                           TAF_UINT16 usSrcLen,
                           TAF_UINT32 *pulAlphaTagType,
                           TAF_UINT16 *pusDstLen,
                           TAF_UINT16 *pusCodeBase)
{
    TAF_UINT16      usGsmCodeLen = 0;
    TAF_UINT16      us81CodeLen = 0;
    TAF_UINT16      us82CodeLen = 0;
    TAF_UINT16      us81Base;
    TAF_UINT16      us82Base;
    TAF_UINT16      usMinCodeLen;
    TAF_UINT32      ulAlphaTagType;
    TAF_UINT16      usCodeBase;

    /* �ȳ���ת��GSMģʽ,�����ת���ɹ����򷵻� */
    if (AT_SUCCESS == At_UnicodeTransferToGsmCalcLength(pucSrc, usSrcLen, &usGsmCodeLen))
    {
        *pulAlphaTagType = SI_PB_ALPHATAG_TYPE_GSM;
        *pusDstLen       = usGsmCodeLen;
        *pusCodeBase     = 0;

        return;
    }

    /***************************************************************************
                            Ĭ����Ϊ80����
    ***************************************************************************/
    usMinCodeLen   = usSrcLen + 1;
    ulAlphaTagType = SI_PB_ALPHATAG_TYPE_UCS2_80;
    usCodeBase     = 0;

    /* ����81���볤��,ѡ����С���볤�ȼ���Ӧ�ı��뷽ʽ */
    if (AT_SUCCESS == At_UnicodeTransferTo81CalcLength(pucSrc, usSrcLen, &us81Base, &us81CodeLen))
    {
        if (us81CodeLen <= usMinCodeLen)
        {
            usMinCodeLen   = us81CodeLen;
            ulAlphaTagType = SI_PB_ALPHATAG_TYPE_UCS2_81;
            usCodeBase     = us81Base;
        }
    }

    /* ����82���볤��,ѡ����С���볤�ȼ���Ӧ�ı��뷽ʽ */
    if (AT_SUCCESS == At_UnicodeTransferTo82CalcLength(pucSrc, usSrcLen, &us82Base, &us82CodeLen))
    {
        if (us82CodeLen <= usMinCodeLen)
        {
            usMinCodeLen   = us82CodeLen;
            ulAlphaTagType = SI_PB_ALPHATAG_TYPE_UCS2_82;
            usCodeBase     = us82Base;
        }
    }

    *pusDstLen          = usMinCodeLen;
    *pusCodeBase        = usCodeBase;
    *pulAlphaTagType    = ulAlphaTagType;

    return;
}


TAF_UINT32 At_UnicodeTransferToGsm(TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen, TAF_UINT8 *pucDst)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicodeChar;
    TAF_UINT16      usGsmDataLen = 0;

    for (usIndex = 0; usIndex < (usSrcLen >> 1); usIndex++)
    {
        usUnicodeChar = (*pucSrc << 8)|(*(pucSrc + 1));

        /* ����ַ�����ת�� */
        if (AT_SUCCESS != At_OneUnicodeToGsm(usUnicodeChar, pucDst, &usGsmDataLen))
        {
            AT_ERR_LOG("At_UnicodeTransferToGsm error");

            return AT_FAILURE;
        }

        pucDst += usGsmDataLen;
        pucSrc += 2;
    }

    return AT_SUCCESS;
}
TAF_VOID At_UnicodeTransferTo80(TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen, TAF_UINT8 *pucDst)
{
    pucDst[0] = SI_PB_ALPHATAG_TYPE_UCS2_80;

    VOS_MemCpy(&pucDst[1], pucSrc, usSrcLen);

    return;
}


TAF_UINT32 At_PbUnicodeTransfer(TAF_UINT8           *pucSrc,
                                TAF_UINT16          usSrcLen,
                                SI_PB_RECORD_STRU   *pstRecord,
                                TAF_UINT16          usCodeBase)
{
    TAF_UINT32      ulResult = AT_FAILURE;

    switch (pstRecord->AlphaTagType)
    {
        case SI_PB_ALPHATAG_TYPE_GSM:
            ulResult = At_UnicodeTransferToGsm(pucSrc, usSrcLen, pstRecord->AlphaTag);

            break;

        case SI_PB_ALPHATAG_TYPE_UCS2_81:
            ulResult = At_UnicodeTransferTo81(pucSrc, usSrcLen, usCodeBase, pstRecord->AlphaTag);

            break;

        case SI_PB_ALPHATAG_TYPE_UCS2_82:
            ulResult = At_UnicodeTransferTo82(pucSrc, usSrcLen, usCodeBase, pstRecord->AlphaTag);

            break;

        case SI_PB_ALPHATAG_TYPE_UCS2_80:
            At_UnicodeTransferTo80(pucSrc, usSrcLen, pstRecord->AlphaTag);
            ulResult = AT_SUCCESS;

            break;

        default:

            break;
    }

    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_PbUnicodeTransfer: UCS2 transfer to gsm, 80, 81 or 82 error");
    }

    return ulResult;
}


TAF_UINT32 At_PbAlphaTagProc(SI_PB_RECORD_STRU *pstRecord, AT_PARSE_PARA_TYPE_STRU *pstAtParaList)
{
    TAF_UINT8       *pucAlphaTag;
    TAF_UINT16      usAlphaTagLen;
    TAF_UINT16      usAlphaCodeLen;
    TAF_UINT16      usCodeBase;

    /* �����ֶ�Ϊ��ʱ�����ô��������ֶΣ����绰����Ӧ�ñ��棬���Է��سɹ� */
    if (0 == pstAtParaList->usParaLen)
    {
        return AT_SUCCESS;
    }

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        if (pstAtParaList->usParaLen > gstPBATInfo.usNameMaxLen)
        {
            AT_ERR_LOG("At_PbAlphaTagProc error: text string to long in gsm7");

            return AT_CME_TEXT_STRING_TOO_LONG;
        }

        pstRecord->AlphaTagType = SI_PB_ALPHATAG_TYPE_GSM;

        /* GSMģʽ���ж��Ƿ�������������С��0x7f��������0x7fʱ��ʾ�û������к��зǷ��ַ� */
        if (AT_SUCCESS != At_Gsm7BitFormat(pstAtParaList->aucPara,
                                           pstAtParaList->usParaLen,
                                           pstRecord->AlphaTag,
                                           (TAF_UINT16 *)&pstRecord->ucAlphaTagLength))
        {
            AT_ERR_LOG("At_PbAlphaTagProc: error:the eighth bit is 1 in gsm7");

            return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
        }

        return AT_SUCCESS;
    }

    /* ����ռ����ڴ洢�м�ת���������ֶΣ���ౣ��Ϊ80���룬������ռ�Ϊ���볤��2�� */
    usAlphaTagLen = (TAF_UINT16)(pstAtParaList->usParaLen << 1);

    pucAlphaTag = (TAF_UINT8*)VOS_MemAlloc(WUEPS_PID_AT, DYNAMIC_MEM_PT, usAlphaTagLen);

    if (VOS_NULL_PTR == pucAlphaTag)
    {
        AT_ERR_LOG("At_PbAlphaTagProc error:malloc failed");

        return AT_FAILURE;
    }

    /* IRAģʽ����ʱ�Ȳ��ת��ΪUCS2���ٴ��� */
    if (AT_CSCS_IRA_CODE == gucAtCscsType)
    {
        At_PbIraToUnicode(pstAtParaList->aucPara,
                          pstAtParaList->usParaLen,
                          pucAlphaTag,
                          &usAlphaTagLen);
    }
    else
    {
        /* UCS2���뷽ʽ�£����ֽڱ�ʶһ���ַ������������ĵı��� */
        if (0 != (pstAtParaList->usParaLen % 4))
        {
            VOS_MemFree(WUEPS_PID_AT, pucAlphaTag);

            AT_LOG1("At_PbAlphaTagProc error: ucs2 codes length [%d] is nor 4 multiple",
                    pstAtParaList->usParaLen);

            return AT_ERROR;
        }

        if(AT_FAILURE == At_UnicodePrint2Unicode(pstAtParaList->aucPara, &(pstAtParaList->usParaLen)))
        {
            VOS_MemFree(WUEPS_PID_AT, pucAlphaTag);

            AT_ERR_LOG("At_PbAlphaTagProc error: Printunicode to unicode failed");

            return AT_ERROR;
        }

        usAlphaTagLen = pstAtParaList->usParaLen;

        VOS_MemCpy(pucAlphaTag, pstAtParaList->aucPara, usAlphaTagLen);
    }

    /* ��UCS2��IRAģʽת�����UCS2����ȷ���洢��ʽ */
    At_PbUnicodeParse(pucAlphaTag, usAlphaTagLen, &pstRecord->AlphaTagType, &usAlphaCodeLen, &usCodeBase);

    /* ����ȷ���ı��볤�ȴ��ڵ绰�������ֶ��ܴ洢�ĳ���ʱ�������û�����̫�� */
    if (usAlphaCodeLen > gstPBATInfo.usNameMaxLen)
    {
        VOS_MemFree(WUEPS_PID_AT, pucAlphaTag);

        AT_LOG1("At_PbAlphaTagProc error: name length [%d] too long", usAlphaCodeLen);

        return AT_CME_TEXT_STRING_TOO_LONG;
    }

    pstRecord->ucAlphaTagLength = (TAF_UINT8)usAlphaCodeLen;

    if (AT_SUCCESS != At_PbUnicodeTransfer(pucAlphaTag, usAlphaTagLen, pstRecord, usCodeBase))
    {
        VOS_MemFree(WUEPS_PID_AT, pucAlphaTag);

        AT_ERR_LOG("At_PbAlphaTagProc: fail to convert UCS2");

        return AT_ERROR;
    }

    VOS_MemFree(WUEPS_PID_AT, pucAlphaTag);

    return AT_SUCCESS;
}
TAF_UINT32 At_PbEmailTransferToGsm(TAF_UINT8  *pucSrc,
                                   TAF_UINT16 usSrcLen,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usGsmCodeLen = 0;
    TAF_UINT8       aucEmailUCS2[2 * SI_PB_EMAIL_MAX_LEN];
    TAF_UINT16      usUCS2Len;

    /* �Ƚ���������ת��ΪUCS2�������� */
    At_PbIraToUnicode(pucSrc, usSrcLen, aucEmailUCS2, &usUCS2Len);

    /* �ж�UCS2�ܷ�ת��ΪGSM7bit�洢 */
    if (AT_SUCCESS != At_UnicodeTransferToGsmCalcLength(aucEmailUCS2, usUCS2Len, &usGsmCodeLen))
    {
        AT_ERR_LOG("At_PbEmailTransferToGsm error: failed to transfer to Gsm");

        return AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING;
    }

    /* EMAIL�ĳ��ȴ��ڵ绰��EMAIL�ֶ��ܴ洢�ĳ���ʱ�������û�����̫�� */
    if (usGsmCodeLen > gstPBATInfo.usEmailLen)
    {
        AT_LOG1("At_PbEmailTransferToGsm error: mail length [%d] too long", usGsmCodeLen);

        return AT_CME_TEXT_STRING_TOO_LONG;
    }

    *pusDstLen = usGsmCodeLen;

    /* ����ת��ΪGSM7bit�����ת�� */
    At_UnicodeTransferToGsm(aucEmailUCS2, usUCS2Len, pucDst);

    return AT_SUCCESS;
}


TAF_UINT32 At_SetCpbfPara(TAF_UINT8 ucIndex)
{
    SI_PB_STORATE_TYPE                  Storage = SI_PB_STORAGE_UNSPECIFIED;
    SI_PB_RECORD_STRU                   stRecords;
    TAF_UINT32                          ulResult;

    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����绰�������ֶΣ��Ӵ���ģʽת��Ϊ�洢ģʽGSM7BIT��UCS2 80/81/82 */
    ulResult = At_PbAlphaTagProc(&stRecords, &gastAtParaList[0]);

    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_SetCpbfPara:something wrong in At_PbAlphaTagProc");
        return ulResult;
    }

    /* ִ��������� */
    if( AT_SUCCESS == SI_PB_Search ( gastAtClientTab[ucIndex].usClientId, 0,
                                      Storage, stRecords.ucAlphaTagLength,
                                      stRecords.AlphaTag)
        )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBF_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_SetModemStatusPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    /* ���������� */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ݳ��Ȳ����� */
    if((1 != gastAtParaList[0].usParaLen) || (1 != gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����balong modem��λ������Ҫ���������� */
    if(0 == gastAtParaList[0].ulParaValue)
    {
        return AT_OK;
    }

    ulRst = AT_FillAndSndCSIMAMsg(gastAtParaList[1].ulParaValue);

    if (VOS_OK == ulRst)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }

}
TAF_UINT32 At_SetCpbwPara2(TAF_UINT8 ucIndex)
{
    SI_PB_RECORD_STRU   stRecords;
    TAF_UINT8           *pucNumber;
    TAF_UINT16          usLen;
    TAF_UINT32          ulResult;
    TAF_UINT32          ulResultTemp;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType) /* ������� */
    {
        AT_ERR_LOG("At_SetCpbwPara2 error:incorect parameters");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex > 4) /* �������� */
    {
        AT_ERR_LOG("At_SetCpbwPara2 error: too many parameters");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ֻ��һ������ʱΪɾ������ */
    if (1 == gucAtParaIndex)
    {
        ulResult = At_PbDeleteProc(ucIndex);

        return ulResult;
    }

    if((0 == gastAtParaList[1].usParaLen)&&(0 == gastAtParaList[3].usParaLen))
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stRecords, 0x00, sizeof(stRecords));/* ��ʼ�� */

    if(0 != gastAtParaList[0].usParaLen)/* ����<index> */
    {
        stRecords.Index = (TAF_UINT16)gastAtParaList[0].ulParaValue;
    }

    if(0 != gastAtParaList[1].usParaLen)/* ����<number> */
    {
        if('+' == gastAtParaList[1].aucPara[0])
        {
            pucNumber = gastAtParaList[1].aucPara   + 1;
            usLen     = gastAtParaList[1].usParaLen - 1;
        }
        else
        {
            pucNumber = gastAtParaList[1].aucPara;
            usLen     = gastAtParaList[1].usParaLen;
        }

        if(AT_FAILURE == At_CheckPBString(pucNumber,&usLen))
        {
            AT_ERR_LOG("At_SetCpbwPara2 error: invalid characters in dial string");

            return AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING;
        }

        PS_MEM_CPY(stRecords.Number, pucNumber, usLen);

        stRecords.NumberLength = (TAF_UINT8)usLen;
    }

    /* �����绰�������ֶΣ��Ӵ���ģʽת��Ϊ�洢ģʽGSM7BIT��UCS2 80/81/82 */
    ulResult = At_PbAlphaTagProc(&stRecords, &gastAtParaList[3]);

    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_SetCpbwPara2:something wrong in At_PbAlphaTagProc");
        return ulResult;
    }

    if (0 != gastAtParaList[2].usParaLen)/* ����<type> */
    {
        /* �������ʹ��޸� */
        stRecords.NumberType = (PB_NUMBER_TYPE_INTERNATIONAL == At_GetCodeType(gastAtParaList[1].aucPara[0]))
                              ? PB_NUMBER_TYPE_INTERNATIONAL : (TAF_UINT8)gastAtParaList[2].ulParaValue;
    }
    else
    {
        stRecords.NumberType = (TAF_UINT8)At_GetCodeType(gastAtParaList[1].aucPara[0]);
    }

    if (stRecords.NumberType < 128)
    {
        AT_ERR_LOG("At_SetCpbwPara2 error: invalid index");

        return AT_CME_INVALID_INDEX;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        /* ���Ӽ�¼ */
        if (AT_SUCCESS == SI_PB_Add(gastAtClientTab[ucIndex].usClientId,
                                    0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }

        AT_ERR_LOG("At_SetCpbwPara2 error: add pb record failed");

        return AT_ERROR;
    }

    /* �޸ļ�¼ */
    ulResult      = SI_PB_GetSPBFlag();
    ulResultTemp  = SI_PB_GetStorateType();

    if((1 == ulResult)&&(SI_PB_STORAGE_SM == ulResultTemp))
    {
        if ( AT_SUCCESS == SI_PB_SModify(gastAtClientTab[ucIndex].usClientId,
                                            0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
    }

    if (AT_SUCCESS == SI_PB_Modify(gastAtClientTab[ucIndex].usClientId,
                                   0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    AT_ERR_LOG("At_SetCpbwPara2 error: modify pb record failed");

    return AT_ERROR;
}
TAF_UINT32 At_SetScpbwPara(TAF_UINT8 ucIndex)
{
    SI_PB_RECORD_STRU   stRecords;
    TAF_UINT8           *pucNumber;
    TAF_UINT16          usLen;
    TAF_UINT16          usAlphaTagLength;
    TAF_UINT32          ulResult;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)    /* ������� */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex > 12)/* �������� */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ֻ��һ������ʱΪɾ������ */
    if (1 == gucAtParaIndex)
    {
        ulResult = At_PbDeleteProc(ucIndex);

        return ulResult;
    }

    if ((0 == gastAtParaList[1].usParaLen) && (0 == gastAtParaList[3].usParaLen)
     && (0 == gastAtParaList[5].usParaLen) && (0 == gastAtParaList[7].usParaLen)
     && (0 == gastAtParaList[9].usParaLen) && (0 == gastAtParaList[11].usParaLen))
    {
        return AT_ERROR;
    }

    /* ȷ�ϱ������ͣ�UNICODE����ASCII�� */
    PS_MEM_SET(&stRecords, 0x00, sizeof(stRecords));/* ��ʼ�� */

    if (0 != gastAtParaList[0].usParaLen)/* ����<index> */
    {
        stRecords.Index = (TAF_UINT16)gastAtParaList[0].ulParaValue;
    }

    if (0 != gastAtParaList[1].usParaLen)    /* ����<num1> */
    {
        if ('+' == gastAtParaList[1].aucPara[0])
        {
            pucNumber = gastAtParaList[1].aucPara   + 1;
            usLen     = gastAtParaList[1].usParaLen - 1;
        }
        else
        {
            pucNumber = gastAtParaList[1].aucPara;
            usLen     = gastAtParaList[1].usParaLen;
        }

        if (AT_FAILURE == At_CheckPBString(pucNumber,&usLen))
        {
            return AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING;
        }

        PS_MEM_CPY(stRecords.Number, pucNumber, usLen);

        stRecords.NumberLength = (TAF_UINT8)usLen;
    }

    /* ������Ϊ��ʱ�������ֶΰ�Э����Ϊ0xFF */
    if(0 == gastAtParaList[1].usParaLen)
    {
        stRecords.NumberType = 0xFF;
        stRecords.NumberLength = 0;
    }
    else
    {
        if (0 != gastAtParaList[2].usParaLen)/* ����<type1> */
        {
            /* �������ʹ��޸� */
            stRecords.NumberType = (PB_NUMBER_TYPE_INTERNATIONAL == At_GetCodeType(gastAtParaList[1].aucPara[0]))
                                  ? PB_NUMBER_TYPE_INTERNATIONAL : (TAF_UINT8)gastAtParaList[2].ulParaValue;
        }
        else
        {
            stRecords.NumberType = (TAF_UINT8)At_GetCodeType(gastAtParaList[1].aucPara[0]);
        }
    }

    if (0 != gastAtParaList[3].usParaLen)    /* ����<num2> */
    {
        if ('+' == gastAtParaList[3].aucPara[0])
        {
            pucNumber = gastAtParaList[3].aucPara   + 1;
            usLen     = gastAtParaList[3].usParaLen - 1;
        }
        else
        {
            pucNumber = gastAtParaList[3].aucPara;
            usLen     = gastAtParaList[3].usParaLen;
        }

        if (AT_FAILURE == At_CheckPBString(pucNumber,&usLen))
        {
            return AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING;
        }

        PS_MEM_CPY(stRecords.AdditionNumber[0].Number, pucNumber, usLen);

        stRecords.AdditionNumber[0].NumberLength = (TAF_UINT8)usLen;
    }

    if(0 == gastAtParaList[3].usParaLen)
    {
        stRecords.AdditionNumber[0].NumberType = 0xFF;
        stRecords.AdditionNumber[0].NumberLength = 0;
    }
    else
    {
        if (0 != gastAtParaList[4].usParaLen)/* ����<type2> */
        {
            /* �������ʹ��޸� */
            stRecords.AdditionNumber[0].NumberType = (PB_NUMBER_TYPE_INTERNATIONAL == At_GetCodeType(gastAtParaList[3].aucPara[0]))
                                                    ? PB_NUMBER_TYPE_INTERNATIONAL : (TAF_UINT8)gastAtParaList[4].ulParaValue;
        }
        else
        {
            stRecords.AdditionNumber[0].NumberType = (TAF_UINT8)At_GetCodeType(gastAtParaList[3].aucPara[0]);
        }
    }

    if (0 != gastAtParaList[5].usParaLen)    /* ����<num3> */
    {
        if ('+' == gastAtParaList[5].aucPara[0])
        {
            pucNumber = gastAtParaList[5].aucPara   + 1;
            usLen     = gastAtParaList[5].usParaLen - 1;
        }
        else
        {
            pucNumber = gastAtParaList[5].aucPara;
            usLen     = gastAtParaList[5].usParaLen;
        }

        if (AT_FAILURE == At_CheckPBString(pucNumber,&usLen))
        {
            return AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING;
        }

        PS_MEM_CPY(stRecords.AdditionNumber[1].Number, pucNumber, usLen);

        stRecords.AdditionNumber[1].NumberLength = (TAF_UINT8)usLen;
    }

    if(0 == gastAtParaList[5].usParaLen)
    {
        stRecords.AdditionNumber[1].NumberType = 0xFF;
        stRecords.AdditionNumber[1].NumberLength = 0;
    }
    else
    {
        if (0 != gastAtParaList[6].usParaLen)/* ����<type3> */
        {
            /* �������ʹ��޸� */
            stRecords.AdditionNumber[1].NumberType = (PB_NUMBER_TYPE_INTERNATIONAL == At_GetCodeType(gastAtParaList[5].aucPara[0]))
                                                    ? PB_NUMBER_TYPE_INTERNATIONAL : (TAF_UINT8)gastAtParaList[6].ulParaValue;
        }
        else
        {
            stRecords.AdditionNumber[1].NumberType = (TAF_UINT8)At_GetCodeType(gastAtParaList[5].aucPara[0]);
        }
    }

    if (0 != gastAtParaList[7].usParaLen)    /* ����<num4> */
    {
        if ('+' == gastAtParaList[7].aucPara[0])
        {
            pucNumber = gastAtParaList[7].aucPara   + 1;
            usLen     = gastAtParaList[7].usParaLen - 1;
        }
        else
        {
            pucNumber = gastAtParaList[7].aucPara;
            usLen     = gastAtParaList[7].usParaLen;
        }

        if (AT_FAILURE == At_CheckPBString(pucNumber,&usLen))
        {
            return AT_CME_INVALID_CHARACTERS_IN_DIAL_STRING;
        }

        PS_MEM_CPY(stRecords.AdditionNumber[2].Number, pucNumber, usLen);

        stRecords.AdditionNumber[2].NumberLength = (TAF_UINT8)usLen;
    }

    if(0 == gastAtParaList[7].usParaLen)
    {
        stRecords.AdditionNumber[2].NumberType = 0xFF;
        stRecords.AdditionNumber[2].NumberLength = 0;
    }
    else
    {
        if (0 != gastAtParaList[8].usParaLen)/* ����<type4> */
        {
            /* �������ʹ��޸� */
            stRecords.AdditionNumber[2].NumberType = (PB_NUMBER_TYPE_INTERNATIONAL == At_GetCodeType(gastAtParaList[7].aucPara[0]))
                                                    ? PB_NUMBER_TYPE_INTERNATIONAL : (TAF_UINT8)gastAtParaList[8].ulParaValue;
        }
        else
        {
            stRecords.AdditionNumber[2].NumberType = (TAF_UINT8)At_GetCodeType(gastAtParaList[7].aucPara[0]);
        }
    }

    /* ����ucAlphaTagType */
    if (AT_CSCS_UCS2_CODE == gastAtParaList[10].ulParaValue)
    {
        stRecords.AlphaTagType = AT_CSCS_UCS2_CODE;
    }
    else if (AT_CSCS_IRA_CODE == gastAtParaList[10].ulParaValue)
    {
        stRecords.AlphaTagType = AT_CSCS_IRA_CODE;
    }
    else
    {
        stRecords.AlphaTagType = AT_CSCS_IRA_CODE;
    }

    if (0 != gastAtParaList[9].usParaLen) /* ����<text> */
    {
        /* ��������AT�����Ѿ�ָʾ��UNICODE����Ҫ���б���ת����ASCII�� */
        usAlphaTagLength = gastAtParaList[9].usParaLen;

        if (AT_CSCS_UCS2_CODE == stRecords.AlphaTagType)
        {
            /* ��ASCIIλ��������UNICODE��ż���� */
            if ((usAlphaTagLength % 2) != 0)
            {
                return AT_ERROR;
            }

            if (AT_FAILURE == At_UnicodePrint2Unicode(gastAtParaList[9].aucPara,&usAlphaTagLength))
            {
                return AT_ERROR;
            }

            if (AT_FAILURE == At_CheckNameUCS2Code(gastAtParaList[9].aucPara, &usAlphaTagLength))
            {
                return AT_ERROR;
            }

            stRecords.AlphaTagType = gastAtParaList[9].aucPara[0];
        }

        /* ���յõ��������ֶεĳ��Ȳ��ܳ���TAF_PB_RECORD_STRU
        �ṹ�е���󳤶ȣ�����ᵼ�¶�ջ��� */
        if (usAlphaTagLength > SI_PB_ALPHATAG_MAX_LEN)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        PS_MEM_CPY(stRecords.AlphaTag, gastAtParaList[9].aucPara, usAlphaTagLength);
        stRecords.ucAlphaTagLength = (TAF_UINT8)usAlphaTagLength;
    }

    if (0 != gastAtParaList[11].usParaLen)  /* ����<email> */
    {
        if (gastAtParaList[11].usParaLen > SI_PB_EMAIL_MAX_LEN)
        {
            return AT_CME_TEXT_STRING_TOO_LONG;
        }

        ulResult = At_PbEmailTransferToGsm(gastAtParaList[11].aucPara,
                                           gastAtParaList[11].usParaLen,
                                           stRecords.Email.Email,
                                           (TAF_UINT16*)&stRecords.Email.EmailLen);

        if (AT_SUCCESS != ulResult)
        {
            return ulResult;
        }
    }

    if (0 == gastAtParaList[0].usParaLen) /* ���� */
    {
        if ( AT_SUCCESS == SI_PB_SAdd(gastAtClientTab[ucIndex].usClientId,
                                        0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }

        return AT_ERROR;

    }

    /* �޸� */
    if ( AT_SUCCESS == SI_PB_SModify(gastAtClientTab[ucIndex].usClientId,
                                        0, SI_PB_STORAGE_UNSPECIFIED, &stRecords))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBW_SET;/* ���õ�ǰ�������� */

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;

}


/*****************************************************************************
 Prototype      : At_SetScpbrPara
 Description    : ^SCPBR
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-23
    Modification: Created
*****************************************************************************/
TAF_UINT32 At_SetScpbrPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        gastAtParaList[1].ulParaValue = gastAtParaList[0].ulParaValue;
    }

    if (AT_SUCCESS == SI_PB_SRead(gastAtClientTab[ucIndex].usClientId,
                                0, SI_PB_STORAGE_UNSPECIFIED,
                                (TAF_UINT16)gastAtParaList[0].ulParaValue,
                                (TAF_UINT16)gastAtParaList[1].ulParaValue))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SCPBR_SET;

        gulPBPrintTag = TAF_FALSE;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_SetCnumPara
 Description    : +CNUM
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-06-11
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCnumPara(TAF_UINT8 ucIndex)
{
#ifdef FEATURE_UPGRADE_TL
    USIMM_GETFILE_REQ_STRU    *pstGetCnumFile;
#endif
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

#ifdef FEATURE_UPGRADE_TL
	pstGetCnumFile = (USIMM_MsgBlock *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(USIMM_GETFILE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if(VOS_NULL_PTR == pstGetCnumFile)
    {
        LogPrint("USIMM_CMDTYPE_GETFILE_REQ:AllocMsg Failed.");

        return VOS_ERR;
    }
    pstGetCnumFile->enAppType     = USIMM_UNLIMIT_APP;
    pstGetCnumFile->enMsgType     = USIMM_CMDTYPE_GETFILE_REQ;
    pstGetCnumFile->ucRecordNum   = 0;
    pstGetCnumFile->usFileID      = 0x6F40;
    pstGetCnumFile->ulReceiverPid = WUEPS_PID_USIM;
    pstGetCnumFile->ulSendPara    = gastAtClientTab[ucIndex].usClientId;

    if(AT_SUCCESS == VOS_SendMsg(WUEPS_PID_AT, pstGetCnumFile))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNUM_READ;

        gulPBPrintTag = TAF_FALSE;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
#else
    /* ִ��������� */
    if(AT_SUCCESS == SI_PB_Read(gastAtClientTab[ucIndex].usClientId,0, SI_PB_STORAGE_ON, 0, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNUM_READ;

        gulPBPrintTag = TAF_FALSE;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
#endif
}


/*****************************************************************************
 Prototype      : At_SetCsimPara
 Description    : +CSIM=<length>,<command>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  1.Date        : 2006-10-23
    Modification: w42656
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_SetCsimPara(TAF_UINT8 ucIndex)
{
    SI_PIH_CSIM_COMMAND_STRU Command;

    /* ������� */
    if((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&Command,0x00,sizeof(Command));

    if(0 != (gastAtParaList[0].ulParaValue % 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != (gastAtParaList[1].usParaLen % 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara,&gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].ulParaValue != (TAF_UINT32)(gastAtParaList[1].usParaLen * 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<length> */
    Command.ulLen = gastAtParaList[1].usParaLen;

    /* ����<command> */
    PS_MEM_CPY((TAF_VOID*)Command.aucCommand,(TAF_VOID*)gastAtParaList[1].aucPara,(VOS_UINT16)Command.ulLen);

    /* ִ��������� */
    if(AT_SUCCESS == SI_PIH_GenericAccessReq(gastAtClientTab[ucIndex].usClientId, 0, &Command))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSIM_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCchoPara
 Description    : +CCHO=<dfname>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-05-15
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCchoPara(TAF_UINT8 ucIndex)
{
    SI_PIH_CCHO_COMMAND_STRU    stCchoCmd;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �ַ������Ȳ�Ϊ2�������� */
    if(0 != (gastAtParaList[0].usParaLen % 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ַ���ת��Ϊ16�������� */
    if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[0].aucPara, &gastAtParaList[0].usParaLen))
    {
        AT_ERR_LOG("At_SetCchoPara: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCchoCmd.ulAIDLen   = gastAtParaList[0].usParaLen;
    stCchoCmd.pucADFName = gastAtParaList[0].aucPara;

    /* ִ��������� */
    if(AT_SUCCESS == SI_PIH_CchoSetReq(gastAtClientTab[ucIndex].usClientId, 0, &stCchoCmd))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCHO_SET;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}

/*****************************************************************************
 Prototype      : At_SetCchcPara
 Description    : +CCHC=<sessionid>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-05-15
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCchcPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == SI_PIH_CchcSetReq(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    gastAtParaList[0].ulParaValue))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCHC_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}

/*****************************************************************************
 Prototype      : At_SetCglaPara
 Description    : +CGLA=<sessionid>,<length>,<command>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-05-15
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCglaPara(TAF_UINT8 ucIndex)
{
    SI_PIH_CGLA_COMMAND_STRU    stCglaCmd;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(3 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* <length>��ҪΪ2�������� */
    if(0 != (gastAtParaList[1].ulParaValue % 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �ַ������Ȳ�Ϊ2�������� */
    if(0 != (gastAtParaList[2].usParaLen % 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ַ���ת��Ϊ16�������� */
    if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[2].aucPara, &gastAtParaList[2].usParaLen))
    {
        AT_ERR_LOG("At_SetCglaPara: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* length�ֶ���ʵ������ȵ�2�� */
    if(gastAtParaList[1].ulParaValue != (TAF_UINT32)(gastAtParaList[2].usParaLen * 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCglaCmd.ulSessionID   = gastAtParaList[0].ulParaValue;
    stCglaCmd.ulLen         = gastAtParaList[2].usParaLen;
    stCglaCmd.pucCommand    = gastAtParaList[2].aucPara;

    /* ִ��������� */
    if(AT_SUCCESS == SI_PIH_CglaSetReq(gastAtClientTab[ucIndex].usClientId, 0, &stCglaCmd))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGLA_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}

/*****************************************************************************
 Prototype      : At_SetCardATRPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-08-22
    Modification: Created function by g47350
*****************************************************************************/
TAF_UINT32 At_SetCardATRPara(TAF_UINT8 ucIndex)
{
    if (AT_SUCCESS == SI_PIH_GetCardATRReq(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARD_ATR_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/********************************************************************
  Function:       At_CrsmFilePathCheck
  Description:    ִ��CRSM���������<path>����(�ļ�·�����м��)
  Input:          TAF_UINT16 usEfId:�ļ�ID
                  TAF_UINT8 *pucFilePath:�ļ�·��
                  TAF_UINT16 *pusPathLen:�ļ�·������
  Output:         ��
  Return:         AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
TAF_UINT32  At_CrsmFilePathCheck(TAF_UINT16 usEfId, TAF_UINT8 *pucFilePath, TAF_UINT16 *pusPathLen)
{
    TAF_UINT16                          usLen;
    TAF_UINT16                          ausPath[USIMM_MAX_PATH_LEN]  = {0};
    TAF_UINT16                          ausTmpPath[USIMM_MAX_PATH_LEN]  = {0};
    TAF_UINT16                          usPathLen;
    TAF_UINT16                          i;


    usPathLen   = *pusPathLen;
    usLen       = 0;

    for (i = 0; i < (usPathLen/sizeof(TAF_UINT16)); i++)
    {
        ausTmpPath[i] = ((pucFilePath[i*2]<<0x08)&0xFF00) + pucFilePath[(i*2)+1];
    }

    /* ���·��������3F00��ʼ����Ҫ����3F00����ͷ */
    if (MFID != ausTmpPath[0])
    {
        ausPath[0] = MFID;

        usLen++;
    }

    VOS_MemCpy(&ausPath[usLen], ausTmpPath, usPathLen);

    usLen += (usPathLen/sizeof(TAF_UINT16));

    if ((usEfId & 0xFF00) == EFIDUNDERMF)
    {
        usLen = 1;
    }
    /* 4F�ļ�Ҫ��5F�£�·������Ϊ3 */
    else if ((usEfId & 0xFF00) == EFIDUNDERMFDFDF)
    {
        if ((usLen != 3)
            ||((ausPath[1]&0xFF00) != DFIDUNDERMF)
            ||((ausPath[2]&0xFF00) != DFIDUNDERMFDF))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    /* 6F�ļ�Ҫ��7F�£�·������Ϊ2 */
    else if ((usEfId & 0xFF00) == EFIDUNDERMFDF)
    {
        if ((usLen != 2)
            ||((ausPath[1]&0xFF00) != DFIDUNDERMF))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    *pusPathLen  = usLen;

    VOS_MemCpy(pucFilePath, ausPath, usLen*2);

    return AT_SUCCESS;
}

/********************************************************************
  Function:       At_CrsmApduParaCheck
  Description:    ִ��CRSM��������Ĳ�����ƥ����
  Input:          ��
  Output:         ��
  Return:         AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
TAF_UINT32  At_CrsmApduParaCheck(VOS_VOID)
{
    TAF_UINT16                          usFileTag;

    /* �������Ͳ�����飬��һ����������Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_ERR_LOG("At_SetCrsmPara: command type null");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��STATUS�����⣬�ļ�ID���벻��Ϊ�� */
    if ((0 == gastAtParaList[1].ulParaValue)
        && (USIMM_STATUS != gastAtParaList[0].ulParaValue))
    {
        AT_ERR_LOG("At_CrsmApduParaCheck: File Id null.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ�ļ�IDǰ��λ */
    usFileTag   = (gastAtParaList[1].ulParaValue >> 8) & (0x00FF);

    /* ������ļ�ID������EF�ļ���ǰ��λ��������3F/5F/7F */
    if ((MFLAB == usFileTag)
       || (DFUNDERMFLAB == usFileTag)
       || (DFUNDERDFLAB == usFileTag))
    {
        AT_ERR_LOG("At_CrsmApduParaCheck: File Id error.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* <P1><P2><P3>����������ȫ��Ϊ�� */
    if ((0 == gastAtParaList[2].usParaLen)
        && (0 == gastAtParaList[3].usParaLen)
        && (0 == gastAtParaList[4].usParaLen))
    {
        return AT_SUCCESS;
    }

    /* <P1><P2><P3>����������ȫ����Ϊ�� */
    if ((0 != gastAtParaList[2].usParaLen)
        && (0 != gastAtParaList[3].usParaLen)
        && (0 != gastAtParaList[4].usParaLen))
    {
        return AT_SUCCESS;
    }

    /* �����������������AT������������� */
    return AT_CME_INCORRECT_PARAMETERS;

}

/********************************************************************
  Function:       At_CrsmFilePathParse
  Description:    ִ��CRSM���������·�����н���
  Input:          ��
  Output:         *pstCommand��CRSM��������ݽṹ
  Return:          AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
TAF_UINT32 At_CrsmFilePathParse(TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{
    TAF_UINT32                          ulResult;

    /* ����ʷ��������������߸�����Ϊ�գ�˵��û���ļ�·�����룬ֱ�ӷ��سɹ� */
    if (0 == gastAtParaList[6].usParaLen)
    {
        return AT_SUCCESS;
    }

    /* ��ת��ǰ������ļ�·�����ȱ�����4�������� */
    if (0 != (gastAtParaList[6].usParaLen % 4))
    {
        AT_ERR_LOG("At_CrsmFilePathParse: Path error");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*��������ַ���ת����ʮ����������*/
    if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[6].aucPara, &gastAtParaList[6].usParaLen))
    {
        AT_ERR_LOG("At_CrsmFilePathParse: At_AsciiNum2HexString error.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������д�ļ�ID��·����Ҫ���ļ�·����飬�����·��������U16Ϊ��λ */
    ulResult = At_CrsmFilePathCheck((TAF_UINT16)gastAtParaList[1].ulParaValue,
                                    gastAtParaList[6].aucPara,
                                    &gastAtParaList[6].usParaLen);

    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_CrsmFilePathParse: At_CrsmFilePathCheck error.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ļ�·���ͳ��� */
    pstCommand->usPathLen   = gastAtParaList[6].usParaLen;

    /* �ļ�·��������U16Ϊ��λ�ģ�·�������ĳ���Ҫ��2 */
    PS_MEM_CPY(pstCommand->ausPath, gastAtParaList[6].aucPara, gastAtParaList[6].usParaLen*sizeof(VOS_UINT16));

    return AT_SUCCESS;
}

/********************************************************************
  Function:       At_CrsmParaStatusCheck
  Description:    ִ��CRSM�����STATUS����Ĳ������
  Input:          ��
  Output:         *pstCommand��CRSM��������ݽṹ
  Return:          AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
TAF_UINT32 At_CrsmParaStatusCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{
    /* STATUS�������û�������ļ�ID���Ͳ���Ҫ��ѡ�ļ�������ֱ�ӷ�STATUS���� */
    if (0 == gastAtParaList[1].ulParaValue)
    {
        pstCommand->usEfId = VOS_NULL_WORD;
    }
    else
    {
        pstCommand->usEfId = (TAF_UINT16)gastAtParaList[1].ulParaValue;
    }

    /* ��д���ݽṹ�е�<P1><P2><P3>��Ӧ��IE�� */
    pstCommand->ucP1        =   (TAF_UINT8)gastAtParaList[2].ulParaValue;
    pstCommand->ucP2        =   (TAF_UINT8)gastAtParaList[3].ulParaValue;
    pstCommand->ucP3        =   (TAF_UINT8)gastAtParaList[4].ulParaValue;
    pstCommand->usCmdType   =   USIMM_STATUS;

    return At_CrsmFilePathParse(pstCommand);
}

/********************************************************************
  Function:       At_CrsmParaReadBinaryCheck
  Description:    ִ��CRSM�����Read Binary����Ĳ������
  Input:          ��
  Output:         *pstCommand��CRSM��������ݽṹ
  Return:          AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
TAF_UINT32 At_CrsmParaReadBinaryCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{

    /* ��д���ݽṹ�е�<P1><P2><P3>��Ӧ��IE�� */
    pstCommand->ucP1        =   (TAF_UINT8)gastAtParaList[2].ulParaValue;
    pstCommand->ucP2        =   (TAF_UINT8)gastAtParaList[3].ulParaValue;
    pstCommand->ucP3        =   (TAF_UINT8)gastAtParaList[4].ulParaValue;
    pstCommand->usEfId      =   (TAF_UINT16)gastAtParaList[1].ulParaValue;
    pstCommand->usCmdType   =   USIMM_READ_BINARY;

    /* ����������ļ�·����Ҫ���������� */
    return At_CrsmFilePathParse(pstCommand);
}


/********************************************************************
  Function:       At_CrsmParaReadBinaryCheck
  Description:    ִ��CRSM�����Read Record�Ĳ������
  Input:          ��
  Output:         *pstCommand��CRSM��������ݽṹ
  Return:         AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
TAF_UINT32 At_CrsmParaReadRecordCheck(TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{

    /* ��д���ݽṹ�е�<P1><P2><P3>��Ӧ��IE�� */
    pstCommand->ucP1        =   (TAF_UINT8)gastAtParaList[2].ulParaValue;
    pstCommand->ucP2        =   (TAF_UINT8)gastAtParaList[3].ulParaValue;
    pstCommand->ucP3        =   (TAF_UINT8)gastAtParaList[4].ulParaValue;
    pstCommand->usEfId      =   (TAF_UINT16)gastAtParaList[1].ulParaValue;
    pstCommand->usCmdType   =   USIMM_READ_RECORD;

    /* ����������ļ�·����Ҫ���������� */
    return At_CrsmFilePathParse(pstCommand);
}

/********************************************************************
  Function:       At_CrsmParaGetRspCheck
  Description:    ִ��CRSM�����Get Response����������
  Input:
  Output:         *pstCommand��CRSM��������ݽṹ?
  Return:         AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
VOS_UINT32 At_CrsmParaGetRspCheck(TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{

    /* ����������������2��������Ҫ���������ͺ��ļ�ID */
    if (gucAtParaIndex < 2)
    {
        AT_ERR_LOG("At_CrsmParaGetRspCheck: Para less than 2.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��д���ݽṹ�е�<P1><P2><P3>��Ӧ��IE�� */
    pstCommand->ucP1        =   (TAF_UINT8)gastAtParaList[2].ulParaValue;
    pstCommand->ucP2        =   (TAF_UINT8)gastAtParaList[3].ulParaValue;
    pstCommand->ucP3        =   (TAF_UINT8)gastAtParaList[4].ulParaValue;
    pstCommand->usEfId      =   (TAF_UINT16)gastAtParaList[1].ulParaValue;
    pstCommand->usCmdType   =   USIMM_GET_RESPONSE;

    /* ����������ļ�·����Ҫ���������� */
    return At_CrsmFilePathParse(pstCommand);
}

/********************************************************************
  Function:       At_CrsmParaUpdateBinaryCheck
  Description:    ִ��CRSM�����Update Binary�������
  Input:          ��
  Output:         *pstCommand��CRSM��������ݽṹ
  Return:         AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
VOS_UINT32 At_CrsmParaUpdateBinaryCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{

    /* Update Binary��������Ҫ��6������������û���ļ�·�� */
    if (gucAtParaIndex < 6)
    {
        AT_ERR_LOG("At_CrsmParaUpdateBinaryCheck: Para less than 6.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��д���ݽṹ�е�<P1><P2><P3>��Ӧ��IE�� */
    pstCommand->ucP1        =   (TAF_UINT8)gastAtParaList[2].ulParaValue;
    pstCommand->ucP2        =   (TAF_UINT8)gastAtParaList[3].ulParaValue;
    pstCommand->ucP3        =   (TAF_UINT8)gastAtParaList[4].ulParaValue;
    pstCommand->usEfId      =   (TAF_UINT16)gastAtParaList[1].ulParaValue;
    pstCommand->usCmdType   =   USIMM_UPDATE_BINARY;

    /* ���������������<data>�ַ�����ת��ǰ���ݳ��ȱ�����2�ı����Ҳ���Ϊ0 */
    if ((0 != (gastAtParaList[5].usParaLen % 2))
        || (0 == gastAtParaList[5].usParaLen))
    {
        AT_ERR_LOG("At_CrsmParaUpdateBinaryCheck: <data> error.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[5].aucPara, &gastAtParaList[5].usParaLen))
    {
        AT_ERR_LOG("At_CrsmParaUpdateBinaryCheck: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<data>���䳤����<data>��������ȷ����P3�����ճ��·���������<data>�ĳ����Ƿ��P3��ֵƥ�� */
    PS_MEM_CPY((TAF_VOID*)pstCommand->aucCommand,
               (TAF_VOID*)gastAtParaList[5].aucPara,
               gastAtParaList[5].usParaLen);

    return At_CrsmFilePathParse(pstCommand);
}

/********************************************************************
  Function:       At_CrsmParaUpdateRecordCheck
  Description:    ִ��CRSM����Ĳ������
  Input:          ��
  Output:         *pstCommand��CRSM��������ݽṹ
  Return:         AT_SUCCESS���ɹ�������Ϊʧ��
  Others:
  History        : ---
  1.Date         : 2012-05-04
    Modification : Created function
********************************************************************/
VOS_UINT32 At_CrsmParaUpdateRecordCheck (TAF_SIM_RESTRIC_ACCESS_STRU *pstCommand)
{

    /* Update Binary��������Ҫ��6������������û���ļ�·�� */
    if (gucAtParaIndex < 6)
    {
        AT_ERR_LOG("At_CrsmParaUpdateRecordCheck: Para less than 6.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��д���ݽṹ�е�<P1><P2><P3>��Ӧ��IE�� */
    pstCommand->ucP1        =   (TAF_UINT8)gastAtParaList[2].ulParaValue;
    pstCommand->ucP2        =   (TAF_UINT8)gastAtParaList[3].ulParaValue;
    pstCommand->ucP3        =   (TAF_UINT8)gastAtParaList[4].ulParaValue;
    pstCommand->usEfId      =   (TAF_UINT16)gastAtParaList[1].ulParaValue;
    pstCommand->usCmdType   =   USIMM_UPDATE_RECORD;

     /* ���������������<data>�ַ������ݳ��ȱ�����2�ı����Ҳ���Ϊ0 */
    if ((0 != (gastAtParaList[5].usParaLen % 2))
        || (0 == gastAtParaList[5].usParaLen))
    {
        AT_ERR_LOG("At_CrsmParaUpdateRecordCheck: <data> error.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[5].aucPara, &gastAtParaList[5].usParaLen))
    {
        AT_ERR_LOG("At_CrsmParaUpdateRecordCheck: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<data>���䳤����<data>��������ȷ����P3�����ճ��·���������<data>�ĳ����Ƿ��P3��ֵƥ�� */
    PS_MEM_CPY((TAF_VOID*)pstCommand->aucCommand,
               (TAF_VOID*)gastAtParaList[5].aucPara,
               gastAtParaList[5].usParaLen);

    return At_CrsmFilePathParse(pstCommand);
}

/*****************************************************************************
 Prototype      : At_SetCrsmPara
 Description    : +CRSM=<command>[,<fileid>[,<P1>,<P2>,<P3>[,<data>,<pathid>]]]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-03-02
    Modification: Created function
  2.Date        : 2012-05-05
    Modification: ���ӶԵ��߸������Ĵ���
*****************************************************************************/
TAF_UINT32 At_SetCrsmPara(TAF_UINT8 ucIndex)
{
    TAF_SIM_RESTRIC_ACCESS_STRU         stCommand;
    TAF_UINT32                          ulResult;

    /* �������� */
    if (gucAtParaIndex > 7)
    {
        AT_ERR_LOG("At_SetCrsmPara: too many para");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���������<P1><P2><P3>����������������ֻ��д���ֲ��� */
    if (AT_SUCCESS != At_CrsmApduParaCheck())
    {
       AT_ERR_LOG("At_SetCrsmPara: At_CrsmApduParaCheck fail.");

       return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stCommand, 0x00, sizeof(TAF_SIM_RESTRIC_ACCESS_STRU));

    switch(gastAtParaList[0].ulParaValue)
    {
        case USIMM_STATUS:
            ulResult = At_CrsmParaStatusCheck(&stCommand);
            break;
        case USIMM_READ_BINARY:
            ulResult = At_CrsmParaReadBinaryCheck(&stCommand);
            break;
        case USIMM_READ_RECORD:
            ulResult = At_CrsmParaReadRecordCheck(&stCommand);
            break;
        case USIMM_GET_RESPONSE:
            ulResult = At_CrsmParaGetRspCheck(&stCommand);
            break;
        case USIMM_UPDATE_BINARY:
            ulResult = At_CrsmParaUpdateBinaryCheck(&stCommand);
            break;
        case USIMM_UPDATE_RECORD:
            ulResult = At_CrsmParaUpdateRecordCheck(&stCommand);
            break;
        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_SUCCESS != ulResult )
    {
        AT_ERR_LOG("At_SetCrsmPara: para parse fail");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_UsimRestrictedAccessCommand(gastAtClientTab[ucIndex].usClientId, 0,&stCommand))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CRSM_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_CheckCpinPara(VOS_VOID)
{
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();


    /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ���<pin>��������̣�ֱ�ӷ��ش��� */
    if ( (TAF_PH_PINCODELENMAX < gastAtParaList[0].usParaLen)
      || (TAF_PH_PINCODELENMIN > gastAtParaList[0].usParaLen) )
    {
        if (SYSTEM_APP_ANDROID != *pucSystemAppConfig)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            /* AP-MODEM��̬�£�����������Ϊ1ʱ, ��һ��������������Ϊ16 */
            if ( (TAF_PH_UNLOCKCODELEN != gastAtParaList[0].usParaLen)
              || (1 != gucAtParaIndex) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }
    }

    /* �����������ʱ��<newpin>��������̣�ֱ�ӷ��ش��� */
    if (2 == gucAtParaIndex)
    {
        if ( (TAF_PH_PINCODELENMAX < gastAtParaList[1].usParaLen)
          || (TAF_PH_PINCODELENMIN > gastAtParaList[1].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    return AT_SUCCESS;

}
TAF_UINT32 At_SetCpinPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32                          ulResult;
    MN_PH_SET_CPIN_REQ_STRU             stSetCPinReq;

    /* ������� */
    ulResult = At_CheckCpinPara();
    if(AT_SUCCESS != ulResult)
    {
        return ulResult;
    }

    stSetCPinReq.usPara0Len = gastAtParaList[0].usParaLen;
    stSetCPinReq.usPara1Len = gastAtParaList[1].usParaLen;
    PS_MEM_CPY((VOS_VOID*)stSetCPinReq.aucPara0,(VOS_VOID*)gastAtParaList[0].aucPara,stSetCPinReq.usPara0Len);
    PS_MEM_CPY((VOS_VOID*)stSetCPinReq.aucPara1,(VOS_VOID*)gastAtParaList[1].aucPara,stSetCPinReq.usPara1Len);


    /* ͨ��TAF_MSG_MMA_SET_PIN ��Ϣ������CPIN */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      At_GetOpId(),
                                      TAF_MSG_MMA_SET_PIN,
                                      (VOS_VOID*)&stSetCPinReq,
                                      sizeof(stSetCPinReq),
                                      I0_WUEPS_PID_MMA);

    if(AT_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MSG_MMA_SET_PIN;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}
/*****************************************************************************
 Prototype      : At_SetCpin2Para
 Description    : +CPIN2=<pin>[,<newpin>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_SetCpin2Para(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;
    TAF_UINT32           ulResult;

    /* ������� */
    ulResult = At_CheckCpinPara();
    if(AT_SUCCESS != ulResult)
    {
        return ulResult;
    }

    /* ��ʼ�� */
    /* PS_MEM_SET(&stPinData,0x00,sizeof(stPinData)); */
    SI_PB_MemSet(sizeof(stPinData), 0xFF, (VOS_UINT8*)&stPinData);

    /* ����<pin> */
    if(0 != gastAtParaList[0].usParaLen)
    {
        PS_MEM_CPY((TAF_VOID*)stPinData.aucOldPin,(TAF_VOID*)gastAtParaList[0].aucPara,gastAtParaList[0].usParaLen);
    }

    /* ����<newpin> */
    if(0 != gastAtParaList[1].usParaLen)
    {
        PS_MEM_CPY((TAF_VOID*)stPinData.aucNewPin,(TAF_VOID*)gastAtParaList[1].aucPara,gastAtParaList[1].usParaLen);
    }

    /* ����CmdType */
    if(0 == gastAtParaList[1].usParaLen)
    {
        stPinData.PinType = TAF_SIM_PIN2;
        stPinData.CmdType = TAF_PIN_VERIFY;
    }
    else
    {
        stPinData.PinType = TAF_SIM_PUK2;
        stPinData.CmdType = TAF_PIN_UNBLOCK;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        /* ���õ�ǰ�������� */
        if(0 == gastAtParaList[1].usParaLen)
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN2_VERIFY_SET;
        }
        else
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN2_UNBLOCK_SET;
        }
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetIccidPara
 Description    : ^ICCID
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetIccidPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ձ�ͣ�ֱ�ӷ���AT_OK */
    return AT_OK;
}


TAF_UINT32 At_SetPNNPara(TAF_UINT8 ucIndex)
{
    TAF_PH_QRY_USIM_INFO_STRU           stUsimInfo;

    PS_MEM_SET(&stUsimInfo, 0x00, sizeof(stUsimInfo));

    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 != gastAtParaList[0].ulParaValue)
        &&(1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    if (0 == gastAtParaList[0].ulParaValue)
    {
        stUsimInfo.Icctype = TAF_PH_ICC_SIM;
    }
    else
    {
        stUsimInfo.Icctype = TAF_PH_ICC_USIM;
    }
    stUsimInfo.enEfId = TAF_PH_PNN_FILE;
    /*linear fixed file only support 254 reocrd*/
    if(0 != gastAtParaList[1].usParaLen)
    {
        if( (gastAtParaList[1].ulParaValue > 0xFE)
         || (gastAtParaList[1].ulParaValue == 0))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            stUsimInfo.ulRecNum = gastAtParaList[1].ulParaValue;
        }
    }
    else
    {
        stUsimInfo.ulRecNum = 0;

        /* �ڶ�ȡPNN�б���ʱ����зִ��·���ÿ��ֻ��ȡTAF_MMA_PNN_INFO_MAX_NUM�����Է�ֹA�������ڴ�ʧ����ɸ�λ */
        stUsimInfo.stPnnQryIndex.usPnnCurrIndex = 0;   /* ��һ���·���ʱ��IndexΪ0���������յ�TAF��CNF��Ϣ��ʱ���ٽ��з������·� */
        stUsimInfo.stPnnQryIndex.usPnnNum       = TAF_MMA_PNN_INFO_MAX_NUM;
    }

    /* ִ��������� */
    if(AT_SUCCESS == TAF_QryUsimInfo(gastAtClientTab[ucIndex].usClientId,0,&stUsimInfo))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PNN_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
TAF_UINT32 At_SetCPNNPara(TAF_UINT8 ucIndex)
{
    TAF_PH_ICC_TYPE                     IccType;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 != gastAtParaList[0].ulParaValue)
        &&(1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    if (0 == gastAtParaList[0].ulParaValue)
    {
        IccType = TAF_PH_ICC_SIM;
    }
    else
    {
        IccType = TAF_PH_ICC_USIM;
    }

    /* ִ��������� */
    if(AT_SUCCESS == TAF_QryCpnnInfo(gastAtClientTab[ucIndex].usClientId,0,IccType))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPNN_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*******************************************************************************
*Function   : At_SetOPLPara
*Description: �ú�����Ҫ�����������AT����Ĳ�����ͨ������Taf_ParaQuery�Ľӿ�ִ
              ��AT����Ĳ���������Taf_ParaQueryʱOpId����Ϊ0xFF����ʶ��ѯOPL�ļ���
              �ݲ�����
*Input      :
*Output     :
*Return     : TAF_UINT32
*Others     :
*History    :
  1.Date        : 2008-03-06
    Modification: Created function
********************************************************************************/
TAF_UINT32 At_SetOPLPara (TAF_UINT8 ucIndex)
{
    TAF_PH_QRY_USIM_INFO_STRU           stUsimInfo;

    /* ������� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 != gastAtParaList[0].ulParaValue)
        &&(1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (0 == gastAtParaList[0].ulParaValue)
    {
        stUsimInfo.Icctype = TAF_PH_ICC_SIM;
    }
    else
    {
        stUsimInfo.Icctype = TAF_PH_ICC_USIM;
    }
    stUsimInfo.enEfId = TAF_PH_OPL_FILE;
    /*linear fixed file only support 254 reocrd*/
    if((0 != gastAtParaList[1].usParaLen))
    {
        if((gastAtParaList[1].ulParaValue > 0xFE)
        || (gastAtParaList[1].ulParaValue == 0))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            stUsimInfo.ulRecNum = gastAtParaList[1].ulParaValue;
        }
    }
    else
    {
        stUsimInfo.ulRecNum = 0;
    }

    /* ִ��������� */
    if(AT_SUCCESS == TAF_QryUsimInfo(gastAtClientTab[ucIndex].usClientId,0,&stUsimInfo))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PNN_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}
/*****************************************************************************
 Prototype      : At_SetCardlockPara
 Description    : ^CARDLOCK
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2008-03-15
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCardlockPara(TAF_UINT8 ucIndex)
{
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* <unlock_code>����Ϊ����Ϊ8�������ַ��� */
    if( TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX == gastAtParaList[0].usParaLen)
    {
        if ( AT_FAILURE == At_CheckNumString(gastAtParaList[0].aucPara,
                                             TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX)
           )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            PS_MEM_SET( &stMePersonalisationData,0,sizeof(TAF_ME_PERSONALISATION_DATA_STRU) );
            /* �����û������� */
            PS_MEM_CPY( stMePersonalisationData.aucOldPwd,
                        gastAtParaList[0].aucPara,
                        TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    /* ��ȫ��������ΪУ������ */
    stMePersonalisationData.CmdType        = TAF_ME_PERSONALISATION_VERIFY;
    /* ��������Ϊ������ */
    stMePersonalisationData.MePersonalType = TAF_OPERATOR_PERSONALISATION;
     /* ִ��������� */
    if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARD_LOCK_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_FillSsBsService(
    TAF_SS_ERASESS_REQ_STRU            *pstSSPara,
    AT_PARSE_PARA_TYPE_STRU            *pstAtPara
)
{
    if ( (0 == pstAtPara->usParaLen )
      || (AT_CLCK_PARA_CLASS_ALL == pstAtPara->ulParaValue) )
    {
        /* Ĭ��ֵ */
        pstSSPara->OP_BsService = 0;
    }
    else
    {
        if(AT_FAILURE == At_SsPrint2Class(&(pstSSPara->BsService),
                                          (VOS_UINT8)pstAtPara->ulParaValue))
        {
            return VOS_ERR;
        }
        pstSSPara->OP_BsService = 1;
    }

    return VOS_OK;
}
VOS_UINT32 AT_FillSsNoRepCondTime(
    VOS_UINT8                           ucSsCode,
    AT_PARSE_PARA_TYPE_STRU            *pstAtPara,
    TAF_SS_REGISTERSS_REQ_STRU         *pstSSPara
)
{
    if ((TAF_ALL_FORWARDING_SS_CODE      == ucSsCode)
     || (TAF_ALL_COND_FORWARDING_SS_CODE == ucSsCode)
     || (TAF_CFNRY_SS_CODE               == ucSsCode))
    {
        if (pstAtPara->usParaLen)
        {
            pstSSPara->OP_NoRepCondTime = 1;
            pstSSPara->NoRepCondTime    = (TAF_SS_NOREPLYCONDITIONTIME)pstAtPara->ulParaValue;
        }
        else
        {
            /* Ĭ��ֵ */
            pstSSPara->OP_NoRepCondTime = 1;
            pstSSPara->NoRepCondTime    = 20;
        }
    }

    return VOS_OK;
}
TAF_UINT32 At_SetCcwaPara(TAF_UINT8 ucIndex)
{
    TAF_SS_ERASESS_REQ_STRU             para;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* ����SsCode */
    para.SsCode = TAF_CW_SS_CODE;

    /* ����<n> */
    if(0 != gastAtParaList[0].usParaLen)
    {
        pstSsCtx->ucCcwaType = (AT_CCWA_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        pstSsCtx->ucCcwaType = AT_CCWA_DISABLE_TYPE;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        return AT_OK;
    }

    /* ����<class> */
    if (VOS_OK != AT_FillSsBsService(&para, &gastAtParaList[2]))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    switch(gastAtParaList[1].ulParaValue)
    {
    case 0: /* disable */
        if(AT_SUCCESS == TAF_DeactivateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCWA_DISABLE;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }

    case 1: /* enable */
        if(AT_SUCCESS == TAF_ActivateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCWA_ENABLE;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }

    default: /* query status */
        gastAtClientTab[ucIndex].ulTemp = gastAtParaList[2].ulParaValue;
        para.OP_BsService = 0;
        if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
        {
            /* ���õ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCWA_QUERY;
            return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
        }
        else
        {
            return AT_ERROR;
        }
    }
}

/*****************************************************************************
�� �� ��  : AT_CheckCcfcParaValid
��������  : ���AT����AT+CFCC��������Ϸ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��19��
�޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckCcfcParaValid( VOS_VOID  )
{

    /* ������� */
    if ( (0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 8 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���<number>������ֱ�ӷ��ش��� */
    if ( gastAtParaList[2].usParaLen > TAF_SS_MAX_FORWARDED_TO_NUM_LEN )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���<subaddr>������ֱ�ӷ��ش��� */
    if ( gastAtParaList[5].usParaLen > TAF_SS_MAX_FORWARDED_TO_SUBADDRESS_LEN )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���NUM�������벻��ȷ */
    if ( 0 != gastAtParaList[2].usParaLen )
    {
        if( AT_FAILURE == At_CheckDialString(gastAtParaList[2].aucPara,
            gastAtParaList[2].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* ���SubAddress�������벻��ȷ */
    if ( 0 != gastAtParaList[5].usParaLen )
    {
        if( AT_FAILURE == At_CheckDialString(gastAtParaList[5].aucPara,
            gastAtParaList[5].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    return AT_OK;
}

/*****************************************************************************
�� �� ��  : AT_GetSsCodeFromCfccPara
��������  : ��ȡ��ǰAT���������SsCode
�������  : VOS_UINT32
ulPara
�������  : ��
�� �� ֵ  : TAF_SS_CODE
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��19��
�޸�����   : �����ɺ���

*****************************************************************************/
TAF_SS_CODE AT_GetSsCodeFromCfccPara( VOS_VOID  )
{
    TAF_SS_CODE                         ssCode;

    /* ����SsCode */
    switch( gastAtParaList[0].ulParaValue )
    {
    case 0:
        ssCode = TAF_CFU_SS_CODE;
        break;

    case 1:
        ssCode = TAF_CFB_SS_CODE;
        break;

    case 2:
        ssCode = TAF_CFNRY_SS_CODE;
        break;

    case 3:
        ssCode = TAF_CFNRC_SS_CODE;
        break;

    case 4:
        ssCode = TAF_ALL_FORWARDING_SS_CODE;
        break;

    default:
        ssCode = TAF_ALL_COND_FORWARDING_SS_CODE;
        break;
    }

    return ssCode;
}

/*****************************************************************************
�� �� ��  : AT_SetNumAttribute
��������  : ���ú���ת�Ƶ�����
�������  : ��
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��19��
�޸�����   : �����ɺ���
 2.��    ��   : 2013��05��28��
   �޸�����   : SS FDN&Call Control��Ŀ��CCFC�����к��벻Я��+�ţ�����BCD����ʧ��
*****************************************************************************/
VOS_VOID AT_SetNumAttribute(
    TAF_SS_NUMTYPE                      *pNumType,
    TAF_UINT8                           *pucFwdToNum
    )
{
    /* +��ʾ���ʺ��룬�ں����������Ѿ�ָʾ������Ҫ��������Ϣ�� */
    if ('+' == gastAtParaList[2].aucPara[0])
    {
        PS_MEM_CPY((TAF_CHAR*)pucFwdToNum,
            (TAF_CHAR*)(gastAtParaList[2].aucPara+1),
            (gastAtParaList[2].usParaLen-1));
    }
    else
    {
        PS_MEM_CPY((TAF_CHAR*)pucFwdToNum,
            (TAF_CHAR*)gastAtParaList[2].aucPara,
            gastAtParaList[2].usParaLen);
    }

    if( gastAtParaList[3].usParaLen )
    {
        *pNumType = (TAF_SS_NUMTYPE)gastAtParaList[3].ulParaValue;
    }
    else
    {
        *pNumType = At_GetCodeType(gastAtParaList[2].aucPara[0]);
    }
}

/*****************************************************************************
�� �� ��  : AT_SetSubAddrAttribute
��������  : ����SubAddr������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��19��
�޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_SetSubAddrAttribute(
    TAF_SS_SUBADDRTYPE                  *pSubAddrType,
    TAF_UINT8                           *pucFwdToSubAddr
)
{
    PS_MEM_CPY((TAF_CHAR*)pucFwdToSubAddr,
        (TAF_CHAR*)gastAtParaList[5].aucPara,
        gastAtParaList[5].usParaLen);

    if( gastAtParaList[6].usParaLen )
    {
        *pSubAddrType = (TAF_UINT8)gastAtParaList[6].ulParaValue;
    }
    else
    {
        *pSubAddrType = 128;
    }

}

/*****************************************************************************
�� �� ��  : AT_DeactivateSSReq
��������  : ȥ�������ת��ҵ��
�������  : ��
�������  : ��
�� �� ֵ  : VOS_VOID
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��19��
�޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_DeactivateSSReq(
    TAF_UINT8                           ucIndex,
    TAF_SS_ERASESS_REQ_STRU             *pstEraseReq
)
{
    if( AT_SUCCESS == TAF_DeactivateSSReq(gastAtClientTab[ucIndex].usClientId,
        0,
        pstEraseReq) )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCFC_DISABLE;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}


VOS_UINT32 AT_ActivateSSReq(
    TAF_UINT8                           ucIndex,
    TAF_SS_ERASESS_REQ_STRU             *pstActivateReq
)
{
    if( AT_SUCCESS == TAF_ActivateSSReq(gastAtClientTab[ucIndex].usClientId,
        0,
        pstActivateReq) )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCFC_ENABLE;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}


VOS_UINT32  AT_InterrogateSSReq(
    TAF_UINT8                           ucIndex,
    TAF_SS_ERASESS_REQ_STRU             *pstInterrogateReq
)
{
    gastAtClientTab[ucIndex].ulTemp = gastAtParaList[4].ulParaValue;

    if ( AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId,
        0,
        pstInterrogateReq) )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCFC_QUERY;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}


VOS_UINT32 AT_RegisterSSReq(
    TAF_UINT8                           ucIndex,
    TAF_SS_REGISTERSS_REQ_STRU          *pstRegisterReq
)
{
    if ( AT_SUCCESS == TAF_RegisterSSReq(gastAtClientTab[ucIndex].usClientId,
        0,
        pstRegisterReq) )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCFC_REGISTRATION;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}

/*****************************************************************************
�� �� ��  : AT_EraseSSReq
��������  : ɾ������ƫת����ҵ��
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32
���ú���  :
��������  :

�޸���ʷ      :
1.��    ��   : 2010��1��19��
�޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_EraseSSReq(
    TAF_UINT8                           ucIndex,
    TAF_SS_ERASESS_REQ_STRU             *pstEraseSSReq
)
{
    if ( AT_SUCCESS == TAF_EraseSSReq(gastAtClientTab[ucIndex].usClientId,
        0,
        pstEraseSSReq) )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCFC_ERASURE;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_ERROR;
}


TAF_UINT32 At_SetCcfcPara(TAF_UINT8 ucIndex)
{
    TAF_SS_REGISTERSS_REQ_STRU          para;
    TAF_SS_ERASESS_REQ_STRU             sndpara;
    VOS_UINT32                          ulRet;

    ulRet = AT_CheckCcfcParaValid();
    if ( AT_OK != ulRet )
    {
        return ulRet;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&para,0x00,sizeof(para));
    PS_MEM_SET(&sndpara,0x00,sizeof(sndpara));

    para.SsCode = AT_GetSsCodeFromCfccPara();

    /* ����<number>,<type> */
    if ( 0 != gastAtParaList[2].usParaLen )
    {
        para.OP_FwdToNum = 1;
        para.OP_NumType  = 1;
        AT_SetNumAttribute(&para.NumType,para.aucFwdToNum);
    }
    else
    {
        para.OP_FwdToNum = 0;
        para.OP_NumType  = 0;
    }

    /* ����<subaddr>,<satype> */
    if ( 0 != gastAtParaList[5].usParaLen )
    {
        para.OP_FwdToAddr = 1;
        para.OP_SubAddrType = 1;
        AT_SetSubAddrAttribute(&(para.SubAddrType), para.aucFwdToSubAddr);
    }
    else
    {
        para.OP_FwdToAddr   = 0;
        para.OP_SubAddrType = 0;
    }

    /* ����<time> */
    AT_FillSsNoRepCondTime(para.SsCode, &gastAtParaList[7], &para);

    /* ����<class> */
    if (VOS_OK != AT_FillSsBsService(&sndpara, &gastAtParaList[4]))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    sndpara.SsCode    = para.SsCode;

    if (VOS_TRUE == sndpara.OP_BsService)
    {
        para.OP_BsService               = sndpara.OP_BsService;
        para.BsService.BsType           = sndpara.BsService.BsType;
        para.BsService.BsServiceCode    = sndpara.BsService.BsServiceCode;
    }

    /* ִ��������� */
    switch(gastAtParaList[1].ulParaValue)
    {
    case 0: /* <mode>: disable */
        ulRet = AT_DeactivateSSReq(ucIndex,&sndpara);
        break;

    case 1: /* <mode>: enable */
        ulRet = AT_ActivateSSReq(ucIndex,&sndpara);
        break;

    case 2: /* <mode>: query status */
        ulRet = AT_InterrogateSSReq(ucIndex,&sndpara);
        break;

    case 3: /* <mode>: registration */
        ulRet = AT_RegisterSSReq(ucIndex,&para);
        break;

    default:    /* <mode>: erasure */
        ulRet = AT_EraseSSReq(ucIndex,&sndpara);
        break;
    }

    return ulRet;
}


/*****************************************************************************
 Prototype      : At_SetCmlckPara
 Description    : +CLCK=<fac>,<action>[,<passwd>[,<data>]]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-10-06
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCmlckPara (TAF_UINT8 ucIndex)
{
    TAF_UINT32 ulresult;


    /* ������� */
    if((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))

    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 4)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[0].ulParaValue)
    {
        case AT_CMLCK_PS_TYPE:
        {
            TAF_ME_PERSONALISATION_DATA_STRU stMePersonalisationData;

            if(TAF_PH_PINCODELENMAX < gastAtParaList[2].usParaLen)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ��ʼ�� */
            PS_MEM_SET(&stMePersonalisationData,0x00,sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

            /* ����<passwd> */
            if(0 != gastAtParaList[2].usParaLen)
            {
                PS_MEM_CPY((TAF_CHAR*)stMePersonalisationData.aucOldPwd,(VOS_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
            }

            /* ����PinType */
            stMePersonalisationData.MePersonalType = TAF_SIM_PERSONALISATION;

            if(0 != gastAtParaList[3].usParaLen)
            {
                ulresult = At_AsciiNum2Num(stMePersonalisationData.unMePersonalisationSet.SimPersionalisationStr.aucSimPersonalisationStr,
                                           gastAtParaList[3].aucPara,
                                           gastAtParaList[3].usParaLen);
                if (AT_SUCCESS != ulresult)
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }
                /*
                At_AsciiNum2HexString(gastAtParaList[3].aucPara,&gastAtParaList[3].usParaLen);
                PS_MEM_CPY((VOS_CHAR*)stMePersonalisationData.unMePersonalisationSet.aucSimPersonalisationStr,
                          (VOS_CHAR*)gastAtParaList[3].aucPara,
                          gastAtParaList[3].usParaLen);
                */
                stMePersonalisationData.unMePersonalisationSet.SimPersionalisationStr.DataLen= (VOS_UINT8)gastAtParaList[3].usParaLen;
            }


            /* ����CmdType */
            switch(gastAtParaList[1].ulParaValue)
            {
            case 0:
                if ((15 < gastAtParaList[3].usParaLen) || (0 == gastAtParaList[3].usParaLen))
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }
                stMePersonalisationData.CmdType = TAF_ME_PERSONALISATION_SET;

                break;

            case 1:
                stMePersonalisationData.CmdType = TAF_ME_PERSONALISATION_RETRIEVE;

                break;

            default:
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ִ��������� */
            if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_PIN_HANDLE;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }

        }

        default:
            return AT_CME_INCORRECT_PARAMETERS;
    }


}

/*****************************************************************************
 �� �� ��  : AT_CheckPinLength
 ��������  : ���PIN�볤��
 �������  : VOS_UINT16                          usLen
             VOS_UINT8                          *pucPin
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckPinLength(
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucPin
)
{
    if (VOS_NULL_PTR == pucPin)
    {
        AT_ERR_LOG("AT_CheckPinLength():PIN is NULL PTR");
        return VOS_ERR;
    }

    if ((usLen > TAF_PH_PINCODELENMAX)
     || (usLen < TAF_PH_PINCODELENMIN))
    {
        AT_ERR_LOG("AT_CheckPinLength():PIN LENGTH is Error");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_CheckPinValue
 ��������  : ���PIN��ֵ
 �������  : VOS_UINT16                          usLen
             VOS_UINT8                          *pucPin
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckPinValue(
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucPin
)
{
    VOS_UINT8                           i;

    if (VOS_NULL_PTR == pucPin)
    {
        AT_ERR_LOG("AT_CheckPinValue(): PIN is NULL PTR");
        return VOS_ERR;
    }

    for (i = 0; i < usLen ; i++ )
    {
        if ( (pucPin[i] >'9' )
           ||(pucPin[i] <'0'))
        {
            AT_ERR_LOG("AT_CheckPinValue(): PIN Value is Error");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_CheckPinAvail
 ��������  : ���PIN��Ч��
 �������  : VOS_UINT16                          usLen,
             VOS_UINT8                          *pucPin
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckPinAvail(
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pucPin
)
{
    if (VOS_OK != AT_CheckPinLength(usLen, pucPin))
    {
        AT_ERR_LOG("AT_CheckPinAvail(): PIN Length is Error");
        return VOS_ERR;
    }
    else
    {
        if (VOS_OK != AT_CheckPinValue(usLen, pucPin))
        {
            AT_ERR_LOG("AT_CheckPinAvail():PIN Value is Error");
            return VOS_ERR;
        }
    }
    return VOS_OK;
}


TAF_UINT32 At_SetClckPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 4)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<fac> */
    switch(gastAtParaList[0].ulParaValue)
    {
    case AT_CLCK_P2_TYPE:
        return AT_CME_INCORRECT_PARAMETERS;

    case AT_CLCK_SC_TYPE:
        {
            TAF_PH_PIN_DATA_STRU stPinData;

            if (TAF_PH_PINCODELENMAX < gastAtParaList[2].usParaLen)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ��ʼ�� */
            PS_MEM_SET(&stPinData, 0xFF, sizeof(stPinData));

            /* ����<passwd> */
            if(0 != gastAtParaList[2].usParaLen)
            {
                PS_MEM_CPY((TAF_CHAR*)stPinData.aucOldPin,(TAF_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
            }

            stPinData.PinType = TAF_SIM_PIN;

            /* ����CmdType */
            switch(gastAtParaList[1].ulParaValue)
            {
            case 0:
                stPinData.CmdType = TAF_PIN_DISABLE;
                if (VOS_OK != AT_CheckPinAvail(gastAtParaList[2].usParaLen, gastAtParaList[2].aucPara))
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }
                break;

            case 1:
                stPinData.CmdType = TAF_PIN_ENABLE;
                if (VOS_OK != AT_CheckPinAvail(gastAtParaList[2].usParaLen, gastAtParaList[2].aucPara))
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }
                break;

            default:
                stPinData.CmdType = TAF_PIN_QUERY;
                break;
            }

            /* ִ��������� */
            if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_PIN_HANDLE;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        }
    case AT_CLCK_FD_TYPE:
        {

            TAF_UINT8   aucPin[TAF_PH_PINCODELENMAX];
            TAF_UINT32  CmdType;
            TAF_UINT32  Result;

            if(TAF_PH_PINCODELENMAX < gastAtParaList[2].usParaLen)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ��ʼ�� */
            PS_MEM_SET(aucPin, 0xFF, sizeof(aucPin));

            /* ����<passwd> */
            if(0 != gastAtParaList[2].usParaLen)
            {
                PS_MEM_CPY((TAF_CHAR*)aucPin,(TAF_CHAR*)gastAtParaList[2].aucPara, gastAtParaList[2].usParaLen);
            }

            CmdType = gastAtParaList[1].ulParaValue;

            /* ִ�������������ǰֻ��FDN��صĲ�����AT�����֧��BDN���� */
            if(SI_PIH_FDN_BDN_ENABLE == CmdType)
            {
                Result = SI_PIH_FdnEnable(gastAtClientTab[ucIndex].usClientId, 0, aucPin);
            }
            else if(SI_PIH_FDN_BDN_DISABLE == CmdType)
            {
                Result = SI_PIH_FdnDisable(gastAtClientTab[ucIndex].usClientId, 0, aucPin);
            }
            else
            {
                Result = SI_PIH_FdnBdnQuery(gastAtClientTab[ucIndex].usClientId, 0, SI_PIH_FDN_QUERY);
            }

            if(AT_SUCCESS == Result)
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_PIN_HANDLE;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        }

    case AT_CLCK_PS_TYPE:
        {
            TAF_ME_PERSONALISATION_DATA_STRU stMePersonalisationData;

            if(TAF_PH_PINCODELENMAX < gastAtParaList[2].usParaLen)
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ��ʼ�� */
            PS_MEM_SET(&stMePersonalisationData,0x00,sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

            /* ����<passwd> */
            if(0 != gastAtParaList[2].usParaLen)
            {
                PS_MEM_CPY((VOS_CHAR*)stMePersonalisationData.aucOldPwd,(VOS_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
            }

            /* ����PinType */
            stMePersonalisationData.MePersonalType = TAF_SIM_PERSONALISATION;


            /* ����CmdType */
            switch(gastAtParaList[1].ulParaValue)
            {
            case 0:
                stMePersonalisationData.CmdType = TAF_ME_PERSONALISATION_DEACTIVE;
                break;

            case 1:
                stMePersonalisationData.CmdType = TAF_ME_PERSONALISATION_ACTIVE;
                break;

            default:
                stMePersonalisationData.CmdType = TAF_ME_PERSONALISATION_QUERY;
                break;
            }

            /* ִ��������� */
            if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_PIN_HANDLE;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        }



    default:
        {
            TAF_SS_ERASESS_REQ_STRU para;

            /* ��ʼ�� */
            PS_MEM_SET(&para,0x00,sizeof(para));

            /* ����<password> */
            if (gastAtParaList[2].usParaLen > 0)
            {
                if (TAF_SS_MAX_PASSWORD_LEN != gastAtParaList[2].usParaLen)
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }

                para.OP_Password = VOS_TRUE;
                PS_MEM_CPY((VOS_CHAR *)para.aucPassword,
                           (VOS_CHAR *)gastAtParaList[2].aucPara,
                           gastAtParaList[2].usParaLen);
            }


            /* ����SsCode */
            At_SsPrint2Code(&para.SsCode,(TAF_UINT8)gastAtParaList[0].ulParaValue);

            /* ����<class> */
            if (VOS_OK != AT_FillSsBsService(&para, &gastAtParaList[3]))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ִ��������� */
            switch(gastAtParaList[1].ulParaValue)
            {
            case 0: /* <mode>: unlock */
                if(AT_SUCCESS == TAF_DeactivateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
                {
                    /* ���õ�ǰ�������� */
                    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_LOCK;
                    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
                }
                else
                {
                    return AT_ERROR;
                }

            case 1: /* <mode>: lock */
                if(AT_SUCCESS == TAF_ActivateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
                {
                    /* ���õ�ǰ�������� */
                    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_UNLOCK;
                    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
                }
                else
                {
                    return AT_ERROR;
                }

            default: /* <mode>: query status */
                para.OP_BsService = 0;
                gastAtClientTab[ucIndex].ulTemp = gastAtParaList[3].ulParaValue;
                if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
                {
                    /* ���õ�ǰ�������� */
                    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCK_QUERY;
                    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
                }
                else
                {
                    return AT_ERROR;
                }
            }
        }
    }
}
TAF_UINT32 At_SetCtfrPara(TAF_UINT8 ucIndex)
{
    MN_CALL_SUPS_PARAM_STRU             stCallSupsParam;
    VOS_UINT32                          ulRst;

    /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 4)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���<number>������ֱ�ӷ��ش��� */
    if(gastAtParaList[0].usParaLen > (MN_CALL_MAX_BCD_NUM_LEN * 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���<subaddr>������ֱ�ӷ��ش��� */
    if(gastAtParaList[2].usParaLen > (MN_CALL_MAX_BCD_NUM_LEN * 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen]='\0';

    ulRst = AT_AsciiNumberToBcd((VOS_CHAR *)gastAtParaList[0].aucPara,
                                stCallSupsParam.stRedirectNum.aucBcdNum,
                                &stCallSupsParam.stRedirectNum.ucNumLen);
    if (MN_ERR_NO_ERROR != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCallSupsParam.callId = 0;
    stCallSupsParam.enCallSupsCmd = MN_CALL_SUPS_CMD_DEFLECT_CALL;
    stCallSupsParam.stRedirectNum.enNumType = (TAF_UINT8)gastAtParaList[1].ulParaValue;

    if (AT_SUCCESS == MN_CALL_Sups(gastAtClientTab[ucIndex].usClientId, 0,&stCallSupsParam))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CTFR_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_SetCusdPara(VOS_UINT8 ucIndex)
{
    TAF_SS_PROCESS_USS_REQ_STRU        *pPara;
    VOS_UINT32                          ulRet;
    TAF_SS_DATA_CODING_SCHEME           DatacodingScheme;

    ulRet =  AT_ERROR;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[2].usParaLen)
    {
        /* Ĭ��Ϊ7bit���� */
        DatacodingScheme = TAF_SS_7bit_LANGUAGE_UNSPECIFIED;
    }
    else
    {
        DatacodingScheme = (TAF_SS_DATA_CODING_SCHEME)gastAtParaList[2].ulParaValue;

        /*��Ʒ��Ҫ��֧��uss2��ussd*/
    }

    /* ���<str>���������ֱ�ӷ��ش��� */
    if(AT_FAILURE == At_CheckUssdNumLen(ucIndex, DatacodingScheme, gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pPara    = (TAF_SS_PROCESS_USS_REQ_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, sizeof(TAF_SS_PROCESS_USS_REQ_STRU));
    if (TAF_NULL_PTR == pPara)
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    PS_MEM_SET(pPara,0x00,sizeof(TAF_SS_PROCESS_USS_REQ_STRU));

    /* ����<n> */
    if(0 != gastAtParaList[0].usParaLen)
    {
        if(2 != gastAtParaList[0].ulParaValue)
        {
            pPara->enCusdType    = (TAF_SS_CUSD_TYPE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
        }
    }
    else
    {
        pPara->enCusdType    = TAF_SS_CUSD_TYPE_DISABLE;
    }

    /* <n>: cancel session */
    if(2 == gastAtParaList[0].ulParaValue)
    {
        if(AT_SUCCESS == TAF_SsReleaseComplete(gastAtClientTab[ucIndex].usClientId, 0))
        {
            ulRet = AT_OK;

        }
        else
        {
            ulRet = AT_ERROR;
        }
    }
    else
    {
        /*  AT+CUSD=0ʱ��Ҳ��Ҫ��C�˷���Ϣ�������õ�C�˻ظ� */
        if(0 == gastAtParaList[1].usParaLen)
        {
            PS_MEM_SET(&(pPara->UssdStr), 0, sizeof(pPara->UssdStr));
        }
        else
        {

            PS_MEM_CPY(pPara->UssdStr.aucUssdStr,gastAtParaList[1].aucPara,gastAtParaList[1].usParaLen);
            pPara->UssdStr.usCnt = gastAtParaList[1].usParaLen;

            if (TAF_SS_UCS2 == DatacodingScheme)
            {
                if(AT_FAILURE == At_UnicodePrint2Unicode(pPara->UssdStr.aucUssdStr,&pPara->UssdStr.usCnt))
                {
                    PS_MEM_FREE(WUEPS_PID_AT, pPara);
                    return AT_CMS_INVALID_TEXT_MODE_PARAMETER;
                }
            }
        }
        /* ����<dcs> */
        pPara->DatacodingScheme = DatacodingScheme;

        /* ִ��������� */
        if(AT_SUCCESS == TAF_ProcessUnstructuredSSReq(gastAtClientTab[ucIndex].usClientId, 0, pPara))
        {
            /*  AT+CUSD=0ʱ��Ҳ��Ҫ��C�˷���Ϣ�������õ�C�˻ظ� */
            if(0 == gastAtParaList[1].usParaLen)
            {
                ulRet =  AT_OK;
            }
            else
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CUSD_REQ;

                /* �������������״̬ */
                ulRet =  AT_WAIT_ASYNC_RETURN;
            }
        }
        else
        {
            ulRet =  AT_ERROR;
        }

    }

    PS_MEM_FREE(WUEPS_PID_AT, pPara);
    return ulRet;
}
TAF_UINT32 At_SetCpwdPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32   i;
    /* ������� */
    if((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen) || (0 == gastAtParaList[2].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<fac> */
    switch(gastAtParaList[0].ulParaValue)
    {
    case AT_CLCK_P2_TYPE:
    case AT_CLCK_SC_TYPE:
        {
            TAF_PH_PIN_DATA_STRU stPinData;

            if((TAF_PH_PINCODELENMAX < gastAtParaList[1].usParaLen) || (TAF_PH_PINCODELENMAX < gastAtParaList[2].usParaLen)
             ||(TAF_PH_PINCODELENMIN > gastAtParaList[1].usParaLen) || (TAF_PH_PINCODELENMIN > gastAtParaList[2].usParaLen))
            {
                return AT_ERROR;
            }

            /* ��ʼ�� */
            PS_MEM_SET(&stPinData, 0xFF, sizeof(stPinData));

            /* ����<pin> */
            if(0 != gastAtParaList[1].usParaLen)
            {
                for(i=0; i<gastAtParaList[1].usParaLen; i++)
                {
                    if((gastAtParaList[1].aucPara[i] > '9' )||(gastAtParaList[1].aucPara[i] < '0'))
                    {
                        return AT_CME_INCORRECT_PARAMETERS;
                    }
                }

                PS_MEM_CPY((TAF_VOID*)stPinData.aucOldPin,(TAF_VOID*)gastAtParaList[1].aucPara,gastAtParaList[1].usParaLen);
            }

            /* ����<newpin> */
            if(0 != gastAtParaList[2].usParaLen)
            {
                for(i=0; i<gastAtParaList[2].usParaLen; i++)
                {
                    if((gastAtParaList[2].aucPara[i] > '9' )||(gastAtParaList[2].aucPara[i] < '0'))
                    {
                        return AT_CME_INCORRECT_PARAMETERS;
                    }
                }

                PS_MEM_CPY((TAF_VOID*)stPinData.aucNewPin,(TAF_VOID*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
            }
            /* ����PinType */
            if(AT_CLCK_P2_TYPE == gastAtParaList[0].ulParaValue)
            {
                stPinData.PinType = TAF_SIM_PIN2;
            }
            else
            {
                stPinData.PinType = TAF_SIM_PIN;
            }

            /* ����CmdType */
            stPinData.CmdType = TAF_PIN_CHANGE;

            /* ִ��������� */
            if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPWD_CHANGE_PIN;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        }

    case AT_CLCK_PS_TYPE:
        {
            TAF_ME_PERSONALISATION_DATA_STRU stMePersonalisationData;

            if((TAF_PH_PINCODELENMAX < gastAtParaList[1].usParaLen) || (TAF_PH_PINCODELENMAX < gastAtParaList[2].usParaLen))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ��ʼ�� */
            PS_MEM_SET(&stMePersonalisationData,0x00,sizeof(stMePersonalisationData));

            /* ����<oldpwd> */
            PS_MEM_CPY((VOS_VOID*)stMePersonalisationData.aucOldPwd,(VOS_VOID*)gastAtParaList[1].aucPara,gastAtParaList[1].usParaLen);

            /* ����<newpwd> */
            PS_MEM_CPY((VOS_CHAR*)stMePersonalisationData.aucNewPwd,(VOS_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);

            /* ����MePersonalType */
            stMePersonalisationData.MePersonalType = TAF_SIM_PERSONALISATION;

            /* ����CmdType */
            stMePersonalisationData.CmdType = TAF_ME_PERSONALISATION_PWD_CHANGE;

            /* ִ��������� */
            if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPWD_CHANGE_PIN;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        }


    default:
        {
            TAF_SS_REGPWD_REQ_STRU para;

            if((TAF_SS_MAX_PASSWORD_LEN < gastAtParaList[1].usParaLen) || (TAF_SS_MAX_PASSWORD_LEN < gastAtParaList[2].usParaLen))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            /* ��ʼ�� */
            PS_MEM_SET(&para,0x00,sizeof(para));

            /* ����<oldpwd> */
            PS_MEM_CPY((TAF_CHAR*)para.aucOldPwdStr,(TAF_CHAR*)gastAtParaList[1].aucPara,gastAtParaList[1].usParaLen);

            /* ����<newpwd> */
            PS_MEM_CPY((TAF_CHAR*)para.aucNewPwdStr,(TAF_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);

            /* ����<newpwd> */
            PS_MEM_CPY((TAF_CHAR*)para.aucNewPwdStrCnf,(TAF_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);

            /* ����SsCode */
            At_SsPrint2Code(&para.SsCode,(TAF_UINT8)gastAtParaList[0].ulParaValue);

            /* ִ��������� */
            if(AT_SUCCESS == TAF_RegisterPasswordReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPWD_SET;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        }
    }
}
/*****************************************************************************
 Prototype      : At_SetDialIGPara
 Description    : D...[I][G][;]
 Input          : ucIndex     --- �û�����
                  ucParaIndex --- ��������
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��21��
    �޸�����   : DSDA PHASE III

*****************************************************************************/
TAF_VOID At_SetDialIGPara(TAF_UINT8 ucIndex,TAF_UINT8 ucParaIndex,TAF_UINT8 *pClir, MN_CALL_CUG_CFG_STRU *pstCcug)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /*->A32D08138*/
    /* Ĭ�������ʹ��CCA���õ�Ĭ��ֵ */

    *pClir   = pstSsCtx->ucClirType;
    *pstCcug = pstSsCtx->stCcugCfg;
    /*<-A32D08138*/

    switch(gastAtParaList[ucParaIndex].aucPara[0])
    {
    case 'i':
        *pClir = MN_CALL_CLIR_SUPPRESS;
        break;

    case 'I':
        *pClir = MN_CALL_CLIR_INVOKE;
        break;

    case 'g':
    case 'G':
        pstCcug->bEnable = 1;
        break;

    default:
        break;
    }

    switch(gastAtParaList[ucParaIndex + 1].aucPara[0])
    {
    case 'g':
    case 'G':
        pstCcug->bEnable = 1;
        break;

    default:
        break;
    }
}

/*****************************************************************************
 �� �� ��  : At_SetDialGprsPara
 ��������  : GPRS���Ŵ�������
 �������  : TAF_UINT8 ucIndex  �û�����
             TAF_UINT8 ucCid    cid
             TAF_GPRS_ACTIVE_TYPE_UINT8 enActiveType   ��������
 �������  : ��
 �� �� ֵ  : TAF_UINT32 AT_XXX  --- ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005-04-19
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��22��
    �޸�����   : AT PROJECT NAS_EventReport -> AT_EventReport
                            OM_GreenChannel -> OM_AppGreenChannel
*****************************************************************************/
TAF_UINT32 At_SetDialGprsPara(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           ucCid,
    TAF_GPRS_ACTIVE_TYPE_UINT8          enActiveType
)
{
    TAF_UINT16 usPppId   = 0;
    VOS_UINT32 ulErrInfo;
    TAF_UINT8  aucEventInfo[4];

    /* ���м������ */
    if(TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE == enActiveType)    /* MT������PPP */
    {
        gastAtClientTab[ucIndex].ucCid = ucCid;   /* ���浱ǰָ����cid */

        if(AT_SUCCESS == Ppp_CreatePppReq(&usPppId))    /* TE��������PPP��MT������PPP */
        {
            /*EVENT-At_SetDialGprsPara: usPppId/index*/
            aucEventInfo[0] = (TAF_UINT8)(usPppId >> 8);
            aucEventInfo[1] = (TAF_UINT8)usPppId;
            aucEventInfo[2] = ucIndex;
            AT_EventReport(WUEPS_PID_AT, NAS_OM_EVENT_DCE_CREATE_PPP,
                           aucEventInfo, sizeof(aucEventInfo));

            gastAtPppIndexTab[usPppId] = ucIndex;       /* ��¼PPP id��Index�Ķ�Ӧ��ϵ */
            gastAtClientTab[ucIndex].usPppId = usPppId; /* ����PPP id */

            At_SetMode(ucIndex,AT_DATA_MODE,AT_PPP_DATA_MODE);   /* �л�ΪPPP����״̬ */

            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_PPP_CALL_SET;

            return AT_CONNECT;
        }
        else
        {
            ulErrInfo = TAF_OM_GREENCHANNEL_PS_CREATE_PPP_REQ_ERR;
            OM_AppGreenChannel(OM_GREEN_FUNC, TAF_OM_GREEN_CHANNEL_PS, (VOS_UINT8 *)&ulErrInfo, sizeof(ulErrInfo));
            return AT_ERROR;
        }
    }
    else
    {
        /* ����͸����PPPʵ�� */
        if (AT_SUCCESS != Ppp_CreateRawDataPppReq(&usPppId))
        {

            ulErrInfo = TAF_OM_GREENCHANNEL_PS_CREATE_RAW_DATA_PPP_REQ_ERR;
            OM_AppGreenChannel(OM_GREEN_FUNC, TAF_OM_GREEN_CHANNEL_PS, (VOS_UINT8 *)&ulErrInfo, sizeof(ulErrInfo));
            return AT_ERROR;
        }

        if ( VOS_OK != TAF_PS_PppDialOrig(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0,
                                          ucCid,
                                          VOS_NULL_PTR) )
        {
            PPP_RcvAtCtrlOperEvent(usPppId, PPP_AT_CTRL_REL_PPP_RAW_REQ);

            /*��PPP����HDLCȥʹ�ܲ���*/
            PPP_RcvAtCtrlOperEvent(usPppId, PPP_AT_CTRL_HDLC_DISABLE);
            return AT_ERROR;
        }

        gastAtPppIndexTab[usPppId]          = ucIndex;  /* ��¼PPP id��Index�Ķ�Ӧ��ϵ */
        gastAtClientTab[ucIndex].usPppId    = usPppId;  /* ����PPP id */

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_IP_CALL_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
}



TAF_UINT32 At_SetDial98Para(TAF_UINT8 ucIndex)
{
    TAF_ATD_PARA_STRU                   stAtdPara;

    /* ��ʼ�� */
    PS_MEM_SET(&stAtdPara, 0x00, sizeof(TAF_ATD_PARA_STRU));

    /* CID���� */
    if (0 != gastAtParaList[4].usParaLen)
    {
        if(AT_FAILURE == At_Auc2ul(gastAtParaList[4].aucPara,gastAtParaList[4].usParaLen,&gastAtParaList[4].ulParaValue))
        {
            return AT_ERROR;
        }

        if(gastAtParaList[4].ulParaValue > 0xFF)   /* ��Ҫ��飬������� */
        {
            return AT_ERROR;
        }

        /* ��ȡ��ǰ�û������CID */
        stAtdPara.ucCid = (VOS_UINT8)gastAtParaList[4].ulParaValue;
    }
    else
    {
        /* ����Ĭ��CID */
        stAtdPara.ucCid = AT_DIAL_DEFAULT_CID;
    }

    /* ��ȡGPRS�������� */
    if ( VOS_OK != TAF_PS_GetGprsActiveType(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0,
                                            &stAtdPara) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_GPRS_SET;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_SetDial99Para(VOS_UINT8 ucIndex)
{
    VOS_INT32                           lParaPPPFlg;
    VOS_INT32                           lParaNULLFlg;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucStar;
    VOS_UINT8                           ucL2pIndex;
    VOS_UINT8                           ucCidIndex;
    TAF_ATD_PARA_STRU                   stAtdPara;

    /* ��ʼ�� */
    ucTmp      = 0;
    ucStar     = 0;
    ucL2pIndex = 0;
    ucCidIndex = 0;
    PS_MEM_SET(&stAtdPara, 0x00, sizeof(TAF_ATD_PARA_STRU));

    /* ���������б� */
    for (ucTmp = 1; ucTmp < gucAtParaIndex; ucTmp++)
    {
        if ('*' == gastAtParaList[ucTmp].aucPara[0])
        {
            ucStar++;
        }
        else
        {
            switch (ucStar)
            {
                case 1:
                case 2:
                    break;

                case 3:
                    ucL2pIndex = ucTmp;
                    break;

                case 4:
                    ucCidIndex = ucTmp;
                    break;

                default:
                    return AT_ERROR;
            }
        }
    }

    /* ��ȡCID: ������CID����ʱ, ȡĬ��ֵ1 */
    if (0 != ucCidIndex)
    {
        if (AT_FAILURE == At_Auc2ul(gastAtParaList[ucCidIndex].aucPara,gastAtParaList[ucCidIndex].usParaLen,&gastAtParaList[ucCidIndex].ulParaValue))
        {
            return AT_ERROR;
        }

        /* ��Ҫ��飬������� */
        if (gastAtParaList[ucCidIndex].ulParaValue > 0xFF)
        {
            return AT_ERROR;
        }

        stAtdPara.ucCid = (VOS_UINT8)gastAtParaList[ucCidIndex].ulParaValue;
    }
    else
    {
        stAtdPara.ucCid = AT_DIAL_DEFAULT_CID;
    }

    /* ��ȡL2PЭ������: ���ݲ�֧�ֵ�Э������ */
    if (0 != ucL2pIndex)
    {
        lParaPPPFlg =  VOS_StrCmp((TAF_CHAR*)gastAtParaList[ucL2pIndex].aucPara,"1");
        lParaNULLFlg = VOS_StrCmp((TAF_CHAR*)gastAtParaList[ucL2pIndex].aucPara,"0");

        if ( (0 == VOS_StrCmp((TAF_CHAR*)gastAtParaList[ucL2pIndex].aucPara,"PPP"))
          || (0 == lParaPPPFlg) )
        {
            stAtdPara.bitOpL2p  = VOS_TRUE;
            stAtdPara.enL2p     = TAF_L2P_PPP;
        }
        else if ( (0 == VOS_StrCmp((TAF_CHAR*)gastAtParaList[ucL2pIndex].aucPara,"NULL"))
               || (0 == lParaNULLFlg) )
        {
            stAtdPara.bitOpL2p  = VOS_TRUE;
            stAtdPara.enL2p     = TAF_L2P_NULL;
        }
        else
        {
            ;
        }
    }
    else
    {
        ;
    }

    /* ��ȡGPRS�������� */
    if ( VOS_OK != TAF_PS_GetGprsActiveType(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0,
                                            &stAtdPara) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_GPRS_SET;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_FillCalledNumPara(
    VOS_UINT8                          *pucAtPara,
    VOS_UINT16                          usLen,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    VOS_UINT32                          ulRelt;

    /* �������ͼ�� */
    if ('+' == *pucAtPara)
    {
        /* ���ʺ���ĵ�һ���ַ�����Ҫ����,������Ϊ81���ַ� */
        if (usLen > (MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1))
        {
            return VOS_ERR;
        }

        *(pucAtPara + usLen) = '\0';
        pucAtPara  += 1;

        pstOrigParam->stDialNumber.enNumType
            = (MN_CALL_IS_EXIT | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);
    }
    else
    {
        /* ���ں����δ֪����������Ϊ80���ַ� */
        if (usLen > MN_CALL_MAX_CALLED_ASCII_NUM_LEN)
        {
            return VOS_ERR;
        }

        *(pucAtPara + usLen) = '\0';

        pstOrigParam->stDialNumber.enNumType
            = (MN_CALL_IS_EXIT | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    }

    ulRelt = AT_AsciiNumberToBcd((VOS_CHAR *)pucAtPara,
                                 pstOrigParam->stDialNumber.aucBcdNum,
                                 &pstOrigParam->stDialNumber.ucNumLen);

    if (MN_ERR_NO_ERROR != ulRelt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
TAF_UINT32 At_SetDialNumPara(TAF_UINT8 ucIndex,MN_CALL_TYPE_ENUM_U8 CallType)
{
    MN_CALL_ORIG_PARAM_STRU             stOrigParam;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /*Ŀǰ��Ϊ�ƶ���AT���������Ӧ��ֻҪ����һ����������м���*/

    /* ��ʼ�� */
    PS_MEM_SET(&stOrigParam,0x00,sizeof(stOrigParam));

    /* ����<dial_string> */
    if (VOS_OK !=  AT_FillCalledNumPara(gastAtParaList[1].aucPara,
                         gastAtParaList[1].usParaLen,
                         &stOrigParam))
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stOrigParam.enCallType = CallType;

    At_SetDialIGPara(ucIndex,2,&stOrigParam.enClirCfg,&stOrigParam.stCugCfg);

    stOrigParam.enCallMode = pstSsCtx->enCModType;

    stOrigParam.stDataCfg = pstSsCtx->stCbstDataCfg;

    /* ��������6�����нӿڣ���Ҫ��������I��G�Ĳ�������Ҫ�޸�D����ʵ�� */
    if(AT_SUCCESS == MN_CALL_Orig(gastAtClientTab[ucIndex].usClientId,
                                  0,
                                  &gastAtClientTab[ucIndex].AtCallInfo.CallId,
                                  &stOrigParam))
    {
        if(MN_CALL_TYPE_VOICE == CallType)
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;
        }
        else
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_DATA_CALL_SET;
        }
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }
}
/*****************************************************************************
 �� �� ��  : At_DialNumByIndexFromPb
 ��������  : �ӵ绰����ȡ����󲦺�
 �������  : VOS_UINT8 ucIndex
             SI_PB_EVENT_INFO_STRU  *pEvent
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��26��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_DialNumByIndexFromPb(VOS_UINT8              ucIndex,
                                            SI_PB_EVENT_INFO_STRU  *pEvent)
{

    /*���ӵ绰�������ĺ���д��gastAtParaList[1].aucPara*/
    VOS_MemCpy(&gastAtParaList[1].aucPara[0],
               pEvent->PBEvent.PBReadCnf.PBRecord.Number,
               pEvent->PBEvent.PBReadCnf.PBRecord.NumberLength);
    gastAtParaList[1].aucPara[pEvent->PBEvent.PBReadCnf.PBRecord.NumberLength] = '\0';
    gastAtParaList[1].usParaLen = pEvent->PBEvent.PBReadCnf.PBRecord.NumberLength;
    /* D[<dial_string>][I][G][;] */
    return At_SetDialNumPara(ucIndex,gastAtClientTab[ucIndex].AtCallInfo.CallType);
}

/*****************************************************************************
 Prototype      : At_SetDialVoiceIndexPara
 Description    : D><n>[I][G][;]
 Input          : ucIndex --- �û�����
                  CallType --- ��������
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetDialVoiceIndexPara(TAF_UINT8 ucIndex, MN_CALL_TYPE_ENUM_U8 enCallType)
{
    TAF_UINT32 uLIndex = 0;
    SI_PB_STORATE_TYPE  Storage = SI_PB_STORAGE_UNSPECIFIED;

    if(AT_FAILURE == At_Auc2ul(gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen,&uLIndex))
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].AtCallInfo.CallType = enCallType;

    At_SetDialIGPara(ucIndex,3,&gastAtClientTab[ucIndex].AtCallInfo.ClirInfo,&gastAtClientTab[ucIndex].AtCallInfo.CugMode);

    if ( AT_SUCCESS == SI_PB_Read( gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    Storage,
                                    (TAF_UINT16)uLIndex,
                                    (TAF_UINT16)uLIndex)
        )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_GET_NUMBER_BEFORE_CALL;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetDialVoiceNamePara
 Description    : D><name>[I][G][;]
 Input          : ucIndex --- �û�����
                  CallType --- ��������
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetDialVoiceNamePara(TAF_UINT8 ucIndex,MN_CALL_TYPE_ENUM_U8 CallType)
{
#if 0
    SI_PB_STORATE_TYPE      Storage = SI_PB_STORAGE_UNSPECIFIED;

    TAF_PB_SEARCH_TYPE  SearchType = TAF_PB_SEARCH_BY_NAME;
    TAF_PB_AlPHATAG_TYPE AlphaTagType = TAF_PB_ALPHATAG_TYPE_GSM;
#endif

    if(AT_FAILURE == At_CheckNumLen(SI_PB_ALPHATAG_MAX_LEN,gastAtParaList[2].usParaLen))
    {
        return AT_ERROR;
    }

    if(AT_FAILURE == At_CheckStringPara(&gastAtParaList[2]))
    {
        return AT_ERROR;
    }

    /* ����ucAlphaTagType */
    if(AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        /* AlphaTagType = TAF_PB_ALPHATAG_TYPE_UCS2; */
        if(AT_FAILURE == At_UnicodePrint2Unicode(gastAtParaList[2].aucPara,&gastAtParaList[2].usParaLen))
        {
            return AT_ERROR;
        }
    }

    gastAtClientTab[ucIndex].AtCallInfo.CallType = CallType;

    At_SetDialIGPara(ucIndex,3,&gastAtClientTab[ucIndex].AtCallInfo.ClirInfo,&gastAtClientTab[ucIndex].AtCallInfo.CugMode);

#if 0
    if ( AT_SUCCESS == Taf_PBSearch ( gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      Storage,
                                      SearchType,
                                      AlphaTagType,
                                      (TAF_UINT8)gastAtParaList[2].usParaLen,
                                      gastAtParaList[2].aucPara
                                     )
        )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_GET_NUMBER_BEFORE_CALL;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
#endif

    return AT_ERROR;
}

TAF_UINT32 At_SetDialVoiceMemPara(TAF_UINT8 ucIndex, MN_CALL_TYPE_ENUM_U8 CallType)
{
    TAF_UINT32 uLIndex = 0;
    SI_PB_STORATE_TYPE  Storage = SI_PB_STORAGE_UNSPECIFIED;

    if(AT_FAILURE == At_Auc2ul(gastAtParaList[3].aucPara,gastAtParaList[3].usParaLen,&uLIndex))
    {
        return AT_ERROR;
    }

    if(0 == VOS_StrCmp((TAF_CHAR*)"SM",(TAF_CHAR*)gastAtParaList[2].aucPara))
    {
        Storage = SI_PB_STORAGE_SM;
    }
    else
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].AtCallInfo.CallType = CallType;

    At_SetDialIGPara(ucIndex,4,&gastAtClientTab[ucIndex].AtCallInfo.ClirInfo,&gastAtClientTab[ucIndex].AtCallInfo.CugMode);

    if ( AT_SUCCESS == SI_PB_Read ( gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    Storage,
                                    (TAF_UINT16)uLIndex,
                                    (TAF_UINT16)uLIndex)
        )
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_GET_NUMBER_BEFORE_CALL;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_SetDMmiNumWithClirPara(
    TAF_UINT8                         ucIndex,
    MN_CALL_CLIR_CFG_ENUM_U8          enClirType,
    TAF_INT8                         *pcStrNum,
    TAF_UINT32                        ulStrLen
)
{
    MN_CALL_ORIG_PARAM_STRU             stOrigParam;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ���ȼ�� */
    if( (MN_CALL_MAX_BCD_NUM_LEN*2) < ulStrLen)
    {
        return AT_CME_DIAL_STRING_TOO_LONG;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stOrigParam,0x00,sizeof(stOrigParam));

    /* ����<dial_string> */
    if ('+' == pcStrNum[0])
    {
        stOrigParam.stDialNumber.enNumType
            = (0x80 | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);
        if (MN_ERR_NO_ERROR != AT_AsciiNumberToBcd((TAF_CHAR *)pcStrNum + 1,
                            stOrigParam.stDialNumber.aucBcdNum,
                            &stOrigParam.stDialNumber.ucNumLen))
        {
            AT_WARN_LOG("At_SetDMmiNumWithClirPara():AT_AsciiNumberToBcd fail");
        }
    }
    else
    {
        stOrigParam.stDialNumber.enNumType
            = (0x80 | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
        if (MN_ERR_NO_ERROR != AT_AsciiNumberToBcd((TAF_CHAR *)pcStrNum,
                            stOrigParam.stDialNumber.aucBcdNum,
                            &stOrigParam.stDialNumber.ucNumLen))
        {
            AT_WARN_LOG("At_SetDMmiNumWithClirPara():AT_AsciiNumberToBcd fail");
        }
    }

    stOrigParam.enCallType = MN_CALL_TYPE_VOICE;
    stOrigParam.enClirCfg  = enClirType;

    stOrigParam.enCallMode = pstSsCtx->enCModType;

    if(AT_SUCCESS == MN_CALL_Orig(gastAtClientTab[ucIndex].usClientId,
                                  0,
                                  &gastAtClientTab[ucIndex].AtCallInfo.CallId,
                                  &stOrigParam))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : At_SetDMmiPara
 ��������  : ����ATD����mmi�ִ�
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : AT_XXX  - ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��20��
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 At_SetDMmiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8                           pucPara[6];

    VOS_MemSet(pucPara, 0 ,sizeof(pucPara));
    gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1] = '\0';

    VOS_StrNCpy((TAF_CHAR *)pucPara, (TAF_CHAR*)gastAtParaList[0].aucPara, sizeof(pucPara) - 1);

    if ((VOS_OK == VOS_StrCmp((TAF_CHAR*)pucPara,"D*31#")))
    {
        return At_SetDMmiNumWithClirPara(ucIndex,
                                         MN_CALL_CLIR_SUPPRESS,
                                         (VOS_INT8*)(gastAtParaList[0].aucPara + VOS_StrLen("D*31#")),
                                         VOS_StrLen((VOS_CHAR *)gastAtParaList[0].aucPara) - VOS_StrLen("D*31#"));
    }
    else if (VOS_OK == VOS_StrCmp((TAF_CHAR*)pucPara,"d*31#"))
    {
        return At_SetDMmiNumWithClirPara(ucIndex,
                                         MN_CALL_CLIR_SUPPRESS,
                                         (VOS_INT8*)(gastAtParaList[0].aucPara + VOS_StrLen("d*31#")),
                                         VOS_StrLen((VOS_CHAR *)gastAtParaList[0].aucPara) - VOS_StrLen("d*31#"));
    }
    else if ((VOS_OK == VOS_StrCmp((TAF_CHAR*)pucPara,"D#31#")))
    {
        return At_SetDMmiNumWithClirPara(ucIndex,
                                         MN_CALL_CLIR_INVOKE,
                                         (VOS_INT8*)(gastAtParaList[0].aucPara + VOS_StrLen("D#31#")),
                                         VOS_StrLen((VOS_CHAR *)gastAtParaList[0].aucPara) - VOS_StrLen("D#31#"));
    }
    else if ((VOS_OK == VOS_StrCmp((TAF_CHAR*)pucPara,"d#31#")))
    {
        return At_SetDMmiNumWithClirPara(ucIndex,
                                         MN_CALL_CLIR_INVOKE,
                                         (VOS_INT8*)(gastAtParaList[0].aucPara + VOS_StrLen("d#31#")),
                                         VOS_StrLen((VOS_CHAR *)gastAtParaList[0].aucPara) - VOS_StrLen("d#31#"));
    }
    else
    {
        /* D*752#+436644101453; */
        gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1] = 0;
        gastAtParaList[0].usParaLen--;
        return AT_ERROR;
    }

}
/*****************************************************************************
 �� �� ��  : At_CheckAtDPin
 ��������  : ����ʱ����Ƿ�����pin��
 �������  : ��
 �������  : ��
 �� �� ֵ  :�ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��12��24��
    �޸�����   : DSDA Phase II
*****************************************************************************/
TAF_UINT32  At_CheckAtDPin(VOS_UINT8 ucIndex)
{
    TAF_UINT32                          ulRst;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulGetModemIdRslt)
    {
        AT_ERR_LOG("At_CheckAtDPin:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);


    /*SIM��״̬�ж�*/
    switch (pstUsimInfoCtx->enCardStatus)
    {
        case USIMM_CARD_SERVIC_AVAILABLE:
            ulRst = AT_SUCCESS;
            break;
        case USIMM_CARD_SERVIC_SIM_PIN:
            ulRst = AT_CME_SIM_PIN_REQUIRED;
            break;
        case USIMM_CARD_SERVIC_SIM_PUK:
            ulRst = AT_CME_SIM_PUK_REQUIRED;
            break;
        case USIMM_CARD_SERVIC_UNAVAILABLE:
        case USIMM_CARD_SERVIC_NET_LCOK:
        case USIMM_CARD_SERVIC_IMSI_LCOK:
            ulRst = AT_CME_SIM_FAILURE;
            break;
        case USIMM_CARD_SERVIC_ABSENT:
            ulRst = AT_CME_SIM_NOT_INSERTED;
            break;
        default:
            ulRst = AT_ERROR;
            break;
    }

    return ulRst;
}
TAF_UINT32  At_PsDPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32    ulRst;

    ulRst = At_CheckAtDPin(ucIndex);
    if (AT_SUCCESS != ulRst)
    {
        return ulRst;
    }

    if(AT_SUCCESS == At_CheckSemicolon(gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1])) /* ������ֺ�,D*752#+436644101453; */
    {

        /* D*752#+436644101453; */
        gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1] = 0;
        gastAtParaList[0].usParaLen--;
    }
    else if('#' == gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1])
    {
        if(0 == VOS_StrNiCmp((TAF_CHAR*)gastAtParaList[2].aucPara,"98", gastAtParaList[2].usParaLen))
        {
            /* D*<GPRS_SC_IP>[*<cid>[,<cid>]]# */
            return At_SetDial98Para(ucIndex);
        }
        else if(0 == VOS_StrNiCmp((TAF_CHAR*)gastAtParaList[2].aucPara,"99", gastAtParaList[2].usParaLen))
        {
            /* D*<GPRS_SC>[*[<called_address>][*[<L2P>][*[<cid>]]]]# */
            return At_SetDial99Para(ucIndex);
        }
        else
        {

        }
    }
    else
    {

    }
    return AT_ERROR;

}

VOS_VOID At_CheckDialStrPara(VOS_VOID)
{
    if (AT_SUCCESS == At_CheckMmiString(gastAtParaList[0].aucPara,gastAtParaList[0].usParaLen))
    {
        if(';' != gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1])
        {
            PS_MEM_CPY(gastAtParaList[1].aucPara, &gastAtParaList[0].aucPara[1], gastAtParaList[0].usParaLen - 1);
            gastAtParaList[1].usParaLen = gastAtParaList[0].usParaLen - 1;
        }
        else
        {
            PS_MEM_CPY(gastAtParaList[1].aucPara, &gastAtParaList[0].aucPara[1], gastAtParaList[0].usParaLen - 2);
            gastAtParaList[1].usParaLen = gastAtParaList[0].usParaLen - 2;
        }
    }

    return;
}


VOS_UINT8 At_JudgeIfIsPsCall(VOS_VOID)
{
    VOS_UINT8                           ucPsCallFlg;

    if (AT_CheckStrStartWith(&gastAtParaList[0].aucPara[1], (VOS_UINT8 *)"*98"))
    {
        ucPsCallFlg = VOS_TRUE;
    }
    else if (AT_CheckStrStartWith(&gastAtParaList[0].aucPara[1], (VOS_UINT8 *)"*99"))
    {
        ucPsCallFlg = VOS_TRUE;
    }
    else
    {
        ucPsCallFlg = VOS_FALSE;
    }

    return ucPsCallFlg;
}

TAF_UINT32 At_SetDPara(TAF_UINT8 ucIndex)
{
    /* cS call */
    if(VOS_TRUE != At_JudgeIfIsPsCall())
    {
        MN_CALL_TYPE_ENUM_U8 CallType = MN_CALL_TYPE_VOICE;

        g_ucDtrDownFlag = VOS_FALSE;

        if(';' != gastAtParaList[0].aucPara[gastAtParaList[0].usParaLen - 1])
        {
            CallType = MN_CALL_TYPE_VIDEO;
        }

        if('>' == gastAtParaList[1].aucPara[0])
        {
            if(('A' <= gastAtParaList[2].aucPara[0]) && (gastAtParaList[2].aucPara[0] <= 'Z'))
            {
                /* D>mem<n>[I][G][;] */
                return At_SetDialVoiceMemPara(ucIndex,CallType);
            }
            else if(('0' <= gastAtParaList[2].aucPara[0]) && (gastAtParaList[2].aucPara[0] <= '9'))
            {
                /* D><n>[I][G][;] */
                return At_SetDialVoiceIndexPara(ucIndex,CallType);
            }
            else
            {
                /* D><name>[I][G][;] */
                return At_SetDialVoiceNamePara(ucIndex,CallType);
            }
        }
        else
        {
            /* D[<dial_string>][I][G][;] */
            return At_SetDialNumPara(ucIndex,CallType);
        }
    }
    else
    {
        return At_PsDPara(ucIndex);
    }

}
TAF_UINT32 At_SetAPara(TAF_UINT8 ucIndex)
{
    MN_CALL_SUPS_PARAM_STRU   stCallMgmtParam;
    VOS_UINT32                ulTimerId;

    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT8                           ucTmp;
    VOS_UINT32                          ulRlst;
    TAFAGERNT_MN_CALL_INFO_STRU         astCallInfos[MN_CALL_MAX_NUM];
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);


    PS_MEM_SET(astCallInfos, 0x00, sizeof(astCallInfos));


    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


#ifndef DMT
    /*��ͬ��API��ȡͨ����Ϣ*/
    ulRlst = TAF_AGENT_GetCallInfoReq(gastAtClientTab[ucIndex].usClientId,
                                      &ucNumOfCalls,
                                      astCallInfos);

    if (VOS_OK != ulRlst)
    {
        return AT_ERROR;
    }

    if (0 == ucNumOfCalls)
    {
        return AT_NO_CARRIER;
    }

    for (ucTmp = 0; ucTmp < ucNumOfCalls; ucTmp++)
    {
        /*�������Զ��������������������Ѿ�����incoming̬���ٴ���ATA����������ok*/
        if ((MN_CALL_S_INCOMING == astCallInfos[ucTmp].enCallState)
             && (0 != pstCcCtx->stS0TimeInfo.ucS0TimerLen)
             && (TAF_FALSE == pstCcCtx->stS0TimeInfo.bTimerStart))
        {
            return AT_OK;
        }
        /*�������Զ��������������������Ѿ����ڷ�incoming̬���ٴ���ATA����������error*/
        else if ((0 != pstCcCtx->stS0TimeInfo.ucS0TimerLen)
              && (TAF_FALSE == pstCcCtx->stS0TimeInfo.bTimerStart))
        {
            return AT_NO_CARRIER;
        }
        /* �����Ѿ���active״̬���յ�ataֱ�ӻظ�ok */
        else if (MN_CALL_S_ACTIVE == astCallInfos[ucTmp].enCallState)
        {
            return AT_OK;
        }
        else
        {
        }
    }
#endif


    PS_MEM_SET(&stCallMgmtParam, 0, sizeof(stCallMgmtParam));
    stCallMgmtParam.enCallSupsCmd = MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH;

    if(AT_SUCCESS == MN_CALL_Sups(gastAtClientTab[ucIndex].usClientId, 0, &stCallMgmtParam))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_A_SET;
        if (TAF_TRUE == pstCcCtx->stS0TimeInfo.bTimerStart)
        {
            ulTimerId = pstCcCtx->stS0TimeInfo.ulTimerName;

            AT_StopRelTimer(ulTimerId, &(pstCcCtx->stS0TimeInfo.s0Timer));
            pstCcCtx->stS0TimeInfo.bTimerStart = TAF_FALSE;
            pstCcCtx->stS0TimeInfo.ulTimerName = 0;
        }
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_NO_CARRIER;
    }


}


VOS_UINT32 AT_MODEM_HangupCall(VOS_UINT8 ucIndex)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstLineCtrl = AT_GetUartLineCtrlInfo();

    /* ONLINE-COMMANDģʽ��, ��Ҫ�Ͽ�PPP�������� */
    if (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        /* ���ڴ���PPP�Ͽ�����, ֱ�Ӽ̳�, ���������������ΪAT_CMD_H_PS_SET */
        if (AT_CMD_PS_DATA_CALL_END_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;
            ulRslt = AT_WAIT_ASYNC_RETURN;
        }
        /* ���ڵȴ�PPP���ͷ���Ӧ, ֱ���ͷ�, ����OK */
        else if (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);
            At_FormatResultData(ucIndex, AT_OK);

            if (AT_UART_DCD_MODE_CONNECT_ON == pstLineCtrl->enDcdMode)
            {
                AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
            }

            ulRslt = AT_SUCCESS;
        }
        else
        {
            (VOS_VOID)TAF_PS_CallEnd(WUEPS_PID_AT,
									 gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     gastAtClientTab[ucIndex].ucCid);

            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_PS_SET;
            ulRslt = AT_WAIT_ASYNC_RETURN;
        }
    }
    /* ����ģʽ��, Ĭ��ֱ�ӷ���OK */
    else
    {
        ulRslt = AT_OK;
    }

    return ulRslt;
}


VOS_UINT32 At_SetHPara(VOS_UINT8 ucIndex)
{
    MN_CALL_SUPS_PARAM_STRU             stCallMgmtParam;

    /* ɾ��ͨ������ģʽ��ʶ����ֱ�ӷ���OK�Ĵ��� */

    /*��Modem�ڽ������⴦��: �յ�ATHֱ�ӷ���OK��
      ��ʹModem�ڷ��������Ҳ��ִ�йҶϲ���*/
    if ((AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
     && (AT_CLIENT_USED == gastAtClientTab[ucIndex].ucUsed))
    {
        return AT_OK;
    }

    /* ����ͨ��ģʽ�ж�:
     * (1) ONLINE-COMMANDģʽ - �Ͽ���ǰͨ����PPP��������
     * (2) COMMANDģʽ        - ֱ�ӷ���OK
     */
    if (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType)
    {
        return AT_MODEM_HangupCall(ucIndex);
    }

    /*����Ŀǰ��ʱ��֧�����ݺ��������л�����Ϊ�ƶ�Ҳ��ʱû������������
      ����������£�ATH��ͬ��CHUP�Ĺ���*/
    PS_MEM_SET(&stCallMgmtParam, 0, sizeof(stCallMgmtParam));
    stCallMgmtParam.enCallSupsCmd = MN_CALL_SUPS_CMD_REL_ALL_CALL;
    if(AT_SUCCESS == MN_CALL_Sups(gastAtClientTab[ucIndex].usClientId, 0, &stCallMgmtParam))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_H_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_SetEPara
 Description    : E[<value>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetEPara(TAF_UINT8 ucIndex)
{
    if(0 != gastAtParaList[0].usParaLen)
    {
        gucAtEType = (AT_CMD_ECHO_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        gucAtEType = AT_E_ECHO_CMD;
    }
    return AT_OK;
}

TAF_UINT32 At_SetVPara(TAF_UINT8 ucIndex)
{
    if(0 != gastAtParaList[0].usParaLen)
    {
        gucAtVType = (AT_V_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        gucAtVType = AT_V_BREVITE_TYPE;
    }
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetTPara
 Description    : T
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetTPara(TAF_UINT8 ucIndex)
{
    /* �ο�Q��ʵ��:This commands will have no effect in our code*/
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetPPara
 Description    : P
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetPPara(TAF_UINT8 ucIndex)
{
    /* �ο�Q��ʵ��:This commands will have no effect in our code*/
    return AT_OK;
}
TAF_UINT32 At_SetXPara(TAF_UINT8 ucIndex)
{
    if(0 != gastAtParaList[0].usParaLen)
    {
        gucAtXType = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        gucAtXType = 0;
    }
    return AT_OK;
}
TAF_UINT32 At_SetZPara(TAF_UINT8 ucIndex)
{
    TAF_AT_TZ_STRU                      stTz;
    VOS_CHAR                            acTzStr[AT_SETZ_LEN+1];

    VOS_UINT16                          usLength;
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_ATSETZ_RET_VALUE, &stTz,
                             AT_SETZ_LEN))
        {
            PS_MEM_CPY(acTzStr, stTz.acTz, AT_SETZ_LEN);
            acTzStr[AT_SETZ_LEN] = 0;
            if ( VOS_StrLen(acTzStr) > 0 )
            {
                usLength  = 0;
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                 "%s",gaucAtCrLf);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s",acTzStr);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                                 (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                 "%s",gaucAtCrLf);

                At_SendResultData((VOS_UINT8)ucIndex,pgucAtSndCodeAddr,usLength);

                return AT_SUCCESS;
            }
        }
    }

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetQPara
 Description    : Q[value]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-06
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetQPara(TAF_UINT8 ucIndex)
{
    if(0 != gastAtParaList[0].usParaLen)
    {
        gucAtQType = (AT_CMD_ECHO_TYPE)gastAtParaList[0].ulParaValue;
    }
    else
    {
        gucAtQType = 0;
    }
    return AT_OK;
}


VOS_UINT32 At_SetAmpCPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_UART_DCD_MODE_ENUM_UINT8         enDcdMode;

    pstUartCtx = AT_GetUartCtxAddr();

    /* ֻ֧��UART�˿��·� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    /* ������� */
    if (0 != gastAtParaList[0].usParaLen)
    {
        if ((0 != gastAtParaList[0].ulParaValue)
         && (1 != gastAtParaList[0].ulParaValue))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        enDcdMode = (AT_UART_DCD_MODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        /* AT&C ��Ч�� AT&C1 */
        enDcdMode = AT_UART_DEFAULT_DCD_MODE;
    }

    /* ����DCD Line Mode�������� */
    pstUartCtx->stLineCtrl.enDcdMode = enDcdMode;

    /* DCD�ܽŲ��� */
    if(AT_UART_DCD_MODE_ALWAYS_ON == enDcdMode)
    {
        AT_CtrlDCD(ucIndex, AT_IO_LEVEL_HIGH);
    }
    else
    {
        if (AT_CMD_MODE == gastAtClientTab[ucIndex].Mode)
        {
            AT_CtrlDCD(ucIndex, AT_IO_LEVEL_LOW);
        }
    }

    return AT_OK;
}
VOS_UINT32 At_SetAmpDPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_UART_DTR_MODE_ENUM_UINT8         enDtrMode;

    pstUartCtx = AT_GetUartCtxAddr();

    /* ֻ֧��UART�˿��·� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    /* ������� */
    if (0 != gastAtParaList[0].usParaLen)
    {
        enDtrMode = (AT_UART_DTR_MODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        /* AT&D ��Ч�� AT&D2 */
        enDtrMode = AT_UART_DEFAULT_DTR_MODE;
    }

    /* ����DTR Line Mode�������� */
    pstUartCtx->stLineCtrl.enDtrMode = enDtrMode;

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_UINT32 At_SetAmpSPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    AT_UART_DSR_MODE_ENUM_UINT8         enDsrMode;
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel;

    pstUartCtx = AT_GetUartCtxAddr();

    /* ֻ֧��UART�˿��·� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    /* ������� */
    if (0 != gastAtParaList[0].usParaLen)
    {
        enDsrMode = (AT_UART_DSR_MODE_ENUM_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        /* AT&S ��Ч�� AT&S0 */
        enDsrMode = AT_UART_DEFAULT_DSR_MODE;
    }

    /* ����DSR �ܽ��ź� */
    enIoLevel = (AT_UART_DSR_MODE_ALWAYS_ON == enDsrMode) ? AT_IO_LEVEL_HIGH : AT_IO_LEVEL_LOW;
    AT_CtrlDSR(ucIndex, enIoLevel);

    /* ����DSR Line Mode��������*/
    pstUartCtx->stLineCtrl.enDsrMode = enDsrMode;

    return AT_OK;
}
#endif
TAF_UINT32 At_SetFPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    /* ��if 0�Ĵ���Ϊ�ձ���Ӫ�̵Ķ������󣬻ָ�8229��8265����NV�������Ҫ��������ˣ����ǵ��������п�����Ҫ�����󣬾���#if 0�ر��ˡ�*/
#if 0
    /*NV4102���������ͣ�16bit unsigned [3]*/
    VOS_UINT16                          ausSptBand[3];
    VOS_UINT32                          ulSptBandLen;
    /*NV8229*/
    NVIM_UE_SUPPORT_FREQ_BAND_STRU      stUserSetFreqBand;
    /*NV8265���������ͣ�64bit unsigned*/
    AT_NV_User_Set_Freq_Band64_STRU     stBand64;
#endif

    /*��ΪMODEN���Ż��·������������moden�ڲ�����NV�ָ���ֱ�ӷ���OK*/
    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        return AT_OK;
    }
    if ( VOS_TRUE == g_bSetFlg )
    {
        return AT_OK;
    }

    /* DPM_SleepDisable(DPM_SLEEP_NV); */


    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_NVRESTORE_MANU_DEFAULT_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_F_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

#if 0
    /*��Ҫ���»ָ�Ƶ����ص�NV:
    ��ȡNV��NV_RF_BAND(NV ID:4102)������ӦƵ����Ϣд��NV��Support_Freqbands(NV ID:8229),
    ��NV��UserSetFreqbands(NV ID:8265)������������Ϊ0x3FFFFFFF.
    */
    /*��ȡNV4102��ȡƵ����Ϣ*/
    NV_GetLength(en_NV_Item_UMTS_BAND, &ulSptBandLen);

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_UMTS_BAND,ausSptBand,ulSptBandLen);

    if ( NV_OK != ulRet )
    {
        return AT_ERROR;
    }

    /*��Ƶ����Ϣд��NV8229��Ӧ����(ǰ�ĸ��ֽ�)*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Support_Freqbands,
                    &stUserSetFreqBand, sizeof(stUserSetFreqBand));

    if ( NV_OK != ulRet )
    {
        return AT_ERROR;
    }

    stUserSetFreqBand.usWcdmaBand = ausSptBand[0];
    stUserSetFreqBand.usGsmBand   = ausSptBand[1];

    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_Support_Freqbands,
                          &(stUserSetFreqBand),
                          sizeof(stUserSetFreqBand));

    if ( NV_OK != ulRet )
    {
        return AT_ERROR;
    }

    /*��NV8265��ֵ����Ϊ0x3FFFFFFF*/
    stBand64.ulBandHigh = 0;
    stBand64.ulBandLow  = 0x3FFFFFFF;

    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_User_Set_Freqbands,
                          &stBand64,
                          sizeof(stBand64));

    if ( NV_OK != ulRet )
    {
        return AT_ERROR;
    }
#endif

}
TAF_UINT32 At_SetS0Para(TAF_UINT8 ucIndex)
{
    TAF_CCA_TELE_PARA_STRU              stTimeInfo;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    enModemId = MODEM_ID_0;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ɾ��ͨ������ģʽ��ʶ����ֱ�ӷ���OK�Ĵ��� */

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("At_SetS0Para: Get modem id fail.");
        return AT_ERROR;
    }

    pstCcCtx = AT_GetModemCcCtxAddrFromModemId(enModemId);

    pstCcCtx->stS0TimeInfo.ucS0TimerLen = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    pstCcCtx->stS0TimeInfo.usClientId   = gastAtClientTab[ucIndex].usClientId;

    PS_MEM_SET(&stTimeInfo, 0x00, sizeof(stTimeInfo));

    if (NV_OK == NV_ReadEx(enModemId, en_NV_Item_CCA_TelePara, &stTimeInfo, sizeof(TAF_CCA_TELE_PARA_STRU)))
    {
        if ( stTimeInfo.ucS0TimerLen == pstCcCtx->stS0TimeInfo.ucS0TimerLen )
        {
            AT_INFO_LOG("At_SetS0Para():The content to write is same as NV's");
            return AT_OK;
        }
    }
    stTimeInfo.ucS0TimerLen = pstCcCtx->stS0TimeInfo.ucS0TimerLen;
    if (NV_OK != NV_WriteEx(enModemId, en_NV_Item_CCA_TelePara, &stTimeInfo, sizeof(TAF_CCA_TELE_PARA_STRU)))
    {
        return AT_ERROR;
    }

    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetS3Para
 Description    : S3=[<value>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetS3Para(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucAtS3 = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucAtS3 = 13;
    }
    gaucAtCrLf[0] = ucAtS3;
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetS4Para
 Description    : S4=[<value>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetS4Para(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucAtS4 = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucAtS4 = 10;
    }
    gaucAtCrLf[1] = ucAtS4;
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetS5Para
 Description    : S5=[<value>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetS5Para(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucAtS5 = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucAtS5 = 8;
    }
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetS6Para
 Description    : S6=[<value>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetS6Para(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        ucAtS6 = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        /* refer to V.250:
           Recommended default setting
           2       Wait two seconds before blind dialling
         */
        ucAtS6 = 2;
    }
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_SetS7Para
 Description    : S7=[<value>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetS7Para(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*
      refer to V.250:
      S7:Number of seconds in which connection must be established or call will be disconnected
     */
    if(0 != gastAtParaList[0].usParaLen)
    {
        ucAtS7 = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        /* �ο�Qʵ�֣�Ĭ��ֵ��дΪ50 */
        ucAtS7 = 50;
    }
    return AT_OK;
}
VOS_VOID AT_SetDefaultRatPrioList(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_PH_RAT_ORDER_STRU              *pstSysCfgRatOrder,
    VOS_UINT8                           ucUserSptLteFlag
)
{
    VOS_UINT8                           ucUserRatNum;

    ucUserRatNum = 0;

#if(FEATURE_ON == FEATURE_LTE)
    /* ��ǰ�����Ƿ�֧��LTE */
    if (VOS_TRUE == ucUserSptLteFlag)
    {
        /* ƽ̨֧��LTE */
        if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE))
        {
             pstSysCfgRatOrder->aenRatOrder[ucUserRatNum] = TAF_PH_RAT_LTE;
             ucUserRatNum++;
        }
    }
#endif

    /* ƽ̨֧��WCDMA */
    if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_WCDMA))
    {
         pstSysCfgRatOrder->aenRatOrder[ucUserRatNum] = TAF_PH_RAT_WCDMA;
         ucUserRatNum++;
    }

    /* ƽ̨֧��GSM */
    if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_GSM))
    {
         pstSysCfgRatOrder->aenRatOrder[ucUserRatNum] = TAF_PH_RAT_GSM;
         ucUserRatNum++;
    }

    pstSysCfgRatOrder->ucRatOrderNum = ucUserRatNum;
    return;
}


VOS_VOID AT_GetGuAccessPrioNvim (
    MODEM_ID_ENUM_UINT16                enModemId,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8      *penAcqorder
)
{
    NAS_MMA_NVIM_ACCESS_MODE_STRU        stAccessMode;
    VOS_UINT32                           ulLength;

    ulLength = 0;

    PS_MEM_SET(&stAccessMode, 0x00, sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU));

    NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId,
                            en_NV_Item_MMA_AccessMode ,
                            &stAccessMode,
                            ulLength))

    {
        *penAcqorder = AT_SYSCFG_RAT_PRIO_AUTO;
        return ;
    }

    *penAcqorder = stAccessMode.aucAccessMode[1];
}



VOS_VOID AT_GetRatOrderNvim(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_PH_RAT_ORDER_STRU              *pstSysCfgRatOrder,
    VOS_UINT8                           ucUserSptLteFlag
)
{
    TAF_PH_NVIM_RAT_ORDER_STRU          stPrioRatList;
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;
    ucIndex = 0;


    PS_MEM_SET(&stPrioRatList, 0x00, sizeof(stPrioRatList));


    /* ��en_NV_Item_RAT_PRIO_LIST����ȡ��ǰ��stSysCfgRatOrder */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_RAT_PRIO_LIST, &stPrioRatList, sizeof(stPrioRatList)))
    {
        AT_SetDefaultRatPrioList(enModemId, pstSysCfgRatOrder, ucUserSptLteFlag);
        return;
    }

#if(FEATURE_ON == FEATURE_LTE)
    /* �жϽ��뼼�������Ƿ���Ч */
    if ((stPrioRatList.ucRatOrderNum > TAF_PH_MAX_GUL_RAT_NUM)
     || (0 == stPrioRatList.ucRatOrderNum))
    {
        AT_SetDefaultRatPrioList(enModemId, pstSysCfgRatOrder, ucUserSptLteFlag);
        return;
    }

    for (i = 0; i < stPrioRatList.ucRatOrderNum; i++)
    {
        pstSysCfgRatOrder->aenRatOrder[ucIndex] = stPrioRatList.aenRatOrder[i];
        ucIndex++;
    }

    pstSysCfgRatOrder->ucRatOrderNum = ucIndex;

#else
    /* �жϽ��뼼�������Ƿ���Ч */
    if ((stPrioRatList.ucRatOrderNum > TAF_PH_MAX_GU_RAT_NUM)
     || (0 == stPrioRatList.ucRatOrderNum))
    {
        AT_SetDefaultRatPrioList(enModemId, pstSysCfgRatOrder, ucUserSptLteFlag);
        return;
    }

    /* ��ȡGU�Ľ������ȼ� */
    for (i = 0; i < stPrioRatList.ucRatOrderNum; i++)
    {
        if ( (TAF_PH_RAT_WCDMA == stPrioRatList.aenRatOrder[i])
          || (TAF_PH_RAT_GSM   == stPrioRatList.aenRatOrder[i]) )
        {
            pstSysCfgRatOrder->aenRatOrder[ucIndex] = stPrioRatList.aenRatOrder[i];
            ucIndex++;
        }
    }
    pstSysCfgRatOrder->ucRatOrderNum = ucIndex;

#endif

    return;
}


VOS_UINT32 AT_IsSupportGMode(
    TAF_PH_RAT_ORDER_STRU              *pstRatOrder
)
{
    VOS_UINT32                          i;
    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        if (TAF_PH_RAT_GSM == pstRatOrder->aenRatOrder[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 AT_IsSupportLMode(
    TAF_PH_RAT_ORDER_STRU              *pstRatOrder
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        if (TAF_PH_RAT_LTE == pstRatOrder->aenRatOrder[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 AT_IsSupportWMode(
    TAF_PH_RAT_ORDER_STRU              *pstRatOrder
)
{
    VOS_UINT32                          i;

    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        if (TAF_PH_RAT_WCDMA == pstRatOrder->aenRatOrder[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 AT_ConvertCpamRatOrderPara(
    VOS_UINT8                           ucClientId,
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     enMode,
    MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8     enAcqorder,
    TAF_PH_RAT_ORDER_STRU              *pstRatOrder,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8      *penSyscfgRatPrio
)
{
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8       enNvimRatPrio;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRst;

    enModemId = MODEM_ID_0;

    ulRst = AT_GetModemIdFromClient(ucClientId, &enModemId);
    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG1("AT_ConvertCpamRatOrderPara:Get ModemID From ClientID fail,ClientID=%d", ucClientId);
        return AT_ERROR;
    }

    /* ����������ȼ����ı���Ĭ�ϴ�NVIM�л�ȡ */
    /* ����NVIM�еĽ������ȼ���CPAM�����õĲ�һ����Ҫת��һ�� */
    if ( MN_MMA_CPAM_RAT_PRIO_NO_CHANGE == enAcqorder )
    {
        AT_GetGuAccessPrioNvim(enModemId, &enNvimRatPrio);
        *penSyscfgRatPrio = enNvimRatPrio;
    }
    else if ( MN_MMA_CPAM_RAT_PRIO_GSM == enAcqorder )
    {
        *penSyscfgRatPrio = AT_SYSCFG_RAT_PRIO_GSM;
    }
    else
    {
        *penSyscfgRatPrio = AT_SYSCFG_RAT_PRIO_WCDMA;
    }



    switch (enMode)
    {
        case MN_MMA_CPAM_RAT_TYPE_WCDMA_GSM:
            if (AT_SYSCFG_RAT_PRIO_GSM == *penSyscfgRatPrio)
            {
                /* GSM���� */
                pstRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
                pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_GSM;
                pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_WCDMA;
                pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            }
            else
            {
                /* WCDMA���� */
                pstRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
                pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_WCDMA;
                pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_GSM;
                pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            }

            break;

        case MN_MMA_CPAM_RAT_TYPE_GSM:
            /* G��ģ */
            pstRatOrder->ucRatOrderNum = 1;
            pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_GSM;
            pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_BUTT;
            pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            break;

        case MN_MMA_CPAM_RAT_TYPE_WCDMA:
            /* W��ģ */
            pstRatOrder->ucRatOrderNum = 1;
            pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_WCDMA;
            pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_BUTT;
            pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            break;

        case MN_MMA_CPAM_RAT_TYPE_NOCHANGE:
            AT_GetRatOrderNvim(enModemId, pstRatOrder, VOS_FALSE);
            AT_GetOnlyGURatOrder(pstRatOrder);

            if (TAF_PH_MAX_GU_RAT_NUM == pstRatOrder->ucRatOrderNum)
            {
                if (AT_SYSCFG_RAT_PRIO_WCDMA == *penSyscfgRatPrio)
                {
                    pstRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
                    pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_WCDMA;
                    pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_GSM;
                    pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
                }
                else if (AT_SYSCFG_RAT_PRIO_GSM == *penSyscfgRatPrio)
                {
                    pstRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
                    pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_GSM;
                    pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_WCDMA;
                    pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
                }
                else
                {
                }

            }

            /* ԭ��ģ���迼�ǽ������ȼ� */

            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;

    }

    return AT_OK;

}
VOS_UINT32 At_SetCpamPara(VOS_UINT8 ucIndex)
{
    TAF_PH_SYS_CFG_EX_STRU              stSysCfgSetPara;
    VOS_UINT32                          ulRst;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    ulRst = AT_OK;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 0 == gastAtParaList[0].usParaLen )
    {
        gastAtParaList[0].ulParaValue = MN_MMA_CPAM_RAT_TYPE_NOCHANGE;
    }


    if ( 0 == gastAtParaList[1].usParaLen )
    {
        gastAtParaList[1].ulParaValue = MN_MMA_CPAM_RAT_PRIO_NO_CHANGE;
    }



    stSysCfgSetPara.ucCmdType = TAF_PH_CMD_SET;


    ulRst = AT_ConvertCpamRatOrderPara(ucIndex,
                                       (VOS_UINT8)gastAtParaList[0].ulParaValue,
                                       (VOS_UINT8)gastAtParaList[1].ulParaValue,
                                       &stSysCfgSetPara.stRatOrder,
                                       &stSysCfgSetPara.enUserPrio);

    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* stSysCfgSetPara����������ֵ */
    if (AT_ROAM_FEATURE_ON == pstNetCtx->ucRoamFeature)
    {
        stSysCfgSetPara.ucRoam = TAF_PH_ROAM_UNCHANGE;
    }
    else
    {
        stSysCfgSetPara.ucRoam = AT_ROAM_FEATURE_OFF_NOCHANGE;
    }
    stSysCfgSetPara.ucSrvDomain         = TAF_PH_SERVICE_NOCHANGE;
    stSysCfgSetPara.stGuBand.ulBandLow  = TAF_PH_BAND_NO_CHANGE;
    stSysCfgSetPara.stGuBand.ulBandHigh = 0;
    stSysCfgSetPara.stLBand.ulBandLow   = TAF_PH_BAND_NO_CHANGE;
    stSysCfgSetPara.stLBand.ulBandHigh  = 0;

    /* ִ��������� */
    if (AT_SUCCESS == Taf_SysCfgHandle(gastAtClientTab[ucIndex].usClientId, 0,stSysCfgSetPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPAM_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_SetStsfPara(TAF_UINT8 ucIndex)
{
    USIMM_STK_CFG_STRU                  ProfileContent;
    TAF_UINT32                          Result;
    TAF_UINT16                          Len = sizeof(USIMM_STK_CFG_STRU);
    MODEM_ID_ENUM_UINT16                usModemId;

    if(gastAtParaList[0].usParaLen != 1)        /* check the para */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex > 3)                          /* para too many */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    Result = NV_ReadEx(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &ProfileContent, Len);

    if(NV_OK != Result)
    {
        return AT_ERROR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &usModemId))
    {
        return AT_ERROR;
    }

    ProfileContent.ucFuncEnable = (TAF_UINT8)gastAtParaList[0].aucPara[0]-0x30;       /* change the string to Ascii value */

    if(gastAtParaList[1].usParaLen != 0x00)         /* have the <config> para */
    {
        if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara,&gastAtParaList[1].usParaLen)) /* change the string formate */
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if(gastAtParaList[1].usParaLen > 32)        /* according the etsi102.223,the most len or Terminal Profile is 32 */
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if (USIMM_CARD_USIM == AT_GetUsimInfoCtxFromModemId(usModemId)->enCardType)
        {
            ProfileContent.stUsimProfile.ucProfileLen = (TAF_UINT8)gastAtParaList[1].usParaLen;

            VOS_MemCpy(ProfileContent.stUsimProfile.aucProfile, gastAtParaList[1].aucPara, ProfileContent.stUsimProfile.ucProfileLen);
        }
        else
        {
            ProfileContent.stSimProfile.ucProfileLen = (TAF_UINT8)gastAtParaList[1].usParaLen;

            VOS_MemCpy(ProfileContent.stSimProfile.aucProfile, gastAtParaList[1].aucPara, ProfileContent.stSimProfile.ucProfileLen);
        }
    }

    if(gastAtParaList[2].usParaLen != 0x00)     /* ave the <Timer>  para */
    {
        Result = At_Auc2ul(gastAtParaList[2].aucPara, gastAtParaList[2].usParaLen, &gastAtParaList[2].ulParaValue);
        if (AT_SUCCESS != Result)
        {
            AT_WARN_LOG("At_SetStsfPara():Warning: At_Auc2ul convert failed!");

            return AT_CME_INCORRECT_PARAMETERS;
        }

        if((gastAtParaList[2].ulParaValue> 0xFF)||(gastAtParaList[2].ulParaValue == 0))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        ProfileContent.ucTimer = (TAF_UINT8)gastAtParaList[2].ulParaValue;
    }

    Result = NV_WriteEx(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &ProfileContent, Len);

    if(Result != NV_OK)
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_ChangeSATCmdType
 Description    : chang the cmdNo to cmdType
 Input          :
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_ChangeSATCmdType(TAF_UINT32 cmdNo, TAF_UINT32 *CmdType)
{
    TAF_UINT32 Result = AT_SUCCESS;

    switch(cmdNo)
    {
        case SI_AT_CMD_DISPLAY_TEXT:
            *CmdType = SI_STK_DISPLAYTET;
            break;
        case SI_AT_CMD_GET_INKEY:
            *CmdType = SI_STK_GETINKEY;
            break;
        case SI_AT_CMD_GET_INPUT:
            *CmdType = SI_STK_GETINPUT;
            break;
        case SI_AT_CMD_SETUP_CALL:
            *CmdType = SI_STK_SETUPCALL;
            break;
        case SI_AT_CMD_PLAY_TONE:
            *CmdType = SI_STK_PLAYTONE;
            break;
        case SI_AT_CMD_SELECT_ITEM:
            *CmdType = SI_STK_SELECTITEM;
            break;
        case SI_AT_CMD_REFRESH:
            *CmdType = SI_STK_REFRESH;
            break;
        case SI_AT_CMD_SEND_SS:
            *CmdType = SI_STK_SENDSS;
            break;
        case SI_AT_CMD_SEND_SMS:
            *CmdType = SI_STK_SENDSMS;
            break;
        case SI_AT_CMD_SEND_USSD:
            *CmdType = SI_STK_SENDUSSD;
            break;
        case SI_AT_CMD_LAUNCH_BROWSER:
            *CmdType = SI_STK_LAUNCHBROWSER;
            break;
        case SI_AT_CMD_SETUP_IDLE_MODE_TEXT:
            *CmdType = SI_STK_SETUPIDLETEXT;
            break;
        case SI_AT_CMD_LANGUAGENOTIFICATION:
            *CmdType = SI_STK_LANGUAGENOTIFICATION;
            break;
        case SI_AT_CMD_SETFRAMES:
            *CmdType = SI_STK_SETFRAMES;
            break;
        case SI_AT_CMD_GETFRAMESSTATUS:
            *CmdType = SI_STK_GETFRAMESSTATUS;
            break;
        default:
            Result = AT_ERROR;
            break;
    }

    return Result;
}


/*****************************************************************************
 Prototype      : At_SetStgiPara
 Description    : ^STGI
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetStgiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32 Result;
    TAF_UINT32 CmdType;

    if(TAF_FALSE == g_ulSTKFunctionFlag)
    {
        return AT_ERROR;
    }

    if(0 == gastAtParaList[0].usParaLen)        /* check the para */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gucAtParaIndex != 2)                         /* the para number is must be 2 */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].ulParaValue > 0x0C)        /* the <cmdType> is not more the 12 */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].ulParaValue== 0x00)        /* get the main menu content */
    {
        Result = SI_STK_GetMainMenu(gastAtClientTab[ucIndex].usClientId,0);
    }
    else  if(AT_ERROR == At_ChangeSATCmdType(gastAtParaList[0].ulParaValue, &CmdType))  /* get other SAT content */
    {
        return AT_ERROR;
    }
    else
    {
        Result = SI_STK_GetSTKCommand(gastAtClientTab[ucIndex].usClientId, 0, CmdType);
    }

    if(AT_SUCCESS == Result)
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_STGI_SET;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 At_SetClvlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8           aucIntraVolume[] = {AT_CMD_CLVL_LEV_0,AT_CMD_CLVL_LEV_1,
                                            AT_CMD_CLVL_LEV_2,AT_CMD_CLVL_LEV_3,
                                            AT_CMD_CLVL_LEV_4,AT_CMD_CLVL_LEV_5};


    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������ߴ��� */
    if ((gucAtParaIndex > 1) || (gastAtParaList[0].ulParaValue > AT_CMD_CLVL_VAL_MAX))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������һ��ת����Ŀǰ��̨Ҫ��ķ�Χ��0~5�������Ƕ�Ӧ�ķ�Χ��0~92��
       ���ݺ�ý���ȷ�ϣ��趨��Χ��0~80�����Զ�Ӧ */

    /* ����ֵΪAT_SUCCESS��ΪVOS_OK����Ӧ����  */
    if (VOS_OK == APP_VC_SetVoiceVolume(gastAtClientTab[ucIndex].usClientId, 0, aucIntraVolume[gastAtParaList[0].ulParaValue]))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLVL_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 At_SetVMSETPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                          ucVoiceMode;


    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucVoiceMode = (VOS_UINT8)gastAtParaList[0].ulParaValue;

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    /* �����ø��� */
    if (VOS_OK != APP_VC_SetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0, ucVoiceMode, I1_WUEPS_PID_VC))
    {
        return AT_ERROR;
    }
#endif

    /* ���������� */
    if (VOS_OK == APP_VC_SetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0, ucVoiceMode, I0_WUEPS_PID_VC))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetTestPara
 Description    : +TEST=[<n>]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetTestPara(TAF_UINT8 ucIndex)
{
    return AT_OK;
}

/* ==> x68770 For WAS AutoTest */

TAF_UINT32 At_SetCwasPara(TAF_UINT8 ucIndex)
{
    AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU   stAtCmd;
    VOS_UINT32                          ulRst;


    /* �������� */
    if ((gucAtParaIndex > 4) || (gucAtParaIndex < 1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    /* ��ʼ�� */
    PS_MEM_SET(&stAtCmd, 0, sizeof(AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU));
    stAtCmd.ucCmd = (TAF_UINT8)gastAtParaList[0].ulParaValue;

    for ( stAtCmd.ucParaNum = 0;
          stAtCmd.ucParaNum < (gucAtParaIndex-1);
          stAtCmd.ucParaNum++)
    {
        stAtCmd.aulPara[stAtCmd.ucParaNum]
            = gastAtParaList[stAtCmd.ucParaNum+1].ulParaValue;
    }


    /* ������Ϣ��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_AUTOTEST_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_WRR_AUTOTEST_QRY_PARA_STRU),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CWAS_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }


}
TAF_UINT32 At_SetCGasPara(TAF_UINT8 ucIndex)
{
    GAS_AT_CMD_STRU                     stAtCmd;
    VOS_UINT32                          ulRst;

    /* �������� */
    if ((gucAtParaIndex > 2) || (gucAtParaIndex < 1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    if ((7 != gastAtParaList[0].ulParaValue)
       &&(gucAtParaIndex > 1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }



    /* ��ȡ������� */
    stAtCmd.ucCmd = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    for (stAtCmd.ucParaNum = 0; stAtCmd.ucParaNum < (gucAtParaIndex-1); stAtCmd.ucParaNum++)
    {
        stAtCmd.aulPara[stAtCmd.ucParaNum] = gastAtParaList[stAtCmd.ucParaNum+1].ulParaValue;
    }

    /* ������ϢDRV_AGENT_GAS_MNTN_CMD��C�˴��� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_GAS_MNTN_CMD,
                                   &stAtCmd,
                                   sizeof(GAS_AT_CMD_STRU),
                                   I0_WUEPS_PID_DRV_AGENT);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAS_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
VOS_UINT32 At_SetAppDialModePara(VOS_UINT8 ucIndex)
{
     VOS_UINT32                         ulStatus;
     VOS_UINT8                         *pucSystemAppConfig;

     pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    if (SYSTEM_APP_WEBUI != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }


     /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        if (1 == gastAtParaList[0].ulParaValue)
        {
            /*���õ����ӿ�֪ͨӦ�ý��в���*/
            ulStatus = AT_USB_ENABLE_EVENT;
        }
        else if(0 == gastAtParaList[0].ulParaValue)
        {
            /*���õ����ӿ�֪ͨӦ�ý��жϿ�����*/
            ulStatus = AT_USB_SUSPEND_EVENT;
        }
        else
        {
             return AT_CME_INCORRECT_PARAMETERS;
        }

    }

    DRV_AT_SETAPPDAILMODE(ulStatus);

    return AT_OK;
}
TAF_UINT32   At_SetCmmPara(TAF_UINT8 ucIndex)
{
    MM_TEST_AT_CMD_STRU                    stAtCmd;

    /* �������� */
    if( gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(MM_TEST_AT_CMD_STRU));

    stAtCmd.ucCmd = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    for (stAtCmd.ucParaNum = 0; stAtCmd.ucParaNum < (gucAtParaIndex-1); stAtCmd.ucParaNum++)
    {
        stAtCmd.aulPara[stAtCmd.ucParaNum]=gastAtParaList[stAtCmd.ucParaNum+1].ulParaValue;
    }

    /* ����TAF_MSG_MMA_CRPN_HANDLE��Ϣ��MMA���� */
    if(VOS_OK == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                        0,
                                        TAF_MSG_MM_TEST_HANDLE,
                                        &stAtCmd,
                                        sizeof(MM_TEST_AT_CMD_STRU),
                                        I0_WUEPS_PID_MMA))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MM_TEST_CMD_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_VOID AT_ShowCccRst(
    NAS_CC_STATE_INFO_STRU              *pstCcState,
    VOS_UINT16                          *pusLength
)
{
    VOS_UINT16                          usLength;

    usLength = *pusLength;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                      "%d,",
                                      pstCcState->ucCallId);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                      "%d,",
                                      pstCcState->ucTi);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                      "%d,",
                                      pstCcState->enCallState);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                      "%d,",
                                      pstCcState->enHoldAuxState);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                      "%d",
                                      pstCcState->enMptyAuxState);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

    *pusLength = usLength;
}


VOS_UINT32  AT_SetCccPara( TAF_UINT8 ucIndex )
{
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRst;

    if ((gucAtParaIndex > 2) || (0 == gucAtParaIndex))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 0 == gastAtParaList[0].ulParaValue )
    {
        ucCallId = 0;   /* 0��ʾ��ѯ����call Id */
    }
    else
    {
        /* gastAtParaList[1].ulParaValueȡֵ������ȡĬ��ֵ,��ȡCallId = 1�ĺ���״̬ */
        if ( 0 == gastAtParaList[1].usParaLen )
        {
            ucCallId = 1;
        }
        else
        {
            ucCallId = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }

    }

    /* ������ϢAT_CC_MSG_STATE_QRY_REQ��CC��ȡCCЭ��״̬ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   AT_CC_MSG_STATE_QRY_REQ,
                                   &ucCallId,
                                   sizeof(VOS_UINT8),
                                   I0_WUEPS_PID_CC);

    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CC_STATE_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
TAF_UINT32   At_SetSPNPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucSpnType;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* �������� */
    if( gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������ȡֵ���� */
    ucSpnType = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    if ( ucSpnType > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��¼AT^SPN��ѯ��SPN���� */
    pstNetCtx->ucSpnType = ucSpnType;

    /* ��MMA������Ϣ����ѯ�²�������TAF_PH_SPN_VALUE_PARA */
    if (VOS_OK == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                0,
                                TAF_PH_SPN_VALUE_PARA,
                                TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SPN_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
TAF_UINT32   At_SetCardModePara(TAF_UINT8 ucIndex)
{
    TAF_UINT8               ucCardMode = 0;   /* 0: card not exists, 1: SIM card, 2: USIM card */
    TAF_UINT16              usLength = 0;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulGetModemIdRslt;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    enModemId = MODEM_ID_0;

    /* �������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulGetModemIdRslt)
    {
        AT_ERR_LOG("At_SetCardModePara:Get Modem Id fail!");
        return AT_ERROR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* ��ȡ��ģʽ */
    if ( USIMM_CARD_SERVIC_ABSENT != pstUsimInfoCtx->enCardStatus)
    {
        if (USIMM_CARD_SIM == pstUsimInfoCtx->enCardType)
        {
            ucCardMode = 1;
        }
        else if (USIMM_CARD_USIM == pstUsimInfoCtx->enCardType)
        {
            ucCardMode = 2;
        }
        else
        {
            ucCardMode = 0;
        }
    }
    else
    {
        ucCardMode = 0;
    }

    /* ������: ^CARDMODE:cardmode */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                       "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                       "%d",
                                       ucCardMode );

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



/*****************************************************************************
 �� �� ��  : At_SetDialModePara
 ��������  : ^DIALMODE=<value>
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��12��01��
    �޸�����   : �����ն�Ҫ������AT����:AT^DIALMODE
*****************************************************************************/
TAF_UINT32   At_SetDialModePara(TAF_UINT8 ucIndex)
{
    /*�����ն˶Ը������Ҫ���������������ERROR*/
    return AT_ERROR;
}
TAF_UINT32   At_SetPortSelPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8               ucPortSel = 0;   /* 0: PCUI, 1: Modem */

    /* �������� */
    if( gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* �������ȡֵ���� */
    ucPortSel = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    if ( ucPortSel > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    gucAtPortSel = ucPortSel;

    return AT_OK;
}
TAF_UINT32   At_SetCurcPara(TAF_UINT8 ucIndex)
{
    AT_MTA_CURC_SET_NOTIFY_STRU         stAtCmd;
    VOS_UINT32                          ulResult;

#if  (FEATURE_ON == FEATURE_LTE)
    L4A_IND_CFG_STRU                    stL4AIndCfgReq;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId  = MODEM_ID_0;
#endif

    /* ������� */
    if ( (gucAtParaIndex > 2)
      || (gucAtParaIndex < 1) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0, sizeof(stAtCmd));
    stAtCmd.enCurcRptType = (AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* mode=0ʱ����ֹ���е������ϱ� */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        PS_MEM_SET(gastAtParaList[1].aucPara, 0x00, sizeof(gastAtParaList[1].aucPara));
    }
    else if (1 == gastAtParaList[0].ulParaValue)
    {
        /* mode=1ʱ�������е������ϱ� */
        PS_MEM_SET(gastAtParaList[1].aucPara, 0xFF, sizeof(gastAtParaList[1].aucPara));
    }
    else if (2 == gastAtParaList[0].ulParaValue)
    {
        /* mode=2ʱ����BITλ���ƶ�Ӧ�������ϱ�,�Զ������������ϱ�������Ҫ<report_cfg>���� */
        if ( (2 != gucAtParaIndex)
          || (AT_CURC_RPT_CFG_PARA_LEN != gastAtParaList[1].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        ulResult = At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen);
        if (AT_SUCCESS != ulResult)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(stAtCmd.aucRptCfg, gastAtParaList[1].aucPara, (AT_CURC_RPT_CFG_MAX_SIZE));

    /* ֪ͨMTA�˴�curc������ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_CURC_SET_NOTIFY,
                                   &stAtCmd,
                                   sizeof(AT_MTA_CURC_SET_NOTIFY_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

#if  (FEATURE_ON == FEATURE_LTE)
    ulResult = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulResult)
    {
        AT_ERR_LOG1("At_SetCurcPara:Get ModemID From ClientID fail,ClientID=%d", ucIndex);
        return AT_ERROR;
    }

    if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE))
    {
        /* ƽ̨����֧��LTE */
        PS_MEM_SET(&stL4AIndCfgReq, 0, sizeof(stL4AIndCfgReq));
        stL4AIndCfgReq.curc_bit_valid  = 1;
        PS_MEM_CPY(stL4AIndCfgReq.aucCurcCfgReq, gastAtParaList[1].aucPara,
                   sizeof(stL4AIndCfgReq.aucCurcCfgReq));

        /* ֪ͨL�˴�curc������ */
        return AT_SetLIndCfgReq(ucIndex, &stL4AIndCfgReq);
    }
    else
    {
        return AT_OK;
    }
#else
    return AT_OK;
#endif
}


TAF_UINT32   At_SetBOOTPara(TAF_UINT8 ucIndex)
{

    /* �������� */
    if( gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    /* �������� */
    if( gucAtParaIndex < 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������ȡֵ���, para2����Ϊ 0 */
    if ( (gastAtParaList[1].usParaLen != 1) || (gastAtParaList[1].aucPara[0]!= '0') )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ֱ�ӷ���OK. */
    return AT_OK;
}


TAF_UINT32 At_SetCellInfoPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulAtCmdCellInfo;
    VOS_UINT32                          ulRst;

    /* �������� */
    if(gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulAtCmdCellInfo = gastAtParaList[0].ulParaValue;


    /* ������ϢID_AT_MTA_WRR_CELLINFO_QRY_REQ��C��AT AGENT���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_CELLINFO_QRY_REQ,
                                   &ulAtCmdCellInfo,
                                   sizeof(VOS_UINT32),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CELLINFO_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }


}


TAF_UINT32  At_GetMeanRpt( TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    /* �������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������ϢID_AT_MTA_WRR_MEANRPT_QRY_REQ��AT AGENT���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_MEANRPT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MEANRPT_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*<--W101153 For Was AutoTest*/

TAF_UINT32 At_SetRRCVersion(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVersion;
    VOS_UINT32                          ulRst;

    /* �������෵�ز������� */
    if(gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucRRCVersion = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ������ϢDRV_AGENT_RRC_VERSION_SET_REQ��AT�������� */

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_RRC_VERSION_SET_REQ,
                                   &ucRRCVersion,
                                   sizeof(VOS_UINT8),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RRC_VERSION_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


TAF_UINT32 At_SetCSNR(TAF_UINT8 ucIndex)
{
    /* �������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;
}
TAF_UINT32 At_SetFreqLock(TAF_UINT8 ucIndex)
{
    MTA_AT_WRR_FREQLOCK_CTRL_STRU       stFreqLock;
    VOS_UINT32                          ulRst;

    /* ������������ȷ�򷵻ز������� */
    if ( (gucAtParaIndex != 1) && (gucAtParaIndex != 2) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����һ����������Ƶ,���ڶ�������Ƶ��ֵû�����û�
       ���õ�ֵ��Ч�򷵻ش���*/
    if ( (gastAtParaList[0].ulParaValue == 1)
      && (gastAtParaList[1].usParaLen == 0) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    /* ������Ϣ��ֵ */
    PS_MEM_SET(&stFreqLock, 0, sizeof(MTA_AT_WRR_FREQLOCK_CTRL_STRU));
    stFreqLock.ucFreqLockEnable = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stFreqLock.usLockedFreq     = (VOS_UINT16)gastAtParaList[1].ulParaValue;

    /* ������Ϣ ID_AT_MTA_WRR_FREQLOCK_SET_REQ ��C�� AT �������� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_FREQLOCK_SET_REQ,
                                   &stFreqLock,
                                   sizeof(MTA_AT_WRR_FREQLOCK_CTRL_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FREQLOCK_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


TAF_UINT32 At_SetParaCmd(TAF_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM ulResult = AT_FAILURE;

    /*
    vts������������Ҫע�⣬���ڲ������еĲ�������ΪTAF_NULL_PTR����ʵ�����ò���ʱ��ȡ�����õĲ���
    �����������޲��������Ҫ�жϣ������Ч����������Ϊ0���򷵻ش���
    */

    if(TAF_NULL_PTR != g_stParseContext[ucIndex].pstCmdElement->pfnSetProc)
    {
        ulResult = (AT_RRETURN_CODE_ENUM)g_stParseContext[ucIndex].pstCmdElement->pfnSetProc(ucIndex);

        if(AT_WAIT_ASYNC_RETURN == ulResult)
        {
            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

            /* ����ʱ�� */
            if(AT_SUCCESS != At_StartTimer(g_stParseContext[ucIndex].pstCmdElement->ulSetTimeOut,ucIndex))
            {
                AT_ERR_LOG("At_SetParaCmd:ERROR:Start Timer");
                return AT_ERROR;
            }
        }
        return ulResult;
    }
    else
    {
        return AT_ERROR;
    }
}
TAF_UINT32 At_StgrSelMenu(TAF_UINT8 ucIndex)
{
    SI_STK_MENU_SELECTION_STRU *pMenu;
    SI_STK_ENVELOPE_STRU        stENStru;
    VOS_UINT32                  ulRslt;

    /* �������� */
    if(gucAtParaIndex > 4)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stENStru.EnvelopeType    = SI_STK_ENVELOPE_MENUSEL;
    stENStru.DeviceId.ucSDId = SI_DEVICE_KEYPAD;
    stENStru.DeviceId.ucDDId = SI_DEVICE_UICC;

    pMenu = &stENStru.uEnvelope.MenuSelect;
    PS_MEM_SET(pMenu, 0x00, sizeof(SI_STK_MENU_SELECTION_STRU));

    if(SI_AT_RESULT_HELP_REQUIRED == gastAtParaList[2].ulParaValue)
    {
        pMenu->OP_Help        = 1;
        pMenu->Help.aucRsv[0] = 1;
    }

    /*select item*/
    if(0 == gastAtParaList[3].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        ulRslt = At_Auc2ul(gastAtParaList[3].aucPara, gastAtParaList[3].usParaLen, &gastAtParaList[3].ulParaValue);
        if (AT_SUCCESS != ulRslt)
        {
            AT_WARN_LOG("At_StgiSelectItem():Warning: At_Auc2ul convert failed!");
            return AT_ERROR;
        }

        pMenu->OP_ItemIp       = 1;
        pMenu->ItemId.ucItemId = (TAF_UINT8)gastAtParaList[3].ulParaValue;
    }

    /* ִ��������� */
    if(AT_SUCCESS == SI_STK_MenuSelection(gastAtClientTab[ucIndex].usClientId, 0,&stENStru))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_STGR_SET;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;    /* �������������״̬ */
    }
}

/*****************************************************************************
 Prototype      : At_ChangeCmdResult
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_ChangeCmdResult(TAF_UINT32 resultNo,TAF_UINT8 *cmdResult)
{
    TAF_UINT32 ulResult;

    ulResult = AT_SUCCESS;

    switch(resultNo)
    {
        case SI_AT_RESULT_END_SESSION:
            *cmdResult = PROACTIVE_UICC_SESSION_TERMINATED_BY_THE_USER;
            break;
        case SI_AT_RESULT_PERFORM_SUCC:
            *cmdResult = COMMAND_PERFORMED_SUCCESSFULLY;
            break;
        case SI_AT_RESULT_HELP_REQUIRED:
            *cmdResult = HELP_INFORMATION_REQUIRED_BY_USER;
            break;
        case SI_AT_RESULT_BACKWARD_MOVE:
            *cmdResult = BACKWARD_MOVE_IN_THE_PROACTIVE_UICC_SESSION_REQUESTED_BY_USER;
            break;
        case SI_AT_RESULT_ME_NOT_SUPPORT:
            *cmdResult = COMMAND_BEYOND_TERMINALS_CAPABILITIES;
            break;
        case SI_AT_RESULT_ME_BROWSER_BUSY:
            *cmdResult = TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND;
            break;
        case SI_AT_RESULT_ME_SS_BUSY:
            *cmdResult = TERMINAL_CURRENTLY_UNABLE_TO_PROCESS_COMMAND;
            break;
        default:
            ulResult= AT_ERROR;
    }

    return ulResult;
}

/*****************************************************************************
 Prototype      : At_StgiGetKey
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_StgiGetKey(TAF_UINT8 ucIndex, SI_STK_TERMINAL_RSP_STRU *pRsp)
{
    TAF_UINT8 cmdResult;
    TAF_UINT8 InputKey[AT_PARA_MAX_LEN + 1];

    if(AT_ERROR == At_ChangeCmdResult(gastAtParaList[2].ulParaValue, &cmdResult))
    {
        return AT_ERROR;
    }

    pRsp->Result.Result = cmdResult;

    if(COMMAND_PERFORMED_SUCCESSFULLY == cmdResult)
    {
        /* ר�в��� */
        pRsp->uResp.GetInkeyRsp.TextStr.pucText = pRsp->aucData;

        VOS_MemCpy(InputKey, gastAtParaList[3].aucPara, gastAtParaList[3].usParaLen);

        /*���ڵ��ĸ������Ǳ�εģ�AT�ʷ��������޷������������ڴ��������н���������
        ����ʱ��Ҫ������ȥ�������ȼ�2*/
        if(AT_FAILURE == At_AsciiString2HexText(&pRsp->uResp.GetInkeyRsp.TextStr,\
                                                    InputKey+1, gastAtParaList[3].usParaLen-2))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        pRsp->uResp.GetInkeyRsp.OP_TextStr = 1;

        if((gucSTKCmdQualify&0x02)== 0x00)
        {
            pRsp->uResp.GetInkeyRsp.TextStr.ucDCS = 0x04;
        }
        else
        {
            pRsp->uResp.GetInkeyRsp.TextStr.ucDCS = 0x08;
        }

        if((gucSTKCmdQualify&0x04)== 0x04)
        {
            *pRsp->uResp.GetInkeyRsp.TextStr.pucText -=0x30;
        }
    }

    return AT_SUCCESS;
}
/*****************************************************************************
 Prototype      : At_StgiGetInput
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_StgiGetInput(TAF_UINT8 ucIndex,SI_STK_TERMINAL_RSP_STRU *pRsp)
{
    TAF_UINT8 cmdResult;
    TAF_UINT8 InputString[AT_PARA_MAX_LEN + 1];

    if(AT_ERROR == At_ChangeCmdResult(gastAtParaList[2].ulParaValue, &cmdResult))
    {
        return AT_ERROR;
    }

    pRsp->Result.Result = cmdResult;

    if(COMMAND_PERFORMED_SUCCESSFULLY == cmdResult)
    {
        /* ר�в��� */
        if(0x03 >  gastAtParaList[3].usParaLen)
        {
            pRsp->uResp.GetInkeyRsp.TextStr.pucText = TAF_NULL_PTR;

            pRsp->uResp.GetInkeyRsp.TextStr.ucLen = 0;
        }
        else
        {
            pRsp->uResp.GetInkeyRsp.TextStr.pucText = pRsp->aucData;

            VOS_MemCpy(InputString, gastAtParaList[3].aucPara, gastAtParaList[3].usParaLen);

            /*���ڵ��ĸ������Ǳ�εģ�AT�ʷ��������޷������������ڴ��������н�������������ʱ��Ҫ������ȥ�������ȼ�2*/
            if(AT_FAILURE == At_AsciiString2HexText(&pRsp->uResp.GetInputRsp.TextStr,\
                                            InputString+1, gastAtParaList[3].usParaLen-2))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }

        pRsp->uResp.GetInputRsp.OP_TextStr = 1;

        if((gucSTKCmdQualify&0x02)== 0x00)
        {
            if((gucSTKCmdQualify&0x08)== 0x00)
            {
                pRsp->uResp.GetInkeyRsp.TextStr.ucDCS = 0x04;
            }
            else
            {
                pRsp->uResp.GetInkeyRsp.TextStr.ucDCS = 0x00;
            }
        }
        else
        {
            pRsp->uResp.GetInkeyRsp.TextStr.ucDCS = 0x08;
        }
    }

    return AT_SUCCESS;
}

TAF_UINT32 At_StgiSelectItem(TAF_UINT8 ucIndex,SI_STK_TERMINAL_RSP_STRU *pRsp)
{
    TAF_UINT8       cmdResult;
    VOS_UINT32      ulRslt;

    if(AT_ERROR == At_ChangeCmdResult(gastAtParaList[2].ulParaValue, &cmdResult))
    {
        return AT_ERROR;
    }

    pRsp->Result.Result = cmdResult;

    if(COMMAND_PERFORMED_SUCCESSFULLY == cmdResult)
    {
        ulRslt = At_Auc2ul(gastAtParaList[3].aucPara, gastAtParaList[3].usParaLen, &gastAtParaList[3].ulParaValue);
        if (AT_SUCCESS != ulRslt)
        {
            AT_WARN_LOG("At_StgiSelectItem():Warning: At_Auc2ul convert failed!");
            return AT_ERROR;
        }

        /* ר�в��� */
        pRsp->uResp.SelectItemRsp.ItemId.ucItemId = (TAF_UINT8)gastAtParaList[3].ulParaValue;
        pRsp->uResp.SelectItemRsp.OP_ItemID       = 1;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_SetStgrPara
 Description    : ^STGR=<cmdnum>,<cmdtype>,<result>,<data>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetStgrPara(TAF_UINT8 ucIndex)
{
    SI_STK_TERMINAL_RSP_STRU Rsponse;
    TAF_UINT32 Result = 0;

#if ( VOS_WIN32 != VOS_OS_VER )
    if(TAF_FALSE == g_ulSTKFunctionFlag)
    {
        return AT_ERROR;
    }
#endif

    if((gucAtParaIndex > 4)||(gucAtParaIndex < 3))          /* the para munber is too many or too few */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 == gastAtParaList[0].usParaLen)||(0 == gastAtParaList[1].usParaLen))  /* the para1 and para2 is must be inputed */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    Rsponse.DeviceId.ucSDId = SI_DEVICE_KEYPAD;
    Rsponse.DeviceId.ucDDId = SI_DEVICE_UICC;

    /* At_Auc2ul(gastAtParaList[3].aucPara, gastAtParaList[3].usParaLen, &gastAtParaList[3].ulParaValue); */

    if(gastAtParaList[0].ulParaValue == 0x00)
    {
        if((gastAtParaList[2].ulParaValue== 1)||(gastAtParaList[2].ulParaValue == 2))   /* menu selection or need the help infomation */
        {
            return At_StgrSelMenu(ucIndex);
        }
        else
        {
            return AT_OK;
        }
    }

    PS_MEM_SET(&Rsponse, 0, sizeof(SI_STK_TERMINAL_RSP_STRU));

    if(SI_AT_CMD_END_SESSION == gastAtParaList[0].ulParaValue)
    {
        Rsponse.Result.Result = PROACTIVE_UICC_SESSION_TERMINATED_BY_THE_USER;
    }
    else if(AT_SUCCESS != At_ChangeSATCmdType(gastAtParaList[0].ulParaValue, &Rsponse.CmdType))
    {
        return AT_ERROR;
    }
    else
    {

    }

    switch(gastAtParaList[0].ulParaValue)
    {
        case SI_AT_CMD_GET_INKEY:
            Result = At_StgiGetKey(ucIndex, &Rsponse);       /* change the GetInkey response content */
            break;
        case SI_AT_CMD_GET_INPUT:
            Result = At_StgiGetInput(ucIndex, &Rsponse);     /* change the GetInput response content */
            break;
        case SI_AT_CMD_SELECT_ITEM:
            Result = At_StgiSelectItem(ucIndex, &Rsponse);   /* change the SelectItem response content */
            break;
        default:
            Result = At_ChangeCmdResult(gastAtParaList[2].ulParaValue, &Rsponse.Result.Result);
            break;
    }

    if(AT_SUCCESS != Result)
    {
        return Result;    /* return the error */
    }

    if(AT_SUCCESS == SI_STK_TerminalResponse(gastAtClientTab[ucIndex].usClientId, 0,&Rsponse))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_STGR_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCstrPara
 Description    : ^STGR=<Len>,<data>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCstrPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8   aucData[256];
    VOS_UINT8   ucDataLen;
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }

    if (gucAtParaIndex != 2)          /* the para munber is too many or too few */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)||(0 == gastAtParaList[1].usParaLen))  /* the para1 and para2 is must be inputed */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_FAILURE == At_AsciiString2HexSimple(aucData, gastAtParaList[1].aucPara, (VOS_UINT16)gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucDataLen = (TAF_UINT8)(gastAtParaList[0].ulParaValue/2);

    if (AT_SUCCESS == SI_STK_DataSendSimple(gastAtClientTab[ucIndex].usClientId, 0, SI_STK_TRSEND, ucDataLen, aucData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSTR_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_SetCsinPara
 Description    : ^CSIN���������
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2012-05-17
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCsinPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ANDROIDϵͳ��֧�� */
    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }

    /* ��ȡ���һ���յ���������������������ʹ��� */
    if (AT_SUCCESS == SI_STK_GetSTKCommand(gastAtClientTab[ucIndex].usClientId, 0, 0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSEN_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCstrPara
 Description    : ^STGR=<Len>,<data>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCsenPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8   aucData[256];
    VOS_UINT8   ucDataLen;
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }

    if (gucAtParaIndex != 2)          /* the para munber is too many or too few */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 == gastAtParaList[0].usParaLen)||(0 == gastAtParaList[1].usParaLen))  /* the para1 and para2 is must be inputed */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_FAILURE == At_AsciiString2HexSimple(aucData, gastAtParaList[1].aucPara, (VOS_UINT16)gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucDataLen = (TAF_UINT8)(gastAtParaList[0].ulParaValue/2);

    if (AT_SUCCESS == SI_STK_DataSendSimple(gastAtClientTab[ucIndex].usClientId, 0, SI_STK_ENVELOPESEND, ucDataLen, aucData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSEN_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCsmnPara
 Description    : ^CSMN
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCsmnPara(TAF_UINT8 ucIndex)
{
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }

    if (gucAtParaIndex != 0)          /* the para munber is too many or too few */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_SUCCESS == SI_STK_GetMainMenu(gastAtClientTab[ucIndex].usClientId, 0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSEN_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_SetCstcPara
 Description    : ^CSTC
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  3.��    ��   : 2012��03��03��
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:OAMȷ��AP���еĴ���ɾ��
  4.��    ��   : 2012��09��18��
    �޸�����   : STK&DCM��Ŀ�� �޸�ʵ��

*****************************************************************************/
TAF_UINT32 At_SetCstcPara(TAF_UINT8 ucIndex)
{
    if (gucAtParaIndex != 1)          /* the para munber is too many or too few */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_SUCCESS == SI_STK_SetUpCallConfirm(gastAtClientTab[ucIndex].usClientId, gastAtParaList[0].ulParaValue))
    {
        return AT_OK;
    }

    return AT_ERROR;
}


/*****************************************************************************
 Prototype      : At_SetImsichgPara
 Description    : ^STGR=<cmdnum>,<cmdtype>,<result>,<data>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2010-02-11
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetImsichgPara(TAF_UINT8 ucIndex)
{
    if (VOS_FALSE == SI_STKIsDualImsiSupport())
    {
        return AT_CMD_NOT_SUPPORT;
    }

    if (1 != gucAtParaIndex)          /* the para munber is too many or too few */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (0 == gastAtParaList[0].usParaLen)  /* the para1 must be inputed */
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_SUCCESS == SI_STKDualIMSIChangeReq(gastAtClientTab[ucIndex].usClientId, 0))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSICHG_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32  AT_PhyNumIsNull(
    MODEM_ID_ENUM_UINT16                enModemId,
    AT_PHYNUM_TYPE_ENUM_UINT32          enSetType,
    VOS_BOOL                           *pbPhyNumIsNull
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulTotalNum;
    IMEI_STRU                           stImei;
    TAF_SVN_DATA_STRU                   stSvnData;
    VOS_UINT8                           *pucCheckNum;
    VOS_UINT8                           aucMac[AT_PHYNUM_MAC_LEN + 1]; /* MAC��ַ*/


    PS_MEM_SET(&stSvnData, 0x00, sizeof(stSvnData));


    /* �ӻ�ȡNV��IMEI��SVN�����ţ���ȡ����ʧ�ܣ��򷵻�AT_ERROR */
    if (AT_PHYNUM_TYPE_IMEI == enSetType)
    {
        ulRet = NV_ReadEx(enModemId, en_NV_Item_IMEI, &stImei, NV_ITEM_IMEI_SIZE);
        if (NV_OK != ulRet)
        {
            AT_WARN_LOG("AT_PhyNumIsNull: Fail to read en_NV_Item_IMEI");
            return AT_ERROR;
        }

        /*NV��en_NV_Item_IMEI�н�15λ��UE��IMEI�ţ����һλ����Чλ�����Ƚ�*/
        ulTotalNum  = TAF_IMEI_DATA_LENGTH;
        pucCheckNum = stImei.aucImei;
    }
    else if (AT_PHYNUM_TYPE_SVN == enSetType)
    {
        ulRet = NV_ReadEx(enModemId, en_NV_Item_Imei_Svn, &stSvnData, sizeof(stSvnData));
        if (NV_OK != ulRet)
        {
            AT_WARN_LOG("AT_PhyNumIsNull: Fail to read en_Nv_Item_Imei_Svn");
            return AT_ERROR;
        }

        /* SVNδ���������Ϊ�մ��� */
        if (NV_ITEM_ACTIVE != stSvnData.ucActiveFlag)
        {
            *pbPhyNumIsNull = VOS_TRUE;
            return AT_OK;
        }

        ulTotalNum  = TAF_SVN_DATA_LENGTH;
        pucCheckNum = stSvnData.aucSvn;
    }
    else if (AT_PHYNUM_TYPE_MAC == enSetType)
    {
        /* �����ǰMAC��ַ�Ƿ�Ϊ��״̬ */
        AT_GetPhynumMac(aucMac);
        ulTotalNum  = AT_PHYNUM_MAC_LEN;
        pucCheckNum = aucMac;
    }
    else
    {
        AT_WARN_LOG("AT_PhyNumIsNull: the type of physical is error.");
        return AT_ERROR;
    }

    /* NV��IMEI��SVN������Ϊȫ0��Ϊ������Ϊ�գ����򣬷ǿ� */
    for (ulLoop = 0; ulLoop < ulTotalNum; ulLoop++)
    {
        if (0 != *pucCheckNum)
        {
            *pbPhyNumIsNull = VOS_FALSE;
            return AT_OK;
        }

        pucCheckNum++;
    }

    *pbPhyNumIsNull = VOS_TRUE;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_UpdateImei
 ��������  : ����IMEI��NV��en_NV_Item_IMEI
             IMEI��Ϣ��IMEI(TAC8λ,SNR6λ)��У��λ���������
             IMEI��Ӧ��NV����IMEI��Ϣ15λ��1λ���λ��ɣ���16λ��
 �������  : MODEM_ID_ENUM_UINT16                enModemId
             VOS_UINT8  aucImei[]    IMEI�ַ����׵�ַ���˴����ݽ�����15λ��IMEI��Ϣ
             VOS_UINT32 ulImeiLength IMEI�ַ�������
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ���²������
             AT_OK                ���²����ɹ�
             AT_PHYNUM_LENGTH_ERR �����ų��ȴ���
             AT_PHYNUM_NUMBER_ERR �����Ŵ���
             AT_ERROR             NV��дʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��2��
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��4��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_UpdateImei(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           aucImei[],
    VOS_UINT16                          usImeiLength
)
{
    VOS_UINT8                           aucBcdNum[TAF_PH_IMEI_LEN];
    VOS_UINT8                           ucCheckData;
    VOS_UINT32                          i;

    /* IMEI ���ȼ��: �û������IMEI����ӦΪ14λ��IMEI��1λ��CHECK NUM����15λ */
    if ((TAF_PH_IMEI_LEN - 1) != usImeiLength)
    {
        AT_NORM_LOG1("AT_UpdateImei: the length of imei is error ", (VOS_INT32)usImeiLength);
        return AT_PHYNUM_LENGTH_ERR;
    }

    /* IMEI ������: ȷ��<imei>Ϊ�����ַ���, ����ASCII��ת����BCD�� */
    if (AT_SUCCESS != At_AsciiNum2Num(aucBcdNum, aucImei, usImeiLength))
    {
        AT_NORM_LOG("AT_UpdateImei: the number of imei is error.");
        return AT_PHYNUM_NUMBER_ERR;
    }
    aucBcdNum[TAF_PH_IMEI_LEN - 1] = 0;

    /* IMEI У����: IMEI��Ϣ��IMEI(TAC8λ,SNR6λ)��У��λ���������
       �ο�Э��: 3GPP 23003 B.2 Computation of CD for an IMEI��B.3 Example of computation */
    ucCheckData = 0;
    for (i = 0; i < (TAF_IMEI_DATA_LENGTH - 1); i += 2)
    {
        ucCheckData += aucBcdNum[i]
                       + ((aucBcdNum[i + 1] + aucBcdNum[i + 1]) / 10)
                       + ((aucBcdNum[i + 1] + aucBcdNum[i + 1]) % 10);
    }
    ucCheckData = (10 - (ucCheckData % 10)) % 10;

    if (ucCheckData != aucBcdNum[TAF_PH_IMEI_LEN - 2])
    {
        AT_NORM_LOG("AT_UpdateImei: the checkdata of imei is error.");
        return AT_PHYNUM_NUMBER_ERR;
    }

    if (NV_OK != NV_WriteEx(enModemId, en_NV_Item_IMEI, aucBcdNum, TAF_PH_IMEI_LEN))
    {
         AT_WARN_LOG("AT_UpdateImei: Fail to write NV.");
         return AT_ERROR;
    }

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : At_SetImeiPara
 ��������  : ����IMEI
 �������  : TAF_UINT8 ucIndex �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��20��
    �޸�����   : �����ɺ��� ���ⵥ��:A32D08019
  2.��    ��   : 2007��02��11��
    �޸�����   : ���ⵥ��:A32D08708
  3.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
  4.��    ��   : 2010��8��4��
    �޸�����   : ATװ����һ��
  4.��    ��   : 2013��3��4��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetImeiPara(TAF_UINT8 ucIndex)
{
    VOS_BOOL                            bPhyNumIsNull;
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        AT_NORM_LOG1("At_SetImeiPara: the number of parameter is error ",
                     (VOS_INT32)gucAtParaIndex);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetImeiPara: Get modem id fail.");
        return AT_ERROR;
    }

    /* �����Ų�Ϊ�գ����ݱ���δ������ֱ�ӷ��ش��󣬴�����Ϊ1�����Ų��Ϸ��� */
    if (AT_OK != AT_PhyNumIsNull(enModemId, AT_PHYNUM_TYPE_IMEI, &bPhyNumIsNull))
    {
        return AT_ERROR;
    }

    if ((VOS_FALSE == bPhyNumIsNull) && (VOS_TRUE == g_bAtDataLocked))
    {
        AT_NORM_LOG("At_SetImeiPara: physical number is not null and data locked.");
        return AT_PHYNUM_TYPE_ERR;
    }

    /* �������ݵ�NV��en_NV_Item_IMEI�����ظ��½�� */
    ulRet = AT_UpdateImei(enModemId, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    return ulRet;
}
TAF_UINT32 At_SetFPlmnPara(TAF_UINT8 ucIndex)
{
    TAF_PH_FPLMN_OPERATE_STRU stFplmnOperate;


    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if( gucAtParaIndex > 2 )

    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[0].usParaLen != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 1 == gucAtParaIndex )
    {
        if ( 0 != gastAtParaList[0].ulParaValue )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        else
        {
            stFplmnOperate.stPlmn.Mcc = 0;
            stFplmnOperate.stPlmn.Mnc = 0;
            stFplmnOperate.ulCmdType = TAF_PH_FPLMN_DEL_ALL;
        }
    }
    else if ( 2 == gucAtParaIndex )
    {
        if(gastAtParaList[1].usParaLen > 6)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        /* Mcc */
        if(AT_FAILURE == At_String2Hex(gastAtParaList[1].aucPara,3,&stFplmnOperate.stPlmn.Mcc))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        /* Mnc */
        if(AT_FAILURE == At_String2Hex(&gastAtParaList[1].aucPara[3],
                                        gastAtParaList[1].usParaLen-3,
                                        &stFplmnOperate.stPlmn.Mnc))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        stFplmnOperate.stPlmn.Mcc &= 0x0FFF;

        if (5==gastAtParaList[1].usParaLen)
        {
            stFplmnOperate.stPlmn.Mnc |= 0x0F00;
        }

        stFplmnOperate.stPlmn.Mnc &= 0x0FFF;

        if ( 0 == gastAtParaList[0].ulParaValue)
        {
            stFplmnOperate.ulCmdType = TAF_PH_FPLMN_DEL_ONE;
        }
        else if ( 1 == gastAtParaList[0].ulParaValue)
        {
            stFplmnOperate.ulCmdType = TAF_PH_FPLMN_ADD_ONE;
        }
        else
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_FplmnHandle(gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     stFplmnOperate))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFPLMN_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}
TAF_UINT32 At_SetQuickStart(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if(1 != gucAtParaIndex)
    {
        return AT_ERROR;
    }

    if (gastAtParaList[0].ulParaValue > 1)
    {
        return AT_ERROR;
    }

    /* ִ��������� */
    if (AT_SUCCESS == TAF_DefQuickStart(gastAtClientTab[ucIndex].usClientId,
                      0,
                      gastAtParaList[0].ulParaValue))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CQST_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_SetAutoAttach(TAF_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {                                                                           /* �������� */
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[0].ulParaValue > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_SUCCESS == Taf_DefPhAutoAttach(gastAtClientTab[ucIndex].usClientId,
                      0,
                      gastAtParaList[0].ulParaValue))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAATT_SET;
        return AT_WAIT_ASYNC_RETURN;                                            /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 At_SetSystemInfo(TAF_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_SYSINFO_VALUE_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSINFO_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_GetBandPara(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_USER_SET_PREF_BAND64 * pStBand)
{
    const TAF_UINT8 ucHexLenOfUlongType = 8;
    TAF_UINT32  ulAtRslt1 = AT_SUCCESS;
    TAF_UINT32  ulAtRslt2 = AT_SUCCESS;

    pStBand->ulBandHigh = 0;
    pStBand->ulBandLow = 0;

    /* Ƶ���������  */
    if (usLen <= ucHexLenOfUlongType)
    {
         ulAtRslt1 = At_String2Hex(nptr,usLen,&(pStBand->ulBandLow));
    }
    else
    {
        ulAtRslt1 = At_String2Hex(nptr,usLen-ucHexLenOfUlongType,&(pStBand->ulBandHigh));
        ulAtRslt2 = At_String2Hex(nptr+(usLen-ucHexLenOfUlongType),ucHexLenOfUlongType,&(pStBand->ulBandLow));
    }

    if ( ( AT_FAILURE == ulAtRslt1 ) || (  AT_FAILURE == ulAtRslt2))
    {
        return  AT_FAILURE;
    }

    return AT_SUCCESS;

}
VOS_VOID At_ConvertSysCfgExRat(
    VOS_UINT8                           ucClientId,
    AT_SYSCFGEX_RAT_ORDER_STRU         *pstSysCfgExRatOrder,
    TAF_PH_RAT_ORDER_STRU              *pstRatOrder
)
{
    VOS_UINT32                          i;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRst;

    enModemId = MODEM_ID_0;

    /* ��ȡModemID*/
    ulRst = AT_GetModemIdFromClient(ucClientId, &enModemId);
    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG1("At_ConvertSysCfgExRat:Get ModemID From ClientID fail,ClientID=%d", ucClientId);
        return;
    }

    /* ���ԭ��ֵ00�Ľ��뼼��ת�� */
    if ( (1 == pstSysCfgExRatOrder->ucRatOrderNum)
      && (AT_SYSCFGEX_RAT_AUTO == pstSysCfgExRatOrder->aenRatOrder[0]))
    {
        AT_SetDefaultRatPrioList(enModemId, pstRatOrder, VOS_TRUE);
        return ;
    }

    /* ���ԭ��ֵ99�Ľ��뼼��ת�� */
    if ( (1 == pstSysCfgExRatOrder->ucRatOrderNum)
      && (AT_SYSCFGEX_RAT_NO_CHANGE == pstSysCfgExRatOrder->aenRatOrder[0]) )
    {
        AT_GetRatOrderNvim(enModemId, pstRatOrder, VOS_TRUE);
        return ;
    }

    /* �����ԭ��ֵ�Ľ��뼼��ת�� */
    pstRatOrder->ucRatOrderNum = pstSysCfgExRatOrder->ucRatOrderNum;
    for (i = 0; i < pstSysCfgExRatOrder->ucRatOrderNum; i++)
    {
        switch ( pstSysCfgExRatOrder->aenRatOrder[i] )
        {
#if (FEATURE_ON == FEATURE_LTE)
            case AT_SYSCFGEX_RAT_LTE:
                pstRatOrder->aenRatOrder[i] = TAF_PH_RAT_LTE;
                break;
#endif

            case AT_SYSCFGEX_RAT_WCDMA:
                pstRatOrder->aenRatOrder[i] = TAF_PH_RAT_WCDMA;
                break;

            case AT_SYSCFGEX_RAT_GSM:
                pstRatOrder->aenRatOrder[i] = TAF_PH_RAT_GSM;
                break;

            default:
                AT_ERR_LOG("At_ConvertSysCfgExRat");
                break;
        }

    }

}





VOS_VOID AT_ReadRoamCfgInfoNvim(
    VOS_UINT8                           ucIndex
)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU          stRoamFeature;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRst;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    enModemId = MODEM_ID_0;
    ulLength  = 0;

    /* ��ȡModemId */
    ulRst = AT_GetModemIdFromClient(ucIndex, &enModemId);
    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG1("AT_ReadRoamCfgInfoNvim:Get ModemID From ClientID fail,ucIndex=%d", ucIndex);
        return;
    }


    stRoamFeature.ucRoamFeatureFlg = NV_ITEM_ACTIVE;
    stRoamFeature.ucRoamCapability = 0;

    NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Roam_Capa,
                         &stRoamFeature, ulLength))
    {
        AT_WARN_LOG("AT_ReadRoamCfgInfoNvim():WARNING: en_NV_Item_Roam_Capa Error");

        return;
    }

    if ((NV_ITEM_ACTIVE != stRoamFeature.ucRoamFeatureFlg)
     && (NV_ITEM_DEACTIVE != stRoamFeature.ucRoamFeatureFlg))
    {
        return;
    }

    pstNetCtx                = AT_GetModemNetCtxAddrFromModemId(enModemId);
    pstNetCtx->ucRoamFeature = stRoamFeature.ucRoamFeatureFlg;
    return;
}


VOS_UINT32 AT_ConvertSysCfgExRatOrderPara(
    VOS_UINT8                           ucClientId,
    TAF_PH_RAT_ORDER_STRU              *pstSysCfgExRatOrder
)
{
    VOS_UINT32                          ulRst;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRatOrder;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRatAutoNoChangeExistFlag;
    AT_SYSCFGEX_RAT_ORDER_STRU          stSyscfgExRatOrder;

    ucIndex                    = 0;
    ulRatAutoNoChangeExistFlag = VOS_FALSE;

    /* acqorder�ַ�������Ϊ���� */
    if ((gastAtParaList[0].usParaLen % 2) != 0)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* acqorder�ַ����������� */
    ulRst = At_CheckNumString(gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);
    if (ulRst != AT_SUCCESS)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* acqorder�ַ���������ż��������6Ҳ�Ƿ�,��01/02/03����� */
    if ((gastAtParaList[0].usParaLen / 2) > TAF_PH_MAX_GUL_RAT_NUM)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    for (i = 0; i < gastAtParaList[0].usParaLen; i += AT_SYSCFGEX_RAT_MODE_STR_LEN)
    {
        ulRst = At_String2Hex(&gastAtParaList[0].aucPara[i], AT_SYSCFGEX_RAT_MODE_STR_LEN, (VOS_UINT32 *)&ulRatOrder);
        if (AT_SUCCESS != ulRst)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ���ulRatOrder��0x99ʮ������������Ҫת��Ϊʮ���Ƶ�99 */
        if (AT_SYSCFGEX_RAT_NO_CHANGE_HEX_VALUE == ulRatOrder)
        {
            ulRatOrder = AT_SYSCFGEX_RAT_NO_CHANGE;
        }

        /* acqorder�ַ�������00/01/02/03/99����� */
        if ( VOS_FALSE == At_CheckSysCfgExRatTypeValid((AT_SYSCFGEX_RAT_TYPE_ENUM_UINT8)ulRatOrder) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ((AT_SYSCFGEX_RAT_AUTO == (AT_SYSCFGEX_RAT_TYPE_ENUM_UINT8)ulRatOrder)
         || (AT_SYSCFGEX_RAT_NO_CHANGE == (AT_SYSCFGEX_RAT_TYPE_ENUM_UINT8)ulRatOrder))
        {
            ulRatAutoNoChangeExistFlag = VOS_TRUE;
        }

        stSyscfgExRatOrder.aenRatOrder[ucIndex++] = (AT_SYSCFGEX_RAT_TYPE_ENUM_UINT8)ulRatOrder;

    }

    stSyscfgExRatOrder.ucRatOrderNum = ucIndex;

    /* acqorder�ַ�����00��99������ֵ����� */
    if ((VOS_TRUE == ulRatAutoNoChangeExistFlag)
     && (stSyscfgExRatOrder.ucRatOrderNum > 1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* acqorder�ַ���ģʽ�������ظ� */
    if ( VOS_TRUE == At_CheckRepeatedRatOrder(&stSyscfgExRatOrder) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��SYSCFGEX�Ľ��뼼����ʽת��ΪTAF_PH_RAT_ORDER_STRU�ṹ��ʽ */
    At_ConvertSysCfgExRat(ucClientId, &stSyscfgExRatOrder, pstSysCfgExRatOrder);

    return AT_OK;
}


VOS_UINT32 At_CheckRepeatedRatOrder(
    AT_SYSCFGEX_RAT_ORDER_STRU         *pstSyscfgExRatOrder
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    for (i = 0; i < pstSyscfgExRatOrder->ucRatOrderNum; i++)
    {
        for (j = i + 1; j < pstSyscfgExRatOrder->ucRatOrderNum; j++)
        {
            if (pstSyscfgExRatOrder->aenRatOrder[i] == pstSyscfgExRatOrder->aenRatOrder[j])
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 At_CheckSysCfgExRatTypeValid(
    VOS_UINT8                           ucRatOrder
)
{
    switch ( ucRatOrder )
    {
        case AT_SYSCFGEX_RAT_AUTO:
        case AT_SYSCFGEX_RAT_NO_CHANGE:
        case AT_SYSCFGEX_RAT_LTE:
        case AT_SYSCFGEX_RAT_WCDMA:
        case AT_SYSCFGEX_RAT_GSM:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }

}



VOS_UINT32 AT_ConvertSysCfgExBandPara(
    VOS_UINT8                          *pucPara,
    VOS_UINT16                          usLen,
    TAF_USER_SET_PREF_BAND64           *pstPrefBandPara
)
{
    VOS_UINT32                          ulRslt;

    pstPrefBandPara->ulBandHigh = 0;
    pstPrefBandPara->ulBandLow  = 0;

    /* ���Ƶ��Ϊ�գ�����ʧ��*/
    if (0 == usLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* Ƶ��ֵС��32λʱ */
    if (usLen <= AT_HEX_LEN_OF_ULONG_TYPE)
    {
        ulRslt = At_String2Hex(pucPara, usLen, &(pstPrefBandPara->ulBandLow));
    }
    else
    {
        /* 64λƵ�εĸ�32λ�ַ���ת��Ϊ16��������ת��ʧ�ܷ��� */
        ulRslt = At_String2Hex(pucPara, (usLen - AT_HEX_LEN_OF_ULONG_TYPE),
                               &(pstPrefBandPara->ulBandHigh));
        if (AT_FAILURE == ulRslt)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* 64λƵ�εĵ�32λ�ַ���ת��Ϊ16��������ת��ʧ�ܷ���  */
        ulRslt = At_String2Hex(pucPara + (usLen - AT_HEX_LEN_OF_ULONG_TYPE),
                               AT_HEX_LEN_OF_ULONG_TYPE, &(pstPrefBandPara->ulBandLow));
    }

    if (AT_FAILURE == ulRslt)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;

}


VOS_UINT32 AT_CheckSysCfgExPara(
    VOS_UINT8                           ucClientId,
    TAF_PH_SYS_CFG_EX_STRU             *pstSysCfgExSetPara
)
{
    VOS_UINT32                          ulRst;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucClientId);

    /* ����������,�����Ϊ7��������AT_CME_INCORRECT_PARAMETERS*/
    if ( AT_SYSCFGEX_PARA_NUM != gucAtParaIndex )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���acqorder�����Ϸ���,����Ϸ�,����ת������¼,������Ϸ�ֱ�ӷ���ʧ��*/
    ulRst = AT_ConvertSysCfgExRatOrderPara(ucClientId, &pstSysCfgExSetPara->stRatOrder);
    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    pstSysCfgExSetPara->enUserPrio = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    if ( VOS_FALSE == AT_IsSupportLMode(&pstSysCfgExSetPara->stRatOrder))
    {
        if ( TAF_PH_RAT_GSM == pstSysCfgExSetPara->stRatOrder.aenRatOrder[0])
        {
            pstSysCfgExSetPara->enUserPrio = TAF_MMA_USER_SET_PRIO_GSM_PREFER;
        }
        else
        {
            pstSysCfgExSetPara->enUserPrio = TAF_MMA_USER_SET_PRIO_AUTO;
        }
    }

    /* ������õ�ģʽ����L,�ҷ�������cs only������ʧ�� */
    if ((VOS_TRUE == AT_IsSupportLMode(&pstSysCfgExSetPara->stRatOrder))
     && ((TAF_PH_SERVICE_CS  == gastAtParaList[3].ulParaValue)
      || (TAF_PH_SERVICE_ANY == gastAtParaList[3].ulParaValue)))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���band�����Ϸ���,����Ϸ�,����ת������¼,������Ϸ�ֱ�ӷ���ʧ��*/
    ulRst = AT_ConvertSysCfgExBandPara(gastAtParaList[1].aucPara,
                                       gastAtParaList[1].usParaLen,
                                       &pstSysCfgExSetPara->stGuBand);
    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������δ����,��������ȡֵ��Χ0-2; �������Լ���,��������ȡֵ��Χ0-3 */
    AT_ReadRoamCfgInfoNvim(ucClientId);
    if (((AT_ROAM_FEATURE_OFF == pstNetCtx->ucRoamFeature) && (gastAtParaList[2].ulParaValue > AT_ROAM_FEATURE_OFF_NOCHANGE))
     || ((AT_ROAM_FEATURE_ON == pstNetCtx->ucRoamFeature) && (gastAtParaList[2].ulParaValue > TAF_PH_ROAM_NATIONAL_OFF_INTERNATIONAL_OFF)))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pstSysCfgExSetPara->ucRoam = (VOS_UINT8)gastAtParaList[2].ulParaValue;

    /* ���lteband�����Ϸ���,����Ϸ�,����ת������¼,������Ϸ�ֱ�ӷ���ʧ��*/
    ulRst = AT_ConvertSysCfgExBandPara(gastAtParaList[4].aucPara,
                                       gastAtParaList[4].usParaLen,
                                       &pstSysCfgExSetPara->stLBand);
    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������������·����������ģʽΪ�������� */
    pstSysCfgExSetPara->ucCmdType   = TAF_PH_CMD_SET;
    pstSysCfgExSetPara->ucSrvDomain = (VOS_UINT8)gastAtParaList[3].ulParaValue;

    return ulRst;

}
VOS_UINT32 AT_SetSysCfgExPara(
    VOS_UINT8                           ucIndex
)
{
    TAF_PH_SYS_CFG_EX_STRU              stSysCfgExSetPara;
    VOS_UINT32                          ulRst;

    PS_MEM_SET(&stSysCfgExSetPara, 0, sizeof(stSysCfgExSetPara));

    /* ���������ͺϷ��Լ��,���Ϸ�ֱ�ӷ���ʧ�� */
    ulRst = AT_CheckSysCfgExPara(ucIndex, &stSysCfgExSetPara);
    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��MMA���н������ɹ�����ʧ�ܣ������ɹ��������������״̬ */
    ulRst = Taf_SysCfgHandle(gastAtClientTab[ucIndex].usClientId, 0, stSysCfgExSetPara);
    if (AT_SUCCESS == ulRst)
    {
        /* ָʾ��ǰ�û��������������Ϊ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFG_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
VOS_UINT32 AT_GetValidNetScanPowerParam(
    VOS_INT16                          *psCellPower
)
{
    VOS_UINT32                          ulCellPower;

    ulCellPower = 0;

    /* power[-110,-47]���ȴ���4��С��3��ʾ��Ч���� */
    if ( (AT_NETSCAN_POWER_PARA_MAX_LEN < gastAtParaList[1].usParaLen)
      || (AT_NETSCAN_POWER_PARA_MIN_LEN > gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �ַ�����һ��������Ϊ'-'����Ϊ��Ч���� */
    if ( '-' != gastAtParaList[1].aucPara[0] )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* POWER���ַ�Ϊ'-',��ȡ�����ֵ */
    if ( AT_SUCCESS != atAuc2ul( &gastAtParaList[1].aucPara[1],
                                 gastAtParaList[1].usParaLen - 1,
                                 &ulCellPower) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����POWERֵΪ��������ת���� */
    *psCellPower = -(VOS_INT16)ulCellPower;

    /* powerȡֵ�ж�[-110,-47] */
    if ( (AT_NETSCAN_POWER_MIN_VALUE > *psCellPower)
      || (AT_NETSCAN_POWER_MAX_VALUE < *psCellPower) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;
}
VOS_UINT32 AT_GetValidNetScanBandPara(
    TAF_USER_SET_PREF_BAND64           *pstPrefBandPara
)
{
    VOS_UINT8                          *pucPara             = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usLen;

    pucPara         = gastAtParaList[3].aucPara;
    usLen           = gastAtParaList[3].usParaLen;

    pstPrefBandPara->ulBandHigh = 0;
    pstPrefBandPara->ulBandLow  = 0;

    /* ���Ƶ��Ϊ�գ�����Ϊ��ȫƵ������ */
    if (0 == usLen)
    {
        pstPrefBandPara->ulBandHigh = 0;
        pstPrefBandPara->ulBandLow  = AT_ALL_GU_BAND;

        return AT_OK;
    }

    /* Ƶ��ֵС��32λʱ */
    if (usLen <= AT_HEX_LEN_OF_ULONG_TYPE)
    {
        ulRslt = At_String2Hex(pucPara, usLen, &(pstPrefBandPara->ulBandLow));
    }
    else
    {
        /* 64λƵ�εĸ�32λ�ַ���ת��Ϊ16��������ת��ʧ�ܷ��� */
        ulRslt = At_String2Hex(pucPara, (usLen - AT_HEX_LEN_OF_ULONG_TYPE),
                               &(pstPrefBandPara->ulBandHigh));
        if (AT_FAILURE == ulRslt)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* 64λƵ�εĵ�32λ�ַ���ת��Ϊ16��������ת��ʧ�ܷ���  */
        ulRslt = At_String2Hex(pucPara + (usLen - AT_HEX_LEN_OF_ULONG_TYPE),
                               AT_HEX_LEN_OF_ULONG_TYPE, &(pstPrefBandPara->ulBandLow));
    }

    if (AT_FAILURE == ulRslt)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;
}



VOS_UINT32 AT_GetValidNetScanPara(
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScanSetPara
)
{
    VOS_UINT32                          ulRst;

    /* ����������,�������4��������AT_CME_INCORRECT_PARAMETERS*/
    if ( (AT_NETSCAN_PARA_MAX_NUM < gucAtParaIndex)
      || (AT_NETSCAN_PARA_MIN_NUM > gucAtParaIndex) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������У�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����CellNum */
    pstNetScanSetPara->usCellNum = (VOS_UINT16)gastAtParaList[0].ulParaValue;

    /* ����CellPow */
    if (AT_OK != AT_GetValidNetScanPowerParam(&(pstNetScanSetPara->sCellPow)))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ȱʡ<mode>����������ȱʡ<band>����������Ϊ�������� */
    if ( (0 == gastAtParaList[2].usParaLen)
      && (0 != gastAtParaList[3].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����û�û������뼼������gastAtParaList[2].ulParaValue����0 */
    if ( 0 == gastAtParaList[2].usParaLen )
    {
        pstNetScanSetPara->ucRat     = TAF_PH_RAT_GSM;
    }
    else
    {
        pstNetScanSetPara->ucRat     = (VOS_UINT8)gastAtParaList[2].ulParaValue;
    }


    /* ���band�����Ϸ���,����Ϸ�,����ת������¼,������Ϸ�ֱ�ӷ���ʧ��*/
    ulRst = AT_GetValidNetScanBandPara(&pstNetScanSetPara->stBand);

    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return ulRst;
}
VOS_UINT32 AT_SetNetScan(
    VOS_UINT8                           ucIndex
)
{
    TAF_MMA_NET_SCAN_REQ_STRU           stNetScanSetPara;
    VOS_UINT32                          ulRst;

    PS_MEM_SET(&stNetScanSetPara, 0, sizeof(stNetScanSetPara));

    /* ���������ͺϷ��Լ��,���Ϸ�ֱ�ӷ���ʧ�� */
    ulRst = AT_GetValidNetScanPara(&stNetScanSetPara);

    if (AT_OK != ulRst)
    {
        return ulRst;
    }

    /* ��MMA���н������ɹ�����ʧ�ܣ������ɹ��������������״̬ */
    ulRst = Taf_NetScanHandle(gastAtClientTab[ucIndex].usClientId, 0, &stNetScanSetPara);
    if (AT_SUCCESS == ulRst)
    {
        /* ָʾ��ǰ�û��������������Ϊ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NETSCAN_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 AT_AbortNetScan(
    VOS_UINT8                           ucIndex
)
{
    /* ��ǰֻ�ܴ���NETSCAN���õĴ��, ���������򲻽��д�ϲ��� */
    if ( AT_CMD_NETSCAN_SET == gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        /* AT��MMA���ʹ��NETSCAN������ */
        if ( AT_SUCCESS == Taf_AbortNetScan(gastAtClientTab[ucIndex].usClientId, 0) )
        {
            /* ֹͣNETSCANAT�ı�����ʱ�� */
            AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);

            /* ���µ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ABORT_NETSCAN;

            return AT_WAIT_ASYNC_RETURN;
        }

        /* AT��MMA���ʹ��NETSCAN������ʧ�ܣ�����ʧ�� */
        return AT_FAILURE;
    }

    /* ��ǰ�������������ʧ�� */
    return AT_FAILURE;
}




VOS_VOID AT_ChangeSysCfgRatPrio(
    TAF_PH_RAT_ORDER_STRU              *pstRatOrder,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8       enAcqorder

)
{
    if (TAF_PH_MAX_GU_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        if (((AT_SYSCFG_RAT_PRIO_AUTO == enAcqorder)
         || (AT_SYSCFG_RAT_PRIO_WCDMA == enAcqorder)))
        {
            pstRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
            pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_WCDMA;
            pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_GSM;
            pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
        }
        else if (AT_SYSCFG_RAT_PRIO_GSM == enAcqorder)
        {
            pstRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
            pstRatOrder->aenRatOrder[0] = TAF_PH_RAT_GSM;
            pstRatOrder->aenRatOrder[1] = TAF_PH_RAT_WCDMA;
            pstRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
        }
        else
        {
        }

    }
    else
    {
        /* ԭ��ģ���迼�ǽ������ȼ� */
    }

}
VOS_UINT32 AT_ConvertSysCfgRatOrderPara(
    VOS_UINT8                           ucClientId,
    AT_SYSCFG_RAT_TYPE_ENUM_UINT8       enRatMode,
    AT_SYSCFG_RAT_PRIO_ENUM_UINT8       enAcqorder,
    TAF_PH_RAT_ORDER_STRU              *pstSysCfgRatOrder
)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRst;

    enModemId = MODEM_ID_0;
    /* ��ȡModemId */
    ulRst = AT_GetModemIdFromClient(ucClientId, &enModemId);
    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG1("AT_ConvertSysCfgRatOrderPara:Get ModemID From ClientID fail,ClientID=%d", ucClientId);
        return AT_ERROR;
    }
    switch (enRatMode)
    {
        case AT_SYSCFG_RAT_AUTO:
            /* ����������ȼ����ı���Ĭ�ϴ�NVIM�л�ȡ */
            if ( AT_SYSCFG_RAT_PRIO_NO_CHANGE == enAcqorder )
            {
                AT_GetGuAccessPrioNvim(enModemId, &enAcqorder);
            }


            /* ucAcqorderΪ0�Զ�����WCDMA��GSM*/

            if (AT_SYSCFG_RAT_PRIO_AUTO == enAcqorder)
            {
                AT_SetDefaultRatPrioList(enModemId, pstSysCfgRatOrder, VOS_FALSE);
            }
            else if (AT_SYSCFG_RAT_PRIO_WCDMA == enAcqorder)
            {
                pstSysCfgRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
                pstSysCfgRatOrder->aenRatOrder[0] = TAF_PH_RAT_WCDMA;
                pstSysCfgRatOrder->aenRatOrder[1] = TAF_PH_RAT_GSM;
                pstSysCfgRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            }
            else if (AT_SYSCFG_RAT_PRIO_GSM == enAcqorder)
            {
                pstSysCfgRatOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
                pstSysCfgRatOrder->aenRatOrder[0] = TAF_PH_RAT_GSM;
                pstSysCfgRatOrder->aenRatOrder[1] = TAF_PH_RAT_WCDMA;
                pstSysCfgRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            }
            else
            {

            }

            break;

        case AT_SYSCFG_RAT_GSM:
            /* G��ģ */
            pstSysCfgRatOrder->ucRatOrderNum  = 1;
            pstSysCfgRatOrder->aenRatOrder[0] = TAF_PH_RAT_GSM;
            pstSysCfgRatOrder->aenRatOrder[1] = TAF_PH_RAT_BUTT;
            pstSysCfgRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            break;

        case AT_SYSCFG_RAT_WCDMA:
            /* W��ģ*/
            pstSysCfgRatOrder->ucRatOrderNum  = 1;
            pstSysCfgRatOrder->aenRatOrder[0] = TAF_PH_RAT_WCDMA;
            pstSysCfgRatOrder->aenRatOrder[1] = TAF_PH_RAT_BUTT;
            pstSysCfgRatOrder->aenRatOrder[2] = TAF_PH_RAT_BUTT;
            break;

        case AT_SYSCFG_RAT_NO_CHANGE:
            AT_GetRatOrderNvim(enModemId, pstSysCfgRatOrder, VOS_FALSE);
            AT_GetOnlyGURatOrder(pstSysCfgRatOrder);
            AT_ChangeSysCfgRatPrio(pstSysCfgRatOrder, enAcqorder);
            break;

        default:
            return AT_CME_INCORRECT_PARAMETERS;

    }


    /*���سɹ�*/
    return AT_OK;
}



VOS_UINT32 At_SetSysCfgPara(VOS_UINT8 ucIndex)
{
    TAF_PH_SYS_CFG_EX_STRU              stSysCfgSetPara;
    VOS_UINT32                          ulRst;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    if ( 5 != gucAtParaIndex )
    {                                                                           /* �������� */
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((gastAtParaList[0].usParaLen == 0)
     || (gastAtParaList[1].usParaLen == 0)
     || (gastAtParaList[2].usParaLen == 0)
     || (gastAtParaList[3].usParaLen == 0)
     || (gastAtParaList[4].usParaLen == 0))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stSysCfgSetPara.ucCmdType = TAF_PH_CMD_SET;


    ulRst = AT_ConvertSysCfgRatOrderPara(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue,
                                         (VOS_UINT8)gastAtParaList[1].ulParaValue,
                                         &stSysCfgSetPara.stRatOrder);
    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stSysCfgSetPara.enUserPrio = (VOS_UINT8)gastAtParaList[1].ulParaValue;



    ulRst = AT_ConvertSysCfgExBandPara(gastAtParaList[2].aucPara,
                                       gastAtParaList[2].usParaLen,
                                       &stSysCfgSetPara.stGuBand);
    if (AT_OK != ulRst)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��Ҫ��L��Ƶ������Ϊ���ı� */
    stSysCfgSetPara.stLBand.ulBandLow  = TAF_PH_BAND_NO_CHANGE;
    stSysCfgSetPara.stLBand.ulBandHigh = 0;
    AT_ReadRoamCfgInfoNvim(ucIndex);

    if (((AT_ROAM_FEATURE_OFF == pstNetCtx->ucRoamFeature) && (gastAtParaList[3].ulParaValue > 2))
     || ((AT_ROAM_FEATURE_ON == pstNetCtx->ucRoamFeature) && (gastAtParaList[3].ulParaValue > 3)))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stSysCfgSetPara.ucRoam      = (VOS_UINT8) gastAtParaList[3].ulParaValue;
    stSysCfgSetPara.ucSrvDomain = (VOS_UINT8) gastAtParaList[4].ulParaValue;

    /* ִ��������� */
    if (AT_SUCCESS == Taf_SysCfgHandle(gastAtClientTab[ucIndex].usClientId, 0,stSysCfgSetPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFG_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_CheckDataState
 Description    :
 Input          :
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    �� : 2007-03-27
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_CheckDataState(TAF_UINT8 ucDataMode)
{
    TAF_UINT8 ucIndex = 0;

    for(ucIndex = 0; ucIndex < AT_MAX_CLIENT_NUM; ucIndex++)
    {
        if( (AT_CLIENT_USED == gastAtClientTab[ucIndex].ucUsed)
         && (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
         && (ucDataMode == gastAtClientTab[ucIndex].DataMode))
        {
            return AT_SUCCESS;
        }
    }

    return AT_FAILURE;
}


/*****************************************************************************
 Prototype      : At_SetCcinPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetCcinPara(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��� ����������Ϊ���������ϱ�ģʽ��
       ����OK�����л���ǰ�û�Ϊ�����ϱ�ģʽ��
       ��� ����������Ϊֹͣ�����ϱ�ģʽ��
       ����OK�����л���ǰ�û�Ϊ��ͨ����ģʽ��*/

    gastAtClientTab[ucIndex].IndMode = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    return AT_OK;
}

TAF_UINT32 At_SetTrigPara (TAF_UINT8 ucIndex)
{
    TAF_UINT8                           i;
    TAF_GPRS_DATA_STRU                  stGprsDataInfo;


    PS_MEM_SET(&stGprsDataInfo, 0x00, sizeof(stGprsDataInfo));


    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(5 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    for(i=0;i<5;i++)
    {
        if (0==gastAtParaList[i].usParaLen)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    stGprsDataInfo.ucMode = (TAF_UINT8)gastAtParaList[0].ulParaValue;
    if ((stGprsDataInfo.ucMode!=0) && (stGprsDataInfo.ucMode!=1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    if((5 <= gastAtParaList[1].ulParaValue) && (gastAtParaList[1].ulParaValue <= 15))
    {
        stGprsDataInfo.ucNsapi = (TAF_UINT8)gastAtParaList[1].ulParaValue;
    }
    else
    {
        return AT_ERROR;
    }

    stGprsDataInfo.ulLength      = (TAF_UINT32)gastAtParaList[2].ulParaValue;
    stGprsDataInfo.ucTimes       = (TAF_UINT8)gastAtParaList[3].ulParaValue;
    stGprsDataInfo.ulMillisecond = (TAF_UINT32)gastAtParaList[4].ulParaValue;

    /* ִ��������� */
    if ( TAF_PS_TrigGprsData(WUEPS_PID_AT,
                             gastAtClientTab[ucIndex].usClientId,
                             gastAtClientTab[ucIndex].opId,
                             &stGprsDataInfo) )
    {
        return AT_ERROR;
    }

    return AT_OK;
}
TAF_UINT32 At_SetGcfIndPara (TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucGctTestFlag;
    VOS_UINT32                          ulRst;

    ucGctTestFlag = 0;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucGctTestFlag = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    if ((ucGctTestFlag != 0) && (ucGctTestFlag != 1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_GCF_IND,
                                   &ucGctTestFlag,
                                   sizeof(VOS_UINT8),
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }

}
VOS_UINT32 At_SetGcapPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16           usLength = 0;

    if(0 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %s",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"+CGSM,+DS,+ES");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_SetMsIdInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_MSID_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MSID_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


TAF_UINT32 AT_SetDsFlowClrPara(TAF_UINT8 ucIndex)
{
    TAF_DSFLOW_CLEAR_CONFIG_STRU        stClearConfigInfo;

    /* ������� */
    if ( AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stClearConfigInfo, 0x00, sizeof(TAF_DSFLOW_CLEAR_CONFIG_STRU));

    /* ���ò��� */
    stClearConfigInfo.enClearMode       = TAF_DSFLOW_CLEAR_TOTAL;

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_ClearDsFlowInfo(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0, &stClearConfigInfo))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_DSFLOWCLR_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_SetDsFlowQryPara(TAF_UINT8 ucIndex)
{

    /* ������� */
    if ( AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetDsFlowInfo(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_DSFLOWQRY_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_SetDsFlowRptPara(TAF_UINT8 ucIndex)
{
    TAF_DSFLOW_REPORT_CONFIG_STRU       stReportConfigInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stReportConfigInfo, 0x00, sizeof(TAF_DSFLOW_REPORT_CONFIG_STRU));

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ò��� */
    stReportConfigInfo.ulRptEnabled         = gastAtParaList[0].ulParaValue;


    if ( VOS_TRUE == stReportConfigInfo.ulRptEnabled )
    {
        /* ���������ϱ�����ʱ�� */
        stReportConfigInfo.ulTimerLength    = 2000;
    }


    /* ִ��������� */
    if ( VOS_OK != TAF_PS_ConfigDsFlowRpt(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0, &stReportConfigInfo))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_DSFLOWRPT_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 At_SetSrvstPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.enReqType       = AT_MTA_SET_SRVST_RPT_TYPE;
    stAtCmd.u.ucSrvstRptFlg = 0;

    if (0 != gastAtParaList[0].usParaLen)
    {
        stAtCmd.u.ucSrvstRptFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    /* ��MTA����^srvst�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 At_SetRssiPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

#if(FEATURE_ON == FEATURE_LTE)
    L4A_IND_CFG_STRU                        stL4AIndCfgReq;
    MODEM_ID_ENUM_UINT16                    enModemId;

    enModemId  = MODEM_ID_0;
#endif

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.enReqType       = AT_MTA_SET_RSSI_RPT_TYPE;
    stAtCmd.u.ucRssiRptFlg  = AT_RSSI_RESULT_CODE_NOT_REPORT_TYPE;

    if (0 != gastAtParaList[0].usParaLen)
    {
        stAtCmd.u.ucRssiRptFlg  = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    /* ��MTA����^rssi�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

#if  (FEATURE_ON == FEATURE_LTE)
    ulResult = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulResult)
    {
        AT_ERR_LOG1("At_SetRssiPara:Get ModemID From ClientID fail,ClientID=%d", ucIndex);
        return AT_ERROR;
    }

    if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE))
    {
        PS_MEM_SET(&stL4AIndCfgReq, 0, sizeof(stL4AIndCfgReq));
        stL4AIndCfgReq.rssi_bit_valid  = VOS_TRUE;
        stL4AIndCfgReq.rssi_bit        = gastAtParaList[0].ulParaValue;

        /* ֪ͨL�˴�mode������ */
        AT_SetLIndCfgReq(ucIndex, &stL4AIndCfgReq);
    }
#endif

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;

}



VOS_UINT32 At_SetCerssiPara(VOS_UINT8 ucIndex)
{
    TAF_START_INFO_IND_STRU             stStartInfoInd;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

#if  (FEATURE_ON == FEATURE_LTE)
    L4A_IND_CFG_STRU                    stL4AIndCfgReq;
    VOS_UINT32                          ulRptFlg;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRst;

    enModemId = MODEM_ID_0;
#endif

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);


    PS_MEM_SET(&stStartInfoInd, 0x00, sizeof(stStartInfoInd));

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((gucAtParaIndex > 2)
     || (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }




    if (1 == gucAtParaIndex)
    {
        pstNetCtx->ucCerssiReportType        = 0;
        pstNetCtx->ucCerssiMinTimerInterval  = 0;
        stStartInfoInd.ucMinRptTimerInterval = 0;
    }

    if (2 == gucAtParaIndex)
    {
        pstNetCtx->ucCerssiMinTimerInterval  = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        stStartInfoInd.ucMinRptTimerInterval = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    }

    if (0 != gastAtParaList[0].ulParaValue)
    {
        pstNetCtx->ucCerssiReportType  = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        stStartInfoInd.ucActionType    = TAF_START_EVENT_INFO_FOREVER;
        stStartInfoInd.ucSignThreshold = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        stStartInfoInd.ucRrcMsgType    = TAF_EVENT_INFO_CELL_SIGN;
#if  (FEATURE_ON == FEATURE_LTE)
        ulRptFlg                       = VOS_TRUE;
#endif
    }
    else
    {
        /* ����+creg/+cgreg/+csq/^rssi����ͨ��RRMM_AT_MSG_REQ��GRRMM_AT_MSG_REQ֪ͨ����������ϱ���
           ���Բ���֪ͨ�����ֹͣ�����ó�Ĭ��rssi 5db�ı��ϱ���AT_GetModemNetCtxAddrFromClientId(ucIndex)->ucCerssiReportTypeȫ�ֱ�������^cerssi�Ƿ��ϱ� */
        stStartInfoInd.ucActionType     = TAF_START_EVENT_INFO_FOREVER;
        stStartInfoInd.ucRrcMsgType     = TAF_EVENT_INFO_CELL_SIGN;
        stStartInfoInd.ucSignThreshold  = 0;
        pstNetCtx->ucCerssiReportType   = AT_CERSSI_REPORT_TYPE_NOT_REPORT;
        pstNetCtx->ucCerssiMinTimerInterval  = 0;
        stStartInfoInd.ucMinRptTimerInterval = 0;
#if  (FEATURE_ON == FEATURE_LTE)
        ulRptFlg                        = VOS_FALSE;
#endif

    }

    Taf_PhoneStartInfoInd(gastAtClientTab[ucIndex].usClientId, 0, stStartInfoInd);

#if  (FEATURE_ON == FEATURE_LTE)
    ulRst = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG1("At_SetCerssiPara:Get ModemID From ClientID fail,ClientID=%d", ucIndex);
        return AT_ERROR;
    }

    if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE))
    {
        PS_MEM_SET(&stL4AIndCfgReq, 0, sizeof(stL4AIndCfgReq));
        stL4AIndCfgReq.cerssi_bit_valid  = VOS_TRUE;
        stL4AIndCfgReq.cerssi_bit        = ulRptFlg;

        /* ֪ͨL�˴�curc������ */
        return AT_SetLIndCfgReq(ucIndex, &stL4AIndCfgReq);
    }
    else
    {
        return AT_OK;
    }

#else
    return AT_OK;
#endif
}
VOS_UINT32 At_SetCnmrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    AT_MTA_QRY_NMR_REQ_STRU             stQryNmrReq;

    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

#if  (FEATURE_ON == FEATURE_LTE)
    /* ��ѯ4g��nmr����ֱ�ӵ���L�Ľӿ� */
    if (AT_CNMR_QRY_LTE_NMR_DATA == gastAtParaList[0].ulParaValue)
    {
        return At_QryCnmrPara(ucIndex);
    }
#else
    /* ��ѯ4g��nmr����ֱ�ӷ���ʧ�� */
    if (AT_CNMR_QRY_LTE_NMR_DATA == gastAtParaList[0].ulParaValue)
    {
        return AT_ERROR;
    }
#endif

    /* ������ϢDRV_AGENT_AS_QRY_NMR_REQ��C�˴��� */
    PS_MEM_SET(&stQryNmrReq, 0x0, sizeof(stQryNmrReq));

    if (AT_CNMR_QRY_WAS_NMR_DATA == gastAtParaList[0].ulParaValue)
    {
        stQryNmrReq.ucRatType = 0;
    }
    else
    {
        stQryNmrReq.ucRatType = 1;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_QRY_NMR_REQ,
                                   &stQryNmrReq,
                                   sizeof(stQryNmrReq),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CNMR_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}





TAF_UINT32  At_SetTimePara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if ((0 == gastAtParaList[0].usParaLen) || (2 < gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.enReqType       = AT_MTA_SET_TIME_RPT_TYPE;
    stAtCmd.u.ucTimeRptFlg  = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ��MTA����^time�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;

}
TAF_UINT32  At_SetCtzrPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if ((0 == gastAtParaList[0].usParaLen) || (2 < gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.enReqType       = AT_MTA_SET_CTZR_RPT_TYPE;
    stAtCmd.u.ucCtzrRptFlg  = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ��MTA����^ctzr�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;

}
TAF_UINT32 At_SetModePara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;
 #if (FEATURE_ON==FEATURE_LTE)
    L4A_IND_CFG_STRU                        stL4AIndCfgReq;
    MODEM_ID_ENUM_UINT16                    enModemId;

    enModemId  = MODEM_ID_0;
#endif

    /* AT��������Ϸ��Լ�� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.enReqType       = AT_MTA_SET_MODE_RPT_TYPE;
    stAtCmd.u.ucModeRptFlg  = AT_MODE_RESULT_CODE_NOT_REPORT_TYPE;

    if (0 != gastAtParaList[0].usParaLen)
    {
        stAtCmd.u.ucModeRptFlg  = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    /* ��MTA����^mode�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

#if  (FEATURE_ON == FEATURE_LTE)
    ulResult = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulResult)
    {
        AT_ERR_LOG1("At_SetModePara:Get ModemID From ClientID fail,ClientID=%d", ucIndex);
        return AT_ERROR;
    }

    if (VOS_TRUE == AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE))
    {
        PS_MEM_SET(&stL4AIndCfgReq, 0, sizeof(stL4AIndCfgReq));
        stL4AIndCfgReq.mode_bit_valid  = 1;
        stL4AIndCfgReq.mode_bit        = gastAtParaList[0].ulParaValue;

        /* ֪ͨL�˴�mode������ */
        AT_SetLIndCfgReq(ucIndex, &stL4AIndCfgReq);
    }
#endif

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;

}
VOS_UINT32 At_SetSimstPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.enReqType       = AT_MTA_SET_SIMST_RPT_TYPE;
    stAtCmd.u.ucSimstRptFlg = AT_SIMST_ENABLE_TYPE;

    if (0 != gastAtParaList[0].usParaLen)
    {
        stAtCmd.u.ucSimstRptFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_SET;

    return AT_WAIT_ASYNC_RETURN;
}
/*****************************************************************************
 �� �� ��  : At_SetHsPara
 ��������  : ϵͳģʽ��ϵͳ��ģʽ�仯�����ϱ�
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��06��13��
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_UINT32 At_SetHSPara(TAF_UINT8 ucIndex)
{
    TAF_UINT8 aucBuf[5];
    TAF_VOID* pPara;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[0].usParaLen)
    {
        PS_MEM_CPY(aucBuf, &gastAtParaList[0].ulParaValue, sizeof(TAF_UINT32));
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 != gastAtParaList[1].usParaLen)
    {
        aucBuf[4] = (TAF_UINT8)gastAtParaList[1].ulParaValue;
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pPara = aucBuf;
    /* ִ�������������Щ�������Բ��÷��͵�MMA */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,
                                   TAF_PH_HS_PARA,pPara))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HS_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 AT_UpdateSvn(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           aucSvn[],
    VOS_UINT16                          usSvnLength
)
{
    TAF_SVN_DATA_STRU                   stSvn;


    PS_MEM_SET(&stSvn, 0x00, sizeof(stSvn));


    /* SVN ���ȼ��: �û������SVN�̶�����ӦΪ2λ */
    if (TAF_SVN_DATA_LENGTH != usSvnLength)
    {
        AT_NORM_LOG("AT_UpdateSvn: the length of SVN is error.");
        return AT_PHYNUM_LENGTH_ERR;
    }

    /* SVN �ַ������1: ȷ��<SVN>Ϊ�����ַ���, ����ASCII��ת����BCD�� */
    if (AT_SUCCESS != At_AsciiNum2Num(stSvn.aucSvn, aucSvn, usSvnLength))
    {
        AT_NORM_LOG("AT_UpdateSvn: the number of SVN is error.");
        return AT_PHYNUM_NUMBER_ERR;
    }

    /* SVN �ַ������2: 99��SVN�ı�����ֵ������AT_PHYNUM_NUMBER_ERR�����Ŵ���
       �ο�Э��: 3GPP 23003 6.3 Allocation principles SVN value 99 is reserved for future use. */
    if ((9 == stSvn.aucSvn[0]) && (9 == stSvn.aucSvn[1]))
    {
        AT_NORM_LOG("AT_UpdateSvn: the number of SVN is reserved.");
        return AT_PHYNUM_NUMBER_ERR;
    }

    /* ����SVN��NV����־Ϊ����˱�־Ĭ��Ϊδ��� */
    stSvn.ucActiveFlag = NV_ITEM_ACTIVE;

    /* �����Ч��ĩλ�ֽ� */
    stSvn.aucReserve[0] = 0;

    if (NV_OK !=  NV_WriteEx(enModemId, en_NV_Item_Imei_Svn, &stSvn, sizeof(stSvn)))
    {
         AT_WARN_LOG("AT_UpdateSvn: Fail to write NV.");
         return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_CheckPhyNumPara
 ��������  : �豸�����ò�����飬���ͨ�����������������
 �������  : ��
 �������  : AT_PHYNUM_TYPE_ENUM_UINT32 *penSetType ���������������
 �� �� ֵ  : VOS_UINT32 �豸�����ò����������
             AT_OK              �������ͨ����
             AT_PHYNUM_TYPE_ERR ���������ʹ���
             AT_ERROR��         TIMES������鲻ͨ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��11��
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��3��
    �޸�����   : С������Ŀ�����Ӷ�MAC���͵�֧��
*****************************************************************************/
VOS_UINT32 AT_CheckPhyNumPara(AT_PHYNUM_TYPE_ENUM_UINT32 *penSetType)
{
    VOS_UINT32                          ulTimes;
    VOS_UINT32                          ulRet;

    /* <type>�������: BALONG��֧������������ΪIMEI��SVN��
       ����ֱ�ӷ��ش���< err_code > ������Ϊ1�����Ų��Ϸ� */
    /* ȫ����ʽ��Ϊ��д�ַ� */
    if(AT_FAILURE == At_UpString(gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    if (0 == VOS_StrCmp((VOS_CHAR *)gastAtParaList[0].aucPara, "IMEI"))
    {
        *penSetType = AT_PHYNUM_TYPE_IMEI;
    }
    else if (0 == VOS_StrCmp((VOS_CHAR *)gastAtParaList[0].aucPara, "SVN"))
    {
        *penSetType = AT_PHYNUM_TYPE_SVN;
    }
    else if (0 == VOS_StrCmp((VOS_CHAR *)gastAtParaList[0].aucPara, "MACWLAN"))
    {
        *penSetType = AT_PHYNUM_TYPE_MAC;
    }
    else
    {
        AT_NORM_LOG("AT_CheckPhyNumPara: the type of physical is error.");
        return AT_PHYNUM_TYPE_ERR;
    }

    /* < times >�������: ����< times >��ΧΪ0-1�����򷵻�AT_ERROR */
    if (gastAtParaList[2].usParaLen != 0)
    {
        /* TIMES��ȡֵ��Χ��0��1 */
        ulRet = At_Auc2ul(gastAtParaList[2].aucPara,
                          gastAtParaList[2].usParaLen,
                          &ulTimes);
        if ((AT_SUCCESS != ulRet) || (ulTimes > 1))
        {
            AT_NORM_LOG("AT_CheckPhyNumPara: times error.");
            return AT_ERROR;
        }
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetPhyNumPara
 ��������  : ���������������
             AT^PHYNUM =<type>,<number>[,< times >
 �������  : VOS_UINT8 ucIndex �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ATC������
             AT_OK                  ���ò����ɹ�
             AT_PHYNUM_LENGTH_ERR   �����ų��ȴ���
             AT_PHYNUM_NUMBER_ERR   �����Ų��Ϸ�
                                    �����ݱ���δ�������󣬸ô���ԭ�����Ʒ��ȷ��
             AT_PHYNUM_TYPE_ERR     ���������ʹ���
             AT_ERROR               MT��ش����TIMES��Χ����ʱ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��8��2��
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��1��3��
    �޸�����   : SMALL IMAGE���Ժ���: ֧��MAC��ַ����
  3.��    ��   : 2013��3��4��
    �޸�����   : DSDA PHASE II
*****************************************************************************/
VOS_UINT32  AT_SetPhyNumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_PHYNUM_TYPE_ENUM_UINT32          enSetType;
    VOS_BOOL                            bPhyNumIsNull;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;

    /* ����������Ч�Լ��: �������ٰ���<type>,<number>�����֣�
       �������ٰ���< times > �������������󣬷���AT_ERROR */
    if ((2 != gucAtParaIndex) && (3 != gucAtParaIndex))
    {
        AT_NORM_LOG("AT_SetPhyNumPara: the number of parameter is error.");
        return AT_ERROR;
    }

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_SetPhyNumPara: Get modem id fail.");
        return AT_ERROR;
    }

    ulRet = AT_CheckPhyNumPara(&enSetType);
    if (AT_OK != ulRet)
    {
        return ulRet;
    }

    /* �����Ų�Ϊ�գ������ݱ���δ������ֱ�ӷ��ش���< err_code > ������Ϊ1�����Ų��Ϸ��� */
    if (AT_OK != AT_PhyNumIsNull(enModemId, enSetType, &bPhyNumIsNull))
    {
        return AT_ERROR;
    }

    if ((VOS_FALSE == bPhyNumIsNull) && (VOS_TRUE == g_bAtDataLocked))
    {
        AT_NORM_LOG("AT_SetPhyNumPara: physical number is not null and data locked.");
        return AT_PHYNUM_TYPE_ERR;
    }

    /* ����ǰ�û����õ�������ΪIMEI�����޸�en_NV_Item_IMEI�е����� */
    /* ����ǰ�û����õ�������ΪSVN�����޸�en_Nv_Item_Imei_Svn�е����� */
    /* ����ǰ�û����õ�������ΪMAC�����޸�MAC��ַ��Ӧ��NV��(�������ݿ�MAC��ַ��NV��)�е����� */
    if (AT_PHYNUM_TYPE_IMEI == enSetType)
    {
        ulRet = AT_UpdateImei(enModemId, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
    }
    else if (AT_PHYNUM_TYPE_SVN == enSetType)
    {
        ulRet = AT_UpdateSvn(enModemId, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
    }
    else
    {
        /*����MAC��ַ��NV*/
        ulRet = AT_UpdateMacPara(gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
    }

    return ulRet;
}
VOS_UINT32 AT_SetGTimerPara(VOS_UINT8 ucIndex)
{

    /* �����������󣬷���AT_DEVICE_OTHER_ERROR���ϱ�CME ERROR:1 */
    if (1 != gucAtParaIndex)
    {
        AT_NORM_LOG("AT_SetGTimerPara: the number of parameter is error.");
        return AT_ERROR;
    }

    /* ���ݱ���δ����������AT_DATA_UNLOCK_ERROR���ϱ�CME ERROR:0 */
    if (g_bAtDataLocked != VOS_FALSE)
    {
        AT_NORM_LOG("AT_SetGTimerPara: data locked.");
        return AT_ERROR;
    }

    if (NV_OK !=  NV_WriteEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                           &gastAtParaList[0].ulParaValue,
                           sizeof(gastAtParaList[0].ulParaValue)))
    {
         AT_WARN_LOG("AT_SetGTimerPara: Fail to write en_NV_Item_GPRS_ActiveTimerLength.");
         return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_SetQcdmgPara
 ��������  : AT$QCDMG (����������USB COM����·��ATͨ����DIAGͨ�����л�)
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��06��10��
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��6��
    �޸�����   : AT Project: ֪ͨOM�˿��л�
*****************************************************************************/
TAF_UINT32 At_SetQcdmgPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������������� */
    if(0 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ucIndex����Ӧ��ATͨ������PCUI/UARTͨ�� */
    if ((AT_USB_COM_PORT_NO != gastAtClientTab[ucIndex].ucPortNo)
     && (AT_UART_PORT_NO != gastAtClientTab[ucIndex].ucPortNo))
    {
        return AT_ERROR;
    }

    /*����Ƿ����д���DIAGģʽ��ͨ��*/
    if(AT_SUCCESS == At_CheckDataState(AT_DIAG_DATA_MODE))
    {
        return AT_ERROR;
    }

    /*��¼AT/DIAGͨ������Ӧ��������*/
    gucOmDiagIndex = ucIndex;

    /* ֪ͨOAM�л���DIAGģʽ */
    if (AT_USB_COM_PORT_NO == gastAtClientTab[ucIndex].ucPortNo)
    {
        CPM_NotifyChangePort(AT_PCUI_PORT, CPM_DIAG_COMM);
    }
    else
    {
        CPM_NotifyChangePort(AT_UART_PORT, CPM_DIAG_COMM);
    }

    /*��ͨ��ģʽ����ΪDIAGģʽ*/
    At_SetMode(gucOmDiagIndex, AT_DATA_MODE, AT_DIAG_DATA_MODE);

    return AT_OK;
}
TAF_UINT32 At_SetU2DiagPara(TAF_UINT8 ucIndex)
{
    AT_USB_ENUM_STATUS_STRU             stUsbEnumStatus;

    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;


    PS_MEM_SET(&stUsbEnumStatus, 0x00, sizeof(stUsbEnumStatus));

    stPidEnableType.ulPidEnabled = VOS_FALSE;

    /* ��ȡPIDʹ��NV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        return AT_ERROR;
    }

    /* NV��ȡ�ɹ������PID�Ƿ�ʹ�ܣ���ʹ�ܣ�����ERROR */
    if (VOS_FALSE != stPidEnableType.ulPidEnabled)
    {
        return AT_ERROR;
    }

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    /* ������Ч�Լ�� */
    if (VOS_OK != DRV_U2DIAG_VALUE_CHECK(gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���stUsbEnumStatus�ṹ�� */
    PS_MEM_SET(&stUsbEnumStatus, 0, sizeof(AT_USB_ENUM_STATUS_STRU));

    if (NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_USB_Enum_Status, &stUsbEnumStatus, sizeof(AT_USB_ENUM_STATUS_STRU)))
    {
        if ( (gastAtParaList[0].ulParaValue == stUsbEnumStatus.ulValue)
            && (1 == stUsbEnumStatus.ulStatus))
        {
            AT_INFO_LOG("At_SetU2DiagPara():The content to write is same as NV's");
            return AT_OK;
        }
    }

    stUsbEnumStatus.ulStatus = 1;
    stUsbEnumStatus.ulValue  = gastAtParaList[0].ulParaValue;

    /* д��NVIM */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_USB_Enum_Status,
                           &stUsbEnumStatus,
                           sizeof(AT_USB_ENUM_STATUS_STRU)))
    {
        return AT_ERROR;
    }

    return AT_OK;
}
VOS_BOOL At_FistScanSetPortPara(
    VOS_UINT16                          *pusSemiIndex,
    VOS_UINT8                           *pucInputString,
    VOS_UINT16                          usInputLen
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT8                           ucSemiCount;
    VOS_UINT8                           aAvailableChar[] = {'0','1', '2', '3', '4',
                                                            '5', '6', '7', 'A',
                                                            'B', 'D', 'E', 'F',
                                                            ',', ';'};

    ucSemiCount = 0;

    for (i = 0; i < usInputLen; i++)
    {
        for (j = 0; j < (sizeof(aAvailableChar)/sizeof(VOS_UINT8)); j++)
        {
            if (*(pucInputString + i) == aAvailableChar[j])
            {
                if (';' == *(pucInputString + i))
                {
                    ucSemiCount++;
                    *pusSemiIndex = (VOS_UINT16)i;

                    /* ����ֻ����һ���ֺ� */
                    if (ucSemiCount > 1)
                    {
                        AT_ERR_LOG("At_FistScanSetPortPara:The num of semi can only be one!");
                        return VOS_FALSE;
                    }
                }
                break;
            }
        }

        /* ���ǺϷ��ַ� */
        if ((sizeof(aAvailableChar)/sizeof(VOS_UINT8)) == j)
        {
            AT_ERR_LOG("At_FistScanSetPortPara:Invalid character!");
            return VOS_FALSE;
        }
    }

    /* ����ֻ����һ���ֺŲ��Ҳ��ǵ�һ���ַ�Ҳ�������һ���ַ� */
    if (( 0 == *pusSemiIndex ) || ((usInputLen - 1) == *pusSemiIndex))
    {
        AT_ERR_LOG("At_FistScanSetPortPara:The position of semi isn't suitable!");
        return VOS_FALSE;
    }

    /* ��һ�������һ���ַ�Ϊ���� */
    if ((',' == *pucInputString) || (',' == pucInputString[usInputLen - 1]))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : At_SecScanSetPortFirstPara
 ��������  : �ڶ���ɨ���һ�������ֻ��ΪA1��A2��ff
 �������  : VOS_UINT16   usSemiIndex
             VOS_UINT8    *pucFirstParaCount
             VOS_UINT8    *pucInputString
             VOS_UINT16   usInputLen
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��3��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL At_SecScanSetPortFirstPara(
    VOS_UINT16                          usSemiIndex,
    VOS_UINT8                           *pucFirstParaCount,
    VOS_UINT8                           *pucInputString,
    VOS_UINT16                          usInputLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucCharCount;

    ucCharCount = 0;

    for (i = 0; i <= usSemiIndex; i++)
    {
        /* ���Ż��ߵ�һ�������Ľ�β */
        if ((',' == *(pucInputString + i)) || (';' == *(pucInputString + i)))
        {
            /* ����֮�������ŵ����A1,,,,A2;1,2 ����ERROR */
            /* �����������ַ�A1,A2,FF */
            if (2 != ucCharCount)
            {
                AT_ERR_LOG("At_SecScanSetPortFirstPara:Invalid first parameter!");
                return VOS_FALSE;
            }

            /* LINT ERROR: ucCharCount = 2, i >= 2 */
            if ((i >= 2)
                && !((('A' == pucInputString[i - 2]) && ('1' == pucInputString[i - 1]))
                    || (('A' == pucInputString[i - 2]) && ('2' == pucInputString[i - 1]))
                    || (('F' == pucInputString[i - 2]) && ('F' == pucInputString[i - 1]))))

            {
                AT_ERR_LOG("At_SecScanSetPortFirstPara:Invalid first parameter!");
                return VOS_FALSE;
            }

            (*pucFirstParaCount)++;

            ucCharCount = 0;
        }
        else
        {
            ucCharCount++;
        }

        if (ucCharCount > 2)
        {
            AT_ERR_LOG("At_SecScanSetPortFirstPara:Invalid character!");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_BOOL At_SecScanSetPortSecPara(
    VOS_UINT16                          usSemiIndex,
    VOS_UINT8                           *pucSecParaCount,
    VOS_UINT8                           aucSecPara[AT_SETPORT_PARA_MAX_LEN][3],
    VOS_UINT8                           *pucInputString,
    VOS_UINT16                          usInputLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucCharCount;
    VOS_UINT8                           aucTmpInputString[AT_SETPORT_PARA_MAX_CHAR_LEN];
    VOS_UINT16                          usTmpInputStringLen;

    ucCharCount = 0;

    if (usInputLen > AT_SETPORT_PARA_MAX_CHAR_LEN)
    {
        return VOS_FALSE;
    }

    /*�ڶ���������β���϶��ű������²������*/
    usTmpInputStringLen = usInputLen - usSemiIndex;
    PS_MEM_CPY(aucTmpInputString, pucInputString + usSemiIndex + 1, usTmpInputStringLen - 1);
    aucTmpInputString[usTmpInputStringLen - 1] = ',';

    for (i = 0; i < usTmpInputStringLen; i++)
    {
        if (',' == *(aucTmpInputString + i))
        {
            /*����֮�������ŵ����A1,A2;1,,,2����eror*/
            if (0 == ucCharCount)
            {
                AT_ERR_LOG("At_SecScanSetPortSecPara:Invalid second parameter!");
                return VOS_FALSE;
            }

            /* ����������ַ�����ΪA1,A2��16 */
            if (2 == ucCharCount)
            {
                /* LINT ERROR: ucCharCount = 2, i >= 2 */
                if ((i >= 2)
                    && !((('A' == aucTmpInputString[i - 2]) && ('1' == aucTmpInputString[i - 1]))
                      || (('A' == aucTmpInputString[i - 2]) && ('2' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('6' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('0' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('1' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('2' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('3' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('4' == aucTmpInputString[i - 1]))
                      || (('1' == aucTmpInputString[i - 2]) && ('5' == aucTmpInputString[i - 1]))
                 ))
                {
                    AT_ERR_LOG("At_SecScanSetPortSecPara:Invalid second parameter!");
                    return VOS_FALSE;
                }
            }

            /* ����Ϸ��Ĳ��� */
            PS_MEM_CPY(aucSecPara[*pucSecParaCount],
                (aucTmpInputString + i) - ucCharCount, ucCharCount);

            (*pucSecParaCount)++;

            ucCharCount = 0;
        }
        else
        {
            ucCharCount++;
        }

        if (ucCharCount > 2)
        {
            AT_ERR_LOG("At_SecScanSetPortSecPara:Invalid second parameter!");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : At_SaveSetPortFirstPara
 ��������  : �����һ�����:ֻ��ΪA1,A2;A1;ff
 �������  : VOS_UINT8    ucFirstParaCount
             VOS_UINT8    *pucFirstPort
             VOS_UINT8    *pucInputString
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��3��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL At_SaveSetPortFirstPara(
    VOS_UINT8                           ucFirstParaCount,
    VOS_UINT8                           *pucFirstPort,
    VOS_UINT8                           *pucInputString
)
{
    /* ��������������Ҫ�� */
    if ((ucFirstParaCount != 1) && (ucFirstParaCount != 2))
    {
        return VOS_FALSE;
    }

    /* ֻ��һ������: FF����A1 */
    if (1 == ucFirstParaCount)
    {
        if (('F' == *pucInputString) && ('F' == *(pucInputString + 1)))
        {
            *pucFirstPort = 0xFF;
        }
        else if (('A' == *pucInputString) && ('1' == *(pucInputString + 1)))
        {
            *pucFirstPort = 0xA1;
        }
        else
        {
            AT_ERR_LOG("At_SaveSetPortFirstPara:Invalid first parameter!");
            return VOS_FALSE;
        }
    }
    /* ��������: A1,A2 */
    else
    {
        if (('A' == *pucInputString) && ('1' == pucInputString[1])
         && ('A' == pucInputString[3]) && ('2' == pucInputString[4]))
        {
            *pucFirstPort       = 0xA1;
            *(pucFirstPort + 1) = 0xA2;
        }
        else
        {
            AT_ERR_LOG("At_SaveSetPortFirstPara:Invalid first parameter!");
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}
VOS_BOOL At_SaveSetPortSecPara(
    VOS_UINT8                           ucSecParaCount,
    VOS_UINT8                           *pucSecPort,
    VOS_UINT8                           aucSecPara[AT_SETPORT_PARA_MAX_LEN][3]
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;

    /* ��������������Ҫ�� */
    if ((0 == ucSecParaCount) || (ucSecParaCount > AT_SETPORT_PARA_MAX_LEN))
    {
        AT_ERR_LOG("At_SaveSetPortSecPara:Invalid second parameter!");
        return VOS_FALSE;
    }

    /* ���������ظ� */
    for (i = 0; i < (VOS_UINT8)(ucSecParaCount - 1); i++)
    {
        for (j = i + 1; j < ucSecParaCount; j++)
        {
            if (!VOS_MemCmp(aucSecPara[i], aucSecPara[j], 3))
            {
                AT_ERR_LOG("At_SaveSetPortSecPara:Invalid second parameter!");
                return VOS_FALSE;
            }
        }
    }

    for (i = 0; i < ucSecParaCount; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_LEN; j++)
        {
            if (!VOS_MemCmp(aucSecPara[i], g_astSetPortParaMap[j].aucAtSetPara, 3))
            {
                pucSecPort[i] = g_astSetPortParaMap[j].ucDrvPara;
                break;
            }
        }

        /* ˵�����ǺϷ����豸��̬�����ش��� */
        if (j >= AT_SETPORT_DEV_LEN)
        {
            AT_ERR_LOG("At_SaveSetPortSecPara:Invalid second parameter!");
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}

/* Add by f62575 for V7����ͬ��, 2012-04-07, Begin   */
/*****************************************************************************
 �� �� ��  : AT_CheckPortTypePara
 ��������  : ����л�ǰ���л���˿��Ƿ����㶯̬�˿�����Ҫ��
                            ��һ���˿�ֻ����AT_DEV_CDROM��AT_DEV_NONE
                            �ڶ����˿�ֻ����AT_DEV_SD
 �������  : VOS_UINT8                           ucFirstParaCount   �л�ǰ�˿ڸ���
                           VOS_UINT8                          *pucFirstPort         �л�ǰ�˿�
                            VOS_UINT8                           ucSecParaCount  �л���˿ڸ���
                            VOS_UINT8                          *pucSecPort         �л���˿�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
                            VOS_TRUE        ���㶯̬�˿�����Ҫ��
                            VOS_FALSE       �����㶯̬�˿�����Ҫ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    �޸�����   : V7����ͬ��: ֧�ֶ�̬��ȡ֧�ֵĶ˿ڼ���

*****************************************************************************/
VOS_UINT32 AT_CheckPortTypePara(
    VOS_UINT8                           ucFirstParaCount,
    VOS_UINT8                          *pucFirstPort,
    VOS_UINT8                           ucSecParaCount,
    VOS_UINT8                          *pucSecPort
)
{
    VOS_UINT32                          ulRet;

    /* �л�ǰ�˿���Ч�Լ��:
    �˿����õ�һλ����ΪA1(CDROM),���򷵻�ERROR��
    �ڶ�λ����У���������A2(SD),���򷵻�ERROR��
    �����ֱ���ϱ���˿�״̬���ֺ�ǰ��ֱ����FF,���򷵻�ERROR��
    */
    if (2 == ucFirstParaCount)
    {
        if ((AT_DEV_CDROM != *(pucFirstPort))
        || (AT_DEV_SD != *(pucFirstPort + 1)))
        {
            return VOS_FALSE;
        }

    }
    else if (1 == ucFirstParaCount)
    {
        if ((AT_DEV_CDROM != *(pucFirstPort))
        && (AT_DEV_NONE != *(pucFirstPort)))
        {
            return VOS_FALSE;
        }

    }
    else
    {
        return VOS_FALSE;
    }

    /*
    �л���˿���Ч�Լ��:
        1.�˿���̬�б�����2(PCUI),���򷵻�ERROR��
        2.�л���˿ڱ����ǲ��������������֧�ֵĶ˿ڣ����򷵻�ERROR��
        3.�����������ظ��Ķ˿ڣ����򷵻�ERROR��
        4.MASS �������õ������˿ڵ�ǰ�棬���򷵻�ERROR
        5.�˿ڸ������ܳ����涨�ĸ���,���򷵻�ERROR��
    */
    ulRet = DRV_USB_PORT_TYPE_VALID_CHECK(pucSecPort, ucSecParaCount);
    if (VOS_OK != ulRet)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Add by f62575 for V7����ͬ��, 2012-04-07, End   */

/*****************************************************************************
 �� �� ��  : At_IsAvailableSetPortPara
 ��������  : �ж�SETPORT�����Ƿ���ȷ
 �������  : VOS_UINT8    *pucInputString
             VOS_UINT16   usInputLen
             VOS_UINT8    *pucFirstPort
             VOS_UINT8    *pucSecPort
 �������  : ��
 �� �� ֵ  : VOS_BOOL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��3��
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��20��
    �޸�����   : V7����ͬ��: �����˿ڼ������

*****************************************************************************/
VOS_BOOL At_IsAvailableSetPortPara(
    VOS_UINT8                           *pucInputString,
    VOS_UINT16                          usInputLen,
    VOS_UINT8                           *pucFirstPort,
    VOS_UINT8                           *pucSecPort
)
{
    /* �ֺŵ�λ�� */
    VOS_UINT16                          usSemiIndex;
    VOS_UINT8                           ucFirstParaCount;
    VOS_UINT8                           ucSecParaCount;
    VOS_UINT8                           aucSecPara[AT_SETPORT_PARA_MAX_LEN][3];
    VOS_BOOL                            bScanResult;
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    usSemiIndex         = 0;
    ucFirstParaCount    = 0;
    ucSecParaCount      = 0;

    VOS_MemSet(aucSecPara, 0x00, AT_SETPORT_PARA_MAX_LEN * 3);

    /* ��һ��ɨ��:�Ƿ��зǷ��ַ� */
    bScanResult = At_FistScanSetPortPara(&usSemiIndex, pucInputString, usInputLen);

    if (VOS_TRUE != bScanResult)
    {
        AT_ERR_LOG("At_IsAvailableSetPortPara:First parameter is invalid!");
        return VOS_FALSE;
    }

    /* �ڶ���ɨ��:ÿ������������A1,A2,FF,A,B,D,E,1,2,3,4,5,6,7 */
    /* ��һ������ */
    bScanResult = At_SecScanSetPortFirstPara(usSemiIndex,
                                        &ucFirstParaCount,
                                        pucInputString,
                                        usInputLen);

    if (VOS_TRUE != bScanResult)
    {
        AT_ERR_LOG("At_IsAvailableSetPortPara:First parameter is invalid!");
        return VOS_FALSE;
    }

    /*�ڶ�������*/
    bScanResult = At_SecScanSetPortSecPara(usSemiIndex,
                                        &ucSecParaCount,
                                        aucSecPara,
                                        pucInputString,
                                        usInputLen);

    if (VOS_TRUE != bScanResult)
    {
        AT_ERR_LOG("At_IsAvailableSetPortPara:Second parameter is invalid!");
        return VOS_FALSE;
    }

    /*�����һ������*/
    bScanResult = At_SaveSetPortFirstPara(ucFirstParaCount, pucFirstPort, pucInputString);

    if (VOS_TRUE != bScanResult)
    {
        AT_ERR_LOG("At_IsAvailableSetPortPara:Save first parameter fail!");
        return VOS_FALSE;
    }

    /*����ڶ�������*/
    bScanResult = At_SaveSetPortSecPara(ucSecParaCount, pucSecPort, aucSecPara);

    if (VOS_TRUE != bScanResult)
    {
        AT_ERR_LOG("At_IsAvailableSetPortPara:Save second parameter fail!");
        return VOS_FALSE;
    }

    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    ulRet = AT_CheckPortTypePara(ucFirstParaCount, pucFirstPort, ucSecParaCount, pucSecPort);

    return  ulRet;
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */
}
VOS_UINT32 At_SetPort(VOS_UINT8 ucIndex)
{
    VOS_BOOL                            bValidPara;
    VOS_UINT8                           aucFirstPort[AT_SETPORT_PARA_MAX_LEN];
    VOS_UINT8                           aucSecPort[AT_SETPORT_PARA_MAX_LEN];
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    PS_MEM_SET(aucFirstPort, 0x00, AT_SETPORT_PARA_MAX_LEN);
    PS_MEM_SET(aucSecPort, 0x00, AT_SETPORT_PARA_MAX_LEN);
    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(AT_DYNAMIC_PID_TYPE_STRU));

    /* ��ȡPIDʹ��NV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                         &stPidEnableType,
                         sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        AT_ERR_LOG("At_SetPort:Read NV failed!");
        return AT_ERROR;
    }

    /* NV��ȡ�ɹ������PID�Ƿ�ʹ�ܣ�����ʹ�ܣ�����ERROR */
    if (VOS_TRUE != stPidEnableType.ulPidEnabled)
    {
        AT_WARN_LOG("At_SetPort:PID is not enabled");
        return AT_ERROR;
    }

    /* 1.����Ϊ��
       2.����������󳤶�
       ������󳤶�: ���������ĳ��ȼ�һ���ֺ� */
    if ((0 == gastAtParaList[0].usParaLen)
     || (gastAtParaList[0].usParaLen > ((AT_SETPORT_PARA_MAX_CHAR_LEN * 2) + 1)))
    {
        return AT_ERROR;
    }

    /* ��AT����֧���û������Сд���Ƚ�Сдת�ɴ�д���ٽ����ַ����Ľ��� */
    At_UpString(gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    /* �������� */
    bValidPara = At_IsAvailableSetPortPara(gastAtParaList[0].aucPara,
                                        gastAtParaList[0].usParaLen,
                                        aucFirstPort,
                                        aucSecPort);
    if (VOS_FALSE == bValidPara)
    {
        AT_WARN_LOG("At_SetPort:Parameter is invalid");
        return AT_ERROR;
    }

    /* ��NVʧ�ܣ�ֱ�ӷ���ERROR */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("At_SetPort:Read NV fail!");
        return AT_ERROR;
    }

    /* ��NV�ɹ����жϸ�NV��ʹ��״̬������ʹ�ܣ�ֱ�ӷ���ERROR */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* �ж�Ҫд�������Ƿ���NV��������ͬ�������ͬ����д������ֱ�ӷ���OK */
        if(!(VOS_MemCmp(stDynamicPidType.aucFirstPortStyle, aucFirstPort, AT_SETPORT_PARA_MAX_LEN)))
        {
            if(!(VOS_MemCmp(stDynamicPidType.aucRewindPortStyle, aucSecPort, AT_SETPORT_PARA_MAX_LEN)))
            {
                AT_INFO_LOG("At_SetPort:Same, not need write");
                return AT_OK;
            }
        }
    }
    else
    {
        return AT_ERROR;
    }

    /* �˴�����DIAG�����뱣��    */
    if (AT_OK != AT_CheckSetPortRight(stDynamicPidType.aucRewindPortStyle,
                                      aucSecPort))
    {
        return AT_ERROR;
    }

    PS_MEM_CPY(stDynamicPidType.aucFirstPortStyle, aucFirstPort, AT_SETPORT_PARA_MAX_LEN);
    PS_MEM_CPY(stDynamicPidType.aucRewindPortStyle, aucSecPort, AT_SETPORT_PARA_MAX_LEN);

    /* д��NV */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("At_SetPort:Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}


VOS_UINT32 AT_OpenSpecificPort(VOS_UINT8 ucPort)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = AT_DEV_NONE;


    /* ��NV��en_NV_Item_Huawei_Dynamic_PID_Type��ȡ��ǰ�Ķ˿�״̬ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_WARN_LOG("AT_OpenSpecificPort: Read NV fail!");
        return AT_ERROR;
    }

    /* �ж϶˿��Ƿ��Ѿ���: �Ѿ�����ֱ�ӷ���AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* ��ѯNV��en_NV_Item_Huawei_Dynamic_PID_Type���Ƿ��Ѿ����ڸö˿� */
        AT_GetSpecificPort(ucPort,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE != ulPortPos)
        {
            return AT_OK;
        }

    }
    else
    {
        AT_WARN_LOG("AT_OpenSpecificPort: en_NV_Item_Huawei_Dynamic_PID_Type is inactive!");
        return AT_ERROR;
    }

    /* ��ǰ���������Ӷ˿� */
    if (ulPortNum >= AT_SETPORT_PARA_MAX_LEN)
    {
        return AT_ERROR;
    }

    stDynamicPidType.aucRewindPortStyle[ulPortNum] = ucPort;

    /* ���¶˿ڼ������ݵ�NV��en_NV_Item_Huawei_Dynamic_PID_Type */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                        &stDynamicPidType,
                        sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_OpenSpecificPort: Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}
VOS_UINT32 AT_CloseSpecificPort(VOS_UINT8 ucPort)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    VOS_UINT32                          ulPortPos;
    VOS_UINT32                          ulPortNum;
    VOS_UINT32                          ulLoop;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(stDynamicPidType));

    ulPortPos = AT_DEV_NONE;


    /* ��NV��en_NV_Item_Huawei_Dynamic_PID_Type��ȡ��ǰ�Ķ˿�״̬ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                          &stDynamicPidType,
                          sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_CloseSpecificPort: Read NV fail!");
        return AT_ERROR;
    }

    /* �жϸö˿��Ƿ��Ѿ��ر�: �Ѿ��ر���ֱ�ӷ���AT_OK */
    if (VOS_TRUE == stDynamicPidType.ulNvStatus)
    {
        /* ��ѯNV��en_NV_Item_Huawei_Dynamic_PID_Type���Ƿ��Ѿ����ڸö˿� */
        AT_GetSpecificPort(ucPort,
                           stDynamicPidType.aucRewindPortStyle,
                           &ulPortPos,
                           &ulPortNum);

        if (AT_DEV_NONE == ulPortPos)
        {
            return AT_OK;
        }
    }
    else
    {
        return AT_ERROR;
    }

    /* ɾ��NV���е�ָ���˿� */
    stDynamicPidType.aucRewindPortStyle[ulPortPos] = 0;
    ulPortNum--;

    for (ulLoop = ulPortPos; ulLoop < ulPortNum; ulLoop++)
    {
        stDynamicPidType.aucRewindPortStyle[ulLoop] = stDynamicPidType.aucRewindPortStyle[ulLoop + 1];
    }

    stDynamicPidType.aucRewindPortStyle[ulPortNum] = 0;

    /* �˿��쳣���ݱ���: �л�����豸��̬�У���һ���豸����ΪMASS�豸(0xa1,0xa2) */
    if (0 != ulPortNum)
    {
        if ((AT_DEV_CDROM == stDynamicPidType.aucRewindPortStyle[0])
         || (AT_DEV_SD == stDynamicPidType.aucRewindPortStyle[0]))
        {
            return AT_ERROR;
        }
    }

    /* ���¶˿ڼ������ݵ�NV��en_NV_Item_Huawei_Dynamic_PID_Type */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Huawei_Dynamic_PID_Type,
                          &stDynamicPidType,
                          sizeof(AT_DYNAMIC_PID_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_CloseSpecificPort: Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}

TAF_UINT32 At_SetPcscInfo(TAF_UINT8 ucIndex)
{
    AT_DYNAMIC_PID_TYPE_STRU            stDynamicPidType;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(AT_DYNAMIC_PID_TYPE_STRU));

    /* ��ȡPIDʹ��NV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                         &stPidEnableType,
                         sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        AT_ERR_LOG("At_SetPcscInfo:Read NV31 failed!");
        return AT_ERROR;
    }

    /* NV��ȡ�ɹ������PID�Ƿ�ʹ�ܣ�����ʹ�ܣ�����ERROR */
    if (VOS_TRUE != stPidEnableType.ulPidEnabled)
    {
        AT_WARN_LOG("At_SetPcscInfo:PID is not enabled!");
        return AT_ERROR;
    }

    /*  ��PCSC��*/
    if ( VOS_TRUE == gastAtParaList[0].ulParaValue )
    {
        return AT_OpenSpecificPort(AT_DEV_PCSC);
    }
    /* �ر�PCSC�� */
    else
    {
        return AT_CloseSpecificPort(AT_DEV_PCSC);
    }
}


VOS_UINT32 At_SetCellSearch(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucCellSrh;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ����Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    ucCellSrh = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ������Ϣ ID_AT_MTA_WRR_CELLSRH_SET_REQ �� AT AGENT ����������Ϣ������(VOS_UINT8)gastAtParaList[0].ulParaValue */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_MTA_WRR_CELLSRH_SET_REQ,
                                   (VOS_VOID*)&ucCellSrh,
                                   sizeof(ucCellSrh),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAS_MNTN_SET_CELLSRH;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



TAF_UINT32 At_SetGetportmodePara (TAF_UINT8 ucIndex)
{
    TAF_PH_PORT_STRU     stPortInfo;
    TAF_PH_FMR_ID_STRU   stFmrID;
    TAF_UINT16           usDataLen = 0;
    TAF_UINT32           ulRslt;
    TAF_UINT32           ulPortInfoLen;

     /* ������� */
    if ((AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType) && (0 == gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stPortInfo, 0, sizeof(TAF_PH_PORT_STRU));

    /* MMA_CardType((VOS_CHAR *)stPortInfo.ProductName.aucProductName); */
    VOS_StrNCpy((VOS_CHAR *)stPortInfo.ProductName.aucProductName,
                 PRODUCTION_CARD_TYPE,
                 sizeof(stPortInfo.ProductName.aucProductName));



    PS_MEM_SET(&stFmrID, 0x00, sizeof(TAF_PH_FMR_ID_STRU));

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_FMRID, &stFmrID, sizeof(TAF_PH_FMR_ID_STRU)))
    {
        AT_WARN_LOG("At_SetMsIdInfo:WARNING:NVIM Read en_NV_Item_FMRID falied!");
        return AT_ERROR;
    }
    else
    {
        PS_MEM_CPY(stPortInfo.FmrId.aucMfrId, &stFmrID, sizeof(TAF_PH_FMR_ID_STRU));
    }

    ulPortInfoLen = TAF_MAX_PORT_INFO_LEN + 1;

    ulRslt = (VOS_UINT32)(DRV_GET_PORT_MODE((char *)stPortInfo.PortId.aucPortInfo, &ulPortInfoLen));
    if( VOS_OK != ulRslt )
    {
        AT_WARN_LOG("At_SetGetportmodePara:DRV_GET_PORT_MODE Info fail.");
        return AT_ERROR;
    }

    usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen, "%s: %s", "TYPE", stPortInfo.ProductName.aucProductName);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen, ": %s,",  stPortInfo.FmrId.aucMfrId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen, "%s",  stPortInfo.PortId.aucPortInfo);

    gstAtSendData.usBufLen = usDataLen;
    return AT_OK;
}


VOS_UINT32   At_SetCvoicePara (VOS_UINT8 ucIndex)
{
    APP_VC_VOICE_MODE_ENUM_U16          usVoiceMode;


    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }


    /* �������� */
    if(gucAtParaIndex != 1)
    {
        return AT_ERROR;
    }

    /* Ŀǰֻ֧��PC VOICEģʽ */
    usVoiceMode = (APP_VC_VOICE_MODE_ENUM_U16)gastAtParaList[0].ulParaValue;

    if (APP_VC_VOICE_MODE_PCVOICE != usVoiceMode)
    {
        return AT_ERROR;
    }

    /* ����ֵΪAT_SUCCESS��ΪVOS_OK����Ӧ����  */
    if (VOS_OK == APP_VC_SetVoiceMode(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      (VOS_UINT8)APP_VC_AppVcVoiceMode2VcPhyVoiceMode(usVoiceMode),
                                      I0_WUEPS_PID_VC))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }



}
VOS_UINT32 At_SetDdsetexPara (VOS_UINT8 ucIndex)
{
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;


    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* Ŀǰֻ֧��DIAG */
    ucVoicePort = (APP_VC_VOICE_PORT_ENUM_U8)gastAtParaList[0].ulParaValue;

    if (APP_VC_VOICE_PORT_DIAG != ucVoicePort)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_OK == APP_VC_SetVoicePort(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ucVoicePort))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}

/*****************************************************************************
 Prototype      : At_SetCmsrPara
 Description    : ^CMSR=<ReadTag>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2012��03��03��
    �޸�����   : BalongV300R002 Build�Ż���Ŀ:ɾ��NAS_FEATURE_CS_VC
  3.��    ��   : 2013��2��22��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmsrPara (TAF_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((0 != gastAtParaList[0].ulParaValue)&&( 1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* �������� */
    pstSmsCtx->ucParaCmsr = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return AT_OK;
}
TAF_UINT32 At_SetCmgiPara (TAF_UINT8 ucIndex)
{
    MN_MSG_STATUS_TYPE_ENUM_U8          enMsgStatus;
    MN_MSG_LIST_PARM_STRU               stListPara;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ����<stat> */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }
    else
    {
        enMsgStatus = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    }

    stListPara.bChangeFlag = VOS_FALSE;
    stListPara.enMemStore  = pstSmsCtx->stCpmsInfo.enMemReadorDelete;
    stListPara.enStatus    = enMsgStatus;
    PS_MEM_SET(stListPara.aucReserve1, 0x00, sizeof(stListPara.aucReserve1));

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_Delete_Test(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              &stListPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGI_SET;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_ SetCmmtPara
 Description    : +CMMT=<index><stat>
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Modification: Created function
  2.��    ��   : 2013��2��25��
    �޸�����   : DSDA PHASE III
*****************************************************************************/
TAF_UINT32 At_SetCmmtPara (TAF_UINT8 ucIndex)
{
    MN_MSG_MODIFY_STATUS_PARM_STRU               stModifyParm;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    /* �������� */
    if(gucAtParaIndex > 2)
    {
          return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ������� */
    if ((AT_CMD_OPT_SET_PARA_CMD == g_stATParseCmd.ucCmdOptType) && (0 == gastAtParaList[0].usParaLen))
    {
        return AT_CMS_OPERATION_NOT_ALLOWED;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stModifyParm,0x00,sizeof(stModifyParm));

    stModifyParm.ulIndex = gastAtParaList[0].ulParaValue;

    /* ����<stat> */
    if (0 == gastAtParaList[1].ulParaValue)
    {
        stModifyParm.enStatus = MN_MSG_STATUS_MT_NOT_READ;
    }
    else
    {
        stModifyParm.enStatus = MN_MSG_STATUS_MT_READ;
    }

    /* ���ö�ȡ�洢�� */
    stModifyParm.enMemStore = pstSmsCtx->stCpmsInfo.enMemReadorDelete;

     /* ִ��������� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_ModifyStatus(gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               &stModifyParm))

    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMMT_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_SetUssdModePara(TAF_UINT8 ucIndex)
{
    USSD_TRANS_MODE_STRU                stUssdTranMode;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������ȡֵ���, ����Ϊ 0/1 */
    if ((1 != gastAtParaList[0].ulParaValue) && (0 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ȫ�ֱ��� */
    pstSsCtx                        = AT_GetModemSsCtxAddrFromClientId(ucIndex);
    pstSsCtx->usUssdTransMode       = (VOS_UINT16)gastAtParaList[0].ulParaValue;

    stUssdTranMode.ucStatus         = VOS_TRUE;
    stUssdTranMode.ucUssdTransMode  = (VOS_UINT8)pstSsCtx->usUssdTransMode;

    /* �����겦��ģʽ�󣬸�C�˷�����Ϣ */
    if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                               gastAtClientTab[ucIndex].opId,
                                               TAF_MSG_SET_USSDMODE_MSG,
                                               &stUssdTranMode,
                                               sizeof(USSD_TRANS_MODE_STRU),
                                               I0_WUEPS_PID_TAF))
    {
        return AT_ERROR;
    }

    return AT_OK;
}
TAF_UINT32 At_SetAdcTempPara(TAF_UINT8 ucIndex)
{
    SPY_TEMP_THRESHOLD_PARA_STRU stTempPara;
    VOS_UINT32                   ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_UNCHANGE;
    VOS_UINT32                   ulRet;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 4)
    {
        return AT_TOO_MANY_PARA;
    }

    /*ȫ��Ϊ��Чֵ*/
    PS_MEM_SET(&stTempPara,0xFF,sizeof(stTempPara));


    if(0 != gastAtParaList[0].usParaLen)
    {
        stTempPara.ulIsEnable   = gastAtParaList[0].ulParaValue;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if(0 != gastAtParaList[1].usParaLen)
    {
        stTempPara.lCloseAdcThreshold = (VOS_INT)gastAtParaList[1].ulParaValue;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if(0 != gastAtParaList[2].usParaLen)
    {
        stTempPara.lAlarmAdcThreshold = (VOS_INT)gastAtParaList[2].ulParaValue;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if(0 != gastAtParaList[3].usParaLen)
    {
        stTempPara.lResumeAdcThreshold = (VOS_INT)gastAtParaList[3].ulParaValue;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if(SPY_TEMP_THRESHOLD_PARA_CHANGE == ulChangeFlag)
    {
        /*���ýӿ���������ֵ*/
        /* ����Ϣ��C������ �ȱ����¶�״̬  */
        ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                       gastAtClientTab[ucIndex].opId,
                                       DRV_AGENT_ADC_SET_REQ,
                                       &stTempPara,
                                       sizeof(stTempPara),
                                       I0_WUEPS_PID_DRV_AGENT);
        if (TAF_SUCCESS != ulRet)
        {
            AT_WARN_LOG("At_SetAdcTempPara: AT_FillAndSndAppReqMsg fail.");
            return AT_ERROR;
        }

        /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ADC_SET;
        return AT_WAIT_ASYNC_RETURN;

    }

    return AT_OK;
}
TAF_UINT32 At_SetCommDebugPara(TAF_UINT8 ucIndex)
{
    SPY_TEMP_THRESHOLD_PARA_STRU        stTempPara;
    TAF_AT_NVIM_COMMDEGBUG_CFG_STRU     stDebugFlag;
    VOS_UINT16                          usFlag;
    USIMM_MsgBlock                     *pstMsg = VOS_NULL_PTR;
#if ( VOS_WIN32 == VOS_OS_VER )
    VOS_UINT8                           aucFilelist[]={0x6f,0x43};
#endif

    stDebugFlag.ulCommDebugFlag = VOS_FALSE;

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /*ȫ��Ϊ��Чֵ*/
    PS_MEM_SET(&stTempPara,0xFF,sizeof(stTempPara));


    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch(gastAtParaList[0].ulParaValue)
    {
        case 0x00:
            /*ȥ��������Debug����*/
            if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG, &(stDebugFlag.ulCommDebugFlag), sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
            {
                LogPrint("At_SetOamDebugPara:NV_ReadEx Debug Flag0 Fail\r\n");

                return AT_CME_OPERATION_NOT_ALLOWED;
            }

            if(0x00 != stDebugFlag.ulCommDebugFlag)
            {
                stDebugFlag.ulCommDebugFlag = 0x00;

                if(NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG,&(stDebugFlag.ulCommDebugFlag),sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
                {
                    LogPrint("At_SetOamDebugPara:NV_WriteEx Debug Flag0 Fail\r\n");

                    return AT_CME_OPERATION_NOT_ALLOWED;
                }

            }

            break;
        case 0x01:
            /*ʹ��DRX��λ��Ϣ�ϱ�����*/
            if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG, &(stDebugFlag.ulCommDebugFlag), sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
            {
                LogPrint("At_SetOamDebugPara:NV_ReadEx Debug Flag Fail\r\n");

                return AT_CME_OPERATION_NOT_ALLOWED;
            }

            if(0x01 != (stDebugFlag.ulCommDebugFlag&0x01))
            {
                stDebugFlag.ulCommDebugFlag |= 0x01;

                if(NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG,&(stDebugFlag.ulCommDebugFlag),sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
                {
                    LogPrint("At_SetOamDebugPara:NV_WriteEx Debug Flag Fail\r\n");

                    return AT_CME_OPERATION_NOT_ALLOWED;
                }

            }

            break;
#if 0
        case 0x02:
            /*����USIMM��ʼ����Ϣ��¼�ӿ�*/
            /* �ӿڴ�׮��LINT���� */
            if(VOS_OK != DRV_USIMMSCI_RECORD_DATA_SAVE())
            {
                return AT_CME_MEMORY_FAILURE;
            }
            /*lint +e774 +e506*/
            break;
#endif
        case 0x03:
            /*ʹ��USIMM��ʼ����Ϣ��¼����*/
            if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG, &(stDebugFlag.ulCommDebugFlag), sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
            {
                LogPrint("At_SetOamDebugPara:NV_ReadEx Debug Flag2 Fail\r\n");

                return AT_CME_OPERATION_NOT_ALLOWED;
            }

            if(0x02 != (stDebugFlag.ulCommDebugFlag&0x02))
            {
                stDebugFlag.ulCommDebugFlag |= 0x02;

                if(NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG,&(stDebugFlag.ulCommDebugFlag),sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
                {
                    LogPrint("At_SetOamDebugPara:NV_WriteEx Debug Flag2 Fail\r\n");

                    return AT_CME_OPERATION_NOT_ALLOWED;
                }

            }

            break;

        case 0x05:

            usFlag = 1;

            if(NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Usim_Debug_Mode_Set, &usFlag, sizeof(VOS_UINT16)))
            {
                LogPrint("At_SetOamDebugPara:NV_WriteEx Usim Debug Flag Fail\r\n");

                return AT_CME_OPERATION_NOT_ALLOWED;
            }

            break;

        case 0x06:

            usFlag = 0;

            if(NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Usim_Debug_Mode_Set, &usFlag, sizeof(VOS_UINT16)))
            {
                LogPrint("At_SetOamDebugPara:NV_WriteEx Usim Debug Flag Fail\r\n");

                return AT_CME_OPERATION_NOT_ALLOWED;
            }

            break;

        case 0x07:
            pstMsg = (USIMM_MsgBlock *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(USIMM_MsgBlock)-VOS_MSG_HEAD_LENGTH);

            if(VOS_NULL_PTR == pstMsg)
            {
                LogPrint("USIMM_InitCardStart:AllocMsg Failed.");

                return VOS_ERR;
            }

            pstMsg->ulReceiverPid      = WUEPS_PID_USIM;
            pstMsg->enMsgType          = USIMM_CMDTYPE_INITSTART;
            if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
            {
                LogPrint("USIMM_InitCardStart:sndmsg Failed.");
            }
            break;

        default:
            break;
    }

    return AT_OK;
}


TAF_UINT32 AT_SetDwinsPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulEnabled;
    WINS_CONFIG_STRU                    stWins;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ò��� */
    ulEnabled = gastAtParaList[0].ulParaValue;
    NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    /* ���stWins�ṹ�� */
    PS_MEM_SET(&stWins, 0, sizeof(WINS_CONFIG_STRU));

    if ( NV_OK == NV_ReadEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, ulLength) )
    {
        if ( (1 == stWins.ucStatus) && (ulEnabled == stWins.ucWins) )
        {
            AT_INFO_LOG("AT_SetDwinsPara():The content to write is same as NV's");

            /* ����PPP��WINS���� */
            PPP_UpdateWinsConfig((VOS_UINT8)gastAtParaList[0].ulParaValue);

            /* ����APS��WINS���� */
            TAF_PS_ConfigNbnsFunction(WUEPS_PID_AT,
                                      gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      ulEnabled);

            return AT_OK;
        }
    }

    stWins.ucStatus = 1;
    stWins.ucWins   = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* д��NVIM */
    NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    if ( NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, ulLength) )
    {
        return AT_ERROR;
    }
    else
    {
        /* ����PPP��WINS���� */
        PPP_UpdateWinsConfig((VOS_UINT8)gastAtParaList[0].ulParaValue);

        /* ����APS��WINS���� */
        TAF_PS_ConfigNbnsFunction(WUEPS_PID_AT,
                                  gastAtClientTab[ucIndex].usClientId,
                                  0,
                                  ulEnabled);

        return AT_OK;
    }
}


TAF_UINT32 At_SetYjcxPara (TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_YJCX_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_YJCX_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_SetAt2OmPara(TAF_UINT8 ucIndex)
{
    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��������������� */
    if(0 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*ucIndex����Ӧ��ATͨ������AT/OMͨ��*/
    if ( (AT_USB_COM_PORT_NO != gastAtClientTab[ucIndex].ucPortNo)
      && (AT_UART_PORT_NO    != gastAtClientTab[ucIndex].ucPortNo)
      && (AT_CTR_PORT_NO     != gastAtClientTab[ucIndex].ucPortNo)
      && (AT_HSUART_PORT_NO  != gastAtClientTab[ucIndex].ucPortNo))
    {
        return AT_ERROR;
    }

    /*����Ƿ����д���OMģʽ��ATͨ��*/
    if(AT_SUCCESS == At_CheckDataState(AT_OM_DATA_MODE))
    {
        return AT_ERROR;
    }

    /*��¼AT/OMͨ������Ӧ��������*/
    gucAtOmIndex = ucIndex;

    /* ֪ͨOAM�л���OMģʽ */
    if (AT_USB_COM_PORT_NO == gastAtClientTab[ucIndex].ucPortNo)
    {
        CPM_NotifyChangePort(AT_PCUI_PORT, CPM_OM_COMM);
    }
    else if(AT_CTR_PORT_NO == gastAtClientTab[ucIndex].ucPortNo)
    {
        vos_printf("\r\nAt_SetAt2OmPara:Change The AT Ctrl to OM, index is %d", ucIndex);

        At_FormatResultData(AT_CLIENT_TAB_CTRL_INDEX, AT_OK); /*��Ҫ�Ȼظ�OK*/

        VOS_TaskDelay(20);  /*��֤�������ݷ������*/

        /* ֪ͨLMSP �ر�ctrl��*/

        if(VOS_OK != dmsVcomCtrlClose())
        {
            vos_printf("\r\nAt_SetAt2OmPara:Close The AT Ctrl to OM Error");
        }
        /* ֪ͨGU MSP ��ctrl��*/
        GU_OamCtrlPortInit();

        /* ֪ͨCPM ctrl���Ѿ��л����*/
        CPM_NotifyChangePort(CPM_CTRL_PORT, CPM_OM_COMM);
    }
    else if (AT_UART_PORT_NO == gastAtClientTab[ucIndex].ucPortNo)
    {
        CPM_NotifyChangePort(AT_UART_PORT, CPM_OM_COMM);
    }

    else if (AT_HSUART_PORT_NO == gastAtClientTab[ucIndex].ucPortNo)
    {
        CPM_NotifyChangePort(AT_HSUART_PORT, CPM_OM_COMM);
    }
    else
    {
        /* make pc_lint happy */
    }

    /*��ͨ��ģʽ����ΪOMģʽ*/
    At_SetMode(gucAtOmIndex, AT_DATA_MODE, AT_OM_DATA_MODE);

    return AT_OK;
}

/*****************************************************************************
 Prototype      : AT_ResumeOm2AtMode
 Description    : ��OM̬�ָ�ΪAT̬
 Input          : ucPortNo    - �˿ں�
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-14
    Modification: Created function
*****************************************************************************/
TAF_UINT32 AT_ResumeOm2AtMode(TAF_VOID)
{
    /*����Ƿ����д���OMģʽ��ͨ��*/
    if(AT_SUCCESS != At_CheckDataState(AT_OM_DATA_MODE))
    {
        return VOS_ERR;
    }

    At_SetMode(gucAtOmIndex,AT_CMD_MODE,AT_NORMAL_MODE);   /* ��������ģʽ */
    return VOS_OK;
}

VOS_UINT32 AT_GetOperatorNameFromParam(
    VOS_UINT16                         *usOperNameLen,
    VOS_CHAR                           *pucOperName,
    VOS_UINT16                          usBufSize,
    VOS_UINT32                          ulFormatType
)
{
    if ((AT_COPS_LONG_ALPH_TYPE == ulFormatType)
     && (usBufSize > gastAtParaList[2].usParaLen)
     && (0 != gastAtParaList[2].usParaLen))
    {
        PS_MEM_CPY((VOS_CHAR*)pucOperName,(VOS_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
        pucOperName[gastAtParaList[2].usParaLen] = 0;
        *usOperNameLen = gastAtParaList[2].usParaLen;

        return AT_OK;
    }
    else if ((AT_COPS_SHORT_ALPH_TYPE == ulFormatType)
          && (usBufSize > gastAtParaList[2].usParaLen)
          && (0 != gastAtParaList[2].usParaLen))
    {
        PS_MEM_CPY((VOS_CHAR*)pucOperName,(VOS_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
        pucOperName[gastAtParaList[2].usParaLen] = 0;
        *usOperNameLen = gastAtParaList[2].usParaLen;

        return AT_OK;
    }
    else if ((usBufSize > gastAtParaList[2].usParaLen)
          && ((5 == gastAtParaList[2].usParaLen)
           || (6 == gastAtParaList[2].usParaLen)))
    {
        PS_MEM_CPY((VOS_CHAR*)pucOperName,(VOS_CHAR*)gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);
        pucOperName[gastAtParaList[2].usParaLen] = 0;
        *usOperNameLen = gastAtParaList[2].usParaLen;

        return AT_OK;
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
}

VOS_UINT32 At_SetCpolPara(VOS_UINT8 ucIndex)
{
    TAF_PH_SET_PREFPLMN_STRU            stPrefPlmn;
    VOS_UINT32                          ulRst;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stPrefPlmn,0,sizeof(stPrefPlmn));

    /* �������� */
#if(FEATURE_ON == FEATURE_LTE)
    if ( gucAtParaIndex > 7 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#else
    if ( gucAtParaIndex > 6 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#endif

    if ( (2 == gucAtParaIndex)
      && (0 == gastAtParaList[0].usParaLen)
      && (0 != gastAtParaList[1].usParaLen))
    {
        /* ��ǰֻ����<format>�������ǰ��Ӧ��<oper>�ܹ���ȡ�����ȡ������<oper>
           ��format��Ҫ�ı� */
        pstNetCtx->ucCpolFormatType = (AT_COPS_FORMAT_TYPE)gastAtParaList[1].ulParaValue;
        return AT_OK;
    }

    if (pstNetCtx->enPrefPlmnType > MN_PH_PREF_PLMN_HPLMN)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*����������ṹ�У����͸�MMA���д���*/
    stPrefPlmn.enPrefPlmnType           = pstNetCtx->enPrefPlmnType;
    stPrefPlmn.ucAtParaIndex            = gucAtParaIndex;
    stPrefPlmn.usIndexLen               = gastAtParaList[0].usParaLen;
    stPrefPlmn.usIndex                  = gastAtParaList[0].ulParaValue;
    stPrefPlmn.usFormatLen              = gastAtParaList[1].usParaLen;
    stPrefPlmn.usFormat                 = gastAtParaList[1].ulParaValue;
    stPrefPlmn.usGsmRatLen              = gastAtParaList[3].usParaLen;
    stPrefPlmn.usGsmRat                 = gastAtParaList[3].ulParaValue;
    stPrefPlmn.usGsmCompactRatLen       = gastAtParaList[4].usParaLen;
    stPrefPlmn.usGsmCompactRat          = gastAtParaList[4].ulParaValue;
    stPrefPlmn.usUtrnLen                = gastAtParaList[5].usParaLen;
    stPrefPlmn.usUtrn                   = gastAtParaList[5].ulParaValue;

#if(FEATURE_ON == FEATURE_LTE)
    /* LTE�Ľ��뼼���Լ����� */
    stPrefPlmn.usEutrnLen                = gastAtParaList[6].usParaLen;
    stPrefPlmn.usEutrn                   = gastAtParaList[6].ulParaValue;
#endif

    if (0 < stPrefPlmn.usFormatLen)
    {
        pstNetCtx->ucCpolFormatType = (AT_COPS_FORMAT_TYPE)stPrefPlmn.usFormat;

        ulRst = AT_GetOperatorNameFromParam(&stPrefPlmn.usOperNameLen,
                                             stPrefPlmn.ucOperName,
                                             sizeof(stPrefPlmn.ucOperName),
                                             stPrefPlmn.usFormat);
        if ( AT_OK != ulRst )
        {
            return ulRst;
        }
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   TAF_MSG_MMA_SET_PREF_PLMN,
                                   (VOS_UINT8*)&stPrefPlmn, /*���������б���������*/
                                   sizeof(TAF_PH_SET_PREFPLMN_STRU),
                                   I0_WUEPS_PID_MMA);

    if( TAF_SUCCESS == ulRst )
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_SET;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}

VOS_UINT32 At_SetCplsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ulRst;
    MN_PH_PREF_PLMN_TYPE_ENUM_U8         ucPrefPlmnType;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        ucPrefPlmnType = (MN_PH_PREF_PLMN_TYPE_ENUM_U8)gastAtParaList[0].ulParaValue;
    }
    else
    {
        ucPrefPlmnType = MN_PH_PREF_PLMN_UPLMN;
    }

    if (ucPrefPlmnType > MN_PH_PREF_PLMN_HPLMN)
    {
        return AT_CME_OPERATION_NOT_SUPPORTED;
    }

    /* ������Ϣ TAF_MSG_MMA_SET_PREF_PLMN_TYPE �� MMA ���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   TAF_MSG_MMA_SET_PREF_PLMN_TYPE,
                                   (VOS_VOID*)&ucPrefPlmnType, /*Ҫ�����õ�������������*/
                                   sizeof(VOS_UINT8),
                                   I0_WUEPS_PID_MMA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_SET_PREF_PLMN_TYPE;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}
/*****************************************************************************
 �� �� ��  : At_SetpidPara
 ��������  : ^SetPid=<value>
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��07��30��
    �޸�����   : �����ն�Ҫ������AT����:AT^SETPID
*****************************************************************************/
TAF_UINT32 At_SetpidPara(TAF_UINT8 ucIndex)
{
    TAF_UINT32           ulRslt;
    TAF_UINT8            diagValue;

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������ȡֵ���, ����Ϊ 0/1 */
    if ((1 != gastAtParaList[0].ulParaValue) && (0 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    diagValue = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    ulRslt = (VOS_UINT32)(DRV_SET_PID(diagValue));
    if( VOS_OK != ulRslt )
    {
        AT_WARN_LOG("At_SetpidPara:Setpid fail.");
        return AT_ERROR;
    }

    return AT_OK;

  }
VOS_UINT32 AT_SetOpwordParaForApModem ( VOS_UINT8  ucIndex )
{
    VOS_UINT32                              ulResult;
    DRV_AGENT_OPWORD_SET_REQ_STRU           stOpwordSetReq;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stOpwordSetReq, 0x00, sizeof(DRV_AGENT_OPWORD_SET_REQ_STRU));

    /* ��������������� */
    if (DRV_AGENT_PORT_PASSWORD_LEN != gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ĺϷ��Լ�飬����Ϊ16����0��-��9��ASCII�ַ�,������ASCII��ת��Ϊʮ�������� */
    ulResult = At_AsciiNum2Num(stOpwordSetReq.aucPortPassword,
                               gastAtParaList[0].aucPara,
                               DRV_AGENT_PORT_PASSWORD_LEN);
    if ( AT_FAILURE == ulResult)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ת���ɹ�, ���Ϳ����Ϣ��C��, ��ȡ����DIAG/SHELL��Ȩ�� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_OPWORD_SET_REQ,
                                      &stOpwordSetReq,
                                      sizeof(DRV_AGENT_OPWORD_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetOpwordParaForApModem: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_OPWORD_SET;
    return AT_WAIT_ASYNC_RETURN;
}
VOS_UINT32 AT_SetOpwordPara ( VOS_UINT8  ucIndex )
{
    VOS_UINT32                              ulCheckRlst = VOS_FALSE;
    VOS_UINT8                              *pucSystemAppConfig;
    VOS_UINT32                              ulResult;

    /* ��ȡNV���е�ǰ��Ʒ��̬ */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

    /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    /* �Ѿ�����Ȩ��  ֱ�ӷ���OK */
    if (AT_E5_RIGHT_FLAG_YES == g_enATE5RightFlag)
    {
        return AT_OK;
    }

    /* ����ǰ�豸����̬ΪAP-MODEM */
    if ( SYSTEM_APP_ANDROID == *pucSystemAppConfig)
    {
        ulResult = AT_SetOpwordParaForApModem(ucIndex);
        return ulResult;
    }

    /* �������볬�� */
    if ( gastAtParaList[0].usParaLen > AT_DISLOG_PWD_LEN )
    {
        return AT_ERROR;
    }

    /* ����Ƚ� */
    if (0 == VOS_StrLen((VOS_CHAR *)g_acATOpwordPwd))
    {
        /* NV������Ϊ���������κ����붼�ܻ�ȡȨ�� */
        ulCheckRlst = VOS_TRUE;
    }
    else
    {
        if (0 == VOS_StrCmp((VOS_CHAR*)g_acATOpwordPwd, (VOS_CHAR*)gastAtParaList[0].aucPara))
        {
            ulCheckRlst = VOS_TRUE;
        }
    }

    if ( VOS_FALSE == ulCheckRlst )
    {
        return AT_ERROR;
    }

    /* ����ȶԳɹ�  ��ȡȨ�� */
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_YES;

    /* ��D25������  ������Ȩ�ޱ�־ */

    return AT_OK;
}


VOS_UINT32 AT_SetCpwordPara ( VOS_UINT8  ucIndex )
{
    /*�Ѿ�������Ȩ��*/
    if (AT_E5_RIGHT_FLAG_NO == g_enATE5RightFlag )
    {
        return AT_OK;
    }

    /* �ͷ�Ȩ�� */
    g_enATE5RightFlag = AT_E5_RIGHT_FLAG_NO;

    /* ��D25������  ������Ȩ�ޱ�־ */

    return AT_OK;
}
VOS_UINT32 AT_SetDislogPara ( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;

#if (FEATURE_ON==FEATURE_LTE)
    VOS_UINT32                          ulRetDiag;
    VOS_UINT32                          ulRet3GDiag;
    VOS_UINT32                          ulRetGps;
#endif


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen) || (gucAtParaIndex > 1))
    {
        return AT_ERROR;
    }

    /* �л�PCUI�ڵ�DIAG���� */
    if ( AT_DISLOG_PCUI_TO_DIAG == gastAtParaList[0].ulParaValue )
    {
        /* ucIndex����Ӧ��ATͨ������PCUI/UARTͨ�� */
        if ((AT_USB_COM_PORT_NO != gastAtClientTab[ucIndex].ucPortNo)
         && (AT_UART_PORT_NO != gastAtClientTab[ucIndex].ucPortNo))
        {
            return AT_ERROR;
        }

        /*����Ƿ����д���DIAGģʽ��ͨ��*/
        if(AT_SUCCESS == At_CheckDataState(AT_DIAG_DATA_MODE))
        {
            return AT_ERROR;
        }

        /*��¼AT/DIAGͨ������Ӧ��������*/
        gucOmDiagIndex = ucIndex;

        /* ֪ͨOAM�л���DIAGģʽ */
        if (AT_USB_COM_PORT_NO == gastAtClientTab[ucIndex].ucPortNo)
        {
            CPM_NotifyChangePort(AT_PCUI_PORT, CPM_DIAG_COMM);
        }
        else
        {
            CPM_NotifyChangePort(AT_UART_PORT, CPM_DIAG_COMM);
        }


        /*��ͨ��ģʽ����ΪDIAGģʽ*/
        At_SetMode(gucOmDiagIndex, AT_DATA_MODE, AT_DIAG_DATA_MODE);

        return AT_OK;
    }

    /* ��ȡPIDʹ��NV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        AT_ERR_LOG("AT_SetDislogPara:Read NV failed!");
        return AT_ERROR;
    }

    /* NV��ȡ�ɹ������PID�Ƿ�ʹ�ܣ�����ʹ�ܣ�����AT_OK */
    if (VOS_TRUE != stPidEnableType.ulPidEnabled)
    {
        AT_WARN_LOG("AT_SetDislogPara:PID is not enabled");
        return AT_OK;
    }


    /*  ��DIAG��*/
    if ( AT_DISLOG_DIAG_OPEN == gastAtParaList[0].ulParaValue )
    {
#if (FEATURE_ON==FEATURE_LTE)
        ulRet3GDiag   = AT_OpenSpecificPort(AT_DEV_DIAG);
        ulRetDiag     = AT_OpenSpecificPort(AT_DEV_4G_DIAG);
        ulRetGps      = AT_OpenSpecificPort(AT_DEV_4G_GPS);

        if((AT_OK == ulRetDiag) && (AT_OK == ulRetGps) && (AT_OK == ulRet3GDiag))
        {
            ulRet = AT_OK;
        }
        else
        {
            ulRet = AT_ERROR;
        }
#else
        ulRet = AT_OpenDiagPort();
#endif
        return ulRet;
    }

    /* �ر�DIAG�� */
    if ( AT_DISLOG_DIAG_CLOSE == gastAtParaList[0].ulParaValue )
    {
#if (FEATURE_ON == FEATURE_LTE)
        ulRet3GDiag = AT_CloseSpecificPort(AT_DEV_DIAG);
        ulRetDiag   = AT_CloseSpecificPort(AT_DEV_4G_DIAG);
        ulRetGps    = AT_CloseSpecificPort(AT_DEV_4G_GPS);

        if((AT_OK == ulRetDiag) && (AT_OK == ulRetGps) && (AT_OK == ulRet3GDiag))
        {
            ulRet = AT_OK;
        }
        else
        {
            ulRet = AT_ERROR;
        }

#else
        ulRet = AT_CloseDiagPort();
#endif
        return ulRet;
    }


    return AT_ERROR;

}
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
/*****************************************************************************
 �� �� ��  : AT_SetSpwordPara
 ��������  : AT^SPWORD�Ĳ�������, ��ȡ������ǿSHELL�ڿ���Ȩ��
 �������  : VOS_UINT8  ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��21��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetSpwordPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           i;
    DRV_AGENT_SPWORD_SET_REQ_STRU       stSpwordSetReq;

    /* ����������Σ�����ϵͳ��������ǰ���ٴ��������ֱ�ӷ���Error */
    if (g_stSpWordCtx.ucErrTimes >= AT_SHELL_PWD_VERIFY_MAX_TIMES)
    {
        AT_WARN_LOG("AT_SetSpwordPara:WARNING: Verify Max Times!");
        return AT_ERROR;
    }

    /* һ��AT^SPWORD����У��ɹ���ϵͳ���ٶ��û��Ժ������AT^SPWORD������д�����ֱ�ӷ���ERROR */
    if (VOS_TRUE == g_stSpWordCtx.ucShellPwdCheckFlag)
    {
        AT_WARN_LOG("AT_SetSpwordPara:WARNING: Not need Verified!");
        return AT_ERROR;
    }

    /* ���ҽ���һ����������������Ϊ8 */
    if ((gucAtParaIndex > 1)
     || (gastAtParaList[0].usParaLen != AT_SHELL_PWD_LEN))
    {
        AT_WARN_LOG("AT_SetSpwordPara:WARNING: Parameter error!");
        return AT_ERROR;
    }

    /* ����ֻ��Ϊ�ַ�0-9 */
    for (i = 0; i < AT_SHELL_PWD_LEN; i++)
    {
        if ((gastAtParaList[0].aucPara[i] < '0')
         || (gastAtParaList[0].aucPara[i] > '9'))
        {
            AT_WARN_LOG("AT_SetSpwordPara:WARNING: PWD NOT 0-9!");
            return AT_ERROR;
        }
    }

    /* ����У����Ҫ��C��ʵ�� */
    VOS_MemCpy(stSpwordSetReq.acShellPwd, (VOS_CHAR *)gastAtParaList[0].aucPara, AT_SHELL_PWD_LEN);

    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_SPWORD_SET_REQ,
                                              &stSpwordSetReq,
                                              sizeof(stSpwordSetReq),
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SPWORD_SET;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 AT_SetShellPara ( VOS_UINT8 ucIndex )
{
    AT_SHELL_OPEN_FLAG_ENUM_U32         enTmpOpenFlag;

    /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    /*  WIFIʹ��SHELL�� */
    if (AT_SHELL_WIFI_USE == gastAtParaList[0].ulParaValue)
    {
        /* ����WIFIʹ��SHELL�����NV�� */
        enTmpOpenFlag = AT_SHELL_OPEN_FLAG_WIFI;
        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_AT_SHELL_OPEN_FLAG, &enTmpOpenFlag,
                              sizeof(enTmpOpenFlag)))
        {
            AT_WARN_LOG("AT_SetShellPara:WARNING:NV_WriteEx SHELL_OPEN_FLAG faild!");
            return AT_ERROR;
        }

        return AT_OK;
    }

    /*  ��SHELL�� */
    if (AT_SHELL_OPEN == gastAtParaList[0].ulParaValue )
    {
        /* �ж�CK�Ƿ�У��ͨ�� */
        if (g_stSpWordCtx.ucShellPwdCheckFlag != VOS_TRUE)
        {
            AT_WARN_LOG("AT_SetShellPara:WARNING:NV_WriteEx SHELL_OPEN_FLAG faild!");

            return AT_ERROR;
        }

        /* ����򿪽����NV�� */
        enTmpOpenFlag = AT_SHELL_OPEN_FLAG_OPEN;
        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_AT_SHELL_OPEN_FLAG, &enTmpOpenFlag,
                              sizeof(enTmpOpenFlag)))
        {
            AT_WARN_LOG("AT_SetShellPara:WARNING:NV_WriteEx SHELL_OPEN_FLAG faild!");

            return AT_ERROR;
        }

        return AT_OK;
    }

    /*�ر�SHELL��*/
    if ( AT_SHELL_CLOSE == gastAtParaList[0].ulParaValue )
    {
        /* ���浱ǰSHELL�ڵĹر�״̬��NV�� */
        enTmpOpenFlag = AT_SHELL_OPEN_FLAG_CLOSE;
        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_AT_SHELL_OPEN_FLAG, &enTmpOpenFlag,
                              sizeof(enTmpOpenFlag)))
        {
            AT_WARN_LOG("AT_SetShellPara:WARNING:NV_WriteEx SHELL_OPEN_FLAG faild!");
            return AT_ERROR;
        }

        return AT_OK;
    }

    return AT_ERROR;
}
#endif

#if (FEATURE_ON==FEATURE_LTE)



VOS_UINT32 AT_SetRsrpCfgPara ( VOS_UINT8 ucIndex )
{

    NVIM_RSRP_CFG_STRU stRsrpCfg;
    VOS_UINT32 RsrpLevel =0;

    PS_MEM_SET(&stRsrpCfg, 0, sizeof(stRsrpCfg));

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (gucAtParaIndex != 2))
    {
        return AT_ERROR;
    }

    if (NV_OK != NVM_Read(EN_NV_ID_RSRP_CFG, &stRsrpCfg,
                          sizeof(stRsrpCfg)))
    {
        vos_printf("AT_SetRsrpCfgPara:WARNING:NV_ReadEx RSRP faild!\n");
        return AT_ERROR;
    }

    /* ��������ֵ����NV�� */
    RsrpLevel = gastAtParaList[0].ulParaValue;
    stRsrpCfg.ssLevel[RsrpLevel] = (VOS_INT16)(gastAtParaList[0].ulParaValue);
    stRsrpCfg.ssValue[RsrpLevel] = (VOS_INT16)(gastAtParaList[1].ulParaValue);
    if(g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if(NV_OK != NVM_Write(EN_NV_ID_RSRP_CFG, &stRsrpCfg,
                          sizeof(stRsrpCfg)))
        {
            vos_printf("AT_SetRsrpCfgPara:WARNING:NV_WriteEx RSRP faild!\n");
            return AT_ERROR;
        }
    }
    else
    {
        return AT_ERROR; /* ���Ȩ��δ�򿪣�����ERROR */
    }

    return AT_OK;
}
#endif

#if (FEATURE_ON==FEATURE_LTE)

VOS_UINT32 AT_SetRscpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSCP_CFG_STRU stRscpCfg;
    VOS_UINT32 RscpLevel =0;

    PS_MEM_SET(&stRscpCfg, 0, sizeof(stRscpCfg));

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (gucAtParaIndex != 2))
    {
            vos_printf("RSCP������ʽ����\n");
        return AT_ERROR;
    }

    if (NV_OK != NVM_Read(EN_NV_ID_RSCP_CFG, &stRscpCfg,
                          sizeof(stRscpCfg)))
    {
        vos_printf("RSCP read error!\n");
        return AT_ERROR;
    }

    /* ��������ֵ����NV�� */
    RscpLevel = gastAtParaList[0].ulParaValue;
    stRscpCfg.ssLevel[RscpLevel] = (VOS_INT16)(gastAtParaList[0].ulParaValue);
    stRscpCfg.ssValue[RscpLevel] = (VOS_INT16)(gastAtParaList[1].ulParaValue);
    if(g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Write(EN_NV_ID_RSCP_CFG, &stRscpCfg,
                          sizeof(stRscpCfg)))
        {
            vos_printf("�ж�RSCP�Ƿ���ȷд��NV \n");
            return AT_ERROR;
        }
    }
    else
    {
        vos_printf("RSCPд��Ȩ��δ��\n");
        return AT_ERROR; /* ���Ȩ��δ�򿪣�����ERROR */
    }

    return AT_OK;
}
#endif
#if (FEATURE_ON==FEATURE_LTE)

VOS_UINT32 AT_SetEcioCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_ECIO_CFG_STRU stEcioCfg;
    VOS_UINT32 EcioLevel =0;

    PS_MEM_SET(&stEcioCfg, 0, sizeof(stEcioCfg));

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (gucAtParaIndex != 2))
    {
            vos_printf("ECIO������ʽ����\n");
        return AT_ERROR;
    }

    if (NV_OK != NVM_Read(EN_NV_ID_ECIO_CFG, &stEcioCfg,
                          sizeof(stEcioCfg)))
    {
            vos_printf("ECIO read ����\n");
        return AT_ERROR;
    }

    /* ��������ֵ����NV�� */
    EcioLevel = gastAtParaList[0].ulParaValue;
    stEcioCfg.ssLevel[EcioLevel] = (VOS_INT16)(gastAtParaList[0].ulParaValue);
    stEcioCfg.ssValue[EcioLevel] = (VOS_INT16)(gastAtParaList[1].ulParaValue);
    if(g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Write(EN_NV_ID_ECIO_CFG, &stEcioCfg,
                          sizeof(stEcioCfg)))
        {
                vos_printf("ECIOд�����\n");
            return AT_ERROR;
        }
    }
    else
    {
        vos_printf("ECIOд��Ȩ��δ��\n");
        return AT_ERROR; /* ���Ȩ��δ�򿪣�����ERROR */
    }

    return AT_OK;
}
#endif
#if (FEATURE_ON==FEATURE_LTE)

VOS_UINT32 AT_SetPdprofmodPara(VOS_UINT8 ucIndex)
{
    TAF_PDP_PROFILE_EXT_STRU    stPdpProfInfo;

    PS_MEM_SET(&stPdpProfInfo, 0, sizeof(TAF_PDP_PROFILE_EXT_STRU));

    /* ���޲�������ֱ�ӷ���OK */
    if ( AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType )
    {
        return AT_OK;
    }

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 6 )
    {
        return AT_TOO_MANY_PARA;
    }

    stPdpProfInfo.ucCid                 = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stPdpProfInfo.ucDefined         = VOS_FALSE;
    }
    else
    {
        stPdpProfInfo.ucDefined         = VOS_TRUE;

        /* ����<PDP_type> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            if ( gastAtParaList[1].ulParaValue < TAF_PDP_PPP )
            {
                stPdpProfInfo.bitOpPdpType   = VOS_TRUE;

                /* IP:1, IPV6:2, IPV4V6:3, PPP:4 */
                stPdpProfInfo.enPdpType  = (VOS_UINT8)(gastAtParaList[1].ulParaValue + 1);

#if ( FEATURE_OFF == FEATURE_IPV6 )
                if ( (TAF_PDP_IPV6   == stPdpProfInfo.enPdpType)
                  || (TAF_PDP_IPV4V6 == stPdpProfInfo.enPdpType) )
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }
#endif
            }
        }
        /* �Ա��ն˵Ľ������<PDP_type>����Ϊ""(��������)ʱ,����ԭ�ȵ�ֵ��
           ��g_TafCidTab[ucCid].ucUsedָʾ�����ı�ɾ������ʹ��֮ǰ����������ֵ */

        /* ����<APN> */
        if ( gastAtParaList[2].usParaLen > TAF_MAX_APN_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ( 0 != gastAtParaList[2].usParaLen )
        {
            /* ��� */
            if ( VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                             gastAtParaList[2].usParaLen) )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            stPdpProfInfo.bitOpApn       = VOS_TRUE;
            PS_MEM_CPY((VOS_CHAR*)stPdpProfInfo.aucApn,
                       (VOS_CHAR*)gastAtParaList[2].aucPara,
                       gastAtParaList[2].usParaLen);
            stPdpProfInfo.aucApn[gastAtParaList[2].usParaLen] = 0;
        }

        /* ����<username> */
        if ( gastAtParaList[3].usParaLen > TAF_MAX_AUTHDATA_USERNAME_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if(0 != gastAtParaList[3].usParaLen)
        {
            stPdpProfInfo.bitOpUsername = VOS_TRUE;

            PS_MEM_CPY((VOS_CHAR*)stPdpProfInfo.aucUserName,
                       (VOS_CHAR*)gastAtParaList[3].aucPara,
                       gastAtParaList[3].usParaLen);
            stPdpProfInfo.aucUserName[gastAtParaList[3].usParaLen] = 0;
        }

        /* ����<passwd> */
        if ( gastAtParaList[4].usParaLen > TAF_MAX_AUTHDATA_PASSWORD_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ( 0 != gastAtParaList[4].usParaLen )
        {
            stPdpProfInfo.bitOpPassword = VOS_TRUE;

            PS_MEM_CPY((VOS_CHAR*)stPdpProfInfo.aucPassWord,
                       (VOS_CHAR*)gastAtParaList[4].aucPara,
                       gastAtParaList[4].usParaLen);
            stPdpProfInfo.aucPassWord[gastAtParaList[4].usParaLen] = 0;
        }

        /* ����<Auth_type> */
        if ( 0 != gastAtParaList[5].usParaLen )
        {
            stPdpProfInfo.bitOpAuthType = VOS_TRUE;
            stPdpProfInfo.ucAuthType        = (VOS_UINT8)gastAtParaList[5].ulParaValue;
        }

    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetPdpProfInfo( WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0, &stPdpProfInfo))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PDPROFMOD_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
#endif



VOS_UINT32 AT_SetWifiGlobalMacPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN+1]; /* MAC��ַ*/

    if (gucAtParaIndex != 1)
    {
        AT_NORM_LOG("AT_SetApMacPara: the number of parameters is error.");
        return AT_ERROR;
    }

    if (gastAtParaList[0].usParaLen > AT_MAC_ADDR_LEN )
    {
        return AT_ERROR;
    }

    PS_MEM_SET(aucE5GwMacAddr, 0x00, sizeof(aucE5GwMacAddr));

    /* дMAC��ַ������NV */
    VOS_StrNCpy( (VOS_CHAR *)aucE5GwMacAddr, (VOS_CHAR *)gastAtParaList[0].aucPara,
                gastAtParaList[0].usParaLen );


    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);

    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_SetApMacPara: Fail to write nv.");
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32 AT_SetDockPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucClientIndex;
    VOS_UINT16                          usLength;

    usLength = 0;

    if (AT_APP_USER != gastAtClientTab[ucIndex].UserType )
    {
        return AT_FAILURE;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FAILURE;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_FAILURE;
    }

    /* ����Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_FAILURE;
    }

    VOS_MemSet(gastAtParaList[0].aucPara + gastAtParaList[0].usParaLen,
               0x00,
               AT_PARA_MAX_LEN - gastAtParaList[0].usParaLen);

    for (ucClientIndex = 0 ; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        if (AT_USBCOM_USER == gastAtClientTab[ucClientIndex].UserType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s%s%s",
                                        gaucAtCrLf,
                                        gastAtParaList[0].aucPara,
                                        gaucAtCrLf);
            At_SendResultData(ucClientIndex, pgucAtSndCodeAddr, usLength);
            break;
        }
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_SetCsqlvlPara( VOS_UINT8 ucIndex )
{
    /* ����Ϣ��C�˻�ȡ �źŸ��� */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId, 0,
                                   TAF_PH_CSQLVL_VALUE_PARA, VOS_NULL_PTR))
    {
        AT_WARN_LOG("AT_SetCsqlvlPara: Taf_ParaQuery fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSQLVL_SET;
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : AT_SetCsqlvlExtPara
 ��������  : E5ȫ��汾�źŸ�����ѯ���� ^CSQLVLEXT����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��14��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  AT_SetCsqlvlExtPara(VOS_UINT8 ucIndex)
{
    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_CSQLVLEXT_VALUE_PARA,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSQLVLEXT_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_SetApbatlvlPara( VOS_UINT8 ucIndex )
{
    BATT_STATE_T                        stBatLvl;
    VOS_UINT32                          ucChargeState;

    if (BSP_MODULE_UNSUPPORT == DRV_GET_BATTERY_SUPPORT() )
    {
        return AT_ERROR;
    }

    /*Arguments found, return error.*/
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        vos_printf("AT^APBATLVL arguments found, return error!!\r\n ");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ýӿڻ�ȡ������ */
    if ( VOS_OK != DRV_CHG_GET_BATTERY_STATE( &stBatLvl ) )
    {
        return AT_ERROR;
    }

    /* ���ֳ���δ���״̬ */
    if ( (stBatLvl.charging_state == CHARGING_UP)
      || (stBatLvl.charging_state == CHARGING_DOWN) )
    {
        ucChargeState = 1;
    }
    else if ( (stBatLvl.charging_state == NO_CHARGING_UP)
           || (stBatLvl.charging_state == NO_CHARGING_DOWN) )
    {
        ucChargeState = 0;
    }
    else
    {
        return AT_ERROR;
    }

    /* ���˵�ص�������ֵ */
    if ( (stBatLvl.battery_level < BATT_LOW_POWER)
       ||(stBatLvl.battery_level >= BATT_LEVEL_MAX))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucChargeState,
                                                    stBatLvl.battery_level);

    return AT_OK;
}


VOS_UINT32 AT_SetOpenportPara( VOS_UINT8 ucIndex )
{
    /* �������ﴦ��OPENPORT, Ҫô���Ѿ���Ȩ����������OPENPORT,ֱ�ӷ���OK
       Ҫô��û�������뱣��, Ҳֱ�ӷ���OK */
    return AT_OK;
}


VOS_UINT32  At_CheckNdisIpv4AddrPara(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen)
{
    VOS_UINT32                          i;
    VOS_UINT32                          usTemp;
    VOS_UINT8                           ucDotNum;
    VOS_UINT8                           ucNNUM;

    usTemp      = 0;
    ucDotNum    = 0;
    ucNNUM      = 0;

    for (i = 0; i < usLen; i++)
    {
        if ('.' == pData[i])
        {
            if ((usTemp > 255) || (ucNNUM > 3) || (ucNNUM == 0))
            {
                return  AT_ERROR;
            }
            usTemp = 0;
            ucNNUM = 0;
            ucDotNum++;
        }
        else if ( (pData[i] >= '0') && (pData[i] <= '9') )
        {
            ucNNUM++;
            usTemp = (usTemp*10) + (pData[i]-'0');
        }
        else
        {
            return  AT_ERROR;
        }
    }

    if ((ucDotNum != 3) || (usTemp > 255) || (ucNNUM > 3) || (ucNNUM == 0))
    {
        return AT_ERROR;
    }

    return  AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_NdisIpv4AddParaProc
 ��������  : ���NdisAddr�����Ƿ���ȷ
 �������  : VOS_UINT8* pData
             VOS_UINT16 usLen
 �������  : AT_OK
             AT_ERROR
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��01��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  At_NdisIpv4AddParaProc(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pDesData,
    VOS_UINT32                         *pulFlag
)
{
    if (0 == usLen)
    {
        AT_INFO_LOG("At_NdisIpv4AddParaProc: Address isn't present.");
        *pulFlag = VOS_FALSE;
        return AT_SUCCESS;
    }
    else
    {
         /*�������Ƿ���ȷ */
        if(AT_ERROR == At_CheckNdisIpv4AddrPara(pData,usLen))
        {
            AT_WARN_LOG("At_NdisIpv4AddParaProc:the para is error.");
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if (usLen > AT_NDIS_ADDR_PARA_LEN)
        {
            AT_WARN_LOG("At_NdisIpv4AddParaProc: length of IP_Address is beyond 15.");
            return AT_CME_INCORRECT_PARAMETERS;
        }
        PS_MEM_SET(pDesData, 0, (AT_NDIS_ADDR_PARA_LEN + 1));
        PS_MEM_CPY(pDesData, pData, usLen);
    }

    *pulFlag = VOS_TRUE;

    return AT_SUCCESS;
}
VOS_UINT32  At_SetDnsPrim(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (1 != gucAtParaIndex)
    {
        AT_WARN_LOG("At_SetDnsPrim: too many parameters.");
        return AT_ERROR;
    }

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* ����IPV4<Primary_DNS>���� */
        ulRst = At_NdisIpv4AddParaProc(gastAtParaList[0].aucPara,
                                       gastAtParaList[0].usParaLen,
                                       pstAppDialPara->aucPrimIPv4DNSAddr,
                                       &pstAppDialPara->ulPrimIPv4DNSValidFlag);
        if (AT_SUCCESS != ulRst)
        {
            pstAppDialPara->ulPrimIPv4DNSValidFlag  = VOS_FALSE;
            PS_MEM_SET(pstAppDialPara->aucPrimIPv4DNSAddr, 0x00, TAF_MAX_IPV4_ADDR_STR_LEN);
            AT_INFO_LOG("At_SetDnsPrim: IPV4 Primary_DNS isn't present.");
            return ulRst;
        }

        return AT_OK;
    }
    /* ����IPV4<Primary_DNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[0].aucPara,
                                   gastAtParaList[0].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv4DNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv4DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        gstAtNdisAddParam.ulPrimIPv4DNSValidFlag = 0;
        PS_MEM_SET(gstAtNdisAddParam.aucPrimIPv4DNSAddr, 0, (AT_NDIS_ADDR_PARA_LEN + 1));
        AT_INFO_LOG("At_SetDnsPrim: IPV4 Primary_DNS isn't present.");
        return ulRst;
    }

    return AT_OK;
}


VOS_UINT32  At_SetDnsSnd(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (1 != gucAtParaIndex)
    {
        AT_WARN_LOG("At_SetDnsSnd: too many parameters.");
        return AT_ERROR;
    }

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* ����IPV4<Secondary_DNS>���� */
        ulRst = At_NdisIpv4AddParaProc(gastAtParaList[0].aucPara,
                                       gastAtParaList[0].usParaLen,
                                       pstAppDialPara->aucSndIPv4DNSAddr,
                                       &pstAppDialPara->ulSndIPv4DNSValidFlag);
        if (AT_SUCCESS != ulRst)
        {
            pstAppDialPara->ulSndIPv4DNSValidFlag   = VOS_FALSE;
            PS_MEM_SET(pstAppDialPara->aucSndIPv4DNSAddr, 0x00, TAF_MAX_IPV4_ADDR_STR_LEN);
            AT_INFO_LOG("At_SetDnsSnd: IPV4 Secondary_DNS isn't present.");
            return ulRst;
        }

        return AT_OK;
    }

    /* ����IPV4<Secondary_DNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[0].aucPara,
                               gastAtParaList[0].usParaLen,
                               gstAtNdisAddParam.aucSndIPv4DNSAddr,
                              &gstAtNdisAddParam.ulSndIPv4DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        gstAtNdisAddParam.ulSndIPv4DNSValidFlag = 0;
        PS_MEM_SET(gstAtNdisAddParam.aucSndIPv4DNSAddr, 0, (AT_NDIS_ADDR_PARA_LEN + 1));
        AT_INFO_LOG("At_SetDnsSnd: IPV4 Secondary_DNS isn't present.");
        return ulRst;
    }

    return AT_OK;
}


#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_CheckIpv6Capability
 ��������  : ����Ƿ��ܷ�����Ӧ��PDP���͵�PDP����
 �������  : ucPdpType - PDP����
 �������  : VOS_ERR   - ���ŵ�PDP���ʹ���
             VOS_OK    - ���ŵ�PDP������ȷ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��10��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_CheckIpv6Capability(
    VOS_UINT8                           ucPdpType
)
{
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            /* IPv4 onlyֻ�ܷ���IPv4��PDP���� */
            if (TAF_PDP_IPV4 != ucPdpType)
            {
                AT_ERR_LOG("AT_CheckIpv6Capablity: Only IPv4 is supported!");
                return VOS_ERR;
            }
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            /* IPv6 onlyֻ�ܷ���IPv6��PDP���� */
            if (TAF_PDP_IPV6 != ucPdpType)
            {
                AT_ERR_LOG("AT_CheckIpv6Capablity: Only IPv6 is supported!");
                return VOS_ERR;
            }
            break;

        default:
            break;
    }

    return VOS_OK;
}
#endif

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT32 AT_CheckNdisIpv6AddrPara(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          usTemp;
    VOS_UINT8                           ucDotNum;
    VOS_UINT8                           ucNNUM;

    usTemp                              = 0;
    ucDotNum                            = 0;
    ucNNUM                              = 0;

    for (i = 0; i < usLen; i++)
    {
        if (':' == pData[i])
        {
            if ((usTemp > 65535) || (ucNNUM > 5) || (ucNNUM == 0))
            {
                return  AT_ERROR;
            }

            usTemp = 0;
            ucNNUM = 0;
            ucDotNum++;
        }
        else if ( (pData[i] >= '0') && (pData[i] <= '9') )
        {
            ucNNUM++;
            usTemp = (usTemp*10) + (pData[i]-'0');
        }
        else
        {
            return  AT_ERROR;
        }
    }

    if ( ((ucDotNum != 7) && (ucDotNum != 2 ))
      || (usTemp > 65535)
      || (ucNNUM > 5)
      || (ucNNUM == 0))
    {
        return AT_ERROR;
    }

    return  AT_OK;
}


VOS_UINT32 AT_NdisIpv6AddParaProc(
    VOS_UINT8                          *pData,
    VOS_UINT16                          usLen,
    VOS_UINT8                          *pDesData,
    VOS_UINT32                         *pulFlag
)
{
    if (0 == usLen)
    {
        AT_INFO_LOG("AT_NdisIpv6AddParaProc: Address isn't present.");
        *pulFlag = VOS_FALSE;
        return AT_SUCCESS;
    }
    else
    {
         /*�������Ƿ���ȷ */
        if(AT_ERROR == AT_CheckNdisIpv6AddrPara(pData,usLen))
        {
            AT_WARN_LOG("AT_NdisIpv6AddParaProc:the para is error.");
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if (usLen > AT_NDIS_IPV6_ADDR_PARA_LEN)
        {
            AT_WARN_LOG("AT_NdisIpv6AddParaProc: length of IP_Address is beyond 63.");
            return AT_CME_INCORRECT_PARAMETERS;
        }
        PS_MEM_SET(pDesData, 0, (AT_NDIS_IPV6_ADDR_PARA_LEN + 1));
        PS_MEM_CPY(pDesData, pData, usLen);
    }

    *pulFlag = VOS_TRUE;

    return AT_SUCCESS;
}
VOS_UINT32 AT_SetNdisIpv6AddPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    /* ����<Primary_DNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[1].aucPara,
                                   gastAtParaList[1].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv6DNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv6DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisIpv6AddPara: Primary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Secondary_DNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[2].aucPara,
                                   gastAtParaList[2].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv6DNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv6DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisIpv6AddPara: Secondary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Primary_NBNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[3].aucPara,
                                   gastAtParaList[3].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv6WINNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv6WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisIpv6AddPara: Primary_NBNS isn't present.");
        return ulRst;
    }

    /* ����<Secondary_NBNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[4].aucPara,
                                   gastAtParaList[4].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv6WINNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv6WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisIpv6AddPara: Secondary_NBNS isn't present.");
        return ulRst;
    }

    return AT_SUCCESS;
}
#endif


VOS_UINT32  AT_SetNdisIpv4v6AddPara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    /* ����<IP_Address>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[1].aucPara,
                                   gastAtParaList[1].usParaLen,
                                   gstAtNdisAddParam.aucIPv4Addr,
                                   &gstAtNdisAddParam.ulIPv4ValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: IP_Address isn't present.");
        return ulRst;
    }


    /* ����<Primary_DNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[2].aucPara,
                                   gastAtParaList[2].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv4DNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv4DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Primary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Secondary_DNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[3].aucPara,
                                   gastAtParaList[3].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv4DNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv4DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Secondary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Primary_NBNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[4].aucPara,
                                   gastAtParaList[4].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv4WINNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv4WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Primary_NBNS isn't present.");
        return ulRst;
    }

    /* ����<Secondary_NBNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[5].aucPara,
                                   gastAtParaList[5].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv4WINNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv4WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Secondary_NBNS isn't present.");
        return ulRst;
    }

#if(FEATURE_ON == FEATURE_IPV6)
    /* ����<Primary_DNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[6].aucPara,
                                   gastAtParaList[6].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv6DNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv6DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Primary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Secondary_DNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[7].aucPara,
                                   gastAtParaList[7].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv6DNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv6DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Secondary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Primary_NBNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[8].aucPara,
                                   gastAtParaList[8].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv6WINNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv6WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Primary_NBNS isn't present.");
        return ulRst;
    }

    /* ����<Secondary_NBNS>���� */
    ulRst = AT_NdisIpv6AddParaProc(gastAtParaList[9].aucPara,
                                   gastAtParaList[9].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv6WINNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv6WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("AT_SetNdisIpv4v6AddPara: Secondary_NBNS isn't present.");
        return ulRst;
    }
#endif

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : At_SetNdisAddPara
 ��������  : ����NDIS���ŵĲ���,�ֽ׶�ֻ֧��IPV4
 �������  : VOS_UINT8 ucIndex
 �������  : AT_OK
             AT_ERROR
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��01��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  At_SetNdisAddPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    if (gucAtParaIndex > 6)
    {
        AT_WARN_LOG("At_SetNdisAddPara: too many parameters.");
        return AT_TOO_MANY_PARA;
    }

    PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));

    /* ����<IP_Type>���� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_WARN_LOG("At_SetNdisAddPara: IP_Type isn't present.");
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        /*0:IPV4   1:IPV6��2:IPV4V6*/
        if (0 == gastAtParaList[0].ulParaValue)
        {
            gstAtNdisAddParam.enPdpType = TAF_PDP_IPV4;
        }
        else if (1 == gastAtParaList[0].ulParaValue)
        {
            gstAtNdisAddParam.enPdpType = TAF_PDP_IPV6;
        }
        else if (2 == gastAtParaList[0].ulParaValue )
        {
            gstAtNdisAddParam.enPdpType = TAF_PDP_IPV4V6;
        }
        else
        {
            AT_WARN_LOG("At_SetNdisAddPara: IP_Type isn't valid.");
            return AT_ERROR;
        }
    }

    gstAtNdisAddParam.ucPdpTypeValidFlag = VOS_TRUE;

    /* ����<IP_Address>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[1].aucPara,
                                   gastAtParaList[1].usParaLen,
                                   gstAtNdisAddParam.aucIPv4Addr,
                                   &gstAtNdisAddParam.ulIPv4ValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisAddPara: IP_Address isn't present.");
        return ulRst;
    }


    /* ����<Primary_DNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[2].aucPara,
                                   gastAtParaList[2].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv4DNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv4DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisAddPara: Primary_DNS isn't present.");
        return ulRst;
    }


    /* ����<Secondary_DNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[3].aucPara,
                                   gastAtParaList[3].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv4DNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv4DNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_WARN_LOG("At_NdisConnProc: length of password is beyond 255.");
        return AT_CME_INCORRECT_PARAMETERS;
    }


    /* ����<Primary_NBNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[4].aucPara,
                                   gastAtParaList[4].usParaLen,
                                   gstAtNdisAddParam.aucPrimIPv4WINNSAddr,
                                   &gstAtNdisAddParam.ulPrimIPv4WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisAddPara: Primary_NBNS isn't present.");
        return ulRst;
    }

    /* ����<Secondary_NBNS>���� */
    ulRst = At_NdisIpv4AddParaProc(gastAtParaList[5].aucPara,
                                   gastAtParaList[5].usParaLen,
                                   gstAtNdisAddParam.aucSndIPv4WINNSAddr,
                                   &gstAtNdisAddParam.ulSndIPv4WINNSValidFlag);
    if (AT_SUCCESS != ulRst)
    {
        PS_MEM_SET(&gstAtNdisAddParam, 0, sizeof(AT_DIAL_PARAM_STRU));
        AT_INFO_LOG("At_SetNdisAddPara: Secondary_NBNS isn't present.");
        return ulRst;
    }

    return AT_OK;
}
VOS_UINT32 AT_NidsCheckDialParam(VOS_VOID)
{
    if (gucAtParaIndex > 6)
    {
        AT_NORM_LOG1("At_NdisDupProc:gucAtParaIndex=%d.\n",gucAtParaIndex);
        return AT_TOO_MANY_PARA;
    }

    /* ���CID,CID��������*/
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_INFO_LOG("At_NdisDupProc:cid not ext");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* CIDΪ1~31*/
    if ( (gastAtParaList[0].ulParaValue > TAF_MAX_CID)
      || (gastAtParaList[0].ulParaValue < 1) )
    {
        AT_NORM_LOG1("At_NdisDupProc:gastAtParaList[0].ulParaValue=%d\n",gastAtParaList[0].ulParaValue);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*���Ų�����飬�ò�������ʡ�ԣ���ֻ��Ϊ0��1��1��ʾ���š�0��ʾ�Ͽ�����*/
    if (0 == gastAtParaList[1].usParaLen)
    {
        AT_INFO_LOG("At_NdisDupProc:dial unknow");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*AT^NDISDUP=1,1*/
    if ( (1 != gastAtParaList[1].ulParaValue)
      && (0 != gastAtParaList[1].ulParaValue) )
    {
        AT_INFO_LOG("At_NdisDupProc:dial unknow");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* APN */
    if ( gastAtParaList[2].usParaLen  > TAF_MAX_APN_LEN )
    {
        AT_WARN_LOG("AT_CheckApn: WARNING: APN len is error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 0 != gastAtParaList[2].usParaLen )
    {
        /* ��� */
        if ( VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                         gastAtParaList[2].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

     /* User Name */
    if ( gastAtParaList[3].usParaLen > TAF_MAX_GW_AUTH_USERNAME_LEN )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* Password */
    if ( gastAtParaList[4].usParaLen > TAF_MAX_GW_AUTH_PASSWORD_LEN )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : AT_NdisFindCidForDialDown
 ��������  : �����Ƿ�����Ҫ ȥ�����PDP
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��18��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 AT_NdisFindCidForDialDown(VOS_VOID)
{
    /* IPv4v6 */
    if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4v6State)
      || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        return g_stAtNdisDhcpPara.ucIpv4v6Cid;
    }
    else
    {
        /* IPv4 */
        if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4State) )
        {
            return g_stAtNdisDhcpPara.ucIpv4Cid;
        }

        /* IPv6 */
        if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv6State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv6State) )
        {
            return g_stAtNdisDhcpPara.ucIpv6Cid;
        }
    }

    return TAF_INVALID_CID;
}
VOS_UINT32 AT_GetNdisDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo,
    VOS_UINT8                           ucIndex
)
{
    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCidInfo;
    VOS_UINT32                          ulRet;


    PS_MEM_SET(&stPdpCidInfo, 0x00, sizeof(stPdpCidInfo));


    pstDialParaInfo->ucCid      = (VOS_UINT8)gastAtParaList[0].ulParaValue;

#ifdef DMT
    ulRet = MN_APS_GetPdpCidPara(&stPdpCidInfo, pstDialParaInfo->ucCid);
#else
    ulRet = TAF_AGENT_GetPdpCidPara(&stPdpCidInfo, ucIndex, pstDialParaInfo->ucCid);
#endif
    if (VOS_OK != ulRet)
    {
        return AT_FAILURE;
    }
    /* ��ȡPDP���� */
    if (VOS_TRUE == gstAtNdisAddParam.ucPdpTypeValidFlag)
    {
        pstDialParaInfo->enPdpType      = gstAtNdisAddParam.enPdpType;
    }
    else if ((TAF_PDP_IPV4   == stPdpCidInfo.stPdpAddr.enPdpType)
     || (TAF_PDP_IPV6   == stPdpCidInfo.stPdpAddr.enPdpType)
     || (TAF_PDP_IPV4V6 == stPdpCidInfo.stPdpAddr.enPdpType))
    {
#if (FEATURE_OFF == FEATURE_IPV6)
        if ((TAF_PDP_IPV6   == stPdpCidInfo.stPdpAddr.enPdpType)
        || (TAF_PDP_IPV4V6 == stPdpCidInfo.stPdpAddr.enPdpType))
        {
            return AT_FAILURE;
        }
#endif
        pstDialParaInfo->enPdpType      = stPdpCidInfo.stPdpAddr.enPdpType;
    }
    else
    {
        /* Ĭ��ʹ��IPV4 */
        pstDialParaInfo->enPdpType      = TAF_PDP_IPV4;
    }

#if(FEATURE_ON == FEATURE_IPV6)
    if (VOS_ERR == AT_CheckIpv6Capability(pstDialParaInfo->enPdpType))
    {
        AT_INFO_LOG("AT_NidsGetDialParam:PDP type is error");
        return AT_FAILURE;
    }
#endif

    if ( 0 != gastAtParaList[2].usParaLen )
    {
        pstDialParaInfo->bitOpApn       = VOS_TRUE;

        PS_MEM_CPY((VOS_CHAR*)pstDialParaInfo->aucApn,
                   (VOS_CHAR*)gastAtParaList[2].aucPara,
                   gastAtParaList[2].usParaLen);
        pstDialParaInfo->aucApn[gastAtParaList[2].usParaLen] = 0;
    }

    if ( 0 != gastAtParaList[3].usParaLen )
    {
        pstDialParaInfo->bitOpUserName  = VOS_TRUE;

        PS_MEM_CPY((VOS_CHAR*)pstDialParaInfo->aucUserName,
                   (VOS_CHAR*)gastAtParaList[3].aucPara,
                   gastAtParaList[3].usParaLen);
        pstDialParaInfo->aucUserName[gastAtParaList[3].usParaLen] = 0;
    }

    if ( 0 != gastAtParaList[4].usParaLen )
    {
        pstDialParaInfo->bitOpPassWord  = VOS_TRUE;

        PS_MEM_CPY((VOS_CHAR*)pstDialParaInfo->aucPassWord,
                   (VOS_CHAR*)gastAtParaList[4].aucPara,
                   gastAtParaList[4].usParaLen);
        pstDialParaInfo->aucPassWord[gastAtParaList[4].usParaLen] = 0;
    }

    /* Auth Type */
    if ( gastAtParaList[5].usParaLen > 0 )
    {
        pstDialParaInfo->bitOpAuthType  = VOS_TRUE;
        pstDialParaInfo->enAuthType     = AT_CtrlGetPDPAuthType(gastAtParaList[5].ulParaValue,
                                                                gastAtParaList[5].usParaLen);
    }
    else
    {
        /* ����û��������볤�Ⱦ���Ϊ0, �Ҽ�Ȩ����δ����, ��Ĭ��ʹ��CHAP���� */
        if ( (0 != gastAtParaList[3].usParaLen)
          && (0 != gastAtParaList[4].usParaLen) )
        {
            pstDialParaInfo->bitOpAuthType = VOS_TRUE;
            pstDialParaInfo->enAuthType    = PPP_CHAP_AUTH_TYPE;
        }
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_NdisDialDownProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulPdpFlag;

    ulPdpFlag = 0;

    /* ������е�PDP������IDLE, ����OK; �����һ������DEACTINGҲ����OK */
    if ( VOS_TRUE == AT_NdisCheckPdpIdleState() )
    {
        AT_WARN_LOG("AT_NdisDialDownProc: the state is already IDLE.");
        return AT_OK;
    }

    if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4v6State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        /* AT^NDISDUP�ĵ�һ�������͵�ǰ��cid��һ�£�ֱ�ӷ���ERROR */
        if (g_stAtNdisDhcpPara.ucIpv4v6Cid != gastAtParaList[0].ulParaValue)
        {
            return AT_ERROR;
        }

        ulPdpFlag = 1;

        if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                     AT_NDIS_GET_CLIENT_ID(),
                                     0,
                                     g_stAtNdisDhcpPara.ucIpv4v6Cid))
        {
            AT_WARN_LOG("AT_NdisDialDownProc():TAF_PS_CallEnd fail");
        }

        AT_NdisSetState(TAF_PDP_IPV4V6, AT_PDP_STATE_DEACTING);
    }
    else
    {
        if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4State) )
        {
            /* AT^NDISDUP�ĵ�һ�������͵�ǰ��cid��һ�£�ֱ�ӷ���ERROR */
            if (g_stAtNdisDhcpPara.ucIpv4Cid == gastAtParaList[0].ulParaValue)
            {
                ulPdpFlag = 1;
                if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_NDIS_GET_CLIENT_ID(),
                                             0,
                                             g_stAtNdisDhcpPara.ucIpv4Cid))
                {
                    AT_WARN_LOG("AT_NdisDialDownProc():TAF_PS_CallEnd fail");
                }
                AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);

                if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv6State)
                  || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv6State) )
                {

                    if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                                 AT_NDIS_GET_CLIENT_ID(),
                                                 0,
                                                 g_stAtNdisDhcpPara.ucIpv6Cid))
                    {
                        AT_WARN_LOG("AT_NdisDialDownProc():TAF_PS_CallEnd fail");
                    }
                    AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
                }
            }
        }

        if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv6State)
          || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv6State) )
        {
            /* AT^NDISDUP�ĵ�һ�������͵�ǰ��cid��һ�£�ֱ�ӷ���ERROR */
            if (g_stAtNdisDhcpPara.ucIpv6Cid == gastAtParaList[0].ulParaValue)
            {
                ulPdpFlag = 1;
                if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_NDIS_GET_CLIENT_ID(),
                                             0,
                                             g_stAtNdisDhcpPara.ucIpv6Cid))
                {
                    AT_WARN_LOG("AT_NdisDialDownProc():TAF_PS_CallEnd fail");
                }
                AT_NdisSetState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);

                if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4State)
                  || (AT_PDP_STATE_ACTED  == g_stAtNdisDhcpPara.enIpv4State) )
                {

                    if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                                 AT_NDIS_GET_CLIENT_ID(),
                                                 0,
                                                 g_stAtNdisDhcpPara.ucIpv4Cid))
                    {
                        AT_WARN_LOG("AT_NdisDialDownProc():TAF_PS_CallEnd fail");
                    }
                    AT_NdisSetState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
                }

            }
        }
    }

    if (0 == ulPdpFlag)
    {
        return AT_ERROR;
    }


    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : AT_NdisCheckActingStateForDial
 ��������  : ���PDP״̬���㲦������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK
             VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��13��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_NdisCheckActingStateForDial(VOS_VOID )
{
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State )
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State )
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State ))
    {
        /* ����PDP��������, ����OK */
        return AT_OK;
    }
    else if ( (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4State )
           || (AT_PDP_STATE_ACTED == g_stAtNdisDhcpPara.enIpv4State )
           || (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv6State )
           || (AT_PDP_STATE_ACTED == g_stAtNdisDhcpPara.enIpv6State )
           || (AT_PDP_STATE_ACTING == g_stAtNdisDhcpPara.enIpv4v6State )
           || (AT_PDP_STATE_ACTED == g_stAtNdisDhcpPara.enIpv4v6State ))
    {
        /* PDP�Ѽ�������ڼ���, ����OK */
        return AT_SUCCESS;
    }
    else
    {
        /* PDP״̬�����㲦��Ҫ��, ����ERROR */
        return  AT_FAILURE;
    }
}
VOS_UINT32 AT_NdisDialUpProc(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;

    AT_PS_USER_INFO_STRU                stUsrInfo;

    PS_MEM_SET(gstAtNdisAddParam.aucUsername, 0x00, TAF_MAX_GW_AUTH_USERNAME_LEN);
    PS_MEM_SET(gstAtNdisAddParam.aucPassword, 0x00, TAF_MAX_GW_AUTH_PASSWORD_LEN);

    PS_MEM_SET(&stUsrInfo, 0x00, sizeof(AT_PS_USER_INFO_STRU));

    /* �����û���Ϣ */
    AT_NDIS_ParseUsrInfo(ucIndex, &stUsrInfo);

    /*����Ѿ����Ż����ڲ��ţ�ֱ�ӻظ�OK*/
    ulResult = AT_NdisCheckActingStateForDial();
    if (AT_SUCCESS == ulResult)
    {
        AT_INFO_LOG("AT_NdisDialUpProc: the state is already active or activing");

        return AT_OK;
    }

    /*�Ͽ����Ź����в���������*/
    if (AT_FAILURE == ulResult)
    {
        AT_INFO_LOG("AT_NdisDialUpProc: the state is error");

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stDialParaInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* ��ȡ���Ų��� */
    ulResult = AT_GetNdisDialParam(&stDialParaInfo, ucIndex);
    if ( AT_SUCCESS != ulResult )
    {
        AT_ERR_LOG("AT_NdisDialUpProc: the PDP TYPE is not fit.");

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ���沦�Ų���������IPV6���� */
    gstAtNdisAddParam.usAuthType      = stDialParaInfo.enAuthType;
    gstAtNdisAddParam.ucCid           = stDialParaInfo.ucCid;
    gstAtNdisAddParam.enPdpType       = stDialParaInfo.enPdpType;

    /* �����û��� */
    gstAtNdisAddParam.usUsernameLen   = gastAtParaList[3].usParaLen;
    PS_MEM_CPY((VOS_CHAR*)gstAtNdisAddParam.aucUsername,
               (VOS_CHAR*)gastAtParaList[3].aucPara,
               gastAtParaList[3].usParaLen);

    /* �����û����� */
    gstAtNdisAddParam.usPasswordLen   = gastAtParaList[4].usParaLen;
    PS_MEM_CPY((VOS_CHAR*)gstAtNdisAddParam.aucPassword,
               (VOS_CHAR*)gastAtParaList[4].aucPara,
               gastAtParaList[4].usParaLen);

    /* APN */
    gstAtNdisAddParam.ucAPNLen        = (VOS_UINT8)gastAtParaList[2].usParaLen;
    PS_MEM_CPY((VOS_CHAR*)gstAtNdisAddParam.aucAPN,
               (VOS_CHAR*)gastAtParaList[2].aucPara,
               gastAtParaList[2].usParaLen);

    AT_GetPdpContextFromAtDialParam(&stPdpPrimContextExt,&gstAtNdisAddParam);


#ifdef DMT
    ulResult = MN_APS_SetPdpCidPara(gastAtClientTab[ucIndex].usClientId, &stPdpPrimContextExt);
#else
    /* ����CID�����Ĳ��� */
    ulResult = TAF_AGENT_SetPdpCidPara(gastAtClientTab[ucIndex].usClientId, &stPdpPrimContextExt);
#endif

    if (VOS_OK != ulResult)
    {
        AT_WARN_LOG("AT_NdisDialUpProc: Def Pdp Context Fail.");

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ���𲦺� */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT,
                                  AT_NDIS_GET_CLIENT_ID(),
                                  0,
                                  &stDialParaInfo))
    {
        /* �����û���Ϣ */
        g_stAtNdisDhcpPara.stUsrInfo = stUsrInfo;

        if (TAF_PDP_IPV4 == stDialParaInfo.enPdpType)
        {
            g_stAtNdisDhcpPara.ucIpv4Cid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        }
        else if (TAF_PDP_IPV6 == stDialParaInfo.enPdpType)
        {
            g_stAtNdisDhcpPara.ucIpv6Cid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        }
        else
        {
            g_stAtNdisDhcpPara.ucIpv4v6Cid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        }

        g_enAtNdisActPdpType       = stDialParaInfo.enPdpType;
        g_enAtFirstNdisActPdpType  = stDialParaInfo.enPdpType;

        AT_NdisSetState(g_enAtNdisActPdpType, AT_PDP_STATE_ACTING);

        /* ���õ�ǰpdpact�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 At_NdisDupProc(VOS_UINT8 ucIndex)
{
    VOS_UINT32                  ulRet;

    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        AT_NORM_LOG1("At_NdisDupProc:g_stATParseCmd.ucCmdOptType=%d\n",g_stATParseCmd.ucCmdOptType);

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*�������*/
    ulRet = AT_NidsCheckDialParam();
    if ( AT_SUCCESS != ulRet)
    {
        AT_NORM_LOG1("At_NdisDupProc:ulRet=%d\n",ulRet);

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return ulRet;
    }

    /* �������ţ����Ż�Ͽ����� */
    if (0 == gastAtParaList[1].ulParaValue)
    {
        return AT_NdisDialDownProc(ucIndex);
    }
    else
    {
        /* ��¼NDIS���Ų��� */
        AT_SaveNdisConnDailPara(gastAtParaList);

        return AT_NdisDialUpProc(ucIndex);
    }

}


VOS_UINT32 AT_AppCheckDialParam(VOS_VOID)
{
    VOS_UINT8                           aucIpv4Addr[TAF_IPV4_ADDR_LEN];

    if (gucAtParaIndex > 7)
    {
        AT_NORM_LOG1("AT_AppCheckDialParam:gucAtParaIndex=%d.\n",gucAtParaIndex);
        return AT_TOO_MANY_PARA;
    }

    /* ���CID,CID��������*/
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_INFO_LOG("AT_AppCheckDialParam:cid not ext");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* CIDΪ1~31*/
    if ( (gastAtParaList[0].ulParaValue > TAF_MAX_CID)
      || (gastAtParaList[0].ulParaValue < 1) )
    {
        AT_NORM_LOG1("AT_AppCheckDialParam:gastAtParaList[0].ulParaValue=%d\n",gastAtParaList[0].ulParaValue);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���Ų�����飬�ò�������ʡ�ԣ���ֻ��Ϊ0��1��1��ʾ���š�0��ʾ�Ͽ����� */
    if (0 == gastAtParaList[1].usParaLen)
    {
        AT_INFO_LOG("AT_AppCheckDialParam:dial unknow");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT^NDISDUP=1,1 */
    if ( (1 != gastAtParaList[1].ulParaValue)
      && (0 != gastAtParaList[1].ulParaValue) )
    {
        AT_INFO_LOG("AT_AppCheckDialParam:dial unknow");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* APN */
    if ( gastAtParaList[2].usParaLen  > TAF_MAX_APN_LEN )
    {
        AT_WARN_LOG("AT_CheckApn: WARNING: APN len is error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 0 != gastAtParaList[2].usParaLen )
    {
        /* ��� */
        if ( VOS_OK != AT_CheckApnFormat(gastAtParaList[2].aucPara,
                                         gastAtParaList[2].usParaLen) )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* User Name */
    if ( gastAtParaList[3].usParaLen > TAF_MAX_GW_AUTH_USERNAME_LEN )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* Password */
    if ( gastAtParaList[4].usParaLen > TAF_MAX_GW_AUTH_PASSWORD_LEN )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*IP��ַ���ܴ��� 15*/
    if (gastAtParaList[6].usParaLen > (TAF_MAX_IPV4_ADDR_STR_LEN - 1))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    else
    {
        if (gastAtParaList[6].usParaLen > 0)
        {
            if (VOS_OK != AT_Ipv4AddrAtoi((VOS_CHAR *)gastAtParaList[6].aucPara, aucIpv4Addr))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }
    }


    return AT_SUCCESS;
}
VOS_UINT32 AT_AppCheckPdpStateForDial(VOS_VOID )
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    if ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State )
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State )
      && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State ))
    {
        /* ����PDP��������, ����OK */
        return AT_OK;
    }
    else if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
           || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4State)
           || (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv6State)
           || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv6State)
           || (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4v6State)
           || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4v6State) )
    {
        /* PDP�Ѽ�������ڼ���, ����OK */
        return AT_SUCCESS;
    }
    else
    {
        /* PDP״̬�����㲦��Ҫ��, ����ERROR */
        return  AT_FAILURE;
    }
}
VOS_UINT8 AT_AppFindCidForDialDown(VOS_VOID)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* IPv4v6 */
    if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4v6State)
      || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4v6State) )
    {
        return pstAppPdpEntity->ucIpv4v6Cid;
    }
    else
    {
        /* IPv4 */
        if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
          || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4State) )
        {
            return pstAppPdpEntity->ucIpv4Cid;
        }

        /* IPv6 */
        if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv6State)
          || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv6State) )
        {
            return pstAppPdpEntity->ucIpv6Cid;
        }
    }

    return TAF_INVALID_CID;
}
VOS_VOID AT_AppReportPdpActiveState(
    VOS_UINT8                           ucIndex,
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity
)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;

    pstAppRaInfoAddr = AT_APP_GetRaInfoAddr();

    usLength                            = 0;

    /* ������������Ѵ���, �ϱ���ǰ������״̬ */
    if (AT_PDP_STATE_ACTED == pstAppPdpEntity->enIpv4v6State)
    {
        AT_NORM_LOG("AT_AppReportPdpActiveState:NORMAL: The state of IPv4v6 is ACTED!");

        /* ���ϱ�OK */
        At_FormatResultData(ucIndex, AT_OK);

        /* ���ϱ�^DCONN */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                    "%s^DCONN:%d,\"%s\"%s",
                                    gaucAtCrLf,
                                    pstAppPdpEntity->ucIpv4v6Cid,
                                    aucAtStrIpv4,
                                    gaucAtCrLf);
        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        if (VOS_TRUE == pstAppRaInfoAddr->bitOpPrefixAddr)
        {
            usLength = 0;

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                    "%s^DCONN:%d,\"%s\"%s",
                                    gaucAtCrLf,
                                    pstAppPdpEntity->ucIpv4v6Cid,
                                    aucAtStrIpv6,
                                    gaucAtCrLf);

            At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
        }
    }
    else if ( (AT_PDP_STATE_ACTED == pstAppPdpEntity->enIpv4State)
           && (AT_PDP_STATE_ACTED == pstAppPdpEntity->enIpv6State) )
    {
        AT_NORM_LOG("AT_AppDialUpProc:NORMAL: The state of IPv4 and IPv6 is ACTED!");

        /* ���ϱ�OK */
        At_FormatResultData(ucIndex, AT_OK);

        /* ���ϱ�^DCONN */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                    "%s^DCONN:%d,\"%s\"%s",
                                    gaucAtCrLf,
                                    pstAppPdpEntity->ucIpv4Cid,
                                    aucAtStrIpv4,
                                    gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        if (VOS_TRUE == pstAppRaInfoAddr->bitOpPrefixAddr)
        {
            usLength = 0;

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                    "%s^DCONN:%d,\"%s\"%s",
                                    gaucAtCrLf,
                                    pstAppPdpEntity->ucIpv6Cid,
                                    aucAtStrIpv6,
                                    gaucAtCrLf);

            At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
        }
    }
    else if ( (AT_PDP_STATE_ACTED == pstAppPdpEntity->enIpv4State)
           && (AT_PDP_STATE_IDLE  == pstAppPdpEntity->enIpv6State) )
    {
        AT_NORM_LOG("AT_AppDialUpProc:NORMAL: The state of IPv4 is ACTED!");

        /* ���ϱ�OK */
        At_FormatResultData(ucIndex, AT_OK);

        /* ���ϱ�^DCONN */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                    "%s^DCONN:%d,\"%s\"%s",
                                    gaucAtCrLf,
                                    pstAppPdpEntity->ucIpv4Cid,
                                    aucAtStrIpv4,
                                    gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }
    else if ( (AT_PDP_STATE_IDLE  == pstAppPdpEntity->enIpv4State)
           && (AT_PDP_STATE_ACTED == pstAppPdpEntity->enIpv6State) )
    {
        AT_NORM_LOG("AT_AppDialUpProc:NORMAL: The state of IPv6 is ACTED!");

        /* ���ϱ�OK */
        At_FormatResultData(ucIndex, AT_OK);

        if (VOS_TRUE == pstAppRaInfoAddr->bitOpPrefixAddr)
        {
            /* ���ϱ�^DCONN */
            usLength = 0;

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                    "%s^DCONN:%d,\"%s\"%s",
                                    gaucAtCrLf,
                                    pstAppPdpEntity->ucIpv6Cid,
                                    aucAtStrIpv6,
                                    gaucAtCrLf);

            At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
        }
    }
    else
    {
        /* �޲�������, ֱ�ӷ���OK */
        AT_NORM_LOG("AT_AppDialUpProc:NORMAL: No PDP is ACTED!");

        /* ���ϱ�OK */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}
VOS_UINT32 AT_GetAppDialParam(
    TAF_PS_DIAL_PARA_STRU              *pstDialParaInfo,
    VOS_UINT8                           ucIndex
)
{
    TAF_PDP_PRIM_CONTEXT_STRU                    stPdpCidInfo;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stPdpCidInfo, 0x00, sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
    PS_MEM_SET(pstDialParaInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* ��ȡCID */
    pstDialParaInfo->ucCid            = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    ulRet = TAF_AGENT_GetPdpCidPara(&stPdpCidInfo, ucIndex, pstDialParaInfo->ucCid);
    if (VOS_OK != ulRet)
    {
        return AT_FAILURE;
    }

    if ((TAF_PDP_IPV4   == stPdpCidInfo.stPdpAddr.enPdpType)
     || (TAF_PDP_IPV6   == stPdpCidInfo.stPdpAddr.enPdpType)
     || (TAF_PDP_IPV4V6 == stPdpCidInfo.stPdpAddr.enPdpType))
    {
#if (FEATURE_OFF == FEATURE_IPV6)
        if ((TAF_PDP_IPV6   == stPdpCidInfo.stPdpAddr.enPdpType)
        || (TAF_PDP_IPV4V6 == stPdpCidInfo.stPdpAddr.enPdpType))
        {
            return AT_FAILURE;
        }
#endif
        pstDialParaInfo->enPdpType      = stPdpCidInfo.stPdpAddr.enPdpType;
    }
    else
    {
        /* Ĭ��ʹ��IPV4 */
        pstDialParaInfo->enPdpType      = TAF_PDP_IPV4;
    }

#if(FEATURE_ON == FEATURE_IPV6)
    if (VOS_ERR == AT_CheckIpv6Capability(pstDialParaInfo->enPdpType))
    {
        AT_INFO_LOG("AT_NidsGetDialParam:PDP type is error");
        return AT_FAILURE;
    }
#endif

    if ( 0 != gastAtParaList[2].usParaLen )
    {
        pstDialParaInfo->bitOpApn       = VOS_TRUE;

        PS_MEM_CPY((VOS_CHAR*)pstDialParaInfo->aucApn,
                   (VOS_CHAR*)gastAtParaList[2].aucPara,
                   gastAtParaList[2].usParaLen);
        pstDialParaInfo->aucApn[gastAtParaList[2].usParaLen] = 0;
    }

    if ( 0 != gastAtParaList[3].usParaLen )
    {
        pstDialParaInfo->bitOpUserName  = VOS_TRUE;

        PS_MEM_CPY((VOS_CHAR*)pstDialParaInfo->aucUserName,
                   (VOS_CHAR*)gastAtParaList[3].aucPara,
                   gastAtParaList[3].usParaLen);
        pstDialParaInfo->aucUserName[gastAtParaList[3].usParaLen] = 0;
    }

    if ( 0 != gastAtParaList[4].usParaLen )
    {
        pstDialParaInfo->bitOpPassWord  = VOS_TRUE;

        PS_MEM_CPY((VOS_CHAR*)pstDialParaInfo->aucPassWord,
                   (VOS_CHAR*)gastAtParaList[4].aucPara,
                   gastAtParaList[4].usParaLen);
        pstDialParaInfo->aucPassWord[gastAtParaList[4].usParaLen] = 0;
    }

    /* Auth Type */
    if ( gastAtParaList[5].usParaLen > 0 )
    {
        pstDialParaInfo->bitOpAuthType  = VOS_TRUE;
        pstDialParaInfo->enAuthType     = AT_CtrlGetPDPAuthType(gastAtParaList[5].ulParaValue,
                                                                gastAtParaList[5].usParaLen);
    }
    else
    {
        /* ����û��������볤�Ⱦ���Ϊ0, �Ҽ�Ȩ����δ����, ��Ĭ��ʹ��CHAP���� */
        if ( (0 != gastAtParaList[3].usParaLen)
          && (0 != gastAtParaList[4].usParaLen) )
        {
            pstDialParaInfo->bitOpAuthType = VOS_TRUE;
            pstDialParaInfo->enAuthType    = PPP_CHAP_AUTH_TYPE;
        }
    }

    /* ����<PDP_addr> */
    if ( gastAtParaList[6].usParaLen > 0 )
    {
        /* ��IP��ַ�ַ���ת��������, IP��ַ��ʽ�Ѿ�ͳһ��ǰ���� */
        if ( VOS_OK == AT_Ipv4AddrAtoi((VOS_CHAR*)gastAtParaList[6].aucPara,
                                       (VOS_UINT8*)pstDialParaInfo->stPdpAddr.aucIpv4Addr) )
        {
            pstDialParaInfo->bitOpIpAddr         = VOS_TRUE;
            pstDialParaInfo->stPdpAddr.enPdpType = TAF_PDP_IPV4;
        }
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_AppDialUpProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_DIAL_PARA_STRU               stDialParaInfo;
    AT_DIAL_PARAM_STRU                 *pstAppDailPara;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;
    AT_PS_USER_INFO_STRU                stUsrInfo;

    /* ��ʼ�� */
    PS_MEM_SET(&stDialParaInfo, 0x00, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstAppPdpEntity = AT_APP_GetPdpEntInfoAddr();
    pstAppDailPara  = AT_APP_GetDailParaAddr();

    PS_MEM_SET(pstAppDailPara->aucUsername, 0x00, TAF_MAX_GW_AUTH_USERNAME_LEN);
    PS_MEM_SET(pstAppDailPara->aucPassword, 0x00, TAF_MAX_GW_AUTH_PASSWORD_LEN);

    PS_MEM_SET(&stUsrInfo, 0x00, sizeof(AT_PS_USER_INFO_STRU));

    /* �����û���Ϣ */
    AT_APP_ParseUsrInfo(ucIndex, &stUsrInfo);

    /* ����Ѿ����Ż����ڲ���, ֱ�ӷ���OK */
    ulResult = AT_AppCheckPdpStateForDial();
    if (AT_SUCCESS == ulResult)
    {
        AT_INFO_LOG("AT_AppDialUpProc: The state is already active or activing");

        /* ����PDP״̬, �ϱ���APP */
        AT_AppReportPdpActiveState(ucIndex, pstAppPdpEntity);

        return AT_SUCCESS;
    }

    /* �Ͽ����Ź����в��������� */
    if (AT_FAILURE == ulResult)
    {
        AT_INFO_LOG("AT_AppDialUpProc: the state is error");

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ��ȡ���Ų��� */
    ulResult = AT_GetAppDialParam(&stDialParaInfo, ucIndex);
    if ( AT_SUCCESS != ulResult )
    {
        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ���沦�Ų���������IPV6���� */
    pstAppDailPara->usAuthType      = stDialParaInfo.enAuthType;
    pstAppDailPara->ucCid           = stDialParaInfo.ucCid;
    pstAppDailPara->enPdpType       = stDialParaInfo.enPdpType;

    /* APN */
    pstAppDailPara->ucAPNLen        = (VOS_UINT8)gastAtParaList[2].usParaLen;
    PS_MEM_CPY((VOS_CHAR *)pstAppDailPara->aucAPN,
               (VOS_CHAR *)gastAtParaList[2].aucPara,
               gastAtParaList[2].usParaLen);

    /* �����û��� */
    pstAppDailPara->usUsernameLen   = gastAtParaList[3].usParaLen;
    PS_MEM_CPY((VOS_CHAR *)pstAppDailPara->aucUsername,
               (VOS_CHAR *)gastAtParaList[3].aucPara,
               gastAtParaList[3].usParaLen);

    /* �����û����� */
    pstAppDailPara->usPasswordLen   = gastAtParaList[4].usParaLen;
    PS_MEM_CPY((VOS_CHAR *)pstAppDailPara->aucPassword,
               (VOS_CHAR *)gastAtParaList[4].aucPara,
               gastAtParaList[4].usParaLen);

    /* PDP ADDR */
    pstAppDailPara->ulIPv4ValidFlag = stDialParaInfo.bitOpIpAddr;
    PS_MEM_CPY((VOS_CHAR *)pstAppDailPara->aucIPv4Addr,
               (VOS_CHAR *)gastAtParaList[6].aucPara,
               gastAtParaList[6].usParaLen);

    AT_GetPdpContextFromAtDialParam(&stPdpPrimContextExt,AT_APP_GetDailParaAddr());

    /* ���ò��Ų��� */
    if (VOS_ERR == TAF_AGENT_SetPdpCidPara(gastAtClientTab[ucIndex].usClientId,
                                        &stPdpPrimContextExt))
    {
        AT_WARN_LOG("AT_AppDialUpProc: Def Pdp Context Fail.");

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

        return AT_ERROR;
    }

    /* ���𲦺� */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_AT,
                                  AT_APP_GET_CLIENT_ID(),
                                  0,
                                  &stDialParaInfo))
    {
        /* �����û���Ϣ */
        pstAppPdpEntity->stUsrInfo = stUsrInfo;

        if (TAF_PDP_IPV4 == stDialParaInfo.enPdpType)
        {
            pstAppPdpEntity->ucIpv4Cid   = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        }
        else if (TAF_PDP_IPV6 == stDialParaInfo.enPdpType)
        {
            pstAppPdpEntity->ucIpv6Cid   = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        }
        else
        {
            pstAppPdpEntity->ucIpv4v6Cid = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        }

        AT_APP_SetFirstActPdpType(stDialParaInfo.enPdpType);
        AT_APP_SetActPdpType(stDialParaInfo.enPdpType);
        AT_AppSetPdpState(stDialParaInfo.enPdpType, AT_PDP_STATE_ACTING);


        /* ���õ�ǰpdpact�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;

    }

    return AT_ERROR;

}
VOS_UINT32 AT_AppDialDownProc(
    VOS_UINT8                           ucIndex
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    VOS_UINT32                          ulPdpFlag;

    ulPdpFlag = 0;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    /* ������е�PDP������IDLE, ����OK; �����һ������DEACTING, Ҳ����OK */
    if (VOS_TRUE == AT_AppCheckPdpIdleState())
    {
        AT_WARN_LOG("AT_AppDialDownProc: The state is already IDLE.");
        return AT_OK;
    }

    if ((AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4v6State)
     || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4v6State) )
    {
         /* AT^NDISDUP�ĵ�һ�������͵�ǰ��cid��һ�£�ֱ�ӷ���ERROR */
        if (pstAppPdpEntity->ucIpv4v6Cid != gastAtParaList[0].ulParaValue)
        {
            return AT_ERROR;
        }

        ulPdpFlag = 1;

        if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                     AT_APP_GET_CLIENT_ID(),
                                     0,
                                     g_stAtAppPdpEntity.ucIpv4v6Cid))
        {
            AT_WARN_LOG("AT_AppDialDownProc():TAF_PS_CallEnd fail");
        }

        AT_AppSetPdpState(TAF_PDP_IPV4V6, AT_PDP_STATE_DEACTING);
    }
    else
    {
        if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
          || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4State) )
        {
            /* AT^NDISDUP�ĵ�һ�������͵�ǰ��cid��һ�£�ֱ�ӷ���ERROR */
            if (pstAppPdpEntity->ucIpv4Cid == gastAtParaList[0].ulParaValue)
            {
                ulPdpFlag = 1;
                if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_APP_GET_CLIENT_ID(),
                                             0,
                                             pstAppPdpEntity->ucIpv4Cid))
                {
                    AT_WARN_LOG("AT_AppDialDownProc():TAF_PS_CallEnd fail");
                }

                AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);

                if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv6State)
                  || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv6State) )
                {
                    if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                                 AT_APP_GET_CLIENT_ID(),
                                                 0,
                                                 pstAppPdpEntity->ucIpv6Cid))
                    {
                        AT_WARN_LOG("AT_AppDialDownProc():TAF_PS_CallEnd fail");
                    }

                    AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);
                }
            }

        }

        if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv6State)
          || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv6State) )
        {
            /* AT^NDISDUP�ĵ�һ�������͵�ǰ��cid��һ�£�ֱ�ӷ���ERROR */
            if (pstAppPdpEntity->ucIpv6Cid == gastAtParaList[0].ulParaValue)
            {
                ulPdpFlag = 1;
                if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                             AT_APP_GET_CLIENT_ID(),
                                             0,
                                             pstAppPdpEntity->ucIpv6Cid))
                {
                    AT_WARN_LOG("AT_AppDialDownProc():TAF_PS_CallEnd fail");
                }

                AT_AppSetPdpState(TAF_PDP_IPV6, AT_PDP_STATE_DEACTING);

                if ( (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
                  || (AT_PDP_STATE_ACTED  == pstAppPdpEntity->enIpv4State) )
                {
                    if (VOS_OK != TAF_PS_CallEnd(WUEPS_PID_AT,
                                                 AT_APP_GET_CLIENT_ID(),
                                                 0,
                                                 pstAppPdpEntity->ucIpv4Cid))
                    {
                        AT_WARN_LOG("AT_AppDialDownProc():TAF_PS_CallEnd fail");
                    }

                    AT_AppSetPdpState(TAF_PDP_IPV4, AT_PDP_STATE_DEACTING);
                }

            }

        }

    }

    if (0 == ulPdpFlag)
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NDISCONN_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_DialProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    /* ����Ϊ�� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        AT_NORM_LOG1("AT_DialProc:g_stATParseCmd.ucCmdOptType=%d\n",g_stATParseCmd.ucCmdOptType);

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������� */
    ulResult = AT_AppCheckDialParam();
    if (AT_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_DialProc:WARNING: Wrong parameter!");

        /* ��¼PS����д����� */
        AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_INVALID_PARAMETER);

        return ulResult;
    }

    /* �������ţ����Ż�Ͽ����� */
    if (0 == gastAtParaList[1].ulParaValue)
    {
        return AT_AppDialDownProc(ucIndex);
    }
    else
    {
        if (AT_HILINK_GATEWAY_MODE == g_enHiLinkMode)
        {
            /* ��¼PS����д����� */
            AT_PS_SetPsCallErrCause(ucIndex, TAF_PS_CAUSE_UNKNOWN);

            return AT_ERROR;
        }

        return AT_AppDialUpProc(ucIndex);
    }
}


VOS_UINT32 AT_SetNdisdupPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    /* ע�ⲻҪ��������:
       AT^NDISUP AT���ֻ������NDIS���š�E5�����翨��̬Ҳʹ�ø�������в��š�
       ʵ��ʱ��Ҫ�����·�AT����Ķ˿���̬�����ò�ͬ�ĺ���API���в��š� */

    /*��ά�ɲ�: ���յ�APP�·���NDIS���������sliceֵ*/
    g_ulRcvAppNdisdupSlice = OM_GetSlice();

    if (AT_NDIS_USER == gastAtClientTab[ucIndex].UserType)
    {
        return At_NdisDupProc(ucIndex);
    }

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        /* ����E5�����翨��E355����̬�Ĳ��� */
        if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
        {
            return AT_DialProc(ucIndex);
        }
        /* �����ֻ���̬�Ĳ��� */
        else
        {
            return AT_PS_ProcDialCmd(ucIndex);
        }
    }

    /* ����AP_MODEM��̬ͨ��HISCͨ���·��Ĳ��� */
    if (VOS_TRUE == AT_CheckHsicUser(ucIndex))
    {
        return AT_PS_ProcDialCmd(ucIndex);
    }

    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            return AT_PS_ProcDialCmd(ucIndex);
        }

        if (SYSTEM_APP_WEBUI == *pucSystemAppConfig)
        {
            return AT_DialProc(ucIndex);
        }
        else
        {
            return At_NdisDupProc(ucIndex);
        }
    }


    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            return AT_PS_ProcDialCmd(ucIndex);
        }
    }

    /*��V2�汾�У������˿�����������ֱ�ӷ���OK*/
    return AT_OK;
}


/*****************************************************************************
 Prototype      : At_SetAuthdataPara
 Description    : ^AUTHDATA=<cid>[,<Auth_type>[<PLMN>[,<passwd>[,<username>]]]
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-27
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_SetAuthdataPara (TAF_UINT8 ucIndex)
{
    TAF_AUTHDATA_EXT_STRU               stAuthDataInfo;

    PS_MEM_SET(&stAuthDataInfo, 0, sizeof(TAF_AUTHDATA_EXT_STRU));

    /* ���޲�������ֱ�ӷ���OK */
    if ( AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType )
    {
        return AT_OK;
    }

    /* ������� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 5 )
    {
        return AT_TOO_MANY_PARA;
    }

    stAuthDataInfo.ucCid                    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* �������ֻ��<CID>, �������������� */
    if ( 1 == gucAtParaIndex )
    {
        stAuthDataInfo.ucDefined            = VOS_FALSE;
    }
    else
    {
        stAuthDataInfo.ucDefined            = VOS_TRUE;

        /* ����<Auth_type> */
        if ( 0 != gastAtParaList[1].usParaLen )
        {
            stAuthDataInfo.bitOpAuthType    = VOS_TRUE;
            stAuthDataInfo.enAuthType       = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }

        /* ����<PLMN> */
        if ( gastAtParaList[2].usParaLen > TAF_MAX_AUTHDATA_PLMN_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ( 0 != gastAtParaList[2].usParaLen )
        {
            stAuthDataInfo.bitOpPlmn        = VOS_TRUE;

            PS_MEM_CPY((VOS_CHAR*)stAuthDataInfo.aucPlmn,
                       (VOS_CHAR*)gastAtParaList[2].aucPara,
                       gastAtParaList[2].usParaLen);
            stAuthDataInfo.aucPlmn[gastAtParaList[2].usParaLen] = 0;
        }

        /* ����<username> */
        if ( gastAtParaList[4].usParaLen > TAF_MAX_AUTHDATA_USERNAME_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if(0 != gastAtParaList[4].usParaLen)
        {
            stAuthDataInfo.bitOpUserName    = VOS_TRUE;

            PS_MEM_CPY((VOS_CHAR*)stAuthDataInfo.aucUserName,
                       (VOS_CHAR*)gastAtParaList[4].aucPara,
                       gastAtParaList[4].usParaLen);
            stAuthDataInfo.aucUserName[gastAtParaList[4].usParaLen] = 0;
        }

        /* ����<passwd> */
        if ( gastAtParaList[3].usParaLen > TAF_MAX_AUTHDATA_PASSWORD_LEN )
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if ( 0 != gastAtParaList[3].usParaLen )
        {
            stAuthDataInfo.bitOpPassWord    = VOS_TRUE;

            PS_MEM_CPY((VOS_CHAR*)stAuthDataInfo.aucPassWord,
                       (VOS_CHAR*)gastAtParaList[3].aucPara,
                       gastAtParaList[3].usParaLen);
            stAuthDataInfo.aucPassWord[gastAtParaList[3].usParaLen] = 0;
        }

    }

    /* ִ��������� */
    if ( VOS_OK != TAF_PS_SetAuthDataInfo(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0,
                                          &stAuthDataInfo))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 At_SetCrpnPara (TAF_UINT8 ucIndex)
{
    MN_MMA_CRPN_QRY_REQ_STRU            stMnMmaCrpnQry;

    /* ������Ч�Լ�� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        return AT_OK;
    }

    if (2 != gucAtParaIndex)
    {
        AT_WARN_LOG("At_SetCrpnPara: gucAtParaIndex != 2.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��<name_index>��<name>����Ϊ�գ��򷵻�ʧ�� */
    if ((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���<name>����������Ч�� */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        if (gastAtParaList[1].usParaLen >= TAF_PH_OPER_NAME_LONG)
        {
            return AT_CME_TEXT_STRING_TOO_LONG;
        }
    }
    else if(1 == gastAtParaList[0].ulParaValue)
    {
        if (gastAtParaList[1].usParaLen >= TAF_PH_OPER_NAME_SHORT)
        {
            return AT_CME_TEXT_STRING_TOO_LONG;
        }
    }
    else
    {
        if ((gastAtParaList[1].usParaLen < 5) || (gastAtParaList[1].usParaLen > 6))
        {
            return AT_CME_TEXT_STRING_TOO_LONG;
        }
    }


    PS_MEM_SET(&stMnMmaCrpnQry, 0, sizeof(MN_MMA_CRPN_QRY_REQ_STRU));

    /* ������Ϣ�ṹ��ֵ */
    stMnMmaCrpnQry.ucPlmnType    = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stMnMmaCrpnQry.usPlmnNameLen = gastAtParaList[1].usParaLen;
    PS_MEM_CPY(stMnMmaCrpnQry.aucPlmnName, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);

    /* ����TAF_MSG_MMA_CRPN_HANDLE��Ϣ��MMA���� */
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                        0,
                                        TAF_MSG_MMA_CRPN_HANDLE,
                                        &stMnMmaCrpnQry,
                                        sizeof(MN_MMA_CRPN_QRY_REQ_STRU),
                                        I0_WUEPS_PID_MMA))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CRPN_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
VOS_UINT32  AT_SetAlsPara( TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* �������� */
    if ( gucAtParaIndex > 2 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*��һ������������*/
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 0 != gastAtParaList[1].usParaLen )
    {
        ulRet = MN_CALL_SetAlsLineNo(ucIndex,
                                     (MN_CALL_ALS_LINE_NO_ENUM_U8)gastAtParaList[1].ulParaValue);
        if (VOS_OK != ulRet)
        {
            return AT_ERROR;
        }

        pstSsCtx->ucSalsType = (TAF_UINT8)gastAtParaList[0].ulParaValue;

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_SET_ALS_REQ;

        return AT_WAIT_ASYNC_RETURN;
    }

    pstSsCtx->ucSalsType = (TAF_UINT8)gastAtParaList[0].ulParaValue;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_CheckRxDivCmdPara
 ��������  : �������^RXDIV�����Ƿ���Ч
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��21��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_CheckRxDivOrRxPriCmdPara(VOS_VOID)
{
    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }
    /* ������ȫ��ֱ�ӷ���ʧ�� */
    if (   (0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (18 < gastAtParaList[1].usParaLen))
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    /* Ŀǰ֧��WCDMA�����������ֵ��ֱ�ӷ���ʧ�� */
    if ('0' != gastAtParaList[0].aucPara[0])
    {
         return AT_CME_RX_DIV_OTHER_ERR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_GetUserSetRxDivParaNum
 ��������  : ���û����õĽ��շּ�����ת��������
 �������  : VOS_UINT32      *pulSetDivLowBands
             VOS_UINT32      *pulSetDivHighBands
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��02��21��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_GetUserSetRxDivOrRxPriParaNum(
                VOS_UINT32      *pulSetDivLowBands,
                VOS_UINT32      *pulSetDivHighBands
                )
{
    VOS_UINT32                      ulResult1;
    VOS_UINT32                      ulResult2;
    VOS_UINT8                       *pucInputPara;
    VOS_UINT16                      usInputLen;

    ulResult1 = AT_OK;
    ulResult2 = AT_OK;

    *pulSetDivLowBands  = 0;
    *pulSetDivHighBands = 0;

    /* ���ý��շּ��������������ָ�ʽ:��0x�Ͳ���0x.
       �����ʽ��0xʱ����0x���治��������������Ϊ�������� */
    pucInputPara = gastAtParaList[1].aucPara;
    usInputLen   = gastAtParaList[1].usParaLen;
    if (   ('0' == gastAtParaList[1].aucPara[0])
        && ('X' == gastAtParaList[1].aucPara[1]))
    {
        if (gastAtParaList[1].usParaLen < 3)
        {
            return AT_CME_RX_DIV_OTHER_ERR;
        }

        pucInputPara = &(gastAtParaList[1].aucPara[2]);
        usInputLen   = (VOS_UINT8)(gastAtParaList[1].usParaLen - 2);
    }

    if (usInputLen > 16)
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    /* AT��ǰ�����ʱ��ת������ASCII�룬��ʱ��Ҫת�������� */
    if (usInputLen <= 8)
    {
        ulResult1 = At_String2Hex(pucInputPara,
                        usInputLen, pulSetDivLowBands);
    }
    else
    {
        ulResult1 = At_String2Hex(pucInputPara,
                            usInputLen-8,pulSetDivHighBands);
        ulResult2 = At_String2Hex(pucInputPara + (usInputLen - 8),
                            8,pulSetDivLowBands);
    }
    if ((AT_FAILURE == ulResult1) || (AT_FAILURE == ulResult2))
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_CovertUserSetRxDivParaToMsInternal
 ��������  : ���û����õķּ���Ϣת���ɱ��ظ�ʽ
 �������  : VOS_UINT32 ulSetDivLowBands
             VOS_UINT32 ulSetDivHighBands
             VOS_UINT16 *pusSetDivBands
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��2��21��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 At_CovertUserSetRxDivOrRxPriParaToMsInternal(
    VOS_UINT32 ulSetDivLowBands,
    VOS_UINT32 ulSetDivHighBands,
    VOS_UINT16 *pusSetDivBands
                )
{
    VOS_UINT32                      ulMsCapaDivLowBands;
    VOS_UINT32                      ulMsCapaDivHighBands;

    *pusSetDivBands      = 0;

    /*�û����õĽ��շּ���ʽ����:
        0x80000            GSM850
        0x300              GSM900
        0x80               DCS1800
        0x200000           PCS1900
        0x400000           WCDMA2100
        0x800000           WCDMA1900
        0x1000000          WCDMA1800
        0x2000000          WCDMA_AWS
        0x4000000          WCDMA850
        0x2000000000000    WCDMA900
        0x4000000000000    WCDMA1700
      ��MS֧�ֵĽ��շּ���ʽ����:
        2100M/ bit1  1900M/bit2  1800M/bit3  1700M/bit4  1600M/bit5
        1500M/bit6   900M/bit7   850M/bit8   800M/bit9   450M/bit10
      ��Ҫ���û����õĽ��շּ�ת����MS֧�ֵĸ�ʽ
    */
    ulMsCapaDivLowBands  = TAF_PH_BAND_WCDMA_I_IMT_2100
                         | TAF_PH_BAND_WCDMA_II_PCS_1900
                         | TAF_PH_BAND_WCDMA_III_1800
                         | TAF_PH_BAND_WCDMA_V_850;
    ulMsCapaDivHighBands = TAF_PH_BAND_WCDMA_IX_1700
                         | TAF_PH_BAND_WCDMA_VIII_900;
    if (   (0 != (ulSetDivLowBands & (~ulMsCapaDivLowBands)))
        || (0 != (ulSetDivHighBands & (~ulMsCapaDivHighBands))))
    {
        return AT_CME_RX_DIV_NOT_SUPPORTED;
    }
    if (0 != (ulSetDivHighBands & TAF_PH_BAND_WCDMA_VIII_900))
    {
        *pusSetDivBands |= AT_MS_SUPPORT_RX_DIV_900;
    }
    if (0 != (ulSetDivHighBands & TAF_PH_BAND_WCDMA_IX_1700))
    {
        *pusSetDivBands |= AT_MS_SUPPORT_RX_DIV_IX_1700;
    }
    if (0 != (ulSetDivLowBands & TAF_PH_BAND_WCDMA_I_IMT_2100))
    {
        *pusSetDivBands |= AT_MS_SUPPORT_RX_DIV_2100;
    }
    if (0 != (ulSetDivLowBands & TAF_PH_BAND_WCDMA_II_PCS_1900))
    {
        *pusSetDivBands |= AT_MS_SUPPORT_RX_DIV_1900;
    }
    if (0 != (ulSetDivLowBands & TAF_PH_BAND_WCDMA_III_1800))
    {
        *pusSetDivBands |= AT_MS_SUPPORT_RX_DIV_1800;
    }
    if (0 != (ulSetDivLowBands & TAF_PH_BAND_WCDMA_V_850))
    {
        *pusSetDivBands |= AT_MS_SUPPORT_RX_DIV_850;
    }

    return AT_OK;
}


VOS_UINT32 At_SaveRxDivPara(
        VOS_UINT16                      usSetDivBands,
        VOS_UINT8                       ucRxDivCfg
        )
{
    TAF_AT_NVIM_RXDIV_CONFIG_STRU       stRxdivConfig;
    VOS_UINT32                          ulNvLength;

    PS_MEM_SET(&stRxdivConfig, 0x00, sizeof(TAF_AT_NVIM_RXDIV_CONFIG_STRU));
    ulNvLength = 0;

    stRxdivConfig.ucVaild = ucRxDivCfg;

    /*NV��en_NV_Item_ANTENNA_CONFIG��V3R2B060��ĳ�en_NV_Item_W_RF_DIV_BAND��
      ����NV����ȫһ����*/
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_W_RF_DIV_BAND, &usSetDivBands, sizeof(VOS_UINT16)))
    {
        PS_LOG(WUEPS_PID_AT, 0, PS_PRINT_ERROR,
                "NV_WriteEx en_NV_Item_W_RF_DIV_BAND fail!\n");
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    NV_GetLength(en_NV_Item_RXDIV_CONFIG, &ulNvLength);
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_RXDIV_CONFIG, &stRxdivConfig, ulNvLength))
    {
        PS_LOG(WUEPS_PID_AT, 0, PS_PRINT_ERROR,
                "NV_WriteEx en_NV_RXDIV_CONFIG fail!\n");
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    return AT_OK;
}
#if(FEATURE_LTE == FEATURE_ON)
VOS_UINT32 At_GetTmodeFromNV(VOS_VOID)
{
    VOS_UINT32                          ulTmodeRat;
    VOS_UINT32                          ulRet;
#if(VOS_OS_VER == VOS_WIN32)
    ulTmodeRat=0x40;
    ulRet = ERR_MSP_SUCCESS;
#else


    ulTmodeRat = 0;

    ulRet = NVM_Read(EN_NV_ID_TMODE_RAT, &ulTmodeRat, sizeof(ulTmodeRat));
    vos_printf("\n At_GetTmodeFromNV ulTmodeRat=0x%x \n",ulTmodeRat);
#endif
    if(ERR_MSP_SUCCESS != ulRet)
    {
        vos_printf("\n At_GetTmodeFromNV return failed !!!\n");
        ulTmodeRat = 0xc0;

        g_stTmodeRat.ucWCDMAIsSet   =      ulTmodeRat & 0x00000001;
        g_stTmodeRat.ucCDMAIsSet    = (ulTmodeRat>>1) & 0x00000001;
        g_stTmodeRat.ucTDSCDMAIsSet = (ulTmodeRat>>2) & 0x00000001;
        g_stTmodeRat.ucGSMIsSet     = (ulTmodeRat>>3) & 0x00000001;
        g_stTmodeRat.ucEDGEIsSet    = (ulTmodeRat>>4) & 0x00000001;
        g_stTmodeRat.ucAWSIsSet     = (ulTmodeRat>>5) & 0x00000001;
        g_stTmodeRat.ucFDDLTEIsSet  = (ulTmodeRat>>6) & 0x00000001;
        g_stTmodeRat.ucTDDLTEIsSet  = (ulTmodeRat>>7) & 0x00000001;
        g_stTmodeRat.ucWIFIIsSet    = (ulTmodeRat>>8) & 0x00000001;

        return ulRet;
    }
    else
    {
        if(ulTmodeRat == 0)
        {
            return ERR_MSP_NV_DATA_INVALID;
        }
        else
        {
            g_stTmodeRat.ucWCDMAIsSet   =      ulTmodeRat & 0x00000001;
            g_stTmodeRat.ucCDMAIsSet    = (ulTmodeRat>>1) & 0x00000001;
            g_stTmodeRat.ucTDSCDMAIsSet = (ulTmodeRat>>2) & 0x00000001;
            g_stTmodeRat.ucGSMIsSet     = (ulTmodeRat>>3) & 0x00000001;
            g_stTmodeRat.ucEDGEIsSet    = (ulTmodeRat>>4) & 0x00000001;
            g_stTmodeRat.ucAWSIsSet     = (ulTmodeRat>>5) & 0x00000001;
            g_stTmodeRat.ucFDDLTEIsSet  = (ulTmodeRat>>6) & 0x00000001;
            g_stTmodeRat.ucTDDLTEIsSet  = (ulTmodeRat>>7) & 0x00000001;
            g_stTmodeRat.ucWIFIIsSet    = (ulTmodeRat>>8) & 0x00000001;

        }
    }
    return ERR_MSP_SUCCESS;

}

VOS_BOOL at_TmodeIsLteSingle(VOS_VOID)
{
    VOS_UINT32 ulLte = 0;
    VOS_UINT32 ulGu = 0;

    ulLte = g_stTmodeRat.ucTDSCDMAIsSet+g_stTmodeRat.ucFDDLTEIsSet+g_stTmodeRat.ucTDDLTEIsSet;
    ulGu = g_stTmodeRat.ucWCDMAIsSet+g_stTmodeRat.ucCDMAIsSet+g_stTmodeRat.ucGSMIsSet
              +g_stTmodeRat.ucEDGEIsSet +g_stTmodeRat.ucAWSIsSet+g_stTmodeRat.ucWIFIIsSet;

    if( ( ulLte >= 1 ) && ( ulGu == 0 ) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

VOS_BOOL at_TmodeIsGuSingle(VOS_VOID)
{
    VOS_UINT32 ulLte = 0;
    VOS_UINT32 ulGu = 0;

    ulLte = g_stTmodeRat.ucTDSCDMAIsSet+g_stTmodeRat.ucFDDLTEIsSet+g_stTmodeRat.ucTDDLTEIsSet;
    ulGu = g_stTmodeRat.ucWCDMAIsSet+g_stTmodeRat.ucCDMAIsSet+g_stTmodeRat.ucGSMIsSet
              +g_stTmodeRat.ucEDGEIsSet +g_stTmodeRat.ucAWSIsSet+g_stTmodeRat.ucWIFIIsSet;

    if( ( ulLte == 0 )&& ( ulGu >= 1 ) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

VOS_BOOL at_TmodeIsMultiMode(VOS_VOID)
{
    VOS_UINT32 ulLte = 0;
    VOS_UINT32 ulGu = 0;

    ulLte = g_stTmodeRat.ucTDSCDMAIsSet+g_stTmodeRat.ucFDDLTEIsSet+g_stTmodeRat.ucTDDLTEIsSet;
    ulGu = g_stTmodeRat.ucWCDMAIsSet+g_stTmodeRat.ucCDMAIsSet+g_stTmodeRat.ucGSMIsSet
              +g_stTmodeRat.ucEDGEIsSet +g_stTmodeRat.ucAWSIsSet+g_stTmodeRat.ucWIFIIsSet;

    if( ( ulLte >= 1 )&& ( ulGu >= 1 ) )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}


TAF_VOID AtTmodShowDebug(VOS_VOID)
{
    vos_printf("\n g_ulTmodeNum=0x%x \n",g_ulTmodeNum);
    vos_printf("\n g_ulGuTmodeCnfNum=0x%x \n",g_ulGuTmodeCnfNum);
}

#endif


TAF_UINT32  At_SetTModePara(TAF_UINT8 ucIndex )
{

    TAF_PH_OP_MODE_STRU                 PhModeSet;
    VOS_UINT8                           ucUpdateFlag;


    PS_MEM_SET(&PhModeSet, 0x00, sizeof(PhModeSet));

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����TMODE */
    if (AT_TMODE_BUTT <= gastAtParaList[0].ulParaValue )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    switch (gastAtParaList[0].ulParaValue)
    {
        case AT_TMODE_NORMAL :

            PhModeSet.CmdType = TAF_PH_CMD_SET;
            PhModeSet.PhMode = TAF_PH_MODE_FULL;

            if(AT_SUCCESS == Taf_DefPhMode(gastAtClientTab[ucIndex].usClientId, 0, PhModeSet))
            {
                /* ���õ�ǰ�������� */
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
                PS_MEM_SET(&g_stAtDevCmdCtrl,0x00,sizeof(g_stAtDevCmdCtrl));
                g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_NORMAL;

                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        case AT_TMODE_FTM :

            if (AT_TMODE_UPGRADE == g_stAtDevCmdCtrl.ucCurrentTMode)
            {
                return AT_ERROR;
            }

            PhModeSet.CmdType = TAF_PH_CMD_SET;
            PhModeSet.PhMode = TAF_PH_MODE_FT;

            if(AT_SUCCESS == Taf_DefPhMode(gastAtClientTab[ucIndex].usClientId, 0, PhModeSet))
            {
                /* ���õ�ǰ�������� */
                g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_FTM;
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
                return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
            }
            else
            {
                return AT_ERROR;
            }
        case AT_TMODE_UPGRADE :

            if (AT_TMODE_FTM == g_stAtDevCmdCtrl.ucCurrentTMode)
            {
                return AT_ERROR;
            }
            /* ����Ϣ�� C ������������־λ������Ҫ������ʱ������Ϣ����ΪDRV_AGENT_TMODE_SET_REQ
               ֱ�ӷ���AT_OK������Ҫ�ȴ����ý�� */
            ucUpdateFlag = VOS_TRUE;

            if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_TMODE_SET_REQ,
                                   &ucUpdateFlag,
                                   sizeof(ucUpdateFlag),
                                   I0_WUEPS_PID_DRV_AGENT))
            {
                AT_ERR_LOG("AT_SetPstandbyPara: AT_FillAndSndAppReqMsg fail.");
            }

            g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_UPGRADE;
            return AT_OK;
        case AT_TMODE_RESET :

            g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_RESET;

            /* �������� */
            ucUpdateFlag = VOS_FALSE;

            if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_TMODE_SET_REQ,
                                   &ucUpdateFlag,
                                   sizeof(ucUpdateFlag),
                                   I0_WUEPS_PID_DRV_AGENT))
            {
                AT_ERR_LOG("AT_SetPstandbyPara: AT_FillAndSndAppReqMsg fail.");
            }

            return AT_OK;
           case AT_TMODE_POWEROFF:
                return AT_SetTmodeAutoPowerOff(ucIndex);

           /* ������Ҫ��ģʽ4->11��ģʽ1����ͬ�Ĵ��� */
           case AT_TMODE_SIGNALING :
               if (AT_TMODE_UPGRADE == g_stAtDevCmdCtrl.ucCurrentTMode)
               {
                   return AT_ERROR;
               }

           PhModeSet.CmdType = TAF_PH_CMD_SET;
           PhModeSet.PhMode = TAF_PH_MODE_FT;

           if(AT_SUCCESS == Taf_DefPhMode(gastAtClientTab[ucIndex].usClientId, 0, PhModeSet))
           {
               /* ���õ�ǰ�������� */
               g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_SIGNALING;
               gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
               return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
           }
           else
           {
               return AT_ERROR;
           }

           /* ������Ҫ��ģʽ5->12��ģʽ0����ͬ�Ĵ��� */
           case AT_TMODE_OFFLINE :
               PhModeSet.CmdType = TAF_PH_CMD_SET;
               PhModeSet.PhMode = TAF_PH_MODE_FULL;

           if(AT_SUCCESS == Taf_DefPhMode(gastAtClientTab[ucIndex].usClientId, 0, PhModeSet))
           {
               /* ���õ�ǰ�������� */
               gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
               PS_MEM_SET(&g_stAtDevCmdCtrl,0x00,sizeof(g_stAtDevCmdCtrl));
               g_stAtDevCmdCtrl.ucCurrentTMode = AT_TMODE_OFFLINE;

               return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
           }
           else
           {
               return AT_ERROR;
           }

#if((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS))
        case AT_TMODE_F_NONESIGNAL:
        case AT_TMODE_SYN_NONESIGNAL:
        case AT_TMODE_SET_SLAVE:
        case AT_TMODE_GU_BT:
        case AT_TMODE_TDS_FAST_CT:
        case AT_TMODE_TDS_BT:
        case AT_TMODE_COMM_CT:
            if(atSetTmodePara(ucIndex, gastAtParaList[0].ulParaValue) == AT_OK)
            {
                gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_TMODE;
                g_stAtDevCmdCtrl.ucCurrentTMode        = (VOS_UINT8)gastAtParaList[0].ulParaValue;
                return AT_WAIT_ASYNC_RETURN;
            }
            else
            {
                return AT_ERROR;
            }
#endif

        default:
            break;
    }


    return AT_ERROR;
}
TAF_UINT8 At_GetDspLoadMode(VOS_UINT32 ulRatMode)
{
    if ((AT_RAT_MODE_WCDMA == ulRatMode)
     || (AT_RAT_MODE_AWS == ulRatMode))
    {
        return VOS_RATMODE_WCDMA;
    }
    else if ((AT_RAT_MODE_GSM == ulRatMode)
          || (AT_RAT_MODE_EDGE == ulRatMode))
    {
        return VOS_RATMODE_GSM;
    }
    else
    {
        return VOS_RATMODE_BUTT;
    }

}


VOS_UINT32  At_SendTxOnOffToGHPA(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucSwitch
)
{
    AT_GHPA_RF_TX_CFG_REQ_STRU          *pstTxMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMask;

    /* ����AT_GHPA_RF_TX_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_GHPA_RF_TX_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstTxMsg = (AT_GHPA_RF_TX_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstTxMsg)
    {
        AT_WARN_LOG("At_SendRfCfgReqToGHPA: alloc Tx msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstTxMsg,0x00,sizeof(AT_GHPA_RF_TX_CFG_REQ_STRU));

    /* ��д��Ϣͷ */
    pstTxMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTxMsg->ulSenderPid     = WUEPS_PID_AT;
    pstTxMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTxMsg->ulReceiverPid   = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
    pstTxMsg->ulLength        = ulLength;

    /* Tx Cfg */

    /* ��д��Ϣ�� */
    pstTxMsg->usMsgID = ID_AT_GHPA_RF_TX_CFG_REQ;
    usMask            = G_RF_MASK_TX_AFC;

    /*AT^FDAC���õ�FDACֵ��AT^FWAVE���õ�powerֵ��ʾ�ĺ�����ͬ��ȡ�����õ�ֵ*/
    /* ������Ʒ�ʽ��
        0��GMSK��ѹ����,�˷�ʽ��usTxVpaҪ���ã�
        1�����ʿ���,�˷�ʽ��usTxPowerҪ���ã�
        2��8PSK PaVbias��ѹ&DBB Atten&RF Atten���ƣ�
        usPAVbias��usRfAtten,sDbbAtten����������Ҫ���ã�*/
    if ( VOS_TRUE == g_stAtDevCmdCtrl.bFdacFlag )
    {
        pstTxMsg->enCtrlMode = AT_GHPA_RF_CTRLMODE_TYPE_GMSK;
        pstTxMsg->usTxVpa = g_stAtDevCmdCtrl.usFDAC;  /* DAC���� */
    }
    else
    {
        pstTxMsg->enCtrlMode = AT_GHPA_RF_CTRLMODE_TYPE_TXPOWER;
        pstTxMsg->usTxPower = g_stAtDevCmdCtrl.usPower;
    }

    /* Tx Cfg */
    pstTxMsg->usMask = usMask;              /* ��λ��ʶ�������� */
    pstTxMsg->usAFC =  0;                   /* AFC */
    pstTxMsg->usFreqNum =
                (VOS_UINT16)((g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand << 12) \
                            | g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn);
                                            /* (Band << 12) | Arfcn */
    pstTxMsg->usTxMode = g_stAtDevCmdCtrl.usTxMode;    /* 0:burst����; 1:�������� */
    pstTxMsg->usModType = G_MOD_TYPE_GMSK;  /* ������Ʒ�ʽ:0��ʾGMSK����;1��ʾ8PSK���Ʒ�ʽ */

    if (AT_DSP_RF_SWITCH_ON == ucSwitch)
    {
        pstTxMsg->usTxEnable = GDSP_CTRL_TX_ON;
    }
    else
    {
        pstTxMsg->usTxEnable = GDSP_CTRL_TX_OFF;
    }

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstTxMsg))
    {
        AT_WARN_LOG("At_SendTxOnOffToGHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_UINT32  At_SendRxOnOffToGHPA(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulRxSwitch
)
{
    AT_GHPA_RF_RX_CFG_REQ_STRU          *pstRxMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMask;

    /* ����AT_GHPA_RF_RX_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_GHPA_RF_RX_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstRxMsg = (AT_GHPA_RF_RX_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstRxMsg)
    {
        AT_WARN_LOG("At_SendRxOnOffToGHPA: alloc Rx msg fail!");
        return AT_FAILURE;
    }

    /* Rx Cfg */
    pstRxMsg->ulReceiverPid   = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
    pstRxMsg->ulLength        = ulLength;
    pstRxMsg->usMsgID         = ID_AT_GHPA_RF_RX_CFG_REQ;
    pstRxMsg->usRsv           = 0;
    pstRxMsg->usRsv2          = 0;

    usMask = G_RF_MASK_RX_ARFCN | G_RF_MASK_RX_AGCMODE \
            | G_RF_MASK_RX_AGCGAIN | G_RF_MASK_RX_MODE;

    /* Reference MASK_CAL_RF_G_RX_* section */
    pstRxMsg->usMask = usMask;

    /* (Band << 12) | Arfcn */
    pstRxMsg->usFreqNum =
                    (VOS_UINT16)((g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand << 12) \
                                | g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn);

    /* 0:burst����; 1:��������;*/
    pstRxMsg->usRxMode  = AT_GDSP_RX_MODE_BURST;

    /* 1:Fast AGC,0:Slow AGC */
    pstRxMsg->usAGCMode = AT_GDSP_RX_SLOW_AGC_MODE;

    /* AGC��λ�����ĵ�,ȡֵΪ0-3*/
    pstRxMsg->usAgcGain = g_stAtDevCmdCtrl.ucLnaLevel;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstRxMsg))
    {
        AT_WARN_LOG("At_SendRxOnOffToGHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}
TAF_UINT32  At_SetFChanPara(TAF_UINT8 ucIndex )
{
    DRV_AGENT_FCHAN_SET_REQ_STRU         stFchanSetReq;

    /* ���� LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)

    if ( (AT_RAT_MODE_FDD_LTE == gastAtParaList[0].ulParaValue)
       ||(AT_RAT_MODE_TDD_LTE == gastAtParaList[0].ulParaValue))
    {

        g_stAtDevCmdCtrl.ucDeviceRatMode = (AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8)(gastAtParaList[0].ulParaValue);

        return atSetFCHANPara(ucIndex);
    }

#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_RAT_MODE_TDSCDMA == gastAtParaList[0].ulParaValue)
    {
        g_stAtDevCmdCtrl.ucDeviceRatMode = (AT_DEVICE_CMD_RAT_MODE_ENUM_UINT8)(gastAtParaList[0].ulParaValue);
        return atSetFCHANPara(ucIndex);
    }
#endif


    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FCHAN_OTHER_ERR;
    }
        /* ����������Ҫ�� */
    if (gucAtParaIndex != 3)
    {
        return AT_FCHAN_OTHER_ERR;
    }

    /* WIFI�ĵ�һ����������Ϊ8���ڶ�����������Ϊ15*/
    if (((AT_RAT_MODE_WIFI == gastAtParaList[0].ulParaValue) && (AT_BAND_WIFI != gastAtParaList[1].ulParaValue))
      ||((AT_BAND_WIFI == gastAtParaList[1].ulParaValue)&&(AT_RAT_MODE_WIFI != gastAtParaList[0].ulParaValue)))
    {
        return AT_CHANNEL_NOT_SET;
    }

    /* WIFI ��֧ */
    if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT())
    {
        if (AT_RAT_MODE_WIFI == gastAtParaList[0].ulParaValue)
        {
            /*WIFIδEnableֱ�ӷ���ʧ��*/
            if(VOS_FALSE == (VOS_UINT32)WIFI_GET_STATUS())
            {
                return AT_FCHAN_OTHER_ERR;
            }

            g_stAtDevCmdCtrl.ucDeviceRatMode = AT_RAT_MODE_WIFI;

            return AT_OK;
        }
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ���FCHAN �Ľ���ģʽ�Ƿ�֧��*/
    if ((AT_RAT_MODE_GSM != gastAtParaList[0].ulParaValue)
     && (AT_RAT_MODE_EDGE != gastAtParaList[0].ulParaValue)
     && (AT_RAT_MODE_WCDMA != gastAtParaList[0].ulParaValue)
     && (AT_RAT_MODE_AWS != gastAtParaList[0].ulParaValue))
    {
        return AT_DEVICE_MODE_ERROR;
    }

    if (AT_BAND_BUTT <= gastAtParaList[1].ulParaValue)
    {
        return AT_FCHAN_BAND_NOT_MATCH;
    }

    PS_MEM_SET(&stFchanSetReq, 0, sizeof(DRV_AGENT_FCHAN_SET_REQ_STRU));

    stFchanSetReq.ucLoadDspMode       = At_GetDspLoadMode (gastAtParaList[0].ulParaValue);
    stFchanSetReq.ucCurrentDspMode    = At_GetDspLoadMode (g_stAtDevCmdCtrl.ucDeviceRatMode);  /*��ǰ����ģʽ */
    stFchanSetReq.bDspLoadFlag        = g_stAtDevCmdCtrl.bDspLoadFlag;
    stFchanSetReq.ucDeviceRatMode     = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stFchanSetReq.ucDeviceAtBand      = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stFchanSetReq.usChannelNo         = (VOS_UINT16)gastAtParaList[2].ulParaValue;

    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_FCHAN_SET_REQ,
                                              &stFchanSetReq,
                                              sizeof(stFchanSetReq),
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FCHAN_SET;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                           /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32  At_SendTxOnOffToHPA(TAF_UINT8 ucSwitch)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMask;

    /* ����AT_HPA_RF_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendTxOnOffToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstMsg,0x00,sizeof(AT_HPA_RF_CFG_REQ_STRU));

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* ��д��Ϣ�� */
    pstMsg->usMsgID = ID_AT_HPA_RF_CFG_REQ;
    /* Tx Cfg */
    usMask =  W_RF_MASK_AFC | W_RF_MASK_TX_ARFCN \
             | W_RF_MASK_TX_TXONOFF | W_RF_MASK_TX_PAMODE;

    /*AT^FDAC���õ�FDACֵ��AT^FWAVE���õ�powerֵ��ʾ�ĺ�����ͬ��ȡ�����õ�ֵ*/
    if ( VOS_TRUE == g_stAtDevCmdCtrl.bFdacFlag )
    {
        usMask                      = usMask | W_RF_MASK_TX_AGC;
        pstMsg->stRfCfgPara.usTxAGC = g_stAtDevCmdCtrl.usFDAC;
    }
    else
    {
        usMask                       = usMask | W_RF_MASK_TX_POWER;
        pstMsg->stRfCfgPara.sTxPower = (VOS_INT16)g_stAtDevCmdCtrl.usPower;
    }

    /* Tx Cfg */
    pstMsg->stRfCfgPara.usMask      = usMask;                             /* ��λ��ʶ�������� */
    pstMsg->stRfCfgPara.usTxAFCInit = W_AFC_INIT_VALUE;              /* AFC */
    pstMsg->stRfCfgPara.usTxBand    = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;    /* 1,2,3...,Э���е�band���,ע�ⲻ��BandId */
    pstMsg->stRfCfgPara.usTxFreqNum = g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn; /* Arfcn */
    pstMsg->stRfCfgPara.usTxPAMode  = g_stAtDevCmdCtrl.ucPaLevel;

    if (AT_DSP_RF_SWITCH_ON == ucSwitch)
    {
        pstMsg->stRfCfgPara.usTxEnable = WDSP_CTRL_TX_ON;               /* �򿪷���TX */
    }
    else
    {
        pstMsg->stRfCfgPara.usTxEnable = WDSP_CTRL_TX_OFF;               /* �رշ���TX */
    }
    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendTxOnOffToHPA: Send msg fail!");
        return AT_FAILURE;
    }
    return AT_SUCCESS;
}


VOS_UINT32 At_SendRxOnOffToHPA(
    VOS_UINT32                          ulRxSwitch
)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMask;

    /* ����AT_HPA_RF_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendRxOnOffToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(AT_HPA_RF_CFG_REQ_STRU));

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* ��д��Ϣ�� */
    pstMsg->usMsgID = ID_AT_HPA_RF_CFG_REQ;

    usMask = W_RF_MASK_RX_ARFCN | W_RF_MASK_RX_ANTSEL \
             | W_RF_MASK_RX_RXONOFF;

    /* ��λ��ʶ�������� */
    pstMsg->stRfCfgPara.usMask      = usMask;

    /* 1,2,3...,Э���е�band��� */
    pstMsg->stRfCfgPara.usRxBand    = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->stRfCfgPara.usRxFreqNum = g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn;

    /* DSPƵ��Band1-Band9��ʽת��Ϊ
       W Rf support
    -------------------------------------------------------------------------------
            bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
    -------------------------------------------------------------------------------
    WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
            spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
    */

    if (AT_RX_DIV_ON == g_stAtDevCmdCtrl.ucPriOrDiv)
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_TWO;
    }
    else
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_ONE;
    }

    /* LNAģʽ���� */
    pstMsg->stRfCfgPara.usRxLNAGainMode = g_stAtDevCmdCtrl.ucLnaLevel;

    if (AT_DSP_RF_SWITCH_ON == ulRxSwitch)
    {
        if (ANT_TWO == pstMsg->stRfCfgPara.usRxAntSel)
        {
            /* CPU���ƴ���ƵоƬ,����1��2 */
            pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ALL_ANT_ON;
        }
        else
        {
            /* CPU���ƴ���ƵоƬ,����1 */
            pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ANT1_ON;
        }
    }
    else
    {
        /* �رս���RX */
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_OFF;
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendRxOnOffToHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}

VOS_UINT32 At_SetFpaPara(VOS_UINT8 ucIndex)
{
    /* ����LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return AT_CMD_NOT_SUPPORT;
    }
#endif
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return AT_CMD_NOT_SUPPORT;
    }
    /* ����״̬��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FPA_OTHER_ERR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_FPA_OTHER_ERR;
    }

    /* ���������ڷ�����ģʽ��ʹ�� */
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* �������������÷������ŵ���ʹ��,��^FCHAN�ɹ�ִ�к� */
    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    /* �����ñ����ڱ��ر��� */
    g_stAtDevCmdCtrl.ucPaLevel = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return AT_OK;

}


VOS_UINT32 At_SetFlnaPara(VOS_UINT8 ucIndex)
{

    /* ���� LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atSetFLNAPara(ucIndex);
    }
#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atSetFLNAPara(ucIndex);
    }
#endif

    /* ����״̬��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FLNA_OTHER_ERR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_FLNA_OTHER_ERR;
    }

    /* ���������ڷ�����ģʽ��ʹ�� */
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* �������������÷������ŵ���ʹ�� */
    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    /* ����LNA�ȼ�ȡֵ��Χ��� */
    if ((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        /* WDSP LNA�ȼ�ȡֵΪ0-2 */
        if (gastAtParaList[0].ulParaValue > DSP_LNA_HIGH_GAIN_MODE)
        {
            return AT_FLNA_OTHER_ERR;
        }
    }

    /* �����ñ����ڱ��ر��� */
    g_stAtDevCmdCtrl.ucLnaLevel = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    return AT_OK;

}


TAF_UINT32  At_SetFTxonPara(TAF_UINT8 ucIndex )
{
    TAF_UINT8                           ucSwitch;

    /* ���� LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atSetFTXONPara(ucIndex);
    }
#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atSetFTXONPara(ucIndex);
    }

#endif
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FTXON_OTHER_ERR;
    }
    /* ����������Ҫ�� */
    if (1 != gucAtParaIndex)
    {
        return AT_FTXON_OTHER_ERR;
    }

    ucSwitch = (VOS_UINT8) gastAtParaList[0].ulParaValue;
    if (ucSwitch > AT_DSP_RF_SWITCH_ON)
    {
        return AT_FTXON_OTHER_ERR;
    }

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    if ((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        if (AT_FAILURE == At_SendTxOnOffToHPA(ucSwitch))
        {
            return AT_FTXON_SET_FAIL;
        }
    }
    else
    {
        if (AT_FAILURE == At_SendTxOnOffToGHPA(ucIndex, ucSwitch))
        {
            return AT_FTXON_SET_FAIL;
        }
    }
    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_FTXON;
    g_stAtDevCmdCtrl.ucIndex = ucIndex;

    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */

}
VOS_UINT32  At_SetFRxonPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ulSwitch;

     /* ���� LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atSetFRXONPara(ucIndex);
    }
#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atSetFRXONPara(ucIndex);
    }
#endif


    /* ����״̬��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FRXON_OTHER_ERR;
    }

    /* ����������Ҫ�� */
    if (gucAtParaIndex != 1)
    {
        return AT_FRXON_OTHER_ERR;
    }

    /* ��AT������AT^TMODE=1������ģʽ��ʹ�� */
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ��AT������Ҫ��AT^FCHAN���÷������ŵ�����ִ�гɹ���ʹ�� */
    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    ulSwitch = gastAtParaList[0].ulParaValue;

    /* �ѿ��ؽ��ջ����󷢸�W������ */
    if ((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_AWS   == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        if (AT_FAILURE == At_SendRxOnOffToHPA(ulSwitch))
        {
            return AT_FRXON_SET_FAIL;
        }
    }
    else
    {
        /* �ѿ��ؽ��ջ����󷢸�G������ */
        if (AT_FAILURE == At_SendRxOnOffToGHPA(ucIndex, ulSwitch))
        {
            return AT_FRXON_SET_FAIL;
        }
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_FRXON;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;

}
TAF_UINT32  AT_SetFDac(TAF_UINT8 ucIndex )
{

    TAF_UINT16                           usDAC;

    /*���� LTE ģ�Ľӿڷ�֧*/
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return AT_CMD_NOT_SUPPORT;
    }
#endif
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return AT_CMD_NOT_SUPPORT;
    }
    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_FDAC_SET_FAIL;
    }
    /* ����������Ҫ�� */
    if (gucAtParaIndex != 1)
    {
        return AT_FDAC_SET_FAIL;
    }
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    usDAC = (VOS_UINT16)gastAtParaList[0].ulParaValue;

    if ((AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_AWS == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        if (usDAC > WDSP_MAX_TX_AGC)
        {
            return AT_FDAC_SET_FAIL;
        }
        else
        {
            g_stAtDevCmdCtrl.usFDAC = (VOS_UINT16)gastAtParaList[0].ulParaValue;
        }
    }
    else
    {
        if (usDAC > GDSP_MAX_TX_VPA)
        {
            return AT_FDAC_SET_FAIL;
        }
        else
        {
            g_stAtDevCmdCtrl.usFDAC = (VOS_UINT16)gastAtParaList[0].ulParaValue;
        }
    }

    /*AT^FDAC���õ�FDACֵ��AT^FWAVE���õ�powerֵ��ʾ�ĺ�����ͬ��ȡ�����õ�ֵ*/
    g_stAtDevCmdCtrl.bFdacFlag  = VOS_TRUE;
    g_stAtDevCmdCtrl.bPowerFlag = VOS_FALSE;

    return AT_OK;    /* �������������״̬ */

}


#if ( FEATURE_ON == FEATURE_LTE )

VOS_UINT32 At_SetSfm(VOS_UINT8 ucIndex)
{
    VOS_UINT32  ulCustomVersion;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    /* AT������NV�д洢����Ϣ�෴ */
    if(0 == gastAtParaList[0].ulParaValue)
    {
        ulCustomVersion = 1;    /* 1 ��ʾ��ʽ�汾 */
    }
    else
    {
        ulCustomVersion = 0;    /* 0 ��ʾ��Ƭ�汾 */
    }

    /* �ж��Ƿ�Ϊ��Ƭ�汾 */
    if ( VOS_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_SW_VERSION_FLAG, &ulCustomVersion, sizeof(ulCustomVersion)) )
    {
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}

#endif



TAF_UINT32   At_SetBsn(TAF_UINT8 ucIndex)
{
    TAF_PH_SERIAL_NUM_STRU stSerialNum;

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    /* �����������<imei>������16��ֱ�ӷ��ش��� */
    if(TAF_SERIAL_NUM_LEN != gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }


    /*���<imei>�Ƿ�Ϊ�����ַ���,������ֱ�ӷ��ش���*/
    if(AT_FAILURE == At_CheckNumCharString( gastAtParaList[0].aucPara,
                                        gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    PS_MEM_CPY(stSerialNum.aucSerialNum, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);
    PS_MEM_SET(stSerialNum.aucSerialNum+TAF_SERIAL_NUM_LEN, 0, 4*sizeof(stSerialNum.aucSerialNum[0]));

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_ManufactureInfo,
                           stSerialNum.aucSerialNum,
                           TAF_SERIAL_NUM_NV_LEN))
    {
        return AT_ERROR;
    }
    else
    {
       return AT_OK;
    }

}


VOS_UINT32   At_SetQosPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                               ucQosPara;
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU         stATTrafficClass;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulNvLength;

    enModemId = MODEM_ID_0;
    ulNvLength = 0;

    /* ����״̬���ͼ�� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ���ݱ���δ��� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_DATA_UNLOCK_ERROR;
    }

    /* ����������Ϊ1 */
    if (gucAtParaIndex != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* �������Ȳ�Ϊ1 */
    if (gastAtParaList[0].usParaLen != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    ucQosPara = gastAtParaList[0].aucPara[0];

    /* ucQosParaȡֵ��ΧΪ'0'~'4' */
    if (('0' <= ucQosPara) && ('4' >= ucQosPara))
    {
        ucQosPara = gastAtParaList[0].aucPara[0] - '0';
    }
    else
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ��NV��en_NV_Item_TRAFFIC_CLASS_Type��ucStatus��Ԫ��Ϊ����̬1 */
    stATTrafficClass.ucStatus       = NV_ITEM_ACTIVE;

    /* �����ֲ���ֵд��NV���ucTrafficClass��Ԫ */
    stATTrafficClass.ucTrafficClass = ucQosPara;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetQosPara: Get modem id fail.");
        return AT_ERROR;
    }

    NV_GetLength(en_NV_Item_TRAFFIC_CLASS_Type, &ulNvLength);
    if (NV_OK != NV_WriteEx(enModemId,
                            en_NV_Item_TRAFFIC_CLASS_Type,
                            &stATTrafficClass,
                            ulNvLength))
    {
        AT_WARN_LOG("At_SetQosPara:WARNING:NVIM Write en_NV_Item_TRAFFIC_CLASS_Type failed!");
        return AT_DEVICE_OTHER_ERROR;
    }

    return  AT_OK;
}
VOS_UINT32   At_SetSDomainPara(VOS_UINT8 ucIndex)
{
    TAF_PH_SERVICE_DOMAIN               ucSrvDomain;
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT32                          ulNvLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    ulNvLength = 0;

    /* ����״̬���ͼ�� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ���ݱ���δ��� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_DATA_UNLOCK_ERROR;
    }

    /* ����������Ϊ1 */
    if (gucAtParaIndex != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* �������Ȳ�Ϊ1 */
    if (gastAtParaList[0].usParaLen != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    ucSrvDomain = gastAtParaList[0].aucPara[0];

    /* ucSrvDomainȡֵ��ΧΪ'0'~'3' */
    if (('0' <= ucSrvDomain) && ('3' >= ucSrvDomain))
    {
        /*���ַ�����ת��Ϊ����,��ΧΪ0~3*/
        ucSrvDomain = gastAtParaList[0].aucPara[0] - '0';
    }
    else
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* �����ֲ���ת��ΪMsClass���ͣ�����3ת��Ϊ0*/
    if (TAF_PH_SERVICE_ANY == ucSrvDomain)
    {
        ucSrvDomain = TAF_PH_SERVICE_CS;
    }

    stMsClass.ucMsClass = ucSrvDomain;
    /* ��ת����Ĳ���ֵд��NV��en_NV_Item_MMA_MsClass��MsClass��Ԫ */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetSDomainPara: Get modem id fail.");
        return AT_ERROR;
    }

    NV_GetLength(en_NV_Item_MMA_MsClass, &ulNvLength);
    if (NV_OK != NV_WriteEx(enModemId,
                            en_NV_Item_MMA_MsClass,
                            &stMsClass,
                            ulNvLength))
    {
       AT_WARN_LOG("At_SetSDomainPara:WARNING:NVIM Write en_NV_Item_MMA_MsClass failed!");
       return AT_DEVICE_OTHER_ERROR;
    }
    return  AT_OK;
}



VOS_UINT32 At_WriteDpaCatToNV(VOS_UINT8 ucDpaRate)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    AT_DPACAT_PARA_STRU                 astDhpaCategory[AT_DPACAT_CATEGORY_TYPE_BUTT] = {
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_6,  PS_FALSE, 0, PS_FALSE},                                                           /* ֧�����ʵȼ�3.6M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_8,  PS_FALSE, 0, PS_FALSE},                                                           /* ֧�����ʵȼ�7.2M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_11, PS_FALSE, 0, PS_FALSE},                                                           /* ֧�����ʵȼ�1.8M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_FALSE, 0, PS_FALSE},                                                          /*  ֧�����ʵȼ�14.4M */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_TRUE,  AT_HSDSCH_PHY_CATEGORY_14, PS_FALSE}};           /*  ֧�����ʵȼ�21M */


    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    if (ucDpaRate >= AT_DPACAT_CATEGORY_TYPE_BUTT)
    {
        AT_WARN_LOG("At_WriteDpaCatToNV: WARNING:Input DPA rate index invalid!");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa, sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("At_WriteDpaCatToNV: en_NV_Item_WAS_RadioAccess_Capa NV Read Fail!");
        return VOS_ERR;
    }

    /* �Ƿ�֧��enHSDSCHSupport�ı�־                */
    stUECapa.enHSDSCHSupport        = astDhpaCategory[ucDpaRate].enHSDSCHSupport;

    /* ֧��HS-DSCH����������ͱ�־                  */
    stUECapa.ucHSDSCHPhyCategory    = astDhpaCategory[ucDpaRate].ucHSDSCHPhyCategory;
    stUECapa.enMacEhsSupport        = astDhpaCategory[ucDpaRate].enMacEhsSupport;
    stUECapa.ucHSDSCHPhyCategoryExt = astDhpaCategory[ucDpaRate].ucHSDSCHPhyCategoryExt;

    /* �Ƿ�֧�� Multi cell support,���֧��MultiCell,Ex2���� */
    stUECapa.enMultiCellSupport     = astDhpaCategory[ucDpaRate].enMultiCellSupport;

    /* ���µ�����д���ڲ���ȫ�ֱ����������µ�NV���� */
    stUECapa.ulHspaStatus           = NV_ITEM_ACTIVE;                /* �����Ϊ������ */

    /* �Ѿ����ú�NV�ṹ���еĶ�Ӧֵ������Щֵд��NV */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa, sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("At_WriteDpaCatToNV: en_NV_Item_WAS_RadioAccess_Capa NV Write Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32   At_SetDpaCat(VOS_UINT8 ucIndex)
{
    /*0     ֧������Ϊ3.6M
     *1     ֧������Ϊ7.2M
     *2     ֧������Ϊ1.8M
     *3     ֧������Ϊ14.4M
     *4     ֧������Ϊ21M
    */
    VOS_UINT8                           ucDpaRate;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������Ϊ1 */
    if (gucAtParaIndex != 1)
    {
        return AT_ERROR;
    }

    /* ��������ֻ��Ϊ1�� */
    if (gastAtParaList[0].usParaLen != 1)
    {
        return AT_ERROR;
    }

    ucDpaRate = gastAtParaList[0].aucPara[0];
    /* ucDpaRateȡֵ��ΧΪ'0'~'4' */
    if (('0' <=ucDpaRate) && ('4' >= ucDpaRate))
    {
        ucDpaRate = gastAtParaList[0].aucPara[0] - '0';
    }
    else
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_ERROR;
    }

    /* ����дNV�ӿں���: At_WriteDpaCatToNV,���ز������ */
    if (VOS_OK == At_WriteDpaCatToNV(ucDpaRate))
    {
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_SetDpaCat:WARNING:WAS_MNTN_SetDpaCat failed!");
        return AT_ERROR;
    }

}
VOS_UINT32 AT_WriteRrcVerToNV(VOS_UINT8 ucSrcWcdmaRRC)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;


    /* ��NV���ж�ȡen_NV_Item_WAS_RadioAccess_Capaֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New,
                         &stUECapa,
                         sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_WriteRrcVerToNV():en_NV_Item_WAS_RadioAccess_Capa_New NV Read Fail!");
        return VOS_ERR;
    }

    switch(ucSrcWcdmaRRC)
    {
        case AT_RRC_VERSION_WCDMA:
            stUECapa.enEDCHSupport    = VOS_FALSE;
            stUECapa.enHSDSCHSupport  = VOS_FALSE;
            break;

        case AT_RRC_VERSION_DPA:
            stUECapa.enEDCHSupport    = VOS_FALSE;
            stUECapa.enHSDSCHSupport  = VOS_TRUE;
            break;

        case AT_RRC_VERSION_DPA_AND_UPA:
            stUECapa.enAsRelIndicator = AT_PTL_VER_ENUM_R6;
            stUECapa.enEDCHSupport    = VOS_TRUE;
            stUECapa.enHSDSCHSupport  = VOS_TRUE;
            break;

        case AT_RRC_VERSION_HSPA_PLUNS:
            stUECapa.enAsRelIndicator = AT_PTL_VER_ENUM_R7;
            stUECapa.enEDCHSupport    = VOS_TRUE;
            stUECapa.enHSDSCHSupport  = VOS_TRUE;
            break;

        default:
            break;
    }

    /* ��Ҫ���õ�ֵд��Balong NV �ṹ�� */
    stUECapa.ulHspaStatus     = NV_ITEM_ACTIVE;


    /* �Ѿ����ú�NV�ṹ���еĶ�Ӧֵ������Щֵд��NV */
    if(NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New,
                         &stUECapa,
                         sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_WriteRrcVerToNV():en_NV_Item_WAS_RadioAccess_Capa_New NV Write Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32   At_SetHspaSpt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_DPAUPA_ERROR;
    }

    /* ��������ֻ��Ϊ1�� */
    if (gastAtParaList[0].usParaLen != 1)
    {
        return AT_DPAUPA_ERROR;
    }

    ucRRCVer = gastAtParaList[0].aucPara[0];
    /* ucRRCVerȡֵ��ΧΪ'0'~'2' */
    if (('0' <=ucRRCVer) && ('2' >= ucRRCVer))
    {
        ucRRCVer = gastAtParaList[0].aucPara[0] - '0';
    }
    else
    {
        return AT_DPAUPA_ERROR;
    }

    /* ����Ƿ������ݱ���,δ���ʱ���س�����Ϣ:ErrCode:0 */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_DATA_UNLOCK_ERROR;
    }

    /* ����дNV�ӿں���: AT_WriteRrcVerToNV,���ز������ */
    if (VOS_OK == AT_WriteRrcVerToNV(ucRRCVer))
    {
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_SetHspaSpt:WARNING:WAS_MNTN_SetHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }

}


VOS_UINT32  At_SetDataLock(VOS_UINT8 ucIndex )
{
    DRV_AGENT_DATALOCK_SET_REQ_STRU     stDatalockInfo;

    /* ���������޲��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    /* <unlock_code>����Ϊ����Ϊ8�������ַ��� */
    if ( TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX != gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    if (AT_FAILURE == At_CheckNumString(gastAtParaList[0].aucPara,
                                        TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX))
    {
        return AT_ERROR;
    }

    if (VOS_TRUE == g_bAtDataLocked)
    {
        /* �����û������� */
        stDatalockInfo.aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX] = '\0';
        PS_MEM_CPY(stDatalockInfo.aucPwd, gastAtParaList[0].aucPara, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

        /* ����Ϣ�� C �� ��ȡ DATALOCK У����Ϣ */
        if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                  gastAtClientTab[ucIndex].opId,
                                                  DRV_AGENT_DATALOCK_SET_REQ,
                                                  &stDatalockInfo,
                                                  sizeof(stDatalockInfo),
                                                  I0_WUEPS_PID_DRV_AGENT))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DATALOCK_SET;           /*���õ�ǰ����ģʽ */
            return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
        }
        else
        {
            return AT_ERROR;
        }
    }

    return AT_OK;

}

#if ( FEATURE_ON == FEATURE_LTE )
/* ����NV�ָ� */
VOS_UINT32  At_SetInfoRRS(VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������������ */
    if (gucAtParaIndex != 0)
    {
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_INFORRS_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INFORRS_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}
#endif

VOS_UINT32  At_SetInfoRBU(VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������������ */
    if (gucAtParaIndex != 0)
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_INFORBU_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_INFORBU_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-3, End */

}

VOS_UINT32 At_SetGPIOPL(VOS_UINT8 ucIndex)
{
    DRV_AGENT_GPIOPL_SET_REQ_STRU       stGpioplSet;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    /* �����������GPIOPL����20���ֽ�,��:BCD�� > 20*2����ֱ�ӷ��ش��� */
    if (gastAtParaList[0].usParaLen > (AT_GPIOPL_MAX_LEN*2))
    {
        return AT_ERROR;
    }

    /*���GPIOֵ�Ƿ�Ϊ16�����ַ���,������ֱ�ӷ��ش���;����ת��Ϊ16��������*/
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[0].aucPara,
                                           &gastAtParaList[0].usParaLen))
    {
        return AT_ERROR;
    }

    PS_MEM_SET(stGpioplSet.aucGpiopl, 0, DRVAGENT_GPIOPL_MAX_LEN);

    PS_MEM_CPY(stGpioplSet.aucGpiopl, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    /*����AT_FillAndSndAppReqMsg����Ϣ��C��I0_WUEPS_PID_DRV_AGENT*/
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg( gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_GPIOPL_SET_REQ,
                                              &stGpioplSet,
                                              sizeof(stGpioplSet),
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GPIOPL_SET;       /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                      /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32  At_ConvertSDErrToAtErrCode(VOS_UINT32 ulSDOprtErr)
{
    VOS_UINT32 ulAtSDErrCode;

    switch (ulSDOprtErr)
    {
        case AT_SD_ERR_CRAD_NOT_EXIST:
            ulAtSDErrCode = AT_SD_CARD_NOT_EXIST;
            break;

        case AT_SD_ERR_INIT_FAILED:
            ulAtSDErrCode = AT_SD_CARD_INIT_FAILED;
            break;

        case AT_SD_ERR_OPRT_NOT_ALLOWED:
            ulAtSDErrCode = AT_SD_CARD_OPRT_NOT_ALLOWED;
            break;

        case AT_SD_ERR_ADDR_ERR :
            ulAtSDErrCode = AT_SD_CARD_ADDR_ERR;
            break;

        default:
            ulAtSDErrCode = AT_SD_CARD_OTHER_ERR;
            break;

    }

    return ulAtSDErrCode;
}

VOS_BOOL At_IsArrayContentValueEquToPara(
    VOS_UINT8                           ucValue,
    VOS_UINT32                          ulArrLen,
    VOS_UINT8                           aucContent[]
 )
{
    VOS_UINT32                          i;

    for (i = 0; i < ulArrLen; i++)
    {
        if(ucValue != aucContent[i])
        {
            break;
        }
    }
    if (i != ulArrLen)
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }

}


VOS_UINT32 At_SDOprtRead(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulOprtErr;
    VOS_UINT32                          ulOprtRslt;
    VOS_UINT32                          ulAddr;
    VOS_UINT8                           *pucSdData;
    VOS_UINT16                          usLength;
    VOS_BOOL                            bSameContent;
    VOS_UINT8                           ucPrintData;

    if (2 != gucAtParaIndex)
    {
        return AT_SD_CARD_OTHER_ERR;
    }

    /* �������ڱ���ָ����ַ��ʼ��512���ֽڵ��ڴ�*/
    pucSdData = (VOS_UINT8* )PS_MEM_ALLOC(WUEPS_PID_AT, AT_SD_DATA_UNIT_LEN);

    if (VOS_NULL_PTR == pucSdData)
    {
        AT_ERR_LOG("At_SD_Read: Fail to Alloc memory.");
        return AT_SD_CARD_OTHER_ERR;
    }

    ulAddr = gastAtParaList[1].ulParaValue;

    ulOprtRslt = DRV_SDMMC_AT_PROCESS(SD_MMC_OPRT_READ, ulAddr, 0, pucSdData, &ulOprtErr);

    ucPrintData = 0;

    if (VOS_OK == ulOprtRslt)
    {
        ulOprtErr = AT_DEVICE_ERROR_BEGIN;

        /* ָ����ַ��ʼ��512���ֽ������Ƿ���ͬ */
        bSameContent = At_IsArrayContentValueEquToPara(pucSdData[0],AT_SD_DATA_UNIT_LEN,pucSdData);

        if (VOS_TRUE == bSameContent)
        {
            switch(pucSdData[0])
            {
                case 0x00:
                    ucPrintData = 0;
                    break;
                case 0x55:
                    ucPrintData = 1;
                    break;
                case 0xAA:
                    ucPrintData = 2;
                    break;
                case 0xFF:
                    ucPrintData = 3;
                    break;
                 default:
                    ulOprtErr = AT_SD_CARD_OTHER_ERR;
                    break;

            }
        }
        else
        {
            ulOprtErr = AT_SD_CARD_OTHER_ERR;
        }

        PS_MEM_FREE(WUEPS_PID_AT, pucSdData);

        if  (AT_DEVICE_ERROR_BEGIN == ulOprtErr)
        {
            /* �������أ���ӡ��Ӧ����ʾ��ʽ */
            usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR*)pgucAtSndCodeAddr,
                                              "%s:%d",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              ucPrintData);

            gstAtSendData.usBufLen = usLength;
            return AT_OK;
        }
        else
        {
            /* ת��Ϊ��Ӧ�������ӡ */
            return At_ConvertSDErrToAtErrCode(ulOprtErr);
        }

    }
    else
    {
        PS_MEM_FREE(WUEPS_PID_AT,pucSdData);
        return At_ConvertSDErrToAtErrCode(ulOprtErr);
    }

}

VOS_UINT32 At_SDOprtWrtEraseFmt(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulOprtErr;
    VOS_UINT32                          ulOprtRslt;
    VOS_UINT32                          ulAddr;
    VOS_UINT32                          ulData;

    switch (gastAtParaList[0].ulParaValue)
    {
        case AT_SD_OPRT_FORMAT:
            /* ��SD�����и�ʽ������ */
            ulOprtRslt = DRV_SDMMC_AT_PROCESS(SD_MMC_OPRT_FORMAT,
                                              0, 0, VOS_NULL_PTR, &ulOprtErr);
            break;

        case AT_SD_OPRT_ERASE:
            /* ֻ��һ������ʱ����������SD��; �������ʱ��ɾ��ָ����ַ��SD������  */
            if (1 == gucAtParaIndex)
            {
                ulOprtRslt = DRV_SDMMC_AT_PROCESS(SD_MMC_OPRT_ERASE_ALL,
                                                  0, 0, VOS_NULL_PTR, &ulOprtErr);
            }
            else
            {
                ulAddr     = gastAtParaList[1].ulParaValue;
                ulOprtRslt = DRV_SDMMC_AT_PROCESS(SD_MMC_OPRT_ERASE_SPEC_ADDR,
                                                  ulAddr, 0, VOS_NULL_PTR, &ulOprtErr);
            }
            break;

        case AT_SD_OPRT_WRITE:
            /* ��SD����ָ����ַ����д���� */
            if (3 == gucAtParaIndex)
            {
                ulAddr     = gastAtParaList[1].ulParaValue;
                ulData     = gastAtParaList[2].ulParaValue;
                ulOprtRslt = DRV_SDMMC_AT_PROCESS(SD_MMC_OPRT_WRITE,
                                                  ulAddr, ulData, VOS_NULL_PTR, &ulOprtErr);
            }
            else
            {
                return AT_SD_CARD_OTHER_ERR;
            }
            break;

        default:
            return AT_SD_CARD_OPRT_NOT_ALLOWED;
    }

    if (VOS_OK != ulOprtRslt)
    {
       return At_ConvertSDErrToAtErrCode(ulOprtErr);
    }

    return AT_OK;
}
VOS_UINT32  At_SetSD(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulCurrentOprtStaus;
    VOS_INT32                           lCurrentSDStaus;

    /* ���������޲���ʱ��AT^SDΪ��ѯSD����λ״̬ */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        lCurrentSDStaus = DRV_SDMMC_GET_STATUS();
        if (AT_SD_STATUS_EXIST == lCurrentSDStaus)
        {
            return AT_OK;
        }
        else
        {
            return AT_ERROR;
        }
    }

    /* �������� */
    if (gucAtParaIndex > 3)
    {
        return AT_SD_CARD_OTHER_ERR;
    }

    /* SD������Ϊ���з�ʽ����ѯ��ǰ�Ƿ��н��еĲ�������ȷ���Ƿ�ɽ����µ����ò��� */
    ulCurrentOprtStaus = DRV_SDMMC_GET_OPRT_STATUS();

    /* �ϴεĲ�����δ���� ���������²��� */
    if (AT_SD_OPRT_RSLT_NOT_FINISH == ulCurrentOprtStaus)
    {
        return AT_SD_CARD_OTHER_ERR;
    }

    /*  ��ǰ��ִ��״̬���ɽ����µĶ���д����ʽ������ */
    if (AT_SD_OPRT_READ == gastAtParaList[0].ulParaValue)
    {
        return At_SDOprtRead(ucIndex);
    }
    else
    {
        return At_SDOprtWrtEraseFmt(ucIndex);
    }


}


 VOS_UINT32 At_CheckRxdivOrRxpriParaIfSupported(
     VOS_UINT16                         *pusSetBands,
     VOS_UINT16                         usBands
 )
 {
     VOS_UINT32                         ulResult;
     VOS_UINT32                         i;
     VOS_UINT32                         ulSetLowBands;
     VOS_UINT32                         ulSetHighBands;

     /* ���û����õĽ��շּ�����������ת�������� */
     ulResult = At_GetUserSetRxDivOrRxPriParaNum(&ulSetLowBands, &ulSetHighBands);
     if (AT_OK != ulResult)
     {
         return ulResult;
     }

     /* ������ó�0X3FFFFFFF����Ϊ�Ǵ�����֧�ֵķּ�������;
        ���򣬰��û����õĲ���ת�ɺ����������RX�ּ���������Ӧ�ĸ�ʽ */
     if ((TAF_PH_BAND_ANY == ulSetLowBands) && (0 == ulSetHighBands))
     {
         *pusSetBands = usBands;
     }
     else
     {
         ulResult = At_CovertUserSetRxDivOrRxPriParaToMsInternal(ulSetLowBands,
                                           ulSetHighBands, pusSetBands);
         if (AT_OK != ulResult)
         {
             return ulResult;
         }
     }

     /* ����֧�ֵ�RX DIV��ʽ����:
          2100M/ bit1  1900M/bit2  1800M/bit3  1700M/bit4  1600M/bit5
          1500M/bit6   900M/bit7   850M/bit8   800M/bit9   450M/bit10
       ����򿪵��ǵ�����֧�ֵķּ������������ش��� */
     for (i = 0; i < 16; i++)
     {
         if ((0 == ((usBands >> i) & 0x0001))
          && (0x0001 == ((*pusSetBands >> i) & 0x0001)))
         {
              return AT_CME_RX_DIV_NOT_SUPPORTED;
         }
     }

     return AT_OK;

 }


VOS_UINT32 At_SetRxDiv(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    AT_DRV_AGENT_RXDIV_SET_STRU         stRxdivSet;
    VOS_UINT32                          ulResult;

    ulResult = At_CheckRxDivOrRxPriCmdPara();
    if (AT_OK != ulResult)
    {
        return ulResult;
    }

    /* ���û����õĽ��շּ�����������ת�������� */
    ulResult = At_GetUserSetRxDivOrRxPriParaNum(&stRxdivSet.ulSetLowBands,
                                                &stRxdivSet.ulSetHighBands);
    if (AT_OK != ulResult)
    {
        return ulResult;
    }

    stRxdivSet.ucRxOnOff = g_stAtDevCmdCtrl.ucRxOnOff;
    stRxdivSet.usDspBand = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;

    /* ������ϢDRV_AGENT_HARDWARE_QRY��AT AGENT����������Ϣ�޲����ṹ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   DRV_AGENT_RXDIV_SET_REQ,
                                   (VOS_VOID*)&stRxdivSet,
                                   sizeof(stRxdivSet),
                                   I0_WUEPS_PID_DRV_AGENT);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_RXDIV_SET_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_UINT32  AT_ProcUus1WithParm(
    VOS_UINT8                           ucIndex,
    MN_CALL_UUS1_PARAM_STRU            *pstUus1Group
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgNum;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;

    /* ȥ��<n>��<m>��,ʵ�ʵ���Ϣ���� */
    ulMsgNum   = gucAtParaIndex;


    if(0 == gastAtParaList[2].usParaLen)
    {
        pstUus1Group->ulActNum = 0;
    }
    else
    {
        /* ����message */
        for (i = 2 ; (i < ulMsgNum && i < (AT_MAX_PARA_NUMBER-1)); i++)
        {

            /* ����Ҫת��,���ڸ���������ö�β���,AT��ʽ�н���ǰ4����������ת��,
            ����Ĳ���δ����ת��,�����Ҫ�������е�ֵ������ת��*/
            if (AT_SUCCESS != At_Auc2ul(gastAtParaList[i].aucPara,
                                        gastAtParaList[i].usParaLen,
                                       &gastAtParaList[i].ulParaValue))
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            pstUus1Group->stUus1Info[pstUus1Group->ulActNum].enMsgType = gastAtParaList[i].ulParaValue;
            i++;

            /*<UUIE>������,������ȥ���� */
            if ( 0 == gastAtParaList[i].usParaLen )
            {
                pstUus1Group->enSetType[pstUus1Group->ulActNum] = MN_CALL_SET_UUS1_DEACT;
            }
            else
            {
                pstUus1Group->enSetType[pstUus1Group->ulActNum] = MN_CALL_SET_UUS1_ACT;
                /* �轫ASCIIת��ΪHEX */
                if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[i].aucPara,
                                                      &gastAtParaList[i].usParaLen))
                {
                    return AT_CME_INCORRECT_PARAMETERS;
                }

                PS_MEM_CPY(pstUus1Group->stUus1Info[pstUus1Group->ulActNum].aucUuie,
                           gastAtParaList[i].aucPara,
                           gastAtParaList[i].usParaLen);
            }

            ulRet = MN_CALL_CheckUus1ParmValid(pstUus1Group->enSetType[pstUus1Group->ulActNum],
                                              &(pstUus1Group->stUus1Info[pstUus1Group->ulActNum]));
            if ( MN_ERR_NO_ERROR != ulRet )
            {
                return AT_CME_INCORRECT_PARAMETERS;
            }

            pstUus1Group->ulActNum++;

            /* ���δЯ��UUIE,��Ĭ�ϱ�ʾ���������ĺ������ */
            if (MN_CALL_SET_UUS1_DEACT == pstUus1Group->enSetType[pstUus1Group->ulActNum])
            {
                break;
            }
        }
    }
    /* 1.��Ҫ���õĸ���Uus1Info�����趨��Ȼ��ͨ��MN_CALL_APP_SET_UUSINFO��Ϣ�������ṹ
         MN_CALL_UUS1_PARAM_STRU֪ͨCS���в�������*/
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_SET_UUSINFO_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   (MN_CALL_APP_REQ_PARM_UNION*)pstUus1Group);
    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_SET_UUSINFO_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


VOS_UINT32 At_SetCuus1Para(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_UUS1_PARAM_STRU             stUus1Group;

    /*************************************************************
    27007�и������ʽ,��������Բ�Я���κβ���,�����Я������ֱ�ӷ���OK
    + CUUS1 =[<n>[,<m>[,<message>[,<UUIE> [,<message>[,<UUIE>[,...]]]]]]]
    ****************************************************************/

    /* ��Я������ֱ�ӷ���OK */
    if ( 0 == gucAtParaIndex )
    {
        return AT_OK;
    }

    PS_MEM_SET(&stUus1Group,0x00,sizeof(stUus1Group));

    /* ����<n> */
    if(0 != gastAtParaList[0].usParaLen)
    {
        stUus1Group.enCuus1IFlg = (MN_CALL_CUUS1_FLG_ENUM_U32)gastAtParaList[0].ulParaValue;
    }
    else
    {
        /* <n>������ͬʱ����������Ϊ0����ERROR */
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<m> */
    if(0 != gastAtParaList[1].usParaLen)
    {
        stUus1Group.enCuus1UFlg = (MN_CALL_CUUS1_FLG_ENUM_U32)gastAtParaList[1].ulParaValue;
    }

    /* ����message */
    /* ֻ��n��m����ʱ��ҲҪ��MN����Ϣ */
    ulRet = AT_ProcUus1WithParm(ucIndex, &stUus1Group);


    return ulRet;

}

VOS_UINT32  At_SetGlastErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    TAF_PS_CAUSE_ENUM_UINT32            enPsCause;

    usLength                            = 0;

    /* ��鲦�Ŵ������Ƿ�ʹ��*/
    if (PPP_DIAL_ERR_CODE_DISABLE == gucPppDialErrCodeRpt)
    {
       return AT_ERROR;
    }

    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* û�в���*/
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ֵ����*/
    if (1 != gastAtParaList[0].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    gulErrType = gastAtParaList[0].ulParaValue;

    /* ��ȡ������*/
    enPsCause = AT_PS_GetPsCallErrCause(ucIndex);
    if (TAF_PS_CAUSE_SUCCESS == enPsCause)
    {
        return AT_ERROR;
    }

    /* ���������ϱ�����̨*/
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %d,%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       gulErrType,
                                       AT_Get3gppSmCauseByPsCause(enPsCause));

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
VOS_UINT32 AT_SetMDatePara(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRet;
    AT_DATE_STRU                        stDate;
    TAF_AT_NVIM_MANUFACTURE_DATE_STRU   stManufactrueDate;

    if (gucAtParaIndex != 1)
    {
        AT_NORM_LOG("AT_SetMDatePara: the number of parameters is error.");
        return AT_ERROR;
    }

    /* �������1:���ڸ�ʽ��飻*/
    ulRet = AT_CheckDateFormat(gastAtParaList[0].aucPara,
                               gastAtParaList[0].usParaLen);
    if (AT_OK != ulRet)
    {
        AT_NORM_LOG("AT_SetMDatePara: the format of parameters is error.");
        return AT_ERROR;
    }

    /* �������2:��ȡ�������ڲ�����������Ч�Լ�飻*/
    ulRet = AT_GetDate(gastAtParaList[0].aucPara,
                       gastAtParaList[0].usParaLen,
                       &stDate);
    if (AT_OK != ulRet)
    {
        AT_NORM_LOG("AT_SetMDatePara: Fail to get the date.");
        return AT_ERROR;
    }

    ulRet = AT_CheckDate(&stDate);
    if (AT_OK != ulRet)
    {
        AT_NORM_LOG("AT_SetMDatePara: the value of parameters is error.");
        return AT_ERROR;
    }

    /* д���ڲ�����NV */
    PS_MEM_CPY(stManufactrueDate.aucMDate, gastAtParaList[0].aucPara, (AT_MDATE_STRING_LENGTH - 1));
    stManufactrueDate.aucMDate[AT_MDATE_STRING_LENGTH - 1] = '\0';
    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_AT_MANUFACTURE_DATE,
                     stManufactrueDate.aucMDate,
                     AT_MDATE_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_SetMDatePara: Fail to write nv.");
        return AT_ERROR;
    }

    return AT_OK;
}
VOS_UINT32 AT_SetFacInfoPara(
    VOS_UINT8                          ucIndex
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucFacInfo = TAF_NULL_PTR;
    VOS_UINT32                          ulOffSet;

    if ((gucAtParaIndex != 2) || ((0 == gastAtParaList[1].usParaLen)))
    {
        AT_WARN_LOG("AT_SetFacInfoPara: the number of parameters is error.");
        return AT_ERROR;
    }

    /* ���ȳ���������Ϣ��Ч�ֶγ�����������ʧ�� */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        if (AT_FACINFO_INFO1_LENGTH != gastAtParaList[1].usParaLen)
        {
            AT_NORM_LOG("AT_SetFacInfoPara: Length of info1 is failure.");
            return AT_ERROR;
        }

        if (AT_FAILURE == At_CheckNumString(gastAtParaList[1].aucPara, AT_FACINFO_INFO1_LENGTH))
        {
            return AT_ERROR;
        }
    }
    else
    {
        if (AT_FACINFO_INFO2_LENGTH != gastAtParaList[1].usParaLen)
        {
            AT_NORM_LOG("AT_SetFacInfoPara: Length of info2 is failure.");
            return AT_ERROR;
        }

        if (AT_FAILURE == At_CheckNumString(gastAtParaList[1].aucPara, AT_FACINFO_INFO2_LENGTH))
        {
            return AT_ERROR;
        }
    }

    /* ��ȡNV���Ѿ��洢��������Ϣ */
    pucFacInfo = (TAF_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FACINFO_STRING_LENGTH);
    if (TAF_NULL_PTR == pucFacInfo)
    {
        AT_WARN_LOG("AT_SetFacInfoPara: fail to alloc memory.");
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_FACTORY_INFO,
                    pucFacInfo,
                    AT_FACINFO_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_SetFacInfoPara: fail to read NVIM . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    /*
       ��װ��д��NV��en_NV_Item_AT_FACTORY_INFO�ľֲ�����:
       �����û��������<INDEX>ˢ��������Ϣ,
       <INDEX>Ϊ0��ˢ��ǰ129�ֽڣ����е�129�ֽ�Ϊ��������
       <INDEX>Ϊ1��ˢ�º�129�ֽڣ����е�129�ֽ�Ϊ��������
    */
    ulOffSet = (AT_FACINFO_INFO1_LENGTH + 1) * gastAtParaList[0].ulParaValue;
    if ((ulOffSet + gastAtParaList[1].usParaLen) > ((AT_FACINFO_INFO1_LENGTH + 1) + AT_FACINFO_INFO2_LENGTH))
    {
        AT_WARN_LOG("AT_SetFacInfoPara: offset is error. ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    *((pucFacInfo + ulOffSet) + gastAtParaList[1].usParaLen) = '\0';

    PS_MEM_CPY((pucFacInfo + ulOffSet),
                gastAtParaList[1].aucPara,
                gastAtParaList[1].usParaLen);

    /* ˢ���û��޸ĺ��������Ϣ��NV��en_NV_Item_AT_FACTORY_INFO */
    ulRet = NV_WriteEx(MODEM_ID_0, en_NV_Item_AT_FACTORY_INFO,
                     pucFacInfo,
                     AT_FACINFO_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_SetFacInfoPara: fail to write NVIM . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
    return AT_OK;
}
VOS_UINT32 At_SetCallSrvPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              stCustSrv;

    /* ����״̬��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ������������ */
    if (gucAtParaIndex != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ����Ƿ������ݱ���,δ���ʱ���س�����Ϣ */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_DATA_UNLOCK_ERROR;
    }

    stCustSrv.ulCustomizeService = gastAtParaList[0].ulParaValue;
    stCustSrv.ulStatus           = NV_ITEM_ACTIVE;          /*NV������Ϊ����*/

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_CustomizeService, &stCustSrv, sizeof(stCustSrv)))
    {
        AT_WARN_LOG("At_SetCallSrvPara():en_NV_Item_CustomizeService NV Write Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }

    return AT_OK;

}

/* Modify by z60575 for multi_ssid, 2012-9-5 begin */
/*****************************************************************************
 �� �� ��  : At_WriteWifiNVToDefault
 ��������  : ����WIFI������ΪĬ��ֵ
 �������  : enCustomizeItem - 0:���ö�����Ĭ��ֵΪ�����������ĵ��е�ֵ
                               1:���ö������Ĭ��ֵΪ�����Զ����Ĭ��ֵ
             Ŀǰ���ڸö������Ĭ��ֵ�ڿ����������ĵ��ж���ֵ�͵����Զ����ֵ��ͬ,
             ����α���δ�ã���������չʹ��
 �������  : ��
 �� �� ֵ  : VOS_OK  - ִ�гɹ�
             VOS_ERR - ִ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��23��
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��9��17��
    �޸�����   : MULTI_SSID�޸�
*****************************************************************************/
VOS_UINT32 At_WriteWifiNVToDefault(
    AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
)
{
    TAF_AT_MULTI_WIFI_SEC_STRU              stWifiKey;
    TAF_AT_MULTI_WIFI_SSID_STRU             stWifiSsid;

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return VOS_OK;
    }

    PS_MEM_SET(&stWifiKey, 0, sizeof(stWifiKey));
    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    /* ��ȡWIFI KEY��Ӧ��NV�� */
    if (NV_OK!= NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("At_WriteCustomizeSrvNVToDefault:READ NV ERROR");
        return VOS_ERR;
    }

    /* ����WIKEYΪĬ��ֵ */
    PS_MEM_SET(stWifiKey.aucWifiWpapsk, 0x00, sizeof(stWifiKey.aucWifiWpapsk));

    /* ����WIWEPΪĬ��ֵ */
    PS_MEM_SET(stWifiKey.aucWifiWepKey1, 0x00, sizeof(stWifiKey.aucWifiWepKey1));
    PS_MEM_SET(stWifiKey.aucWifiWepKey2, 0x00, sizeof(stWifiKey.aucWifiWepKey2));
    PS_MEM_SET(stWifiKey.aucWifiWepKey3, 0x00, sizeof(stWifiKey.aucWifiWepKey3));
    PS_MEM_SET(stWifiKey.aucWifiWepKey4, 0x00, sizeof(stWifiKey.aucWifiWepKey4));

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("At_WriteCustomizeSrvNVToDefault:WRITE NV ERROR");
        return VOS_ERR;
    }

    /*��ȡSSID��Ӧ��NV��*/
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("At_WriteCustomizeSrvNVToDefault:READ NV ERROR");
        return VOS_ERR;
    }

    /* ����SSIDΪĬ��ֵ */
    PS_MEM_SET(stWifiSsid.aucWifiSsid, 0x00, sizeof(stWifiSsid.aucWifiSsid));

    /*д��WIFI SSID��Ӧ��NV��*/
    if (VOS_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("At_WriteCustomizeSrvNVToDefault:WRITE NV ERROR");
        return VOS_ERR;
    }

    return VOS_OK;
}
/* Modify by z60575 for multi_ssid, 2012-9-5 end */

VOS_UINT32 At_WriteSimLockNVToDefault(
    AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;
    VOS_UINT32                          i;

    VOS_UINT8                           aucRange[TAF_PH_SIMLOCK_PLMN_STR_LEN]
                                            = {AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                               AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL};


    /* �ö������ڿ����������ĵ���Ĭ��ֵ�͵����Զ����Ĭ��ֵ��ͬ
       en_NV_Item_CustomizeSimLockPlmnInfo��ulStatus:Ĭ��δ����;
       mnc_num:Ĭ��Ϊ2; range_begin��rang_endĬ��ȫΪ0xAA */
    stSimLockPlmnInfo.ulStatus = NV_ITEM_DEACTIVE;
    for (i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++)
    {
        stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum = AT_SIM_LOCK_MNC_NUM_DEFAULT_VAL;
        PS_MEM_CPY(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                   aucRange, sizeof(aucRange));
        PS_MEM_CPY(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                   aucRange, sizeof(aucRange));
    }

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockPlmnInfo,
                          &stSimLockPlmnInfo, sizeof(stSimLockPlmnInfo)))
    {
        AT_WARN_LOG("At_WriteSimLockNVToDefault():en_NV_Item_CustomizeSimLockPlmnInfo NV Write Fail!");
        return VOS_ERR;
    }

    /* �ö������ڿ����������ĵ���Ĭ��ֵ�͵����Զ����Ĭ��ֵ��ͬ,
       en_NV_Item_CardlockStatus��ulStatus:Ĭ��Ϊδ����; CardlockStatus:Ĭ��ֵΪ2;
       RemainUnlockTimes:Ĭ��ֵΪ0 */
    stCardLockStatus.ulStatus            = NV_ITEM_DEACTIVE;
    stCardLockStatus.enCardlockStatus    = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
    stCardLockStatus.ulRemainUnlockTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_CardlockStatus, &stCardLockStatus,
                          sizeof(stCardLockStatus)))

    {
        AT_WARN_LOG("At_WriteSimLockNVToDefault():en_NV_Item_CardlockStatus NV Write Fail!");
        return VOS_ERR;
    }


    /*��C�˷�����Ϣ����simlockNV*/
    if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(0,
                                              0,
                                              DRV_AGENT_SIMLOCK_NV_SET_REQ,
                                              &stCardLockStatus,
                                              sizeof(stCardLockStatus),
                                              I0_WUEPS_PID_DRV_AGENT))
    {

        AT_WARN_LOG("At_WriteSimLockNVToDefault():DRV_AGENT_SIMLOCK_NV_SET_REQ NV Write Fail!");
        return VOS_ERR;
    }


    /* �ö������ڿ����������ĵ���Ĭ��ֵ�͵����Զ����Ĭ��ֵ��ͬ,
       en_NV_Item_CustomizeSimLockMaxTimes��ulStatus:Ĭ��Ϊδ���
       LockMaxTimes:Ĭ������������Ϊ10�� */
    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockMaxTimes, &stSimLockMaxTimes,
                          sizeof(stSimLockMaxTimes)))
    {
        AT_WARN_LOG("At_WriteSimLockNVToDefault():en_NV_Item_CustomizeSimLockMaxTimes NV Write Fail!");
        return VOS_ERR;
    }

    return VOS_OK;

}



VOS_UINT32 At_WriteCustomizeSrvNVToDefault(
    AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              stCustSrv;

    /* �ö������ڿ����������ĵ���Ĭ��ֵ�뵥���Զ����Ĭ��ֵ��ͬ,
       ulStatus:Ĭ��Ϊδ����;ulCustomizeService:Ĭ�Ͻ�ֹ��ͨ����ҵ�� */
    stCustSrv.ulCustomizeService = VOS_FALSE;
    stCustSrv.ulStatus           = NV_ITEM_DEACTIVE;

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_CustomizeService, &stCustSrv, sizeof(stCustSrv)))
    {
        AT_WARN_LOG("At_WriteCustomizeSrvNVToDefault():en_NV_Item_CustomizeService NV Write Fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 At_WriteGprsActTimerNVToDefault(
    AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
)
{
    VOS_UINT32                          ulGprsActiveTimerLen;

    /* �����������ĵ���Ĭ��ֵ�͵����Զ����Ĭ��ֵ��Ϊ20�� */
    ulGprsActiveTimerLen = AT_GPRS_ACT_TIMER_LEN_DEFAULT_VAL;
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                          &ulGprsActiveTimerLen, sizeof(ulGprsActiveTimerLen)))
    {
        AT_WARN_LOG("At_WriteGprsActTimerNVToDefault():en_NV_Item_GPRS_ActiveTimerLength NV Write Fail!");
        return VOS_ERR;
    }

    return VOS_OK;

}
VOS_UINT32 At_SetCustomizeItemToDefaultVal(
    AT_CUSTOMIZE_ITEM_DFLT_ENUM_UINT8   enCustomizeItem
)
{

    /* ����WIFI�������Ӧ��en_NV_Item_WIFI_KEY��
       en_NV_Item_WIFI_STATUS_SSID 2��NV�� */
    if (VOS_OK != At_WriteWifiNVToDefault(enCustomizeItem))
    {
        return VOS_ERR;
    }

    /* ����SimLock�������Ӧ��en_NV_Item_CustomizeSimLockPlmnInfo��
       en_NV_Item_CardlockStatus��en_NV_Item_CustomizeSimLockMaxTimes 3��NV�� */
    if (VOS_OK != At_WriteSimLockNVToDefault(enCustomizeItem))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 At_SetCsdfltPara(VOS_UINT8 ucIndex)
{
    /* ����״̬��� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������������ */
    if (gucAtParaIndex != 0)
    {
        return AT_ERROR;
    }

    /* ����Ƿ������ݱ���,δ���ʱ���س�����Ϣ */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_ERROR;
    }

    /* Ĭ��ֵΪ0 */
    if (VOS_OK != At_SetCustomizeItemToDefaultVal(AT_CUSTOMIZE_ITEM_DEFAULT_VALUE_FROM_CFGFILE))
    {
        return AT_ERROR;
    }

    /*  �ָ��������ú�֪ͨӦ�ñ���wifi������Ϣ */
    if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        AT_PhSendRestoreFactParmNoReset();
    }

    return AT_OK;

}
VOS_UINT32  At_GetParaCnt(
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_UINT16                          i;
    VOS_UINT32                          ulCnt;

    ulCnt = 0;
    for ( i = 0; i < usLen ; i++ )
    {
        if (',' == pucData[i])
        {
            ++ ulCnt;
        }
    }

    /*�������� = ','����+1*/
    return (ulCnt + 1);
}
VOS_UINT32 At_AsciiNum2SimLockImsiStr (
    VOS_UINT8                           *pucDst,
    VOS_UINT8                           *pucSrc,
    VOS_UINT16                          usSrcLen
)
{
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucBcdCode;

    /* �ַ����������Ϊ16 */
    if (usSrcLen > (TAF_PH_SIMLOCK_PLMN_STR_LEN * 2))
    {
        return AT_FAILURE;
    }

    for (usChkLen = 0; usChkLen < usSrcLen; usChkLen++)
    {
        /* the number is 0-9 */
        if ((pucSrc[usChkLen] >= 0x30) && (pucSrc[usChkLen] <= 0x39))
        {
            ucBcdCode = pucSrc[usChkLen] - 0x30;
        }
        else
        {
            return AT_FAILURE;
        }

        ucTmp = usChkLen % 2;   /* �жϸߵ�λ */
        if (0 == ucTmp)
        {
            pucDst[usChkLen/2] = (VOS_UINT8)((ucBcdCode << 4) & 0xF0); /* ��λ */
        }
        else
        {
            pucDst[usChkLen/2] |= (VOS_UINT8)(ucBcdCode);   /* ��λ */
        }
    }

    if(1 == (usSrcLen % 2))
    {
        pucDst[usSrcLen/2] |= 0x0F; /* ��λ */
    }

    return AT_SUCCESS;
}


VOS_UINT32 At_CovertAtParaToSimlockPlmnInfo(
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist,
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  *pstSimLockPlmnInfo
)
{
    VOS_UINT8                           ucMncNum;
    VOS_UINT8                           aucImsiStr[TAF_PH_SIMLOCK_PLMN_STR_LEN];
    VOS_UINT8                           *pucPlmnRange;
    VOS_UINT32                          i;
    VOS_UINT32                          ulPlmnParaIdx;
    VOS_UINT32                          ulImsiStrLen;

    ulPlmnParaIdx = 0;
    ucMncNum      = 2;


    PS_MEM_SET(aucImsiStr, 0x00, sizeof(aucImsiStr));

    /* Plmn�Ŷ���Ϣ���ӵ�2��������ʼ��ÿ3��Ϊһ�飬��Ӧ(MNClen,PlmnRangeBegin,PlmnRangeEnd) */
    for (i = 1; i < ulParaCnt; i++)
    {
        /* ��Plmninfo����index��3n+1ʱ,��ӦMNC�ĳ��� */
        if (1 == (i % 3))
        {
            if (1 != pstParalist[i].usParaLen)
            {
                return AT_SIMLOCK_PLMN_MNC_LEN_ERR;
            }
            else if (('2' != pstParalist[i].aucPara[0])
                  && ('3' != pstParalist[i].aucPara[0]))
            {
                return AT_SIMLOCK_PLMN_MNC_LEN_ERR;
            }
            else
            {
                ucMncNum = pstParalist[i].aucPara[0] - '0';
                pstSimLockPlmnInfo->astSimLockPlmnRange[ulPlmnParaIdx].ucMncNum = ucMncNum;
            }

        }
        else if (2 == (i % 3))
        {
            /* ��Plmninfo����index��3n+2 ʱ,��ӦPlmnRangeBegin */
            if (AT_FAILURE == At_AsciiNum2SimLockImsiStr(aucImsiStr, pstParalist[i].aucPara,pstParalist[i].usParaLen))
            {
                return AT_ERROR;
            }
            else
            {
                ulImsiStrLen = (pstParalist[i].usParaLen + 1) / 2;
                pucPlmnRange = pstSimLockPlmnInfo->astSimLockPlmnRange[ulPlmnParaIdx].aucRangeBegin;
                PS_MEM_CPY(pucPlmnRange, aucImsiStr, (VOS_UINT16)ulImsiStrLen);
                PS_MEM_SET(pucPlmnRange + ulImsiStrLen, 0xFF,
                                (TAF_PH_SIMLOCK_PLMN_STR_LEN - ulImsiStrLen));
            }
        }
        else
        {
            /* ��Plmninfo����index��3n+2 ʱ,��ӦPlmnRangeEnd */
            if (AT_FAILURE == At_AsciiNum2SimLockImsiStr(aucImsiStr, pstParalist[i].aucPara,pstParalist[i].usParaLen))
            {
                return AT_ERROR;
            }
            else
            {
                ulImsiStrLen = (pstParalist[i].usParaLen + 1) / 2;
                pucPlmnRange = pstSimLockPlmnInfo->astSimLockPlmnRange[ulPlmnParaIdx].aucRangeEnd;
                PS_MEM_CPY(pucPlmnRange, aucImsiStr, (VOS_UINT16)ulImsiStrLen);
                PS_MEM_SET(pucPlmnRange + ulImsiStrLen, 0xFF,
                                (TAF_PH_SIMLOCK_PLMN_STR_LEN - ulImsiStrLen));
            }
            ++ ulPlmnParaIdx;
        }

    }

    return AT_OK;

}


VOS_UINT32 At_SetSimLockPlmnInfo(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulParaCnt,
    AT_PARSE_PARA_TYPE_STRU             *pstParalist
)
{
    VOS_UINT32                          ulRslt;
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    VOS_UINT32                          i;
    VOS_UINT32                          ulPlmnInfoNum;
    /*TAF_CUSTOM_SIM_LOCK_PLMN_RANGE_STRU stDftPlmnInfoVal;*/

    if (VOS_TRUE == g_bAtDataLocked)
    {
        ulRslt = AT_DATA_UNLOCK_ERROR;
    }
    else if (ulParaCnt > ((TAF_MAX_SIM_LOCK_RANGE_NUM * 3) + 1))
    {
        ulRslt = AT_SIMLOCK_PLMN_NUM_ERR;
    }
    else if (((ulParaCnt - 1) % 3) != 0)
    {
        ulRslt = AT_ERROR;
    }
    else
    {
        ulRslt =  At_CovertAtParaToSimlockPlmnInfo(ulParaCnt, pstParalist, &stSimLockPlmnInfo);
    }

    if (AT_OK != ulRslt)
    {
        At_FormatResultData(ucIndex, ulRslt);
        return AT_ERROR;
    }
#if 0
    if (VOS_TRUE == DRV_SEC_CHECK())
    {
        At_FormatResultData(ucIndex, AT_OK);
        return AT_OK;
    }
#endif

    /* ���PLMN �Ŷ�(MNClen,PlmnRangeBegin,PlmnRangeEnd)�ĸ��� ����2��������ʼ��Plmn ��Ϣ */
    ulPlmnInfoNum = (ulParaCnt - 1) / 3;

    /* ��ʣ���PLMN�Ŷ�����ΪĬ��ֵ */
    for (i = ulPlmnInfoNum ; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++)
    {
        PS_MEM_SET(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                        AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                        TAF_PH_SIMLOCK_PLMN_STR_LEN);
        PS_MEM_SET(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                        AT_SIM_LOCK_PLMN_RANGE_DEFAULT_VAL,
                                        TAF_PH_SIMLOCK_PLMN_STR_LEN);
        stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum = AT_SIM_LOCK_MNC_NUM_DEFAULT_VAL;
    }

    stSimLockPlmnInfo.ulStatus = NV_ITEM_ACTIVE;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    /* ��ȡ��ǰ����״̬*/
    ulRslt = NV_ReadEx(MODEM_ID_0, en_NV_Item_CardlockStatus,
                      &stCardLockStatus,
                      sizeof(stCardLockStatus));

    if (NV_OK != ulRslt)
    {
        AT_WARN_LOG("At_SetSimLockPlmnInfo:read en_NV_Item_CardlockStatus Fail.");
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_ERROR;
    }

    /* �����ǰ�Ѿ���������״̬��ֱ�ӷ���ERROR */
    if ((NV_ITEM_ACTIVE == stCardLockStatus.ulStatus)
     && (TAF_OPERATOR_UNLOCK_TIMES_MIN == stCardLockStatus.ulRemainUnlockTimes)
     && (TAF_OPERATOR_LOCK_LOCKED == stCardLockStatus.enCardlockStatus))
    {
        AT_WARN_LOG("At_SetSimLockPlmnInfo: is locked, operation is not allowed.");
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_ERROR;

    }

    /* ��en_NV_Item_CardlockStatus��״̬��Ϊ���CardStatus ����������Ϊ1,Remain Times���ֲ��� */
    stCardLockStatus.ulStatus            = NV_ITEM_ACTIVE;
    stCardLockStatus.enCardlockStatus    = TAF_OPERATOR_LOCK_NEED_UNLOCK_CODE;

    ulRslt = NV_WriteEx(MODEM_ID_0, en_NV_Item_CardlockStatus,
                        &stCardLockStatus,
                        sizeof(stCardLockStatus));
    if (NV_OK != ulRslt)
    {
        AT_WARN_LOG("At_SetSimLockPlmnInfo:write en_NV_Item_CardlockStatus Fail.");
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_ERROR;
    }


    /*��C�˷�����Ϣ����simlockNV*/
    if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(0,
                                              0,
                                              DRV_AGENT_SIMLOCK_NV_SET_REQ,
                                              &stCardLockStatus,
                                              sizeof(stCardLockStatus),
                                              I0_WUEPS_PID_DRV_AGENT))
    {

        AT_WARN_LOG("At_SetSimLockPlmnInfo():DRV_AGENT_SIMLOCK_NV_SET_REQ NV Write Fail!");
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }


    /* ��PLMN��Ϣд�뵽NV��en_NV_Item_CustomizeSimLockPlmnInfo */

    ulRslt = NV_WriteEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockPlmnInfo,
                        &stSimLockPlmnInfo,
                        sizeof(stSimLockPlmnInfo));
    if (NV_OK != ulRslt)
    {
        AT_WARN_LOG("At_SetSimLockPlmnInfo:write en_NV_Item_CustomizeSimLockPlmnInfo Fail.");
        At_FormatResultData(ucIndex, AT_ERROR);
        return AT_ERROR;
    }

    At_FormatResultData(ucIndex, AT_OK);
    return AT_OK;
}


VOS_UINT32 At_SetMaxLockTimes(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;

    /* ���ò���Ϊ�� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ������������ */
    if (gucAtParaIndex != 1)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ����Ƿ������ݱ���,δ���ʱ���س�����Ϣ */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return  AT_DATA_UNLOCK_ERROR;
    }

    stSimLockMaxTimes.ulStatus       = NV_ITEM_ACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = gastAtParaList[0].ulParaValue;


    /* ��C�˷�����Ϣ����SIMLOCK�������� */
    if (TAF_SUCCESS != AT_FillAndSndAppReqMsg(0,
                                              0,
                                              DRV_AGENT_MAX_LOCK_TIMES_SET_REQ,
                                              &stSimLockMaxTimes,
                                              sizeof(stSimLockMaxTimes),
                                              I0_WUEPS_PID_DRV_AGENT))
    {

        AT_WARN_LOG("At_SetMaxLockTimes():DRV_AGENT_SIMLOCK_NV_SET_REQ NV Write Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MAXLCKTMS_SET;
    return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */


}


VOS_UINT32 AT_SetVertime ( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������ϢDRV_AGENT_VERTIME_QRY_REQ��AT�������� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_VERTIME_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VERSIONTIME_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if ( VOS_WIN32 == VOS_OS_VER )
VOS_UINT32 AT_SetNvimPara ( VOS_UINT8 ucIndex )
{
    NV_ID_ENUM_U16                      eNvimTempId;
    VOS_UINT32                          ulTempLen;
    VOS_UINT32                          ulRst;
    VOS_UINT8*                          pNvTemp;
    VOS_UINT16                          usLength;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    ulTempLen = 0;

    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetCgsnPara: Get modem id fail.");
        return AT_ERROR;
    }

    /* ��������ȷ*/
    if (!(((0 == gastAtParaList[0].ulParaValue) && (2 == gucAtParaIndex))
       || ((1 == gastAtParaList[0].ulParaValue) && (3 == gucAtParaIndex))))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*�ڶ�������ΪNV��ID*/
    eNvimTempId = (NV_ID_ENUM_U16)gastAtParaList[1].ulParaValue;

    /*��һ������Ϊ0��ʾ��NV��ֵ��Ϊ1��ʾдNV��*/
    if (0 == gastAtParaList[0].ulParaValue)
    {
        NV_GetLength(eNvimTempId, &ulTempLen);
        pNvTemp = (VOS_UINT8 *)PS_MEM_ALLOC(I0_WUEPS_PID_TAF, ulTempLen);

        if (VOS_NULL_PTR == pNvTemp)
        {
            AT_ERR_LOG("AT_SetNvimPara:ERROR:ALLOC MEMORY FAIL.");
            return AT_ERROR;
        }
        ulRst = AT_ReadValueFromNvim(eNvimTempId, pNvTemp, ulTempLen, enModemId);
        if (AT_OK == ulRst )
        {
            usLength = 0;
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"^NVSTUB:");
            usLength += (TAF_UINT16)At_HexString2AsciiNumPrint(AT_CMD_MAX_LEN,
                                                                 (TAF_INT8 *)pgucAtSndCodeAddr,
                                                                 pgucAtSndCodeAddr + usLength,
                                                                 pNvTemp,
                                                                 (VOS_UINT16)ulTempLen);

            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);
            ulRst = AT_SUCCESS;
        }

        /* �����ڴ��ͷ� */
        PS_MEM_FREE(I0_WUEPS_PID_TAF, pNvTemp);
        return ulRst;
    }
    else
    {
        if(AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[2].aucPara,
                                              &gastAtParaList[2].usParaLen))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        if (NV_OK !=  NV_WriteEx(enModemId, eNvimTempId, gastAtParaList[2].aucPara, gastAtParaList[2].usParaLen))
        {
             AT_WARN_LOG("AT_SetNvimPara():WARNING:Invoke NVIM Write function falied");
             return AT_ERROR;
        }

#ifdef DMT
        NAS_STUB_UpdateGlobalVar(eNvimTempId);
#endif
        return AT_OK;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SetPidReinitPara
 ��������  : ���½���PID��ʼ���еĲ�����س�ʼ������
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��28��
    �޸�����   : DSDA GUNAS C CORE DMT
*****************************************************************************/
VOS_UINT32 AT_SetPidReinitPara ( VOS_UINT8 ucIndex )
{
#ifdef DMT
    VOS_UINT8                           ucValue;

    ucValue = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    NAS_STUB_PidReinit(ucValue);
#endif
    return AT_OK;
}

TAF_UINT32 AT_SetUSIMPara(TAF_UINT8 ucIndex)
{
    USIMM_STK_COMMAND_DETAILS_STRU      stCMDDetail;
    VOS_UINT8                           ucRecordNum;
    USIMM_SET_FILE_INFO_STRU            stSetFileInfo;
    USIMM_RESET_INFO_STRU               stRstInfo;

    ucRecordNum = 0;

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (3 == gucAtParaIndex)
    {
        ucRecordNum = gastAtParaList[2].ulParaValue;
    }

    /* ������AT&T & DCM�Ķ����������0x4F36��0x4F34�ļ�ʱ��Ҫ����enAppType */
    if ((USIMM_ATT_RAT_BALANCING_FID == gastAtParaList[0].ulParaValue)
     || (USIMM_ATT_ACTING_PLMN_FID == gastAtParaList[0].ulParaValue))
    {
        stSetFileInfo.enAppType     = USIMM_ATT_APP;
        stSetFileInfo.usEfId        = (VOS_UINT16)gastAtParaList[0].ulParaValue;
        stSetFileInfo.ucRecordNum   = ucRecordNum;
        stSetFileInfo.ulEfLen       = gastAtParaList[1].usParaLen;
        stSetFileInfo.pucEfContent  = gastAtParaList[1].aucPara;
        stSetFileInfo.ucRsv         = 0;

        USIMM_SetFileReq(WUEPS_PID_AT, 0, &stSetFileInfo);
    }
    else
    {
        stSetFileInfo.enAppType     = USIMM_UNLIMIT_APP;
        stSetFileInfo.usEfId        = (VOS_UINT16)gastAtParaList[0].ulParaValue;
        stSetFileInfo.ucRecordNum   = ucRecordNum;
        stSetFileInfo.ulEfLen       = gastAtParaList[1].usParaLen;
        stSetFileInfo.pucEfContent  = gastAtParaList[1].aucPara;
        stSetFileInfo.ucRsv         = 0;

        USIMM_SetFileReq(WUEPS_PID_AT, 0, &stSetFileInfo);
    }

    if (0x6F07 == gastAtParaList[0].ulParaValue)
    {
        stCMDDetail.ucCommandType = USIMM_RESET;
        VOS_MemSet(&stRstInfo, 0x0, sizeof(stRstInfo));

        USIMM_ResetReq(WUEPS_PID_AT, &stCMDDetail, &stRstInfo);
    }


#ifdef DMT
    NAS_STUB_ReadUsimPara();
#endif

    return AT_OK;
}

VOS_UINT32 AT_SetSTKParaStub(VOS_UINT8 ucIndex)
{
    USIMM_STK_COMMAND_DETAILS_STRU      stCMDDetail;
    STK_NAS_STEERING_OF_ROAMING_STRU   *pstSteerOfRoamMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    /* �����ڴ�  */
    pstSteerOfRoamMsg = (STK_NAS_STEERING_OF_ROAMING_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(STK_NAS_STEERING_OF_ROAMING_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSteerOfRoamMsg )
    {
        /* �ڴ�����ʧ�� */
        AT_ERR_LOG("AT_SetSTKParaStub:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ģ��USIM��MMCģ�鷢����Ϣ */
    pstSteerOfRoamMsg->ulMsgName  = STK_NAS_STEERING_OF_ROAMING_IND;
    pstSteerOfRoamMsg->usOplmnListLen = 0;

    /* ��д��ز��� */
    pstSteerOfRoamMsg->ulSenderPid          = MAPS_STK_PID;
    pstSteerOfRoamMsg->ulReceiverPid        = AT_GetDestPid(ucIndex, I0_WUEPS_PID_MMC);
    pstSteerOfRoamMsg->ulLength             = sizeof(STK_NAS_STEERING_OF_ROAMING_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ����VOS����ԭ�� */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstSteerOfRoamMsg);
    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_SetSTKParaStub:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return AT_OK;
}
VOS_UINT32 AT_RefreshUSIMPara(VOS_UINT8 ucIndex)
{

    USIMM_STK_COMMAND_DETAILS_STRU      stCMDDetail;
    PS_USIM_REFRESH_IND_STRU           *pstMmcUsimRefreshMsg;
    PS_USIM_REFRESH_IND_STRU           *pstMmaUsimRefreshMsg;
    VOS_UINT32                          ulRslt;

    /* �����ڴ�  */
    pstMmcUsimRefreshMsg = (PS_USIM_REFRESH_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(PS_USIM_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMmcUsimRefreshMsg )
    {
        /* �ڴ�����ʧ�� */
        AT_ERR_LOG("AT_RefreshUSIMPara:ERROR: Memory Alloc Error for pstMsg");
        return VOS_ERR;
    }

    /* �����ڴ�  */
    pstMmaUsimRefreshMsg = (PS_USIM_REFRESH_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                               sizeof(PS_USIM_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMmaUsimRefreshMsg )
    {
        /* �ڴ�����ʧ�� */
        AT_ERR_LOG("AT_RefreshUSIMPara:ERROR: Memory Alloc Error for pstMsg");
        PS_MEM_FREE(WUEPS_PID_AT, pstMmcUsimRefreshMsg);
        return VOS_ERR;
    }


    /* ������� */
    if ((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ģ��USIM��MMCģ�鷢����Ϣ */
    pstMmcUsimRefreshMsg->ulMsgName            = PS_USIM_REFRESH_IND;
    pstMmcUsimRefreshMsg->astEfId[0].usFileId  = gastAtParaList[0].ulParaValue;
    pstMmcUsimRefreshMsg->usEfNum              = 1;
    pstMmcUsimRefreshMsg->enRefreshType        = USIMM_REFRESH_FILE_LIST;

    /* ��д��ز��� */
    pstMmcUsimRefreshMsg->ulSenderPid          = MAPS_PIH_PID;
    pstMmcUsimRefreshMsg->ulReceiverPid        = AT_GetDestPid(ucIndex, I0_WUEPS_PID_MMC);
    pstMmcUsimRefreshMsg->ulLength             = sizeof(PS_USIM_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ����VOS����ԭ�� */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMmcUsimRefreshMsg);

    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_RefreshUSIMPara:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    /* ģ��USIM��MMAģ�鷢����Ϣ */
    pstMmaUsimRefreshMsg->ulMsgName            = PS_USIM_REFRESH_IND;
    pstMmaUsimRefreshMsg->astEfId[0].usFileId  = gastAtParaList[0].ulParaValue;
    pstMmaUsimRefreshMsg->usEfNum              = 1;
    pstMmaUsimRefreshMsg->enRefreshType        = USIMM_REFRESH_FILE_LIST;

    /* ��д��ز��� */
    pstMmaUsimRefreshMsg->ulSenderPid          = MAPS_PIH_PID;
    pstMmaUsimRefreshMsg->ulReceiverPid        = AT_GetDestPid(ucIndex, I0_WUEPS_PID_MMA);
    pstMmaUsimRefreshMsg->ulLength             = sizeof(PS_USIM_REFRESH_IND_STRU) - VOS_MSG_HEAD_LENGTH;


    /* ����VOS����ԭ�� */
    ulRslt = PS_SEND_MSG(WUEPS_PID_AT, pstMmaUsimRefreshMsg);

    if ( VOS_OK != ulRslt )
    {
        AT_ERR_LOG("AT_RefreshUSIMPara:ERROR:PS_SEND_MSG ");
        return VOS_ERR;
    }

    return AT_OK;
}
#endif



VOS_UINT32 At_SetSystemInfoEx(TAF_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_SYSINFO_EX_VALUE_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSINFO_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/* end V7R1 PhaseI Modify */

/*****************************************************************************
 �� �� ��  : AT_SetGodloadPara
 ��������  : ʹ�����������ģʽ
             <CR><LF>OK<CR><LF>
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_ERR��VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��19��
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��17��
    �޸�����   : AT PROJECT
*****************************************************************************/
VOS_UINT32 AT_SetGodloadPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRet;

    /* ������� */
    if (0 != gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetGodloadPara: too many parameters.");
        return AT_ERROR;
    }

    /* ����Ϣ��C��ָʾʹ�����������ģʽ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_GODLOAD_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_SetApbatlvlPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GODLOAD_SET;
    return AT_WAIT_ASYNC_RETURN;

}
VOS_UINT32 At_SetResetPara( VOS_UINT8 ucIndex  )
{
    VOS_UINT8                           ucUpdateFlag;
    VOS_UINT32                          ulRslt;

    if (0 != gucAtParaIndex)
    {
        AT_WARN_LOG("At_SetResetPara: too many parameters.");
        return AT_ERROR;
    }

    /* �ȷ���OK */
    At_FormatResultData(ucIndex,AT_OK);

    /* B31�汾���������л����·�AT^RESET�������������OK�ظ���PC����Ҫ������ʱ����ʱ500ms */
    VOS_TaskDelay(500);

    /* ������Ϣ��C�ˣ����� */
    ucUpdateFlag = VOS_FALSE;

    ulRslt = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    DRV_AGENT_TMODE_SET_REQ,
                                    &ucUpdateFlag,
                                    sizeof(ucUpdateFlag),
                                    I0_WUEPS_PID_DRV_AGENT);
    if (VOS_OK != ulRslt)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetNvBackUpPara
 ��������  : ��NV����ݷ�����
            <CR><LF><result code><CR><LF >
            <CR><LF>OK<CR><LF>
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_ERR��VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��19��
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��4��
    �޸�����   : AT Project:NV_BACKUP��C��ʵ��
*****************************************************************************/
VOS_UINT32 AT_SetNvBackUpPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    /*Modified by l60609 for At Project, 2011-11-4, Begin */
    if (0 != gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetNvBackUpPara: too many parameters.");
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_NVBACKUP_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVBACKUP_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-4, End */
}


VOS_UINT32 AT_SetNvManufactureExtPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    if (0 != gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetNvManufactureExtPara: too many parameters.");
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_NVMANUFACTUREEXT_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVMANUFACTUREEXT_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_SetNvRestorePara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                 ulRst;

    if (0 != gucAtParaIndex)
    {
        AT_WARN_LOG("At_SetNvRestorePara: too many parameters.");
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_NVRESTORE_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVRESTORE_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32  AT_SetNvRststtsPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;

    if (0 != gucAtParaIndex)
    {
        AT_WARN_LOG("AT_SetNvRststtsPara: too many parameters.");
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_NVRSTSTTS_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVRSTSTTS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_SetWiFiEnablePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    ulRst = VOS_OK;

    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].ulParaValue )
    {
        /*�ر�WIFI*/
        ulRst = (VOS_UINT32)WIFI_POWER_SHUTDOWN();
    }
    else if (1 == gastAtParaList[0].ulParaValue )
    {
        /* ��Ʒ��APIδ�ṩ */
        #if 0
            WiFiReset();
        #endif
    }
    else
    {
#if(FEATURE_ON == FEATURE_LTE)

        VOS_TaskDelay(5500);    /* ������Ҫ����Ҫ5.5s���ӳ� */

#endif

        if ( VOS_OK != WIFI_POWER_SHUTDOWN())
        {
            return AT_ERROR;
        }

#if(FEATURE_ON == FEATURE_LTE)

        VOS_TaskDelay(1000);    /* ������Ҫ����Ҫ1���ӳ� */

#endif


        /*����ģʽ��WIFI*/
        ulRst = (VOS_UINT32)WIFI_POWER_START();
    }

    if (VOS_OK != ulRst)
    {
        return AT_ERROR;
    }

    return AT_OK;
}

VOS_UINT32 AT_SetWiFiModePara(VOS_UINT8 ucIndex)
{
    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    WIFI_TEST_CMD("wl down");

    if (AT_WIFI_SUPPORT_MODE_B == gastAtParaList[0].ulParaValue)
    {
        WIFI_TEST_CMD("wl nmode 0");
        WIFI_TEST_CMD("wl gmode 0");
    }
    else if (AT_WIFI_SUPPORT_MODE_G == gastAtParaList[0].ulParaValue)
    {
        WIFI_TEST_CMD("wl nmode 0");
        WIFI_TEST_CMD("wl gmode 2");
    }
    else
    {
        WIFI_TEST_CMD("wl nmode 1");
        WIFI_TEST_CMD("wl gmode 1");
    }

    WIFI_TEST_CMD("wl up");

    /*����ȫ�ֱ�����ѱ���ѯ*/
    g_ulWifiMode = gastAtParaList[0].ulParaValue;

    return AT_OK;
}
/*****************************************************************************
 �� �� ��  : AT_SetWiFiBandPara
 ��������  : ����Wifi�Ĵ���
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��26��
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 AT_SetWiFiBandPara(VOS_UINT8 ucIndex)
{

    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /*ĿǰWifiֻ֧��20M��40M����ERROR*/
    if(AT_WIFI_BAND_20M != gastAtParaList[0].ulParaValue)
    {
        return AT_ERROR;
    }

    return AT_OK;
}

VOS_UINT32 AT_SetWiFiFreqPara(VOS_UINT8 ucIndex)
{
    VOS_CHAR                            acCmd[200]={0};
    VOS_UINT32                          ulWifiFreq;
    VOS_UINT32                          i;
    VOS_UINT32                          aulChannel[] = {2412,2417,2422,2427,2432,
                                                        2437,2442,2447,2452,2457,
                                                        2462,2467,2472,2484};

    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /* �����ŵ�  */
    ulWifiFreq = 0;
    for (i=0; i<(sizeof(aulChannel)/sizeof(VOS_UINT32)); i++)
    {
        if (gastAtParaList[0].ulParaValue == aulChannel[i])
        {
            ulWifiFreq = (i+1);
            break;
        }
    }

    if (0 == ulWifiFreq)
    {
        AT_WARN_LOG("AT_SetWiFiFreqPara: freq ERROR");
        return AT_ERROR;
    }

    /* ���õ����ӿ� */
    WIFI_TEST_CMD("wl down");

    VOS_sprintf(acCmd, "wl channel %d", ulWifiFreq);
    WIFI_TEST_CMD(acCmd);

    WIFI_TEST_CMD("wl up");

    /* ����ȫ�ֱ�����ѱ���ѯ */
    g_ulWifiFreq = ulWifiFreq;

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_TransferWifiRate
 ��������  : ��AT���õ�����ֵת��ΪWIFI�ӿڵ�ֵ
 �������  : VOS_UINT32                          ulInRate
             VOS_UINT32                         *pulOutRate
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��17��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_TransferWifiRate(
    VOS_UINT32                          ulInRate,
    VOS_UINT32                         *pulOutRate
)
{
    VOS_UINT8                           ucIndex;
    /* WIFI nģʽ AT^WIDATARATE���õ�����ֵ��WL��������ֵ�Ķ�Ӧ�� */
    VOS_UINT32                          aucAtWifiNRate_Table[AT_WIFI_N_RATE_NUM] = {650, 1300, 1950, 2600, 3900, 5200, 5850, 6500};

    for (ucIndex = 0; ucIndex < AT_WIFI_N_RATE_NUM; ucIndex++)
    {
        if (aucAtWifiNRate_Table[ucIndex] == ulInRate)
        {
            *pulOutRate = ucIndex;
            break;
        }
    }

    if (ucIndex >= AT_WIFI_N_RATE_NUM)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_SetWiFiRatePara(VOS_UINT8 ucIndex)
{
    VOS_CHAR                            acCmd[200]={0};
    VOS_UINT32                          ulWifiRate;

#if(FEATURE_ON == FEATURE_LTE)
#else
    VOS_UINT32                          ulNRate;
    VOS_UINT32                          ulRslt;
#endif
    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    ulWifiRate = gastAtParaList[0].ulParaValue/100;


    if (AT_WIFI_SUPPORT_MODE_N == g_ulWifiMode)         /*11 n*/
    {
#if(FEATURE_ON == FEATURE_LTE)
        VOS_sprintf(acCmd, "wl nrate -m %d", 7);
#else
        ulRslt = AT_TransferWifiRate(gastAtParaList[0].ulParaValue, &ulNRate);

        if (VOS_OK == ulRslt)
        {
            VOS_sprintf(acCmd, "wl nrate -m %d", ulNRate);
        }
        else
        {
            return AT_ERROR;
        }
#endif
    }
    else if (AT_WIFI_SUPPORT_MODE_G == g_ulWifiMode )    /*11 g*/
    {
#if(FEATURE_ON == FEATURE_LTE)
        VOS_sprintf(acCmd, "wl bg_rate %d", ulWifiRate);
#else
        VOS_sprintf(acCmd, "wl rate %d", ulWifiRate);
#endif
    }
    else if(AT_WIFI_SUPPORT_MODE_B == g_ulWifiMode)    /*11 b*/
    {
#if(FEATURE_ON == FEATURE_LTE)
        VOS_sprintf(acCmd, "wl bg_rate %d", ulWifiRate);
#else
        VOS_sprintf(acCmd, "wl rate %d", ulWifiRate);
#endif
    }
    else
    {
        AT_WARN_LOG("AT_SetWiFiRatePara: wifimode ERROR");
        return AT_ERROR;
    }

    WIFI_TEST_CMD(acCmd);


    /*����ȫ�ֱ�����ѱ���ѯ*/
    g_ulWifiRate = gastAtParaList[0].ulParaValue;

    return AT_OK;
}

VOS_UINT32 AT_SetWiFiPowerPara(VOS_UINT8 ucIndex)
{
    VOS_CHAR                            acCmd[200]={0};
    VOS_INT32                           lWifiPower;

    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    g_lWifiPower = (VOS_INT32)gastAtParaList[0].ulParaValue;

    lWifiPower = g_lWifiPower/100;

    if (lWifiPower < AT_WIFI_POWER_MIN)
    {
        lWifiPower = AT_WIFI_POWER_MIN;
    }

    if (lWifiPower > AT_WIFI_POWER_MAX)
    {
        lWifiPower = AT_WIFI_POWER_MAX;
    }

    VOS_sprintf(acCmd, "wl txpwr1 -o -d %d", lWifiPower);

    /*���õ����ӿ�*/
    WIFI_TEST_CMD(acCmd);


    return AT_OK;
}



VOS_UINT32 AT_SetWiFiTxPara(VOS_UINT8 ucIndex)
{
#if(FEATURE_ON == FEATURE_LTE)
    VOS_CHAR                            acCmd[200]={0};
#endif

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }
#if(FEATURE_ON == FEATURE_LTE)
    if(g_ulWifiMode == AT_WIFI_SUPPORT_MODE_CW)
    {
        if (AT_WIFI_TX_OFF == gastAtParaList[0].ulParaValue)
        {
            /* WIFI_TEST_CMD("wl down"); */
            WIFI_TEST_CMD("wl fqacurcy 0");
            /* WIFI_TEST_CMD("wl up"); */
        }
        else
        {
            WIFI_TEST_CMD("wl up");
            WIFI_TEST_CMD("wl band b");
            WIFI_TEST_CMD("wl out");
            WIFI_TEST_CMD("wl phy_txpwrctrl 0");

            if(0 == g_ulWifiRF)
            {
                WIFI_TEST_CMD("wl phy_txpwrindex 0 127");
            }
            else
            {
                WIFI_TEST_CMD("wl phy_txpwrindex 127 0");
            }

            WIFI_TEST_CMD("wl phy_txpwrctrl 1");

            VOS_sprintf(acCmd, "wl fqacurcy %d", g_ulWifiFreq);

            WIFI_TEST_CMD(acCmd);

        }
    }
    else
    {
#endif
    /* ����Ϊ��رշ����������Ϊ1�򿪷���� */
    if (AT_WIFI_TX_OFF == gastAtParaList[0].ulParaValue)
    {
         WIFI_TEST_CMD("wl pkteng_stop tx");
    }
    else
    {
        /* ���õ����ӿ� */
        WIFI_TEST_CMD("wl down");

        WIFI_TEST_CMD("wl mpc 0");

        WIFI_TEST_CMD("wl country ALL");

        WIFI_TEST_CMD("wl frameburst 1");

        WIFI_TEST_CMD("wl scansuppress 1");

        WIFI_TEST_CMD("wl up");

        WIFI_TEST_CMD("wl pkteng_start 00:11:22:33:44:55 tx 100 1500 0");

#if(FEATURE_ON == FEATURE_LTE)
        WIFI_TEST_CMD("wl phy_forcecal 1");
#endif
    }
#if(FEATURE_ON == FEATURE_LTE)
    }
#endif
    return AT_OK;
}

VOS_UINT32 AT_SetWiFiRxPara(VOS_UINT8 ucIndex)
{
    VOS_CHAR                            acCmd[200]={0};

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /* ��������*/
    if (gucAtParaIndex > 3)
    {
        return  AT_TOO_MANY_PARA;
    }

    /*����Ϊ��رս��ջ�������Ϊ1�򿪽��ջ�*/
    if ( AT_WIFI_RX_OFF == gastAtParaList[0].ulParaValue)
    {
        /* ���������رս��ջ� */
        WIFI_TEST_CMD("wl pkteng_stop rx");
    }
    else
    {
        WIFI_TEST_CMD("wl down");

        WIFI_TEST_CMD("wl mpc 0");

        WIFI_TEST_CMD("wl country ALL");

        WIFI_TEST_CMD("wl frameburst 1");

        WIFI_TEST_CMD("wl scansuppress 1");


        WIFI_TEST_CMD("wl up");

        VOS_sprintf(acCmd, "wl pkteng_start %c%c:%c%c:%c%c:%c%c:%c%c:%c%c rx async 0 0",
                    gastAtParaList[1].aucPara[0],gastAtParaList[1].aucPara[1],
                    gastAtParaList[1].aucPara[2],gastAtParaList[1].aucPara[3],
                    gastAtParaList[1].aucPara[4],gastAtParaList[1].aucPara[5],
                    gastAtParaList[1].aucPara[6],gastAtParaList[1].aucPara[7],
                    gastAtParaList[1].aucPara[8],gastAtParaList[1].aucPara[9],
                    gastAtParaList[1].aucPara[10],gastAtParaList[1].aucPara[11]);

        WIFI_TEST_CMD(acCmd);

        WIFI_GET_RX_PACKET_REPORT(&g_ulUcastWifiRxPkts,  &g_ulMcastWifiRxPkts);


    }

    return AT_OK;
}
VOS_UINT32 AT_SetWiFiPacketPara(VOS_UINT8 ucIndex)
{
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* ��������*/
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }


    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    /* TODO: */
    /* Ŀǰ���ø÷�ʽ���� */
    WIFI_GET_RX_PACKET_REPORT(&g_ulUcastWifiRxPkts,  &g_ulMcastWifiRxPkts);


    return AT_OK;
}

/* Modify by z60575 for multi_ssid, 2012-9-5 begin */

VOS_UINT32 AT_SetWiFiLogPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU               stWifiSsid;
    TAF_AT_MULTI_WIFI_SEC_STRU                stWifiKey;

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /* ��������*/
    if (gucAtParaIndex > 2)
    {
        return  AT_TOO_MANY_PARA;
    }

    PS_MEM_SET(&stWifiKey, 0, sizeof(stWifiKey));
    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    /*����WIFI SSID*/
    if (0 == gastAtParaList[0].ulParaValue)
    {
        /*�������ȹ���*/
        if (gastAtParaList[1].usParaLen >= AT_WIFI_SSID_LEN_MAX)
        {
            return  AT_CME_INCORRECT_PARAMETERS;
        }

        /*��ȡWIFI KEY��Ӧ��NV��*/
        if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
        {
            AT_WARN_LOG("AT_SetWiFiSsidPara:READ NV ERROR");
            return AT_ERROR;
        }
        else
        {
            PS_MEM_SET(stWifiSsid.aucWifiSsid[0], 0x00, AT_WIFI_SSID_LEN_MAX);

            PS_MEM_CPY(stWifiSsid.aucWifiSsid[0], gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);

            stWifiSsid.aucWifiSsid[0][gastAtParaList[1].usParaLen] = '\0';

            /*д��WIFI SSID��Ӧ��NV��*/
            if (VOS_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
            {
                AT_WARN_LOG("AT_SetWiFiSsidPara:WRITE NV ERROR");
                return AT_ERROR;
            }
        }
    }
    else
    {
        /*��ȡWIFI KEY��Ӧ��NV��*/
        if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
        {
            AT_WARN_LOG("AT_SetWiFiKeyPara:READ NV ERROR");
            return AT_ERROR;
        }
        else
        {

            /*�������ȹ���*/
            if (gastAtParaList[1].usParaLen >= AT_WIFI_KEY_LEN_MAX)
            {
                return  AT_CME_INCORRECT_PARAMETERS;
            }

            /*����indexд���Ӧ��KEY*/
            switch(stWifiKey.ucWifiWepKeyIndex[0])
            {
                case 0:
                    VOS_MemCpy(stWifiKey.aucWifiWepKey1[0], gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
                    stWifiKey.aucWifiWepKey1[0][gastAtParaList[1].usParaLen] = '\0';
                    break;

                case 1:
                    VOS_MemCpy(stWifiKey.aucWifiWepKey2[0], gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
                    stWifiKey.aucWifiWepKey2[0][gastAtParaList[1].usParaLen] = '\0';
                    break;

                case 2:
                    VOS_MemCpy(stWifiKey.aucWifiWepKey3[0], gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
                    stWifiKey.aucWifiWepKey3[0][gastAtParaList[1].usParaLen] = '\0';
                    break;

                case 3:
                    VOS_MemCpy(stWifiKey.aucWifiWepKey4[0], gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
                    stWifiKey.aucWifiWepKey4[0][gastAtParaList[1].usParaLen] = '\0';
                    break;

                default:
                    break;
            }

            if (VOS_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
            {
                AT_WARN_LOG("AT_SetWiFiKeyPara:WRITE NV ERROR");
                return AT_ERROR;
            }
        }
    }

    return AT_OK;
}


VOS_UINT32 AT_SetWiFiSsidPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU         stWifiSsid;
    VOS_UINT8                           ucGroup;

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /* ��������*/
    if (gucAtParaIndex > 2)
    {
        return  AT_TOO_MANY_PARA;
    }

    /*�������ȹ���*/
    if (gastAtParaList[1].usParaLen >= AT_WIFI_SSID_LEN_MAX)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    /* SSID���4�� */
    if (gastAtParaList[0].ulParaValue >= AT_WIFI_MAX_SSID_NUM)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    ucGroup = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /*��ȡWIFI KEY��Ӧ��NV��*/
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_SetWiFiSsidPara:READ NV ERROR");
        return AT_ERROR;
    }
    else
    {
        PS_MEM_CPY(&(stWifiSsid.aucWifiSsid[ucGroup][0]), gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
        stWifiSsid.aucWifiSsid[ucGroup][gastAtParaList[1].usParaLen] = '\0';

        /*д��WIFI SSID��Ӧ��NV��*/
        if (VOS_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
        {
            AT_WARN_LOG("AT_SetWiFiSsidPara:WRITE NV ERROR");
            return AT_ERROR;
        }
    }

    return AT_OK;
}
VOS_UINT32 AT_SetWiFiKeyPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SEC_STRU          stWifiKey;
    VOS_UINT8                           ucGroup;

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return  AT_TOO_MANY_PARA;
    }

    /* �������ȹ��� */
    if (gastAtParaList[1].usParaLen > AT_WIFI_WLWPAPSK_LEN)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_ERROR;
    }

    /* ����4��SSID */
    if (gastAtParaList[0].ulParaValue >= AT_WIFI_MAX_SSID_NUM)
    {
       return  AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stWifiKey, 0, sizeof(stWifiKey));

    ucGroup = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ��ȡWIFI KEY��Ӧ��NV�� */
    if (NV_OK!= NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY,&stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_SetWiFiKeyPara:READ NV ERROR");
        return AT_ERROR;
    }
    else
    {
        /* д��KEY */
        PS_MEM_CPY(&(stWifiKey.aucWifiWpapsk[ucGroup][0]), gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
        stWifiKey.aucWifiWpapsk[ucGroup][gastAtParaList[1].usParaLen] = '\0';


        if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
        {
            AT_WARN_LOG("AT_SetWiFiKeyPara:WRITE NV ERROR");
            return AT_ERROR;
        }
    }


    return AT_OK;
}

VOS_VOID AT_PrintWifiChannelInfo(
    AT_WIFI_INFO_STRU                  *pstWifiInfo,
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT8                           ucLoopIndex;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    ucLoopIndex                         = 0;
    usLength                            = gstAtSendData.usBufLen;


    /* ����֧��802.11b��ʽ, ���802.11b��ʽ֧�ֵ��ŵ��� */
    if (VOS_TRUE == pstWifiInfo->bitOpbSupport)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           "b");
        for (ucLoopIndex = pstWifiInfo->usbLowChannel; ucLoopIndex <= pstWifiInfo->usbHighChannel; ucLoopIndex++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d",
                                               ucLoopIndex);
        }
        if ( (VOS_TRUE == pstWifiInfo->bitOpgSupport)
          || (VOS_TRUE == pstWifiInfo->bitOpnSupport) )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",gaucAtCrLf);
        }
    }

    /* ����֧��802.11g��ʽ, ���802.11g��ʽ֧�ֵ��ŵ��� */
    if (VOS_TRUE == pstWifiInfo->bitOpgSupport)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           "g");
        for (ucLoopIndex = pstWifiInfo->usgLowChannel; ucLoopIndex <= pstWifiInfo->usgHighChannel; ucLoopIndex++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d",
                                               ucLoopIndex);
        }
        if (VOS_TRUE == pstWifiInfo->bitOpnSupport)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",gaucAtCrLf);
        }
    }

    /* ����֧��802.11n��ʽ, ���802.11n��ʽ֧�ֵ��ŵ��� */
    if (VOS_TRUE == pstWifiInfo->bitOpnSupport)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           "n");
        for (ucLoopIndex = pstWifiInfo->usnLowChannel; ucLoopIndex <= pstWifiInfo->usnHighChannel; ucLoopIndex++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d",
                                               ucLoopIndex);
        }
    }

    gstAtSendData.usBufLen += usLength;
    return;
}


VOS_VOID AT_PrintWifibPowerInfo(
    AT_WIFI_INFO_STRU                  *pstWifiInfo,
    VOS_UINT8                           ucWifiMode,
    VOS_UINT8                           ucIndex
)
{

    /* ���802.11b��ʽ�������� */
    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                       "%s:%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       "b");
    if ( (AT_WIFI_MODE_ONLY_PA == ucWifiMode)
      || (AT_WIFI_MODE_PA_NOPA == ucWifiMode) )
    {
        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                           ",%d",
                                           pstWifiInfo->ausbPower[0]);
    }
    if ( (AT_WIFI_MODE_ONLY_NOPA == ucWifiMode)
      || (AT_WIFI_MODE_PA_NOPA == ucWifiMode) )
    {
        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                           ",%d",
                                           pstWifiInfo->ausbPower[1]);
    }
}
VOS_VOID AT_PrintWifigPowerInfo(
    AT_WIFI_INFO_STRU                  *pstWifiInfo,
    VOS_UINT8                           ucWifiMode,
    VOS_UINT8                           ucIndex
)
{

    /* ���802.11g��ʽ�������� */
    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                       "%s:%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       "g");
    if ( (AT_WIFI_MODE_ONLY_PA == ucWifiMode)
      || (AT_WIFI_MODE_PA_NOPA == ucWifiMode) )
    {
        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                           ",%d",
                                           pstWifiInfo->ausgPower[0]);
    }
    if ( (AT_WIFI_MODE_ONLY_NOPA == ucWifiMode)
      || (AT_WIFI_MODE_PA_NOPA == ucWifiMode) )
    {
        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                           ",%d",
                                           pstWifiInfo->ausgPower[1]);
    }
}
VOS_VOID AT_PrintWifinPowerInfo(
    AT_WIFI_INFO_STRU                  *pstWifiInfo,
    VOS_UINT8                           ucWifiMode,
    VOS_UINT8                           ucIndex
)
{
    /* ���802.11n��ʽ�������� */
    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                       "%s:%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       "n");
    if ( (AT_WIFI_MODE_ONLY_PA == ucWifiMode)
      || (AT_WIFI_MODE_PA_NOPA == ucWifiMode) )
    {
        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                           ",%d",
                                           pstWifiInfo->ausnPower[0]);
    }
    if ( (AT_WIFI_MODE_ONLY_NOPA == ucWifiMode)
      || (AT_WIFI_MODE_PA_NOPA == ucWifiMode) )
    {
        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                           ",%d",
                                           pstWifiInfo->ausnPower[1]);
    }
}
VOS_VOID AT_PrintWifiPowerInfo(
    AT_WIFI_INFO_STRU                  *pstWifiInfo,
    VOS_UINT8                           ucIndex
)
{
    AT_WIFI_MODE_ENUM_UINT8             ucWifiMode;

    /* ��ʼ�� */
    ucWifiMode                          = (VOS_UINT8)WIFI_GET_PA_MODE();

    /* ����֧��802.11b��ʽ, ����������� */
    if (VOS_TRUE == pstWifiInfo->bitOpbSupport)
    {
        AT_PrintWifibPowerInfo(pstWifiInfo, ucWifiMode, ucIndex);
        if ( (VOS_TRUE == pstWifiInfo->bitOpgSupport)
          || (VOS_TRUE == pstWifiInfo->bitOpnSupport) )
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                       "%s",gaucAtCrLf);
        }

    }

    /* ����֧��802.11g��ʽ, ����������� */
    if (VOS_TRUE == pstWifiInfo->bitOpgSupport)
    {
        AT_PrintWifigPowerInfo(pstWifiInfo, ucWifiMode, ucIndex);
        if (VOS_TRUE == pstWifiInfo->bitOpnSupport)
        {
            gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                       "%s",gaucAtCrLf);
        }
    }

    /* ����֧��802.11n��ʽ, ����������� */
    if (VOS_TRUE == pstWifiInfo->bitOpnSupport)
    {
        AT_PrintWifinPowerInfo(pstWifiInfo, ucWifiMode, ucIndex);
    }

    return;
}


VOS_UINT32 AT_SetWifiInfoPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT16                          usLen;
    VOS_CHAR * cString = "1,2,3,4,5,6,7,8,9,10,11,12,13";

    usLen = 0;

    if(gucAtParaIndex > 2)
    {
        return AT_ERROR;
    }

    if(0 == gastAtParaList[0].ulParaValue)
    {
        /* 0,0 */
        if(0 == gastAtParaList[1].ulParaValue)
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                        (TAF_CHAR *)pgucAtSndCodeAddr,
                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                        "^WIINFO:b,%s%s^WIINFO:g,%s%s^WIINFO:n,%s",
                        cString, gaucAtCrLf, cString, gaucAtCrLf, cString);
        }
        else    /* 0,1 */
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                        (TAF_CHAR *)pgucAtSndCodeAddr,
                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                        "^WIINFO:n,%s",
                        cString);
        }
    }
    else
    {
        /* 1,0 */
        if(0 == gastAtParaList[1].ulParaValue)
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                        (TAF_CHAR *)pgucAtSndCodeAddr,
                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                        "^WIINFO:b,130%s^WIINFO:g,80%s^WIINFO:n,80",
                        gaucAtCrLf, gaucAtCrLf);
        }
        else    /* 1,1 */
        {
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                        (TAF_CHAR *)pgucAtSndCodeAddr,
                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                        "^WIINFO:n,80");
        }
    }
    gstAtSendData.usBufLen = usLen;

    return AT_OK;
#else

    AT_WIFI_INFO_STRU                   stWifiInfo = {0};

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /* ��ʼ�� */
    gstAtSendData.usBufLen              = 0;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_ERROR;
    }

    /*��ȡWIFI INFO��Ӧ��NV��*/
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_INFO, &stWifiInfo, sizeof(AT_WIFI_INFO_STRU)))
    {
        AT_WARN_LOG("AT_SetWifiInfoPara:READ NV ERROR!");
        return AT_ERROR;
    }

    /* ��ѯ֧�ֵ��ŵ��Ż��������� */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        /* �������ʽ֧�ֵ��ŵ��� */
        AT_PrintWifiChannelInfo(&stWifiInfo, ucIndex);
    }
    else
    {
        /* �������ʽ���������� */
        AT_PrintWifiPowerInfo(&stWifiInfo, ucIndex);
    }

    return AT_OK;
#endif
}
VOS_UINT32 AT_SetWifiPaRangePara (VOS_UINT8 ucIndex)
{
    AT_WIFI_MODE_ENUM_UINT8             ucWifiMode;

    /* ��ʼ�� */
    ucWifiMode                          = (VOS_UINT8)WIFI_GET_PA_MODE();

    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }


    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    /*�������*/
    if ('h' == gastAtParaList[0].aucPara[0])
    {
        if (AT_WIFI_MODE_ONLY_NOPA == ucWifiMode)
        {
            return AT_ERROR;
        }

        if (VOS_OK != WIFI_SET_PA_MODE(AT_WIFI_MODE_ONLY_PA))
        {
            return AT_ERROR;
        }
    }
    else if ('l' == gastAtParaList[0].aucPara[0])
    {
        if (AT_WIFI_MODE_ONLY_PA == ucWifiMode)
        {
            return AT_ERROR;
        }

        if (VOS_OK != WIFI_SET_PA_MODE(AT_WIFI_MODE_ONLY_NOPA))
        {
            return AT_ERROR;
        }
    }
    else
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;
}


/*****************************************************************************
 �� �� ��  : AT_SetTmmiPara
 ��������  : ����MMI���Խ��
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��26��
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��2��20��
    �޸�����   : �ɵ��õ����ӿ��޸�ΪдNV
  3.��    ��   : 2012��03��03��
    �޸�����   : BalongV300R002 Build�Ż���Ŀ  :ɾ��FEATURE_E5��
*****************************************************************************/
VOS_UINT32 AT_SetTmmiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucFacInfo[AT_FACTORY_INFO_LEN];

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }


    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }
    VOS_MemSet(aucFacInfo, 0x00, AT_FACTORY_INFO_LEN);

    /* д��en_NV_Item_Factory_Info����ƫ��24���ֽڣ�����4Ϊ�ĸ��ֽڣ������Ҫ�ȶ� */
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Factory_Info, aucFacInfo, AT_FACTORY_INFO_LEN);

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_SetTmmiPara: NV Read Fail!");
        return AT_ERROR;
    }

    /* �ɹ� д��"ST P" */
    if (1 == gastAtParaList[0].ulParaValue)
    {
        VOS_MemCpy(&aucFacInfo[AT_MMI_TEST_FLAG_OFFSET], AT_MMI_TEST_FLAG_SUCC, AT_MMI_TEST_FLAG_LEN);
    }
    /* ʧ�� ��� */
    else
    {
        VOS_MemCpy(&aucFacInfo[AT_MMI_TEST_FLAG_OFFSET], "0000", AT_MMI_TEST_FLAG_LEN);
    }

    ulResult = NV_WriteEx(MODEM_ID_0, en_NV_Item_Factory_Info, aucFacInfo, AT_FACTORY_INFO_LEN);

    if (NV_OK != ulResult)
    {
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}
VOS_UINT32 AT_SetChrgEnablePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    ulRet                               = DRV_GET_BATTERY_SUPPORT();

    if (BSP_MODULE_UNSUPPORT == ulRet)
    {
        return AT_ERROR;
    }


    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }


    /*�������ȹ���*/
    if (1 != gastAtParaList[0].usParaLen)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 == gastAtParaList[0].ulParaValue)
    || (1 == gastAtParaList[0].ulParaValue))
    {

        /* ���������ӿ�ʹ�ܻ�ȥʹ�ܳ�� */
        DRV_CHG_STATE_SET(gastAtParaList[0].ulParaValue);
    }
    else
    {

        /*���ò���ӿ�*/
        DRV_CHG_BATT_SPLY();
    }


    return AT_OK;
}
/*****************************************************************************
 �� �� ��  : AT_SetTestScreenPara
 ��������  : ����������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��26��
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    �޸�����   : BalongV300R002 Build�Ż���Ŀ  :ɾ��FEATURE_E5��
*****************************************************************************/
VOS_UINT32 AT_SetTestScreenPara(VOS_UINT8 ucIndex)
{
#if 0
    VOS_UINT32                          ulRst;

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return  AT_TOO_MANY_PARA;
    }

    /* ���õ��������Խӿ� */
    ulRst = (VOS_UINT32)DRV_SCREEN_TEST_CMD(gastAtParaList[0].ulParaValue,gastAtParaList[1].ulParaValue);

    if (VOS_OK != ulRst)
    {
        return AT_ERROR;
    }
#endif
    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetCdurPara
 ��������  : ��ѯͨ��ʱ��
 �������  : VOS_UINT8 ucIndex �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32 ATC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��26��
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��10��17��
    �޸�����   : AT PROJECT
*****************************************************************************/
VOS_UINT32 AT_SetCdurPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRet;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return  AT_TOO_MANY_PARA;
    }

    if ((gucAtParaIndex != 1)
     || (0 == gastAtParaList[0].usParaLen)
     || (gastAtParaList[0].ulParaValue > AT_CALL_MAX_NUM))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucCallId = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ����Ϣ��C�˻�ȡͨ��ʱ�� */
    ulRet = MN_CALL_QryCdur(gastAtClientTab[ucIndex].usClientId,
                            gastAtClientTab[ucIndex].opId,
                            ucCallId);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_SetCdurPara: MN_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CDUR_READ;
    return AT_WAIT_ASYNC_RETURN;
}
VOS_UINT32 AT_SetWebPwdPara(VOS_UINT8 ucIndex)
{
    VOS_CHAR                                aucWebPwdTmp[AT_WEBUI_PWD_MAX + 1];
    TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU     stWebPwd;

    /* ������� */
    if (gucAtParaIndex > 2)
    {
        return  AT_TOO_MANY_PARA;
    }

    /* �������ȹ��� */
    if (gastAtParaList[1].usParaLen > AT_WEBUI_PWD_MAX)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }
    /* У��WEBUI PWD */
    if (AT_WEBUI_PWD_VERIFY == gastAtParaList[0].ulParaValue)
    {
        if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WEB_ADMIN_PASSWORD,&stWebPwd, sizeof(stWebPwd)))
        {
            AT_WARN_LOG("AT_SetWebPwdPara:READ NV ERROR");
            return AT_ERROR;
        }

        PS_MEM_CPY(aucWebPwdTmp, &stWebPwd, sizeof(stWebPwd));

        /* ���벻ƥ�� */
        if (0 != VOS_StrCmp(aucWebPwdTmp,(VOS_CHAR*)gastAtParaList[1].aucPara))
        {
            return AT_ERROR;
        }
    }
    else
    {
        /* ��ȡWEBPWD��Ӧ��NV�� */
        if (VOS_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_WEB_ADMIN_PASSWORD, gastAtParaList[1].aucPara, AT_WEBUI_PWD_MAX))
        {
            AT_WARN_LOG("AT_SetWebPwdPara:WRITE NV ERROR");
            return AT_ERROR;
        }
    }

    return AT_OK;
}
VOS_UINT32  AT_SetSdloadPara(VOS_UINT8 ucIndex)
{

#if (FEATURE_ON == FEATURE_LTE)
    return AT_SetLteSdloadPara(ucIndex);
#else
    VOS_UINT32                          ulRet;

    /* 1. ����Ϣ��C��ָʾʹ�����������ģʽ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_SDLOAD_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_SetSdloadPara: MN_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* 2. ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SDLOAD_SET;
    return AT_WAIT_ASYNC_RETURN;

#endif
}


VOS_UINT32 AT_SetProdNamePara(VOS_UINT8 ucIndex)
{
    TAF_AT_PRODUCT_ID_STRU              stProductId;
    VOS_UINT32                          ulProductIdLen;
    VOS_UINT32                          ulRet;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    PS_MEM_SET(&stProductId,0,sizeof(TAF_AT_PRODUCT_ID_STRU));

    /* ��NV50048�ж�ȡ��Ʒ���� */
    /* ��ȡNV��en_NV_Item_PRODUCT_ID*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_PRODUCT_ID,
                    &stProductId,
                    sizeof(stProductId.ulNvStatus) + sizeof(stProductId.aucProductId));

    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_SetProdNamePara: Fail to read en_NV_Item_PRODUCT_ID");
        return AT_ERROR;
    }


    /*��Ʒ����д��NV���У������AT_PRODUCT_NAME_MAX_NUM 30�������ض�*/
    ulProductIdLen
        = (gastAtParaList[0].usParaLen > AT_PRODUCT_NAME_MAX_NUM) ? AT_PRODUCT_NAME_MAX_NUM:gastAtParaList[0].usParaLen;

    PS_MEM_SET(stProductId.aucProductId, 0, sizeof(stProductId.aucProductId));
    PS_MEM_CPY(stProductId.aucProductId, gastAtParaList[0].aucPara, (VOS_UINT16)ulProductIdLen);

    stProductId.ulNvStatus = VOS_TRUE;

    /* д��NV */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_PRODUCT_ID,
                        &stProductId,
                        sizeof(stProductId.ulNvStatus) + sizeof(stProductId.aucProductId)))
    {
        AT_ERR_LOG("AT_SetProdNamePara:Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}


VOS_UINT32  At_SendContinuesWaveOnToHPA(
    VOS_UINT8                           ucCtrlType,
    VOS_UINT16                          usPower
)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usMask;

    /* ����AT_HPA_RF_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendContinuesWaveOnToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstMsg,0x00,sizeof(AT_HPA_RF_CFG_REQ_STRU));

    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = DSP_PID_WPHY;
    pstMsg->ulLength        = ulLength;

    /* ��д��Ϣ�� */
    pstMsg->usMsgID = ID_AT_HPA_RF_CFG_REQ;

    /* Tx Cfg */
    usMask =  W_RF_MASK_TX_TXONOFF | W_RF_MASK_TX_POWER;
    pstMsg->stRfCfgPara.sTxPower = (VOS_INT16)usPower;

    /* ��λ��ʶ�������� */
    pstMsg->stRfCfgPara.usMask      = usMask;
    pstMsg->stRfCfgPara.usTxAFCInit = W_AFC_INIT_VALUE;

    /* �򿪵����ź� */
    pstMsg->stRfCfgPara.usTxEnable = ucCtrlType;

    if ( VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendContinuesWaveOnToHPA: Send msg fail!");
        return AT_FAILURE;
    }
    return AT_SUCCESS;
}


VOS_UINT32 AT_SetFwavePara(VOS_UINT8 ucIndex)
{
    /* WIFI*/
    VOS_CHAR                        acCmd[200] = {0};

#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
        || (AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atSetFWAVEPara(ucIndex);
    }
#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if (AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atSetFWAVEPara(ucIndex);
    }
#endif

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������������ȷ����������������ͺͲ��ι��� */
    if (gucAtParaIndex != 2)
    {
        return AT_ERROR;
    }

    /* Ŀǰ��������ֻ֧�����õ���*/
    if (gastAtParaList[0].ulParaValue > 7)
    {
        return AT_ERROR;
    }

    /* ���������ڷ�����ģʽ��ʹ�� */
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_ERROR;
    }

    /* WIFI*/
    if (AT_RAT_MODE_WIFI == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        /*WIFIδEnableֱ�ӷ���ʧ��*/
        if(VOS_FALSE == (VOS_UINT32)WIFI_GET_STATUS())
        {
            return AT_ERROR;
        }

        /*��WIFI���͵��������ź�����*/
        VOS_sprintf(acCmd,"athtestcmd -ieth0 --tx sine --txpwr %d", gastAtParaList[1].ulParaValue/100);

        WIFI_TEST_CMD(acCmd);

        return AT_OK;
    }


    /* �����ñ����ڱ��ر���
       AT^FDAC���õ�FDACֵ��AT^FWAVE���õ�powerֵ��ʾ�ĺ�����ͬ��ȡ�����õ�ֵ
       ����ֵ��0.01Ϊ��λ������DSP��ֵ���10������AT����Ҫ����ֵ�ٳ�10*/
    g_stAtDevCmdCtrl.usPower    = (VOS_UINT16)(gastAtParaList[1].ulParaValue/10);
    g_stAtDevCmdCtrl.bPowerFlag = VOS_TRUE;
    g_stAtDevCmdCtrl.bFdacFlag  = VOS_FALSE;
    /* ��¼��type��Ϣ����ת��ΪG������ʹ�õ�TxMode�����������㷢��ID_AT_GHPA_RF_TX_CFG_REQʱЯ�� */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        g_stAtDevCmdCtrl.usTxMode = 1;
    }
    else
    {
        g_stAtDevCmdCtrl.usTxMode = 0;
    }


    /* WCDMA */
    if (AT_RAT_MODE_WCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        /* ��WDSP���Ϳ��ص����źŵ�ԭ������ */
        if (AT_FAILURE == At_SendContinuesWaveOnToHPA(WDSP_CTRL_TX_ONE_TONE, g_stAtDevCmdCtrl.usPower))
        {
            return AT_ERROR;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_FWAVE;
        g_stAtDevCmdCtrl.ucIndex = ucIndex;

        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }

    return AT_OK;

}

/*****************************************************************************
 �� �� ��  : AT_SetApRptSrvUrlPara
 ��������  : ����XML Reporting������URL
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��11��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetApRptSrvUrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApRptSrvUrl[AT_AP_XML_RPT_SRV_URL_LEN + 1];
    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (1 != gucAtParaIndex )
    {
        return AT_ERROR;
    }

    /* URLΪ�ջ��߳��ȳ���127*/
    if ((0 == gastAtParaList[0].usParaLen) || (gastAtParaList[0].usParaLen > AT_AP_XML_RPT_SRV_URL_LEN))
    {
        return AT_ERROR;
    }

    PS_MEM_SET(aucApRptSrvUrl, 0, AT_AP_XML_RPT_SRV_URL_LEN + 1);
    PS_MEM_CPY(aucApRptSrvUrl, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    /* дNV:en_NV_Item_AP_RPT_SRV_URL*/
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_AP_RPT_SRV_URL,
                        aucApRptSrvUrl,
                        AT_AP_XML_RPT_SRV_URL_LEN + 1))
    {
        AT_ERR_LOG("AT_SetApRptSrvUrlPara:Write NV fail");
        return AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "^APRPTSRVURLNTY");

        return AT_OK;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SetApXmlInfoTypePara
 ��������  : ����XML Reporting��Ϣ����
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��08��11��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetApXmlInfoTypePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApXmlInfoType[AT_AP_XML_RPT_INFO_TYPE_LEN + 1];

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (1 != gucAtParaIndex )
    {
        return AT_ERROR;
    }

    /* INFO TYPEΪ�ջ��߳��ȳ���127*/
    if ((0 == gastAtParaList[0].usParaLen) || (gastAtParaList[0].usParaLen > AT_AP_XML_RPT_INFO_TYPE_LEN))
    {
        return AT_ERROR;
    }

    PS_MEM_SET(aucApXmlInfoType, 0, AT_AP_XML_RPT_INFO_TYPE_LEN + 1);
    PS_MEM_CPY(aucApXmlInfoType, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    /* дNV:en_NV_Item_AP_XML_INFO_TYPE*/
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_AP_XML_INFO_TYPE,
                        aucApXmlInfoType,
                        AT_AP_XML_RPT_INFO_TYPE_LEN + 1))
    {
        AT_ERR_LOG("AT_SetApXmlInfoTypePara:Write NV fail");
        return AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "^APXMLINFOTYPENTY");

        return AT_OK;
    }
}


VOS_UINT32 AT_SetApXmlRptFlagPara(VOS_UINT8 ucIndex)
{
    TAF_AT_NVIM_AP_XML_RPT_FLG_STRU     stApXmlRptFlg;
    VOS_UINT32                          ulNvLength;

    ulNvLength = 0;
    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (1 != gucAtParaIndex )
    {
        return AT_ERROR;
    }

    stApXmlRptFlg.ucApXmlRptFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* дNV:en_NV_Item_AP_XML_RPT_FLAG*/
    NV_GetLength(en_NV_Item_AP_XML_RPT_FLAG, &ulNvLength);
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_AP_XML_RPT_FLAG,
                        &stApXmlRptFlg,
                        ulNvLength))
    {
       AT_ERR_LOG("AT_SetApXmlRptFlagPara:Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }
}



VOS_UINT32 AT_SetFastDormPara(VOS_UINT8 ucIndex)
{
    AT_RABM_FASTDORM_PARA_STRU          stFastDormPara;
    VOS_UINT32                          ulRslt;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �ڶ�������Ϊ�գ�����дĬ��ֵ */
    if (0 == gastAtParaList[1].usParaLen)
    {
        /* ��дĬ��ֵ5S */
        gastAtParaList[1].ulParaValue = AT_FASTDORM_DEFAULT_TIME_LEN;
    }

    stFastDormPara.enFastDormOperationType = gastAtParaList[0].ulParaValue;
    stFastDormPara.ulTimeLen = gastAtParaList[1].ulParaValue;

#if (FEATURE_ON == FEATURE_LTE)
    AT_SetLFastDormPara(ucIndex);
#endif

    /* ��AT�ںϰ汾�ϣ������Ľӿ�Ϊֱ�ӷ���Ϣ���������ֱ�ӷ�����Ϣ��RABM */
    ulRslt = AT_SndSetFastDorm(gastAtClientTab[ucIndex].usClientId,
                               gastAtClientTab[ucIndex].opId,
                               &stFastDormPara);
    if (VOS_OK == ulRslt)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FASTDORM_SET;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


VOS_UINT32 AT_SetMemInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ������� */
    if( (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
     || (gucAtParaIndex > 1) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϣ��C�˻�ȡ MEMINFO ��Ϣ, gastAtParaList[0].ulParaValue ��Ϊ��ѯ������ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_MEMINFO_QRY_REQ,
                                   &(gastAtParaList[0].ulParaValue),
                                   sizeof(gastAtParaList[0].ulParaValue),
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryMemInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MEMINFO_READ;
    return AT_WAIT_ASYNC_RETURN;

}

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 �� �� ��  : AT_SetRplmnStub
 ��������  : ��RPLMN���д�׮�Ա�GTR��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��18��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  AT_SetRplmnStub( VOS_UINT8 ucIndex )
{
    TAF_PLMN_ID_STRU                    stPlmnId;
    VOS_UINT32                          ulLai;
    VOS_UINT32                          ulRac;


    /* ��������ȷ,
    0:��ʾ��Ҫ����L��RPLMN
    1:��ʾ��Ҫ����GU��RPLMN
    */
    if ( (0 != gastAtParaList[0].ulParaValue)
      && (1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��Ҫ����PLMN ID��ֵ */
    if ( (5 != gastAtParaList[1].usParaLen)
       && (6 != gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* Mcc */
    if(AT_FAILURE == At_String2Hex(gastAtParaList[1].aucPara,3,&stPlmnId.Mcc))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    /* Mnc */
    if(AT_FAILURE == At_String2Hex(&gastAtParaList[1].aucPara[3],gastAtParaList[1].usParaLen-3,&stPlmnId.Mnc))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    stPlmnId.Mcc |= 0xFFFFF000;
    stPlmnId.Mnc |= (0xFFFFFFFF << ((gastAtParaList[1].usParaLen-3)*4));

    /* lai */
    ulLai = 0x0001;
    if (4 == gastAtParaList[2].usParaLen)
    {
        if(AT_FAILURE == At_String2Hex(gastAtParaList[2].aucPara, 4, &ulLai))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /*rac  */
    ulRac = 0x01;
    if (2 == gastAtParaList[3].usParaLen)
    {
        if(AT_FAILURE == At_String2Hex(gastAtParaList[3].aucPara, 2, &ulRac))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    /* ��Ҫ����L��RPLMN */
    if ( 0 == gastAtParaList[0].ulParaValue )
    {
        NAS_SetLteRplmnId(&stPlmnId, ulLai,ulRac);
    }
    else
    {
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetCsUnAvailPlmnStub
 ��������  : ��LTE��CS������������д�׮�Ա�GTR��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��25��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetCsUnAvailPlmnStub( VOS_UINT8 ucIndex )
{
    TAF_PLMN_ID_STRU                    stPlmnId;


    /* ��������ȷ,
    0:��ʾ��Ҫɾ��CS����������
    1:��ʾ��Ҫ����CS����������
    */
    if ( (0 != gastAtParaList[0].ulParaValue)
      && (1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��Ҫ����PLMN ID��ֵ */
    if ( (5 != gastAtParaList[1].usParaLen)
       && (6 != gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* Mcc */
    if(AT_FAILURE == At_String2Hex(gastAtParaList[1].aucPara,3,&stPlmnId.Mcc))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    /* Mnc */
    if(AT_FAILURE == At_String2Hex(&gastAtParaList[1].aucPara[3],gastAtParaList[1].usParaLen-3,&stPlmnId.Mnc))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    stPlmnId.Mcc |= 0xFFFFF000;
    stPlmnId.Mnc |= (0xFFFFFFFF << ((gastAtParaList[1].usParaLen-3)*4));

    /* ��Ҫ����L��CS���������� */
    if (VOS_OK == NAS_SetCsUnAvailPlmnId(gastAtParaList[0].ulParaValue, &stPlmnId))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : AT_SetForbRoamTaStub
 ��������  : ��LTE�½�ֹ����TA���д�׮�Ա�GTR��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��25��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetForbRoamTaStub( VOS_UINT8 ucIndex )
{
    /* ��������ȷ,
    0:��ʾ��Ҫɾ����ֹ����TA
    1:��ʾ��Ҫ������ֹ����TA
    */
    if ( (0 != gastAtParaList[0].ulParaValue)
      && (1 != gastAtParaList[0].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��Ҫ����L�Ľ�ֹ����TA */
    if (VOS_OK == NAS_SetForbRoamTa(gastAtParaList[0].ulParaValue))
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32  AT_SetTinTypeStub( VOS_UINT8 ucIndex )
{
    if (gucAtParaIndex > 1)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����TIN���� */
    NAS_SetTinType(gastAtParaList[0].ulParaValue);

    return AT_OK;
}
VOS_UINT32  AT_SetPsRegisterContainDrxStub( VOS_UINT8 ucIndex )
{
    if (gucAtParaIndex > 1)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

    NAS_SetPsRegContainDrx(gastAtParaList[0].ulParaValue);

    return AT_OK;
}


VOS_UINT32  AT_SetPsBearIsrFlgStub( VOS_UINT8 ucIndex )
{
    if (gucAtParaIndex > 3)
    {
        return  AT_CME_INCORRECT_PARAMETERS;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ����usapi ��Ӧ��pdp����ISR����ǰ����Ļ�����ISR����󼤻�� */
    NAS_SetPsBearerIsrFlg(gastAtParaList[0].ulParaValue,
                          gastAtParaList[1].ulParaValue,
                          gastAtParaList[2].ulParaValue);
#endif

    return AT_OK;
}
VOS_UINT32 AT_SetImsRatStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                               ucLteImsSupportFlg;
    VOS_UINT8                                               ucLteEmsSupportFlg;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������ LTE IMS�Ƿ�֧�� */
    ucLteImsSupportFlg       = gastAtParaList[0].ulParaValue;

    /* �ڶ������� LTE EMS�Ƿ�֧�� */
    ucLteEmsSupportFlg    = gastAtParaList[1].ulParaValue;

    NAS_SetLteImsSupportFlag(ucLteImsSupportFlg, ucLteEmsSupportFlg);

    return AT_OK;

}



VOS_UINT32 AT_SetImsCapabilityStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                               ucVoiceCallOnImsSupportFlg;
    VOS_UINT8                                               ucVideoCallOnImsSupportFlg;
    VOS_UINT8                                               ucSmsOnImsSupportFlg;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 3)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ��������ʾvoice call�Ƿ�֧�� 0:��֧��;1:֧�� */
    ucVoiceCallOnImsSupportFlg      = gastAtParaList[0].ulParaValue;

    /* �ڶ���������ʾvideo call�Ƿ�֧�� 0:��֧��;1:֧�� */
    ucVideoCallOnImsSupportFlg      = gastAtParaList[1].ulParaValue;

    /* ������������ʾsms�Ƿ�֧�� 0:��֧��;1:֧�� */
    ucSmsOnImsSupportFlg            = gastAtParaList[2].ulParaValue;

    NAS_SetImsCapabilitySupportFlag(ucVoiceCallOnImsSupportFlg, ucVideoCallOnImsSupportFlg, ucSmsOnImsSupportFlg);

    return AT_OK;

}
VOS_UINT32 AT_SetDomainStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                               ucVoiceDomain;
    VOS_UINT8                                               ucSmsDomain;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������ voice domainʱ��0:CS ONLY; 1:IMS PS ONLY; 2:CS PREFERRED; 3:IMS PS PREFERRED */
    ucVoiceDomain   = gastAtParaList[0].ulParaValue;

    /* �ڶ������� sms domainʱ��  0:NOT USE SMS OVER IP;    1:PREFERR TO USE SMS OVER IP */
    ucSmsDomain    = gastAtParaList[1].ulParaValue;

    NAS_SetPreferDomain(ucVoiceDomain, ucSmsDomain);

    return AT_OK;

}



VOS_UINT32 AT_SetCmdImsRoamingStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucImsRoamingFlag;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ����֧�ֲ��� */
    ucImsRoamingFlag   = gastAtParaList[0].ulParaValue;

    NAS_SetImsRoaming(ucImsRoamingFlag);

    return AT_OK;
}
VOS_UINT32 AT_SetCmdRedailStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallRedialImsToCs;
    VOS_UINT8                           ucSmsRedialImsToCs;
    VOS_UINT8                           ucSsRedialImsToCs;
    VOS_UINT8                           ucCallRedialCsToIms;
    VOS_UINT8                           ucSmsRedialCsToIms;
    VOS_UINT8                           ucSsRedialCsToIms;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 7)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* IMS��CS���л����ز����� */
    ucCallRedialImsToCs = gastAtParaList[0].ulParaValue;

    /* IMS��CS���Ż����ز����� */
    ucSmsRedialImsToCs  = gastAtParaList[1].ulParaValue;

    /* IMS��CS���任���ز����� */
    ucSsRedialImsToCs   = gastAtParaList[2].ulParaValue;

    /* CS��IMS���л����ز����� */
    ucCallRedialCsToIms = gastAtParaList[3].ulParaValue;

    /* CS��IMS���Ż����ز����� */
    ucSmsRedialCsToIms  = gastAtParaList[4].ulParaValue;

    /* CS��IMS���任���ز����� */
    ucSsRedialCsToIms   = gastAtParaList[5].ulParaValue;

    NAS_SetRedialCfg(ucCallRedialImsToCs, ucSmsRedialImsToCs, ucSsRedialImsToCs,
                     ucCallRedialCsToIms, ucSmsRedialCsToIms, ucSsRedialCsToIms);

    return AT_OK;
}



VOS_UINT32 AT_SetImsVoiceInterSysLauEnableStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucForceLauFlag;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ����֧�ֲ��� */
    ucForceLauFlag   = gastAtParaList[0].ulParaValue;

    NAS_SetImsVoiceInterSysLauEnable(ucForceLauFlag);

    return AT_OK;
}
VOS_UINT32 AT_SetImsVoiceMMEnableStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucImsVoiceMMEnableFlag;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ����֧�ֲ��� */
    ucImsVoiceMMEnableFlag   = gastAtParaList[0].ulParaValue;

    NAS_SetImsVoiceMMEnableFlg(ucImsVoiceMMEnableFlag);

    return AT_OK;
}
VOS_UINT32 AT_SetHighRatPlmnSearchActiveStub(VOS_UINT8 ucFlag)
{
    VOS_UINT8                           ucHighRatPlmnSearchActiveFlg;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ����֧�ֲ��� */
    ucHighRatPlmnSearchActiveFlg   = gastAtParaList[0].ulParaValue;

    NAS_SetHighRatHPLMNSearchActiveFlg(ucHighRatPlmnSearchActiveFlg);

    return AT_OK;
}
VOS_UINT32 AT_SetCmdImsUssdStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucImsUssdFlag;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ����֧�ֲ��� */
    ucImsUssdFlag   = gastAtParaList[0].ulParaValue;

    NAS_SetImsUssd(ucImsUssdFlag);

    return AT_OK;
}

#endif
VOS_UINT32 AT_SetDnsQueryPara(VOS_UINT8 ucIndex)
{

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��APSģ�鷢��ִ�����������Ϣ */
    if ( VOS_OK != TAF_PS_GetDynamicDnsInfo(WUEPS_PID_AT,
                                                gastAtClientTab[ucIndex].usClientId,
                                                gastAtClientTab[ucIndex].opId,
                                                (VOS_UINT8)gastAtParaList[0].ulParaValue))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DNSQUERY_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_SetMemStatusPara(VOS_UINT8 ucIndex)
{
    MN_MSG_SET_MEMSTATUS_PARM_STRU      stMemStatus;

    /* ��ʼ�� */
    PS_MEM_SET(&stMemStatus, 0x00, sizeof(MN_MSG_SET_MEMSTATUS_PARM_STRU));

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 1 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ò��� */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        stMemStatus.enMemFlag = MN_MSG_MEM_FULL_SET;
    }
    else
    {
        stMemStatus.enMemFlag = MN_MSG_MEM_FULL_UNSET;
    }

    /* ����MN��ϢAPI�������������MSGģ�� */
    if ( MN_ERR_NO_ERROR != MN_MSG_SetMemStatus(gastAtClientTab[ucIndex].usClientId,
                                                gastAtClientTab[ucIndex].opId,
                                                &stMemStatus))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt  = AT_CMD_CSASM_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetApRptPortSelectPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucClientIndex;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulPortSel1;
    VOS_UINT32                          ulPortSel2;

    ulPortSel1 = 0;
    ulPortSel2 = 0;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if ( gucAtParaIndex > 2 )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if ( 0 == gastAtParaList[0].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ( 0 == gastAtParaList[1].usParaLen )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ�û����õĲ��� */
    /* AT�Ķ˿ڸ�������32��������������32bit�Ĳ�����ʾ��Ӧ�Ķ˿��Ƿ����������ϱ� */
    AT_String2Hex(gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen, &ulPortSel1);

    AT_String2Hex(gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen, &ulPortSel2);

    for (ucClientIndex = 0; ucClientIndex < AT_CLIENT_BUTT ; ucClientIndex++)
    {
        pstAtClientCtx = AT_GetClientCtxAddr(ucClientIndex);

        if (ucClientIndex >= 32)
        {
            if ((1 << (ucClientIndex - 32)) == (ulPortSel2 & (1 << (ucClientIndex - 32))))
            {
                pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;
            }
            else
            {
                pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_FALSE;
            }
        }
        else
        {
            if ((1 << ucClientIndex) == (ulPortSel1 & (1 << ucClientIndex)))
            {
                pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_TRUE;
            }
            else
            {
                pstAtClientCtx->stClientConfiguration.ucReportFlg = VOS_FALSE;
            }
        }
    }

    return AT_OK;
}




VOS_UINT32 At_SetGpioPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucGroup;
    VOS_UINT8                           ucPin;
    VOS_UINT8                           ucValue;

    /* �����֧��HSIC���ԣ���֧��GPIO�л� */
    if (BSP_MODULE_SUPPORT != DRV_GET_HSIC_SUPPORT())
    {
        return AT_ERROR;
    }

    /* para too many */
    if (gucAtParaIndex > 3)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucGroup = (VOS_UINT8)(gastAtParaList[0].ulParaValue / 100);
    ucPin   = (VOS_UINT8)(gastAtParaList[0].ulParaValue % 100);

    if (VOS_OK != DRV_GPIO_SET(ucGroup, ucPin, (VOS_UINT8)gastAtParaList[1].ulParaValue))
    {
        return AT_ERROR;
    }

    VOS_TaskDelay(gastAtParaList[2].ulParaValue);

    /* ���GPIO���ú���Ҫ����ƽ��ת���� */
    ucValue = (gastAtParaList[1].ulParaValue == DRV_GPIO_HIGH)?DRV_GPIO_LOW:DRV_GPIO_HIGH;


    if (VOS_OK != DRV_GPIO_SET(ucGroup, ucPin, ucValue))
    {
        return AT_ERROR;
    }

    return AT_OK;
}
VOS_UINT32 At_SetUsbSwitchPara (VOS_UINT8 ucIndex)
{
    VOS_INT                          iResult;
    VOS_UINT8                        ucUsbStatus;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* para too many */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    ucUsbStatus = USB_SWITCH_OFF;

    if (VOS_OK != DRV_USB_PHY_SWITCH_GET(&ucUsbStatus))
    {
        return AT_ERROR;
    }

    /* ����Modem��USB���� */
    if(AT_USB_SWITCH_SET_VBUS_VALID == gastAtParaList[0].ulParaValue)
    {
        if (USB_SWITCH_ON != ucUsbStatus)
        {
            iResult = DRV_USB_PHY_SWITCH_SET(USB_SWITCH_ON);
        }
        else
        {
            return AT_OK;
        }
    }
    else if(AT_USB_SWITCH_SET_VBUS_INVALID == gastAtParaList[0].ulParaValue)
    {
        if (USB_SWITCH_OFF != ucUsbStatus)
        {
            iResult = DRV_USB_PHY_SWITCH_SET(USB_SWITCH_OFF);
        }
        else
        {
            return AT_OK;
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (iResult == VOS_OK)
    {
        return At_PortSwitchSndMsg(ucUsbStatus);
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : At_PortSwitchSndMsg
 ��������  : USBSWITCH�����л�OM�˿���Ϣ����
 �������  : TAF_UINT32 ulSwitchMode
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012-03-05
    �޸�����   : ��ά�ɲ���Ŀ����
*****************************************************************************/
TAF_UINT32 At_PortSwitchSndMsg (TAF_UINT32 ulSwitchMode)
{
    OM_PORT_SWITCH_MSG_STRU             *pMsg;

    pMsg = (OM_PORT_SWITCH_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_AT,
                                                   sizeof(OM_PORT_SWITCH_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        return AT_ERROR;
    }

    pMsg->ulReceiverPid = ACPU_PID_OM;
    pMsg->ulMsgName     = (OM_AT_MSG_ENUM_UINT32)AT_OM_PORT_SWITCH;
    pMsg->ulSwitchMode  = (OM_PORT_SWITCH_MODE_ENUM_UINT32)ulSwitchMode;

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        return AT_ERROR;
    }

    return AT_OK;
}



VOS_UINT32 AT_SetSARReduction(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;
	VOS_UINT16                              usUETestMode;

    VOS_UINT16                              usSarReduction;
    AT_MODEM_MT_INFO_CTX_STRU              *pstMtInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;
    VOS_UINT16                              usAntState;

	usUETestMode = 0;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_ERR_LOG("AT_SetSARReduction: Cmd Opt Type is wrong.");
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡNV���ж��Ƿ�Ϊ����ģʽ����NV��ֻ��һ�� */
    ulResult = NV_ReadEx(MODEM_ID_0,
                         en_NV_Item_RF_SAR_BACKOFF_TESTMODE,
                         &usUETestMode,
                         sizeof(usUETestMode));

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_SetSARReduction:Read NV fail");
        return AT_ERROR;
    }


    enModemId  = MODEM_ID_0;

    ulResult   = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulResult)
    {
        AT_ERR_LOG("AT_SetSARReduction:Get modem id fail");

        return AT_ERROR;
    }

    pstMtInfoCtx = AT_GetModemMtInfoCtxAddrFromModemId(enModemId);

    ulResult = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulResult)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    if ((AT_ANT_CONDUCTION_MODE == usAntState) && (VOS_TRUE != usUETestMode))
    {
        AT_ERR_LOG("AT_SetSARReduction: Test mode wrong");
        return AT_ERROR;
    }

    usSarReduction = (VOS_UINT16)gastAtParaList[0].ulParaValue;
    pstMtInfoCtx->usSarReduction = usSarReduction;

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      DRV_AGENT_SARREDUCTION_SET_REQ,
                                      &usSarReduction,
                                      sizeof(usSarReduction),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_ERR_LOG("AT_SetSARReduction: Send Msg Fail");

        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : At_SetScidPara
 ��������  : SCID�����ú���
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : TAF_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��24��
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_UINT32 At_SetScidPara(TAF_UINT8 ucIndex)
{
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_ICC_ID,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ICCID_READ;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}



/*****************************************************************************
 �� �� ��  : ToBase64Char
 ��������  : BASE64�ַ�ת��
 �������  : const VOS_UCHAR code6bit  �������ַ�
 �������  : ��
 �� �� ֵ  : VOS_UCHAR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��29��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UCHAR ToBase64Char(const VOS_UCHAR code6bit)
{
    /* [ 0..25] => ['A'..'Z'] */
    if (code6bit<26)
    {
        return (VOS_UCHAR)(code6bit+'A');
    }

    /* [26..51] => ['a'..'z'] */
    else if (code6bit<52)
    {
        return (VOS_UCHAR)(code6bit+('a'-26));
    }

    /* [52..61] => ['0'..'9'] */
    else if (code6bit<62)
    {
        return (VOS_UCHAR)(code6bit-52+'0');
    }

    /* 62 => '+' */
    else if (code6bit==62)
    {
        return '+';
    }

    /* 63 => */
    else
    {
        return '/';
    }
}


/*****************************************************************************
 �� �� ��  : AtBase64Encode
 ��������  : BASE64���뺯��
 �������  : const VOS_VOID* pdata       ԭ���ݵ�ַ
             const VOS_UINT32 data_size  ԭ�����ֽڴ�С
             VOS_VOID* out_pcode         ���������ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��29��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AtBase64Encode(const VOS_VOID* pdata,const VOS_UINT32 data_size,VOS_VOID* out_pcode)
{
    const VOS_UCHAR* input      =(const unsigned char*)pdata;
    const VOS_UCHAR* input_end  =&input[data_size];
    VOS_UCHAR*       output     =(unsigned char*)out_pcode;
    VOS_UINT32       bord_width = 0;

    for(; input+2 < input_end; input += 3, output += 4 )
    {
        output[0] = ToBase64Char(   input[0] >> 2 );
        output[1] = ToBase64Char( ((input[0] << 4) | (input[1] >> 4)) & 0x3F );
        output[2] = ToBase64Char( ((input[1] << 2) | (input[2] >> 6)) & 0x3F );
        output[3] = ToBase64Char(   input[2] & 0x3F);
    }

    if(input_end > input)
    {
        bord_width = (VOS_UINT32)(input_end-input);
        if ( bord_width == 1 )
        {
            output[0] = ToBase64Char(   input[0] >> 2 );
            output[1] = ToBase64Char(  (input[0] << 4) & 0x3F );
            output[2] = AT_BASE64_PADDING;
            output[3] = AT_BASE64_PADDING;
        }
        else if (bord_width==2)
        {
            output[0] = ToBase64Char(   input[0] >> 2 );
            output[1] = ToBase64Char( ((input[0] << 4) | (input[1] >> 4)) & 0x3F );
            output[2] = ToBase64Char(  (input[1] << 2) & 0x3F );
            output[3] = AT_BASE64_PADDING;
        }
        else
        {
        }
    }
}


/*****************************************************************************
 �� �� ��  : AtBase64Decode
 ��������  : Base64���뺯��
 �������  : const void* pcode                     ����Դ����
             const unsigned long code_size         ����Դ���ݳ���
             void* out_pdata                       ����Ŀ������
             const unsigned long data_size         ����Ŀ��������󳤶�
             unsigned long* out_pwrited_data_size  ����Ŀ�����ݳ���
 �������  : ��
 �� �� ֵ  : unsigned long
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��3��
    �޸�����   : �����ɺ���

*****************************************************************************/
unsigned long AtBase64Decode(const void* pcode,const unsigned long code_size,void* out_pdata,
                            const unsigned long data_size,unsigned long* out_pwrited_data_size)
{
    const unsigned char DECODE_DATA_MAX = 64-1;
    const unsigned char DECODE_PADDING  = DECODE_DATA_MAX+2;
    const unsigned char DECODE_ERROR    = DECODE_DATA_MAX+3;
    static unsigned char BASE64_DECODE[256];
    static VOS_BOOL initialized=VOS_FALSE;
    unsigned int code0;
    unsigned int code1;
    unsigned int code2;
    unsigned int code3;
    unsigned long bord_width;
    const unsigned char* input_last_fast_node;
    unsigned long output_size;
    unsigned char* output;
    const unsigned char* input;
    unsigned long code_node;
    unsigned long i;

    if(!initialized)
    {
        for(i=0;i<256;++i)
        {
            BASE64_DECODE[i]=DECODE_ERROR;
        }
        for(i='A';i<='Z';++i)
        {
            BASE64_DECODE[i]=(unsigned char)(i-'A');
        }
        for(i='a';i<='z';++i)
        {
            BASE64_DECODE[i]=(unsigned char)(i-'a'+26);
        }
        for(i='0';i<='9';++i)
        {
            BASE64_DECODE[i]=(unsigned char)(i-'0'+26*2);
        }
        BASE64_DECODE['+']=26*2+10;
        BASE64_DECODE['/']=26*2+10+1;
        BASE64_DECODE['=']=DECODE_PADDING;
        initialized=VOS_TRUE;
    }
    *out_pwrited_data_size=0;
    code_node=code_size/4;
    if ((code_node*4)!=code_size)
    {
        return b64Result_CODE_SIZE_ERROR;
    }
    else if (code_node==0)
    {
        return b64Result_OK;
    }
    else
    {
    }

    /* code_node>0 */
    input=(const unsigned char*)pcode;
    output=(unsigned char*)out_pdata;
    output_size=code_node*3;

    if (input[code_size-2]==AT_BASE64_PADDING)
    {
        if (input[code_size-1]!=AT_BASE64_PADDING)
        {
            return b64Result_CODE_ERROR;
        }

        output_size-=2;
    }
    else if (input[code_size-1]==AT_BASE64_PADDING)
    {
        --output_size;
    }
    else
    {
    }

    if (output_size>data_size)
    {
        return b64Result_DATA_SIZE_SMALLNESS;
    }
    input_last_fast_node=&input[output_size/3*4];

    for(;input<input_last_fast_node;input+=4,output+=3)
    {
        code0=BASE64_DECODE[input[0]];
        code1=BASE64_DECODE[input[1]];
        code2=BASE64_DECODE[input[2]];
        code3=BASE64_DECODE[input[3]];
        if ( ((code0|code1)|(code2|code3)) <= DECODE_DATA_MAX )
        {
            output[0]=(unsigned char)((code0<<2) + (code1>>4));
            output[1]=(unsigned char)((code1<<4) + (code2>>2));
            output[2]=(unsigned char)((code2<<6) + code3);
        }
        else
        {
            return b64Result_CODE_ERROR;
        }
    }
    bord_width=output_size%3;
    if (bord_width==1)
    {
        code0=BASE64_DECODE[input[0]];
        code1=BASE64_DECODE[input[1]];
        if ((code0|code1) <= DECODE_DATA_MAX)
        {
            output[0]=(unsigned char)((code0<<2) + (code1>>4));
        }
        else
        {
            return b64Result_CODE_ERROR;
        }
    }
    else if (bord_width==2)
    {
        code0=BASE64_DECODE[input[0]];
        code1=BASE64_DECODE[input[1]];
        code2=BASE64_DECODE[input[2]];
        if ((code0|code1|code2) <= DECODE_DATA_MAX)
        {
            output[0]=(unsigned char)((code0<<2) + (code1>>4));
            output[1]=(unsigned char)((code1<<4) + (code2>>2));
        }
        else
        {
            return b64Result_CODE_ERROR;
        }
    }
    else
    {
    }
    *out_pwrited_data_size=output_size;
    return b64Result_OK;
}
VOS_UINT32 AT_RsfrSimLockProc(VOS_UINT8* pgcSrcData, VOS_UINT16* pusLen)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulPlmnIdx;
    VOS_UINT32                          ulRsltChkPlmnBegin;
    VOS_UINT32                          ulRsltChkPlmnEnd;
    VOS_UINT32                          ulTotalPlmnNum;
    VOS_BOOL                            abPlmnValidFlg[TAF_MAX_SIM_LOCK_RANGE_NUM] = {VOS_FALSE};
    VOS_UINT8                           aucAsciiNumBegin[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];
    VOS_UINT8                           aucAsciiNumEnd[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return AT_ERROR;
    }

    ulTotalPlmnNum = 0;

    if (NV_ITEM_DEACTIVE == stSimLockPlmnInfo.ulStatus)
    {
        /* ״̬�Ǽ���ʱ����ʾPlmn����Ϊ0 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgcSrcData,
                                           (VOS_CHAR *)pgcSrcData, "%s%s:%d%s",
                                           gaucAtCrLf,"^SIMLOCK",ulTotalPlmnNum,gaucAtCrLf);

        *pusLen = usLength;
        return AT_OK;
    }

    /*  �ж�Plmn�Ŷ��Ƿ���Ч */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        ucMncLen = stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum;

        ulRsltChkPlmnBegin = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        ulRsltChkPlmnEnd = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        if ((AT_SUCCESS == ulRsltChkPlmnBegin)
         && (AT_SUCCESS == ulRsltChkPlmnEnd)
         && ((ucMncLen <= 3) && (ucMncLen >= 2)))
        {
            abPlmnValidFlg[i] = VOS_TRUE;
            ++ ulTotalPlmnNum;
        }
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgcSrcData,
                                       (VOS_CHAR *)pgcSrcData, "%s%s:%d%s",
                                       gaucAtCrLf,"^SIMLOCK",ulTotalPlmnNum,gaucAtCrLf);

    if (0 == ulTotalPlmnNum)
    {
        *pusLen = usLength;
        return AT_OK;
    }

    /* CustomInfoSetting ��������Ҫ��ĸ�ʽ */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgcSrcData,
                                (VOS_CHAR *)pgcSrcData + usLength,
                                "^SIMLOCK:");

    ulPlmnIdx = 0;
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (VOS_FALSE == abPlmnValidFlg[i])
        {
            continue;
        }

        ++ ulPlmnIdx;

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgcSrcData,
                                    (VOS_CHAR *)pgcSrcData + usLength,
                                    "%d,%d,%s,%s%s",
                                    ulPlmnIdx,
                                    stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum,
                                    aucAsciiNumBegin,
                                    aucAsciiNumEnd,
                                    gaucAtCrLf);
    }

    *pusLen = usLength;

    return AT_OK;
}



/*****************************************************************************
 �� �� ��  : AT_SetRsfrPara
 ��������  : ^RSFR�����(������ֻ֧�ֺ�CustomInfoSetting ���������Խӵ�ʵ��)
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��29��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetRsfrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength = 0;
    VOS_CHAR                            cName[AT_RSFR_RSFW_NAME_LEN + 1]       = {0};
    VOS_CHAR                            cSubName[AT_RSFR_RSFW_SUBNAME_LEN + 1] = {0};
    VOS_UINT8                          *pcRsfrSrcItem;
    VOS_CHAR                           *pcRsfrDstItem;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ����������Ϊ���� */
    if (gucAtParaIndex != 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������Ϊ�� */
    if ((0 == gastAtParaList[0].usParaLen)
        || (gastAtParaList[0].usParaLen > AT_RSFR_RSFW_NAME_LEN))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(cName, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    At_UpString((VOS_UINT8*)cName, gastAtParaList[0].usParaLen);

    if (gastAtParaList[1].usParaLen > AT_RSFR_RSFW_SUBNAME_LEN)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(cSubName, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);

    if(ERR_MSP_SUCCESS == AT_STRCMP(cName, "VERSION"))
    {
        if(TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                gastAtClientTab[ucIndex].opId,
                                                DRV_AGENT_VERSION_QRY_REQ,
                                                VOS_NULL_PTR,
                                                0,
                                                I0_WUEPS_PID_DRV_AGENT))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RSFR_VERSION_QRY;
            return AT_WAIT_ASYNC_RETURN;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else if(ERR_MSP_SUCCESS == AT_STRCMP(cName, "SIMLOCK"))
    {
        pcRsfrSrcItem = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_RSFR_RSFW_MAX_LEN);
        if (VOS_NULL_PTR == pcRsfrSrcItem )
        {
            return AT_ERROR;
        }

        PS_MEM_SET(pcRsfrSrcItem, 0, AT_RSFR_RSFW_MAX_LEN);

        ulRet = AT_RsfrSimLockProc(pcRsfrSrcItem, &usLength);
        if(AT_OK != ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pcRsfrSrcItem);
            return ulRet;
        }

        pcRsfrDstItem = (VOS_CHAR*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_RSFR_RSFW_MAX_LEN);
        if (VOS_NULL_PTR == pcRsfrDstItem )
        {
            PS_MEM_FREE(WUEPS_PID_AT, pcRsfrSrcItem);
            return AT_ERROR;
        }

        PS_MEM_SET(pcRsfrDstItem, 0, AT_RSFR_RSFW_MAX_LEN);

        /* �Ѵ�SIMLOCK�����ж������Ľ���ַ�����Ϊ����Դ */
        AtBase64Encode(pcRsfrSrcItem, usLength, pcRsfrDstItem);

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    "^RSFR:\"%s\",\"%s\",123,1,1,%s",
                                    cName, cSubName, gaucAtCrLf);

        gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                    "\"%s\"", pcRsfrDstItem);

        PS_MEM_FREE(WUEPS_PID_AT, pcRsfrSrcItem);
        PS_MEM_FREE(WUEPS_PID_AT, pcRsfrDstItem);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 �� �� ��  : AT_SetRsfrVersionCnf
 ��������  : ^RSFR�����ѯVERSION��Ϣ�ķ��صĴ���
 �������  : VOS_UINT8 ucData  pgucAtSndCodeAddr(����������ȫ�ֱ�����ַ)
             VOS_UINT32 ulLen  gstAtSendData.usBufLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��30��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_SetRsfrVersionCnf(VOS_UINT8 ucIndex, VOS_UINT8* pucData, VOS_UINT32 ulLen)
{
    VOS_UINT16 usLength;
    VOS_CHAR* pcRsfrItem = NULL;

    pcRsfrItem = (VOS_CHAR*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_RSFR_RSFW_MAX_LEN);
    if (VOS_NULL_PTR == pcRsfrItem )
    {
        return ;
    }

    PS_MEM_SET(pcRsfrItem, 0, AT_RSFR_RSFW_MAX_LEN);

    /* �Ѵ�SIMLOCK�����ж������Ľ���ַ�����Ϊ����Դ */
    AtBase64Encode(pucData, ulLen, pcRsfrItem);

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "^RSFR:\"VERSION\",\"111\",125,1,1,%s",
                                gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "\"%s\"", pcRsfrItem);

    gstAtSendData.usBufLen = usLength;

    At_FormatResultData(ucIndex, AT_OK);

    PS_MEM_FREE(WUEPS_PID_AT, pcRsfrItem);

    return ;
}


/*****************************************************************************
 �� �� ��  : AT_RsfwSimLockProc
 ��������  : ����SIMLOCK�ַ���������"AT"��":"->"="��"0"->"2"(CustomInfoSettingȱ��)
 �������  : VOS_UINT8 *pucData   ���������ַ���
             VOS_UINT16 usLen      ���������ַ�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��31��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID AT_RsfwSimLockProc(VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    VOS_UINT16 i = 0;
    VOS_UINT32 usNum = 0;

    /* ����AT�����ַ� */
    pucData[0] = 'A';
    pucData[1] = 'T';
    pucData[10] = '=';      /* ��ð�Ÿ�Ϊ�Ⱥ� */

    if(usLen < 13)
    {
        return ;
    }

    if(('1' == pucData[11]) && (',' == pucData[12]))
    {

        /* �����·����ַ�����MNC����������0����Ҫ��Ϊ2��3 */
        for(i = 11; i < usLen; i++)
        {
            if(',' == pucData[i])
            {
                usNum++;
                if(i+8 >= usLen)
                {
                    return ;
                }

                /* ͨ���ж�PLMN��λ����ȷ����2����3 */
                if((1 == (usNum%3)) && ('0' == pucData[i+1]) && (',' == pucData[i+2]))
                {
                    if(',' == pucData[i+8])
                    {
                        pucData[i+1] = '2';
                    }
                    else
                    {
                        pucData[i+1] = '3';
                    }
                }
            }
        }
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : AT_SetRsfwPara
 ��������  : ^RSFW�����(������ֻ֧�ֺ�CustomInfoSetting ���������Խӵ�ʵ��)
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��29��
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 AT_SetRsfwPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32  ulRet;
    VOS_UINT32  ulLength = 0;
    VOS_CHAR    cName[AT_RSFR_RSFW_NAME_LEN + 1]   = {0};
    VOS_UINT8*  pucRsfw  = NULL;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ����������Ϊ���� */
    if (gucAtParaIndex != 6)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������Ϊ�� */
    if ((0 == gastAtParaList[0].usParaLen)
        || (gastAtParaList[0].usParaLen > AT_RSFR_RSFW_NAME_LEN))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(cName, gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen);

    At_UpString((VOS_UINT8*)cName, gastAtParaList[0].usParaLen);

    /* CustomInfoSetting ��������ֻ������<name>�������������� */

    if(ERR_MSP_SUCCESS == AT_STRCMP(cName, "SIMLOCK"))
    {
        if(gastAtParaList[5].usParaLen > AT_PARA_MAX_LEN)
        {
            vos_printf("[AT_SetRsfwPara] : param 5 is too long : %d.\n", gastAtParaList[5].usParaLen);

            return AT_ERROR;
        }

        pucRsfw = (TAF_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_RSFR_RSFW_MAX_LEN);
        if (VOS_NULL_PTR == pucRsfw )
        {
            return AT_ERROR;
        }

        PS_MEM_SET(pucRsfw, 0, AT_RSFR_RSFW_MAX_LEN);

        /* ǰ�����ַ���������AT��Ȼ���͸�^SIMLOCK����Ĵ����������� */
        ulRet = AtBase64Decode(gastAtParaList[5].aucPara, gastAtParaList[5].usParaLen,
            &(pucRsfw[2]), (AT_RSFR_RSFW_MAX_LEN-2), &ulLength);
        if(b64Result_OK != ulRet)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);
            return AT_ERROR;
        }

        /* ������CustomInfoSetting���յ����ַ��� */
        AT_RsfwSimLockProc(pucRsfw, (VOS_UINT16)(ulLength + 2));

        ulRet = At_ProcSimLockPara(ucIndex, pucRsfw, (VOS_UINT16)(ulLength + 2));

        if(AT_SUCCESS != ulRet)
        {
            vos_printf("[AT_SetRsfwPara] : At_ProcSimLockPara failed %d.\n", ulRet);
        }

        PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

        /* AT_ERROR AT_OK��At_ProcSimLockPara�з��� */
        return AT_SUCCESS;
    }
#if (FEATURE_ON == FEATURE_VSIM)
    else if(VOS_OK == AT_STRCMP(cName, "VSIM"))
    {
        return At_DealRSFWVsim(ucIndex);
    }
#endif  /*(FEATURE_ON == FEATURE_VSIM)*/
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_SetHukPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    DRV_AGENT_HUK_SET_REQ_STRU          stHukSetReq;

    /* �ֲ�������ʼ�� */
    ulResult = VOS_NULL;
    usLength = gastAtParaList[0].usParaLen;
    PS_MEM_SET(&stHukSetReq, 0x00, sizeof(DRV_AGENT_HUK_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ��������������� */
    if (AT_HUK_PARA_LEN != usLength)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ַ�������ת��Ϊ���� */
    ulResult = At_AsciiNum2HexString(gastAtParaList[0].aucPara, &usLength);
    if ( (AT_SUCCESS != ulResult) || (DRV_AGENT_HUK_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    PS_MEM_CPY(stHukSetReq.aucHUK, gastAtParaList[0].aucPara, DRV_AGENT_HUK_LEN);

    /* ת���ɹ�, ���Ϳ����Ϣ��C��, ����HUK */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_HUK_SET_REQ,
                                      &stHukSetReq,
                                      sizeof(DRV_AGENT_HUK_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetHukPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HUK_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_DecodeFacAuthPubkeyPara(AT_FACAUTHPUBKEY_SET_REQ_STRU *pstFacAuthPubKey)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* �ֲ�������ʼ�� */
    ulResult = VOS_NULL;
    usLength = AT_FACAUTHPUBKEY_PARA_LEN;

    ulResult = At_AsciiNum2HexString(pstFacAuthPubKey->aucPubKey, &usLength);
    if ( (AT_SUCCESS != ulResult) || (DRV_AGENT_PUBKEY_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = AT_FACAUTHPUBKEY_SIGN_PARA_LEN;

    ulResult = At_AsciiNum2HexString(pstFacAuthPubKey->aucPubKeySign, &usLength);
    if ( (AT_SUCCESS != ulResult) || (DRV_AGENT_PUBKEY_SIGNATURE_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}
VOS_UINT32 AT_SetFacAuthPubkeyPara(
    VOS_UINT8                           ucIndex,
    AT_FACAUTHPUBKEY_SET_REQ_STRU      *pstFacAuthPubKey
)
{
    VOS_UINT32                              ulResult;
    DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU    stFacAuthPubkeySetReq;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stFacAuthPubkeySetReq, 0x00, sizeof(DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ���ַ�������ת��Ϊ���� */
    ulResult = AT_DecodeFacAuthPubkeyPara(pstFacAuthPubKey);
    if (AT_SUCCESS != ulResult)
    {
        return ulResult;
    }
    PS_MEM_CPY(stFacAuthPubkeySetReq.aucPubKey,
               pstFacAuthPubKey->aucPubKey,
               DRV_AGENT_PUBKEY_LEN);
    PS_MEM_CPY(stFacAuthPubkeySetReq.aucPubKeySign,
               pstFacAuthPubKey->aucPubKeySign,
               DRV_AGENT_PUBKEY_SIGNATURE_LEN);

    /* ת���ɹ�, ���Ϳ����Ϣ��C��, ���ò��߹�Կ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_FACAUTHPUBKEY_SET_REQ,
                                      &stFacAuthPubkeySetReq,
                                      sizeof(DRV_AGENT_FACAUTHPUBKEY_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetFacAuthPubkeyPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����FACAUTHPUBKEY���⴦������Ҫ�ֶ�������ʱ��*/
    if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
    {
        AT_WARN_LOG("AT_SetFacAuthPubkeyPara: At_StartTimer fail.");
        return AT_ERROR;
    }

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FACAUTHPUBKEY_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetIdentifyStartPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���Ϳ����Ϣ��C��, �����Ȩ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_IDENTIFYSTART_SET_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetIdentifyStartPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IDENTIFYSTART_SET;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_SetIdentifyEndPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    DRV_AGENT_IDENTIFYEND_SET_REQ_STRU  stIdentifyEndSetReq;
    VOS_UINT16                          usLength;

    /* �ֲ�������ʼ�� */
    ulResult = VOS_NULL;
    usLength = gastAtParaList[0].usParaLen;
    PS_MEM_SET(&stIdentifyEndSetReq, 0x00, sizeof(DRV_AGENT_IDENTIFYEND_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (1 < gucAtParaIndex)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ��������������� */
    if (AT_RSA_CIPHERTEXT_PARA_LEN != usLength)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ַ�������ת��Ϊ���� */
    ulResult = At_AsciiNum2HexString(gastAtParaList[0].aucPara, &usLength);
    if ( (AT_SUCCESS != ulResult) || (DRV_AGENT_RSA_CIPHERTEXT_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    PS_MEM_CPY(stIdentifyEndSetReq.aucRsaText,
               gastAtParaList[0].aucPara,
               DRV_AGENT_RSA_CIPHERTEXT_LEN);

    /* ���Ϳ����Ϣ��C��, ��ɲ��߼�Ȩ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_IDENTIFYEND_SET_REQ,
                                      &stIdentifyEndSetReq,
                                      sizeof(DRV_AGENT_IDENTIFYEND_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetIdentifyEndPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IDENTIFYEND_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetSimlockDataWritePara(
    VOS_UINT8                           ucIndex,
    AT_SIMLOCKDATAWRITE_SET_REQ_STRU   *pstSimlockDataWrite
)
{
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU     stSimlockDataWriteSetReq;

    /* �ֲ�������ʼ�� */
    ulResult = VOS_NULL;
    usLength = AT_SIMLOCKDATAWRITE_PARA_LEN;
    PS_MEM_SET(&stSimlockDataWriteSetReq,
               0x00,
               sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ���ַ�������ת��Ϊ���� */
    ulResult = At_AsciiNum2HexString(pstSimlockDataWrite->aucCategoryData, &usLength);
    if ( (AT_SUCCESS != ulResult)
      || (DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    PS_MEM_CPY(stSimlockDataWriteSetReq.aucCategoryData,
               pstSimlockDataWrite->aucCategoryData,
               DRV_AGENT_SIMLOCKDATAWRITE_STRU_LEN);

    /* ת���ɹ�, ���Ϳ����Ϣ��C��, д�������������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ,
                                      &stSimlockDataWriteSetReq,
                                      sizeof(DRV_AGENT_SIMLOCKDATAWRITE_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetSimlockDataWritePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����SIMLOCKDATAWRITE���⴦������Ҫ�ֶ�������ʱ��*/
    if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
    {
        AT_WARN_LOG("AT_SetSimlockDataWritePara: At_StartTimer fail.");
        return AT_ERROR;
    }

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMLOCKDATAWRITE_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_CheckPhonePhyNumPara(DRV_AGENT_PH_PHYNUM_TYPE_ENUM_UINT8 *penSetType)
{
    /* <type>�������: ֧������������IMEI��SN������, ֱ�ӷ������������ʹ��� */
    /* ȫ����ʽ��Ϊ��д�ַ� */
    if (AT_FAILURE == At_UpString(gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen))
    {
        return AT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR;
    }

    if (0 == VOS_StrCmp((VOS_CHAR *)gastAtParaList[0].aucPara, "IMEI"))
    {
        *penSetType = DRV_AGENT_PH_PHYNUM_IMEI;
    }
    else if (0 == VOS_StrCmp((VOS_CHAR *)gastAtParaList[0].aucPara, "SN"))
    {
        *penSetType = DRV_AGENT_PH_PHYNUM_SN;
    }
    else
    {
        AT_NORM_LOG("AT_CheckPhonePhyNumPara: the type of physical is error.");
        return AT_PERSONALIZATION_PH_PHYNUM_TYPE_ERROR;
    }

    /* �������ȼ�� */
    if (AT_RSA_CIPHERTEXT_PARA_LEN != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}
VOS_UINT32 AT_SetPhonePhynumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulCheckParaRst;
    DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU  stPhonePhynumSetReq;
    VOS_UINT16                          usLength;

    /* �ֲ�������ʼ�� */
    ulResult        = VOS_NULL;
    ulCheckParaRst  = VOS_NULL;
    usLength        = gastAtParaList[1].usParaLen;
    PS_MEM_SET(&stPhonePhynumSetReq, 0x00, sizeof(DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (2 < gucAtParaIndex)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ������������ */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulCheckParaRst = AT_CheckPhonePhyNumPara(&(stPhonePhynumSetReq.enPhynumType));
    if (AT_SUCCESS != ulCheckParaRst)
    {
        return ulCheckParaRst;
    }

    /* ���ַ�������ת��Ϊ���� */
    ulResult = At_AsciiNum2HexString(gastAtParaList[1].aucPara, &usLength);
    if ( (AT_SUCCESS != ulResult) || (DRV_AGENT_RSA_CIPHERTEXT_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    PS_MEM_CPY(stPhonePhynumSetReq.aucPhynumValue,
               gastAtParaList[1].aucPara,
               DRV_AGENT_RSA_CIPHERTEXT_LEN);

    /* ���Ϳ����Ϣ��C��, ��ɲ��߼�Ȩ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONEPHYNUM_SET_REQ,
                                      &stPhonePhynumSetReq,
                                      sizeof(DRV_AGENT_PHONEPHYNUM_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetPhonePhynumPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONEPHYNUM_SET;
    return AT_WAIT_ASYNC_RETURN;

}



VOS_UINT32 AT_SetPortCtrlTmpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;
    DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU      stPortCtrlTmpSetReq;
    VOS_UINT8                               aucPara[AT_PORTCTRLTMP_PARA_LEN];

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stPortCtrlTmpSetReq, 0x00, sizeof(DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU));
    PS_MEM_SET(aucPara, 0x00, AT_PORTCTRLTMP_PARA_LEN);

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ��������������� */
    if (AT_PORTCTRLTMP_PARA_LEN != gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ĺϷ��Լ�飬����Ϊ16����0��-��9��ASCII�ַ�,������ASCII��ת��Ϊʮ�������� */
    ulResult = At_AsciiNum2Num(aucPara, gastAtParaList[0].aucPara, DRV_AGENT_PORT_PASSWORD_LEN);
    if ( AT_FAILURE == ulResult)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������ɹ�, ���Ϳ����Ϣ��C�� */
    PS_MEM_CPY(stPortCtrlTmpSetReq.aucPortPassword, aucPara, DRV_AGENT_PORT_PASSWORD_LEN);
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PORTCTRLTMP_SET_REQ,
                                      &stPortCtrlTmpSetReq,
                                      sizeof(DRV_AGENT_PORTCTRLTMP_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetPortCtrlTmpPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PORTCTRLTMP_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetPortAttribSetPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU    stPortAttribSetReq;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stPortAttribSetReq, 0x00, sizeof(DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ��������������� */
    if ( (AT_PORTATTRIBSET_PARA_ONOFF_LEN != gastAtParaList[0].usParaLen)
      || (AT_RSA_CIPHERTEXT_PARA_LEN      != gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ò�ѯ�˿���״̬ */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        stPortAttribSetReq.enPortStatus = DRV_AGENT_PORT_STATUS_OFF;
    }
    else
    {
        stPortAttribSetReq.enPortStatus = DRV_AGENT_PORT_STATUS_ON;
    }

    /* ���ַ�������ת��Ϊ���� */
    usLength = gastAtParaList[1].usParaLen;
    ulResult = At_AsciiNum2HexString(gastAtParaList[1].aucPara, &usLength);
    if ( (TAF_SUCCESS != ulResult) || (DRV_AGENT_RSA_CIPHERTEXT_LEN != usLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(stPortAttribSetReq.aucPortPassword,
               gastAtParaList[1].aucPara,
               DRV_AGENT_RSA_CIPHERTEXT_LEN);
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PORTATTRIBSET_SET_REQ,
                                      &stPortAttribSetReq,
                                      sizeof(DRV_AGENT_PORTATTRIBSET_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetPortAttribSetPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PORTATTRIBSET_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SetApSimStPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;
    DRV_AGENT_AP_SIMST_SET_REQ_STRU         stApSimStSetReq;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stApSimStSetReq, 0x00, sizeof(DRV_AGENT_AP_SIMST_SET_REQ_STRU));

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_ERROR;
    }

     /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_ERROR;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    /* ��������Ϊ1ʱ��Ŀǰ��֧�֣�ֱ�ӷ���OK */
    if (1 == gastAtParaList[0].ulParaValue)
    {
        stApSimStSetReq.ulUsimState = DRV_AGENT_USIM_OPERATE_ACT;
    }
    else
    {
        stApSimStSetReq.ulUsimState = DRV_AGENT_USIM_OPERATE_DEACT;
    }

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_AP_SIMST_SET_REQ,
                                      &stApSimStSetReq,
                                      sizeof(DRV_AGENT_AP_SIMST_SET_REQ_STRU),
                                      I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetApSimStPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APSIMST_SET;

    return AT_WAIT_ASYNC_RETURN;

}


VOS_VOID AT_ConvertMccToNasType(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                         *pulNasMcc
)
{
    VOS_UINT32                          aulTmp[3];
    VOS_UINT32                          i;

    *pulNasMcc  = 0;

    for (i = 0; i < 3 ; i++ )
    {
        aulTmp[i]       = ulMcc & 0x0f;
        ulMcc         >>=  4;
    }

    *pulNasMcc  = aulTmp[2]
             |((VOS_UINT32)aulTmp[1] << 8)
             |((VOS_UINT32)aulTmp[0] << 16);

}


VOS_UINT32 AT_SetNvmEccNumPara(
    VOS_UINT8                           ucIndex
)
{
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU stEccNumReq;
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulTemp;
    VOS_UINT32                          ulMcc;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_ERR_LOG("AT_SetNvmEccNumSetPara: Cmd Opt Type is wrong.");
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex != 6)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����Ϸ��Լ��, index > total��Ϊ������Ч */
    if (gastAtParaList[0].ulParaValue > gastAtParaList[1].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��Ϣ��ʼ�� */
    VOS_MemSet(&stEccNumReq, 0, sizeof(MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU));

    /* ��ECC NUMת��ΪBCD�� */
    if (MN_ERR_NO_ERROR != AT_AsciiNumberToBcd((TAF_CHAR*)&gastAtParaList[2].aucPara[0],
                                                stEccNumReq.stEccNum.aucBcdNum,
                                                &stEccNumReq.stEccNum.ucNumLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulTemp  = 0;
    ulTemp |= (gastAtParaList[5].ulParaValue % 10);
    ulTemp |= (((gastAtParaList[5].ulParaValue /10) % 10) << 4);
    ulTemp |= (((gastAtParaList[5].ulParaValue /100) % 10) << 8);

    /* ��MCCת��ΪNAS�ṹ */
    AT_ConvertMccToNasType(ulTemp, &ulMcc);

    stEccNumReq.ucIndex         = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stEccNumReq.ucTotal         = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stEccNumReq.ucCategory      = (VOS_UINT8)gastAtParaList[3].ulParaValue;
    stEccNumReq.ucSimPresent    = (VOS_UINT8)gastAtParaList[4].ulParaValue;
    stEccNumReq.ulMcc           = ulMcc;

    /* ������Ϣ */
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_CUSTOM_ECC_NUM_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   0,
                                  (MN_CALL_APP_REQ_PARM_UNION*)&stEccNumReq);

    if (MN_ERR_NO_ERROR != ulRst)
    {
        AT_WARN_LOG("AT_SetNvmEccNumPara: MN_CALL_SendAppRequest fail.");
        return AT_ERROR;
    }

    /* ���ý���ֱ�ӷ���OK */
    return AT_OK;
}


VOS_UINT32 AT_SetCposPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* Ϊ׼�������XML���������ڴ� */
    pstAgpsCtx->stXml.pcXmlTextHead = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_XML_MAX_LEN);
    if (VOS_NULL_PTR == pstAgpsCtx->stXml.pcXmlTextHead)
    {
        AT_ERR_LOG("AT_SetCposPara: Memory malloc failed!");
        return AT_ERROR;
    }
    pstAgpsCtx->stXml.pcXmlTextCur  = pstAgpsCtx->stXml.pcXmlTextHead;

    /* �л�ΪAGPS XML��������ģʽ */
    At_SetMode(ucIndex, AT_CMD_MODE, AT_XML_MODE);

    /* ������ʾXML��������״̬ */
    return AT_WAIT_XML_INPUT;
}
VOS_UINT32 AT_SetCposrPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pstAgpsCtx->enCposrReport = (AT_CPOSR_FLG_ENUM_UNIT8)gastAtParaList[0].ulParaValue;

    return AT_OK;
}
VOS_UINT32 AT_SetXcposrPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if( gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����ģʽ */
    pstAgpsCtx->enXcposrReport = (AT_XCPOSR_FLG_ENUM_UNIT8)gastAtParaList[0].ulParaValue;
    return AT_OK;
}


VOS_UINT32 AT_SetCgpsClockPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_AGPS)
    struct clk                             *pClk;
#endif

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if( gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

#if (FEATURE_ON == FEATURE_AGPS)
    pClk = clk_get(NULL, "clk_gps");

    if (1 == gastAtParaList[0].ulParaValue)
    {
        if (!clk_enable(pClk))
        {
            AT_ERR_LOG("AT_SetCgpsClockPara: clk_enable failed!");
        }
    }
    else if (0 == gastAtParaList[0].ulParaValue)
    {
        clk_disable(pClk);
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_OK;
#else
    return AT_OK;
#endif
}

/*****************************************************************************
 �� �� ��  : AT_SetGpsInfoPara
 ��������  : (AT^CGPSINFO)AP����GPS��Ϣ
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��08��18��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetGpsInfoPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_SetLogCfgPara(VOS_UINT8 ucIndex)
{
    NV_SOCP_SDLOG_CFG_STRU              stSocpCfg;
    VOS_UINT32                          ulResult;

    /* ������^logcfg=1ʱ�����������������ᵱ��0��������SOCP�޷�������ˮ��Ϊ0K�Ļ��棬���µ���᲻ͣ��λ */
    if (((1 == gucAtParaIndex) && (0 == gastAtParaList[0].ulParaValue)) || (4 == gucAtParaIndex))
    {
        /* �����Ϸ�������ִ�� */
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stSocpCfg.ulSocpDelayWriteFlg   = gastAtParaList[0].ulParaValue;
    stSocpCfg.ulGuSocpLevel         = gastAtParaList[1].ulParaValue;
    stSocpCfg.ulLSocpLevel          = gastAtParaList[2].ulParaValue;
    stSocpCfg.ulTimeOutValue        = gastAtParaList[3].ulParaValue;

    BSP_SOCP_RefreshSDLogCfg(stSocpCfg.ulTimeOutValue);

    ulResult = NV_WriteEx(MODEM_ID_0, en_NV_ID_SOCP_SDLOG_CFG, (VOS_VOID *)(&stSocpCfg), sizeof(NV_SOCP_SDLOG_CFG_STRU));

    if (VOS_OK != ulResult)
    {
        return AT_ERROR;
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetLogSavePara
 ��������  : (AT^LOGSAVE)AP���ý�A��SOCPĿ��BUFFER�л�������ݱ��浽AP��
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  :
 �޸���ʷ      :
  1.��    ��   : 2012��12��18��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetLogSavePara(VOS_UINT8 ucIndex)
{
    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* SOCP�Ľӿ���V9R1����OAM�ṩ��ʹ����ԭ�� */
    if (BSP_OK != BSP_SOCP_EncDstBufFlush())
    {
        return AT_ERROR;
    }

    return AT_OK;
}

VOS_UINT32 AT_SetApSecPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucCmdPara,
    VOS_UINT16                          usParaLen )
{
    VOS_UINT32                          ulResult;
    AT_MTA_APSEC_REQ_STRU               stApSecSetReq;

    /* ��ʼ�� */
    PS_MEM_SET(&stApSecSetReq, 0x00, sizeof(AT_MTA_APSEC_REQ_STRU));

    /* ���ַ�������ת��Ϊ���� */
    ulResult = At_AsciiNum2HexString(pucCmdPara, &usParaLen);
    if (AT_SUCCESS != ulResult)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stApSecSetReq.ulSPLen = (VOS_UINT32)usParaLen;
    PS_MEM_CPY(stApSecSetReq.aucSecPacket, pucCmdPara, stApSecSetReq.ulSPLen);

    /* ���Ϳ����ϢID_AT_MTA_APSEC_SET_REQ��C�� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_APSEC_SET_REQ,
                                      &stApSecSetReq,
                                      sizeof(AT_MTA_APSEC_REQ_STRU),
                                      I0_UEPS_PID_MTA);
    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetApSecPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APSEC_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : AT_SetIsdbSimAccessPara
 ��������  : (AT^CISA)ISDB͸��APDU��(U)SIM��
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú��� :
 �������� :

 �޸���ʷ      :
  1.��    ��   : 2012��08��28��
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 AT_SetCISAPara(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulLengthValue,
    VOS_UINT8                          *pucCommand,
    VOS_UINT16                          usCommandLength)
{
    SI_PIH_ISDB_ACCESS_COMMAND_STRU     stCommand;
    VOS_UINT16                          usCommandHexLen;

    /* ��ʼ�� */
    PS_MEM_SET(&stCommand, 0x00, sizeof(stCommand));

    /* ������� */
    if ( (ulLengthValue > (SI_APDU_MAX_LEN * 2))
       ||(ulLengthValue != usCommandLength) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* <command>��ASCII�룬�����������HEX��ת�� */
    usCommandHexLen =   usCommandLength;
    if (AT_FAILURE == At_AsciiNum2HexString(pucCommand, &usCommandHexLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����<length> */
    stCommand.ulLen = usCommandHexLen;

    /* ����<command> */
    PS_MEM_CPY((TAF_VOID *)stCommand.aucCommand, (TAF_VOID *)pucCommand, (VOS_UINT16)stCommand.ulLen);

    /* ִ��������� */
    if(AT_SUCCESS == SI_PIH_IsdbAccessReq(gastAtClientTab[ucIndex].usClientId, 0, &stCommand))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CISA_SET;

        /* �������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("AT_SetCISAPara: SI_PIH_IsdbAccessReq fail.");

        return AT_ERROR;
    }
}

VOS_UINT32 AT_SetCmutPara(VOS_UINT8 ucIndex)
{
    APP_VC_MUTE_STATUS_ENUM_UINT8        enMuteStatus;

    /* �޲��� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������ߴ��� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ�������, ��ȡҪ���õľ���״̬ */
    if (0 == gastAtParaList[0].ulParaValue)
    {
        enMuteStatus = APP_VC_MUTE_STATUS_UNMUTED;
    }
    else
    {
        enMuteStatus = APP_VC_MUTE_STATUS_MUTED;
    }

    /* ִ��������� */
    if (VOS_OK != APP_VC_SetMuteStatus(gastAtClientTab[ucIndex].usClientId,
                                       0,
                                       enMuteStatus))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMUT_SET;

    /* �������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : AT_SetSimlockUnlockPara
 ��������  : ^SIMLOCKUNLOCK�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��19��
    �޸�����   : STK�������Լ�DCM���󿪷���Ŀ�����ɺ���

*****************************************************************************/
VOS_UINT32  AT_SetSimlockUnlockPara( VOS_UINT8 ucIndex )
{
    VOS_UINT32                          ulResult;
    AT_MTA_SIMLOCKUNLOCK_REQ_STRU       stSimlockUnlockSetReq;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������������������� */
    if ( (0 == gastAtParaList[0].usParaLen)
      || (AT_SIMLOCKUNLOCK_PWD_PARA_LEN != gastAtParaList[1].usParaLen)
      || (gastAtParaList[0].ulParaValue > AT_MTA_PERS_CATEGORY_SERVICE_PROVIDER) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stSimlockUnlockSetReq, 0, sizeof(AT_MTA_SIMLOCKUNLOCK_REQ_STRU));
    stSimlockUnlockSetReq.enCategory = (AT_MTA_PERS_CATEGORY_ENUM_UINT8)gastAtParaList[0].ulParaValue;

    /* ����ĺϷ��Լ�飬����Ϊ16����0��-��9��ASCII�ַ�,������ASCII��ת��Ϊʮ�������� */
    ulResult = At_AsciiNum2Num(stSimlockUnlockSetReq.aucPassword,
                               gastAtParaList[1].aucPara,
                               gastAtParaList[1].usParaLen);
    if ( AT_SUCCESS != ulResult)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���Ϳ����Ϣ��C��, ������������ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_SIMLOCKUNLOCK_SET_REQ,
                                      &stSimlockUnlockSetReq,
                                      sizeof(AT_MTA_SIMLOCKUNLOCK_REQ_STRU),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetSimlockUnlockPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMLOCKUNLOCK_SET;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_FillApdsPara(
    VOS_UINT8                           ucIndex,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* Ĭ�������ʹ��CCA���õ�Ĭ��ֵ */
    pstOrigParam->enCallMode  = pstSsCtx->enCModType;
    pstOrigParam->stDataCfg   = pstSsCtx->stCbstDataCfg;
    pstOrigParam->enClirCfg   = pstSsCtx->ucClirType;
    pstOrigParam->stCugCfg    = pstSsCtx->stCcugCfg;

    /* ����<dial_string> */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return VOS_ERR;
    }
    else
    {
        if (VOS_OK !=  AT_FillCalledNumPara(gastAtParaList[0].aucPara,
                                            gastAtParaList[0].usParaLen,
                                            pstOrigParam))
        {
            return VOS_ERR;
        }
    }

    /* ��鱻�к����ӵ�ַ�ĳ��� */
    if (gastAtParaList[1].usParaLen > MN_CALL_MAX_SUBADDR_INFO_LEN)
    {
        return VOS_ERR;
    }

    /* ����<sub_string> */
    if (0 != gastAtParaList[1].usParaLen)
    {
        pstOrigParam->stSubaddr.IsExist       = VOS_TRUE;

        /* ƫ���� = �ӵ�ַ����ĳ��� + Octet3�ĳ���*/
        pstOrigParam->stSubaddr.LastOctOffset = (VOS_UINT8)gastAtParaList[1].usParaLen + sizeof(pstOrigParam->stSubaddr.Octet3);
        pstOrigParam->stSubaddr.Octet3        = (0x80 | (MN_CALL_SUBADDR_NSAP << 4));
        PS_MEM_CPY(pstOrigParam->stSubaddr.SubAddrInfo,
                   gastAtParaList[1].aucPara,
                   gastAtParaList[1].usParaLen);
    }

    /* ����<I><G><call_type>���� */
    if (0 != gastAtParaList[2].usParaLen)
    {
        if (0 == gastAtParaList[2].ulParaValue)
        {
            pstOrigParam->enClirCfg = AT_CLIR_INVOKE;
        }
        else if (1 == gastAtParaList[2].ulParaValue)
        {
            pstOrigParam->enClirCfg = AT_CLIR_SUPPRESS;
        }
        else
        {
            return VOS_ERR;
        }
    }

    if (0 != gastAtParaList[3].usParaLen)
    {
        pstOrigParam->stCugCfg.bEnable    = gastAtParaList[3].ulParaValue;
    }

    if (0 != gastAtParaList[4].usParaLen)
    {
        pstOrigParam->enCallType          = (VOS_UINT8)gastAtParaList[4].ulParaValue;
    }

    return VOS_OK;
}


VOS_UINT32 AT_SetApdsPara(VOS_UINT8 ucIndex)
{
    MN_CALL_ORIG_PARAM_STRU             stOrigParam;
    VOS_UINT32                          ulRelt;

    /* ��ʼ�� */
    PS_MEM_SET(&stOrigParam, 0x00, sizeof(MN_CALL_ORIG_PARAM_STRU));

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

     /* �������� */
    if (gucAtParaIndex > 5)
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��鲢��д����Ĳ��� */
    ulRelt = AT_FillApdsPara(ucIndex, &stOrigParam);
    if (VOS_OK != ulRelt)
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϣԭ�� */
    if (AT_SUCCESS == MN_CALL_Orig(gastAtClientTab[ucIndex].usClientId,
                                  0,
                                  &gastAtClientTab[ucIndex].AtCallInfo.CallId,
                                  &stOrigParam))
    {
        if (MN_CALL_TYPE_VOICE == stOrigParam.enCallType)
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_VOICE_CALL_SET;
        }
        else
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_D_CS_DATA_CALL_SET;
        }
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_UNKNOWN);
        return AT_ERROR;
    }
}


VOS_UINT32 AT_SetClprPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���Ϳ����ϢAT_CALL_CLPR_GET_REQ��C��,  */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_CLPR_GET_REQ,
                                      gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      (MN_CALL_ID_T)gastAtParaList[0].ulParaValue,
                                      VOS_NULL_PTR);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetClprPara: MN_CALL_SendAppRequest fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLPR_SET;

    return AT_WAIT_ASYNC_RETURN;

}



VOS_UINT32 AT_SetCLteRoamAllowPara(VOS_UINT8 ucIndex)
{
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU  stNvimLteRoamAllowedFlg;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (1 != gucAtParaIndex)
    {
        return AT_ERROR;
    }

    stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;
    stNvimLteRoamAllowedFlg.aucReserve[0]       = 0x00;

    /* дNV:en_NV_Item_Lte_Internation_Roam_Config,
       ��NV�ĽṹΪ NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU, ֻд��1���ֽ� */
    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_Lte_Internation_Roam_Config,
                          &(stNvimLteRoamAllowedFlg),
                          sizeof(VOS_UINT16)))
    {
        AT_ERR_LOG("AT_SetCLteRoamAllowPara:Write NV fail");
        return AT_ERROR;
    }
    else
    {
        return AT_OK;
    }

}



VOS_UINT32 At_SetWlthresholdcfgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                                              ulResult;
    AT_MTA_RESEL_OFFSET_CFG_SET_NTF_STRU                    stReselOffsetCfgNtf;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stReselOffsetCfgNtf, 0, sizeof(stReselOffsetCfgNtf));

    stReselOffsetCfgNtf.ucOffsetFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ������ϢAT_MTA_RESEL_OFFSET_CFG_SET_REQ_STRU*/
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_RESEL_OFFSET_CFG_SET_NTF,
                                      &stReselOffsetCfgNtf,
                                      sizeof(stReselOffsetCfgNtf),
                                      I0_UEPS_PID_MTA);

#if  (FEATURE_ON == FEATURE_LTE)
    /*Lʹ�ò���*/
    At_SetLWThresholdCfgPara(ucIndex);
#endif

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetWlthresholdcfgPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    return AT_OK;

}



VOS_UINT32 At_SetSwverPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ����Ϣ��C�˻�ȡ���״̬�͵�ص��� */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_SWVER_SET_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_SetSwverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SWVER_SET;
    return AT_WAIT_ASYNC_RETURN;

}

/*****************************************************************************
 �� �� ��  : AT_SetCbgPara
 ��������  : ^CBG�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��28��
    �޸�����   : ˫ͨ��������HIFI�л���
                 ���� 0 :ǰ̨ģʽ������ 1 :��̨ģʽ
*****************************************************************************/
VOS_UINT32 AT_SetCbgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    APP_VC_MSG_ENUM_U16                 usMsgName;

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡ�·�VC����Ϣͷ���� */
    if ( 0 == gastAtParaList[0].ulParaValue )
    {
        usMsgName = APP_VC_MSG_SET_FOREGROUND_REQ;
    }
    else
    {
        usMsgName = APP_VC_MSG_SET_BACKGROUND_REQ;
    }

    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      usMsgName,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetCbgPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBG_SET;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_SndMtaBodySarPara(
    VOS_UINT8                           ucIndex,
    MTA_BODY_SAR_STATE_ENUM_UINT16      enBodySarState,
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT32                          ulResult;
    AT_MTA_BODY_SAR_SET_REQ_STRU        stBodySarSetReq;

    PS_MEM_SET(&stBodySarSetReq, 0, sizeof(stBodySarSetReq));

    /* �����Ϣ�ṹ�� */
    stBodySarSetReq.enState = enBodySarState;
    PS_MEM_CPY(&stBodySarSetReq.stBodySARPara, pstBodySarPara, sizeof(MTA_BODY_SAR_PARA_STRU));

    /* ������ϢAT_MTA_BODY_SAR_SET_REQ_STRU */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_BODY_SAR_SET_REQ,
                                      &stBodySarSetReq,
                                      sizeof(AT_MTA_BODY_SAR_SET_REQ_STRU),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SndMtaBodySarPara: AT_FillAndSndAppReqMsg fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_SetBodySarOnPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �ж�BODYSAR��ǰ״̬ */
    if (g_enAtBodySarState == gastAtParaList[0].ulParaValue)
    {
        return AT_OK;
    }

    /* ��ȡBODYSAR NV�� */
    ulResult = NV_ReadEx(MODEM_ID_0,
                         en_NV_Item_BODY_SAR_PARA,
                         &stBodySarPara,
                         sizeof(MTA_BODY_SAR_PARA_STRU));

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_SetBodySarOnPara: Read NV fail");
        return AT_ERROR;
    }

    /* ������Ϣ��MTA */
    ulResult = AT_SndMtaBodySarPara(ucIndex,
                                    (MTA_BODY_SAR_STATE_ENUM_UINT16)gastAtParaList[0].ulParaValue,
                                    &stBodySarPara);
    if (VOS_OK != ulResult)
    {
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_BODYSARON_SET;
    return AT_WAIT_ASYNC_RETURN;
}
VOS_UINT32 AT_CheckBodySarWcdmaPara(
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara)
{
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulLen;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));

    /* ����������� */
    if ( (gucAtParaIndex < 1)
      || (gucAtParaIndex > AT_BODYSARWCDMA_MAX_PARA_NUM) )
    {
        AT_WARN_LOG1("AT_CheckBodySarWcdmaPara: Para Num Incorrect!", gucAtParaIndex);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������Ϊ1ʱ������Ĭ��ֵ */
    if (1 == gucAtParaIndex)
    {
        ulLen = VOS_StrLen(AT_RF_BAND_ANY_STR);
        PS_MEM_CPY(gastAtParaList[1].aucPara,
                   AT_RF_BAND_ANY_STR,
                   ulLen);
        gastAtParaList[1].aucPara[ulLen]    = '\0';
        gastAtParaList[1].usParaLen         = (VOS_UINT16)ulLen;
        gucAtParaIndex                      = 2;
    }

    /* ������������Ϊż�� */
    if (0 != (gucAtParaIndex % 2))
    {
        AT_WARN_LOG1("AT_CheckBodySarWcdmaPara: Para Num is not Even!", gucAtParaIndex);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡWCDMA Band����ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_WG_RF_MAIN_BAND,
                           &stWGBand,
                           sizeof(stWGBand)))
    {
        AT_ERR_LOG("AT_CheckBodySarWcdmaPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ѭ�����BandƵ���Ƿ�֧�֣����������ṹ�� */
    pstBodySarWcdmaPara->ucParaNum = 0;
    for (ucLoop = 0; ucLoop < (gucAtParaIndex / 2); ucLoop++)
    {
        /* ���û������Ƶ�β�����16�����ַ���ת��Ϊ���� */
        if (AT_SUCCESS != At_String2Hex(gastAtParaList[ucLoop * 2 + 1].aucPara,
                                        gastAtParaList[ucLoop * 2 + 1].usParaLen,
                                        &gastAtParaList[ucLoop * 2 + 1].ulParaValue))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ����û������������BandƵ�Σ����滻Ϊ��ǰ֧�ֵ�BandƵ��ֵ */
        if (AT_RF_BAND_ANY == gastAtParaList[ucLoop * 2 + 1].ulParaValue)
        {
            gastAtParaList[ucLoop * 2 + 1].ulParaValue = stWGBand.unWcdmaBand.ulBand;
        }

        /* ����û������Ƶ�ε�ǰ�Ƿ�֧�֣������֧�ַ��ز������� */
        if (0 != (gastAtParaList[ucLoop * 2 + 1].ulParaValue & (~stWGBand.unWcdmaBand.ulBand)))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        pstBodySarWcdmaPara->asPower[pstBodySarWcdmaPara->ucParaNum]    = (VOS_INT16)gastAtParaList[ucLoop * 2].ulParaValue;
        pstBodySarWcdmaPara->aulBand[pstBodySarWcdmaPara->ucParaNum]    = gastAtParaList[ucLoop * 2 + 1].ulParaValue;
        pstBodySarWcdmaPara->ucParaNum++;
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_FillBodySarWcdmaPara(
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara,
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT8                           ucLoop1;
    MTA_WCDMA_BAND_ENUM_UINT16          enLoop2;
    VOS_UINT8                           ucLoop3;

    /* �����������еĲ��� */
    for (ucLoop1 = 0; ucLoop1 < pstBodySarWcdmaPara->ucParaNum; ucLoop1++)
    {
        /* ����WCDMA Band�������� */
        for (enLoop2 = MTA_WCDMA_I_2100; enLoop2 < MTA_WCDMA_BAND_BUTT; enLoop2++)
        {
            if (0 == (pstBodySarWcdmaPara->aulBand[ucLoop1] & (0x00000001 << (enLoop2 - 1))))
            {
                continue;
            }

            for (ucLoop3 = 0; ucLoop3 < pstBodySarPara->usWBandNum; ucLoop3++)
            {
                if (enLoop2 == pstBodySarPara->astWBandPara[ucLoop3].enBand)
                {
                    break;
                }
            }

            if (ucLoop3 == pstBodySarPara->usWBandNum)
            {
                /* ������W Band���֧�ָ�������ظ�ʧ�� */
                if (MTA_BODY_SAR_WBAND_MAX_NUM <= pstBodySarPara->usWBandNum)
                {
                    AT_ERR_LOG("AT_FillBodySarWcdmaPara: Too Many W Band!");
                    return VOS_ERR;
                }

                pstBodySarPara->usWBandNum++;
            }

            pstBodySarPara->astWBandPara[ucLoop3].enBand = enLoop2;
            pstBodySarPara->astWBandPara[ucLoop3].sPower = pstBodySarWcdmaPara->asPower[ucLoop1];
        }
    }

    return VOS_OK;
}
VOS_UINT32 AT_SetBodySarWcdmaPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarWcdmaPara, 0, sizeof(stBodySarWcdmaPara));

    /* ��������Ч�� */
    ulResult = AT_CheckBodySarWcdmaPara(&stBodySarWcdmaPara);
    if (AT_SUCCESS != ulResult)
    {
        return ulResult;
    }

    /* ��NV���ж�ȡBody SAR��������ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_BODY_SAR_PARA,
                           &stBodySarPara,
                           sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_SetBodysarWcdmaPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ��WCDMA��Ƶ�β�����䵽Body SAR�����ṹ���� */
    if (VOS_OK != AT_FillBodySarWcdmaPara(&stBodySarWcdmaPara, &stBodySarPara))
    {
        return AT_ERROR;
    }

    /* ��Body SAR��������ֵ���浽NV */
    if (NV_OK != NV_WriteEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &(stBodySarPara),
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_SetBodysarWcdmaPara: Write NV fail!");
        return AT_ERROR;
    }

    /* �����ǰ������Body SAR���ܣ���֪ͨ�������µ�Body SAR���� */
    if (MTA_BODY_SAR_ON == g_enAtBodySarState)
    {
        if (VOS_OK != AT_SndMtaBodySarPara(ucIndex,
                                           g_enAtBodySarState,
                                           &stBodySarPara))
        {
            AT_WARN_LOG("AT_SetBodySarWcdmaPara: AT_SndMtaBodySarPara fail!");
        }
    }

    return AT_OK;
}
VOS_UINT32 AT_GetGsmBandCapa(VOS_UINT32 *pulGBand)
{
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));
    *pulGBand = 0;

    /* ��NV���ж�ȡ����֧�ֵ�Ƶ�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_WG_RF_MAIN_BAND,
                           &stWGBand,
                           sizeof(stWGBand)))
    {
        AT_ERR_LOG("AT_GetGsmBandCapa: Read NV fail!");
        return VOS_ERR;
    }

    if (VOS_TRUE == stWGBand.unGsmBand.BitBand.BandGsm850)
    {
        *pulGBand |= MTA_BODY_SAR_GBAND_GPRS_850_MASK;
        *pulGBand |= MTA_BODY_SAR_GBAND_EDGE_850_MASK;
    }

    if ( (VOS_TRUE == stWGBand.unGsmBand.BitBand.BandGsmP900)
      || (VOS_TRUE == stWGBand.unGsmBand.BitBand.BandGsmR900)
      || (VOS_TRUE == stWGBand.unGsmBand.BitBand.BandGsmE900) )
    {
        *pulGBand |= MTA_BODY_SAR_GBAND_GPRS_900_MASK;
        *pulGBand |= MTA_BODY_SAR_GBAND_EDGE_900_MASK;
    }

    if (VOS_TRUE == stWGBand.unGsmBand.BitBand.BandGsm1800)
    {
        *pulGBand |= MTA_BODY_SAR_GBAND_GPRS_1800_MASK;
        *pulGBand |= MTA_BODY_SAR_GBAND_EDGE_1800_MASK;
    }

    if (VOS_TRUE == stWGBand.unGsmBand.BitBand.BandGsm1900)
    {
        *pulGBand |= MTA_BODY_SAR_GBAND_GPRS_1900_MASK;
        *pulGBand |= MTA_BODY_SAR_GBAND_EDGE_1900_MASK;
    }

    return VOS_OK;
}
VOS_UINT32 AT_CheckBodySarGsmPara(
    AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara)
{
    VOS_UINT32                          ulGBand;
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulLen;

    ulGBand         = 0;

    /* ����������� */
    if ( (gucAtParaIndex < 1)
      || (gucAtParaIndex > AT_BODYSARGSM_MAX_PARA_NUM) )
    {
        AT_WARN_LOG1("AT_CheckBodySarGsmPara: Para Num Incorrect!", gucAtParaIndex);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������Ϊ1ʱ������Ĭ��ֵ */
    if (1 == gucAtParaIndex)
    {
        ulLen = VOS_StrLen(AT_RF_BAND_ANY_STR);
        PS_MEM_CPY(gastAtParaList[1].aucPara,
                   AT_RF_BAND_ANY_STR,
                   ulLen);
        gastAtParaList[1].aucPara[ulLen]    = '\0';
        gastAtParaList[1].usParaLen         = (VOS_UINT16)ulLen;
        gucAtParaIndex                      = 2;
    }

    /* ������������Ϊż�� */
    if (0 != (gucAtParaIndex % 2))
    {
        AT_WARN_LOG1("AT_CheckBodySarGsmPara: Para Num is not Even!", gucAtParaIndex);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ȡGSM Band����ֵ */
    if (VOS_OK != AT_GetGsmBandCapa(&ulGBand))
    {
        return AT_ERROR;
    }

    /* ѭ�����BandƵ���Ƿ�֧�֣����������ṹ�� */
    pstBodySarGsmPara->ucParaNum = 0;
    for (ucLoop = 0; ucLoop < (gucAtParaIndex / 2); ucLoop++)
    {
        /* ���û������Ƶ�β�����16�����ַ���ת��Ϊ���� */
        if (AT_SUCCESS != At_String2Hex(gastAtParaList[ucLoop * 2 + 1].aucPara,
                                        gastAtParaList[ucLoop * 2 + 1].usParaLen,
                                        &gastAtParaList[ucLoop * 2 + 1].ulParaValue))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* ����û������������BandƵ�Σ����滻Ϊ��ǰ֧�ֵ�BandƵ��ֵ */
        if (AT_RF_BAND_ANY == gastAtParaList[ucLoop * 2 + 1].ulParaValue)
        {
            gastAtParaList[ucLoop * 2 + 1].ulParaValue = ulGBand;
        }

        /* ����û������Ƶ�ε�ǰ�Ƿ�֧�֣������֧�ַ��ز������� */
        if (0 != (gastAtParaList[ucLoop * 2 + 1].ulParaValue & (~ulGBand)))
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        pstBodySarGsmPara->asPower[pstBodySarGsmPara->ucParaNum]    = (VOS_INT16)gastAtParaList[ucLoop * 2].ulParaValue;
        pstBodySarGsmPara->aulBand[pstBodySarGsmPara->ucParaNum]    = gastAtParaList[ucLoop * 2 + 1].ulParaValue;
        pstBodySarGsmPara->ucParaNum++;
    }

    return AT_SUCCESS;
}


VOS_VOID AT_FillBodySarGsmPara(
    AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara,
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT8                           ucLoop;

    /* �����������еĲ��� */
    for (ucLoop = 0; ucLoop < pstBodySarGsmPara->ucParaNum; ucLoop++)
    {
        if (0 != (MTA_BODY_SAR_GBAND_GPRS_850_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_850_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_850].sGPRSPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_EDGE_850_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_850_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_850].sEDGEPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_GPRS_900_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_900_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_900].sGPRSPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_EDGE_900_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_900_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_900].sEDGEPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_GPRS_1800_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_1800_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_1800].sGPRSPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_EDGE_1800_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_1800_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_1800].sEDGEPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_GPRS_1900_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_1900_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_1900].sGPRSPower = pstBodySarGsmPara->asPower[ucLoop];
        }

        if (0 != (MTA_BODY_SAR_GBAND_EDGE_1900_MASK & pstBodySarGsmPara->aulBand[ucLoop]))
        {
            pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_1900_MASK;
            pstBodySarPara->astGBandPara[MTA_GSM_1900].sEDGEPower = pstBodySarGsmPara->asPower[ucLoop];
        }
    }

    return;
}
VOS_UINT32 AT_SetBodySarGsmPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARGSM_SET_PARA_STRU         stBodySarGsmPara;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarGsmPara, 0, sizeof(stBodySarGsmPara));

    /* ��������Ч�� */
    ulResult = AT_CheckBodySarGsmPara(&stBodySarGsmPara);
    if (AT_SUCCESS != ulResult)
    {
        return ulResult;
    }

    /* ��NV���ж�ȡBody SAR��������ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_BODY_SAR_PARA,
                           &stBodySarPara,
                           sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_SetBodySarGsmPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ��GSM��Ƶ�β�����䵽Body SAR�����ṹ���� */
    AT_FillBodySarGsmPara(&stBodySarGsmPara, &stBodySarPara);

    /* ��Body SAR��������ֵ���浽NV */
    if (NV_OK != NV_WriteEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &(stBodySarPara),
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_SetBodySarGsmPara: Write NV fail!");
        return AT_ERROR;
    }

    /* �����ǰ������Body SAR���ܣ���֪ͨ�������µ�Body SAR���� */
    if (MTA_BODY_SAR_ON == g_enAtBodySarState)
    {
        if (VOS_OK != AT_SndMtaBodySarPara(ucIndex,
                                           g_enAtBodySarState,
                                           &stBodySarPara))
        {
            AT_WARN_LOG("AT_SetBodySarGsmPara: AT_SndMtaBodySarPara fail!");
        }
    }

    return AT_OK;
}

/*****************************************************************************
 �� �� ��  : AT_SetCopnPara
 ��������  : +COPN���������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��06��
    �޸�����   : SS FDN&Call Control��Ŀ��֧��+COPN����
*****************************************************************************/
VOS_UINT32 AT_SetCopnPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    TAF_MMA_COPN_INFO_QUERY_REQ_STRU    stCopnInfo;

    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*
    AT��MMA������Ӫ����Ϣ:
    ��Ϊ�˼���Ϣ���ƣ�����һ�λ�ȡ������Ӫ����Ϣ�����ﶨ��Ϊһ�λ�ȡ50����Ӫ����Ϣ
    ��һ��������Ϣ��������0��ʼҪ��������50����Ӫ����Ϣ
    */
    stCopnInfo.usFromIndex  = 0;
    stCopnInfo.usPlmnNum    = TAF_MMA_COPN_PLMN_MAX_NUM;

    /* ��MMA����Ϣ������Ӫ����Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_MSG_MMA_COPN_INFO_QUERY_REQ,
                                   &stCopnInfo,
                                   sizeof(stCopnInfo),
                                   I0_WUEPS_PID_MMA);
    if (TAF_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPN_QRY;

    return AT_WAIT_ASYNC_RETURN;

}

VOS_UINT32 AT_SetNCellMonitorPara(VOS_UINT8 ucIndex)
{
    AT_MTA_NCELL_MONITOR_SET_REQ_STRU                       stAtCmd;
    VOS_UINT32                                              ulResult;

    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(stAtCmd));
    stAtCmd.ucSwitch    = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ��MTA����^NCELLMONITOR�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_NCELL_MONITOR_SET_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_NCELL_MONITOR_SET_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NCELL_MONITOR_SET;

    return AT_WAIT_ASYNC_RETURN;

}
VOS_UINT32 At_SetSimInsertPara(VOS_UINT8 ucIndex)
{
    TAF_MMA_SIM_INSERT_IND_STRU         stSimInsertState;
    VOS_UINT32                          ulResult;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gastAtParaList[0].ulParaValue > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ִ��������� */

    stSimInsertState.enSimInsertState = (TAF_SIM_INSERT_STATE_ENUM_UINT32)gastAtParaList[0].ulParaValue;

    ulResult = MN_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      TAF_MSG_MMA_SIMINSERT_IND,
                                      &stSimInsertState,
                                      sizeof(TAF_MMA_SIM_INSERT_IND_STRU),
                                      I0_WUEPS_PID_MMA);
    if (AT_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMINSERT_SET;
        return AT_WAIT_ASYNC_RETURN;    /* �������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 At_SetModemLoopPara(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucModemLoop;

    /* ������� */
    if ( AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucModemLoop = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    ulResult = APP_VC_SetModemLoop(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ucModemLoop);
    if (TAF_SUCCESS == ulResult)
    {
        return AT_OK;    /* �������Ҫ�ȴ�C�˻ظ���ֱ�ӷ���OK */
    }
    else
    {
        return AT_ERROR;
    }

}
VOS_UINT32 At_SetReleaseRrc(VOS_UINT8 ucIndex)
{
    VOS_UINT8                              *pucSystemAppConfig;

    /* ��ȡNV���е�ǰ��Ʒ��̬ */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

#ifndef DMT
    /* ��ANDROIDϵͳ��֧�� */
    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_CMD_NOT_SUPPORT;
    }
#endif

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �·����� */
    if (VOS_OK == At_SndReleaseRrcReq(gastAtClientTab[ucIndex].usClientId,
                                          gastAtClientTab[ucIndex].opId))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RELEASE_RRC_SET;

        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_SetRefclkfreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_MTA_REFCLKFREQ_SET_REQ_STRU      stRefClockReq;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ������� */
    if (1 != gucAtParaIndex)
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stRefClockReq, 0, sizeof(stRefClockReq));

    stRefClockReq.enRptFlg = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ���Ϳ����Ϣ��C��, ����GPS�ο�ʱ��״̬�Ƿ������ϱ� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_REFCLKFREQ_SET_REQ,
                                      &stRefClockReq,
                                      sizeof(stRefClockReq),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetRefclkfreqPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REFCLKFREQ_SET;

    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 At_SetPullomlogrrcPara(VOS_UINT8 ucIndex)
{
    OM_AcpuLogShowToFile(VOS_TRUE);

    return AT_OK;
}


VOS_UINT32 At_SetDieSNPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucDieSN[AT_DIE_SN_LEN];
    VOS_INT32                           i;
    VOS_UINT16                          usLength;

    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ��ȡDIE SN */
    if (VOS_OK != DRV_GET_DIEID(aucDieSN, AT_DIE_SN_LEN))
    {
        return AT_ERROR;
    }

    /* ���λ,��4 BIT��0 */
    aucDieSN[AT_DIE_SN_LEN -1] = (aucDieSN[AT_DIE_SN_LEN -1] & 0x0F);

    /* ��ʽ�������ѯ��� */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: 0x",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    for (i = (AT_DIE_SN_LEN-1); i>=0; i--)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%02x",
                                      aucDieSN[i]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_SetChipSNPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucChipSN[AT_CHIP_SN_LEN];
    VOS_INT32                           i;
    VOS_UINT16                          usLength;

    /* ������� */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ��ȡCHIP SN */
    if (VOS_OK != DRV_GET_CHIPID(aucChipSN, AT_CHIP_SN_LEN))
    {
        return AT_ERROR;
    }

    /* ��ʽ�������ѯ��� */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: 0x",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    for (i = (AT_CHIP_SN_LEN-1); i>=0; i--)
    {

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "%02x",
                                      aucChipSN[i]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32 At_SetHandleDect(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucHandleType;
    VOS_UINT8                          *pucSystemAppConfig;

    /* ��ȡNV���е�ǰ��Ʒ��̬ */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

#ifndef DMT
    /* ��������������phone��pad��̬cp���ֳ�λ�ã���ANDROIDϵͳ��֧�� */
    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig )
    {
        return AT_CMD_NOT_SUPPORT;
    }
#endif

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ����Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_ERROR;
    }

    /* handletype ȡֵ���� */
    if (gastAtParaList[0].ulParaValue > AT_MTA_HANDLEDECT_MAX_TYPE)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucHandleType = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ������Ϣ ID_AT_MTA_HANDLEDECT_SET_REQ ��MTA����������Ϣ������(VOS_UINT8)gastAtParaList[0].ulParaValue */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_MTA_HANDLEDECT_SET_REQ,
                                   (VOS_VOID*)&ucHandleType,
                                   sizeof(ucHandleType),
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HANDLEDECT_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if (FEATURE_ON == FEATURE_IMS)
TAF_UINT32 AT_SetCiregPara(TAF_UINT8 ucIndex)
{

    AT_IMSA_CIREG_SET_REQ_STRU          stCireg;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stCireg, 0x00, sizeof(AT_IMSA_CIREG_SET_REQ_STRU));

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        stCireg.enCireg = gastAtParaList[0].ulParaValue;

    }
    else
    {
        /* �������Ϊ�գ�Ĭ������Ϊ�������ϱ� */
        stCireg.enCireg = AT_IMSA_IMS_REG_STATE_DISABLE_REPORT;
    }


    /* ��IMSA����+CIREG�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     ID_AT_IMSA_CIREG_SET_REQ,
                                     &stCireg.enCireg,
                                     sizeof(AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32),
                                     PS_PID_IMSA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREG_SET;

    return AT_WAIT_ASYNC_RETURN;
}
TAF_UINT32 AT_SetCirepPara(TAF_UINT8 ucIndex)
{

    AT_IMSA_CIREP_SET_REQ_STRU          stCirep;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stCirep, 0x00, sizeof(AT_IMSA_CIREP_SET_REQ_STRU));

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ϊ�� */
    if(0 != gastAtParaList[0].usParaLen)
    {
        stCirep.enReport = gastAtParaList[0].ulParaValue;

    }
    else
    {
        /* �������Ϊ�գ�Ĭ������Ϊ�������ϱ� */
        stCirep.enReport = AT_IMSA_CIREP_REPORT_DISENABLE;
    }


    /* ��IMSA����+CIREG�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     ID_AT_IMSA_CIREP_SET_REQ,
                                     &stCirep.enReport,
                                     sizeof(AT_IMSA_CIREP_REPORT_ENUM_UINT32),
                                     PS_PID_IMSA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREP_SET;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 �� �� ��  : AT_SetVolteimpuPara
 ��������  : ^VOLTEIMPU�������������
 �������  : VOS_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��07��
    �޸�����   : ��������

*****************************************************************************/
TAF_UINT32 AT_SetVolteimpuPara(TAF_UINT8 ucIndex)
{
    AT_IMSA_VOLTEIMPU_QRY_REQ_STRU      stImpu;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stImpu, 0x00, sizeof(AT_IMSA_VOLTEIMPU_QRY_REQ_STRU));

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��IMSA����^VOLTEIMPU�������� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                     0,
                                     ID_AT_IMSA_VOLTEIMPU_QRY_REQ,
                                     stImpu.aucContent,
                                     sizeof(stImpu.aucContent),
                                     PS_PID_IMSA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMPU_SET;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_SetCacmimsPara(TAF_UINT8 ucIndex)
{

    MN_CALL_ORIG_PARAM_STRU             stOrigParam;
    AT_MODEM_SS_CTX_STRU               *pstSsCtx    = VOS_NULL_PTR;

    /* ��ʼ�� */
    PS_MEM_SET(&stOrigParam, 0x00, sizeof(MN_CALL_ORIG_PARAM_STRU));

    /* ������� */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if(1 != gucAtParaIndex)
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* ����<dial_string> */
    if (VOS_OK !=  AT_FillCalledNumPara(gastAtParaList[0].aucPara,
                                        gastAtParaList[0].usParaLen,
                                        &stOrigParam))
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_INVALID_PARAMETER);
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stOrigParam.enCallType              = MN_CALL_TYPE_VOICE;
    stOrigParam.enCallMode              = pstSsCtx->enCModType;
    stOrigParam.stDataCfg               = pstSsCtx->stCbstDataCfg;
    stOrigParam.ucImsInvitePtptFlag     = VOS_TRUE;

    if(VOS_OK == MN_CALL_Orig(gastAtClientTab[ucIndex].usClientId,
                              0,
                              &gastAtClientTab[ucIndex].AtCallInfo.CallId,
                              &stOrigParam))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CACMIMS_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_SetCsCallErrCause(ucIndex, TAF_CS_CAUSE_UNKNOWN);
        return AT_ERROR;
    }

}


TAF_UINT32 AT_SetCcwaiPara(TAF_UINT8 ucIndex)
{
    AT_IMSA_CCWAI_SET_REQ_STRU *    stCcwaiReq;
    VOS_UINT32                      ulResult;

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ�� */
    if((0 == gastAtParaList[0].usParaLen) || (0 == gastAtParaList[1].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stCcwaiReq = (AT_IMSA_CCWAI_SET_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(AT_IMSA_CCWAI_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if(stCcwaiReq == VOS_NULL)
    {
        return AT_ERROR;
    }
    
    /* �����Ϣ�ṹ�� */
    stCcwaiReq->ulSenderPid     = WUEPS_PID_AT;
    stCcwaiReq->ulReceiverPid   = PS_PID_IMSA;
    stCcwaiReq->ulLength        = sizeof(AT_IMSA_CCWAI_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    stCcwaiReq->ulMsgId         = ID_AT_IMSA_CCWAI_SET_REQ;
    stCcwaiReq->usClientId      = gastAtClientTab[ucIndex].usClientId;
    stCcwaiReq->ucOpId          = 0;
    stCcwaiReq->enMode          = gastAtParaList[0].ulParaValue;
    stCcwaiReq->ulSrvClass      = gastAtParaList[1].ulParaValue;
    
    /* ��IMSA����^CCWAI�������� */
    ulResult = VOS_SendMsg(WUEPS_PID_AT, stCcwaiReq);
    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CCWAI_SET;

    return AT_WAIT_ASYNC_RETURN;
}
#endif


VOS_UINT32 AT_SetEOPlmnParaCheck(VOS_VOID)
{

    /*������Ч�Լ��*/
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����������ΪTAF_AT_EOPLMN_PARA_NUM������AT_CME_INCORRECT_PARAMETERS*/
    if ( TAF_AT_EOPLMN_PARA_NUM != gucAtParaIndex )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��1���������,version���Ȳ��ܴ���TAF_MAX_USER_CFG_OPLMN_VERSION_LEN */
    if (TAF_MAX_USER_CFG_OPLMN_VERSION_LEN <= gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��2��������飬��Indexֵ���ܴ���5 */
    if (TAF_MAX_USER_CFG_OPLMN_GROUP_INDEX < gastAtParaList[1].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��3��������飬pduLenֵ���ܴ���500 */
    if (TAF_AT_PLMN_WITH_RAT_LEN * TAF_MAX_GROUP_CFG_OPLMN_NUM < gastAtParaList[2].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��3��������飬pduLenֵ����ΪTAF_AT_PLMN_WITH_RAT_LEN�������� */
    if (0 != (gastAtParaList[2].ulParaValue % TAF_AT_PLMN_WITH_RAT_LEN))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���ֻ��������256����������ĵ�6��(index=5)��������û�����6��OPLMN */
    if ((gastAtParaList[2].ulParaValue > 6 * TAF_AT_PLMN_WITH_RAT_LEN)
     && (TAF_MAX_USER_CFG_OPLMN_GROUP_INDEX == gastAtParaList[1].ulParaValue))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��4��������飬PDU��ʵ�ʳ��ȱ�����ָ����pdulen��ͬ */
    if (gastAtParaList[3].usParaLen != gastAtParaList[2].ulParaValue)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��4��������飬PDU���ݱ���������16�����ַ���ת�� */
    if (AT_SUCCESS != At_AsciiNum2HexString(gastAtParaList[3].aucPara, &gastAtParaList[3].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    return AT_SUCCESS;
}
VOS_UINT32 AT_SetUserCfgOPlmnPara(VOS_UINT8 ucIndex)
{
    TAF_MMA_SET_EOPLMN_LIST_STRU        stEOPlmnSetPara;
    VOS_UINT32                          ulRst;

    PS_MEM_SET(&stEOPlmnSetPara, 0, sizeof(TAF_MMA_SET_EOPLMN_LIST_STRU));


    /* ���������ͺϷ��Լ��,���Ϸ�ֱ�ӷ���ʧ�� */
    ulRst = AT_SetEOPlmnParaCheck();
    if (AT_SUCCESS != ulRst)
    {
        return ulRst;
    }

    /* �����õ�AT������װ��TAF_MMA_SET_EOPLMN_LIST_STRU����ʽ */
    PS_MEM_CPY(stEOPlmnSetPara.aucVersion,
               gastAtParaList[0].aucPara,
               TAF_MAX_USER_CFG_OPLMN_VERSION_LEN);

    PS_MEM_CPY(stEOPlmnSetPara.aucOPlmnWithRat,
               gastAtParaList[3].aucPara,
               gastAtParaList[3].usParaLen);

    stEOPlmnSetPara.ucIndex      = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    stEOPlmnSetPara.ucOPlmnCount = (VOS_UINT8)(gastAtParaList[2].ulParaValue / TAF_AT_PLMN_WITH_RAT_LEN);

    /* ��MMA���н������ɹ�����ʧ�ܣ������ɹ��������������״̬ */
    ulRst = Taf_SetEOPlmnHandle(gastAtClientTab[ucIndex].usClientId, 0, &stEOPlmnSetPara);
    if (AT_SUCCESS == ulRst)
    {
        /* ָʾ��ǰ�û��������������Ϊ�������� */
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_EOPLMN_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_SetEcidPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_MTA_ECID_SET_REQ_STRU            stEcidSetReq;

    /* ������� */
    if (1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ʼ�� */
    PS_MEM_SET(&stEcidSetReq, 0, sizeof(stEcidSetReq));

    stEcidSetReq.ulVersion = gastAtParaList[0].ulParaValue;

    /* ���Ϳ����Ϣ��C��, ����GPS�ο�ʱ��״̬�Ƿ������ϱ� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_ECID_SET_REQ,
                                      &stEcidSetReq,
                                      sizeof(stEcidSetReq),
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_SetEcidPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ECID_SET;

    return AT_WAIT_ASYNC_RETURN;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_VOID AT_UpdateUartCfgNV(VOS_VOID)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    TAF_NV_UART_CFG_STRU                stUartNvCfg;

    /* ��ʼ�� */
    PS_MEM_SET(&stUartNvCfg, 0, sizeof(TAF_NV_UART_CFG_STRU));

    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_UART_CFG,
                           &stUartNvCfg,
                           sizeof(TAF_NV_UART_CFG_STRU)))
    {
        AT_ERR_LOG("AT_UpdateUartCfgNV: Read NV fail!");
        AT_HSUART_DBG_NV_READ_ERR(1);
        return;
    }

    /* ��ȡUART���� */
    pstUartCtx                   = AT_GetUartCtxAddr();
    stUartNvCfg.ulBaudRate       = pstUartCtx->stPhyConfig.enBaudRate;
    stUartNvCfg.stFrame.ucFormat = pstUartCtx->stPhyConfig.stFrame.enFormat;
    stUartNvCfg.stFrame.ucParity = pstUartCtx->stPhyConfig.stFrame.enParity;

    /* ����UART����NV */
    if (NV_OK != NV_WriteEx(MODEM_ID_0,
                            en_NV_Item_UART_CFG,
                            &stUartNvCfg,
                            sizeof(TAF_NV_UART_CFG_STRU)))
    {
        AT_ERR_LOG("AT_UpdateUartCfgNV: Write NV fail!");
        AT_HSUART_DBG_NV_WRITE_ERR(1);
    }

    return ;
}
VOS_UINT32 AT_SetIprPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulBaudRate;

    pstUartCtx = AT_GetUartCtxAddr();

    /* ֻ֧��UART�˿��·� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    /* ������� */
    if (gucAtParaIndex > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����Ϊ��, ʹ�õ�Чֵ115200 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        ulBaudRate = AT_UART_DEFAULT_BAUDRATE;
    }
    else
    {
        if (0 == gastAtParaList[0].usParaLen)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        ulBaudRate = gastAtParaList[0].ulParaValue;
    }

    /* ��������Ч�Լ�� */
    if (VOS_TRUE != AT_HSUART_IsBaudRateValid(ulBaudRate))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���沨���ʲ����������� */
    pstUartCtx->stPhyConfig.enBaudRate = ulBaudRate;

    /* ����UART������NV */
    AT_UpdateUartCfgNV();

    /* ���ϱ�OK */
    At_FormatResultData(ucIndex, AT_OK);

    /* ����DRV�������ô��ڵĲ����� */
    if (VOS_OK != DRV_UDI_IOCTL(g_alAtUdiHandle[ucIndex], UART_IOCTL_SET_BAUD, (VOS_VOID *)&ulBaudRate))
    {
        AT_ERR_LOG("AT_SetIprPara, ERROR, Set Baud failed!");
        AT_HSUART_DBG_IOCTL_SET_BAUD_FAIL_NUM(1);
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_INT32 AT_ConfigUartCharFrameParam(
    VOS_UINT8                           ucIndex,
    AT_UART_FORMAT_ENUM_UINT8           enFormat,
    AT_UART_PARITY_ENUM_UINT8           enParity
)
{
    AT_UART_FORMAT_PARAM_STRU          *pstFormatPara = VOS_NULL_PTR;
    VOS_UINT32                          ulUdiDataLenth;
    VOS_UINT32                          ulUdiStpLenth;
    VOS_UINT32                          ulUdiParity;
    VOS_UINT32                          ulResult;

    /* ������ʼ�� */
    ulUdiDataLenth = WLEN_8_BITS;
    ulUdiStpLenth  = STP2_OFF;
    ulUdiParity    = PARITY_NO_CHECK;

    /* �����õ�֡��ʽ��У�鷽��ת��ΪDRV�ӿڸ�ʽ */
    pstFormatPara = AT_HSUART_GetFormatParam(enFormat);
    if (VOS_NULL_PTR == pstFormatPara)
    {
       return VOS_ERROR;
    }

    ulResult = AT_HSUART_GetUdiValueByDataLen(pstFormatPara->enDataBitLength, &ulUdiDataLenth);
    if (VOS_OK != ulResult)
    {
        return VOS_ERROR;
    }

    ulResult = AT_HSUART_GetUdiValueByStopLen(pstFormatPara->enStopBitLength, &ulUdiStpLenth);
    if (VOS_OK != ulResult)
    {
        return VOS_ERROR;
    }

    if (AT_UART_PARITY_LEN_1_BIT == pstFormatPara->enParityBitLength)
    {
        ulResult = AT_HSUART_GetUdiValueByParity(enParity, &ulUdiParity);
        if (VOS_OK != ulResult)
        {
            return VOS_ERROR;
        }
    }
    else
    {
        ulUdiParity = PARITY_NO_CHECK;
    }

    /* ����DRV�������ô�������λ���� */
    if (VOS_OK != DRV_UDI_IOCTL(g_alAtUdiHandle[ucIndex], UART_IOCTL_SET_WLEN, (VOS_VOID *)&ulUdiDataLenth))
    {
        AT_ERR_LOG("AT_ConfigUartCharFrameParam, ERROR, Set WLEN failed!");
        AT_HSUART_DBG_IOCTL_SET_WLEN_FAIL_NUM(1);
        return VOS_ERROR;
    }

    /* ����DRV�������ô���ֹͣλ���� */
    if (VOS_OK != DRV_UDI_IOCTL(g_alAtUdiHandle[ucIndex], UART_IOCTL_SET_STP2, (VOS_VOID *)&ulUdiStpLenth))
    {
        AT_ERR_LOG("AT_ConfigUartCharFrameParam, ERROR, Set STP2 failed!");
        AT_HSUART_DBG_IOCTL_SET_STP_FAIL_NUM(1);
        return VOS_ERROR;
    }

    /* ����DRV�������ô���У��λ */
    if (VOS_OK != DRV_UDI_IOCTL(g_alAtUdiHandle[ucIndex], UART_IOCTL_SET_EPS, (VOS_VOID *)&ulUdiParity))
    {
        AT_ERR_LOG("AT_ConfigUartCharFrameParam, ERROR, Set Parity failed!");
        AT_HSUART_DBG_IOCTL_SET_PARITY_FAIL_NUM(1);
        return VOS_ERROR;
    }

    return VOS_OK;
}
VOS_UINT32 AT_SetIcfPara(VOS_UINT8 ucIndex)
{

    AT_UART_CTX_STRU                   *pstUartCtx      = VOS_NULL_PTR;
    AT_UART_FORMAT_ENUM_UINT8           enFormat;
    AT_UART_PARITY_ENUM_UINT8           enParity;

    pstUartCtx = AT_GetUartCtxAddr();

    /* ֻ֧��UART�˿��·� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    /* ������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ������Ч�Լ�� */
    /* ����Ϊ�գ�ʹ�õ�Чֵ(3,3),��:8������λ1��ֹͣλ��У��λ */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        enFormat = AT_UART_DEFAULT_FORMAT;
        enParity = AT_UART_DEFAULT_PARITY;
    }
    else
    {
        /* AT_CMD_OPT_SET_PARA_CMD */
        /* AT+ICF= */
        if (0 == gucAtParaIndex)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        /* AT+ICF=, */
        if (0 == gastAtParaList[0].usParaLen)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }

        enFormat = (VOS_UINT8)gastAtParaList[0].ulParaValue;
        if (gucAtParaIndex > 1)
        {
            if (0 != gastAtParaList[1].usParaLen)
            {
                enParity = (VOS_UINT8)gastAtParaList[1].ulParaValue;
            }
            else
            {
                /* AT+ICF=<format>, */
                return AT_CME_INCORRECT_PARAMETERS;
            }
        }
        else
        {
            /* AT+ICF=<format> */
            enParity = AT_UART_DEFAULT_PARITY;
        }
    }

    /* ����֡��ʽ������������ */
    pstUartCtx->stPhyConfig.stFrame.enFormat = enFormat;
    pstUartCtx->stPhyConfig.stFrame.enParity = enParity;

    /* ����UART������NV */
    AT_UpdateUartCfgNV();

    /* ���ϱ�OK */
    At_FormatResultData(ucIndex, AT_OK);

    if (VOS_OK != AT_ConfigUartCharFrameParam(ucIndex, enFormat, enParity))
    {
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_SetIfcPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRtsFlag;
    VOS_UINT32                          ulCtsFlag;

    ulRtsFlag   = VOS_FALSE;
    ulCtsFlag   = VOS_FALSE;
    pstUartCtx  = AT_GetUartCtxAddr();

    /* �������������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT+IFC��Ч��AT+IFC=0,0
     * ע: �ô���Ϊ��Ʒ��Ҫ��, IUT-T-V.250�й涨AT+IFC��Ч��AT+IFC=2,2
     */
    if (AT_CMD_OPT_SET_CMD_NO_PARA == g_stATParseCmd.ucCmdOptType)
    {
        pstUartCtx->stFlowCtrl.enDceByDte = AT_UART_DEFAULT_FC_DCE_BY_DTE;
        pstUartCtx->stFlowCtrl.enDteByDce = AT_UART_DEFAULT_FC_DTE_BY_DCE;
        AT_HSUART_ConfigFlowCtrl(ucIndex, VOS_FALSE, VOS_FALSE);
        return AT_OK;
    }

    /* AT_CMD_OPT_SET_PARA_CMD */
    /* AT+IFC= */
    if (0 == gucAtParaIndex)
    {
        /* AT+IFC= */
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* AT+IFC=, */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (gucAtParaIndex > 1)
    {
        if (0 != gastAtParaList[1].usParaLen)
        {
            /* AT+IFC=<DCE_by_DTE>,<DTE_by_DCE> */
            pstUartCtx->stFlowCtrl.enDteByDce = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }
        else
        {
            /* AT+IFC=<DCE_by_DTE>, */
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        /* AT+IFC=<DCE_by_DTE> */
        pstUartCtx->stFlowCtrl.enDteByDce = AT_UART_DEFAULT_FC_DTE_BY_DCE;
    }

    pstUartCtx->stFlowCtrl.enDceByDte = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    if (AT_UART_FC_DCE_BY_DTE_RTS == pstUartCtx->stFlowCtrl.enDceByDte)
    {
        ulRtsFlag = VOS_TRUE;
    }

    if (AT_UART_FC_DTE_BY_DCE_CTS == pstUartCtx->stFlowCtrl.enDteByDce)
    {
        ulCtsFlag = VOS_TRUE;
    }

    AT_HSUART_ConfigFlowCtrl(ucIndex, ulRtsFlag, ulCtsFlag);

    return AT_OK;
}
VOS_UINT32 AT_SetOPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;
    AT_DATA_MODE_TYPE                   ucDataMode;

    /* ��ȡ��ǰ����ģʽ */
    ucDataMode = gastAtClientTab[ucIndex].DataMode;

    /* �����ǰͨ��ģʽΪONLINE-COMMANDģʽ, ֱ�ӻָ���ǰ����ģʽ */
    if (AT_ONLINE_CMD_MODE == gastAtClientTab[ucIndex].Mode)
    {
        At_SetMode(ucIndex, AT_DATA_MODE, ucDataMode);
        ulRslt = AT_CONNECT;
    }
    else
    {
        ulRslt = AT_NO_CARRIER;
    }

    return ulRslt;
}


VOS_UINT32 AT_SetSwitchUart(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulmode;

    if(AT_CLIENT_ID_HSUART != ucIndex)
    {
        vos_printf("AT_SetSwitchUart: 1\r\n");
        return AT_ERROR;
    }

    /* �ж�CK�Ƿ�У��ͨ�� */
    if (VOS_TRUE != g_stSpWordCtx.ucShellPwdCheckFlag)
    {
        vos_printf("AT_SetSwitchUart: 2\r\n");
        AT_WARN_LOG("AT_SetSwitchUart:WARNING: datalock check faild!");
        return AT_ERROR;
    }

     /* ������� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        vos_printf("AT_SetSwitchUart: 3\r\n");
        return AT_ERROR;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        vos_printf("AT_SetSwitchUart: 4\r\n");
        return AT_ERROR;
    }

    /* �л��� A shell*/
    if (AT_UART_MODE_ASHELL == gastAtParaList[0].ulParaValue)
    {
        vos_printf("AT_SetSwitchUart: 5\r\n");
        ulmode = UART_A_SHELL;
    }
    else if(AT_UART_MODE_CSHELL == gastAtParaList[0].ulParaValue)
    {
        vos_printf("AT_SetSwitchUart: 6\r\n");
        ulmode = UART_C_SHELL;
    }
    else
    {
        vos_printf("AT_SetSwitchUart: 7\r\n");
        AT_WARN_LOG("AT_SetSwitchUart: unknown value!");
        return AT_ERROR;
    }

    if (VOS_OK != DRV_UDI_IOCTL(g_alAtUdiHandle[ucIndex], UART_IOCTL_SET_AC_SHELL, &ulmode))
    {
        vos_printf("AT_SetSwitchUart: 8\r\n");
        AT_WARN_LOG("AT_SetSwitchUart:DRV_UDI_IOCTL faild!");
        return AT_ERROR;
    }

    AT_INFO_LOG("AT_SetSwitchUart: success and leave!!");
    vos_printf("AT_SetSwitchUart: success and leave!!");

    return AT_OK;

}
#endif

VOS_UINT32 At_SetAntSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    DRV_AGENT_ANTSWITCH_SET_STRU        stAntSwitchSetPara;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    /* ����Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(gastAtParaList[0].ulParaValue > 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stAntSwitchSetPara.ulState = gastAtParaList[0].ulParaValue;
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   DRV_AGENT_ANTSWITCH_SET_REQ,
                                   (VOS_VOID*)(&stAntSwitchSetPara),
                                   sizeof(stAntSwitchSetPara),
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANTSWITCH_SET;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
VOS_UINT32 AT_SetRATCombinePara(VOS_UINT8 ucIndex)
{
    TAF_NV_LC_CTRL_PARA_STRU        stCtrlData;

    /* ������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stCtrlData, 0x0, sizeof(stCtrlData));

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_LC_Ctrl_PARA, &stCtrlData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return AT_ERROR;
    }

    if (VOS_TRUE != stCtrlData.ucLCEnableFlg)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (0 == gastAtParaList[0].ulParaValue)
    {
        stCtrlData.enRatCombined = TAF_NVIM_LC_RAT_COMBINED_CL;
    }
    else
    {
        stCtrlData.enRatCombined = TAF_NVIM_LC_RAT_COMBINED_GUL;
    }

    if (NV_OK != NV_WriteEx(MODEM_ID_0, en_NV_Item_LC_Ctrl_PARA, &stCtrlData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return AT_ERROR;
    }

    return AT_OK;
}


#ifdef  __cplusplus
#if  __cplusplus
  }
  #endif
#endif

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : AtEventReport.h
  �� �� ��   : ����
  ��������   : 2010��1��20��
  ����޸�   :
  ��������   : AtEventReport.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��1��20��
    �޸�����   : �����ļ�

******************************************************************************/


#ifndef __ATEVENTREPORT_H__
#define __ATEVENTREPORT_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsApi.h"

#include "siappstk.h"
#include "MnCallApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define AT_UNKNOWN_CLCK_CLASS  (0)


#define AT_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenAtCurcRptCmdTable[0])
#define AT_GET_CURC_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenAtCurcRptCmdTable)/sizeof(AT_RPT_CMD_INDEX_ENUM_UINT8))

#define AT_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_PTR()    (&g_aenAtUnsolicitedRptCmdTable[0])
#define AT_GET_UNSOLICITED_RPT_CTRL_STATUS_MAP_TBL_SIZE()   (sizeof(g_aenAtUnsolicitedRptCmdTable)/sizeof(AT_RPT_CMD_INDEX_ENUM_UINT8))

#define AT_GET_CME_CALL_ERR_CODE_MAP_TBL_PTR()  (g_astAtCmeCallErrCodeMapTbl)
#define AT_GET_CME_CALL_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astAtCmeCallErrCodeMapTbl)/sizeof(AT_CME_CALL_ERR_CODE_MAP_STRU))

#define AT_GET_CMS_SMS_ERR_CODE_MAP_TBL_PTR()  (g_astAtCmsSmsErrCodeMapTbl)
#define AT_GET_CMS_SMS_ERR_CODE_MAP_TBL_SIZE() (sizeof(g_astAtCmsSmsErrCodeMapTbl)/sizeof(AT_CMS_SMS_ERR_CODE_MAP_STRU))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32                       g_ulAtAppDialModeCnf;

extern VOS_UINT32                       g_ulLcStartTime;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef TAF_VOID (*AT_SMS_RSP_PROC_FUN)(
    TAF_UINT8                           ucIndex,
    MN_MSG_EVENT_INFO_STRU              *pstEvent
);

typedef TAF_VOID (*AT_QRY_PARA_PROC_FUNC)(TAF_UINT8   ucIndex,
                                          TAF_UINT8   OpId,
                                          TAF_VOID    *pPara);

typedef struct
{
    VOS_UINT32                          QueryType;                              /* ��ѯ���� */
    AT_QRY_PARA_PROC_FUNC               AtQryParaProcFunc;                      /* ��ѯ���Ͷ�Ӧ�Ĵ������� */
}AT_QUERY_TYPE_FUNC_STRU;


typedef struct
{
    TAF_MSG_ERROR_ENUM_UINT32           enMsgErrorCode;
    AT_RRETURN_CODE_ENUM                enAtErrorCode;
}AT_SMS_ERROR_CODE_MAP_STRU;

typedef struct
{
    VOS_UINT32                          ulCmeCode;
    TAF_CS_CAUSE_ENUM_UINT32            enCsCause;

} AT_CME_CALL_ERR_CODE_MAP_STRU;


typedef struct
{
    VOS_UINT32                          ulCmsCode;
    VOS_UINT32                          ulSmsCause;

} AT_CMS_SMS_ERR_CODE_MAP_STRU;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern TAF_UINT32 At_ChangeSTKCmdNo(TAF_UINT32 ulCmdType, TAF_UINT8 *ucCmdNo );

VOS_VOID AT_CsUus1InfoEvtIndProc(
    VOS_UINT8                           ucIndex,
    MN_CALL_EVENT_ENUM_U32              enEvent,
    MN_CALL_INFO_STRU                   *pstCallInfo
);


VOS_VOID At_CsAllCallInfoEvtCnfProc(
    MN_AT_IND_EVT_STRU *pstData,
    TAF_UINT16 usLen
);


/*****************************************************************************
 �� �� ��  : AT_MnPsEvtProc
 ��������  : PS���¼���������
 �������  : pstEvt                     - PS���¼�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_RcvTafPsEvt(
    TAF_PS_EVT_STRU                     *pstEvt
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpErrorInd
 ��������  :
 �������  : pEvtInfo                   - �¼�����(������EvtId)
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpErrorInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpActivateCnf
 ��������  :
 �������  : pEvtInfo                   - �¼�����(������EvtId)
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpActivateRej
 ��������  :
 �������  : pEvtInfo                   - �¼�����(������EvtId)
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateRej(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpManageInd
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpManageInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpActivateInd
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpActivateInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtPdpModifyCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpModifyCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpModifyRej
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpModifyRej(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpModifiedInd
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpModifiedInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpDeactivateCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpDeactivateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtPdpDeactivatedInd
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtPdpDeactivatedInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);


/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtCallOrigCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallOrigCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtCallEndCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallEndCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtCallEndCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallModifyCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtCallAnswerCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallAnswerCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsCallEvtCallHangupCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsCallEvtCallHangupCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetPrimPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPrimPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetPrimPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPrimPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);


/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetSecPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetSecPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetSecPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetSecPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvPsSetPdpTftInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetTftInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetTftInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetTftInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetUmtsQosInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetUmtsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetUmtsQosInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetUmtsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetUmtsQosMinInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetUmtsQosMinInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetUmtsQosMinInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetUmtsQosMinInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicUmtsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetPdpStateCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPdpStateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtCgactQryCnf
 ��������  : Cgact��ѯ�����
 �������  : pEvtInfo                   - �¼�����, MN_PS_EVT_STRUȥ��EvtId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtCgactQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtCgeqnegTestCnf
 ��������  : Cgeqneg���������
 �������  : pEvtInfo - �¼�����, MN_PS_EVT_STRUȥ��EvtId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/

VOS_UINT32 AT_RcvTafPsEvtCgeqnegTestCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetPdpStateCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpStateCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetPdpIpAddrInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpIpAddrInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetAnsModeInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetAnsModeInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetAnsModeInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetAnsModeInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicPrimPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicSecPdpContextInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetDynamicTftInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicTftInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetEpsQosInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetEpsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetEpsQosInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetEpsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetDynamicEpsQosInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDynamicEpsQosInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetDsFlowInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetDsFlowInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtClearDsFlowInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtClearDsFlowInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtConfigDsFlowRptCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtConfigDsFlowRptCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtReportDsFlowInd
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtReportDsFlowInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetPdpAuthInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPdpAuthInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetPdpAuthInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpAuthInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetPdpDnsInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetPdpDnsInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetPdpDnsInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetPdpDnsInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtSetAuthDataInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtSetAuthDataInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetAuthDataInfoCnf
 ��������  :
 �������  : VOS_VOID                           *pEvtInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetAuthDataInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetGprsActiveTypeCnf
 ��������  : ID_EVT_TAF_PS_GET_D_GPRS_ACTIVE_TYPE_CNF�¼���������, ����PPP����
 �������  : pEvtInfo                   - �¼�����, MN_PS_EVT_STRUȥ��EvtId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetGprsActiveTypeCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtPppDialOrigCnf
 ��������  : ID_EVT_TAF_PS_PPP_DIAL_ORIG_CNF�¼���������, ����PPP����
 �������  : pEvtInfo                   - �¼�����, MN_PS_EVT_STRUȥ��EvtId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtPppDialOrigCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

#if (FEATURE_ON == FEATURE_IPV6)
/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtReportDsFlowInd
 ��������  : ID_EVT_TAF_PS_IPV6_INFO_IND�¼���������, ���ڴ���IPV6��RA����
 �������  : pEvtInfo                   - �¼�����,
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtReportRaInfo(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
#endif

VOS_UINT32 AT_RcvTafPsEvtPdpDisconnectInd(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_VOID AT_QryParaRspCeregProc(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucOpId,
    VOS_VOID                           *pPara
);

VOS_UINT32 AT_RcvTafPsEvtGetDynamicDnsInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);



TAF_VOID  At_StkCsinIndPrint(TAF_UINT8 ucIndex,SI_STK_EVENT_INFO_STRU *pEvent);

#if (FEATURE_ON==FEATURE_LTE)
VOS_UINT32 atReadLtecsCnfProc(VOS_UINT8   ucIndex,VOS_VOID    *pEvtInfo);

VOS_UINT32 atReadCemodeCnfProc(VOS_UINT8   ucIndex,VOS_VOID    *pEvtInfo);

VOS_UINT32 AT_RcvTafPsEvtSetPdprofInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);
#endif


VOS_VOID At_RcvMnCallEccNumIndProc(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

VOS_VOID At_RcvMmaPlmnChangeIndProc(
    TAF_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU           *pEvent
);
VOS_VOID AT_ConvertNasMccToBcdType(
    VOS_UINT32                          ulNasMcc,
    VOS_UINT32                         *pulMcc
);


VOS_VOID AT_RcvMmaNsmStatusInd(
    TAF_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
);

VOS_UINT32 AT_CheckRptCmdStatus(
    VOS_UINT8                          *pucRptCfg,
    AT_CMD_RPT_CTRL_TYPE_ENUM_UINT8     enRptCtrlType,
    AT_RPT_CMD_INDEX_ENUM_UINT8         enRptCmdIndex
);

VOS_VOID AT_ReportCCallstateResult(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                          *pucRptCfg,
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState,
    TAF_CALL_VOICE_DOMAIN_ENUM_UINT8    enVoiceDomain
);

VOS_VOID AT_ReportCCallstateHoldList(
    MN_CALL_EVT_HOLD_STRU              *pstHoldEvt,
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState
);
VOS_VOID AT_ReportCCallstateRetrieveList(
    MN_CALL_EVT_RETRIEVE_STRU          *pstRetrieveEvt,
    AT_CS_CALL_STATE_ENUM_UINT8         enCallState
);


VOS_VOID AT_ReportCendResult(
    VOS_UINT8                           ucIndex,
    MN_CALL_INFO_STRU                  *pstCallInfo );

VOS_VOID AT_CSCallStateReportProc(
    MN_AT_IND_EVT_STRU                 *pstData );

VOS_VOID At_SetClprCnf(MN_AT_IND_EVT_STRU *pstData);


VOS_VOID  At_StkCcinIndPrint(TAF_UINT8 ucIndex, SI_STK_EVENT_INFO_STRU *pstEvent);

VOS_VOID At_StkHvsmrIndPrint(VOS_UINT8 ucIndex, SI_STK_EVENT_INFO_STRU *pstEvent);

/*****************************************************************************
 �� �� ��  : AT_RcvMnCallErrInd
 ��������  : ����MN_CALL_EVT_ERR_IND�¼�, ��¼CS�������
 �������  : pEvtInfo - �¼�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID AT_RcvMnCallErrInd(VOS_VOID *pEvtInfo);

VOS_VOID AT_RcvMmaRssiChangeInd(
    TAF_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
);


VOS_VOID AT_RcvMmaAcInfoChangeInd(
    VOS_UINT8                           ucIndex,
    TAF_PHONE_EVENT_INFO_STRU          *pstEvent
);

VOS_VOID AT_PhRegRejInfoProc(TAF_UINT8* pData,TAF_UINT16 usLen);

VOS_VOID AT_PhPlmnSelectInfoProc(TAF_UINT8* pData,TAF_UINT16 usLen);

VOS_VOID AT_PhNetScanCnfProc(
    TAF_UINT8                          *pData,
    TAF_UINT16                          usLen
);

TAF_UINT32 AT_ProcOperModeWhenLteOn(VOS_UINT8 ucIndex);


VOS_VOID AT_RcvMnCallChannelInfoInd(VOS_VOID *pEvtInfo);


/**********************************************************
 �� �� ��  : At_RcvPlmnQryCnf
 ��������  : ������ѯ���^PLMN���ϱ�����
 �������  : ucIndex
             OpId
             pPara
 �������  : ��
 �� �� ֵ  :
*************************************************************/
VOS_VOID At_RcvPlmnQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                           *pPara
);

/*****************************************************************************
 �� �� ��  : At_RcvXlemaQryCnf
 ��������  : �յ�CALL�����������ѯ�Ĵ���
 �������  : MN_AT_IND_EVT_STRU   pstData
             VOS_UINT16           usLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID At_RcvXlemaQryCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    VOS_UINT16                          usLen
);

/*****************************************************************************
 �� �� ��  : AT_GetSsEventErrorCode
 ��������  : ��SS Event�л�ȡAT���������
 �������  : VOS_UINT8                           ucIndex -- ATͨ��������
             TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent  -- SS Event��Ϣ
 �������  : ��
 �� �� ֵ  : AT_RRETURN_CODE_ENUM   -- AT���������
*****************************************************************************/
VOS_UINT32 AT_GetSsEventErrorCode(
    VOS_UINT8                           ucIndex,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pEvent);

VOS_VOID AT_RcvUserSrvStateQryCnf(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           OpId,
    VOS_VOID                           *pPara
);


extern TAF_UINT8 At_GetClckClassFromBsCode(TAF_SS_BASIC_SERVICE_STRU *pstBs);

VOS_VOID AT_RcvTafCallStartDtmfCnf(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallStopDtmfCnf(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallStartDtmfRslt(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_RcvTafCallStopDtmfRslt(
    MN_AT_IND_EVT_STRU                 *pstData
);

VOS_VOID AT_PhEOPlmnQueryCnfProc(TAF_UINT8 *pData);
VOS_VOID AT_PhEOPlmnSetCnfProc(TAF_UINT8 *pData);

extern VOS_VOID AtBase64Encode(const VOS_VOID* pdata,const VOS_UINT32 data_size,VOS_VOID* out_pcode);

VOS_VOID AT_FlushSmsIndication(VOS_VOID);
VOS_UINT32  AT_IsClientBlock(VOS_VOID);


VOS_VOID At_RcvTafCallOrigCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    TAF_UINT16                          usLen
);
VOS_VOID At_RcvTafCallSupsCmdCnf(
    MN_AT_IND_EVT_STRU                 *pstData,
    TAF_UINT16                          usLen
);


/*****************************************************************************
 �� �� ��  : AT_RcvTafPsEvtGetCidSdfInfoCnf
 ��������  : ID_MSG_TAF_GET_CID_SDF_CNF�¼���������
 �������  : VOS_UINT8                  ucIndex,
             VOS_VOID                  *pEvtInfo       - �¼�����, MN_PS_EVT_STRUȥ��EvtId
 �������  : ��
 �� �� ֵ  : VOS_UINT32

*****************************************************************************/
VOS_UINT32 AT_RcvTafPsEvtGetCidSdfInfoCnf(
    VOS_UINT8                           ucIndex,
    VOS_VOID                           *pEvtInfo
);

VOS_UINT32 AT_ConvertCallError(TAF_CS_CAUSE_ENUM_UINT32 enCause);

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID At_ProcQryClccResult(
    VOS_UINT8                           ucNumOfCalls,
    MN_CALL_INFO_QRY_CNF_STRU          *pstCallInfos,
    VOS_UINT8                           ucIndex
);
#endif


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif


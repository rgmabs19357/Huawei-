/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : AdsLog.h
  �� �� ��   : ����
  ��������   : 2011��12��17��
  ����޸�   :
  ��������   : ADS LOG ��ӡ
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��12��17��
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef __ADS_LOG_H__
#define __ADS_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "pslog.h"
#include "PsCommonDef.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
#define     ADS_MEM_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "ADS Mem Operation Failed!");
#define     ADS_MSG_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "ADS Msg Opration Failed!");
#define     ADS_TIMER_FAIL()            PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "ADS Timer Opration Failed!");

/*================================================*/
/* ���ܺ����궨�� */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define ADS_LOG(String)\
    {\
        Print( (String) );\
        Print("\n");\
    }

#define ADS_LOG1(String, Para1)\
    {\
        Print ( (String) );\
        Print1( ",%d\n",(VOS_INT32)(Para1));\
    }

#define ADS_LOG2(String, Para1, Para2)\
    {\
        Print ( (String) );\
        Print2( ",%d,%d\n",(VOS_INT32)(Para1), (VOS_INT32)(Para2));\
    }

#define ADS_LOG3(String, Para1, Para2, Para3)\
    {\
        Print ( (String) );\
        Print3 ( ",%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) );\
    }

#define ADS_LOG4(String, Para1, Para2, Para3, Para4)\
    {\
        Print ( (String) );\
        Print4 ( ",%d,%d,%d,%d\n", (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) );\
    }

#if 0
#define    ADS_INFO_LOG(Mod, String)                                    ADS_LOG( (String) )
#define    ADS_INFO_LOG1(Mod, String,Para1)                             ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_INFO_LOG2(Mod, String,Para1,Para2)                       ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_NORMAL_LOG(Mod, String)                                  ADS_LOG ( (String) )
#define    ADS_NORMAL_LOG1(Mod, String,Para1)                           ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_NORMAL_LOG2(Mod, String,Para1,Para2)                     ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_WARNING_LOG(Mod, String)                                 ADS_LOG ( (String) )
#define    ADS_WARNING_LOG1(Mod, String,Para1)                          ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_WARNING_LOG2(Mod, String,Para1,Para2)                    ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_ERROR_LOG(Mod, String)                                   ADS_LOG ( (String) )
#define    ADS_ERROR_LOG1(Mod, String,Para1)                            ADS_LOG1 ( (String), (VOS_INT32)(Para1) )
#define    ADS_ERROR_LOG2(Mod, String,Para1,Para2)                      ADS_LOG2 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                ADS_LOG3 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          ADS_LOG4 ( (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )
#endif

#if 1
#define    ADS_INFO_LOG(Mod, String)                                    PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_INFO, (String) )
#define    ADS_INFO_LOG1(Mod, String,Para1)                             PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1) )
#define    ADS_INFO_LOG2(Mod, String,Para1,Para2)                       PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_NORMAL_LOG(Mod, String)                                  PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_NORMAL, (String) )
#define    ADS_NORMAL_LOG1(Mod, String,Para1)                           PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1) )
#define    ADS_NORMAL_LOG2(Mod, String,Para1,Para2)                     PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_WARNING_LOG(Mod, String)                                 PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_WARNING, (String) )
#define    ADS_WARNING_LOG1(Mod, String,Para1)                          PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1) )
#define    ADS_WARNING_LOG2(Mod, String,Para1,Para2)                    PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    ADS_ERROR_LOG(Mod, String)                                   PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_ERROR, (String) )
#define    ADS_ERROR_LOG1(Mod, String,Para1)                            PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1) )
#define    ADS_ERROR_LOG2(Mod, String,Para1,Para2)                      PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    ADS_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    ADS_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )
#endif

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
ö����    : ADS_LOG_MSG_ID_ENUM
ö��˵��  : ADS LOG��Ϣ����

  1.��    ��   : 2011��12��6��
    �޸�����   : ����ADS LOG��Ϣ����
*****************************************************************************/
enum ADS_LOG_MSG_ID_ENUM
{
    ID_ADS_UL_LOG              = 0x1101,                                        /* _H2ASN_MsgChoice  */
    ID_ADS_DL_LOG              = 0x1102,                                        /* _H2ASN_MsgChoice  */
    ID_ADS_LOG_RPT_STATS_INFO  = 0x1103,                                        /* _H2ASN_MsgChoice  */
    ID_ADS_LOG_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 ADS_LOG_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ     */    /* _H2ASN_Skip */
    ADS_LOG_MSG_ID_ENUM_UINT32          enMsgId;                                /*  ��Ϣ���� */      /*  _H2ASN_Skip */
}ADS_LOG_HEAD_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* AdsLog.h */



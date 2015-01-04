/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : Siapppb.h
Version     : V200R001
Date        : 2008-10-10
Description : 电话本的的头文件
History     :
History     :
1.日    期  : 2006年11月14日
  修改内容  : Create
************************************************************************/

#ifndef __SIAPPPB_H__
#define __SIAPPPB_H__

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

/**/
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "sitypedef.h"
#include "vos.h"
#include "TafOamInterface.h"
#include "UsimPsInterface.h"
#include "omnvinterface.h"

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define SI_PB_PHONENUM_MAX_LEN          40    /*返回结构中号码的最大长度，是指字节数*/
#define SI_PB_ALPHATAG_MAX_LEN          242   /*返回结构中名字的最大长度，是指字节数*/

#define SI_PB_EMAIL_MAX_LEN             64    /*返回结构中邮件的最大长度，是指字节数*/

/* SIM卡里最多只支持5个紧急呼叫号码，我看到的USIM卡也就只有5条记录 */
#define USIM_MAX_ECC_RECORDS    5
#define USIM_ECC_LEN            3

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
#define SI_PB_STORAGE_UNSPECIFIED       0       /*存储器类型不指定，根据设置确定介质类型*/
#define SI_PB_STORAGE_SM                1       /*存储器类型为ADN*/
#define SI_PB_STORAGE_ME                2       /*存储器类型为NV*/
#define SI_PB_STORAGE_BOTH              3       /*存储器类型为ADN和NV*/
#define SI_PB_STORAGE_ON                4       /*存储器类型为MSISDN*/
#define SI_PB_STORAGE_FD                5       /*存储器类型为FDN*/
#define SI_PB_STORAGE_EC                6       /*存储器类型为ECC*/
#define SI_PB_STORAGE_BD                7       /*存储器类型为BDN*/

typedef SI_UINT32  SI_PB_EVENT;
#define SI_PB_EVENT_INFO_IND            0       /* 号码本信息事件上报           */
#define SI_PB_EVENT_READ_CNF            1       /* 号码本读取结果回复           */
#define SI_PB_EVENT_QUERY_CNF           2       /* 号码本查询结果回复           */
#define SI_PB_EVENT_SET_CNF             3       /* 号码本设置结果回复           */
#define SI_PB_EVENT_ADD_CNF             4       /* 号码本添加结果回复           */
#define SI_PB_EVENT_MODIFY_CNF          5       /* 号码本修改结果回复           */
#define SI_PB_EVENT_DELETE_CNF          6       /* 号码本删除结果回复           */
#define SI_PB_EVENT_SEARCH_CNF          7       /* 号码本搜索结果回复           */
#define SI_PB_EVENT_SREAD_CNF           8       /* 复合号码本读取结果回复       */
#define SI_PB_EVENT_SADD_CNF            9       /* 复合号码本添加结果回复       */
#define SI_PB_EVENT_SMODIFY_CNF         10      /* 复合号码本修改结果回复       */

typedef SI_UINT32  SI_PB_AlPHATAG_TYPE;
#define SI_PB_ALPHATAG_TYPE_UCS2_80     0x80            /*名字的编码类型，16-bit universal multiple-octet coded character set (ISO/IEC10646 [32])*/
#define SI_PB_ALPHATAG_TYPE_UCS2_81     0x81
#define SI_PB_ALPHATAG_TYPE_UCS2_82     0x82
#define SI_PB_ALPHATAG_TYPE_GSM         0x00            /*名字的编码类型，GSM 7 bit default alphabet (3GPP TS 23.038)*/
#define SI_PB_ALPHATAG_TYPE_UCS2        0x80

#define SI_PB_CONTENT_VALID             0x01
#define SI_PB_CONTENT_INVALID           0x00

#define SI_PB_LAST_TAG_TRUE             1

#define SI_PB_ALPHATAG_TRANSFER_TAG     0x1B

enum PB_FDN_CHECK_RSLT_ENUM
{
    PB_FDN_CHECK_SUCC                   = 0,
    PB_FDN_CHECK_NUM1_FAIL              = 1,
    PB_FDN_CHECK_NUM2_FAIL              = 2,
    PB_FDN_CHECK_BOTH_NUM_FAIL          = 3,
    PB_FDN_CHECK_RSLT_BUTT
};
typedef VOS_UINT32 PB_FDN_CHECK_RSLT_ENUM_UINT32;


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/

/*****************************************************************************
  5 STRUCT定义
*****************************************************************************/
/* 电话本号码类型枚举 */
enum PB_NUMBER_TYPE_ENUM
{
    PB_NUMBER_TYPE_NORMAL        = 129,            /* 普通号码类型 */
    PB_NUMBER_TYPE_INTERNATIONAL = 145,            /* 国际号码类型 */
    PB_NUMBER_TYPE_BUTT
};

/*仅数据卡产品支持电话本查询功能*/
typedef struct
{
    SI_UINT16                InUsedNum;           /*已使用记录数目*/
    SI_UINT16                TotalNum;            /*总记录数目*/
    SI_UINT16                TextLen;             /*支持的text的最大长度*/
    SI_UINT16                NumLen;              /*支持的number的最大长度*/
    SI_UINT16                EMAILTextLen;        /*Emai长度*/
    SI_UINT16                ANRNumberLen;        /*ANR号码长度*/
}SI_PB_EVENT_QUERY_CNF_STRU;

typedef struct
{
    SI_UINT16                ADNRecordNum ;              /*ADN记录总数*/
    SI_UINT16                ADNTextLen ;                /*ADN姓名字段长度*/
    SI_UINT16                ADNNumberLen;              /*ADN号码长度*/
    SI_UINT16                FDNRecordNum ;              /*FDN记录总数*/
    SI_UINT16                FDNTextLen ;                /*FDN姓名字段长度*/
    SI_UINT16                FDNNumberLen;              /*FDN号码长度*/
    SI_UINT16                BDNRecordNum ;              /*BDN记录总数*/
    SI_UINT16                BDNTextLen ;                /*BDN姓名字段长度*/
    SI_UINT16                BDNNumberLen;              /*BDN号码长度*/
    SI_UINT16                MSISDNRecordNum;            /*MSISDN记录总数*/
    SI_UINT16                MSISDNTextLen ;             /*MSISDN姓名字段长度*/
    SI_UINT16                MSISDNNumberLen;           /*MSISDN号码长度*/
    SI_UINT16                EMAILTextLen;              /*EMAIL长度*/
    SI_UINT16                ANRNumberLen;              /*ANR号码长度*/
    SI_UINT16                FdnState;                   /*FDN使能状态*/
    SI_UINT16                BdnState;                   /*BDN使能状态*/
    SI_UINT16                CardType;                   /*卡类型：0 SIM卡　1 USIM卡*/
}SI_PB_EVENT_INFO_IND_STRU;

typedef struct
{
    SI_UINT16                InUsedNum;           /*已使用记录数目*/
    SI_UINT16                TotalNum;            /*总记录数目*/
    SI_UINT16                TextLen;             /*支持的text的最大长度*/
    SI_UINT16                NumLen;              /*支持的number的最大长度*/
    SI_UINT16                EMAILTextLen;        /*Emai长度*/
    SI_UINT16                ANRNumberLen;        /*ANR号码长度*/
}SI_PB_EVENT_SET_CNF_STRU;

typedef struct
{
    SI_UINT8                 NumberType;                      /*号码类型，145或129*/
    SI_UINT8                 NumberLength;                    /*号码长度，是不包括NumberType的长度*/
    SI_UINT8                 Number[SI_PB_PHONENUM_MAX_LEN+2];  /*号码，采用ASCII的编码方式*/
}SI_PB_ADDITION_NUM_STRU;

typedef struct
{
    SI_UINT32                EmailLen;                        /*Email长度*/
    SI_UINT8                 Email[SI_PB_EMAIL_MAX_LEN];      /*Email，采用ASCII的编码方式*/
}SI_PB_EMAIL_STRU;

typedef struct
{
    SI_UINT16                Index;                           /*记录的index*/
    SI_UINT8                 AlphaTag[SI_PB_ALPHATAG_MAX_LEN];/*记录的姓名字段包含编码类型*/
    SI_UINT8                 ucAlphaTagLength;                /*名字长度, 字节数，如果是UNICODE编码包含编码类型指示字节*/
    SI_UINT8                 NumberType;                      /*号码类型，145或129*/
    SI_UINT8                 NumberLength;                    /*号码长度，是不包括NumberType的长度*/
    SI_UINT8                 ValidFlag;                       /*记录有效标志*/
    SI_UINT8                 Number[SI_PB_PHONENUM_MAX_LEN];  /*号码1，采用ASCII的编码方式*/
    SI_PB_AlPHATAG_TYPE      AlphaTagType;                    /*编码类型*/
    SI_PB_ADDITION_NUM_STRU  AdditionNumber[3];
    SI_PB_EMAIL_STRU         Email;
}SI_PB_RECORD_STRU;

typedef struct
{
    SI_UINT16                RecordNum;   /*记录的数目*/
    SI_UINT16                Rsv;
    SI_PB_RECORD_STRU        PBRecord; /*第一个记录项*/
}SI_PB_EVENT_READ_CNF_STRU;

typedef struct
{
    SI_UINT16                RecordNum;   /*记录的数目*/
    SI_UINT16                Rsv;
    SI_PB_RECORD_STRU        PBRecord; /*第一个记录项*/
}SI_PB_EVENT_SEARCH_CNF_STRU;

typedef struct
{
    SI_UINT16                Index; /*返回添加的记录索引号*/
}SI_PB_EVENT_ADD_CNF_STRU;

typedef struct
{
    SI_UINT16                ClientId;
    SI_UINT8                 OpId;
    SI_UINT8                 Reserve;
    SI_UINT32                PBEventType;
    SI_UINT32                PBError;
    SI_PB_STORATE_TYPE       Storage;
    SI_UINT32                PBLastTag;
    union
    {
        SI_PB_EVENT_QUERY_CNF_STRU      PBQueryCnf ;
        SI_PB_EVENT_INFO_IND_STRU       PBInfoInd ;
        SI_PB_EVENT_SET_CNF_STRU        PBSetCnf ;
        SI_PB_EVENT_READ_CNF_STRU       PBReadCnf ;
        SI_PB_EVENT_ADD_CNF_STRU        PBAddCnf ;
        SI_PB_EVENT_SEARCH_CNF_STRU     PBSearchCnf;
    }PBEvent;
}SI_PB_EVENT_INFO_STRU;

typedef struct
{
    SI_BOOL                  bESC;                       /* ESC字节是否存在标志 */
    SI_UINT8                 aucEccCode[USIM_ECC_LEN];   /* Emergency Call Code */
    SI_UINT8                 ucESC;                      /* ESC字段值 */
    SI_UINT8                 ucLen;                      /* ESC字符长度 */
    SI_UINT8                 AlphaIdentifier[253];        /* ESC字符内容 */
    SI_UINT8                 aucReserved[2];
}SI_PB_ECC_RECORD_STRU;

typedef struct
{
    SI_BOOL                  bEccExists;         /* ECC文件是否存在 */
    SI_UINT32                ulReocrdNum;        /* ECC中紧急呼叫号码的个数 */
    SI_PB_ECC_RECORD_STRU    astEccRecord[USIM_MAX_ECC_RECORDS];
}SI_PB_ECC_DATA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;          /* 消息名   */
}PBMsgBlock;

/* 回复FDN检测结果的消息结构 */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;          /* 消息名 */
    VOS_UINT32                          ulSendPara;
    VOS_UINT32                          ulContextIndex;
    PB_FDN_CHECK_RSLT_ENUM_UINT32       enResult;           /* 验证结果 */
}PB_FDN_CHECK_CNF_STRU;

/*****************************************************************************
  5 函数定义
*****************************************************************************/

extern SI_UINT32 SI_PB_Read(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_UINT16 Index1,SI_UINT16 Index2);

extern SI_UINT32 SI_PB_Set(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage);

extern SI_UINT32 SI_PB_Modify(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU* pRecord) ;

extern SI_UINT32 SI_PB_SModify(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU* pRecord);

extern SI_UINT32 SI_PB_SRead(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage, SI_UINT16 Index1,SI_UINT16 Index2);

extern SI_UINT32 SI_PB_Delete(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_UINT16 Index);

extern SI_UINT32 SI_PB_Add(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU *pRecord);

extern SI_UINT32 SI_PB_SAdd(SI_UINT16 ClientId,SI_UINT8 OpId,SI_PB_STORATE_TYPE Storage,SI_PB_RECORD_STRU *pRecord);

extern SI_UINT32 SI_PB_Search(SI_UINT16 ClientId,  SI_UINT8 OpId, SI_PB_STORATE_TYPE Storage, SI_UINT8 ucLength, SI_UINT8 *pucContent);

extern SI_UINT32 SI_PB_Query(SI_UINT16 ClientId,SI_UINT8 OpId);

extern SI_UINT32 SI_PB_GetEccNumber(SI_PB_ECC_DATA_STRU *pstEccData);

extern SI_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);

extern VOS_VOID SI_PB_MemSet(VOS_UINT8 ucLen, VOS_UINT8 ucValue,VOS_UINT8 *pucMem);

extern VOS_VOID   SI_PB_PidMsgProc(struct MsgCB *pstPBMsg);

extern VOS_UINT32 SI_PB_GetStorateType(VOS_VOID);

extern VOS_UINT32 SI_PB_GetSPBFlag(VOS_VOID);

extern VOS_UINT32 SI_PB_FdnNumCheck(VOS_UINT32 ulPid, VOS_UINT32 ulContextIndex, VOS_UINT32 ulClientId, PS_PB_FDN_NUM_STRU *pstFdnInfo);

/*单编译接口声明*/
/*****************************************************************************
函 数 名  :SI_PB_FdnNumCheck_Instance
功能描述  :提供给NAS进行FDN号码检查的API
输入参数  :enModemID:Modem ID
           ulPid:发送FDN号码检查请求的Pid
           ulContextIndex:索引值
           ulSendPara:发送参数
           pstFdnInfo:号码信息
输出参数  :无
修订记录  :
1. 日    期   : 2013年5月27日
   修改内容   : Creat
*****************************************************************************/
extern VOS_UINT32 SI_PB_FdnNumCheck_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    PS_PB_FDN_NUM_STRU                 *pstFdnInfo);

/*****************************************************************************
函 数 名  :SI_PB_GetEccNumber_Instance
功能描述  :获取ECC号码
输入参数  :enModemID:Modem ID
输出参数  :pstEccData:ECC号码数据结构
修订记录  :
1. 日    期   : 2013年5月27日
   修改内容   : Creat
*****************************************************************************/
extern VOS_UINT32 SI_PB_GetEccNumber_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    SI_PB_ECC_DATA_STRU                *pstEccData);




#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of SiAppPB.h */


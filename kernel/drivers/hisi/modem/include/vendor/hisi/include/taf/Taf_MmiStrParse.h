/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
  文 件 名   : Taf_MmiStrParse.h
  版 本 号   : 初稿
  生成日期   : 2008年3月14日
  最近修改   :
  功能描述   : 定义字符串解析的对外接口定义
  函数列表   :
  修改历史   :
  1.日    期   : 2008年3月14日
    修改内容   : 创建文件

******************************************************************************/

#ifndef __TAF_MMI_STR_PARSE_H__
#define __TAF_MMI_STR_PARSE_H__


/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  "TafTypeDef.h"
#include  "MnCallApi.h"
#include  "TafAppSsa.h"
#include  "TafAppMma.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* 因为新增的TafMmiEncode.c也要使用下面宏，从Taf_MmiStrParse.c移动到Taf_MmiStrParse.c */
/*****************************************************************************
  3 宏定义
*****************************************************************************/
#define  MMI_MAX_DTMF_STR_LEN           40
#define MN_MMI_MIN_USSD_LEN             2

#define MN_MMI_DONT_CARE_CHAR           '?'
#define MN_MMI_START_SI_CHAR            '*'
#define MN_MMI_STOP_CHAR                '#'

#define MN_MMI_isdigit(c)               (((c) >= '0') && ((c) <= '9'))

#define MN_MMI_STR_PTR_IS_VALID(pcFrom, pcTo)   ((VOS_NULL_PTR == (pcTo)) || ((VOS_NULL_PTR != (pcTo)) && ((pcFrom) <= (pcTo))))

#define MN_MMI_MAX(a, b)                (((a) > (b)) ? (a) : (b))

#define MN_MMI_MAX_SC_LEN               3                                       /* 目前来说，最大长度为3*/
#define MN_MMI_MAX_SIA_LEN              30                                      /* 来自于号码长度的最大限制 */
#define MN_MMI_MAX_SIB_LEN              8                                       /* PWD和PIN的长度 */
#define MN_MMI_MAX_SIC_LEN              8                                       /* PWD和PIN的长度 */

#define MN_MMI_MAX_BUF_SIZE             64
#define MN_MMI_MAX_PARA_NUM             4
/*****************************************************************************
  3类型定义
*****************************************************************************/
enum TAF_MMI_OPERATION_TYPE_ENUM
{
    TAF_MMI_CALL_ORIG,                                                           /*Setup a Call*/
    TAF_MMI_CALL_CHLD_REQ,
    TAF_MMI_CHANGE_PIN,
    TAF_MMI_CHANGE_PIN2,                                                         /*Change Pin*/
    TAF_MMI_UNBLOCK_PIN,                                                        /*Unblock Pin*/
    TAF_MMI_UNBLOCK_PIN2,
    TAF_MMI_DISPLAY_IMEI,                                                       /*Display IMEI*/
    TAF_MMI_REGISTER_SS,                                                        /*Register Operation*/
    TAF_MMI_ERASE_SS,                                                           /*Erase Operation*/
    TAF_MMI_ACTIVATE_SS,                                                        /*Activate Operation*/
    TAF_MMI_DEACTIVATE_SS,                                                      /*Deactivate Operation*/
    TAF_MMI_INTERROGATE_SS,                                                     /*Interrogate Operation*/
    TAF_MMI_REGISTER_PASSWD,                                                    /*Register the password*/
    /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    /* Delete TAF_MMI_GET_PASSWD */
    /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, end */
    TAF_MMI_FWD_CHECK_SS_IND,                                                   /*Forward Check Operation*/
    TAF_MMI_PROCESS_USSD_REQ,                                                   /*Process USSD Request*/
    TAF_MMI_SUPPRESS_CLIR,
    TAF_MMI_INVOKE_CLIR,
    TAF_MMI_SUPPRESS_CLIP,
    TAF_MMI_INVOKE_CLIP,
    TAF_MMI_SUPPRESS_COLR,
    TAF_MMI_INVOKE_COLR,
    TAF_MMI_SUPPRESS_COLP,
    TAF_MMI_INVOKE_COLP,
    TAF_MMI_NULL_OPERATION,                                                     /*Null Operation*/
    TAF_MMI_DEACTIVATE_CCBS,
    TAF_MMI_INTERROGATE_CCBS,
    TAF_MMI_MAX_OPERATION
};
typedef TAF_UINT8 MN_MMI_OPERATION_TYPE_ENUM_U8;

/* 因为新增的TafMmiEncode.c也要使用下面结构，从Taf_MmiStrParse.c移动到Taf_MmiStrParse.c */
typedef struct
{
    VOS_CHAR                            *pString;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enOperationType;
    VOS_UINT8                           aucRsv[3];
}MN_MMI_STR_OPERATION_Tbl_STRU;

typedef struct
{
    VOS_CHAR                            acSsCode[MN_MMI_MAX_SC_LEN + 1];
    VOS_CHAR                            acSia[MN_MMI_MAX_SIA_LEN + 1];
    VOS_CHAR                            acSib[MN_MMI_MAX_SIB_LEN + 1];
    VOS_CHAR                            acSic[MN_MMI_MAX_SIC_LEN + 1];
}MN_MMI_SC_SI_PARA_STRU;

typedef struct
{
    VOS_CHAR                            *pcMmiSc;                               /* MMI value of SC */
    VOS_UINT8                           ucNetSc;                                /* Network SC */
    VOS_UINT8                           aucRsv[3];
} MN_MMI_SC_TABLE_STRU;


typedef struct
{
    VOS_CHAR                            *pcMmiBs;                               /* MMI value of BS */
    VOS_UINT8                           ucNetBsCode;                            /* Network Basic Service Code */
    VOS_UINT8                           ucNetBsType;                            /* Network Basic Service Type */
    VOS_UINT8                           aucRsv[2];
} MN_MMI_BS_TABLE_STRU;

typedef struct
{
    VOS_CHAR                            *pcMmiChldStr;
    MN_CALL_SUPS_CMD_ENUM_U8            enChldOpType;
    VOS_UINT8                           aucRsv[3];
}MN_MMI_CHLD_OP_Tbl_STRU;

typedef struct
{
    VOS_CHAR                            *pcSsOpStr;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    VOS_UINT8                           aucRsv[3];
}MN_MMI_SS_OP_Tbl_STRU;

/*****************************************************************************
 结构名    : MN_MMI_OPERATION_PARAM_STRU
 结构说明  : MMI字符串解析结果数据结构
 修改历史:
  1.日    期   : 2013年05月06日
    修改内容   : SS FDN&Call Control，删除SubseqMmiOperationType 
*****************************************************************************/
typedef struct
{
    MN_MMI_OPERATION_TYPE_ENUM_U8       MmiOperationType;                       /*当前的操作类型*/

    TAF_UINT8                           aReserved[2];

    MN_CALL_ORIG_PARAM_STRU             MnCallOrig;
    MN_CALL_SUPS_PARAM_STRU             MnCallSupsReq;
    TAF_SS_REGISTERSS_REQ_STRU          RegisterSsReq;
    TAF_SS_ERASESS_REQ_STRU             EraseSsReq;
    TAF_SS_ACTIVATESS_REQ_STRU          ActivateSsReq;
    TAF_SS_DEACTIVATESS_REQ_STRU        DeactivateSsReq;
    TAF_SS_INTERROGATESS_REQ_STRU       InterrogateSsReq;
    TAF_SS_REGPWD_REQ_STRU              RegPwdReq;
    TAF_SS_GETPWD_RSP_STRU              GetPwdReq;
    TAF_SS_PROCESS_USS_REQ_STRU         ProcessUssdReq;
    TAF_PH_PIN_DATA_STRU                PinReq;
    MN_CALL_CLIR_CFG_ENUM_U8            enClir;
    TAF_SS_ERASECC_ENTRY_REQ_STRU       stCcbsEraseReq;

}MN_MMI_OPERATION_PARAM_STRU;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/

/*****************************************************************************
  6 接口函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : MN_MmiStringParse
 功能描述  : 将Mmi字串进行解析，将当前的MMI字串解析成对应的操作，以及操作需要的参数
 输入参数  : pInMmiStr       - 输入的MMI字串
             inCall          - 当前呼叫的状态，是处于呼叫状态，还是处于空闲状态
 输出参数  : ppOutRestMmiStr - 剩余字符串的起始地址
             pMmiOpParam     - 操作类型及其相应的参数
 返 回 值  : MN_ERR_NO_ERROR - 解析成功
             其余返回值      - 解析失败

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年3月17日
    修改内容   : 新生成函数
*****************************************************************************/
TAF_UINT32 MN_MmiStringParse(
    TAF_CHAR                            *pInMmiStr,
    TAF_BOOL                            inCall,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    TAF_CHAR                            **ppOutRestMmiStr
);


extern MN_CALL_CLIR_CFG_ENUM_U8  f_enClirOperate;

/**********************************************************
 函 数 名  : MMI_GetOporationTypeTblSize
 功能描述  : 获取补充业务操作码映射表的容量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 补充业务操作码映射表的容量
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日                                
    修改内容   : SS FDN&Call Control项目，
*************************************************************/
VOS_UINT32 MMI_GetOporationTypeTblSize(VOS_VOID);

/**********************************************************
 函 数 名  : MMI_GetOporationTypeTblAddr
 功能描述  : 获取通用补充业务操作码映射表的地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 通用补充业务操作码映射表的地址
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年05月06日                                
    修改内容   : SS FDN&Call Control项目，
*************************************************************/
MN_MMI_SS_OP_Tbl_STRU *MMI_GetOporationTypeTblAddr(VOS_VOID);

/*****************************************************************************
 函 数 名  : MMI_GetBSTblSize   
 功能描述  : 获取BS表容量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BS表容量

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MMI_GetBSTblSize(VOS_VOID);

/*****************************************************************************
 函 数 名  : MMI_GetBSTblAddr   
 功能描述  : 获取BS表地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : BS表地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    修改内容   : 新生成函数
*****************************************************************************/
MN_MMI_BS_TABLE_STRU *MMI_GetBSTblAddr(VOS_VOID);

/*****************************************************************************
 函 数 名  : MMI_GetSCTblSize   
 功能描述  : 获取SC表容量
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC表容量

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 MMI_GetSCTblSize(VOS_VOID);

/*****************************************************************************
 函 数 名  : MMI_GetSCTblSize   
 功能描述  : 获取SC表地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : SC表地址

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月06日
    修改内容   : 新生成函数
*****************************************************************************/
MN_MMI_SC_TABLE_STRU *MMI_GetSCTblAddr(VOS_VOID);

#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __TAF_MMI_STR_PARSE_H___ */


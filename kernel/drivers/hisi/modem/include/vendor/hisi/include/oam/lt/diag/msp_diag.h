/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : msp_diag.h
  Description     : msp_diag.h header file
  History         :
     1.w00182550       2012-11-20     Draft Enact
     2. 
******************************************************************************/

#ifndef __MSP_DIAG_H__
#define __MSP_DIAG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile                            
*****************************************************************************/
#include "vos.h"


#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
/*最好PS将MODID 和DIAG_AIR_MSG_LOG_ID的地方都替换成DIAG_ID*/
#define DIAG_ID(module_id, log_type)   (VOS_UINT32)(module_id | (log_type << 12))

#define MODID(module_id, log_type) DIAG_ID(module_id, log_type)

#define DIAG_AIR_MSG_LOG_ID(module_id, is_up_link)  DIAG_ID(module_id, is_up_link) /*module_id对应PID*/


/*is_up_link取值*/
#define OS_MSG_UL                (0x01)/* 表示上行消息*/
#define OS_MSG_DL                (0x02)/* 表示下行消息*/
#define LPS_OM_SPECIFY_FLG       (0x01)


#define DIAG_SIDE_UE             (0x1)  /* 表示UE接收的空口消息：NET-->UE*/
#define DIAG_SIDE_NET            (0x2)  /* 表示NET接收的空口消息：UE-->NET*/


/* 事件信息打印级别定义*/
#define LOG_TYPE_INFO            0x00000008UL
#define LOG_TYPE_AUDIT_FAILURE   0x00000004UL
#define LOG_TYPE_AUDIT_SUCCESS   0x00000002UL
#define LOG_TYPE_ERROR           0x00000001UL
#define LOG_TYPE_WARNING         0x00000010UL

/*DIAG消息ID定义*/
/*diag fw发给自己的解码消息处理请求*/
#define ID_MSG_DIAG_CMD_REQ_FW_TO_FW                (0x00010001)

/*diag fw发给AGENT模块的请求，以及相应的回复消息*/
#define ID_MSG_DIAG_CMD_REQ_FW_TO_AGENT             (0x00010002)
#define ID_MSG_DIAG_CMD_CNF_AGENT_TO_FW             (0x00010003)
#define ID_MSG_DIAG_HSO_DISCONN_IND                 (0x00010004)

/*diag fw发给APP AGENT模块的请求，以及相应的回复消息*/
#define ID_MSG_DIAG_CMD_REQ_FW_TO_APP_AGENT         (0x00010005)
#define ID_MSG_DIAG_CMD_CNF_APP_AGENT_TO_FW         (0x00010006)

/*diag AGENT发给BBP AGENT模块的请求*/
#define ID_MSG_REQ_DRX_DATA_SAMPLE_START            (0x00010009)
#define ID_MSG_REQ_DRX_DATA_SAMPLE_STOP             (0x0001000A)
#define ID_MSG_REQ_DRX_LOG_SAMPLE_START             (0x0001000B)
#define ID_MSG_REQ_DRX_LOG_SAMPLE_STOP              (0x0001000C)

#define ID_MSG_DIAG_CMD_IND                         (0x0001000D)

/*diag AGENT发给PS模块的HSO回放请求*/
#define ID_MSG_DIAG_CMD_REPLAY_TO_PS    			(0x00010100)


/*****************************************************************************
  3 Massage Declare 
*****************************************************************************/


/*****************************************************************************
  4 Enum 
*****************************************************************************/


/*****************************************************************************
   5 STRUCT 
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
/*****************************************************************************
 Function Name   : DIAG_PrintfV
 Description     : 打印上报接口，供PS调用
 Input           :VOS_UINT32 id          
                VOS_CHAR* pszFileName  
                VOS_UINT32 ulLineNum   
                VOS_CHAR* pszFmt       
                ...                    
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/

/*最大允许字节数,包括前面文件名和行号长度，-1是预留\0结束符*/
#define DIAG_PRINTF_MAX_LEN 	(1024-1)

extern VOS_UINT32 DIAG_PrintfV_TDS( VOS_CHAR* pszFmt, ...);

extern VOS_UINT32 DIAG_PrintfV_TDS1( VOS_UINT32 id ,VOS_CHAR* pszFmt, ...);

extern VOS_UINT32 DIAG_PrintfV(VOS_UINT32 id, VOS_CHAR* pszFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...);

/*****************************************************************************
 Function Name   : DIAG_ReportEventLog
 Description     : 事件上报接口，供PS调用
 Input           :VOS_UINT32 ulId       
                VOS_UINT32 ulEventID  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/
extern VOS_UINT32 DIAG_ReportEventLog(VOS_UINT32 ulId, VOS_UINT32 ulEventID);


/*****************************************************************************
 Function Name   : DIAG_ReportAirMessageLog
 Description     : L空口上报接口，供PS调用
 Input           :DIAG_AIR_MSG_LOG_STRU* pRptMessage  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulMessageID;  /* Specify the message id.*/
    VOS_UINT32 ulSideId;     /* 空口消息的方向*/
    VOS_UINT32 ulDestMod;    /* 目的模块*/
    VOS_UINT32 ulDataSize;   /* the data size in bytes.*/
    VOS_VOID* pData;      /* Pointer to the data buffer.*/
} DIAG_AIR_MSG_LOG_STRU;
extern VOS_UINT32 DIAG_ReportAirMessageLog(DIAG_AIR_MSG_LOG_STRU* pRptMessage);


/*****************************************************************************
 Function Name   : DIAG_ReportVoLTELog
 Description     : VoLTE消息上报接口，供IMS调用
 Input           :DIAG_AIR_MSG_LOG_STRU* pRptMessage
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.fuxin 00221597      2012-12-26  Draft Enact

*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulMessageID;  /* Specify the message id.*/
    VOS_UINT32 ulSideId;     /* VoLTE消息的方向,0x1:网侧到UE侧 0x2:UE侧到网侧 0xFFFFFFFF:为无效值,代表与方向无关*/
    VOS_UINT32 ulDestMod;    /* 目的模块*/
    VOS_UINT32 ulDataSize;   /* the data size in bytes.*/
    VOS_VOID*  pData;        /* Pointer to the data buffer.*/
} DIAG_VoLTE_LOG_STRU;

extern VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VoLTE_LOG_STRU* pRptMessage);
/*****************************************************************************
 Function Name   : DIAG_ReportGUAirMessageLog
 Description     : L空口上报接口，供PS调用
 Input           :VOS_VOID* pRptMessage  
                VOS_UINT16 ulMsgLen    
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/
typedef struct
{
    VOS_UINT8	    ucFuncType;
    VOS_UINT8       ucReserved1;
    VOS_UINT16      usLength;
    VOS_UINT32      ulSn;           /*Sequence Number for Trace, Event, OTA msg.*/
    VOS_UINT32      ulTimeStamp;    /*CPU time coming from ARM.*/
	VOS_UINT16      usPrimId;
    VOS_UINT16      usToolId;
	VOS_UINT16      usOtaMsgID;         /*空口消息的ID号*/
    VOS_UINT8       ucUpDown;           /*空口消息的方向*/
    VOS_UINT8       ucReserved;         /*逻辑信道类型*/
    VOS_UINT32      ulLengthASN;        /*空口消息内容的长度*/
	VOS_VOID*    pData;                 /* Pointer to the data buffer.*/
} DIAG_GU_AIR_MSG_LOG_STRU;
extern VOS_UINT32 DIAG_ReportGUAirMessageLog(VOS_VOID* pRptMessage,VOS_UINT16 ulMsgLen);


/*****************************************************************************
 Function Name   : DIAG_ReportLayerMessageLog
 Description     : 层间消息上报接口，供PS调用
 Input           :DIAG_LAYER_MSG_STRU* pRptMessage  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/
typedef DIAG_AIR_MSG_LOG_STRU DIAG_LAYER_MSG_STRU;

extern VOS_UINT32 DIAG_ReportLayerMessageLog(DIAG_LAYER_MSG_STRU* pRptMessage);

/*****************************************************************************
 Function Name   : DIAG_ReportUserPlaneMessageLog
 Description     : 用户面消息上报接口，供PS调用
 Input           :DIAG_USERPLANE_MSG_STRU* pRptMessage  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulMessageID;    /* Specify the message id.*/
    VOS_UINT32 ulDataSize;     /* the data size in bytes.*/
    VOS_VOID* pData;        /* Pointer to the data buffer.*/
} DIAG_USERPLANE_MSG_STRU;

extern VOS_UINT32 DIAG_ReportUserPlaneMessageLog(DIAG_USERPLANE_MSG_STRU* pRptMessage);

/*****************************************************************************
 Function Name   : DIAG_ReportCommand
 Description     : 命令上报接口，供PS和MSP调用
 Input           :VOS_UINT16 ulID        
                VOS_UINT32 ulDataSize  
                VOS_VOID* pData        
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/
extern VOS_UINT32 DIAG_ReportCommand(VOS_UINT16 ulID,VOS_UINT32 ulDataSize,VOS_VOID* pData);


/*****************************************************************************
 Function Name   : DIAG_ReportCommandPack
 Description     : MSP内部命令上报接口，封装了注册使用
 Input           :VOS_UINT32 ulID        
                VOS_UINT32 ulDataSize  
                VOS_VOID* pData        
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-11-20  Draft Enact 

*****************************************************************************/

VOS_UINT32 DIAG_ReportCommandPack(VOS_UINT32 ulID, VOS_VOID* pData, VOS_UINT32 ulDataSize);
/*****************************************************************************
 Function Name   : DIAG_GtrRcvCallBackReg
 Description     :自动化测试上报接口，供PS调用
 Input           :DIAG_GTR_DATA_RCV_PFN pfnGtrRcv  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-26  Draft Enact 

*****************************************************************************/
typedef VOS_UINT32 (*DIAG_GTR_DATA_RCV_PFN)(VOS_UINT32 ulGtrDtaSize, VOS_VOID* pGtrData);

extern VOS_VOID DIAG_GtrRcvCallBackReg(DIAG_GTR_DATA_RCV_PFN pfnGtrRcv);

/*****************************************************************************
 Function Name   : diag_LogPortSwitch
 Description     :diag log port切换，供AT使用
 Input           :ulLogPort   0:usb   1: vcom
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.y00228784     2012-12-26  Draft Enact

*****************************************************************************/
/*提供给AT调用*/
VOS_UINT32 diag_LogPortSwitch(VOS_UINT32 ulLogPort);

/*****************************************************************************
 Function Name   : diag_getLogPort
 Description     :返回当前端口号，供AT使用
 Input           :None
 Output          : None
 Return          : VOS_UINT32 0:usb   1: vcom

 History         :
    1.y00228784     2012-12-26  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_getLogPort(VOS_VOID);




/*****************************************************************************
  9 OTHERS
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

#endif /* end of msp_diag.h */

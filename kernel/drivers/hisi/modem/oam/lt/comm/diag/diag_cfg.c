/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_cfg.c
  Description     :
  History         :
     1.w00182550       2012-11-29   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -e830 -e525 -e550 -e539 -e628*/
/*lint -save -e537*/
#include "diag_common.h"
#include "diag_debug.h"
#include "diag_cfg.h"
#include "diag_cmd_id.h"
#include "msp_errno.h"
#include "LPsNvInterface.h"
#include "DrvInterface.h"
#if(VOS_OS_VER == VOS_LINUX)
#include "diag_port.h"
#include "diag_app_agent.h"
#else
#include "diag_agent.h"
#endif
/*lint -restore*/
/*lint -save -e767 原因:Log打印*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_CFG_C
/*lint -restore +e767*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define DIAG_CFG_PRINT_MODULE_NUM              (44)

/*lint -save -e40*/
VOS_UINT32 g_ulDiagCfgInfo = 0;
VOS_UINT8 g_LayerSrcModuleCfg[DIAG_CFG_PID_NUM] = {0}; 
VOS_UINT8 g_LayerDecModuleCfg[DIAG_CFG_PID_NUM] = {0};  
VOS_UINT8 g_PrintModuleCfg[DIAG_CFG_PID_NUM] = {0};
VOS_UINT32 g_PrintTotalCfg = DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE;
DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU g_stUserPlaneCfg[DIAG_CFG_USER_PLANE_ID_NUM] = {{0}};
DIAG_CFG_LOG_CAT_CFG_STRU g_stMsgCfg = {0};

/*lint -restore +e40*/
/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : diag_CfgResetAllSwt
 Description     : 重置开关状态
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-1  Draft Enact 

*****************************************************************************/
VOS_VOID diag_CfgResetAllSwt(VOS_VOID)
{

    /*清空空口开关等状态，清成1是因为DIAG初始化状态不能清*/
    g_ulDiagCfgInfo = 0x1;    

    /*清空层间开关状态*/
    VOS_MemSet(g_LayerSrcModuleCfg,0,sizeof(g_LayerSrcModuleCfg));
    VOS_MemSet(g_LayerDecModuleCfg,0,sizeof(g_LayerDecModuleCfg));
    
    /*清空打印开关状态*/
    VOS_MemSet(g_PrintModuleCfg,0,sizeof(g_PrintModuleCfg));    

    /*清空打印总开关状态*/
	g_PrintTotalCfg = DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE;

    /*清空用户面消息开关状态*/
    VOS_MemSet(g_stUserPlaneCfg,0,sizeof(g_stUserPlaneCfg));

    /*清空消息过滤开关状态*/
    VOS_MemSet(&g_stMsgCfg,0,sizeof(DIAG_CFG_LOG_CAT_CFG_STRU));


    return;
}

/*****************************************************************************
 Function Name   : diag_CfgSetGlobalBitValue
 Description     : 设置DIAG空口等开关状态
 Input           :VOS_UINT32* pstDiagGlobal       
                ENUM_DIAG_CFG_BIT enBit         
                VOS_UINT32 enSwtich  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-1  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_CfgSetGlobalBitValue(VOS_UINT32* pstDiagGlobal,ENUM_DIAG_CFG_BIT_U32 enBit,ENUM_DIAG_CFG_SWT_U8 enSwtich)
{
    /*设置为open 1时，需要使用|才能置该bit 为1*/
    if(DIAG_CFG_SWT_OPEN == enSwtich)
    {
        *pstDiagGlobal |=  ((VOS_UINT)1 << enBit);
    }
    /*设置为close 0时，需要使用&才能置该bit 为0*/
    else if(DIAG_CFG_SWT_CLOSE == enSwtich)
    {
        /*lint -save -e502*/
        *pstDiagGlobal &= ~((VOS_UINT)1 << enBit);
        /*lint -restore +e502*/
    }
    else
    {
        return ERR_MSP_INVALID_PARAMETER;
    }
    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 Function Name   : diag_CfgProcEntry
 Description     : 该函数为处理DIAG FW发过来的开关相关命令的入口
 Input           : pstReq 待处理数据
                   ulCmdSn 命令ID
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_CfgProcEntry (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
     VOS_UINT32 ret = ERR_MSP_SUCCESS; 
          
     switch(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
     {
          case DIAG_CMD_LOG_CAT_PRINT:
              ret = diag_PrintCfgProc(pstReq,ulCmdId);
              break;
          case DIAG_CMD_LOG_CAT_LAYER:
              ret = diag_LayerCfgProc(pstReq,ulCmdId);
              break;
          case DIAG_CMD_LOG_CAT_AIR:
              ret = diag_AirCfgProc(pstReq,ulCmdId);
              break;
          case DIAG_CMD_LOG_CAT_USERPLANE:
              ret = diag_UsrPlaneCfgProc(pstReq,ulCmdId);
              break;
          case DIAG_CMD_LOG_CAT_EVENT:
              ret = diag_EventCfgProc(pstReq,ulCmdId);
              break;
          case DIAG_CMD_LOG_CAT_MSG:
              ret = diag_MsgCfgProc(pstReq,ulCmdId);
              break;
          default:
              ret = ERR_MSP_FAILURE;
              break;
    }

    return ret;
}

/*****************************************************************************
 Function Name   : diag_AirCfgProc
 Description     : 该函数用于处理CfgProcEntry传进来的空口开关命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_AirCfgProc (VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_LOG_CAT_AIR_REQ_STRU* pstAirSwtReq = NULL;
    DIAG_CMD_LOG_CAT_AIR_CNF_STRU stAirSwtCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    ENUM_DIAG_CFG_SWT_U8 enLSwitch = 0;
    ENUM_DIAG_CFG_SWT_U8 enGuSwitch = 0;
    VOS_UINT32 ulSetRet = 0;/*lint !e958 */

    pstAirSwtReq = (DIAG_CMD_LOG_CAT_AIR_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));/*lint !e958 */

    /*设置LT空口开关值*/
    enLSwitch = DIAG_GET_CFG_SWT(pstAirSwtReq->ulSwitch);
    enGuSwitch = DIAG_GET_CFG_SWT(pstAirSwtReq->ulGuSwitch);
    
    ulSetRet = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_LT_AIR_BIT,enLSwitch);    

    /*设置GU空口开关值*/
    ulSetRet |= diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_GU_AIR_BIT,enGuSwitch);

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_AIR_CFG, pstAirSwtReq->ulSwitch, ulSetRet, 0);
    
    if(ERR_MSP_SUCCESS == ulSetRet)
    {
        stAirSwtCnf.ulRc = ERR_MSP_SUCCESS;
    }
    else
    {
        stAirSwtCnf.ulRc = ERR_MSP_FAILURE;
    }

#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stAirSwtCnf,ulCmdId,sizeof(DIAG_CMD_LOG_CAT_AIR_CNF_STRU));
#endif
    return ret;
}


/*****************************************************************************
 Function Name   : diag_CfgSetLayerSwt
 Description     : 设置层间消息开关
 Input           :DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq
                VOS_UINT32 ulCfgCnt
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.w00182550      2012-11-29  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_CfgSetLayerSwt(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq, VOS_UINT32 ulCfgSize)
{
    /*lint -save -e958*/
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    ENUM_DIAG_CFG_SWT_U8 enSwitch = 0;
    VOS_UINT32 j = 0;
    /*lint -restore*/
    if((0 == ulCfgSize)||(0 !=ulCfgSize %sizeof(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU)))
    {
        return  ERR_MSP_INVALID_PARAMETER;
    }

    /* 遍历某Category的开关配置项列表，查找对应的配置项进行设置*/
    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU);j++)
    {
		
        enSwitch = DIAG_GET_CFG_SWT((pstLayerReq + j)->ulSwitch);

                  /*lint -save -e40 -e63*/
		if(DIAG_CFG_MODULE_IS_INVALID((pstLayerReq + j)->ulModuleId ))
		{
			continue;
		}
		
		if( DIAG_CMD_LAYER_MOD_SRC == (pstLayerReq + j)->ulIsDestModule)
		{
			g_LayerSrcModuleCfg[(pstLayerReq + j)->ulModuleId - VOS_PID_DOPRAEND] = enSwitch;
		}
		else 
		{
			g_LayerDecModuleCfg[(pstLayerReq + j)->ulModuleId - VOS_PID_DOPRAEND] = enSwitch;
		}
		/*lint -restore  +e40 +e63*/
    }
        
	return ret;
}

/*****************************************************************************
 Function Name   : diag_LayerCfgProc
 Description     : 该函数用于处理CfgProcEntry传进来的层间开关命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_LayerCfgProc (VOS_UINT8* pstReq, VOS_UINT32 ulCmdId)
{
    MSP_DIAG_HEAD_STRU *pstDiagHead = NULL;
    DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerSwtReq = NULL;
    DIAG_CMD_LOG_CAT_LAYER_CNF_STRU stLayerSwtCnf = {0}; 
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet;    

    pstDiagHead = (MSP_DIAG_HEAD_STRU*)(DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq));

    pstLayerSwtReq = (DIAG_CMD_LOG_CAT_LAYER_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));
    
    
    /*设置层间模块开关到全局变量中*/
    ulSetRet = diag_CfgSetLayerSwt(pstLayerSwtReq, pstDiagHead->ulDataSize - sizeof(MSP_DIAG_DATA_REQ_STRU));

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_LAYER_CFG, ulSetRet, 0, 0);

    stLayerSwtCnf.ulRc = ulSetRet;
    stLayerSwtCnf.ulModuleId = pstLayerSwtReq->ulModuleId;

#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stLayerSwtCnf,ulCmdId,sizeof(DIAG_CMD_LOG_CAT_LAYER_CNF_STRU));
#endif
    return ret;
}


/*****************************************************************************
 Function Name   : diag_EventCfgProc
 Description     : 该函数用于处理CfgProcEntry传进来的事件开关命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_EventCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_LOG_CAT_EVENT_REQ_STRU* pstEvtSwtReq = NULL;
    DIAG_CMD_LOG_CAT_EVENT_CNF_STRU stEvtSwtCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet;
    ENUM_DIAG_CFG_SWT_U8 enSwitch =0;
      
    pstEvtSwtReq = (DIAG_CMD_LOG_CAT_EVENT_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    /*设置事件开关值*/
    enSwitch = DIAG_GET_CFG_SWT(pstEvtSwtReq->ulSwitch);
    ulSetRet = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_EVENT_BIT,enSwitch);
    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_EVENT_CFG, pstEvtSwtReq->ulSwitch, ulSetRet, 0);
    
    stEvtSwtCnf.ulRc = ulSetRet;
    stEvtSwtCnf.ulSwitch = pstEvtSwtReq->ulSwitch;

#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stEvtSwtCnf,ulCmdId,sizeof(DIAG_CMD_LOG_CAT_EVENT_CNF_STRU));
#endif
    return ret;
}

/*****************************************************************************
 Function Name   : diag_CfgSetUserPlaneSwt
 Description     : 设置用户面消息开关状态
 Input           :DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU *pstUserPlaneReq  
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-5  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_CfgSetUserPlaneSwt(DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU *pstUserPlaneReq,VOS_UINT32 ulCfgSize)
{
    /*lint -save -e958*/
    VOS_UINT32 i = 0,j = 0;
    ENUM_DIAG_CFG_SWT_U8 enSwitch =0;
    VOS_UINT32 ret = ERR_MSP_FAILURE;
    /*lint -restore*/
    if((0 == ulCfgSize)||(0 !=ulCfgSize % sizeof(DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU)))
    {
        return  ERR_MSP_INVALID_PARAMETER;
    }

    /* 遍历某Category的开关配置项列表，查找对应的配置项进行设置*/
    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU);j++)
    {
        enSwitch = DIAG_GET_CFG_SWT((pstUserPlaneReq + j)->ulSwitch);
        
        for(i=0;i<DIAG_CFG_USER_PLANE_ID_NUM;i++)
        {
            if(DIAG_NOT_SET_USERPALNE_MSGID == g_stUserPlaneCfg[i].ulMsgId)
            {
                g_stUserPlaneCfg[i].ulMsgId  = (pstUserPlaneReq + j)->ulMsgId;
                g_stUserPlaneCfg[i].ulSwitch = enSwitch;
                ret = ERR_MSP_SUCCESS;
				break;
            }

			if(g_stUserPlaneCfg[i].ulMsgId == (pstUserPlaneReq + j)->ulMsgId)
            {
                g_stUserPlaneCfg[i].ulSwitch = enSwitch;
                ret = ERR_MSP_SUCCESS;
				break;
            }
        }
    }
    return ret;
}
/*****************************************************************************
 Function Name   : diag_UsrPlaneCfgProc
 Description     : 该函数用于处理CfgProcEntry传进来的用户面开关命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_UsrPlaneCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU* pstUserPlaneSwtReq = NULL;
    DIAG_CMD_LOG_CAT_USERPLANE_CNF_STRU stUserPlaneSwtCnf = {0};
    MSP_DIAG_HEAD_STRU *pstDiagHead = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet;

    pstDiagHead = (MSP_DIAG_HEAD_STRU*)(DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq));

    pstUserPlaneSwtReq = (DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    
    /*设置用户面开关到全局变量中*/
    ulSetRet = diag_CfgSetUserPlaneSwt(pstUserPlaneSwtReq, pstDiagHead->ulDataSize - sizeof(MSP_DIAG_DATA_REQ_STRU));
	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_USEPLANE_CFG, ulSetRet, 0, 0);
	
    stUserPlaneSwtCnf.ulRc = ulSetRet;
    stUserPlaneSwtCnf.ulMsgId = pstUserPlaneSwtReq->ulMsgId;

#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stUserPlaneSwtCnf,ulCmdId,sizeof(DIAG_CMD_LOG_CAT_USERPLANE_CNF_STRU));
#endif
    return ret;
}

/*****************************************************************************
 Function Name   : diag_SetMsgCfgSwt
 Description     : 消息ID过滤开关设置
 Input           :DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq  
                VOS_UINT32 ulCfgSize                         
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-5  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_CfgSetMsgSwt(DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq,VOS_UINT32 ulCfgSize)
{
    /*lint -save -e958*/
    VOS_UINT32 i = 0,j = 0;
    ENUM_DIAG_CFG_SWT_U8 enSwitch =0;
    VOS_UINT32 ulRst = ERR_MSP_INVALID_PARAMETER;
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU *pstItemCfg =NULL;
    /*lint -restore*/
    /*参数检查*/
    if((0 == ulCfgSize)||(0 !=ulCfgSize % sizeof(DIAG_CMD_LOG_CAT_CFG_REQ_STRU)))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG_ERR, ulCfgSize, 0, 0);
        return ERR_MSP_DIAG_CMD_SIZE_INVALID;
    }

    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_CFG_REQ_STRU);j++)
    {
        
        /*仅支持层间消息CATEGORY过滤*/
        if(DIAG_CMD_LOG_CATETORY_LAYER_ID != (pstCatCfgReq + j)->ulCategory)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG_ERR, (pstCatCfgReq + j)->ulCategory, 0, 1);
            return ERR_MSP_NOT_SUPPORT;
        }
    }


    /* 遍历某Category的开关配置项列表，查找对应的配置项进行设置*/
    for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_CFG_REQ_STRU);j++)
    {
        enSwitch = DIAG_GET_CFG_SWT((pstCatCfgReq + j)->ulSwitch);
        
        for(i = 0; i < g_stMsgCfg.ulCfgCnt; i++)
        {
            pstItemCfg = (g_stMsgCfg.astMsgCfgList + i);
            
            if((pstCatCfgReq + j)->ulId == pstItemCfg->ulId)
            {
                pstItemCfg->ulSwt = enSwitch;
                return ERR_MSP_SUCCESS;
            }
        }

        /*目前仅一次支持DIAG_CFG_CAT_CFG_NUM个消息过滤*/
        if(g_stMsgCfg.ulCfgCnt < DIAG_CFG_CAT_CFG_NUM)
        {
            pstItemCfg = g_stMsgCfg.astMsgCfgList + g_stMsgCfg.ulCfgCnt;
            
            pstItemCfg->ulId  = (pstCatCfgReq + j)->ulId;
            pstItemCfg->ulSwt = (pstCatCfgReq + j)->ulSwitch;
            
            g_stMsgCfg.ulCfgCnt++;

            return ERR_MSP_SUCCESS;
        }
        else
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG_ERR, g_stMsgCfg.ulCfgCnt, 0, 3);
            return ERR_MSP_INVALID_PARAMETER;
        }


    }
    
    return ulRst;
    
}

/*****************************************************************************
 Function Name   : diag_MsgCfgProc
 Description     : 该函数用于处理CfgProcEntry传进来的消息开关命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_MsgCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_LOG_CAT_CFG_CNF_STRU stCatSwtCnf = {0};
    DIAG_CMD_LOG_CAT_CFG_REQ_STRU* pstCatCfgReq = NULL; 
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet;
    MSP_DIAG_HEAD_STRU *pstDiagHead = NULL;

    pstDiagHead = (MSP_DIAG_HEAD_STRU *)(DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq));

    pstCatCfgReq = (DIAG_CMD_LOG_CAT_CFG_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));


    /*设置消息过滤开关到全局变量中*/
    ulSetRet = diag_CfgSetMsgSwt(pstCatCfgReq,pstDiagHead->ulDataSize - sizeof(MSP_DIAG_DATA_REQ_STRU));

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_MSG, ulSetRet, 0, 0);

    stCatSwtCnf.ulRc = ulSetRet;
    stCatSwtCnf.ulId = pstCatCfgReq->ulId;

#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stCatSwtCnf,ulCmdId,sizeof(DIAG_CMD_LOG_CAT_CFG_CNF_STRU));
#endif
    return ret;
    
}

/*****************************************************************************
 Function Name   : diag_CfgSetPrintSwt
 Description     : 设置打印开关状态
 Input           :DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq  
                VOS_UINT32 ulCfgCnt                           
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.w00182550      2012-12-6  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_CfgSetPrintSwt(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq, VOS_UINT32 ulCfgSize)
{
    /*lint -save -e958*/
    VOS_UINT32 j = 0;
    VOS_UINT8 ucLevelFilter = 0;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    /*lint -restore*/
    if ((0 == ulCfgSize)||(0 != ulCfgSize % sizeof(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU)))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(DIAG_CFG_PRINT_TOTAL_MODULE == pstPrintReq->ulModuleId)
    {
        /*设置PRINT时首先重置所有模块设置*/
         VOS_MemSet(g_PrintModuleCfg,0,sizeof(g_PrintModuleCfg)); 
        
        /*设置打印总开关*/
        ucLevelFilter = DIAG_GET_PRINT_CFG_SWT(pstPrintReq->ulLevelFilter);
        g_PrintTotalCfg = ucLevelFilter;
    }
    else
    {
        /* 重置PRINT总开关0xFF模块*/
        g_PrintTotalCfg = DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE;

        /* 遍历某Category的开关配置项列表，查找对应的配置项进行设置*/
        for(j = 0 ; j< ulCfgSize /sizeof(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU);j++)
        {
              /*lint -save -e40 -e63*/
            if(DIAG_CFG_MODULE_IS_INVALID((pstPrintReq + j)->ulModuleId ))
            {
                //ret = ERR_MSP_INVALID_PARAMETER;
                continue;
            }

            ucLevelFilter = DIAG_GET_PRINT_CFG_SWT((pstPrintReq +j)->ulLevelFilter);

            g_PrintModuleCfg[(pstPrintReq +j)->ulModuleId - VOS_PID_DOPRAEND] = ucLevelFilter;
              /*lint -restore  +e40 +e63*/
        }
    }

	return ret;
}


/*****************************************************************************
 Function Name   : diag_PrintCfgProc
 Description     : 该函数用于处理CfgProcEntry传进来的打印开关命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_PrintCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    MSP_DIAG_HEAD_STRU *pstDiagHead = NULL;
    DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintSwtReq = NULL;
    DIAG_CMD_LOG_CAT_PRINT_CNF_STRU stPrintSwtCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet;

    pstDiagHead = (MSP_DIAG_HEAD_STRU*)(DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq));

    pstPrintSwtReq = (DIAG_CMD_LOG_CAT_PRINT_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));


    /*设置打印开关到全局变量中*/
    ulSetRet = diag_CfgSetPrintSwt(pstPrintSwtReq, pstDiagHead->ulDataSize - sizeof(MSP_DIAG_DATA_REQ_STRU));
    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_PRINT_CFG, ulSetRet, 0, 0);
    
    stPrintSwtCnf.ulRc = ulSetRet;

    stPrintSwtCnf.ulModuleId = pstPrintSwtReq->ulModuleId;
    
#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stPrintSwtCnf,ulCmdId,sizeof(DIAG_CMD_LOG_CAT_PRINT_CNF_STRU));
#endif
    return ret;

}
 
/*****************************************************************************
 Function Name   : diag_ConnProcEntry
 Description     : 该函数为处理DIAG FW发过来的HSO连接相关命令的入口
 Input           : pstReq 待处理数据
                   ulCmdId 命令ID
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_ConnProcEntry(VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    switch(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
    {
        case DIAG_CMD_HOST_CONNECT:
            ret = diag_ConnProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_HOST_DISCONNECT:
            ret = diag_DisConnProc(pstReq,ulCmdId);
            break;
#if(VOS_OS_VER == VOS_LINUX)
        case DIAG_CMD_SET_LOG_MODE:
            ret = diag_LogSaveProc(pstReq,ulCmdId);
            break;
#endif            
        default:
            ret = ERR_MSP_INVALID_PARAMETER;
            break;
    }
    return ret;
}

/*****************************************************************************
 Function Name   : diag_ConnProc
 Description     : 该函数用于处理ConnProcEntry传进来的HSO连接命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_ConnProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret      = ERR_MSP_SUCCESS;
    VOS_UINT32 ulCnfRst = ERR_MSP_UNAVAILABLE;  
#if (VOS_OS_VER == VOS_LINUX)
    DIAG_CMD_HOST_CONNECT_CNF_STRU stCnf = {0};
	NV_ITEM_PWC_SWITCH_STRU stPwrctrlSwitch = {0};
	VOS_UINT32 ulPwrFlag = 0;  
	LPS_SWITCH_PARA_STRU stDrxControlFlag = {0};
	UE_SW_BUILD_VER_INFO_STRU *pstBuildVer =NULL; 
	DIAG_CMD_REPLAY_SET_REQ_STRU stReplay={0};
#endif

    /*重置所有开关状态为未打开*/
    diag_CfgResetAllSwt();
    
    /*设置连接状态开关值*/
    ulCnfRst = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_CONN_BIT,DIAG_CFG_SWT_OPEN);

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_CONN_CFG, ulCnfRst, 0, 0);

#if (VOS_OS_VER == VOS_LINUX)
    VOS_MemSet(&(stCnf.stBuildVersion), 0, sizeof(DIAG_CMD_UE_BUILD_VER_STRU));

    /*获取版本信息*/
    pstBuildVer = BSP_GetBuildVersion();
	if(pstBuildVer!=NULL)
	{
        pstBuildVer->ulProductNo = BSP_HwGetVerMain();
        stCnf.stBuildVersion.usVVerNo        = pstBuildVer->ulVVerNo;
        stCnf.stBuildVersion.usRVerNo        = pstBuildVer->ulRVerNo;
        stCnf.stBuildVersion.usCVerNo        = pstBuildVer->ulCVerNo;
        stCnf.stBuildVersion.usBVerNo        = pstBuildVer->ulBVerNo;
        stCnf.stBuildVersion.usSpcNo         = pstBuildVer->ulSpcNo;
        stCnf.stBuildVersion.usHardwareVerNo = pstBuildVer->ulCustomVer;
        stCnf.stBuildVersion.ulProductNo     = pstBuildVer->ulProductNo;
	}

    /*获取IMEI号*/
    ret = diag_GetImei(stCnf.szImei);
    if(ret)
    {
    }

    /*获取软件版本号*/
    VOS_MemSet(&stCnf.stUeSoftVersion,0,sizeof(DIAG_CMD_UE_SOFT_VERSION_STRU));

    /*获取数采基地址*/
    stCnf.ulChipBaseAddr = (VOS_UINT32)BSP_OM_GetChipType();
    //stCnf.ulChipBaseAddr = (VOS_UINT32)V7R1_PILOT_CHIP;
    
    /*路测信息获取*/
    ret = NVM_Read(EN_NV_ID_AGENT_FLAG,&(stCnf.stAgentFlag),sizeof(NV_ITEM_AGENT_FLAG_STRU));
    if(ret)
    {
    }

    /*低功耗开关获取*/
  	ret = NVM_Read(EN_NV_ID_PWC_SWITCH,&stPwrctrlSwitch,sizeof(NV_ITEM_PWC_SWITCH_STRU));
    if(ret)
    {
    }
	ulPwrFlag = stPwrctrlSwitch.drxLBbpPd;

    ret = NVM_Read(EN_NV_ID_SWITCH_PARA,&stDrxControlFlag,sizeof(stDrxControlFlag));
    if(ret)
    {
    }
    stCnf.ulDrxControlFlag = stDrxControlFlag.ulDrxControlFlag & ulPwrFlag;
    /*lint -save -e40*/

	ulCnfRst |= diag_SendMsg(diag_GetAgentPid(),PS_PID_MM,ID_MSG_DIAG_CMD_REPLAY_TO_PS,(VOS_UINT8*)&stReplay,\
					sizeof(DIAG_CMD_REPLAY_SET_REQ_STRU));
    /*lint -restore  +e40*/
    /*获取当前存取模式*/
    stCnf.ulLpdMode = diag_GetLogSendType();
	
    /*处理结果*/
    stCnf.ulRc = ulCnfRst;

    /*组包给FW回复*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stCnf,ulCmdId,sizeof(DIAG_CMD_HOST_CONNECT_CNF_STRU));
#else
/*lint -e18 -e718 -e628 -e830 -e746*/
	diag_EnableSocpChan();
/*lint +e18 +e718 +e628 +e830 +e746*/
#endif
    return ret;
}


/*****************************************************************************
 Function Name   : diag_DisConnProc
 Description     : 该函数用于处理ConnProcEntry传进来的HSO断开命令
 Input           : pstReq 待处理数据
 Output          : None
 Return          : VOS_UINT32
 
 History         :
    1.y00228784      2012-11-22  Draft Enact 

*****************************************************************************/
VOS_UINT32 diag_DisConnProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_HOST_DISCONNECT_CNF_STRU stCnfDisConn = {0};
    VOS_UINT32 ulRst = ERR_MSP_SUCCESS;
   
    /*重置所有开关状态为未打开*/
    diag_CfgResetAllSwt();
        
    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DIS_CONN_CFG, 0, 0, 0);

    stCnfDisConn.ulRc = ulRst;

#if(VOS_OS_VER == VOS_LINUX)
    /*组包给FW回复*/
    ulRst = diag_AgentCnfFun((VOS_UINT8*)&stCnfDisConn,ulCmdId,sizeof(DIAG_CMD_HOST_DISCONNECT_CNF_STRU));
#endif
    return ulRst;
}
/*lint +e830 +e525 +e550 +e539 +e628*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


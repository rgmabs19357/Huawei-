#include <linux/kthread.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <BSP.h>
#include <platdrv.h>

#define DBG_FLAG 0

#ifdef DBG_FLAG
#define DBG(args...)	printk(args)
#else
#define DBG(args...)	do { } while(0)
#endif

extern void set_mcu_mntn_on_off(u8 ucMntnOnOff);
static OM_RSP_FUNC *om_response_hook = NULL;   /*send om response hook*/
static DRV_TRACE_PERMISSION *trace_option_table = NULL;   /*trace permission table*/
MPS_PROC_S om_msp_hooks = {NULL};

static DRV_PWRCTRL_CPULOAD_SWITCH_STRU mntn_cpu_load_switch = {0};
static DRV_PWRCTRL_SLEEP_SWITCH_STRU mntn_sleep_switch = {0};

/***********************************************************************************
 Function:          omDrvTraceReqEntry
 Description:       om查询函数
 Calls:
 Input:             pReqPacket,
                    pRsqFuncPtr
 Output:            pReqPacket,
                    pRsqFuncPtr
 Return:            NA
 ************************************************************************************/
BSP_VOID BSP_MNTN_OmDrvTraceReqEntry(OM_REQ_PACKET_STRU *pReqPacket, OM_RSP_FUNC *pRsqFuncPtr)
{
	BSP_U16 req_len = 0x0;
	DRV_TRACE_REQ_STRU *trace_req = NULL;
	DRV_TRACE_IND_STRU trace_rsp;
    DRV_TRACE_PERMISSION *perm = NULL;

	if ((NULL == pReqPacket) |(NULL == pRsqFuncPtr)){
		printk(KERN_ERR"%s para error ReqPacket %p pRsqFuncPtr %p!\n", __FUNCTION__, pReqPacket, pRsqFuncPtr);
		return;
	}

	trace_req = (DRV_TRACE_REQ_STRU *)pReqPacket;

	switch (trace_req->usPrimId)
	{
		case DRV_PRIM_SEND_CONF_REQ:
			om_response_hook = pRsqFuncPtr;

			req_len = trace_req->usLength - (sizeof(DRV_TRACE_REQ_STRU) - 4) + 4;
			if (req_len % sizeof(DRV_TRACE_PERMISSION) != 0) {
				printk("recieve SDT Conf req ERROR\n");
				memset(trace_req->aucData, 0x00, 0x04 );
				return;
			}

			if (NULL != trace_option_table){
				kfree(trace_option_table);
				trace_option_table = NULL;
			}

			trace_option_table = (DRV_TRACE_PERMISSION *)kmalloc(req_len +
									sizeof(DRV_TRACE_PERMISSION), GFP_KERNEL);
			if (NULL == trace_option_table) {
				printk("omDRV  malloc permission error\n");
				return;
			}

			/*modified for lint e665 */
			memset(trace_option_table, 0x0, (req_len + sizeof(DRV_TRACE_PERMISSION)));
			memcpy(trace_option_table, trace_req->aucData, req_len);
			perm = (DRV_TRACE_PERMISSION *)((DRV_TRACE_PERMISSION *)trace_option_table
			                                + req_len / sizeof(DRV_TRACE_PERMISSION));
			perm->usPrimId = INVALID_PRIM_ID;
			perm->usVal = 0x0000;

			perm = trace_option_table;
			while(INVALID_PRIM_ID !=perm->usPrimId){
                if (DRV_PRIM_MCU_SWITCH == perm->usPrimId)
                {
                    set_mcu_mntn_on_off((u8)perm->usVal);
                }
				printk("primId:%#x,val:%#x\n",perm->usPrimId, perm->usVal);
				perm++;
			}
	   		memset((char *)(&trace_rsp + 1), 0xFF, 0x04);
			break;

	    case PWRCRL_CPULOAD_SWTICH:
	        memcpy(&mntn_cpu_load_switch, trace_req->aucData, sizeof(mntn_cpu_load_switch));
	        printk("config ACPU cpuload switch: %d\n", mntn_cpu_load_switch.acpu);
	        break;

        case PWRCRL_SLEEP_SWTICH:
            trace_rsp.usPrimId = (BSP_U16)PWRCRL_SLEEP_SWTICH;
            trace_rsp.ulModuleId = (BSP_U32)DRV_MODULE_ID_MNTN;
            memcpy(&mntn_sleep_switch, trace_req->aucData, sizeof(mntn_sleep_switch));
            printk("config ACPU sleep switch: %d\n", mntn_sleep_switch.acpu);
            break;

		default:
			return;
	}

	trace_rsp.usPrimId   = DRV_PRIM_SEND_CONF_RSP;
	trace_rsp.ulModuleId = DRV_MODULE_ID_MNTN;
	trace_rsp.usLength   = sizeof(trace_rsp) - 4;
	trace_rsp.ucFuncType = DRV_FUNCTION_TRACE;
	trace_rsp.usReserve  = trace_req->usReserve;

	if(NULL == om_msp_hooks.OM_AddSNTime){
		return;
	}

	(*(om_msp_hooks.OM_AddSNTime))(&(trace_rsp.ulSn), &(trace_rsp.ulTimeStamp));

	if(OSAL_OK != (*pRsqFuncPtr)((OM_RSP_PACKET_STRU *)&trace_rsp, sizeof(trace_rsp))){
		DBG("send rsp error\n");
	}else{
		DBG("send is ok\n");
	}

	return;
}

/***********************************************************************************
 Function:          BSP_MNTN_DrvPrimCanSendOrNot
 Description:       usb_mntn模块查询函数
 Calls:
 Input:             usPrimId
 Output:            NA
 Return:            NA
 ************************************************************************************/
BSP_S32 BSP_MNTN_DrvPrimCanSendOrNot(BSP_U16 usPrimId)
{
	DRV_TRACE_PERMISSION *perm = NULL;

	if ((NULL == om_response_hook)||(NULL == trace_option_table))
	{
		return OSAL_ERROR;
	}

	perm = trace_option_table;
	while (INVALID_PRIM_ID != perm->usPrimId){
		if (perm->usPrimId == usPrimId){
			if(PRIM_SEND_PERMIT == perm->usVal){
				return OSAL_OK;
			}
			return OSAL_ERROR;
		}
		perm++;
	}

	return OSAL_ERROR;
}

/***********************************************************************************
 Function:          BSP_MNTN_OmDrvTraceSend
 Description:       OM发送函数
 Calls:
 Input:             usPrimId
                    ulModuleId
                    buffer
                    ulLength
 Output:            NA
 Return:            NA
 ************************************************************************************/
BSP_S32 BSP_MNTN_OmDrvTraceSend(BSP_U16 usPrimId, BSP_U32 ulModuleId, BSP_U8 *buffer, BSP_U32 ulLength)
{
	DRV_TRACE_IND_STRU *trace_rsp = NULL;

	if ((NULL == buffer) || (0 == ulLength)){
		return OSAL_ERROR;
	}

	if ((NULL == om_msp_hooks.OM_AddSNTime) || (NULL == om_response_hook)){
		return OSAL_ERROR;
	}

	trace_rsp = (DRV_TRACE_IND_STRU *)(buffer - sizeof(DRV_TRACE_IND_STRU) + 4);
	trace_rsp->usPrimId = usPrimId;
	trace_rsp->ulModuleId = ulModuleId;
	trace_rsp->usLength = (BSP_U16)(ulLength + sizeof(DRV_TRACE_IND_STRU) - 8);
	trace_rsp->ucFuncType = DRV_FUNCTION_TRACE;

	(*(om_msp_hooks.OM_AddSNTime))(&(trace_rsp->ulSn), &(trace_rsp->ulTimeStamp));

	if (OSAL_OK != (*om_response_hook)((OM_RSP_PACKET_STRU *)trace_rsp, trace_rsp->usLength + 4)){
		return OSAL_ERROR;
	}

	return OSAL_OK;
}

BSP_S32 BSP_MNTN_OmDrvReplayTraceSend(BSP_U16 usPrimId, BSP_U32 ulModuleId, BSP_U8 *buffer, BSP_U32 ulLength)
{
	DRV_TRACE_IND_STRU *trace_rsp;
	static int i = 0;

	if ((NULL == buffer) || (0 == ulLength)){
		printk(KERN_ERR"usb laction info error\n");
		return OSAL_ERROR;
	}

	if ((NULL == om_response_hook) || (NULL == om_msp_hooks.OM_AddSNTime)){
		printk(KERN_ERR"msp hook error\n");
		return OSAL_ERROR;
	}

	trace_rsp = (DRV_TRACE_IND_STRU *)(buffer - sizeof(DRV_TRACE_IND_STRU));
	trace_rsp->usPrimId   = usPrimId;
	trace_rsp->ulModuleId = ulModuleId;
	trace_rsp->usLength   = (BSP_U16)(ulLength + sizeof(DRV_TRACE_IND_STRU) + sizeof(DRV_REPALY_IND_STRU) - 8);
	trace_rsp->ucFuncType = DRV_FUNCTION_TRACE;

	(*(om_msp_hooks.OM_AddSNTime))(&(trace_rsp->ulSn), &(trace_rsp->ulTimeStamp));

	if (OSAL_OK != (*om_response_hook)((OM_RSP_PACKET_STRU *)trace_rsp, trace_rsp->usLength + 4)){
		if(0 == (i % 50)){
			printk(KERN_ERR"BSP_MNTN_OmDrvReplayTraceSend rsp error\n");
		}
		i++;
		return OSAL_ERROR;
	}

	return OSAL_OK;
}

/***********************************************************************************
 Function:          BSP_MspProcReg
 Description:       DRV提供给MSP的注册函数
 Calls:
 Input:             MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
 Output:            NA
 Return:            NA
 ************************************************************************************/
BSP_VOID BSP_MspProcReg(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc)
{
	BSP_U32 ret_reg = OSAL_OK;

	if(NULL == pFunc){
		printk(KERN_ERR"pFunc is error!\n");
		return;
	}

	if (eFuncID < 0 || eFuncID >= MSP_PROC_REG_ID_MAX){
		printk(KERN_ERR"eFuncID is error\n");
		return;
	}

	/*lint -e661*/
	((BSP_U32*)(&om_msp_hooks))[eFuncID] = (BSP_U32)pFunc;
	/*lint +e661*/

    if (0 == eFuncID){
        ret_reg |= (*(om_msp_hooks.OM_RegisterRequestProcedure))(DRV_FUNCTION_TRACE, BSP_MNTN_OmDrvTraceReqEntry);
        if (OSAL_OK !=ret_reg){
            (void)printk("OM_RegisterRequestProcedure reg!\n");
            return;
        }
    }

	return;
}

EXPORT_SYMBOL(BSP_MspProcReg);
EXPORT_SYMBOL(BSP_MNTN_OmDrvTraceSend);
EXPORT_SYMBOL(BSP_MNTN_DrvPrimCanSendOrNot);


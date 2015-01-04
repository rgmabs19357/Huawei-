/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : AtCmdFtmProc.c
  版 本 号   : 初稿
  生成日期   : 2013年3月13日
  最近修改   :
  功能描述   : 工程测试命令处理文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年3月13日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "AtCmdFtmProc.h"
#include "ATCmdProc.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_FTM_PROC_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : At_SetLogPortPara
 功能描述  : ^LOGPORT的设置函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月20日
    修改内容   : 新生成函数
  2.日    期   : 2013年8月9日
    修改内容   : LOG35_TL调用TL接口
*****************************************************************************/
VOS_UINT32 At_SetLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulOmLogPort;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex != 1)
    {
        return AT_ERROR;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulRslt = diag_LogPortSwitch(gastAtParaList[0].ulParaValue);

    if (VOS_OK != ulRslt)
    {
        AT_WARN_LOG1("At_SetLogPortPara TL Error, Para: %d \n", gastAtParaList[0].ulParaValue);
        AT_WARN_LOG1("At_SetLogPortPara TL Error, Result: 0x%x \n", ulRslt);

        return AT_ERROR;
    }
#endif

    if (AT_LOG_PORT_USB == gastAtParaList[0].ulParaValue)
    {
        ulOmLogPort = COMM_LOG_PORT_USB;
    }
    else
    {
        ulOmLogPort = COMM_LOG_PORT_VCOM;
    }

    /* 调用OM的接口 */
    ulRslt = GU_OamLogPortSwitch(ulOmLogPort);

    if (VOS_OK == ulRslt)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_QryLogPortPara
 功能描述  : ^LOGPORT的查询函数
 输入参数  : VOS_UINT8 ucIndex
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月20日
    修改内容   : 新生成函数
  2.日    期   : 2013年8月9日
    修改内容   : LOG35_TL调用TL接口
*****************************************************************************/
VOS_UINT32 At_QryLogPortPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulOmLogPort;
    VOS_UINT32                          ulAtLogPort;
    VOS_UINT32                          ulRslt;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulTlLogPort;
#endif

    usLength                            = 0;
    ulOmLogPort                         = AT_LOG_PORT_USB;

    ulRslt = GU_OamQueryLogPort(&ulOmLogPort);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    if (COMM_LOG_PORT_USB == ulOmLogPort)
    {
        ulAtLogPort = AT_LOG_PORT_USB;
    }
    else
    {
        ulAtLogPort = AT_LOG_PORT_VCOM;
    }

#if (FEATURE_ON == FEATURE_LTE)
    ulTlLogPort = diag_getLogPort();
    if (ulAtLogPort != ulTlLogPort)
    {
        vos_printf("\n At_QryLogPortPara ulAtLogPort: %d \n", ulAtLogPort);
        vos_printf("\n At_QryLogPortPara ulTlLogPort: %d \n", ulTlLogPort);
    }
#endif

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulAtLogPort);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


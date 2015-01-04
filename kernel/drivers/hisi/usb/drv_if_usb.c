/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : usb_api.c
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2012年9月15日
  最近修改   :
  功能描述   : USB模块对外接口实现,接口定义参见接口文档
  函数列表   :
  修改历史   :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include  <linux/slab.h>
#include  <linux/kernel.h>
#include  <linux/module.h>
#include  "drv_usb.h"
#include  "drv_usb_if.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
PNP_CALLBACK_STACK* pEnableStack = NULL;
PNP_CALLBACK_STACK* pDisableStack = NULL;

int g_usb_enum_complete = 0;


/*****************************************************************************
  3 函数实现
*****************************************************************************/

/*****************************************************************************
   与NAS的接口实现，包含打桩实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : BSP_USB_RegUdiEnableCB
 功能描述  : 协议栈通知USB上层应用打开UDI设备端口
 输入参数  : USB_UDI_ENABLE_CB_T pFunc  : USB使能回调函数指针
 输出参数  : 无
 返 回 值  : unsigned int: 0表示成功 1表示失败,与VOS定义的返回值类型一致
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 自V3R2移植函数

*****************************************************************************/
unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc)
{
    PNP_CALLBACK_STACK* tmp = pEnableStack;

    USB_API_DBG("enter\n");

    if (NULL == pFunc)
    {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }

    pEnableStack = (PNP_CALLBACK_STACK*) kmalloc(sizeof(PNP_CALLBACK_STACK), M_ZERO);

    pEnableStack->pPre = tmp;
    pEnableStack->pCallback = pFunc;

    if(g_usb_enum_complete)
    {
        pEnableStack->pCallback();
    }

    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_RegUdiDisableCB
 功能描述  : 协议栈通知USB上层应用关闭UDI设备端口
 输入参数  : USB_UDI_DISABLE_CB_T pFunc  : USB使能回调函数指针
 输出参数  : 无
 返 回 值  : unsigned int: 0表示成功 1表示失败,与VOS定义的返回值类型一致
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 自V3R2移植函数

*****************************************************************************/
unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc)
{
    PNP_CALLBACK_STACK* tmp = pDisableStack;

    USB_API_DBG("enter\n");

    if (NULL == pFunc)
    {
        USB_API_DBG("pFunc NULL\n");
        return 1;
    }

    pDisableStack = (PNP_CALLBACK_STACK*) kmalloc(sizeof(PNP_CALLBACK_STACK), M_ZERO);

    pDisableStack->pPre = tmp;
    pDisableStack->pCallback = pFunc;

    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_UdiEnableNotify
 功能描述  : USB模块调用上层注册回调通知上层USB已经OK，可以打开UDI
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 自V3R2移植函数

*****************************************************************************/
void BSP_USB_UdiEnableNotify (void)
{
    PNP_CALLBACK_STACK* pEnableFunc = pEnableStack;
    /* 模拟USB插入通知 */
    while (pEnableFunc)
    {
        pEnableFunc->pCallback();
        pEnableFunc = pEnableFunc->pPre;
    }
    g_usb_enum_complete = 1;
}

/*****************************************************************************
 函 数 名  : BSP_USB_UdiDisableNotify
 功能描述  : USB模块调用上层注册回调通知上层USB已经关闭，需要关闭UDI
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 自V3R2移植函数

*****************************************************************************/
void BSP_USB_UdiDisableNotify (void)
{
    PNP_CALLBACK_STACK* pDisableFunc = pDisableStack;
    /* 模拟USB插入通知 */
    while (pDisableFunc)
    {
        pDisableFunc->pCallback();
        pDisableFunc = pDisableFunc->pPre;
    }
    g_usb_enum_complete = 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetDiagModeValue
 功能描述  : 获取设备拨号类型
 输入参数  : unsigned char *dial_mode  : 拨号类型
             unsigned char *cdc_spec   : CDC规范
 输出参数  : 无
 返 回 值  : int:打桩实现，默认返回1（VOS_ERR）
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 自V3R2移植函数

*****************************************************************************/
int BSP_USB_GetDiagModeValue(unsigned char *dial_mode, unsigned char *cdc_spec)
{
    return 1;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetLinuxSysType
 功能描述  : 查询系统是否为Linux
 输入参数  : void
 输出参数  : 无
 返 回 值  : int:打桩实现，默认返回-1
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int BSP_USB_GetLinuxSysType(void)
{
    return -1;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetPortMode
 功能描述  : 获取端口形态模式
 输入参数  : char* PsBuffer         :用于存放端口形态名称和端口号
             unsigned long* Length  :获取PsBuffer长度
 输出参数  : 无
 返 回 值  : unsigned char:打桩实现，默认返回1（VOS_ERR）
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned char BSP_USB_GetPortMode(char* PsBuffer, unsigned long* Length )
{
    return 1;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetU2diagDefaultValue
 功能描述  : 获取端口默认u2diag值
 输入参数  : void
 输出参数  : 无
 返 回 值  : unsigned int:打桩实现，默认返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int BSP_USB_GetU2diagDefaultValue(void)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_NASSwitchGatewayRegFunc
 功能描述  : 用于NAS注册切换网关通知回调函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int :打桩实现，默认返回0（VOS_OK）
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int BSP_USB_NASSwitchGatewayRegFunc(USB_NET_DEV_SWITCH_GATEWAY switchGwMode)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_SetPid
 功能描述  : 设置PID的值
 输入参数  : unsigned char u2diagValue
 输出参数  : 无
 返 回 值  : int :打桩实现，默认返回1（VOS_ERR）
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
int BSP_USB_SetPid(unsigned char u2diagValue)
{
    return 1;
}

/*****************************************************************************
   与OAM的接口实现，包含打桩实现
*****************************************************************************/






/*****************************************************************************
   与TTF的接口实现，包含打桩实现
*****************************************************************************/

/*****************************************************************************
 函 数 名  : USB_ETH_DrvSetRxFlowCtrl
 功能描述  : 本接口设置流控
 输入参数  : unsigned long ulParam1  :保留为扩展用
             unsigned long ulParam2  :保留为扩展用
 输出参数  : 无
 返 回 值  : unsigned long :打桩实现，默认返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long USB_ETH_DrvSetRxFlowCtrl(unsigned long ulParam1, unsigned long ulParam2)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : USB_ETH_DrvClearRxFlowCtrl
 功能描述  : 本接口解除流控
 输入参数  : unsigned long ulParam1  :保留为扩展用
             unsigned long ulParam2  :保留为扩展用
 输出参数  : 无
 返 回 值  : unsigned long :打桩实现，默认返回0
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年9月15日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long USB_ETH_DrvClearRxFlowCtrl(unsigned long ulParam1, unsigned long ulParam2)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_PortTypeValidCheck
 功能描述  : 提供给上层查询设备端口形态配置合法性接口
             1、端口为已支持类型，2、包含PCUI口，3、无重复端口，4、端点数不超过16，
             5、第一个设备不为MASS类
 输入参数  : pucPortType  端口形态配置
             ulPortNum    端口形态个数
 输出参数  : 无
 返 回 值  : unsigned int 0-端口形态合法 其它-端口形态非法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned long ulPortNum)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_GetAvailabePortType
 功能描述  : 提供给上层查询当前设备支持端口形态列表接口
 输入参数  : ulPortMax    协议栈支持最大端口形态个数
 输出参数  : pucPortType  支持的端口形态列表
             pulPortNum   支持的端口形态个数
 返 回 值  : unsigned int 0-获取端口形态列表成功 其它-获取端口形态列表失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int BSP_USB_GetAvailabePortType(unsigned char *pucPortType, unsigned long *pulPortNum, unsigned long ulPortMax)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : BSP_USB_PortTypeQuery
 功能描述  : 查询当前的设备枚举的端口形态值
 输入参数  : 无
 输出参数  : stDynamicPidType  端口形态
 返 回 值  : unsigned int 0-查询成功 其它-查询失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年10月9日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
unsigned int BSP_USB_PortTypeQuery(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType)
{
    return 0;
}

/*****************************************************************************
 函 数 名  : l2_notify_register
 功能描述  : L2状态进入退出通知回调函数注册接口
 输入参数  : FUNC_USB_LP_NOTIFY *pUSBLPFunc回调函数指针
 输出参数  : 无
 返 回 值  : 0:    注册成功
           其他：注册失败
*****************************************************************************/
int l2_notify_register(FUNC_USB_LP_NOTIFY pUSBLPFunc)
{
    return ERROR;
}

/*提供给NAS的接口*/
EXPORT_SYMBOL(BSP_USB_RegUdiEnableCB);
EXPORT_SYMBOL(BSP_USB_RegUdiDisableCB);
EXPORT_SYMBOL(BSP_USB_UdiEnableNotify);
EXPORT_SYMBOL(BSP_USB_UdiDisableNotify);
EXPORT_SYMBOL(BSP_USB_GetDiagModeValue);
EXPORT_SYMBOL(BSP_USB_GetU2diagDefaultValue);
EXPORT_SYMBOL(BSP_USB_SetPid);
EXPORT_SYMBOL(BSP_USB_GetPortMode);
EXPORT_SYMBOL(BSP_USB_GetLinuxSysType);
EXPORT_SYMBOL(BSP_USB_NASSwitchGatewayRegFunc);
EXPORT_SYMBOL(BSP_USB_PortTypeValidCheck);
EXPORT_SYMBOL(BSP_USB_GetAvailabePortType);
EXPORT_SYMBOL(BSP_USB_PortTypeQuery);

/*提供给OAM的接口*/
EXPORT_SYMBOL(l2_notify_register);

/*提供给TTF的接口*/
EXPORT_SYMBOL(USB_ETH_DrvSetRxFlowCtrl);
EXPORT_SYMBOL(USB_ETH_DrvClearRxFlowCtrl);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


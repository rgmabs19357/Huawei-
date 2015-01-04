

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "drv_global.h"


#ifndef __DRV_PMU_H__
#define __DRV_PMU_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 宏定义
*****************************************************************************/

/*****************************************************************************
  3 枚举定义
*****************************************************************************/
/*通信模块供电的 CONSUMER的id枚举*/
typedef enum EM_MODEM_CONSUMER_ID_E
{
    MODEM_PA0,
    MODEM_RFIC0_ANALOG0,
    MODEM_RFIC0_ANALOG1,
    MODEM_FEM0,
    MODEM_PA_VBIAS0,
    MODEM_PA1,
    MODEM_RFIC1_ANALOG0,
    MODEM_RFIC1_ANALOG1,
    MODEM_FEM1,
    MODEM_PA_VBIAS1,
    MODEM_SIM0,
    MODEM_SIM1,
    MODEM_FEM0_AUX,
    MODEM_CONSUMER_ID_BUTT
}EM_MODEM_CONSUMER_ID;

/*PA动态电压枚举*/
typedef enum EM_MODEM_PA_DYNAMIC_VOLTAGE_ID_E
{
    MODEM_PA_LOW_POWER_VOLTAGE,
}EM_MODEM_PA_DYNAMIC_VOLTAGE_ID;
/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/


/*****************************************************************************
  7 UNION定义
*****************************************************************************/


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
/*****************************************************************************
 函 数 名  : DRV_GET_PMU_STATE
 功能描述  : 获取PMU模块开机方式、充电状态、电池电量、电池在位状态。
 输入参数  : 无。
 输出参数  : Pmu_State :开机方式、充电状态、电池电量、电池在位状态。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项　：该接口仅在PS的PC工程中使用，目前没有应用，暂保留。
*****************************************************************************/
extern unsigned int DRV_GET_PMU_STATE(void*  Pmu_State);

/*****************************************************************************
 函 数 名  : BSP_PMU_UsbEndRegActionFunc
 功能描述  : 本接口是USB插入/拔出回调注册函数。
 输入参数  : srcFunc：注册的USB插入或拔出动作发生时的回调函数指针。
             actionIndex：动作指示。
                          0：参数srcFunc是注册的USB插入动作的回调函数；
                          1：参数srcFunc是注册的USB拔出动作的回调函数。

 输出参数  : 无。
 返 回 值  : 0:  操作成功；
             -1：操作失败。
 注意事项  ：调用此接口，将所要执行的函数指针传入，即在USB插入或拔出时调用所要执行的函数。
*****************************************************************************/
extern int BSP_PMU_UsbEndRegActionFunc(pFUNCPTR srcFunc, unsigned char actionIndex);
#define DRV_USB_ENDREGACTION_FUNC(srcFunc,actionIndex) \
                BSP_PMU_UsbEndRegActionFunc(srcFunc,actionIndex)


/*****************************************************************************
函数名：   BSP_USB_PortTypeValidCheck
功能描述:  提供给上层查询设备端口形态配置合法性接口
           1、端口为已支持类型，2、包含PCUI口，3、无重复端口，4、端点数不超过16，
           5、第一个设备不为MASS类
输入参数： pucPortType  端口形态配置
           ulPortNum    端口形态个数
返回值：   0:    端口形态合法
           其他：端口形态非法
*****************************************************************************/
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned long ulPortNum);
#define DRV_USB_PORT_TYPE_VALID_CHECK(pucPortType, ulPortNum)  \
                    BSP_USB_PortTypeValidCheck(pucPortType, ulPortNum)

/*****************************************************************************
函数名：   BSP_USB_GetAvailabePortType
功能描述:  提供给上层查询当前设备支持端口形态列表接口
输入参数： ulPortMax    协议栈支持最大端口形态个数
输出参数:  pucPortType  支持的端口形态列表
           pulPortNum   支持的端口形态个数
返回值：   0:    获取端口形态列表成功
           其他：获取端口形态列表失败
*****************************************************************************/
unsigned int BSP_USB_GetAvailabePortType(unsigned char *pucPortType,
                            unsigned long *pulPortNum, unsigned long ulPortMax);
#define DRV_USB_GET_AVAILABLE_PORT_TYPE(pucPortType, pulPortNum, ulPortMax)  \
                BSP_USB_GetAvailabePortType(pucPortType, pulPortNum, ulPortMax)

/*****************************************************************************
 函 数 名  : BSP_PMU_LDOOFF
 功能描述  : 本接口用于关闭某路LDO的电压输出。
 输入参数  : ucLDO：指示某路LDO电压。取值范围为1～12。
 输出参数  : 无。
 返 回 值  : 无。
 注意事项　：LDO6由硬件控制，软件不支持对LDO6的操作。如果对LDO1关闭，则系统会关机。
*****************************************************************************/
extern void BSP_PMU_LDOOFF(BSP_U8 u8LDO);
#define DRV_PM_LDO_OFF(u8LDO)                 BSP_PMU_LDOOFF(u8LDO)

/*****************************************************************************
 函 数 名  : BSP_PMU_LDOON
 功能描述  : 本接口用于设置打开某路LDO的电压输出。
 输入参数  : ucLDO：指示某路LDO电压。取值范围为2～12。
 输出参数  : 无。
 返 回 值  : 无。
 注意事项　：不支持对LDO1，LDO6的操作。LDO1是在系统开机时自动打开，一旦关闭则整个系统会下电；LDO6是由硬件管脚控制。
*****************************************************************************/
extern void BSP_PMU_LDOON(BSP_U8 u8LDO);
#define DRV_PM_LDO_ON(u8LDO)                  BSP_PMU_LDOON(u8LDO)

/************************************
函 数 名  : BSP_PMU_AptEnable
功能描述  : 使能PMU的APT功能
输入参数  : 无
输出参数  : 返回设置状态
返 回 值  : BSP_OK，设置成功
		其他值：设置失败
**************************************/
extern BSP_S32 BSP_PMU_AptEnable(BSP_VOID);
#define DRV_PMU_APT_ENABLE()    BSP_PMU_AptEnable()

/************************************
函 数 名  : BSP_PMU_AptDisable
功能描述  : 去使能PMU的APT功能
输入参数  : 无
输出参数  : 返回设置状态
返 回 值  : BSP_OK，设置成功
		其他值：设置失败
**************************************/
extern BSP_S32 BSP_PMU_AptDisable(BSP_VOID);
#define DRV_PMU_APT_DISABLE()    BSP_PMU_AptDisable()

/************************************
函 数 名  : BSP_PMU_AptIsEnable
功能描述  : 查询PMU的APT功能是否使能
输入参数  : 无
输出参数  : 返回设置状态
返 回 值  : BSP_TURE，使能APT
		    BSP_FALSE,未使能APT
**************************************/
extern BSP_BOOL  BSP_PMU_AptIsEnable(BSP_VOID);
#define DRV_PMU_APT_ISENABLE()    BSP_PMU_AptIsEnable()


/**********************************NEW PMU INTERFACE BEGIN*******************************************/


/*****************************************************************************
 函 数 名  : DRV_PASTAR_EXC_CHECK
 功能描述  : 通信模块检查PASTAR是否有异常接口
 输入参数  : modem_id       卡号
 输出参数  : 无
 返 回 值  : BSP_OK          没有异常
             BSP_ERROR       存在异常
*****************************************************************************/
extern BSP_S32 DRV_PASTAR_EXC_CHECK(PWC_COMM_MODEM_E modem_id);
/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_SET
 功能描述  : 通信模块设置电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      设置的电压值毫伏(对于PA电压配置，可以使用枚举EM_MODEM_PA_DYNAMIC_VOLTAGE_ID替代)
 输出参数  : 无
 返 回 值  : BSP_OK          设置成功
             BSP_ERROR       设置失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_SET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 voltage_mv );
/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_GET
 功能描述  : 通信模块获取电压接口
 输入参数  : consumer_id     用户id
             voltage_mv      获得的电压值毫伏
 输出参数  : 无
 返 回 值  : BSP_OK          获取成功
             BSP_ERROR       获取失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_GET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 *voltage_mv );

/*****************************************************************************
 函 数 名  : DRV_MODEM_VOLTAGE_LIST
 功能描述  : 通信模块获取电压设置范围接口
 输入参数  : consumer_id     用户id
             list            电压范围数组
             size            数组大小
 输出参数  : 无
 返 回 值  : BSP_OK          获取成功
             BSP_ERROR       获取失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_LIST(EM_MODEM_CONSUMER_ID consumer_id,BSP_U16 **list, BSP_U32 *size);
/*****************************************************************************
 函 数 名  : DRV_MODEM_APT_ENABLE
 功能描述  : 通信模块使能APT接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : BSP_OK         设置成功
             BSP_ERROR      设置失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_APT_ENABLE(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 函 数 名  : DRV_MODEM_APT_DISABLE
 功能描述  : 通信模块去使能APT接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : BSP_OK         设置成功
             BSP_ERROR      设置失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_APT_DISABLE(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 函 数 名  : DRV_MODEM_APT_STATUS_GET
 功能描述  : 通信模块获取当前APT状态接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : PWRCTRL_COMM_ON     APT使能
             PWRCTRL_COMM_OFF    APT未使能
             BSP_ERROR           获取失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_APT_STATUS_GET(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);


/*****************************************************************************
 函 数 名  : DRV_MODEM_MODE_CONFIG
 功能描述  : 通信模块配置G模或W模接口
 输入参数  : modem_id       卡号
             mode_id        通信模式
 输出参数  : 无
 返 回 值  : BSP_OK         配置成功
             BSP_ERROR      配置失败
*****************************************************************************/
extern BSP_S32 DRV_MODEM_MODE_CONFIG(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);




/**********************************NEW PMU INTERFACE END*******************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of drv_pmu.h */


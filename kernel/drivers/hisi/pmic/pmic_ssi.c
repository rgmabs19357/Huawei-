/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : ssiDrv.c
  版 本 号   : 初稿
  作    者   :
  生成日期   :
  最近修改   :
  功能描述   : SSI Module driver
  函数列表   :
              BSP_SSI_ReceiveData
              BSP_SSI_SendData
              SSI_test_RegGet
              SSI_test_RegSet
  修改历史   :
  1.日    期   :
    作    者   :
    修改内容   :

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include <mach/pmussi_drv.h>

#include "pmic_common.h"

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : BSP_PMU_RegSet
 功能描述  : set v register data
 输入参数  : unsigned int regAddr --- 待设置寄存器地址,PMU地址位宽为8bit,32bit留作扩展
             unsigned int setData --- 设置的值,PMU数据位宽为8bit,32bit留作扩展
 输出参数  : 无
 返 回 值  : BSP_OK    - successful
             BSP_ERROR - unsuccessful
 调用函数  : BSP_SSI_SendData
 被调函数  : NA

*****************************************************************************/
BSP_S32 BSP_PMU_RegSet( BSP_U32 regAddr, BSP_U32 setData )
{
    pmussi_reg_write(regAddr,setData);
    return BSP_OK;
}

/*****************************************************************************
 函 数 名  : DRV_PMU_REG_GET
 功能描述  : get PMU register data
 输入参数  : BSP_U32  regAddr --- 待读寄存器地址,PMU地址位宽为8bit,32bit留作扩展
 输出参数  : BSP_U32  * getData --- 存放寄存器值,PMU数据位宽为8bit,32bit留作扩展
 返 回 值  : BSP_OK    - successful
             BSP_ERROR - unsuccessful
 调用函数  : BSP_SSI_ReceiveData
 被调函数  : NA

*****************************************************************************/
BSP_S32 BSP_PMU_RegGet( BSP_U32 regAddr, BSP_U32 * getData )
{
  *getData = pmussi_reg_read(regAddr);
   return BSP_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


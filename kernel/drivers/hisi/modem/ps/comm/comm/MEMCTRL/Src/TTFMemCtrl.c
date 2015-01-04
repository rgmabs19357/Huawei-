/******************************************************************************
  Copyright    : 2005-2011, Huawei Tech. Co., Ltd.
  File name    : TtfMemCtrl.c
  Version      : V900R001
  Date         : 2012-12-24
  Description  : TTF内存地址管理
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2012-12-24
     Modification:Create

******************************************************************************/


/******************************************************************************
   1 头文件包含
******************************************************************************/
#include "TTFMemCtrl.h"
#include "vos.h"
#include "DrvInterface.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_MEMCTRL_C


/******************************************************************************
   2 宏定义
******************************************************************************/


/*****************************************************************************
   函数声明
*****************************************************************************/


/*****************************************************************************
   全局变量定义
*****************************************************************************/
TTF_MEMCTRL_ADDR_STRU              g_stTtfMemCtrlAddr;


/******************************************************************************
   6 函数实现
******************************************************************************/
/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_ACORE_AddrInit
 功能描述  : TTF内存地址A-CPU上初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long   TTF_MEMCTRL_GetMemTotalLen(void)
{
    BSP_DDR_SECT_QUERY                  stQuery;
    BSP_DDR_SECT_INFO                   stInfo;
    unsigned long                       ulMemTotalLen;
    signed int                          lRslt;


    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    stInfo.ulSectSize  = TTF_MEMCTRL_INVAILD_SIZE;

    lRslt = DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    if (BSP_OK != lRslt)
    {
        stInfo.ulSectSize = TTF_MEMCTRL_INVAILD_SIZE;
    }

    ulMemTotalLen    = stInfo.ulSectSize;


    return ulMemTotalLen;
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_AddrInit
 功能描述  : TTF内存地址初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long   TTF_MEMCTRL_AddrInit(void)
{
    unsigned char                       ucTypeLoop;
    unsigned char                       ucTypeLoopOne   = 0;
    unsigned long                       ulTypeOffestLen = 0;
    unsigned long                       ulCCoreTypeLen  = 0;
    unsigned long                       ulMemTotalLen   = 0;


    if (TTF_MEMCTRL_TYPE_INIT_FLG == TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
         vos_printf("TTF_MEMCTRL_AddrInit::Addrs were already initialized!\n");

         return 0;
    }

    memset(&g_stTtfMemCtrlAddr, 0, sizeof(TTF_MEMCTRL_ADDR_STRU));

    /* 设置TTF 内存各个类型的内存长度 */
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_HDLC_MASTER_LINK_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_PARA_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_BBPMST_BUFF_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_ACORE_POOL_MEM_TOTAL_LEN);

    ulMemTotalLen   = TTF_MEMCTRL_GetMemTotalLen();

    if (TTF_MEMCTRL_INVAILD_SIZE == ulMemTotalLen)
    {
        vos_printf("TTF_MEMCTRL_AddrInit:ulMemTotalLen is invalid!\n");
        return 0;
    }

    ulCCoreTypeLen  = (ulMemTotalLen - TTF_HDLC_MASTER_LINK_TOTAL_LEN
                        - TTF_PARA_MEM_TOTAL_LEN - TTF_BBPMST_BUFF_TOTAL_LEN - TTF_ACORE_POOL_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, ulCCoreTypeLen);


    for (ucTypeLoop = 0; ucTypeLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ucTypeLoop++)
    {
        if (0 != TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop))
        {
            TTF_MEMCTRL_SET_TYPE_FLG(ucTypeLoop, TTF_MEMCTRL_TYPE_EXIST_FLG);
        }

        ulTypeOffestLen += TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop);
        ucTypeLoopOne   =  ucTypeLoop + 1;
        if (ucTypeLoopOne < TTF_MEMCTRL_ADDR_TYPE_BUTT)
        {
            /* TTF 各个类型内存相对于基址的偏移长度设置 */
            TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(ucTypeLoopOne, ulTypeOffestLen);
        }
    }

    TTF_MEMCTRL_SET_ADDR_INIT_FLG(TTF_MEMCTRL_TYPE_INIT_FLG);


    return 0;
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_ACORE_AddrInit
 功能描述  : TTF内存地址A-CPU上初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long   TTF_MEMCTRL_ACORE_AddrInit(void)
{
    TTF_MEMCTRL_AddrInit();

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);


    return 0;
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_CCORE_AddrInit
 功能描述  : TTF内存地址C-CPU上初始化处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK  成功
           : VOS_ERR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long   TTF_MEMCTRL_CCORE_AddrInit(void)
{
    TTF_MEMCTRL_AddrInit();

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);


    return 0;
}

/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetOffsetBaseLen
 功能描述  : 获取TTF内存类型对应的起始地址偏移值
 输入参数  : VOS_UINT32  ulType  - 内存类型
 输出参数  : VOS_UINT32      偏移基地址值
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long  TTF_MEMCTRL_GetOffsetBaseLen(unsigned long  ulType)
{
    unsigned long                          ulAttribute;


    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        vos_printf("TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d is invalid!\n", ulType);

        return 0;
    }

    if (TTF_MEMCTRL_TYPE_INIT_FLG != TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
        vos_printf("TTF_MEMCTRL_GetOffsetBaseLen::addr is not init!\n");

        return 0;
    }

    ulAttribute = TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ulType);
    if ((TTF_MEMCTRL_TYPE_EXIST_FLG == (TTF_MEMCTRL_TYPE_EXIST_FLG & ulAttribute))
            && (TTF_MEMCTRL_TYPE_VISIBLE_FLG == (TTF_MEMCTRL_TYPE_VISIBLE_FLG & ulAttribute)))
    {
        return TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ulType);
    }
    else
    {
        vos_printf("TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d, ulAttribute:%d is not exist or not visible!\n",
                    ulType, ulAttribute);

        return 0;
    }

}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_GetTypeAddr
 功能描述  : 获取TTF内存类型对应的起始地址
 输入参数  : VOS_UINT32  ulAddr  - 地址值
           : VOS_UINT32  ulType  - 内存类型
 输出参数  : VOS_UINT32      地址值
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数

*****************************************************************************/
unsigned long  TTF_MEMCTRL_GetTypeAddr(unsigned long ulAddr, unsigned long  ulType)
{
    unsigned long                       ulOffsetBaseLen;
    unsigned long                       ulTtfMemCtrlTypeAddr = 0;


    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        vos_printf("TTF_MEMCTRL_GetTypeAddr::ulType:%d is invalid!\n", ulType);
        return 0;
    }

    ulOffsetBaseLen         = TTF_MEMCTRL_GetOffsetBaseLen(ulType);
    ulTtfMemCtrlTypeAddr    = ulAddr + ulOffsetBaseLen;


    return  ulTtfMemCtrlTypeAddr;
}


/*****************************************************************************
 函 数 名  : TTF_MEMCTRL_PrintAddrType
 功能描述  : 打印NV配置
 输入参数  :
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月24日
    修改内容   : 新生成函数
*****************************************************************************/
void TTF_MEMCTRL_PrintAddrType(void)
{
    unsigned char                       ucTypeLoop;


    vos_printf("TTF Mem Ctrl Addr Init is :%d.\r\n", TTF_MEMCTRL_GET_ADDR_INIT_FLG());
    vos_printf("TTF Mem Ctrl Type Print :\r\n");

    for(ucTypeLoop = 0; ucTypeLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ucTypeLoop++)
    {
        vos_printf("TTF Mem Type [%d]: -- ulAttribute [%d] -- ulLen [%d] -- ulOffsetBaseLen[%d]\r\n",
            ucTypeLoop, TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ucTypeLoop),
            TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop), TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ucTypeLoop));
    }

    vos_printf("TTF Mem Ctrl Type Print END.\r\n");


    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



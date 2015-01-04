/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

******************************************************************************
 文 件 名   : rxiq_om_def.h
 版 本 号   : 初稿
 生成日期   : 2011年06月23日
 最近修改   :
 功能描述   : RXIQ OM的头文件
 函数列表   :
 修改历史   :
 1.日    期   : 2011年06月23日
   修改内容   : 创建文件
******************************************************************************/


#ifndef __RXIQ_OM_DEF_H__
#define __RXIQ_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
/************************************************************
                     包含其它模块的头文件
************************************************************/

/************************************************************
                               宏定义
************************************************************/

/************************************************************
                             数据结构定义
************************************************************/

/************************************************************
                             接口函数声明
 ************************************************************/

/************************************************************
                           1. REQ命令和对应的数据结构定义
************************************************************/

typedef enum
{
    LPHY_REQ_RXIQ_COMP_ENA          = OM_CMD_ID(LPHY_RXIQ_MID, OM_TYPE_REQ, 0x1),
    LPHY_REQ_RXIQ_CALC_ENA,
    LPHY_REQ_RXIQ_FIXED_VALUE_ENA,
}LPHY_REQ_RXIQ_ENUM;

typedef enum
{
    RXIQ_SWITCH_OFF = 0,
    RXIQ_SWITCH_ON,
    RXIQ_SWITCH_RESERVED,
}RXIQ_SWITCH_ENUM;

typedef struct
{
    RXIQ_SWITCH_ENUM    enEnable;
}LPHY_REQ_RXIQ_ENA_STRU;
typedef enum
{
    RXIQ_ON_AIR = 0,
    RXIQ_FIXED,
}RXIQ_FIX_ENABLE_ENUM;


typedef struct
{
    OM_REQ_ENABLE_ENUM    enEnable;
    RXIQ_FIX_ENABLE_ENUM  enFixedEn;
    UINT16                usRxiqAValue;
    UINT16                usRxiqPValue;
}LPHY_REQ_RXIQ_FIXED_VALUE_ENA_STRU;


/************************************************************
                           3. Sg数据结构定义
************************************************************/


/************************************************************
                           4. TRACE数据结构定义
************************************************************/
/************************************************************
                           5. ERROR数据结构定义
************************************************************/

typedef enum
{
    LPHY_ERROR_RXIQ_ARRAY_INDEX         = OM_CMD_ID(LPHY_DCOC_MID, OM_TYPE_ERROR, 0x1),
    LPHY_ERROR_RXIQ_CASE,
}LPHY_ERROR_RXIQ_ENUM;

typedef struct
{
    UINT32      ulLineNum;/*__LINE__*/
    UINT32      ulIncorrectValue;
}LPHY_ERROR_RXIQ_ARRAY_INDEX_STRU;

typedef struct
{
    UINT32      ulLineNum;/*__LINE__*/
    UINT32      ulCase;
}LPHY_ERROR_RXIQ_CASE_STRU;

typedef union
{
    LPHY_ERROR_RXIQ_ARRAY_INDEX_STRU   stRxiqArrayIndexError;
    LPHY_ERROR_RXIQ_CASE_STRU          stRxiqCaseError;
}RXIQ_OM_REPORT_UNION;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __RXIQ_OM_DEF_H__ */


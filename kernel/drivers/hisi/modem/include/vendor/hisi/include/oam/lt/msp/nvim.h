/*****************************************************************************

                  版权所有 (C), 1998-2010, 华为技术有限公司

*****************************************************************************
  文 件 名   : nvim.h
  版 本 号   : V1.0
  生成日期   : 2010-02-27
  功能描述   : 包含模块对MSP内部其他模块提供，而无需对外部组件提供的
               接口等，如果对内外都提供则定义在外部组件接口msp_xxx.h

  函数列表   : TODO: ...
  修改历史   :
  1.日    期 : 2010-02-27
    修改内容 : 创建文件

*****************************************************************************/

/*****************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
*****************************************************************************/
#ifndef __NVIM_H__
#define __NVIM_H__

#include "gen_msg.h"
#include <SysNvId.h>

#define NVM_FLASH_BLOCK_SIZE      (64*2048)
#define NVM_BACKUP_VERSION_FILE_BLOCK_NUM  4
#define NVM_IMEI_LENTH    15

typedef enum
{
    EN_NVM_HSO_HNV_FILE = 0,      /*HSO新生成的文件*/
    EN_NVM_VERSION_FILE = 1,      /*当前版本使用的NV文件*/
    EN_NVM_BACKUP_FILE =2,           /*正常升级时做备份的文件*/
    EN_NVM_VERSION_INIT_FILE=3,     /* 备份当前版本的初始值*/
    EN_NVM_FILE_LAST
} NVM_FILE_TEPY_ENUM;

typedef struct
{
    /*VOS_UINT32 ulType;        0: 初始文件, 1: 当前文件*/
    VOS_UINT32 ulFileLen;
    VOS_UINT8 *pData;
}NVIM_EXPORT_FILE_INFO_STRU;

typedef  enum
{
    NVIM_REVERT_SUSS,/*恢复成功*/
    NVIM_REVERT_FAIL,/*恢复失败*/
    NVIM_REVERT_BLOCK,/*自动恢复挂起*/
    NVIM_REVERT_BLOCK_FOR_NO_BACKUP,/*自动恢复无备份而挂起*/
    NVIM_REVERT_FAIL_FOR_NO_BACKUP/*强制恢复无备份而失败*/
}NVIM_REVERT_STATE_EN;


extern VOS_UINT32 nvim_GetImei(VOS_CHAR szImei[16]);

#endif

/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : ATUSBMdmInterfaceProc.h
  Version     : V200R001
  Date        : 2007-11-13
  Description : 该头文件定义了---
  History     :
  1. Date:2007-11-14
     Modification:Create
  2.日    期   : 2009-12-04
    修改内容   : 问题单号:AT2D15720,驱动接口清理
************************************************************************/

#ifndef _ATUSBMDMROC_H_
#define _ATUSBMDMROC_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*ucPortType =3 ; ucDlci = 64*/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of ATUSBMdmInterfaceProc.h*/


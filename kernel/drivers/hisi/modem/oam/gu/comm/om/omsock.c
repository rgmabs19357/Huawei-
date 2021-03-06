/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名      : OmSock.c
  版 本 号      : 初稿
  生成日期      : 2008年8月11日
  最近修改      :
  功能描述      : 协议栈与工具侧的通信SOCKET接口
  函数列表      :
  修改历史      :
  1.日    期    : 2008年8月11日
    修改内容    : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "omprivate.h"
#include "NVIM_Interface.h"
#include "omrl.h"
#include "omsock.h"
#include "cpm.h"
#if (VOS_WIN32 == VOS_OS_VER)
#include <winsock2.h>
#include <windows.h>
#elif (VOS_VXWORKS == VOS_OS_VER)
#include <sockLib.h>
#endif

#if (VOS_LINUX == VOS_OS_VER)
#include "hisocket.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif



/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_SOCK_C
/*lint +e767 */

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*作为服务器端用来监听端口的socket*/
SOCKET              g_sockListen = SOCK_NULL;

/*保存当前链路的基本信息*/
COMM_INFO_STRU      g_astCommInfo[SOCKET_NUM_MAX] = {{SOCK_NULL, VOS_NULL_PTR},{SOCK_NULL, VOS_NULL_PTR}};

/*同步信号量，用来保证SOCKET服务器任务在APP启动后再运行*/
VOS_UINT32          g_ulSockTaskSem = VOS_NULL_PTR;

/*互斥信号量，用来保证SOCKET发送过程中不能被关闭*/
VOS_UINT32          g_ulSockCloseSem = VOS_NULL_PTR;

/*保存当前SOCKET的状态*/
VOS_UINT32          g_ulSockState = SOCK_OK;

/*****************************************************************************
 Prototype      : Sock_IsEnable
 Description    : SOCK功能是否支持
 Input          : void
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2012-05-24
    Modification: Created function
*****************************************************************************/
VOS_BOOL Sock_IsEnable(VOS_VOID)
{
#if (VOS_LINUX == VOS_OS_VER)
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;

    /* 读取OM的物理输出通道 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_FALSE;
    }

    stPortCfg.enPortNum += CPM_APP_PORT;

    /* 检测参数*/
    if (CPM_WIFI_OM_PORT != stPortCfg.enPortNum)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 Prototype      : Sock_ShutdownAll
 Description    : 关闭所有的SOCKET连接
 Input          : VOS_VOID

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        : ---
    Date        : 2008-05-3
    Modification: Created function
 *****************************************************************************/
VOS_VOID Sock_ShutdownAll(VOS_VOID)
{
    VOS_UINT32 ulIndex;

    for (ulIndex = 0; ulIndex < SOCKET_NUM_MAX; ulIndex++)
    {
        if (SOCK_NULL != g_astCommInfo[ulIndex].socket)
        {
            (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);

            closesocket(g_astCommInfo[ulIndex].socket);

            g_astCommInfo[ulIndex].socket = SOCK_NULL;

            VOS_SmV(g_ulSockCloseSem);
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : Sock_Startup
 Description    : 提供给APP调用，用来启动SOCKET任务
 Input          : VOS_VOID

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        : ---
    Date        : 2008-05-3
    Modification: Created function
 *****************************************************************************/
VOS_VOID Sock_Startup(VOS_VOID)
{
    if (VOS_NULL_PTR == g_ulSockTaskSem)
    {
        return;
    }

    if (VOS_OK != VOS_SmV(g_ulSockTaskSem))
    {
        g_ulSockState = SOCK_V_SEM;
    }

    return;
}

/*****************************************************************************
 Prototype      : Sock_JudgeCommType
 Description    : 通过第一个数据包的内容，判断是OM链路还是邋AT链路
 Input          : pData        - 指向数据包内容的指针.
                  uslength     - 指向数据包内容的长度.
 Output         : void
 Return Value   : 1 为AT链路
                  0 为OM链路

 History        : ---
    Date        : 2008-05-3
    Modification: Created function
 *****************************************************************************/
VOS_UINT32 Sock_JudgeCommType(VOS_UINT8* pucData, VOS_UINT16 uslength)
{
    if (0 == VOS_MemCmp(pucData, "AT\r", uslength))
    {
        /*AT*/
        return 1;
    }

    /*OM*/
    return 0;
}

/*****************************************************************************
 Prototype      : Sock_Init
 Description    : 初始化Socket服务器端
 Input          : VOS_VOID
 Output         : void
 Return Value   : VOS_TRUE :初始化成功
                  VOS_FALSE:初始化失败

 History        : ---
    Date        : 2008-05-3
    Modification: Created function
 *****************************************************************************/
VOS_BOOL Sock_Init(VOS_VOID)
{
    struct sockaddr_in  sAddr;
    VOS_INT             lAddLen;

#if (VOS_WIN32 == VOS_OS_VER)
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
#endif

    g_sockListen = socket(AF_INET, SOCK_STREAM, 0);

#if (VOS_LINUX == VOS_OS_VER)
    if (VOS_OK > g_sockListen)
#else
    if (INVALID_SOCKET == g_sockListen)
#endif
    {
        g_ulSockState = SOCK_INIT_ERR;

        closesocket(g_sockListen);

        return VOS_FALSE;
    }

    VOS_MemSet(&sAddr, 0, sizeof(sAddr));
    sAddr.sin_family = AF_INET;

    sAddr.sin_addr.s_addr = 0;

    /*监听的端口号为3000*/
    sAddr.sin_port = htons(SOCK_PORT_NUM);

    lAddLen = sizeof(struct sockaddr_in);

    /*将监听Socket绑定到对应的端口上*/
    if (SOCKET_ERROR == bind(g_sockListen, (struct sockaddr *)&sAddr, lAddLen))
    {
        g_ulSockState = SOCK_BIND_ERR;

        closesocket(g_sockListen);

        return VOS_FALSE;
    }

    /*设置服务器端监听的最大客户端数*/
    if (SOCKET_ERROR == listen(g_sockListen, SOCKET_NUM_MAX))
    {
        g_ulSockState = SOCK_LISTEN_ERR;

        closesocket(g_sockListen);

        return VOS_FALSE;
    }

    /* 创建SOCKET保护信号量 */
    if(VOS_OK != VOS_SmMCreate("SOCK", VOS_SEMA4_FIFO, &g_ulSockCloseSem))
    {
        closesocket(g_sockListen);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Prototype      : Sock_ServerProc
 Description    : 服务器线程，用来处理服务器端和客户端的所有请求。
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Modification: Created function
*****************************************************************************/
VOS_VOID Sock_ServerProc(VOS_VOID)
{
    VOS_INT8    acRcvBuf[OM_APP_SPLIT_MSG_LEN];
    Ip_fd_set   allfds;
    Ip_fd_set   readfds;
    VOS_INT     lRet = 0;
    VOS_INT     lIndex = 0;
    VOS_INT     lRevSize = 0;
    SOCKET      sockUnknown = SOCK_NULL;
    VOS_UINT32  ulFlag;

    SOCK_FD_ZERO(&allfds);
    SOCK_FD_ZERO(&readfds);
    SOCK_FD_SET(g_sockListen, &allfds);
    SOCK_FD_SET(g_sockListen, &readfds);

    for(;;)
    {
        ulFlag = VOS_FALSE;

        /*接收来自所有socket的消息*/
        lRet = select(FD_SETSIZE, &readfds, 0, 0, 0);

    #if (VOS_LINUX == VOS_OS_VER)
        if ( 0 > lRet )
    #else
        if ( (SOCKET_ERROR == lRet) || (0 == lRet) )
    #endif
        {
            g_ulSockState = SOCK_SELECT_ERR;

            return;
        }

        /*判断此请求是否属于监听Socket.*/
        if (0 != SOCK_FD_ISSET(g_sockListen, &readfds))
        {
            ulFlag = VOS_TRUE;

            /*有一个客户端连接上服务器，但此链路的类型未定*/
            sockUnknown = accept(g_sockListen, NULL, 0);

        #if (VOS_LINUX == VOS_OS_VER)
            if (0 > sockUnknown)
        #else
            if (SOCKET_ERROR == sockUnknown)
        #endif
            {
                sockUnknown   = SOCK_NULL;
                g_ulSockState = SOCK_ACCEPT_ERR;

                continue;
            }

            SOCK_FD_SET(sockUnknown, &allfds);
        }

        /*来自客户端socket的消息*/
        for (lIndex = 0; lIndex < SOCKET_NUM_MAX; lIndex++)
        {
            /*接收到来自PC的工具的数据*/
            if (0 != SOCK_FD_ISSET(g_astCommInfo[lIndex].socket, &readfds))
            {
                ulFlag = VOS_TRUE;
                lRevSize = recv(g_astCommInfo[lIndex].socket, acRcvBuf, OM_APP_SPLIT_MSG_LEN, 0);

                /*客户端已经关闭，需要做将其清空*/
            #if (VOS_LINUX == VOS_OS_VER)
                if (0 >= lRevSize)
            #else
                if ((SOCKET_ERROR == lRevSize) || (0 == lRevSize))
            #endif
                {
                    SOCK_FD_CLR(g_astCommInfo[lIndex].socket, &allfds);
                    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);
                    closesocket(g_astCommInfo[lIndex].socket);
                    g_astCommInfo[lIndex].socket = SOCK_NULL;
                    VOS_SmV(g_ulSockCloseSem);

                    continue;
                }

                /*将接收到的数据提交给上层处理*/
                CPM_ComRcv((lIndex + CPM_WIFI_OM_PORT), acRcvBuf, lRevSize);
            }
        }

        /*确认链路的类型*/
        if (0 != SOCK_FD_ISSET(sockUnknown, &readfds))
        {
            ulFlag = VOS_TRUE;

            lRevSize = recv(sockUnknown, acRcvBuf, OM_APP_SPLIT_MSG_LEN, 0);

            /*客户端已经关闭，需要做将其清空*/
        #if (VOS_LINUX == VOS_OS_VER)
            if (0 >= lRevSize)
        #else
            if ((SOCKET_ERROR == lRevSize) || (0 == lRevSize))
        #endif
            {
                SOCK_FD_CLR(sockUnknown, &allfds);
                (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);
                closesocket(sockUnknown);
                VOS_SmV(g_ulSockCloseSem);
            }
            else
            {
                /*判断当前链路的类型*/
                lIndex = (VOS_INT)Sock_JudgeCommType(acRcvBuf, (VOS_UINT16)lRevSize);

                if (SOCK_NULL == g_astCommInfo[lIndex].socket)
                {
                    g_astCommInfo[lIndex].socket = sockUnknown;

                    /*将接收来自客户端的数据交给上层应用*/
                    CPM_ComRcv((lIndex + CPM_WIFI_OM_PORT), acRcvBuf, lRevSize);
                }
                else
                {
                    SOCK_FD_CLR(sockUnknown, &allfds);
                    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);
                    closesocket(sockUnknown);
                    VOS_SmV(g_ulSockCloseSem);

                    LogPrint("Sock_ServerProc: The Current Link Is Existent!\r\n");
                }
            }

            sockUnknown = SOCK_NULL;
        }

        if ( VOS_FALSE == ulFlag )/* 有错误发生，恢复set */
        {
            Sock_ShutdownAll();

            SOCK_FD_ZERO(&allfds);
            SOCK_FD_SET(g_sockListen, &allfds);
        }

        VOS_MemCpy(&readfds, &allfds, sizeof(Ip_fd_set));
    }
}

/*****************************************************************************
 Prototype      : Sock_ServerTask
 Description    : 服务器线程，用来处理服务器端和客户端的所有请求。
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Modification: Created function
*****************************************************************************/
VOS_VOID Sock_ServerTask(VOS_VOID)
{
#if (VOS_VXWORKS == VOS_OS_VER)

    /*假如当前没有配置为WIFI模式,则强制退出*/
    /*if (OMRL_WIFI != g_RlSndLinkType)
    {
        g_ulSockState = SOCK_NO_START;

        return;
    }*/



    /*创建同步信号量用来保证在应用之后启动*/
    if ( VOS_OK != VOS_SmBCreate( "Sock", 0, VOS_SEMA4_FIFO, &g_ulSockTaskSem))
    {
        g_ulSockState = SOCK_INIT_SEM_ERR;

        return;
    }

    if(VOS_OK != VOS_SmP(g_ulSockTaskSem, 0))
    {
        g_ulSockState = SOCK_P_SEM;

        return;
    }
#endif

    /*初始化SOCKET*/
    if (VOS_FALSE == Sock_Init())
    {
        return;
    }

    g_ulSockState = SOCK_START;

    Sock_ServerProc();

    return;
}

/*****************************************************************************
 Prototype      : Sock_OMComSend
 Description    : 提供给上层OM发送数据的接口.
 Input          :
                  pucData  - 指向发送数据内容的指针
                  uslength - 发送数据的长度
 Output         : void
 Return Value   : VOS_ERR  - 发送失败
                  VOS_OK   - 发送成功

 History        : ---
    Date        : 2012-01-21
    Modification: Created function
 *****************************************************************************/
VOS_INT32 Sock_OMComSend(VOS_UINT8* pucData, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);

    socket = g_astCommInfo[SOCKET_OM].socket;

    if (SOCK_NULL == socket)
    {
        VOS_SmV(g_ulSockCloseSem);

        return VOS_ERR;
    }

    /*调用send将数据通过socket发送出去*/
    nSndNum = send(socket, pucData, uslength, 0);

    VOS_SmV(g_ulSockCloseSem);

    if (nSndNum != uslength)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Prototype      : Sock_ATComSend
 Description    : 提供给上层AT发送数据的接口.
 Input          :
                  pucData  - 指向发送数据内容的指针
                  uslength - 发送数据的长度
 Output         : void
 Return Value   : VOS_ERR  - 发送失败
                  VOS_OK   - 发送成功

 History        : ---
    Date        : 2012-01-21
    Modification: Created function
 *****************************************************************************/
VOS_INT32 Sock_ATComSend(VOS_UINT8* pucData, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);

    socket = g_astCommInfo[SOCKET_AT].socket;

    if (SOCK_NULL == socket)
    {
        VOS_SmV(g_ulSockCloseSem);

        return VOS_ERR;
    }

    /*调用send将数据通过socket发送出去*/
    nSndNum = send(socket, pucData, uslength, 0);

    VOS_SmV(g_ulSockCloseSem);

    if (nSndNum != uslength)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  :
 功能描述  : 用于WIFI通道的初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_ERR/VOS_OK
 调用函数  :
 被调函数  :
 修改历史  :
   1.日    期  : 2012年1月21日
     修改内容  : Creat Function
*****************************************************************************/
VOS_UINT32 Sock_PortInit(VOS_VOID)
{
    if(BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT())  /*当前不支持WIFI*/
    {
        return VOS_OK;
    }

    CPM_PhySendReg(CPM_WIFI_OM_PORT,  (CPM_FUNC)Sock_OMComSend);
    CPM_PhySendReg(CPM_WIFI_AT_PORT,  (CPM_FUNC)Sock_ATComSend);

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

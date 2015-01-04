/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_ifc.c
  版 本 号   : 初稿
  生成日期   : 2012年12月27日
  最近修改   :
  功能描述   : ifc 单板测试用例
  函数列表   :
  修改历史   :
  1.日    期   : 2012年12月27日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "drv_ifc.h"
#include <linux/kernel.h>
#include "bsp_mailbox.h"
#include "drv_ifc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
unsigned char             g_InputPara[20] = {0};
unsigned char             g_ExternInputBuffer[32] = {0};
unsigned char             g_OutPutBuffer[512] = {0};
long                      g_IfcCommAsyncSum = 0;
int                       g_IfcResponseFlag = 0;
unsigned long             g_IfcSyncFlag = 0;
int                       g_InputLength = 0;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TEST_IFC_CommCallback
 功能描述  : ifc common call callback
 输入参数  : unsigned long Funid
             long retValue
 输出参数  : 无
 返 回 值  : long
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年12月28日
    修改内容   : 新生成函数

*****************************************************************************/
long TEST_IFC_CommCallback(unsigned long Funid, long retValue)
{
    if (g_IfcCommAsyncSum == retValue)
    {
        printk("test_ifc_commcall test pass!");
    }
    else
    {
        printk("test_ifc_commcall test fail!");
    }

    g_IfcCommAsyncSum = 0;
    return 0;
}

long TEST_IFC_ExtendCallback(unsigned long Funid, unsigned char* pBuffer, unsigned long u32Length)
{
    if (g_IfcResponseFlag)
    {
        long result = *(long*)(&g_ExternInputBuffer[0] + g_InputLength * 4 -4);
        if ((*(long*)pBuffer) == result)
        {
            printk("test_ifc_extendcall test pass!\n");
        }
        else
        {
            printk("test_ifc_extendcall test fail!\n");
        }
    }
    else
    {
        printk("test_ifc_extendcal \n!");

        int i = 0;
        for (; i < (u32Length / 4); i++)
        {
            printk("%d\n", *(long*)(pBuffer + i * 4));
        }
    }
    return 0;
}

long sum(long ParaNum)
{
    long sum = 0;
    while(ParaNum)
    {
        sum = sum + ParaNum;
        ParaNum--;
    }
    return sum;
}

void test_ifc_commcall(unsigned long Funid,unsigned long SyncFlag, long ParaNum)
{
    g_IfcSyncFlag = SyncFlag;

    IFC_COMM_CALLBACK   CallBack = TEST_IFC_CommCallback;
    unsigned long ret;

    *(long*)g_InputPara = 1;
    *(long*)(g_InputPara+4) = 2;
    *(long*)(g_InputPara+8) = 3;
    *(long*)(g_InputPara+12) = 4;
    *(long*)(g_InputPara+16) = 5;

    if (SyncFlag == BSP_MAILBOX_IFC_CALL_SYNC)
    {
        ret = MB_IFC_CommCall( Funid, SyncFlag, NULL, (unsigned char*)(&g_InputPara[0]), ParaNum);

        if (sum(ParaNum) == ret)
        {
            printk("test_ifc_commcall test pass!");
        }
        else
        {
            printk("test_ifc_commcall test fail!");
        }
    }

    if (SyncFlag == BSP_MAILBOX_IFC_CALL_ASYN)
    {
        g_IfcCommAsyncSum = sum(ParaNum);
        ret = MB_IFC_CommCall( Funid, SyncFlag, CallBack, (unsigned char*)(&g_InputPara[0]), ParaNum);
    }

    return;

}


void test_ifc_extendcall(unsigned long Funid,unsigned long SyncFlag,unsigned long InputLen)
{
    IFC_EXTEN_CALLBACK  CallBack = (IFC_EXTEN_CALLBACK)TEST_IFC_ExtendCallback;
    unsigned long             OutPutLen = 100;
    long result;

    if (InputLen > 8){
        printk("test_ifc_extendcall: InputLen too length!!");
    }

    *(long*)g_ExternInputBuffer = 1;
    *(long*)(g_ExternInputBuffer+4) = 2;
    *(long*)(g_ExternInputBuffer+8) = 3;
    *(long*)(g_ExternInputBuffer+12) = 4;
    *(long*)(g_ExternInputBuffer+16) = 5;
    *(long*)(g_ExternInputBuffer+20) = 6;
    *(long*)(g_ExternInputBuffer+24) = 7;
    *(long*)(g_ExternInputBuffer+28) = 8;

    g_IfcSyncFlag = SyncFlag;
    g_InputLength = InputLen;

    if (SyncFlag == BSP_MAILBOX_IFC_CALL_SYNC)
    {
        MB_IFC_ExtendCall( Funid, SyncFlag, NULL,(unsigned char*)(&g_ExternInputBuffer[0]),
                4 * InputLen, (unsigned char*)(&g_OutPutBuffer[0]), &OutPutLen);
        result = *(long*)(&g_OutPutBuffer[0]);

        if ((*(long*)(g_ExternInputBuffer+(InputLen - 1) * 4)) == result)
        {
            printk("test_ifc_extendcall test pass!");
        }
        else
        {
            printk("test_ifc_extendcall test fail!");
        }
    }

    if (SyncFlag == BSP_MAILBOX_IFC_CALL_ASYN)
    {
        MB_IFC_ExtendCall( Funid, SyncFlag, CallBack,(unsigned char*)(&g_ExternInputBuffer[0]),
                4 * InputLen, (unsigned char*)(&g_OutPutBuffer[0]), &OutPutLen);
    }


   return;


}

long ifc_test_func_comm(long a, long b, long c, long d, long e)
{
    long sum = a + b + c + d + e;

    if (!g_IfcResponseFlag)
    {
        MB_IFC_Response(BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_RESPONSE_CH,
                        IFCP_FUNC_ACPU_BOARD_COMMCALL_TEST,
                        0,
                        NULL,
                        (unsigned long)BSP_MAILBOX_IFC_CALL_COMM,
                        &sum,
                        sizeof(long),
                        NULL,
                        NULL);
    }
    return sum;
}

long ifc_test_func_extend(unsigned char* Buffer,unsigned long Length)
{
    long ret;

    if (!g_IfcResponseFlag)
    {
        MB_IFC_Response(BSP_MAILBOX_CHANNEL_ACPU_TO_MCU_IFC_RESPONSE_CH,
                        IFCP_FUNC_ACPU_BOARD_EXTENDCALL_TEST,
                        1,
                        NULL,
                        (unsigned long)BSP_MAILBOX_IFC_CALL_EXTENED,
                        Buffer,
                        Length,
                        NULL,
                        NULL);
         return 0;
    }
    else
    {
        ret = *(long*)(Buffer + Length - 4);
        return ret;
    }
}

void register_ifc_func(int flag)
{
    g_IfcResponseFlag = flag;

    MB_IFC_RegFunc(IFCP_FUNC_ACPU_BOARD_COMMCALL_TEST,
                   ifc_test_func_comm,
                   flag);
    MB_IFC_RegFunc(IFCP_FUNC_ACPU_BOARD_EXTENDCALL_TEST,
                   ifc_test_func_extend,
                   flag);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


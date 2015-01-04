#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "nvim_internalfunc.h"
#include "DrvInterface.h"
#include "NvIdList.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <linux/semaphore.h>
#include <asm/uaccess.h>
#endif

/* Macro of log */
#define    THIS_FILE_ID        PS_FILE_ID_NVIM_AFUNC_C

/*NV Memory ADDR*/
VOS_UINT32                      g_ulNVMemAddr       = 0;

/* 存放NV数据的内存块 */
NV_CONTROL_FILE_INFO_STRU       *g_pstNVDataBuf = VOS_NULL_PTR;

/* NV's ID coms from 1 to 20 */
NV_FILE_HANDLE_STRU             g_astNvFileHandle[NV_BACKUP_FILE_MAX_NUM+1];

VOS_UINT32                      g_ulNVInitStartSlice = 0;

VOS_UINT32                      g_ulNVInitEndSlice   = 0;

VOS_UINT32                      g_ulNVInitSem        = 0;

/* NV 写操作是否需要记录slice标记 */
extern  VOS_UINT32              g_ulRecordNvFlag;

/* 控制NV写操作的互斥信号量 */
VOS_UINT32                      g_ulNVWriteSem;

#if( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )

VOS_CHAR *g_aucNvFolderPath = ".\\NvimUse\\"; /* NV File path */
/*FlashLess文件接口定义*/
const VOS_CHAR g_aucNvFilePath[]   = "Nvim.bin";  /* NV Ctrl File */

#else

#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION) /* SFT board*/

/* Absolute Path for Operating NV file */
const VOS_CHAR g_aucNvFolderPath[]   = "/mnvm2:0/NvimUse/"; /* NV File path */

/*FlashLess文件接口定义*/ /* V9R1 SFT多文件系统不会出现flashbess，暂时没有定这个路径 */
const VOS_CHAR g_aucNvFilePath[]     = "/yaffs0/Nvim/Nvim.bin";  /* NV Ctrl File */

#else /* BBIT board*/

/* Absolute Path for Operating NV file */
const VOS_CHAR g_aucNvFolderPath[]   = "/yaffs0/NvimUse/"; /* NV File path */

/*FlashLess文件接口定义*/
const VOS_CHAR g_aucNvFilePath[]     = "/yaffs0/Nvim/Nvim.bin";  /* NV Ctrl File */

#endif

#endif

#if (VOS_LINUX == VOS_OS_VER)

/* A C 核同步等待信号量 */
struct semaphore               g_stCoreNvSem;

/* NV 写互斥信号量 */
struct semaphore               g_stNvWriteSem;

/*****************************************************************************
 函 数 名  : _VOS_SmMCreate
 功能描述  : 创建互斥信号量操作
 输入参数  : acSmName: 信号量名字
             ulSmInit: 信号量初始化值
             ulFlags: 信号量类型
             pulSmID: 保存信号量ID的地址

 输出参数  : pulSmID: 保存信号量ID的地址

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2013年5月2日
   作    者    :  
   修改内容    : C核单独复位项目开发
*****************************************************************************/
VOS_UINT32 _VOS_SmMCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_UINT32 *pulSmID)
{
    sema_init(&g_stNvWriteSem, 1);

    *pulSmID = (VOS_UINT32)(&g_stNvWriteSem);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : _VOS_SmCCreate
 功能描述  : 创建信号量操作
 输入参数  : acSmName: 信号量名字
             ulSmInit: 信号量初始化值
             ulFlags: 信号量类型
             pulSmID: 保存信号量ID的地址

 输出参数  : pulSmID: 保存信号量ID的地址

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年13月26日
   作    者    :  
   修改内容    : A核循环等待修改为与C核信号量同步方案开发
*****************************************************************************/
VOS_UINT32 _VOS_SmCCreate(VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_UINT32 *pulSmID)
{
    sema_init(&g_stCoreNvSem, 0);

    *pulSmID = (VOS_UINT32)(&g_stCoreNvSem);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : _VOS_SmP
 功能描述  : 等待信号量
 输入参数  : ulSemId: 信号量ID
             ulTimeOutInMillSec: 超时时间(ms)

 输出参数  : 无

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年13月26日
   作    者    :  
   修改内容    : A核循环等待修改为与C核信号量同步方案开发
*****************************************************************************/
VOS_UINT32 _VOS_SmP(VOS_UINT32 ulSemId, VOS_UINT32 ulTimeOutInMillSec)
{
    down((struct semaphore *)ulSemId);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : _VOS_SmV
 功能描述  : 释放信号量
 输入参数  : ulSemId: 信号量ID

 输出参数  : 无

 返 回 值  : VOS_OK:成功、VOS_ERR:失败

 修改历史      :
 1.日    期    : 2012年13月26日
   作    者    :  
   修改内容    : A核循环等待修改为与C核信号量同步方案开发
*****************************************************************************/
VOS_UINT32 _VOS_SmV(VOS_UINT32 ulSemId)
{
    up((struct semaphore *)ulSemId);

    return VOS_OK;
}
#endif

/*****************************************************************************
 函 数 名  : NV_ACoreInitIpcIsr
 功能描述  : C 核NV初始化完毕中断处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化结果

 修改历史      :
  1.日    期   : 2013年03月26日
    作    者   :  
    修改内容   : A核循环等待修改为与C核信号量同步方案开发

*****************************************************************************/
VOS_VOID NV_ACoreInitIpcIsr(VOS_VOID)
{
    DRV_IPC_INTDISABLE((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);

    /*收到C核初始化完毕中断，释放信号量*/
    VOS_SmV(g_ulNVInitSem);

    DRV_IPC_INTENABLE((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);
}

/*****************************************************************************
 函 数 名  : NV_ACoreInitSync
 功能描述  : NV A核信号量同步
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID

 修改历史      :
 修改历史      :
  1.日    期   : 2013年03月26日
    作    者   :  
    修改内容   : A核循环等待修改为与C核信号量同步方案开发

*****************************************************************************/
VOS_VOID NV_ACoreInitSync(VOS_VOID)
{
#if (VOS_LINUX == VOS_OS_VER)
    /* 创建信号量 */
    VOS_SmCCreate("NVOK", 0, 0, &g_ulNVInitSem);
#endif
    /* 注册给C核中断 */
    DRV_IPC_INTCONNECT((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM, (VOIDFUNCPTR)NV_ACoreInitIpcIsr, 0);

    DRV_IPC_INTENABLE((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_NVIM);
}

/*****************************************************************************
 函 数 名  : NV_Init
 功能描述  : Acpu Nv 初始化
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 初始化结果

 修改历史      :
  1.日    期   : 2011年10月03日
    作    者   : 
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NV_Init(VOS_VOID)
{
    VOS_UINT8           aucMagicNum[NV_MAGIC_NUM_LEN];
    VOS_UINT8           aucTemp[NV_MAGIC_NUM_LEN];
    BSP_DDR_SECT_INFO   stNVMemInfo;
    BSP_DDR_SECT_QUERY  stNVMemQuery;

    g_ulNVInitStartSlice = DRV_GET_SLICE();

    VOS_MemSet(g_astNvFileHandle, 0, sizeof(g_astNvFileHandle));

    vos_printf("\r\n---------------------NV_Init Start-----------------------------\r\n");

    VOS_MemSet(aucMagicNum, NV_MAGIC_NUM, NV_MAGIC_NUM_LEN);

    stNVMemQuery.enSectType = BSP_DDR_SECT_TYPE_NV;
    stNVMemQuery.ulSectSize = NV_BACKUP_BUFFER_SIZE;
    stNVMemQuery.enSectAttr = BSP_DDR_SECT_ATTR_NONCACHEABLE;

    if(BSP_OK != DRV_GET_FIX_DDR_ADDR(&stNVMemQuery, &stNVMemInfo))
    {
        vos_printf("\r\nNV_Init: Acpu DRV_GET_FIX_DDR_ADDR Failed\r\n");

        DRV_SYSTEM_ERROR(NV_INIT_ERROR, NV_GET_DRV_FIX_DDR_ADDR_FAIL,
                            0, (VOS_CHAR *)VOS_NULL_PTR, 0);

        return NV_INIT_FAIL;
    }

    g_ulNVMemAddr = stNVMemInfo.ulSectVirtAddr;     /*上层使用虚地址*/

    /* 创建NV写操作保护信号量 */
    if(VOS_OK != VOS_SmMCreate("NV", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE,
                                &g_ulNVWriteSem))
    {
        return VOS_ERR;
    }

    if(BSP_OK != DRV_IPC_SEMCREATE(IPC_SEM_NVIM))
    {
        NV_Printf("NV_Init: Acpu DRV_IPC_SEMCREATE Failed\r\n");

        return NV_INIT_FAIL;
    }

    /* 等待C 核NV初始化完毕 */
    (VOS_VOID)VOS_SmP(g_ulNVInitSem, 0);

    NV_MEMCPY(aucTemp, (VOS_VOID*)NV_MAGICNUM_ADDR, NV_MAGIC_NUM_LEN);  /*从share memory读取标志字节*/

    if(VOS_OK != VOS_MemCmp(aucMagicNum, aucTemp, NV_MAGIC_NUM_LEN))    /*Ccpu的Nv项已经初始化成功*/
    {
        /* 单板复位 */
        DRV_SYSTEM_ERROR(NV_INIT_ERROR, NV_GET_CCORE_MAGIC_NUM_FAIL,
                            0, (VOS_CHAR *)VOS_NULL_PTR, 0);
    }

    NV_BuildGlobalVar();

    vos_printf("\r\n---------------------NV_Init End-----------------------------\r\n");

    g_ulNVInitEndSlice = DRV_GET_SLICE();

    DRV_MSP_PROC_REG(OM_READ_NV_PROC, (BSP_MspProc)NV_ReadEx);

    /* 检测是否开启NV写操作记录跟踪 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Write_Slice_Record_Flag, (VOS_VOID*)&g_ulRecordNvFlag, sizeof(g_ulRecordNvFlag)))
    {
        g_ulRecordNvFlag = 0;
    }

    return NV_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




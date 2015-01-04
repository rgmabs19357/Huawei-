/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : dms_dev_ops.c
  Description     : 
  History         :
     1.w00182550       2013-1-31   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile                            
*****************************************************************************/
/*lint -save -e322 -e7 -e537*/
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "vos.h"
#include "DrvInterface.h"
#include "diag_vcom.h"
/*lint -restore*/

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function 
*****************************************************************************/
    /*lint -save -e40 -e63*/

/*****************************************************************************
* 函 数 名  : diag_udi_open name:/dev/acm_at
*
* 功能描述  : 打开设备(数据通道)
*
* 输入参数  : pParam: 设备的打开配置参数
* 输出参数  : 无
* 返 回 值  : -1:失败 / 其他:成功
*****************************************************************************/
/*lint --e{718, 746, 730}*/
UDI_HANDLE diag_udi_open(char* name)
{
    /*lint --e{565}*/
    struct file* filp;

    filp = filp_open(name, O_RDWR, 0);
    if (IS_ERR(filp)) 
    {
        /*lint -save -e515*/
        pr_emerg("%s, open(%d) fail:%s\n", __FUNCTION__, (int)filp, name);
        /*lint -restore*/
        return UDI_INVALID_HANDLE;
    }

    return (UDI_HANDLE)filp;
}

/*****************************************************************************
* 函 数 名  : diag_udi_close
*
* 功能描述  : 关闭设备(数据通道)
*
* 输入参数  : handle: 设备的handle
* 输出参数  : 无
* 返 回 值  : 成功/失败
*****************************************************************************/
VOS_INT32 diag_udi_close(UDI_HANDLE handle)
{
    struct file* filp = (struct file*)handle;
    /*lint -save -e515*/
    if (unlikely((UDI_HANDLE)UDI_INVALID_HANDLE == handle || (UDI_HANDLE)0 == handle))
    {
        pr_emerg("%s, invalid param\n", __FUNCTION__);
        /*lint -restore*/
        return (UDI_HANDLE)(VOS_ERROR);
    }

    filp_close(filp, NULL);
    return VOS_OK;
}

/*****************************************************************************
* 函 数 名  : diag_udi_write
*
* 功能描述  : 数据写
*
* 输入参数  : handle:  设备的handle
*             pMemObj: buffer内存 或 内存链表对象
*             u32Size: 数据写尺寸 或 内存链表对象可不设置
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
VOS_INT32 diag_udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size)
{
    mm_segment_t old_fs;
    struct file* filp = (struct file*)handle;
    VOS_INT32 status;
    loff_t pos = 0;

    if (unlikely((UDI_HANDLE)VOS_ERROR == handle || (UDI_HANDLE)0 == handle)) 
    {
        /*lint -save -e515*/
        pr_emerg("%s, invalid param\n", __FUNCTION__);
        /*lint -restore*/
        return (UDI_HANDLE)(VOS_ERROR);
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
    /*lint -save -e151 -e529*/
    status = vfs_write(filp, (void __force __user *)pMemObj, u32Size, &pos);
    set_fs(old_fs);
    /*lint -restore*/
    return status;
/*lint -save -e529*/
}
/*lint -restore*/
/*****************************************************************************
* 函 数 名  : diag_udi_read
*
* 功能描述  : 数据读
*
* 输入参数  : handle:  设备的handle
*             pMemObj: buffer内存 或 内存链表对象
*             u32Size: 数据读尺寸 或 内存链表对象可不设置
* 输出参数  :
*
* 返 回 值  : 完成字节数 或 成功/失败
*****************************************************************************/
VOS_INT32 diag_udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size)
{
    mm_segment_t old_fs;
    struct file* filp = (struct file*)handle;
    VOS_INT32 status;
    loff_t pos = 0;

    if (unlikely((UDI_HANDLE)VOS_ERROR == handle || (UDI_HANDLE)0 == handle)) 
    {
        /*lint -save -e515*/
        pr_emerg("%s, invalid param\n", __FUNCTION__);
        /*lint -restore*/
        return (UDI_HANDLE)(VOS_ERROR);
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);
/*lint -save -e151 -e529*/
    status = vfs_read(filp, (void __force __user *)pMemObj, u32Size, &pos);
    set_fs(old_fs);
    return status;
}
/*lint -restore*/
/*****************************************************************************
* 函 数 名  : diag_udi_ioctl
*
* 功能描述  : 数据通道属性配置
*
* 输入参数  : handle: 设备的handle
*             u32Cmd: IOCTL命令码
*             pParam: 操作参数
* 输出参数  :
*
* 返 回 值  : 成功/失败
*****************************************************************************/
VOS_INT32 diag_udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, VOID* pParam)
{
    mm_segment_t old_fs;
    struct file* filp = (struct file*)handle;
    VOS_INT32 status;

    if (unlikely((UDI_HANDLE)VOS_ERROR == handle || (UDI_HANDLE)0 == handle))
    {
        /*lint -save -e515*/
        pr_emerg("%s, invalid param\n", __FUNCTION__);
        /*lint -restore*/
        return (UDI_HANDLE)(VOS_ERROR);
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

	printk("%s:filp=0x%x,u32Cmd=%d\n",__FUNCTION__,filp,u32Cmd);
    status = do_vfs_ioctl(filp, 0, (unsigned int)u32Cmd, (unsigned long)pParam);
    set_fs(old_fs);
    return status;
}

/*lint -restore +e40 +e63*/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


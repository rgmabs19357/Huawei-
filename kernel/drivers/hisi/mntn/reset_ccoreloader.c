
#include <mach/reset.h>
#include <linux/module.h>
#include <linux/slab.h>
#include "../../rfile/rfilesystem_process.h"
#include "../../rfile/rfilesystem_logunit.h"
#include "reset_secure.h"
#include "reset_ccoreloader.h"
#include <linux/io.h>
#include <linux/delay.h>

#include "MemoryMap.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


unsigned int phy_img_head_ccore = 0;
unsigned int phy_img_buf_ccore = 0;

int      g_load_modem_addr = 0;
int      g_load_bbe16_addr = 0;
typedef unsigned int dma_addr_t;

extern void *dma_alloc_coherent(struct device *dev, size_t size,
               dma_addr_t *dma_handle, gfp_t flag);

extern void dma_free_coherent(struct device *dev, size_t size,
             void *vaddr, dma_addr_t dma_handle);

/*****************************************************************************
变量引用
*****************************************************************************/


/*****************************************************************************
函数声明
*****************************************************************************/

/*****************************************************************************
函数定义
*****************************************************************************/


int is_binary_header_invalid(CCORE_IMAGE_HEAD_STRU* header, unsigned length)
{

    if((header->uwImageSize == 0) ||
        (header->uwImageSize > length) ||
        (header->uwSecNum > CCORE_SECTION_NUMBER_MAX)||
        (header->uwSecNum == 0))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
int is_binary_section_invalid(CCORE_IMAGE_SEC_STRU* section, CCORE_IMAGE_HEAD_STRU* header)
{



    if ((section->uhwSn >= header->uwSecNum) ||
        (section->uwSrcOffset + section->uwSize > header->uwImageSize))
    {
        return TRUE;
    }

    if ((section->enType >= CCORE_IMAGE_SEC_TYPE_BUTT) ||
        (section->enLoadAttrib >= CCORE_IMAGE_SEC_LOAD_BUTT))
    {
        return TRUE;
    }
    return FALSE;

}

/*****************************************************************************
 函 数 名  : ccorereset_loadcbin
 功能描述  : 加载CCORE映像，并解复位CCORE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_loadcbin(void)
{
    char            *image_name = "modemimage";
    unsigned int    image_size = EMMC_BLOCK_SIZE;
    int             image_real_size = 0;
    char            *buff = 0;

    /* 以下是新增的安全校验代码 */
#ifdef BSP_C_HIFI_RESET_ALONE_SEC_FEATURE
    if (TRUE == check_secure_mode())
    {
        if (check_image_in_emmc(ID_CP_OS) != BSP_RESET_OK)
        {
            printk(KERN_ERR "%s: modem image is not security\n", __FUNCTION__);
            iounmap(buff);
            buff = NULL;
            return BSP_RESET_ERROR;
        }
    }
#else
    image_size = MODEM_ZIP_SIZE;
    /*加载modem bin用的是MODEM_RESET_LOAD_CBIN_ADDR这段内存，所以需要判断!!*/
    if (image_size > MODEM_RESET_LOAD_CBIN_SIZE)
    {
        printk(KERN_ERR "%s: error modem size is too large to read from flash!! %d > %d\n", __FUNCTION__, image_size, MODEM_RESET_LOAD_CBIN_SIZE);
        return BSP_RESET_ERROR;
    }
    buff = ioremap_nocache(MODEM_ZIP_LOAD_ADDR,image_size);
    if (NULL == buff)
    {
        printk(KERN_ERR "%s: fail to remap space\n", __FUNCTION__);
        return BSP_RESET_ERROR;
    }
    memset((void*)buff, 0, image_size);
    printk(KERN_INFO "%s: read c core bin to phy addr 0x%x, virt addr 0x%x, size = %d\n", __FUNCTION__, GU_RESERVED_MEM_ADDR, (unsigned int)buff, GU_RESERVED_MEM_SIZE);

    image_real_size = bsp_mass_read((const char*)image_name, 0, image_size, buff);
    if (image_real_size < 0)
    {
        printk(KERN_ERR "%s: fail to read modem image\n", __FUNCTION__);
        iounmap(buff);
        buff = NULL;
        return BSP_RESET_ERROR;
    }
#endif

    iounmap(buff);
    buff = NULL;
    printk(KERN_INFO "%s: leave\n", __FUNCTION__);

   return BSP_RESET_OK;
}
/*****************************************************************************
 函 数 名  : ccorereset_loadcbin_loadaddr
 功能描述  : 获得c core映像加载地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_loadcbin_loadaddr(void)
{
    return g_load_modem_addr;
}

/*****************************************************************************
 函 数 名  : ccorereset_loadbbebin
 功能描述  : 加载BBE16映像
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_loadbbebin(void)
{
    int                    iRet = 0;
    char                   *image_name = "dsp";
    unsigned int           image_load_phy_addr = (GLOBAL_MEM_TDS_TABLE_ADDR);
    unsigned int           image_load_size = (GLOBAL_MEM_TDS_TABLE_SIZE + GLOBAL_MEM_LT_IMAGE_SIZE);
    char                   *buff = 0;

    g_load_bbe16_addr = image_load_phy_addr;

    buff = ioremap_nocache(image_load_phy_addr,image_load_size);
    if (NULL == buff)
    {
        printk(KERN_ERR "%s: fail to remap space\n", __FUNCTION__);
        return BSP_RESET_ERROR;
    }
    memset((void*)buff, 0, image_load_size);
    printk(KERN_INFO "%s: read bbe16 bin to phy addr 0x%x, virt addr 0x%x, size = %d\n", __FUNCTION__, image_load_phy_addr, (unsigned int)buff, image_load_size);

    iRet = bsp_mass_read((const char*)image_name, 0, image_load_size, (char *)buff);
    if(RFILE_OK != iRet)
    {
        printk(KERN_ERR "%s: read bbe16 bin fail\n", __FUNCTION__);
        iounmap((void*)buff);
    }

    iounmap((void*)buff);
    printk(KERN_INFO "%s: leave\n", __FUNCTION__);
    return iRet;
}

/*****************************************************************************
 函 数 名  : ccorereset_loadbbebin_loadaddr
 功能描述  : 获得bbe16映像加载地址
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int ccorereset_loadbbebin_loadaddr(void)
{
    return g_load_bbe16_addr;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

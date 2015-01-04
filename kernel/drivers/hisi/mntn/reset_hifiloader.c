

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <mach/reset.h>
#include <mach/hardware.h>
#include <soc_sctrl_interface.h>
#include <soc_ao_sctrl_interface.h>
#include <soc_pmctrl_interface.h>
#include <drv_mailbox_cfg.h>
#include <drv_mem_remap.h>
#include "drv_hifi_if.h"
#include "reset_hifiloader.h"
#include "../../rfile/rfilesystem_process.h"
#include "MemoryLayout.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
unsigned int phy_img_head = 0;
unsigned int phy_img_buf = 0;
typedef unsigned int dma_addr_t;

extern void *dma_alloc_coherent(struct device *dev, size_t size,
			   dma_addr_t *dma_handle, gfp_t flag);

extern void dma_free_coherent(struct device *dev, size_t size,
			 void *vaddr, dma_addr_t dma_handle);
/*****************************************************************************
  3 函数实现
*****************************************************************************/


void drv_hifi_power_up(void)
{
    /*虚实地址转换*/
    unsigned long sctrl_on  = (unsigned long)IO_ADDRESS(SOC_SC_ON_BASE_ADDR);
    unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);
    unsigned long pmctrl    = (unsigned long)IO_ADDRESS(SOC_PMCTRL_BASE_ADDR);

    /* 加载前先复位hifi */
    writel(0x1<<6, SOC_SCTRL_SC_PERIPH_RSTEN0_ADDR(sctrl_off));

    /* PW EN，默认已打开 */

    /* 关闭时钟 */
    writel(0x1<<27,  SOC_SCTRL_SC_PERIPH_CLKDIS12_ADDR(sctrl_off));

    /* 选择HIFI的PLL，源自PERIPH_PLL */
    writel(0x90, SOC_PMCTRL_CLKCFG4BIT1_ADDR(pmctrl));

    /* 配置4分频，输出360MHz */
    writel(0x83, SOC_SCTRL_SC_CLKCFG8BIT4_ADDR(sctrl_off));

    /* 外设时钟使能 */
    writel(0x1<<27,  SOC_SCTRL_SC_PERIPH_CLKEN12_ADDR(sctrl_off));

    /* 打开下电区总时钟 */
    writel(0x1<<8, SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(sctrl_on));

    mdelay(1);

    /* PW ISO DIS */
    writel(0x1<<8,  SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(sctrl_on));

    /* 下电区总解复位 */
    writel(0x1<<8,  SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(sctrl_on));

    /* 解复位IP */
    writel(0x1<<6, SOC_SCTRL_SC_PERIPH_RSTDIS0_ADDR(sctrl_off));

    mdelay(1);

}
void drv_hifi_phy2virt(unsigned int *sec_addr)
{
    if (*sec_addr >= HIFI_PHY2VIRT_BEGIN_ADDR && *sec_addr <= HIFI_PHY2VIRT_END_ADDR) {
        *sec_addr -= HIFI_PHY2VIRT_OFFSET;
    }
}


void drv_hifi_fill_mb_info(unsigned int addr)
{
    CARM_HIFI_DYN_ADDR_SHARE_STRU *mb_addr;
    BSP_DDR_SECT_QUERY  ddr_sec_query = {0};
    BSP_DDR_SECT_INFO   ddr_sec_info = {0};

    mb_addr = (CARM_HIFI_DYN_ADDR_SHARE_STRU*)(addr);

    mb_addr->uwProtectWord = HIFI_MB_ADDR_PROTECT;

    mb_addr->stCarmHifiMB.uwProtectWord         = HIFI_MB_ADDR_PROTECT;
    mb_addr->stCarmHifiMB.uwHifi2CarmMailBoxLen = (unsigned long)MAILBOX_QUEUE_SIZE(HIFI, CCPU, MSG);
    mb_addr->stCarmHifiMB.uwCarm2HifiMailBoxLen = (unsigned long)MAILBOX_QUEUE_SIZE(CCPU, HIFI, MSG);
    mb_addr->stCarmHifiMB.uwHifiCarmHeadAddr    = (unsigned long)MAILBOX_HEAD_ADDR(HIFI, CCPU, MSG);
    mb_addr->stCarmHifiMB.uwHifiCarmBodyAddr    = (unsigned long)MAILBOX_QUEUE_ADDR(HIFI, CCPU, MSG);
    mb_addr->stCarmHifiMB.uwCarmHifiHeadAddr    = (unsigned long)MAILBOX_HEAD_ADDR(CCPU, HIFI, MSG);
    mb_addr->stCarmHifiMB.uwCarmHifiBodyAddr    = (unsigned long)MAILBOX_QUEUE_ADDR(CCPU, HIFI, MSG);

    mb_addr->stAarmHifiMB.uwProtectWord         = HIFI_MB_ADDR_PROTECT;
    mb_addr->stAarmHifiMB.uwHifi2AarmMailBoxLen = (unsigned long)MAILBOX_QUEUE_SIZE(HIFI, ACPU, MSG);
    mb_addr->stAarmHifiMB.uwAarm2HifiMailBoxLen = (unsigned long)MAILBOX_QUEUE_SIZE(ACPU, HIFI, MSG);
    mb_addr->stAarmHifiMB.uwHifiAarmHeadAddr    = (unsigned long)MAILBOX_HEAD_ADDR(HIFI, ACPU, MSG);
    mb_addr->stAarmHifiMB.uwHifiAarmBodyAddr    = (unsigned long)MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG);
    mb_addr->stAarmHifiMB.uwAarmHifiHeadAddr    = (unsigned long)MAILBOX_HEAD_ADDR(ACPU, HIFI, MSG);
    mb_addr->stAarmHifiMB.uwAarmHifiBodyAddr    = (unsigned long)MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG);

    /*设置nv地址*/
    ddr_sec_query.enSectType = BSP_DDR_SECT_TYPE_NV;
    if (BSP_OK == BSP_DDR_GetSectInfo(&ddr_sec_query, &ddr_sec_info))
    {
        mb_addr->uwNvBaseAddrPhy = ddr_sec_info.ulSectPhysAddr;
        mb_addr->uwNvBaseAddrVirt = ddr_sec_info.ulSectVirtAddr;

        printk("drv_hifi_fill_nv_info:phy addr = %lx, virt addr = %lx.\n",mb_addr->uwNvBaseAddrPhy, mb_addr->uwNvBaseAddrVirt);
    }
}
void drv_hifi_init_mem(unsigned int share_addr_base)
{
    struct drv_hifi_sec_load_info *sec_info;

    sec_info = (struct drv_hifi_sec_load_info*)share_addr_base;

    /* 共享内存中前加magic number 0x55AA55AA */
    sec_info->sec_magic = MEM_BEGIN_CHECK32_DATA;

    /* 共享内存中后加magic number 0xAA55AA55 */
    *(unsigned int*)((char*)share_addr_base + HIFI_SHARE_ADDR_LENGTH - sizeof(int))
        = MEM_END_CHECK32_DATA;
}



int drv_hifi_check_img_head(struct drv_hifi_image_head *img_head, unsigned length)
{
    /* check image size and sections num */
    if (img_head->image_size> length
        || img_head->sections_num> HIFI_SEC_MAX_NUM) {
        return ERROR;
    }

    return OK;
}
int drv_hifi_check_sections(struct drv_hifi_image_head *img_head,
                                 struct drv_hifi_image_sec *img_sec)
{

    /* 检查SN号大于段数目
       或 段大小加源偏移量大于镜像大小
       或 段属性和类型不合法*/
    if ((img_sec->sn >= img_head->sections_num)
        || (img_sec->src_offset + img_sec->size > img_head->image_size)
        || (img_sec->type >= (unsigned char)DRV_HIFI_IMAGE_SEC_TYPE_BUTT)
        || (img_sec->load_attib >= (unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_BUTT)) {
        return ERROR;
    }

    return OK;
}


int drv_hifi_load_sec(void *img_buf, unsigned int share_mem)
{
    struct drv_hifi_sec_load_info *sec_info;
    struct drv_hifi_image_head    *head;
    struct drv_hifi_sec_addr      *dynamic_sec;
    unsigned long   iviraddr     = 0;
    unsigned long   iviraddr_src = 0;

    SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_UNION runstall_val;

    unsigned int  dynamic_sec_num = 0;
    unsigned long sec_data_num    = 0;

    unsigned int i = 0;

    unsigned long sctrl_off = (unsigned long)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);

    int ret;

    unsigned int share_mem_base_addr = HIFI_SHARE_ADDR_BASE;
    unsigned int data_addr_offset = sizeof(struct drv_hifi_sec_addr) * HIFI_DYNAMIC_SEC_MAX_NUM + sizeof(unsigned int) * 2;

    if (NULL == img_buf) {
        printk(KERN_INFO"drv_hifi_load_sec: img_buf is NULL.\n");
    	return BSP_RESET_ERROR;
    }

    head = (struct drv_hifi_image_head *)img_buf;

    printk("drv_hifi_load_sec: sections_num = %d, image_size = %lu.\n",\
                head->sections_num,head->image_size);

    /* initial share memery */
    drv_hifi_init_mem(share_mem);

    drv_hifi_power_up();

    sec_info = (struct drv_hifi_sec_load_info*)share_mem;

    for (i = 0; i < head->sections_num; i++) {
        printk("drv_hifi_load_sec:head->sections_num = %d, i = %d.\n",head->sections_num,i);

        printk("drv_hifi_load_sec:des_addr = 0x%lx, load_attib = %d, size = %lu, sn = %d, src_offset = %lu, type = %d\n", \
                          head->sections[i].des_addr,\
                          head->sections[i].load_attib,\
                          head->sections[i].size,\
                          head->sections[i].sn,\
                          head->sections[i].src_offset,\
                          head->sections[i].type);

        /* check the sections */
        ret = drv_hifi_check_sections(head, &(head->sections[i]));
        if (ret != 0) {
        	(void)printk("drv_hifi_load_sec:Invalid hifi section.\n");
            return BSP_RESET_ERROR;
        }

        /*如果段的目的地址是在0xC0000000到0xEFFFFFFF,则进行hifi虚实地址转换*/
        drv_hifi_phy2virt((unsigned int*)(&(head->sections[i].des_addr)));

        iviraddr = (unsigned long)(ioremap_nocache((head->sections[i].des_addr),head->sections[i].size));
        printk("drv_hifi_load_sec00:iviraddr is 0x%lx, phy addr is 0x%lx.\n",iviraddr, head->sections[i].des_addr);
        if ((unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_STATIC == head->sections[i].load_attib) {

            /* copy the sections */
            memcpy((void*)iviraddr,
                   (void*)((char*)head + head->sections[i].src_offset),
                   head->sections[i].size);

        } else if ((unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_DYNAMIC == head->sections[i].load_attib) {

            dynamic_sec = &(sec_info->sec_addr_info[dynamic_sec_num]);
            printk("drv_hifi_load_sec02:dynamic step1, head = 0x%x dynamic_sec = 0x%x\n", (unsigned int)head,  (unsigned int)dynamic_sec);
            /* copy the sections */
            memcpy((void*)iviraddr,
                   (void*)((char*)head + head->sections[i].src_offset),
                   head->sections[i].size);
            printk("drv_hifi_load_sec02:dynamic step2\n");
            /* 填充段信息头 */
            dynamic_sec->sec_source_addr
                = (unsigned int)(&(sec_info->sec_data[sec_data_num]));
            dynamic_sec->sec_length    = head->sections[i].size;
            dynamic_sec->sec_dest_addr = head->sections[i].des_addr;

            printk("drv_hifi_load_sec02:dynamic step3\n");
            /* 拷贝段数据到共享内存 */
            iviraddr_src = dynamic_sec->sec_source_addr;
            printk("drv_hifi_load_sec02:iviraddr is 0x%lx phy addr is 0x%x.\n",iviraddr_src, dynamic_sec->sec_source_addr);
            memcpy((void*)iviraddr_src,
               (void*)((char*)head + head->sections[i].src_offset),
                head->sections[i].size);

            /*保存share_mem的段数据源地址的物理地址，供mcu使用加载hifi*/
            dynamic_sec->sec_source_addr = share_mem_base_addr + data_addr_offset;
            data_addr_offset += head->sections[i].size;
            /* 更新段数据地址 */
            sec_data_num += head->sections[i].size;

            /* 更新非单次加载段的个数 */
            dynamic_sec_num++;

        } else if ((unsigned char)DRV_HIFI_IMAGE_SEC_UNLOAD == head->sections[i].load_attib) {

            /* 不需要加载的段，填充Hifi邮箱地址信息 */
            drv_hifi_fill_mb_info(iviraddr);

            printk("drv_hifi_load_sec:hifi unload sections.\n");
        } else {
            /*just for pclint*/
        }
        iounmap((void*)iviraddr);
    }

    /* 填充段信息头，非单次加载段的个数 */
    sec_info->sec_num = dynamic_sec_num;

    /*配置系统控制器拉高HiFi的输入信号RunStall*/
    runstall_val.value             = 0x0;
    runstall_val.reg.hifi_runstall = 0x0;

    writel(runstall_val.value, SOC_SCTRL_SC_DSP_SUBSYS_CTRL0_ADDR(sctrl_off));
    return OK;

}


int drv_hifi_read_image(void *img_head, void **img_buf)
{
    struct drv_hifi_image_head *head = NULL;
    int ret = 0;
    char **buff = NULL;

    unsigned int size = sizeof(struct drv_hifi_image_head);

    head = (struct drv_hifi_image_head *)img_head;

    buff = (char **)img_buf;

    /* read hifi image head from EMMC */
    ret = bsp_mass_read((const char*)HIFI_IMAGE_NAME, 0, size, (char *)head);
    printk(KERN_INFO"RESET LOADHIFI: after bsp_mass_read ret = %d.\n", ret);

    /* the size of hifi image */
    size = head->image_size;

    *buff = vmalloc(size);
    if (NULL == *buff)
    {
        printk(KERN_INFO"drv_hifi_read_image: Fail to malloc %d bytes in load hifi bin function\n", size);
        return BSP_RESET_ERROR;
    }

    printk(KERN_INFO"RESET RESET: read hifi bin to virt addr 0x%x, size = %d\n", (unsigned int)(*buff), size);

    memset((void*)*buff, 0, size);

    /* read hifi image head from EMMC */
    ret = bsp_mass_read((const char*)HIFI_IMAGE_NAME, 0, size, *buff);
    if (ret < 0)
    {
        printk(KERN_INFO"RESET LOADHIFI: drv_hifi_read_image:Read image %s error.\n", HIFI_IMAGE_NAME);
    	return BSP_RESET_ERROR;
    }

    /*dma_free_coherent(NULL, sizeof(struct drv_hifi_image_head),*buff,phy_img_buf);*/

    return 0;
}


int image_verification(void **img_buf)
{
#ifdef BSP_C_HIFI_RESET_ALONE_SEC_FEATURE
    ptentry *ptn;

    /* search hifi partition info in partition table */
    ptn = find_ptn(HIFI_IMAGE_NAME);
    if ( NULL == ptn ) {
    	printk("Can't find ptn %s.\n", HIFI_IMAGE_NAME);
    	return BSP_RESET_ERROR;
    }

    if (check_image_in_emmc(ptn->id) != 0){
        return BSP_RESET_ERROR;
    }

    *img_buf = g_image_load_addr;
#endif
    return 0;
}
int  execute_load_hifi(int safe_load, unsigned int share_mem)
{
    void *img_buf  = NULL;
    void *img_head = NULL;
    int  ret;
    unsigned int *share_memory = NULL;

    share_memory = ioremap_nocache(share_mem,HIFI_SHARE_ADDR_LENGTH);
    if (NULL == share_memory)
    {
        printk(KERN_INFO"execute_load_hifi: Fail to IOREMAP\n");
        return BSP_RESET_ERROR;
    }

    printk(KERN_INFO"RESET LOADHIFI: Enter execute_load_hifi, safe = %d, share_mem = 0x%8x\n", safe_load, (unsigned int)share_memory);

	img_head = (struct drv_hifi_image_head *)kmalloc(sizeof(struct drv_hifi_image_head),GFP_KERNEL);
    if (NULL == img_head)
    {
        iounmap(share_memory);
        printk(KERN_INFO"RESET LOADHIFI: execute_load_hifi: alloc img_head error.\n");
        return BSP_RESET_ERROR;
    }

    if (HIFI_SAFE_LOAD == safe_load)
    {
        /* Hifi镜像安全校验 */
        ret = image_verification(&img_buf);
        if (ret != 0)
        {
            printk(KERN_INFO"RESET LOADHIFI: execute_load_hifi:Hifi image verification error.\n");
            kfree(img_head);
            iounmap(share_memory);
            return BSP_RESET_ERROR;
        }
    }
    else
    {
        /* 如果没有安全校验，调用下面接口读取Hifi镜像 */
        ret = drv_hifi_read_image(img_head, (void **)&img_buf);
        if (ret != 0)
        {
            /* 读取镜像失败 */
            printk(KERN_INFO"RESET LOADHIFI: execute_load_hifi:Read image error.\n");
            kfree(img_head);
            vfree(img_buf);
            iounmap(share_memory);
            return BSP_RESET_ERROR;
        }
    }

    /* 调用drv_hifi_load_sec，解析各个段，并加载 */
    ret = drv_hifi_load_sec(img_buf, (unsigned int)share_memory);
    if (ret != 0)
    {
        /* 加载镜像失败 */
        printk(KERN_INFO"RESET LOADHIFI: execute_load_hifi:Read sections error.\n");
        kfree(img_head);
        iounmap(share_memory);
        vfree(img_buf);
        return BSP_RESET_ERROR;
    }

    kfree(img_head);
    iounmap(share_memory);
    vfree(img_buf);
    return 0;
}
int check_secure_mode(void)
{
    /*stub*/
    return FALSE;
}
/*****************************************************************************
 函 数 名  : hifireset_loadhifibin
 功能描述  : 加载hifi映像
 输入参数  : 无
 输出参数  : 无
 返 回 值  : int
*****************************************************************************/
int hifireset_loadhifibin(void)
{
            /* load hifi */
    if (TRUE == check_secure_mode())
    {
        printk(KERN_INFO"RESET LOADHIFI: It's secure mode\n");

        if (execute_load_hifi((int)HIFI_SAFE_LOAD, (unsigned int)HIFI_SHARE_ADDR_BASE))
        {
            return BSP_RESET_ERROR;
        }
    }
    else
    {
        printk(KERN_INFO"RESET LOADHIFI: It's un-secure mode\n");
        if (execute_load_hifi((int)HIFI_UNSAFE_LOAD, (unsigned int)HIFI_SHARE_ADDR_BASE))
        {
            return BSP_RESET_ERROR;
        }
    }

    return BSP_RESET_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


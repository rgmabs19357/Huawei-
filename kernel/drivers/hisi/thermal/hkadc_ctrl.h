/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hkadc_ctrl.h
  版 本 号   : 初稿
  作    者   : 
  生成日期   : 2013年6月23日
  最近修改   :
  功能描述   : A核温度获取模块
                1.从共享内存读取hkadc数据的
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月23日
    作    者   : 
    修改内容   : 创建文件

******************************************************************************/
#include "drv_temp_cfg.h"


#include <mach/hardware.h>

#define HKADC_DEBUG(p) printk p

/*ACPU实地址向虚拟地址映射的转换接口*/
#define THERMAL_CORE_SHARE_PHY2VIRT(phy)  \
        (((unsigned int)phy) - MCU_SHARE_MEM_ADDR + MCU_SHARE_MEM_VIRT_ADDR)

/*通道属性和对应温度电压转换表*/
struct hkadc_table_data
{
    unsigned int logic_chan;
    unsigned int phy_chan;
    unsigned int ctrlflag;
    struct hkadc_nv_config hkadc_conf;
    unsigned int table_len;
    struct hkadc_tem_value temp_table[32];
};

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

extern int thermal_data_init(void);
extern int hkadc_debug_init(int chanid);
extern int hkadc_debug_uninit(int chanid);
extern int hkadc_get_shared_value(int chanid, unsigned short* volt);

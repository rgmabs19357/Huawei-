/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : hkadc_ctrl.c
  版 本 号   : 初稿
  作    者   :
  生成日期   : 2013年6月23日
  最近修改   :
  功能描述   : A核HKADC读取控制模块
                1.从共享内存读取hkadc数据的
  函数列表   :
  修改历史   :
  1.日    期   : 2013年6月23日
    作    者   :
    修改内容   : 创建文件

******************************************************************************/
#include "drv_temp_cfg.h"
#include "hkadc_value.h"
#include "hkadc_ctrl.h"
#ifdef _DRV_LLT_
#include "stdio.h"
#endif
#include <hsad/config_interface.h>

static unsigned int out_config_save[HKADC_CHAN_MAX];
static unsigned int have_config_save[HKADC_CHAN_MAX];
static unsigned short out_peroid_save[HKADC_CHAN_MAX];

struct ACPU_HKADC_PROPERTY
{
    struct hkadc_table_data* array;
    int size; 
};

struct ACPU_HKADC_PROPERTY g_acpu_hkadc_property = {NULL,0};

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
struct thermal_data_area *g_thermal_share_area =
        (struct thermal_data_area *)(THERMAL_CORE_SHARE_PHY2VIRT(M3_HKADC_DDR_ADDR));

/*ACPU hkadc通道属性，电压温度转换表*/

/*
unsigned int outconfig;   bit0-bit1 0:不输出 1:单次输出 2:循环输出
                          bit2 1:唤醒输出 0:非唤醒输出
                          bit3: 0:只输出电压 1:电压温度均输出
                          bit8: A核输出
                          bit9: C核输出
unsigned short outperiod;         循环输出时的循环周期，单位:秒
unsigned short convertlistlen;    温度转换表长度
*/
struct hkadc_table_data sophia_acpu_hkadc_property[] = 
{
    {
        /*电池*/
        HKADC_TEMP_BATTERY,
        /*物理通道*/
        HKADC_CHAN_2,
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        31,
        /*电压温度转换表*/
        {   
            {-273, 2600}, {-40, 2380}, {-36, 2331}, {-32, 2275}, {-28, 2210},
            {-24, 2137}, {-20, 2057}, {-16, 1969}, {-12, 1875}, {-8, 1775},
            {-4, 1671}, {0, 1565}, {4, 1457}, {8, 1350}, {12, 1244},
            {16, 1142}, {20, 1044}, {24, 951}, {28, 863}, {32, 781},
            {36, 705}, {40, 636}, {44, 572}, {48, 515}, {52, 462},
            {56, 415}, {60, 372}, {64, 335}, {74, 257}, {84, 199},
            {125, 74}, {0, 0},
        },
    },

     {
        /*电池ID*/
        HKADC_TEMP_BATT_ID,
        /*物理通道*/
        HKADC_CHAN_13,
        1,
        /*通道属性*/
        {0x0101, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-20, 2353}, {-15, 2282}, {-10, 2197}, {-5, 2173}, {0, 2058},
            {5, 1927}, {10, 1782}, {15, 1623}, {20, 1463}, {25, 1300},
            {30, 1141}, {35, 991}, {40, 853}, {45, 729}, {50, 619},
            {55, 523}, {60, 441}, {65, 372}, {70, 313}, {75, 263},
            {80, 222}, {85, 187}, {90, 158}, {95, 134}, {100, 113},
            {105, 97}, {110, 83}, {115, 71}, {0, 0}, {0, 0},
            {0, 0}, {0, 0},
        },
    },
    {
        /*sCamera thermal*/
        HKADC_TEMP_SCAMERA,
        /*物理通道*/
        HKADC_CHAN_7,
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-300, 2388}, {-250, 2348}, {-200, 2297}, {-150, 2233}, {-100, 2154}, {-50, 2060}, {0, 1951},
            {50, 1827}, {100, 1691}, {150, 1547}, {200, 1398}, {250, 1250},
            {300, 1105}, {350, 967}, {400, 840}, {450, 725}, {500, 622},
            {550, 532}, {600, 454}, {650, 387}, {700, 329}, {750, 280},
            {800, 239}, {850, 204}, {900, 174}, {950, 149}, {1000, 128},
            {1050, 110}, {1100, 95}, {1150, 82}, {0, 0}, {0, 0},
        },
    },
    {
        /*Flash thermal*/
        HKADC_TEMP_FLASH,
        /*物理通道*/
        HKADC_CHAN_9,
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-300, 2388}, {-250, 2348}, {-200, 2297}, {-150, 2233}, {-100, 2154}, {-50, 2060}, {0, 1951},
            {50, 1827}, {100, 1691}, {150, 1547}, {200, 1398}, {250, 1250},
            {300, 1105}, {350, 967}, {400, 840}, {450, 725}, {500, 622},
            {550, 532}, {600, 454}, {650, 387}, {700, 329}, {750, 280},
            {800, 239}, {850, 204}, {900, 174}, {950, 149}, {1000, 128},
            {1050, 110}, {1100, 95}, {1150, 82}, {0, 0}, {0, 0},
        },
    },
    {
        /*系统热区*/
        HKADC_TEMP_SYSTEMH,
        /*物理通道*/
        HKADC_CHAN_11,
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-300, 2388}, {-250, 2348}, {-200, 2297}, {-150, 2233}, {-100, 2154}, {-50, 2060}, {0, 1951},
            {50, 1827}, {100, 1691}, {150, 1547}, {200, 1398}, {250, 1250},
            {300, 1105}, {350, 967}, {400, 840}, {450, 725}, {500, 622},
            {550, 532}, {600, 454}, {650, 387}, {700, 329}, {750, 280},
            {800, 239}, {850, 204}, {900, 174}, {950, 149}, {1000, 128},
            {1050, 110}, {1100, 95}, {1150, 82}, {0, 0}, {0, 0},
        },
    },
    {
        /*系统冷区*/
        HKADC_TEMP_SYSTEML,
        HKADC_CHAN_12, 
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-300, 2388}, {-250, 2348}, {-200, 2297}, {-150, 2233}, {-100, 2154}, {-50, 2060}, {0, 1951},
            {50, 1827}, {100, 1691}, {150, 1547}, {200, 1398}, {250, 1250},
            {300, 1105}, {350, 967}, {400, 840}, {450, 725}, {500, 622},
            {550, 532}, {600, 454}, {650, 387}, {700, 329}, {750, 280},
            {800, 239}, {850, 204}, {900, 174}, {950, 149}, {1000, 128},
            {1050, 110}, {1100, 95}, {1150, 82}, {0, 0}, {0, 0},
        },
    } ,
    {
        HKADC_TEMP_PA0,
        HKADC_CHAN_5,
        0,
        {0x0102, 2, 0, {0, 0}},  
        28,
        {
            {-30, 2388}, {-25, 2348}, {-20, 2297}, {-15, 2233}, {-10, 2154}, {-5, 2060}, {0, 1951},
            {5, 1827}, {10, 1691}, {15, 1547}, {20, 1398}, {25, 1250},
            {30, 1105}, {35, 967}, {40, 840}, {45, 725}, {50, 622},
            {55, 532}, {60, 454}, {65, 387}, {70, 329}, {75, 280},
            {80, 239}, {85, 204}, {90, 174}, {95, 149}, {100, 128},
            {105, 110}, {110, 95}, {115, 82}, {0, 0}, {0, 0},
        },
    },
    {
        HKADC_TEMP_PA1,
        HKADC_CHAN_6,
        0,
        {0x0102, 2, 0, {0, 0}},  
        28,
        {
            {-30, 2388}, {-25, 2348}, {-20, 2297}, {-15, 2233}, {-10, 2154}, {-5, 2060}, {0, 1951},
            {5, 1827}, {10, 1691}, {15, 1547}, {20, 1398}, {25, 1250},
            {30, 1105}, {35, 967}, {40, 840}, {45, 725}, {50, 622},
            {55, 532}, {60, 454}, {65, 387}, {70, 329}, {75, 280},
            {80, 239}, {85, 204}, {90, 174}, {95, 149}, {100, 128},
            {105, 110}, {110, 95}, {115, 82}, {0, 0}, {0, 0},
        },
    }
};
struct hkadc_table_data default_acpu_hkadc_property[] = 
{
    {
        /*电池*/
        HKADC_TEMP_BATTERY,
        /*物理通道*/
        HKADC_CHAN_2,
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        31,
        /*电压温度转换表*/
        {
            {-273, 2600}, {-40, 2380}, {-36, 2331}, {-32, 2275}, {-28, 2210},
            {-24, 2137}, {-20, 2057}, {-16, 1969}, {-12, 1875}, {-8, 1775},
            {-4, 1671}, {0, 1565}, {4, 1457}, {8, 1350}, {12, 1244},
            {16, 1142}, {20, 1044}, {24, 951}, {28, 863}, {32, 781},
            {36, 705}, {40, 636}, {44, 572}, {48, 515}, {52, 462},
            {56, 415}, {60, 372}, {64, 335}, {74, 257}, {84, 199},
            {125, 74}, {0, 0},
        },
    },

     {
        /*电池ID*/
        HKADC_TEMP_BATT_ID,
        /*物理通道*/
        HKADC_CHAN_13,
        1,
        /*通道属性*/
        {0x0101, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-20, 2353}, {-15, 2282}, {-10, 2197}, {-5, 2173}, {0, 2058},
            {5, 1927}, {10, 1782}, {15, 1623}, {20, 1463}, {25, 1300},
            {30, 1141}, {35, 991}, {40, 853}, {45, 729}, {50, 619},
            {55, 523}, {60, 441}, {65, 372}, {70, 313}, {75, 263},
            {80, 222}, {85, 187}, {90, 158}, {95, 134}, {100, 113},
            {105, 97}, {110, 83}, {115, 71}, {0, 0}, {0, 0},
            {0, 0}, {0, 0},
        },
    },
#if 0
     {
        /*camera0 ID*/
        HKADC_TEMP_CAMERA0_ID,
        /*物理通道*/
        HKADC_CHAN_9,
        1,
        /*通道属性*/
        {0x0101, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-20, 2353}, {-15, 2282}, {-10, 2197}, {-5, 2173}, {0, 2058},
            {5, 1927}, {10, 1782}, {15, 1623}, {20, 1463}, {25, 1300},
            {30, 1141}, {35, 991}, {40, 853}, {45, 729}, {50, 619},
            {55, 523}, {60, 441}, {65, 372}, {70, 313}, {75, 263},
            {80, 222}, {85, 187}, {90, 158}, {95, 134}, {100, 113},
            {105, 97}, {110, 83}, {115, 71}, {0, 0}, {0, 0},
            {0, 0}, {0, 0},
        },
    },
#endif
    {
        /*camera1 ID*/
        HKADC_TEMP_CAMERA1_ID,
        /*物理通道*/
        HKADC_CHAN_7,
        1,
        /*通道属性*/
        {0x0101, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-20, 2353}, {-15, 2282}, {-10, 2197}, {-5, 2173}, {0, 2058},
            {5, 1927}, {10, 1782}, {15, 1623}, {20, 1463}, {25, 1300},
            {30, 1141}, {35, 991}, {40, 853}, {45, 729}, {50, 619},
            {55, 523}, {60, 441}, {65, 372}, {70, 313}, {75, 263},
            {80, 222}, {85, 187}, {90, 158}, {95, 134}, {100, 113},
            {105, 97}, {110, 83}, {115, 71}, {0, 0}, {0, 0},
            {0, 0}, {0, 0},
        },
    },

    {
        /*系统热区*/
        HKADC_TEMP_SYSTEMH,
        /*物理通道*/
        HKADC_CHAN_11,
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-300, 2388}, {-250, 2348}, {-200, 2297}, {-150, 2233}, {-100, 2154}, {-50, 2060}, {0, 1951},
            {50, 1827}, {100, 1691}, {150, 1547}, {200, 1398}, {250, 1250},
            {300, 1105}, {350, 967}, {400, 840}, {450, 725}, {500, 622},
            {550, 532}, {600, 454}, {650, 387}, {700, 329}, {750, 280},
            {800, 239}, {850, 204}, {900, 174}, {950, 149}, {1000, 128},
            {1050, 110}, {1100, 95}, {1150, 82}, {0, 0}, {0, 0},
        },
    },

    {
        /*系统冷区*/
        HKADC_TEMP_SYSTEML,
        HKADC_CHAN_12, 
        1,
        /*通道属性*/
        {0x0102, 2, 0, {0, 0}},
        /*电压温度转换表长度*/
        28,
        /*电压温度转换表*/
        {
            {-300, 2388}, {-250, 2348}, {-200, 2297}, {-150, 2233}, {-100, 2154}, {-50, 2060}, {0, 1951},
            {50, 1827}, {100, 1691}, {150, 1547}, {200, 1398}, {250, 1250},
            {300, 1105}, {350, 967}, {400, 840}, {450, 725}, {500, 622},
            {550, 532}, {600, 454}, {650, 387}, {700, 329}, {750, 280},
            {800, 239}, {850, 204}, {900, 174}, {950, 149}, {1000, 128},
            {1050, 110}, {1100, 95}, {1150, 82}, {0, 0}, {0, 0},
        },
    } ,
    {
        HKADC_TEMP_PA0,
        HKADC_CHAN_5,
        0,
        {0x0102, 2, 0, {0, 0}},
        28,
        {
            {-30, 2388}, {-25, 2348}, {-20, 2297}, {-15, 2233}, {-10, 2154}, {-5, 2060}, {0, 1951},
            {5, 1827}, {10, 1691}, {15, 1547}, {20, 1398}, {25, 1250},
            {30, 1105}, {35, 967}, {40, 840}, {45, 725}, {50, 622},
            {55, 532}, {60, 454}, {65, 387}, {70, 329}, {75, 280},
            {80, 239}, {85, 204}, {90, 174}, {95, 149}, {100, 128},
            {105, 110}, {110, 95}, {115, 82}, {0, 0}, {0, 0},
        },
    },
    {
        HKADC_TEMP_PA1,
        HKADC_CHAN_6,
        0,
        {0x0102, 2, 0, {0, 0}},
        28,
        {
            {-30, 2388}, {-25, 2348}, {-20, 2297}, {-15, 2233}, {-10, 2154}, {-5, 2060}, {0, 1951},
            {5, 1827}, {10, 1691}, {15, 1547}, {20, 1398}, {25, 1250},
            {30, 1105}, {35, 967}, {40, 840}, {45, 725}, {50, 622},
            {55, 532}, {60, 454}, {65, 387}, {70, 329}, {75, 280},
            {80, 239}, {85, 204}, {90, 174}, {95, 149}, {100, 128},
            {105, 110}, {110, 95}, {115, 82}, {0, 0}, {0, 0},
        },
    }
};

/*v9r1 电池放电温度保护*/
struct sys_temp_cfg default_bat_tempproc_conf =
{
    /*enable*/      0x0000,
    /*hkadc_id*/    2,
    /*high_thres*/  55,
    /*high_count*/  10,
    /*low_thres*/   -5,
    /*low_count*/   10,
    /*reserved[2]*/{ 0, 0}
};

/*****************************************************************************
函 数 名  : hkadc_tempvolt_trans
功能描述  :
输入参数  :
                      ucChan       :通道值
                      tempvalue    :温度值
                      hkAdcTable   :电压与其余数据的换算表
                      tempTableLen :hkadc电压温度转换表的长度
输出参数  :
           N/A
返 回 值  :
           换算完的数据
调用函数  :
被调函数  :

修改历史      :
 1.日    期   : 2013年5月6日
   作    者   : 
   修改内容   : 新生成函数

*****************************************************************************/

unsigned short hkadc_tempvolt_trans(unsigned char ucChan,
                short tempvalue,
                unsigned short *hkAdcTable,
                unsigned short tempTableLen)
{
    unsigned short usTemNum = 0x00;          /*记录温度个数*/
    unsigned short RetVal = 0x00;

    struct hkadc_tem_value *pstTemVoltTAble = (struct hkadc_tem_value *)hkAdcTable;
    struct hkadc_tem_value *pstTemp = (struct hkadc_tem_value *)hkAdcTable;

    /*need convert*/
    if(!hkAdcTable)
    {
        printk(KERN_ERR "hkadc_tempvolt_trans failed ucChan %d\n", ucChan);
        /*直接返回电压*/
        return HKADC_VALUE_INVALID;
    }

    for(usTemNum=0; usTemNum< tempTableLen;usTemNum++)
    {
        if((0x00 == pstTemp->volt) && (0x00 == pstTemp->temp))
        {
            break;
        }
        pstTemp++;
    }

    /*NV项无效，返回无效值*/
    if((0x00 == pstTemVoltTAble->temp) && (0x00 == pstTemVoltTAble->volt) )
    {
        printk(KERN_ERR "hkadc_tempvolt_trans failed\n");

        return HKADC_VALUE_INVALID;
    }
    /*NV项数据合法*/

    /*判断极端值*/
    if(tempvalue <= pstTemVoltTAble->temp)
    {
        RetVal =  pstTemVoltTAble->volt;
        return RetVal;
    }

    pstTemp =(struct hkadc_tem_value *)((pstTemVoltTAble + usTemNum) -1);
    if(tempvalue >= pstTemp->temp)
    {
        RetVal = pstTemp->volt;
        return RetVal;
    }

    /*根据温度值，进行插值计算*/
    while(tempvalue > pstTemVoltTAble->temp)
    {
        pstTemVoltTAble++;
    }

    pstTemp = (struct hkadc_tem_value *)(pstTemVoltTAble -1);
    /*指向前一个元素*/

    RetVal = pstTemp->volt - (((tempvalue - pstTemp ->temp) * (pstTemp->volt - pstTemVoltTAble->volt)) \
                /(pstTemVoltTAble->temp - pstTemp->temp));

    printk(KERN_INFO "hkadc_tempvolt_trans %d\n", RetVal);

    return RetVal;

}

/*****************************************************************************
 函 数 名  : bat_tempprotect_param_init
 功能描述  : 电池放电温保参数初始化
 输入参数  :
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年5月13日
    作    者   :
    修改内容   : 新生成函数

*****************************************************************************/
int bat_tempprotect_param_init(void)
{
    int ret = -1;
    struct hkadc_chan_config*  chan_cfg = g_thermal_share_area->chan_cfg;
    int bat_hkadc_id = 0;
    unsigned short volt_high_thres;
    unsigned short volt_low_thres;

    printk(KERN_ALERT"enter, enable %d, bat_hkadc_id %d, \
        high_thres %d, high_count %d, low_thres %d, low_count %d\n",
        g_thermal_share_area->sys_temp_cfg.enable,
        g_thermal_share_area->sys_temp_cfg.hkadc_id,
        g_thermal_share_area->sys_temp_cfg.high_thres,
        g_thermal_share_area->sys_temp_cfg.high_count,
        g_thermal_share_area->sys_temp_cfg.low_thres,
        g_thermal_share_area->sys_temp_cfg.low_count);


    /*将电池温保的温度阀值，改成电压*/
    bat_hkadc_id = g_thermal_share_area->sys_temp_cfg.hkadc_id;
    if (bat_hkadc_id >= HKADC_CHAN_MAX)
        return ret;

    /*高温阀值转换 */
    volt_high_thres = hkadc_tempvolt_trans(bat_hkadc_id, g_thermal_share_area->sys_temp_cfg.high_thres,
                (unsigned short *)chan_cfg[bat_hkadc_id].temp_table, chan_cfg[bat_hkadc_id].temp_data_len);

    if (volt_high_thres == HKADC_VALUE_INVALID)
    {
        printk(KERN_ALERT"hkadc_tempvolt_trans failed\n");
        g_thermal_share_area->sys_temp_cfg.high_thres = 0;
    }
    else
    {
        g_thermal_share_area->sys_temp_cfg.high_thres = volt_high_thres;
        ret = 0;
    }

    /*低温阀值转换 */
    volt_low_thres = hkadc_tempvolt_trans(bat_hkadc_id, g_thermal_share_area->sys_temp_cfg.low_thres,
                (unsigned short *)chan_cfg[bat_hkadc_id].temp_table, chan_cfg[bat_hkadc_id].temp_data_len);

    if (volt_low_thres == HKADC_VALUE_INVALID)
    {
        printk(KERN_ALERT"hkadc_tempvolt_trans failed\n");
        ret = -1;
    }
    /*低温阀值如果转换失败，直接使用HKADC_VALUE_INVALID*/
    g_thermal_share_area->sys_temp_cfg.low_thres = volt_low_thres;

    printk(KERN_ALERT"after, enable %d, bat_hkadc_id %d, \
        high_thres %d, high_count %d, low_thres %d, low_count %d\n",
        g_thermal_share_area->sys_temp_cfg.enable,
        g_thermal_share_area->sys_temp_cfg.hkadc_id,
        g_thermal_share_area->sys_temp_cfg.high_thres,
        g_thermal_share_area->sys_temp_cfg.high_count,
        g_thermal_share_area->sys_temp_cfg.low_thres,
        g_thermal_share_area->sys_temp_cfg.low_count);


    return ret;
}

void acpu_hkadc_fill_chan_map(void)
{
    int i = 0;
    int logic_id;
    int phy_id;
    struct drv_hkadc_map * chan_map;

    for (i = 0; i < g_acpu_hkadc_property.size; i++)
    {
        logic_id = g_acpu_hkadc_property.array[i].logic_chan;
        phy_id = g_acpu_hkadc_property.array[i].phy_chan;
        chan_map = bsp_hkadc_get_chan_map(logic_id);
        if (HKADC_NULL != chan_map)
        {
            printk(KERN_ALERT"acpu_hkadc_fill_chan_map logic_id->phyID: %d -> %d \n",
                            logic_id, phy_id);
            chan_map->phy_chan = phy_id;
        }
        else
        {
            printk(KERN_ALERT"acpu_hkadc_fill_chan_map get map ERROR: logic_id %d \n",
                            logic_id);
        }   
    }

}

int thermal_data_init(void)
{
    int i = 0;
    int phy_chan;
    struct hkadc_chan_config*  chan_cfg = g_thermal_share_area->chan_cfg;

    if(product_type("SOPHIA"))
    {
        g_acpu_hkadc_property.array = sophia_acpu_hkadc_property; 
        g_acpu_hkadc_property.size = sizeof(sophia_acpu_hkadc_property)/sizeof(struct hkadc_table_data);
    }else
    {
        g_acpu_hkadc_property.array = default_acpu_hkadc_property;
        g_acpu_hkadc_property.size = sizeof(default_acpu_hkadc_property)/sizeof(struct hkadc_table_data);
    }


    /*1.填充ACPU每个通道的配置数据*/
    for (i = 0; i < g_acpu_hkadc_property.size; i++)
    {
        if(g_acpu_hkadc_property.array[i].ctrlflag == 0)
            continue;
        phy_chan = g_acpu_hkadc_property.array[i].phy_chan;
        chan_cfg[phy_chan].outcfg.out_config = g_acpu_hkadc_property.array[i].hkadc_conf.outconfig;
        chan_cfg[phy_chan].out_peroid = g_acpu_hkadc_property.array[i].hkadc_conf.outperiod;
        chan_cfg[phy_chan].temp_data_len = g_acpu_hkadc_property.array[i].table_len;
        memcpy(chan_cfg[phy_chan].temp_table, g_acpu_hkadc_property.array[i].temp_table, 
            (sizeof(struct hkadc_tem_value) * g_acpu_hkadc_property.array[i].table_len));

        chan_cfg[phy_chan].have_config = 1;

        printk(KERN_ALERT"phy [%d], out_config %x, out_period %d, temp_data_len %d\n", \
                g_acpu_hkadc_property.array[i].phy_chan, chan_cfg[g_acpu_hkadc_property.array[i].phy_chan].outcfg.out_config,  \
                chan_cfg[g_acpu_hkadc_property.array[i].phy_chan].out_peroid, chan_cfg[g_acpu_hkadc_property.array[i].phy_chan].temp_data_len);            
   
    }

    /*2.填充g_hkadc_chan_map中的物理通道号*/
    acpu_hkadc_fill_chan_map();

    /*3.读取并填充系统放电温保配置*/
    memcpy((void *)(&g_thermal_share_area->sys_temp_cfg), (void *)&default_bat_tempproc_conf, \
            sizeof(struct sys_temp_cfg));


    /*4.将电池温保的温度阀值，改成电压*/
    if (bat_tempprotect_param_init() != 0)
    {
        printk(KERN_ALERT"bat_tempprotect_param_init failed\n");
        //return -1;
    }

    /*5.设置完成标记, 与MCU同步电池温保参数配置*/
    g_thermal_data_area->magic_end = HKADC_INIT_MAGIC_CODE;

    return 0;
}

int hkadc_debug_init(int chanid)
{
	struct hkadc_chan_config*  chan_cfg = g_thermal_share_area->chan_cfg;

	out_config_save[chanid] = chan_cfg[chanid].outcfg.out_config ;
	out_peroid_save[chanid] = chan_cfg[chanid].out_peroid;
	have_config_save[chanid] = chan_cfg[chanid].have_config;
	chan_cfg[chanid].outcfg.out_config = chan_cfg[chanid].outcfg.out_config | 0x0102;
	chan_cfg[chanid].out_peroid = 1;	

	chan_cfg[chanid].have_config = 1;
	
	return 0;
}

int hkadc_debug_uninit(int chanid)
{
	struct hkadc_chan_config*  chan_cfg = g_thermal_share_area->chan_cfg;
	 
	chan_cfg[chanid].outcfg.out_config = out_config_save[chanid];
	chan_cfg[chanid].out_peroid = out_peroid_save[chanid];	

	chan_cfg[chanid].have_config = have_config_save[chanid];

	return 0;
}

int hkadc_get_shared_value(int chanid, unsigned short* volt)
{ 
    struct hkadc_chan_out * chan_out = g_thermal_data_area->chan_out;
    struct hkadc_chan_config *chan_cfg = g_thermal_data_area->chan_cfg;
    short  volt_l;
    short  volt_r;
    unsigned int count;
    int ret = 0; 
    unsigned short voltvalue;
    OUT_PROP_CONFIG outConfig;

    /*如果通道没有配置，直接返回HKADC_ERROR*/
    if (chan_cfg[chanid].have_config == 0)
        return -1;
        
    outConfig = chan_cfg[chanid].outcfg.bit_out_config;
    
    /*比较电压的原始值和取反值，如果相符合则返回原始值*/
    count = 5;        
    do {   
        volt_l = (short)chan_out[chanid].volt_l;
        volt_r = (short)chan_out[chanid].volt_r;
    } while ((count--) && (~volt_l != volt_r));

    if (~volt_l == volt_r) {
        voltvalue = volt_l;
    } else {
        return -1;
    }
      
    if (volt) { 
        *volt = voltvalue;
    }

    return ret;
}


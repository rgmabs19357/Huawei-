/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : tp-balong-acpu.c
  版 本 号   : 初稿
  生成日期   : 2012年7月7日
  最近修改   :
  功能描述   : Balong V9R1 TP的A核驱动
  函数列表   :
  修改历史   :
  1.日    期   : 2012年7月7日
    修改内容   : 创建文件

******************************************************************************/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include <drv_mb.h>
#include "synaptics-tp-acpu.h"
//#include "drv_mailbox_ifc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*打桩宏定义*/



/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*input 设备指针*/
struct input_dev *g_syn_tp_input_dev = (struct input_dev *)NULL;

/* 是否支持多点触控 */
int g_is_support_multi_touch = 0;
int syn_dump_platform_data(const STRU_TP_PLATFORM_DATA *p_tp_platform_data);

/*****************************************************************************
  3 函数实现
*****************************************************************************/
ssize_t syn_virtual_keys_show(struct kobject *kobj,
                                    struct kobj_attribute *attr, char *buf)
{
    return sprintf(buf,
                    __stringify(EV_KEY) ":" __stringify(KEY_BACK)   ":125:1380:160:90"
                    ":" __stringify(EV_KEY) ":" __stringify(KEY_HOMEPAGE)   ":360:1380:160:90"
                    ":" __stringify(EV_KEY) ":" __stringify(KEY_MENU) ":598:1380:160:90\n");
}

struct kobj_attribute syn_virtual_keys_attr =
{
    .attr =
    {
        .name = "virtualkeys.synaptics",
        .mode = S_IRUGO,
    },
    .show = &syn_virtual_keys_show,
};

struct attribute *syn_properties_attrs[] =
{
    &syn_virtual_keys_attr.attr,
    NULL
};

struct attribute_group syn_properties_attr_group =
{
    .attrs = syn_properties_attrs,
};

void __init syn_virtual_keys_init(void)
{
    struct kobject *properties_kobj;
    int ret = 0;

    properties_kobj = (struct kobject *)kobject_create_and_add("board_properties", NULL);

    if(properties_kobj)
    {
        ret = sysfs_create_group(properties_kobj, &syn_properties_attr_group);
    }

    if(!properties_kobj || ret)
    {
        printk("%s: failed to create board_properties!\n", __func__);
    }
}

/*****************************************************************************
 函 数 名  : syn_rmi4_config_input_dev
 功能描述  : 触摸屏配置输入设备
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
int syn_rmi4_config_input_dev(
                struct input_dev *input_device,
                const STRU_TP_PLATFORM_DATA *platform_data)
{
    int ret = OK;

    input_device->name = "synaptics";
    set_bit(EV_SYN,         input_device->evbit);
    set_bit(EV_ABS,         input_device->evbit);
    set_bit(EV_REL,         input_device->evbit);
    set_bit(EV_KEY,         input_device->evbit);
    set_bit(ABS_X,          input_device->absbit);
    set_bit(ABS_Y,          input_device->absbit);
    set_bit(BTN_TOUCH,      input_device->keybit);
    set_bit(ABS_PRESSURE,   input_device->absbit);
    set_bit(ABS_TOOL_WIDTH, input_device->absbit);

    input_set_abs_params(input_device, ABS_X, 0,
            platform_data->x_res, platform_data->fuzz_x, 0);

    input_set_abs_params(input_device, ABS_Y, 0,
            platform_data->y_res, platform_data->fuzz_y, 0);

    input_set_abs_params(input_device, ABS_PRESSURE,
            0, 255, platform_data->fuzz_p, 0);

    input_set_abs_params(input_device, ABS_TOOL_WIDTH,
            0, 15, platform_data->fuzz_w, 0);

    input_set_abs_params(input_device, ABS_MT_TRACKING_ID, 0,
            platform_data->points_supported, 0, 0);

    input_set_abs_params(input_device, ABS_MT_POSITION_X, 0,
            platform_data->x_res, platform_data->fuzz_x, 0);

    input_set_abs_params(input_device, ABS_MT_POSITION_Y, 0,
            platform_data->y_res, platform_data->fuzz_y, 0);

    input_set_abs_params(input_device, ABS_MT_WIDTH_MAJOR, 0,
            255, platform_data->fuzz_w, 0);

    input_set_abs_params(input_device, ABS_MT_TOUCH_MAJOR, 0,
            15, platform_data->fuzz_p, 0);

    ret = input_register_device(input_device);
    if(ret)
    {
        LOG_PRINT(0, ("%s: Unable to register %s input device\n", __func__,
            input_device->name));
        return ret;
    }
    return ret;
}

/*****************************************************************************
 函 数 名  : syn_mailbox_callback
 功能描述  : 触摸屏核间通信函数
 输入参数  : unsigned int dstChannelId
             unsigned char *buffer
             unsigned int length
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
void syn_tp_mailbox_callback(unsigned int dstChannelId,unsigned char *buffer,
                                      unsigned int length)
{
    STRU_TP_DATA *tp_data;
    struct input_dev *input_device = g_syn_tp_input_dev;
    int i;

	LOG_PRINT(0, ("%s: ++\n", __func__));

    if(BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_TP_CH != dstChannelId)
    {
        LOG_PRINT(0, ("%s: dstChannelId(%d) error\n", __func__, dstChannelId));
        return;
    }

    if(NULL == buffer)
    {
        LOG_PRINT(0, ("%s: buffer error\n", __func__));
        return;
    }

    if(length != sizeof(STRU_TP_DATA))
    {
        LOG_PRINT(0, ("%s: length(%d) error\n", __func__, length));
        return;
    }
    tp_data = (STRU_TP_DATA*)buffer;


    LOG_PRINT(0, ("%s: touch_count:%d\n", __func__, tp_data->touch_count));
    /* report the data */
    if(tp_data->touch_count)
    {
        input_report_abs(input_device, ABS_X,          tp_data->x[0]);
        input_report_abs(input_device, ABS_Y,          tp_data->y[0]);
        input_report_abs(input_device, ABS_PRESSURE,   tp_data->z[0]);
        input_report_abs(input_device, ABS_TOOL_WIDTH, max(tp_data->wx[0],tp_data->wy[0]));
        input_report_key(input_device, BTN_TOUCH,      1);

        LOG_PRINT(0, ("%s: x:%d y:%d wx:%d wy:%d z:%d,support_multi_touch:%d\n", __func__,
            tp_data->x[0],tp_data->y[0],tp_data->wx[0],tp_data->wy[0],tp_data->z[0],
            g_is_support_multi_touch));

        if(g_is_support_multi_touch)
        {
            for (i = 0; i != tp_data->touch_count; i++)
            {
                input_report_abs(input_device, ABS_MT_TRACKING_ID, i);
                input_report_abs(input_device, ABS_MT_POSITION_X,  tp_data->x[i]);
                input_report_abs(input_device, ABS_MT_POSITION_Y,  tp_data->y[i]);
                input_report_abs(input_device, ABS_MT_TOUCH_MAJOR, tp_data->z[i]);
                input_report_abs(input_device, ABS_MT_WIDTH_MAJOR,
                                    max(tp_data->wx[i], tp_data->wy[i]));
                input_report_abs(input_device, ABS_MT_ORIENTATION,
                                    (tp_data->wx[i] > tp_data->wy[i] ? 1 : 0));
                input_mt_sync(input_device);

	            LOG_PRINT(0, ("%s: x:%d y:%d wx:%d wy:%d z:%d\n",
	                tp_data->x[i],tp_data->y[i],tp_data->wx[i],tp_data->wy[i],tp_data->z[i]));
            }
        }
        else
        {
            input_report_key(input_device, BTN_TOUCH,  0);
            input_report_abs(input_device, ABS_PRESSURE, 0);
            input_mt_sync(input_device);
        }
    }

    input_sync(input_device);
	LOG_PRINT(0, ("%s: --\n", __func__));
}

/*****************************************************************************
 函 数 名  : syn_tp_platform_callback
 功能描述  : 触摸屏平台信息核间通信函数
 输入参数  : unsigned int fundi
             unsigned char *buffer
             unsigned int length
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
void syn_tp_platform_callback(unsigned int fundi,unsigned char *buffer,unsigned int length)
{
    int ret = OK;
    STRU_TP_PLATFORM_DATA *p_tp_platform_data = (STRU_TP_PLATFORM_DATA *)buffer;

	LOG_PRINT(0, ("%s: ++\n", __func__));

    if(IFCP_FUNC_MCU_TP_ENABLE != (SIFCP_FUNC_E)fundi)
    {
        LOG_PRINT(0, ("%s: fundi(%d) error\n", __func__, fundi));
        return;
    }
    if(NULL == p_tp_platform_data)
    {
        LOG_PRINT(0, ("%s: p_tp_platform_data error\n", __func__));
        return;
    }

    if(sizeof(STRU_TP_PLATFORM_DATA) != length)
    {
        LOG_PRINT(0, ("%s: length(%d) error\n", __func__, length));
        return;
    }
    ret = syn_dump_platform_data(p_tp_platform_data);

    /*input设备创建*/
    g_syn_tp_input_dev = input_allocate_device();
    if(!g_syn_tp_input_dev)
    {
        LOG_PRINT(0, ("%s: failed to allocate input device.\n", __func__));
        return;
    }
    g_is_support_multi_touch = p_tp_platform_data->is_support_multi_touch;
    LOG_PRINT(0, ("%s: g_is_support_multi_touch:%d.\n", __func__, g_is_support_multi_touch));

    /* config input device parameter */
    ret = syn_rmi4_config_input_dev(g_syn_tp_input_dev, p_tp_platform_data);
    if(ret)
    {
        LOG_PRINT(0, ("%s: failed to register input device.\n", __func__));
        return;
    };

    syn_virtual_keys_init();
	LOG_PRINT(0, ("%s: --\n", __func__));
}

/*****************************************************************************
 函 数 名  : syn_tp_suspend
 功能描述  : 触摸屏挂起函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
int syn_tp_suspend(void)
{
    unsigned int ret;
	LOG_PRINT(0, ("%s: ++\n", __func__));
    ret = MB_IFC_CommCall((unsigned int)IFCP_FUNC_MCU_TP_SUSPEND,
                     (unsigned int)BSP_MAILBOX_IFC_CALL_SYNC,
                     (IFC_COMM_CALLBACK*)NULL, (unsigned char*)NULL, 0);
	LOG_PRINT(0, ("%s: MB_IFC_CommCall ret %d\n", __func__, ret));
    return OK;
}

/*****************************************************************************
 函 数 名  : syn_tp_resume
 功能描述  : 触摸屏恢复函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
int syn_tp_resume(void)
{
    unsigned int ret;
	LOG_PRINT(0, ("%s: ++\n", __func__));
    ret = MB_IFC_CommCall((unsigned int)IFCP_FUNC_MCU_TP_RESUME,
                     (unsigned int)BSP_MAILBOX_IFC_CALL_SYNC,
                     (IFC_COMM_CALLBACK*)NULL, (unsigned char*)NULL, 0);
	LOG_PRINT(0, ("%s: MB_IFC_CommCall ret %d\n", __func__, ret));
    return OK;
}

/*****************************************************************************
 函 数 名  : syn_tp_exit
 功能描述  : 触摸屏卸载函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : static void __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
void  __init syn_tp_exit(void)
{
    unsigned int ret;
	LOG_PRINT(0, ("%s: ++\n", __func__));
    ret = MB_IFC_CommCall((unsigned int)IFCP_FUNC_MCU_TP_REMOVE,
                     (unsigned int)BSP_MAILBOX_IFC_CALL_SYNC,
                     (IFC_COMM_CALLBACK*)NULL, (unsigned char*)NULL, 0);
	LOG_PRINT(0, ("%s: MB_IFC_CommCall ret %d\n", __func__, ret));
    return;
}
/*****************************************************************************
 函 数 名  : syn_tp_init
 功能描述  : 触摸屏初始化函数
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int __init
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月7日
    修改内容   : 新生成函数

*****************************************************************************/
int __init syn_tp_init(void)
{

    unsigned int ret;
    printk("begin syn tp init");

	LOG_PRINT(0, ("%s: ++\n", __func__));
    BSP_MAILBOX_IsrRegister(MAILBOX_TARGET_CPU_MCU, BSP_MAILBOX_CHANNEL_MCU_TO_ACPU_TP_CH, syn_tp_mailbox_callback);

    ret = MB_IFC_ExtendCall((unsigned int)IFCP_FUNC_MCU_TP_ENABLE,
                             (unsigned int)BSP_MAILBOX_IFC_CALL_ASYN,
                       syn_tp_platform_callback, NULL, 0, NULL, 0);
	LOG_PRINT(0, ("%s: MB_IFC_CommCall ret %d\n", __func__, ret));

    printk("after syn tp init");
    return OK;

}

module_init(syn_tp_init);
module_exit(syn_tp_exit);

MODULE_DESCRIPTION("Synaptics Touchscreen ACPU");
MODULE_LICENSE("GPL");

/*****************************************************************************
 函 数 名  : syn_dump_platform_data
 功能描述  : 触摸屏平台信息dump函数
 输入参数  : STRU_TP_PLATFORM_DATA *p_tp_platform_data 平台信息结构体指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年7月27日
    修改内容   : 新生成函数

*****************************************************************************/
int syn_dump_platform_data(const STRU_TP_PLATFORM_DATA *p_tp_platform_data)
{
    if(!p_tp_platform_data)
    {
        LOG_PRINT(0, ("%s: p_tp_platform_data error\n", __func__));
        return 0;
    };
	LOG_PRINT(0, ("irq                      :%d\n",  p_tp_platform_data->irq));
	LOG_PRINT(0, ("irq_flag                 :%d\n",  p_tp_platform_data->irq_flag));
	LOG_PRINT(0, ("flip_flags 	            :%d\n",  p_tp_platform_data->flip_flags));
	LOG_PRINT(0, ("x_res 		            :%d\n",  p_tp_platform_data->x_res));
	LOG_PRINT(0, ("y_res 		            :%d\n",  p_tp_platform_data->y_res));
	LOG_PRINT(0, ("y_all                    :%d\n",  p_tp_platform_data->y_all));
	LOG_PRINT(0, ("fuzz_x 		            :%d\n",  p_tp_platform_data->fuzz_x));
	LOG_PRINT(0, ("fuzz_y 		            :%d\n",  p_tp_platform_data->fuzz_y));
	LOG_PRINT(0, ("fuzz_p 		            :%d\n",  p_tp_platform_data->fuzz_p));
	LOG_PRINT(0, ("fuzz_w 		            :%d\n",  p_tp_platform_data->fuzz_w));
	LOG_PRINT(0, ("reset_pin                :%d\n",  p_tp_platform_data->reset_pin));
	LOG_PRINT(0, ("points_supported         :%d\n",  p_tp_platform_data->points_supported));
	LOG_PRINT(0, ("is_support_multi_touch   :%d\n",  p_tp_platform_data->is_support_multi_touch));
    return 0;

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


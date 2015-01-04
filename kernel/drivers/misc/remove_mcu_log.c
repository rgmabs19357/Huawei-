#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/list.h>
#include <linux/sysfs.h>
#include <linux/ctype.h>
#include <linux/mtd/nve_interface.h>

#define NV_PWCSWCH_NUM 295
#define NV_PWCSWCH_SIZE 4
#define MAX_RETRY   3

extern void RunMcuCmd(char* cmd);
struct nve_info_user  info;
struct delayed_work remove_mcu_log_work;
static int max_retry = MAX_RETRY; 

static int is_log_flag_checkd(void)
{
    int ret = -1;
   
    memset(&info, 0, sizeof(info));
    info.nv_number  = NV_PWCSWCH_NUM;
    strncpy( info.nv_name, "PWCSWCH",sizeof(info.nv_name));
    info.valid_size = NV_PWCSWCH_SIZE;
    info.nv_operation = NV_READ;
        
    ret = nve_direct_access( &info );
    if (0 != ret)
    { 
        printk("%s: nve_direct_access read error\n", __func__);    
        if (max_retry--) 
        {
            /* code */
            schedule_delayed_work(&remove_mcu_log_work,10*HZ);
        }
        return ret; 
    }
    printk("PWCSWCH nv_data: 0x%x 0x%x 0x%x 0x%x\n",info.nv_data[0],info.nv_data[1],info.nv_data[2],info.nv_data[3]);
    if (0x1 == info.nv_data[2])
        ret = 1;
    return ret;
}

static void remove_log_flag(void)
{
    info.nv_data[2] = 0;
    info.nv_operation = NV_WRITE;    
    if (nve_direct_access(&info)) 
    {
         printk("%s: nve_direct_access write error\n", __func__);    
         return;
    }
    memset(info.nv_data,0,sizeof(info.nv_data));

    info.nv_operation = NV_READ;
    if (nve_direct_access(&info)) 
    { 
        printk("%s: nve_direct_access read error\n", __func__);    
        return; 
    }
    printk("PWCSWCH changed nv_data: 0x%x 0x%x 0x%x 0x%x\n",info.nv_data[0],info.nv_data[1],info.nv_data[2],info.nv_data[3]);
}

static void do_remove_mcu_log(struct work_struct *work)
{
    if (1 == is_log_flag_checkd()) 
    {
        remove_log_flag();
        RunMcuCmd("MntnFunc 0 0");
    }
}

static int __init remove_mcu_log_init(void)
{
    printk("init %s",__func__);
    INIT_DELAYED_WORK(&remove_mcu_log_work, do_remove_mcu_log);
    schedule_delayed_work(&remove_mcu_log_work,10*HZ);

	return 0;
}

static void __exit remove_mcu_log_exit(void)
{
    printk("exit %s",__func__);
}

MODULE_AUTHOR("ZYP");
MODULE_DESCRIPTION("remove mcu power log");
MODULE_LICENSE("GPL");

late_initcall(remove_mcu_log_init);
module_exit(remove_mcu_log_exit);

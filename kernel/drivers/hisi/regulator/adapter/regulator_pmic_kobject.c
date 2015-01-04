/*
 * regulator pmic kobject implementation
 *
 * Copyright (C) 2004-2007 Greg Kroah-Hartman <greg@kroah.com>
 * Copyright (C) 2007 Novell Inc.
 *
 * Released under the GPL version 2 only.
 *
 */
#include <linux/kobject.h>
#include <linux/string.h>
#include <linux/sysfs.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include "pmic_common.h"
#include "regulator_pmic.h"
#include "regulator_pmic_info.h"

extern PMIC_COMSUMER_INFO pmic_comsumer_info[PMU_CHANNEL_ID_BUTT];

static ssize_t foo_show(struct kobject *kobj, struct kobj_attribute *attr,
            char *buf)
{
    char *start = buf;
    int i = 0;

    buf +=sprintf(buf, "STATUS -1:unset   0:ON   1:OFF   \n");
    buf +=sprintf(buf, "Channel ID  NAME      STATUS  Voltage mini max \n");

    for(i = BUCK_ID_BEGIN;i<PMU_CHANNEL_ID_BUTT;i++)
    {
            int  status  =  pmic_comsumer_info[i].comsumer_channel_status;
            if(-1 == status)
           {
                buf +=sprintf(buf, " %8d %16s unset %d  %d\n",
                i,
                regulator_pmic_getname_by_id(i),
                pmic_comsumer_info[i].comsumer_voltage_mini,
                pmic_comsumer_info[i].comsumer_voltage_max);

           }
            else if (0 == status)
           {
                buf +=sprintf(buf, " %8d %16s ON %d  %d\n",
                i,
                regulator_pmic_getname_by_id(i),
                pmic_comsumer_info[i].comsumer_voltage_mini,
                pmic_comsumer_info[i].comsumer_voltage_max);
           }else if(1 == status)
            {
                buf +=sprintf(buf, " %8d %16s OFF %d  %d\n",
                i,
                regulator_pmic_getname_by_id(i),
                pmic_comsumer_info[i].comsumer_voltage_mini,
                pmic_comsumer_info[i].comsumer_voltage_max);
            }

    }

    return (buf-start);
}

static ssize_t foo_store(struct kobject *kobj, struct kobj_attribute *attr,
             const char *buf, size_t count)
{
    return count;
}

static struct kobj_attribute pmic_comsumerinfo_attribute =
    __ATTR(pmic_comsumer_info, 0664, foo_show, foo_store);

/*
 * Create a group of attributes so that we can create and destroy them all
 * at once.
 */
static struct attribute *attrs[] = {
    &pmic_comsumerinfo_attribute.attr,
    NULL,   /* need to NULL terminate the list of attributes */
};

/*
 * An unnamed attribute group will put all of the attributes directly in
 * the kobject directory.  If we specify a name, a subdirectory will be
 * created for the attributes with the directory being the name of the
 * attribute group.
 */
static struct attribute_group attr_group = {
    .attrs = attrs,
};

static struct kobject *pmic_comsumerinfo_kobj;

static int __init pmic_comsumerinfo_init(void)
{
    int retval = 0;
    int i = 0;

    for(i = BUCK_ID_BEGIN;i<PMU_CHANNEL_ID_BUTT;i++)
    {
        pmic_comsumer_info[i].comsumer_channel_status = -1;
    }

    pmic_comsumerinfo_kobj = kobject_create_and_add("pmic", kernel_kobj);
    if (!pmic_comsumerinfo_kobj)
    {
         return -ENOMEM;
    }

    retval = sysfs_create_group(pmic_comsumerinfo_kobj, &attr_group);
    if (retval)
    {
         kobject_put(pmic_comsumerinfo_kobj);
    }
    return retval;
}

static void __exit pmic_comsumerinfo_exit(void)
{
    kobject_put(pmic_comsumerinfo_kobj);
}

module_init(pmic_comsumerinfo_init);
module_exit(pmic_comsumerinfo_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Tech.Co.,Ltd.<fansaihua@huawei.com>");


#include <linux/module.h>
#include <linux/device.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include "dev_common.h"

int dev_i2c_add_devices(int bus_num, struct i2c_board_info const *devs, int len)
{
    int index = 0;
    struct i2c_adapter *adapter = NULL;
    struct i2c_client **clients = NULL;

    if (devs == NULL || len == 0) 
        return -EINVAL;

    clients = kmalloc(sizeof(struct i2c_client *) * len, GFP_KERNEL);
    if (clients == NULL) {
        pr_err("%s: Failed to allocate memory for i2c clients.", __func__);
        goto err_out;
    }

    adapter = i2c_get_adapter(bus_num);
    if (NULL == adapter) {
        pr_err("%s:Failed to get adapter for bus %d", __func__, 2);
        goto err_out;
    }

    for (; index < len; index++){
        clients[index] = i2c_new_device(adapter, &devs[index]);
        if (clients[index] == NULL){
            pr_err("%s: Failed to add i2c device %s", __func__, devs[index].type);
            goto err_remove_device;
        }
    }

    kfree(clients);
    return 0;

err_remove_device:
    index--;
    while(index >= 0){
        i2c_unregister_device(clients[index]);
        index--;
    }

err_out:
    kfree(clients);
    return -EINVAL;
}
EXPORT_SYMBOL(dev_i2c_add_devices);


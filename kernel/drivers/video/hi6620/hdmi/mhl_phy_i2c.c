/* This file is only for MHL wolv40 PHY daughter board in SFT platform */
#ifdef CONFIG_MACH_HI6620SFT

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/mhl/mhl_phy_i2c.h>
#include <asm/io.h>

#define DRV_NAME         "[mhl_phy]"

static const struct i2c_device_id hisik3_mhl_phy_id[] = {
	{ MHL_PHY_I2C_NAME, 0 },        
	{},
};

struct i2c_client *mhl_phy_client = NULL;

u8 mhl_phy_read_reg(u8 reg)
{
    return i2c_smbus_read_byte_data(mhl_phy_client, reg);
}

int mhl_phy_write_reg(u8 reg, u8 val)
{
    return i2c_smbus_write_byte_data(mhl_phy_client, reg, val);
}
EXPORT_SYMBOL(mhl_phy_read_reg);
EXPORT_SYMBOL(mhl_phy_write_reg);
/******************************************************************************
* Function:       config_mhl_phy_register
* Description:    set some registers for initial
* Input:          
* Output:
* Return:
*******************************************************************************/
static void init_mhl_phy_register(void)
{	
	u8 i, val = 0;

    printk(KERN_INFO DRV_NAME "config mhl phy registers for initial\n");

    /* config wolv40 MHL PHY registers */
	mhl_phy_write_reg(0x00, 0x33);  //no power down
	mhl_phy_write_reg(0x01, 0x6c);
	mhl_phy_write_reg(0x02, 0x4d);
	mhl_phy_write_reg(0x03, 0x94);
	mhl_phy_write_reg(0x04, 0x40);
	mhl_phy_write_reg(0x05, 0x20);
	mhl_phy_write_reg(0x06, 0x30);
	mhl_phy_write_reg(0x07, 0x30);
	mhl_phy_write_reg(0x08, 0x64);
    mhl_phy_write_reg(0x09, 0x8b); 

    /* check if the registers are right */    
    printk(KERN_INFO DRV_NAME "read mhl phy register:\n");
    for (i = 0; i < 10; i++ ) {
        val = mhl_phy_read_reg(i);
        printk(KERN_INFO DRV_NAME "reg[%02x]:0x%02x\n", i, val);
    }    
}

/******************************************************************************
* Function:       match_id
* Description:    compare whether the name is same
* Input:          
* Output:
* Return:
*******************************************************************************/
static bool match_id(const struct i2c_device_id *id, const struct i2c_client *client)
{
	if (strcmp(client->name, id->name) == 0) {
		return true;
	} else {
        return false;
    }
}

/******************************************************************************
* Function:       hisik3_mhl_phy_probe
* Description:    mhl phy probe function
* Input:          
* Output:
* Return:
*******************************************************************************/
static int hisik3_mhl_phy_probe(struct i2c_client *client,
							    const struct i2c_device_id *dev_id)
{	
    struct mhl_phy_platform_data *pdata = NULL;
    int ret = 0;

    if (!match_id(&hisik3_mhl_phy_id[0], client)) {
        dev_err(&client->adapter->dev, "%s:mhl_phy:can not found dev_id matched\n"
                 , __func__);
        return -EIO;
    }
    
    dev_info(&client->adapter->dev, "mhl_phy:attached %s "
                          "into i2c adapter successfully\n", dev_id->name); 
    
	mhl_phy_client = client;        
    pdata = mhl_phy_client->dev.platform_data;
    
    /* apply gpio resource */
    if (gpio_request(pdata->gpio_reset, "mhl_phy_reset") < 0) {
        printk(KERN_ERR DRV_NAME "%s:mhl_reset GPIO request failed\n", __func__);
        ret =  -ENOMEM;
        goto mhl_fail_1;
    }
        
    if (gpio_request(pdata->gpio_mode_sel, "mhl_mode_sel") < 0) {
        printk(KERN_ERR DRV_NAME "%s:mode_sel GPIO request failed\n", __func__);
        ret =  -ENOMEM;
        goto mhl_fail_2;
    }
    
    /* set gpio direction and level */
    if (gpio_direction_output(pdata->gpio_mode_sel, 0) < 0) {
        printk(KERN_ERR DRV_NAME "%s:mod_sel GPIO direction failed\n", __func__);
        ret =  -ENOMEM;
        goto mhl_fail_3;
    }
    msleep(10);
    
    /* reset MHL PHY: first 0 and then 1 */
    if (gpio_direction_output(pdata->gpio_reset, 0) < 0) {
        printk(KERN_ERR DRV_NAME "%s:reset GPIO direction failed\n", __func__);
        ret =  -ENOMEM;
        goto mhl_fail_3;
    }
    msleep(10);     
    gpio_set_value(pdata->gpio_reset, 1);
    
	msleep(200);
    
	init_mhl_phy_register();    
    
	return 0;
    
mhl_fail_3:
    gpio_free(pdata->gpio_mode_sel);
mhl_fail_2:
    gpio_free(pdata->gpio_reset);
mhl_fail_1:    
    printk(KERN_INFO DRV_NAME "%s: function out with error\n", __func__);
    return ret;	
}

/******************************************************************************
* Function:       hisik3_mhl_phy_remove
* Description:    resource recycle when driver is removed
* Input:          
* Output:
* Return:
*******************************************************************************/
static int hisik3_mhl_phy_remove(struct i2c_client *client)
{
	struct mhl_phy_platform_data *pdata = NULL;

	if (false == match_id(&hisik3_mhl_phy_id[0], client)) {
		return 0;
	}
    
    pdata = mhl_phy_client->dev.platform_data;    
	if (!pdata) {
		printk(KERN_ERR DRV_NAME "%s:pdata is NULL!\n", __func__);
		return -ENOMEM;
	}

	gpio_free(pdata->gpio_reset);
    gpio_free(pdata->gpio_mode_sel);
    
	return 0;
}

MODULE_DEVICE_TABLE(i2c, hisik3_mhl_phy_id);

static struct i2c_driver mhl_phy_i2c_driver = {
	.driver =   {
		.name = MHL_PHY_I2C_NAME,
	},
	.id_table = hisik3_mhl_phy_id,
	.probe = hisik3_mhl_phy_probe,
	.remove = hisik3_mhl_phy_remove,
};

static int __init mhl_phy_init(void)
{
	int ret;    
    
	ret = i2c_add_driver(&mhl_phy_i2c_driver);	
	if (ret) {
		printk(KERN_ERR DRV_NAME "%s: i2c add driver error\n", __func__);
		return ret;
	}
    
    printk(KERN_INFO DRV_NAME "%s: i2c add driver success\n", __func__);
	return 0;
}

static void __exit mhl_phy_exit(void)
{
	i2c_del_driver(&mhl_phy_i2c_driver);
}

MODULE_LICENSE("GPL");
/* Don't use late_initcall, mhl phy must be intilized before mhl controller init */
module_init(mhl_phy_init); 
module_exit(mhl_phy_exit);

#endif /* CONFIG_MACH_HI6620SFT */

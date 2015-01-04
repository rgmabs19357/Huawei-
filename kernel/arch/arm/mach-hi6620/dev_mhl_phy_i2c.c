/* This file is only for MHL wolv40 PHY daughter board in SFT platform */
#ifdef CONFIG_MACH_HI6620SFT

#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/mhl/mhl_phy_i2c.h>

static struct mhl_phy_platform_data k3_mhl_phy_data =
{
	.gpio_reset 	= MHL_PHY_GPIO_RESET,        
	.gpio_mode_sel	= MHL_PHY_GPIO_MODE_SEL,
};

static struct i2c_board_info mhl_phy_i2c_device[] = { 
	[0]	= {
		.type			= MHL_PHY_I2C_NAME,
		.addr			= MHL_PHY_I2C_ADDRESS,
		.platform_data  = &k3_mhl_phy_data,
		},
};

static int __init mhl_phy_i2c_device_init(void)
{
    /* MHL PHY daughter board use I2C bus 2 */
	return i2c_register_board_info(2, mhl_phy_i2c_device, ARRAY_SIZE(mhl_phy_i2c_device));
};

arch_initcall(mhl_phy_i2c_device_init);

#endif /* CONFIG_MACH_HI6620SFT */

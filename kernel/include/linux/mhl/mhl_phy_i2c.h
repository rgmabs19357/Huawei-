/******************************************************************************
  File name   : mhl_phy_i2c.h
  Author      : -----           
  Version     : 
  Date        : 
  Description : 该头文件定义了HI6620  MHL相关结构
  History     :
  1. Date:2013-06-07
     Author: 
     Modification:添加文件头注释
******************************************************************************/


/* This file is only for MHL wolv40 PHY daughter board in SFT platform */
#ifdef CONFIG_MACH_HI6620SFT

#ifndef __LINUX_MHL_PHY_I2C_H__
#define __LINUX_MHL_PHY_I2C_H__
#include <mach/gpio.h>

/* MHL PHY slave address is 0x60, but must use 0x30 in software */
#define MHL_PHY_I2C_ADDRESS		     0x30
#define MHL_PHY_I2C_NAME             "hisik3_mhl_phy_i2c"

#define MHL_PHY_GPIO_RESET			(GPIO_0_1)
#define MHL_PHY_GPIO_MODE_SEL		(GPIO_0_5)

struct mhl_phy_platform_data
{
	int gpio_reset;    
	int gpio_mode_sel;
};

#endif /* __LINUX_MHL_PHY_I2C_H__ */

#endif /* CONFIG_MACH_HI6620SFT */

#include "drv_regulator_user.h"
#include "reg_ops.h"
#include "soc_baseaddr_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_ao_sctrl_interface.h"
#include "soc_smart_interface.h"
#include "reg_ops.h"
#include "linux/io.h"
#include "linux/spinlock.h"

/*****************************************************************************
  2 宏定义
*****************************************************************************/

/* efuse操作相关的宏定义 */
/* 后续需要根据实际的APB时钟更新 */
#if 0 //PLATFORM_TYPE == PLATFORM_FPGA
#define APB_CLK             30000000
#endif
        
#if 1 //PLATFORM_TYPE == PLATFORM_ASIC
#define APB_CLK             150000000
#endif
        
/* 烧写时序要求:
*  1.EFUSE_COUNT*Trefclk > 120ns,EFUSE_COUNT>=3. Trefclk = 1/APB_CLK,故EFUSE_COUNT取3
*  11us < (EFUSE_COUNT + PGM_COUNT) * Trefclk < 13us,取12us
*/
#if 0 //PLATFORM_TYPE == PLATFORM_FPGA
#define EFUSE_COUNT_CFG     3
#endif
        
#if 1 //PLATFORM_TYPE == PLATFORM_ASIC
#define EFUSE_COUNT_CFG     9
#endif
        
#define PGM_COUNT_CFG       ((APB_CLK / 1000000) * 12 - EFUSE_COUNT_CFG)
        
/***************************** efuse register *****************************/
#define EFUSE_BASE_REG   0 //SOC_EFUSEC_BASE_ADDR
        
#define EFUSEC_PG_EN     (1<<0)
#define EFUSEC_PRE_PG    (1<<1)
#define EFUSEC_RD_EN     (1<<2)
#define EFUSEC_SIG_SEL_INNER     (1<<3)
        
#define EFUSEC_PG_FIN (1<<0)
#define EFUSEC_RD_FIN (1<<1)
        
        /* 烧写控制 */
#define EFUSEC_PG_CTRL_POS      0
#define EFUSEC_PG_CTRL_WIDTH    1
#define EFUSEC_PG_CTRL_MASK     (((1<<EFUSEC_PG_CTRL_WIDTH)-1)<<EFUSEC_PG_CTRL_POS)
#define EFUSEC_PG_CTRL_DIS      (1<<EFUSEC_PG_CTRL_POS)
        /* 安全校验使能标志 */
#define EFUSEC_SEC_EN_POS       1
#define EFUSEC_SEC_EN_WIDTH     1
#define EFUSEC_SEC_EN_MASK      (((1<<EFUSEC_SEC_EN_WIDTH)-1)<<EFUSEC_SEC_EN_POS)
#define EFUSEC_SEC_EN           (1<<EFUSEC_SEC_EN_POS)
        /* JTAG访问控制 */
#define EFUSEC_JTAG_CTRL_POS     2
#define EFUSEC_JTAG_CTRL_WIDTH   1
#define EFUSEC_JTAG_CTRL_MASK    (((1<<EFUSEC_JTAG_CTRL_WIDTH)-1)<<EFUSEC_JTAG_CTRL_POS)
#define EFUSEC_JTAG_CTRL_EN      (0<<EFUSEC_JTAG_CTRL_POS)
        
#define EFUSE_MAX_SIZE  512     /* Efuse大小 */
#define EFUSE_HAD_WRITED 1      /*Efuse 已经烧写*/
#define EFUSE_NOT_WRITED 0      /*Efuse 没有烧写*/
        
#define EFUSE_GRP_CFG			(EFUSE_MAX_SIZE/4 - 1)
        
#define EFUSE_OP_TIMEOUT_TIME   0x100000    /* Efuse操作超时最大延时时间 */
        
        
#define EFUSEC_CFG_OFFSET              (EFUSE_BASE_REG+0x0)
#define EFUSEC_PG_EN_MASK       (1<<0)
#define EFUSEC_PRE_PG_MASK      (1<<1)
#define EFUSEC_RD_EN_MASK       (1<<2)
#define EFUSEC_SIG_SEL_MASK     (1<<3)
        
#define EFUSEC_STATUS_OFFSET           (EFUSE_BASE_REG+0x04)
#define EFUSEC_PG_STATUS        (1<<0)
#define EFUSEC_RD_STATUS        (1<<1)
#define EFUSEC_PRE_PG_FIN       (1<<2)
        
#define EFUSE_GROUP_OFFSET             (EFUSE_BASE_REG+0x08)
#define EFUSE_GP_MASK           ((1<<7)-1)
        
#define EFUSE_PG_VALUE_OFFSET          (EFUSE_BASE_REG+0x0C)
        
#define EFUSEC_COUNT_OFFSET            (EFUSE_BASE_REG+0x10)
#define EFUSE_COUNT_MASK        ((1<<8)-1)
        
#define EFUSEC_PGM_COUNT_OFFSET        (EFUSE_BASE_REG+0x14)
#define EFUSE_PGM_COUNT_MASK    ((1<<16)-1)
        
#define EFUSEC_DATA_OFFSET             (EFUSE_BASE_REG+0x18)
        
#define EFUSEC_HW_CFG_OFFSET           (EFUSE_BASE_REG+0x1C)
        /* 烧写控制 */
#define EFUSEC_PG_DIS           0x1
        
        /* 启动设备选择 */
#define EFUSEC_BOOTMODE_WIDTH   3
#define EFUSEC_BOOTMODE_POS     3
#define EFUSEC_BOOTMODE_MASK     (((1<<EFUSEC_BOOTMODE_WIDTH)-1)<<EFUSEC_BOOTMODE_POS)
        
#define EFUSE_SECURITY_ENABLE_BIT  	(1UL << 26)
        
#define EFUSE_OEM_SEL_BIT_START             (1024)
#define EFUSE_OEM_SEL_BIT_SIZE              (8)
#define EFUSE_CARRIER_ID_BIT_SIZE           (16)
#define EFUSE_HW_ID_BIT_SIZE                (16)
#define EFUSE_CARRIER_HW_BIT1_CNT_SIZE      (8)
        
        /* register control */
#define READ_REGISTER_ULONG(addr) readl(addr) //(*(volatile unsigned int *)(addr))
        
        
#define WRITE_REGISTER_ULONG(addr,val)  writel(val, addr) //(*(volatile unsigned int *)(addr) = (val))
        
#define INREG32(x)          READ_REGISTER_ULONG(x)
#define OUTREG32(x, y)      WRITE_REGISTER_ULONG((x), (unsigned int)(y))
#define SETREG32(x, y)      OUTREG32((x), INREG32(x)|(y))
#define CLRREG32(x, y)      OUTREG32((x), INREG32(x)&~(y))
#define SETBITVALUE32(addr, mask, value)  OUTREG32((addr), (INREG32(addr)&(~(mask))) | ((value)&(mask)))




/*****************************************************************************
  10 函数声明
*****************************************************************************/

int read_efuse(unsigned int group, unsigned int *buf, unsigned int len);

extern int get_temp_adjust_value(unsigned int * buffer);



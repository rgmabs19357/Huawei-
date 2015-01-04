#ifndef _HI_MCI_H_
#define _HI_MCI_H_

/*#include <linux/workqueue.h>*/
/*#include <linux/semaphore.h>*/
#define OSDRV_MODULE_VERSION_STRING   "NULL"

#define SD_FPGA_GPIO

extern int trace_level;

#define HIMCI_TRACE_LEVEL				5
#define HIMCI_TRACE_SIGNIFICANT			5
#define HIMCI_TRACE_GEN_INFO			4
#define HIMCI_TRACE_JUST_FOR_REVIEW		3
#define HIMCI_TRACE_GEN_API				2
#define HIMCI_TRACE_DEBUG_REG			1

#define SDMMC_3V3_IO_LDO7_285          (2850000)
#define SDMMC_3V3_IO_LDO22_1425        (1425000)

#define SDMMC_1V8_IO_LDO7_180          (1800000)
#define SDMMC_1V8_IO_LDO22_0           (0)

#define SDMMC_SDCARD_285                  (2850000)

#define HIMCI_TRACE_FMT					KERN_INFO

#define himci_trace(level, msg...) do { \
	if ((level) >= trace_level) { \
		printk(HIMCI_TRACE_FMT "[himci][%s]:", __func__); \
		printk(msg); \
		printk("\n");\
	} \
} while (0)

#define hi_host_trace(level, msg...) do { \
	if ((level) >= trace_level) { \
		printk(HIMCI_TRACE_FMT "[%s][%s]:", dev_name(hi_host->dev), __func__); \
		printk(msg); \
		printk("\n");\
	} \
} while (0)

#define himci_assert(cond) do { \
	if (!(cond)) { \
		printk(KERN_ERR "Assert:[himci][%s]:%d\n", \
				__func__, \
				__LINE__); \
		BUG(); \
	} \
} while (0)

#define himci_error(s...) do { \
	printk(KERN_ERR "[himci][%s]:", __func__); \
	printk(s); \
	printk("\n"); \
} while (0)

#define himci_readl(addr) ({ unsigned int reg = readl((unsigned int)(addr)); \
	himci_trace(HIMCI_TRACE_DEBUG_REG, "readl(0x%04X) = 0x%08X", \
										(unsigned int)(addr), reg); \
	reg; })

#define himci_writel(v, addr) do { writel(v, (unsigned int)(addr)); \
	himci_trace(HIMCI_TRACE_DEBUG_REG, "writel(0x%04X) = 0x%08X", \
							(unsigned int)(addr), (unsigned int)(v)); \
} while (0)

#define HI_MAX_REQ_SIZE     (128*1024)

/* maximum size of one mmc block */
#define MAX_BLK_SIZE        512

/* maximum number of bytes in one req */
#define MAX_REQ_SIZE        HI_MAX_REQ_SIZE

/* maximum number of blocks in one req */
#define MAX_BLK_COUNT       (HI_MAX_REQ_SIZE/512)

/* maximum number of segments, see blk_queue_max_phys_segments */
#define MAX_SEGS            (HI_MAX_REQ_SIZE/512)

/* maximum size of segments, see blk_queue_max_segment_size */
#define MAX_SEG_SIZE        HI_MAX_REQ_SIZE

/*  to do max input clock */
#ifdef CONFIG_MACH_HI6620SFT
#define MMC_CCLK_MAX        30000000    /* there is an issue, the real clock is 40M */
#define MMC_CCLK_MAX_30M    30000000   /*for low speed use*/
#endif

#ifdef CONFIG_MACH_HI6620OEM
#define MMC_CCLK_MAX_25M     25000000
#define MMC_CCLK_MAX_30M     30000000   /*for low speed use*/
#define MMC_CCLK_MAX_50M     50000000
#define MMC_CCLK_MAX_100M   100000000
#define MMC_CCLK_MAX_150M   150000000
#define MMC_CCLK_MAX_300M   300000000
#define MMC_CCLK_MAX        150000000
#endif



#define REG_SCPEREN4        0x66C
#define REG_SCPERDIS4       0x670
#define REG_SCPERSTAT4      0x674

#define BIT_SYS_MMC0_CLKEN   ( (0x1<<23) | (1<<18) | (1<<13) )

#define REG_SCCLKDIV2       0x108
#define REG_SCCLKDIV16      0x140

struct himci_host {
	struct mshci_host       *ms_host;
	struct device           *dev;
	struct platform_device  *pdev;
	struct clk              *pclk;				/* peripheral bus clock */
    struct clk              *clk_mmc_high;
	struct hisik3_mmc_platform_data *plat;
	struct iomux_block      *piomux_block;
	struct block_config     *pblock_config;
	struct regulator	    *vcc_ldo;
	struct regulator	    *vcc_lvs;
	struct regulator        *signal_vcc;
	struct notifier_block	nb;
	int						ocp_flag;
	unsigned char           old_power_mode;     /* record power mode */
	unsigned char           old_sig_voltage;
	unsigned char			old_timing;
	int 					allow_switch_signal_voltage;
#ifdef SD_FPGA_GPIO
	void __iomem            *gpioaddr;
#endif
	int                     *timing_config;
	int						suspend_timing_config;
	int                     *init_tuning_config;
	int						tuning_current_sample;		/* record current sample */
	int						tuning_init_sample;			/* record the inital sample */
	int						tuning_move_sample;			/* record the move sample */
	int						tuning_move_count;			/* record the move count */
	unsigned int			tuning_sample_flag;			/* record the sample OK or NOT */
};

#endif

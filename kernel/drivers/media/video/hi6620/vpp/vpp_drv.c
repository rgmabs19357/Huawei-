
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/interrupt.h>

#include <asm/irq.h>
#include <media/v4l2-common.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <mach/hisi_mem.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/delay.h>
#include <mach/clk_name_interface.h>
#include "drv_regulator_user.h"
#include "reg_ops.h"
#include "soc_baseaddr_interface.h"
#include "soc_sctrl_interface.h"
#include "soc_ao_sctrl_interface.h"

#include "vpp_drv.h"

#define LOG_TAG "VPP_DRV"
#include "vpp_log.h"

#ifdef	CONFIG_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/string.h>
#endif

/* module description */
MODULE_LICENSE("Proprietary");
MODULE_AUTHOR("j00140427");
MODULE_DESCRIPTION("vpp driver");

#define VPP_DEVICE_ID     19            //VPP IP设备号
//#define VPP_TEST
#ifdef __KERNEL__
#define VPP_CLOCK               CONFIG_VPP_CLK
#define VPP_WAIT_TIMEOUT_COEFF  CONFIG_VPP_WAIT_TIMEOUT_COEFF
#endif

#ifndef VPP_CLOCK
#define VPP_CLOCK               140000000
#endif

#ifndef VPP_WAIT_TIMEOUT_COEFF
#define VPP_WAIT_TIMEOUT_COEFF  1
#endif


/* dump SCCTRL/AO_SCCTRL/PMCTRL reg about vpp power on/off,
   rst en/dis, and clk en/dis, 2013/05/06 */
//#define DUMP_SCCTRL_VPP_REG

#ifdef CONFIG_DEBUG_FS
#define VPP_DEBUGFS_DIR_NAME        "mit2vpp"
#define VPP_DEBUGFS_PWDN_FILE_NAME  "pwdn"
#endif

#define	VPP_RSTLOOPTIMES  10            //软复位时循读寄存器次数

/* VPP相关时钟的结构体指针 */
typedef struct
{
    struct clk *s_src_clk;
    struct clk *s_x2x_clk;
    struct clk *s_p2p_clk;
    struct clk *s_vpp_clk;

    unsigned int    s_src_clk_enable      : 1;
    unsigned int    s_x2x_clk_enable      : 1;
    unsigned int    s_p2p_clk_enable      : 1;
    unsigned int    s_vpp_clk_enable      : 1;
    unsigned int    reserve               : 28;
} vpp_clk;

vpp_clk s_clk;
extern S_VPP_REGS_TYPE *pVoReg;

static struct video_device *s_vpp_device_p = NULL;
static struct video_device s_vpp_device;
static wait_queue_head_t s_wait_queue;
static bool s_interrupt_cond = false;
struct regulator *s_vpp_vdd = NULL;
static struct semaphore s_busy_lock;

//VPP主设备open次数
static unsigned int s_vpp_count = 0;

static u32 vpp_dbgfs_pwdncfg = 1;
static u32 vpp_pwdn_status = 0;


#ifdef DUMP_SCCTRL_VPP_REG
/***********************************************************************************
* Function:       dump_scctrl_vpp_reg
* Description:    dump SCCTRL/AO_SCCTRL/PMCTRL register about vpp power on/off,
                  rst en/dis and clk en/dis.
* Data Accessed:
* Data Updated:
* Input:		  NA
* Output:
* Return:		  0
* Others:
***********************************************************************************/
void dump_scctrl_vpp_reg(void)
{
    unsigned int reg_value;

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_MTCMOS_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_MTCMOS_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_RST_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_PW_RST_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_ISO_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_PW_ISO_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_ON_BASE_ADDR, SOC_AO_SCTRL_SC_PW_CLK_STAT0_ADDR(0), 0, 31);
    printk("%s, SOC_AO_SCTRL_SC_PW_CLK_STAT0 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_RSTSTAT7_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_RSTSTAT7 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_CLKSTAT12_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_CLKSTAT12 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_CLKSTAT10_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_CLKSTAT10 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_PERIPH_CLKSTAT8_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_PERIPH_CLKSTAT8 = 0x%0x,\n", __func__, reg_value);

    reg_value = phy_reg_readl(SOC_SC_OFF_BASE_ADDR, SOC_SCTRL_SC_CLKCFG8BIT8_ADDR(0), 0, 31);
    printk("%s, SOC_SCTRL_SC_CLKCFG8BIT8 = 0x%0x,\n", __func__, reg_value);
}
#endif

/* the func regist to irq */
static irqreturn_t vpp_isr ( int irq, void *dev_id )
{
    if (hal_get_int_sta(HAL_INTMSK_VTEINT))
    {
        logd("============== the irq is my care\n");
        s_interrupt_cond = true;
        wake_up_interruptible(&s_wait_queue);
        hal_clear_int_sta(HAL_INTMSK_VTEINT);
    }
    else
    {
        logd("============== the irq is not my care\n");
    }

    return IRQ_HANDLED;
}

/***********************************************************************************
* Function:       vpp_request_rst
* Description:    配置VPP IP请求复位
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         0
* Others:
***********************************************************************************/
int vpp_request_rst(void)
{
    U_VOUVERSION1        VOUVERSION1;
    U_VOUVERSION2        VOUVERSION2;
    int i = 0;

    logi("in vpp_request_rst\n");

    /* 配置寄存器为1，发出VPP软复位请求 */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_ADDR(CALC_REG_OFFSET),
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl1_vpp_srst_req_START,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl1_vpp_srst_req_END,
                   1);

    /* 轮循读寄存器为0 */
    for (i = 0; i < VPP_RSTLOOPTIMES; i++) {
        msleep(1);
        VOUVERSION1.u32 = reg_read(&(pVoReg->VOUVERSION1.u32));
        VOUVERSION2.u32 = reg_read(&(pVoReg->VOUVERSION2.u32));
        if ((0 == VOUVERSION1.bits.vouversion0) && (0 == VOUVERSION2.bits.vouversion1)) {
            break;
        }
    }

    if (i >= VPP_RSTLOOPTIMES) {
        loge("wait register time out. VOUVERSION1 = 0x%x\n, VOUVERSION2 = 0x%x\n", VOUVERSION1.bits.vouversion0, VOUVERSION2.bits.vouversion1);
        return -ETIME;
    }

    /* VPP完成复位，配置寄存器为0 */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_ADDR(CALC_REG_OFFSET),
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl1_vpp_srst_req_START,
                   SOC_SCTRL_SC_MEDIA_SUBSYS_CTRL3_media_subsys_ctrl1_vpp_srst_req_END,
                   0);

    /* 轮循读寄存器为非0 */
    for (i = 0; i < VPP_RSTLOOPTIMES; i++) {
        msleep(1);
        VOUVERSION1.u32 = reg_read(&(pVoReg->VOUVERSION1.u32));
        if (0 != VOUVERSION1.bits.vouversion0) {
            break;
        }
    }

    if (i >= VPP_RSTLOOPTIMES) {
        loge("wait register time out. VOUVERSION1 = 0x%x\n", VOUVERSION1.bits.vouversion0);
        return -ETIME;
    }

    return 0;
}

/***********************************************************************************
* Function:       vpp_force_rst
* Description:    配置VPP IP强制复位
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         NA
* Others:
***********************************************************************************/
void vpp_force_rst(void)
{
    logi("in vpp_force_rst\n");

    /* 配置寄存器为1，强制VPP复位 */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(CALC_REG_OFFSET),
                   SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_17vppw_START,
                   SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_17vppw_END,
                   1);
    msleep(1);

    /* VPP复位完成，配置寄存器为1 */
    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_PERIPH_RSTEN7_ADDR(CALC_REG_OFFSET),
                   SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_17vppw_START,
                   SOC_SCTRL_SC_PERIPH_RSTEN7_periph_rsten7_17vppw_END,
                   0);

    return;
}

/***********************************************************************************
* Function:       vpp_clk_rstdisable
* Description:    配置VPP工作时钟域解复位
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         NA
* Others:
***********************************************************************************/
void vpp_clk_rstdisable(void)
{
    logi("in vpp_clk_rstdisable\n");

    phy_reg_writel(SOC_SC_OFF_BASE_ADDR,
                   SOC_SCTRL_SC_PERIPH_RSTDIS7_ADDR(CALC_REG_OFFSET),
                   SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_17vppw_START,
                   SOC_SCTRL_SC_PERIPH_RSTDIS7_periph_rstdis7_17vppw_END,
                   1);
    return;
}

/***********************************************************************************
* Function:       vpp_clk_get
* Description:    配置VPP相关时钟获取
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         0
* Others:
***********************************************************************************/
int vpp_clk_get(void)
{
    logi("in vpp_clk_get\n");

    /* VPP分频前时钟门控的时钟获取 */
    s_clk.s_src_clk = clk_get(&s_vpp_device_p->dev, CLK_PERIPLL_VPP_GATED);
    if (IS_ERR(s_clk.s_src_clk)) {
        loge("get CLK_VPP_SRC clock failed. s_src_clk = %p\n", s_clk.s_src_clk);
        return -EIO;
    }

    /* VPP X2X桥时钟获取 */
    s_clk.s_x2x_clk = clk_get(&s_vpp_device_p->dev, CLK_X2X_VPP_BRG_S);
    if (IS_ERR(s_clk.s_x2x_clk)) {
        loge("get CLK_VPP_X2X clock failed. s_x2x_clk = %p\n", s_clk.s_x2x_clk);
        return -EIO;
    }

    /* CFGMAPB到VPP的P2P桥时钟获取 */
    s_clk.s_p2p_clk = clk_get(&s_vpp_device_p->dev, CLK_P2P_VPP_BRG_S);
    if (IS_ERR(s_clk.s_p2p_clk)) {
        loge("get CLK_VPP_P2P clock failed. s_p2p_clk = %p\n", s_clk.s_p2p_clk);
        return -EIO;
    }

    /* VPP系统工作时钟获取 */
    s_clk.s_vpp_clk = clk_get(&s_vpp_device_p->dev, CLK_2VPP_SLAVE_CLK);
    if (IS_ERR(s_clk.s_vpp_clk)) {
        loge("get CLK_VPP clock failed. s_vpp_clk = %p\n", s_clk.s_vpp_clk);
        return -EIO;
    }

    return 0;
}

/***********************************************************************************
* Function:       vpp_clk_enable
* Description:    配置VPP相关时钟使能
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         0
* Others:
***********************************************************************************/
int vpp_clk_enable(void)
{
    int ret = 0;

    logi("in vpp_clk_enable\n");

    if (NULL == s_clk.s_src_clk || NULL == s_clk.s_x2x_clk
        || NULL == s_clk.s_p2p_clk || NULL == s_clk.s_vpp_clk) {
        loge("the clk is null. s_src_clk = %p, s_x2x_clk = %p, s_p2p_clk= %p, s_vpp_clk = %p",
             s_clk.s_src_clk, s_clk.s_x2x_clk, s_clk.s_p2p_clk, s_clk.s_vpp_clk);
        return -EIO;
    }

    /* VPP分频前时钟门控的时钟使能 */
    ret = clk_enable(s_clk.s_src_clk);
    if (0 != ret) {
        loge("s_src_clk enable failed.\n");
        return -EIO;
    }
    s_clk.s_src_clk_enable = 1;

    /* VPP IP工作频率设置 */
    ret = clk_set_rate(s_clk.s_vpp_clk, VPP_CLOCK);
    if (0 != ret) {
        loge("clk_set_rate failed.\n");
        return -EIO;
    }

    /* VPP X2X桥时钟使能 */
    ret = clk_enable(s_clk.s_x2x_clk);
    if (0 != ret) {
        loge("s_x2x_clk enable failed.\n");
        vpp_clk_disable();
         return -EIO;
    }
    s_clk.s_x2x_clk_enable = 1;

    /* CFGMAPB到VPP的P2P桥时钟使能 */
    ret = clk_enable(s_clk.s_p2p_clk);
    if (0 != ret) {
        loge("s_p2p_clk enable failed.\n");
        vpp_clk_disable();
        return -EIO;
    }
    s_clk.s_p2p_clk_enable = 1;

    /* VPP系统工作时钟使能 */
    ret = clk_enable(s_clk.s_vpp_clk);
    if (0 != ret) {
        loge("s_vpp_clk enable failed.\n");
        vpp_clk_disable();
         return -EIO;
    }
    s_clk.s_vpp_clk_enable = 1;

    return 0;
}

/***********************************************************************************
* Function:       vpp_clk_disable
* Description:    配置VPP相关时钟禁止
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         NA
* Others:
***********************************************************************************/
void vpp_clk_disable(void)
{
    logi("in vpp_clk_disable\n");

    /* VPP系统工作时钟禁止 */
    if ((NULL != s_clk.s_vpp_clk) && (1 == s_clk.s_vpp_clk_enable)) {
        clk_disable(s_clk.s_vpp_clk);
        logi(" s_vpp_clk is disable\n");
        s_clk.s_vpp_clk_enable = 0;
    }

    /* VPP X2X桥时钟禁止 */
    if ((NULL != s_clk.s_x2x_clk) && (1 == s_clk.s_x2x_clk_enable)) {
        clk_disable(s_clk.s_x2x_clk);
        logi(" s_x2x_clk is disable\n");
        s_clk.s_x2x_clk_enable = 0;
    }

    /* CFGMAPB到VPP的P2P桥时钟禁止 */
    if ((NULL != s_clk.s_p2p_clk) && (1 == s_clk.s_p2p_clk_enable)) {
        clk_disable(s_clk.s_p2p_clk);
        logi(" s_p2p_clk is disable\n");
        s_clk.s_p2p_clk_enable = 0;
    }

    /* VPP分频前时钟门控的时钟禁止 */
    if ((NULL != s_clk.s_src_clk) && (1 == s_clk.s_src_clk_enable)) {
        clk_disable(s_clk.s_src_clk);
        logi(" s_src_clk is disable\n");
        s_clk.s_src_clk_enable = 0;
    }

    return;
}

/***********************************************************************************
* Function:       vpp_clk_put
* Description:    配置VPP相关时钟释放
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         NA
* Others:
***********************************************************************************/
void vpp_clk_put(void)
{
    logi("in vpp_clk_put\n");

    /* VPP系统工作时钟释放 */
    if (NULL != s_clk.s_vpp_clk) {
        clk_put(s_clk.s_vpp_clk);
        s_clk.s_vpp_clk = NULL;
    }

    /* VPP X2X桥时钟释放 */
    if (NULL != s_clk.s_x2x_clk) {
        clk_put(s_clk.s_x2x_clk);
        s_clk.s_x2x_clk = NULL;
    }

    /* CFGMAPB到VPP的P2P桥时钟释放 */
    if (NULL != s_clk.s_p2p_clk) {
        clk_put(s_clk.s_p2p_clk);
        s_clk.s_p2p_clk = NULL;
    }

    /* VPP分频前时钟门控的时钟释放 */
    if (NULL != s_clk.s_src_clk) {
        clk_put(s_clk.s_src_clk);
        s_clk.s_src_clk = NULL;
    }

    return;
}

/***********************************************************************************
* Function:       vpp_regulator_enable
* Description:    配置VPP掉电区上电
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         0
* Others:
***********************************************************************************/
int vpp_regulator_enable(void)
{
    int ret = 0;

    logi("in vpp_regulator_enable\n");

    /* VPP掉电区电源上电 */
    ret = regulator_enable(s_vpp_vdd);
    if (0 != ret) {
        loge("failed to enable VPP_VDD regulator.\n");
        return -EIO;
    }

    /* VPP掉电区解复位 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                   SOC_AO_SCTRL_SC_PW_RSTDIS0_ADDR(CALC_REG_OFFSET),
                   SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_9vpp_START,
                   SOC_AO_SCTRL_SC_PW_RSTDIS0_pw_rstdis0_9vpp_END,
                   1);

    /* VPP掉电区ISO禁止 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                   SOC_AO_SCTRL_SC_PW_ISODIS0_ADDR(CALC_REG_OFFSET),
                   SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_9vpp_START,
                   SOC_AO_SCTRL_SC_PW_ISODIS0_pw_isodis0_9vpp_END,
                   1);

    /* VPP掉电区时钟使能 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                   SOC_AO_SCTRL_SC_PW_CLKEN0_ADDR(CALC_REG_OFFSET),
                   SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_9vpp_START,
                   SOC_AO_SCTRL_SC_PW_CLKEN0_pw_clken0_9vpp_END,
                   1);

    return 0;
}

/***********************************************************************************
* Function:       vpp_regulator_disable
* Description:    配置VPP掉电区下电
* Data Accessed:
* Data Updated:
* Input:          NA
* Output:
* Return:         NA
* Others:
***********************************************************************************/
void vpp_regulator_disable(void)
{
    int rc = 1;

    logi("in vpp_regulator_disable\n");

    /* VPP掉电区时钟关闭 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                   SOC_AO_SCTRL_SC_PW_CLKDIS0_ADDR(CALC_REG_OFFSET),
                   SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_9vpp_START,
                   SOC_AO_SCTRL_SC_PW_CLKDIS0_pw_clkdis0_9vpp_END,
                   1);

    /* VPP掉电区ISO使能 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                   SOC_AO_SCTRL_SC_PW_ISOEN0_ADDR(CALC_REG_OFFSET),
                   SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_9vpp_START,
                   SOC_AO_SCTRL_SC_PW_ISOEN0_pw_isoen0_9vpp_END,
                   1);

    /* VPP掉电区复位 */
    phy_reg_writel(SOC_SC_ON_BASE_ADDR,
                   SOC_AO_SCTRL_SC_PW_RSTEN0_ADDR(CALC_REG_OFFSET),
                   SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_9vpp_START,
                   SOC_AO_SCTRL_SC_PW_RSTEN0_pw_rsten0_9vpp_END,
                   1);

    /* VPP掉电区电源关闭 */
    if (NULL !=  s_vpp_vdd) {
        rc = regulator_disable(s_vpp_vdd);
        if (rc)
    	{
  			printk(KERN_ERR "Regulator vpp disable failed rc=%d\n", rc);
  		}
    }

    return;
}

#ifdef CONFIG_DEBUG_FS
int __init vpp_dbgfs_init(void)
{
    struct dentry *vpp_debugfs_dir = NULL;

    printk("vpp_debugfs_init, vpp_dbgfs_pwdncfg = %d, vpp_pwdn_status = %d.\n", vpp_dbgfs_pwdncfg, vpp_pwdn_status);

    vpp_debugfs_dir = debugfs_create_dir(VPP_DEBUGFS_DIR_NAME, NULL);
    if (ERR_PTR(-ENODEV) == vpp_debugfs_dir) {
        printk("debugfs_create_dir create dir %s failed!\n", VPP_DEBUGFS_DIR_NAME);
        return -EINVAL;
    }

    debugfs_create_u32(VPP_DEBUGFS_PWDN_FILE_NAME, 0664, vpp_debugfs_dir, &vpp_dbgfs_pwdncfg);

    return 0;
}
late_initcall(vpp_dbgfs_init);
#endif

int __init vpp_init(void)
{
    int ret = 0;
    struct video_device *video_dev = NULL;
    memset(&s_clk, 0 ,sizeof(s_clk));

    logi("in vpp_init: vpp_phymem = 0x%x, camera_phymem = 0x%x, codec_phymem = 0x%x\n",
         hisi_reserved_vpp_phymem,
         hisi_reserved_camera_phymem,
         hisi_reserved_codec_phymem);

    sema_init(&s_busy_lock, 1);

    /* alloc memory for video device */
    video_dev = video_device_alloc();
    if (NULL == video_dev) {
        loge("alloc video device failed\n");
        ret =  -ENOMEM;
        goto err;
    }

    /* init v4l device */
    s_interrupt_cond = false;
    *video_dev = s_vpp_device;

    /* register vpp device */
    ret = video_register_device(video_dev, 0, VPP_DEVICE_ID);
    if (0 !=ret) {
        loge("video device register failed\n");
        ret = -EINVAL;
        goto err;
    }
    s_vpp_device_p = video_dev;

    /*init the wait queue*/
    init_waitqueue_head(&s_wait_queue);

    /*register a irq for vpp*/
    ret = request_irq(IRQ_VPP, vpp_isr, 0, "VPP", NULL);
    if (0 !=ret) {
        loge("fail to request irq, ret = 0x%x\n",ret);
        goto err;
    }

    s_vpp_vdd = regulator_get(NULL, VPP_VDD);
    if (IS_ERR(s_vpp_vdd)) {
        loge("%s: failed to get VPP_VDD regulator\n", __func__);
        ret =  PTR_ERR(s_vpp_vdd);
        s_vpp_vdd = NULL;
        goto err;
    }

    ret = vpp_clk_get();
    if (0 != ret) {
        loge("fail to get clk, ret = 0x%x\n", ret);
        goto err;
    }

    ret = vpp_regulator_enable();
    if (0 != ret) {
        loge("fail to enable regulator, ret = 0x%x\n", ret);
        goto err;
    }

    vpp_clk_rstdisable();

    ret = vpp_clk_enable();
    if (0 != ret) {
        loge("fail to enable clk, ret = 0x%x\n", ret);
        goto err;
    }

    vpp_pwdn_status = 1;

#ifdef DUMP_SCCTRL_VPP_REG
    dump_scctrl_vpp_reg();
#endif

    if (0 != vpp_dbgfs_pwdncfg) {
        vpp_clk_disable();
        vpp_regulator_disable();
        vpp_pwdn_status = 0;
    }

#ifdef DUMP_SCCTRL_VPP_REG
    dump_scctrl_vpp_reg();
#endif


    hal_init();

    return ret;

  err:
    loge("module not inserted\n");
    if (NULL != s_vpp_device_p) {
        video_unregister_device(video_dev);
        s_vpp_device_p = NULL;
    }

    if (NULL != video_dev) {
        kfree(video_dev);
        video_dev = NULL;
    }

    /* Balong power off */
    vpp_clk_disable();
    vpp_regulator_disable();
    vpp_pwdn_status = 0;
    vpp_clk_put();
    if (NULL != s_vpp_vdd) {
        regulator_put(s_vpp_vdd);
        s_vpp_vdd = NULL;
    }

    return ret;
}

void __exit vpp_deinit(void)
{
    logi("in vpp_deinit\n");

    hal_deinit();

    if (NULL != s_vpp_device_p) {
        video_unregister_device(s_vpp_device_p);
        kfree(s_vpp_device_p);
        s_vpp_device_p = NULL;
    }

    free_irq(IRQ_VPP, 0);

    return;
}

static int vpp_open(struct file *file)
{
    int ret = -EFAULT;

    ret = down_interruptible(&s_busy_lock);
    if (0 != ret) {
        loge("down_interruptible fail, ret = %d\n", ret);
        ret = -EINTR;
    }

    logi("in vpp_open: vpp_phymem = 0x%x, camera_phymem = 0x%x, codec_phymem = 0x%x\n",
         hisi_reserved_vpp_phymem,
         hisi_reserved_camera_phymem,
         hisi_reserved_codec_phymem);

    if (s_vpp_count > 0) {
        logi("don't need to open device, the open count is %d\n", s_vpp_count);
        s_vpp_count++;
        up(&s_busy_lock);
        return 0;
    }

    if (0 == vpp_pwdn_status) {
        ret = vpp_regulator_enable();
        if (0 != ret) {
            loge("fail to enable regulator, ret = %d\n", ret);
            up(&s_busy_lock);
            return -EIO;
        }

        ret = vpp_clk_enable();
        if (0 != ret) {
            loge("fail to enable clk, ret = %d\n", ret);
            vpp_regulator_disable();
            up(&s_busy_lock);
            return -EIO;
        }

        vpp_pwdn_status = 1;
    }
    printk(KERN_INFO "vpp_open: vpp debugfs pwdn config = %d, vpp pwdn status = %d\n", vpp_dbgfs_pwdncfg, vpp_pwdn_status);

#ifdef DUMP_SCCTRL_VPP_REG
    dump_scctrl_vpp_reg();
#endif

    ret = inter_init();
    if (K3_SUCCESS != ret) {
        loge("vpp init failed ret = %d\n", ret);

        if (0 != vpp_dbgfs_pwdncfg) {
            vpp_clk_disable();
            vpp_regulator_disable();
            vpp_pwdn_status = 0;
        }
        printk(KERN_INFO "vpp_open: vpp_dbgfs_pwdncfg = %d, vpp_pwdn_status = %d\n", vpp_dbgfs_pwdncfg, vpp_pwdn_status);

        up(&s_busy_lock);
        return -EFAULT;
    }

    inter_open(HAL_LAYER_VIDEO1);
    hal_set_int_enable(HAL_INTMSK_VTEINT);

    s_vpp_count++;
    up(&s_busy_lock);

    return 0;
}

static int vpp_close(struct file *file)
{
    int ret = -EFAULT;

    ret = down_interruptible(&s_busy_lock);
    if (0 != ret) {
        loge("down_interruptible fail, ret = %d\n", ret);
        ret = -EINTR;
    }

    logi("in vpp_close\n");

    s_vpp_count--;
    logi("in vpp_close s_vpp_count = %d\n",s_vpp_count);
    if (s_vpp_count > 0)//TODO: < 0, 试一下
    {
        logi("don't need to close device, the open count is %d\n", s_vpp_count);
        up(&s_busy_lock);
        return 0;
    }

    inter_close(HAL_LAYER_VIDEO1);
    inter_deinit();

    if (0 != vpp_dbgfs_pwdncfg) {
        vpp_clk_disable();
        vpp_regulator_disable();
        vpp_pwdn_status = 0;
    }
    printk(KERN_INFO "vpp_close: vpp debugfs pwdn config = %d, vpp pwdn status = %d\n", vpp_dbgfs_pwdncfg, vpp_pwdn_status);

#ifdef DUMP_SCCTRL_VPP_REG
    dump_scctrl_vpp_reg();
#endif

    up(&s_busy_lock);

    return 0;
}

static long vpp_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    U_VOINTSTA 		VOINTSTA;

	int err = 0;

    logi("in vpp_ioctl\n");
    /*
     * extract the type and number bitfields, and don't decode
     * wrong cmds: return ENOTTY (inappropriate ioctl) before access_ok()
     */
    if(_IOC_TYPE(cmd) != VPP_IOC_MAGIC)
    {
        loge("vpp magic is wrong\n");
        return -ENOTTY;
    }

    if(_IOC_NR(cmd) > VPP_IOC_MAXNR)
    {
        loge("vpp NR is wrong\n");
        return -ENOTTY;
    }

    if(_IOC_DIR(cmd) & _IOC_READ)
    {
        err = !access_ok(VERIFY_WRITE, (void *) arg, _IOC_SIZE(cmd));
    }
    else if(_IOC_DIR(cmd) & _IOC_WRITE)
    {
        err = !access_ok(VERIFY_READ, (void *) arg, _IOC_SIZE(cmd));
    }

    if(err)
    {
        loge("vpp err: %d\n",err);
        return -EFAULT;
    }

    switch (cmd)
    {
        case VPP_STARTCONFIG:
        {
            VPP_CONFIG_S vpp_config;

            logi("VPP_STARTCONFIG\n");

            err = __copy_from_user(&vpp_config, (const void *) arg, sizeof(VPP_CONFIG_S));
            if (err)
            {
                loge("__copy_from_user failed\n");
                err =  -EFAULT;
                break;
            }

            s_interrupt_cond = false;

            err = inter_start(&vpp_config);
            if (K3_SUCCESS == err)
            {
                //fixme:time

                int ret = wait_event_interruptible_timeout(s_wait_queue, s_interrupt_cond, VPP_WAIT_TIMEOUT_COEFF * HZ);


                s_interrupt_cond = false;
                if (ret > 0)
                {
                    err = 0;
                    logi("wait event success\n");
                }
                else
                {

                    /* read interrupt status */
                    VOINTSTA.u32 = 0;
                    VOINTSTA.u32 = reg_read(&(pVoReg->VOINTSTA.u32));
                    logw("be_int = 0x%x\n, vhddr_int = 0x%x\n, vte_int = 0x%x\n,", VOINTSTA.bits.be_int,
                         VOINTSTA.bits.vhdrr_int, VOINTSTA.bits.vte_int);
                    loge("wait event time out\n");

                    /* 软复位 */
                    err = vpp_request_rst();
                    loge("vpp_request_rst %s !!\n", (0 == err)?"succ":"fail");


                    err = -ETIME;
                }
            }
            else
            {
                err = -EFAULT;
                loge("set vpp config failed\n");
            }

            break;
        }

        /* just for test */
        case VPP_GETBUSADDR:
        {
            VPP_BUSADDR_S stBussAddr;

            stBussAddr.vppBusAddr       = hisi_reserved_vpp_phymem;
            stBussAddr.codecBusAddr     = hisi_reserved_codec_phymem;
            stBussAddr.cameraBusAddr    = hisi_reserved_camera_phymem;

            if (__copy_to_user((void *)arg, &stBussAddr, sizeof(stBussAddr)))
            {
                printk(KERN_ERR "%s(%d):ioctl error\n", __FUNCTION__, __LINE__);
                return -EFAULT;
            }

            break;
        }

        default:
        {
            loge("unsurport cmd cmd = %d\n",cmd);
            err = -ENOIOCTLCMD;
            break;
        }
    }

    return err;
}

//only for test
#ifdef VPP_TEST
static int vpp_mmap(struct file *file, struct vm_area_struct *vma)
{
    unsigned long start = 0;
    unsigned long size = 0;

    logi();

    if (NULL == vma)
    {
        loge("can not get vm_area_struct!");
        return -EBADF;
    }

    start = vma->vm_start;
    size = vma->vm_end - vma->vm_start;

    /* make buffers write-thru cacheable */
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot); //update to 2.6.32
    if (remap_pfn_range(vma, start, vma->vm_pgoff, size, vma->vm_page_prot))
    {
        loge("remap_pfn_range error!");
        return -ENOBUFS;
    }

    return 0;
}
#endif

static void vpp_release( struct video_device *vdev )
{
    logi("in vpp_release\n");

    vpp_clk_put();
    if (NULL != s_vpp_vdd) {
        regulator_put(s_vpp_vdd);
        s_vpp_vdd = NULL;
    }

    return;
}

/* VFS methods */
static struct v4l2_file_operations s_vpp_fops = {
  .owner = THIS_MODULE,
  .open =  vpp_open,
  .release = vpp_close,
#ifdef VPP_TEST
  .mmap = vpp_mmap,
#endif
  .ioctl= vpp_ioctl,
};

static struct video_device s_vpp_device = {
    .name      = "VPP",
    .fops      = &s_vpp_fops,
    .ioctl_ops = NULL,
    .release   = vpp_release,
};

module_init(vpp_init);
module_exit(vpp_deinit);
MODULE_LICENSE("GPL");


/*
* hi6401.c   --  HI6401 ALSA Soc codec driver
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/clk.h>
#include <linux/timer.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/tlv.h>
#include <asm/io.h>
#include <linux/spinlock.h>
#include <linux/switch.h>
#include <linux/wakelock.h>
#include <linux/moduleparam.h>
#include <linux/semaphore.h>

#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>

#include <linux/hkadc/hisi_adc_hal.h>
#include <linux/hkadc/hisi_adc_linux.h>

#include <linux/debugfs.h>

#include <mach/clk_name_interface.h>  
#include "soc_smart_interface.h"

/*add for codec irq*/
#include <linux/gpio.h>
/*  Reason: For hook  */
#include <sound/jack.h>
/*KEY_MEDIA defined in linux/input.h*/
#include <linux/input/matrix_keypad.h>
#include <linux/irq.h>
#include <sound/hi6421_common.h>
#include <linux/interrupt.h>
#include <linux/irqnr.h>
#include <linux/mux.h>
#include <mach/pmussi_drv.h>
#include <reg_ops.h>
#include <mach/pmussi_drv.h>
#include "drv_pmic_if.h"
#define LOG_TAG "hi6401"
#include "hi6401.h"
#include "drv_ipcm.h"
#include <hsad/config_mgr.h>

#define HI6401_PB_MIN_CHANNELS ( 2 )
#define HI6401_PB_MAX_CHANNELS ( 2 )
#define HI6401_CP_MIN_CHANNELS ( 2 )
#define HI6401_CP_MAX_CHANNELS ( 2 )
#define HI6401_FORMATS     ( SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)
#define HI6401_RATES       ( SNDRV_PCM_RATE_8000  | SNDRV_PCM_RATE_16000 |\
                             SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 )


/* saradc sample retry times
booted times keeps about 5 seconds(100 times), half eco time(10 seconds) */
#define HI6401_SARADC_BOOTING_RETRIES       ( 5 )
#define HI6401_SARADC_BOOTED_RETRIES        ( 100 )

#define HI6401_PLUGIN_ECO_DELAY             ( 900 )
#define HI6401_PLUGIN_DELAY                 ( HI6401_PLUGIN_ECO_DELAY + 100 )

/* HI6401 CODEC CLOCK */
/*static struct clk *g_codec_clk = NULL;*/

/* HI6401 CODEC */
static struct snd_soc_codec *g_codec = NULL;

/* HI6401 VERSION*/
static unsigned int g_codec_version = 0;
/* HI6401 REGISTER BASE ADDR */
static unsigned int g_hi6401_reg_base_addr = -1;

/*vmic bias*/
#define SAR_REF  2800
#define __DRV_DUMP__

static spinlock_t ssi_hardware_spinlock_t;
static unsigned long flags = 0;

enum hi6401_jack_states {
    HI6401_JACK_BIT_NONE           = 0, /* unpluged */
    HI6401_JACK_BIT_HEADSET        = 1, /* pluged with mic */
    HI6401_JACK_BIT_HEADSET_NO_MIC = 2, /* pluged without mic */
    HI6401_JACK_BIT_HEADPHONE      = 3, /* pluged with 3 pole */
    HI6401_JACK_BIT_INVALID        = 4, /* index */
};

struct headset_voltage {/*mV*/
    int hs_3_pole_max_voltage;
    int hs_4_pole_min_voltage;
    int hs_4_pole_max_voltage;

    int hs_eco_voltage;
};
struct btn_voltage{/*mV*/
    int key_up_min_value;
    int key_up_max_value;
    int key_play_min_value;
    int key_play_max_value;
    int key_back_min_value;
    int key_back_max_value;
    int key_forward_min_value;
    int key_forward_max_value;
};

struct hi6401_jack_data{
    struct snd_soc_jack *jack;
    int report;
    struct switch_dev sdev;
};

/* codec private data */

struct hi6401_priv{
    struct snd_soc_codec *codec;
    struct hi6401_jack_data *hs_jack;
    enum hi6401_jack_states  hs_status;
    enum hi6401_jack_states  old_hs_status;
    int  pole_flag;
    int work_mode;
    #define quick_mode      (2)
    #define eco_mode        (1)
    #define normal_mode     (0)
    bool is_power_on;
    int  saradc_value;
    /* sample retry times */
    int  saradc_retries;
    struct wake_lock wake_lock;
    struct clk *codec_clk;
    struct regulator *regulator_avdd_1v8;
    struct regulator *regulator_dvdd_1v8;
    struct regulator *regulator_avdd_3v15;
    struct workqueue_struct *hs_wq;
    struct work_struct hs_work;
    struct delayed_work  low_power_work;
    spinlock_t lock;
    struct mutex io_mutex;
    struct semaphore state_sema;
    void (*set_reg_bits)(unsigned int reg,unsigned int value);
    void (*clr_reg_bits)(unsigned int reg,unsigned int value);
    void (*__set_reg_bits)(unsigned int reg,unsigned int value);
    void (*__clr_reg_bits)(unsigned int reg,unsigned int value);
    struct iomux_block      *piomux_block;
	struct block_config     *pblock_config;
	struct timer_list        timer;
    struct workqueue_struct *recover_wq;
    struct delayed_work      pll_recover_work;
    struct delayed_work      pdstat_recover_work;
    bool    clock_type;
    #define  TCXO_CLOCK     (1)
    #define  SSI_CLOCK      (0)

    struct headset_voltage *headset_voltage;
    struct btn_voltage *btn_voltage;
};


#define HI6401_HS_INIT_STATUS   (   0  )
#define HI6401_HS_DETECTING     ( 1<<2 )
#define HI6401_HS_WITH_MIC      ( 1<<0 )
#define HI6401_HS_WITHOUT_MIC   ( 1<<1 )

#define IRQ_OVER_TEMP           ( 0x1<<7 )
#define IRQ_SARADC_READ         ( 0x1<<6 )
#define IRQ_PLUG_IN             ( 0x1<<4 )
#define IRQ_PLUG_OUT            ( 0x1<<5 )
#define IRQ_ECO_BTN_DOWN        ( 0x1<<2 )
#define IRQ_ECO_BTN_UP          ( 0x1<<3 )
#define IRQ_BTN_DOWN            ( 0x1<<0 )
#define IRQ_BTN_UP              ( 0x1<<1 )
#define IRQ_PLUG_OUT_STATUS     ( 0x1<<2 )

#define ECO_MODE_ENTRY_TIME_SEC         (15)

static int hi6401_ibias_enabled = 0;

static void hi6401_enter_eco_mode(struct work_struct *work);
static int hi6401_exit_eco_mode(struct snd_soc_codec *codec);
static int  hs_plug_out_detect_func(struct snd_soc_codec *codec);

static inline void hi6401_select_reg_page(unsigned int reg)
{
    if (0 == (reg & BASE_ADDR_PAGE_1)) {
        /* select page 0 */
        writel(0, g_hi6401_reg_base_addr + (PAGE_SELECT_REG << 2));
    }
    else {
        /* select page 1 */
        writel(1, g_hi6401_reg_base_addr + (PAGE_SELECT_REG << 2));
    }
    udelay(1);
}

void ssi_codec_hardware_spinlock(void)
{
    volatile SOC_AO_SCTRL_SC_SYS_STAT0_UNION *sc_sys_stat0 = NULL;
    volatile SOC_AO_SCTRL_SC_SYS_CTRL1_UNION *sc_sys_ctrl1 = \
        (volatile SOC_AO_SCTRL_SC_SYS_CTRL1_UNION *)AOSCTRL_SC_SYS_CTRL1;

    /*SC_MCU_VOTE1EN0
     0~7    MCU
     8~15   ACPU
     16~23  CCPU
     24~31  DVFS
    */
    /*vote1*/

    while(1)
    {


        spin_lock_irqsave(&ssi_hardware_spinlock_t, flags);

        sc_sys_ctrl1->value = (1<<SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_msk_START)\
                             |(1<<SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_START);

        sc_sys_stat0 = (volatile SOC_AO_SCTRL_SC_SYS_STAT0_UNION *)AOSCTRL_SC_SYS_STAT0;
        if(1 == sc_sys_stat0->reg.vote1_semphsta)
        {
           return ;/*get vote*/
        }
        else
        {
            sc_sys_ctrl1->value = (1<<SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_msk_START)\
                                 |(0<<SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_START);

            spin_unlock_irqrestore(&ssi_hardware_spinlock_t, flags);
             udelay(1);

        }

    }
}

void ssi_codec_hardware_unspinlock(void)
{
    volatile SOC_AO_SCTRL_SC_SYS_CTRL1_UNION *sc_sys_ctrl1 = \
        (volatile SOC_AO_SCTRL_SC_SYS_CTRL1_UNION *)AOSCTRL_SC_SYS_CTRL1;

    udelay(2);
    sc_sys_ctrl1->value = (1<<SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_msk_START)\
                           |(0<<SOC_AO_SCTRL_SC_SYS_CTRL1_vote1_reg_semphen_req_START);

    spin_unlock_irqrestore(&ssi_hardware_spinlock_t, flags);
}


static unsigned int __hi6401_reg_read(struct snd_soc_codec *codec,unsigned int reg)
{
    volatile unsigned int ret = 0;
    unsigned long flags = 0;
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv ) {
        printk(KERN_ERR "%s: get drvdata failed !\n", __func__);
        return (unsigned int)(-1);
    }

    if(PMU_VERSION_SSI_BUG < pmu_get_version())
    {
       spin_lock_irqsave(&priv->lock, flags);
    }
    else
    {
        ssi_codec_hardware_spinlock();
    }

    /* read reg */
    hi6401_select_reg_page(reg);
    ret = readl(g_hi6401_reg_base_addr + ((reg & PAGE_OFFSET_MASK) << 2));

    if(PMU_VERSION_SSI_BUG < pmu_get_version())
    {
       spin_unlock_irqrestore(&priv->lock, flags);
       udelay(1);
    }
    else
    {
        ssi_codec_hardware_unspinlock();
    }


    return ret;
}

static void __hi6401_reg_write(struct snd_soc_codec *codec,unsigned int reg,
                               unsigned int value)
{
    unsigned long flags = 0;
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv) {
        printk(KERN_ERR "%s: get drvdata failed !\n", __func__);
        return;
    }

    if(PMU_VERSION_SSI_BUG < pmu_get_version())
    {
       spin_lock_irqsave(&priv->lock, flags);
    }
    else
    {
        ssi_codec_hardware_spinlock();
    }

    /* write reg */
    hi6401_select_reg_page(reg);
    writel(value, g_hi6401_reg_base_addr + ((reg & PAGE_OFFSET_MASK) << 2));

    if(PMU_VERSION_SSI_BUG < pmu_get_version())
    {
       spin_unlock_irqrestore(&priv->lock, flags);
       udelay(1);
    }
    else
    {
        ssi_codec_hardware_unspinlock();
    }

}

static void  hi6401_power_up(struct snd_soc_codec *codec,struct hi6401_priv *priv)
{
    int ret = 0;

    del_timer_sync(&priv->timer);
    cancel_delayed_work_sync(&priv->low_power_work);
    down(&priv->state_sema);
    if (eco_mode != priv->work_mode) {
        logi("already no-eco mode \n");
        goto out;
    }

    if (!priv->is_power_on){

        ret = regulator_enable(priv->regulator_avdd_1v8);
        if (ret != 0)
        {
            printk(KERN_ERR "regulator_enable fail\n");
            up(&priv->state_sema);
            return;
        }
        msleep(10); /* regulator stable time */
        clk_enable(priv->codec_clk);
        logi("regulator enable \n");

        priv->is_power_on = true;
    }

    __hi6401_reg_write(codec,HI6401_IBIAS_PD_REG,0x39);

    msleep(30); /* ibias stable time */

    __hi6401_reg_write(codec,HI6401_IBIAS_PD_REG,0x19);

    priv->work_mode = quick_mode;
out:
    up(&priv->state_sema);    
    mod_timer(&priv->timer,jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);
}

static inline unsigned int hi6401_reg_read(struct snd_soc_codec *codec,
                                           unsigned int reg)
{
    volatile unsigned int ret = 0;

    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv) {
        printk(KERN_ERR "%s: get drvdata failed !\n", __func__);
        return (unsigned int)(-1);
    }

    if (eco_mode == priv->work_mode){
        hi6401_power_up(codec,priv);
    }

    ret = __hi6401_reg_read(codec,reg);

    return ret;
}

static inline int hi6401_reg_write(struct snd_soc_codec *codec,
                                   unsigned int reg,
                                   unsigned int value)
{
    int ret = 0;
#ifdef CONFIG_FACTORY_MODE
    unsigned int regval = 0;
#endif

    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv) {
        printk(KERN_ERR "%s: get drvdata failed !\n", __func__);
        return -1;
    }

    if (eco_mode == priv->work_mode){
        hi6401_power_up(codec,priv);
    }
/*
 * Add in factory mode for select chip
 */
#ifdef CONFIG_FACTORY_MODE
    if ( HI6401_MAINPGA_REG == reg )
    {
       /*
        * main mic mute close zc first
        */
        if (value & 0x01 << HI6401_MAINPGA_MUTE_BIT) 
        {
            regval = __hi6401_reg_read(codec, HI6401_ZC_EN) & ~(0x01 << HI6401_MAINPGA_ZCD_EN_BIT);
            __hi6401_reg_write(codec, HI6401_ZC_EN, regval);
        }
        /*
         *  when unmute open zc first then mute then unmute
         */
        else   
        {
            regval = __hi6401_reg_read(codec, HI6401_ZC_EN) | (0x01 << HI6401_MAINPGA_ZCD_EN_BIT);
            __hi6401_reg_write(codec, HI6401_ZC_EN, regval);
            regval = __hi6401_reg_read(codec, HI6401_MAINPGA_REG) | (0x01 << HI6401_MAINPGA_MUTE_BIT);
            __hi6401_reg_write(codec, HI6401_MAINPGA_REG, regval);
        }
    }
    /*
     * submic: the same as main mic sequence
     */
    else if ( HI6401_AUXPGA_REG == reg )  
    {
        if (value & 0x01 << HI6401_AUXPGA_MUTE_BIT)
        {
            regval = __hi6401_reg_read(codec, HI6401_ZC_EN) & ~(0x01 << HI6401_AUXPGA_ZCD_EN_BIT);
            __hi6401_reg_write(codec, HI6401_ZC_EN, regval);
        }
        else
        {
            regval = __hi6401_reg_read(codec, HI6401_ZC_EN) | (0x01 << HI6401_AUXPGA_ZCD_EN_BIT);
            __hi6401_reg_write(codec, HI6401_ZC_EN, regval);
            regval = __hi6401_reg_read(codec, HI6401_AUXPGA_REG) | (0x01 << HI6401_AUXPGA_MUTE_BIT);
            __hi6401_reg_write(codec, HI6401_AUXPGA_REG, regval);
        }
    }
#endif

    __hi6401_reg_write(codec,reg,value);

    return ret;
}

static void hi6401_set_reg_bits(unsigned int reg, unsigned int value)
{
    unsigned int val = 0;

    struct hi6401_data *priv = snd_soc_codec_get_drvdata(g_codec);
    if (priv) {
        /*spin_lock_irqsave (&priv->lock, flags);*/
        val = hi6401_reg_read(g_codec, reg) | (value);
        hi6401_reg_write(g_codec, reg, val);
        /*spin_unlock_irqrestore (&priv->lock, flags);*/
    }
    else
    {
        printk(KERN_ERR "priv is null pointer\n");
    }
}

void hi6401_clr_reg_bits(unsigned int reg, unsigned int value)
{
    unsigned int val = 0;

    struct hi6401_data *priv = snd_soc_codec_get_drvdata(g_codec);
    if (priv) {
        /*spin_lock_irqsave (&priv->lock, flags);*/
        val = hi6401_reg_read(g_codec, reg) & ~(value);
        hi6401_reg_write(g_codec, reg, val);
        /*spin_unlock_irqrestore (&priv->lock, flags);*/
    }
    else
    {
        printk(KERN_ERR "priv is null pointer\n");
    }
}

static void __hi6401_set_reg_bits(unsigned int reg, unsigned int value)
{
    unsigned int val = 0;

    struct hi6401_data *priv = snd_soc_codec_get_drvdata(g_codec);
    if (priv) {
        /*spin_lock_irqsave (&priv->lock, flags);*/
        val = __hi6401_reg_read(g_codec, reg) | (value);
        __hi6401_reg_write(g_codec, reg, val);
        /*spin_unlock_irqrestore (&priv->lock, flags);*/
    }
    else
    {
        printk(KERN_ERR "priv is null pointer\n");
    }
}

void __hi6401_clr_reg_bits(unsigned int reg, unsigned int value)
{
    unsigned int val = 0;

    struct hi6401_data *priv = snd_soc_codec_get_drvdata(g_codec);
    if (priv) {
        /*spin_lock_irqsave (&priv->lock, flags);*/
        val = __hi6401_reg_read(g_codec, reg) & ~(value);
        __hi6401_reg_write(g_codec, reg, val);
        /*spin_unlock_irqrestore (&priv->lock, flags);*/
    }
    else
    {
        printk(KERN_ERR "priv is null pointer\n");
    }
}
/* provide to tools use only */
unsigned int codec_reg_read(unsigned int reg)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    int ret = 0;
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return (unsigned int)(-1);
    }
    if ( eco_mode == priv->work_mode ){
        ret = hi6401_exit_eco_mode(g_codec);
    }

    /* working then delay entering eco mode */
    mod_timer(&priv->timer,jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);

    return hi6401_reg_read(g_codec, reg);
}

/* provide to tools use only */
void codec_reg_write(unsigned int reg, unsigned int value)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    int ret = 0;
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return;
    }
    if ( eco_mode == priv->work_mode ){
        ret = hi6401_exit_eco_mode(g_codec);
    }

    hi6401_reg_write(g_codec, reg, value);

    /* working then delay entering eco mode */
    mod_timer(&priv->timer,jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);
}

static int codec_version_check(void)
{
    int ret = SSI_DEVICE_ERR;
    unsigned int regval = 0;

    regval = hi6401_reg_read(g_codec ,HI6401_VERSION);
    if((regval >= CODEC_VER_START) && (regval <= CODEC_VER_END))
    {
        ret = SSI_DEVICE_OK;
    }

    return ret;
}

/* VOLUME CONTROLS */
/*
* MAIN MIC GAIN volume control:
* from 0 to 22 dB in 2 dB steps
* MAX VALUE is 11
*/
static DECLARE_TLV_DB_SCALE(main_mic_tlv, 0, 200, 0);

/*
* SUB MIC GAIN volume control:
* from 0 to 22 dB in 2 dB steps
* MAX VALUE is 11
*/
static DECLARE_TLV_DB_SCALE(sub_mic_tlv, 0, 200, 0);

/*
* SIDE MIC GAIN volume control:
* from -30 to 16 dB in 2 dB steps
* MAX VALUE is 23
*/
static DECLARE_TLV_DB_SCALE(side_mic_tlv, -3000, 200, 0);

/*
* LINEIN GAIN volume control:
* from -30 to 16 dB in 2 dB steps
* MAX VALUE is 23
*/
static DECLARE_TLV_DB_SCALE(linein_tlv, -3000, 200, 0);

/*
* LINEOUT GAIN volume control:
* from -42 to 6 dB in 1.5 dB steps
* MAX VALUE is 32
*/
static DECLARE_TLV_DB_SCALE(lineout_tlv, -4200, 150, 0);

/*
* EARPIECE GAIN volume control:
* from -42 to 6 dB in 1.5 dB steps
* MAX VALUE is 32
*/
static DECLARE_TLV_DB_SCALE(earpiece_tlv, -4200, 150, 0);

/*
* HEADSET GAIN volume control:
* from -42 to 6 dB in 1.5 dB steps
* MAX VALUE is 32
*/
static DECLARE_TLV_DB_SCALE(headset_tlv, -4200, 150, 0);

/* SOUND KCONTROLS */
static const struct snd_kcontrol_new hi6401_snd_controls[] = {
    /* VOLUME */
        /*DBGAIN INT*/
    SOC_SINGLE("HI6401_S1_IL_GAIN_INT",
               HI6401_S1_IL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S1_IR_GAIN_INT",
               HI6401_S1_IR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S2_IL_GAIN_INT",
               HI6401_S2_IL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S2_IR_GAIN_INT",
               HI6401_S2_IR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S2_OL_GAIN_INT",
               HI6401_S2_OL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S2_OR_GAIN_INT",
               HI6401_S2_OR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S3_I_GAIN_INT",
               HI6401_S3_I_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S3_OL_GAIN_INT",
               HI6401_S3_OL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S3_OR_GAIN_INT",
               HI6401_S3_OR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S4_I_GAIN_INT",
               HI6401_S4_I_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S4_OL_GAIN_INT",
               HI6401_S4_OL_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_S4_OR_GAIN_INT",
               HI6401_S4_OR_GAIN_INT_REG, HI6401_DBGAIN_INT_BIT, 0xFF, 0),

    SOC_SINGLE_TLV("MAINMIC PGA VOLUME",
            HI6401_MAINPGA_REG, HI6401_MAINPGA_GAIN_BIT,
            11, /* MAX VALUE(11) SEE IN MAIN MIC GAIN NOTE */
            0, main_mic_tlv),
    SOC_SINGLE_TLV("SUBMIC PGA VOLUME",
            HI6401_AUXPGA_REG, HI6401_AUXPGA_GAIN_BIT,
            11, /* MAX VALUE(11) SEE IN SUB MIC GAIN NOTE */
            0, sub_mic_tlv),
    SOC_SINGLE_TLV("SIDETONE PGA VOLUME",
            HI6401_SIDEPGA_REG, HI6401_SIDEPGA_GAIN_BIT,
            23, /* MAX VALUE(23) SEE IN SIDE MIC GAIN NOTE */
            0, side_mic_tlv),
    SOC_SINGLE_TLV("EARPIECE PGA VOLUME",
            HI6401_EARPGA_REG, HI6401_EARPGA_GAIN_BIT,
            32, /* MAX VALUE(32) SEE IN EARPIECE GAIN NOTE */
            0, earpiece_tlv),

    SOC_SINGLE_TLV("LINEINL PGA VOLUME",
            HI6401_LINEINLPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
            23, /* MAX VALUE(23) SEE IN LINEIN GAIN NOTE */
            0, linein_tlv),
    SOC_SINGLE_TLV("LINEINR PGA VOLUME",
            HI6401_LINEINRPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
            23, /* MAX VALUE(23) SEE IN LINEIN GAIN NOTE */
            0, linein_tlv),
    SOC_SINGLE_TLV("LINEOUTL PGA VOLUME",
            HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
            32, /* MAX VALUE(32) SEE IN LINEOUT GAIN NOTE */
            0, lineout_tlv),
    SOC_SINGLE_TLV("LINEOUTR PGA VOLUME",
            HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_GAIN_BIT,
            32, /* MAX VALUE(32) SEE IN LINEOUT GAIN NOTE */
            0, lineout_tlv),
    SOC_SINGLE_TLV("HEADSETL PGA VOLUME",
            HI6401_HSLPGA_REG, HI6401_HSPGA_GAIN_BIT,
            32, /* MAX VALUE(32) SEE IN HEADSET GAIN NOTE */
            0, headset_tlv),
    SOC_SINGLE_TLV("HEADSETR PGA VOLUME",
            HI6401_HSRPGA_REG, HI6401_HSPGA_GAIN_BIT,
            32, /* MAX VALUE(32) SEE IN HEADSET GAIN NOTE */
            0, headset_tlv),

    SOC_SINGLE("MAINMIC PGA BOOST",
               HI6401_MAINPGA_REG, HI6401_MAINPGA_BOOST_BIT, 1, 0),
    SOC_SINGLE("MAINMIC PGA MUTE",
               HI6401_MAINPGA_REG, HI6401_MAINPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("SUBMIC PGA BOOST",
               HI6401_AUXPGA_REG, HI6401_AUXPGA_BOOST_BIT, 1, 0),
    SOC_SINGLE("SUBMIC PGA MUTE",
               HI6401_AUXPGA_REG, HI6401_AUXPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("SIDETONE PGA MUTE",
               HI6401_SIDEPGA_REG, HI6401_SIDEPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("EARPIECE PGA MUTE",
               HI6401_EARPGA_REG, HI6401_EARPGA_MUTE_BIT, 1, 0),

    SOC_SINGLE("LINEINL PGA MUTE",
               HI6401_LINEINLPGA_REG, HI6401_LINEINPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("LINEINR PGA MUTE",
               HI6401_LINEINRPGA_REG, HI6401_LINEINPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("LINEOUTL PGA MUTE",
               HI6401_LINEOUTLPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("LINEOUTR PGA MUTE",
               HI6401_LINEOUTRPGA_REG, HI6401_LINEOUTPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("HEADSETL PGA MUTE",
               HI6401_HSLPGA_REG, HI6401_HSPGA_MUTE_BIT, 1, 0),
    SOC_SINGLE("HEADSETR PGA MUTE",
               HI6401_HSRPGA_REG, HI6401_HSPGA_MUTE_BIT, 1, 0),

    /*INTERFACE*/
    /*S1 CONFIG*/
    SOC_SINGLE("INTERFACE S1 HZ",
               HI6401_I2S_IO_CONFIG, HI6401_S1_HZ_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 FRAMEMODE",
               HI6401_S1_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 MASTERSLAVE",
               HI6401_S1_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 LRCLOCK",
               HI6401_S1_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 CHANNEL",
               HI6401_S1_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 WORDLENGTH",
               HI6401_S1_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),

    SOC_SINGLE("INTERFACE S1 DIRECTLOOP",
               HI6401_S1_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
    SOC_SINGLE("INTERFACE S1 TX CLK SEL",
               HI6401_S1_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 RX CLK SEL",
               HI6401_S1_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 DATAFORMAT",
               HI6401_S1_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S1 FUNCMODE",
               HI6401_S1_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

    /*S2 CONFIG*/
    SOC_SINGLE("INTERFACE S2 HZ",
               HI6401_I2S_IO_CONFIG, HI6401_S2_HZ_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 FRAMEMODE",
               HI6401_S2_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 MASTERSLAVE",
               HI6401_S2_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 LRCLOCK",
               HI6401_S2_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 CHANNEL",
               HI6401_S2_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 WORDLENGTH",
               HI6401_S2_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),

    SOC_SINGLE("INTERFACE S2 DIRECTLOOP",
               HI6401_S2_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
    SOC_SINGLE("INTERFACE S2 TX CLK SEL",
               HI6401_S2_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 RX CLK SEL",
               HI6401_S2_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 DATAFORMAT",
               HI6401_S2_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S2 FUNCMODE",
               HI6401_S2_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

    /*S3 CONFIG*/
    SOC_SINGLE("INTERFACE S3 HZ",
               HI6401_I2S_IO_CONFIG, HI6401_S3_HZ_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 FRAMEMODE",
               HI6401_S3_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 MASTERSLAVE",
               HI6401_S3_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 LRCLOCK",
               HI6401_S3_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 CHANNEL",
               HI6401_S3_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 WORDLENGTH",
               HI6401_S3_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),

    SOC_SINGLE("INTERFACE S3 DIRECTLOOP",
               HI6401_S3_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
    SOC_SINGLE("INTERFACE S3 TX CLK SEL",
               HI6401_S3_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 RX CLK SEL",
               HI6401_S3_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 DATAFORMAT",
               HI6401_S3_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S3 FUNCMODE",
               HI6401_S3_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

    /*S4 CONFIG*/
    SOC_SINGLE("INTERFACE S4 HZ",
               HI6401_I2S_IO_CONFIG, HI6401_S4_HZ_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 FRAMEMODE",
               HI6401_S4_CONFIG_1, HI6401_FRAME_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 MASTERSLAVE",
               HI6401_S4_CONFIG_1, HI6401_MST_SLV_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 LRCLOCK",
               HI6401_S4_CONFIG_1, HI6401_LRCLK_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 CHANNEL",
               HI6401_S4_CONFIG_1, HI6401_CHNNL_MODE_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 WORDLENGTH",
               HI6401_S4_CONFIG_1, HI6401_WORD_LENGTH_BIT, 3, 0),

    SOC_SINGLE("INTERFACE S4 DIRECTLOOP",
               HI6401_S4_CONFIG_2, HI6401_DIRECT_LOOP_BIT, 2, 0),
    SOC_SINGLE("INTERFACE S4 TX CLK SEL",
               HI6401_S4_CONFIG_2, HI6401_TX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 RX CLK SEL",
               HI6401_S4_CONFIG_2, HI6401_RX_CLK_SEL_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 DATAFORMAT",
               HI6401_S4_CONFIG_2, HI6401_DATA_FORMAT_BIT, 1, 0),
    SOC_SINGLE("INTERFACE S4 FUNCMODE",
               HI6401_S4_CONFIG_2, HI6401_FUNC_MODE_BIT, 5, 0),

    /*FS S1/S2/S3/S4*/
    SOC_SINGLE("INTERFACE S1 FS",
               HI6401_FS_S1_S2_REG, HI6401_FS_S1_BIT, 6, 0),
    SOC_SINGLE("INTERFACE S2 FS",
               HI6401_FS_S1_S2_REG, HI6401_FS_S2_BIT, 6, 0),
    SOC_SINGLE("INTERFACE S3 FS",
               HI6401_FS_S3_S4_REG, HI6401_FS_S3_BIT, 6, 0),
    SOC_SINGLE("INTERFACE S4 FS",
               HI6401_FS_S3_S4_REG, HI6401_FS_S4_BIT, 6, 0),

    /*FS ADCLR/DACLR/DACV*/
    SOC_SINGLE("HI6401_FS_ADCLR",
               HI6401_FS_ADCLR_REG, HI6401_FS_ADCLR_BIT, 6, 0),
    SOC_SINGLE("HI6401_FS_DACLR",
               HI6401_FS_DAC_REG, HI6401_FS_DACLR_BIT, 6, 0),
    SOC_SINGLE("HI6401_FS_DACV",
               HI6401_FS_DAC_REG, HI6401_FS_DACV_BIT, 6, 0),

    /*SDM DITHER*/
    SOC_SINGLE("HI6401_DACV_SDM_DITHER",
               HI6401_DAC_DITHER_CFG, HI6401_DACV_SDM_DITHER_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACR_SDM_DITHER",
               HI6401_DAC_DITHER_CFG, HI6401_DACR_SDM_DITHER_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACL_SDM_DITHER",
               HI6401_DAC_DITHER_CFG, HI6401_DACL_SDM_DITHER_BIT, 1, 0),

    /*DEEMP*/
    SOC_SINGLE("HI6401_BYPASS_DACR_DEEMP",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACR_DEEMP_BIT, 1, 0),
    SOC_SINGLE("HI6401_BYPASS_DACL_DEEMP",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACL_DEEMP_BIT, 1, 0),


    /*HBF2I and HBF1I*/
    SOC_SINGLE("HI6401_BYPASS_DACR_HBF2I",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACR_HBF2I_BIT, 1, 0),
    SOC_SINGLE("HI6401_BYPASS_DACR_HBF1I",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACR_HBF1I_BIT, 1, 0),
    SOC_SINGLE("HI6401_BYPASS_DACL_HBF2I",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACL_HBF2I_BIT, 1, 0),
    SOC_SINGLE("HI6401_BYPASS_DACL_HBF1I",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACL_HBF1I_BIT, 1, 0),
    SOC_SINGLE("HI6401_BYPASS_DACV_HBF2I",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACV_HBF2I_BIT, 1, 0),
    SOC_SINGLE("HI6401_BYPASS_DACV_HBFVI",
               HI6401_DAC_BYPASS_CFG, HI6401_BYPASS_DACV_HBFVI_BIT, 1, 0),

    /*S2/S3/S4 SRC MODE*/
    SOC_SINGLE("HI6401_S4_SRC_MODE",
               HI6401_SRC_MODE, HI6401_S4_SRC_MODE_BIT, 3, 0),
    SOC_SINGLE("HI6401_S3_SRC_MODE",
               HI6401_SRC_MODE, HI6401_S3_SRC_MODE_BIT, 3, 0),
    SOC_SINGLE("HI6401_S2_SRC_MODE",
               HI6401_SRC_MODE, HI6401_S2_SRC_MODE_BIT, 3, 0),

    /*S2 S4 MIXER GAIN*/
    SOC_SINGLE("HI6401_S4_OR_MIXER_GAIN",
               HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S4_OR_MIXER_GAIN_BIT, 2, 0),
    SOC_SINGLE("HI6401_S4_OL_MIXER_GAIN",
               HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S4_OL_MIXER_GAIN_BIT, 2, 0),
    SOC_SINGLE("HI6401_S2_OR_MIXER_GAIN",
               HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S2_OR_MIXER_GAIN_BIT, 2, 0),
    SOC_SINGLE("HI6401_S2_OL_MIXER_GAIN",
               HI6401_S2_S4_MIXER_GAIN_REG, HI6401_S2_OL_MIXER_GAIN_BIT, 2, 0),

    /*DAC MIXER GAIN*/
    SOC_SINGLE("HI6401_DACR_MIXER_GAIN",
               HI6401_DAC_MIXER_CONFIG, HI6401_DACR_MIXER_GAIN_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACL_MIXER_GAIN",
               HI6401_DAC_MIXER_CONFIG, HI6401_DACL_MIXER_GAIN_BIT, 1, 0),

    /*DMIC CONFIG*/
    SOC_SINGLE("HI6401_DMIC_REVERSE",
               HI6401_DMIC_CFG, HI6401_DMIC_REVERSE_BIT, 1, 0),
    SOC_SINGLE("HI6401_DMIC_MODE",
               HI6401_DMIC_CFG, HI6401_DMIC_MODE_BIT, 1, 0),

    /*DACL AGC*/
    /*config 1*/
    SOC_SINGLE("HI6401_DACL_AGC_TIMENNG",
               HI6401_DACL_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_NGI",
               HI6401_DACL_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_DACL_AGC_TIMER",
               HI6401_DACL_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),

    /*config 2*/
    SOC_SINGLE("HI6401_DACL_AGC_NGH",
               HI6401_DACL_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_NGL",
               HI6401_DACL_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_KFRAPID",
               HI6401_DACL_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_KFSLOW",
               HI6401_DACL_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),

    /*config 3*/
    SOC_SINGLE("HI6401_DACL_AGC_GSUPPRESS",
               HI6401_DACL_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACL_AGC_T_AMIN",
               HI6401_DACL_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_YTARGET",
               HI6401_DACL_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_DACL_AGC_NGW",
               HI6401_DACL_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),

    /*config 4*/
    SOC_SINGLE("HI6401_DACL_AGC_TIMEMUTE",
               HI6401_DACL_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_GSTEPD",
               HI6401_DACL_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_LEVELLOW",
               HI6401_DACL_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_GWIN",
               HI6401_DACL_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),

    /*config 5*/
    SOC_SINGLE("HI6401_DACL_AGC_BYPASS",
               HI6401_DACL_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACL_AGC_MUTE_BYPASS",
               HI6401_DACL_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACL_AGC_GMUTE",
               HI6401_DACL_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_TIMEHOLD",
               HI6401_DACL_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACL_AGC_TIMEDECAY",
               HI6401_DACL_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),

    /*config user*/
    SOC_SINGLE("HI6401_DACL_AGC_USER",
               HI6401_DACL_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

    /*DACR AGC*/
    /*config 1*/
    SOC_SINGLE("HI6401_DACR_AGC_TIMENNG",
               HI6401_DACR_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_NGI",
               HI6401_DACR_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_DACR_AGC_TIMER",
               HI6401_DACR_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),

    /*config 2*/
    SOC_SINGLE("HI6401_DACR_AGC_NGH",
               HI6401_DACR_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_NGL",
               HI6401_DACR_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_KFRAPID",
               HI6401_DACR_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_KFSLOW",
               HI6401_DACR_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),

    /*config 3*/
    SOC_SINGLE("HI6401_DACR_AGC_GSUPPRESS",
               HI6401_DACR_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACR_AGC_T_AMIN",
               HI6401_DACR_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_YTARGET",
               HI6401_DACR_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_DACR_AGC_NGW",
               HI6401_DACR_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),

    /*config 4*/
    SOC_SINGLE("HI6401_DACR_AGC_TIMEMUTE",
               HI6401_DACR_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_GSTEPD",
               HI6401_DACR_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_LEVELLOW",
               HI6401_DACR_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_GWIN",
               HI6401_DACR_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),

    /*config 5*/
    SOC_SINGLE("HI6401_DACR_AGC_BYPASS",
               HI6401_DACR_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACR_AGC_MUTE_BYPASS",
               HI6401_DACR_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_DACR_AGC_GMUTE",
               HI6401_DACR_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_TIMEHOLD",
               HI6401_DACR_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_DACR_AGC_TIMEDECAY",
               HI6401_DACR_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),

    /*config user*/
    SOC_SINGLE("HI6401_DACR_AGC_USER",
               HI6401_DACR_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

    /*ADCL AGC*/
    /*config 1*/
    SOC_SINGLE("HI6401_ADCL_AGC_TIMENNG",
               HI6401_ADCL_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_NGI",
               HI6401_ADCL_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_TIMER",
               HI6401_ADCL_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),

    /*config 2*/
    SOC_SINGLE("HI6401_ADCL_AGC_NGH",
               HI6401_ADCL_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_NGL",
               HI6401_ADCL_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_KFRAPID",
               HI6401_ADCL_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_KFSLOW",
               HI6401_ADCL_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),

    /*config 3*/
    SOC_SINGLE("HI6401_ADCL_AGC_GSUPPRESS",
               HI6401_ADCL_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_T_AMIN",
               HI6401_ADCL_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_YTARGET",
               HI6401_ADCL_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_NGW",
               HI6401_ADCL_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),

    /*config 4*/
    SOC_SINGLE("HI6401_ADCL_AGC_TIMEMUTE",
               HI6401_ADCL_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_GSTEPD",
               HI6401_ADCL_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_LEVELLOW",
               HI6401_ADCL_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_GWIN",
               HI6401_ADCL_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),

    /*config 5*/
    SOC_SINGLE("HI6401_ADCL_AGC_BYPASS",
               HI6401_ADCL_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_MUTE_BYPASS",
               HI6401_ADCL_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_GMUTE",
               HI6401_ADCL_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_TIMEHOLD",
               HI6401_ADCL_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_TIMEDECAY",
               HI6401_ADCL_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),

    /*config user*/
    SOC_SINGLE("HI6401_ADCL_AGC_USER",
               HI6401_ADCL_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

    /*ADCR AGC*/
    /*config 1*/
    SOC_SINGLE("HI6401_ADCR_AGC_TIMENNG",
               HI6401_ADCR_AGC_CFG_1, HI6401_AGC_TIMENNG_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_NGI",
               HI6401_ADCR_AGC_CFG_1, HI6401_AGC_NGI_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_TIMER",
               HI6401_ADCR_AGC_CFG_1, HI6401_AGC_TIMER_BIT, 7, 0),
    /*config 2*/
    SOC_SINGLE("HI6401_ADCR_AGC_NGH",
               HI6401_ADCR_AGC_CFG_2, HI6401_AGC_NGH_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_NGL",
               HI6401_ADCR_AGC_CFG_2, HI6401_AGC_NGL_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_KFRAPID",
               HI6401_ADCR_AGC_CFG_2, HI6401_AGC_KFRAPID_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_KFSLOW",
               HI6401_ADCR_AGC_CFG_2, HI6401_AGC_KFSLOW_BIT, 3, 0),

    /*config 3*/
    SOC_SINGLE("HI6401_ADCR_AGC_GSUPPRESS",
               HI6401_ADCR_AGC_CFG_3, HI6401_AGC_GSUPPRESS_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_T_AMIN",
               HI6401_ADCR_AGC_CFG_3, HI6401_AGC_T_AMIN_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_YTARGET",
               HI6401_ADCR_AGC_CFG_3, HI6401_AGC_YTARGET_CONFIG_BIT, 7, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_NGW",
               HI6401_ADCR_AGC_CFG_3, HI6401_AGC_NGW_CONFIG_BIT, 3, 0),

    /*config 4*/
    SOC_SINGLE("HI6401_ADCR_AGC_TIMEMUTE",
               HI6401_ADCR_AGC_CFG_4, HI6401_AGC_TIMEMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_GSTEPD",
               HI6401_ADCR_AGC_CFG_4, HI6401_AGC_GSTEPD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_LEVELLOW",
               HI6401_ADCR_AGC_CFG_4, HI6401_AGC_LEVELLOW_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_GWIN",
               HI6401_ADCR_AGC_CFG_4, HI6401_AGC_GWIN_CONFIG, 3, 0),

    /*config 5*/
    SOC_SINGLE("HI6401_ADCR_AGC_BYPASS",
               HI6401_ADCR_AGC_CFG_5, HI6401_AGC_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_MUTE_BYPASS",
               HI6401_ADCR_AGC_CFG_5, HI6401_AGC_MUTE_BYPASS_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_GMUTE",
               HI6401_ADCR_AGC_CFG_5, HI6401_AGC_GMUTE_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_TIMEHOLD",
               HI6401_ADCR_AGC_CFG_5, HI6401_AGC_TIMEHOLD_CONFIG_BIT, 3, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_TIMEDECAY",
               HI6401_ADCR_AGC_CFG_5, HI6401_AGC_TIMEDECAY_CONFIG_BIT, 3, 0),

    /*config user*/
    SOC_SINGLE("HI6401_ADCR_AGC_USER",
               HI6401_ADCR_AGC_CFG_USER, HI6401_AGC_USR_GDB_BIT, 0xFF, 0),

    /*ADC BYPASS*/
    SOC_SINGLE("HI6401_ADCR_AGC_HBF2D",
               HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCR_HBF2D_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_HBFVD",
               HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCR_HBFVD_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCR_AGC_HPF",
               HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCR_HPF_BIT, 1, 0),

    SOC_SINGLE("HI6401_ADCL_AGC_HBF2D",
               HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCL_HBF2D_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_HBFVD",
               HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCL_HBFVD_BIT, 1, 0),
    SOC_SINGLE("HI6401_ADCL_AGC_HPF",
               HI6401_ADC_BYPASS_CFG, HI6401_BYPAS_ADCL_HPF_BIT, 1, 0),
    SOC_SINGLE("HI6401_POP_CTRL1",
               HI6401_POP_CTRL1,HI6401_POP_CTRL1_BIT , 0xFF, 0),
    SOC_SINGLE("HI6401_POP_CTRL2",
               HI6401_POP_CTRL2, HI6401_POP_CTRL2_BIT, 0xFF, 0),
    SOC_SINGLE("HI6401_CP_PD",
               HI6401_CP_PD_REG, HI6401_CP_PD_BIT, 1, 0),
    SOC_SINGLE("HI6401_CP_DET_PD",
               HI6401_CP_DET_PD_REG, HI6401_CP_DET_PD_BIT, 1, 0),
    SOC_SINGLE("HI6401_HSL_PD",
               HI6401_HSL_PD_REG, HI6401_HSL_PD_BIT, 1, 1),
    SOC_SINGLE("HI6401_HSR_PD",
               HI6401_HSR_PD_REG, HI6401_HSR_PD_BIT, 1, 1),
};

/* DAPM KCONTROLS */

/* OUT EAR MIXERPICE*/
static const struct snd_kcontrol_new hi6401_mixerout_ear_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXOUT_EAR, HI6401_MIXOUT_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXOUT_EAR, HI6401_MIXOUT_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXOUT_EAR, HI6401_MIXOUT_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXOUT_EAR, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXOUT_EAR, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("SIDETONE SWITCH",
                    HI6401_MIXOUT_EAR, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* HEADSETL MIXER*/
static const struct snd_kcontrol_new hi6401_mixerout_hsl_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXOUT_HSL, HI6401_MIXOUT_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXOUT_HSL, HI6401_MIXOUT_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXOUT_HSL, HI6401_MIXOUT_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXOUT_HSL, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXOUT_HSL, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("SIDETONE SWITCH",
                    HI6401_MIXOUT_HSL, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* HEADSETR MIXER*/
static const struct snd_kcontrol_new hi6401_mixerout_hsr_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXOUT_HSR, HI6401_MIXOUT_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXOUT_HSR, HI6401_MIXOUT_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXOUT_HSR, HI6401_MIXOUT_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXOUT_HSR, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXOUT_HSR, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("SIDETONE SWITCH",
                    HI6401_MIXOUT_HSR, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* MIXER OUT LINEOUT LEFT*/
static const struct snd_kcontrol_new hi6401_mixerout_lineoutl_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("SIDETONE SWITCH",
                    HI6401_MIXOUT_LINEOUTL, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* MIXER OUT LINEOUT RIGHT*/
static const struct snd_kcontrol_new hi6401_mixerout_lineoutr_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("SIDETONE SWITCH",
                    HI6401_MIXOUT_LINEOUTR, HI6401_MIXOUT_SIDEPGA_BIT, 1, 0),
};

/* ADCL MIXER */
static const struct snd_kcontrol_new hi6401_mixerin_left_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("MAINMIC SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_MAINPGA_BIT, 1, 0),
    SOC_DAPM_SINGLE("SUBMIC SWITCH",
                    HI6401_MIXINL, HI6401_MIXIN_AUXPGA_BIT, 1, 0),
};

/* ADCR MIXER */
static const struct snd_kcontrol_new hi6401_mixerin_right_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_DACL_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_DACR_BIT, 1, 0),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_DACV_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIL SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_LINEINL_BIT, 1, 0),
    SOC_DAPM_SINGLE("LIR SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_LINEINR_BIT, 1, 0),
    SOC_DAPM_SINGLE("MAINMIC SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_MAINPGA_BIT, 1, 0),
    SOC_DAPM_SINGLE("SUBMIC SWITCH",
                    HI6401_MIXINR, HI6401_MIXIN_AUXPGA_BIT, 1, 0),
};

/* MIXER DACL */
static const struct snd_kcontrol_new hi6401_mixer_dacl_controls[] = {
    SOC_DAPM_SINGLE("S1L SWITCH",
                    HI6401_MIXER_DACL_REG, HI6401_MIXER_DACL_S1_BIT, 1, 1),
    SOC_DAPM_SINGLE("S2L SWITCH",
                    HI6401_MIXER_DACL_REG, HI6401_MIXER_DACL_S2_BIT, 1, 1),
};

/* MIXER DACR */
static const struct snd_kcontrol_new hi6401_mixer_dacr_controls[] = {
    SOC_DAPM_SINGLE("S1R SWITCH",
                    HI6401_MIXER_DACR_REG, HI6401_MIXER_DACR_S1_BIT, 1, 1),
    SOC_DAPM_SINGLE("S2R SWITCH",
                    HI6401_MIXER_DACR_REG, HI6401_MIXER_DACR_S2_BIT, 1, 1),
};

/* MIXER S2L */
static const struct snd_kcontrol_new hi6401_mixer_s2l_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_S2_MIXER_OL_REG, HI6401_S2_MIXER_OL_DACL_BIT, 1, 1),
    SOC_DAPM_SINGLE("ADCL SWITCH",
                    HI6401_S2_MIXER_OL_REG, HI6401_S2_MIXER_OL_ADCL_BIT, 1, 1),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_S2_MIXER_OR_REG, HI6401_S2_MIXER_OL_DACV_BIT, 1, 1),
    SOC_DAPM_SINGLE("S1LR SWITCH",
                    HI6401_S2_MIXER_OR_REG, HI6401_S2_MIXER_OL_S1_LR_BIT, 1, 1),
};

/* MIXER S2R */
static const struct snd_kcontrol_new hi6401_mixer_s2r_controls[] = {
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_S2_MIXER_OR_REG, HI6401_S2_MIXER_OR_DACR_BIT, 1, 1),
    SOC_DAPM_SINGLE("ADCR SWITCH",
                    HI6401_S2_MIXER_OR_REG, HI6401_S2_MIXER_OR_ADCR_BIT, 1, 1),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_S2_MIXER_OR_REG, HI6401_S2_MIXER_OR_DACV_BIT, 1, 1),
    SOC_DAPM_SINGLE("S1LR SWITCH",
                    HI6401_S2_MIXER_OR_REG, HI6401_S2_MIXER_OR_S1_LR_BIT, 1, 1),
};

/* MIXER S4L */
static const struct snd_kcontrol_new hi6401_mixer_s4l_controls[] = {
    SOC_DAPM_SINGLE("DACL SWITCH",
                    HI6401_S4_MIXER_OL_REG, HI6401_S4_MIXER_OL_DACL_BIT, 1, 1),
    SOC_DAPM_SINGLE("ADCL SWITCH",
                    HI6401_S4_MIXER_OL_REG, HI6401_S4_MIXER_OL_ADCL_BIT, 1, 1),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_S4_MIXER_OL_REG, HI6401_S4_MIXER_OL_DACV_BIT, 1, 1),
    SOC_DAPM_SINGLE("S1LR SWITCH",
                    HI6401_S4_MIXER_OL_REG, HI6401_S4_MIXER_OL_S1_LR_BIT, 1, 1),
};

/* MIXER S4R */
static const struct snd_kcontrol_new hi6401_mixer_s4r_controls[] = {
    SOC_DAPM_SINGLE("DACR SWITCH",
                    HI6401_S4_MIXER_OR_REG, HI6401_S4_MIXER_OR_DACR_BIT, 1, 1),
    SOC_DAPM_SINGLE("ADCR SWITCH",
                    HI6401_S4_MIXER_OR_REG, HI6401_S4_MIXER_OR_ADCR_BIT, 1, 1),
    SOC_DAPM_SINGLE("DACV SWITCH",
                    HI6401_S4_MIXER_OR_REG, HI6401_S4_MIXER_OR_DACV_BIT, 1, 1),
    SOC_DAPM_SINGLE("S1LR SWITCH",
                    HI6401_S4_MIXER_OR_REG, HI6401_S4_MIXER_OR_S1_LR_BIT, 1, 1),
};


static const char *hi6401_mic_mux_texts[] = {
    "MIC OFF", /* 00/11 : mute */
    "MIC MAIN",/* 01 : enable mainmic */
    "MIC HS"   /* 10 : enable hs_mic */
};
static const struct soc_enum hi6401_mic_mux_enum =
    SOC_ENUM_SINGLE(HI6401_MAINPGA_REG, HI6401_MAINPGA_SEL_BIT,
            ARRAY_SIZE(hi6401_mic_mux_texts), hi6401_mic_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_mic_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_mic_mux_enum);

static const char *hi6401_chn_mux_texts[] = {
    "LEFT", /* 0 : LEFT */
    "RIGHT",/* 1 : RIGHT */
};
static const struct soc_enum hi6401_s3_chn_mux_enum =
    SOC_ENUM_SINGLE(HI6401_MISC_CONFIG, HI6401_S3_CHN_SEL,
            ARRAY_SIZE(hi6401_chn_mux_texts), hi6401_chn_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s3_chn_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_s3_chn_mux_enum);

static const struct soc_enum hi6401_s4_chn_mux_enum =
    SOC_ENUM_SINGLE(HI6401_MISC_CONFIG, HI6401_S4_CHN_SEL,
            ARRAY_SIZE(hi6401_chn_mux_texts), hi6401_chn_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s4_chn_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_s4_chn_mux_enum);

static const char *hi6401_dacv_mux_texts[] = {
    "S3MODEM",/* 0 : S3 MODEM */
    "S4MODEM",/* 1 : S4 MODEM */
};
static const struct soc_enum hi6401_dacv_mux_enum =
    SOC_ENUM_SINGLE(HI6401_MISC_CONFIG, HI6401_DACV_CHN_SEL,
            ARRAY_SIZE(hi6401_dacv_mux_texts), hi6401_dacv_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_dacv_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_dacv_mux_enum);


static const char *hi6401_adc_agc_mux_texts[] = {
    "ADCL",   /* 0 : ADCL */
    "ADCR",   /* 1 : ADCR */
    "S2L",    /* 2 : S2L  */
    "S2R",    /* 3 : S2R  */
    "S3MODEM",/* 4 : S3MODEM */
    "S4MODEM",/* 5 : S4MODEM */
};

static const struct soc_enum hi6401_adc_agcl_mux_enum =
    SOC_ENUM_SINGLE(HI6401_S1_MUX_SEL, HI6401_S1_OL_BIT,
            ARRAY_SIZE(hi6401_adc_agc_mux_texts), hi6401_adc_agc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_agcl_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_adc_agcl_mux_enum);

static const struct soc_enum hi6401_adc_agcr_mux_enum =
    SOC_ENUM_SINGLE(HI6401_S1_MUX_SEL, HI6401_S1_OR_BIT,
            ARRAY_SIZE(hi6401_adc_agc_mux_texts), hi6401_adc_agc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_agcr_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_adc_agcr_mux_enum);

static const char *hi6401_uplinkl_mux_texts[] = {
    "S1L",    /* 0 : S1L */
    "S1LR",   /* 1 : S1LR */
    "S2L",    /* 2 : S2L */
    "DACL",   /* 3 : DACL */
    "ADCL",   /* 4 : ADCL */
    "S4MODEM",/* 5 : S4MODEM */
};
static const struct soc_enum hi6401_uplinkl_mux_enum =
    SOC_ENUM_SINGLE(HI6403_S3_MUX_SEL, HI6401_S3_OL_BIT,
            ARRAY_SIZE(hi6401_uplinkl_mux_texts), hi6401_uplinkl_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_uplinkl_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_uplinkl_mux_enum);

static const char *hi6401_uplinkr_mux_texts[] = {
    "S1R",    /* 0 : S1R */
    "S1LR",   /* 1 : S1LR */
    "S2R",    /* 2 : S2R */
    "DACR",   /* 3 : DACR */
    "ADCR",   /* 4 : ADCR */
    "S4MODEM",/* 5 : S4MODEM */
};
static const struct soc_enum hi6401_uplinkr_mux_enum =
    SOC_ENUM_SINGLE(HI6403_S3_MUX_SEL, HI6401_S3_OR_BIT,
            ARRAY_SIZE(hi6401_uplinkr_mux_texts), hi6401_uplinkr_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_uplinkr_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_uplinkr_mux_enum);


static const char *hi6401_s4l_mux_texts[] = {
    "UPLINKL",  /* 0 : UPLINKL */
    "S4MIXERL", /* 1 : S4MIXERL */
    "S4MIXERLR",/* 2 : S4MIXERLR */
};
static const struct soc_enum hi6401_s4l_mux_enum =
    SOC_ENUM_SINGLE(HI6404_S4_MUX_SEL, HI6401_S4_OL_BIT,
            ARRAY_SIZE(hi6401_s4l_mux_texts), hi6401_s4l_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s4l_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_s4l_mux_enum);


static const char *hi6401_s4r_mux_texts[] = {
    "UPLINKR",  /* 0 : UPLINKR */
    "S4MIXERR", /* 1 : S4MIXERR */
    "S4MIXERLR",/* 2 : S4MIXERLR */
};
static const struct soc_enum hi6401_s4r_mux_enum =
    SOC_ENUM_SINGLE(HI6404_S4_MUX_SEL, HI6401_S4_OR_BIT,
            ARRAY_SIZE(hi6401_s4r_mux_texts), hi6401_s4r_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_s4r_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_s4r_mux_enum);

/* ADC FLITER LEFT & RIGHT MUX */
static const char *hi6401_adc_mux_texts[] = {
    "ADC", /* 0 : ADC FILTER Mux choose ADC */
    "DACL",/* 1 : ADC FILTER Mux choose DAC Filter L */
    "DACR",/* 2 : ADC FILTER Mux choose DAC Filter R */
    "DACV",/* 3 : ADC FILTER Mux choose DAC Filter V */
    "DMIC" /* 4 : ADC FILTER Mux choose Digital Mic */
};

static const struct soc_enum hi6401_adcl_mux_enum =
    SOC_ENUM_SINGLE(HI6401_ADCL_MUX, HI6401_ADCL_MUX_BIT,
            ARRAY_SIZE(hi6401_adc_mux_texts), hi6401_adc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_adcl_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_adcl_mux_enum);

static const struct soc_enum hi6401_adcr_mux_enum =
    SOC_ENUM_SINGLE(HI6401_ADCR_MUX, HI6401_ADCR_MUX_BIT,
            ARRAY_SIZE(hi6401_adc_mux_texts), hi6401_adc_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_adcr_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_adcr_mux_enum);

/* DIGITAL MIC MUX */
static const char *hi6401_digmic_mux_texts[] = {
    "OFF",/* 0 : off the clock */
    "2FD",/* 1 : 2 frequency division */
    "3FD",/* 2 : 3 frequency division */
    "4FD" /* 3 : 4 frequency division */
};

static const struct soc_enum hi6401_digmic_mux_enum =
    SOC_ENUM_SINGLE(HI6401_DMIC_CFG, HI6401_DMIC_CLK_BIT,
            ARRAY_SIZE(hi6401_digmic_mux_texts), hi6401_digmic_mux_texts);
static const struct snd_kcontrol_new hi6401_dapm_digmic_mux_controls =
    SOC_DAPM_ENUM("Mux", hi6401_digmic_mux_enum);

/* S1 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_s1_outl_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S1_MODULE_CLK_REG, HI6401_S1_AGC_OL_EN_BIT, 1, 0);

/* S1 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_s1_outr_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S1_MODULE_CLK_REG, HI6401_S1_AGC_OR_EN_BIT, 1, 0);

/* S2 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S2_outl_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_OL_EN_BIT, 1, 0);

/* S2 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S2_outr_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_OR_EN_BIT, 1, 0);

/* S3 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S3_outl_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S3_MODULE_CLK_REG, HI6401_S3_PGA_OL_EN_BIT, 1, 0);

/* S3 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S3_outr_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S3_MODULE_CLK_REG, HI6401_S3_PGA_OR_EN_BIT, 1, 0);

/* S4 OUT L SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S4_outl_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S4_MODULE_CLK_REG, HI6401_S4_PGA_OL_EN_BIT, 1, 0);

/* S4 OUT R SWITCH */
static const struct snd_kcontrol_new hi6401_dapm_S4_outr_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_S4_MODULE_CLK_REG, HI6401_S4_PGA_OR_EN_BIT, 1, 0);

/* DACV FILTER */
static const struct snd_kcontrol_new hi6401_dapm_dacv_filter_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_CHANNEL_CLK_REG, HI6401_DACV_CLK_EN_BIT, 1, 0);
/* ADCL FILTER */
static const struct snd_kcontrol_new hi6401_dapm_adcl_filter_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_CHANNEL_CLK_REG, HI6401_ADCL_CLK_EN_BIT, 1, 0);

/* ADCR FILTER */
static const struct snd_kcontrol_new hi6401_dapm_adcr_filter_switch_controls =
    SOC_DAPM_SINGLE("SWITCH",
            HI6401_CHANNEL_CLK_REG, HI6401_ADCR_CLK_EN_BIT, 1, 0);

static inline bool is_k3_platfrom(void)
{
    /*TODO*/
    return false;
}

static void hi6401_ibias_enable(void)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return;
    }
    logd("Begin, hi6401_ibias_enabled=%d", hi6401_ibias_enabled);
    if (0 == hi6401_ibias_enabled) {
        del_timer_sync(&priv->timer);
        cancel_delayed_work_sync(&priv->low_power_work);
        down(&priv->state_sema);
        hi6401_ibias_enabled++;
        hi6401_exit_eco_mode(g_codec);
        up(&priv->state_sema);

        /* check pll is ok or not */
        if (!(hi6401_reg_read(g_codec, HI6401_LOR_GAIN_DONE) & 0x01)){
            hi6401_reg_write(g_codec, HI6401_PLL_EN_REG, 0x5F);
            msleep(2);
            priv->set_reg_bits(HI6401_DAC_PLL_PD, 0x1);
            msleep(2);
            priv->clr_reg_bits(HI6401_DAC_PLL_PD, 0x1);
            msleep(2);
            hi6401_reg_write(g_codec, HI6401_PLL_EN_REG, HI6401_PLL_EN_VALUE);
        }
    } else {
        hi6401_ibias_enabled++;
    }
    logd("End, hi6401_ibias_enabled=%d", hi6401_ibias_enabled);
}

static void hi6401_ibias_disable(void)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return;
    }
    logd("Begin, hi6401_ibias_enabled=%d", hi6401_ibias_enabled);
    hi6401_ibias_enabled--;
    if (0 == hi6401_ibias_enabled) {
        /* set timer to enter eco mode */
        mod_timer(&priv->timer, jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);
    }
    logd("End, hi6401_ibias_enabled=%d", hi6401_ibias_enabled);
}

int hi6401_s1il_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_IL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_IL_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s1ir_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_IR_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_IR_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s2il_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_IL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_IL_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s2ir_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S2_MODULE_CLK_REG,  0x1 << HI6401_S2_SRC_IR_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_IR_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s3i_power_mode_event(struct snd_soc_dapm_widget *w,
                                struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S3_MODULE_CLK_REG, 0x1 << HI6401_S3_SRC_I_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S3_MODULE_CLK_REG, 0x1 << HI6401_S3_SRC_I_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s4i_power_mode_event(struct snd_soc_dapm_widget *w,
                                struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S4_MODULE_CLK_REG, 0x1 << HI6401_S4_SRC_I_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S4_MODULE_CLK_REG, 0x1 << HI6401_S4_SRC_I_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s1ol_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_OL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_OL_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s1or_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_OR_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S1_MODULE_CLK_REG, 0x1 << HI6401_S1_SRC_OR_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s2ol_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_OL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_OL_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s2or_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_OR_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S2_MODULE_CLK_REG, 0x1 << HI6401_S2_SRC_OR_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s3ol_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S3_MODULE_CLK_REG, 0x1 << HI6401_S3_SRC_OL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S3_MODULE_CLK_REG, 0x1 << HI6401_S3_SRC_OL_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s3or_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())  {
         if (SND_SOC_DAPM_PRE_PMU == event)  {
              /* add delay to avoid headset pop while picking up the phone */
              mdelay(50);
         }
         return 0;
    }

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S3_MODULE_CLK_REG, 0x1 << HI6401_S3_SRC_OR_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S3_MODULE_CLK_REG, 0x1 << HI6401_S3_SRC_OR_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s4ol_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S4_MODULE_CLK_REG, 0x1 << HI6401_S4_SRC_OL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S4_MODULE_CLK_REG, 0x1 << HI6401_S4_SRC_OL_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_s4or_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    if (!is_k3_platfrom())
        return 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_S4_MODULE_CLK_REG, 0x1 << HI6401_S4_SRC_OR_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_S4_MODULE_CLK_REG, 0x1 << HI6401_S4_SRC_OR_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}
int hi6401_mainmic_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
#ifdef CONFIG_FACTORY_MODE
    return 0;
#endif
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_MAINPGA_ZCD_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_MAINPGA_ZCD_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_submic_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
#ifdef CONFIG_FACTORY_MODE
    return 0;
#endif
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_AUXPGA_ZCD_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_AUXPGA_ZCD_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_hsl_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    int hp_pga = 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        logi("PRE Begin.");
        /* let empty */
        logi("PRE End.");
        break;
    case SND_SOC_DAPM_POST_PMD:
        logi("POST Begin");

        /* hp PGA step down, not mute now */
        for(hp_pga=0x19/*0x18<-6db>*/; hp_pga >= 0; ) {
            hi6401_reg_write(g_codec, HI6401_HSLPGA_REG, hp_pga << HI6401_HSPGA_GAIN_BIT);
            hi6401_reg_write(g_codec, HI6401_HSRPGA_REG, hp_pga << HI6401_HSPGA_GAIN_BIT);
            mdelay(5);

            if (hp_pga > 0x0C/*0x0C<-24db>*/) {
                hp_pga--;
            } else if (hp_pga > 0x08) {
                hp_pga -= 4;
            } else {
                hp_pga -= 8;
            }
        }

        /* hp mute */
        hi6401_reg_write(g_codec, HI6401_HSLPGA_REG, 0x01);
        hi6401_reg_write(g_codec, HI6401_HSRPGA_REG, 0x01);

        /* 关闭MIXER */
        hi6401_set_reg_bits(HI6401_MIXOUT_HSL_PD_REG, 0x1 << HI6401_MIXOUT_HSL_PD_BIT);
        hi6401_set_reg_bits(HI6401_MIXOUT_HSR_PD_REG, 0x1 << HI6401_MIXOUT_HSR_PD_BIT);

        /* config pop抑制模块 */
        hi6401_reg_write(g_codec, HI6401_POP_CTRL2, 0x5C);

        /* hp PGA 下电 */
        hi6401_set_reg_bits(HI6401_HSL_PD_REG, 0x1 << HI6401_HSL_PD_BIT);
        hi6401_set_reg_bits(HI6401_HSR_PD_REG, 0x1 << HI6401_HSR_PD_BIT);
        mdelay(70);

        /* hp Zero Cross */
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_HSL_ZCD_EN_BIT);
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_HSR_ZCD_EN_BIT);

        /* charger pump det 下电 */
        hi6401_set_reg_bits(HI6401_CP_PD_REG, 0x1 << HI6401_CP_DET_PD_BIT);

        /* charger pump 下电 */
        hi6401_set_reg_bits(HI6401_CP_PD_REG, 0x1 << HI6401_CP_PD_BIT);

        logi("POST End");
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_hsr_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    int hp_pga = 0;

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        logi("PRE Begin");

        /* charger pump 上电 */
        mdelay(1);
        hi6401_clr_reg_bits(HI6401_CP_PD_REG, 0x1 << HI6401_CP_PD_BIT);
        /* charger pump det 上电 */
        hi6401_clr_reg_bits(HI6401_CP_PD_REG, 0x1 << HI6401_CP_DET_PD_BIT);


        /* config pop抑制模块 */
        hi6401_reg_write(g_codec, HI6401_POP_CTRL1, 0xE1);
        hi6401_reg_write(g_codec, HI6401_POP_CTRL2, 0x6C);

        /* hp mute(&& PGA set) */
        hi6401_reg_write(g_codec, HI6401_HSLPGA_REG, 0x01);
        hi6401_reg_write(g_codec, HI6401_HSRPGA_REG, 0x01);

        /* hp Zero Cross */
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_HSL_ZCD_EN_BIT);
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_HSR_ZCD_EN_BIT);
        mdelay(7);

        /* hp PGA 上电 */
        hi6401_clr_reg_bits(HI6401_HSL_PD_REG, 0x1 << HI6401_HSL_PD_BIT);
        hi6401_clr_reg_bits(HI6401_HSR_PD_REG, 0x1 << HI6401_HSR_PD_BIT);
        mdelay(70);

        /* 打开MIXER */
        hi6401_clr_reg_bits(HI6401_MIXOUT_HSL_PD_REG, 0x1 << HI6401_MIXOUT_HSL_PD_BIT);
        hi6401_clr_reg_bits(HI6401_MIXOUT_HSR_PD_REG, 0x1 << HI6401_MIXOUT_HSR_PD_BIT);

        /* hp unmute && PGA step up */
        hi6401_clr_reg_bits(HI6401_HSLPGA_REG, 0x1 << HI6401_HSPGA_MUTE_BIT);
        hi6401_clr_reg_bits(HI6401_HSRPGA_REG, 0x1 << HI6401_HSPGA_MUTE_BIT);
        for(hp_pga=0; hp_pga < 0x1A/*0x18<-6db>*/; ) {
            hi6401_reg_write(g_codec, HI6401_HSLPGA_REG, hp_pga << HI6401_HSPGA_GAIN_BIT);
            hi6401_reg_write(g_codec, HI6401_HSRPGA_REG, hp_pga << HI6401_HSPGA_GAIN_BIT);
            mdelay(5);

            if (hp_pga >= 0x0C/*0x0C<-24db>*/) {
                hp_pga++;
            } else if (hp_pga >= 0x08) {
                hp_pga += 4;
            } else {
                hp_pga += 8;
            }
        }

        logi("PRE End");
        break;
    case SND_SOC_DAPM_POST_PMD:
        logi("POST Begin.");
        /* let empty */
        logi("POST End.");
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_ear_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_EAR_ZCD_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_EAR_ZCD_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}
int hi6401_lol_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_LOL_ZCD_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_LOL_ZCD_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_lor_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_LOR_ZCD_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_ZC_EN, 0x1 << HI6401_LOR_ZCD_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}
int hi6401_dacl_agc_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_CHANNEL_CLK_REG, 0x1 << HI6401_DACL_CLK_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_CHANNEL_CLK_REG, 0x1 << HI6401_DACL_CLK_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

int hi6401_dacr_agc_power_mode_event(struct snd_soc_dapm_widget *w,
                                 struct snd_kcontrol *kcontrol, int event)
{
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_set_reg_bits(HI6401_CHANNEL_CLK_REG, 0x1 << HI6401_DACR_CLK_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_clr_reg_bits(HI6401_CHANNEL_CLK_REG, 0x1 << HI6401_DACR_CLK_EN_BIT);
        break;
    default :
        pr_warn("%s : pga event err : %d\n", __FUNCTION__, event);
        break;
    }
    return 0;
}

/* IBIAS EVENT */
int hi6401_ibias_power_mode_event(struct snd_soc_dapm_widget *w,
        struct snd_kcontrol *kcontrol, int event)
{
    /*pr_info("%s : event = %d\n",__FUNCTION__, event);*/
    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        hi6401_ibias_enable();
        break;
    case SND_SOC_DAPM_POST_PMD:
        hi6401_ibias_disable();
        break;
    default :
        pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
        break;
    }

    return 0;
}
/* PLL EVENT */
int hi6401_pll_power_mode_event(struct snd_soc_dapm_widget *w,
        struct snd_kcontrol *kcontrol, int event)
{
    /*pr_info("%s : event = %d\n",__FUNCTION__, event);*/
    struct hi6401_priv *priv = NULL;
    priv = snd_soc_codec_get_drvdata(g_codec);

    switch (event) {
    case SND_SOC_DAPM_PRE_PMU:
        priv->clr_reg_bits(HI6401_DAC_PLL_PD, 0x1 << HI6401_PLL_PD_BIT);
        msleep(5);
        priv->set_reg_bits(HI6401_PLL_EN_REG, 0x1 << HI6401_PLL_EN_BIT);
        break;
    case SND_SOC_DAPM_POST_PMD:
        priv->clr_reg_bits(HI6401_PLL_EN_REG, 0x1 << HI6401_PLL_EN_BIT);
        msleep(5);
        priv->set_reg_bits(HI6401_DAC_PLL_PD, 0x1 << HI6401_PLL_PD_BIT);
        break;
    default :
        pr_warn("%s : power mode event err : %d\n", __FUNCTION__, event);
        break;
    }

    return 0;
}

/* DAPM WIDGETS */
static const struct snd_soc_dapm_widget hi6401_dapm_widgets[] = {

    /* INPUT */
    SND_SOC_DAPM_INPUT("LINEINL"),
    SND_SOC_DAPM_INPUT("LINEINR"),
    SND_SOC_DAPM_INPUT("MAINMIC"),
    SND_SOC_DAPM_INPUT("SUBMIC"),
    SND_SOC_DAPM_INPUT("HSMIC"),

    SND_SOC_DAPM_INPUT("ANALOG DACL"),
    SND_SOC_DAPM_INPUT("ANALOG DACR"),
    SND_SOC_DAPM_INPUT("ANALOG DACV"),

    SND_SOC_DAPM_INPUT("S1L IN"),
    SND_SOC_DAPM_INPUT("S1R IN"),
    SND_SOC_DAPM_INPUT("S2L IN"),
    SND_SOC_DAPM_INPUT("S2R IN"),
    SND_SOC_DAPM_INPUT("S3 IN"),
    SND_SOC_DAPM_INPUT("S4 IN"),
    SND_SOC_DAPM_INPUT("DIGMIC"),
    SND_SOC_DAPM_INPUT("DIGITAL ADCL"),
    SND_SOC_DAPM_INPUT("DIGITAL ADCR"),

    /* OUTPUT */
    SND_SOC_DAPM_OUTPUT("OUT EAR"),
    SND_SOC_DAPM_OUTPUT("OUT HSL"),
    SND_SOC_DAPM_OUTPUT("OUT HSR"),
    SND_SOC_DAPM_OUTPUT("LINEOUT L"),
    SND_SOC_DAPM_OUTPUT("LINEOUT R"),
    SND_SOC_DAPM_OUTPUT("ANALOG ADCL"),
    SND_SOC_DAPM_OUTPUT("ANALOG ADCR"),

    SND_SOC_DAPM_OUTPUT("S1L OUT"),
    SND_SOC_DAPM_OUTPUT("S1R OUT"),
    SND_SOC_DAPM_OUTPUT("S2L OUT"),
    SND_SOC_DAPM_OUTPUT("S2R OUT"),
    SND_SOC_DAPM_OUTPUT("S3L OUT"),
    SND_SOC_DAPM_OUTPUT("S3R OUT"),
    SND_SOC_DAPM_OUTPUT("S4L OUT"),
    SND_SOC_DAPM_OUTPUT("S4R OUT"),
    SND_SOC_DAPM_OUTPUT("DIGITAL DACL"),
    SND_SOC_DAPM_OUTPUT("DIGITAL DACR"),
    SND_SOC_DAPM_OUTPUT("DIGITAL DACV"),

    /* MICS */
    SND_SOC_DAPM_MIC("MAIN MIC", NULL),
    SND_SOC_DAPM_MIC("SUB MIC", NULL),
    SND_SOC_DAPM_MIC("HS MIC", NULL),

    /* MICBIAS */
    SND_SOC_DAPM_MICBIAS("MAIN MICBIAS", HI6401_MAINMICBIAS_PD_REG,
                         HI6401_MAINMICBIAS_PD_BIT, 1),
    SND_SOC_DAPM_MICBIAS("SUB MICBIAS", HI6401_SUBMICBIAS_PD_REG,
                         HI6401_SUBMICBIAS_PD_BIT, 1),

    /* SUPPLY */
    SND_SOC_DAPM_SUPPLY("S1 TX CLK",
                        HI6401_S1_CONFIG_1, HI6401_IF_TX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S1 RX CLK",
                        HI6401_S1_CONFIG_1, HI6401_IF_RX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S1 INTERFACE CLK",
                        HI6401_IF_CLK_REG, HI6401_S1_IF_CLK_EN_BIT, 0,
                        NULL, 0),

    SND_SOC_DAPM_SUPPLY("S2 TX CLK",
                        HI6401_S2_CONFIG_1, HI6401_IF_TX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S2 RX CLK",
                        HI6401_S2_CONFIG_1, HI6401_IF_RX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S2 INTERFACE CLK",
                        HI6401_IF_CLK_REG, HI6401_S2_IF_CLK_EN_BIT, 0,
                        NULL, 0),

    SND_SOC_DAPM_SUPPLY("S3 TX CLKV",
                        SND_SOC_NOPM/*HI6401_S3_CONFIG_1*/, HI6401_IF_TX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S3 TX CLK",
                        HI6401_S3_CONFIG_1, HI6401_IF_TX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S3 RX CLK",
                        HI6401_S3_CONFIG_1, HI6401_IF_RX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S3 INTERFACE CLK",
                        HI6401_IF_CLK_REG, HI6401_S3_IF_CLK_EN_BIT, 0,
                        NULL, 0),

    SND_SOC_DAPM_SUPPLY("S4 TX CLK",
                        HI6401_S4_CONFIG_1, HI6401_IF_TX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S4 RX CLK",
                        HI6401_S4_CONFIG_1, HI6401_IF_RX_EN_BIT, 0,
                        NULL, 0),
    SND_SOC_DAPM_SUPPLY("S4 INTERFACE CLK",
                        HI6401_IF_CLK_REG, HI6401_S4_IF_CLK_EN_BIT, 0,
                        NULL, 0),

    SND_SOC_DAPM_SUPPLY("PLL CLK",
                        SND_SOC_NOPM, 0, 0,
                        hi6401_pll_power_mode_event,
                        SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SUPPLY("IBIAS",
                        SND_SOC_NOPM, 0, 0,
                        hi6401_ibias_power_mode_event,
                        SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

    /* PGA */
    SND_SOC_DAPM_PGA_E("MAINMIC PGA",
                     HI6401_MAINPGA_PD_REG, HI6401_MAINPGA_PD_BIT, 1,
                     NULL, 0,
                     hi6401_mainmic_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("SUBMIC PGA",
                     HI6401_AUXPGA_PD_REG, HI6401_AUXPGA_PD_BIT, 1,
                     NULL, 0,
                     hi6401_submic_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

    SND_SOC_DAPM_PGA("SIDETONE PGA",
                     HI6401_SIDEPGA_PD_REG, HI6401_SIDEPGA_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("LINEINL PGA",
                     HI6401_LINEINLPGA_PD_REG, HI6401_LINEINLPGA_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("LINEINR PGA",
                     HI6401_LINEINRPGA_PD_REG, HI6401_LINEINRPGA_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("DACL",
                     HI6401_DACL_PD_REG, HI6401_DACL_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("DACR",
                     HI6401_DACR_PD_REG, HI6401_DACR_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("DACV",
                     HI6401_DACV_PD_REG, HI6401_DACV_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("ADC L",
                     HI6401_ADCL_PD_REG, HI6401_ADCL_PD_BIT, 1,
                     NULL, 0),
    SND_SOC_DAPM_PGA("ADC R",
                     HI6401_ADCR_PD_REG, HI6401_ADCR_PD_BIT, 1,
                     NULL, 0),

    /* PGA FOR LR MIXER */
    SND_SOC_DAPM_PGA("S1 FIX PGA",
                     SND_SOC_NOPM, 0, 0,
                     NULL, 0),

    SND_SOC_DAPM_PGA_E("DACL AGC",
                       HI6401_DAC_AGC_CLK_REG, HI6401_DACL_AGC_CLK_EN_BIT, 0,
                       NULL, 0,
                       hi6401_dacl_agc_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("DACR AGC",
                       HI6401_DAC_AGC_CLK_REG, HI6401_DACR_AGC_CLK_EN_BIT, 0,
                       NULL, 0,
                       hi6401_dacr_agc_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

    SND_SOC_DAPM_PGA_E("S1 IL PGA",
                       HI6401_S1_MODULE_CLK_REG, HI6401_S1_PGA_IL_EN_BIT, 0,
                       NULL, 0,
                       hi6401_s1il_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("S1 IR PGA",
                       HI6401_S1_MODULE_CLK_REG, HI6401_S1_PGA_IR_EN_BIT, 0,
                       NULL, 0,
                       hi6401_s1ir_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("S2 IL PGA",
                       HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_IL_EN_BIT, 0,
                       NULL, 0,
                       hi6401_s2il_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("S2 IR PGA",
                       HI6401_S2_MODULE_CLK_REG, HI6401_S2_PGA_IR_EN_BIT, 0,
                       NULL, 0,
                       hi6401_s2ir_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("S3 I PGA",
                       HI6401_S3_MODULE_CLK_REG, HI6401_S3_PGA_I_EN_BIT, 0,
                       NULL, 0,
                       hi6401_s3i_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_PGA_E("S4 I PGA",
                       HI6401_S4_MODULE_CLK_REG, HI6401_S4_PGA_I_EN_BIT, 0,
                       NULL, 0,
                       hi6401_s4i_power_mode_event,
                       SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

    SND_SOC_DAPM_OUT_DRV_E("EARPIECE PGA",
                     HI6401_EAR_PD_REG, HI6401_EAR_PD_BIT, 1,
                     NULL, 0,
                     hi6401_ear_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_OUT_DRV_E("HEADSETL PGA",
                     SND_SOC_NOPM/*HI6401_HSL_PD_REG*/, HI6401_HSL_PD_BIT, 1,
                     NULL, 0,
                     hi6401_hsl_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_OUT_DRV_E("HEADSETR PGA",
                     SND_SOC_NOPM/*HI6401_HSR_PD_REG*/, HI6401_HSR_PD_BIT, 1,
                     NULL, 0,
                     hi6401_hsr_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_OUT_DRV_E("LINEOUTL PGA",
                     HI6401_LOL_PD_REG, HI6401_LOL_PD_BIT, 1,
                     NULL, 0,
                     hi6401_lol_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_OUT_DRV_E("LINEOUTR PGA",
                     HI6401_LOR_PD_REG, HI6401_LOR_PD_BIT, 1,
                     NULL, 0,
                     hi6401_lor_power_mode_event,
                     SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

    /* MUX */
    SND_SOC_DAPM_MUX("MIC MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_mic_mux_controls),
    SND_SOC_DAPM_MUX("S3 CHN MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_s3_chn_mux_controls),
    SND_SOC_DAPM_MUX("S4 CHN MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_s4_chn_mux_controls),
    SND_SOC_DAPM_MUX("DACV MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_dacv_mux_controls),
    SND_SOC_DAPM_MUX("ADCL MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_adcl_mux_controls),
    SND_SOC_DAPM_MUX("ADCR MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_adcr_mux_controls),
    SND_SOC_DAPM_MUX("AGCL MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_agcl_mux_controls),
    SND_SOC_DAPM_MUX("AGCR MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_agcr_mux_controls),
    SND_SOC_DAPM_MUX("UPLINKL MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_uplinkl_mux_controls),
    SND_SOC_DAPM_MUX("UPLINKR MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_uplinkr_mux_controls),
    SND_SOC_DAPM_MUX("S4L MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_s4l_mux_controls),
    SND_SOC_DAPM_MUX("S4R MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_s4r_mux_controls),
    SND_SOC_DAPM_MUX("DIGMIC MUX",
                     SND_SOC_NOPM, 0, 0,
                     &hi6401_dapm_digmic_mux_controls),

    /* MIXERS */
    SND_SOC_DAPM_MIXER("EAR MIXER",
                       HI6401_MIXOUT_EAR_PD_REG,
                       HI6401_MIXOUT_EAR_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerout_ear_controls,
                       ARRAY_SIZE(hi6401_mixerout_ear_controls)),
    SND_SOC_DAPM_MIXER("HEADSETL MIXER",
                       SND_SOC_NOPM/*HI6401_MIXOUT_HSL_PD_REG*/,
                       HI6401_MIXOUT_HSL_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerout_hsl_controls,
                       ARRAY_SIZE(hi6401_mixerout_hsl_controls)),
    SND_SOC_DAPM_MIXER("HEADSETR MIXER",
                       SND_SOC_NOPM/*HI6401_MIXOUT_HSR_PD_REG*/,
                       HI6401_MIXOUT_HSR_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerout_hsr_controls,
                       ARRAY_SIZE(hi6401_mixerout_hsr_controls)),
    SND_SOC_DAPM_MIXER("ADCL MIXER",
                       HI6401_MIXINL_PD_REG,
                       HI6401_MIXINL_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerin_left_controls,
                       ARRAY_SIZE(hi6401_mixerin_left_controls)),
    SND_SOC_DAPM_MIXER("ADCR MIXER",
                       HI6401_MIXINR_PD_REG,
                       HI6401_MIXINR_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerin_right_controls,
                       ARRAY_SIZE(hi6401_mixerin_right_controls)),
    SND_SOC_DAPM_MIXER("LINEOUTL MIXER",
                       HI6401_MIXOUT_LINEOUTL_PD_REG,
                       HI6401_MIXOUT_LINEOUTL_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerout_lineoutl_controls,
                       ARRAY_SIZE(hi6401_mixerout_lineoutl_controls)),
    SND_SOC_DAPM_MIXER("LINEOUTR MIXER",
                       HI6401_MIXOUT_LINEOUTR_PD_REG,
                       HI6401_MIXOUT_LINEOUTR_PD_BIT,
                       1, /* INVERT */
                       hi6401_mixerout_lineoutr_controls,
                       ARRAY_SIZE(hi6401_mixerout_lineoutr_controls)),

    SND_SOC_DAPM_MIXER("S2L MIXER",
                       HI6401_MIXER_CLK_REG,
                       HI6401_S2_L_MIXER_EN_BIT,
                       0, /* INVERT */
                       hi6401_mixer_s2l_controls,
                       ARRAY_SIZE(hi6401_mixer_s2l_controls)),
    SND_SOC_DAPM_MIXER("S2R MIXER",
                       HI6401_MIXER_CLK_REG,
                       HI6401_S2_R_MIXER_EN_BIT,
                       0, /* INVERT */
                       hi6401_mixer_s2r_controls,
                       ARRAY_SIZE(hi6401_mixer_s2r_controls)),
    SND_SOC_DAPM_MIXER("S4L MIXER",
                       HI6401_MIXER_CLK_REG,
                       HI6401_S4_L_MIXER_EN_BIT,
                       0, /* INVERT */
                       hi6401_mixer_s4l_controls,
                       ARRAY_SIZE(hi6401_mixer_s4l_controls)),
    SND_SOC_DAPM_MIXER("S4R MIXER",
                       HI6401_MIXER_CLK_REG,
                       HI6401_S4_R_MIXER_EN_BIT,
                       0, /* INVERT */
                       hi6401_mixer_s4r_controls,
                       ARRAY_SIZE(hi6401_mixer_s4r_controls)),
    SND_SOC_DAPM_MIXER("DACL MIXER",
                       HI6401_MIXER_CLK_REG,
                       HI6401_DACL_MIXER_EN_BIT,
                       0, /* INVERT */
                       hi6401_mixer_dacl_controls,
                       ARRAY_SIZE(hi6401_mixer_dacl_controls)),
    SND_SOC_DAPM_MIXER("DACR MIXER",
                       HI6401_MIXER_CLK_REG,
                       HI6401_DACR_MIXER_EN_BIT,
                       0, /* INVERT */
                       hi6401_mixer_dacr_controls,
                       ARRAY_SIZE(hi6401_mixer_dacr_controls)),

    /* SWITCH */
    SND_SOC_DAPM_SWITCH_E("S1 OUT L",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_s1_outl_switch_controls,
                          hi6401_s1ol_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S1 OUT R",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_s1_outr_switch_controls,
                          hi6401_s1or_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S2 OUT L",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_S2_outl_switch_controls,
                          hi6401_s2ol_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S2 OUT R",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_S2_outr_switch_controls,
                          hi6401_s2or_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S3 OUT L",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_S3_outl_switch_controls,
                          hi6401_s3ol_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S3 OUT R",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_S3_outr_switch_controls,
                          hi6401_s3or_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S4 OUT L",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_S4_outl_switch_controls,
                          hi6401_s4ol_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
    SND_SOC_DAPM_SWITCH_E("S4 OUT R",
                          SND_SOC_NOPM, 0, 0,
                          &hi6401_dapm_S4_outr_switch_controls,
                          hi6401_s4or_power_mode_event,
                          SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

    SND_SOC_DAPM_SWITCH("DACV FILTER",
                        SND_SOC_NOPM, 0, 0,
                        &hi6401_dapm_dacv_filter_switch_controls),
    SND_SOC_DAPM_SWITCH("ADCL FILTER",
                        SND_SOC_NOPM, 0, 0,
                        &hi6401_dapm_adcl_filter_switch_controls),
    SND_SOC_DAPM_SWITCH("ADCR FILTER",
                        SND_SOC_NOPM, 0, 0,
                        &hi6401_dapm_adcr_filter_switch_controls),
};

static const struct snd_soc_dapm_route route_map[] = {

    {"S1 IL PGA",               NULL,                   "S1L IN"},
    {"S1 IR PGA",               NULL,                   "S1R IN"},
    {"S2 IL PGA",               NULL,                   "S2L IN"},
    {"S2 IR PGA",               NULL,                   "S2R IN"},
    {"S3 I PGA",                NULL,                   "S3 CHN MUX"},
    {"S4 I PGA",                NULL,                   "S4 CHN MUX"},

    {"S1 FIX PGA",              NULL,                   "S1 IL PGA"},
    {"S1 FIX PGA",              NULL,                   "S1 IR PGA"},

    {"S1L OUT",                 NULL,                   "S1 OUT L"},
    {"S1R OUT",                 NULL,                   "S1 OUT R"},
    {"S2L OUT",                 NULL,                   "S2 OUT L"},
    {"S2R OUT",                 NULL,                   "S2 OUT R"},
    {"S3L OUT",                 NULL,                   "S3 OUT L"},
    {"S3R OUT",                 NULL,                   "S3 OUT R"},
    {"S4L OUT",                 NULL,                   "S4 OUT L"},
    {"S4R OUT",                 NULL,                   "S4 OUT R"},

    {"S1 OUT L",                "SWITCH",               "AGCL MUX"},
    {"S1 OUT R",                "SWITCH",               "AGCR MUX"},
    {"S2 OUT L",                "SWITCH",               "S2L MIXER"},
    {"S2 OUT R",                "SWITCH",               "S2R MIXER"},
    {"S3 OUT L",                "SWITCH",               "UPLINKL MUX"},
    {"S3 OUT R",                "SWITCH",               "UPLINKR MUX"},
    {"S4 OUT L",                "SWITCH",               "S4L MUX"},
    {"S4 OUT R",                "SWITCH",               "S4R MUX"},

    {"DACL AGC",                NULL,                   "DACL MIXER"},
    {"DACR AGC",                NULL,                   "DACR MIXER"},

    {"DACV FILTER",             "SWITCH",               "DACV MUX"},
    {"ADCL FILTER",             "SWITCH",               "ADCL MUX"},
    {"ADCR FILTER",             "SWITCH",               "ADCR MUX"},

    {"DIGITAL DACL",            NULL,                   "DACL AGC"},
    {"DIGITAL DACR",            NULL,                   "DACR AGC"},
    {"DIGITAL DACV",            NULL,                   "DACV FILTER"},

    /*MUX*/
    {"S3 CHN MUX",              "LEFT",                 "S3 IN"},
    {"S3 CHN MUX",              "RIGHT",                "S3 IN"},
    {"S4 CHN MUX",              "LEFT",                 "S4 IN"},
    {"S4 CHN MUX",              "RIGHT",                "S4 IN"},

    {"DIGMIC MUX",              "OFF",                  "DIGMIC"},
    {"DIGMIC MUX",              "2FD",                  "DIGMIC"},
    {"DIGMIC MUX",              "3FD",                  "DIGMIC"},
    {"DIGMIC MUX",              "4FD",                  "DIGMIC"},

    {"AGCL MUX",                "ADCL",                 "ADCL FILTER"},
    {"AGCL MUX",                "ADCR",                 "ADCR FILTER"},
    {"AGCL MUX",                "S2L",                  "S2 IL PGA"},
    {"AGCL MUX",                "S2R",                  "S2 IR PGA"},
    {"AGCL MUX",                "S3MODEM",              "S3 I PGA"},
    {"AGCL MUX",                "S4MODEM",              "S4 I PGA"},

    {"AGCR MUX",                "ADCL",                 "ADCL FILTER"},
    {"AGCR MUX",                "ADCR",                 "ADCR FILTER"},
    {"AGCR MUX",                "S2L",                  "S2 IL PGA"},
    {"AGCR MUX",                "S2R",                  "S2 IR PGA"},
    {"AGCR MUX",                "S3MODEM",              "S3 I PGA"},
    {"AGCR MUX",                "S4MODEM",              "S4 I PGA"},

    {"DACV MUX",                "S3MODEM",              "S3 I PGA"},
    {"DACV MUX",                "S4MODEM",              "S4 I PGA"},

    {"UPLINKL MUX",             "S1L",                  "S1 IL PGA"},
    {"UPLINKL MUX",             "S1LR",                 "S1 FIX PGA"},
    {"UPLINKL MUX",             "S2L",                  "S2 IL PGA"},
    {"UPLINKL MUX",             "DACL",                 "DACL AGC"},
    {"UPLINKL MUX",             "ADCL",                 "ADCL FILTER"},
    {"UPLINKL MUX",             "S4MODEM",              "S4 I PGA"},

    {"UPLINKR MUX",             "S1R",                  "S1 IR PGA"},
    {"UPLINKR MUX",             "S1LR",                 "S1 FIX PGA"},
    {"UPLINKR MUX",             "S2R",                  "S2 IR PGA"},
    {"UPLINKR MUX",             "DACR",                 "DACR AGC"},
    {"UPLINKR MUX",             "ADCR",                 "ADCR FILTER"},
    {"UPLINKR MUX",             "S4MODEM",              "S4 I PGA"},

    {"S4L MUX",                 "UPLINKL",              "UPLINKL MUX"},
    {"S4L MUX",                 "S4MIXERL",             "S4L MIXER"},
    {"S4L MUX",                 "S4MIXERLR",            "S4L MIXER"},
    {"S4L MUX",                 "S4MIXERLR",            "S4R MIXER"},

    {"S4R MUX",                 "UPLINKR",              "UPLINKR MUX"},
    {"S4R MUX",                 "S4MIXERR",             "S4R MIXER"},
    {"S4R MUX",                 "S4MIXERLR",            "S4L MIXER"},
    {"S4R MUX",                 "S4MIXERLR",            "S4R MIXER"},

    {"ADCL MUX",                "ADC",                  "DIGITAL ADCL"},
    {"ADCL MUX",                "DACL",                 "DIGITAL DACL"},
    {"ADCL MUX",                "DACR",                 "DIGITAL DACR"},
    {"ADCL MUX",                "DACV",                 "DIGITAL DACV"},
    {"ADCL MUX",                "DMIC",                 "DIGMIC MUX"},

    {"ADCR MUX",                "ADC",                  "DIGITAL ADCR"},
    {"ADCR MUX",                "DACL",                 "DIGITAL DACL"},
    {"ADCR MUX",                "DACR",                 "DIGITAL DACR"},
    {"ADCR MUX",                "DACV",                 "DIGITAL DACV"},
    {"ADCR MUX",                "DMIC",                 "DIGMIC MUX"},

    /*MIXER*/
    {"S2L MIXER",               "DACL SWITCH",          "DACL AGC"},
    {"S2L MIXER",               "ADCL SWITCH",          "ADCL FILTER"},
    {"S2L MIXER",               "DACV SWITCH",          "DACV MUX"},
    {"S2L MIXER",               "S1LR SWITCH",          "S1 FIX PGA"},

    {"S2R MIXER",               "DACR SWITCH",          "DACR AGC"},
    {"S2R MIXER",               "ADCR SWITCH",          "ADCR FILTER"},
    {"S2R MIXER",               "DACV SWITCH",          "DACV MUX"},
    {"S2R MIXER",               "S1LR SWITCH",          "S1 FIX PGA"},

    {"S4L MIXER",               "DACL SWITCH",          "DACL AGC"},
    {"S4L MIXER",               "ADCL SWITCH",          "ADCL FILTER"},
    {"S4L MIXER",               "DACV SWITCH",          "DACV MUX"},
    {"S4L MIXER",               "S1LR SWITCH",          "S1 FIX PGA"},

    {"S4R MIXER",               "DACR SWITCH",          "DACR AGC"},
    {"S4R MIXER",               "ADCR SWITCH",          "ADCR FILTER"},
    {"S4R MIXER",               "DACV SWITCH",          "DACV MUX"},
    {"S4R MIXER",               "S1LR SWITCH",          "S1 FIX PGA"},

    {"DACL MIXER",              "S1L SWITCH",           "S1 IL PGA"},
    {"DACL MIXER",              "S2L SWITCH",           "S2 IL PGA"},

    {"DACR MIXER",              "S1R SWITCH",           "S1 IR PGA"},
    {"DACR MIXER",              "S2R SWITCH",           "S2 IR PGA"},

    /* CLOCK SUPPLY */
    {"S1L IN",                  NULL,                   "S1 RX CLK"},
    {"S1R IN",                  NULL,                   "S1 RX CLK"},
    {"S1L OUT",                 NULL,                   "S1 TX CLK"},
    {"S1R OUT",                 NULL,                   "S1 TX CLK"},
    {"S1 TX CLK",               NULL,                   "S1 INTERFACE CLK"},
    {"S1 RX CLK",               NULL,                   "S1 INTERFACE CLK"},

    {"S2L IN",                  NULL,                   "S2 RX CLK"},
    {"S2R IN",                  NULL,                   "S2 RX CLK"},
    {"S2L OUT",                 NULL,                   "S2 TX CLK"},
    {"S2R OUT",                 NULL,                   "S2 TX CLK"},
    {"S2 TX CLK",               NULL,                   "S2 INTERFACE CLK"},
    {"S2 RX CLK",               NULL,                   "S2 INTERFACE CLK"},

    {"S3 IN",                   NULL,                   "S3 RX CLK"},
    {"S3L OUT",                 NULL,                   "S3 TX CLKV"},
    {"S3R OUT",                 NULL,                   "S3 TX CLK"},
    {"S3 TX CLKV",              NULL,                   "S3 INTERFACE CLK"},
    {"S3 TX CLK",               NULL,                   "S3 INTERFACE CLK"},
    {"S3 RX CLK",               NULL,                   "S3 INTERFACE CLK"},

    {"S4 IN",                   NULL,                   "S4 RX CLK"},
    {"S4L OUT",                 NULL,                   "S4 TX CLK"},
    {"S4R OUT",                 NULL,                   "S4 TX CLK"},
    {"S4 TX CLK",               NULL,                   "S4 INTERFACE CLK"},
    {"S4 RX CLK",               NULL,                   "S4 INTERFACE CLK"},

    {"S1 INTERFACE CLK",        NULL,                   "PLL CLK"},
    {"S2 INTERFACE CLK",        NULL,                   "PLL CLK"},
    {"S3 INTERFACE CLK",        NULL,                   "PLL CLK"},
    {"S4 INTERFACE CLK",        NULL,                   "PLL CLK"},
    {"PLL CLK",                 NULL,                   "IBIAS"},

    /*ADC*/
    {"ANALOG ADCL",             NULL,                   "ADC L"},
    {"ANALOG ADCR",             NULL,                   "ADC R"},

    /* DAC */
    {"DACL",                    NULL,                   "ANALOG DACL"},
    {"DACR",                    NULL,                   "ANALOG DACR"},
    {"DACV",                    NULL,                   "ANALOG DACV"},

    {"LINEINL PGA",             NULL,                   "LINEINL"},
    {"LINEINR PGA",             NULL,                   "LINEINR"},

    /* MIXER */
    {"EAR MIXER",               "DACL SWITCH",          "DACL"},
    {"EAR MIXER",               "DACR SWITCH",          "DACR"},
    {"EAR MIXER",               "DACV SWITCH",          "DACV"},
    {"EAR MIXER",               "LIL SWITCH",           "LINEINL PGA"},
    {"EAR MIXER",               "LIR SWITCH",           "LINEINR PGA"},
    {"EAR MIXER",               "SIDETONE SWITCH",      "SIDETONE PGA"},

    {"HEADSETL MIXER",          "DACL SWITCH",          "DACL"},
    {"HEADSETL MIXER",          "DACR SWITCH",          "DACR"},
    {"HEADSETL MIXER",          "DACV SWITCH",          "DACV"},
    {"HEADSETL MIXER",          "LIL SWITCH",           "LINEINL PGA"},
    {"HEADSETL MIXER",          "LIR SWITCH",           "LINEINR PGA"},
    {"HEADSETL MIXER",          "SIDETONE SWITCH",      "SIDETONE PGA"},

    {"HEADSETR MIXER",          "DACL SWITCH",          "DACL"},
    {"HEADSETR MIXER",          "DACR SWITCH",          "DACR"},
    {"HEADSETR MIXER",          "DACV SWITCH",          "DACV"},
    {"HEADSETR MIXER",          "LIL SWITCH",           "LINEINL PGA"},
    {"HEADSETR MIXER",          "LIR SWITCH",           "LINEINR PGA"},
    {"HEADSETR MIXER",          "SIDETONE SWITCH",      "SIDETONE PGA"},

    {"LINEOUTL MIXER",          "DACL SWITCH",          "DACL"},
    {"LINEOUTL MIXER",          "DACR SWITCH",          "DACR"},
    {"LINEOUTL MIXER",          "DACV SWITCH",          "DACV"},
    {"LINEOUTL MIXER",          "LIL SWITCH",           "LINEINL PGA"},
    {"LINEOUTL MIXER",          "LIR SWITCH",           "LINEINR PGA"},
    {"LINEOUTL MIXER",          "SIDETONE SWITCH",      "SIDETONE PGA"},

    {"LINEOUTR MIXER",          "DACL SWITCH",          "DACL"},
    {"LINEOUTR MIXER",          "DACR SWITCH",          "DACR"},
    {"LINEOUTR MIXER",          "DACV SWITCH",          "DACV"},
    {"LINEOUTR MIXER",          "LIL SWITCH",           "LINEINL PGA"},
    {"LINEOUTR MIXER",          "LIR SWITCH",           "LINEINR PGA"},
    {"LINEOUTR MIXER",          "SIDETONE SWITCH",      "SIDETONE PGA"},

    {"ADCL MIXER",              "DACL SWITCH",          "DACL"},
    {"ADCL MIXER",              "DACR SWITCH",          "DACR"},
    {"ADCL MIXER",              "DACV SWITCH",          "DACV"},
    {"ADCL MIXER",              "LIL SWITCH",           "LINEINL PGA"},
    {"ADCL MIXER",              "LIR SWITCH",           "LINEINR PGA"},
    {"ADCL MIXER",              "MAINMIC SWITCH",       "MAINMIC PGA"},
    {"ADCL MIXER",              "SUBMIC SWITCH",        "SUBMIC PGA" },

    {"ADCR MIXER",              "DACL SWITCH",          "DACL"},
    {"ADCR MIXER",              "DACR SWITCH",          "DACR"},
    {"ADCR MIXER",              "DACV SWITCH",          "DACV"},
    {"ADCR MIXER",              "LIL SWITCH",           "LINEINL PGA"},
    {"ADCR MIXER",              "LIR SWITCH",           "LINEINR PGA"},
    {"ADCR MIXER",              "MAINMIC SWITCH",       "MAINMIC PGA"},
    {"ADCR MIXER",              "SUBMIC SWITCH",        "SUBMIC PGA" },

    /* MICBIAS */
    {"MAIN MICBIAS",            NULL,                   "MAIN MIC"},
    {"MAINMIC",                 NULL,                   "MAIN MICBIAS"},
    {"SUB MICBIAS",             NULL,                   "SUB MIC"},
    {"SUBMIC",                  NULL,                   "SUB MICBIAS"},
    /* headset always poweron micbias */
    {"HSMIC",                   NULL,                   "HS MIC"},

    /* MUX */
    //{"MIC MUX",               "MIC OFF",              NULL},
    {"MIC MUX",                 "MIC MAIN",             "MAINMIC"},
    {"MIC MUX",                 "MIC HS",               "HSMIC"},

    {"MAINMIC PGA",             NULL,                   "MIC MUX"},
    {"SUBMIC PGA",              NULL,                   "SUBMIC"},
    {"SIDETONE PGA",            NULL,                   "MAINMIC PGA"},

    {"EARPIECE PGA",            NULL,                   "EAR MIXER"},
    {"HEADSETL PGA",            NULL,                   "HEADSETL MIXER"},
    {"HEADSETR PGA",            NULL,                   "HEADSETR MIXER"},
    {"LINEOUTL PGA",            NULL,                   "LINEOUTL MIXER"},
    {"LINEOUTR PGA",            NULL,                   "LINEOUTR MIXER"},

    /* OUTPUT */
    {"OUT EAR",                 NULL,                   "EARPIECE PGA"},
    {"OUT HSL",                 NULL,                   "HEADSETL PGA"},
    {"OUT HSR",                 NULL,                   "HEADSETR PGA"},
    {"LINEOUT L",               NULL,                   "LINEOUTL PGA"},
    {"LINEOUT R",               NULL,                   "LINEOUTR PGA"},
    {"ADC L",                   NULL,                   "ADCL MIXER"},
    {"ADC R",                   NULL,                   "ADCR MIXER"},

    /* IBIAS SUPPLY */
    {"EAR MIXER",               NULL,                   "IBIAS"},
    {"HEADSETL MIXER",          NULL,                   "IBIAS"},
    {"HEADSETR MIXER",          NULL,                   "IBIAS"},
    {"ADCL MIXER",              NULL,                   "IBIAS"},
    {"ADCR MIXER",              NULL,                   "IBIAS"},
    {"LINEOUTL MIXER",          NULL,                   "IBIAS"},
    {"LINEOUTR MIXER",          NULL,                   "IBIAS"},

};

static int hi6401_add_widgets(struct snd_soc_codec *codec)
{
    snd_soc_add_controls(codec, hi6401_snd_controls,
            ARRAY_SIZE(hi6401_snd_controls));
    snd_soc_dapm_new_controls(&codec->dapm, hi6401_dapm_widgets,
            ARRAY_SIZE(hi6401_dapm_widgets));
    snd_soc_dapm_add_routes(&codec->dapm, route_map,
            ARRAY_SIZE(route_map));

    snd_soc_dapm_new_widgets(&codec->dapm);

    return 0;
}

static inline bool pll_clock_validate(void)
{
    //19.2M
    return true;
}


/* INIT REGISTER VALUE FROM ARRAY */
static void init_reg_value(struct snd_soc_codec *codec)
{
    /*
    1. PLL config
    2. charge pump
    3. zero cross  配置检测时间
    4. vref i
    5. sradc  800mV 80% (apu ver.e /....)
    */
    int ret = 0;
    unsigned int comph_val;

    ret = get_hw_config_int("audio/comph_val", &comph_val, NULL);
    if(false == ret) {
        printk(KERN_ERR "Error : comph_val not found !\n");
        return;
    }
    hi6401_reg_write(codec, HI6401_MIXOUT_EAR, 0x0);
    hi6401_reg_write(codec, HI6401_MIXOUT_HSL, 0x0);
    hi6401_reg_write(codec, HI6401_MIXOUT_HSR, 0x0);
    hi6401_reg_write(codec, HI6401_MIXOUT_LINEOUTL, 0x0);
    hi6401_reg_write(codec, HI6401_MIXOUT_LINEOUTR, 0x0);
    hi6401_reg_write(codec, HI6401_MIXINL, 0x0);
    hi6401_reg_write(codec, HI6401_MIXINR, 0x0);

    hi6401_reg_write(codec,HI6401_IBIAS_PD_REG, 0x39);/*config fast powerup*/
    msleep(20); /*waite power ready*/

    //hi6401_reg_write(codec,HI6401_DAC_PLL_PD,0xFE);
    //msleep(5);/*wait pll power Ok*/

    if (pll_clock_validate()) {
        hi6401_reg_write(codec, HI6401_PLL_FCW_0, HI6401_PLL_FCW_0_19M2);
        hi6401_reg_write(codec, HI6401_PLL_FCW_1, HI6401_PLL_FCW_1_19M2);
        hi6401_reg_write(codec, HI6401_PLL_FCW_2, HI6401_PLL_FCW_2_19M2);
    } else {
        hi6401_reg_write(codec, HI6401_PLL_FCW_0, HI6401_PLL_FCW_0_26M);
        hi6401_reg_write(codec, HI6401_PLL_FCW_1, HI6401_PLL_FCW_1_26M);
        hi6401_reg_write(codec, HI6401_PLL_FCW_2, HI6401_PLL_FCW_2_26M);
    }

    //hi6401_reg_write(codec, HI6401_PLL_EN_REG, HI6401_PLL_EN_VALUE);
    //msleep(1);/*ensure pll enable OK*/
    //pr_info("pll state : ----%#04x\n",hi6401_reg_read(g_codec, HI6401_LOR_GAIN_DONE));

    hi6401_reg_write(codec,HI6401_MICBIAS_ECO_EN, 0x86);
    hi6401_reg_write(codec,HI6401_IBIAS_PD_REG, HI6401_IBIAS_VALUE);/*restore normal powerup for power saving*/
    hi6401_reg_write(codec, HI6401_MICBIAS1_HSMICB_SEL, 0x36);/*config micbias vref*/
    hi6401_reg_write(codec, HI6401_DEB_0, 0x50);/*config qudou 20ms*/
    hi6401_reg_write(codec, HI6401_DEB_1, 0x14);/*config key qudou 20ms*/
    hi6401_reg_write(codec, HI6401_POP_CTRL1, 0xE1);
    hi6401_reg_write(codec, HI6401_POP_CTRL2, 0x6C);

    #if 0/*used for minize pop sound when plugging*/
    hi6401_reg_write(codec,HI6401_HSLPGA_REG,0xB9);
    hi6401_reg_write(codec,HI6401_HSRPGA_REG,0xB9);
    #endif
    hi6401_reg_write(codec, HI6401_ADC_PD, 0x7F);/*pd main mic pga*/
    hi6401_reg_write(codec, HI6401_MBHD_VREF_CTRL, comph_val);/*config compl threhold*/
    hi6401_reg_write(codec, HI6401_HSLPGA_REG, 0x01);
    hi6401_reg_write(codec, HI6401_HSRPGA_REG, 0x01);
    hi6401_reg_write(codec, HI6401_CHOPPER_SEL, 0x6C); /*charge pump*/

}


#ifdef __DRV_DUMP__
#define HI6401_PAGE_0_START         (BASE_ADDR_PAGE_0 + 0x1b0)
#define HI6401_PAGE_0_END           (BASE_ADDR_PAGE_0 + 0x1ff)
#define HI6401_PAGE_1_START         (BASE_ADDR_PAGE_1 + 0x1b0)
#define HI6401_PAGE_1_END           (BASE_ADDR_PAGE_1 + 0x1ff)
void _reg_dp(void)
{
    unsigned int i = 0;

    /* page 0 */
    logi("===========hi6401 Page 0 start ===========");
    for (i = HI6401_PAGE_0_START; i <= HI6401_PAGE_0_END; i++)
        logi("%#04x : %#04x", i, hi6401_reg_read(g_codec, i));
    logi("===========hi6401 Page 0 end ===========");

    /* page 1 */
    logi("===========hi6401 Page 1 start ===========");
    for (i = HI6401_PAGE_1_START; i <= HI6401_PAGE_1_END; i++)
        logi("%#04x : %#04x", i, hi6401_reg_read(g_codec, i));
    logi("===========hi6401 Page 1 end ===========");
}

#endif

static int hi6401_startup(struct snd_pcm_substream *substream,
                          struct snd_soc_dai *dai)
{
    struct hi6401_priv *priv = NULL;
    logi(">>> hi6401_startup! <<<\n");
    if (NULL != g_codec)
    {
        logi(">>> CHECK PLL! <<<\n");
        priv = snd_soc_codec_get_drvdata(g_codec);
        if (!priv)
        {
            printk(KERN_ERR "priv is null pointer\n");
            return -1;
        }
        queue_delayed_work(priv->recover_wq,
                       &priv->pll_recover_work,
                       msecs_to_jiffies(40));
    }
    return 0;
}

static void hi6401_shutdown(struct snd_pcm_substream *substream,
                            struct snd_soc_dai *dai)
{
     /*TODO*/
}

static int hi6401_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
    /*TODO*/
    return 0;
}

/*add hs plug */

static inline int read_saradc_value(struct snd_soc_codec *codec)
{
    int ret = 0;
    int i = 0;
    struct  hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return -1;
    }
    snd_soc_write(codec, HI6401_SARADC_VREF_SEL, 0x06);
    snd_soc_write(codec, HI6401_SARADC_CTRL, 0xCE);
    snd_soc_write(codec, HI6401_SARADC_CTRL, 0xEE);

    for (i = 0; i < 3; i++) {
        if ( IRQ_SARADC_READ & snd_soc_read(codec, HI6401_ANA_IRQ_0)) {
            snd_soc_write(codec, HI6401_ANA_IRQ_0, IRQ_SARADC_READ);
            priv->saradc_value = (int)(snd_soc_read(codec, HI6401_SAR_DATA)) * SAR_REF / 256;
            logd("saradc value is %d", priv->saradc_value);
            break;
        }
        msleep(1);
    }
    snd_soc_write(codec, HI6401_SARADC_VREF_SEL, 0x07);

    if (3 == i) {
        /*timeout*/
        loge("waiting for saradc read intr timeout!");
        ret = -1;
    }

    return ret;
}
static void hi6401_timeout_timer(unsigned long data)
{
    /* if codec is on, never enter eco mode */
    struct hi6401_priv *priv;

    priv = (struct hi6401_priv *)data;
    if (hi6401_ibias_enabled > 0) {
        return;
    }
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return;
    }
    schedule_delayed_work(&priv->low_power_work, 0);
}
static void hi6401_enter_eco_mode(struct work_struct *work)
{
    struct hi6401_priv *priv =
            container_of(work, struct hi6401_priv, low_power_work.work);

    int ret = 0;
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return;
    }

    down(&priv->state_sema);
    if ( eco_mode  == priv->work_mode ){
        logi("already in eco mode\n");
        goto out;
    }
    if (hi6401_ibias_enabled) {
        logi("ibias is enabled just return\n");
        goto out;
    }
    __hi6401_reg_write(g_codec,HI6401_DAC_PLL_PD,0xFF);/* pll power off */

    if ((HI6401_JACK_BIT_HEADPHONE == priv->hs_status) || (HI6401_JACK_BIT_NONE == priv->hs_status)){
        __hi6401_reg_write(g_codec, HI6401_ANA_IRQ_0, 0x0F);
    }
    else{
        priv->__set_reg_bits(HI6401_ANA_IRQM_0, IRQ_ECO_BTN_DOWN | IRQ_ECO_BTN_UP  |IRQ_BTN_DOWN | IRQ_BTN_UP);
        priv->__set_reg_bits(HI6401_HSMICB_PD_REG, 0x1 << HI6401_HSMICB_PD_BIT);
        priv->__set_reg_bits(HI6401_MICBIAS_ECO_EN, 0x1 << HI6401_HSMICB_DSCHG_BIT);
        mdelay(5);
        priv->__clr_reg_bits(HI6401_MICBIAS_ECO_EN, 0x1 << HI6401_HSMICB_DSCHG_BIT);
        priv->__set_reg_bits(HI6401_MICBIAS_ECO_EN, 0x1 << HI6401_MBHD_ECO_EN_BIT);
        mdelay(25);
        __hi6401_reg_write(g_codec, HI6401_ANA_IRQ_0, 0x0F);
        priv->__clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_ECO_BTN_DOWN | IRQ_ECO_BTN_UP);
    }
   #ifdef CONFIG_MACH_HI6620OEM

    ret = blockmux_set(priv->piomux_block, priv->pblock_config, LOWPOWER);
    if (ret != 0)
    {
        printk(KERN_ERR "blockmux_set fail\n");
        goto out;
    }
    #endif
    __hi6401_reg_write(g_codec,HI6401_IBIAS_PD_REG, 0x0B);

    priv->work_mode = eco_mode;
    logi("entering eco mode\n");

out:
    up(&priv->state_sema);
    return;
}

static int hi6401_exit_eco_mode(struct snd_soc_codec *codec)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    unsigned int irq_raw = 0;
    int ret = 0;
    int i  = 0;
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return -1;
    }
    logd("Begin\n");

    if ( normal_mode  == priv->work_mode ){
        logi("already in normal mode\n");
        ret = -1;
        goto out;
    }

    #ifdef CONFIG_MACH_HI6620OEM
    ret = blockmux_set(priv->piomux_block, priv->pblock_config, NORMAL);
    if (ret != 0)
    {
        printk(KERN_ERR "blockmux_set fail\n");
        goto out;
    }
    #endif

    if ( quick_mode != priv->work_mode ){

        __hi6401_reg_write(codec,HI6401_IBIAS_PD_REG, 0x39); /* cost 90ms ! */
        msleep(10);
        for (i = 0;i < 3; i++){
            if (g_codec_version == __hi6401_reg_read(codec, HI6401_VERSION)){
                break;
            }
            msleep(10);
        }
        if (3 == i) {
            loge("timeout for entering normal  mode\n");
            ret = -1;
            goto out;
        }
        __hi6401_reg_write(codec,HI6401_IBIAS_PD_REG, 0x19);
    } else {
        logd("in quick mode\n");
        /* do nothing */
    }

    if ((HI6401_JACK_BIT_HEADPHONE == priv->hs_status) || (HI6401_JACK_BIT_NONE == priv->hs_status)){
        __hi6401_reg_write(codec, HI6401_ANA_IRQ_0, 0x0F);
    }
    else{
        priv->__set_reg_bits(HI6401_ANA_IRQM_0, IRQ_ECO_BTN_DOWN | IRQ_ECO_BTN_UP | IRQ_BTN_DOWN | IRQ_BTN_UP);

        irq_raw = __hi6401_reg_read(codec, HI6401_ANA_IRQ_0);
        logd("irq before switch 0x%x", irq_raw);
        priv->__clr_reg_bits(HI6401_HSMICB_PD_REG, 0x1 << HI6401_HSMICB_PD_BIT);
        priv->__clr_reg_bits(HI6401_MICBIAS_ECO_EN, 0x1 << HI6401_MBHD_ECO_EN_BIT);

        msleep(15);
        logd("irq after switch 0x%x", __hi6401_reg_read(codec, HI6401_ANA_IRQ_0));
        if (__hi6401_reg_read(g_codec, HI6401_ANA_IRQ_0) & (IRQ_PLUG_IN | IRQ_PLUG_OUT)){
            __hi6401_reg_write(codec, HI6401_ANA_IRQ_0, 0x0F);
        } else {
            /* hsmicbias switch trigger button irq by mistake, save and restore to clear it */
            __hi6401_reg_write(codec, HI6401_ANA_IRQ_0, ~irq_raw);
        }
        priv->__clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_BTN_DOWN | IRQ_BTN_UP);

    }
    ret = 1;
    priv->work_mode = normal_mode;
    logi("entering normal  mode\n");


out:
    return ret;
}

static irqreturn_t hi6401_irq_handler (int irq, void *data)
{
    struct  snd_soc_codec *codec = data;
    struct  hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    struct hi6401_codec_platform_data *pdata = dev_get_platdata(codec->dev);
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return IRQ_NONE;
    }
    logd(">>> irq handler enter! <<<\n");

    disable_irq_nosync(gpio_to_irq(pdata->gpio_intr));

    /* because of eco mode, mutex cannot be used in interrupt context, we can do nothing in irq_handler */
    queue_work(priv->hs_wq, &priv->hs_work);

    return IRQ_HANDLED;
}

static void hi6401_pll_work_func(struct work_struct *work)
{
    int loop = 0;
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);

    logi("hi6401_pll_work_func\n");

    if (NULL == priv) {
        loge("hi6401 priv is NULL\n");
        return;
    }

    if (eco_mode == priv->work_mode){
        hi6401_power_up(g_codec, priv);
    }

    while(1) {
        /* check pll is ok or not */
        if (!(hi6401_reg_read(g_codec, HI6401_LOR_GAIN_DONE) & 0x01)){
            logi("hi6401_pll_reset enter\n");
            hi6401_reg_write(g_codec, HI6401_PLL_EN_REG, 0x5F);
            msleep(2);
            priv->set_reg_bits(HI6401_DAC_PLL_PD, 0x1);
            msleep(2);
            priv->clr_reg_bits(HI6401_DAC_PLL_PD, 0x1);
            msleep(2);
            hi6401_reg_write(g_codec, HI6401_PLL_EN_REG, HI6401_PLL_EN_VALUE);
            logi("hi6401_pll_reset exit\n");
        }
        else {
            break;
        }

        if (loop++ > 10) {
            break;
        }
        msleep(40);
    }

    logi("hi6401_pll_work_func exit\n");
}

static void hi6401_pdstat_work_func(struct work_struct *work)
{
}

static int hs_plug_in_detect_func(struct snd_soc_codec *codec)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    int retries = 0;
    int ret = 0;
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return -1;
    }
    /* check status */
    if (priv->hs_status == HI6401_JACK_BIT_NONE) {
        snd_soc_write(codec, HI6401_ANA_IRQ_0, IRQ_PLUG_IN);
        priv->clr_reg_bits(HI6401_MICBIAS_ECO_EN, 0x1 << HI6401_HSMICB_DSCHG_BIT);
        priv->clr_reg_bits(HI6401_HSMICB_PD_REG, 0x1 << HI6401_HSMICB_PD_BIT);
        priv->clr_reg_bits(HI6401_MBHD_VREF_CTRL, 0x1 << HI6401_MBHD_VREF_CTRL_EN_BIT);
        msleep(150);
    }
    else {
        priv->clr_reg_bits(HI6401_HSMICB_PD_REG, 0x1 << HI6401_HSMICB_PD_BIT);
        snd_soc_write(codec, HI6401_ANA_IRQ_0, (snd_soc_read(codec,HI6401_ANA_IRQ_0) & (0x0F)));
    }

    ret = read_saradc_value(codec);

    if ( (priv->saradc_value > priv->headset_voltage->hs_3_pole_max_voltage) && ( priv->saradc_value < priv->headset_voltage->hs_eco_voltage) ) {
        logi("saradc_value is between 20 to 180 cycle check\n"); /*slow plug in */
        snd_soc_write(codec, HI6401_ANA_IRQ_0, 0x0F);
        do {
            msleep(20);
            ret = read_saradc_value(codec);

            if (!(IRQ_PLUG_OUT_STATUS & snd_soc_read(codec,HI6401_IRQ_SOURCE_STAT))){ /*in this case plug in is not realized*/
                hs_plug_out_detect_func(codec);
                logi("\n plug out happens \n");
                return ret;
            }
        } while ( ((priv->saradc_value > priv->headset_voltage->hs_3_pole_max_voltage) && ( priv->saradc_value < priv->headset_voltage->hs_eco_voltage)) &&
                (++retries < priv->saradc_retries) );

        /*
        if retries>=priv->retries, treat HS as reserve 4 pole, goto else
        */
        logi("cycle end, saradc_value is %d (retries=%d)", priv->saradc_value, retries);
    }

    retries = 0;
    /* check transition value of 4 pole and 3 pole */
    if ((priv->saradc_value > priv->headset_voltage->hs_4_pole_max_voltage/*4 pole*/) ||
        ((priv->saradc_value > priv->headset_voltage->hs_eco_voltage) && (priv->saradc_value < priv->headset_voltage->hs_4_pole_min_voltage)/*3 pole*/)) {
        do {
            msleep(5);
            ret = read_saradc_value(codec);

            if (!(IRQ_PLUG_OUT_STATUS & snd_soc_read(codec,HI6401_IRQ_SOURCE_STAT))){ /*in this case plug in is not realized*/
                hs_plug_out_detect_func(codec);
                logi("\n plug out happens \n");
                return ret;
            }
        } while (((priv->saradc_value > priv->headset_voltage->hs_4_pole_max_voltage/*4 pole*/) ||
            ((priv->saradc_value > priv->headset_voltage->hs_eco_voltage) && (priv->saradc_value < priv->headset_voltage->hs_4_pole_min_voltage)/*3 pole*/)) &&
            (++retries < HI6401_SARADC_BOOTING_RETRIES));

        logi("short cycle end, saradc_value=%d (retries=%d)", priv->saradc_value, retries);
    }

    if ((priv->saradc_value <= priv->headset_voltage->hs_3_pole_max_voltage) && (!(priv->pole_flag))) {
        /* 3-pole or reverse 4-pole*/
        priv->hs_jack->report = SND_JACK_HEADPHONE;

        if (HI6401_JACK_BIT_HEADSET_NO_MIC == priv->hs_status ){/*second check*/
            snd_soc_write(codec, HI6401_ANA_IRQ_0, 0x0F);
            priv->set_reg_bits(HI6401_ANA_IRQM_0, IRQ_BTN_DOWN | IRQ_BTN_UP | IRQ_ECO_BTN_DOWN | IRQ_ECO_BTN_UP);
        }

        priv->hs_status = HI6401_JACK_BIT_HEADPHONE;

        priv->set_reg_bits(HI6401_HSMICB_PD_REG, 0x1<<HI6401_HSMICB_PD_BIT);
        priv->set_reg_bits(HI6401_MBHD_VREF_CTRL, 0x1<<HI6401_MBHD_VREF_CTRL_EN_BIT);

        logi("headphone is 3 pole, saradc=%d\n", priv->saradc_value);
    }
    else if ((priv->saradc_value > priv->headset_voltage->hs_4_pole_min_voltage) && (priv->saradc_value < priv->headset_voltage->hs_4_pole_max_voltage) ) {
        /*4-pole*/
        priv->hs_status = HI6401_JACK_BIT_HEADSET;
        priv->hs_jack->report = SND_JACK_HEADSET;
        snd_soc_write(codec, HI6401_ANA_IRQ_0, 0x0F);
        priv->set_reg_bits(HI6401_ANA_IRQM_0, IRQ_ECO_BTN_DOWN | IRQ_ECO_BTN_UP);
        priv->clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_BTN_DOWN | IRQ_BTN_UP);
        priv->pole_flag = 1;

        logi("headphone is 4 pole, saradc=%d\n", priv->saradc_value);
    }
    else {
        /* other second check */
        priv->hs_jack->report = SND_JACK_HEADPHONE;
        priv->hs_status = HI6401_JACK_BIT_HEADSET_NO_MIC;

        snd_soc_write(codec, HI6401_ANA_IRQ_0, 0x0F);
        priv->clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_BTN_DOWN | IRQ_BTN_UP | IRQ_ECO_BTN_DOWN | IRQ_ECO_BTN_UP);/*eco irq can be used for 3-pole slow in  */
        logi("headphone is set reserve 4 pole temparily second check, saradc=%d\n", priv->saradc_value);
    }

    /*判断耳机类型不为空*/
    if ((HI6401_JACK_BIT_NONE != priv->hs_status) && (priv->hs_status != priv->old_hs_status)) {

        priv->clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_PLUG_OUT);
        priv->set_reg_bits(HI6401_ANA_IRQM_0, IRQ_PLUG_IN);
        hi6401_clr_reg_bits(HI6401_CP_PD_REG, 0x1 << HI6401_CP_PD_BIT);
        priv->old_hs_status = priv->hs_status;


        if (priv->hs_status != switch_get_state(&priv->hs_jack->sdev)) {
            if (HI6401_HS_WITH_MIC == priv->hs_status) {
                logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
                snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report, SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2);
            }
            else{
                logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
                snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report, SND_JACK_HEADSET);
            }
        }
            switch_set_state(&priv->hs_jack->sdev, priv->hs_status);
    }else {
        loge("hs status=%d(old=%d) not recognized!", priv->hs_status, priv->old_hs_status);
        ret = -1;
    }
    snd_soc_write(codec, HI6401_ANA_IRQ_0, 0x7F);

    if (!(IRQ_PLUG_OUT_STATUS & snd_soc_read(codec,HI6401_IRQ_SOURCE_STAT))){ /*in this case plug in is not realized*/
        hs_plug_out_detect_func(codec);
        logi("\n plug out happens \n");
        return ret;
    }

    return ret;
}

static int  hs_plug_out_detect_func(struct snd_soc_codec *codec)
{

    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    int ret = 0;
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return -1;
    }
    if (priv->hs_status == HI6401_JACK_BIT_NONE) {
        loge("Error, NO HS IN BUT PLUG OUT INTR HAPPENS!");
    }

    priv->hs_status = HI6401_JACK_BIT_NONE;
    priv->old_hs_status = HI6401_JACK_BIT_INVALID;
    priv->hs_jack->report = 0;
    priv->pole_flag = 0;

    priv->set_reg_bits(HI6401_ANA_IRQM_0, 0xFF);
    priv->clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_PLUG_IN);

    priv->set_reg_bits(HI6401_HSMICB_PD_REG, 0x1 << HI6401_HSMICB_PD_BIT);
    priv->set_reg_bits(HI6401_MBHD_VREF_CTRL, 0x1 << HI6401_MBHD_VREF_CTRL_EN_BIT);
    hi6401_set_reg_bits(HI6401_CP_PD_REG, 0x1 << HI6401_CP_PD_BIT);
    priv->set_reg_bits(HI6401_MICBIAS_ECO_EN, 0x1 << HI6401_HSMICB_DSCHG_BIT);
    snd_soc_write(codec, HI6401_ANA_IRQ_0, 0x6F);

    logi("hs_status = %d\n", priv->hs_status);

    /*report info */
    if (priv->hs_status != switch_get_state(&priv->hs_jack->sdev)) {
        logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
        snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report, SND_JACK_HEADSET);
        switch_set_state(&priv->hs_jack->sdev, priv->hs_status);
    }

    return ret;
}

static int hs_btn_detect_func(struct snd_soc_codec *codec)
{
    int ret = 0;

    static int pressed_btn_type = 0;
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(codec);
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return -1;
    }
    /* irq cleared in hs_work */
    snd_soc_write(codec, HI6401_ANA_IRQ_0, (IRQ_ECO_BTN_UP | IRQ_ECO_BTN_DOWN));

    if (HI6401_JACK_BIT_HEADSET & priv->hs_status) {
        /* read saradc as early as possible, we read at begin of hs_work_func
           ret = read_saradc_value(codec);
        */
        logd("pressed_btn_type=0x%x, saradc=%d", pressed_btn_type, priv->saradc_value);
      } else {
        loge("Error non-4 pole hs but btn intr happens, stat=%d\n", priv->hs_status);
      }

      /*if (-1 == ret) {
        ret = -1;
      } else {*/

    /*judge key type*/
        if ( (priv->saradc_value > priv->btn_voltage->key_up_min_value) && (priv->saradc_value <= priv->btn_voltage->key_up_max_value) && (pressed_btn_type)){
            priv->hs_jack->jack->jack->type = pressed_btn_type;
            priv->hs_jack->report &= ~(SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2);
            pressed_btn_type = 0;
            logi("key up happens, saradc value is %d",priv->saradc_value);
        } else if ((priv->saradc_value >= priv->btn_voltage->key_play_min_value) && (priv->saradc_value <= priv->btn_voltage->key_play_max_value) && (!pressed_btn_type)) {
            priv->hs_jack->jack->jack->type = SND_JACK_BTN_0;
            priv->hs_jack->report |= SND_JACK_BTN_0;
            pressed_btn_type = SND_JACK_BTN_0;
            logi("key1 play down, saradc value is %d",priv->saradc_value);
        } else if ((priv->saradc_value >= priv->btn_voltage->key_forward_min_value) && (priv->saradc_value <= priv->btn_voltage->key_forward_max_value) && (!pressed_btn_type)) {
            priv->hs_jack->jack->jack->type = SND_JACK_BTN_1;
            priv->hs_jack->report |= SND_JACK_BTN_1;
            pressed_btn_type = SND_JACK_BTN_1;
            logi("key 2 forward down, saradc value is %d",priv->saradc_value);
        } else if ((priv->saradc_value >= priv->btn_voltage->key_back_min_value) && (priv->saradc_value <= priv->btn_voltage->key_back_max_value) && (!pressed_btn_type)) {
            priv->hs_jack->jack->jack->type = SND_JACK_BTN_2;
            priv->hs_jack->report |= SND_JACK_BTN_2;
            pressed_btn_type = SND_JACK_BTN_2;
            logi("key3 back key down , saradc value is %d", priv->saradc_value);
        } else {
            /* exception */
            if (pressed_btn_type) {
                /* if button has just pressed down, then up supposed */
                priv->hs_jack->jack->jack->type = pressed_btn_type;
                priv->hs_jack->report &= ~pressed_btn_type;
                loge("key up supposed, saradc value=%d(btn_type=0x%x)", priv->saradc_value, pressed_btn_type);
                pressed_btn_type = 0;

                /*report key event*/
                logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
                snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report,
                                    SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2);

            } else if (!(HI6401_JACK_BIT_HEADSET & priv->hs_status)) {
                /* if button not down, the irq may triggered by a slow-plugout at the moment,
                   just ignored and make a plug_in_detect */
                loge("key ignored, saradc value=%d(btn_type=0x%x)", priv->saradc_value, pressed_btn_type);

                /* add condition to avoid recog as 3 pole */
                if (priv->saradc_value > priv->headset_voltage->hs_eco_voltage){
                    ret = hs_plug_in_detect_func(codec);
                }
            } else {
                 loge("key ignored in 4 pole,saradc value=%d\n",priv->saradc_value);
            }
            goto end;
        }
    //}
    /*report key event*/
    logi("report type=0x%x, status=0x%x\n", priv->hs_jack->report, priv->hs_status);
    snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report,
                        SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 | SND_JACK_BTN_2);

end:
    return ret;
}

static void  hi6401_hs_work_func(struct work_struct *work)
{
    int ret= 0;
    unsigned int irq_status;
    unsigned int irq_raw = 0, irq_mask = 0;
    int come_from_eco = 0;
    struct snd_soc_codec *codec = NULL;
    struct hi6401_codec_platform_data *pdata = NULL;

    struct hi6401_priv *priv = container_of(work, struct hi6401_priv, hs_work);
    if (!priv)
    {
        printk(KERN_ERR "priv is null pointer\n");
        return;
    }
    
    codec = priv->codec;
    pdata = dev_get_platdata(codec->dev);
    if (!pdata)
    {
        printk(KERN_ERR "pdata is null pointer\n");
        return;
    }

    logd(">> Begin");
    wake_lock_timeout(&priv->wake_lock, 5 * HZ);

    del_timer_sync(&priv->timer);
    cancel_delayed_work_sync(&priv->low_power_work);
    down(&priv->state_sema);
    if ( eco_mode == priv->work_mode ){
        ret = hi6401_exit_eco_mode(codec);
        come_from_eco = 1;
    }
    up(&priv->state_sema);

    irq_raw = snd_soc_read(codec, HI6401_ANA_IRQ_0);
    irq_mask = snd_soc_read(codec, HI6401_ANA_IRQM_0);
    irq_status = irq_raw & (~irq_mask);

    if (!irq_status && (1 == ret)){
        irq_status = IRQ_BTN_DOWN; /* when exit eco,there must be a btn event, so just fake it*/
    }

    /* clear intr before saradc, avoid to clear next irq */
    snd_soc_write(codec ,HI6401_ANA_IRQ_0, irq_raw);

    /* sample button saradc as quick as possible */
    if ((irq_status & ( IRQ_BTN_DOWN | IRQ_BTN_UP | IRQ_ECO_BTN_UP | IRQ_ECO_BTN_DOWN))) {
        ret = read_saradc_value(codec);
    }

    enable_irq(gpio_to_irq(pdata->gpio_intr));

    logd("RAW irq=0x%x, IRQM=0x%x, irq_stat =0x%x, ADC=%d", irq_raw, irq_mask, irq_status, priv->saradc_value);


    /* distribute and handle irq individually, one deal one time */
    if ( irq_status & IRQ_PLUG_IN ){
        if(priv->hs_status == HI6401_JACK_BIT_NONE){
            if(come_from_eco)
                msleep(HI6401_PLUGIN_ECO_DELAY);
            else
                msleep(HI6401_PLUGIN_DELAY);
        }
        ret = hs_plug_in_detect_func(codec);
    } else
    if ( irq_status & IRQ_PLUG_OUT ){
        ret = hs_plug_out_detect_func(codec);
    } else
    if ( irq_status & IRQ_OVER_TEMP ){
        loge("over temp err");
        priv->set_reg_bits(HI6401_ANA_IRQ_0, IRQ_OVER_TEMP);
    } else
    if ((irq_status & ( IRQ_BTN_DOWN | IRQ_BTN_UP | IRQ_ECO_BTN_UP | IRQ_ECO_BTN_DOWN))) {
        /* when hs plug out , btn down irq occured by mistake
           sw need to handle this situation*/
        msleep(15);
        if (snd_soc_read(codec, HI6401_ANA_IRQ_0) & IRQ_PLUG_OUT) {
            logi("hs is pluggout called after 15ms\n");
            ret = hs_plug_out_detect_func(codec);
        }
        else {
            if (priv->hs_status == HI6401_JACK_BIT_HEADSET_NO_MIC) {
                /* intr triggered 2nd-RECG */
                ret = hs_plug_in_detect_func(codec);
            }
            else if (priv->hs_status == HI6401_JACK_BIT_HEADPHONE){

                logi(" 3-pole no key intr!");
                snd_soc_write(codec ,HI6401_ANA_IRQ_0, 0x0F);
            }
            else {
                ret = hs_btn_detect_func(codec);
            }
        }
    }

    if ((0 != snd_soc_read(codec, HI6401_ANA_IRQ_0)) && (!(irq_status & IRQ_PLUG_OUT))) {
       logd("there are other int unhandled!,0x%x", snd_soc_read(codec, HI6401_ANA_IRQ_0));
       ret = -1;
    }

    if (ret < 0) {
        logd("err may happens");
    }

    /* working then delay entering eco mode */
    mod_timer(&priv->timer,jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);

    logd("<< End . irq=0x%x", snd_soc_read(codec, HI6401_ANA_IRQ_0));

}

struct snd_soc_dai_ops hi6401_dai_ops = {
    .startup    = hi6401_startup,
    .shutdown   = hi6401_shutdown,
    .hw_params  = hi6401_hw_params,
};

struct snd_soc_dai_driver hi6401_dai[] = {
    {
        .name = "hi6401-dai",
        .playback = {
            .stream_name    = "Playback",
            .channels_min   = HI6401_PB_MIN_CHANNELS,
            .channels_max   = HI6401_PB_MAX_CHANNELS,
            .rates          = HI6401_RATES,
            .formats        = HI6401_FORMATS},
        .capture = {
            .stream_name    = "Capture",
            .channels_min   = HI6401_CP_MIN_CHANNELS,
            .channels_max   = HI6401_CP_MAX_CHANNELS,
            .rates          = HI6401_RATES,
            .formats        = HI6401_FORMATS},
        .ops = &hi6401_dai_ops,
    },
};
#ifdef CONFIG_DEBUG_FS 

static int hi6401_read(struct file *file, char __user *user_buf,
				   size_t count, loff_t *ppos)
{
    #define SIZE_MAX 2048
    unsigned int i = 0;
    char * buf = NULL;
    ssize_t value_ret= 0;
	
    buf = kmalloc(SIZE_MAX, GFP_KERNEL);
    if (NULL == buf) {
		logi("buf NULL");
		return simple_read_from_buffer(user_buf, count, ppos, "buf alloc fail\n", 15);
    	}

    memset( buf, 0, SIZE_MAX);
    for (i = HI6401_PAGE_0_START; i <= HI6401_PAGE_0_END; i++)
    {
        snprintf(buf, SIZE_MAX, "%s%#04x--%#04x\n", buf, i, hi6401_reg_read(g_codec, i));
    }
    snprintf(buf, SIZE_MAX, "%s\n", buf);

    for (i = HI6401_PAGE_1_START; i <= HI6401_PAGE_1_END; i++)
    {
        snprintf(buf, SIZE_MAX, "%s%#04x--%#04x\n", buf, i, hi6401_reg_read(g_codec, i));
    }
    snprintf(buf, SIZE_MAX, "%s\n", buf);

    value_ret = simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));

    kfree(buf);
    buf = NULL;

    return value_ret;
}
static const struct file_operations hi6401_list_fops = {
	.read =     hi6401_read,
};
#endif

static int set_headset_keys_config(struct hi6401_priv *priv)
{
    int ret = 0;
    unsigned int hs_4_pole_min_voltage_tmp;
    unsigned int hs_4_pole_max_voltage_tmp;
    unsigned int key_back_min_value_tmp;
    unsigned int key_back_max_value_tmp;

    /* config the headset */
    ret = get_hw_config_int("audio/hs_4_pole_min_voltage", &hs_4_pole_min_voltage_tmp, NULL);
    if (false == ret) {
        printk(KERN_ERR "hs_4_pole_min_voltage not found !\n");
        return -1;
    }
    ret = get_hw_config_int("audio/hs_4_pole_max_voltage", &hs_4_pole_max_voltage_tmp, NULL);
    if (false == ret) {
        printk(KERN_ERR "hs_4_pole_max_voltage not found !\n");
        return -1;
    }
    priv->headset_voltage->hs_3_pole_max_voltage = 8;
    priv->headset_voltage->hs_4_pole_min_voltage = hs_4_pole_min_voltage_tmp;
    priv->headset_voltage->hs_4_pole_max_voltage = hs_4_pole_max_voltage_tmp;
    priv->headset_voltage->hs_eco_voltage = 160;
    printk(KERN_INFO "%s: the headset_voltage is {%d, %d, %d, %d}\n", __func__, 8, priv->headset_voltage->hs_4_pole_min_voltage, priv->headset_voltage->hs_4_pole_max_voltage, 160);

    /* config the keys */
    ret = get_hw_config_int("audio/key_back_min_value", &key_back_min_value_tmp, NULL);
    if (false == ret) {
        printk(KERN_ERR "key_back_min_value not found !\n");
        return -1;
    }
    ret = get_hw_config_int("audio/key_back_max_value", &key_back_max_value_tmp, NULL);
    if (false == ret) {
        printk(KERN_ERR "key_back_max_value not found !\n");
        return -1;
    }
    priv->btn_voltage->key_up_min_value = 1350;
    priv->btn_voltage->key_up_max_value = 2565;
    priv->btn_voltage->key_play_min_value = 0;
    priv->btn_voltage->key_play_max_value = 70;
    priv->btn_voltage->key_back_min_value = key_back_min_value_tmp;
    priv->btn_voltage->key_back_max_value = key_back_max_value_tmp;
    priv->btn_voltage->key_forward_min_value = 130;
    priv->btn_voltage->key_forward_max_value = 300;
    printk(KERN_INFO "%s: the btn_voltage is {%d, %d, %d, %d, %d, %d, %d, %d}\n", __func__, 1350, 2565, 0, 70, priv->btn_voltage->key_back_min_value, priv->btn_voltage->key_back_max_value, 130, 300);

    return 0;
}

static int hi6401_codec_probe(struct snd_soc_codec *codec)
{
    int ret = 0;
    struct hi6401_priv *priv = NULL;
    struct snd_soc_dapm_context *dapm = &codec->dapm;
    struct hi6401_codec_platform_data *pdata = dev_get_platdata(codec->dev);
    unsigned int clock_flag;

    logd("Begin");

    if (!pdata) {
        loge("pdata is NULL");
        return -ENOMEM;
    }

    priv = kzalloc(sizeof(struct hi6401_priv), GFP_KERNEL);  //todo
    if (NULL == priv) {
        loge("kzalloc failed");
        return -ENOMEM;
    }
    priv->hs_jack = kzalloc(sizeof(struct hi6401_jack_data), GFP_KERNEL);
    if (NULL == priv->hs_jack) {
        loge("kzalloc failed");
        ret =  -ENOMEM;
        goto priv_hs_jack_alloc_err;
    }
    priv->hs_jack->jack = kzalloc(sizeof(struct snd_soc_jack), GFP_KERNEL);
    if (NULL == priv->hs_jack->jack) {
        loge("kzalloc failed");
        ret = -ENOMEM;
        goto priv_hs_jack_jack_alloc_err;
    }

    priv->headset_voltage = kzalloc(sizeof(struct headset_voltage), GFP_KERNEL);
    if (NULL == priv->headset_voltage) {
        loge("kzalloc failed");
        ret = -ENOMEM;
        goto priv_headset_voltage_alloc_err;
    }
    priv->btn_voltage = kzalloc(sizeof(struct btn_voltage), GFP_KERNEL);
    if (NULL == priv->btn_voltage) {
        loge("kzalloc failed");
        ret = -ENOMEM;
        goto priv_btn_voltage_alloc_err;
    }
    set_headset_keys_config(priv);

    snd_soc_codec_set_drvdata(codec, priv);
    priv->codec = codec;
    g_codec = codec;

    priv->work_mode = normal_mode;
    priv->is_power_on = true;

    /*private ops*/
    priv->set_reg_bits = hi6401_set_reg_bits;
    priv->clr_reg_bits = hi6401_clr_reg_bits;
    priv->__set_reg_bits = __hi6401_set_reg_bits;
    priv->__clr_reg_bits = __hi6401_clr_reg_bits;

    spin_lock_init(&priv->lock);
    mutex_init(&priv->io_mutex);
    sema_init(&priv->state_sema, 1);
	ret = get_hw_config_int("audio/tcxo_support", &clock_flag, NULL);

    if ( ret && (1 == clock_flag)){
        priv->clock_type = TCXO_CLOCK;
    } else {
        priv->clock_type = SSI_CLOCK;
    }

    #ifdef CONFIG_MACH_HI6620OEM
    priv->piomux_block = iomux_get_block(pdata->iomux_name);
    priv->pblock_config = iomux_get_blockconfig(pdata->iomux_name);
    ret = blockmux_set(priv->piomux_block, priv->pblock_config, NORMAL);
    if (ret != 0)
    {
        printk(KERN_ERR "blockmux_set fail\n");
        return ret;
    }
    #endif

    /*codec powerup*/
    #ifdef CONFIG_MACH_HI6620SFT

    /*powerup seq is dvdd_1.8v  -(1s)-> avdd_1.8v -(20ms)-> avdd_3.15 -(20ms)-> */
    ret = gpio_request(pdata->gpio_dvdd_1v8, "gpio_dvdd_1v8");
    if (ret){
        printk(KERN_ERR "error request gpio_6_7 fail\n");
        goto request_gpio_6_7_fail;
    }
    gpio_direction_output(pdata->gpio_dvdd_1v8, 1);

    msleep(1050);

    ret = gpio_request(pdata->gpio_avdd_1v8, "gpio_avdd_1v8");
    if (ret){
        printk(KERN_ERR "error request gpio_6_6 fail\n");
        goto request_gpio_6_6_fail;
    }
    gpio_direction_output(pdata->gpio_avdd_1v8, 1);

    msleep(20);

    ret = gpio_request(pdata->gpio_avdd_3v15, "gpio_avdd_3v15");
    if (ret){
        printk(KERN_ERR "error request gpio_6_5 fail\n");
        goto request_gpio_6_5_fail;
    }
    gpio_direction_output(pdata->gpio_avdd_3v15, 1);

    msleep(20);

    #endif


    #ifdef CONFIG_MACH_HI6620OEM

    priv->regulator_dvdd_1v8 = regulator_get(NULL, pdata->reg_dvdd_1v8);

    if (!IS_ERR(priv->regulator_dvdd_1v8)) {
        ret = regulator_enable(priv->regulator_dvdd_1v8);
    }
    else{
        printk(KERN_ERR "regulator_dvdd_1v8 get error\n");
        goto regulator_get_dvdd_1v8_fail;
    }

    priv->regulator_avdd_1v8 = regulator_get(NULL, pdata->reg_avdd_1v8);

    if (!IS_ERR(priv->regulator_avdd_1v8)) {
        if (TCXO_CLOCK == priv->clock_type){
            ret = regulator_enable(priv->regulator_avdd_1v8);
            msleep(10);
        } else {
            ssi_codec_hardware_spinlock();
            writel(0x10, g_hi6401_reg_base_addr + (SOC_SMART_ENABLE5_ADDR(0) << 2));
            udelay(300);
            ssi_codec_hardware_unspinlock();
            msleep(10);
        }
    }
    else{
        printk(KERN_ERR "regulator_avdd_1v8 get error\n");
        goto regulator_get_avdd_1v8_fail;
    }

    priv->regulator_avdd_3v15 = regulator_get(NULL, pdata->reg_avdd_3v15);

    if (!IS_ERR(priv->regulator_avdd_3v15)) {
        ret = regulator_set_voltage(priv->regulator_avdd_3v15, 3150000, 3150000);
        if (ret != 0)
        {
            printk(KERN_ERR "regulator_set_voltage fail\n");
            return ret;
        }
        ret = regulator_enable(priv->regulator_avdd_3v15);
    }
    else{
        printk(KERN_ERR "regulator_avdd_3v15 get error\n");
        goto regulator_get_avdd_3v15_fail;
    }

    #endif

    if (TCXO_CLOCK == priv->clock_type)
    {
        priv->codec_clk = clk_get(NULL, CLK_NFC);
        if (IS_ERR(priv->codec_clk))
        {
            printk(KERN_ERR "Get Codec clk failed\n");
            goto priv_clock_get_err;
        }
        ret = clk_enable(priv->codec_clk);
        if (ret)
        {
            printk(KERN_ERR "Enable Codec clk failed, ret=%d\n", ret);
            goto priv_clock_enable_err;
        }
    }
    /* judge the clock source */

    init_reg_value(codec);
    g_codec_version = hi6401_reg_read(codec, HI6401_VERSION);
    logi("codec_version=%d", g_codec_version);

    wake_lock_init(&priv->wake_lock, WAKE_LOCK_SUSPEND, "hi6401");

    if(0x01 == g_codec_version){
        /*revert*/;
        priv->set_reg_bits(HI6401_MBHD_POLL, 0x1 << 1);
    }

    priv->hs_status = HI6401_JACK_BIT_NONE;
    priv->old_hs_status = HI6401_JACK_BIT_INVALID;
    priv->hs_jack->report = 0;
    priv->pole_flag = 0;

    priv->set_reg_bits(HI6401_HSMICB_PD_REG, 0x1 << HI6401_HSMICB_PD_BIT);
    priv->set_reg_bits(HI6401_MBHD_VREF_CTRL, 0x1 << HI6401_MBHD_VREF_CTRL_EN_BIT);

    snd_soc_write(codec, HI6401_ANA_IRQ_0,0xFF);
    priv->set_reg_bits(HI6401_ANA_IRQM_0, 0xFF);
    priv->clr_reg_bits(HI6401_ANA_IRQM_0, IRQ_PLUG_IN);

    mdelay(5);

	/*config intr for codec*/
    ret = gpio_request(pdata->gpio_intr, "gpio_int_detect");
    if (ret){
        printk(KERN_ERR "error request gpio_intr fail\n");
        goto request_gpio_5_5_fail;
    }
    gpio_direction_input(pdata->gpio_intr);

    /* Headset jack detection */
    ret = snd_soc_jack_new(codec, "Headset Jack", SND_JACK_HEADSET, (priv->hs_jack->jack));
    if (ret) {
        loge("jack new error, errornum = %d\n", ret);
        goto snd_soc_jack_new_err;
    }

    /* set a key mapping on a jack*/
    ret = snd_jack_set_key(priv->hs_jack->jack->jack, SND_JACK_BTN_0,KEY_MEDIA);
    if( ret ) {
        loge("Set headset key failed!\n");
        goto snd_soc_jack_new_err;
    }
    ret = snd_jack_set_key(priv->hs_jack->jack->jack, SND_JACK_BTN_1,KEY_VOLUMEUP);
    if( ret ) {
        loge("Set headset key failed!\n");
        goto snd_soc_jack_new_err;
    }
    ret = snd_jack_set_key(priv->hs_jack->jack->jack, SND_JACK_BTN_2,KEY_VOLUMEDOWN);
    if( ret ) {
        loge("Set headset key failed!\n");
        goto snd_soc_jack_new_err;
    }

    priv->hs_jack->sdev.name = "h2w";
    ret = switch_dev_register(&(priv->hs_jack->sdev));
    if (ret){
        loge("error registering switch device  \n");
        goto snd_soc_jack_new_err;
    }

    INIT_WORK(&priv->hs_work, hi6401_hs_work_func);

    priv->hs_wq =create_singlethread_workqueue("headset_workqueue");
    if (!(priv->hs_wq)) {
        loge("workqueue create failed");
        ret = -ENOMEM;
        goto snd_soc_dapm_sync_err;
    }
    INIT_DELAYED_WORK(&priv->pll_recover_work, hi6401_pll_work_func);

    INIT_DELAYED_WORK(&priv->pdstat_recover_work, hi6401_pdstat_work_func);

    priv->recover_wq = create_singlethread_workqueue("recover_workqueue");
    if (!(priv->recover_wq)) {
        loge("recover workqueue create failed");
		ret = -ENOMEM;
        goto snd_soc_dapm_sync_err;
    }

    INIT_DELAYED_WORK(&priv->low_power_work, hi6401_enter_eco_mode);
    setup_timer(&priv->timer, hi6401_timeout_timer, (unsigned long)priv);
    mod_timer(&priv->timer, jiffies + ECO_MODE_ENTRY_TIME_SEC * HZ);

    hi6401_add_widgets(codec);

    ret = snd_soc_dapm_sync(dapm);
    if (ret) {
        loge("dapm sync error, errornum = %d\n", ret);
        goto snd_soc_dapm_sync_err;
    }

    /*judge when powerup hs is present or not*/
    logd("when system up irq soure stat is%#04x",hi6401_reg_read(codec,HI6401_IRQ_SOURCE_STAT));
    if ((hi6401_reg_read(codec, HI6401_IRQ_SOURCE_STAT)) & ( 0x1 << 2 )){
        priv->saradc_retries = HI6401_SARADC_BOOTING_RETRIES;
        ret = hs_plug_in_detect_func(codec);
    }
    /* retries always be BOOTED_RETRIES afterward */
    priv->saradc_retries = HI6401_SARADC_BOOTED_RETRIES;

    ret = request_irq(gpio_to_irq(pdata->gpio_intr), hi6401_irq_handler,IRQF_TRIGGER_LOW | IRQF_SHARED | IRQF_NO_SUSPEND, "codec_irq", codec);

    if (ret) {
            logd("request irq for codec failed, errornum = %d\n", ret);
            goto snd_soc_dapm_sync_err;
        }
    if (0x1 == g_codec_version){
        msleep(100);
        hi6401_reg_write(g_codec, HI6401_ANA_IRQ_0, IRQ_PLUG_OUT);
    }
    ret = codec_version_check();
    pmussi_device_state_notify(SSI_DEVICE_CODEC, ret);

#ifdef CONFIG_DEBUG_FS
	if (!debugfs_create_file("hi6401", 0644, NULL, NULL,
				 &hi6401_list_fops))
		loge("hi6401: Failed to create hi6401 debugfs file\n");
#endif
    return ret;

snd_soc_dapm_sync_err:
snd_soc_jack_new_err:
    gpio_free(pdata->gpio_intr);
request_gpio_5_5_fail:
#ifdef CONFIG_MACH_HI6620SFT
    gpio_free(pdata->gpio_avdd_3v15);
request_gpio_6_5_fail:
    gpio_free(pdata->gpio_avdd_1v8);
request_gpio_6_6_fail:
    gpio_free(pdata->gpio_dvdd_1v8);
request_gpio_6_7_fail:
#endif
#ifdef CONFIG_MACH_HI6620OEM
    regulator_put(priv->regulator_avdd_3v15);
regulator_get_avdd_3v15_fail:
    regulator_put(priv->regulator_avdd_1v8);
regulator_get_avdd_1v8_fail:
    regulator_put(priv->regulator_dvdd_1v8);
regulator_get_dvdd_1v8_fail:
#endif
priv_clock_enable_err:
	if(TCXO_CLOCK == priv->clock_type)
	     clk_put(priv->codec_clk);
priv_clock_get_err:
    kfree(priv->btn_voltage);
priv_btn_voltage_alloc_err:
    kfree(priv->headset_voltage);
priv_headset_voltage_alloc_err:
    kfree(priv->hs_jack->jack);
priv_hs_jack_jack_alloc_err:
    kfree(priv->hs_jack);
priv_hs_jack_alloc_err:
    kfree(priv);

    return ret;
}

static int hi6401_codec_remove(struct snd_soc_codec *codec)
{
    /*TODO*/
    struct hi6401_priv *priv = NULL;

    if (NULL != codec)
    {
        priv = snd_soc_codec_get_drvdata(codec);
        if (!priv)
        {
            printk(KERN_ERR "priv is null pointer\n");
            return -1;
        }
        if(priv->recover_wq) {
            cancel_delayed_work(&priv->pll_recover_work);
            cancel_delayed_work(&priv->pdstat_recover_work);
            flush_workqueue(priv->recover_wq);
            destroy_workqueue(priv->recover_wq);
        }
    }

    return 0;
}
#ifdef CONFIG_PM
static int hi6401_power_onoff(bool power_on)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    int ret = 0;

    if(TCXO_CLOCK != priv->clock_type){
        logi("ssi clock dont poweroff\n");
        goto out;
    }
    if (power_on && (!(priv->is_power_on))){
        ret = regulator_enable(priv->regulator_avdd_1v8);
        if (ret){
            loge("[%s]regulator enable fail\n", __func__);
        }
        msleep(10);
        clk_enable(priv->codec_clk);

        priv->is_power_on= true;
        logi("LVS7 turned on\n");
    } else if ((!power_on) && (priv->is_power_on)){
        clk_disable(priv->codec_clk);
        ret = regulator_disable(priv->regulator_avdd_1v8);
        if (ret){
            loge("[%s]regulator disable fail\n", __func__);
        }
        priv->is_power_on = false;
        logi("LVS7 turned off\n");
    } else {
        /*do noting*/
        goto out;
    }
out:
    return ret;
}
static int hi6401_suspend(struct platform_device *dev, pm_message_t state)
{
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    int ret;

    if (NULL == priv) {
        loge("hi6401 priv is NULL\n");
        return 0;
    }

    if (0 == hi6401_ibias_enabled){
        if ( del_timer(&priv->timer) ){
            schedule_delayed_work(&priv->low_power_work, 0);
            flush_work(&priv->low_power_work.work);
        }
        hi6401_power_onoff(false);
        /* notify mcu to pd */
        BSP_IPC_IntSend(IPC_CORE_MCU, (IPC_INT_LEV_E)IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID);
    } else {
        ret = hi6401_reg_read(g_codec, HI6401_S1_CONFIG_1) | hi6401_reg_read(g_codec, HI6401_S2_CONFIG_1)
                    | hi6401_reg_read(g_codec, HI6401_S3_CONFIG_1) | hi6401_reg_read(g_codec, HI6401_S4_CONFIG_1);

        if ( ret & ((0x1 << 6) | (0x1 << 7))){
	    if ( SSI_CLOCK == priv->clock_type ){
                /*notify mcu to slow*/
                BSP_IPC_IntSend(IPC_CORE_MCU, (IPC_INT_LEV_E)IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW);
	    } else {
                /* notify mcu to sleep */
                BSP_IPC_IntSend(IPC_CORE_MCU, (IPC_INT_LEV_E)IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP);
				return 0;
            }
        } else {
                /* notify mcu to pd */
                hi6401_power_onoff(false);
                BSP_IPC_IntSend(IPC_CORE_MCU, (IPC_INT_LEV_E)IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID);
        }
    }

    return 0;
}
static int hi6401_resume(struct platform_device *dev)
{
    struct hi6401_codec_platform_data *pdata = dev_get_platdata(g_codec->dev);
    struct hi6401_priv *priv = snd_soc_codec_get_drvdata(g_codec);
    int ret;

    if (NULL == priv) {
        loge("hi6401 priv is NULL\n");
        return 0;
    }

    if (NULL == pdata) {
        loge("hi6401 pdata is NULL\n");
        return 0;
    }

    hi6401_power_onoff(true);
    priv->piomux_block = iomux_get_block(pdata->iomux_name);
    priv->pblock_config = iomux_get_blockconfig(pdata->iomux_name);
    ret = blockmux_set(priv->piomux_block, priv->pblock_config, NORMAL);

    if (ret != 0)
    {
        printk(KERN_ERR "blockmux_set fail\n");
        return 0;
    }
    return 0;
}
#else
#define hi6401_suspend NULL
#define hi6401_resume NULL
#endif


static struct snd_soc_codec_driver soc_codec_dev_hi6401 = {
    .probe          = hi6401_codec_probe,
    .remove         = hi6401_codec_remove,
    .read           = hi6401_reg_read,
    .write          = hi6401_reg_write,
};

static int __devinit hi6401_probe(struct platform_device *pdev)
{

    struct resource* res;
    struct hi6401_codec_platform_data *pdata = dev_get_platdata(&pdev->dev);

    spin_lock_init(&ssi_hardware_spinlock_t);

    /* get pmuspi register base address */
    res = platform_get_resource_byname(pdev, IORESOURCE_MEM, pdata->reg_base_name);
    if (!res) {
        logd("Could not get register base\n");
        return -ENOMEM;
    }

    g_hi6401_reg_base_addr = (unsigned int)ioremap(res->start, resource_size(res));
    return snd_soc_register_codec(&pdev->dev, &soc_codec_dev_hi6401,
                                 hi6401_dai, ARRAY_SIZE(hi6401_dai));
}

static int __devexit hi6401_remove(struct platform_device *pdev)
{
    logd("Begin\n");

    snd_soc_unregister_codec(&pdev->dev);
#if 0
    if (!IS_ERR(g_codec_clk))
        clk_put(g_codec_clk);
#endif


return 0;
}

static void hi6401_codec_shutdown(struct platform_device *pdev)
{
    struct hi6401_priv *priv = platform_get_drvdata(pdev);

    if(HI6401_JACK_BIT_NONE == priv->hs_status){
       logi("hi6401_codec_shutdown without headset\n");
       return;
    }

    hi6401_hsl_power_mode_event((struct snd_soc_dapm_widget *)NULL,( struct snd_kcontrol *)NULL,SND_SOC_DAPM_POST_PMD);
    logi("hi6401_codec_shutdown with headset finished \n");

}

void hi6401_check_pll(void)
{
    logd("hi6401_check_pll entry\n");
}
EXPORT_SYMBOL_GPL(hi6401_check_pll);

void hi6401_lock_sysclk(bool lock)
{

}
EXPORT_SYMBOL_GPL(hi6401_lock_sysclk);

/*
simu headsest button event
for hifi reset use only
*/
void codec_btn_simu_func(int pressed_button)
{
    struct hi6401_priv *priv = NULL;

    if (hi6401_ibias_enabled <= 0) {
        logi("codec is not on(%d)", hi6401_ibias_enabled);
        return;
    }

    priv = snd_soc_codec_get_drvdata(g_codec);
    if (!priv)
    {
        loge("priv is null pointer\n");
        return;
    }

    /*judge key type*/
    if (0 == pressed_button){
        priv->hs_jack->jack->jack->type = SND_JACK_BTN_0;
        priv->hs_jack->report &= ~(SND_JACK_BTN_0);
        logi("simu key play up happens");
    } else {
        priv->hs_jack->jack->jack->type = SND_JACK_BTN_0;
        priv->hs_jack->report |= SND_JACK_BTN_0;
        logi("simu key play down happens");
    }

    /*report key event*/
    logi("report=0x%x type=0x%x\n", priv->hs_jack->report, priv->hs_jack->jack->jack->type);
    snd_soc_jack_report(priv->hs_jack->jack, priv->hs_jack->report,
                        SND_JACK_HEADSET | SND_JACK_BTN_0);

    return;
}
EXPORT_SYMBOL_GPL(codec_btn_simu_func);

static struct platform_driver hi6401_driver = {
    .driver = {
        .name  = "hi6401-codec",
        .owner = THIS_MODULE,
    },
    .probe   = hi6401_probe,
    .remove  = __devexit_p(hi6401_remove),
    .suspend = hi6401_suspend,
    .resume  = hi6401_resume,
    .shutdown = hi6401_codec_shutdown,
};

static int __init hi6401_codec_init(void)
{
    logd("Begin\n");
    return platform_driver_register(&hi6401_driver);
}
module_init(hi6401_codec_init);

static void __exit hi6401_codec_exit(void)
{
    logd("Begin\n");
    platform_driver_unregister(&hi6401_driver);
}
module_exit(hi6401_codec_exit);

MODULE_DESCRIPTION("ASoC hi6401 driver");
MODULE_LICENSE("GPL");

#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <mach/clk_name_interface.h>
#include <soc_sctrl_interface.h>
#include <reg_ops.h>

#define LOG_TAG "hi6620_digital"
#include "hi6620_digital.h"
#include "hi6620_log.h"

#ifdef HDMI_DISPLAY
#include "../../../drivers/video/hi6620/hdmi/k3_hdmi.h"
#endif


//systrace
#include <trace/trace_kernel.h>

/*
* PLAYBACK SUPPORT FORMATS
* BITS : 8/16/24  18/20
* LITTLE_ENDIAN / BIG_ENDIAN
* MONO / STEREO
* UNSIGNED / SIGNED
*/
#define HI6620_PB_FORMATS  (SNDRV_PCM_FMTBIT_S8 | \
                            SNDRV_PCM_FMTBIT_U8 | \
                            SNDRV_PCM_FMTBIT_S16_LE | \
                            SNDRV_PCM_FMTBIT_S16_BE | \
                            SNDRV_PCM_FMTBIT_U16_LE | \
                            SNDRV_PCM_FMTBIT_U16_BE | \
                            SNDRV_PCM_FMTBIT_S24_LE | \
                            SNDRV_PCM_FMTBIT_S24_BE | \
                            SNDRV_PCM_FMTBIT_U24_LE | \
                            SNDRV_PCM_FMTBIT_U24_BE)
/*
*                           SNDRV_PCM_FMTBIT_S20_3LE |
*                           SNDRV_PCM_FMTBIT_S20_3BE |
*                           SNDRV_PCM_FMTBIT_U20_3LE |
*                           SNDRV_PCM_FMTBIT_U20_3BE |
*                           SNDRV_PCM_FMTBIT_S18_3LE |
*                           SNDRV_PCM_FMTBIT_S18_3BE |
*                           SNDRV_PCM_FMTBIT_U18_3LE |
*                           SNDRV_PCM_FMTBIT_U18_3BE
*/

/*
* PLAYBACK SUPPORT RATES
* 8/11.025/16/22.05/32/44.1/48/88.2/96kHz
*/
#define HI6620_PB_RATES    (SNDRV_PCM_RATE_8000_192000)

#define HI6620_PB_MIN_CHANNELS  ( 1 )
#define HI6620_PB_MAX_CHANNELS  ( 8 )
#define HI6620_PB_FIFO_SIZE     ( SIO_TX_FIFO_SIZE )

#define HI6620_MAX_BUFFER_SIZE  ( 512 * 1024 )    /* 0x20000 */
#define HI6620_MIN_BUFFER_SIZE  ( 32 )
#define HI6620_MAX_PERIODS      ( 32 )
#define HI6620_MIN_PERIODS      ( 2 )

#define HI6620_RATE_INDEX_32000       6
#define HI6620_RATE_INDEX_44100       7
#define HI6620_RATE_INDEX_48000       8
#define HI6620_RATE_INDEX_96000       10
#define HI6620_RATE_INDEX_176400      11
#define HI6620_RATE_INDEX_192000      12
#define HI6620_RATE_48000       ( 48000 )

/* sleep time to check DMA & IRS state */
#define HI6620_MIN_DMA_TIME_US                ( 50000 ) /*time of one period*/
#define HI6620_MAX_DMA_TIME_US                ( 55000 )

static DEFINE_SPINLOCK(g_lock);

static const unsigned int freq[] = {
    8000,   11025,  12000,  16000,
    22050,  24000,  32000,  44100,
    48000,  88200,  96000,  176400,
    192000,
};

static AUDIO_CLK_STRU g_clk_asp_hdmi = {0};

/* HI6620 ASP IRQ */
static unsigned int g_hi6620_asp_irq_line = -1;

/* HI6620 ASP REGISTER BASE ADDR */
static unsigned int g_hi6620_asp_reg_base_addr = -1;

struct proc_dir_entry *audio_digital_dir;
//add for handling an asynchronous work at one DMA interrupt [end]
static int g_digitaloutStatus = 0; //indicate the current audio digital out scene.
static int g_spdifout = 0;  //indicate the spdif output is or not enable, disabled by default
static int g_aformat = 0;     //indicate the current audio compressed format

static struct snd_soc_dai_driver hi6620_digital_dai[] = {
    {
        .name = "hi6620-digital",
        .playback = {
            .stream_name  = "hi6620-digital Playback",
            .channels_min = HI6620_PB_MIN_CHANNELS,
            .channels_max = HI6620_PB_MAX_CHANNELS,
            .rates        = HI6620_PB_RATES,
            .formats      = HI6620_PB_FORMATS},
    },
};

/* define the capability of playback channel */
static const struct snd_pcm_hardware hi6620_digital_playback = {
    .info             = SNDRV_PCM_INFO_INTERLEAVED
                      | SNDRV_PCM_INFO_NONINTERLEAVED
                      | SNDRV_PCM_INFO_BLOCK_TRANSFER
                      | SNDRV_PCM_INFO_PAUSE,
    .formats          = SNDRV_PCM_FORMAT_S16_LE,
    .channels_min     = HI6620_PB_MIN_CHANNELS,
    .channels_max     = HI6620_PB_MAX_CHANNELS,
    .buffer_bytes_max = HI6620_MAX_BUFFER_SIZE,
    .period_bytes_min = HI6620_MIN_BUFFER_SIZE,
    .period_bytes_max = HI6620_MAX_BUFFER_SIZE,
    .periods_min      = HI6620_MIN_PERIODS,
    .periods_max      = HI6620_MAX_PERIODS,
    .fifo_size        = HI6620_PB_FIFO_SIZE,
};

static inline bool is_addr_valid(unsigned int addr)
{
    if (ASP_FIRST_REG <= addr && ASP_LAST_REG >= addr)
        return true;

    if (SIO0_FIRST_REG <= addr && SIO0_LAST_REG >= addr)
        return true;

    if (SIO1_FIRST_REG <= addr && SIO1_LAST_REG >= addr)
        return true;

    if (SPDIF_FIRST_REG <= addr && SPDIF_LAST_REG >= addr)
        return true;

    return false;
}

static inline int hi6620_reg_read(unsigned int addr)
{
    BUG_ON(!is_addr_valid(addr));
//    return readl_mutex(g_hi6620_asp_reg_base_addr + addr);
    return readl(g_hi6620_asp_reg_base_addr + addr);
}

static inline void hi6620_reg_write(unsigned int value, unsigned int addr)
{
    BUG_ON(!is_addr_valid(addr));
//    writel_asp_mutex(value, g_hi6620_asp_reg_base_addr + addr);
    writel(value, g_hi6620_asp_reg_base_addr + addr);
}

static inline void hi6620_set_bits(unsigned int value, unsigned int addr)
{
    unsigned int reg_val = 0;
    unsigned long flags = 0;
    spin_lock_irqsave(&g_lock, flags);
    reg_val = hi6620_reg_read(addr);
    reg_val |= value;
    hi6620_reg_write(reg_val, addr);
    spin_unlock_irqrestore(&g_lock, flags);
}

static inline void hi6620_clr_bits(unsigned int value, unsigned int addr)
{
    unsigned int reg_val = 0;
    unsigned long flags = 0;
    spin_lock_irqsave(&g_lock, flags);
    reg_val = hi6620_reg_read(addr);
    reg_val &= ~value;
    hi6620_reg_write(reg_val, addr);
    spin_unlock_irqrestore(&g_lock, flags);
}

/* config dma start address & data length, then enable dma */
static void enable_dma(unsigned int dma, unsigned int addr,
            int period_next, int size)
{
    unsigned int dma_addr_reg = 0;
    unsigned int dma_len_reg  = 0;

    switch (dma) {
    case TX2_DMA_A :
        dma_addr_reg = ASP_TX2ASAR;
        dma_len_reg  = ASP_TX2ADLR;
        break;

    case TX2_DMA_B :
        dma_addr_reg = ASP_TX2BSAR;
        dma_len_reg  = ASP_TX2BDLR;
        break;

    case TX3_DMA_A :
        dma_addr_reg = ASP_TX3ASAR;
        dma_len_reg  = ASP_TX3ADLR;
        break;

    case TX3_DMA_B :
        dma_addr_reg = ASP_TX3BSAR;
        dma_len_reg  = ASP_TX3BDLR;
        break;
    default :
        loge("%s : error DMA num : %#x", __FUNCTION__, dma);
        break;
    }

    hi6620_reg_write(addr + period_next * size, dma_addr_reg);
    hi6620_reg_write(size, dma_len_reg);
    hi6620_reg_write(dma, ASP_DER);
}

static void wait_dma_stop(unsigned int bits)
{
    unsigned int der = 0;
    unsigned int irsr = 0;
    unsigned int i = 3;

    /*don't use ASP_DSTOP whick can create delayed interrupt*/
    do {
        der = hi6620_reg_read(ASP_DER);
        irsr = hi6620_reg_read(ASP_IRSR);
        if ((der | irsr) & bits) {
            usleep_range(HI6620_MIN_DMA_TIME_US,
                HI6620_MAX_DMA_TIME_US);
        } else {
            break;
        }
    } while(--i);

    if (!i)
        loge("%s exit with der=%#x, irsr=%#x\n", __FUNCTION__, der, irsr);
}

/* transform data to the format that low 16bits is effective and high 16bits is zero */
static void pcm_16bits_to_32bits
                        (unsigned char *pcm16addr, unsigned char *pcm32addr, int pcm32len)
{
    unsigned int *sour = (unsigned int *)pcm16addr;
    unsigned short int *dest = (unsigned short int *)pcm32addr;
    unsigned short int sour2[32] = {0};
    int i = 0;

    for ( ; i < pcm32len ; ) {
        memcpy(sour2, sour, 64);
        dest[0] = sour2[0];
        dest[2] = sour2[1];
        dest[4] = sour2[2];
        dest[6] = sour2[3];
        dest[8] = sour2[4];
        dest[10] = sour2[5];
        dest[12] = sour2[6];
        dest[14] = sour2[7];
        dest[16] = sour2[8];
        dest[18] = sour2[9];
        dest[20] = sour2[10];
        dest[22] = sour2[11];
        dest[24] = sour2[12];
        dest[26] = sour2[13];
        dest[28] = sour2[14];
        dest[30] = sour2[15];
        dest[32] = sour2[16];
        dest[34] = sour2[17];
        dest[36] = sour2[18];
        dest[38] = sour2[19];
        dest[40] = sour2[20];
        dest[42] = sour2[21];
        dest[44] = sour2[22];
        dest[46] = sour2[23];
        dest[48] = sour2[24];
        dest[50] = sour2[25];
        dest[52] = sour2[26];
        dest[54] = sour2[27];
        dest[56] = sour2[28];
        dest[58] = sour2[29];
        dest[60] = sour2[30];
        dest[62] = sour2[31];
        dest += 64;
        sour += 16;
        i += 128;
    }
}

/* data format transform */
static void hi6620_data_transform_work(struct work_struct *work)
{
    struct dc_dma_para *dma_para = container_of(work, struct dc_dma_para, irq_work);
    unsigned char *data_buff_src = dma_para->sour_vir_addr + dma_para->period_next * dma_para->dma_size;
    int dst_dma_size = dma_para->dma_size*2;

    /* transform data_buff_src's data to the format that low 16bits is effective
        and high 16bits is zero, and then save into data_buff_dst*/
    pcm_16bits_to_32bits(data_buff_src, dma_para->dst_vir_addr, dst_dma_size);

    enable_dma(dma_para->dma, dma_para->dst_dma_addr, 0, dst_dma_size);
}

/* handle an asynchronous work at one DMA interrupt */
static inline void hi6620_intr_handle_digital_work(unsigned int dma, unsigned int period_next, struct hi6620_digital_runtime_data *prtd)
{
    switch (dma) {
        case TX3_DMA_A:
                prtd->dmaa_para.period_next = period_next;
                schedule_work(&prtd->dmaa_para.irq_work);
            break;
        case TX3_DMA_B:
                prtd->dmaa_para.period_next = period_next;
                schedule_work(&prtd->dmab_para.irq_work);
            break;
        default:
            break;
    }
}

static int hi6620_dc_para_init(struct snd_pcm_runtime *runtime)
{
    struct hi6620_digital_runtime_data *prtd = runtime->private_data;
    int ret = 0;

    /* init dmaa_irq_work struct */
    memset(&prtd->dmaa_para, 0, sizeof(struct dc_dma_para));
    memset(&prtd->dmab_para, 0, sizeof(struct dc_dma_para));
    /*
        init buff to save dmaa's transformed data
    */
    prtd->dmaa_para.dst_vir_addr = (unsigned char *)dma_alloc_coherent(NULL, prtd->period_size * 2, &prtd->dmaa_para.dst_dma_addr, GFP_KERNEL);
    if(NULL == prtd->dmaa_para.dst_vir_addr) {
        pr_err("%s hi6620_digital_txs_queuework_init() data_buff_dmaa alloc failed", __FUNCTION__);
        return -EINVAL;
    }

    /*
        init buff to save dmab's transformed data
    */
    prtd->dmab_para.dst_vir_addr = (unsigned char *)dma_alloc_coherent(NULL, prtd->period_size * 2, &prtd->dmab_para.dst_dma_addr, GFP_KERNEL);
    if(NULL == prtd->dmab_para.dst_vir_addr) {
        pr_err("%s hi6620_digital_txs_queuework_init() data_buff_dmab alloc failed", __FUNCTION__);
        dma_free_coherent(NULL, prtd->period_size * 2, prtd->dmaa_para.dst_vir_addr,
            prtd->dmaa_para.dst_dma_addr);
        return -EINVAL;
    }
    memset(prtd->dmaa_para.dst_vir_addr, 0x0, prtd->period_size * 2);
    prtd->dmaa_para.sour_dma_addr = runtime->dma_addr;
    prtd->dmaa_para.sour_vir_addr = runtime->dma_area;
    prtd->dmaa_para.dma_size = prtd->period_size;
    prtd->dmaa_para.dma = TX3_DMA_A;
    memset(prtd->dmab_para.dst_vir_addr, 0x0, prtd->period_size * 2);
    prtd->dmab_para.sour_dma_addr = runtime->dma_addr;
    prtd->dmab_para.sour_vir_addr = runtime->dma_area;
    prtd->dmab_para.dma_size = prtd->period_size;
    prtd->dmab_para.dma = TX3_DMA_B;

    INIT_WORK(&prtd->dmaa_para.irq_work, hi6620_data_transform_work);
    INIT_WORK(&prtd->dmab_para.irq_work, hi6620_data_transform_work);

    prtd->data_convert = true;
    return ret;
}

static void hi6620_dc_para_free(struct hi6620_digital_runtime_data *prtd)
{
    if (prtd->data_convert == true) {
        dma_free_coherent(NULL, prtd->period_size * 2, prtd->dmaa_para.dst_vir_addr,
            prtd->dmaa_para.dst_dma_addr);
        dma_free_coherent(NULL, prtd->period_size * 2, prtd->dmab_para.dst_vir_addr,
            prtd->dmab_para.dst_dma_addr);
        memset(&prtd->dmaa_para, 0, sizeof(struct dc_dma_para));
        memset(&prtd->dmab_para, 0, sizeof(struct dc_dma_para));
        prtd->data_convert = false;
    }
}

/* handle one TX DMA interrupt at a time */
static irqreturn_t hi6620_intr_handle_digital_pb(struct snd_pcm_substream *substream)
{
    struct hi6620_digital_runtime_data *prtd = substream->runtime->private_data;
    unsigned int period_size = 0;
    unsigned int rt_period_size = substream->runtime->period_size;
    unsigned int num_period = substream->runtime->periods;
    snd_pcm_uframes_t avail = 0;
    int txindex = 0;
    int dmacur = 0;
    int dmanext = 0;

    unsigned int irs = hi6620_reg_read(ASP_IRSR) & (TX2_DMAS  | TX3_DMAS);

    if (NULL == prtd) {
        loge("%s PCM = NULL \n", __FUNCTION__);
        /* CLEAR ALL TX DMA INTERRUPT */
        hi6620_reg_write(irs, ASP_ICR);
        return IRQ_HANDLED;
    }

    if (prtd->tx[0].dmas == (irs & prtd->tx[0].dmas))
        logd("%s : TWO INTS COME TOGETHER::PLAYBACK\n", __FUNCTION__);

    if (0 == (irs & prtd->tx[0].dmas)) {
            loge("%s : unexpected interrupt\n",__FUNCTION__);
            hi6620_reg_write(irs, ASP_ICR);
            return IRQ_HANDLED;
    }

    period_size = prtd->period_size;

    if (irs & prtd->tx[0].dmaa) {
        txindex = 0;
        dmacur = prtd->tx[0].dmaa;
        dmanext = prtd->tx[0].dmab;
    } else {
        txindex = 0;
        dmacur = prtd->tx[0].dmab;
        dmanext = prtd->tx[0].dmaa;
    }
    hi6620_reg_write(dmacur, ASP_ICR);
    prtd->tx[txindex].period_cur++;

    spin_lock(&prtd->lock);
    prtd->period_cur = prtd->tx[0].period_cur % num_period;
    spin_unlock(&prtd->lock);

    snd_pcm_period_elapsed(substream);

    spin_lock(&prtd->lock);

    /* DMA IS STOPPED CLEAR INTERRUPT */
    if (STATUS_STOP == prtd->status) {
        logd("%s : stop dma, irs = %#x\n", __FUNCTION__, irs);
        hi6620_reg_write(irs, ASP_ICR);
        spin_unlock(&prtd->lock);
        return IRQ_HANDLED;
    }

    avail = snd_pcm_playback_hw_avail(substream->runtime);

    if(avail < rt_period_size) {
        prtd->tx[0].two_dma_flag = false;
        logd("Run out of data in both DMAs, disable both DMAs\n");
        spin_unlock(&prtd->lock);
        return IRQ_HANDLED;
    } else {
        /* avail >= rt_period_size, enable one dma at least */
        /* handle a work of TX data format transform
            and this work need to be done before current DMA enabled */
        if (prtd->data_convert == true) {
            hi6620_intr_handle_digital_work(dmacur, prtd->tx[txindex].period_next, prtd);
        } else {
            enable_dma(dmacur, substream->runtime->dma_addr,
                        prtd->tx[txindex].period_next, period_size);
        }
        prtd->tx[txindex].period_next = (prtd->tx[txindex].period_next + 1) % num_period;

        if ((!prtd->tx[txindex].two_dma_flag) && (avail >= rt_period_size * 2 )) {
            logd("enable both DMAs\n");
            /* enable DMA B */
            prtd->tx[txindex].two_dma_flag = true;

            /* handle a work of TX data format transform
                and this work need to be done before next DMA enabled*/
            if (prtd->data_convert == true) {
                hi6620_intr_handle_digital_work(dmanext, prtd->tx[txindex].period_next, prtd);
            } else {
                enable_dma(dmanext, substream->runtime->dma_addr,
                            prtd->tx[txindex].period_next, period_size);
            }
            prtd->tx[txindex].period_next = (prtd->tx[txindex].period_next + 1) % num_period;
        }
    }

    spin_unlock(&prtd->lock);

    return IRQ_HANDLED;
}

static irqreturn_t hi6620_intr_handle_digital(int irq, void *dev_id)
{
    struct snd_pcm *pcm = dev_id;
    struct snd_pcm_substream *substream;
    unsigned int irs = hi6620_reg_read(ASP_IRSR);
    irqreturn_t ret = IRQ_NONE;
    unsigned int irs_valid = hi6620_reg_read(ASP_IER) & irs;

    /* clean unexpected interrupt*/
    if (irs != irs_valid) {
        loge("clean unexpected interrupt irs:%x valid:%x\n", irs, irs_valid);
        irs = irs & (~irs_valid);
        hi6620_reg_write(irs, ASP_ICR);
        irs = irs_valid;
        ret = IRQ_HANDLED;
    }

    /* BUSERROR INTERRUPT */
    if (ASP_BUS_ERROR & irs) {
        loge("asp bus error\n");
        hi6620_reg_write(ASP_BUS_ERROR, ASP_ICR);
        ret = IRQ_HANDLED;
    }

    /* PLAYBACK INTERRUPT */
    if ((TX2_DMAS  | TX3_DMAS)& irs) {
        substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
        if (substream) {
			trace_dot(AASP,"4",0);	
            ret = hi6620_intr_handle_digital_pb(substream);
			trace_dot(AASP,"5",0);	
        } else {
            loge("%s : PLAYBACK is NULL\n",__FUNCTION__);
            hi6620_reg_write((TX2_DMAS  | TX3_DMAS) & irs, ASP_ICR);
            ret = IRQ_HANDLED;
        }
    }

    return ret;
}

static void hi6620_set_tx123_outfreq(unsigned int outfreq_index)
{
    unsigned int value = hi6620_reg_read(ASP_TX1);

    value = value & 0xff;
    /* set  output rate */
    // for passthrough, this register is invalid.
    if (outfreq_index > HI6620_RATE_INDEX_176400) {
        value |= TX_192K_OUTPUT_BIT;
    } else if (outfreq_index > HI6620_RATE_INDEX_48000) {
        value |= TX_96K_OUTPUT_BIT;
    }
    hi6620_reg_write(value, ASP_TX1);
}

/*get route for audio data*/
static unsigned int hi6620_get_aout_route(bool compressed,unsigned int infreq_index,unsigned int* outfreq_index,unsigned int channels)
{
    AUDIO_ROUTE_ENUM eroute = AUDIO_ROUTE_PB_MAX;
    unsigned int div_frac = 0;

    logi("compressed=%d, infreq_index=%d, channels=%d\n", compressed, infreq_index, channels);

    //by default, input freq is equal to output freq
    *outfreq_index = infreq_index;

    logi("g_aformat=%d, g_digitaloutStatus=%d, g_spdifout=%d\n", g_aformat, g_digitaloutStatus, g_spdifout);

    if (g_aformat == AFORMAT_RESERVED) {
        //reserved
        loge("invalid audio format\n");
        return AUDIO_ROUTE_PB_MAX;
    } else if (g_aformat == AFORMAT_MULTI_PCM) {
        //multi-channels pcm
        eroute = AUDIO_ROUTE_PCM_SIO_ONLY;
    } else if (g_digitaloutStatus == 0) {
        //compressed data, HDMI is pulled out.
        if (g_spdifout == 0) {
            //no HDMI, use SPDIF.
            //if hardware doesnt' exist, no sound can be hear.
            //this scene shouldn't happen, APP can do well.
            loge("no HDMI, use spdif for output\n");
            eroute = AUDIO_ROUTE_AUX_SPDIF;
//            eroute = AUDIO_ROUTE_PB_MAX;
        } else {
            //SPDIF output is enabled
            eroute = AUDIO_ROUTE_AUX_SPDIF;
        }
        switch(g_aformat) {
        case AFORMAT_AC3:
        case AFORMAT_DTS:
            break;
        case AFORMAT_DDP: //DDP should convert to DD
        case AFORMAT_DTSHD:   //wjh???  Dolby TrueHD
        default:
            loge("%s not support format %d\n", __FUNCTION__,g_aformat);
            eroute = AUDIO_ROUTE_PB_MAX;  //high bit rate can't support
            break;
        }
    } else {
        //compressed data, HDMI is plugged in.
        switch(g_aformat) {
        case AFORMAT_DDP:
            if ((infreq_index == HI6620_RATE_INDEX_48000) || (infreq_index == HI6620_RATE_INDEX_96000)
                 || (infreq_index == HI6620_RATE_INDEX_192000)) {
                *outfreq_index = HI6620_RATE_INDEX_192000;
            } else {
                *outfreq_index = HI6620_RATE_INDEX_176400;
            }
            eroute = AUDIO_ROUTE_AUX_SPDIF;
            break;
        case AFORMAT_MAT_MLP:
        case AFORMAT_DTSHD:
            if ((infreq_index == HI6620_RATE_INDEX_48000) || (infreq_index == HI6620_RATE_INDEX_96000)
                 || (infreq_index == HI6620_RATE_INDEX_192000)) {
                *outfreq_index = HI6620_RATE_INDEX_192000;
            } else {
                *outfreq_index = HI6620_RATE_INDEX_176400;
            }
            eroute = AUDIO_ROUTE_AUX_SIO;
            break;
        default:
            eroute = AUDIO_ROUTE_AUX_SPDIF;
            break;
        }
    }

    /*
    [HDMIPLL 1188M通过小数分频得到HDMI_MCLK的49.152M时钟]
    [对于SFT平台是594M主时钟频率]
    [分频系数共计占24个bit, 23:0]
    [49.152M时钟固定分频得到i2s 192K时钟]
    [i2s 192K == spdif 96K]
    divfrac / 2^27 = 49.152M / 1188M
    so, divfrac = 49.152 * 2^27 / 1188 = 0x54BBC1 = 5553089
    [192K==>0x54BBC1，如需降低i2s时钟，则降低相应分频系数]
    [对于SFT平台，192K==>0xA97782=11106178]
    [其他对应关系freq==>_dfrac
    96K==>0x2A5DE0
    48K==>0x152EF0
    ]
    _dfrac = 0x54BBC1 * freq / 192K
          = 0x54BBC1*100 / (192000*100 / freq)
    */
#ifdef CONFIG_MACH_HI6620OEM
    div_frac = 0x54BBC1 * 100 / (19200000 / freq[*outfreq_index]);
#else
    div_frac = 0xA97782 * 100 / (19200000 / freq[*outfreq_index]);
#endif
    logi("div_frac=0x%x, freq=%d\n", div_frac, freq[*outfreq_index]);
    phy_reg_writel(REG_BASE_SC_OFF,
                   SOC_SCTRL_SC_CLKCFGALL4_ADDR(CALC_REG_OFFSET),
                   SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_START,
                   SOC_SCTRL_SC_CLKCFGALL4_divfrac_49m_END,
                   div_frac);

    return eroute;
}

/*used for low bit rate compacted data,  SPDIF-->HDMI*/
static int hi6620_digital_tx2_enable(unsigned int aformat,unsigned int dataformat, unsigned int infreq_index,unsigned int outfreq_index, struct hi6620_tx_runtime_data* tx)
{
    unsigned int value = 0;
    unsigned int value_spdif_config = 0;
    unsigned int value_spdif_status1 = 0;
    unsigned int value_spdif_status2 = 0;

    IN_FUNCTION;

    //HDMI use SPDIF, SPDIF also enabled
    tx->dmaa = TX2_DMA_A;
    tx->dmab = TX2_DMA_B;
    tx->dmas = TX2_DMAS;

    //choose SPDIF
    hi6620_reg_write(1, ASP_SPDIFSELR);

    //ASP_TX2
    /* set  output rate */
    hi6620_set_tx123_outfreq(outfreq_index);

    value = TX2_EN_BIT | HIGHBIT_IS_RIGHT|TX2_TSEN_BIT |dataformat;//enable TX2 and transparent
    hi6620_reg_write(value, ASP_TX2);

    /* ENABLE TX2 DMA INTERRUPT */
    wait_dma_stop(TX2_DMAS);
    hi6620_reg_write(TX2_DMAS, ASP_ICR);
    hi6620_set_bits(TX2_DMAS | ASP_BUS_ERROR, ASP_IER);

    //SPDIF
    if( aformat == AFORMAT_PCM  )
    {
        value_spdif_config = 0;
        value_spdif_status1 = 0x404;
        value_spdif_status2 = 0x202;
    }
    else
    {
        value_spdif_config = 1;
        value_spdif_status1 = 0x606;
        value_spdif_status2 = 0;
    }
//    hi6620_reg_write(0x0, SPDIF_CTRL); //Reset SPDIF, for the Left and Right channel's data might abnormal exchange when audio paused and restarted
    hi6620_reg_write(value_spdif_config, SPDIF_CONFIG);//not line-pcm
    hi6620_reg_write(0x7, SPDIF_IRQ_MASK);//interrupt mask

    hi6620_reg_write(value_spdif_status1, SPDIF_CH_STATUS1);//not line-pcm
    hi6620_reg_write(value_spdif_status2, SPDIF_CH_STATUS2); // DVD
    hi6620_reg_write(0x2010, SPDIF_CH_STATUS3);//left-->left,right-->right
    switch(outfreq_index) {
    case HI6620_RATE_INDEX_32000:
        value = 0x303;
        break;
    case HI6620_RATE_INDEX_44100:
        value = 0x0;
        break;
    case HI6620_RATE_INDEX_96000:
        value = 0xA0A;
        break;
    case HI6620_RATE_INDEX_176400:
        value = 0xC0C;
        break;
    case HI6620_RATE_INDEX_192000:
        value = 0xE0E;
        break;
    case HI6620_RATE_INDEX_48000:
    default:
        value = 0x202;
        break;
    }
    hi6620_reg_write(value, SPDIF_CH_STATUS4);

    switch(infreq_index) {
    case HI6620_RATE_INDEX_32000:
        value = 0xC0C0;
        break;
    case HI6620_RATE_INDEX_44100:
        value = 0xF0F0;
        break;
    case HI6620_RATE_INDEX_96000:
        value = 0x5050;
        break;
    case HI6620_RATE_INDEX_176400:
        value = 0x3030;
        break;
    case HI6620_RATE_INDEX_192000:
        value = 0x1010;
        break;
    case HI6620_RATE_INDEX_48000:
    default:
        value = 0xD0D0;
        break;
    }
    value |= 0x202; // 16bits
    hi6620_reg_write(value,SPDIF_CH_STATUS5);

    hi6620_reg_write(0x5, SPDIF_CTRL); //FIFO 16,enable

#ifdef HDMI_DISPLAY
    /*if use SPDIF for passthrough, HDMI needn't power on*/
    if (g_digitaloutStatus != 0) {
        //init HDMI start
        if( aformat == AFORMAT_PCM  )
        {
        	k3_hdmi_audio_set_param(freq[outfreq_index], HDMI_SAMPLE_16BITS, false, LAYOUT_2CH, aformat );
        }
	 else
	 {
	 	k3_hdmi_audio_set_param(freq[outfreq_index], HDMI_SAMPLE_16BITS, false, LAYOUT_6CH, aformat );
	 }
    }
#endif

    OUT_FUNCTION;

    return 0;
}

/*used for low bit rate compacted data,  SIO1-->HDMI*/
static int hi6620_digital_tx3_enable(unsigned int aformat, unsigned int dataformat, unsigned int infreq_index,unsigned int outfreq_index, struct hi6620_tx_runtime_data* tx)
{
    unsigned int value = 0;

    IN_FUNCTION;

    //HDMI use I2S1, SPDIF diaabled
    tx->dmaa = TX3_DMA_A;
    tx->dmab = TX3_DMA_B;
    tx->dmas = TX3_DMAS;

    /* Set resample rate */
    hi6620_reg_write(infreq_index, ASP_TX3RSRR);

    /* set  output rate */
    hi6620_set_tx123_outfreq(outfreq_index);
    //HDMI choose SIO1
    hi6620_reg_write(0, ASP_SPDIFSELR);

    /* CONFIG SIO1 INTERFACE FOR PB */
    hi6620_reg_write(1, SIO1_ASPIF_SEL);//enable SIO1
    hi6620_reg_write(SIO_TX_ENABLE | SIO_TX_FIFO, SIO1_I2S_CLR);//bits same as SIO0
    hi6620_set_bits(SIO_TX_ENABLE | SIO_TX_FIFO, SIO1_I2S_SET);

    //ASP_TX3
    if (aformat <= AFORMAT_PCM) {
        // 5.1/7.1 PCM
        value = TX3_EN_BIT;//enable TX3
    } else {
        //compressed
        value = TX3_EN_BIT |TX3_TSEN_BIT;//enable TX3 and transparent
    }

    switch(dataformat&0x7) {
    case STEREO_18BIT:
        value |= 0x1;
        break;
    case STEREO_20BIT:
        value |= 0x2;
        break;
    case STEREO_24BIT:
        value |= 0x3;
        break;
    case STEREO_16BIT:
    default:
        break;
    }
    hi6620_reg_write(value, ASP_TX3);

    /* ENABLE TX3 DMA INTERRUPT */
    wait_dma_stop(TX3_DMAS);
    hi6620_reg_write(TX3_DMAS, ASP_ICR);
    hi6620_set_bits(TX3_DMAS | ASP_BUS_ERROR, ASP_IER);

#ifdef HDMI_DISPLAY
    //init HDMI start
    k3_hdmi_audio_set_param(freq[outfreq_index], HDMI_SAMPLE_16BITS, true, 1, aformat );
#endif

    OUT_FUNCTION;

    return 0;
}

static void hi6620_digital_tx_disable(struct hi6620_digital_runtime_data *prtd)
{
    IN_FUNCTION;

    wait_dma_stop(prtd->tx[0].dmas);
    /* disable DMA interrupt */
    hi6620_clr_bits(prtd->tx[0].dmas, ASP_IER);

    hi6620_reg_write(0, ASP_TX2);
    hi6620_reg_write(0, ASP_TX3);
    hi6620_reg_write(SIO_TX_ENABLE | SIO_TX_FIFO, SIO1_I2S_CLR);

    OUT_FUNCTION;
}

void hi6620_digital_clk_enable(AUDIO_ROUTE_ENUM eroute)
{
    int ret = 0;
    logd("%s : clk_enable\n", __FUNCTION__);
    ret = clk_enable(g_clk_asp_hdmi.clk_asp_cfg);
    if (ret != 0)
    {
        printk(KERN_ERR "regulator_enable fail\n");
        return;
    }
    if (AUDIO_ROUTE_CAP == eroute) {
        /*clock enable for capture*/
        (void)clk_enable(g_clk_asp_hdmi.clk_asphdmi_ref);
        return;
    }
    /*clock enable for pb*/
    (void)clk_enable(g_clk_asp_hdmi.clk_asphdmi_ref);
    g_clk_asp_hdmi.enable_clk_asphdmi = true;
    switch(eroute) {
    case AUDIO_ROUTE_PCM_SPDIF_ONLY:
        (void)clk_enable(g_clk_asp_hdmi.clk_aspspdif);
        g_clk_asp_hdmi.enable_clk_aspspdif = true;
        if (g_digitaloutStatus != 0) {
            (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_m);
            (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_s);
            g_clk_asp_hdmi.enable_clk_hdmi_m = true;
        }
        break;
    case AUDIO_ROUTE_PCM_DAC_SPDIF/* xxDACxx */:
        (void)clk_enable(g_clk_asp_hdmi.clk_aspspdif);
        g_clk_asp_hdmi.enable_clk_aspspdif = true;
        if (g_digitaloutStatus != 0) {
            (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_m);
            (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_s);
            g_clk_asp_hdmi.enable_clk_hdmi_m = true;
        }
        break;
    case AUDIO_ROUTE_AUX_SPDIF:
        (void)clk_enable(g_clk_asp_hdmi.clk_aspspdif);
        g_clk_asp_hdmi.enable_clk_aspspdif = true;
        if (g_digitaloutStatus != 0) {
            (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_m);
            (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_s);
            g_clk_asp_hdmi.enable_clk_hdmi_m = true;
        }
        break;
    case AUDIO_ROUTE_PCM_SIO_ONLY:
    case AUDIO_ROUTE_AUX_SIO:
        (void)clk_enable(g_clk_asp_hdmi.clk_asphdmi_adws);
        (void)clk_enable(g_clk_asp_hdmi.clk_asphdmi_bclk);
        g_clk_asp_hdmi.enable_clk_aspsio = true;
        (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_m);
        (void)clk_enable(g_clk_asp_hdmi.clk_hdmi_s);
        g_clk_asp_hdmi.enable_clk_hdmi_m = true;
        break;
    case AUDIO_ROUTE_PCM_DAC_ONLY/* xxDACxx */:
    default:
        (void)clk_enable(g_clk_asp_hdmi.clk_asphdmi_adws);
        (void)clk_enable(g_clk_asp_hdmi.clk_asphdmi_bclk);
        g_clk_asp_hdmi.enable_clk_aspsio = true;
        break;
    }
}

/*only AUDIO_ROUTE_CAP is used for distinguish pb and cap*/
void hi6620_digital_clk_disable(AUDIO_ROUTE_ENUM eroute)
{
    logd("%s : clk_disable\n", __FUNCTION__);

    if (AUDIO_ROUTE_CAP == eroute) {
        /*clock disable for capture*/
        clk_disable(g_clk_asp_hdmi.clk_asphdmi_ref);
    } else {
        /*clock disable for playback*/
        if (g_clk_asp_hdmi.enable_clk_asphdmi == true) {
            g_clk_asp_hdmi.enable_clk_asphdmi = false;
            clk_disable(g_clk_asp_hdmi.clk_asphdmi_ref);
        }

        if (g_clk_asp_hdmi.enable_clk_aspspdif == true) {
            g_clk_asp_hdmi.enable_clk_aspspdif = false;
            clk_disable(g_clk_asp_hdmi.clk_aspspdif);
        }

        if (g_clk_asp_hdmi.enable_clk_hdmi_m == true) {
            g_clk_asp_hdmi.enable_clk_hdmi_m = false;
            clk_disable(g_clk_asp_hdmi.clk_hdmi_m);
            clk_disable(g_clk_asp_hdmi.clk_hdmi_s);
        }
    }

    clk_disable(g_clk_asp_hdmi.clk_asp_cfg);
}
int hi6620_digital_init_txs(struct snd_pcm_runtime *runtime, struct snd_pcm_hw_params *params)
{
    struct hi6620_digital_runtime_data *prtd = runtime->private_data;
    unsigned int params_value = 0;
    unsigned int channels = 0;
    unsigned int format = 0;
    unsigned int infreq_index = 0;
    unsigned int outfreq_index = 0;
    AUDIO_ROUTE_ENUM eroute = 0;
    bool compressed = false;
    BUG_ON(!prtd);

    /*get parameters */
    /* CHECK SUPPORT CHANNELS : mono or stereo */
    params_value = params_channels(params);
    if ((params_value >= 1) && (params_value <=8)) {
        channels = params_value;
    } else {
        loge("%s : DAC not support %d channels\n", __FUNCTION__, params_value);
        return -EINVAL;
    }

    /* CHECK SUPPORT RATE */
    params_value = params_rate(params);
    logi("%s : set rate = %d \n",__FUNCTION__, params_value);
    for (infreq_index = 0; infreq_index < ARRAY_SIZE(freq); infreq_index++) {
        if(params_value == freq[infreq_index])
            break;
    }
    if ( ARRAY_SIZE(freq) <= infreq_index) {
        loge("%s : set rate = %d error\n",__FUNCTION__, params_value);
        return -EINVAL;
    }

    params_value = params_format(params);
    /* check formats */
    switch (params_value) {
    case SNDRV_PCM_FORMAT_S16_BE :
        format |= BIG_DIAN_BIT;
        /* full through*/
    case SNDRV_PCM_FORMAT_S16_LE :
        format |= STEREO_16BIT;
        break;

    default :
        loge("%s : format err : %d, not support\n",
                __FUNCTION__, params_value);
        return -EINVAL;
    }

    /*get audio out route*/
    eroute = hi6620_get_aout_route(compressed, infreq_index, &outfreq_index, channels);
    hi6620_digital_clk_enable(eroute);

    /*init tx channel and dma*/
    memset(prtd->tx, 0, sizeof(prtd->tx));
    logi("hi6620_get_aout_route %d\r\n",eroute);

    prtd->data_convert = false;
    switch(eroute) {
    case AUDIO_ROUTE_AUX_SPDIF:  // HDMI/SPDIF COMPACT,only tx2
        hi6620_digital_tx2_enable(g_aformat, format, infreq_index, outfreq_index, &prtd->tx[0]);
        break;
    case AUDIO_ROUTE_AUX_SIO:// HDMI COMPACT,only tx3
        hi6620_dc_para_init(runtime);
        hi6620_digital_tx3_enable(g_aformat, format, infreq_index, outfreq_index, &prtd->tx[0]);
        break;
    case AUDIO_ROUTE_PCM_SIO_ONLY://HDMI 5.1/7.1 PCM;  DAC disable
        if (STEREO_16BIT == (format&0x7)) {
            //todo:only 16bits need data format convert
            hi6620_dc_para_init(runtime);
        }
        hi6620_digital_tx3_enable(AFORMAT_PCM, format, infreq_index, outfreq_index, &prtd->tx[0]);
        break;
    default :/*if return EINVAL, hi6620_digital_open is called repeatly,so use TX0 as default route*/
        hi6620_digital_tx2_enable(g_aformat, format, infreq_index, outfreq_index, &prtd->tx[0]);
        break;
    }
    return 0;
}

static int hi6620_digital_hw_params(struct snd_pcm_substream *substream,
        struct snd_pcm_hw_params *params)
{
    unsigned long bytes = params_buffer_bytes(params);
    struct hi6620_digital_runtime_data *prtd = substream->runtime->private_data;
    int ret = 0;

    logi("%s entry : %s\n", __FUNCTION__,
            substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE");

    ret = snd_pcm_lib_malloc_pages(substream, bytes);
    if ( ret < 0 ) {
        loge("snd_pcm_lib_malloc_pages ret : %d\n", ret);
        return ret;
    }
    prtd->period_size = params_period_bytes(params);
    prtd->period_next = 0;

    /* PLAYBACK */
    if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
        ret = hi6620_digital_init_txs(substream->runtime, params);
        if ( ret < 0 ) {
            loge("hi6620_digital_init_txs ret : %d\n", ret);
            snd_pcm_lib_free_pages(substream);
            return ret;
        }
    }

    OUT_FUNCTION;

    return ret;
}

static int hi6620_digital_hw_free(struct snd_pcm_substream *substream)
{
    struct hi6620_digital_runtime_data *prtd = substream->runtime->private_data;

    logi("%s : %s\n", __FUNCTION__,
            substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE");

    if(SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
        hi6620_dc_para_free(prtd);
        hi6620_digital_tx_disable(prtd);
    }

    /* disable clk. for pb, we don't care the value of eroute*/
    hi6620_digital_clk_disable(AUDIO_ROUTE_PCM_DAC_ONLY);
    return snd_pcm_lib_free_pages(substream);
}

static int hi6620_digital_prepare(struct snd_pcm_substream *substream)
{
    struct hi6620_digital_runtime_data *prtd = substream->runtime->private_data;
    unsigned long flags = 0;

    logi("%s : %s\n", __FUNCTION__,
            substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE");

    spin_lock_irqsave(&prtd->lock, flags);
    /* init prtd */
    prtd->status = STATUS_STOP;
    prtd->period_next = 0;
    prtd->period_cur = 0;
    prtd->two_dma_flag = true;
    spin_unlock_irqrestore(&prtd->lock, flags);

    if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
        wait_dma_stop(TX2_DMAS | TX3_DMAS);
        hi6620_reg_write(TX23_NEWSONG, ASP_TXNSSR); /* clear fifo */
    }

    return 0;
}

static int hi6620_digital_trigger(struct snd_pcm_substream *substream, int cmd)
{
    unsigned long flags = 0;
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct hi6620_digital_runtime_data *prtd = substream->runtime->private_data;
    unsigned int num_periods = runtime->periods;
    unsigned int period_size = prtd->period_size;
    int ret = 0;

    logi("%s entry : %s, cmd: %d\n", __FUNCTION__,
            substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE", cmd);
	
	trace_dot(AASP,"2",0);	
#ifdef HDMI_DISPLAY
    switch (cmd) {
    case SNDRV_PCM_TRIGGER_START:
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if (g_digitaloutStatus != 0) {
            k3_hdmi_audio_set_power(true);
        }
        break;

    case SNDRV_PCM_TRIGGER_STOP:
    case SNDRV_PCM_TRIGGER_SUSPEND:
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if (g_digitaloutStatus != 0) {
            k3_hdmi_audio_set_power(false);
        }
        break;
    }
#endif

    spin_lock_irqsave(&prtd->lock, flags);

    switch (cmd) {
    case SNDRV_PCM_TRIGGER_START:
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        prtd->status = STATUS_RUNNING;
        prtd->two_dma_flag = true;
        if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream) {
            /*enable tx[0]*/
            prtd->tx[0].two_dma_flag = true;
            enable_dma(prtd->tx[0].dmaa, runtime->dma_addr, prtd->tx[0].period_next, period_size);
            prtd->tx[0].period_next = (prtd->tx[0].period_next + 1) % num_periods;
            enable_dma(prtd->tx[0].dmab, runtime->dma_addr, prtd->tx[0].period_next, period_size);
            prtd->tx[0].period_next = (prtd->tx[0].period_next + 1) % num_periods;
        }
        break;

    case SNDRV_PCM_TRIGGER_STOP:
    case SNDRV_PCM_TRIGGER_SUSPEND:
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        prtd->status = STATUS_STOP;
        break;

    default:
        loge("%s cmd error : %d", __FUNCTION__, cmd);
        ret = -EINVAL;
        break;
    }

    spin_unlock_irqrestore(&prtd->lock, flags);
	trace_dot(AASP,"3",0);	
    return ret;
}

static snd_pcm_uframes_t hi6620_digital_pointer(struct snd_pcm_substream *substream)
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct hi6620_digital_runtime_data *prtd = runtime->private_data;
    unsigned long frame = 0L;

    frame = bytes_to_frames(runtime, prtd->period_cur * prtd->period_size);
    if(frame >= runtime->buffer_size)
        frame = 0;

    return frame;
}

static int hi6620_digital_open(struct snd_pcm_substream *substream)
{
    struct hi6620_digital_runtime_data *prtd = NULL;

    logi("%s : %s\n", __FUNCTION__,
            substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE");

    prtd = kzalloc(sizeof(struct hi6620_digital_runtime_data), GFP_KERNEL);
    if (NULL == prtd) {
        loge("%s : kzalloc hi6620_digital_runtime_data error!\n", __FUNCTION__);
        return -ENOMEM;
    }

    spin_lock_init(&prtd->lock);

    substream->runtime->private_data = prtd;

	trace_dot(AASP,"0",0);	
    if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
        snd_soc_set_runtime_hwparams(substream, &hi6620_digital_playback);
	trace_dot(AASP,"1",0);		

    return 0;
}

static int hi6620_digital_close(struct snd_pcm_substream *substream)
{
    struct hi6620_digital_runtime_data *prtd = substream->runtime->private_data;

    logi("%s entry : %s\n", __FUNCTION__,
            substream->stream == SNDRV_PCM_STREAM_PLAYBACK
            ? "PLAYBACK" : "CAPTURE");

    if(NULL == prtd)
        loge("hisik3_pcm_close called with prtd == NULL\n");
	
	trace_dot(AASP,"6",0);
    if (prtd) {
        kfree(prtd);
        substream->runtime->private_data = NULL;
    }
	trace_dot(AASP,"7",0);
    return 0;
}


/* define all pcm ops of hi6620 pcm */
static struct snd_pcm_ops hi6620_digital_ops = {
    .open       = hi6620_digital_open,
    .close      = hi6620_digital_close,
    .ioctl      = snd_pcm_lib_ioctl,
    .hw_params  = hi6620_digital_hw_params,
    .hw_free    = hi6620_digital_hw_free,
    .prepare    = hi6620_digital_prepare,
    .trigger    = hi6620_digital_trigger,
    .pointer    = hi6620_digital_pointer,
};

static u64 hi6620_digital_dmamask = (u64)(0xffffffff);

static int hi6620_digital_new(struct snd_card *card,
        struct snd_soc_dai *dai, struct snd_pcm *pcm)
{
    int ret = 0;

    IN_FUNCTION;

    if (!card->dev->dma_mask) {
        logi("%s : dev->dma_mask not set\n", __FUNCTION__);
        card->dev->dma_mask = &hi6620_digital_dmamask;
    }

    if (!card->dev->coherent_dma_mask) {
        logi("%s : dev->coherent_dma_mask not set\n", __FUNCTION__);
        card->dev->coherent_dma_mask = hi6620_digital_dmamask;
    }
    ret = snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,
            pcm->card->dev, HI6620_MAX_BUFFER_SIZE, HI6620_MAX_BUFFER_SIZE);
    if (ret) {
        loge("snd_pcm_lib_preallocate_pages_for_all error : %d\n", ret);
        return ret;
    }
    logi("pcm->device = %d\n", pcm->device);
    ret = request_irq(g_hi6620_asp_irq_line, hi6620_intr_handle_digital,
            IRQF_SHARED, "ASP", pcm);

    if (ret) {
        loge("request_irq error : %d\n", ret);
        snd_pcm_lib_preallocate_free_for_all(pcm);
    }

    OUT_FUNCTION;

    return ret;
}

static void hi6620_digital_free(struct snd_pcm *pcm)
{
    IN_FUNCTION;

    logi("%s: pcm->device = 0\n", __FUNCTION__);
    free_irq(g_hi6620_asp_irq_line, pcm);

    snd_pcm_lib_preallocate_free_for_all(pcm);

    OUT_FUNCTION;
}

struct snd_soc_platform_driver hi6620_digital_platform = {
    .ops      = &hi6620_digital_ops,
    .pcm_new  = hi6620_digital_new,
    .pcm_free = hi6620_digital_free,
};

static void hi6620_digital_platform_close_clocks(void)
{
    if (g_clk_asp_hdmi.clk_asphdmi_ref != NULL) {
        clk_put(g_clk_asp_hdmi.clk_asphdmi_ref);
        g_clk_asp_hdmi.clk_asphdmi_ref = NULL;
    }

    if (g_clk_asp_hdmi.clk_aspspdif != NULL) {
        clk_put(g_clk_asp_hdmi.clk_aspspdif);
        g_clk_asp_hdmi.clk_aspspdif = NULL;
    }

    if (g_clk_asp_hdmi.clk_hdmi_m != NULL) {
        clk_put(g_clk_asp_hdmi.clk_hdmi_m);
        g_clk_asp_hdmi.clk_hdmi_m = NULL;
    }

    if (g_clk_asp_hdmi.clk_hdmi_s != NULL) {
        clk_put(g_clk_asp_hdmi.clk_hdmi_s);
        g_clk_asp_hdmi.clk_hdmi_s = NULL;
    }

    if (g_clk_asp_hdmi.clk_asphdmi_adws != NULL) {
        clk_put(g_clk_asp_hdmi.clk_asphdmi_adws);
        g_clk_asp_hdmi.clk_asphdmi_adws = NULL;
    }

    if (g_clk_asp_hdmi.clk_asphdmi_bclk != NULL) {
        clk_put(g_clk_asp_hdmi.clk_asphdmi_bclk);
        g_clk_asp_hdmi.clk_asphdmi_bclk = NULL;
    }
}

/* de-reset */
static void hi6620_digital_dereset(void)
{
    IN_FUNCTION;



    phy_reg_writel(REG_BASE_SC_OFF,
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_ADDR(CALC_REG_OFFSET),
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_3ac_START,
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_3ac_END, 1);
    phy_reg_writel(REG_BASE_SC_OFF,
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_ADDR(CALC_REG_OFFSET),
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_5ahdmi_START,
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_5ahdmi_END, 1);
    phy_reg_writel(REG_BASE_SC_OFF,
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_ADDR(CALC_REG_OFFSET),
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_16aspdif_START,
                       SOC_SCTRL_SC_PERIPH_RSTDIS2_periph_rstdis2_16aspdif_END, 1);

    OUT_FUNCTION;
}

static int __devinit hi6620_digital_platform_probe(struct platform_device *pdev)
{
    int ret = -ENODEV;
    struct resource* res;

    IN_FUNCTION;

    memset(&g_clk_asp_hdmi, 0, sizeof(g_clk_asp_hdmi));
    /* get ASP clock n*/
    g_clk_asp_hdmi.clk_asphdmi_ref = clk_get(NULL, CLK_ASP_HDMI_REF);
    if (IS_ERR(g_clk_asp_hdmi.clk_asphdmi_ref)) {
        loge("%s : Could not get clk_asphdmi_ref\n", __FUNCTION__);
        goto probe_failed;
    }

    /* get ASPHDMI mclk */
    g_clk_asp_hdmi.clk_hdmi_m = clk_get(NULL, CLK_MCLK_HDMI/*CLK_MCLK_HDMI*/);
    if (IS_ERR(g_clk_asp_hdmi.clk_hdmi_m)) {
        loge("%s : Could not get clk_hdmi_m\n", __FUNCTION__);
        goto probe_failed;
    }
    g_clk_asp_hdmi.clk_hdmi_s = clk_get(NULL, CLK_HDMI_SCK/*CLK_HDMI_SCK*/);
    if (IS_ERR(g_clk_asp_hdmi.clk_hdmi_s)) {
        loge("%s : Could not get clk_hdmi_s\n", __FUNCTION__);
        goto probe_failed;
    }
#ifdef CONFIG_MACH_HI6620OEM
    g_clk_asp_hdmi.clk_asp_cfg= clk_get(NULL, CLK_ASP_CFG);
    if (IS_ERR(g_clk_asp_hdmi.clk_asp_cfg)) {
        loge("%s : Could not get clk_asp_cfg\n", __FUNCTION__);
        goto probe_failed;
    }
#else
    g_clk_asp_hdmi.clk_asp_cfg= clk_get(NULL, CLK_HDMI_SCK);
    if (IS_ERR(g_clk_asp_hdmi.clk_asp_cfg)) {
        loge("%s : Could not get clk_asp_cfg\n", __FUNCTION__);
        goto probe_failed;
    }  
#endif

    /* get ASPSPDIF clk */
    g_clk_asp_hdmi.clk_aspspdif = clk_get(NULL, CLK_ASP_SPDIF_REF);
    if (IS_ERR(g_clk_asp_hdmi.clk_aspspdif)) {
        loge("%s : Could not get clk_aspspdif\n", __FUNCTION__);
        goto probe_failed;
    }

    /* get ASPSIO clk */
    g_clk_asp_hdmi.clk_asphdmi_adws = clk_get(NULL, CLK_ASP_HDMI_ADWS);
    if (IS_ERR(g_clk_asp_hdmi.clk_asphdmi_adws)) {
        loge("%s : Could not get clk_asphdmi_adws\n", __FUNCTION__);
        goto probe_failed;
    }
    g_clk_asp_hdmi.clk_asphdmi_bclk = clk_get(NULL, CLK_ASP_HDMI_BCLK);
    if (IS_ERR(g_clk_asp_hdmi.clk_asphdmi_bclk)) {
        loge("%s : Could not get clk_asphdmi_bclk\n", __FUNCTION__);
        goto probe_failed;
    }

    /* get pmuspi register base address */
    res = platform_get_resource_byname(pdev, IORESOURCE_IRQ, "asp_irq");
    if (!res) {
        loge("%s: Could not get irq line\n", __FUNCTION__);
        goto probe_failed;
    }
    g_hi6620_asp_irq_line = res->start;

    /* get pmuspi register base address */
    res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "asp_base");
    if (!res) {
        loge("%s: Could not get register base\n", __FUNCTION__);
        goto probe_failed;
    }
    g_hi6620_asp_reg_base_addr =
            (unsigned int)ioremap(res->start, resource_size(res));

    /* register dai (name : hi6620-digital) */
    ret = snd_soc_register_dais(&pdev->dev, hi6620_digital_dai, ARRAY_SIZE(hi6620_digital_dai));
    if (ret) {
        loge("%s: snd_soc_register_dai return %d\n", __FUNCTION__ ,ret);
        goto probe_failed;
    }

    /* register platform (name : hi6620-digital) */
    ret = snd_soc_register_platform(&pdev->dev, &hi6620_digital_platform);
    if (ret) {
        loge("%s: snd_soc_register_platform return %d\n", __FUNCTION__ ,ret);
        goto probe_failed;
    }
    hi6620_digital_dereset();

    OUT_FUNCTION;

    return ret;

probe_failed:
    hi6620_digital_platform_close_clocks();

    OUT_FUNCTION;
    return ret;
}

static int __devexit hi6620_digital_platform_remove(struct platform_device *pdev)
{
    snd_soc_unregister_platform(&pdev->dev);
    snd_soc_unregister_dais(&pdev->dev, ARRAY_SIZE(hi6620_digital_dai));
    hi6620_digital_platform_close_clocks();
    return 0;
}

static struct platform_driver hi6620_digital_platform_driver = {
    .driver = {
        .name = "hi6620-aspdigital",
        .owner = THIS_MODULE,
    },
    .probe  = hi6620_digital_platform_probe,
    .remove = __devexit_p(hi6620_digital_platform_remove),
};

static int status_read_proc_astatus(char *page, char **start, off_t offset,
                    int count, int *eof, void *data)
{
    *eof = 1;
    return sprintf(page, "%d", g_digitaloutStatus);
}

static int status_write_proc_astatus(struct file *file, const char *buffer,
                    unsigned long count, void *data)
{
    char buf[64] = {0};
    int value = 0;

    if (count < 1)
        return -EINVAL;
    if (count > 60)
        count  = 60;

    if (copy_from_user(buf, buffer, count)) {
        loge("copy_from_user Error\n");
        return -EFAULT;
    }
    if (sscanf(buf, "0x%8x", &value) != 1) {
        logi("set the audiostatus error\r\n");
    }
    logi("get the audiostatus %d\r\n",value);
    g_spdifout = value >> 16; //SPDIF output config
    g_digitaloutStatus = value & 0xffff;

    return count;
}

static int status_read_proc_aformat(char *page, char **start, off_t offset,
                    int count, int *eof, void *data)
{
    *eof = 1;
    return sprintf(page, "%d", g_aformat);
}


static int status_write_proc_aformat(struct file *file, const char *buffer,
                    unsigned long count, void *data)
{
    char buf[64] = {0};

    if (count < 1) {
        loge("count(%ld) < 1\n", count);
        return -EINVAL;
    }
    if (count > 60)
        count  = 60;

    if (copy_from_user(buf, buffer, count)) {
        loge("copy_from_user Error\n");
        return -EFAULT;
    }
    if (sscanf(buf, "0x%8x", &g_aformat) != 1) {
        loge("set the audiostatus error\r\n");
    }
    logi("get the audioformat=%d, count=%ld\r\n", g_aformat, count);

    return count;
}
static int __init hi6620_digital_init(void)
{
    struct proc_dir_entry *ent;

    IN_FUNCTION;

    audio_digital_dir = proc_mkdir("adigital", NULL);
    if (audio_digital_dir == NULL) {
        loge("Unable to create /proc/adigital directory");
        return -ENOMEM;
    }

    /* Creating read/write "status" entry */
    ent = create_proc_entry("status", 0777, audio_digital_dir);
    if (ent == NULL) {
        remove_proc_entry("adigital", 0);
        loge("Unable to create /proc/adigital/status entry");
        return -ENOMEM;
    }
    ent->read_proc = status_read_proc_astatus;
    ent->write_proc = status_write_proc_astatus;

    /* Creating read/write "format" entry */
    ent = create_proc_entry("format", 0777, audio_digital_dir);
    if (ent == NULL) {
        remove_proc_entry("status", audio_digital_dir);
        remove_proc_entry("adigital", 0);
        loge("Unable to create /proc/adigital/format entry");
        return -ENOMEM;
    }
    ent->read_proc = status_read_proc_aformat;
    ent->write_proc = status_write_proc_aformat;

    OUT_FUNCTION;

    return platform_driver_register(&hi6620_digital_platform_driver);
}
module_init(hi6620_digital_init);

static void __exit hi6620_digital_exit(void)
{
    remove_proc_entry("status", audio_digital_dir);
    remove_proc_entry("format", audio_digital_dir);
    remove_proc_entry("adigital", 0);
    platform_driver_unregister(&hi6620_digital_platform_driver);
}
module_exit(hi6620_digital_exit);

MODULE_AUTHOR("C00166660");
MODULE_DESCRIPTION("Hi6620 ASP digital driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:asp-digital");


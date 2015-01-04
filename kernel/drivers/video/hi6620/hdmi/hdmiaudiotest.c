#include <asm/uaccess.h>
#include <asm/atomic.h>
#include <asm/unistd.h>
#include <linux/bootmem.h>
#include <linux/cdev.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/ioctl.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/types.h>

#include "hdmitest.h"

#include "si_mhl_main.h"
#include "si_reg_access.h"
#include "si_drv_mhl_tx.h"
#include "k3_hdmi.h"
#include "edc_overlay.h"
#include "./../../../../sound/soc/hisilicon/hi6620_digital.h"


/****************
** Audio test  begin
****************/
#define PRINT_FILE_DATA	1


#define FILE_SIZE ( 1024 * 1024 )

unsigned char *RAW_FILE_ADDR_VA = NULL;
dma_addr_t RAW_FILE_ADDR_PA;


u32 asp_reg_baddr ;
u32 g_filesize;
u32 g_count;

u32 asp_read_reg(u16 idx)
{
    return __raw_readl(asp_reg_baddr + idx);
}

void asp_write_reg(u16 idx, u32 val)
{
    __raw_writel(val, asp_reg_baddr + idx);
}

static void write_reg(u32 base, u16 idx, u32 val)
{
    writel(val, base + idx);
    return;
}

static u32 read_reg(u32 base, u16 idx)
{
    return readl(base + idx);
}



void asp_load_file_to_memory_regions(char *filename, u32 addr, u32 size)
{
    mm_segment_t fs;
    struct file *fp;
    int file_flag = O_RDONLY;

    //must have the following 2 statement
    fs = get_fs();
    set_fs(KERNEL_DS);

    fp = filp_open(filename, file_flag, 0666);
    if (IS_ERR(fp)){
        printk("open file error!\n");
        return;
    }

    if(vfs_read(fp, (char *)addr, size, &fp->f_pos) < 0) {
        printk("read file error!\n");
    }


    //must have the following 1 statement
    set_fs(fs);

    if (fp)
    {
        filp_close(fp, 0);
    }
    printk("===%s===%s\n",__FUNCTION__, filename);
}

static int asp_allocate_memory_regions(u32 filesize)
{
    IN_FUNCTION;

	RAW_FILE_ADDR_VA = (unsigned char *)dma_alloc_coherent(NULL, filesize, &RAW_FILE_ADDR_PA, GFP_KERNEL);
    if(!RAW_FILE_ADDR_VA){
        printk("Failed to allocate memory for file!\n");
        return -1;
    }

	printk("..RAW_FILE_ADDR_VA = 0x%0x!\n", RAW_FILE_ADDR_VA);
	printk("..RAW_FILE_ADDR_PA = 0x%0x!\n", RAW_FILE_ADDR_PA);

	memset(RAW_FILE_ADDR_VA, 0x0, filesize);

    OUT_FUNCTION;
	return 0;
}

/*static*/ void alloc_dma_area(AUDIO_CHANNEL_TYPE chn, char *file_name)
{
    IN_FUNCTION;

    logi("chn = %d, file_name = %s\r\n", chn, file_name);
    	/* alloc and load file */
    	asp_allocate_memory_regions(g_filesize);
    	asp_load_file_to_memory_regions(file_name, RAW_FILE_ADDR_VA, g_filesize);



    OUT_FUNCTION;
}

void config_dma(AUDIO_CHANNEL_TYPE chn, char *file_name)
{
	u32 reg_val = 0 ;
	u32 reg_ofs = 0, reg_ofs_2 = 0;
	u32 reg_ofs_b = 0, reg_ofs_b_2 = 0;
    u32 dmasize;
    int i = 0;

    IN_FUNCTION;

    logi("chn=%d, file_name = %s\r\n", chn, file_name);

    /* DMA addr and size setting */
    if (chn == CHANNEL_TX2) {
        reg_val = 0xC0;
        reg_ofs     = ASP_TX2ASAR;
        reg_ofs_2   = ASP_TX2ADLR;
        reg_ofs_b   = ASP_TX2BSAR;
        reg_ofs_b_2 = ASP_TX2BDLR;
    } else if (chn == CHANNEL_TX3) {
        reg_val = 0x300;
        reg_ofs     = ASP_TX3ASAR;
        reg_ofs_2   = ASP_TX3ADLR;
        reg_ofs_b   = ASP_TX3BSAR;
        reg_ofs_b_2 = ASP_TX3BDLR;
    } else {
        loge("no valid chn\r\n");
        return;
    }
    dmasize = g_filesize/2;
    alloc_dma_area(chn, file_name);

    logi("reg_val=0x%x\r\n", reg_val);
    logi("reg_ofs=0x%x(0x%x), _2=0x%x(0x%x)\r\n", reg_ofs, RAW_FILE_ADDR_PA, reg_ofs_2, dmasize);
    logi("reg_ofs_b=0x%x(0x%x), b_2=0x%x(0x%x)\r\n", reg_ofs_b, RAW_FILE_ADDR_PA+dmasize, reg_ofs_b_2, dmasize);

#if PRINT_FILE_DATA
    unsigned int  * pu32VirAddr = (unsigned int *)(RAW_FILE_ADDR_VA);
        logi("pu32VirAddr = 0x%x\r\n", pu32VirAddr);
    if (NULL == pu32VirAddr) {
        loge("pu32VirAddr = 0x%x\r\n", pu32VirAddr);
        return;
    }
	for(i=0; i<16; i+=4)
	{
        printk("%#x : %#010x %#010x %#010x %#010x\n", pu32VirAddr + i*4,
                                    read_reg(pu32VirAddr, (i * 4)),
                                    read_reg(pu32VirAddr, (i+1) * 4),
                                    read_reg(pu32VirAddr, (i+2) * 4),
                                    read_reg(pu32VirAddr, (i+3) * 4)
                                    );
	}
    pu32VirAddr = (unsigned int *)(RAW_FILE_ADDR_VA+ dmasize-16);
	for(i=0; i<16; i+=4)
	{
        printk("%#x : %#010x %#010x %#010x %#010x\n", pu32VirAddr + i*4,
                                    read_reg(pu32VirAddr, (i * 4)),
                                    read_reg(pu32VirAddr, (i+1) * 4),
                                    read_reg(pu32VirAddr, (i+2) * 4),
                                    read_reg(pu32VirAddr, (i+3) * 4)
                                    );
	}
#endif

    /* disable DMA, clr INTR */
    asp_write_reg(ASP_DSTOP, reg_val);  // disable DMA
    asp_write_reg(ASP_ICR, reg_val);  // clr intr
    /* setting DMA addr and size */
    asp_write_reg(reg_ofs, RAW_FILE_ADDR_PA);
    asp_write_reg(reg_ofs_2, dmasize);
    asp_write_reg(reg_ofs_b, (RAW_FILE_ADDR_PA + dmasize));
    asp_write_reg(reg_ofs_b_2, dmasize);

    OUT_FUNCTION;

}

void config_channel(AUDIO_CHANNEL_TYPE chn, u32 audioFormat, u32 samplesize)
{
	u32 reg_val = 0, reg_ofs = 0, reg_dis = 0;
	u32 reg_val_2 = 0, reg_ofs_2 = 0;

    IN_FUNCTION;
    logi("chn=%d, audioFormat=%d, samplesize=%d\r\n", chn, audioFormat, samplesize);

    if (chn == CHANNEL_TX2) {
        reg_ofs = ASP_TX2;
        reg_dis = ASP_TX3;
        reg_val = TX2_EN_BIT | TX2_TSEN_BIT | HIGHBIT_IS_RIGHT;//enable TX2 and transparent and highbit is left

        switch(samplesize) {
        case 18:
            reg_val |= 0x4;
            break;
        case 20:
            reg_val |= 0x5;
            break;
        case 24:
            reg_val |= 0x6;
            break;
        case 16:
        default:
            break;
        }

        reg_val_2 = 0x04;
    } 
    else if (chn == CHANNEL_TX3)
    {
        /*
        bit 4 : TX3 透传使能
        bit 2 : TX3通道使能
        bit 0-1 : TX3通道音频数据格式选择
        */
        reg_ofs = ASP_TX3;
        reg_dis = ASP_TX2;
        reg_val = TX3_EN_BIT |TX3_TSEN_BIT;//enable TX3 and transparent


        switch(samplesize) {
        case 18:
            reg_val |= 0x1;
            break;
        case 20:
            reg_val |= 0x2;
            break;
        case 24:
            reg_val |= 0x3;
            break;
        case 16:
        default:
            break;
        }

        /* new audio */
        reg_val_2 = 0x08;

    } 
    else 
    {
        loge("chn = %d\r\n", chn);
        return;
    }
    
    logi("reg_ofs=0x%x(0x%x, 0x%x)\r\n", reg_ofs, reg_val, reg_val_2);


    /* disable another tx */
    asp_write_reg(reg_dis, 0x00);
    asp_write_reg(reg_ofs, reg_val);
    asp_write_reg(ASP_TXNSSR/*ASP_PCMNSSR*/, reg_val_2); /* new audio */

    OUT_FUNCTION;
}

void config_sio_spdif(AUDIO_IF_TYPE if_type, u32 audioFormat, u32 SampleFreq, u32 samplesize)
{
       u32 spdif_status[6]={0};

       /*                    16   17   18   19   20   21   22   23   24  */
       u8 samplesizeValue[]={0x2, 0xC, 0x4, 0x8, 0xA, 0xD, 0x5, 0x9, 0xB};

    IN_FUNCTION;
    logi("if_type=%d, audioFormat = %d, SampleFreq=%d,  samplesize=%d\r\n", if_type, audioFormat,SampleFreq,samplesize);

    if (if_type == IF_SPDIF) {
        asp_write_reg(ASP_SPDIFSELR, 0x01);
        asp_write_reg(SPDIF_CTRL, 0x1);
        asp_write_reg(SPDIF_INTRUPT, 0x7); //CLEAR INT

    switch (SampleFreq) {
        case 48000:
            spdif_status[3] = 0x0202;
            spdif_status[4] = 0xD0D0;
            break;
        case 44100:
            spdif_status[3] = 0x0000;
            spdif_status[4] = 0xF0F0;
            break;
        case 32000:
            spdif_status[3] = 0x0303;
            spdif_status[4] = 0xC0C0;
            break;
        case 88200:
            spdif_status[3] = 0x0808;
            spdif_status[4] = 0x7070;
            break;
        case 96000:
            spdif_status[3] = 0x0A0A;
            spdif_status[4] = 0x5050;
            break;
        case 192000:
            spdif_status[3] = 0x0E0E;
            spdif_status[4] = 0x1010;
            break;
        case 176400:
            spdif_status[3] = 0x0C0C;
            spdif_status[4] = 0x3030;
            break;
        default:
            logw("sample freq is invalid: %d. \n", SampleFreq);
            OUT_FUNCTION;
    		return ;
        }

        spdif_status[4] |= samplesizeValue[samplesize-16];
        spdif_status[4] |= (samplesizeValue[samplesize-16] << 4);
    
        if(audioFormat == AFORMAT_PCM)
        {
            spdif_status[0] = 0x0404;
            spdif_status[1] = 0x0202;
            spdif_status[5] = 0;
        }
        else
        {
            spdif_status[0] = 0x0606;
            spdif_status[1] = 0x0000;
            spdif_status[5] = 1;
            //asp_write_reg(ASP_TX2, 0x178);
        }

        spdif_status[2] = 0x2010;
        
        asp_write_reg(SPDIF_CH_STATUS1, spdif_status[0]);
        asp_write_reg(SPDIF_CH_STATUS2, spdif_status[1]);
        asp_write_reg(SPDIF_CH_STATUS3, spdif_status[2]);
        asp_write_reg(SPDIF_CH_STATUS4, spdif_status[3]);
        asp_write_reg(SPDIF_CH_STATUS5, spdif_status[4]);

        asp_write_reg(SIO1_CLR, BIT0); //clear fifo

        asp_write_reg(SPDIF_CTRL, 0x5); //fifo 100    enable 1
        asp_write_reg(SPDIF_CONFIG, spdif_status[5]); //line pcm 0, direct audio 1
    } 
    else if (if_type == IF_HDMI)
    {
        asp_write_reg(ASP_SPDIFSELR, 0x00);
        asp_write_reg(SIO1_ASPIF_SEL, 0x1); // normal mode
        asp_write_reg(SIO1_INT_CLR, BIT1); 
        asp_write_reg(SIO1_INT_ENABLE, BIT1);  // bit 1: 发送中断使能
        asp_write_reg(SIO1_I2S_CLR, SIO_TX_ENABLE | SIO_TX_FIFO); //clear setting
        asp_write_reg(SIO1_I2S_SET, SIO_TX_ENABLE | SIO_TX_FIFO); //set i2s mode
        asp_write_reg(SIO1_CLR, BIT0); //clear fifo
    }
    
    OUT_FUNCTION;

}

void cfg_asp_init( u32 filesize, u32 count)
{
    asp_reg_baddr =ioremap(REG_BASE_ASP, REG_ASP_IOSIZE);//IO_ADDRESS(HI3620_ASP_BASE);
    g_filesize = filesize;
    g_count = count;
}

void cfg_asp_clk(u32 SampleFreq)
{
        logi("ASP dereset&clock Begin\r\n");
    /*
    dereset
    */
    soc_sctrl_reg_wr(0x6DC/*SC_PERIPH_RSTDIS2*/, 3/*periph_rstdis2_3ac*/, 3, 0x01);
    soc_sctrl_reg_wr(0x6DC/*SC_PERIPH_RSTDIS2*/, 5/*periph_rstdis2_5ahdmi*/, 5, 0x01);
    soc_sctrl_reg_wr(0x6DC/*SC_PERIPH_RSTDIS2*/, 16/*periph_rstdis2_16aspdif*/, 16, 0x01);

    /*
    clock disable
    */
    soc_sctrl_reg_wr(0x628/*SC_PERIPH_CLKEN3*/, 2/*periph_clken3_asp_cfg_clk*/, 2, 0x01);
    /* bit4: periph_clken3_clk_asp_hdmi_bclk
       bit5: periph_clken3_clk_asp_hdmi_ref
       bit6: periph_clken3_clk_asp_hdmi_adws */
    soc_sctrl_reg_wr(0x628/*SC_PERIPH_CLKEN3*/, 3, 6, 0x0F);
    soc_sctrl_reg_wr(0x628/*SC_PERIPH_CLKEN3*/, 27/*periph_clken3_clk_asp_spdif_ref*/, 27, 0x01);

    /*
    clock rate setting
    */
    logi("SC_CLKCFGALL3=0x%x  SC_CLKCFGALL4=0x%x\n",
                                soc_sctrl_reg_rd(0xC8C),soc_sctrl_reg_rd(0xC90));

    soc_sctrl_reg_wr(0xC90/*SC_CLKCFGALL4*/, 0/*divfrac_49m*/, 23, 11106178/2*100/(19200000/SampleFreq));
    logi("SC_CLKCFGALL3=0x%x  SC_CLKCFGALL4=0x%x\n",
                                soc_sctrl_reg_rd(0xC8C),soc_sctrl_reg_rd(0xC90));

    /*
    clock enable
    */
    soc_sctrl_reg_wr(0x624/*SC_PERIPH_CLKEN3*/, 2/*periph_clken3_asp_cfg_clk*/, 2, 0x01);
    /* bit4: periph_clken3_clk_asp_hdmi_bclk
       bit5: periph_clken3_clk_asp_hdmi_ref
       bit6: periph_clken3_clk_asp_hdmi_adws */
    soc_sctrl_reg_wr(0x624/*SC_PERIPH_CLKEN3*/, 3, 6, 0x0F);
    soc_sctrl_reg_wr(0x624/*SC_PERIPH_CLKEN3*/, 27/*periph_clken3_clk_asp_spdif_ref*/, 27, 0x01);

    logi("ASP dereset&clock End\r\n");

}
/*
a_format:
    bit 0-2 : 0-STEREO_16BIT
    bit 3   : 1-TX_TRANSPARENT
AUDIO_CHANNEL_TYPE
    CHANNEL_TX2 = 0,
    CHANNEL_TX3
AUDIO_DATA_TYPE
    DATA_PCM_48K = 0,
    DATA_PCM_96K,
    DATA_AC3
AUDIO_IF_TYPE
    IF_HDMI = 0,
    IF_SPDIF
AUDIO_TX_TYPE
    TX_NORMAL = 0,
    TX_TRANSPARENT = 0x08,
*/
void cfg_asp(AUDIO_CHANNEL_TYPE chann_typ, AUDIO_IF_TYPE if_typ,
                   u32 audioFormat, u32 SampleFreq, u32 samplesize, char *file_name)
{
    IN_FUNCTION;

    logi("chann_typ=%d, audioFormat=%d, if_typ=%d, SampleFreq=%d, samplesize=%d, file_name=%s, g_filezie=0x%x\n",
                                chann_typ, audioFormat, if_typ, SampleFreq, samplesize,file_name,g_filesize);

    /* dma */
    config_dma(chann_typ, file_name);

    /* channel */
    config_channel(chann_typ, audioFormat, samplesize);

    /* sio */
    config_sio_spdif(if_typ, audioFormat, SampleFreq, samplesize);

    OUT_FUNCTION;
}

static void free_memory_regions(void)
{
    IN_FUNCTION;

	if(RAW_FILE_ADDR_VA){
	    dma_free_coherent(NULL, FILE_SIZE, (void*)RAW_FILE_ADDR_VA, RAW_FILE_ADDR_PA);
	}

    OUT_FUNCTION;
}
void rpt(AUDIO_CHANNEL_TYPE chn, int count)
{
    IN_FUNCTION;
    int channel_enable = 0;
	u32 reg_val = 0, reg_ofs = 0;
	u32 reg_val_2 = 0, reg_ofs_2 = 0;

    if (chn == CHANNEL_TX2) {
        channel_enable = 0xc0;
        reg_ofs = 0x140/*ASP_P2ADL, 0-19bit*/;
        reg_ofs_2 = 0x144/*ASP_P2BDL, 0-19bit*/;
    } else if (chn == CHANNEL_TX3) {
        channel_enable = 0x300;
        reg_ofs = 0x148/*ASP_P3ADL, 0-19bit*/;
        reg_ofs_2 = 0x14C/*ASP_P3BDL, 0-19bit*/;
    } else {
        channel_enable = 0xc0;
    }

    //enable int
    asp_write_reg(ASP_IER, channel_enable);
    //enable dma
    asp_write_reg(ASP_DER, channel_enable);

	while(count--)
	{
		printk("count = %d \n",count);

        reg_val = asp_read_reg(reg_ofs);
        reg_val_2 = asp_read_reg(reg_ofs_2);
        printk("==pXadl %#010x, pXbdl %#010x\n", reg_val, reg_val_2);

		while(1)
		{
            msleep(100);
            reg_val = asp_read_reg(reg_ofs);
            reg_val_2 = asp_read_reg(reg_ofs_2);
            printk("=====pXadl %#010x, pXbdl %#010x\n", reg_val, reg_val_2);

            reg_val = asp_read_reg(0x28/*ASP_IMSR, 1:有中断*/);
            reg_val_2 = asp_read_reg(0x20/*ASP_IRSR, 1:有中断*/);
            printk("=====imsr %#010x(r=%#010x)\n", reg_val, reg_val_2);

            if( channel_enable & reg_val ) break;
		}
        reg_val = asp_read_reg(ASP_DER);
		printk("asp_der = %#010xs\n", reg_val);

        reg_val = asp_read_reg(0x28);
        asp_write_reg(ASP_ICR, reg_val);
        asp_write_reg(ASP_DER, reg_val);
	}
	free_memory_regions();

    OUT_FUNCTION;
}

extern hdmi_device hdmi;
/*
typedef enum{
    AFORMAT_RESERVED = 0,
    AFORMAT_PCM,
    AFORMAT_AC3,
    AFORMAT_MPEG1,
    AFORMAT_MP3,
    AFORMAT_MPEG2,  //5
    AFORMAT_AAC,
    AFORMAT_DTS,
    AFORMAT_ATRAC,
    AFORMAT_OBA,
    AFORMAT_DDP,  // 10
    AFORMAT_DTSHD,
    AFORMAT_MAT_MLP,
    AFORMAT_DST,
    AFORMAT_WMAP,
    AFORMAT_MULTI_PCM, // 15   5.1/ 7.1 pcm
}AUDIO_FORMAT;
*/
void cfg_mhl(int sample_freq, u32 samplesize, bool bsio, u32 layout, u32 audiotype)
{
        dump_mhl_reg();
        hdmi.audiochanged = true;
        
        k3_hdmi_audio_set_param(sample_freq, samplesize, bsio, layout, audiotype);
        k3_hdmi_audio_set_power(true);
        
        dump_mhl_reg();
        hdmi.audiochanged = false;
}

void TestAudioAll(int sample_freq, u32 samplesize, u32 bsio, u32 chan_num, u32 audioformat, char* file_name)
{
        AUDIO_CHANNEL_TYPE chann_typ;
        AUDIO_IF_TYPE if_typ;
        hdmi_sample_size bit_typ;
        bool bi2s;

        cfg_asp_clk(sample_freq);

        switch(samplesize)
            {
            case 16:bit_typ = HDMI_SAMPLE_16BITS;break;
            case 20:bit_typ = HDMI_SAMPLE_20BITS;break;
            case 24:bit_typ = HDMI_SAMPLE_24BITS;break;
            default:break;
            }
        if(0 != (bsio&0x1))
            {
                if_typ = IF_HDMI;
                bi2s = true;
            }
        else
            {
                if_typ = IF_SPDIF;
                bi2s = false;
            }
        if(0 != (bsio&0x2))
            {
                chann_typ = CHANNEL_TX2;
            }
        else
            {
                chann_typ = CHANNEL_TX3;
            }

        cfg_mhl(sample_freq, bit_typ, bi2s, (chan_num-2), audioformat);

        cfg_asp(chann_typ, if_typ, audioformat, sample_freq, samplesize,file_name);

        rpt(chann_typ, g_count);
        
}

#if 1
const audioConfig_t audioData[16] =                     
{
    //I2S, 2ch, 192k, dowsamling 4:1 to 48K
    {0x11, 0x40, 0x0E, 0x03, 0x00, 0x01},

    //I2S, 2ch, 96k, dowsamling 2:1 to 48K
    {0x11, 0x40, 0x0A, 0x01, 0x00, 0x01},

    //I2S, 2ch, 48k
    {0x11, 0x40, 0x02, 0x00, 0x00, 0x01},

    //I2S, 2ch, 176k, dowsamling 4:1
    {0x11, 0x40, 0x0C, 0x03, 0x00, 0x01},

    //I2S, 2ch, 88k, dowsamling 2:1
    {0x11, 0x40, 0x08, 0x01, 0x00, 0x01},

    //I2S, 2ch, 44k
    {0x11, 0x40, 0x00, 0x00, 0x00, 0x01},

    //I2S, 2ch, 32k
    {0x11, 0x40, 0x03, 0x00, 0x00, 0x01},

    //TDM, 2ch, 192k, dowsamling 4:1
    {0x11, 0x40, 0x0E, 0x03, 0x03, 0x05},

    //TDM, 2ch, 96k, dowsamling 2:1
    {0x11, 0x40, 0x0A, 0x01, 0x03, 0x05},

    //TDM, 2ch, 48k
    {0x11, 0x40, 0x02, 0x00, 0x03, 0x05},

    //TDM, 2ch, 176k, dowsamling 4:1
    {0x11, 0x40, 0x0C, 0x03, 0x03, 0x05},

    //TDM, 2ch, 88k, dowsamling 2:1
    {0x11, 0x40, 0x08, 0x01, 0x03, 0x05},

    //TDM, 2ch, 44k
    {0x11, 0x40, 0x00, 0x00, 0x03, 0x05},

    //TDM, 2ch, 32k
    {0x11, 0x40, 0x03, 0x00, 0x03, 0x05},

    //TDM, 8ch, 192k
    {0xF1, 0x40, 0x0E, 0x00, 0x03, 0x07},

    //SPDIF
    {0x03, 0x00, 0x00, 0x00, 0x00, 0x05}
};
static void SetAudioMode(K3_AudioType)//设置HDMI enable  / channel通道/ 上升沿触发sd 和ws source  / 频率
{
    //Set I2S 48K as the default input mode.

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUDP_TXCTRL_ADDR & 0x00FF,
                               audioData[K3_AudioType].regAUD_path);
 dump_mhl_reg();

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_AUD_MODE_ADDR & 0x00FF,
                               audioData[K3_AudioType].regAUD_mode);
 dump_mhl_reg();

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_IN_CTRL_ADDR & 0x00FF,
                               audioData[K3_AudioType].regAUD_ctrl);
 dump_mhl_reg();

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_CHST4_ADDR & 0x00FF,
                               audioData[K3_AudioType].regAUD_freq);
 dump_mhl_reg();

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_ASRC_ADDR & 0x00FF,
                               audioData[K3_AudioType].regAUD_src);
 dump_mhl_reg();

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_I2S_CHST5_ADDR & 0x00FF, 0x0B); //24bit audio
 dump_mhl_reg();

    SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_SPDIF_CTRL_ADDR & 0x00FF, 0x00); //Disable FS override
 dump_mhl_reg();
}

static void SetACRNValue (void)//设置采样率
{
    u32 audioFs;

    if ((SiiDrvReadIndexedRegister(INDEXED_PAGE_1,
                                   P1_AUD_MODE_ADDR) & BIT1) && (!(SiiDrvReadIndexedRegister(INDEXED_PAGE_1, P1_SPDIF_CTRL_ADDR) & BIT1)))
    {
        audioFs = SiiDrvReadIndexedRegister(INDEXED_PAGE_1, P1_SPDIF_FS_ADDR) & 0x0F;
    }
    else
    {
        audioFs = SiiDrvReadIndexedRegister(INDEXED_PAGE_1, P1_I2S_CHST4_ADDR) & 0x0F;
    }
 dump_mhl_reg();

    switch (audioFs)
    {
    case 0x03:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_32k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_32k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_32k));
        break;
    case 0x00:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_44k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_44k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_44k));
        break;
    case 0x02:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_48k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_48k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_48k));
        break;
    case 0x08:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_88k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_88k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_88k));
        break;
    case 0x0A:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_96k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_96k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_96k));
        break;
    case 0x0C:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_176k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_176k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_176k));
        break;
    case 0x0E:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_192k >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_192k >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_192k));
        break;
    default:
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL3_ADDR, (u8)(ACR_N_value_default >> 16));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL2_ADDR, (u8)(ACR_N_value_default >> 8));
        SiiDrvWriteIndexedRegister(INDEXED_PAGE_1, P1_N_SVAL1_ADDR, (u8)(ACR_N_value_default));
        break;
    }
 dump_mhl_reg();

    //Register Position changed.  8/21/2012
    //SiiDrvRegModify(REG_AUDP_TXCTRL, BIT2, CLEAR_BITS);                     //Mute off
    //SiiDrvReadModifyWriteIndexedRegister(INDEXED_PAGE_1, REG_AUDP_TXCTRL, BIT2, CLEAR_BITS);
}

//////////////////////////////////////////////////////////////////////////////
//
// FUNCTION      :  SendAudioInfoFrame()
//
// PURPOSE       :  Load Audio InfoFrame data into registers and send to sink
//
// INPUT PARAMS  :  (1) Channel count (2) speaker configuration per CEA-861D
//                  Tables 19, 20 (3) Coding type: 0x09 for DSD Audio. 0 (refer
//                                      to stream header) for all the rest (4) Sample Frequency. Non
//                                      zero for HBR only (5) Audio Sample Length. Non zero for HBR
//                                      only.
//
// OUTPUT PARAMS :  None
//
// GLOBALS USED  :  None
//
// RETURNS       :  TRUE
//
//////////////////////////////////////////////////////////////////////////////
static void SendAudioInfoFrame (void)
{
    if (1)//g_PlumTxConfig.EDID.HDMI_Sink)
    {
        u8 ifData[SIZE_AUDIO_INFOFRAME]={0};
        u32 i;

        ifData[0] = 0x84;
        ifData[1] = 0x01;
        ifData[2] = 0x0A;
        for (i = 3; i < SIZE_AUDIO_INFOFRAME; ++i)
        {
            ifData[i] = 0;
        }

        ifData[4] = 0x01; 
        ifData[3] = CalculateGenericCheckSum(ifData, 0, SIZE_AUDIO_INFOFRAME);

        SiiDrvWriteByteTPI(TPI_I_F_SELECT_ADDR,
                       BIT_TPI_INFO_EN
                       | BIT_TPI_INFO_RPT
                       | BIT_TPI_INFO_READ_FLAG_NO_READ
                       | BIT_TPI_INFO_SEL_Audio
        );
        SiiDrvWriteBlockTPI(TPI_I_F_TYPE_ADDR, SIZE_AUDIO_INFOFRAME, ifData);
 dump_mhl_reg();

        //printk( ("REG_TPI_INFO_BYTE13: %02x\n", REG_TPI_INFO_BYTE13));
    }
}

void K3TestAudio(inAudioTypes_t K3_AudioType)
{
            printk("before audio 0x1a is %02x\n", SiiDrvReadByteTPI(0x1A*4));
            SetAudioMode(K3_AudioType);
			printk("after setAudioMode\n");

            SetACRNValue();

            SendAudioInfoFrame();

}

#endif

void configEDC_3DFBF()
{    
    unsigned int width = 1280;//timing->x_res;
    unsigned int height = 1470;//timing->y_res;  
    unsigned int hsw = 40;//timing->hsw;
    unsigned int hfp = 440;//timing->hfp;
    unsigned int hbp = 220;//timing->hbp;
    unsigned int vsw = 5;//timing->vsw;
    unsigned int vfp = 5;//timing->vfp;
    unsigned int vbp = 20;//timing->vbp; 
 
    unsigned int base = (unsigned int)IO_ADDRESS(0xfa206000);
        
    unsigned int height_width = 0;
    unsigned int hbp_hfp = 0;
    unsigned int vbp_vfp = 0;
    
    height_width += (height - 1);
    height_width <<= 20;
    height_width += (width - 1);
    
    hbp_hfp += hbp;
    hbp_hfp <<= 20;
    hbp_hfp += hfp;
    
    vbp_vfp += vbp;
    vbp_vfp <<= 20;
    vbp_vfp += vfp;
    
    printk("ENTER configEDC!!!\n");
#if 1
    write_reg(base,0x814,height_width);
    write_reg(base,0x830,0x04);
   // write_reg(base,0x830,0x01);//v2pro test
    //write_reg(base,0x820,0xed1);
    write_reg(base,0x820,0xfd1);//v2pro test
    write_reg(base,0x800,hbp_hfp);
    write_reg(base,0x804,hsw-1);
    write_reg(base,0x808,vbp_vfp);
    write_reg(base,0x80c,vsw-1);
    //write_reg(base,0x810,0x3);
    write_reg(base,0x810,0x0);//v2pro test
#else
    write_reg(base,0x814,0x23f002cf);//0x23f002cf);
    //write_reg(base,0x830,0x04);
    write_reg(base,0x830,0x01);//v2pro test
    //write_reg(base,0x820,0xed1);
    write_reg(base,0x820,0xfd1);//v2pro test
    write_reg(base,0x800,0xc00044);
    write_reg(base,0x804,0x3f);
    write_reg(base,0x808,0x500027);
    write_reg(base,0x80c,0x4);
    //write_reg(base,0x810,0x3);
    write_reg(base,0x810,0x0);//v2pro test
#endif

#if 0//v2pro test
#define FILESIZE 1729440//2048//829440//5644854//7526454//1882678
    int i,j;
    u32 phyaddr = hisi_reserved_codec_phymem;
    u32* viraddr = (u32*)ioremap(phyaddr,HISI_MEM_CODEC_SIZE);
    asp_load_file_to_memory_regions("/data/rgb565.bin", viraddr,FILESIZE);
    for(i =0;i<30;i++){
        printk("viraddr[%d]=%x\n", i, viraddr[i]);
    }
    char* tempp = (char*)viraddr;
    for(j =0;j<30;j++){
        printk("viraddr[%d]=%x\n", FILESIZE-30+j, (char*)tempp[FILESIZE-30+j]);
    }


#if 1
    write_reg(base,0x04,(char*)phyaddr);
    write_reg(base,0x0c,0x5a0);
    write_reg(base,0x10,0x0);
    write_reg(base,0x14,0x2cf04b0);
    write_reg(base,0x18,0x01010000);
    write_reg(base,0x98,0xffff0);
    write_reg(base,0xd8,0x0);
    write_reg(base,0x90,0x2cf04b0);
    write_reg(base,0x94,0x3c000482);
#else
    write_reg(base,0x04,(char*)phyaddr);
    write_reg(base,0x0c,0x40);
    write_reg(base,0x10,0xf000f0);
    write_reg(base,0x14,0x01f001f);
    write_reg(base,0x18,0x01010000);
    write_reg(base,0x98,0xffff0);
    write_reg(base,0xd8,0x0);
    write_reg(base,0x90,0x4ff05bd);//0x2cf023f);
    write_reg(base,0x94,0x3c000482);
#endif
#endif
    printk("EXIT configEDC!!!\n");
    
}



/*
 *  hi6620_hi6421.c
 *  ALSA SoC
 *  cpu-dai   : Hi6620
 *  codec-dai : Hi6421
 */

#include <linux/clk.h>
#include <linux/kernel.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/soc.h>
#include <sound/jack.h>
#include <soc_baseaddr_interface.h>
#include <soc_sctrl_interface.h>
#include <asm/io.h>

static struct platform_device *hi6620_hi6421_snd_device;

static struct snd_soc_dai_link hi6620_hi6421_dai_link[] =
{
    {
        /* dai link name*/
        .name           = "Hi6620_Hi6421",
        /* stream name same as name */
        .stream_name    = "Hi6620_Hi6421",
        /* codec(hi6421) device name ,see in hi6421.c */
        .codec_name     = "hi6421-codec",
        /* cpu(v9r1:hifi) dai name(device name), see in hi6620-pcm.c */
        .cpu_dai_name   = "hi6620-mm",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6421.c */
        .codec_dai_name = "hi6421-dai",
        /* platform(v9r1:hifi) device name, see in hi6620-pcm.c */
        .platform_name  = "hi6620-hifi",
    },
    {
        .name           = "MODEM_HI6421",
        .stream_name    = "MODEM_HI6421",
        .codec_name     = "hi6421-codec",
        .cpu_dai_name   = "hi6620-modem",
        .codec_dai_name = "hi6421-dai",
        .platform_name  = "hi6620-hifi",
    },
    {
        .name           = "FM_HI6421",
        .stream_name    = "FM_HI6421",
        .codec_name     = "hi6421-codec",
        .cpu_dai_name   = "hi6620-fm",
        .codec_dai_name = "hi6421-dai",
        .platform_name  = "hi6620-hifi",
    },
    {
        .name           = "BT_HI6421",
        .stream_name    = "BT_HI6421",
        .codec_name     = "hi6421-codec",
        .cpu_dai_name   = "hi6620-bt",
        .codec_dai_name = "hi6421-dai",
        .platform_name  = "hi6620-hifi",
    },
#ifdef CONFIG_SND_ASP
    {
        .name           = "DIGITAL_HI6421",
        .stream_name    = "DIGITAL_HI6421",
        .codec_name     = "digital-audio",
        .cpu_dai_name   = "hi6620-digital",
        .codec_dai_name = "digital-audio-dai",
        .platform_name  = "hi6620-aspdigital",
    },
#endif
};

/* Audio machine driver */
static struct snd_soc_card snd_soc_hi6620_hi6421 =
{
    /* sound card name, can see all sound cards in /proc/asound/cards */
    .name       = "HI6620_HI6421_CARD",
    .dai_link   = hi6620_hi6421_dai_link,
    .num_links  = ARRAY_SIZE(hi6620_hi6421_dai_link),
};

static int hi6620_hi6421_probe(struct platform_device *pdev)
{
    int ret = 0;

    pr_info("%s Begin\n",__FUNCTION__);

    /*
        do board related job of hi6421 codec Begin
        be sure to place in the first place
    */
    /* spi_clkdiv，临时解决SPI分频配置引起的spi读问题 */
    #define SPI_CLKDIV_VAL                  (0x14)
    #define SPI_CLKDIV_VAL_START_BIT        (8)
    unsigned int sctrl_addr = (unsigned int)IO_ADDRESS(SOC_SC_OFF_BASE_ADDR);
    volatile unsigned int tmp_val = 0;

    tmp_val = readl(SOC_SCTRL_SC_PERIPH_CTRL2_ADDR(sctrl_addr));
    tmp_val = (tmp_val & (~(0xFF << SPI_CLKDIV_VAL_START_BIT))) | (SPI_CLKDIV_VAL << SPI_CLKDIV_VAL_START_BIT);
    writel(tmp_val, SOC_SCTRL_SC_PERIPH_CTRL2_ADDR(sctrl_addr));
    /* do board related job of hi6421 codec End */


    /* alloc soc sound card memory*/
    hi6620_hi6421_snd_device = platform_device_alloc("soc-audio", -1);
    if (!hi6620_hi6421_snd_device)
    {
        pr_err("%s : Unable to alloc memory for soc sound card\n",__FUNCTION__);
        return -ENOMEM;
    }

    snd_soc_hi6620_hi6421.dev = &pdev->dev;
    platform_set_drvdata(hi6620_hi6421_snd_device, &snd_soc_hi6620_hi6421);

    /* register soc sound card */
    ret = platform_device_add(hi6620_hi6421_snd_device);
    if (ret)
    {
        pr_err("%s : Unable to register sound card : %s\n",
                    __FUNCTION__, snd_soc_hi6620_hi6421.name);
        platform_device_put(hi6620_hi6421_snd_device);
    }

    pr_info("%s(spidiv=0x%x) End", __FUNCTION__, tmp_val);
    return ret;
}

static int hi6620_hi6421_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    if( snd_soc_hi6620_hi6421.dev != &pdev->dev )
    {
        pr_info("hi6620_hi6421_remove dev error\n");
        return -ENODEV;
    }

    platform_device_unregister(hi6620_hi6421_snd_device);

    return 0;
}

static struct platform_driver hi6620_hi6421_driver =
{
    .probe  = hi6620_hi6421_probe,
    .remove = hi6620_hi6421_remove,
    .driver =
    {
        .name    = "hi6620_hi6421",
        .owner   = THIS_MODULE,
    },
};

static int __init hi6620_hi6421_soc_init(void)
{
    pr_info("%s\n",__FUNCTION__);
    return platform_driver_register(&hi6620_hi6421_driver);
}

static void __exit hi6620_hi6421_soc_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&hi6620_hi6421_driver);
}

module_init(hi6620_hi6421_soc_init);
module_exit(hi6620_hi6421_soc_exit);

/* Module information */
MODULE_AUTHOR("S00212991");
MODULE_DESCRIPTION("Hi6620_Hi6421 ALSA SoC audio driver");
MODULE_LICENSE("GPL");

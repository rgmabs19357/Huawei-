/*
 *  hi6620_hi6401.c
 *  ALSA SoC
 *  cpu-dai   : Hi6620
 *  codec-dai : hi6401
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

static struct platform_device *hi6620_hi6401_snd_device;

static struct snd_soc_dai_link hi6620_hi6401_dai_link[] =
{
    {
        /* dai link name*/
        .name           = "Hi6620_hi6401",
        /* stream name same as name */
        .stream_name    = "Hi6620_hi6401",
        /* codec(hi6401) device name ,see in hi6401.c */
        .codec_name     = "hi6401-codec",
        /* cpu(v9r1:hifi) dai name(device name), see in hi6620-pcm.c */
        .cpu_dai_name   = "hi6620-mm",
        /* codec dai name, see in struct snd_soc_dai_driver in hi6401.c */
        .codec_dai_name = "hi6401-dai",
        /* platform(v9r1:hifi) device name, see in hi6620-pcm.c */
        .platform_name  = "hi6620-hifi",
    },
    {
        .name           = "MODEM_hi6401",
        .stream_name    = "MODEM_hi6401",
        .codec_name     = "hi6401-codec",
        .cpu_dai_name   = "hi6620-modem",
        .codec_dai_name = "hi6401-dai",
        .platform_name  = "hi6620-hifi",
    },
    {
        .name           = "FM_hi6401",
        .stream_name    = "FM_hi6401",
        .codec_name     = "hi6401-codec",
        .cpu_dai_name   = "hi6620-fm",
        .codec_dai_name = "hi6401-dai",
        .platform_name  = "hi6620-hifi",
    },
    {
        .name           = "BT_hi6401",
        .stream_name    = "BT_hi6401",
        .codec_name     = "hi6401-codec",
        .cpu_dai_name   = "hi6620-bt",
        .codec_dai_name = "hi6401-dai",
        .platform_name  = "hi6620-hifi",
    },
#ifdef CONFIG_SND_ASP
    {
        .name           = "DIGITAL_hi6401",
        .stream_name    = "DIGITAL_hi6401",
        .codec_name     = "digital-audio",
        .cpu_dai_name   = "hi6620-digital",
        .codec_dai_name = "digital-audio-dai",
        .platform_name  = "hi6620-aspdigital",
    },
#endif
};

/* Audio machine driver */
static struct snd_soc_card snd_soc_hi6620_hi6401 =
{
    /* sound card name, can see all sound cards in /proc/asound/cards */
    .name       = "HI6620_hi6401_CARD",
    .dai_link   = hi6620_hi6401_dai_link,
    .num_links  = ARRAY_SIZE(hi6620_hi6401_dai_link),
};

static int hi6620_hi6401_probe(struct platform_device *pdev)
{
    int ret = 0;

    pr_info("%s Begin\n",__FUNCTION__);




    /* alloc soc sound card memory*/
    hi6620_hi6401_snd_device = platform_device_alloc("soc-audio", -1);
    if (!hi6620_hi6401_snd_device)
    {
        pr_err("%s : Unable to alloc memory for soc sound card\n",__FUNCTION__);
        return -ENOMEM;
    }

    snd_soc_hi6620_hi6401.dev = &pdev->dev;
    platform_set_drvdata(hi6620_hi6401_snd_device, &snd_soc_hi6620_hi6401);

    /* register soc sound card */
    ret = platform_device_add(hi6620_hi6401_snd_device);
    if (ret)
    {
        pr_err("%s : Unable to register sound card : %s\n",
                    __FUNCTION__, snd_soc_hi6620_hi6401.name);
        platform_device_put(hi6620_hi6401_snd_device);
    }

    return ret;
}

static int hi6620_hi6401_remove(struct platform_device *pdev)
{
    pr_info("%s\n",__FUNCTION__);

    if( snd_soc_hi6620_hi6401.dev != &pdev->dev )
    {
        pr_info("hi6620_hi6401_remove dev error\n");
        return -ENODEV;
    }

    platform_device_unregister(hi6620_hi6401_snd_device);

    return 0;
}

static struct platform_driver hi6620_hi6401_driver =
{
    .probe  = hi6620_hi6401_probe,
    .remove = hi6620_hi6401_remove,
    .driver =
    {
        .name    = "hi6620_hi6401",
        .owner   = THIS_MODULE,
    },
};

static int __init hi6620_hi6401_soc_init(void)
{
    pr_info("%s\n",__FUNCTION__);
    return platform_driver_register(&hi6620_hi6401_driver);
}

static void __exit hi6620_hi6401_soc_exit(void)
{
    pr_info("%s\n",__FUNCTION__);
    platform_driver_unregister(&hi6620_hi6401_driver);
}

module_init(hi6620_hi6401_soc_init);
module_exit(hi6620_hi6401_soc_exit);

/* Module information */
MODULE_AUTHOR("hisilicon");
MODULE_DESCRIPTION("Hi6620_hi6401 ALSA SoC audio driver");
MODULE_LICENSE("GPL");

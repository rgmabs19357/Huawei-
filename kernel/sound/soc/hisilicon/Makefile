# HI3620 Platform Support
snd-soc-hi3620-objs := hi3620-pcm.o hi3620-digital.o

# HI3620-HI6421 Machine Support
snd-soc-hi3620-hi6421-objs := hi3620_hi6421.o

obj-$(CONFIG_SND_SOC_PCM_HI3620) += snd-soc-hi3620.o
obj-$(CONFIG_SND_HI3620_HI6421) += snd-soc-hi3620-hi6421.o

ifeq ($(CONFIG_K3_HDMI_SII9134),y)
EXTRA_CFLAGS := -DHDMI_DISPLAY
endif


# HI6620 Platform Support
ifeq ($(CONFIG_SND_ASP),y)
snd-soc-hi6620-objs := hi6620_pcm.o hi6620_digital.o
else
snd-soc-hi6620-objs := hi6620_pcm.o
endif

# HI6620-HI6421 Machine Support
snd-soc-hi6620-hi6421-objs := hi6620_hi6421.o
# HI6620-HI6401 Machine Support
snd-soc-hi6620-hi6401-objs := hi6620_hi6401.o

obj-$(CONFIG_SND_SOC_PCM_HI6620) += snd-soc-hi6620.o
obj-$(CONFIG_SND_HI6620_HI6421) += snd-soc-hi6620-hi6421.o
obj-$(CONFIG_SND_HI6620_HI6401) += snd-soc-hi6620-hi6401.o

ifeq ($(CONFIG_HI6620_HDMI_SII9134),y)
EXTRA_CFLAGS := -DHDMI_DISPLAY
endif

EXTRA_CFLAGS += -Idrivers/mailbox
EXTRA_CFLAGS += -Iarch/arm/mach-hi6620/include/mach/

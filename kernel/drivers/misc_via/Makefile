ifeq ($(EVDO_VIA_HAVE_VOLT_PROTECTION), yes)#if we have voltage protection in design
ccflags-y += -DOEM_HAVE_VOLT_PROTECTION
endif

ccflags-y += -DWAKE_HOST_BY_SYNC

obj-$(CONFIG_MISC_VIA) := core.o power.o oem.o sync.o
obj-$(CONFIG_MISC_VIA)	+= cbp_sdio.o modem_sdio.o
#obj-$(CONFIG_MISC_VIA) += f_rawbulk.o rawbulk.o rawbulk_transfer.o

obj-$(CONFIG_HI6620_HDMI_SII9134):= k3hdmi.o
#obj-m := k3hdmi.o
k3hdmi-objs :=  si_drv_mhl_tx.o si_edid.o si_mhl_hw.o si_mhl_main.o si_reg_access.o si_mhl_tx.o si_mhl_tx_rcp_table.o si_hdcp.o
obj-$(CONFIG_MACH_HI6620SFT)	+= mhl_phy_i2c.o

EXTRA_CFLAGS += -Idrivers/video/hi6620
EXTRA_CFLAGS += -Iarch/arm/mach-hi6620

ifeq ($(CONFIG_HDCP_ENABLE),y)
EXTRA_CFLAGS += -DUSE_HDCP=1
else
EXTRA_CFLAGS += -DUSE_HDCP=0
endif

all:
	make $(KERNEL_MAKE) M=$(PWD) modules
clean:
	make $(KERNEL_MAKE) M=$(PWD) clean
	rm *.o .*cmd

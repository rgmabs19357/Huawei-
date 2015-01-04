obj-$(CONFIG_FB_HI6620_CLCD) := k3fb.o
#obj-m := k3fb.o

k3fb-objs := edc_reg.o \
	ldi_reg.o \
	mipi_reg.o \
	sbl_reg.o \
	k3_fb_panel.o \
	fb_monitor.o\
	edc_overlay.o \
	mipi_dsi_host.o \
	k3_fb.o \
	ldi.o \
	mipi_dsi.o \
	backlight_pwm.o
	

EXTRA_CFLAGS += -Iarch/arm/mach-k3v2

ifeq ($(CONFIG_HI6620_HDMI_SII9134),y)
EXTRA_CFLAGS += -DHDMI_DISPLAY
endif

#KERNEL_MAKE := -C /home/z00176046/v200sdk/kernel

all:
	make $(KERNEL_MAKE) M=$(PWD) modules
clean:
	make $(KERNEL_MAKE) M=$(PWD) clean
#	rm *.o .*cmd

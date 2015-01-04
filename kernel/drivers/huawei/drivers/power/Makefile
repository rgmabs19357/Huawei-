obj-$(CONFIG_BATTERY_BQ27510) += bq27510_battery.o
obj-$(CONFIG_CHARGER_BQ2419x) += bq2419x_charger.o
obj-$(CONFIG_BQ_BCI_BATTERY) += bq_bci_battery.o
obj-$(CONFIG_BATTERY_HISI_SMARTSTAR)	+= hisi_battery_data.o hisi_smartstar_coul.o
obj-$(CONFIG_BATTERY_HISI_COUL)		+= hisi_coul_drv.o

EXTRA_CFLAGS = -Idrivers/huawei/device

ifeq ($(KERNELRELEASE),)

# KERNELDIR ?= /home/<AndroidKernelDirectory>
PWD := $(shell pwd)

.PHONY: build clean

build:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c
else

$(info Building with KERNELRELEASE = ${KERNELRELEASE})

endif


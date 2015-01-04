obj-$(CONFIG_RMI4_BUS) += fhd_rmi_bus.o
obj-$(CONFIG_RMI4_I2C) += fhd_rmi_i2c.o
obj-$(CONFIG_RMI4_SPI) += fhd_rmi_spi.o
obj-$(CONFIG_RMI4_GENERIC) += fhd_rmi_driver.o fhd_rmi_f01.o
obj-$(CONFIG_RMI4_FWLIB) += fhd_rmi_fw_update.o
obj-$(CONFIG_RMI4_F09) += fhd_rmi_f09.o
obj-$(CONFIG_RMI4_F1A) += fhd_rmi_f1a.o
obj-$(CONFIG_RMI4_F11) += fhd_rmi_f11.o
obj-$(CONFIG_RMI4_F17) += fhd_rmi_f17.o
obj-$(CONFIG_RMI4_F19) += fhd_rmi_f19.o
obj-$(CONFIG_RMI4_F21) += fhd_rmi_f21.o
obj-$(CONFIG_RMI4_F34) += fhd_rmi_f34.o
obj-$(CONFIG_RMI4_F54) += fhd_rmi_f54.o
obj-$(CONFIG_RMI4_DEV) += fhd_rmi_dev.o

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
obj-m +=    fhd_rmi_dev.o

endif


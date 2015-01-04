#Android makefile to build kernel as a part of Android Build

#ifeq ($(TARGET_PREBUILT_KERNEL),)

ifeq ($(OBB_PRODUCT_NAME),)
OBB_PRODUCT_NAME := $(HISI_TARGET_PRODUCT)
ifeq ($(HISI_TARGET_PRODUCT), hi6620sft)
OBB_PRODUCT_NAME := hi6620cs_sft
endif
ifeq ($(HISI_TARGET_PRODUCT), hi6620oem)	
OBB_PRODUCT_NAME := hi6620cs_oem_gutl_dsda
endif
endif

ifeq ($(BALONG_TOPDIR),)
BALONG_TOPDIR := $(shell pwd)/vendor/hisi
endif

ifeq ($(OBB_PRINT_CMD), true)
KERNEL_OUT := vendor/hisi/build/delivery/$(OBB_PRODUCT_NAME)/obj/android
else
KERNEL_OUT := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ
endif
KERNEL_CONFIG := $(KERNEL_OUT)/.config
TARGET_PREBUILT_KERNEL := $(KERNEL_OUT)/arch/arm/boot/zImage

include $(BALONG_TOPDIR)/build/scripts/make_base.mk


COMMON_HEAD := $(shell pwd)/kernel/drivers/
COMMON_HEAD += $(shell pwd)/kernel/mm/
COMMON_HEAD += $(shell pwd)/kernel/include/hisi/
COMMON_HEAD += $(shell pwd)/vendor/hisi/include/drv/
COMMON_HEAD += $(shell pwd)/vendor/hisi/include/med/
COMMON_HEAD += $(shell pwd)/vendor/hisi/include/drv/MODULE_H
COMMON_HEAD += $(shell pwd)/vendor/hisi/include/nv/gu/drv
COMMON_HEAD += $(shell pwd)/vendor/hisi/modem/drv/hi6620/src/comm/inc		
COMMON_HEAD += $(shell pwd)/vendor/hisi/modem/drv/common/src/comm/inc		
COMMON_HEAD += $(shell pwd)/vendor/hisi/config/nvim/include/gu/		
COMMON_HEAD += $(shell pwd)/kernel/drivers/hisi/nvim/	
COMMON_HEAD += $(shell pwd)/kernel/drivers/gpu/mali/platform/balong/
COMMON_HEAD += $(shell pwd)/kernel/drivers/gpu/mali/common/
COMMON_HEAD += $(shell pwd)/kernel/drivers/gpu/mali/linux/
ifeq ($(HISI_TARGET_PRODUCT), hi6620sft)
COMMON_HEAD += $(shell pwd)/vendor/hisi/platform/hi6620cs_sft/
endif
ifeq ($(HISI_TARGET_PRODUCT), hi6620oem)	
COMMON_HEAD += $(shell pwd)/vendor/hisi/platform/hi6620cs_asic/				
endif
ifeq ($(HISI_TARGET_PRODUCT), k3v2oem1)	
COMMON_HEAD += $(shell pwd)/vendor/hisi/platform/hi6620cs_sft/	
endif

COMMON_HEAD += $(shell pwd)/vendor/hisi/config/product/include/$(OBB_PRODUCT_NAME)/
COMMON_HEAD += $(shell pwd)/vendor/hisi/config/product/define/$(OBB_PRODUCT_NAME)/config/


ifneq ($(COMMON_HEAD),)
BALONG_INC := $(patsubst %,-I%,$(COMMON_HEAD))
else
BALONG_INC := 
endif
 
export BALONG_INC
export TARGET_BOARD_PLATFORM

KERNEL_ARCH_ARM_CONFIGS := $(shell pwd)/kernel/arch/arm/configs
KERNEL_GEN_CONFIG_FILE := hw_$(HW_PRODUCT)_defconfig
KERNEL_GEN_CONFIG_PATH := $(KERNEL_ARCH_ARM_CONFIGS)/$(KERNEL_GEN_CONFIG_FILE)

KERNEL_COMMON_DEFCONFIG := $(KERNEL_ARCH_ARM_CONFIGS)/$(KERNEL_DEFCONFIG)
KERNEL_PRODUCT_CONFIGS := $(shell pwd)/device/hisi/hi6620oem/product_spec/kernel_config/$(HW_PRODUCT)

GPIO_CONFIG_TARGET := $(KERNEL_OUT)/gpio_config

ifeq ($(OBB_PRINT_CMD), true)
$(GPIO_CONFIG_TARGET) : $(shell find device/hisi/hi6620/customize/hsad/ -name "ipps_para.xls")
$(GPIO_CONFIG_TARGET) : $(shell find device/hisi/hi6620/customize/hsad/ -name "gpio_mux.xls")
$(GPIO_CONFIG_TARGET) : $(shell find device/hisi/hi6620/customize/hsad/ -name "*_regulator_cfg.xls")
$(GPIO_CONFIG_TARGET) : $(shell find device/hisi/hi6620/customize/hsad/ -name "hw_configs.xml")
$(GPIO_CONFIG_TARGET) : $(shell find device/hisi/hi6620/customize/hsad/ -name "iomux_cfg.xls")
	+mkdir -p $(KERNEL_OUT)
	+@touch $@
else
.PHONY: $(GPIO_CONFIG_TARGET)
$(GPIO_CONFIG_TARGET) : FORCE
endif
	$(shell cd device/hisi/hi6620/customize/hsad;./xml2complete.sh > /dev/null)
	$(shell cd kernel/drivers/huawei/hsad;./xml2code.sh)
	$(shell cd device/hisi/hi6620/customize/hsad; python excel.py)
	$(shell cd device/hisi/hi6620/customize/hsad; python ipps_para.py)

ifeq ($(OBB_PRINT_CMD), true)
$(KERNEL_GEN_CONFIG_PATH): $(KERNEL_COMMON_DEFCONFIG) $(shell ls $(KERNEL_PRODUCT_CONFIGS))
else
$(KERNEL_GEN_CONFIG_PATH): FORCE
endif
	+$(shell $(shell pwd)/device/hisi/hi6620oem/kernel-config.sh -f $(KERNEL_COMMON_DEFCONFIG) -d $(KERNEL_PRODUCT_CONFIGS) -o $(KERNEL_GEN_CONFIG_PATH))

ifeq ($(OBB_PRINT_CMD), true)
$(KERNEL_CONFIG): MAKEFLAGS := 
endif
$(KERNEL_CONFIG): $(KERNEL_GEN_CONFIG_PATH)
	+mkdir -p $(KERNEL_OUT)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-linux-androideabi- $(KERNEL_GEN_CONFIG_FILE)
	@rm -frv $(KERNEL_GEN_CONFIG_PATH)

$(TARGET_PREBUILT_KERNEL): $(GPIO_CONFIG_TARGET) $(KERNEL_CONFIG)
ifeq ($(OBB_PRINT_CMD), true)
	$(hide) $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-linux-androideabi- vmlinux
	touch $@
else
	$(hide) $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-linux-androideabi-
endif

kernelconfig: $(KERNEL_GEN_CONFIG_PATH)
	mkdir -p $(KERNEL_OUT)
	$(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-linux-androideabi- $(KERNEL_GEN_CONFIG_FILE) menuconfig
	@rm -frv $(KERNEL_GEN_CONFIG_PATH)

zImage:$(TARGET_PREBUILT_KERNEL)
	@mkdir -p $(dir $(INSTALLED_KERNEL_TARGET))
	@cp -fp $(TARGET_PREBUILT_KERNEL) $(INSTALLED_KERNEL_TARGET)

pclint_kernel: $(KERNEL_CONFIG)
	$(hide) $(MAKE) -C kernel O=../$(KERNEL_OUT) ARCH=arm CROSS_COMPILE=arm-linux-androideabi- pc_lint_all


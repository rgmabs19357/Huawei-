local_path := $(srctree)/$(src)

huawei_driver_modules := $(addsuffix /, $(notdir $(shell find $(local_path)/ -maxdepth 1 -type d | sed '{1d}')))

obj-y += $(huawei_driver_modules)

huawei_driver_test:
	@echo "============================================================"
	@echo "              HUAWEI DRIVER MODULES                         "
	@echo $(huawei_drivers_modules)

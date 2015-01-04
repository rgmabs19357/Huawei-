
local_path := $(srctree)/$(src)
huawei_device_srcs := $(shell find $(local_path) -maxdepth 1 -type f -name *.c)
huawei_device_objs := $(patsubst %.c,%.o,$(notdir $(huawei_device_srcs)))
obj-y += $(huawei_device_objs)

#find out all the subdir under device directory
huawei_device_subdirs := $(addsuffix /, $(notdir $(shell find $(local_path)/ -maxdepth 1 -type d | sed '{1d}'))) 
obj-y += $(huawei_device_subdirs)

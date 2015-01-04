#sensor unification for differ platform
# Makefile for the compass drivers.
#

# Each configuration option enables a list of files.
obj-$(CONFIG_HUAWEI_FEATURE_SENSORS_AKM8975)   += akm8975.o
obj-$(CONFIG_HUAWEI_FEATURE_SENSORS_AKM8963)   += akm8963.o
obj-$(CONFIG_HUAWEI_FEATURE_SENSORS_AKM09911)   += akm09911.o

ifeq ($(CONFIG_COMPASS_DEBUG),y)
EXTRA_CFLAGS += -DDEBUG
endif


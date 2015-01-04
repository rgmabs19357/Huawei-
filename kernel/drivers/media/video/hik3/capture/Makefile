#
# Makefile for hisilicon K3 soc camera v4l2 driver
#
EXTRA_CFLAGS += -Idrivers/media/video/hik3/capture/isp
EXTRA_CFLAGS += -fno-pic


k3_capture-objs := isp/cam_util.o \
		   isp/cam_dbg.o \
		   isp/k3_v4l2_capture.o \
		   isp/k3_isp.o \
		   isp/k3_isp_io.o \
		   isp/k3_ispv1.o \
		   isp/k3_ispv1_afae.o \
		   isp/k3_ispv1_tune_ops.o \
		   isp/k3_ispv1_io.o \
		   isp/sensor_common.o \


obj-$(CONFIG_VIDEO_HIK3_CAMERA) += k3_capture.o
#obj-m += k3_capture.o

ifdef CONFIG_HIK3_CAMERA_OV5642
#obj-$(CONFIG_HIK3_CAMERA_OV5642) += ov5642/
#obj-m += ov5642/
endif

ifdef CONFIG_HIK3_CAMERA_OV8830
obj-$(CONFIG_HIK3_CAMERA_OV8830) += ov8830/
#obj-m += ov8830/
endif

ifdef CONFIG_HIK3_CAMERA_SONYIMX105
obj-$(CONFIG_HIK3_CAMERA_SONYIMX105) += sonyimx105/
#obj-m += sonyimx105/
endif

ifdef CONFIG_HIK3_CAMERA_S5K3H2YX_FOXCONN
obj-$(CONFIG_HIK3_CAMERA_S5K3H2YX_FOXCONN) += s5k3h2yx_foxconn/
#obj-m += s5k3h2yx_foxconn/
endif

ifdef CONFIG_HIK3_CAMERA_S5K3H2YX_SAMSUNGEM
obj-$(CONFIG_HIK3_CAMERA_S5K3H2YX_SAMSUNGEM) += s5k3h2yx_samsungem/
#obj-m += s5k3h2yx_samsungem/
endif

ifdef CONFIG_HIK3_CAMERA_MT9M114
obj-$(CONFIG_HIK3_CAMERA_MT9M114) += mt9m114/
#obj-m += mt9m114/
endif

ifdef CONFIG_HIK3_CAMERA_FLASH
obj-$(CONFIG_HIK3_CAMERA_FLASH) += flash/
#obj-m += flash/
endif

ifdef CONFIG_HIK3_CAMERA_SONYIMX091
obj-$(CONFIG_HIK3_CAMERA_SONYIMX091) += sonyimx091/
#obj-m += sonyimx091/
endif
ifdef CONFIG_HIK3_CAMERA_S5K5CAG
obj-$(CONFIG_HIK3_CAMERA_S5K5CAG) += s5k5cag/
#obj-m += s5k5cag/
endif

##############################################################################
#
#    Copyright (c) 2005 - 2013 by Vivante Corp.  All rights reserved.
#
#    The material in this file is confidential and contains trade secrets
#    of Vivante Corporation. This is proprietary information owned by
#    Vivante Corporation. No part of this work may be disclosed,
#    reproduced, copied, transmitted, or used in any way for any purpose,
#    without the express written permission of Vivante Corporation.
#
##############################################################################


LOCAL_PATH := $(call my-dir)
include $(LOCAL_PATH)/../../Android.mk.def
#
# libGAL
#
include $(CLEAR_VARS)

GC_HAL_ARCH_USER_DIR := ../../arch/$(GPU_TYPE)/hal/user
GC_HAL_USER_DIR      := .
GC_HAL_OS_USER_DIR   := ../os/linux/user

LOCAL_SRC_FILES := \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_blt.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_filter_blt_vr.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_pattern.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_pipe.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_primitive.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_query.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_source.c \
	$(GC_HAL_ARCH_USER_DIR)/gc_hal_user_hardware_target.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_brush.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_brush_cache.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_buffer.c \
	$(GC_HAL_USER_DIR)/gc_hal_user.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_dump.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_heap.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_profiler.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_query.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_queue.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_raster.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_rect.c \
	$(GC_HAL_USER_DIR)/gc_hal_user_surface.c \
	$(GC_HAL_OS_USER_DIR)/gc_hal_user_debug.c \
	$(GC_HAL_OS_USER_DIR)/gc_hal_user_os.c \
	$(GC_HAL_OS_USER_DIR)/gc_hal_user_math.c


LOCAL_CFLAGS := \
	$(CFLAGS)

LOCAL_CFLAGS += \
	-DVIVANTE_NO_3D


LOCAL_C_INCLUDES := \
	$(AQROOT)/hal/inc \
	$(AQROOT)/hal/user \
	$(AQROOT)/hal/os/linux/user \
	$(AQVGARCH)/hal/user


ifeq ($(USE_LINUX_MODE_FOR_ANDROID), 1)
	LOCAL_C_INCLUDES += \
		$(AQROOT)/sdk/inc

	LOCAL_SRC_FILES += \
		$(GC_HAL_USER_DIR)/gc_hal_user_fbdev.c
endif

LOCAL_LDFLAGS := \
	-Wl,-z,defs \
	-Wl,--version-script=$(LOCAL_PATH)/libGAL.map

LOCAL_SHARED_LIBRARIES := \
	libcutils \
	liblog \
	libdl

LOCAL_GENERATED_SOURCES := \


LOCAL_MODULE         := libGAL
LOCAL_MODULE_TAGS    := optional
LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)


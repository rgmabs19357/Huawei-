# The gps config appropriate for this device
$(call inherit-product, device/common/gps/gps_us_supl.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)

$(call inherit-product, $(SRC_TARGET_DIR)/product/languages_full.mk)

LOCAL_PATH := device/huawei/hwp7

DEVICE_PACKAGE_OVERLAYS += $(LOCAL_PATH)/overlay

ifeq ($(TARGET_PREBUILT_KERNEL),)
	LOCAL_KERNEL := $(LOCAL_PATH)/kernel
else
	LOCAL_KERNEL := $(TARGET_PREBUILT_KERNEL)
endif

PRODUCT_COPY_FILES += \
    $(LOCAL_KERNEL):kernel

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/recovery/ueventd.hi6620oem.rc:recovery/root/ueventd.hi6620oem.rc \
    $(LOCAL_PATH)/recovery/fstab.hi6620oem:recovery/root/fstab.hi6620oem \
    $(LOCAL_PATH)/recovery/twrp.fstab:recovery/root/etc/twrp.fstab

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/recovery/system/bin/linker:recovery/root/system/bin/linker \
    $(LOCAL_PATH)/recovery/system/lib/libc.so:recovery/root/system/lib/libc.so \
    $(LOCAL_PATH)/recovery/system/lib/libdl.so:recovery/root/system/lib/libdl.so \
    $(LOCAL_PATH)/recovery/system/lib/liblog.so:recovery/root/system/lib/liblog.so \
    $(LOCAL_PATH)/recovery/system/lib/libm.so:recovery/root/system/lib/libm.so \
    $(LOCAL_PATH)/recovery/system/lib/libstdc++.so:recovery/root/system/lib/libstdc++.so \
    $(LOCAL_PATH)/recovery/system/lib/libz.so:recovery/root/system/lib/libz.so

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/batt_level_scale.png:recovery/root/res/images/1080x1920/batt_level_scale.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/batt_level_top.png:recovery/root/res/images/1080x1920/batt_level_top.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/bg.png:recovery/root/res/images/1080x1920/bg.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/empty_charge.png:recovery/root/res/images/1080x1920/empty_charge.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/err_charge.png:recovery/root/res/images/1080x1920/err_charge.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/full_charge.png:recovery/root/res/images/1080x1920/full_charge.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_0.png:recovery/root/res/images/1080x1920/number_0.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_1.png:recovery/root/res/images/1080x1920/number_1.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_2.png:recovery/root/res/images/1080x1920/number_2.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_3.png:recovery/root/res/images/1080x1920/number_3.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_4.png:recovery/root/res/images/1080x1920/number_4.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_5.png:recovery/root/res/images/1080x1920/number_5.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_6.png:recovery/root/res/images/1080x1920/number_6.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_7.png:recovery/root/res/images/1080x1920/number_7.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_8.png:recovery/root/res/images/1080x1920/number_8.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/number_9.png:recovery/root/res/images/1080x1920/number_9.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/percent_5.png:recovery/root/res/images/1080x1920/percent_5.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/percent_10.png:recovery/root/res/images/1080x1920/percent_10.png \
    $(LOCAL_PATH)/recovery/res/images/1080x1920/percent_sign.png:recovery/root/res/images/1080x1920/percent_sign.png


# This device have enough room for precise davick
PRODUCT_TAGS += dalvik.gc.type-precise

# Prime spacific overrides
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.manufacturer=HUAWEI \
    ro.product.model=P-L10

# General
PRODUCT_PROPERTY_OVERRIDES := \
    ro.ril.hsxpa=2

# OpenGL ES
PRODUCT_PROPERTY_OVERRIDES += \
    wifi.interface=wlan0 \
    ap.interface=wlan1 \
    persist.sys.usb.config=mtp,adb \
    ro.opengles.version=131072

$(call inherit-product, build/target/product/full.mk)

# call dalvik heap config
$(call inherit-product, frameworks/native/build/phone-xhdpi-2048-dalvik-heap.mk)

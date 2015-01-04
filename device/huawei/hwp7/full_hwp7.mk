$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base.mk)

PRODUCT_AAPT_CONFIG := normal hdpi xhdpi xxhdpi
PRODUCT_AAPT_PREF_CONFIG := xxhdpi

PRODUCT_LOCALES += en_US

## Device identifier. This must come after all inclusions

PRODUCT_NAME := full_hwp7
PRODUCT_DEVICE := hwp7
PRODUCT_BRAND := huawei
PRODUCT_MODEL := P7-L10
PRODUCT_MANUFACTURER := HUAWEI

$(call inherit-product, device/huawei/hwp7/device_hwp7.mk)



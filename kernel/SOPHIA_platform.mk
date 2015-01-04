PRODUCT_NAME := SOPHIA
PRODUCT_BRAND := Huawei
#PRODUCT_PACKAGES += xx
$(call inherit-product, frameworks/native/build/phone-xxhdpi-2048-dalvik-heap.mk)
PRODUCT_PROPERTY_OVERRIDES += service.inputaccel.config=2,5,0,0,4,160
# Properties for OpenGLRenderer
PRODUCT_PROPERTY_OVERRIDES += \
    ro.hwui.texture_cache_flushrate=0.4  \
    ro.hwui.text_large_cache_height=1024 \
    ro.hwui.text_large_cache_width=2048  \
    ro.hwui.text_small_cache_height=1024 \
    ro.hwui.text_small_cache_width=1024

export USE_AUDIO_RING_VOLUME_CHANGE := true

obj-y += drvif/
#obj-y += ipf/
obj-y += misc/
obj-y += mntn/
obj-y += om/
obj-y += thermal/
obj-y += subvic/
obj-y += timer/
obj-y += udi/
obj-y += usb/
obj-y += watchdog/
obj-y += pmussi/
obj-y += pmic/
obj-y += regulator/
obj-y += hifidsp/
obj-y += interface/
obj-y += etb/
obj-y += ddrc/
obj-y += drvnve/
obj-y += keymaster/

ifdef OBB_SEPARATE
ifneq ($(OBB_SEPARATE),SEPARATE)
obj-y += modem/
endif
endif

obj-$(CONFIG_HISI_TEST) += test/

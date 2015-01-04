# sample makefile

ifneq ($(IPPORT),las)
ifneq ($(IPPORT),lkm)

#############################################################################
# PRODUCT
###########################################################################

IPPROD ?= InterpeakMntn

#############################################################################
# DEFINE
###########################################################################
# add your definition here
#IPDEFINE	+= -DIPTEST1


#############################################################################
# INCLUDE
###########################################################################
#IPCOM_ROOT = ../../ipcom
#IPNET_ROOT = ../../ipnet2

IPINCLUDE = -I$(IPCOM_ROOT)/config -I$(IPCOM_ROOT)/include -I$(IPNET_ROOT)/config -I$(IPNET_ROOT)/include -I$(IPNET_ROOT)/src -I$(IPCOM_ROOT)/port/vxworks/include -I$(IPCOM_ROOT)/port/vxworks/config
IPINCLUDE += -I$(INTERPEAKMNTN_ROOT)/config
IPINCLUDE += -I$(INTERPEAKMNTN_ROOT)/include

IPLIBINCLUDE += -I$(INTERPEAKMNTN_ROOT)/src


#############################################################################
# OBJECTS
###########################################################################

IPLIBOBJECTS    += InterpeakMntn.o


#############################################################################
# VPATH
###########################################################################

IPSRCDIRS += $(INTERPEAKMNTN_ROOT)/src $(INTERPEAKMNTN_ROOT)/config


#############################################################################
# LIB
###########################################################################

IPLIBS += $(IPLIBROOT)/libInterpeakMntn.a

endif
endif

###########################################################################
# END OF IPTEST1.MK
###########################################################################

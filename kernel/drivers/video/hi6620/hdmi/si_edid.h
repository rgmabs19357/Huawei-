/*
********************************************************************
  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.
  No part of this work may be reproduced, modified, distributed, transmitted,
  transcribed, or translated into any language or computer format, in any form
  or by any means without written permission of: Silicon Image, Inc.,
  1060 East Arques Avenue, Sunnyvale, California 94085
******************************************************************
*/

#ifndef _SI_EDID_H_
#define _SI_EDID_H_

#include <linux/types.h>

#include "si_mhl_defs.h"
#include "si_infoframe.h"
#pragma pack(1)
typedef unsigned char  byte;
#define HDMI_DEFAULT_PCM_PLAY 		 1

typedef struct SI_PACK_THIS_STRUCT _TwoBytes_t
{
    unsigned char low;
    unsigned char high;
}TwoBytes_t,*PTwoBytes_t;

#define EDID_EXTENSION_TAG  0x02
#define EDID_REV_THREE      0x03
#define LONG_DESCR_LEN      18
#define EDID_BLOCK_NUMBER   4
#define EDID_BLOCK_SIZE     128
#define EDID_BLOCK_0        0x00
#define EDID_BLOCK_2_3      0x01
#define EDID_BLOCK_0_OFFSET 0x0000
#define EDID_BLOCK_1_OFFSET 0x0080

#define MHL_READ_EDID_COUNT 3


typedef enum
{
	dbtcTerminator                 = 0,
	dbtcAudioDataBlock             = 1,
	dbtcVideoDataBlock             = 2,
	dbtcVendorSpecificDataBlock    = 3,
	dbtcSpeakerAllocationDataBlock = 4,
	dbtcVesaDtcDataBlock           = 5,
	//reserved                      = 6
	dbtcUsedExtendedTag            = 7
}DataBlockTagCode_e;
typedef struct SI_PACK_THIS_STRUCT _DataBlockHeaderByte_t
{
    uint8_t lengthFollowingHeader:5;
    DataBlockTagCode_e tagCode:3;
}DataBlockHeaderByte_t,*PDataBlockHeaderByte_t;

typedef enum
{
    etcVideoCapabilityDataBlock                    =  0,
    etcVendorSpecificVideoDataBlock                =  1,
    etcVESAVideoDisplayDeviceInformationDataBlock  =  2,
    etcVESAVideoDataBlock                          =  3,
    etcHDMIVideoDataBlock                          =  4,
    etcColorimetryDataBlock                        =  5,
    etcVideoRelated                                =  6,

    etcCEAMiscAudioFields                          = 16,
    etcVendorSpecificAudioDataBlock                = 17,
    etcHDMIAudioDataBlock                          = 18,
    etcAudiorRelated                               = 19,

    etcGeneral                                     = 32,
}ExtendedTagCode_e;

typedef struct SI_PACK_THIS_STRUCT _ExtendedTagCode_t
{
    ExtendedTagCode_e extendedTagCode:8;
}ExtendedTagCode_t,*PExtendedTagCode_t;

typedef struct SI_PACK_THIS_STRUCT _CeaShortDescriptor_t
{
    unsigned char VIC:7;
    unsigned char native:1;

}CeaShortDescriptor_t,*PCeaShortDescriptor_t;

typedef struct SI_PACK_THIS_STRUCT  _MHLShortDesc_t
{
    CeaShortDescriptor_t ceaShortDesc;
    Mhl2VideoDescriptor_t mhlVidDesc;
}MHLShortDesc_t,*PMHLShortDesc_t;

typedef struct SI_PACK_THIS_STRUCT _VideoDataBlock_t
{
    DataBlockHeaderByte_t header;
    CeaShortDescriptor_t shortDescriptors[31];
}VideoDataBlock_t,*PVideoDataBlock_t;

typedef enum
{
    // reserved            =  0
    afdLinearPCM_IEC60958  =  1,
    afdAC3                 =  2,
    afdMPEG1Layers1_2      =  3,
    afdMPEG1Layer3         =  4,
    afdMPEG2_MultiChannel  =  5,
    afdAAC                 =  6,
    afdDTS                 =  7,
    afdATRAC               =  8,
    afdOneBitAudio         =  9,
    afdDolbyDigital        = 10,
    afdDTS_HD              = 11,
    afdMAT_MLP             = 12,
    afdDST                 = 13,
    afdWMAPro              = 14
    //reserved             = 15
}AudioFormatCodes_e;

typedef struct SI_PACK_THIS_STRUCT _CeaShortAudioDescriptor_t
{
    unsigned char       maxChannelsMinusOne :3;
    AudioFormatCodes_e  audioFormatCode     :4;
    unsigned char       F17                 :1;

    unsigned char freq32Khz   :1;
    unsigned char freq44_1KHz :1;
    unsigned char freq48KHz   :1;
    unsigned char freq88_2KHz :1;
    unsigned char freq96KHz   :1;
    unsigned char freq176_4KHz:1;
    unsigned char freq192Khz  :1;
    unsigned char F27         :1;

    union
    {
        struct
        {
            unsigned char res16bit:1;
            unsigned char res20bit:1;
            unsigned char res24bit:1;
            unsigned char F33_37:5;
        }audioCode1LPCM;
        struct
        {
            uint8_t maxBitRateDivBy8KHz;
        }audioCodes2_8;
        struct
        {
            uint8_t defaultZero;
        }audioCodes9_15;
    }byte3;
}CeaShortAudioDescriptor_t,*PCeaShortAudioDescriptor_t;

typedef struct SI_PACK_THIS_STRUCT _AudioDataBlock_t
{
    DataBlockHeaderByte_t header;
    CeaShortAudioDescriptor_t  shortAudioDescriptors[1]; // open ended
}AudioDataBlock_t,*PAudioDataBlock_t;

typedef struct SI_PACK_THIS_STRUCT _SpeakerAllocationFlags_t
{
    unsigned char   spkFrontLeftFrontRight:1;
    unsigned char   spkLFE:1;
    unsigned char   spkFrontCenter:1;
    unsigned char   spkRearLeftRearRight:1;
    unsigned char   spkRearCenter:1;
    unsigned char   spkFrontLeftCenterFrontRightCenter:1;
    unsigned char   spkRearLeftCenterReadRightCenter:1;
    unsigned char   spkReserved:1;
}SpeakerAllocationFlags_t,*PSpeakerAllocationFlags_t;
typedef struct SI_PACK_THIS_STRUCT _SpeakerAllocationDataBlockPayLoad_t
{
    SpeakerAllocationFlags_t speakerAllocFlags;

    uint8_t         reserved[2];
}SpeakerAllocationDataBlockPayLoad_t,*PSpeakerAllocationDataBlockPayLoad_t;

typedef struct SI_PACK_THIS_STRUCT _SpeakerAllocationDataBlock_t
{
    DataBlockHeaderByte_t header;
    SpeakerAllocationDataBlockPayLoad_t payload;

}SpeakerAllocationDataBlock_t,*PSpeakerAllocationDataBlock_t;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLC_BA_t
{
    unsigned char B:4;
    unsigned char A:4;
}HdmiLLC_BA_t,*PHdmiLLC_BA_t;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLC_DC_t
{
    unsigned char D:4;
    unsigned char C:4;
}HdmiLLC_DC_t,*PHdmiLLC_DC_t;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLC_Byte6_t
{
    unsigned char DVI_Dual      :1;
    unsigned char reserved      :2;
    unsigned char DC_Y444       :1;
    unsigned char DC_30bit      :1;
    unsigned char DC_36bit      :1;
    unsigned char DC_48bit      :1;
    unsigned char Supports_AI   :1;
}HdmiLLC_Byte6_t,*PHdmiLLC_Byte6_t;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLC_Byte8_t
{
    unsigned char CNC0_AdjacentPixelsIndependent        :1;
    unsigned char CNC1_SpecificProcessingStillPictures  :1;
    unsigned char CNC2_SpecificProcessingCinemaContent  :1;
    unsigned char CNC3_SpecificProcessingLowAVLatency   :1;
    unsigned char reserved                              :1;
    unsigned char HDMI_VideoPresent                     :1;
    unsigned char I_LatencyFieldsPresent                :1;
    unsigned char LatencyFieldsPresent                  :1;
}HdmiLLC_Byte8_t,*PHdmiLLC_Byte8_t;

typedef enum
{
    imszNoAdditional                                    = 0
    ,imszAspectRatioCorrectButNoGuarranteeOfCorrectSize = 1
    ,imszCorrectSizesRoundedToNearest1cm                = 2
    ,imszCorrectSizesDividedBy5RoundedToNearest5cm      = 3
}ImageSize_e;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLC_Byte13_t
{
    unsigned char reserved          :3;
    ImageSize_e Image_Size          :2;
    unsigned char _3D_Multi_present :2;
    unsigned char _3D_present       :1;
}HdmiLLC_Byte13_t,*PHdmiLLC_Byte13_t;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLC_Byte14_t
{
    unsigned char HDMI_3D_LEN :5;
    unsigned char HDMI_VIC_LEN:3;
}HdmiLLC_Byte14_t,*PHdmiLLC_Byte14_t;

typedef struct SI_PACK_THIS_STRUCT _VSDBByte13ThroughByte15_t
{
    HdmiLLC_Byte13_t    byte13;
    HdmiLLC_Byte14_t    byte14;
    uint8_t vicList[1]; // variable length list base on HDMI_VIC_LEN
}VSDBByte13ThroughByte15_t,*PVSDBByte13ThroughByte15_t;

typedef struct SI_PACK_THIS_STRUCT _VSDBAllFieldsByte9ThroughByte15_t
{
    uint8_t Video_Latency;
    uint8_t Audio_Latency;
    uint8_t Interlaced_Video_Latency;
    uint8_t Interlaced_Audio_Latency;
    VSDBByte13ThroughByte15_t   byte13ThroughByte15;
    // There must be no fields after here
}VSDBAllFieldsByte9ThroughByte15_t,*PVSDBAllFieldsByte9ThroughByte15_t;

typedef struct SI_PACK_THIS_STRUCT _VSDBAllFieldsByte9ThroughByte15SansProgressiveLatency_t
{
    uint8_t Interlaced_Video_Latency;
    uint8_t Interlaced_Audio_Latency;
    VSDBByte13ThroughByte15_t   byte13ThroughByte15;
    // There must be no fields after here
}VSDBAllFieldsByte9ThroughByte15SansProgressiveLatency_t,*PVSDBAllFieldsByte9ThroughByte15SansProgressiveLatency_t;

typedef struct SI_PACK_THIS_STRUCT _VSDBAllFieldsByte9ThroughByte15SansInterlacedLatency_t
{
    uint8_t Video_Latency;
    uint8_t Audio_Latency;
    VSDBByte13ThroughByte15_t   byte13ThroughByte15;
    // There must be no fields after here
}VSDBAllFieldsByte9ThroughByte15SansInterlacedLatency_t,*PVSDBAllFieldsByte9ThroughByte15SansInterlacedLatency_t;

typedef struct SI_PACK_THIS_STRUCT _VSDBAllFieldsByte9ThroughByte15SansAllLatency_t
{
    VSDBByte13ThroughByte15_t   byte13ThroughByte15;
    // There must be no fields after here
}VSDBAllFieldsByte9ThroughByte15SansAllLatency_t,*PVSDBAllFieldsByte9ThroughByte15SansAllLatency_t;

typedef struct SI_PACK_THIS_STRUCT _HdmiLLCVendorSpecificDataBlockPayload_t
{
    HdmiLLC_BA_t B_A;
    HdmiLLC_DC_t D_C;
    HdmiLLC_Byte6_t byte6;
    uint8_t maxTMDSclock;
    HdmiLLC_Byte8_t byte8;
    union
    {
        VSDBAllFieldsByte9ThroughByte15SansAllLatency_t         vsdbAllFieldsByte9ThroughByte15SansAllLatency;
        VSDBAllFieldsByte9ThroughByte15SansProgressiveLatency_t vsdbAllFieldsByte9ThroughByte15SansProgressiveLatency;
        VSDBAllFieldsByte9ThroughByte15SansInterlacedLatency_t  vsdbAllFieldsByte9ThroughByte15SansInterlacedLatency;
        VSDBAllFieldsByte9ThroughByte15_t                       vsdbAllFieldsByte9ThroughByte15;
    }vsdbFieldsByte9ThroughByte15;
    // There must be no fields after here
}HdmiLLCVendorSpecificDataBlockPayload_t,*PHdmiLLCVendorSpecificDataBlockPayload_t;

typedef struct SI_PACK_THIS_STRUCT st_3D_Structure_ALL_15_8_t
{
    uint8_t framePacking    : 1;
    uint8_t reserved1       : 5;
    uint8_t topBottom       : 1;
    uint8_t reserved2       : 1;
}_3D_Structure_ALL_15_8_t,*P_3D_Structure_ALL_15_8_t;

typedef struct SI_PACK_THIS_STRUCT st_3D_Structure_ALL_7_0_t
{
    uint8_t sideBySide      : 1;
    uint8_t reserved        : 7;
}_3D_Structure_ALL_7_0_t,*P_3D_Structure_ALL_7_0_t;


typedef struct SI_PACK_THIS_STRUCT tag_3D_MultiPresent_01_or_10_t
{
    _3D_Structure_ALL_15_8_t _3D_Structure_ALL_15_8;
    _3D_Structure_ALL_7_0_t _3D_Structure_ALL_7_0;
}_3D_StructureAll_t,*P_3D_StructureAll_t;


typedef struct SI_PACK_THIS_STRUCT _3D_MultiPresent_01_10_t
{
    uint8_t _3D_Mask_15_8;
    uint8_t _3D_Mask_7_0;
}_3D_Mask_t,*P_3D_Mask_t;



typedef struct SI_PACK_THIS_STRUCT tag_2D_VIC_order_3D_Structure_t
{
    ThreeDStructure_e _3D_Structure:4;     // definition from info frame
    unsigned    char _2D_VIC_order:4;
}_2D_VIC_order_3D_Structure_t,*P_2D_VIC_order_3D_Structure_t;

typedef struct SI_PACK_THIS_STRUCT tag_3D_Detail_t
{
    unsigned char reserved    :4;
    unsigned char _3D_Detail  :4;
}_3D_Detail_t,*P_3D_Detail_t;

typedef struct SI_PACK_THIS_STRUCT tag_3DStructureAndDetailEntrySansByte1_t
{
    _2D_VIC_order_3D_Structure_t    byte0;
    _3D_Detail_t                    byte1;
}_3DStructureAndDetailEntrySansByte1_t,*P_3DStructureAndDetailEntrySansByte1_t;

typedef struct SI_PACK_THIS_STRUCT tag_3DStructureAndDetailEntryWithByte1_t
{
    _2D_VIC_order_3D_Structure_t    byte0;
    _3D_Detail_t                    byte1;
}_3DStructureAndDetailEntryWithByte1_t,*P_3DStructureAndDetailEntryWithByte1_t;

typedef union tag_3DStructureAndDetailEntry_u
{
    _3DStructureAndDetailEntrySansByte1_t   sansByte1;
    _3DStructureAndDetailEntryWithByte1_t   withByte1;
}_3DStructureAndDetailEntry_u,*P_3DStructureAndDetailEntry_u;

typedef struct SI_PACK_THIS_STRUCT _Hdmi3DSubBlockSansAllAndMask_t
{
    _3DStructureAndDetailEntry_u    _3DStructureAndDetailList[1];
}Hdmi3DSubBlockSansAllAndMask_t,*PHdmi3DSubBlockSansAllAndMask_t;

typedef struct SI_PACK_THIS_STRUCT _Hdmi3DSubBlockSansMask_t
{
    _3D_StructureAll_t  _3D_StructureAll;
    _3DStructureAndDetailEntry_u    _3DStructureAndDetailList[1];
}Hdmi3DSubBlockSansMask_t,*PHdmi3DSubBlockSansMask_t;

typedef struct SI_PACK_THIS_STRUCT _Hdmi3DSubBlockWithAllAndMask_t
{
    _3D_StructureAll_t  _3D_StructureAll;
    _3D_Mask_t          _3D_Mask;
    _3DStructureAndDetailEntry_u    _3DStructureAndDetailList[1];
}Hdmi3DSubBlockWithAllAndMask_t,*PHdmi3DSubBlockWithAllAndMask_t;

typedef union
{
    Hdmi3DSubBlockSansAllAndMask_t   hdmi3DSubBlockSansAllAndMask;
    Hdmi3DSubBlockSansMask_t         hdmi3DSubBlockSansMask;
    Hdmi3DSubBlockWithAllAndMask_t   hdmi3DSubBlockWithAllAndMask;
}Hdmi3DSubBlock_t,*PHdmi3DSubBlock_t;

typedef struct SI_PACK_THIS_STRUCT _VendorSpecificDataBlock_t
{
    DataBlockHeaderByte_t header;
    uint8_t IEEE_OUI[3];
    union
    {
        HdmiLLCVendorSpecificDataBlockPayload_t HdmiLLC;
        uint8_t payload[1]; // open ended
    }payload_u;
}VendorSpecificDataBlock_t,*PVendorSpecificDataBlock_t;

typedef enum
{
     xvYCC_601   = 1,
     xvYCC_709   = 2
}Colorimetry_xvYCC_e;

typedef struct SI_PACK_THIS_STRUCT _Colorimetry_xvYCC_t
{
    Colorimetry_xvYCC_e     xvYCC       :2;
    unsigned char           reserved1   :6;
}Colorimetry_xvYCC_t,*PColorimetry_xvYCC_t;

typedef struct SI_PACK_THIS_STRUCT _ColorimeteryMetaData_t
{
    unsigned char           metaData    :3;
    unsigned char           reserved2   :5;
}ColorimeteryMetaData_t,*PColorimeteryMetaData_t;

typedef struct SI_PACK_THIS_STRUCT _ColorimeteryDataPayLoad_t
{
    Colorimetry_xvYCC_t     ciData;
    ColorimeteryMetaData_t  cmMetaData;
}ColorimeteryDataPayLoad_t,*PColorimeteryDataPayLoad_t;
typedef struct SI_PACK_THIS_STRUCT _ColorimetryDataBlock_t
{
    DataBlockHeaderByte_t   header;
    ExtendedTagCode_t       extendedTag;
    ColorimeteryDataPayLoad_t payload;

}ColorimetryDataBlock_t,*PColorimetryDataBlock_t;

typedef enum
{
    ceouNeither                    = 0,
    ceouAlwaysOverScanned          = 1,
    ceouAlwaysUnderScanned         = 2,
    ceouBoth                       = 3
}CEOverScanUnderScanBehavior_e;

typedef enum
{
    itouNeither                    = 0,
    itouAlwaysOverScanned          = 1,
    itouAlwaysUnderScanned         = 2,
    itouBoth                       = 3
}ITOverScanUnderScanBehavior_e;

typedef enum
{
    ptouNeither                    = 0,
    ptouAlwaysOverScanned          = 1,
    ptouAlwaysUnderScanned         = 2,
    ptouBoth                       = 3
}PTOverScanUnderScanBehavior_e;

typedef struct SI_PACK_THIS_STRUCT _VideoCapabilityDataPayLoad_t
{
    CEOverScanUnderScanBehavior_e S_CE     :2;
    ITOverScanUnderScanBehavior_e S_IT     :2;
    PTOverScanUnderScanBehavior_e S_PT     :2;
    unsigned char                 QS       :1;
    unsigned char                 reserved :1;
}VideoCapabilityDataPayLoad_t,*PVideoCapabilityDataPayLoad_t;

typedef struct SI_PACK_THIS_STRUCT _VideoCapabilityDataBlock_t
{
    DataBlockHeaderByte_t   header;
    ExtendedTagCode_t       extendedTag;
    VideoCapabilityDataPayLoad_t payload;

}VideoCapabilityDataBlock_t,*PVideoCapabilityDataBlock_t;

typedef struct SI_PACK_THIS_STRUCT _CeaDataBlockCollection_t
{
    DataBlockHeaderByte_t header;

    union
    {
        ExtendedTagCode_t extendedTag;
        CeaShortDescriptor_t shortDescriptor;
    }payload_u;
    // open ended array of CeaShortDescriptor_t starts here
}CeaDataBlockCollection_t,*PCeaDataBlockCollection_t;

typedef struct SI_PACK_THIS_STRUCT _CeaExtensionVersion1_t
{
    uint8_t reservedMustBeZero;
    uint8_t reserved[123];
}CeaExtensionVersion1_t,*PCeaExtensionVersion1_t;

typedef struct SI_PACK_THIS_STRUCT _CeaExtension2_3MiscSupport_t
{
    uint8_t totalNumberDetailedTimingDescriptorsInEntireEDID:4;
    uint8_t YCrCb422Support:1;
    uint8_t YCrCb444Support:1;
    uint8_t basicAudioSupport:1;
    uint8_t underscanITformatsByDefault:1;
}CeaExtension2_3MiscSupport_t,*PCeaExtension2_3MiscSupport_t;
typedef struct SI_PACK_THIS_STRUCT _CeaExtensionVersion2_t
{
    CeaExtension2_3MiscSupport_t miscSupport;

    uint8_t reserved[123];
}CeaExtensionVersion2_t,*PCeaExtensionVersion2_t;

typedef struct SI_PACK_THIS_STRUCT _CeaExtensionVersion3_t
{
    CeaExtension2_3MiscSupport_t miscSupport;
    union
    {
        uint8_t dataBlockCollection[123];
        uint8_t reserved[123];
    }Offset4_u;
}CeaExtensionVersion3_t,*PCeaExtensionVersion3_t;

typedef struct SI_PACK_THIS_STRUCT _CeaExtension_t
{
    uint8_t tag;
    uint8_t revision;
    uint8_t byteOffsetTo18ByteDescriptors;
    union
    {
        CeaExtensionVersion1_t      version1;
        CeaExtensionVersion2_t      version2;
        CeaExtensionVersion3_t      version3;
    }version_u;
    uint8_t checkSum;
}CeaExtension_t,*PCeaExtension_t;

typedef struct SI_PACK_THIS_STRUCT _DetailedTimingDescriptor_t
{
    uint8_t pixelClockLow;
    uint8_t pixelClockHigh;
    uint8_t horzActive7_0;
    uint8_t horzBlanking7_0;
    struct
    {
        unsigned char horzBlanking11_8    :4;
        unsigned char horzActive11_8      :4;
    }horzActiveBlankingHigh;
    uint8_t vertActive7_0;
    uint8_t vertBlanking7_0;
    struct
    {
        unsigned char vertBlanking11_8    :4;
        unsigned char vertActive11_8      :4;
    }vertActiveBlankingHigh;
    uint8_t horzSyncOffset7_0;
    uint8_t horzSyncPulseWidth7_0;
    struct
    {
        unsigned char vertSyncPulseWidth3_0 :4;
        unsigned char vertSyncOffset3_0     :4;
    }vertSyncOffsetWidth;
    struct
    {
        unsigned char vertSyncPulseWidth5_4 :2;
        unsigned char vertSyncOffset5_4     :2;
        unsigned char horzSyncPulseWidth9_8 :2;
        unsigned char horzSyncOffset9_8     :2;
    }hsOffsetHsPulseWidthVsOffsetVsPulseWidth;
    uint8_t horzImageSizemm_7_0;
    uint8_t vertImageSizemm_7_0;
    struct
    {
        unsigned char vertImageSizemm_11_8  :4;
        unsigned char horzImageSizemm_11_8  :4;
    }imageSizeHigh;
    uint8_t horzBorderLines;
    uint8_t vertBorderPixels;
    struct
    {
        unsigned char stereoBit0            :1;
        unsigned char syncSignalOptions     :2;
        unsigned char syncSignalType        :2;
        unsigned char stereoBits2_1         :2;
        unsigned char interlaced            :1;
    }flags;
}DetailedTimingDescriptor_t,*PDetailedTimingDescriptor_t;

typedef struct SI_PACK_THIS_STRUCT _RedGreenBits1_0_t
{
    unsigned char   Green_y :2;
    unsigned char   Green_x :2;
    unsigned char   Red_y   :2;
    unsigned char   Red_x   :2;
}RedGreenBits1_0_t,*PRedGreenBits1_0_t;

typedef struct SI_PACK_THIS_STRUCT _BlueWhiteBits1_0_t
{
    unsigned char   White_y :2;
    unsigned char   White_x :2;
    unsigned char   Blue_y  :2;
    unsigned char   Blue_x  :2;

}BlueWhiteBits1_0_t,*PBlueWhiteBits1_0_t;


typedef struct SI_PACK_THIS_STRUCT _EstablishedTimingsI_t
{
    unsigned char et800x600_60Hz  :1;
    unsigned char et800x600_56Hz  :1;
    unsigned char et640x480_75Hz  :1;
    unsigned char et640x480_72Hz  :1;
    unsigned char et640x480_67Hz  :1;
    unsigned char et640x480_60Hz  :1;
    unsigned char et720x400_88Hz  :1;
    unsigned char et720x400_70Hz  :1;
}EstablishedTimingsI_t,*PEstablishedTimingsI_t;

typedef struct SI_PACK_THIS_STRUCT _EstablishedTimingsII_t
{
    unsigned char et1280x1024_75Hz:1;
    unsigned char et1024x768_75Hz :1;
    unsigned char et1024x768_70Hz :1;
    unsigned char et1024x768_60Hz :1;
    unsigned char et1024x768_87HzI:1;
    unsigned char et832x624_75Hz  :1;
    unsigned char et800x600_75Hz  :1;
    unsigned char et800x600_72Hz  :1;
}EstablishedTimingsII_t,*PEstablishedTimingsII_t;

typedef struct SI_PACK_THIS_STRUCT _ManufacturersTimings_t
{
    unsigned char   reserved        :7;
    unsigned char   et1152x870_75Hz :1;
}ManufacturersTimings_t,*PManufacturersTimings_t;

typedef enum
{
    iar16to10   = 0
    ,iar4to3    = 1
    ,iar5to4    = 2
    ,iar16to9   = 3
}ImageAspectRatio_e;

typedef struct SI_PACK_THIS_STRUCT _StandardTiming_t
{
    unsigned char   horzPixDiv8Minus31;
    unsigned char   fieldRefreshRateMinus60:6;
    ImageAspectRatio_e imageAspectRatio    :2;
}StandardTiming_t,*PStandardTiming_t;

typedef struct SI_PACK_THIS_STRUCT _EDID_Block0_t
{
    unsigned char               headerData[8];
    TwoBytes_t                  idManufacturerName;
    TwoBytes_t                  idProductCode;
    unsigned char               serialNumber[4];
    unsigned char               weekOfManufacture;
    unsigned char               yearOfManufacture;
    unsigned char               edidVersion;
    unsigned char               edidRevision;
    unsigned char               videoInputDefinition;
    unsigned char               horzScreenSizeOrAspectRatio;
    unsigned char               vertScreenSizeOrAspectRatio;
    unsigned char               displayTransferCharacteristic;
    unsigned char               featureSupport;
    RedGreenBits1_0_t           redGreenBits1_0;
    BlueWhiteBits1_0_t          blueWhiteBits1_0;
    unsigned char               Red_x;
    unsigned char               Red_y;
    unsigned char               Green_x;
    unsigned char               Green_y;
    unsigned char               Blue_x;
    unsigned char               Blue_y;
    unsigned char               White_x;
    unsigned char               White_y;
    EstablishedTimingsI_t       establishedTimingsI;
    EstablishedTimingsII_t      establishedTimingsII;
    ManufacturersTimings_t      manufacturersTimings;
    StandardTiming_t            standardTimings[8];
    DetailedTimingDescriptor_t  detailedTimingDescriptors[4];
    unsigned char               extensionFlag;
    unsigned char               checkSum;

}EDID_Block0_t,*PEDID_Block0_t;

typedef struct SI_PACK_THIS_STRUCT _MonitorName_t
{
    uint8_t flagRequired[2];
    uint8_t flagReserved;
    uint8_t dataTypeTag;
    uint8_t flag;
    uint8_t asciiName[13];


}MonitorName_t,*PMonitorName_t;

typedef struct SI_PACK_THIS_STRUCT _MonitorRangeLimits_t
{

    uint8_t flagRequired[2];
    uint8_t flagReserved;
    uint8_t dataTypeTag;
    uint8_t flag;
    uint8_t minVerticalRateHz;
    uint8_t maxVerticalRateHz;
    uint8_t minHorizontalRateKHz;
    uint8_t maxHorizontalRateKHz;
    uint8_t maxPixelClockMHzDiv10;
    uint8_t tagSecondaryFormula;
    uint8_t filler[7];
}MonitorRangeLimits_t,*PMonitorRangeLimits_t;


typedef union tag_18ByteDescriptor_u
{
    DetailedTimingDescriptor_t  dtd;
    MonitorName_t               name;
    MonitorRangeLimits_t        rangeLimits;
}_18ByteDescriptor_u,*P_18ByteDescriptor_u;


typedef struct SI_PACK_THIS_STRUCT _DisplayMode3DInfo_t
{
    unsigned char dmi3Dsupported:1;
    unsigned char dmiSufficientBandwidth:1;
}DisplayMode3DInfo_t,*PDisplayMode3DInfo_t;


#define MAX_V_DESCRIPTORS 20
#define MAX_A_DESCRIPTORS 10
#define MAX_SPEAKER_CONFIGURATIONS 4
#define AUDIO_DESCR_SIZE 3
#define EDID_FIFO_LENGTH 16

#define AR16_10 0
#define AR4_3 1
#define AR5_4 2
#define AR16_9 3

typedef struct
{
    // for storing EDID parsed data
    uint8_t VideoDescriptor[MAX_V_DESCRIPTORS]; // maximum number of video descriptors
    uint8_t AudioDescriptor[MAX_A_DESCRIPTORS][3];  // maximum number of audio descriptors
    uint8_t rsved0[2];
    uint8_t SpkrAlloc[MAX_SPEAKER_CONFIGURATIONS];  // maximum number of speaker configurations
    bool  UnderScan;                              // "1" if DTV monitor underscans IT video formats by default
    bool  BasicAudio;                         // Sink supports Basic Audio
    bool  YCbCr_4_4_4;                        // Sink supports YCbCr 4:4:4
    bool  YCbCr_4_2_2;                        // Sink supports YCbCr 4:2:2
    bool  HDMI_Sink;                              // "1" if HDMI signature found
    uint8_t CEC_A_B;                                // CEC Physical address. See HDMI 1.3 Table 8-6
    uint8_t CEC_C_D;
    uint8_t VideoCapabilityFlags;
    uint8_t ColorimetrySupportFlags;                // IEC 61966-2-4 colorimetry support: 1 - xvYCC601; 2 - xvYCC709
    uint8_t MetadataProfile;
    uint8_t rsved1[3];
    bool  _3D_Supported;
    //uint16_t uVerticalImageSize,uHorizontalImageSize;  //Horizontal/Verical Addressable Video Image Size in mm.

    uint8_t edidBlockData [EDID_BLOCK_NUMBER * EDID_BLOCK_SIZE];   //raw data
} Type_EDID_Descriptors;

enum EDID_ErrorCodes
{
    EDID_OK,
    EDID_INCORRECT_HEADER,
    EDID_CHECKSUM_ERROR,
    EDID_NO_861_EXTENSIONS,
    EDID_SHORT_DESCRIPTORS_OK,
    EDID_LONG_DESCRIPTORS_OK,
    EDID_EXT_TAG_ERROR,
    EDID_REV_ADDR_ERROR,
    EDID_V_DESCR_OVERFLOW,
    EDID_UNKNOWN_TAG_CODE,
    EDID_NO_DETAILED_DESCRIPTORS,
    EDID_DDC_BUS_REQ_FAILURE,
    EDID_DDC_BUS_RELEASE_FAILURE
};

#define IsHDMI_Sink() (g_PlumTxConfig.EDID.HDMI_Sink)
#define IsCEC_DEVICE() (((g_PlumTxConfig.EDID.CEC_A_B != 0xFF) && (g_PlumTxConfig.EDID.CEC_C_D != 0xFF)) ? true : false)

#define SinkSupportYCbCr444() (g_PlumTxConfig.EDID.YCbCr_4_4_4)
#define SinkSupportYCbCr422() (g_PlumTxConfig.EDID.YCbCr_4_2_2)

#define PIXEL_CLOCK_OFFSET             500

/* HDMI EDID Extension Data Block Tags  */
#define HDMI_EDID_EX_DATABLOCK_TAG_MASK         0xE0  /* tag mask of data block in cea */
#define HDMI_EDID_EX_DATABLOCK_LEN_MASK         0x1F  /* length of data block in cea */
#define HDMI_EDID_EX_SUPPORTS_AI_MASK           0x80  /* bit mask of support ai */
#define HDMI_EDID_EX_DATABLOCK_AUDIO            0x20  /* tag of audio block in cea */
#define HDMI_EDID_EX_DATABLOCK_VIDEO            0x40  /* tag of video block in cea */
#define HDMI_EDID_EX_DATABLOCK_VENDOR           0x60  /* tag of vendor block in cea */
#define HDMI_EDID_EX_DATABLOCK_SPEAKERS         0x80  /* tag of speakers block in cea */

#define EDID_TIMING_DESCRIPTOR_SIZE             0x12  /* size of timing descriptor */
#define EDID_DESCRIPTOR_BLOCK0_ADDRESS          0x36  /* address of first 18 byte data block */
#define EDID_DESCRIPTOR_BLOCK1_ADDRESS          0x80  /* address of cea */
#define EDID_SIZE_BLOCK0_TIMING_DESCRIPTOR      4     /* size of timing descriptor in edid block0 */
#define EDID_SIZE_BLOCK1_TIMING_DESCRIPTOR      4     /* size of timing descriptor in edid block1 */

/* EDID Detailed Timing    Info 0 begin offset */
#define HDMI_EDID_DETAILED_TIMING_OFFSET        0x36  /* address of first detailed timing */

#define HDMI_EDID_PIX_CLK_OFFSET            0    /* offset of pixel clock in detailed timing */
#define HDMI_EDID_H_ACTIVE_OFFSET           2    /* offset of horizontal addressable video in pixels */
#define HDMI_EDID_H_BLANKING_OFFSET         3    /* offset of horizontal blanking in pixels */
#define HDMI_EDID_V_ACTIVE_OFFSET           5    /* offset of vertical addressable video in lines */
#define HDMI_EDID_V_BLANKING_OFFSET         6    /* offset of vertical blanking in lines */
#define HDMI_EDID_H_SYNC_OFFSET             8    /* offset of Horizontal Front Porch in pixels */
#define HDMI_EDID_H_SYNC_PW_OFFSET          9    /* offset of Horizontal Sync Pulse Width in pixels */
#define HDMI_EDID_V_SYNC_OFFSET             10   /* offset of Vertical Front Porch in Lines */
#define HDMI_EDID_V_SYNC_PW_OFFSET          11   /* offset of Vertical Sync Pulse Width in lines */
#define HDMI_EDID_H_IMAGE_SIZE_OFFSET       12   /* offset of Horizontal Addressable Video Image Size in mm */
#define HDMI_EDID_V_IMAGE_SIZE_OFFSET       13   /* offset of Vertical Addressable Video Image Size in mm */
#define HDMI_EDID_H_BORDER_OFFSET           15   /* offset of Right Horizontal Border or Left Horizontal Border in pixels */
#define HDMI_EDID_V_BORDER_OFFSET           16   /* offset of Top Vertical Border or Bottom Vertical Border in Lines */
#define HDMI_EDID_FLAGS_OFFSET              17   /* offset of flags */

#define HDMI_IEEE_REGISTRATION_ID        0x000c03  /* IEEE ID */

/* HDMI Connected States */
#define HDMI_STATE_NOMONITOR    0           /* No HDMI monitor connected*/
#define HDMI_STATE_CONNECTED    1           /* HDMI monitor connected but powered off */
#define HDMI_STATE_ON           2           /* HDMI monitor connected and powered on*/

/* HDMI EDID Length */
#define HDMI_EDID_MAX_LENGTH            (EDID_BLOCK_NUMBER * EDID_BLOCK_SIZE) /* max length of edid data */
#define HDMI_EDID_BLOCK_LENGTH          EDID_BLOCK_SIZE /* echo block length of edid data */

/* HDMI EDID DTDs */
#define HDMI_EDID_MAX_DTDS              4   /* max number of DTDs block */

/* HDMI EDID DTD Tags */
#define HDMI_EDID_DTD_TAG_MONITOR_NAME          0xFC  /* tag of monitor name of dtd block */
#define HDMI_EDID_DTD_TAG_MONITOR_SERIALNUM     0xFF  /* tag of monitor serialnum of dtd block */
#define HDMI_EDID_DTD_TAG_MONITOR_LIMITS        0xFD  /* tag of monitor limits of dtd block */
#define HDMI_EDID_DTD_TAG_STANDARD_TIMING_DATA  0xFA  /* tag of standard timing data of dtd block */
#define HDMI_EDID_DTD_TAG_COLOR_POINT_DATA      0xFB  /* tag of color point data of dtd block */
#define HDMI_EDID_DTD_TAG_ASCII_STRING          0xFE  /* tag of ascii string of dtd block */

#define HDMI_IMG_FORMAT_MAX_LENGTH              40    /* max length of video block */
#define HDMI_VIDEO_NATIVE_DTDS_MASK             0x0f  /* mask of video native DTDs */
#define HDMI_AUDIO_FORMAT_MAX_LENGTH            10    /* max length of audio block */
#define HDMI_AUDIO_BASIC_MASK                   0x40  /* mask of audio basic */

/* HDMI EDID Extenion Data Block Values: Video */
#define HDMI_EDID_EX_VIDEO_NATIVE               0x80  /* mask of native in video block */
#define HDMI_EDID_EX_VIDEO_MASK                 0x7F  /* mask of code in video block */

#define HDMI_CODE_VESA_OFFSET   100     /* offset of VESA code with CEA code */

/* macros of CEA timing code */
#define HDMI_EDID_EX_VIDEO_640x480p_60Hz_4_3        1
#define HDMI_EDID_EX_VIDEO_720x480p_60Hz_4_3        2
#define HDMI_EDID_EX_VIDEO_720x480p_60Hz_16_9       3
#define HDMI_EDID_EX_VIDEO_1280x720p_60Hz_16_9      4
#define HDMI_EDID_EX_VIDEO_1920x1080i_60Hz_16_9     5
#define HDMI_EDID_EX_VIDEO_720x480i_60Hz_4_3        6
#define HDMI_EDID_EX_VIDEO_720x480i_60Hz_16_9       7
#define HDMI_EDID_EX_VIDEO_720x240p_60Hz_4_3        8
#define HDMI_EDID_EX_VIDEO_720x240p_60Hz_16_9       9
#define HDMI_EDID_EX_VIDEO_2880x480i_60Hz_4_3       10
#define HDMI_EDID_EX_VIDEO_2880x480i_60Hz_16_9      11
#define HDMI_EDID_EX_VIDEO_2880x240p_60Hz_4_3       12
#define HDMI_EDID_EX_VIDEO_2880x240p_60Hz_16_9      13
#define HDMI_EDID_EX_VIDEO_1440x480p_60Hz_4_3       14
#define HDMI_EDID_EX_VIDEO_1440x480p_60Hz_16_9      15
#define HDMI_EDID_EX_VIDEO_1920x1080p_60Hz_16_9     16
#define HDMI_EDID_EX_VIDEO_720x576p_50Hz_4_3        17
#define HDMI_EDID_EX_VIDEO_720x576p_50Hz_16_9       18
#define HDMI_EDID_EX_VIDEO_1280x720p_50Hz_16_9      19
#define HDMI_EDID_EX_VIDEO_1920x1080i_50Hz_16_9     20
#define HDMI_EDID_EX_VIDEO_720x576i_50Hz_4_3        21
#define HDMI_EDID_EX_VIDEO_720x576i_50Hz_16_9       22
#define HDMI_EDID_EX_VIDEO_720x288p_50Hz_4_3        23
#define HDMI_EDID_EX_VIDEO_720x288p_50Hz_16_9       24
#define HDMI_EDID_EX_VIDEO_2880x576i_50Hz_4_3       25
#define HDMI_EDID_EX_VIDEO_2880x576i_50Hz_16_9      26
#define HDMI_EDID_EX_VIDEO_2880x288p_50Hz_4_3       27
#define HDMI_EDID_EX_VIDEO_2880x288p_50Hz_16_9      28
#define HDMI_EDID_EX_VIDEO_1440x576p_50Hz_4_3       29
#define HDMI_EDID_EX_VIDEO_1440x576p_50Hz_16_9      30
#define HDMI_EDID_EX_VIDEO_1920x1080p_50Hz_16_9     31
#define HDMI_EDID_EX_VIDEO_1920x1080p_24Hz_16_9     32
#define HDMI_EDID_EX_VIDEO_1920x1080p_25Hz_16_9     33
#define HDMI_EDID_EX_VIDEO_1920x1080p_30Hz_16_9     34
#define HDMI_EDID_EX_VIDEO_2880x480p_60Hz_4_3       35
#define HDMI_EDID_EX_VIDEO_2880x480p_60Hz_16_9      36
#define HDMI_EDID_EX_VIDEO_2880x576p_60Hz_4_3       37
#define HDMI_EDID_EX_VIDEO_2880x576p_60Hz_16_9      38
#define HDMI_EDID_EX_VIDEO_1920x1250i_50Hz_16_9     39
#define HDMI_EDID_EX_VIDEO_1920x1080i_100Hz_16_9    40
#define HDMI_EDID_EX_VIDEO_1280x720p_100Hz_16_9     41
#define HDMI_EDID_EX_VIDEO_720x576p_100Hz_4_3       42
#define HDMI_EDID_EX_VIDEO_720x576p_100Hz_16_9      43
#define HDMI_EDID_EX_VIDEO_720x576i_100Hz_4_3       44
#define HDMI_EDID_EX_VIDEO_720x576i_100Hz_16_9      45
#define HDMI_EDID_EX_VIDEO_1920x1080i_120Hz_16_9    46
#define HDMI_EDID_EX_VIDEO_1280x720p_120Hz_16_9     47
#define HDMI_EDID_EX_VIDEO_720x480p_120Hz_4_3       48
#define HDMI_EDID_EX_VIDEO_720x480p_120Hz_16_9      49
#define HDMI_EDID_EX_VIDEO_720x480i_120Hz_4_3       50
#define HDMI_EDID_EX_VIDEO_720x480i_120Hz_16_9      51
#define HDMI_EDID_EX_VIDEO_720x576p_200Hz_4_3       52
#define HDMI_EDID_EX_VIDEO_720x576p_200Hz_16_9      53
#define HDMI_EDID_EX_VIDEO_720x576i_200Hz_4_3       54
#define HDMI_EDID_EX_VIDEO_720x576i_200Hz_16_9      55
#define HDMI_EDID_EX_VIDEO_720x480p_240Hz_4_3       56
#define HDMI_EDID_EX_VIDEO_720x480p_240Hz_16_9      57
#define HDMI_EDID_EX_VIDEO_720x480i_240Hz_4_3       58
#define HDMI_EDID_EX_VIDEO_720x480i_240Hz_16_9      59

/* macros of VESA timing code */
#define HDMI_EDID_VESA_VIDEO_640x350p_85Hz_4_3          1+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_640x400p_85Hz_4_3          2+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_720x400p_85Hz_4_3          3+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_640x480p_60Hz_4_3          4+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_640x480p_72Hz_4_3          5+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_640x480p_75Hz_4_3          6+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_640x480p_85Hz_4_3          7+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_800x600p_56Hz_4_3          8+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_800x600p_60Hz_4_3          9+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_800x600p_72Hz_4_3          10+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_800x600p_75Hz_4_3          11+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_800x600p_85Hz_4_3          12+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_848x480p_60Hz_4_3          14+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1024x768p_43Hz_4_3         15+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1024x768p_60Hz_4_3         16+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1024x768p_70Hz_4_3         17+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1024x768p_75Hz_4_3         18+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1024x768p_85Hz_4_3         19+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1152x864p_75Hz_4_3         21+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x768p_60Hz_CVT_16_9    22+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x768p_60Hz_16_9        23+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x768p_75Hz_16_9        24+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x768p_85Hz_16_9        25+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x800p_60Hz_CVT_16_9    27+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x800p_60Hz_16_9        28+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x800p_75Hz_16_9        29+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x800p_85Hz_16_9        30+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x960p_60Hz_4_3         32+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x960p_85Hz_4_3         33+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x1024p_60Hz_4_3        35+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x1024p_75Hz_4_3        36+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x1024p_85Hz_4_3        37+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1360x768p_60Hz_16_9        39+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1400x1050p_60Hz_CVT_4_3    41+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1400x1050p_60Hz_4_3        42+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1400x1050p_75Hz_4_3        43+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1400x1050p_85Hz_4_3        44+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1440x900p_60Hz_CVT_16_9    46+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1440x900p_60Hz_16_9        47+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1440x900p_75Hz_16_9        48+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1440x900p_85Hz_16_9        49+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1600x1200p_60Hz_4_3        51+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1600x1200p_65Hz_4_3        52+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1600x1200p_70Hz_4_3        53+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1600x1200p_75Hz_4_3        54+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1600x1200p_80Hz_4_3        55+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1680x1050p_60Hz_CVT_16_9   57+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1680x1050p_60Hz_16_9       58+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1680x1050p_75Hz_16_9       59+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1680x1050p_85Hz_16_9       60+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1920x1080p_60Hz_16_9       82+HDMI_CODE_VESA_OFFSET
#define HDMI_EDID_VESA_VIDEO_1280x720p_60Hz_16_9        85+HDMI_CODE_VESA_OFFSET

#define HDMI_TIMINGS_VESA_START                     27  /* start of VESA timing code in timing array */
#define HDMI_TIMINGS_VESA_END                       95  /* end of VESA timing code in timing array */

#define HDMI_CODE_TYPE_CEA      1   /* timing mode which timing code followed CEA */
#define HDMI_CODE_TYPE_VESA     0   /* timing mode which timing code followed VESA */

/* default timing mode */
#define HDMI_DEFAULT_TIMING_MODE  HDMI_CODE_TYPE_CEA

/* default timing code */
#define HDMI_DEFAULT_MHL_TIMING_CODE   HDMI_EDID_EX_VIDEO_1280x720p_60Hz_16_9
#define HDMI_DEFAULT_VESA_TIMING_CODE  HDMI_EDID_VESA_VIDEO_1440x900p_60Hz_16_9
#ifndef HDMI_MAX_VESA_TIMING_CODE
#define HDMI_MAX_VESA_TIMING_CODE      HDMI_EDID_VESA_VIDEO_1280x720p_60Hz_16_9
#endif

/* invalid timing code */
#define INVALID_VALUE   -1

/* timing order of mhl not support, refer to timing_order[]*/
#define MHL_NOT_SUPPORT_TIMING_ORDER_FPGA        5    /* max timing: 720x576p_50Hz_16_9 */
#define MHL_NOT_SUPPORT_TIMING_ORDER             7    /* max timing: 1280x720p_60Hz_16_9 */
#define MHL_NOT_SUPPORT_TIMING_ORDER_1080P       10   /* max timing: 1920x1080p_30Hz_16_9 */
#define MHL_NOT_SUPPORT_VESA_TIMING_ORDER_FPGA   4    /* max timing: 640x480p_60Hz_4_3 */
#define MHL_NOT_SUPPORT_VESA_TIMING_ORDER        32   /* max timing: 1440x900p_60Hz_16_9 */
#define HDMI_TIMING_1080P_XRES      1920
#define HDMI_TIMING_1080P_YRES      1080

/* audio type */
#define HDMI_EDID_EX_AUDIO_PCM      1
#define HDMI_EDID_EX_AUDIO_AC3      2
#define HDMI_EDID_EX_AUDIO_MP1      3
#define HDMI_EDID_EX_AUDIO_MP3      4
#define HDMI_EDID_EX_AUDIO_MP2      5
#define HDMI_EDID_EX_AUDIO_AAC      6
#define HDMI_EDID_EX_AUDIO_DTS      7
#define HDMI_EDID_EX_AUDIO_ATRAC    8
#define HDMI_EDID_EX_AUDIO_DSD      9
#define HDMI_EDID_EX_AUDIO_EAC3     10
#define HDMI_EDID_EX_AUDIO_DTS_HD   11
#define HDMI_EDID_EX_AUDIO_MLP      12
#define HDMI_EDID_EX_AUDIO_DST      13
#define HDMI_EDID_EX_AUDIO_WMA      14

/* audio channel number */
#define HDMI_EDID_EX_AUDIO_CHN_NUM_2      1
#define HDMI_EDID_EX_AUDIO_CHN_NUM_3      2
#define HDMI_EDID_EX_AUDIO_CHN_NUM_4      3
#define HDMI_EDID_EX_AUDIO_CHN_NUM_5      4
#define HDMI_EDID_EX_AUDIO_CHN_NUM_6      5
#define HDMI_EDID_EX_AUDIO_CHN_NUM_7      6
#define HDMI_EDID_EX_AUDIO_CHN_NUM_8      7

/* audio freq */
#define HDMI_EDID_EX_AUDIO_FREQUENCY_32K     (1<<0)
#define HDMI_EDID_EX_AUDIO_FREQUENCY_44_1K   (1<<1)
#define HDMI_EDID_EX_AUDIO_FREQUENCY_48K     (1<<2)
#define HDMI_EDID_EX_AUDIO_FREQUENCY_88_2K   (1<<3)
#define HDMI_EDID_EX_AUDIO_FREQUENCY_96K     (1<<4)
#define HDMI_EDID_EX_AUDIO_FREQUENCY_176_4K  (1<<5)
#define HDMI_EDID_EX_AUDIO_FREQUENCY_192K    (1<<6)

/* default audio param */
#if HDMI_DEFAULT_PCM_PLAY
#define HDMI_DEFAULT_AUDIO_TYPE        HDMI_EDID_EX_AUDIO_PCM
#define HDMI_DEFAULT_AUDIO_CHANNL_NUM  HDMI_EDID_EX_AUDIO_CHN_NUM_2
#else
#define HDMI_DEFAULT_AUDIO_TYPE        HDMI_EDID_EX_AUDIO_EAC3
#define HDMI_DEFAULT_AUDIO_CHANNL_NUM  HDMI_EDID_EX_AUDIO_CHN_NUM_8
#endif
#define HDMI_DEFAULT_AUDIO_FREQUENCY   0x7F //support all freq type
#define GLOBAL_BYTE_BUF_BLOCK_SIZE 131
#define PIXEL_CLOCK_OFFSET             500

#define BITS_2_1 0x06
#define TWO_LSBITS 0x03
#define THREE_LSBITS 0x07
#define FOUR_LSBITS 0x0F
#define FIVE_LSBITS 0x1F
#define TWO_MSBITS 0xC0

#define T_DDC_ACCESS 50

#define EDID_HDR_NO_OF_FF 0x06
#define NUM_OF_EXTEN_ADDR 0x7E

#define EDID_TAG_ADDR 0x00
#define EDID_REV_ADDR 0x01
#define EDID_TAG_IDX 0x02
#define LONG_DESCR_PTR_IDX 0x02
#define MISC_SUPPORT_IDX 0x03

#define ESTABLISHED_TIMING_INDEX 35      // Offset of Established Timing in EDID block
#define NUM_OF_STANDARD_TIMINGS 8
#define STANDARD_TIMING_OFFSET 38
#define NUM_OF_DETAILED_DESCRIPTORS 4

#define DETAILED_TIMING_OFFSET 0x36

// Offsets within a Long Descriptors Block
//========================================
#define PIX_CLK_OFFSET 0
#define H_ACTIVE_OFFSET 2
#define H_BLANKING_OFFSET 3
#define V_ACTIVE_OFFSET 5
#define V_BLANKING_OFFSET 6
#define H_SYNC_OFFSET 8
#define H_SYNC_PW_OFFSET 9
#define V_SYNC_OFFSET 10
#define V_SYNC_PW_OFFSET 10
#define H_IMAGE_SIZE_OFFSET 12
#define V_IMAGE_SIZE_OFFSET 13
#define H_BORDER_OFFSET 15
#define V_BORDER_OFFSET 16
#define FLAGS_OFFSET 17


// Data Block Tag Codes
//=====================
#define AUDIO_D_BLOCK 0x01
#define VIDEO_D_BLOCK 0x02
#define VENDOR_SPEC_D_BLOCK 0x03
#define SPKR_ALLOC_D_BLOCK 0x04
#define USE_EXTENDED_TAG 0x07

// Extended Data Block Tag Codes
//==============================
#define COLORIMETRY_D_BLOCK 0x05

#define HDMI_SIGNATURE_LEN 0x03

#define EDID_REV_THREE 0x03
#define EDID_DATA_START 0x04

#define VIDEO_CAPABILITY_D_BLOCK 0x00



/*  Video Descriptor Block  */
typedef struct _hdmi_edid_dtd_video {
    u16 pixel_clock;          /* 54-55 */
    u8  horiz_active;         /* 56 */
    u8  horiz_blanking;       /* 57 */
    u8  horiz_high;           /* 58 */
    u8  vert_active;          /* 59 */
    u8  vert_blanking;        /* 60 */
    u8  vert_high;            /* 61 */
    u8  horiz_sync_offset;    /* 62 */
    u8  horiz_sync_pulse;     /* 63 */
    u8  vert_sync_pulse;      /* 64 */
    u8  sync_pulse_high;      /* 65 */
    u8  horiz_image_size;     /* 66 */
    u8  vert_image_size;      /* 67 */
    u8  image_size_high;      /* 68 */
    u8  horiz_border;         /* 69 */
    u8  vert_border;          /* 70 */
    u8  misc_settings;        /* 71 */
} hdmi_edid_dtd_video;

/* Monitor Limits Descriptor Block */
typedef struct _hdmi_edid_dtd_monitor {
    u16 pixel_clock;          /* 54-55*/
    u8  _reserved1;           /* 56 */
    u8  block_type;           /* 57 */
    u8  _reserved2;           /* 58 */
    u8  min_vert_freq;        /* 59 */
    u8  max_vert_freq;        /* 60 */
    u8  min_horiz_freq;       /* 61 */
    u8  max_horiz_freq;       /* 62 */
    u8  pixel_clock_mhz;      /* 63 */
    u8  GTF[2];               /* 64 -65 */
    u8  start_horiz_freq;     /* 66 */
    u8  C;                    /* 67 */
    u8  M[2];                 /* 68-69 */
    u8  K;                    /* 70 */
    u8  J;                    /* 71 */

} __attribute__ ((packed)) hdmi_edid_dtd_monitor;

/* Text Descriptor Block */
typedef struct _hdmi_edid_dtd_text {
    u16 pixel_clock;          /* 54-55 */
    u8  _reserved1;           /* 56 */
    u8  block_type;           /* 57 */
    u8  _reserved2;           /* 58 */
    u8  text[13];             /* 59-71 */
} __attribute__ ((packed)) hdmi_edid_dtd_text;

/* DTD Union */
typedef union _hdmi_edid_dtd {
    hdmi_edid_dtd_video     video;                  /* video timing data block of dtd block */
    hdmi_edid_dtd_text      monitor_name;           /* monitor name block of dtd block */
    hdmi_edid_dtd_text      monitor_serial_number;  /* monitor serial number block of dtd block */
    hdmi_edid_dtd_text      ascii;                  /* ascii string block of dtd block */
    hdmi_edid_dtd_monitor   monitor_limits;         /* monitor limits block of dtd block */
} __attribute__ ((packed)) hdmi_edid_dtd;

/*    EDID struct    */
typedef struct _hdmi_edid {
    u8  header[8];            /* 00-07  edid的头，8个字节，为固定值(00 FF FF FF FF FF FF 00)，
                                在1.4中为必须设置的*/
    u16 manufacturerID;       /* 08-09  基于ASCII码，最高位设置为0,1没有使用。
                                后面分别的三个五位对应五位编码的ASCII*/
    u16 product_id;           /* 10-11 2字节，用于区别同一个生产商的不同产品，例如模块名*/
    u32 serial_number;        /* 12-15 用于区别相同显示模式下不同个体，应该是不同单个产品，该使用是可选的
                                序列号是唯一的和ASCII不对应，范围为0到4,294,967,295，如果没有使用，则为全0*/

    u8  week_manufactured;    /* 16 该字节为可选，范围为1-54，如果没有使用该字节，则设置为00h*/
    u8  year_manufactured;    /* 17 代表产品生产的年份或是模块年份，如果用于代表模块年份，
                                则week字节要设置为FFh,而该字节存储的是从以下的函数计算得出的数据
                                (Year of Manufacture {or Model Year} - 1990)*/

    u8  edid_version;         /* 18 版本号 当前为1*/
    u8  edid_revision;        /* 19 版本修订号 当前为4*/

    /*基本显示参数和特性---5字节*/
    u8  video_in_definition;  /* 20 源设备需要根据当前字节来确认自身设备的输出视频特性，
                                具体格式，详见3.11ofEDIDrAr2,最高位分别表示数字信号和模拟信号
                                模拟信号:6、5位信号水平标准,4位video设置，3、2、1位同步类型，0位锯齿
                                数字信号:6\5\4位色深，3、2、1、0数字视频标准支持接口
                                如果第7位设置为1，那么24字节的4和3位定义为支持的颜色编码格式
                                如果显示支持多于一种以上的同步种类，同步H&V分隔信号会拥有更高
                                的权限，水平复合同步信号有比较低的权限*/

    /*源设备通过使用这个数据来获取一个大概的图像尺寸来产生一个缩放到合适大小的文字和图像
       21,22字节表示水平和垂直屏幕尺寸，两字节如果有一个设置为0，则21字节表示横屏宽高比，22表示竖屏宽高比*/
    u8  max_horiz_image_size; /* 21 表示设备显示尺寸或是宽高比；表示显示尺寸时，该字节表示水平
                                宽度，精确到cm。当表示宽高比时，则表示为横屏宽高比
                                Aspect Ratio = (Stored Value + 99) ÷ 100*/
    u8  max_vert_image_size;  /* 22 同上，表示垂直高度，精确到cm。当表示宽高比时，则表示竖屏宽高比*/



    u8  display_gamma;        /* 23 显示传输特征，范围1.00 到 3.54 存储值遵循以下公式
                                Stored Value = (GAMMA x 100) – 100
                                如果设置为ffh，那么该字节没有定义，而是在扩展块中进行的定义
                                GAMMA值为生产厂商定义*/


    u8  power_features;       /* 24 用来显示支持的不同显示特征，详见3.14ofEDIDrAr2
                                7、6、5位为显示电源管理，如果第7位设置为0，
                                那么第4、3位为显示颜色类型，如果设置为1,那么第4、3位为颜色编码格式
                                2、1、0三位表示其他支持特征*/


    /**/
    u8  chroma_info[10];      /* 25-34 高9位到2位作为一个字节，低两位1-0和前一个字节的地两位作为一对。
                                所有值应该精确到+/-0.0005 单色显示不考虑实际颜色，
                                只用来显示相应的白点的xy并设置相应的红绿蓝xy为00h
                                详见table3.17*/

    /*Established Timings I & II:3个字节,是一个1bit标志列表，
    用来显示对VESA和其他压缩格式的通用Timing，显示的是Factory Supported Modes,工厂模式
    不用来表示显示设备的局限范围，而是一旦设置为1，则表示Factory Supported Modes
    任何一个Timing都可以用Detailed Timings data field defined来描述*/
    u8  timing_1;             /* 35 */
    u8  timing_2;             /* 36 */
    u8  timing_3;             /* 37 6-0位可能用来标识生产者私有Timing,VESA对此没有相应定义*/

    /*Standard Timings 16字节
    没有用到的区域会被设置为01h，
    所有Standard Timings会被定义为等比像素(1:1)详见table3.19*/
    u8  std_timings[16];      /* 38-53 */

    /*72个字节分为4个数据区，每个18个字节长度，这些区域要么是detailed timing data
    要么是其他数据类型36h → 47h第一 Preferred Timing Mode
    48h → 59h 第二 2nd Detailed Timing Descriptor or the 1st Display Descriptor
    5Ah → 6Bh 第三
    6Ch → 7Dh 第四*/
    hdmi_edid_dtd dtd[4];     /* 54-125
                                1、Detailed Timing Descriptor可能定义4个数据域，分两部分，Detailed Timing Definition
                                2、Display Descriptor Definitions可选，前一个块为Preferred Timing Mode
                                   后三个可能包含video timing definitions或者使用通用格式DisplayDescriptors
                                   如果前三个字节都为0，那么包含的是DisplayDescriptors，第四个字节要包含tag数字，第五个字节为00h
                                   tag为FFh，Display Product Serial Number Descriptor Definition
                                   tag为FEh，Alphanumeric Data String Descriptor
                                   tag为FDh，Display Range Limits & Additional Timing Descriptor Definition，可选
                                   tag为FCh，Display Product Name (ASCII) String Descriptor Definition
                                   FBh       Color Point Descriptor Definition
                                   FAh       Standard Timing Identifier Definition
                                   F9h       Color Management Data Definition
                                   F8h       CVT 3 Byte Code Descriptor Definition
                                   F7h       Established Timings III Descriptor Definition
                                   11h to F6h  Unused – Reserved Data Tag Number
                                   10h       Dummy Descriptor Definition
                                   00h to 0Fh  Manufacturer Specified Data Tag Numbers
                              */

    u8  extension_edid;       /* 126 EDID扩展块的数量
                                源设备会执行checksum校验*/
    u8  checksum;             /* 127 */
    u8  extension_tag;        /* 00 (extensions follow EDID) */
    u8  extention_rev;        /* 01 */
    u8  offset_dtd;           /* 02 */
    u8  num_dtd;              /* 03 */

    u8  data_block[123];      /* 04 - 126 */
    u8  extension_checksum;   /* 127 */

    u8  ext_datablock[256];   /* extend data block */
} __attribute__ ((packed)) hdmi_edid;

typedef struct _hdmi_video_timings {

    u16 x_res;          /* Unit: pixels */
    u16 y_res;          /* Unit: pixels */

    u32 pixel_clock;    /* Unit: KHz */

    u16 hsw;    /* Horizontal synchronization pulse width, Unit: pixel clocks */
    u16 hfp;    /* Horizontal front porch, Unit: pixel clocks */
    u16 hbp;    /* Horizontal back porch, Unit: pixel clocks */

    u16 vsw;    /* Vertical synchronization pulse width, Unit: line clocks */
    u16 vfp;    /* Vertical front porch, Unit: line clocks */
    u16 vbp;    /* Vertical back porch, Unit: line clocks */

    u16 refresh_rate;     /* Unit: KHz */
    u16 reserved;
} hdmi_video_timings;

typedef struct _hdmi_hvsync_pol {
    int vsync_pol;              /* horizontal polarity */
    int hsync_pol;              /* vertical polarity */
} hdmi_hvsync_pol;

typedef enum _extension_edid_db {
    DATABLOCK_AUDIO    = 1,     /* index of audio block in cea */
    DATABLOCK_VIDEO    = 2,     /* index of video block in cea */
    DATABLOCK_VENDOR   = 3,     /* index of vendor block in cea */
    DATABLOCK_SPEAKERS = 4,     /* index of speakers block in cea */
    DATABLOCK_EXTENDED_TAG = 7, /* index of extended tag block in cea */
} extension_edid_db;

typedef struct _img_edid {
    bool pref;                  /* video timing native */
    int code;                   /* video timing code */
} img_edid;

typedef struct _image_format {
    int number;                                 /* number of video timing */
    img_edid fmt[HDMI_IMG_FORMAT_MAX_LENGTH];   /* array of video timing code */
} image_format;

typedef struct _audio_edid {
    int num_of_ch;              /* number of audio channel */
    int format;                 /* audio format */
    int sampling_freq;          /* audio frequency */
} audio_edid;

typedef struct _audio_format {
    int number;                                     /* number of audio timing */
    audio_edid fmt[HDMI_AUDIO_FORMAT_MAX_LENGTH];   /* array of audio type */
} audio_format;

typedef struct _latency {
    /* vid: if indicated, value=1+ms/2 with a max of 251 meaning 500ms */
    int vid_latency;            /* video latency */
    int aud_latency;            /* audio latency */
    int int_vid_latency;        /* interlaced video latency */
    int int_aud_latency;        /* interlaced audio latency */
} latency;

typedef struct _deep_color {
    bool bit_30;                /* deep color 30 bit support */
    bool bit_36;                /* deep color 36 bit support */
    int max_tmds_freq;          /* max tmds clock frequency */
} deep_color;

typedef struct _hdmi_cm {
    int code;                   /* video timing code */
    int mode;                   /* video mode: 0 for VESA, 1 for CEA  */
} hdmi_cm;

typedef enum _edid_timing_mode {
    EDID_TIMING_MODE_P,         /* video timing pronounced mode */
    EDID_TIMING_MODE_I          /* video timing interleaved mode */
} edid_timing_mode;

extern bool edid_ai_supported(u8 *edid);
extern void edid_dump(u8* edid);
extern void edid_dump_parser(u8* edid);
extern uint8_t SiiDrvParse861Extensions(uint8_t NumOfExtensions);
extern bool SiiDrvParseDetailedTiming(uint8_t *Data, uint8_t DetailedTimingOffset, uint8_t Block);
extern void edid_dump_video_timings(hdmi_video_timings *timings);
extern int edid_get_audio_format(u8 *edid, audio_format *format);

extern hdmi_cm edid_get_best_timing(hdmi_edid *edid);
extern void edid_get_deep_color_info(u8 *edid, deep_color *format);
extern int edid_get_default_code(void);
extern hdmi_hvsync_pol* edid_get_hvpol_byindex(int index);
extern int edid_get_image_format(u8 *edid, image_format *format);
extern int edid_get_s3d_timings_index(int mode, int code);

extern hdmi_video_timings* edid_get_timings_byindex(int index);
extern int edid_get_timings_index(int mode, int code);
extern hdmi_cm edid_get_best_timing_code(hdmi_edid *edid, bool s3d_enabled);
extern edid_timing_mode edid_get_timing_mode(int code);
extern int edid_get_timing_order(int code, bool mhl_check);
extern int edid_get_vesa_timing_order(int code, bool mhl_check);
extern bool edid_has_ieee_id(u8 *edid);
extern bool edid_has_vcdb(u8 *edid);
extern bool edid_is_valid_code(int mode, int code);
extern bool edid_is_valid_edid(u8 *edid);
extern bool edid_s3d_supported(u8 *edid);
extern bool edid_tv_yuv_supported(u8 *edid);
extern int get_datablock_offset(u8 *edid, extension_edid_db datablock,
                                  int *offset);
extern int edid_get_timings_info(hdmi_edid_dtd *edid_dtd,
                                   hdmi_video_timings *timings);
extern int mhl_read_edid(void);
extern void s3d_format_dump(u8 *edid,int offset);
extern bool SiiDrvDoEDID_Checksum(uint8_t *Block);
extern void SiiDrvEDIDReadFIFO(uint8_t Segment, uint8_t BlockOffset, uint8_t *pBufEdid, uint8_t FifoNum);
extern uint8_t SiiDrvMhlTxReadEdid (void);
extern uint8_t SiiDrvParse861LongDescriptors(uint8_t *Data);
extern uint8_t SiiDrvParseEDID (uint8_t *pEdid, uint8_t *numExt);
extern void SiiDrvReadBlockEDID(uint8_t Block);

extern void edid_print_valid_timing_code(hdmi_cm cm, char** p, int *size, bool mhl_check);
extern int edid_get_timing_code_from_videoblock(char** p, int *size,  bool mhl_check);
extern int edid_get_timing_code_from_b0DTD(char** p, int *size, bool mhl_check, bool s3d_enabled);
extern int edid_get_timing_code_from_SVD(char** p, int *size, bool mhl_check, bool s3d_enabled);
extern int edid_get_timing_code_from_b1DTD(char** p, int *size, bool mhl_check, bool s3d_enabled, bool audio_support);
extern int edid_get_timing_code_from_EstablishTiming(char** p, int *size,  bool mhl_check);
extern int edid_get_timing_code_from_StandardTiming(char** p, int *size, bool mhl_check);

#endif

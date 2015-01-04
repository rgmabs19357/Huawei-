/**********************************************************************************/

/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/

//***************************************************************************
//!file     si_reg_access.h
//!brief    Silicon Image implementation of MHL driver.
//
//***************************************************************************/
#ifndef __SI_REG_ACCESS_H__
#define __SI_REG_ACCESS_H__

#include <linux/types.h>

#define CHECK_SOFTWARE_TPI      0

#define FLD_MASK(start, end)    (((1 << ((start) - (end) + 1)) - 1) << (end))
#define FLD_VAL(val, start, end) (((val) << (end)) & FLD_MASK(start, end))
#define FLD_GET(val, start, end) (((val) & FLD_MASK(start, end)) >> (end))
#define FLD_MOD(orig, val, start, end) (((orig) & ~FLD_MASK(start, end)) | FLD_VAL(val, start, end))


#define MHL_CORE_SYS	hw_res.base_core 
#define MHL_TPI_SYS	 	hw_res.base_tpi 
#define MHL_PHY_BASE	hw_res.base_phy
#define MHL_CBUS_BASE	hw_res.base_cbus

#define INDEXED_PAGE_0 0x01
#define INDEXED_PAGE_1 0x02
#define INDEXED_PAGE_2 0x03

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#define P0_DDC_FIFO_EMPTY_MASK	0x04
#define P0_DDC_FIFO_FULL_MASK	0x08
#define ADDR_MASK				0x03FF

#define BIT_TPI_INPUT_FORMAT_MASK           0x03
#define BIT_TPI_INPUT_FORMAT_RGB            0x00
#define BIT_TPI_INPUT_FORMAT_YCbCr444       0x01
#define BIT_TPI_INPUT_FORMAT_YCbCr422       0x02
#define BIT_TPI_INPUT_FORMAT_INTERNAL_RGB   0x03

#define BIT_TPI_INPUT_QUAN_RANGE_MASK       0x0C
#define BIT_TPI_INPUT_QUAN_RANGE_AUTO       0x00
#define BIT_TPI_INPUT_QUAN_RANGE_LIMITED    0x04
#define BIT_TPI_INPUT_QUAN_RANGE_FULL       0x08
#define BIT_TPI_INPUT_QUAN_RANGE_RSVD       0x0C

#define BIT_TPI_OUTPUT_FORMAT_MASK          0x03
#define BIT_TPI_OUTPUT_FORMAT_HDMI_TO_RGB   0x00
#define BIT_TPI_OUTPUT_FORMAT_YCbCr444      0x01
#define BIT_TPI_OUTPUT_FORMAT_YCbCr422      0x02
#define BIT_TPI_OUTPUT_FORMAT_DVI_TO_RGB    0x03

#define BIT_TPI_OUTPUT_QUAN_RANGE_MASK      0x0C
#define BIT_TPI_OUTPUT_QUAN_RANGE_AUTO      0x00
#define BIT_TPI_OUTPUT_QUAN_RANGE_LIMITED   0x04
#define BIT_TPI_OUTPUT_QUAN_RANGE_FULL      0x08
#define BIT_TPI_OUTPUT_QUAN_RANGE_RSVD      0x0C

#define BIT_EDID_FIELD_FORMAT_HDMI_TO_RGB   0x00
#define BIT_EDID_FIELD_FORMAT_YCbCr422      0x01
#define BIT_EDID_FIELD_FORMAT_YCbCr444      0x02
#define BIT_EDID_FIELD_FORMAT_DVI_TO_RGB    0x03

#define TPI_1A_AUTO_REAUTHENTICATION_MASK	(0x40)
#define TPI_1A_AUTO_REAUTHENTICATION_OFF	(0x00)
#define TPI_1A_AUTO_REAUTHENTICATION_ENABLE	(0x40)

#define TMDS_OUTPUT_CONTROL_MASK			(0x10)
#define TMDS_OUTPUT_CONTROL_ACTIVE			(0x00)
#define TMDS_OUTPUT_CONTROL_POWER_DOWN		(0x10)

#define AV_MUTE_MASK						(0x08)
#define AV_MUTE_NORMAL						(0x00)
#define AV_MUTE_MUTED						(0x08)

#define DDC_BUS_REQUEST_MASK				(0x04)
#define DDC_BUS_REQUEST_NOT_USING			(0x00)
#define DDC_BUS_REQUEST_REQUESTED			(0x04)

#define DDC_BUS_GRANT_MASK					(0x02)
#define DDC_BUS_GRANT_NOT_AVAILABLE			(0x00)
#define DDC_BUS_GRANT_GRANTED				(0x02)

#define TMDS_OUTPUT_MODE_MASK				(0x01)
#define TMDS_OUTPUT_MODE_DVI				(0x00)
#define TMDS_OUTPUT_MODE_HDMI				(0x01)

#define CTRL_PIN_CONTROL_MASK				(BIT4)
#define CTRL_PIN_TRISTATE					(0x00)
#define CTRL_PIN_DRIVEN_TX_BRIDGE			(0x10)

#define TX_POWER_STATE_MASK					(BIT1 | BIT0)
#define TX_POWER_STATE_D0					(0x00)
#define TX_POWER_STATE_D2					(0x02)
#define TX_POWER_STATE_D3					(0x03)

typedef enum{
     BIT_TPI_AUDIO_HANDLING_MASK                          = 0x03,
     BIT_TPI_AUDIO_HANDLING_PASS_BASIC_AUDIO_ONLY         = 0x00,
     BIT_TPI_AUDIO_HANDLING_PASS_ALL_AUDIO_MODES          = 0x01,
     BIT_TPI_AUDIO_HANDLING_DOWNSAMPLE_INCOMING_AS_NEEDED = 0x02,
      BIT_TPI_AUDIO_HANDLING_DO_NOT_CHECK_AUDIO_STREAM    = 0x03
}TpiConfig2Bits_e;

typedef enum{
     BIT_TPI_AUDIO_CODING_TYPE_MASK             = 0x0F,
     BIT_TPI_AUDIO_CODING_TYPE_STREAM_HEADER    = 0x00,
     BIT_TPI_AUDIO_CODING_TYPE_PCM              = 0x01,
     BIT_TPI_AUDIO_CODING_TYPE_AC3              = 0x02,
     BIT_TPI_AUDIO_CODING_TYPE_MPEG1            = 0x03,
     BIT_TPI_AUDIO_CODING_TYPE_MP3              = 0x04,
     BIT_TPI_AUDIO_CODING_TYPE_MPEG2            = 0x05,
     BIT_TPI_AUDIO_CODING_TYPE_AAC              = 0x06,
     BIT_TPI_AUDIO_CODING_TYPE_DTS              = 0x07,
     BIT_TPI_AUDIO_CODING_TYPE_ATRAC            = 0x08,

     BIT_TPI_CONFIG3_MUTE_MASK                  = 0x10,
     BIT_TPI_CONFIG3_MUTE_NORMAL                = 0x00,
     BIT_TPI_CONFIG3_MUTE_MUTED                 = 0x10,

     BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_MASK    = 0x20,
     BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_2CH     = 0x00,
     BIT_TPI_CONFIG3_AUDIO_PACKET_HEADER_LAYOUT_8CH_MAX = 0x20,

     BIT_TPI_CONFIG_3_AUDIO_INTERFACE_MASK      = 0xC0,
     BIT_TPI_CONFIG_3_AUDIO_INTERFACE_DISABLED  = 0x00,
     BIT_TPI_CONFIG_3_AUDIO_INTERFACE_SPDIF     = 0x40,
     BIT_TPI_CONFIG_3_AUDIO_INTERFACE_I2S       = 0x80,
     BIT_TPI_CONFIG_3_AUDIO_INTERFACE_HD_AUDIO  = 0xC0
}TpiConfig3Bits_e;

#define EXTENDED_LINK_PROTECTION_MASK		(BIT7)
#define EXTENDED_LINK_PROTECTION_NONE		(0x00)
#define EXTENDED_LINK_PROTECTION_SECURE		(0x80)

#define LOCAL_LINK_PROTECTION_MASK			(BIT6)
#define LOCAL_LINK_PROTECTION_NONE			(0x00)
#define LOCAL_LINK_PROTECTION_SECURE		(0x40)

#define LINK_STATUS_MASK					(BIT5 | BIT4)
#define LINK_STATUS_NORMAL					(0x00)
#define LINK_STATUS_LINK_LOST				(0x10)
#define LINK_STATUS_RENEGOTIATION_REQ		(0x20)
#define LINK_STATUS_LINK_SUSPENDED			(0x30)

#define HDCP_REPEATER_MASK					(BIT3)
#define HDCP_REPEATER_NO					(0x00)
#define HDCP_REPEATER_YES					(0x08)

#define CONNECTOR_TYPE_MASK					(BIT2 | BIT0)
#define CONNECTOR_TYPE_DVI					(0x00)
#define CONNECTOR_TYPE_RSVD					(0x01)
#define CONNECTOR_TYPE_HDMI					(0x04)
#define CONNECTOR_TYPE_FUTURE				(0x05)

#define PROTECTION_TYPE_MASK				(BIT1)
#define PROTECTION_TYPE_NONE				(0x00)
#define PROTECTION_TYPE_HDCP				(0x02)

typedef enum
{
     BIT_TPI_HDCP_CONTROL_DATA_COPP_PROTLEVEL_MASK    = 0x01,
     BIT_TPI_HDCP_CONTROL_DATA_COPP_PROTLEVEL_MIN     = 0x00,
     BIT_TPI_HDCP_CONTROL_DATA_COPP_PROTLEVEL_MAX     = 0x01,

     BIT_TPI_HDCP_CONTROL_DATA_DOUBLE_RI_CHECK_MASK   = 0x04,
     BIT_TPI_HDCP_CONTROL_DATA_DOUBLE_RI_CHECK_DISABLE= 0x00,
     BIT_TPI_HDCP_CONTROL_DATA_DOUBLE_RI_CHECK_ENABLE = 0x04

}TpiHdcpControlDataBits_e;

#define PROTECTION_LEVEL_MASK				(BIT0)
#define PROTECTION_LEVEL_MIN				(0x00)
#define PROTECTION_LEVEL_MAX				(0x01)

#define KSV_FORWARD_MASK					(BIT4)
#define KSV_FORWARD_ENABLE					(0x10)
#define KSV_FORWARD_DISABLE					(0x00)

#define HDCP_MAJOR_REVISION_MASK			(BIT7 | BIT6 | BIT5 | BIT4)
#define HDCP_MAJOR_REVISION_VALUE			(0x10)

#define HDCP_MINOR_REVISION_MASK			(BIT3 | BIT2 | BIT1 | BIT0)
#define HDCP_MINOR_REVISION_VALUE			(0x02)

typedef enum{
     BITS_TPI_INTR_ST0_NOP                          = 0x00
#ifdef OLD_TPI_REGS //(
    ,BIT_TPI_INTR_ST0_HOT_PLUG_EVENT                = 0x01
    ,BIT_TPI_INTR_ST0_RECEIVER_SENSE_EVENT          = 0x02

    ,BIT_TPI_INTR_ST0_HOT_PLUG_PIN_STATE_MASK       = 0x04
    ,BIT_TPI_INTR_ST0_HOT_PLUG_PIN_STATE_LOW        = 0x00
    ,BIT_TPI_INTR_ST0_HOT_PLUG_PIN_STATE_HIGH       = 0x04
#else //)(
    ,BIT_TPI_INTR_ST0_BKSV_ERR                      = 0x02
    ,BIT_TPI_INTR_ST0_BKSV_DONE                     = 0x04
#endif //)
    ,BIT_TPI_INTR_ST0_KSV_FIFO_FIRST                = 0x08
    ,BIT_TPI_INTR_ST0_AUDIO_ERROR_EVENT             = 0x10
    ,BIT_TPI_INTR_ST0_HDCP_SECURITY_CHANGE_EVENT    = 0x20
    ,BIT_TPI_INTR_ST0_HDCP_VPRIME_VALUE_READY_EVENT = 0x40
    ,BIT_TPI_INTR_ST0_HDCP_AUTH_STATUS_CHANGE_EVENT = 0x80
}TpiIntrSt1Bits_e;

#define CPI_EVENT_MASK						(BIT3)
#define CPI_EVENT_NO						(0x00)
#define CPI_EVENT_YES						(0x08)
#define RX_SENSE_MASK						(BIT3)		/* This bit is dual purpose depending on the value of 0x3C[3] */
#define RX_SENSE_NOT_ATTACHED				(0x00)
#define RX_SENSE_ATTACHED					(0x08)

#define HOT_PLUG_PIN_STATE_MASK				(BIT2)
#define HOT_PLUG_PIN_STATE_LOW				(0x00)
#define HOT_PLUG_PIN_STATE_HIGH				(0x04)

#define RECEIVER_SENSE_EVENT_MASK			(BIT1)
#define RECEIVER_SENSE_EVENT_NO				(0x00)
#define RECEIVER_SENSE_EVENT_YES			(0x02)

#define HOT_PLUG_EVENT_MASK					(BIT0)
#define HOT_PLUG_EVENT_NO					(0x00)
#define HOT_PLUG_EVENT_YES					(0x01)

// Define the rest here when needed.

typedef enum{
     BIT_TPI_INFO_SEL_MASK                  = 0x07
    ,BIT_TPI_INFO_SEL_AVI                   = 0x00
    ,BIT_TPI_INFO_SEL_SPD                   = 0x01
    ,BIT_TPI_INFO_SEL_Audio                 = 0x02
    ,BIT_TPI_INFO_SEL_MPEG                  = 0x03
    ,BIT_TPI_INFO_SEL_GENERIC               = 0x04
    ,BIT_TPI_INFO_SEL_GENERIC2              = 0x05

    ,BIT_TPI_INFO_READ_FLAG_MASK            = 0x20
    ,BIT_TPI_INFO_READ_FLAG_NO_READ         = 0x00
    ,BIT_TPI_INFO_READ_FLAG_READ            = 0x20
    ,BIT_TPI_INFO_RPT                       = 0x40
    ,BIT_TPI_INFO_EN                        = 0x80
}TpiInfoFSelBits_e;

#define SET_BITS 0xFF
#define CLEAR_BITS 0x00

#define DOWN_SAMPLE (BIT0)                          //4:4:4=>4:2:2
#define RANGE_COMPRESS (BIT1)                       //0~255=>16~235/240
#define RGB2YCbCr (BIT2)
#define RANGE_CLIP (BIT3)                           //0~16=>16
#define CLIP_INPUTS_YC (BIT4)                       //0: RGB, 1:YCbCr
#define PUF_RANGE_CLIP (BIT5)                       //
#define PUF_DITHER (BIT7)                           //10to8 before puf

#define UP_SAMPLE (BIT2)                            //4:2:2=>4:4:4
#define YCbCr2RGB (BIT3)
#define RANGE_EXPAND (BIT4)                         //16~235/240=>0~255
#define DITHER (BIT5)                               //10to8 after puf

typedef enum
{
     BIT_VID_OVRRD_3DCONV_EN_MASK       = 0x10
    ,BIT_VID_OVRRD_3DCONV_EN_NORMAL     = 0x00
    ,BIT_VID_OVRRD_3DCONV_EN_FRAME_PACK = 0x10

    ,BIT_VID_OVRRD_M1080p_ovrrd_MASK    = 0x40
    ,BIT_VID_OVRRD_M1080p_ovrrd_DISABLE = 0x00
    ,BIT_VID_OVRRD_M1080p_ovrrd_ENABLE  = 0x40
}VidOvrRdBits_e;

typedef enum
{
    BIT_INTR1_RSEN_CHG  = 0x20,
      BIT_INTR1_HPD_CHG = 0x40
} Intr1Bits_e;

#define TMDS_OE (BIT4)

#define DDC_GPU_REQUEST (BIT0)
#define DDC_TPI_SW (BIT2)
#define VIDEO_MUTE_EN (BIT5)
#define SW_TPI_EN (BIT7)


#define DDC_FIFO_EMPTY (BIT2)
#define DDC_IN_PROGRAMMING (BIT4)

typedef enum
{
      BIT_INTRM4_SCDT_CHG     = BIT0,
      BIT_INTRM4_VBUS_CHG   = BIT1,
      BIT_INTRM4_MHL_EST    = BIT2,
      BIT_INTRM4_USB_EST    = BIT3,
      BIT_INTRM4_CBUS_LKOUT = BIT4,
      BIT_INTRM4_CBUS_DISCONNECT = BIT5,
      BIT_INTRM4_RGND_DETECTION = BIT6
} CBusIntrm4Bits_e;

typedef enum
{
    BIT_ZONE_CTRL_SW_RST_SZONE_I2C_MASK = 0x30
}ZoneCtrlSwRstBits_e;

#define BIT_MSC_MSG_RCV           (BIT3)    /* Responder sent a VS_MSG packet (response data or command.) */
#define BIT_MSC_XFR_DONE          (BIT4)    /* Responder sent ACK packet (not VS_MSG) */

#define BIT_BUS_CONNECTED         0x01

#define BIT_TRANSFER_PVT_CMD      0x01
#define BIT_SEND_MSC_MSG          0x02

#define MSC_START_BIT_MSC_CMD     (0x01 << 0)
#define MSC_START_BIT_VS_CMD      (0x01 << 1)
#define MSC_START_BIT_READ_REG    (0x01 << 2)
#define MSC_START_BIT_WRITE_REG   (0x01 << 3)
#define MSC_START_BIT_WRITE_BURST (0x01 << 4)

#define MSC_REQUESTOR_DONE_NACK   (0x01 << 6)

typedef enum
{
	  BIT_CBUS_CEC_ABRT   = 0x02,               /*Source sent ABORT to Sink.*/ /* Responder aborted DDC command at translation layer */
      BIT_CBUS_DDC_ABRT = 0x04,           /* Responder sent a VS_MSG packet (response data or command.) */
      BIT_CBUS_MSC_ABORT = 0x08,        
      BIT_CBUS_MSC_SET_CAP_ID_RCVD = 0x10,
      BIT_CBUS_RCV_VALID = 0x20,
      BIT_CBUS_CMD_ABORT = 0x40,   /*Source as requester, sink as responder.*/
      BIT_CBUS_MHL_CABLE_CNX_CHG = 0x80
} CBusInt1Bits_e;

typedef enum{
     BIT_CBUS_DDC_MAX_FAIL      = 0x01,
     BIT_CBUS_DDC_PROTO_ERR     = 0x02,
     BIT_CBUS_DDC_TIMEOUT       = 0x04,
     BIT_CBUS_DDC_PEER_ABORT    = 0x80
}CBusDDCAbortIntBits_e;
 
typedef enum{
     BIT_CBUS_MSC_MT_ABORT_INT_MAX_FAIL             = 0x01,
     BIT_CBUS_MSC_MT_ABORT_INT_PROTO_ERR            = 0x02,
     BIT_CBUS_MSC_MT_ABORT_INT_TIMEOUT              = 0x04,
     BIT_CBUS_MSC_MT_ABORT_INT_UNDEF_CMD            = 0x08,
     BIT_CBUS_MSC_MT_ABORT_INT_MSC_MT_PEER_ABORT    = 0x80
}MscMtAbortIntBits_e;

typedef enum{
     BIT_CBUS_MSC_MR_ABORT_INT_MAX_FAIL             = 0x01,
     BIT_CBUS_MSC_MR_ABORT_INT_PROTO_ERR            = 0x02,
     BIT_CBUS_MSC_MR_ABORT_INT_TIMEOUT              = 0x04,
     BIT_CBUS_MSC_MR_ABORT_INT_UNDEF_CMD            = 0x08,
     BIT_CBUS_MSC_MR_ABORT_INT_MSC_MR_PEER_ABORT    = 0x80
}MscMrAbortIntBits_e;

#define MSC_INT2_REQ_WRITE_MSC (0x01 << 0) // Write REG data written.
#define MSC_INT2_HEARTBEAT_MAXFAIL (0x01 << 1) // Retry threshold exceeded for sending the Heartbeat

#define MSC_HEARTBEAT_PERIOD_MASK 0x0F    // bits 3..0
#define MSC_HEARTBEAT_FAIL_LIMIT_MASK 0x70    // bits 6..4
#define MSC_HEARTBEAT_ENABLE 0x80    // bit 7

#define MSC_TIMEOUT_LIMIT_MSB_MASK (0x0F)          // default is 1
#define MSC_LEGACY_BIT (0x01 << 7)     // This should be cleared.

typedef enum
{
	BIT_CBUS_CNX_CHG = BIT0,
	BIT_CBUS_MSC_MT_DONE = BIT1,
	BIT_CBUS_HPD_CHANGE = BIT2,
	BIT_CBUS_MSC_MR_WRITE_STAT = BIT3,
	BIT_CBUS_MSC_MR_MSC_MSG = BIT4, /* Responder sent a VS_MSG packet (response data or command.) */
	BIT_CBUS_MSC_MR_WRITE_BURST = BIT5,
	BIT_CBUS_MSC_MR_SET_INT   = BIT6,
	BIT_CBUS_MSC_MT_DONE_NACK = BIT7
} CBusInt0Bits_e;

typedef enum
{
      BIT_CBUS_CONNECTED = 0x0001,
      BIT_MHL_MODE = 0x0002,
      BIT_CBUS_HPD = 0x0004,
      BIT_MSC_HB_SUCCESS = 0x0008,
      BIT_MHL_CABLE_PRESENT = 0x0010
} CBusStatusBits_e;

/* REG£ºVendor ID Low Byte
   Name:  P0_VND_IDL_ADDR */
#define P0_VND_IDL_ADDR                  (0x000)

/* REG£ºVendor ID High Byte
   Name:  P0_VND_IDH_ADDR */
#define P0_VND_IDH_ADDR                  (0x004)

/* REG£ºDevice ID Low Byte
   Name:  P0_DEV_IDL_ADDR */
#define P0_DEV_IDL_ADDR                  (0x008)

/* REG£ºDevice ID High Byte
   Name:  P0_DEV_IDH_ADDR */
#define P0_DEV_IDH_ADDR                  (0x00C)

/* REG£ºDevice Revision Byte
   Name:  P0_DEV_REV_ADDR */
#define P0_DEV_REV_ADDR                  (0x010)

/* REG£ºSoftware Reset Register
   Name:  P0_SRST_ADDR */
#define P0_SRST_ADDR                     (0x014)

/* REG£ºSystem Control Register #1
   Name:  P0_SYS_CTRL1_ADDR */
#define P0_SYS_CTRL1_ADDR                (0x020)

/* REG£ºSystem Status Register
   Name:  P0_SYS_STAT_ADDR */
#define P0_SYS_STAT_ADDR                 (0x024)

/* REG£ºLegacy Register
   Name:  P0_SYS_CTRL3_ADDR */
#define P0_SYS_CTRL3_ADDR                (0x028)

/* REG£ºData Control Register
   Name:  P0_DCTL_ADDR */
#define P0_DCTL_ADDR                     (0x034)

/* REG£ºHDCP Control Register
   Name:  P0_HDCP_CTRL_ADDR */
#define P0_HDCP_CTRL_ADDR                (0x03C)

/* REG£ºHDCP BKSV Register 1
   Name:  P0_BKSV1_ADDR */
#define P0_BKSV1_ADDR                    (0x040)

/* REG£ºHDCP BKSV Register 2
   Name:  P0_BKSV2_ADDR */
#define P0_BKSV2_ADDR                    (0x044)

/* REG£ºHDCP BKSV Register 3
   Name:  P0_BKSV3_ADDR */
#define P0_BKSV3_ADDR                    (0x048)

/* REG£ºHDCP BKSV Register 4
   Name:  P0_BKSV4_ADDR */
#define P0_BKSV4_ADDR                    (0x04C)

/* REG£ºHDCP BKSV Register 5
   Name:  P0_BKSV5_ADDR */
#define P0_BKSV5_ADDR                    (0x050)

/* REG£ºHDCP AN Register1
   Name:  P0_AN1_ADDR */
#define P0_AN1_ADDR                      (0x054)

/* REG£ºHDCP AN Register2
   Name:  P0_AN2_ADDR */
#define P0_AN2_ADDR                      (0x058)

/* REG£ºHDCP AN Register3
   Name:  P0_AN3_ADDR */
#define P0_AN3_ADDR                      (0x05C)

/* REG£ºHDCP AN Register4
   Name:  P0_AN4_ADDR */
#define P0_AN4_ADDR                      (0x060)

/* REG£ºHDCP AN Register5
   Name:  P0_AN5_ADDR */
#define P0_AN5_ADDR                      (0x064)

/* REG£ºHDCP AN Register6
   Name:  P0_AN6_ADDR */
#define P0_AN6_ADDR                      (0x068)

/* REG£ºHDCP AN Register7
   Name:  P0_AN7_ADDR */
#define P0_AN7_ADDR                      (0x06C)

/* REG£ºHDCP AN Register8
   Name:  P0_AN8_ADDR */
#define P0_AN8_ADDR                      (0x070)

/* REG£ºHDCP AKSV Register1
   Name:  P0_AKSV1_ADDR */
#define P0_AKSV1_ADDR                    (0x074)

/* REG£ºHDCP AKSV Register2
   Name:  P0_AKSV2_ADDR */
#define P0_AKSV2_ADDR                    (0x078)

/* REG£ºHDCP AKSV Register3
   Name:  P0_AKSV3_ADDR */
#define P0_AKSV3_ADDR                    (0x07C)

/* REG£ºHDCP AKSV Register4
   Name:  P0_AKSV4_ADDR */
#define P0_AKSV4_ADDR                    (0x080)

/* REG£ºHDCP AKSV Register5
   Name:  P0_AKSV5_ADDR */
#define P0_AKSV5_ADDR                    (0x084)

/* REG£ºHDCP Ri Register1
   Name:  P0_RI1_ADDR */
#define P0_RI1_ADDR                      (0x088)

/* REG£ºHDCP Ri Register2
   Name:  P0_RI2_ADDR */
#define P0_RI2_ADDR                      (0x08C)

/* REG£ºHDCP Ri 128 Compare Register
   Name:  P0_RI_128_COMP_ADDR */
#define P0_RI_128_COMP_ADDR              (0x090)

/* REG£ºHDCP I Counter Register
   Name:  P0_I_CNT_ADDR */
#define P0_I_CNT_ADDR                    (0x094)

/* REG£ºRi Status Register
   Name:  P0_RI_STAT_ADDR */
#define P0_RI_STAT_ADDR                  (0x098)

/* REG£ºRi Command Register
   Name:  P0_RI_CMD_ADDR */
#define P0_RI_CMD_ADDR                   (0x09C)

/* REG£ºRi Line Start Register
   Name:  P0_RI_LINE_START_ADDR */
#define P0_RI_LINE_START_ADDR            (0x0A0)

/* REG£ºRi From RX Register1
   Name:  P0_RI_RX_L_ADDR */
#define P0_RI_RX_L_ADDR                  (0x0A4)

/* REG£ºRi From RX Register2
   Name:  P0_RI_RX_H_ADDR */
#define P0_RI_RX_H_ADDR                  (0x0A8)

/* REG£ºRi Debug Registers
   Name:  P0_RI_DEBUG_ADDR */
#define P0_RI_DEBUG_ADDR                 (0x0AC)

/* REG£ºVideo DE Delay Register
   Name:  P0_DE_DLY_ADDR */
#define P0_DE_DLY_ADDR                   (0x0C8)

/* REG£ºVideo DE Control Register
   Name:  P0_DE_CTRL_ADDR */
#define P0_DE_CTRL_ADDR                  (0x0CC)

/* REG£ºVideo DE Top Register
   Name:  P0_DE_TOP_ADDR */
#define P0_DE_TOP_ADDR                   (0x0D0)

/* REG£ºVideo DE Count Register1
   Name:  P0_DE_CNTL_ADDR */
#define P0_DE_CNTL_ADDR                  (0x0D8)

/* REG£ºVideo DE Count Register2
   Name:  P0_DE_CNTH_ADDR */
#define P0_DE_CNTH_ADDR                  (0x0DC)

/* REG£ºVideo DE Line Register1
   Name:  P0_DE_LINL_ADDR */
#define P0_DE_LINL_ADDR                  (0x0E0)

/* REG£ºVideo DE Line Register2
   Name:  P0_DE_LINH_ADDR */
#define P0_DE_LINH_ADDR                  (0x0E4)

/* REG£ºVideo H Resolution Register1
   Name:  P0_HRES_L_ADDR */
#define P0_HRES_L_ADDR                   (0x0E8)

/* REG£ºVideo H Resolution Register2
   Name:  P0_HRES_H_ADDR */
#define P0_HRES_H_ADDR                   (0x0EC)

/* REG£ºVideo V Refresh Register1
   Name:  P0_VRES_L_ADDR */
#define P0_VRES_L_ADDR                   (0x0F0)

/* REG£ºVideo V Refresh Register2
   Name:  P0_VREL_H_ADDR */
#define P0_VREL_H_ADDR                   (0x0F4)

/* REG£ºVideo Interlace Adjustment Register
   Name:  P0_IADJUST_ADDR */
#define P0_IADJUST_ADDR                  (0x0F8)

/* REG£ºVideo SYNC Polarity Detection Register
   Name:  P0_POL_DETECT_ADDR */
#define P0_POL_DETECT_ADDR               (0x0FC)

/* REG£ºVideo Hbit to HSYNC Register1
   Name:  P0_HBIT_2HSYNC1_ADDR */
#define P0_HBIT_2HSYNC1_ADDR             (0x100)

/* REG£ºVideo Hbit to HSYNC Register2
   Name:  P0_HBIT_2HSYNC2_ADDR */
#define P0_HBIT_2HSYNC2_ADDR             (0x104)

/* REG£ºVideo Field2 HSYNC Offset Register1
   Name:  P0_FLD2_HS_OFSTL_ADDR */
#define P0_FLD2_HS_OFSTL_ADDR            (0x108)

/* REG£ºVideo Field2 HSYNC Offset Register2
   Name:  P0_FLD2_HS_OFSTH_ADDR */
#define P0_FLD2_HS_OFSTH_ADDR            (0x10C)

/* REG£ºVideo HSYNC Length Register1
   Name:  P0_HWIDTH1_ADDR */
#define P0_HWIDTH1_ADDR                  (0x110)

/* REG£ºVideo HSYNC Length Register2
   Name:  P0_HWIDTH2_ADDR */
#define P0_HWIDTH2_ADDR                  (0x114)

/* REG£ºVideo Vbit to VSYNC Register
   Name:  P0_VBIT_TO_VSYNC_ADDR */
#define P0_VBIT_TO_VSYNC_ADDR            (0x118)

/* REG£ºVideo VSYNC Length Register
   Name:  P0_VWIDTH_ADDR */
#define P0_VWIDTH_ADDR                   (0x11C)

/* REG£ºVideo Control Register
   Name:  P0_VID_CTRL_ADDR */
#define P0_VID_CTRL_ADDR                 (0x0120)

/* REG£ºVideo Action Enable Register
   Name:  P0_VID_ACEN_ADDR */
#define P0_VID_ACEN_ADDR                 (0x0124)

/* REG£ºVideo Mode1 Register
   Name:  P0_VID_MODE_ADDR */
#define P0_VID_MODE_ADDR                 (0x0128)

/* REG£ºVideo Blanking Register1
   Name:  P0_VID_BLANK1_ADDR */
#define P0_VID_BLANK1_ADDR               (0x12C)

/* REG£ºVideo Blanking Register2
   Name:  P0_VID_BLANK2_ADDR */
#define P0_VID_BLANK2_ADDR               (0x130)

/* REG£ºVideo Blanking Register3
   Name:  P0_VID_BLANK3_ADDR */
#define P0_VID_BLANK3_ADDR               (0x134)

/* REG£ºDeep Color Header Register
   Name:  P0_DC_HEADER_ADDR */
#define P0_DC_HEADER_ADDR                (0x138)

/* REG£ºVideo Mode2 Register
   Name:  P0_VID_DITHER_ADDR */
#define P0_VID_DITHER_ADDR               (0x13C)

/* REG£ºRGB_2_xvYCC control Register
   Name:  P0_RGB2XVYCC_CT_ADDR */
#define P0_RGB2XVYCC_CT_ADDR             (0x140)

/* REG£ºRGB_2_xvYCC Conversion R_2_Y Register1
   Name:  P0_R2Y_COEFF_LOW_ADDR */
#define P0_R2Y_COEFF_LOW_ADDR            (0x144)

/* REG£ºRGB_2_xvYCC Conversion R_2_Y Register2
   Name:  P0_R2Y_COEFF_UP_ADDR */
#define P0_R2Y_COEFF_UP_ADDR             (0x148)

/* REG£ºRGB_2_xvYCC Conversion G_2_Y Register1
   Name:  P0_G2Y_COEFF_LOW_ADDR */
#define P0_G2Y_COEFF_LOW_ADDR            (0x14C)

/* REG£ºRGB_2_xvYCC Conversion G_2_Y Register2
   Name:  P0_G2Y_COEFF_UP_ADDR */
#define P0_G2Y_COEFF_UP_ADDR             (0x150)

/* REG£ºRGB_2_xvYCC Conversion B_2_Y Register1
   Name:  P0_B2Y_COEFF_LOW_ADDR */
#define P0_B2Y_COEFF_LOW_ADDR            (0x154)

/* REG£ºRGB_2_xvYCC Conversion B_2_Y Register2
   Name:  P0_B2Y_COEFF_UP_ADDR */
#define P0_B2Y_COEFF_UP_ADDR             (0x158)

/* REG£ºRGB_2_xvYCC Conversion R_2_Cb Register1
   Name:  P0_R2CB_COEFF_LOW_ADDR */
#define P0_R2CB_COEFF_LOW_ADDR           (0x15C)

/* REG£ºRGB_2_xvYCC Conversion R_2_Cb Register2
   Name:  P0_R2CB_COEFF_UP_ADDR */
#define P0_R2CB_COEFF_UP_ADDR            (0x160)

/* REG£ºRGB_2_xvYCC Conversion G_2_Cb Register1
   Name:  P0_G2CB_COEFF_LOW_ADDR */
#define P0_G2CB_COEFF_LOW_ADDR           (0x164)

/* REG£ºRGB_2_xvYCC Conversion G_2_Cb Register2
   Name:  P0_G2CB_COEFF_UP_ADDR */
#define P0_G2CB_COEFF_UP_ADDR            (0x168)

/* REG£ºRGB_2_xvYCC Conversion B_2_Cb Register1
   Name:  P0_B2CB_COEFF_LOW_ADDR */
#define P0_B2CB_COEFF_LOW_ADDR           (0x16C)

/* REG£ºRGB_2_xvYCC Conversion B_2_Cb Register2
   Name:  P0_B2CB_COEFF_UP_ADDR */
#define P0_B2CB_COEFF_UP_ADDR            (0x170)

/* REG£ºRGB_2_xvYCC Conversion R_2_Cr Register1
   Name:  P0_R2CR_COEFF_LOW_ADDR */
#define P0_R2CR_COEFF_LOW_ADDR           (0x174)

/* REG£ºRGB_2_xvYCC Conversion R_2_Cr Register2
   Name:  P0_R2CR_COEFF_UP_ADDR */
#define P0_R2CR_COEFF_UP_ADDR            (0x178)

/* REG£ºRGB_2_xvYCC Conversion G_2_Cr Register1
   Name:  P0_G2CR_COEFF_LOW_ADDR */
#define P0_G2CR_COEFF_LOW_ADDR           (0x17C)

/* REG£ºRGB_2_xvYCC Conversion G_2_Cr Register2
   Name:  P0_G2CR_COEFF_UP_ADDR */
#define P0_G2CR_COEFF_UP_ADDR            (0x180)

/* REG£ºRGB_2_xvYCC Conversion B_2_Cr Register1
   Name:  P0_B2CR_COEFF_LOW_ADDR */
#define P0_B2CR_COEFF_LOW_ADDR           (0x184)

/* REG£ºRGB_2_xvYCC Conversion B_2_Cr Register2
   Name:  P0_B2CR_COEFF_UP_ADDR */
#define P0_B2CR_COEFF_UP_ADDR            (0x188)

/* REG£ºRGB_2_xvYCC RGB Input Offset Register1
   Name:  P0_RGB_OFFSET_LOW_ADDR */
#define P0_RGB_OFFSET_LOW_ADDR           (0x18C)

/* REG£ºRGB_2_xvYCC RGB Input Offset Register2
   Name:  P0_RGB_OFFSET_UP_ADDR */
#define P0_RGB_OFFSET_UP_ADDR            (0x190)

/* REG£ºRGB_2_xvYCC Conversion Y Output Offset Register1
   Name:  P0_Y_OFFSET_LOW_ADDR */
#define P0_Y_OFFSET_LOW_ADDR             (0x194)

/* REG£ºRGB_2_xvYCC Conversion Y Output Offset Register2
   Name:  P0_Y_OFFSET_UP_ADDR */
#define P0_Y_OFFSET_UP_ADDR              (0x198)

/* REG£ºRGB_2_xvYCC Conversion CbCr Output Offset Register1
   Name:  P0_CBCR_OFFSET_LOW_ADDR */
#define P0_CBCR_OFFSET_LOW_ADDR          (0x19C)

/* REG£ºRGB_2_xvYCC Conversion CbCr Output Offset Register2
   Name:  P0_CBCR_OFFSET_UP_ADDR */
#define P0_CBCR_OFFSET_UP_ADDR           (0x1A0)

/* REG£ºVideo Input Mode
   Name:  P0_VID_IN_MODE_ADDR */
#define P0_VID_IN_MODE_ADDR              (0x1A4)

/* REG£ºInterrupt State Register
   Name:  P0_INTR_STATE_ADDR */
#define P0_INTR_STATE_ADDR               (0x1C0)

/* REG£ºInterrupt Source Register1
   Name:  P0_INTR1_ADDR */
#define P0_INTR1_ADDR                    (0x1C4)

/* REG£ºInterrupt Source Register2
   Name:  P0_INTR2_ADDR */
#define P0_INTR2_ADDR                    (0x1C8)

/* REG£ºInterrupt Source Register3
   Name:  P0_INTR3_ADDR */
#define P0_INTR3_ADDR                    (0x1CC)

/* REG£ºInterrupt Source Register4
   Name:  P0_INTR4_ADDR */
#define P0_INTR4_ADDR                    (0x1D0)

/* REG£ºInterrupt Source Register5
   Name:  P0_INTR5_ADDR */
#define P0_INTR5_ADDR                    (0x1D4)

/* REG£ºInterrupt Unmask Register1
   Name:  P0_INT_UNMASK1_ADDR */
#define P0_INT_UNMASK1_ADDR              (0x1D8)

/* REG£ºInterrupt Unmask Register2
   Name:  P0_INT_UNMASK2_ADDR */
#define P0_INT_UNMASK2_ADDR              (0x1DC)

/* REG£ºInterrupt Unmask Register3
   Name:  P0_INT_UNMASK3_ADDR */
#define P0_INT_UNMASK3_ADDR              (0x1E0)

/* REG£ºInterrupt Unmask Register4
   Name:  P0_INT_UNMASK4_ADDR */
#define P0_INT_UNMASK4_ADDR              (0x1E4)

/* REG£ºInterrupt Unmask Register5
   Name:  P0_INT_UNMASK5_ADDR */
#define P0_INT_UNMASK5_ADDR              (0x1E8)

/* REG£ºInterrupt Control Register
   Name:  P0_INT_CTRL_ADDR */
#define P0_INT_CTRL_ADDR                 (0x1EC)

/* REG£ºHot Plug Control debouncing timer 2 Register
   Name:  P0_HTPLG_T2_ADDR */
#define P0_HTPLG_T2_ADDR                 (0x1F0)

/* REG£ºHot Plug Control debouncing timer 1 Register
   Name:  P0_HTPLG_T1_ADDR */
#define P0_HTPLG_T1_ADDR                 (0x1F4)

/* REG£ºTMDS Register
   Name:  P0_TMDS_CCTRL_ADDR */
#define P0_TMDS_CCTRL_ADDR               (0x200)

/* REG£ºxvYCC_2_RGB Control Register
   Name:  P0_XVYCC2RGB_CTL_ADDR */
#define P0_XVYCC2RGB_CTL_ADDR            (0x240)

/* REG£ºxvYCC_2_RGB Conversion Y_2_R Register1
   Name:  P0_Y2R_COEFF_LOW_ADDR */
#define P0_Y2R_COEFF_LOW_ADDR            (0x244)

/* REG£ºxvYCC_2_RGB Conversion Y_2_R Register2
   Name:  P0_Y2R_COEFF_UP_ADDR */
#define P0_Y2R_COEFF_UP_ADDR             (0x248)

/* REG£ºxvYCC_2_RGB Conversion Cr_2_R Register1
   Name:  P0_CR2R_COEFF_LOW_ADDR */
#define P0_CR2R_COEFF_LOW_ADDR           (0x24C)

/* REG£ºxvYCC_2_RGB Conversion Cr_2_R Register2
   Name:  P0_CR2R_COEFF_UP_ADDR */
#define P0_CR2R_COEFF_UP_ADDR            (0x250)

/* REG£ºxvYCC_2_RGB Conversion Cb_2_B Register1
   Name:  P0_CB2B_COEFF_LOW_ADDR */
#define P0_CB2B_COEFF_LOW_ADDR           (0x254)

/* REG£ºxvYCC_2_RGB Conversion Cb_2_B Register2
   Name:  P0_CB2B_COEFF_UP_ADDR */
#define P0_CB2B_COEFF_UP_ADDR            (0x258)

/* REG£ºxvYCC_2_RGB Conversion Cr_2_G Register1
   Name:  P0_CR2G_COEFF_LOW_ADDR */
#define P0_CR2G_COEFF_LOW_ADDR           (0x25C)

/* REG£ºxvYCC_2_RGB Conversion Cr_2_G Register2
   Name:  P0_CR2G_COEFF_UP_ADDR */
#define P0_CR2G_COEFF_UP_ADDR            (0x260)

/* REG£ºxvYCC_2_RGB Conversion Cb_2_G Register1
   Name:  P0_CB2G_COEFF_LOW_ADDR */
#define P0_CB2G_COEFF_LOW_ADDR           (0x264)

/* REG£ºxvYCC_2_RGB Conversion Cb_2_G Register2
   Name:  P0_CB2G_COEFF_UP_ADDR */
#define P0_CB2G_COEFF_UP_ADDR            (0x268)

/* REG£ºxvYCC_2_RGB Conversion Y Offset Register1
   Name:  P0_YOFFSET1_LOW_ADDR */
#define P0_YOFFSET1_LOW_ADDR             (0x26C)

/* REG£ºxvYCC_2_RGB Conversion Y Offset Register2
   Name:  P0_YOFFSET1_UP_ADDR */
#define P0_YOFFSET1_UP_ADDR              (0x270)

/* REG£ºxvYCC_2_RGB Conversion Offset1 Register1
   Name:  P0_OFFSET1_LOW_ADDR */
#define P0_OFFSET1_LOW_ADDR              (0x274)

/* REG£ºxvYCC_2_RGB Conversion Offset1 Register2
   Name:  P0_OFFSET1_MID_ADDR */
#define P0_OFFSET1_MID_ADDR              (0x278)

/* REG£ºxvYCC_2_RGB Conversion Offset1 Register3
   Name:  P0_OFFSET1_UP_ADDR */
#define P0_OFFSET1_UP_ADDR               (0x27C)

/* REG£ºxvYCC_2_RGB Conversion Offset2 Register1
   Name:  P0_OFFSET2_LOW_ADDR */
#define P0_OFFSET2_LOW_ADDR              (0x280)

/* REG£ºxvYCC_2_RGB Conversion Offset2 Register2
   Name:  P0_OFFSET2_UP_ADDR */
#define P0_OFFSET2_UP_ADDR               (0x284)

/* REG£ºxvYCC_2_RGB Conversion DC Level Register1
   Name:  P0_DC_LEVEL_LOW_ADDR */
#define P0_DC_LEVEL_LOW_ADDR             (0x288)

/* REG£ºxvYCC_2_RGB Conversion DC Level Register2
   Name:  P0_DC_LEVEL_UP_ADDR */
#define P0_DC_LEVEL_UP_ADDR              (0x28C)

/* REG£ºTpi or Page Mode Register
   Name:  P0_LM_DDC_ADDR */
#define P0_LM_DDC_ADDR                  (0x31C)

/* REG£ºHDCP Repeater Control Register
   Name:  P0_TXSHA_CTRL_ADDR */
#define P0_TXSHA_CTRL_ADDR               (0x330)

/* REG£ºHDCP SHA Repeater KSV FIFO Register
   Name:  P0_TXKSV_FIFO_ADDR */
#define P0_TXKSV_FIFO_ADDR               (0x334)

/* REG£ºHDCP Repeater Down Stream BSTATUS Register #1
   Name:  P0_TXDS_BSTATUS1_ADDR */
#define P0_TXDS_BSTATUS1_ADDR            (0x338)

/* REG£ºHDCP Repeater Down Stream BSTATUS Register #2
   Name:  P0_TXDS_BSTATUS2_ADDR */
#define P0_TXDS_BSTATUS2_ADDR            (0x33C)

/* REG£ºHDCP SHA Repeater V.H0 Register #0
   Name:  P0_TXVH0_0_ADDR */
#define P0_TXVH0_0_ADDR                  (0x360)

/* REG£ºHDCP SHA Repeater V.H0 Register #1
   Name:  P0_TXVH0_1_ADDR */
#define P0_TXVH0_1_ADDR                  (0x364)

/* REG£ºHDCP SHA Repeater V.H0 Register #2
   Name:  P0_TXVH0_2_ADDR */
#define P0_TXVH0_2_ADDR                  (0x368)

/* REG£ºHDCP SHA Repeater V.H0 Register #3
   Name:  P0_TXVH0_3_ADDR */
#define P0_TXVH0_3_ADDR                  (0x36C)

/* REG£ºHDCP SHA Repeater V.H1 Register #0
   Name:  P0_TXVH1_0_ADDR */
#define P0_TXVH1_0_ADDR                  (0x370)

/* REG£ºHDCP SHA Repeater V.H1 Register #1
   Name:  P0_TXVH1_1_ADDR */
#define P0_TXVH1_1_ADDR                  (0x374)

/* REG£ºHDCP SHA Repeater V.H1 Register #2
   Name:  P0_TXVH1_2_ADDR */
#define P0_TXVH1_2_ADDR                  (0x378)

/* REG£ºHDCP SHA Repeater V.H1 Register #3
   Name:  P0_TXVH1_3_ADDR */
#define P0_TXVH1_3_ADDR                  (0x37C)

/* REG£ºHDCP SHA Repeater V.H2 Register #0
   Name:  P0_TXVH2_0_ADDR */
#define P0_TXVH2_0_ADDR                  (0x380)

/* REG£ºHDCP SHA Repeater V.H2 Register #1
   Name:  P0_TXVH2_1_ADDR */
#define P0_TXVH2_1_ADDR                  (0x384)

/* REG£ºHDCP SHA Repeater V.H2 Register #2
   Name:  P0_TXVH2_2_ADDR */
#define P0_TXVH2_2_ADDR                  (0x388)

/* REG£ºHDCP SHA Repeater V.H2 Register #3
   Name:  P0_TXVH2_3_ADDR */
#define P0_TXVH2_3_ADDR                  (0x38C)

/* REG£ºHDCP SHA Repeater V.H3 Register #0
   Name:  P0_TXVH3_0_ADDR */
#define P0_TXVH3_0_ADDR                  (0x390)

/* REG£ºHDCP SHA Repeater V.H3 Register #1
   Name:  P0_TXVH3_1_ADDR */
#define P0_TXVH3_1_ADDR                  (0x394)

/* REG£ºHDCP SHA Repeater V.H3 Register #2
   Name:  P0_TXVH3_2_ADDR */
#define P0_TXVH3_2_ADDR                  (0x398)

/* REG£ºHDCP SHA Repeater V.H3 Register #3
   Name:  P0_TXVH3_3_ADDR */
#define P0_TXVH3_3_ADDR                  (0x39C)

/* REG£ºHDCP SHA Repeater V.H4 Register #0
   Name:  P0_TXVH4_0_ADDR */
#define P0_TXVH4_0_ADDR                  (0x3A0)

/* REG£ºHDCP SHA Repeater V.H4 Register #1
   Name:  P0_TXVH4_1_ADDR */
#define P0_TXVH4_1_ADDR                  (0x3A4)

/* REG£ºHDCP SHA Repeater V.H4 Register #2
   Name:  P0_TXVH4_2_ADDR */
#define P0_TXVH4_2_ADDR                  (0x3A8)

/* REG£ºHDCP SHA Repeater V.H4 Register #3
   Name:  P0_TXVH4_3_ADDR */
#define P0_TXVH4_3_ADDR                  (0x3AC)

/* REG£ºDDC I2C Manual Register
   Name:  P0_DDC_MAN_ADDR */
#define P0_DDC_MAN_ADDR                  (0x3B0)

/* REG£ºDDC I2C Target Slave Address Register
   Name:  P0_DDC_ADDR_ADDR */
#define P0_DDC_ADDR_ADDR                 (0x3B4)

/* REG£ºDDC I2C Target Segment Address Register
   Name:  P0_DDC_SEGM_ADDR */
#define P0_DDC_SEGM_ADDR                 (0x3B8)

/* REG£ºDDC I2C Target Offset Address Register
   Name:  P0_DDC_OFFSET_ADDR */
#define P0_DDC_OFFSET_ADDR               (0x3BC)

/* REG£ºDDC I2C Data Count Register1
   Name:  P0_DDC_COUNT1_ADDR */
#define P0_DDC_COUNT1_ADDR               (0x3C0)

/* REG£ºDDC I2C Data Count Register2
   Name:  P0_DDC_COUNT2_ADDR */
#define P0_DDC_COUNT2_ADDR               (0x3C4)

/* REG£ºDDC I2C Status Register
   Name:  P0_DDC_STATUS_ADDR */
#define P0_DDC_STATUS_ADDR               (0x3C8)

/* REG£ºDDC I2C Command Register
   Name:  P0_DDC_CMD_ADDR */
#define P0_DDC_CMD_ADDR                  (0x3CC)

/* REG£ºDDC I2C Data Register
   Name:  P0_DDC_DATA_ADDR */
#define P0_DDC_DATA_ADDR                 (0x3D0)

/* REG£ºDDC I2C FIFO Count Register
   Name:  P0_DDC_FIFOCNT_ADDR */
#define P0_DDC_FIFOCNT_ADDR              (0x3D4)

/* REG£ºDDC Delay Count Register
   Name:  P0_DDC_DELAY_CNT_ADDR */
#define P0_DDC_DELAY_CNT_ADDR            (0x3D8)

/* REG£ºDDC Min IDLE Time Register
   Name:  P0_DDC_MIN_IDLE_ADDR */
#define P0_DDC_MIN_IDLE_ADDR             (0x3DC)

/* REG£ºDDC STALL Time Register
   Name:  P0_DDC_STALL_IDLE_ADDR */
#define P0_DDC_STALL_IDLE_ADDR           (0x3E0)

/* REG£ºROM Status Register
   Name:  P0_EPST_ADDR */
#define P0_EPST_ADDR                     (0x3E4)

/* REG£ºROM Command Register
   Name:  P0_EPCM_ADDR */
#define P0_EPCM_ADDR                     (0x3E8)

/* REG£ºOTP Clock Divide Register
   Name:  P0_OTP_CLK_ADDR */
#define P0_OTP_CLK_ADDR                  (0x3EC)

/* REG£º
   Name:  PO_REG_BANK0_ADDR */
#define PO_REG_BANK0_ADDR                (0x3FC)

/* REG£ºACR Control Register
   Name:  P1_ACR_CTRL_ADDR */
#define P1_ACR_CTRL_ADDR                 (0x004)

/* REG£ºACR Audio Frequency Register
   Name:  P1_FREQ_SVAL_ADDR */
#define P1_FREQ_SVAL_ADDR                (0x008)

/* REG£ºACR N Software Value Register1
   Name:  P1_N_SVAL1_ADDR */
#define P1_N_SVAL1_ADDR                  (0x00C)

/* REG£ºACR N Software Value Register2
   Name:  P1_N_SVAL2_ADDR */
#define P1_N_SVAL2_ADDR                  (0x010)

/* REG£ºACR N Software Value Register3
   Name:  P1_N_SVAL3_ADDR */
#define P1_N_SVAL3_ADDR                  (0x014)

/* REG£ºACR CTS Software Value Register1
   Name:  P1_CTS_SVAL1_ADDR */
#define P1_CTS_SVAL1_ADDR                (0x018)

/* REG£ºACR CTS Software Value Register2
   Name:  P1_CTS_SVAL2_ADDR */
#define P1_CTS_SVAL2_ADDR                (0x01C)

/* REG£ºACR CTS Software Value Register3
   Name:  P1_CTS_SVAL3_ADDR */
#define P1_CTS_SVAL3_ADDR                (0x020)

/* REG£ºACR CTS Hardware Value Register1
   Name:  P1_CTS_HVAL1_ADDR */
#define P1_CTS_HVAL1_ADDR                (0x024)

/* REG£ºACR CTS Hardware Value Register2
   Name:  P1_CTS_HVAL2_ADDR */
#define P1_CTS_HVAL2_ADDR                (0x028)

/* REG£ºACR CTS Hardware Value Register3
   Name:  P1_CTS_HVAL3_ADDR */
#define P1_CTS_HVAL3_ADDR                (0x02C)

/* REG£ºDSD INTERLEAVE Register
   Name:  P1_DSD_INTERLEAVE_ADDR */
#define P1_DSD_INTERLEAVE_ADDR           (0x030)

/* REG£ºAUDIO MODE SEL Register
   Name:  P1_AUDIO_PAR_MODE_SEL_ADDR */
#define P1_AUDIO_PAR_MODE_SEL_ADDR       (0x034)

/* REG£ºAudio In Mode Register
   Name:  P1_AUD_MODE_ADDR */
#define P1_AUD_MODE_ADDR                 (0x050)

/* REG£ºAudio In S/PDIF Control Register
   Name:  P1_SPDIF_CTRL_ADDR */
#define P1_SPDIF_CTRL_ADDR               (0x054)

/* REG£ºAUDIO IN SPDIF SOFTWARE 1UI OVERWRITE Register
   Name:  P1_SPDIF_SSMPL_ADDR */
#define P1_SPDIF_SSMPL_ADDR              (0x058)

/* REG£ºAudio In SPDIF Software 2UI Overwrite Register
   Name:  P1_SPDIF_SSMPL2_ADDR */
#define P1_SPDIF_SSMPL2_ADDR             (0x064)

/* REG£ºAUDIO IN SPDIF HARDWARE 1UI OVERWRITE Register
   Name:  P1_SPDIF_HSMPL_ADDR */
#define P1_SPDIF_HSMPL_ADDR              (0x05C)

/* REG£ºAUDIO IN SPDIF HARDWARE 2UI OVERWRITE Register
   Name:  P1_SPDIF_HSMPL2_ADDR */
#define P1_SPDIF_HSMPL2_ADDR             (0x068)

/* REG£ºAudio In S/PDIF Extracted Fs and Length Register
   Name:  P1_SPDIF_FS_ADDR */
#define P1_SPDIF_FS_ADDR                 (0x060)

/* REG£ºAudio In I2S Channel Swap Register
   Name:  P1_SWAP_I2S_ADDR */
#define P1_SWAP_I2S_ADDR                 (0x064)

/* REG£ºAudio Error Threshold Register
   Name:  P1_SPDIF_ERTH_ADDR */
#define P1_SPDIF_ERTH_ADDR               (0x06C)

/* REG£ºAudio In I2S Data In Map Register
   Name:  P1_I2S_IN_MAP_ADDR */
#define P1_I2S_IN_MAP_ADDR               (0x070)

/* REG£ºAudio In I2S Control Register
   Name:  P1_I2S_IN_CTRL_ADDR */
#define P1_I2S_IN_CTRL_ADDR              (0x074)

/* REG£ºAudio In I2S Channel Status Register0
   Name:  P1_I2S_CHST0_ADDR */
#define P1_I2S_CHST0_ADDR                (0x078)

/* REG£ºAudio In I2S Channel Status Register1
   Name:  P1_I2S_CHST1_ADDR */
#define P1_I2S_CHST1_ADDR                (0x07C)

/* REG£ºAudio In I2S Channel Status Register2
   Name:  P1_I2S_CHST2_ADDR */
#define P1_I2S_CHST2_ADDR                (0x080)

/* REG£ºAudio In I2S Channel Status Register4
   Name:  P1_I2S_CHST4_ADDR */
#define P1_I2S_CHST4_ADDR                (0x084)

/* REG£ºAudio In I2S Channel Status Register5
   Name:  P1_I2S_CHST5_ADDR */
#define P1_I2S_CHST5_ADDR                (0x088)

/* REG£ºAudio Sample Rate Conversion Register
   Name:  P1_ASRC_ADDR */
#define P1_ASRC_ADDR                     (0x08C)

/* REG£ºAudio I2S Input Length Register
   Name:  P1_I2S_IN_LEN_ADDR */
#define P1_I2S_IN_LEN_ADDR               (0x090)

/* REG£ºAudio Parallel Bus Clock Register1
   Name:  P1_AUD_PAR_BUSCLK_1_ADDR */
#define P1_AUD_PAR_BUSCLK_1_ADDR         (0x094)

/* REG£ºAudio Parallel Bus Clock Register2
   Name:  P1_AUD_PAR_BUSCLK_2_ADDR */
#define P1_AUD_PAR_BUSCLK_2_ADDR         (0x098)

/* REG£ºAudio Parallel Bus Clock Register3
   Name:  P1_AUD_PAR_BUSCLK_3_ADDR */
#define P1_AUD_PAR_BUSCLK_3_ADDR         (0x09C)

/* REG£ºAudio Path Control Register
   Name:  P1_AUDP_TXCTRL_ADDR */
#define P1_AUDP_TXCTRL_ADDR              (0x0BC)

/* REG£ºAudio Path Status Register
   Name:  P1_AUDO_TXSTAT_ADDR */
#define P1_AUDO_TXSTAT_ADDR              (0x0C0)

/* REG£ºAudio PATH Tx FIFO Read Write Ptr Difference Register
   Name:  P1_AUDO_TXFIFO_ADDR */
#define P1_AUDO_TXFIFO_ADDR              (0x0C4)

/* REG£ºPhase Look Up Table Register
   Name:  P1_PP_TABLE_ADDR */
#define P1_PP_TABLE_ADDR                 (0x0C8)

/* REG£ºBIST Test Status Register
   Name:  P1_TEST_STAT_ADDR */
#define P1_TEST_STAT_ADDR                (0x0EC)

/* REG£ºTest Control Register
   Name:  P1_TEST_TXCTRL_ADDR */
#define P1_TEST_TXCTRL_ADDR              (0x0F0)

/* REG£ºDiagnostic Power Down Register
   Name:  P1_DPD_ADDR */
#define P1_DPD_ADDR                      (0x0F4)

/* REG£ºPacket Buffer Control #1 Register
   Name:  P1_INF_CTRL1_ADDR */
#define P1_INF_CTRL1_ADDR                (0x0F8)

/* REG£ºPacket Buffer Control #2 Register
   Name:  P1_INF_CTRL2_ADDR */
#define P1_INF_CTRL2_ADDR                (0x0FC)

/* REG£ºAVI InfoFrame Type Code
   Name:  P1_AVI_TYPE_ADDR */
#define P1_AVI_TYPE_ADDR                 (0x100)

/* REG£ºAVI InfoFrame Versin Code
   Name:  P1_AVI_VERS_ADDR */
#define P1_AVI_VERS_ADDR                 (0x104)

/* REG£ºAVI InfoFrame Length
   Name:  P1_AVI_LEN_ADDR */
#define P1_AVI_LEN_ADDR                  (0x108)

/* REG£ºAVI InfoFrame Checksum
   Name:  P1_AVI_CHSUM_ADDR */
#define P1_AVI_CHSUM_ADDR                (0x10C)

/* REG£ºAVI InfoFrame Data
   Name:  P1_AVI_DBYTE_ADDR */
#define P1_AVI_DBYTE_ADDR                (0x110)

/* REG£ºSPD InfoFrame Type Code
   Name:  P1_SPD_TYPE_ADDR */
#define P1_SPD_TYPE_ADDR                 (0x180)

/* REG£ºSPD InfoFrame Versin Code
   Name:  P1_SPD_VERS_ADDR */
#define P1_SPD_VERS_ADDR                 (0x184)

/* REG£ºSPD InfoFrame Length
   Name:  P1_SPD_LEN_ADDR */
#define P1_SPD_LEN_ADDR                  (0x188)

/* REG£ºSPD InfoFrame Checksum
   Name:  P1_SPD_CHSUM_ADDR */
#define P1_SPD_CHSUM_ADDR                (0x18C)

/* REG£ºSPD InfoFrame Data
   Name:  P1_SPD_DBYTE_ADDR */
#define P1_SPD_DBYTE_ADDR                (0x190)

/* REG£ºAUDIO InfoFrame Type Code
   Name:  P1_AUDIO_TYPE_ADDR */
#define P1_AUDIO_TYPE_ADDR               (0x200)

/* REG£ºAUDIO InfoFrame Versin Code
   Name:  P1_AUDIO_VERS_ADDR */
#define P1_AUDIO_VERS_ADDR               (0x204)

/* REG£ºAUDIO InfoFrame Length
   Name:  P1_AUDIO_LEN_ADDR */
#define P1_AUDIO_LEN_ADDR                (0x208)

/* REG£ºAUDIO InfoFrame Checksum
   Name:  P1_AUDIO_CHSUM_ADDR */
#define P1_AUDIO_CHSUM_ADDR              (0x20C)

/* REG£ºAUDIO InfoFrame Data
   Name:  P1_AUDIO_DBYTE_ADDR */
#define P1_AUDIO_DBYTE_ADDR              (0x210)

/* REG£ºMPEG InfoFrame Type Code
   Name:  P1_MPEG_TYPE_ADDR */
#define P1_MPEG_TYPE_ADDR                (0x280)

/* REG£ºMPEG InfoFrame Versin Code
   Name:  P1_MPEG_VERS_ADDR */
#define P1_MPEG_VERS_ADDR                (0x284)

/* REG£ºMPEG InfoFrame Length
   Name:  P1_MPEG_LEN_ADDR */
#define P1_MPEG_LEN_ADDR                 (0x288)

/* REG£ºMPEG InfoFrame Checksum
   Name:  P1_MPEG_CHSUM_ADDR */
#define P1_MPEG_CHSUM_ADDR               (0x28C)

/* REG£ºMPEG InfoFrame Data
   Name:  P1_MPEG_DBYTE_ADDR */
#define P1_MPEG_DBYTE_ADDR               (0x290)

/* REG£ºGeneric Packet #1 Registers
   Name:  P1_GEN_DBYTE_ADDR */
#define P1_GEN_DBYTE_ADDR                (0x300)

/* REG£ºGeneral Control Packet Register
   Name:  P1_CP_BYTE1_ADDR */
#define P1_CP_BYTE1_ADDR                 (0x37C)

/* REG£ºGeneric Packet #2 Registers
   Name:  P1_GEN2_DBYTE_ADDR */
#define P1_GEN2_DBYTE_ADDR               (0x380)

/* REG£ºDiscovery Control Register 1
   Name:  P2_DISC_CTRL1_ADDR */
#define P2_DISC_CTRL1_ADDR               (0x100)

/* REG£ºDiscovery Control Register 2
   Name:  P2_DISC_CTRL2_ADDR */
#define P2_DISC_CTRL2_ADDR               (0x104)

/* REG£ºDiscovery Control Register 3
   Name:  P2_DISC_CTRL3_ADDR */
#define P2_DISC_CTRL3_ADDR               (0x108)

/* REG£ºDiscovery Control Register 4
   Name:  P2_DISC_CTRL4_ADDR */
#define P2_DISC_CTRL4_ADDR               (0x10C)

/* REG£ºDiscovery Control Register 5
   Name:  P2_DISC_CTRL5_ADDR */
#define P2_DISC_CTRL5_ADDR               (0x110)

/* REG£ºDiscovery Control Register 6
   Name:  P2_DISC_CTRL6_ADDR */
#define P2_DISC_CTRL6_ADDR               (0x114)

/* REG£ºDiscovery Control Register 7
   Name:  P2_DISC_CTRL7_ADDR */
#define P2_DISC_CTRL7_ADDR               (0x118)

/* REG£ºDiscovery Control Register 8
   Name:  P2_DISC_CTRL8_ADDR */
#define P2_DISC_CTRL8_ADDR               (0x11C)

/* REG£ºDiscovery Control Register 8
   Name:  P2_DISC_CTRL9_ADDR */
#define P2_DISC_CTRL9_ADDR               (0x120)

/* REG£ºDiscovery Status Register 2
   Name:  P2_DISC_STAT2_ADDR */
#define P2_DISC_STAT2_ADDR               (0x130)

/* REG£ºInterrupt Source Register 4
   Name:  P2_INTR4_ADDR */
#define P2_INTR4_ADDR                    (0x144)

/* REG£ºInterrupt Mask Register 4
   Name:  P2_INTR4_MASK_ADDR */
#define P2_INTR4_MASK_ADDR               (0x148)

/* REG£ºInterrupt Source Register 5
   Name:  P2_INTR5_ADDR */
#define P2_INTR5_ADDR                    (0x14C)

/* REG£ºInterrupt Mask Register 5
   Name:  P2_INTR5_MASK_ADDR */
#define P2_INTR5_MASK_ADDR               (0x150)

/* REG£ºMHL Transmitter Control Register 1
   Name:  P2_MHLTX_CTL1_ADDR */
#define P2_MHLTX_CTL1_ADDR               (0x180)

/* REG£ºMHL Transmitter Control Register 2
   Name:  P2_MHLTX_CTL2_ADDR */
#define P2_MHLTX_CTL2_ADDR               (0x184)

/* REG£ºMHL Transmitter Control Register 4
   Name:  P2_MHLTX_CTL4_ADDR */
#define P2_MHLTX_CTL4_ADDR               (0x18C)

/* REG£ºMHL Transmitter Control Register 6
   Name:  P2_MHLTX_CTL6_ADDR */
#define P2_MHLTX_CTL6_ADDR               (0x194)

/* REG£ºMHL Transmitter Control Register 7
   Name:  P2_MHLTX_CTL7_ADDR */
#define P2_MHLTX_CTL7_ADDR               (0x198)

/* REG£ºMHL Transmitter Control Register 8
   Name:  P2_MHLTX_CTL8_ADDR */
#define P2_MHLTX_CTL8_ADDR               (0x19C)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_PCLK_LSB_ADDR */
#define TPI_VIDEO_PCLK_LSB_ADDR          (0x000)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_PCLK_MSB_ADDR */
#define TPI_VIDEO_PCLK_MSB_ADDR          (0x004)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_VF_LSB_ADDR */
#define TPI_VIDEO_VF_LSB_ADDR            (0x008)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_VF_MSB_ADDR */
#define TPI_VIDEO_VF_MSB_ADDR            (0x00C)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_TPL_LSB_ADDR */
#define TPI_VIDEO_TPL_LSB_ADDR           (0x010)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_TPL_MSB_ADDR */
#define TPI_VIDEO_TPL_MSB_ADDR           (0x014)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_TL_LSB_ADDR */
#define TPI_VIDEO_TL_LSB_ADDR            (0x018)

/* REG£ºTPI Video Mode Data
   Name:  TPI_VIDEO_TL_MSB_ADDR */
#define TPI_VIDEO_TL_MSB_ADDR            (0x01C)

/* REG£ºTPI Input bus and Pixel Repetition Data
   Name:  TPI_INPUTBUS_FMT_ADDR */
#define TPI_INPUTBUS_FMT_ADDR            (0x020)

/* REG£ºTPI Input format data
   Name:  TPI_INPUT_FMT_ADDR */
#define TPI_INPUT_FMT_ADDR               (0x024)

/* REG£ºTPI Output format data
   Name:  TPI_OUTPUT_FMT_ADDR */
#define TPI_OUTPUT_FMT_ADDR              (0x028)

/* REG£ºTPI YC Input Mode Select
   Name:  TPI_YC_MODE_ADDR */
#define TPI_YC_MODE_ADDR                 (0x02C)

/* REG£ºTPI AVI InfoFrame Date #0
   Name:  TPI_AVI_DBYTE_ADDR */
#define TPI_AVI_DBYTE_ADDR               (0x030)

/* REG£ºTPI AVI InfoFrame Date #1
   Name:  TPI_AVI_DBYTE_1_ADDR */
#define TPI_AVI_DBYTE_1_ADDR             (0x034)

/* REG£ºTPI AVI InfoFrame Date #2
   Name:  TPI_AVI_DBYTE_2_ADDR */
#define TPI_AVI_DBYTE_2_ADDR             (0x038)

/* REG£ºTPI AVI InfoFrame Date #3
   Name:  TPI_AVI_DBYTE_3_ADDR */
#define TPI_AVI_DBYTE_3_ADDR             (0x03C)

/* REG£ºTPI AVI InfoFrame Date #4
   Name:  TPI_AVI_DBYTE_4_ADDR */
#define TPI_AVI_DBYTE_4_ADDR             (0x040)

/* REG£ºTPI AVI InfoFrame Date #5
   Name:  TPI_AVI_DBYTE_5_ADDR */
#define TPI_AVI_DBYTE_5_ADDR             (0x044)

/* REG£ºTPI AVI InfoFrame Date #6
   Name:  TPI_AVI_DBYTE_6_ADDR */
#define TPI_AVI_DBYTE_6_ADDR             (0x048)

/* REG£ºTPI AVI InfoFrame Date #7
   Name:  TPI_AVI_DBYTE_7_ADDR */
#define TPI_AVI_DBYTE_7_ADDR             (0x04C)

/* REG£ºTPI AVI InfoFrame Date #8
   Name:  TPI_AVI_DBYTE_8_ADDR */
#define TPI_AVI_DBYTE_8_ADDR             (0x050)

/* REG£ºTPI AVI InfoFrame Date #9
   Name:  TPI_AVI_DBYTE_9_ADDR */
#define TPI_AVI_DBYTE_9_ADDR             (0x054)

/* REG£ºTPI AVI InfoFrame Date #10
   Name:  TPI_AVI_DBYTE_10_ADDR */
#define TPI_AVI_DBYTE_10_ADDR            (0x058)

/* REG£ºTPI AVI InfoFrame Date #11
   Name:  TPI_AVI_DBYTE_11_ADDR */
#define TPI_AVI_DBYTE_11_ADDR            (0x05C)

/* REG£ºTPI AVI InfoFrame Date #12
   Name:  TPI_AVI_DBYTE_12_ADDR */
#define TPI_AVI_DBYTE_12_ADDR            (0x060)

/* REG£ºTPI AVI InfoFrame Date #13
   Name:  TPI_AVI_DBYTE_13_ADDR */
#define TPI_AVI_DBYTE_13_ADDR            (0x064)

/* REG£ºTPI system Control
   Name:  TPI_SYSTEM_CTRL_ADDR */
#define TPI_SYSTEM_CTRL_ADDR             (0x068)

/* REG£ºTPI Identification Register 1
   Name:  TPI_DEV_ID_ADDR */
#define TPI_DEV_ID_ADDR                  (0x06C)

/* REG£ºTPI Identification Register 2
   Name:  TPI_RO2_ADDR */
#define TPI_RO2_ADDR                     (0x070)

/* REG£ºTPI Identification Register 3
   Name:  TPI_VENDOR_B3_ADDR */
#define TPI_VENDOR_B3_ADDR               (0x074)

/* REG£ºTPI Device Power State Control Data
   Name:  TPI_POWER_STATUS_ADDR */
#define TPI_POWER_STATUS_ADDR            (0x078)

/* REG£ºMapping of I2S Interface
   Name:  TPI_IIS_MAP_ADDR */
#define TPI_IIS_MAP_ADDR                 (0x07C)

/* REG£ºConfiguration of I2S Interface
   Name:  TPI_IIS_INTERFACE_ADDR */
#define TPI_IIS_INTERFACE_ADDR           (0x080)

/* REG£ºStream Header Settings for I2S
   Name:  TPI_IIS_CHANNEL_STATUS_L_ADDR */
#define TPI_IIS_CHANNEL_STATUS_L_ADDR    (0x084)

/* REG£ºStream Header Settings for I2S
   Name:  TPI_IIS_CHANNEL_STATUS_H_ADDR */
#define TPI_IIS_CHANNEL_STATUS_H_ADDR    (0x088)

/* REG£ºI2S Channel Status Byte 2: Source, Channel Number
   Name:  TPI_IIS_CHANNEL_SOURCE_ADDR */
#define TPI_IIS_CHANNEL_SOURCE_ADDR      (0x08C)

/* REG£ºI2S Channel Status Byte 3: Accuracy, Sampling fs
   Name:  TPI_IIS_FS_1_ADDR */
#define TPI_IIS_FS_1_ADDR                (0x090)

/* REG£ºI2S Channel Status Byte 4: Original fs, Sample Length
   Name:  TPI_IIS_FS_2_ADDR */
#define TPI_IIS_FS_2_ADDR                (0x094)

/* REG£ºTPI Audio Configuration Write Data #0
   Name:  TPI_SPDIF_HEADER_ADDR */
#define TPI_SPDIF_HEADER_ADDR            (0x090)

/* REG£ºTPI Audio Configuration Write Data #1
   Name:  TPI_AUDIO_HANDLING_ADDR */
#define TPI_AUDIO_HANDLING_ADDR          (0x094)

/* REG£ºTPI Audio Configuration Write Data #2
   Name:  TPI_AUDIO_CONF_1_ADDR */
#define TPI_AUDIO_CONF_1_ADDR            (0x098)

/* REG£ºTPI Audio Configuration Write Data #3
   Name:  TPI_AUDIO_CONF_2_ADDR */
#define TPI_AUDIO_CONF_2_ADDR            (0x09C)

/* REG£ºTPI Audio Configuration Write Data #4 */
#define TPI_AUDIO_CONF_3_ADDR            (0x0A0)

/* REG£ºTPI Security Register #0
   Name:  TPI_QUERY_DATA_ADDR */
#define TPI_QUERY_DATA_ADDR              (0x0A4)

/* REG£ºTPI Security Register #1
   Name:  TPI_CONTROL_DATA_ADDR */
#define TPI_CONTROL_DATA_ADDR            (0x0A8)

/* REG£ºTPI Security Register #2
   Name:  TPI_BKSV_1_ADDR */
#define TPI_BKSV_1_ADDR                  (0x0AC)

/* REG£ºTPI Security Register #3
   Name:  TPI_BKSV_2_ADDR */
#define TPI_BKSV_2_ADDR                  (0x0B0)

/* REG£ºTPI Security Register #4
   Name:  TPI_BKSV_3_ADDR */
#define TPI_BKSV_3_ADDR                  (0x0B4)

/* REG£ºTPI Security Register #5
   Name:  TPI_BKSV_4_ADDR */
#define TPI_BKSV_4_ADDR                  (0x0B8)

/* REG£ºTPI Security Register #6
   Name:  TPI_BKSV_5_ADDR */
#define TPI_BKSV_5_ADDR                  (0x0BC)

/* REG£ºTPI HDCP Revision Data
   Name:  TPI_HDCP_REVISION_ADDR */
#define TPI_HDCP_REVISION_ADDR           (0x0C0)

/* REG£ºTPI KSV and V* Value Data
   Name:  TPK_KSV_VALUE_ADDR */
#define TPK_KSV_VALUE_ADDR               (0x0C4)

/* REG£ºTPI V* Value Readback Data (RO)
   Name:  TPI_V_VALUE_0_ADDR */
#define TPI_V_VALUE_0_ADDR               (0x0C8)

/* REG£ºTPI V* Value Readback Data (RO)
   Name:  TPI_V_VALUE_1_ADDR */
#define TPI_V_VALUE_1_ADDR               (0x0CC)

/* REG£ºTPI V* Value Readback Data (RO)
   Name:  TPI_V_VALUE_2_ADDR */
#define TPI_V_VALUE_2_ADDR               (0x0D0)

/* REG£ºTPI V* Value Readback Data (RO)
   Name:  TPI_V_VALUE_3_ADDR */
#define TPI_V_VALUE_3_ADDR               (0x0D4)

/* REG£ºTPI Aksv Readback Data (RO)
   Name:  TPI_AKSV_1_ADDR */
#define TPI_AKSV_1_ADDR                  (0x0D8)

/* REG£ºTPI Aksv Readback Data (RO)
   Name:  TPI_AKSV_2_ADDR */
#define TPI_AKSV_2_ADDR                  (0x0DC)

/* REG£ºTPI Aksv Readback Data (RO)
   Name:  TPI_AKSV_3_ADDR */
#define TPI_AKSV_3_ADDR                  (0x0E0)

/* REG£ºTPI Aksv Readback Data (RO)
   Name:  TPI_AKSV_4_ADDR */
#define TPI_AKSV_4_ADDR                  (0x0E4)

/* REG£ºTPI Aksv Readback Data (RO)
   Name:  TPI_AKSV_5_ADDR */
#define TPI_AKSV_5_ADDR                  (0x0E8)

/* REG£ºTPI Interrupt Enable
   Name:  TPI_INTERRUPT_ADDR */
#define TPI_INTERRUPT_ADDR               (0x0F0)

/* REG£ºTPI Interrupt Status
   Name:  TPI_INTERRUPT_STATUS_ADDR */
#define TPI_INTERRUPT_STATUS_ADDR        (0x0F4)

/* REG£ºTPI Interrupt Status
   Name:  TPI_INTERRUPT_STATUS_1_ADDR */
#define TPI_INTERRUPT_STATUS_1_ADDR      (0x0F8)

/* REG£ºTPI Interrupt Status
   Name:  TPI_INTERRUPT_STATUS_2_ADDR */
#define TPI_INTERRUPT_STATUS_2_ADDR      (0x0FC)

/* REG£ºTPI Soft Reset
   Name:  TPI_SOFT_RESET_ADDR */
#define TPI_SOFT_RESET_ADDR              (0x100)

/* REG£ºTPI KSV Forward
   Name:  TPI_KSV_FORWARD_ADDR */
#define TPI_KSV_FORWARD_ADDR             (0x104)

/* REG£ºTPI KSV Forward
   Name:  TPI_KSV_FIFO_DATA_ADDR */
#define TPI_KSV_FIFO_DATA_ADDR           (0x108)

/* REG£ºTPI BCAPS (RO)
   Name:  TPI_BCAPS_ADDR */
#define TPI_BCAPS_ADDR                   (0x110)

/* REG£ºTPI BSTATUS (RO)
   Name:  TPI_BSTATUS_1_ADDR */
#define TPI_BSTATUS_1_ADDR               (0x114)

/* REG£ºTPI BSTATUS (RO)
   Name:  TPI_BSTATUS_2_ADDR */
#define TPI_BSTATUS_2_ADDR               (0x118)

/* REG£ºCb component / Blue component
   Name:  TPI_CB_B_COMPONENT_L_ADDR */
#define TPI_CB_B_COMPONENT_L_ADDR        (0x128)

/* REG£ºCb component / Blue component
   Name:  TPI_CB_B_COMPONENT_H_ADDR */
#define TPI_CB_B_COMPONENT_H_ADDR        (0x12C)

/* REG£ºY component / Green component
   Name:  TPI_Y_G_COMPONENT_L_ADDR */
#define TPI_Y_G_COMPONENT_L_ADDR         (0x130)

/* REG£ºY component / Green component
   Name:  TPI_Y_G_COMPONENT_H_ADDR */
#define TPI_Y_G_COMPONENT_H_ADDR         (0x134)

/* REG£ºCr component / Red component
   Name:  TPI_CR_R_COMPONENT_L_ADDR */
#define TPI_CR_R_COMPONENT_L_ADDR        (0x138)

/* REG£ºCr component / Red component
   Name:  TPI_CR_R_COMPONENT_H_ADDR */
#define TPI_CR_R_COMPONENT_H_ADDR        (0x13C)

/* REG£ºSync Register Configuration and Sync Monitoring Register #0
   Name:  TPI_SYNC_CTRL_0_ADDR */
#define TPI_SYNC_CTRL_0_ADDR             (0x180)

/* REG£ºSync Register Configuration and Sync Monitoring Register #1
   Name:  TPI_SYNC_CTRL_1_ADDR */
#define TPI_SYNC_CTRL_1_ADDR             (0x184)

/* REG£ºExplicit Sync DE Generator Register #0
   Name:  TPI_DE_DLY_ADDR */
#define TPI_DE_DLY_ADDR                  (0x188)

/* REG£ºExplicit Sync DE Generator Register #1
   Name:  TPI_SYNC_DE_ADDR */
#define TPI_SYNC_DE_ADDR                 (0x18C)

/* REG£ºExplicit Sync DE Generator Register #2
   Name:  TPI_SYNC_DE_TOP_ADDR */
#define TPI_SYNC_DE_TOP_ADDR             (0x190)

/* REG£ºExplicit Sync DE Generator Register #3 */
#define TPI_SYNC_DE_3_ADDR               (0x194)

/* REG£ºExplicit Sync DE Generator Register #4
   Name:  TPI_SYNC_DE_CNT_L_ADDR */
#define TPI_SYNC_DE_CNT_L_ADDR           (0x198)

/* REG£ºExplicit Sync DE Generator Register #5
   Name:  TPI_SYNC_DE_CNT_H_ADDR */
#define TPI_SYNC_DE_CNT_H_ADDR           (0x19C)

/* REG£ºExplicit Sync DE Generator Register #6
   Name:  TPI_SYNC_DE_LIN_L_ADDR */
#define TPI_SYNC_DE_LIN_L_ADDR           (0x1A0)

/* REG£ºExplicit Sync DE Generator Register #7
   Name:  TPI_SYNC_DE_LIN_H_ADDR */
#define TPI_SYNC_DE_LIN_H_ADDR           (0x1A4)

/* REG£ºExplicit Sync DE Generator Register #8
   Name:  TPI_SYNC_DE_H_RES_L_ADDR */
#define TPI_SYNC_DE_H_RES_L_ADDR         (0x1A8)

/* REG£ºExplicit Sync DE Generator Register #9
   Name:  TPI_SYNC_DE_H_RES_H_ADDR */
#define TPI_SYNC_DE_H_RES_H_ADDR         (0x1AC)

/* REG£ºExplicit Sync DE Generator Register #10
   Name:  TPI_SYNC_DE_V_RES_L_ADDR */
#define TPI_SYNC_DE_V_RES_L_ADDR         (0x1B0)

/* REG£ºExplicit Sync DE Generator Register #11
   Name:  TPI_SYNC_DE_V_RES_H_ADDR */
#define TPI_SYNC_DE_V_RES_H_ADDR         (0x1B4)

/* REG£ºTPI HW Debug #1 Register
   Name:  TPI_HW_DBG1_ADDR */
#define TPI_HW_DBG1_ADDR                 (0x1E4)

/* REG£ºTPI HW Debug #3 Register
   Name:  TPI_HW_DBG3_ADDR */
#define TPI_HW_DBG3_ADDR                 (0x1EC)

/* REG£ºTPI HW Debug #7 Register
   Name:  TPI_HW_DBG7_ADDR */
#define TPI_HW_DBG7_ADDR                 (0x1FC)

/* REG£ºTPI Security Registers
   Name:  TPI_SECURITY_CTRL_ADDR */
#define TPI_SECURITY_CTRL_ADDR           (0x2EC)

/* REG£ºTPI Index Reg page number
   Name:  TPI_INDEX_REG_PAGE_ADDR */
#define TPI_INDEX_REG_PAGE_ADDR          (0x2F0)

/* REG£ºTPI Index Reg offset
   Name:  TPI_INDEX_REG_OFFSET_ADDR */
#define TPI_INDEX_REG_OFFSET_ADDR        (0x2F4)

/* REG£ºTPI Index Reg data
   Name:  TPI_INDEX_REG_VALUE_ADDR */
#define TPI_INDEX_REG_VALUE_ADDR         (0x2F8)

/* REG£ºTPI Miscellaneous InfoFrame Data #0
   Name:  TPI_I_F_SELECT_ADDR */
#define TPI_I_F_SELECT_ADDR              (0x2FC)

/* REG£ºTPI Miscellaneous InfoFrame Data #1
   Name:  TPI_I_F_TYPE_ADDR */
#define TPI_I_F_TYPE_ADDR                (0x300)

/* REG£ºTPI Miscellaneous InfoFrame Data #2
   Name:  TPI_I_F_VER_ADDR */
#define TPI_I_F_VER_ADDR                 (0x304)

/* REG£ºTPI Miscellaneous InfoFrame Data #3
   Name:  TPI_I_F_LENGTH_ADDR */
#define TPI_I_F_LENGTH_ADDR              (0x308)

/* REG£ºTPI Miscellaneous InfoFrame Data #4
   Name:  TPI_I_F_CHECKSUM_ADDR */
#define TPI_I_F_CHECKSUM_ADDR            (0x30C)

/* REG£ºTPI Miscellaneous InfoFrame Data #5
   Name:  TPI_I_F_BYTE_0_ADDR */
#define TPI_I_F_BYTE_0_ADDR              (0x310)

/* REG£ºTPI Miscellaneous InfoFrame Data #6
   Name:  TPI_I_F_BYTE_1_ADDR */
#define TPI_I_F_BYTE_1_ADDR              (0x314)

/* REG£ºTPI Miscellaneous InfoFrame Data #n
   Name:  TPI_I_F_BYTE_2N_ADDR */
#define TPI_I_F_BYTE_2N_ADDR             (0x318)

/* REG£ºTPI DDC I2C Data Register
   Name:  TPI_DDC_DATA_ADDR */
#define TPI_DDC_DATA_ADDR                (0x3D0)

/* REG£ºTPI Page Number
   Name:  TPI_PAGE_INDEX_ADDR  */
#define TPI_PAGE_INDEX_ADDR              (0x3FC)

/* REG£º
   Name:  PHY_DM_TX_TEST_MUX_CTRL_ADDR */
#define PHY_DM_TX_TEST_MUX_CTRL_ADDR     (0x0000)

/* REG£º
   Name:  PHY_DM_TX_CHIP_ID_ADDR */
#define PHY_DM_TX_CHIP_ID_ADDR           (0x0004)

/* REG£º
   Name:  PHY_PLL_CTRL_ADDR */
#define PHY_PLL_CTRL_ADDR                (0x0008)

/* REG£º
   Name:  PHY_OSC_CTRL_ADDR */
#define PHY_OSC_CTRL_ADDR                (0x000C)

/* REG£º
   Name:  PHY_OSC_ACLK_CTRL_ADDR */
#define PHY_OSC_ACLK_CTRL_ADDR           (0x0010)

/* REG£º
   Name:  PHY_DM_TX_CTRL1_ADDR */
#define PHY_DM_TX_CTRL1_ADDR             (0x0014)

/* REG£º
   Name:  PHY_DM_TX_CTRL2_ADDR */
#define PHY_DM_TX_CTRL2_ADDR             (0x0018)

/* REG£º
   Name:  PHY_DM_TX_CTRL3_ADDR */
#define PHY_DM_TX_CTRL3_ADDR             (0x001C)

/* REG£º
   Name:  PHY_DM_TX_CTRL4_ADDR */
#define PHY_DM_TX_CTRL4_ADDR             (0x0020)

/* REG£º
   Name:  PHY_DM_TX_CTRL5_ADDR */
#define PHY_DM_TX_CTRL5_ADDR             (0x0024)

/* REG£º
   Name:  PHY_BIAS_GEN_CTRL1_ADDR */
#define PHY_BIAS_GEN_CTRL1_ADDR          (0x0028)

/* REG£º
   Name:  PHY_BIAS_GEN_CTRL2_ADDR */
#define PHY_BIAS_GEN_CTRL2_ADDR          (0x002C)

/* REG£º
   Name:  PHY_DM_TX_STAT_ADDR */
#define PHY_DM_TX_STAT_ADDR              (0x0030)

/* REG£º
   Name:  PHY_HDMI_CTRL_ADDR */
#define PHY_HDMI_CTRL_ADDR               (0x0034)

/* REG£º
   Name:  PHY_HDMI_DRV_CTRL_ADDR */
#define PHY_HDMI_DRV_CTRL_ADDR           (0x0038)

/* REG£º
   Name:  PHY_MHL_DRV_CTRL_ADDR */
#define PHY_MHL_DRV_CTRL_ADDR            (0x003C)

/* REG£º
   Name:  PHY_MHL_CTRL1_ADDR */
#define PHY_MHL_CTRL1_ADDR               (0x0040)

/* REG£º
   Name:  PHY_MHL_CTRL2_ADDR */
#define PHY_MHL_CTRL2_ADDR               (0x0044)

/* REG£º
   Name:  PHY_MHL_STAT_ADDR */
#define PHY_MHL_STAT_ADDR                (0x0048)

/* REG£º
   Name:  PHY_CBUS_MEAS_RGND_CTRL1_ADDR */
#define PHY_CBUS_MEAS_RGND_CTRL1_ADDR    (0x004C)

/* REG£º
   Name:  PHY_CBUS_MEAS_RGND_CTRL2_ADDR */
#define PHY_CBUS_MEAS_RGND_CTRL2_ADDR    (0x0050)

/* REG£º
   Name:  PHY_CBUS_DRV_CTRL_ADDR */
#define PHY_CBUS_DRV_CTRL_ADDR           (0x0054)

/* REG£º
   Name:  PHY_CBUS_STAT_ADDR */
#define PHY_CBUS_STAT_ADDR               (0x0058)

/* REG£º
   Name:  PHY_BIST_CTRL_ADDR */
#define PHY_BIST_CTRL_ADDR               (0x0074)

/* REG£º
   Name:  PHY_BIST_STAT_ADDR */
#define PHY_BIST_STAT_ADDR               (0x0078)

/* REG£º
   Name:  PHY_BIST_PATTERN_L_ADDR */
#define PHY_BIST_PATTERN_L_ADDR          (0x0080)

/* REG£º
   Name:  PHY_BIST_PATTERN_H_ADDR */
#define PHY_BIST_PATTERN_H_ADDR          (0x0084)

/* REG£º
   Name:  PHY_BIST_INSTRUCT_L_ADDR */
#define PHY_BIST_INSTRUCT_L_ADDR         (0x0088)

/* REG£º
   Name:  PHY_BIST_INSTRUCT_H_ADDR */
#define PHY_BIST_INSTRUCT_H_ADDR         (0x008C)

/* REG£º
   Name:  PHY_BIST_CONFIG_L_ADDR */
#define PHY_BIST_CONFIG_L_ADDR           (0x0090)

/* REG£º
   Name:  PHY_BIST_CONFIG_H_ADDR */
#define PHY_BIST_CONFIG_H_ADDR           (0x0094)

/* REG£ºCBUS Connection Status Register
   Name:  CBUS_REG_CBUS_CONN_STATUS_ADDR */
#define CBUS_REG_CBUS_CONN_STATUS_ADDR   (0x0244)

/* REG£ºMSC Interrupt Register
   Name:  CBUS_REG_MSC_INTR_ADDR */
#define CBUS_REG_MSC_INTR_ADDR           (0x0248)

/* REG£ºMSC Interrupt Mask Register
   Name:  CBUS_REG_MSC_INTR_MASK_ADDR */
#define CBUS_REG_MSC_INTR_MASK_ADDR      (0x024C)

/* REG£ºMSC Command Start Register
   Name:  CBUS_REG_MSC_CMD_START_ADDR */
#define CBUS_REG_MSC_CMD_START_ADDR      (0x02E0)

/* REG£ºMSC Command or Offset Register
   Name:  CBUS_REG_MSC_CMD_OR_OFFSET_ADDR */
#define CBUS_REG_MSC_CMD_OR_OFFSET_ADDR  (0x02E4)

/* REG£ºMSC Send Data Register #1
   Name:  CBUS_REG_MSC_SEND_DATA1_ADDR */
#define CBUS_REG_MSC_SEND_DATA1_ADDR     (0x02E8)

/* REG£ºMSC Send Data Register #2
   Name:  CBUS_REG_MSC_SEND_DATA2_ADDR */
#define CBUS_REG_MSC_SEND_DATA2_ADDR     (0x02EC)

/* REG£ºMSC Receive Data Register #1
   Name:  CBUS_REG_MSC_RCVD_DATA1_ADDR */
#define CBUS_REG_MSC_RCVD_DATA1_ADDR     (0x02F0)

/* REG£ºMSC Receive Data Register #2
   Name:  CBUS_REG_MSC_RCVD_DATA2_ADDR */
#define CBUS_REG_MSC_RCVD_DATA2_ADDR     (0x02F4)

/* REG£ºMSC_MSG Received Data Register #1
   Name:  CBUS_REG_MSC_MSG_RCVD_DATA1_ADDR */
#define CBUS_REG_MSC_MSG_RCVD_DATA1_ADDR  (0x02FC)

/* REG£ºMSC_MSG Received Data Register #2
   Name:  CBUS_REG_MSC_MSG_RCVD_DATA2_ADDR */
#define CBUS_REG_MSC_MSG_RCVD_DATA2_ADDR  (0x0300)

/* REG£ºMSC Responder  Receivd Offset Register
   Name:  CBUS_REG_MSC_MR_RCVD_OFFSET_ADDR */
#define CBUS_REG_MSC_MR_RCVD_OFFSET_ADDR  (0x0304)

/* REG£ºMSC Responder  Receivd Data Register
   Name:  CBUS_REG_MSC_MR_RCVD_DATA_ADDR */
#define CBUS_REG_MSC_MR_RCVD_DATA_ADDR   (0x0308)

/* REG£ºMSC Retry Interval Register
   Name:  CBUS_REG_MSC_RETRY_INTERVAL_ADDR */
#define CBUS_REG_MSC_RETRY_INTERVAL_ADDR  (0x0354)

/* REG£ºMSC Error Interrupt Register
   Name:  CBUS_REG_MSC_ERROR_INTR_ADDR */
#define CBUS_REG_MSC_ERROR_INTR_ADDR     (0x0250)

/* REG£ºMSC Error Interrupt Mask Register
   Name:  CBUS_REG_MSC_ERROR_INTR_MASK_ADDR */
#define CBUS_REG_MSC_ERROR_INTR_MASK_ADDR  (0x0254)

/* REG£ºCBUS DDC Abort Interrupt Register
   Name:  CBUS_REG_DDC_ABORT_INTR_ADDR */
#define CBUS_REG_DDC_ABORT_INTR_ADDR      (0x0260)

/* REG£ºCBUS DDC Abort Interrupt Mask Register
   Name:  CBUS_REG_DDC_ABORT_INTR_MASK_ADDR */
#define CBUS_REG_DDC_ABORT_INTR_MASK_ADDR (0x0264)

/* REG£ºMSC Send Error Register
   Name:  CBUS_REG_MSC_SEND_ERROR_ADDR */
#define CBUS_REG_MSC_SEND_ERROR_ADDR     (0x0268)

/* REG£ºMSC Send Error Mask Register
   Name:  CBUS_REG_MSC_SEND_ERROR_MASK_ADDR */
#define CBUS_REG_MSC_SEND_ERROR_MASK_ADDR  (0x026C)

/* REG£ºMSC Receive Error Register
   Name:  CBUS_REG_MSC_RCV_ERROR_ADDR */
#define CBUS_REG_MSC_RCV_ERROR_ADDR      (0x0270)

/* REG£ºMSC Receive Error Mask Register
   Name:  CBUS_REG_MSC_RCV_ERROR_MASK_ADDR */
#define CBUS_REG_MSC_RCV_ERROR_MASK_ADDR  (0x0274)

/* REG£ºMHL Device Capability Registers
   Name:  CBUS_MHL_DEVCAP_0_F_ADDR */
#define CBUS_MHL_DEVCAP_0_F_ADDR         (0x0000)

/* REG£ºMHL Interrupt Registers
   Name:  CBUS_MHL_INT_0_ADDR */
#define CBUS_MHL_INT_0_ADDR              (0x0080)

/* REG£ºMHL Interrupt Registers
   Name:  CBUS_MHL_INT_1_ADDR */
#define CBUS_MHL_INT_1_ADDR              (0x0084)

/* REG£ºMHL Interrupt Mask Registers
   Name:  CBUS_MHL_INT_0_MASK_ADDR */
#define CBUS_MHL_INT_0_MASK_ADDR         (0x0200)

/* REG£ºMHL Interrupt Mask Registers
   Name:  CBUS_MHL_INT_1_MASK_ADDR */
#define CBUS_MHL_INT_1_MASK_ADDR         (0x0204)

/* REG£ºMHL Status Registers
   Name:  CBUS_MHL_STAT_0_3_ADDR */
#define CBUS_MHL_STAT_0_3_ADDR           (0x00C0)

/* REG£ºMHL Scratchpad Registers
   Name:  CBUS_MHL_SCRPAD_0_F_ADDR */
#define CBUS_MHL_SCRPAD_0_F_ADDR         (0x0100)

/* REG£ºMHL Write Burst Transmit Registers
   Name:  CBUS_WB_XMIT_DATA_0_F_ADDR */
#define CBUS_WB_XMIT_DATA_0_F_ADDR       (0x0180)

/* REG£ºWRITE_BURST Receive Control Register
   Name:  CBUS_SPAD_RCV_CTRL_ADDR */
#define CBUS_SPAD_RCV_CTRL_ADDR          (0x0218)

/* REG£ºWRITE_BURST Receive Read Port Register
   Name:  CBUS_SPAD_RFIFO_DATA_ADDR */
#define CBUS_SPAD_RFIFO_DATA_ADDR        (0x021C)

/* REG£ºWRITE_BURST Received Count Register
   Name:  CBUS_REG_WBURST_RCVD_DATA_CNT_ADDR */
#define CBUS_REG_WBURST_RCVD_DATA_CNT_ADDR  (0x030C)

/* REG£ºWRITE_BURST Transmit Control Register
   Name:  CBUS_SPAD_XMIT_CTRL_ADDR */
#define CBUS_SPAD_XMIT_CTRL_ADDR         (0x0220)

/* REG£ºWRITE_BURST Transmit Write Port Register
   Name:  CBUS_SPAD_XMIT_WRITE_PORT_ADDR */
#define CBUS_SPAD_XMIT_WRITE_PORT_ADDR   (0x0224)

/* REG£ºWRITE_BURST Transmit Count Register
   Name:  CBUS_REG_MSC_WRITE_BURST_DATA_LEN_ADDR */
#define CBUS_REG_MSC_WRITE_BURST_DATA_LEN_ADDR  (0x0318)

/* REG£ºWRITE_BURST Receive FIFO Status Register
   Name:  CBUS_SPAD_RFIFO_STAT_ADDR */
#define CBUS_SPAD_RFIFO_STAT_ADDR        (0x0228)

/* REG£ºWRITE_BURST Transmit FIFO Status Register
   Name:  CBUS_SPAD_XFIFO_STAT_ADDR */
#define CBUS_SPAD_XFIFO_STAT_ADDR        (0x022C)

/* REG£ºWRITE_BURST Interrupt Register
   Name:  CBUS_SPAD_INTR_ADDR */
#define CBUS_SPAD_INTR_ADDR              (0x0230)

/* REG£ºWRITE_BURST Interrupt Mask Register
   Name:  CBUS_SPAD_INTR_MASK_ADDR */
#define CBUS_SPAD_INTR_MASK_ADDR         (0x0234)

/* REG£ºWRITE_BURST Error Interrupt Register
   Name:  CBUS_SPAD_ERROR_INTR_ADDR */
#define CBUS_SPAD_ERROR_INTR_ADDR        (0x0238)

/* REG£ºWRITE_BURST Error Interrupt Mask Register
   Name:  CBUS_SPAD_ERROR_INTR_MASK_ADDR */
#define CBUS_SPAD_ERROR_INTR_MASK_ADDR   (0x023C)

/* REG£ºWRITE_BURST Peer Adopter ID Low Byte Register
   Name:  CBUS_SPAD_PEER_ADPT_ID_LBYTE_ADDR */
#define CBUS_SPAD_PEER_ADPT_ID_LBYTE_ADDR  (0x02D8)

/* REG£ºWRITE_BURST Peer Adopter ID High Byte Register
   Name:  CBUS_SPAD_PEER_ADPT_ID_HBYTE_ADDR */
#define CBUS_SPAD_PEER_ADPT_ID_HBYTE_ADDR  (0x02DC)

uint8_t	    SiiDrvRegRead(uint32_t base, uint32_t idx);
void        SiiDrvRegWrite(uint32_t base, uint32_t idx, uint8_t val);
void        SiiDrvRegModify(uint32_t base, uint32_t idx, uint8_t mask, uint8_t value);
void        SiiDrvRegReadBlock(uint32_t base, uint32_t idx, uint8_t *pBuffer, uint8_t count );
void        SiiDrvRegWriteBlock(uint32_t base, uint32_t idx, uint8_t *pBuffer, uint8_t count );

uint8_t     SiiDrvReadByteTPI(uint32_t RegOffset);
void        SiiDrvWriteByteTPI (uint32_t RegOffset, uint8_t value);
void        SiiDrvModifyByteTPI(uint32_t RegOffset, uint8_t mask, uint8_t value);
void        SiiDrvReadBlockTPI(uint32_t TPI_Offset, uint8_t NBytes, uint8_t *pData);
void        SiiDrvWriteBlockTPI(uint32_t TPI_Offset, uint8_t NBytes, uint8_t *pData);

uint8_t     SiiDrvReadIndexedRegister(uint8_t PageNum, uint32_t RegOffset);
void        SiiDrvWriteIndexedRegister(uint8_t PageNum, uint32_t RegOffset, uint8_t RegValue);
void        SiiDrvModifyIndexedRegister (uint8_t PageNum, uint32_t RegOffset, uint8_t Mask, uint8_t Value);

#endif  // __SI_REG_ACCESS_H__

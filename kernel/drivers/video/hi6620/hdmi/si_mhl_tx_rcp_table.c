/**********************************************************************************/
/*  Copyright (c) 2011, Silicon Image, Inc.  All rights reserved.                 */
/*  No part of this work may be reproduced, modified, distributed, transmitted,   */
/*  transcribed, or translated into any language or computer format, in any form  */
/*  or by any means without written permission of: Silicon Image, Inc.,           */
/*  1140 East Arques Avenue, Sunnyvale, California 94085                          */
/**********************************************************************************/
/*
   @file si_mhl_tx_rcp_table.c
*/
#include "si_mhl_main.h"  
#include "si_mhl_defs.h"
#include <linux/input.h>

#define	MHL_MAX_RCP_KEY_CODE	(0x7F + 1)	// inclusive

//PLACE_IN_CODE_SEG uint8_t rcpSupportTable [MHL_MAX_RCP_KEY_CODE] = {
uint8_t rcpSupportTable [MHL_MAX_RCP_KEY_CODE] = {  
	(MHL_DEV_LD_GUI),		// 0x00 = Select
	(MHL_DEV_LD_GUI),		// 0x01 = Up
	(MHL_DEV_LD_GUI),		// 0x02 = Down
	(MHL_DEV_LD_GUI),		// 0x03 = Left
	(MHL_DEV_LD_GUI),		// 0x04 = Right
	0, 0, 0, 0,				// 05-08 Reserved
	(MHL_DEV_LD_GUI),		// 0x09 = Root Menu
	0, 0, 0,				// 0A-0C Reserved
	(MHL_DEV_LD_GUI),		// 0x0D = Select
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,	// 0E-1F Reserved
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),	// Numeric keys 0x20-0x29
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),
	0,						// 0x2A = Dot
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),	// Enter key = 0x2B
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA | MHL_DEV_LD_TUNER),	// Clear key = 0x2C
	0, 0, 0,				// 2D-2F Reserved
	(MHL_DEV_LD_TUNER),		// 0x30 = Channel Up
	(MHL_DEV_LD_TUNER),		// 0x31 = Channel Dn
	(MHL_DEV_LD_TUNER),		// 0x32 = Previous Channel
	(MHL_DEV_LD_AUDIO),		// 0x33 = Sound Select
	0,						// 0x34 = Input Select
	0,						// 0x35 = Show Information
	0,						// 0x36 = Help
	0,						// 0x37 = Page Up
	0,						// 0x38 = Page Down
	0, 0, 0, 0, 0, 0, 0,	// 0x39-0x3F Reserved
	0,						// 0x40 = Undefined

	(MHL_DEV_LD_SPEAKER),	// 0x41 = Volume Up
	(MHL_DEV_LD_SPEAKER),	// 0x42 = Volume Down
	(MHL_DEV_LD_SPEAKER),	// 0x43 = Mute
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO),	// 0x44 = Play
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_RECORD),	// 0x45 = Stop
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_RECORD),	// 0x46 = Pause
	(MHL_DEV_LD_RECORD),	// 0x47 = Record
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO),	// 0x48 = Rewind
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO),	// 0x49 = Fast Forward
	(MHL_DEV_LD_MEDIA),		// 0x4A = Eject
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA),	// 0x4B = Forward
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_MEDIA),	// 0x4C = Backward
	0, 0, 0,				// 4D-4F Reserved
	0,						// 0x50 = Angle
	0,						// 0x51 = Subpicture
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 52-5F Reserved
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO),	// 0x60 = Play Function
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO),	// 0x61 = Pause the Play Function
	(MHL_DEV_LD_RECORD),	// 0x62 = Record Function
	(MHL_DEV_LD_RECORD),	// 0x63 = Pause the Record Function
	(MHL_DEV_LD_VIDEO | MHL_DEV_LD_AUDIO | MHL_DEV_LD_RECORD),	// 0x64 = Stop Function

	(MHL_DEV_LD_SPEAKER),	// 0x65 = Mute Function
	(MHL_DEV_LD_SPEAKER),	// 0x66 = Restore Mute Function
	0, 0, 0, 0, 0, 0, 0, 0, 0, 	                        // 0x67-0x6F Undefined or reserved
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 		// 0x70-0x7F Undefined or reserved
};


unsigned short rcpKeyMapTable[RCP_CMD_MAX]=
{
	    KEY_REPLY,			//= 0x00,MHL_RCP_CMD_SELECT          
        KEY_UP,				//= 0x01,MHL_RCP_CMD_UP              
        KEY_DOWN,			//= 0x02,MHL_RCP_CMD_DOWN            
        KEY_LEFT,			//= 0x03,MHL_RCP_CMD_LEFT            
        KEY_RIGHT,			//= 0x04,MHL_RCP_CMD_RIGHT           
        KEY_RESERVED,		//= 0x05,MHL_RCP_CMD_RIGHT_UP        
        KEY_RESERVED,		//= 0x06,MHL_RCP_CMD_RIGHT_DOWN      
        KEY_RESERVED,		//= 0x07,MHL_RCP_CMD_LEFT_UP         
        KEY_RESERVED,		//= 0x08,MHL_RCP_CMD_LEFT_DOWN       
        KEY_HOMEPAGE,		//= 0x09,MHL_RCP_CMD_ROOT_MENU       
        KEY_RESERVED,		//= 0x0A,MHL_RCP_CMD_SETUP_MENU      
        KEY_RESERVED,		//= 0x0B,MHL_RCP_CMD_CONTENTS_MENU 
        KEY_RESERVED,		//= 0x0C,MHL_RCP_CMD_FAVORITE_MENU   
        KEY_BACK,			//= 0x0D,MHL_RCP_CMD_EXIT     

	/*0x0E - 0x1F are reserved*/
	 KEY_RESERVED,		//= 0x0E 
	 KEY_RESERVED,		//= 0x0F 
	 KEY_RESERVED,		//= 0x10
	 KEY_RESERVED,		//= 0x11
	 KEY_RESERVED,		//= 0x12 
	 KEY_RESERVED,		//= 0x13
 	 KEY_RESERVED,		//= 0x14
	 KEY_RESERVED,		//= 0x15 
	 KEY_RESERVED,		//= 0x16
 	 KEY_RESERVED,		//= 0x17
	 KEY_RESERVED,		//= 0x18 
	 KEY_RESERVED,		//= 0x19
 	 KEY_RESERVED,		//= 0x1A
	 KEY_RESERVED,		//= 0x1B 
	 KEY_RESERVED,		//= 0x1C
 	 KEY_RESERVED,		//= 0x1D
	 KEY_RESERVED,		//= 0x1E 
	 KEY_RESERVED,		//= 0x1F
	 
        
        KEY_0,				//= 0x20,MHL_RCP_CMD_NUM_0           
        KEY_1,				//= 0x21,MHL_RCP_CMD_NUM_1           
        KEY_2,				//= 0x22,MHL_RCP_CMD_NUM_2           
        KEY_3,				//= 0x23,MHL_RCP_CMD_NUM_3           
        KEY_4,				//= 0x24,MHL_RCP_CMD_NUM_4           
        KEY_5,				//= 0x25,MHL_RCP_CMD_NUM_5           
        KEY_6,				//= 0x26,MHL_RCP_CMD_NUM_6           
        KEY_7,				//= 0x27,MHL_RCP_CMD_NUM_7           
        KEY_8,				//= 0x28,MHL_RCP_CMD_NUM_8          
        KEY_9,				//= 0x29,MHL_RCP_CMD_NUM_9           

        KEY_DOT,			//= 0x2A,MHL_RCP_CMD_DOT             
        KEY_ENTER,			//= 0x2B,MHL_RCP_CMD_ENTER           
        KEY_BACKSPACE,		//= 0x2C,MHL_RCP_CMD_CLEAR           

   	/*0x2D - 0x2F are reserved*/
	KEY_RESERVED,		//= 0x2D 
	KEY_RESERVED,		//= 0x2E 
	KEY_RESERVED,		//= 0x2F

        KEY_CHANNELUP,		//= 0x30,MHL_RCP_CMD_CH_UP           
        KEY_CHANNELDOWN,	//= 0x31,MHL_RCP_CMD_CH_DOWN         
        KEY_PREVIOUSSONG,	//= 0x32,MHL_RCP_CMD_PRE_CH          
        KEY_SOUND,			//= 0x33,MHL_RCP_CMD_SOUND_SELECT    
        KEY_RESERVED,		//= 0x34,MHL_RCP_CMD_INPUT_SELECT    
        KEY_RESERVED,		//= 0x35,MHL_RCP_CMD_SHOW_INFO       
        KEY_RESERVED,		//= 0x36,MHL_RCP_CMD_HELP            
        KEY_RESERVED,		//= 0x37,MHL_RCP_CMD_PAGE_UP         
        KEY_RESERVED,		//= 0x38,MHL_RCP_CMD_PAGE_DOWN       

	/*0x39 - 0x40 are reserved*/
	 KEY_RESERVED,		//=0x39
	 KEY_RESERVED,		//=0x3A
	 KEY_RESERVED,		//=0x3B
	 KEY_RESERVED,		//=0x3C
	 KEY_RESERVED,		//=0x3D
	 KEY_RESERVED,		//=0x3E
	 KEY_RESERVED,		//=0x3F
	 KEY_RESERVED,		//=0x40
	 
        KEY_VOLUMEUP,		//= 0x41,MHL_RCP_CMD_VOL_UP            
        KEY_VOLUMEDOWN,	//= 0x42,MHL_RCP_CMD_VOL_DOWN        
        KEY_MUTE,			//= 0x43,MHL_RCP_CMD_MUTE            
        KEY_PLAY,			//= 0x44,MHL_RCP_CMD_PLAY            
        KEY_STOP,			//= 0x45,MHL_RCP_CMD_STOP            
        KEY_PLAYPAUSE,		//= 0x46,MHL_RCP_CMD_PAUSE           
        KEY_RECORD,			//= 0x47,MHL_RCP_CMD_RECORD          
        KEY_REWIND,			//= 0x48,MHL_RCP_CMD_REWIND          
        KEY_FASTFORWARD,	//= 0x49,MHL_RCP_CMD_FAST_FWD        
        KEY_EJECTCD,			//= 0x4A,MHL_RCP_CMD_EJECT           
        KEY_FORWARD,		//= 0x4B,MHL_RCP_CMD_FWD             
        KEY_PREVIOUSSONG,	//= 0x4C,MHL_RCP_CMD_BKWD            

	/*0x4D - 0x4F are reserved*/
	KEY_RESERVED,		//=0x4D
	KEY_RESERVED,		//=0x4E
	KEY_RESERVED,		//=0x4F

        KEY_RESERVED,		//= 0x50,MHL_RCP_CMD_ANGLE            
        KEY_RESERVED,		//= 0x51,MHL_RCP_CMD_SUBPICTURE       

        /*0x52 - 0x5F are reserved*/
	KEY_RESERVED,		//=0x52
	KEY_RESERVED,		//=0x53
	KEY_RESERVED,		//=0x54
	KEY_RESERVED,		//=0x55
	KEY_RESERVED,		//=0x56
	KEY_RESERVED,		//=0x57
	KEY_RESERVED,		//=0x58
	KEY_RESERVED,		//=0x59
	KEY_RESERVED,		//=0x5A
	KEY_RESERVED,		//=0x5B
	KEY_RESERVED,		//=0x5C
	KEY_RESERVED,		//=0x5D
	KEY_RESERVED,		//=0x5E
	KEY_RESERVED,		//=0x5F
	
        KEY_PLAYCD,			//= 0x60,MHL_RCP_CMD_PLAY_FUNC       
        KEY_PAUSECD,		//= 0x61,MHL_RCP_CMD_PAUSE_PLAY_FUNC 
        KEY_RECORD,			//= 0x62,MHL_RCP_CMD_RECORD_FUNC     
        KEY_RESERVED,		//= 0x63,MHL_RCP_CMD_PAUSE_REC_FUNC  
        KEY_STOP,			//= 0x64,MHL_RCP_CMD_STOP_FUNC       
        KEY_RESERVED,		//= 0x65,MHL_RCP_CMD_MUTE_FUNC       
        KEY_RESERVED,		//= 0x66,MHL_RCP_CMD_UN_MUTE_FUNC    
        KEY_RESERVED,		//= 0x67,MHL_RCP_CMD_TUNE_FUNC       
        KEY_RESERVED,		//= 0x68,MHL_RCP_CMD_MEDIA_FUNC      

 	/*0x69 - 0x70 are reserved*/
	KEY_RESERVED,		//=0x69
	KEY_RESERVED,		//=0x6A
	KEY_RESERVED,		//=0x6B
	KEY_RESERVED,		//=0x6C
	KEY_RESERVED,		//=0x6D
	KEY_RESERVED,		//=0x6E
	KEY_RESERVED,		//=0x6F
	KEY_RESERVED,		//=0x70

        KEY_F1,				//= 0x71,MHL_RCP_CMD_F1              
        KEY_F2,				//= 0x72,MHL_RCP_CMD_F2              
        KEY_F3,				//= 0x73,MHL_RCP_CMD_F3              
        KEY_F4,				//= 0x74,MHL_RCP_CMD_F4              
        KEY_F5,				//= 0x75,MHL_RCP_CMD_F5              

        /*0x76 - 0x7D are reserved*/
	 KEY_RESERVED,		//=0x76
	 KEY_RESERVED,		//=0x77
	 KEY_RESERVED,		//=0x78
	 KEY_RESERVED,		//=0x79
	 KEY_RESERVED,		//=0x7A
	 KEY_RESERVED,		//=0x7B
	 KEY_RESERVED,		//=0x7C
	 KEY_RESERVED,		//=0x7D

        KEY_RESERVED,		//= 0x7E,MHL_RCP_CMD_VS              
        KEY_RESERVED		//= 0x7F,MHL_RCP_CMD_RSVD            
};

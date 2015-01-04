/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : test_hifi.h
  版 本 号   : 初稿
  生成日期   : 2012年11月20日
  最近修改   :
  功能描述   :
  函数列表   :

 修改历史      :


******************************************************************************/
#ifndef __TEST_HIFI_H__
#define __TEST_HIFI_H__
/*****************************************************************************
  1 头文件包含
*****************************************************************************/



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DSP_PID_VOICE_RT (301)
#define DSP_PID_AUDIO_RT (302)
#define DSP_PID_VOICE    (303)
#define DSP_PID_AUDIO    (304)
#define DSP_PID_HIFI_OM  (305)

#define ID_AP_HIFI_TEST_CMD  (0xDD32)
#define DRV_MAILBOX_CHANNEL_AUDIO_CH (3)

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 实 体 名  : TEST_HIFI_MSG_STRU
 功能描述  : A核传给hifi的消息结构体，封装在邮箱消息中
*****************************************************************************/
typedef struct
{
    unsigned short   usMsgId;           /*_H2ASN_Skip */
    unsigned short   usReserve;
    unsigned long    ulSenderPid;       /* SenderPid */
    unsigned long    ulReceiverPid;     /* ReceiverPid */
    unsigned long    ulChannel;         /* 通道号 */
    unsigned long    ulMsgLen;          /* 消息长度 */
}TEST_HIFI_MSG_STRU;


/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/
extern int test_send_encap_msg(unsigned char  *buff, unsigned long len);
extern int test_audioplayer_time_query(void);
extern int test_hifi_mail_reg( void  );
extern void test_hifi_handle_mail( void *usr_para, void *mail_handle, unsigned int mail_len  );
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of test_drv_mailbox.h */


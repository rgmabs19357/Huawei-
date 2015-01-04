#ifndef FB_MONITOR_H
#define FB_MONITOR_H

#include <linux/uaccess.h>

#define G_FOLLOW_FLAG_STOP 0
#define G_FOLLOW_FLAG_START 1
#define MAX_NUM 200

extern int g_follow_flag;
extern long *g_pframeinfo;
extern int  g_frame_num;

extern long k3fb_getCurrTime();

extern void k3fb_follow_start();

extern void k3fb_follow_stop(void __user *p);

extern long k3fb_first_disp_time( void __user *p);

extern long k3fb_every_disp_time( void __user *p);

extern long k3fb_average_frame_rate(void __user *p);
extern void k3fb_clear_frame_record();
extern void k3fb_listInsert(long currenttime);

#endif

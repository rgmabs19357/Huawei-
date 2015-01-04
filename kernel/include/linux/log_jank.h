#ifndef __LINUX_LOG_JANK_H__
#define __LINUX_LOG_JANK_H__

#define LOG_JANK_FS "/dev/log/jank"

int pr_jank(char* tag, const char* fmt, ...);

#endif

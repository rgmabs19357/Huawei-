#ifndef __LINUX_LOGEXCEPTION_H
#define __LINUX_LOGEXCEPTION_H

#define LOG_EXCEPTION_FS "/dev/log/exception"
int log_to_exception(char* tag, char* msg);


#endif

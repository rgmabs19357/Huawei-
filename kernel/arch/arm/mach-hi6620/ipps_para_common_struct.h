#ifndef __IPPS_PARA_COMMON_STRUCT_H__
#define __IPPS_PARA_COMMON_STRUCT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
struct ipps_para{
    unsigned int policy_num;
    unsigned int policy_head_len;
    unsigned int policy_each_freq_size;
    unsigned int policy_freq_num;
    unsigned char *policy_data;
};
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

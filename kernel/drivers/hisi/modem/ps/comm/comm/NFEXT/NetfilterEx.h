/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : NetWInterface.h
  Version     : V300R002
  Date        : 2011-11-23
  Description :
  History     :
  1. Date:2011-11-23
     Modification:Create
*******************************************************************************/

#ifndef _NETFILTEREX_H_
#define _NETFILTEREX_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "v_id.h"
#include "vos.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"
#include "NetWInterface.h"
#include "PsTypeDef.h"
#include "IpsMntn.h"
#include "omringbuffer.h"
#include "PsCommonDef.h"
#include "LinuxInterface.h"
#include "TtfNvInterface.h"


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define DBG_ON                                      (1)
#define DBG_OFF                                     (0)

#define NF_EXT_DBG                                  DBG_ON

#define NF_EXT_DEF_BR_ARP_HOOK_ON_MASK              (g_stExHookMask.ulBrArpHookValue)

#define NF_EXT_DEF_PRE_ROUTING_HOOK_ON_MASK         (g_stExHookMask.ulInHookValue)

#define NF_EXT_DEF_POST_ROUTING_HOOK_ON_MASK        (g_stExHookMask.ulOutHookValue)

/* 网络协议栈流控HOOK MASK开关 */
#define NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK           (g_stExHookMask.ulFlowCtrlHookValue)


#define NF_EXT_RPO_TCP                              (0x6)   /*TCP协议类型标志*/
#define NF_EXT_RING_BUF_SIZE                        (2048)  /*环形buff的大小*/
#define NF_TX_MSG_TASK_STACK_SIZE                   (32768)
#define MAC_HEADER_LENGTH                           (14)

#define NF_EXT_MAX_IP_SIZE                          (1500)

/* netfilter钩子函数掩码 */
#define NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK          (1)
#define NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK         (1 << 1)
#define NF_EXT_BR_FORWARD_HOOK_ON_MASK              (1 << 2)
#define NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK             (1 << 3)
#define NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK            (1 << 4)
#define NF_EXT_ARP_LOCAL_IN_ON_MASK                 (1 << 5)
#define NF_EXT_ARP_LOCAL_OUT_ON_MASK                (1 << 6)
#define NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK         (1 << 7)
#define NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK        (1 << 8)
#define NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK            (1 << 9)
#define NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK           (1 << 10)
#define NF_EXT_IP4_FORWARD_HOOK_ON_MASK             (1 << 11)
#define NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK         (1 << 12)
#define NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK        (1 << 13)
#define NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK            (1 << 14)
#define NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK           (1 << 15)
#define NF_EXT_IP6_FORWARD_HOOK_ON_MASK             (1 << 16)
#define NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK    (1 << 17)

#define NF_EXT_BR_FORWARD_FLOW_CTRL_MASK            (1)

#define NF_EXT_BR_NAME                              "br0"
#if(NF_EXT_DBG == DBG_ON)
#define NF_EXT_STATS_INC(a, b)                       (g_stNfExtStats.aulStats[b] += a)
#else
#define NF_EXT_STATS_INC(a, b)                       do{}while(0)
#endif

#define NF_EXT_TX_BYTES_INC(a, b)                    (g_stExFlowCtrlEntity.aulTxBytesCnt[b] += a)

#ifndef __UT_CENTER__
#define NF_EXT_MEM_ALLOC(pid, size)                  kmalloc(size, GFP_ATOMIC)
#define NF_EXT_MEM_FREE(pid, p)                      kfree(p);
#else
#define NF_EXT_MEM_ALLOC(pid, size)                  PS_MEM_ALLOC(pid, size)
#define NF_EXT_MEM_FREE(pid, p)                      PS_MEM_FREE(pid, p);
#endif

/*******************************************************************************
  3 枚举定义
*******************************************************************************/
enum NF_EXT_FLAG_OM_DATA_ENUM
{
    NF_EXT_FLAG_OM_DATA                = 0,                    /* OM消息标志 */
    NF_EXT_FLAG_NOT_OM_DATA            = 1,                    /* 非OM消息标志 */

    NF_EXT_FLAG_OM_DATA_BUTT
};
typedef int NF_EXT_FLAG_OM_DATA_ENUM_U32;

enum NF_EXT_FLAG_BLOCK_ENUM
{
    NF_EXT_FLAG_BLOCKED                = 0,                    /* 阻塞标志 */
    NF_EXT_FLAG_UNBLOCKED              = 1,                    /* 非阻塞标志 */

    NF_EXT_FLAG_BUTT
};

enum NF_EXT_TX_BYTES_CNT_ENUM
{
    NF_EXT_TX_BYTES_CNT_BR             = 0,                    /* 统计类型 */
    NF_EXT_TX_BYTES_CNT_BUTT
};

#if(NF_EXT_DBG == DBG_ON)
enum NF_EXT_STATS_ENUM
{
    NF_EXT_STATS_BR_FC_DROP            = 0,
    NF_EXT_STATS_BR_FC_ENTER,
    NF_EXT_STATS_BUF_FULL_DROP,
    NF_EXT_STATS_PUT_BUF_FAIL,
    NF_EXT_STATS_ALLOC_MEM_FAIL,
    NF_EXT_STATS_GET_BUF_FAIL,

    NF_EXT_STATS_BUT
};
#endif
/*****************************************************************************
  4 结构定义
*****************************************************************************/
/*********************************************
 结构体名 :NF_EXT_MASK_OPS_STRU
 协议表格 :无
 结构体说明 :勾子开关掩码映射表结构体
*********************************************/
typedef struct
{
    u_int32_t                       ulHookMask;
    struct nf_hook_ops              stNfExtOps;
} NF_EXT_MASK_OPS_STRU;


typedef struct
{
    VOS_UINT32                      ulIsBlkflag;               /* 阻塞条件 */
    VOS_UINT32                      ulCurHookOnMask;           /* 当前Hook掩码 */
    VOS_UINT32                      ulIsDeviceOpen ;           /* 设备是否开启的标志 */
    VOS_UINT32                      ulOmIp;
    VOS_UINT8                       aucKbuff[DEV_BUFF_LEN];    /* 内核空间的缓冲区 */
#ifndef __UT_CENTER__
    struct class                   *pstNfExtClass;
#else
    struct classStub               *pstNfExtClass;
#endif
    struct cdev                     stNfExtCdev;               /* 字符设备结构体 */
    dev_t                           ulDevNo;                   /* 字符设备号 */
    OM_RING_ID                      pRingBufferId;             /* 环形buff*/
    wait_queue_head_t               stWaitHeadDev;             /* 等待队列头 */
    wait_queue_head_t               stWaitHeadTxTask;          /* 等待队列头，自处理任务使用 */
    spinlock_t                      stLockTxTask;              /* 自旋锁，用于环形buff操作的互斥保护 */
}NF_EXT_ENTITY_STRU;

typedef struct
{
    VOS_UINT16   usDataLen;
    VOS_UINT8    aucRsv[2];
    VOS_UINT8   *pData;
}NF_EXT_DATA_RING_BUF_STRU;


typedef struct
{
    VOS_UINT32         ulFlowCtrlMsk;
    VOS_UINT32         aulTxBytesCnt[NF_EXT_TX_BYTES_CNT_BUTT];
    VOS_UINT8          aucRsv[4];
    struct net_device *pstBrDev;
}NF_EXT_FLOW_CTRL_ENTITY;

#if(NF_EXT_DBG == DBG_ON)
typedef struct
{
    VOS_UINT32  aulStats[NF_EXT_STATS_BUT];
}NF_EXT_STATS_STRU;
#endif

typedef struct
{
    VOS_UINT32          ulBrArpHookValue;       /* 网桥和ARP钩子函数对应的掩码 */
    VOS_UINT32          ulInHookValue;          /* IP层PRE_ROUTING钩子函数对应的掩码 */
    VOS_UINT32          ulOutHookValue;         /* IP层POST_ROUTING钩子函数对应的掩码 */
    VOS_UINT32          ulFlowCtrlHookValue;    /* 网桥流控钩子函数所对应的掩码 */
}NF_EXT_HOOK_MASK_NV_STRU;

/*****************************************************************************
  5 全局变量声明
*****************************************************************************/
#if(NF_EXT_DBG == DBG_ON)
extern NF_EXT_STATS_STRU g_stNfExtStats;
#endif

/*****************************************************************************
  6 函数声明
*****************************************************************************/
extern unsigned int NFExt_BrPreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrPostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));


extern unsigned int NFExt_BrLocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrLocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_ArpInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_ArpOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrForwardFlowCtrlHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));


extern unsigned int NFExt_Poll(struct file *file, poll_table *wait);
extern int NFExt_Open(struct inode *inode, struct file *file);

extern int NFExt_Release(struct inode *inode, struct file *file);

extern ssize_t NFExt_Read(struct file *filp, char *buff, size_t len, loff_t *offset);

extern ssize_t NFExt_Write(struct file *filp, const char *buff, size_t len, loff_t *offset);

extern PS_BOOL_ENUM_UINT8 NFExt_ConfigEffective(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg);

extern VOS_UINT32 NFExt_AddDataToRingBuf(NF_EXT_DATA_RING_BUF_STRU *pstMsg);

extern VOS_UINT32 NFExt_SaveBrDev(VOS_VOID);

extern VOS_VOID NFExt_FlowCtrlInit(VOS_VOID);

#if(NF_EXT_DBG == DBG_ON)
extern VOS_VOID NFExt_StatsShow(VOS_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
                            }
#endif
#endif

#endif

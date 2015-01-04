/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : drv_edma.h
  版 本 号   : 初稿
  最近修改   :
  功能描述   : drv_edma.h 的头文件
  函数列表   :
  修改历史   :
  1.日    期   : 2013年2月2日
    修改内容   : 创建文件

******************************************************************************/
#ifndef __DRV_EDMA_H__
#define __DRV_EDMA_H__
#include "drv_global.h"

typedef void (*channel_isr)(BSP_U32 channel_arg, BSP_U32 int_status);
#if 0
/*定义外设请求号*/
typedef enum _BALONG_DMA_REQ
{
    /* BBIT平台使用*/
    EDMA_SCI_RX = 0,
    EDMA_SCI_TX,
    EDMA_HSUART_RX,
    EDMA_HSUART_TX,
    EDMA_BBP_GRIF = 6,     /* BBP grif */

    /* 以下为SFT平台使用 */
    EDMA_SPI0_RX = 0,      /* v9r1 用于连接CMMB ，v3r3 用作SSP的Rx DMA请求*/
    EDMA_SPI0_TX,
    EDMA_SPI1_RX,            /* v9r1用于Touch Panel和Key Pad/备用, v3r3 为HS_SPI请求*/
    EDMA_SPI1_TX,
    EDMA_UART1_RX,         /* v9r1用于Felica（NFC) ，v3r3 用于UART0 的 Rx DMA请求*/
    EDMA_UART1_TX,
    EDMA_UART2_RX,         /* v9r1用于连接GPS ， v3r3 用于UART1  的 Rx DMA请求*/
    EDMA_UART2_TX,
    EDMA_UART3_RX,         /* v9r1用于连接BT ,v3r3 用于HSUART0 的 Rx DMA请求*/
    EDMA_UART3_TX,
    EDMA_UART4_RX,         /* v9r1用于连接CDMA ,v3r3 用于HSUART1的 Rx DMA请求*/
    EDMA_UART4_TX,
    EDMA_UART5_RX,         /* 用于连接CDMA */
    EDMA_UART5_TX,
    EDMA_SCI0_RX = 14,     /* 双卡双待 ,v3r3 用于sim卡的RX DMA请求*/
    EDMA_SCI0_TX,
    EDMA_SCI1_RX,
    EDMA_SCI1_TX,
    EDMA_SIO0_RX = 18,     /* v9r1用于音频接口 ，v3r3 用作SIO的Rx DMA请求*/
    EDMA_SIO0_TX,
    EDMA_SIO1_RX,
    EDMA_SIO1_TX,
    EDMA_SIO2_RX,
    EDMA_SIO2_TX,
    EDMA_SLIMBUS4,
    EDMA_SLIMBUS5,
    EDMA_SLIMBUS6,
    EDMA_SLIMBUS7,
    EDMA_SLIMBUS8,
    EDMA_SLIMBUS9,
    EDMA_SLIMBUS10,
    EDMA_UICC,                   /* 大容量SIM卡 */
    EDMA_MEMORY = 32,      /* 32,M2M虚拟外设请求线 */
    EDMA_MEMORY_DSP,      /* 为DSP定义的M2M虚拟外设请求线 */
    /*v3r3使用begin*/
    EDMA_MMC0,
    EDMA_MMC1,
    EDMA_I2C_RX,
    EDMA_I2C_TX,
    /*v3r3使用end*/
    EDMA_REQ_MAX      /* 如果设备请求不小于此值,则为非法请求 */
} BALONG_DMA_REQ;
#endif
typedef enum _BALONG_DMA_REQ
{
    EDMA_SPI0_RX,
    EDMA_SPI0_TX,
    EDMA_SPI1_RX,
    EDMA_SPI1_TX,
    EDMA_UART1_RX,
    EDMA_UART1_TX,
    EDMA_UART2_RX,
    EDMA_UART2_TX,
    EDMA_UART3_RX,
    EDMA_UART3_TX,
    EDMA_UART4_RX,
    EDMA_UART4_TX,
    EDMA_UART5_RX,
    EDMA_UART5_TX,
    EDMA_SCI0_RX,
    EDMA_SCI0_TX,
    EDMA_SCI1_RX,
    EDMA_SCI1_TX,
    EDMA_SIO0_RX,
    EDMA_SIO0_TX,
    EDMA_SIO1_RX,
    EDMA_SIO1_TX,
    EDMA_SIO2_RX,
    EDMA_SIO2_TX,
    EDMA_SLIMBUS4,
    EDMA_SLIMBUS5,
    EDMA_SLIMBUS6,
    EDMA_SLIMBUS7,
    EDMA_SLIMBUS8,
    EDMA_SLIMBUS9,
    EDMA_SLIMBUS10,
    EDMA_UICC,
    EDMA_MEMORY_1,
    EDMA_MEMORY_2,
    EDMA_MEMORY_3,
    EDMA_MEMORY_4,
    EDMA_MEMORY_DSP_1,
    EDMA_MEMORY_DSP_2,
    EDMA_MEMORY_DSP_3,
    EDMA_MEMORY_DSP_4,
    EDMA_MEMORY_DSP_5,
    EDMA_MEMORY_DSP_6,
    EDMA_MEMORY_DSP_7,
    EDMA_MEMORY_DSP_8,
    EDMA_BBP_GRIF,
    EDMA_BBP_DBG,
    EDMA_MMC0,
    EDMA_MMC1,
    EDMA_I2C_RX,
    EDMA_I2C_TX,
    EDMA_LOG_CHAN_RESERVED
} BALONG_DMA_REQ;

/* 函数void (*channel_isr)(BSP_U32 channel_arg, BSP_U32 int_status)的参数int_status、
    函数int balong_dma_channel_init (BALONG_DMA_REQ req,  channel_isr pFunc,
                     UINT32 channel_arg, UINT32 int_flag)的参数int_flag
    为以下几种中断类型，可组合       */
#define BALONG_DMA_INT_DONE           1          /*DMA传输完成中断*/
#define BALONG_DMA_INT_LLT_DONE       2          /*链式DMA节点传输完成中断*/
#define BALONG_DMA_INT_CONFIG_ERR     4          /*DMA配置错误导致的中断*/
#define BALONG_DMA_INT_TRANSFER_ERR   8          /*DMA传输错误导致的中断*/
#define BALONG_DMA_INT_READ_ERR       16         /*DMA链表读错误导致的中断*/

/* EDMAC传输方向定义*/
#define BALONG_DMA_P2M      1
#define BALONG_DMA_M2P      2
#define BALONG_DMA_M2M      3

/* EDMAC流控制与传输类型*/
typedef enum tagEDMA_TRANS_TYPE
{
    MEM_MEM_DMA = 0x00,    /* 内存到内存，DMA流控*/
    MEM_PRF_DMA = 0x01,        /* 内存与外设，DMA流控*/
    MEM_PRF_PRF = 0x10        /* 内存与外设，外设流控*/
} EDMA_TRANS_TYPE;

/* 通道状态 */

#define   EDMA_CHN_FREE          1   /* 通道空闲 */
#define   EDMA_CHN_BUSY          0   /* 通道忙 */


/* EDMA传输位宽，源、目的地址约束为一致的值 */
#define   EDMA_TRANS_WIDTH_8       0x0   /* 8bit位宽*/
#define   EDMA_TRANS_WIDTH_16      0x1   /* 16bit位宽*/
#define   EDMA_TRANS_WIDTH_32      0x2   /* 32bit位宽*/
#define   EDMA_TRANS_WIDTH_64      0x3   /* 64bit位宽*/

/*  EDMA burst length, 取值范围0~15，表示的burst长度为1~16*/
#define   EDMA_BUR_LEN_1    0x0    /* burst长度，即一次传输的个数为1个*/
#define   EDMA_BUR_LEN_2    0x1    /* burst长度，即一次传输的个数为2个*/
#define   EDMA_BUR_LEN_3    0x2   /* burst长度，即一次传输的个数为3个*/
#define   EDMA_BUR_LEN_4    0x3   /* burst长度，即一次传输的个数为4个*/
#define   EDMA_BUR_LEN_5    0x4   /* burst长度，即一次传输的个数为5个*/
#define   EDMA_BUR_LEN_6    0x5   /* burst长度，即一次传输的个数为6个*/
#define   EDMA_BUR_LEN_7    0x6   /* burst长度，即一次传输的个数为7个*/
#define   EDMA_BUR_LEN_8    0x7   /* burst长度，即一次传输的个数为8个*/
#define   EDMA_BUR_LEN_9    0x8   /* burst长度，即一次传输的个数为9个*/
#define   EDMA_BUR_LEN_10   0x9   /* burst长度，即一次传输的个数为10个*/
#define   EDMA_BUR_LEN_11   0xa   /* burst长度，即一次传输的个数为11个*/
#define   EDMA_BUR_LEN_12   0xb   /* burst长度，即一次传输的个数为12个*/
#define   EDMA_BUR_LEN_13   0xc   /* burst长度，即一次传输的个数为13个*/
#define   EDMA_BUR_LEN_14   0xd   /* burst长度，即一次传输的个数为14个*/
#define   EDMA_BUR_LEN_15   0xe   /* burst长度，即一次传输的个数为15个*/
#define   EDMA_BUR_LEN_16   0xf   /* burst长度，即一次传输的个数为16个*/


/* EDMA 对应的具体位，供EDMA  寄存器配置宏
       EDMAC_BASIC_CONFIG、BALONG_DMA_SET_LLI、BALONG_DMA_SET_CONFIG 使用*/
#define EDMAC_TRANSFER_CONFIG_SOUR_INC      (0X80000000)
#define EDMAC_TRANSFER_CONFIG_DEST_INC      (0X40000000)

#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH( _len )  ((BSP_U32)((_len)<<24))
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH( _len )  ((BSP_U32)((_len)<<20))

#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH( _len )  ((BSP_U32)((_len)<<16))
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH( _len )  ((BSP_U32)((_len)<<12))

#define EDMAC_TRANSFER_CONFIG_REQUEST( _ulReg )    ( (_ulReg ) << 4)
#define EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )    ((BSP_U32)((_len)<<2))

#define EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE            ( 0x2 )
#define EDMAC_TRANSFER_CONFIG_INT_TC_DISABLE           ( 0x0 )

#define EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE           ( 0x1 )
#define EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE          ( 0x0 )

#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_A_SYNC     ( 0UL )
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_AB_SYNC    ( 0x00008000 )

#define EDMAC_NEXT_LLI_ENABLE       0x2           /* Bit 1 */


#ifdef WIN32
#ifndef __attribute__
#define __attribute__(p)
#endif
#endif

/*链式传输时的节点信息*/
typedef struct _BALONG_DMA_CB
{
    volatile BSP_U32 lli;     /*指向下个LLI*/
    volatile BSP_U32 bindx;
    volatile BSP_U32 cindx;
    volatile BSP_U32 cnt1;
    volatile BSP_U32 cnt0;   /*块传输或者LLI传输的每个节点数据长度 <= 65535字节*/
    volatile BSP_U32 src_addr; /*物理地址*/
    volatile BSP_U32 des_addr; /*物理地址*/
    volatile BSP_U32 config;
} BALONG_DMA_CB __attribute__ ((aligned (32)));

#define P2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_DEST_INC)
#define M2P_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC)
#define M2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_MEM_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC | EDMAC_TRANSFER_CONFIG_DEST_INC)

#define EDMAC_BASIC_CONFIG(burst_width, burst_len) \
               ( EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH(burst_len) | EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH(burst_len) \
               | EDMAC_TRANSFER_CONFIG_SOUR_WIDTH(burst_width) | EDMAC_TRANSFER_CONFIG_DEST_WIDTH(burst_width) )

#define BALONG_DMA_SET_LLI(addr, last)   ((last)?0:(EDMAC_MAKE_LLI_ADDR(addr) | EDMAC_NEXT_LLI_ENABLE))

/**************************************************************************
  宏定义
**************************************************************************/

/*错误码定义*/
#define DMAC_SUCCESS                       BSP_OK
#define DMA_FAIL                           BSP_ERROR

#define DMA_ERROR_BASE                          -100
#define DMA_CHANNEL_INVALID                     (DMA_ERROR_BASE-1)
#define DMA_TRXFERSIZE_INVALID                  (DMA_ERROR_BASE-2)
#define DMA_SOURCE_ADDRESS_INVALID              (DMA_ERROR_BASE-3)
#define DMA_DESTINATION_ADDRESS_INVALID         (DMA_ERROR_BASE-4)
#define DMA_MEMORY_ADDRESS_INVALID              (DMA_ERROR_BASE-5)
#define DMA_PERIPHERAL_ID_INVALID               (DMA_ERROR_BASE-6)
#define DMA_DIRECTION_ERROR                     (DMA_ERROR_BASE-7)
#define DMA_TRXFER_ERROR                        (DMA_ERROR_BASE-8)
#define DMA_LLIHEAD_ERROR                       (DMA_ERROR_BASE-9)
#define DMA_SWIDTH_ERROR                        (DMA_ERROR_BASE-0xa)
#define DMA_LLI_ADDRESS_INVALID                 (DMA_ERROR_BASE-0xb)
#define DMA_TRANS_CONTROL_INVALID               (DMA_ERROR_BASE-0xc)
#define DMA_MEMORY_ALLOCATE_ERROR               (DMA_ERROR_BASE-0xd)
#define DMA_NOT_FINISHED                        (DMA_ERROR_BASE-0xe)
#define DMA_CONFIG_ERROR                        (DMA_ERROR_BASE-0xf)


/*******************************************************************************
  函数名:      BSP_S32 balong_dma_init(void)
  功能描述:    DMA初始化程序，挂接中断
  输入参数:    无
  输出参数:    无
  返回值:      0
*******************************************************************************/
extern BSP_S32 balong_dma_init(void);

/*******************************************************************************
  函数名:       int balong_dma_current_transfer_address(UINT32 channel_id)
  函数描述:     获得某通道当前传输的内存地址
  输入参数:     channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
  输出参数:     无
  返回值:       成功：通道当前传输的内存地址
                失败：-1
*******************************************************************************/
extern int balong_dma_current_transfer_address(BSP_U32 channel_id);
#define DRV_EDMA_CURR_TRANS_ADDR(channel_id)  balong_dma_current_transfer_address(channel_id)

/*******************************************************************************
  函数名:       int balong_dma_channel_stop(UINT32 channel_id)
  函数描述:     停止指定的DMA通道
  输入参数:     channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
  输出参数:     无
  返回值:       成功：通道当前传输的内存地址
                失败：-1
*******************************************************************************/
extern BSP_S32 balong_dma_channel_stop(BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_STOP(channel_id)  balong_dma_channel_stop(channel_id)


/*******************************************************************************
  函数名:      BALONG_DMA_CB *balong_dma_channel_get_lli_addr(UINT32 channel_id)
  函数描述:    获取指定DMA通道的链表控制块的起始地址
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
  输出参数:    无
  返回值:      成功：链表控制块起始地址
               失败：0
*******************************************************************************/
extern BALONG_DMA_CB *balong_dma_channel_get_lli_addr (BSP_U32 channel_id);
#define DRV_EDMA_CHAN_GET_LLI_ADDR(channel_id)  balong_dma_channel_get_lli_addr(channel_id)


/******************************************************************************
  函数名:      int balong_dma_channel_init (BALONG_DMA_REQ req,
                  channel_isr pFunc, UINT32 channel_arg, UINT32 int_flag)
  函数描述:    根据外设逻辑通道号映射物理通道号与请求号，注册通道中断回调函数、
               初始化传输完成信号量、将外设号写入config寄存器
  输入参数:    req : 逻辑通道号
               pFunc : 上层模块注册的DMA通道中断处理函数，NULL时表明不注册
               channel_arg : pFunc的入参1，
                             pFunc为NULL，不需要设置这个参数
                             为dsp分配的通道号为4~11,对于该参数，
                             dsp需传入4~11的某值来表示需要使用的通道号
               int_flag : pFunc的入参2, 产生的中断类型，取值范围为
                        BALONG_DMA_INT_DONE、BALONG_DMA_INT_LLT_DONE、
                      ALONG_DMA_INT_CONFIG_ERR、BALONG_DMA_INT_TRANSFER_ERR、
                        BALONG_DMA_INT_READ_ERR之一，或者组合。
                        pFunc为NULL，不需要设置这个参数
  输出参数:    无
  返回值:      成功：通道号
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_init (BALONG_DMA_REQ req, channel_isr pFunc, BSP_U32 channel_arg, BSP_U32 int_flag);
#define DRV_EDMA_CHANNEL_INIT(req, pFunc,channel_arg,int_flag) balong_dma_channel_init(req, pFunc,channel_arg,int_flag)

/*******************************************************************************
  函数名:      int balong_dma_channel_set_config (UINT32 channel_id,
                       UINT32 direction, UINT32 burst_width, UINT32 burst_len)
  函数描述:    非链式DMA传输时，调用本函数配置通道参数
               链式DMA传输时，不需要使用本函数。
  输入参数:    channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
               direction : DMA传输方向, 取值为BALONG_DMA_P2M、BALONG_DMA_M2P、
                           BALONG_DMA_M2M之一
               burst_width：取值为0、1、2、3，表示的burst位宽为8、16、32、64bit
               burst_len：取值范围0~15，表示的burst长度为1~16
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_set_config (BSP_U32 channel_id, BSP_U32 direction,BSP_U32 burst_width, BSP_U32 burst_len);
#define DRV_EDMA_CHANNEL_CONFIG(channel_id, direction,burst_width,burst_len)  balong_dma_channel_set_config(channel_id, direction,burst_width,burst_len)

/*******************************************************************************
  函数名:      int balong_dma_channel_dest_set_config (UINT32 channel_id,
                       UINT32 burst_width, UINT32 burst_len)
  函数描述:    BBP GRIF需要单独配置目的数据位宽和长度，调用本函数，其它情形不使用。
               使用时，该接口在balong_dma_channel_set_config之后调用。
  输入参数:    channel_id：通道ID，调用balong_dma_channel_init函数的返回值
               burst_width：取值为0、1、2、3，表示的burst位宽为8、16、32、64bit
               burst_len：取值范围0~15，表示的burst长度为1~16
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_dest_set_config (BSP_U32 channel_id, BSP_U32 dest_width, BSP_U32 dest_len);
#define DRV_EDMA_CHANNEL_DEST_CONFIG(channel_id, dest_width, dest_len)  balong_dma_channel_dest_set_config(channel_id, dest_width, dest_len)

/*******************************************************************************
  函数名:      int balong_dma_channel_start (UINT32 channel_id, UINT32 src_addr,
                       UINT32 des_addr, UINT32 len)
  函数描述:    启动一次同步DMA传输, DMA传输完成后，才返回
               使用本函数时，不需要注册中断处理函数
               len<65536(64K):一维传输
               65536(64K)<=len<16384*65536(1G)时:二维传输
               len>16384*65536:不支持
               二维传输len为16K整数倍，非整数倍将不支持
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
               src_addr：数据传输源地址，必须是物理地址
               des_addr：数据传输目的地址，必须是物理地址
               len：数据传输长度，单位：字节；支持最大长度是0x40000000字节
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_start (BSP_U32 channel_id, BSP_U32 src_addr, BSP_U32 des_addr, BSP_U32 len);
#define DRV_EDMA_CHANNEL_START(channel_id,src_addr,des_addr,len)  balong_dma_channel_start(channel_id,src_addr,des_addr,len)


/*******************************************************************************
  函数名:      int balong_dma_channel_async_start (UINT32 channel_id,
                unsigned int src_addr, unsigned int des_addr, unsigned int len)
  函数描述:    启动一次异步DMA传输。启动DMA传输后，就返回。不等待DMA传输完成。
               使用本函数时，注册中断处理函数，中断处理函数中处理DMA
传输完成事件
               或者，不注册中断处理函数，使用balong_dma_channel_is_idle函数查询
               DMA传输是否完成
               len<65536(64K):一维传输
               65536(64K)<=len<16384*65536(1G)时:二维传输
               len>16384*65536:不支持
               二维传输len为16K整数倍，非整数倍将不支持
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
               src_addr：数据传输源地址，必须是物理地址
               des_addr：数据传输目的地址，必须是物理地址
               len：数据传输长度，单位：字节；支持最大长度是0x40000000字节
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_async_start (BSP_U32 channel_id, BSP_U32 src_addr, BSP_U32 des_addr, BSP_U32 len);
#define DRV_EDMA_CHANNEL_ASYNC_START(channel_id,src_addr,des_addr,len) balong_dma_channel_async_start(channel_id,src_addr,des_addr,len)


/*******************************************************************************
  函数名:      int balong_dma_channel_lli_start (UINT32 channel_id)
  函数描述:    启动链式DMA传输。在链式DMA的所有节点传输都全部完成后才返回。
               链式DMA的每个节点的数据最大传输长度为65535字节。
               注意：调用此函数前，必须设置好链表控制块。
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_lli_start (BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_lli_START(channel_id)   balong_dma_channel_lli_start(channel_id)

/*******************************************************************************
  函数名:      int balong_dma_channel_lli_start (UINT32 channel_id)
  函数描述:    启动链式DMA传输，然后立即返回，不等待DMA传输完成。
               链式DMA的每个节点的数据最大传输长度为65535字节。
               注意：调用此函数前，必须设置好链表控制块。
  输入参数:    channel_id：通道ID,调用balong_dma_channel_init函数的返回值
  输出参数:    无
  返回值:      成功：0
               失败：负数
*******************************************************************************/
extern BSP_S32 balong_dma_channel_lli_async_start (BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_lli_ASYNC_START(channel_id)   balong_dma_channel_lli_async_start(channel_id)


/******************************************************************************
*
  函数名:       int balong_dma_channel_is_idle (UINT32 channel_id)
  函数描述:     查询DMA通道是否空闲
  输入参数:     channel_id : 通道ID，调用balong_dma_channel_init函数的返回值
  输出参数:     无
  返回值:       0 : 通道忙碌
                1 : 通道空闲
                负数 : 失败
*******************************************************************************/
extern BSP_S32 balong_dma_channel_is_idle (BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_IS_IDLE(chanel_id) balong_dma_channel_is_idle(chanel_id)

/*****************************************************************************
 函 数 名  : balong_dma_set_config
 功能描述  : 用于根据用户下发EDMA配置信息生成config寄存器信息并返回给用户
 输入参数  : req         逻辑请求号
             direction   传输方向
             burst_width burst传输位宽
             burst_len   burst传输长度
 输出参数  : 无
 返 回 值  : 0-失败，其他-生成的寄存器信息
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013年1月15日
    修改内容   : 新生成函数

*****************************************************************************/
extern BSP_U32 balong_dma_set_config(BALONG_DMA_REQ req, BSP_U32 direction, BSP_U32 burst_width, BSP_U32 burst_len);
#define BALONG_DMA_SET_CONFIG(req, direction, burst_width, burst_len) \
    balong_dma_set_config(req, direction, burst_width, burst_len)

/*****************************************************************************
 函 数 名  : DRV_EDMA_BBP_SAMPLE_REBOOT
 功能描述  : BBP采数使用重启接口，重启后系统会停留在fastboot阶段，以便导出采集数据，
             SFT平台A核使用，其他直接返回-1
 输入参数  : NA
 输出参数  : 无
 返 回 值  : OK-执行重启，ERROR-不执行重启
 调用函数  : NA
 被调函数  : NA

 修改历史      :
  1.日    期   : 2013年1月5日
    修改内容   : 新生成函数

*****************************************************************************/
extern BSP_S32 DRV_EDMA_BBP_SAMPLE_REBOOT(BSP_VOID);

#endif


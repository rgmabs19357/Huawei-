
#ifndef AXIMONITOR_H
#define AXIMONITOR_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BALONG_DEBUG_TAG    "AXI MONITOR "
#define ALIGN_DOWN(value,align) ((value)&~(align -1 ))
#define MONITOR_CLK_TIMEOUT (3000)
//#define taskDelay(time) do{msleep(time);}while(0)
/*中断次数后dump*/
#define AXI_MONITOR_TEST_TIMES  (100)

#define LOG_PATH "/dev/console"//"/data/axi_monitor.txt"

/*id最大数目*/
#define AXI_MON_IDS_NUM     (8)

/*虚实地址映射*/
#define TMP_INTEGRATOR_SC_BASE      (0xF7410000)
#define TMP_AXI_MONITOR_1_ADDR      (0xF7180000)
#define TMP_AXI_MONITOR_0_ADDR      (0xF5411000)
#define INTEGRATOR_SC_BASE_K ((unsigned int)map_address_sc)
#define AXI_MONITOR_1_ADDR  ((unsigned int)map_address_mon1)
#define AXI_MONITOR_0_ADDR  ((unsigned int)map_address_mon0)

/*SC中monitor寄存器使能与启动对应位,0x48c*/
#define AXI_MON0_ENABLE_BIT 4
#define AXI_MON1_ENABLE_BIT 1
#define AXI_MON0_START_BIT 14
#define AXI_MON1_START_BIT 8

/*寄存器读写*/
#define BSP_REG_BASE(base) (*(volatile unsigned int *)((unsigned int)base))
#define BSP_REG_READ_BASE(base,result) \
    ((result) = BSP_REG_BASE(base))

#define BSP_REG_WRITE_BASE(base, data) \
    (BSP_REG_BASE(base) = (data))
#define BSP_REG64(base) (*(volatile unsigned long long *)((unsigned int)base))
#define BSP_REG_READ64(base,result) \
        ((result) = BSP_REG64(base))

#define BSP_REG_WRITE64(base, data) \
    (BSP_REG64(base) = (data))

#define fprintf_axi(strem,format, args...)   \
        do{                                 \
                printk(format, ##args);    \
                taskDelay(1);\
        }while(0)

#define printk_axi(strem,format, args...)   \
        do{                                 \
                printk(format, ##args);    \
                msleep(1);\
        }while(0)


#define AXI_MONITOR_ADDR(base, offset)  ((base) + (offset))
/*****************************************************************************
  3 枚举定义
*****************************************************************************/

typedef enum{
    SOC_SEL_MON0,
    SOC_SEL_MON1,
    SOC_SEL_MAX,
}SOC_SEL;

typedef enum{
	SOC_SEL_DEFAULT=0,
	SOC_SEL_READ,
	SOC_SEL_WRITE,
	SOC_SEL_CNT_TYPE_MAX,
}SOC_CNT_TYPE;

/*****************************************************************************
  4 消息头定义
*****************************************************************************/


/*****************************************************************************
  5 消息定义
*****************************************************************************/


/*****************************************************************************
  6 STRUCT定义
*****************************************************************************/
typedef struct _monitor_param_
{
    unsigned int timeCycle;
    unsigned int timerMode;
    unsigned int axi_timerId;
    unsigned int monitorId;
    SOC_CNT_TYPE axi_mon_test_type;
    unsigned int loopMonitor;
}monitor_param;
/*****************************************************************************
  7 UNION定义
*****************************************************************************/

/*---------------------------SC 系统控制器 --------------------*/
/*axi monitor配置寄存器。Offset 0x48C,  0*/
union _union_sc_axi_monitor_{
    unsigned int sc_axi_monitor_reg;
    struct _sc_axi_monitor_{
        unsigned int :1;
        unsigned int amonitor1_en:1;
        unsigned int :1;
        unsigned int :1;
        unsigned int amonitor0_en:1;
        unsigned int :1;
        unsigned int :1;
        unsigned int :1;
        unsigned int amon1_monitor_start:1;
        unsigned int :1;
        unsigned int :1;
        unsigned int amon1_bypass_mask_port0:1;/*bit 11:GPU*/
        unsigned int :1;
        unsigned int amon1_bypass_mask_port1:1;/*bit 13:IMG*/
        unsigned int amon0_monitor_start:1;
        unsigned int amon0_bypass_mask_port0:1;/*bit 15:VIDEO*/
        unsigned int :1;
        unsigned int amon0_bypass_mask_port1:1;/*bit 17:MDM*/
        unsigned int reserved:14;
    }bits;
};
typedef volatile union _union_sc_axi_monitor_ sc_axi_monitor;
#define SC_AXI_MONITOR_ADDR       AXI_MONITOR_ADDR(INTEGRATOR_SC_BASE_K,0x48C)
/*---------------------------SC 系统控制器 end--------------------*/

/*--------------------------axi monitor registers start---------------------*/
/*CNT_RESET是axi monitor所有计数器的软复位寄存器。 offset 0x000 ,   0x00000000*/
union _union_cn_reset_{
    unsigned int cn_reset_reg;
    struct _cn_reset_{
        unsigned int reset_state:1;
        unsigned int soft_rst:1;
        unsigned int reserved:30;
    }bits;
};
typedef volatile union _union_cn_reset_ cn_reset;
#define CNT_RESET_ADDR(base) AXI_MONITOR_ADDR(base,0x000)

/*CNT_CTRL是axi monitor的系统配置寄存器。 0x004,  0x1FE0*/
union _union_cnt_ctrl_{
    unsigned int cnt_ctrl_reg;
    struct _cnt_ctrl_{
        unsigned int monitor_start:1;
        unsigned int win_enable:1;
        unsigned int win_finish_mask:1;
        unsigned int read_error_mask:1;
        unsigned int :1;
        unsigned int wait_mask_bypass_port0_r:1;
		unsigned int wait_mask_bypass_port0_w:1;
		unsigned int wait_mask_bypass_port1_r:1;
		unsigned int wait_mask_bypass_port1_w:1;
		unsigned int wait_mask_bypass_port2_r:1;
		unsigned int wait_mask_bypass_port2_w:1;
		unsigned int wait_mask_bypass_port3_r:1;
		unsigned int wait_mask_bypass_port3_w:1;
        unsigned int reserved:19;
    }bits;
};
typedef volatile union _union_cnt_ctrl_ cnt_ctrl;
#define CNT_CTRL_ADDR(base) AXI_MONITOR_ADDR(base,0x004)

/*CNT_STATE_INT是axi monitor的系统状态寄存器。 0x008,  0x00000000*/
union _union_cnt_state_int_{
    unsigned int cnt_state_int_reg;
    struct _cnt_state_int_{
        unsigned int win_finish:1;
        unsigned int read_error:1;
        unsigned int system_state:2;
        unsigned int soft_rst_ok:1;
        unsigned int reserved:27;
    }bits;
};
typedef volatile union _union_cnt_state_int_ cnt_state_int;
#define CNT_STATE_INT_ADDR(base) AXI_MONITOR_ADDR(base,0x008)

/*WIN_COUNTER是axi monitor的系统时间窗计数器。 0x00C, 0x0000*/
union _union_win_counter_{
    unsigned long long win_counter_reg;
    struct _win_counter_{
        unsigned long long win_counter:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_win_counter_ win_counter;
#define WIN_COUNTER_ADDR(base) AXI_MONITOR_ADDR(base,0x00C)

/*IDLE_COUNTER是axi monitor的系统idle统计计数器。 0x014,  0x0*/
union _union_idle_counter_{
    unsigned long long idle_counter_reg;
    struct _idle_counter_{
        unsigned long long idle_counter:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_idle_counter_ idle_counter;
#define IDLE_COUNTER_ADDR(base) AXI_MONITOR_ADDR(base,0x014)

/*CNT_PORT_SEL是axi_monitor的监控ID选择哪个AXI PORT, 0x01C, 0x00000000*/
union _union_port_sel_{
    unsigned int port_sel_reg;
    struct _port_sel_{
        unsigned int id1_port_sel:2;
        unsigned int id2_port_sel:2;
        unsigned int id3_port_sel:2;
        unsigned int id4_port_sel:2;
        unsigned int id5_port_sel:2;
        unsigned int id6_port_sel:2;
        unsigned int id7_port_sel:2;
        unsigned int id8_port_sel:2;
        unsigned int idle_port_sel:2;
        unsigned int reserved:14;
    }bits;
};
typedef volatile union _union_port_sel_ port_sel;
#define CNT_PORT_SEL_ADDR(base) AXI_MONITOR_ADDR(base,0x01C)

/*INT_CLR是axi_monitor的中断清除寄存器, 0x020, 0x00000000*/
union _union_int_clr_{
    unsigned int int_clr_reg;
    struct _int_clr_{
        unsigned int win_finish_clr:1;
        unsigned int read_error_clr:1;
        unsigned int reserved:14;
        unsigned int id1_wr_int_clr:1;
        unsigned int id1_rd_int_clr:1;
        unsigned int id2_wr_int_clr:1;
        unsigned int id2_rd_int_clr:1;
        unsigned int id3_wr_int_clr:1;
        unsigned int id3_rd_int_clr:1;
        unsigned int id4_wr_int_clr:1;
        unsigned int id4_rd_int_clr:1;
        unsigned int id5_wr_int_clr:1;
        unsigned int id5_rd_int_clr:1;
        unsigned int id6_wr_int_clr:1;
        unsigned int id6_rd_int_clr:1;
        unsigned int id7_wr_int_clr:1;
        unsigned int id7_rd_int_clr:1;
        unsigned int id8_wr_int_clr:1;
        unsigned int id8_rd_int_clr:1;
    }bits;
};
typedef volatile union _union_int_clr_ int_clr;
#define INT_CLR_ADDR(base) AXI_MONITOR_ADDR(base,0x020)

/*ID_INT_SRC是ID读,写监控中断原始寄存器,0x24,0x00000000*/
union _union_id_int_src_{
    unsigned int id_int_src_reg;
    struct _id_int_src_{
        unsigned int id1_wr_int_src:1;
        unsigned int id1_rd_int_src:1;
        unsigned int id2_wr_int_src:1;
        unsigned int id2_rd_int_src:1;
        unsigned int id3_wr_int_src:1;
        unsigned int id3_rd_int_src:1;
        unsigned int id4_wr_int_src:1;
        unsigned int id4_rd_int_src:1;
        unsigned int id5_wr_int_src:1;
        unsigned int id5_rd_int_src:1;
        unsigned int id6_wr_int_src:1;
        unsigned int id6_rd_int_src:1;
        unsigned int id7_wr_int_src:1;
        unsigned int id7_rd_int_src:1;
        unsigned int id8_wr_int_src:1;
        unsigned int id8_rd_int_src:1;
        unsigned int reserved:16;
    }bits;
};
typedef volatile union _union_id_int_src_ id_int_src;
#define ID_INT_SRC_ADDR(base) AXI_MONITOR_ADDR(base,0x024)

/*ID_INT_MASK是ID读，写监控中断屏蔽除寄存器,0x28,0x0000ffff*/
union _union_id_int_mask_{
    unsigned int id_int_mask_reg;
    struct _id_int_mask_{
        unsigned int id1_wr_int_mask:1;
        unsigned int id1_rd_int_mask:1;
        unsigned int id2_wr_int_mask:1;
        unsigned int id2_rd_int_mask:1;
        unsigned int id3_wr_int_mask:1;
        unsigned int id3_rd_int_mask:1;
        unsigned int id4_wr_int_mask:1;
        unsigned int id4_rd_int_mask:1;
        unsigned int id5_wr_int_mask:1;
        unsigned int id5_rd_int_mask:1;
        unsigned int id6_wr_int_mask:1;
        unsigned int id6_rd_int_mask:1;
        unsigned int id7_wr_int_mask:1;
        unsigned int id7_rd_int_mask:1;
        unsigned int id8_wr_int_mask:1;
        unsigned int id8_rd_int_mask:1;
        unsigned int reserved:16;
    }bits;
};
typedef volatile union _union_id_int_mask_ id_int_mask;
#define ID_INT_MASK_ADDR(base) AXI_MONITOR_ADDR(base,0x028)

/*ID_INT_STAT是ID读，写监控中断状态寄存器,0x2C,0x00000000*/
union _union_id_int_stat_{
    unsigned int id_int_stat_reg;
    struct _id_int_stat_{
        unsigned int id1_wr_int_stat:1;
        unsigned int id1_rd_int_stat:1;
        unsigned int id2_wr_int_stat:1;
        unsigned int id2_rd_int_stat:1;
        unsigned int id3_wr_int_stat:1;
        unsigned int id3_rd_int_stat:1;
        unsigned int id4_wr_int_stat:1;
        unsigned int id4_rd_int_stat:1;
        unsigned int id5_wr_int_stat:1;
        unsigned int id5_rd_int_stat:1;
        unsigned int id6_wr_int_stat:1;
        unsigned int id6_rd_int_stat:1;
        unsigned int id7_wr_int_stat:1;
        unsigned int id7_rd_int_stat:1;
        unsigned int id8_wr_int_stat:1;
        unsigned int id8_rd_int_stat:1;
        unsigned int reserved:16;
    }bits;
};
typedef volatile union _union_id_int_stat_ id_int_stat;
#define ID_INT_STAT_ADDR(base) AXI_MONITOR_ADDR(base,0x02C)

/*RD_WAIT_CYCLE_PORT是监控PORTs为精确定位读等待计数而消耗的时间周期寄存器。 0x30+0x10*ports, 0x00000000*/
union _union_rd_wait_cycle_ports_{
    unsigned long long rd_wait_cycle_ports_reg;
    struct _rd_wait_cycle_ports_{
        unsigned long long rd_wait_cycle_port:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_rd_wait_cycle_ports_ rd_wait_cycle_ports;
#define RD_WAIT_CYCLE_PORT_ADDR(base,ports) AXI_MONITOR_ADDR(base,(0x30+0x10*ports))

/*WR_WAIT_CYCLE_PORT是监控PORTs为精确定位写等待计数而消耗的时间周期寄存器。 0x38+0x10*ports, 0x00000000*/
union _union_wr_wait_cycle_ports_{
    unsigned long long wr_wait_cycle_ports_reg;
    struct _wr_wait_cycle_ports_{
        unsigned long long wr_wait_cycle_port:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_wr_wait_cycle_ports_ wr_wait_cycle_ports;
#define WR_WAIT_CYCLE_PORT_ADDR(base,ports) AXI_MONITOR_ADDR(base,(0x38+0x10*ports))

/*CNT_TYPE是监控ID的计数器监控类型选择, 0xb0+0x4*ids, 0x00000000*/
union _union_cnt_type_{
    unsigned int cnt_type_reg;
    struct _cnt_type_{
        unsigned int incr_type_incr1:1;
		unsigned int incr_type_incr2:1;
		unsigned int incr_type_incr4:1;
		unsigned int incr_type_incr8:1;
		unsigned int incr_type_incr16:1;
        unsigned int wrap_type:2;
        unsigned int burst_bype:1;
        unsigned int finish_type:1;
        unsigned int wr_wait_type:1;
        unsigned int reserved:22;
    }bits;
};
typedef volatile union _union_cnt_type_ cnt_type;
#define CNT_TYPE_ADDR(base,ids) AXI_MONITOR_ADDR((base),(0xb0+0x4*(ids)))

/*FPGA2_VERSION_NUM是Porting FPGA2 版本号, 0x0d0, 0x80000000*/
union _union_fpga2_version_num_{
    unsigned int fpga2_version_num_reg;
    struct _fpga2_version_num_{
        unsigned int fpga2_version_num:32;
    }bits;
};
typedef volatile union _union_fpga2_version_num_ fpga2_version_num;
#define FPGA2_VERSION_NUM_ADDR(base,ids) AXI_MONITOR_ADDR((base),0xd0)

/*CNT_ID是axi monitor的系统ID信息寄存器。, 0x100+0x100*ids, 0x80000000*/
union _union_cnt_id_{
    unsigned int cnt_id_reg;
    struct _cnt_id_{
        unsigned int cnt_id:15;
        unsigned int cnt_id_mask:15;
        unsigned int address_enable:1;
        unsigned int id_enable:1;
    }bits;
};
typedef volatile union _union_cnt_id_ cnt_id;
#define CNT_ID_ADDR(base,ids) AXI_MONITOR_ADDR((base),(0x100+0x100*(ids)))

/*ID_ADDR_DES是axi monitor系统希望监控的地址信息下边界, 0x104+0x100*ids*/
union _union_id_addr_des_{
    unsigned int id_addr_des_reg;
    struct _id_addr_des_{
        unsigned int id_addr_des:32;
    }bits;
};
typedef volatile union _union_id_addr_des_ id_addr_des;
#define ID_ADDR_DES_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x104+0x100*(ids)))

/*ID_ADDR_DES_M是axi monitor系统希望监控的地址信息上边界,配合address_enable信号使用，指示地址过滤的上边界
0x108+0x100*ids, 0x00000000*/
union _union_id_addr_des_m_{
    unsigned int id_addr_des_m_reg;
    struct _id_addr_des_m_{
        unsigned int id_addr_des_m:32;
    }bits;
};
typedef volatile union _union_id_addr_des_m_ id_addr_des_m;
#define ID_ADDR_DES_M_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x108+0x100*(ids)))

/*INCR1_ID是axi monitor统计监控ID号发出INCR1操作计数器。 0x110+0x100*ids, 0x0*/
union _union_incr1_id_{
    unsigned long long incr1_id_reg;
    struct _incr1_id_{
        unsigned long long cnt_id_incr1:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_incr1_id_ incr1_id;
#define INCR1_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x110+0x100*(ids)))

/*INCR2_ID是axi monitor统计监控ID号发出INCR2操作计数器。 0x118+0x100*ids, 0x0*/
union _union_incr2_id_{
    unsigned long long incr2_id_reg;
    struct _incr2_id_{
        unsigned long long cnt_id_incr2:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_incr2_id_ incr2_id;
#define INCR2_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x118+0x100*(ids)))

/*INCR4_ID是axi monitor统计监控ID号发出INCR4操作计数器。 0x120+0x100*ids, 0x0*/
union _union_incr4_id_{
    unsigned long long incr4_id_reg;
    struct _incr4_id_{
        unsigned long long cnt_id_incr4:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_incr4_id_ incr4_id;
#define INCR4_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x120+0x100*(ids)))

/*INCR8_ID是axi monitor统计监控ID号发出INCR8操作计数器。 0x128+0x100*ids, 0x0*/
union _union_incr8_id_{
    unsigned long long incr8_id_reg;
    struct _incr8_id_{
        unsigned long long cnt_id_incr8:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_incr8_id_ incr8_id;
#define INCR8_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x128+0x100*(ids)))

/*INCR16_ID是axi monitor统计监控ID号发出INCR16操作计数器。 0x130+0x100*ids, 0x0*/
union _union_incr16_id_{
    unsigned long long incr16_id_reg;
    struct _incr16_id_{
        unsigned long long cnt_id_incr16:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_incr16_id_ incr16_id;
#define INCR16_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x130+0x100*(ids)))

/*WRAP_ID是axi monitor统计监控ID号发出WRAP操作计数器。 0x160+0x100*ids, 0x0*/
union _union_wrap_id_{
    unsigned long long wrap_id_reg;
    struct _wrap_id_{
        unsigned long long cnt_id_wrap4_rd:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_wrap_id_ wrap_id;
#define WRAP_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x160+0x100*(ids)))

/*BURST_ID是axi monitor统计监控ID号发出burst操作计数器。 0x190+0x100*ids, 0x0*/
union _union_burst_id_{
    unsigned long long burst_id_reg;
    struct _burst_id_{
        unsigned long long cnt_id_burst:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_burst_id_ burst_id;
#define BURST_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x190+0x100*(ids)))

/*FINISH_ID是axi monitor统计监控ID号完成burst操作数器。 0x1A0+0x100*ids, 0x0*/
union _union_finish_id_{
    unsigned long long finish_id_reg;
    struct _finish_id_{
        unsigned long long cnt_id_finish:32;
        unsigned long long reserved:32;
    }bits;
};
typedef volatile union _union_finish_id_ finish_id;
#define FINISH_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1A0+0x100*(ids)))

/*READ_WAIT_ID是axi monitor统计监控ID号读等待周期计数器 0x1B8+0x100*ids, 0x0*/
union _union_read_wait_id_{
    unsigned long long read_wait_id_reg;
    struct _read_wait_id_{
        unsigned long long cnt_id_rd_wait:44;
        unsigned long long reserved:20;
    }bits;
};
typedef volatile union _union_read_wait_id_ read_wait_id;
#define READ_WAIT_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1B8+0x100*(ids)))

/*WRITE_WAIT_ID是axi monitor统计监控ID号写数据等待周期计数器 0x1C0+0x100*ids, 0x0*/
union _union_write_wait_id_{
    unsigned long long write_wait_id_reg;
    struct _write_wait_id_{
        unsigned long long cnt_id_wr_wait:44;
        unsigned long long reserved:20;
    }bits;
};
typedef volatile union _union_write_wait_id_ write_wait_id;
#define WRITE_WAIT_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1C0+0x100*(ids)))

/*WRITE_WAIT_RESP_ID是axi monitor统计监控ID号写响应等待周期计数器 0x1D0+0x100*ids, 0x0*/
union _union_write_wait_resp_id_{
    unsigned long long write_wait_resp_id_reg;
    struct _write_wait_resp_id_{
        unsigned long long cnt_id_wr_wait_2:44;
        unsigned long long reserved:20;
    }bits;
};
typedef volatile union _union_write_wait_resp_id_ write_wait_resp_id;
#define WRITE_WAIT_RESP_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1D0+0x100*(ids)))

/*READ_MAX_WAIT_ID是axi monitor统计监控ID号读最大等待周期计数器 0x1D8+0x100*ids , 0x0*/
union _union_read_max_wait_id_{
    unsigned int read_max_wait_id_reg;
    struct _read_max_wait_id_{
        unsigned int cnt_id_rd_max_wait:12;
        unsigned int reserved:20;
    }bits;
};
typedef volatile union _union_read_max_wait_id_ read_max_wait_id;
#define READ_MAX_WAIT_ID_ADDR(base, ids) AXI_MONITOR_ADDR((base),(0x1D8+0x100*(ids)))

/*WRITE_MAX_WAIT_ID是axi monitor统计监控ID号写数据最大等待周期计数器 0x1DC+0x100*ids, 0x0*/
union _union_write_max_wait_id_{
    unsigned int write_max_wait_id_reg;
    struct _write_max_wait_id_{
        unsigned int cnt_id_wr_max_wait:12;
        unsigned int reserved:20;
    }bits;
};
typedef volatile union _union_write_max_wait_id_ write_max_wait_id;
#define WRITE_MAX_WAIT_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1DC+0x100*(ids)))

/*WRITE_MAX_WAIT_RESP_ID是axi monitor统计监控ID号写响应最大等待周期计数器 0x1E4+0x100*ids, 0x0*/
union _union_write_max_wait_resp_id_{
    unsigned int write_max_wait_resp_id_reg;
    struct _write_max_wait_resp_id_{
        unsigned int cnt_id_wr_max_wait_resp:12;
        unsigned int reserved:20;
    }bits;
};
typedef volatile union _union_write_max_wait_resp_id_ write_max_wait_resp_id;
#define WRITE_MAX_WAIT_RESP_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1E4+0x100*(ids)))

/*READ_BYTES_ID是axi monitor统计监控ID号所有读数据总量以byte为单位, 0x1E8+0x100*ids, 0x0*/
union _union_read_bytes_id_{
    unsigned long long read_bytes_id_reg;
    struct _read_bytes_id_{
        unsigned long long cnt_id_rd_bytes:40;
        unsigned long long reserved:24;
    }bits;
};
typedef volatile union _union_read_bytes_id_ read_bytes_id;
#define READ_BYTES_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1E8+0x100*(ids)))

/*WRITE_BYTES_ID是axi monitor统计监控ID号所有写数据总量以byte为单位, 0x1F0+0x100*ids, 0x0*/
union _union_write_bytes_id_{
    unsigned long long write_bytes_id_reg;
    struct _write_bytes_id_{
        unsigned long long cnt_id_wr_bytes:40;
        unsigned long long reserved:24;
    }bits;
};
typedef volatile union _union_write_bytes_id_ write_bytes_id;
#define WRITE_BYTES_ID_AADR(base,ids) AXI_MONITOR_ADDR((base),(0x1F0+0x100*(ids)))

/*--------------------------axi monitor registers end---------------------*/

typedef struct _monitor_id_data_
{
	unsigned long  id;
	unsigned long port_sel;
	unsigned long monitor_id;
	unsigned long long read_bytes;
	unsigned long long write_bytes;
	cnt_type cnt_type_mon;
	burst_id burst_id_mon;
	wrap_id	  wrap_id_mon;
	incr1_id  incr1_id_mon;
	incr2_id  incr2_id_mon;
	incr4_id  incr4_id_mon;
	incr8_id  incr8_id_mon;
	incr16_id incr16_id_mon;
	finish_id finish_id_mon;
}monitor_id_data;

#define BALONG_MONITOR_REQUEST_IDS      (8)
typedef struct _monitor_output_data_
{
	unsigned long long cycles;
	unsigned long long win_counter[2];
	unsigned long long cycles_debug[2];
	monitor_id_data id_data[BALONG_MONITOR_REQUEST_IDS];
}monitor_output_data;


/*****************************************************************************
  8 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  9 全局变量声明
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
void BSP_Axi_Mon_Start(unsigned int id);
void BSP_Axi_Mon_Stop(unsigned int id);
int BSP_Axi_Mon_Config(unsigned int monitorId, SOC_CNT_TYPE ct);
void BSP_Axi_Print(unsigned int id);
void BSP_Axi_Mon_Reset(unsigned int monId);
int AXI_Wait_Monitor_Ready(unsigned int monitor_addr);
static void axi_monitor_cnt_type_set(unsigned long base_addr,  SOC_CNT_TYPE ct);
unsigned int BSP_Axi_Get_Module_Addr(unsigned int id);
void BSP_Axi_Mon_Active(void);
int printf_axi_m(const char *fmt, ...);
void BSP_AXI_Print_ToDDR_ID(monitor_id_data* id_data,unsigned long base_addr, unsigned long u32ID);
void BSP_AXI_Print_ToDDR(monitor_output_data* output_data,unsigned int modId);
void BSP_Axi_Mon_Dump_Isr(void);
int BSP_Axi_Mon_Dump_Task(void);
void Axi_Mon_Entry(unsigned int modId,SOC_CNT_TYPE rwType,unsigned int cycle,unsigned int timerId,unsigned int mode,unsigned int loopMode);
void Axi_Mon_Entry_Stop(void);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif/* end of axi_monitor.h */




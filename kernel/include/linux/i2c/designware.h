/*
 * designware.h - designware I2C driver header file
 *
 * Copyright (c) 2011
 */
 
#include <linux/pm_qos_params.h>

#ifndef __DESIGNWARE_H_
#define __DESIGNWARE_H_

#define ENABLE_DELAY_SDA		1
#define DISABLE_DELAY_SDA		0

struct dma_chan;
struct i2c_dw_data {
	bool (*dma_filter)(struct dma_chan *chan, void *filter_param);
	void *dma_rx_param;
	void *dma_tx_param;
#if defined(CONFIG_ARCH_K3V2) || defined(CONFIG_ARCH_HI6620)
	void (*init) (void);
	void (*exit) (void);
	void (*reset) (void);
	void (*delay_sda) (int enable);
	void (*reset_controller) (void);
#endif
	char *iomux_name;
	struct pm_qos_request_list pm_qos_req;
};


extern int debug_on;
#define pm_qos_debug_trace(id,msg...) do { \
	if (debug_on) { \
		printk(KERN_INFO "[i2c.%d][%s]:", id, __func__); \
		printk(msg); \
		printk("\n");\
	} \
} while (0)


#endif /* __DESIGNWARE_H_ */

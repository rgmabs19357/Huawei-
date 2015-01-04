#ifndef _HSAD_DEV_H_
#define _HSAD_DEV_H_
#include <linux/types.h>
extern int hsad_connectivity_get_gpio(char *name);
extern int hsad_get_bt_en(void);
extern int hsad_get_bt_wake_host(void);
extern int hsad_get_host_wake_bt(void);
extern int hsad_get_nfc_ven_id(void);
extern int hsad_get_nfc_irq_id(void);
extern int hsad_get_nfc_firm_dload_id(void);
extern int hsad_get_nfc_ven_valid_level(void);
extern bool hsad_get_nfc_clk_src(char *clk_src);

#endif /* _HSAD_DEV_H_ */

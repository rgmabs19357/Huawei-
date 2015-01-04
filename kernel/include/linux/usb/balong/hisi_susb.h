#ifndef __HISI_SUSB_H__
#define __HISI_SUSB_H__

#include <linux/clk.h>
#include <linux/notifier.h>
#include <linux/regulator/consumer.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/semaphore.h>
#include <linux/usb/balong/usb_charger.h>
#include <linux/wakelock.h>
#include <linux/workqueue.h>

#include <linux/pm_qos_params.h>

struct lm_device;

#ifdef _DRV_LLT_
#define STATIC
#else
#define STATIC    static
#endif

/* struct for reset */
struct hisi_rst {
    unsigned int addr;
    unsigned int value;
    unsigned int addr_stat;
    unsigned int stat;
    unsigned int udelay;/* us */
};

/* struct for diff platform*/
struct hiusb_info {
    struct clk *clk_usbotg_off;
    struct clk *clk_picophy;
    
    int vbus_pin;
    void (*set_vbus)(struct lm_device *,int);
    int phy_reset_pin;
    int switch_pin1;
    int switch_pin2;
    int switch_id_pin;
    int cdma_usb_enable;
    int otg_int_gpio;
    int otg_without_mhl;

    int insert_irq;
    int draw_irq;

    struct iomux_block *usb_block;
    struct block_config *usb_config;

    struct semaphore hiusb_info_sema;
    spinlock_t switch_lock;
    struct wake_lock dev_wakelock;
#define HOST_WAKELOCK_TIMEOUT   (5*HZ)
    struct wake_lock host_wakelock;   
    struct delayed_work otg_intr_work;

#define CHARGER_INSERT  0
#define CHARGER_DRAW    1
#define ID_FALL_EVENT   2
#define ID_RISE_EVENT   3
    int intr_flag;
    spinlock_t intr_flag_lock;

    /* linux/usb/balong/usb_charger.h */
    int charger_type;
    struct atomic_notifier_head charger_type_notifier_head;

#define HIUSB_OFF       0
#define HIUSB_DEVICE    1
#define HIUSB_HOST      2
#define HIUSB_SUSPEND   3
    int hiusb_status;
    int gadget_enable;

#define HIUSB_QUIRKS_CHARGER      0x00000001
#define HIUSB_QUIRKS_PMUIRQ       0x00000002
    int quirks;
    
    struct lm_device *lm_dev;
    
    struct pm_qos_request_list pm_qos_req;

    int (*init_phase1)(struct lm_device *);
    int (*init_phase2)(struct lm_device *);
    int (*remove)(struct lm_device *);
    int (*pullup)(struct lm_device *,int);
    int (*suspend)(struct lm_device *);
    int (*resume)(struct lm_device *);

    void (*acpu_idle_add_request)(struct lm_device *);
    void (*acpu_idle_remove_request)(struct lm_device *);
};

int get_charger_name(void);
int hiusb_charger_registe_notifier(struct notifier_block *nb);
int hiusb_charger_unregiste_notifier(struct notifier_block *nb);
int hiusb_id_changed(int flag);
int switch_reset(void);
int switch_usb(void);
int switch_mhl(void);
int switch_cdma(void);
int switch_off(void);
int id_state(void);
int dwc_dev_insert_init(struct lm_device *);
int dwc_host_insert_init(struct lm_device *);
void dwc_dev_draw_init(struct lm_device *);
void dwc_host_draw_init(struct lm_device *);
void dwc_otg_set_hibernation(struct lm_device *, int);
void hiusb_hibernation_init(void);
int hiusb_is_host_mode(struct lm_device *);
int dwc_pm_runtime_enable(struct lm_device *);
int dwc_pm_runtime_disable(struct lm_device *);

#endif

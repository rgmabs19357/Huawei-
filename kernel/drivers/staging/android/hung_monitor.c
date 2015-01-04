#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/reboot.h>
#include <linux/string.h>
#include <linux/notifier.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include <linux/kthread.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define STATE_LEN_MAX (64)

#define INIT_RC_PATH "/init.rc"

#define SUCESS_TIME (9*HZ)
#define KERNEL_TIME (15*HZ)
#define NATIVE_TIME (60*HZ)
#define FRAMEWORK_TIME (120*HZ)
#define MAINAPP_TIME (11*HZ)
#define BOOT_TIME (KERNEL_TIME+NATIVE_TIME+FRAMEWORK_TIME+MAINAPP_TIME)
#define MAGIC_REMAIN (-2345)


enum BD_CMD{
    MACH_START = 0,         /* bootupd started */
    NATIVE_EARLY_INIT = 1,  /* init trigger the early init action */
    SERVICE_START = 2,      /* At the start of ServerThread executing */
    MAINAPP_FOUNDED = 3,    /* start home activity in ams */
    BOOT_SUCESS = 4,        /* sys.boot_completed is set */
    PAUSE,                  /* stop bootupd monitor */
    RESUME,                 /* resume bootupd monitor */
    STOP,                   /* stop bootupd */
    REBOOT,                 /* reboot system to show message */
    CMD_MAX
};

struct cmd_map {
    int cmd;
    char *name;
} cmd_maps[] = {
    {MACH_START,        "MACH_START"},
    {NATIVE_EARLY_INIT, "NATIVE_EARLY_INIT"},
    {SERVICE_START,     "SERVICE_START"},
    {MAINAPP_FOUNDED,   "MAINAPP_FOUNDED"},
    {PAUSE,             "PAUSE"},
    {RESUME,            "RESUME"},
    {STOP,              "STOP"},
    {BOOT_SUCESS,       "BOOT_SUCESS"},
};

struct state_cmd {
    struct list_head list;
    int cmd;
    unsigned long stamp;
};

int bootupd_init = false;
struct bootup_daemon {
    int                 paused;
    int                 stoped;
    int                 state;
    struct timer_list   success_timer;
    struct timer_list   main_timer;
    unsigned long       boot_start;
    unsigned long       last_resume;
    unsigned long       boot_remain;
    struct task_struct *bd_thread;
    spinlock_t          list_lock;      /* spin lock for protect cmd_list */
    struct list_head    cmd_list;       /* cmd list */
    wait_queue_head_t    cmd_event;     /* wait queue for looper */
} bootupd;


extern unsigned int get_boot_into_recovery_flag(void);
extern int  write_reboot_type( const char *cmd );
static void bd_exit(struct bootup_daemon *this);
static void bd_reset(struct bootup_daemon *this, int duration);

/* now we dont support panic detected */
/*static int bd_panic_cb(struct notifier_block *this, unsigned long event, void *ptr)
  {
  pr_warning("[bootupd]: ##############################################\n");
  pr_warning("[bootupd]: #      bootupd detected panic when boot [%d]  \n", bootupd.state);

*//* in panic, the system is failed , do nothing */
/* write reboot type to SECRAM_RESET_ADDR */
/*write_reboot_type("hungdetect");
  return NOTIFY_DONE;
  }

  static struct notifier_block panic_blk = {
  .notifier_call    = bd_panic_cb,
  };*/

static void bd_send_cmd_ptr(struct bootup_daemon *this, struct state_cmd * cmd_ptr)
{
    unsigned long flags;

    cmd_ptr->stamp = jiffies;
    spin_lock_irqsave(&this->list_lock, flags);
    list_add_tail(&cmd_ptr->list, &this->cmd_list);
    wake_up(&this->cmd_event);
    spin_unlock_irqrestore(&this->list_lock, flags);
}

#define TRIGGER_ON "on"
#define TRIGGER_SERVICE "service"
static int check_init_rc(struct bootup_daemon *this) 
{
    struct file *fp;
    int ret = -EINVAL;
    mm_segment_t oldfs;
    char *buf_ptr = NULL;
    char *line_ptr = NULL;
    int read_len = 0;
    int prop_find = false;
    int line_remain = 0;
    int sucess_find = false;
    int find_end = false;
    char *line_trim = NULL; 

    buf_ptr = kzalloc(PAGE_SIZE, GFP_KERNEL);
    if (NULL == buf_ptr) {
        ret = -ENOMEM;
        goto alloc_return;
    }

    line_ptr = kzalloc(PAGE_SIZE, GFP_KERNEL);
    if (NULL == line_ptr) {
        ret = -ENOMEM;
        goto alloc_return;
    }

    oldfs = get_fs();
    set_fs(KERNEL_DS);

    fp = filp_open(INIT_RC_PATH, O_RDONLY, 0);
    if (IS_ERR(fp)) {
        pr_warning("[bootupd]: open %s failed\n", INIT_RC_PATH);
        ret = PTR_ERR(fp);
        goto fs_return;
    }

    if (NULL == fp->f_op->read) {
        ret = -EIO;
        goto close_return;
    }

    while (!sucess_find && !find_end) {
        int i = 0;

        read_len = fp->f_op->read(fp, (char*)buf_ptr, PAGE_SIZE - 1, &fp->f_pos);
        if (read_len <= 0) {
            find_end = true;
            goto line_process;
        }


        for (i = 0; i < read_len; i++) {
            if (buf_ptr[i] != '\xa') {
                if (line_remain >= PAGE_SIZE) {
                    pr_warning("[bootupd]: num char of this line too long, discard!\n");
                } else {
                    line_ptr[line_remain++] = buf_ptr[i];
                }

                continue;
            }

line_process:
            /* come here, process line */
            line_ptr[line_remain] = '\0';
            line_trim = skip_spaces(line_ptr);

            if (line_trim[0]=='\0' || line_trim[0]=='#') {
                line_remain = 0;
                continue;
            }

            if (!strncmp(line_trim, TRIGGER_ON, strlen(TRIGGER_ON)) 
                    || !strncmp(line_trim, TRIGGER_SERVICE, strlen(TRIGGER_SERVICE))) {
                /* pr_warning("[bootupd]: find trigger %s\n", line_trim); */
                if (strstr(line_trim, "sys.boot_completed=1")) {
                    pr_info("[bootupd]: find prop boot_completed\n");
                    prop_find = true;
                } else {
                    prop_find =  false;
                }
            } else if (prop_find == true) {
                if (strstr(line_trim, "BOOT_SUCESS")) {
                    pr_info("[bootupd]: find BOOT_SUCESS \n");
                    sucess_find = true;
                    ret = 0;
                    break;
                }

            }

            line_remain = 0;

        }
    }


close_return:
    filp_close(fp, NULL);
fs_return:
    set_fs(oldfs);

alloc_return:
    if (buf_ptr) kfree(buf_ptr);
    if (line_ptr) kfree(line_ptr);

    return ret;
}

static int bd_send_cmd(struct bootup_daemon *this, int cmd)
{
    struct state_cmd * cmd_ptr = NULL;

    cmd_ptr = kzalloc(sizeof(struct state_cmd), GFP_KERNEL);
    if (!cmd_ptr) {
        pr_warning("[bootupd]: malloc state_cmd failed %d", cmd);
        return ENOMEM;
    }
    cmd_ptr->cmd = cmd;
    INIT_LIST_HEAD(&cmd_ptr->list);
    bd_send_cmd_ptr(this, cmd_ptr);

    return 0;
}

static int bd_change_to_state(struct bootup_daemon *this, int new_state)
{
    int old_state = this->state;

    this->state = new_state;

    pr_info("[bootupd]: change to state From %d to %d\n", old_state, this->state);

    return old_state;
}

static void bd_service_start(struct bootup_daemon *this, struct state_cmd *cmd_ptr)
{
    pr_info("[bootupd]: bd_service_start\n");
    bd_reset(this, FRAMEWORK_TIME+MAINAPP_TIME);
    bd_change_to_state(this, SERVICE_START);

    return ;
}

static void bd_mainapp_founded(struct bootup_daemon *this,struct state_cmd *cmd_ptr)
{ 
    pr_info("[bootupd]: mainapp_founded set success_timer\n");
    /*bd_reset(this, MAINAPP_TIME);
      mod_timer(&this->success_timer, jiffies+SUCESS_TIME);*/
    bd_change_to_state(this, MAINAPP_FOUNDED);

    return ;
}

static void bd_boot_success(struct bootup_daemon *this)
{
    pr_info("[bootupd]: boot sucess \n");
    this->boot_remain=(unsigned long)MAGIC_REMAIN;
    del_timer(&this->main_timer);
    del_timer(&this->success_timer);
    bd_change_to_state(this, MAINAPP_FOUNDED);
    /* atomic_notifier_chain_unregister(&panic_notifier_list, &panic_blk); */

    return ;
}

static void bd_reset(struct bootup_daemon *this, int duration)
{
    /*pr_info("[bootupd]: bd reset boot_remain %d,last_resume %d, duration %d \n", 
            this->boot_remain, this->last_resume, duration);*/
    if (this->boot_remain == (unsigned long)MAGIC_REMAIN) {
        this->boot_remain = duration;
    } else if (!this->paused) {
        unsigned long t = jiffies - this->last_resume;
        this->boot_remain = (this->boot_remain < t)?0:this->boot_remain-t; 
    } else {
        ;
    }

    this->paused = false;
    this->last_resume = jiffies;

    pr_info("[bootupd]: bd reset 2 boot_remain %lu,last_resume %lu\n", 
            this->boot_remain, this->last_resume);
    del_timer(&this->success_timer);
    mod_timer(&this->main_timer, jiffies+this->boot_remain);

    return;
}

static void bd_pause(struct bootup_daemon *this)
{
    unsigned long t;
    /*pr_info("[bootupd]: bd reset boot_remain %d,last_resume %d\n", 
            this->boot_remain, this->last_resume);*/

    if (this->boot_remain==MAGIC_REMAIN) {
        pr_warning("[bootupd]: pause remain time is invalidate!\n");
        return;
    }

    this->paused = true;
    t = jiffies - this->last_resume;
    this->boot_remain = (this->boot_remain < t)?0:this->boot_remain-t; 
    this->last_resume = jiffies;

    del_timer(&this->main_timer);

    pr_info("[bootupd]: bd reset 2 boot_remain %lu,last_resume %lu\n", 
            this->boot_remain, this->last_resume);
    return;
}

static void bd_resume(struct bootup_daemon *this)
{
    /*pr_info("[bootupd]: bd reset boot_remain %d,last_resume %d\n", 
            this->boot_remain, this->last_resume);*/

    if (!this->paused) {
        pr_warning("[bootupd]: current state is not paused!\n");
        return;
    }

    if (this->boot_remain==MAGIC_REMAIN) {
        pr_warning("[bootupd]: resume remain time is invalidate!\n");
        return;
    }


    this->paused = false;
    this->last_resume = jiffies;

    mod_timer(&this->main_timer, jiffies + this->boot_remain);

    pr_info("[bootupd]: bd reset 2 boot_remain %lu,last_resume %lu\n", 
            this->boot_remain, this->last_resume);

    return;
}

static void bd_stop(struct bootup_daemon *this) 
{
    pr_info("[bootupd]: bd stop");

    if ( !this->stoped ) {
        this->stoped = true;
    }

    del_timer(&this->success_timer);
    del_timer(&this->main_timer);
    /* atomic_notifier_chain_unregister(&panic_notifier_list, &panic_blk); */
}

static void bd_reboot(struct bootup_daemon *this)
{
    pr_warning("[bootupd]: ##############################################\n");
    pr_warning("[bootupd]: #      bootupd detected failed when boot [%d]     \n", bootupd.state);

    kernel_restart("hungdetect");
}

static int bd_process_cmd(struct bootup_daemon * this, struct state_cmd *cmd_ptr)
{
    pr_info("[bootupd]: loop stoped=%d paused=%d current=%d cmd=%d \n", 
            this->stoped, this->paused, this->state, cmd_ptr->cmd);
    if (this->stoped) {
        return -1;
    }

    switch (cmd_ptr->cmd) {
        case MACH_START:
            bd_change_to_state(this, cmd_ptr->cmd);
            break;
        case NATIVE_EARLY_INIT:
            bd_reset(this, NATIVE_TIME+FRAMEWORK_TIME+MAINAPP_TIME);
            bd_change_to_state(this, cmd_ptr->cmd);
            break;
        case SERVICE_START:
            bd_service_start(this, cmd_ptr);
            break;
        case MAINAPP_FOUNDED:
            bd_mainapp_founded(this, cmd_ptr);
            break;
        case BOOT_SUCESS:
            bd_boot_success(this);
            break;
        case PAUSE:
            bd_pause(this);
            break;
        case RESUME:
            bd_resume(this);
            break;
        case STOP:
            bd_stop(this);
            break;
        case REBOOT:
            bd_reboot(this);
            break;
        default:
            pr_info("[bootupd]: invalidate cmd \n" );
            break;

    }

    return 0;
}

/* bdthread main function, loop for cmd process */
static int bd_thread_main(void *data)
{
    struct bootup_daemon *this = data;
    struct list_head *entry = NULL;
    struct state_cmd *cmd = NULL;
    unsigned long flags;

    while (!kthread_should_stop() || !list_empty(&this->cmd_list)) {

        wait_event_interruptible(this->cmd_event,
                !list_empty(&this->cmd_list) ||
                kthread_should_stop());

        if (list_empty(&this->cmd_list))
            continue;

        spin_lock_irqsave(&this->list_lock, flags);
        entry = this->cmd_list.next;
        list_del(entry);
        spin_unlock_irqrestore(&this->list_lock, flags);

        cmd = list_entry(entry, struct state_cmd, list);
        if (cmd) {
            bd_process_cmd(this, cmd);
            kfree(cmd);
        }
    }

    return 0;
}

static void bd_main_timer_handler(unsigned long dev_addr)
{
    struct bootup_daemon *this = (struct bootup_daemon *)dev_addr;

    pr_info("[bootupd]: mainapp timer handler timeout state %d", this->state); 

    bd_send_cmd(this, REBOOT);
}

static void bd_sucess_handler(unsigned long dev_addr)
{
    struct bootup_daemon *this = (struct bootup_daemon *)dev_addr;

    pr_info("[bootupd]: sucess timer handler timeout"); 
    if ( this->state==MAINAPP_FOUNDED ) {
        /* reboot to recovery */
        bd_send_cmd(this, BOOT_SUCESS);
    } else {
        pr_info("[bootupd]: in state %d received sucess timeout", this->state);
    }
}

static int bd_parse_state(char *val, char *casue)
{
    int i = 0;
    int cmd = -1;
    int max = sizeof(cmd_maps)/sizeof(struct cmd_map);

    for( ; i<max; i++ ) {
        if ( !strcmp(cmd_maps[i].name, val) ) {
            cmd = cmd_maps[i].cmd;
            break;
        }
    }

    /* pr_info("[bootupd]: br_parse_state %d", cmd); */
    return cmd;
}


int bootupd_param_set(const char *val, const struct kernel_param *kp)
{
    char state_str[STATE_LEN_MAX] = {0};
    char cause_str[STATE_LEN_MAX] = {0};
    char * separator_ptr = NULL;
    int cmd = -1;
    struct bootup_daemon *this = &bootupd;

    /* check our bootup daemon is initialized */
    if (!bootupd_init) {
        pr_info("[bootupd]: bootupd is not started, do nothing\n");
        return 0;
    }

    if (val == NULL || val[0] == '\0' ) {
        pr_info("[bootupd]: state string is null\n");
        return 0;
    }

    strncpy(state_str, val, STATE_LEN_MAX-1);
    state_str[STATE_LEN_MAX-1]='\0';
    separator_ptr = strchr(state_str, ':');
    if (separator_ptr != NULL) {
        /* cause str is alse buffer safe */
        strncpy(cause_str, separator_ptr+1, STATE_LEN_MAX-1);
        *separator_ptr = '\0';
    }

    pr_info("[bootupd]: param_set state %s cause %s\n", state_str, cause_str);
    cmd = bd_parse_state(state_str, cause_str);

    if (cmd != -1) {
        bd_send_cmd(this,cmd);
    } else {
        pr_warning("[bootupd]: invalidate state string %s > %s", state_str, cause_str);
    }

    return 0;
}

static void bd_exit(struct bootup_daemon *this)
{
    pr_info("[bootupd]: do exit\n");
    del_timer(&this->main_timer);
    del_timer(&this->success_timer);

    /* atomic_notifier_chain_unregister(&panic_notifier_list, &panic_blk); */

    if (this->bd_thread) {
        kthread_stop(this->bd_thread);
        this->bd_thread = NULL;
    }
}


static int bd_init(struct bootup_daemon *this, int duration)
{
    int error = 0;

    pr_info("[bootupd]: do init duration(%d)\n", duration);

    /* initialize main timer */
    this->boot_start = jiffies;
    this->last_resume = this->boot_start;
    this->boot_remain = duration;
    init_timer(&this->main_timer);
    this->main_timer.function = bd_main_timer_handler;
    this->main_timer.expires = jiffies + this->boot_remain;
    this->main_timer.data = (unsigned long)this;

    add_timer(&this->main_timer);

    /* initialize success timer */
    init_timer(&this->success_timer);
    this->success_timer.function = bd_sucess_handler;
    this->success_timer.expires = jiffies + SUCESS_TIME;
    this->success_timer.data = (unsigned long)this;

    /* initialize other */
    this->paused = 0;
    this->stoped = 0;
    this->state = MACH_START;

    /* catch panic when system is not ready, reset to fastboot mode */
    /* atomic_notifier_chain_register(&panic_notifier_list, &panic_blk); */


    INIT_LIST_HEAD(&this->cmd_list);
    init_waitqueue_head(&this->cmd_event);
    this->list_lock = SPIN_LOCK_UNLOCKED;
    /* start bootupd thread */
    this->bd_thread = kthread_create(bd_thread_main, this, "bdthread");
    if (IS_ERR(this->bd_thread)) {
        error = PTR_ERR(this->bd_thread);
        pr_warning("[bootupd]: start bootd thread failed(%d)\n", error);
        goto out_clr;
    }

    wake_up_process(this->bd_thread);

    return error;

out_clr:
    del_timer(&this->main_timer);
    /* atomic_notifier_chain_unregister(&panic_notifier_list, &panic_blk); */
    return error;
}


struct kernel_param_ops param_ops_state = {
    .set = bootupd_param_set
};

static int __init hung_monitor_init(void)
{
    // TODO check charger status or recovery status too
    if (get_boot_into_recovery_flag()) {
        pr_info("[bootupd]: init in recovery, do nothing\n");
        return 0;
    }

    pr_info("[bootupd]: check init rc start\n");
    /* if init.rc is tampered, cancel to start */
    if (0 != check_init_rc(&bootupd)) {
        pr_warning("[bootupd]: init.rc is changed, do nothing\n");
        return 0;
    }
    pr_info("[bootupd]: check init rc end\n");

    bootupd_init = true;

    bd_init(&bootupd, BOOT_TIME);
    return 0;
}

module_init(hung_monitor_init);

static void __exit hung_monitor_exit(void)
{
    /* check our bootup daemon is initialized */
    if (!bootupd_init) {
        pr_info("[bootupd]: exit in recovery, do nothing\n");
        return;
    }

    bd_exit(&bootupd);
}

module_exit(hung_monitor_exit);

module_param_cb(state, &param_ops_state, NULL, 0664);
MODULE_PARM_DESC(state, "set state for hung_monitor");

MODULE_LICENSE("GPL");

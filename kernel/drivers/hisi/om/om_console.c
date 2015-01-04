/* Copyright (c) 2008-2011, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 *  virtual_con.c  hisi virtua console driver, to make a copy of console output to SDT
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 */
#include <linux/module.h>			/* For module specific items */
#include <linux/moduleparam.h>		/* For new moduleparam's */
#include <linux/types.h>			/* For standard types (like size_t) */
#include <linux/errno.h>			/* For the -ENODEV/... values */
#include <linux/kernel.h>			/* For printk/... */
#include <linux/watchdog.h>			/* For the watchdog specific items */
#include <linux/init.h>				/* For __init/__exit/... */
#include <linux/fs.h>				/* For file operations */
#include <linux/console.h>			/* For register_console/unregister_console */
#include <linux/workqueue.h>		/* For workqueue... */
#include <linux/hardirq.h>			/* For in_interrupt() */
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <mach/util.h>
#include <BSP.h>

extern BSP_S32 BSP_MNTN_OmDrvTraceSend(BSP_U16 usPrimId, BSP_U32 ulModuleId, BSP_U8 *buffer, BSP_U32 ulLength);

#define CONSOLE_BUFF_LEN 5120

static struct work_struct om_console_work;
static struct workqueue_struct *om_console_work_queue;

static DEFINE_SPINLOCK(buffer_lock);

static char buffer[CONSOLE_BUFF_LEN];
static unsigned int head = 0;
static unsigned int tail = 0;

static atomic_t om_console_omit_bytes = ATOMIC_INIT(0);
static atomic_t om_console_output_bytes = ATOMIC_INIT(0);

#define cursor_move(cursor, bytes) ((cursor + bytes)%(CONSOLE_BUFF_LEN))

#if 0
static void om_console_do_work(struct work_struct *work)
{
	unsigned int output = 0;
	unsigned long flags = 0;
	unsigned int head_snap;

	do {
		spin_lock_irqsave(&buffer_lock, flags);
		tail = cursor_move(tail, output);
		if (tail == head){ /*no buffer to output, leave the task*/
			spin_unlock_irqrestore(&buffer_lock, flags);
			break;
		}
		head_snap = head;
		spin_unlock_irqrestore(&buffer_lock, flags);

		/*calc the size to output this round*/
		if (head_snap < tail){
			output = CONSOLE_BUFF_LEN - tail;
		}else{
			output = head_snap - tail;
		}

		/*send to OM, update the tail cursor*/
		BSP_MNTN_OmDrvTraceSend(0, 0, buffer + tail, output);
	} while (1);


	return;
}
#endif

/*****************************************************************************
 Description : console output write to OM
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static void write_msg(struct console *con, const char *msg, unsigned int len)
{
	unsigned long flags = 0;
	unsigned int free = 0;
	unsigned int output = 0;
	unsigned int left = 0;
	unsigned int trigger = 0;

	/*in hard/soft irq context*/
	if (unlikely(in_interrupt())){
		spin_lock_irqsave(&buffer_lock, flags);

		free = (tail + CONSOLE_BUFF_LEN - head - 1)%CONSOLE_BUFF_LEN; /*free buffer space*/
		output = min(free, len); /*output bytes*/

		/*copy data to ring buffer */
		left = CONSOLE_BUFF_LEN - head;
		if (output > left){
			memcpy(buffer + head, msg, left);
			memcpy(buffer, msg + left, output - left);
		}else{
			memcpy(buffer + head, msg, output);
		}

		if (head == tail){
			trigger = 1;
		}
		head = cursor_move(head, output);
		spin_unlock_irqrestore(&buffer_lock, flags);

		if (1 == trigger){
			queue_work_on(0, om_console_work_queue, &om_console_work);
		}
	}else{
		output = len;
		/*in other context, output to OM directly*/
		BSP_MNTN_OmDrvTraceSend(0, 0, (BSP_U8 *)msg, output);
	}

	atomic_add(output, &om_console_output_bytes);
	atomic_add(len - output, &om_console_omit_bytes);

	return;
}

/*virtual console struct definiton */
static struct console om_console = {
	.name = "om_console",
	.flags = CON_ENABLED,
	.write = write_msg,
};

/*om console debug info show*/
static int om_console_proc_show(struct seq_file *m, void *v)
{
	unsigned int omitbytes = atomic_read(&om_console_omit_bytes);
	unsigned int outputbytes = atomic_read(&om_console_output_bytes);

	seq_printf(m, "om console : \n");
	seq_printf(m, "output bytes %d\n", outputbytes);
	seq_printf(m, "omit bytes %d\n", omitbytes);

	return 0;
}

static int om_console_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, om_console_proc_show, NULL);
}

static const struct file_operations om_console_proc_fops = {
	.open = om_console_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

#if 0
/*****************************************************************************
 Description : virtual console initial, register to console system
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static int __init om_console_init(void)
{
	INIT_WORK(&om_console_work, om_console_do_work);

	balong_create_debug_proc_entry("omconsole", S_IRUGO, &om_console_proc_fops, NULL);

	om_console_work_queue = create_singlethread_workqueue("om_console");
	if (NULL == om_console_work_queue){
		printk(KERN_ERR"failed to create workqueue\n");
		return -ESRCH;
	}

	register_console(&om_console);

	return 0;
}
/*module_init(om_console_init);*/
#endif 

/*****************************************************************************
 Description : virtual console initial, register to console system
  History
  1.Date: 2012/9/13
    Author : x00138766
    Modification : Created function
*****************************************************************************/
static void __exit om_console_exit(void)
{
	unregister_console(&om_console);

	return;
}
module_exit(om_console_exit);

MODULE_DESCRIPTION("Hisilicon OM Console Driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");


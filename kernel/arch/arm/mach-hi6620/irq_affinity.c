/*
 *  arch/arm/mach-hi660/irq_affinity.c
 *
 *  Copyright (C) 2011 Hisilicon Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/errno.h>
#include <linux/device.h>
#include <linux/smp.h>
#include <linux/cpumask.h>
#include <linux/notifier.h>
#include <linux/interrupt.h>
#include <linux/cpu.h>
#include <asm/irq.h>
#include <mach/irqs.h>
#include <mach/util.h>
#include <linux/seq_file.h>
#include <hsad/config_mgr.h>
#include <linux/suspend.h>
#include <mach/irqs.h>

#define IRQ_AFFINITY_PROCNAME_SIZE 32

/*irq affinity key prefix in hw config xml*/
static char *irq_affinity_key_prefix = "irq_affinity/irq%d";

/*record the cpu id of the irq*/
static int irq_affinity_records[NR_SOC_IRQS];

/*restore irq affinity when cpu up*/
static void irq_affinity_cpu_up(unsigned int cpu)
{
	unsigned int i;
	int ret = 0;

	/*skip cpu 0, default is cpu 0*/
	if (0 == cpu)
		return;

	for (i = 0; i < NR_SOC_IRQS; i++)
	{
		if (cpu != irq_affinity_records[i])
			continue;

		/*restore the irq affinity*/
		ret = irq_set_affinity(i, cpumask_of(cpu));
		if (ret)
			printk(KERN_ERR"%s %d : fail to restore IRQ %d on CPU %d error %d\n",
		            __FUNCTION__, __LINE__, i, cpu, ret);
	}

	return;
}

static int cpu_up_notify(struct notifier_block *nfb,
                    unsigned long status, void *cpuid)
{
	unsigned int cpu = (unsigned int)cpuid;

	switch(status)
	{
		case CPU_ONLINE:
			irq_affinity_cpu_up(cpu);
			break;
		default:
		/*just pass other event*/
		break;
	}

	return NOTIFY_DONE;
}

static struct notifier_block __refdata cpu_up_notifier = {
	.notifier_call = cpu_up_notify,
	.priority = INT_MIN
};

static void irq_affinity_post_suspend(void)
{
	unsigned int i;
	int ret = 0;
	int cpu;

	for (i = 0; i < NR_SOC_IRQS; i++)
	{
		if (0 == irq_affinity_records[i])
			continue;

		cpu = irq_affinity_records[i];
		
    	if(cpu_online(cpu))
    	{
    		ret = irq_set_affinity(i, cpumask_of(cpu));
    		if (ret)
    			printk(KERN_ERR"%s %d : fail to restore IRQ %d on CPU %d error %d\n",
    		        __FUNCTION__, __LINE__, i, cpu, ret);
		}
	}

	return;
}

static int post_suspend_notify(struct notifier_block *notify_block,
					unsigned long mode, void *unused)
{
	switch (mode)
	{
		case PM_POST_SUSPEND:
			irq_affinity_post_suspend();
			break;
		default:
			break;
	}

	return NOTIFY_DONE;
}

static struct notifier_block __refdata post_suspend_notifier = {
	.notifier_call = post_suspend_notify,
	.priority = INT_MIN
};

#ifdef CONFIG_SYSCTL
static struct ctl_path balong_irq_affinity_path[] = {
	{ .procname = "balong", },
	{ .procname = "irq_affinity", },
	{ },
};
#endif

static int min_cpu_id = 0;
static int max_cpu_id = 1;

static void irq_affinity_register_sysctl_table(unsigned int irq, int cpu)
{
	struct ctl_table *table;
	char *procname;
	struct ctl_table_header *head;

	table = (struct ctl_table *)kmalloc(sizeof(struct ctl_table)*2, GFP_KERNEL);
	if (NULL == table)
	{
		printk(KERN_ERR"%s %d failed to kmalloc \r\n", __FUNCTION__,__LINE__);
		return;
	}
	memset(table, 0, sizeof(struct ctl_table)*2);

	procname = (char *)kmalloc(IRQ_AFFINITY_PROCNAME_SIZE, GFP_KERNEL);
	if (NULL == procname)
	{
		kfree(table);
		printk(KERN_ERR"%s %d failed to kmalloc \r\n", __FUNCTION__,__LINE__);
		return;
	}

	snprintf(procname, IRQ_AFFINITY_PROCNAME_SIZE, "%d", irq);
	table[0].procname = procname;
	table[0].data = &irq_affinity_records[irq];
	table[0].maxlen = sizeof(int);
	table[0].mode = 0644;
	table[0].proc_handler = proc_dointvec_minmax;
	table[0].extra1 = &min_cpu_id;
	table[0].extra2 = &max_cpu_id;

	head = register_sysctl_paths(balong_irq_affinity_path, table);
	if (NULL == head)
		printk(KERN_ERR "%s %d : failed to irq_affinity_register_sysctl_table %d\r\n",
			__FUNCTION__, __LINE__, irq);

	return;
};

static void irq_affinity_init(struct work_struct *dummy)
{
	int ret, cpu, i;
	char irq_affinity_key[48];

	memset(irq_affinity_records, 0, sizeof(irq_affinity_records));

	for (i = 0; i < NR_SOC_IRQS; i++)
	{
		snprintf(irq_affinity_key, sizeof(irq_affinity_key), irq_affinity_key_prefix, i);

		ret = get_hw_config_int(irq_affinity_key, &cpu, NULL);
		if (ret == false)
			continue;
		if (cpu < 0)
			continue;
		if (cpu > NR_CPUS)
			continue;

		irq_affinity_register_sysctl_table(i, cpu);

		/*init the records. as default, irqs binds to CPU0*/
		irq_affinity_records[i] = cpu;

		ret = irq_set_affinity(i, cpumask_of(cpu));
		if (ret < 0)
			printk(KERN_ERR "%s %d : failed to irq_set_affinity %d errno %d\r\n",
		           __FUNCTION__, __LINE__, i, ret);
		}

		ret = register_hotcpu_notifier(&cpu_up_notifier);
		if (ret < 0){
			printk(KERN_ERR"%s : register_hotcpu_notifier failed %d !\n",__FUNCTION__, ret);
		}

		ret = register_pm_notifier(&post_suspend_notifier);
		if (ret < 0){
			printk(KERN_ERR"%s : register_pm_notifier failed %d !\n",__FUNCTION__, ret);
	}

	kfree(dummy);

	return;
}

static int __initdata irq_affinity_disabled = 0; /*1 : disabled , 0 : enabled*/
static int __init irq_affinity_disable(char *__unused)
{
	irq_affinity_disabled = 1;
	return 0;
}
early_param("no_irq_affinity", irq_affinity_disable);

static int __init irq_affinity_work_init(void)
{
	struct work_struct *irq_affinity_work;

	if (1 == irq_affinity_disabled)
		return 0;

	irq_affinity_work = (struct work_struct *)kmalloc(sizeof(struct work_struct), GFP_KERNEL);
	if (NULL == irq_affinity_work){
		printk(KERN_ERR"%s %d : kmalloc work struct fail !\r\n", __FUNCTION__,__LINE__);
		return -ENOMEM;
	}

	INIT_WORK(irq_affinity_work, irq_affinity_init);

	schedule_work(irq_affinity_work);

	return 0;
}
late_initcall(irq_affinity_work_init);

static int proc_irq_affinity_record_show(struct seq_file *m, void *v)
{
	int i;

	seq_printf(m, "irq affinity record : \n");
	for(i = 0; i < NR_SOC_IRQS ; i++){
		seq_printf(m, "IRQ [%3d] CPU [%u]\n", i, irq_affinity_records[i]);
	}
	seq_printf(m, "end.\n");

	return 0;
}

static int proc_irq_affinity_record_open(struct inode *inode, struct file *file)
{
	return single_open(file, proc_irq_affinity_record_show, NULL);
}

static const struct file_operations proc_irq_affinity_record_fops = {
	.open = proc_irq_affinity_record_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int __init proc_irq_affinity_record_init(void)
{
	if (1 == irq_affinity_disabled)
		return 0;

	balong_create_stats_proc_entry("irq_affinity", S_IRUGO, &proc_irq_affinity_record_fops, NULL);

	return 0;
}
late_initcall_sync(proc_irq_affinity_record_init);
static void __exit proc_irq_affinity_record_exit(void)
{
	return;
}
module_exit(proc_irq_affinity_record_exit);

MODULE_DESCRIPTION("IRQ Affinity Set/Restore Module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("xuyiping <xuyiping@huawei.com>");

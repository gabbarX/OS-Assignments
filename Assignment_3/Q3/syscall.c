#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/tasks.h>
#include <linux/file.h>
// #include <linux/

static int pid=0;
module_param(pid, int, 0);
struct task_struct *task;
MODULE_DESCRIPTION("My Kernel module");
MODULE_AUTHOR("syscall");
MODULE_LICENSE("GPL");
static int __init abc_init(void)
{
	struct pid *pid_struct;
	struct task_struct *task;
	pid_struct = find_get_pid(pid);
	task=pid_task(pid_struct,PIDTYPE_PID);
	if (!task) {
		pr_err("Can't find task");
		return -EINVAL;
	}	
	printk("PROCESS_NAME : %s\n", task->comm);
	printk("PROCESS_ID : %d\n", task->pid);
	printk("USER_ID : %d\n", __kuid_val(task->cred->uid));
	printk("PROCESS_GROUP_ID : %d\n", pid_vnr(task_pgrp(task)));

	return 0;
}
static void __exit dummy_exit(void)
{
	printk(KERN_INFO "ERROR Module has been Unloaded");
	return;
}
module_init(abc_init);
module_exit(dummy_exit);

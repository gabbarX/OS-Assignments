#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/file.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/capability.h>
#include <linux/completion.h>
#include <linux/personality.h>
#include <linux/tty.h>
#include <linux/iocontext.h>
#include <linux/key.h>
#include <linux/security.h>
#include <linux/cpu.h>
#include <linux/acct.h>
#include <linux/tsacct_kern.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/binfmts.h>
#include <linux/nsproxy.h>
#include <linux/pid_namespace.h>
#include <linux/ptrace.h>
#include <linux/profile.h>
#include <linux/mount.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/mempolicy.h>
#include <linux/taskstats_kern.h>
#include <linux/delayacct.h>
#include <linux/freezer.h>
#include <linux/cgroup.h>
#include <linux/syscalls.h>
#include <linux/signal.h>
#include <linux/posix-timers.h>
#include <linux/cn_proc.h>
#include <linux/mutex.h>
#include <linux/futex.h>
#include <linux/pipe_fs_i.h>
#include <linux/audit.h>
#include <linux/resource.h>
#include <linux/blkdev.h>
#include <linux/task_io_accounting_ops.h>
#include <linux/fs_struct.h>
#include <linux/init_task.h>
#include <linux/perf_event.h>
#include <trace/events/sched.h>
#include <linux/hw_breakpoint.h>
#include <linux/oom.h>
#include <linux/writeback.h>
#include <linux/shm.h>

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

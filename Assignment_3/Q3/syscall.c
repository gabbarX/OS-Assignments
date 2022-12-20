#include <linux/kernel.h>
#include <linux/taskstats_kern.h>
#include <linux/tsacct_kern.h>
#include <linux/acct.h>
#include <linux/delayacct.h>
#include <linux/cpumask.h>
#include <linux/percpu.h>
#include <linux/slab.h>
#include <linux/cgroupstats.h>
#include <linux/cgroup.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/pid_namespace.h>
#include <net/genetlink.h>
#include <linux/atomic.h>
#include <linux/sched/cputime.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/anon_inodes.h>
#include <linux/slab.h>
#include <linux/sched/autogroup.h>
#include <linux/sched/mm.h>
#include <linux/sched/coredump.h>
#include <linux/sched/user.h>
#include <linux/sched/numa_balancing.h>
#include <linux/sched/stat.h>
#include <linux/sched/task.h>
#include <linux/sched/task_stack.h>
#include <linux/sched/cputime.h>
#include <linux/seq_file.h>
#include <linux/rtmutex.h>
#include <linux/init.h>
#include <linux/unistd.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/completion.h>
#include <linux/personality.h>
#include <linux/mempolicy.h>
#include <linux/sem.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/iocontext.h>
#include <linux/key.h>
#include <linux/binfmts.h>
#include <linux/mman.h>
#include <linux/mmu_notifier.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/mm_inline.h>
#include <linux/nsproxy.h>
#include <linux/capability.h>
#include <linux/cpu.h>
#include <linux/cgroup.h>
#include <linux/security.h>
#include <linux/hugetlb.h>
#include <linux/seccomp.h>
#include <linux/swap.h>
#include <linux/jiffies.h>
#include <linux/futex.h>
#include <linux/compat.h>
#include <linux/kthread.h>
#include <linux/task_io_accounting_ops.h>
#include <linux/rcupdate.h>
#include <linux/ptrace.h>
#include <linux/mount.h>
#include <linux/audit.h>
#include <linux/memcontrol.h>
#include <linux/ftrace.h>
#include <linux/proc_fs.h>
#include <linux/profile.h>
#include <linux/rmap.h>
#include <linux/ksm.h>
#include <linux/acct.h>
#include <linux/userfaultfd_k.h>
#include <linux/tsacct_kern.h>
#include <linux/cn_proc.h>
#include <linux/freezer.h>
#include <linux/delayacct.h>
#include <linux/taskstats_kern.h>
#include <linux/random.h>
#include <linux/tty.h>
#include <linux/fs_struct.h>
#include <linux/magic.h>
#include <linux/perf_event.h>
#include <linux/posix-timers.h>
#include <linux/user-return-notifier.h>
#include <linux/oom.h>
#include <linux/khugepaged.h>
#include <linux/sysctl.h>
#include <linux/kcov.h>
#include <linux/thread_info.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>     /* current */

#include <linux/vmalloc.h> 
#include <linux/mm_types.h>

#include <linux/sched/signal.h>
#include <linux/mm.h>
#include <linux/atomic.h>
#include <linux/spinlock.h>

static int pid=0;
module_param(pid, int, 0);
struct task_struct *task_list;
MODULE_DESCRIPTION("My Kernel module");
MODULE_AUTHOR("syscall");
MODULE_LICENSE("GPL");
static int abc_init(void)
{
	pid_struct = find_get_pid(pid);
	task_list=pid_task(pid_struct,PIDTYPE_PID);
	if (!task_list) {
		pr_err("Can't find task");
		return -EINVAL;
	}	
	printk("PROCESS_NAME : %s\n", task_list->comm);
	printk("PROCESS_ID : %d\n", task_list->pid);
	printk("USER_ID : %d\n", __kuid_val(task_list->cred->uid));
	printk("PROCESS_GROUP_ID : %d\n", pid_vnr(task_pgrp(task_list)));

	return 0;
}
static void dummy_exit(void)
{
	printk(KERN_INFO "ERROR Module has been Unloaded");
	return;
}
module_init(abc_init);
module_exit(abc_exit);

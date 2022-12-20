#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/mutex.h>
#include <linux/futex.h>
#include <linux/pipe_fs_i.h>
#include <linux/audit.h>
#include <linux/resource.h>
#include <linux/blkdev.h>
#include <linux/task_io_accounting_ops.h>
// #include <linux/syscalls.h>
#include <linux/unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankit Gautam");
MODULE_DESCRIPTION("Custom kernel module");

static unsigned long find_sys_call_table(void)
{
    unsigned long sctable;
    unsigned long ptr;

    sctable = NULL;
    for (ptr = (unsigned long)sys_close;
         ptr < (unsigned long)&loops_per_jiffy; ptr += sizeof(void )) {
        unsigned longp;

        p = (unsigned long *)ptr;
        if (p[NR_close] == (unsigned long)sys_close) {
            sctable = (unsigned long **)p;
            return sctable;
        }
    }

    return NULL;
}

SYSCALL_DEFINE1(print_task_struct, pid_t, pid)
{
    struct task_struct *task;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task)
        return -EINVAL;

    printk(KERN_INFO "pid: %d\n", task->pid);
    printk(KERN_INFO "user id: %d\n", __kuid_val(task->cred->uid));
    printk(KERN_INFO "process group id: %d\n", pid_vnr(task_pgrp(task)));
    printk(KERN_INFO "command path: %s\n", task->comm);

    return 0;
}

static int __init sys_call_init(void)
{    
    unsigned long cr0;
    unsigned long sctable;

    sctable = find_sys_call_table();
    if (!sctable) {
        printk(KERN_ERR "Syscall table not found\n");
        return -EINVAL;
    }

    cr0 = read_cr0();
    write_cr0(cr0 & ~0x00010000);
    sctable[NR_my_syscall] = my_syscall;
    write_cr0(cr0);

    return 0;
}

static void __exit sys_call_exit(void)
{
    unsigned long cr0;
    unsigned long sctable;

    sctable = find_sys_call_table();
    if (!sctable)
        return;

    cr0 = read_cr0();
    write_cr0(cr0 & ~0x00010000);
    sctable[__NR_my_syscall] = NULL;
    write_cr0(cr0);
}

module_init(sys_call_init);
module_exit(sys_call_exit);

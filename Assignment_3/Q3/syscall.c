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
#include <linux/cred.h>
// #include <module.h>
#include <linux/moduleparam.h>
#include <linux/task_io_accounting_ops.h>
// #include <linux/syscalls.h>
#include <linux/unistd.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankit Gautam");
MODULE_DESCRIPTION("Custom kernel module");


static int pid;

module_param(num,int,S_IRUSR | S_IRWSR | S_IRGRP| S_IROTH);


static int __init sys_call_init(void)
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

static void __exit sys_call_exit(void)
{
    printk(KERN_INFO "Exiting module!\n");
}

module_init(sys_call_init);
module_exit(sys_call_exit);

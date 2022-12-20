#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manan Chugh");
MODULE_DESCRIPTION("Manan's custom kernel module");

SYSCALL_DEFINE1(print_task_struct, pid_t, pid)
{
    struct task_struct task;

    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task)
        return -EINVAL;

    printk(KERN_INFO "pid: %d\n", task->pid);
    printk(KERN_INFO "user id: %d\n", task->uid);
    printk(KERN_INFO "process group id: %d\n", task->pgid);
    printk(KERN_INFO "command path: %s\n", task->comm);

    return 0;
}

static int __init sys_call_init(void)
{
    long error;

    error = register_syscall("print_task_struct", (void)print_task_struct);
    if (error) {
        printk(KERN_ERR "Failed to register syscall\n");
        return error;
    }

    printk(KERN_INFO "Syscall registered\n");
    return 0;
}

static void __exit sys_call_exit(void)
{
    unregister_syscall("print_task_struct");
    printk(KERN_INFO "Syscall unregistered\n");
}

module_init(sys_call_init);
module_exit(sys_call_exit);

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankit Gautam");
MODULE_DESCRIPTION("Module");
MODULE_VERSION("0.01");

int pid = 0;
module_param(pid, int, 0);

static int __init processIdGiverInit(void)
{
    struct task_struct *task;
    task = pid_task(find_vpid(pid), PIDTYPE_PID);
    if (!task)
    {
        return -ESRCH;
    }
    printk(KERN_INFO "The pid is: %d\n", task->pid);
    printk(KERN_INFO "The uid is: %d\n", task->cred->uid.val);
    printk(KERN_INFO "The pgid is: %d\n", task->group_leader->pid);
    printk(KERN_INFO "The comm is: %s\n", task->comm);
    return 0;
}
static void __exit processIdGiverExit(void)
{
    printk(KERN_INFO "Module is Exiting\n");
}
module_init(processIdGiverInit);
module_exit(processIdGiverExit);

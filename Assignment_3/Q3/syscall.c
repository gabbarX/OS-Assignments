#include <linux/syscalls.h>
#include <linux/types.h>
#include <linux/sched.h>


MODULE_LICENSE("GPL");
//Define syscall
#define PROCESS_INFO 287

//Define the system call
SYSCALL_DEFINE1(PROCESS_INFO,int,pid)
{
    struct task_struct *task;
    struct pid *pid_struct;

    pid_struct = find_get_pid(pid);
    task = pid_task(pid_struct, PIDTYPE_PID);

    printk("pid: %d\n",task->pid);
    printk("user_id: %d\n",task->cred->uid.val);
    printk("pgid: %d\n",task->group_leader->pid);
    printk("common path: %s\n",task->comm);

    return 0;
}
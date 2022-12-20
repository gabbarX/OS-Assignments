#include <linux/module.h> 
#include <linux/kernel.h>   
#include <linux/init.h>     

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ankit Gautam");
MODULE_DESCRIPTION("Process Info Linux Kernel Module."); 


static int __init hello_init(void)
{
    printk(KERN_INFO "Hello world!\n");
    return 0;   
}

static void __exit hello_cleanup(void)
{
    printk(KERN_INFO "Cleaning up module.\n");
}
module_init(hello_init);      
module_exit(hello_cleanup);   

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

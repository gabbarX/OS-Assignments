#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pid.h>
#include <linux/pid_namespace.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <linux/cred.h>

MODULE_AUTHOR("Ankit Gautam");
MODULE_LICENSE("GPL");

static int pNum;
static struct task_struct* pTask;
static struct pid* pidStruct;

module_param(pNum, int,  0);

int init_module(void) 
{
    if (!(pidStruct = find_get_pid(pNum))) {
        pr_info("NULL PID found. Terminating.\n");
        return 0;
    }
    

    if (!(pTask = pid_task(pidStruct, PIDTYPE_PID))) {
        pr_info("NULL task struct found. Terminating.\n");
        return 0;
    }

    printk("Process Name: %s\n", pTask -> comm);
    printk("PID: %d\n", pTask -> pid);
    printk("UID: %d\n", pTask -> cred -> uid);
    printk("PGID: %d\n", pTask -> cred -> gid);
    printk("Command Path: %s\n", pTask -> comm);
    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "Cleaning module has run.\n");
}

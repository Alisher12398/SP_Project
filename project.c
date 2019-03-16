#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/string.h>
#include <asm/current.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Alisher" );

static int license_key = 0;
module_param(license_key, int, 0);

int kill_process(pid_t pid, int sig) {
    int error = -ESRCH;
    struct task_struct* p;
    struct task_struct* temp_task_pid = NULL; 
    struct pid* process_pid;
   
    p = &init_task;
    do {
        if (p->pid == pid) {
            temp_task_pid = p;
            break;
        }
        p = next_task(p);
    } while (p != &init_task);
    if (temp_task_pid != NULL) {
        process_pid = temp_task_pid->pids[PIDTYPE_PID].pid;
        if (process_pid != NULL) error = kill_pid(process_pid,sig,1);
    }
    return error;
}

void check_lisence(void)
{
	printk(KERN_INFO "\n\n***** Project: start check_lisence.\n");

	struct task_struct *p;
	char *process_name = "2048-qt";

	for_each_process(p){
		printk(KERN_INFO "%s[%d]\n", (*p).comm, (*p).pid);
		if (strcmp(p->comm, process_name) == 0){
			if (license_key != 24031998){
				printk("Error! \n Wrong lisence key!");
				kill_process((*p).pid,9);	
			}
			
		}
	}
	printk(KERN_INFO "\n\n***** Project: end check_lisence.\n");
}

int init_module(void)
{
	printk(KERN_INFO "\n\n\n\n***** Project: start init_module.\n\n");

	check_lisence();

	printk(KERN_INFO "\n\n***** Project: end init_module.\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "\n\n***** Project: start cleanup_module.\n\n");
}
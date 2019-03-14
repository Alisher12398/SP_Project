#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <asm/current.h>

int my_kill_proc(pid_t pid, int sig) {
    int error = -ESRCH;
    struct task_struct* p;
    struct task_struct* t = NULL; 
    struct pid* pspid;
    rcu_read_lock();
    p = &init_task;
    do {
        if (p->pid == pid) {
            t = p;    
            break;
        }
        p = next_task(p);
    } while (p != &init_task);
    if (t != NULL) {
        pspid = t->pids[PIDTYPE_PID].pid;
        if (pspid != NULL) error = kill_pid(pspid,sig,1);
    }
    rcu_read_unlock();
    return error;
}

void fun1(void)
{
	printk(KERN_INFO "\n\n***** Project: start fun1.\n");
	struct task_struct *p;
	// char process_name[] = "\n\n\n\n\n***** Hello\n\n\n";
	// char process_name2[];
	// char *process_name3;

	bool b = false;
	//struct task_struct *p = &comm;
	//char proadas = &(*p).comm;
	//char proadas2 = (*p).comm;
	char process_name = 'atom';
	char *process_name2 = &process_name;
	char *process_name3 = "atom";
	for_each_process(p){
		printk(KERN_INFO "%s[%d]\n", (*p).comm, (*p).pid);
		//char a[] = p->comm;
		if (p->comm == process_name3){
			b = true;
		}
	}

	if (b == true){
		printk(KERN_INFO "\n\ntrue\n");
	}
	if (b == false){
		printk(KERN_INFO "\n\nfalse\n");
	}

	//printk(proadas);
	//printk(proadas2);

}

int init_module(void)
{
	printk(KERN_INFO "\n\n\n\n***** Project: start init_module.\n\n");

	// my_kill_proc(10576, 9);
	// my_kill_proc(10578, 9);
	// my_kill_proc(10580, 9);
	// my_kill_proc(10608, 9);
	// my_kill_proc(10621, 9);
	// my_kill_proc(10696, 9);

	//print_processes();
	fun1();
	//run_init_process(subl);
	//kill_pid_info(1, a, 1000);
	// int signum = SIGKILL;
	// //task = current;
	// struct siginfo info;
	// memset(&info, 0, sizeof(struct siginfo));
	// info.si_signo = signum;
	// int ret = send_sig_info(signum, &info, "sublime_text");
	// if (ret < 0) {
	//   print


	printk(KERN_INFO "\n\n***** Project: end init_module.\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "\n\n***** Project: start cleanup_module.\n\n");
}
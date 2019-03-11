#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <asm/current.h>

void fun1(void)
{
	printk(KERN_INFO "\n\n***** Project: start fun1.\n");
	struct task_struct *p;
	printk(KERN_INFO "Begin");
	char process_name[] = "\n\n\n\n\n***** Hello\n\n\n";
	char process_name2[];
	char *process_name3;
	process_name3 = 'chrome';
	bool b = false;
	for_each_process(p){
		printk(p->comm);
		process_name2 = p->comm;

		if (process_name2 == process_name3)
		{
			//printk("\n\n\n\n\n***** Sublime\n\n\n");
			b = true;
		}
		if (process_name2 == 'chrome')
		{
			//printk("\n\n\n\n\n***** Sublime\n\n\n");
			b = true;
		}
		// for_each_thread(p, t) {
		// 	printk(KERN_INFO "  %s[%d]\n", t->comm, t->pid);
		// }
	}
	if (b == true){
		printk(KERN_INFO "\n\n***** TRUUUE.\n");
	}
	if (b == false){
		printk(process_name);
	}
	printk(KERN_INFO "\n\n***** Project: end fun1.\n");
}

//int kill_pid(struct pid *pid, int sig, int priv)

int init_module(void)
{
	printk(KERN_INFO "\n\n\n\n***** Project: start init_module.\n\n");

	fun1();

	printk(KERN_INFO "\n\n***** Project: end init_module.\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "\n\n***** Project: start cleanup_module.\n\n");
}
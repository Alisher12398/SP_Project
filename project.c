#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/smp.h>

void fun(void) (
}


int init_module(void)
{
	printk(KERN_INFO "Project: start.\n");

	printk(KERN_INFO "Begin");
	fun();
	printk(KERN_INFO "End");

	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Project: end.\n");
}

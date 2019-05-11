#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/string.h>
#include <asm/current.h>
#include <asm/segment.h>
#include <linux/buffer_head.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/fdtable.h>
#include <linux/dcache.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>

#define TAG "Check if wait work"


MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Alisher and Rustembek" );


char original_key[255] ,  temp_key[255];

void fs_read_original_key(void)
{
    struct file *f;
    mm_segment_t fs;
    loff_t offset;
    offset = 0;
    
    f = filp_open("user_key.txt",O_RDWR | O_CREAT,0644);
    
    fs = get_fs();

    set_fs(get_ds());
    
    vfs_read(f, original_key, 255, &offset);
    
    set_fs(fs);
    filp_close(f,NULL);

    printk(KERN_INFO "Char: %s\n", original_key);
    
}

void fs_read_temp_key(void)
{
    struct file *f;
    mm_segment_t fs;
    loff_t offset;
    offset = 0;
    
    f = filp_open("user_key_temp.txt",O_RDWR | O_CREAT,0644);
    
    fs = get_fs();

    set_fs(get_ds());
    
    vfs_read(f, temp_key, 255, &offset);
    
    set_fs(fs);
    filp_close(f,NULL);

    printk(KERN_INFO "Char: %s\n", temp_key);
    
}

static int is_auth = 0;

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
		if (strcmp(p->comm, process_name) == 0)
        {
			if (strcmp(original_key, temp_key) != 0){
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


    fs_read_temp_key();
    fs_read_original_key();
    check_lisence();
	printk(KERN_INFO "\n\n***** Project: end init_module.\n");
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "\n\n***** Project: start cleanup_module.\n\n");
}
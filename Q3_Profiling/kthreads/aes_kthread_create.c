/*
* @file aes_kthread_create.c
* @brief Kernel module for profiling kthread_create
*
* This source file contains code for profiling kthread_create (kthread_run) used 
* in this case). 
*
* Tools used: GCC Compiler, make
* How to compile from source: make
*
* @author Rishi Soni
* @date October 5 2017
* @version 1.0
*
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/time.h>
#include <linux/kthread.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rishi Soni");
MODULE_DESCRIPTION("kthread profiler");

static struct  task_struct *kthread;
static struct timeval tv1, tv2;

//start function for kthread
static int mod_fn(void *ptr)
{
	do_gettimeofday(&tv2);
	printk(KERN_INFO "Kthread creation time: %ld\n",((tv2.tv_usec) - (tv1.tv_usec)));
	while(!kthread_should_stop()){
		schedule();
	}
	do_exit(0);
	return 0;
}


static __s32 init_mod(void)
{
	printk(KERN_INFO "Entering module\n");
	do_gettimeofday(&tv1);
	//Creating and running kthread
	kthread = kthread_run(mod_fn, NULL, "kthread_profiler");
	return 0;
}

static void exit_mod(void)
{
	if(kthread)
	{
		kthread_stop(kthread);
	}
	printk(KERN_INFO "Exiting module. Stopping kthread\n");
	
}

module_init(init_mod);
module_exit(exit_mod);
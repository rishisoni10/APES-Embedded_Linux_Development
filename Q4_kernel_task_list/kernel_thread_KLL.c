/*
* @file kernel_thread_KLL.c
* @brief Kernel module for testing kernel linked lists
*
* This source file contains code for printing all the processes in the system, 
* by traversing the kernel doubly linked list
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
#include <linux/init.h>
#include <linux/list.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rishi Soni");
MODULE_DESCRIPTION("kernel task list");


static __u32 process_call_count = 0;
static __u32 num_child = 0;
static __u32 num_sibling = 0;

static __s32 init_mod(void)
{
	struct task_struct *task;
	struct list_head *list;
	printk(KERN_INFO "Printing all tasks...\n");
	//Traverse all the tasks using kernel LL, and print out all the required values from task_struct
	for_each_process(task)
	{
		list_for_each(list, &(task->children))
		{
			++num_child;
		}

		list_for_each(list, &(task->sibling))
		{
			++num_sibling;
		}
		
		printk(KERN_INFO "%s [%d] | State: %ld | No. of Children/Sibling: %d / %d\n", task->comm, task->pid, task->state, num_child, num_sibling);
		num_child = 0;
		num_sibling = 0;

		process_call_count++;
	}
	return 0;
}

static void exit_mod(void)
{
	printk(KERN_INFO "Exiting process print module. Number of processes is %d\n", process_call_count);
}

module_init(init_mod);
module_exit(exit_mod);
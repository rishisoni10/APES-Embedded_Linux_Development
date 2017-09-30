#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/sched/signal.h>



static __u32 process_call_count = 0;
static __u32 num_child = 0;
static __u32 num_sibling = 0;

static __s32 init_mod(void)
{
	struct task_struct *task;
	struct list_head *list;

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
		
		printk(KERN_INFO "Name | PID | State | No. of Children/Sibling: %s | %d | %ld | %d / %d\n", task->comm, task->pid, task->state, num_child, num_sibling);
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
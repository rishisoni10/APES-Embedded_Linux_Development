/*
* @file exsyscall.c
* @brief Custom kernel module
*
* This source file contains code for a custom kernel module. Currently, this module uses a kernel
* timer to update the number of times the callback function has run. The output of this code
* can be seen with dmesg | tail
*
* Tools used: GCC Compiler, make
* How to compile from source: make
*
* @author Rishi Soni
* @date September 19 2017
* @version 1.0
*
*/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("First module");
MODULE_AUTHOR("Rishi Soni");

static struct timer_list my_timer;
static __u32 timer_call_count = 0;

//Callback function entered every 500ms
static void timer_callback(unsigned long data)
{
	timer_call_count++;
	printk(KERN_ALERT "Timer call count is %d\n", timer_call_count);
	if(mod_timer(&my_timer, jiffies + msecs_to_jiffies(500)))
		printk(KERN_ALERT "Error in modifying timer\n");
}


//Entry function for module
static __s32 mod_init(void)
{
	printk(KERN_ALERT "Entering timer module\n");
	setup_timer(&my_timer, timer_callback, 0);
	printk(KERN_ALERT "Starting timer to fire in 500ms\n");
	if(mod_timer(&my_timer, jiffies + msecs_to_jiffies(500)))
		printk(KERN_ALERT "Error in modifying timer\n");
	return 0;
}

//Exit function for module
static void mod_exit(void)
{
	if(del_timer(&my_timer))
		printk(KERN_ALERT "Timer is still in use ....\n");
	printk(KERN_ALERT "Timer module uninstalling\n");
}

module_init(mod_init);
module_exit(mod_exit);
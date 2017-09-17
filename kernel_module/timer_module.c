#include <linux/module.h>
// #include <linux/config.h>
#include <linux/kernel.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/types.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("First module");
MODULE_AUTHOR("Rishi Soni");

static struct timer_list my_timer;
static __u32 timer_call_count = 0;

static void timer_callback(unsigned long data)
{
	timer_call_count++;
	printk(KERN_ALERT "Timer call count is %d\n", timer_call_count);
	if(mod_timer(&my_timer, jiffies + msecs_to_jiffies(500)))
		printk(KERN_ALERT "Error in modifying timer\n");
}

static __s32 mod_init(void)
{
	printk(KERN_ALERT "Entering timer module\n");
	setup_timer(&my_timer, timer_callback, 0);
	printk(KERN_ALERT "Starting timer to fire in 500ms\n");
	if(mod_timer(&my_timer, jiffies + msecs_to_jiffies(500)))
		printk(KERN_ALERT "Error in modifying timer\n");
	return 0;
}

static void mod_exit(void)
{
	if(del_timer(&my_timer))
		printk(KERN_ALERT "Timer is still in use ....\n");
	printk(KERN_ALERT "Timer module uninstalling\n");
}

module_init(mod_init);
module_exit(mod_exit);
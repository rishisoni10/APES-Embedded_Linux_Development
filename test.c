//Defining the sorting syscall (#333 in syscall_64.tbl)
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>

SYSCALL_DEFINE1(sorting, char *, msg)
{
	char buffer[256];
	long copied = copy_from_user(buffer, msg, sizeof(buffer));
	if (copied < 0 || copied == sizeof(buffer))
		return -EFAULT;
	printk(KERN_INFO "sorting syscall called with \"%s\"\n", buffer);
	return 0;
}

// asmlinkage long sys_sorting(void)
// {
// 	// char buffer[256];
// 	// long copied = copy_from_user(buffer, msg, sizeof(buffer));
// 	// if (copied < 0 || copied == sizeof(buffer))
// 	// 	return -EFAULT;
// 	// printk(KERN_INFO "sorting syscall called with \"%s\"\n", buffer);
// 	printk(KERN_INFO "Hello World\n");
// 	return 0;
// }
//Defining the sorting syscall (#333 in syscall_64.tbl)
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/sort.h>

int comp_func(const void *low, const void *high);

SYSCALL_DEFINE3(sorting, __s32*, input_buffer, __s32, size, __s32*, sorted_buffer)
{
	printk(KERN_INFO "Entering 'sorting' syscall\n");
	printk(KERN_INFO "Size of the buffer from user space is: %d bytes\n", size);
	if(!(access_ok(VERIFY_WRITE, input_buffer, size)))
	{
		printk(KERN_ERR "Input buffer not in userspace\n");
		// exit(1);
	}

	if(input_buffer == NULL)
	{
		printk(KERN_ERR "Input buffer points to NULL address. Error\n");
		// exit(1);
	}

	sorted_buffer = (__s32*)kmalloc(size, GFP_KERNEL);
	long copied = copy_from_user(sorted_buffer, input_buffer, size);

	printk(KERN_INFO "Starting the sort of userspace buffer\n");
	sort(sorted_buffer, size/4, sizeof(__s32), &comp_func, NULL);
	printk(KERN_INFO "Starting the sort of userspace buffer\n");
	
	long ret = copy_to_user(input_buffer, sorted_buffer, size);
	if (ret == 0)
	{
		printk(KERN_INFO "All elements successfully sorted and supplied back in user space\n");
	}

	// long copied = copy_from_user(buffer, msg, sizeof(buffer));
	// if (copied < 0 || copied == sizeof(buffer))
	// 	return -EFAULT;
	printk(KERN_INFO "Exiting 'sorting' syscall\n");
	return 0;
}

int comp_func(const void *low, const void *high)
{
	int low__value = *(const int *)(low);
	int high_value = *(const int *)(high);

	if(low__value < high_value) return 1;
	if(low__value > high_value) return -1;
	return 0;
}

// void swap_func(void *low, void *high, int size)
// {

// }

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
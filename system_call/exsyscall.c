/*
* @file exsyscall.c
* @brief Custom system call
*
* This source file contains code for a custom system call. Currently, this call sorts a buffer of 
* random user space data in the kernel space. Code checks if the buffer is in the user space,
* and not in the kernel space. This system call can be added in any system running a Linux 4.x 
* kernel.
*
* Tools used: GCC Compiler, make
* How to compile from source: Add the system call in the kernel tree and re-build it.
*
* @author Rishi Soni
* @date September 19 2017
* @version 1.0
*
*/
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/types.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/sort.h>
#include <uapi/asm-generic/errno-base.h>
#include <linux/errno.h>

int comp_func(const void *low, const void *high);

//Defining the sorting syscall (#333 in syscall_64.tbl)
SYSCALL_DEFINE3(sorting, __s32*, input_buffer, __s32, size, __s32*, sorted_buffer)
{
	printk(KERN_INFO "Entering 'sorting' syscall\n");
	printk(KERN_INFO "Size of the buffer from user space is: %d bytes\n", size);

	if(input_buffer == NULL)
	{
		printk(KERN_ALERT "Input buffer points to NULL address. Error: %d\n", EFAULT);
		return EFAULT;		//Bad address = -14
	}

	if(!(access_ok(VERIFY_WRITE, input_buffer, size)))
	{
		printk(KERN_ALERT "Input buffer not in userspace: %d\n", EACCES);
		return EACCES;			//Permission denied = -13
	}

	if(size < 1024)
	{
		printk(KERN_ERR "Input buffer size less than required 256 int32_t elements (< 1024 bytes): %d\n", EINVAL);
		return EINVAL;		//Invalid size input = -22
	}

	sorted_buffer = (__s32*)kmalloc(size, GFP_KERNEL);
	long copied = copy_from_user(sorted_buffer, input_buffer, size);

	printk(KERN_INFO "Starting the sort of userspace buffer\n");
	sort(sorted_buffer, size/4, sizeof(__s32), &comp_func, NULL);
	printk(KERN_INFO "Sorting completed!\n");

	long ret = copy_to_user(input_buffer, sorted_buffer, size);
	if (ret == 0)
	{
		printk(KERN_INFO "All elements success








			fully sorted and supplied back in user space\n");
	}
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

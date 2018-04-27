Problem Statement:

Create your own system call. This system call needs to support the following features:
- Print information to the kernel buffer when issued and other useful debug strings
	○ Log when syscall enters, exits, the size of the buffer, and the start/completion of the sort
● Your system call needs to take a set of input parameters including a
	○ Pointer to a buffer
	○ Size of that buffer
	○ Pointer to a sorted buffer
● Validate all input parameters
● Your system call needs to allocate dynamic memory to copy data in from user space
● Pass in memory from user-to-kernel space
● Pass memory back to user space from kernel

The buffer will need to be copied into kernel space. Your syscall will need to sort your buffer in an order
of largest to smallest. Once sorted, it needs to pass the buffer back to the sorted buffer array. You
should create a buffer of at least 256 int32_t data items. You can randomly generate this buffer of data
elements using rand and time.
Show that your kernel module works by writing a piece of software that calls your system call numerous
times. You should that:

● System call works correctly (all input parameters valid and correct)
	○ Print information showing that the sort worked correctly
● System call fails (input parameters are not valid and/or correct)
	○ All errors should return appropriate Error values (defined in errno.h and errno-base.h )

SYSTEM CALL:

The system call has been defined in "exsyscall.c", with the appropriate changes in the Makefile. 
The syscall table (syscall_64.tbl) has been edited to add a new system call called "sorting" / "sys_sorting", with a system call number of 333 (line 342)

This folder has been added to the "core-y" variable (line 569) in the Makefile of the kernel (Makefile_kernel)

To test the system call, run the executable "syscall_test" in the folder Homework_2/
If the user wants to dump the sorted data, type on the command line:

	./syscall_test print_data

If no data needs to be dumped with just the printing of return status, type the following on the command line:

	./syscall_test


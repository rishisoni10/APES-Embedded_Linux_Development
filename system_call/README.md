SYSTEM CALL:

The system call has been defined in "exsyscall.c", with the appropriate changes in the Makefile. 
The syscall table (syscall_64.tbl) has been edited to add a new system call called "sorting" / "sys_sorting", with a system call number of 333 (line 342)

This folder has been added to the "core-y" variable (line 569) in the Makefile of the kernel (Makefile_kernel)

To test the system call, run the executable "syscall_test" in the folder Homework_2/
If the user wants to dump the sorted data, type on the command line:

	./syscall_test print_data

If no data needs to be dumped with just the printing of return status, type the following on the command line:

	./syscall_test


KERNEL MODULES:

- To create a kernel module, define a entry function and an exit function. 
- Initialize the kernel timer to wake up every 500 ms and jump into the callback function
- Re-initialize the timer in the callback function so that kernel timer keeps running and the 
  callback function is call infinitely, unless the module is uninstalled.

  After compilation, install the kernel module using the following command:
  					$ sudo insmod timer_module.ko

  This loads the kernel object of the module into the kernel 

  Following this, run:	
  						$ sudo depmod -a 

  This updates the dependency files of the system.

  To remove the module, run
  						$ sudo rmmod timer_module.ko
  
/*
* @file led_driver_Rishi.c
* @brief Linux Device Driver for on-board Beaglebone Green LEDs through a kernel module
*
* This source file has the basic I/O functionality for controlling user LEDs on a Beaglebone, 
* written in the form of a kernel module. Userspace programs can exploit its functionality by
* reading/writing to the created device fele in the /dev/ folder in userspace
*
* Tools used: GCC Compiler, GDB
* Command to compile from source: make
*
* @author Rishi Soni
* @date November 19 2017
* @version 1.0
*/


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <asm/uaccess.h>

 
#define GPIO_NUMBER    53 //User LED 0.
MODULE_AUTHOR("Rishi Soni");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple LED character device driver");
MODULE_VERSION("0.1");

static int init_result;
static struct timer_list my_timer;
static bool ledStatus;
static int count = 0;
static int freq = 1;;
static int duty = 50;
static int flag;
static int flag1;
static int flag2;
static int flag3;
static int flag4;


static int my_atoi(char *str)
{
    if (*str == '\0')          //If the string is empty, return integer is '0'
       return 0;

    int number = 0;  // Initialize the output number
    int neg = 1;  // For negative values, setting it as positive by default
    //uint8_t i = 0;  // Initialize index of first digit

    // If number is negative, then update sign
    if (*str == '-'){
        neg = -1;
        str++;
    }

    // Calculating and adding each digit of the string.
    while(*str != '\0')
    {
        if (*str >= '0' && *str <= '9')
            number = number*10 + *str++ - '0';
        else {
	        printk(KERN_INFO "Invalid numerical string\n");           //Generate error message if string does not have a number
        return 0;
        }
    }

    // Return result with sign
    return neg*number;
}

//callback function when timer expires
void my_timer_callback(unsigned long data)
{
	if(!flag)
	{
		//Do Nothing
	}
	else
	{
	    count++;

	    if(count%2){
	        // printk( "The count is odd: %d\n", count );
	        ledStatus = !ledStatus;                          // Invert the LED state on each button press
	          gpio_set_value(GPIO_NUMBER, ledStatus); 
	        mod_timer( &my_timer, jiffies + usecs_to_jiffies((500000*(100 - duty))/(100*freq)) );            
	    }
	    else{
	        // printk("The count is even: %d\n", count);
	        ledStatus = !ledStatus;                          // Invert the LED state on each button press
	          gpio_set_value(GPIO_NUMBER, ledStatus); 
	        mod_timer( &my_timer, jiffies + usecs_to_jiffies((500000*duty)/(100*freq)) );    
	    }
	}

    //printk( "The count is %d\n", count );
}

static ssize_t gpio_read( struct file* F, char *buf, size_t count, loff_t *f_pos )
{
	char buffer[100];	
	memset(buffer, 0, sizeof(buffer));
	if(flag1){
		sprintf( buffer, "%d %d %d" , ledStatus, freq, duty);
		flag1 = 0;
	}
	if(flag2){
		sprintf( buffer, "%d" , ledStatus);
		flag2 = 0;
	} 
	if(flag3){
		sprintf( buffer, "%d" , freq);
		flag3 = 0;
	}
	if(flag4){
		sprintf( buffer, "%d" , duty);
		flag4 = 0;
	}	

	count = sizeof( buffer );
 
	if( copy_to_user( buf, buffer, count ) ){
		return -EFAULT;
	}

	return 0;

}


static ssize_t gpio_write( struct file* F, const char *buf, size_t count, loff_t *f_pos )
{ 
	printk(KERN_INFO "Executing WRITE.\n");
	int n1;
	int number1;
	int operation_num;
	int data_num;
	int len;
	int ret;
	int j = 0;
	char *operation;
	char *length;
	char *data;
	char kern_buffer[50];
	char* kern_ptr;

	memset(kern_buffer, 0, sizeof(kern_buffer));

	n1 = copy_from_user(kern_buffer, buf, count);
	if(n1 == 0)
		printk(KERN_INFO "Success in copying\n");
	else
		printk(KERN_INFO "Failed in copying\n");		
	
	// number1 = my_atoi(kern_buffer);
	printk(KERN_INFO "Kern buffer_r is %s\n", kern_buffer);
	kern_ptr = kern_buffer;
	
	operation = strsep(&kern_ptr," ");
	printk(KERN_INFO "operation_r is %s\n", operation);
	length = strsep(&kern_ptr, " ");
	printk(KERN_INFO "length_r is %s\n", length);
	data = strsep(&kern_ptr, " ");
	printk(KERN_INFO "data_r is %s\n", data);

	flag = 0;
	flag1 = 0;

	operation_num = my_atoi(operation);
	data_num = my_atoi(data);
	len = my_atoi(length);

	//LED control
	if(operation_num == 1)
	{
		flag = 0;
		// LED ON or OFF
		printk("Data to write in LED is %d\n", data_num);
		if(data_num == 0 || data_num == 1)
		{	
			gpio_set_value(GPIO_NUMBER, data_num);
		}
		else
		{	
			printk(KERN_ALERT "LED Control: Invalid arguement from user space\n");
			gpio_set_value(GPIO_NUMBER, 0);
		}

		operation_num = 0;
	}

	//frequency adjustment
	if(operation_num == 2)
	{
		printk(KERN_INFO "operation_num %d and data_num %d and len %d\n", operation_num, data_num, len);
		freq = data_num;
		flag = 1;
	    ret = mod_timer( &my_timer, jiffies + usecs_to_jiffies((500000*duty)/(100*freq)) );
	}	

	//duty cycle adjustment
	if(operation_num == 3)
	{
		printk(KERN_INFO "operation_num %d and data_num %d and len %d\n", operation_num, data_num, len);
		flag = 0;
		duty = data_num;
	}
	//reading all state variables
	else if(operation_num == 4)
	{		
		printk(KERN_INFO "Reading all state variables.\n");
		flag1 = 1;
	}

	//reading LED status
	else if(operation_num == 5){		
		printk(KERN_INFO "Reading LED status.\n");
		flag2 = 1;
	}	
	//reading frequency value
	else if(operation_num == 6){		
		printk(KERN_INFO "Reading frequency value.\n");
		flag3 = 1;
	}	
	//for reading duty cycle
	else if(operation_num == 7){		
		printk(KERN_INFO "Reading duty cycle value.\n");
		flag4 = 1;
	}	
			
	return count;
}
 

static int gpio_open( struct inode *inode, struct file *file )
{
	printk("Did gpio open.\n");
	return 0;
}
 

static int gpio_close( struct inode *inode, struct file *file ){
	printk("Did gpio close.\n");
	return 0;
}

 
static struct file_operations FileOps =
{
	.open         = gpio_open,
	.read         = gpio_read,
	.write        = gpio_write,
	.release      = gpio_close,
};
 
static int init_gpio(void)
{
	int ret;
	init_result = register_chrdev( 0, "gpio", &FileOps );
 
	if(init_result < 0)
	{
		printk(KERN_ALERT "Device Registration failed\n");
		return -1;
	}
	else
	{
		printk(KERN_ALERT "Major number is (Rishi): %d\n",init_result);
		flag = 0;
		setup_timer(&my_timer, my_timer_callback, 0);
    	ret = mod_timer(&my_timer, jiffies + usecs_to_jiffies((500000*duty)/(100*freq)));
		return 0;
	}
}
 
void cleanup_gpio(void)
{
	int ret;
	unregister_chrdev( init_result, "gpio" );
	printk(KERN_ALERT "Device unregistered (Rishi): %d\n",init_result);
    ret = del_timer(&my_timer);
	gpio_set_value(GPIO_NUMBER, 0);

    printk(KERN_INFO "Exiting the kernel module.\n");
}
 
module_init(init_gpio);
module_exit(cleanup_gpio);
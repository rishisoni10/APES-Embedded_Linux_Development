#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

#define SYS_sorting	333


int main(int argc, char *argv[])
{
	int32_t i, size, elements;
	uint8_t option;
	time_t t;
	int32_t *buffer;
	int32_t *kernel_buffer = NULL;

	printf("CASE - I: ALL PARAMETERS ARE CORRECT\n");
	elements = 300;
	buffer = (int32_t*)malloc(sizeof(int32_t) * elements);
	if(buffer == NULL)
	{
		printf("Buffer malloc FAILED\n");	
		exit(EXIT_FAILURE);
	}
	else
		printf("Buffer malloc success\n");
	
	memset(buffer, 0, sizeof(buffer));
	//Initializing random number generator
	srand((unsigned) time(&t));
	//Filling random data in buffer
	for (int i = 0; i < elements; i++)
	{
		*(buffer +i) = rand();
	}
	size = sizeof(int32_t) * elements; //Total size in bytes
	printf("Size of buffer in bytes: %d\n", size);
	int res = syscall(SYS_sorting, buffer, size, kernel_buffer);
	if (res > 0)
	{
		if (res == 14)
		{
			printf("EFAULT error. Input buffer points to NULL address\n");
			exit(1);
		}		
		else if (res == 13)
		{
			printf("EACCES error. Input buffer is not in user-space\n");
			exit(1);
		}	
		else if (res == 22)
		{
			printf("EINVAL error. Size passed is less than 1024 bytes (256 elements)\n");
			exit(1);
		}	
	}
	else
	{
		printf("System call for sorting implemented SUCCESSFULLY!\n");
		if(argc == 2)
		{
			if (!strcmp(argv[1], "print_data"))
			{
				printf("Sorted data is: \n");
				for (i = 0; i < elements; i++)
					printf("%d\n", *(buffer + i));
			}
			else
				printf("Compare failed\n");
		}
		
	}
	

	printf("\n\nCASE - II: NUMBER OF ELEMENTS IS LESS THAN 256\n");
	elements = 30;
	buffer = (int32_t*)malloc(sizeof(int32_t) * elements);
	if(buffer == NULL)
	{
		printf("Buffer malloc FAILED\n");	
		exit(EXIT_FAILURE);
	}
	else
		printf("Buffer malloc success\n");
	
	memset(buffer, 0, sizeof(buffer));
	//Initializing random number generator
	srand((unsigned) time(&t));
	//Filling random data in buffer
	for (int i = 0; i < elements; i++)
	{
		*(buffer +i) = rand();
	}
	size = sizeof(int32_t) * elements; //Total size in bytes
	printf("Size of buffer in bytes: %d\n", size);
	res = syscall(SYS_sorting, buffer, size, kernel_buffer);
	// printf("Value of res is %d\n", res);
	if (res > 0)
	{
		if (res == 14)
		{
			printf("EFAULT error. Input buffer points to NULL address\n");
			// exit(1);
		}		
		else if (res == 13)
		{
			printf("EACCES error. Input buffer is not in user-space\n");
			// exit(1);
		}	
		else if (res == 22)
		{
			printf("EINVAL error. Size passed is less than 1024 bytes (256 elements)\n");
			// exit(1);
		}	
	}
	else
	{
		printf("System call for sorting implemented SUCCESSFULLY!\n");
		if(argc == 2)
		{
			if (!strcmp(argv[1], "print_data"))
			{
				printf("Sorted data is: \n");
				for (i = 0; i < elements; i++)
					printf("%d\n", *(buffer + i));
			}
			else
				printf("Compare failed\n");
		}
	}


	printf("\n\nCASE - III: USERSPACE BUFFER POINTS TO NULL\n");
	elements = 300;
	buffer = NULL;
	if(buffer == NULL)
	{
		printf("Buffer malloc FAILED\n");	
		exit(EXIT_FAILURE);
	}
	else
		printf("Buffer malloc success\n");
	
	memset(buffer, 0, sizeof(buffer));
	// printf("Buffer zeroed\n");

	//Initializing random number generator
	srand((unsigned) time(&t));
	//Filling random data in buffer
	for (int i = 0; i < elements; i++)
	{
		*(buffer +i) = rand();
	}
	size = sizeof(int32_t) * elements; //Total size in bytes
	printf("Size of buffer in bytes: %d\n", size);
	res = syscall(SYS_sorting, buffer, size, kernel_buffer);
	if (res > 0)
	{
		if (res == 14)
		{
			printf("EFAULT error. Input buffer points to NULL address\n");
			exit(1);
		}		
		else if (res == 13)
		{
			printf("EACCES error. Input buffer is not in user-space\n");
			exit(1);
		}	
		else if (res == 22)
		{
			printf("EINVAL error. Size passed is less than 1024 bytes (256 elements)\n");
			exit(1);
		}	
	}
	else
	{
		printf("System call for sorting implemented SUCCESSFULLY!\n");
		if(argc == 2)
		{
			if (!strcmp(argv[1], "print_data"))
			{
				printf("Sorted data is: \n");
				for (i = 0; i < elements; i++)
					printf("%d\n", *(buffer + i));
			}
			else
				printf("Compare failed\n");
		}
	}
	return 0;
}

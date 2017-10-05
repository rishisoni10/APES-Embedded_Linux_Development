/*
* @file aes_pthread_create.c
* @brief Program for profiling user space thread creation
*
* This source file contains code for profiling pthread_create in user spce
*
* Tools used: GCC Compiler, make
* How to compile from source: gcc -o aes_pthread_create aes_pthread_create.c -lpthread
*
* @author Rishi Soni
* @date October 5 2017
* @version 1.0
*
*/
#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>

pthread_t thread;
clock_t start_t, end_t;
double total_t;


static void *thread_function(void *ptr)
{
   	end_t = clock();
}


int main(int argc, char const *argv[])
{  
	const char *i = "Rishi";
 	start_t = clock();
	//Creating thread
 	if (pthread_create(&thread, NULL, thread_function, (void*)i))
    {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
  pthread_join(thread, NULL);
	total_t = end_t - start_t;
  printf("Total clock ticks taken is %lf\n", total_t);
  pthread_exit(NULL);
}

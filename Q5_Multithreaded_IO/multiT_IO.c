/*
* @file multiT_IO.c
* @brief Program to demostrate use of multithreading with mutexs and condition variables
*
* This source file contains code for communication between 3 threads, and execution of the 
* threads according to the signal received by the parent process using the kill command
*
* Tools used: GCC Compiler, make
* How to compile from source: gcc -o multiT_IO multiT_IO.c -lpthread
* How to run: ./multiT_IO text_file_name.txt
*
* @author Rishi Soni
* @date October 5 2017
* @version 1.0
*
*/
#define _GNU_SOURCE     /* To get pthread_getattr_np() declaration */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>


#define	MAX_CHAR	  (1000000)
#define NUM_THREADS	  (2)

FILE *fp;
pthread_mutex_t syn_mutex_1, syn_mutex_2;
pthread_cond_t t1_cond, t2_cond;
int done = 1;
pthread_t thread[NUM_THREADS];

struct file_data
{
	int words;
	int lines;
	int characters;
};
struct file_data data;

//Handle the signals registered in the main thread 
void signal_handler(int signum)
{
	if(signum == SIGUSR1)
	{
		pthread_mutex_lock(&syn_mutex_1);
		done = 1;
		//Giving SIGUSR1 signal from cmd line releases the condition signal for thread_2
		pthread_cond_signal(&t1_cond);
		pthread_mutex_unlock(&syn_mutex_1);
	}

	if(signum == SIGUSR2)
	{
		pthread_mutex_lock(&syn_mutex_2);
		//Giving SIGUSR2 signal from cmd line releases the condition signal for thread_3
		pthread_cond_signal(&t2_cond);
		pthread_mutex_unlock(&syn_mutex_2);
	}

	//Clean-up block
	if(signum == SIGINT)
	{
		printf("Cleaning up...\n");
		if (fp != NULL)
		{	
			fclose(fp);
			printf("File closed\n");
		}
		else
			printf("File is already in closed state\n");
	    printf("Exiting....\n");
	    exit(1);
	}
}

//Start function of thread_2
static void *thread_2(void *ptr)
{
	int ch;
	char const *file_name = (char *)ptr;
	char buffer[MAX_CHAR];
	pthread_mutex_lock(&syn_mutex_1);
	printf("Entered thread 2. Waiting for SIGUSR1 signal\n");
	
	//Waits for user signal
	pthread_cond_wait(&t1_cond, &syn_mutex_1);

	printf("USR1 signal received\n");
	fp = fopen(file_name, "r");
	if(fp==NULL)
	{
		perror("File does not exist");
	}

	data.lines = 0;
	while(fgets(buffer, MAX_CHAR, fp) != NULL)
	{
		data.lines++;
	}

	fseek(fp, 0, SEEK_SET);
	data.lines = 0;
	data.characters = 0;
	data.words = 0;
	while(1)
	{
		int ch = fgetc(fp);
		if(ch == EOF)
			break;
		data.characters++;
		if (ch == ' ' || ch == '\n')
			data.words++;
		if (ch == '\n')
			data.lines++;
	}
	pthread_mutex_unlock(&syn_mutex_1);
}

//Start function of thread_3
static void *thread_3(void *ptr)
{
	pthread_mutex_lock(&syn_mutex_2);
	printf("Entered thread 3. Waiting for SIGUSR2 signal\n");
	pthread_cond_wait(&t2_cond, &syn_mutex_2);			//Waits for user signal 
	printf("USR2 signal received\n");
	printf("Number of characters: %d\n", data.characters);
	printf("Number of words: %d\n", data.words);
	printf("Number of lines: %d\n", data.lines);

	pthread_mutex_unlock(&syn_mutex_2);
}



int main(int argc, char const *argv[])
{
    const char *message1 = "Entered Thread 1";
    const char *message2 = "Entered Thread 2";
	char sentence[MAX_CHAR];

	fp = fopen(argv[1], "w");
	printf("file name is %s\n", argv[1]);
	if(fp == NULL)
	{
		perror("could not open file");
		exit(1);
	}	
	

	printf("Enter the file contents\n");
	while(fgets(sentence, MAX_CHAR, stdin) != NULL)
	{
		fwrite(sentence, 1, strlen(sentence), fp);
	}
	fclose(fp);
	fp = NULL;

	//Registering functionality of the expected signals at runtime
	signal(SIGUSR1, signal_handler);
	signal(SIGUSR2, signal_handler);
	signal(SIGINT, signal_handler);
    
    pthread_mutex_init(&syn_mutex_1, NULL);
    pthread_mutex_init(&syn_mutex_2, NULL);

    pthread_cond_init(&t1_cond, NULL);
	//Creating thread 2 (processing thread)
 	if (pthread_create(&thread[0], NULL, thread_2, (void*)argv[1]))
    {
        perror("Thread1 creation failed");
        exit(EXIT_FAILURE);
    }

    pthread_cond_init(&t2_cond, NULL);
    //Creating thread 3 (reporting thread)
 	if (pthread_create(&thread[1], NULL, thread_3, (void*)argv[1]))
    {
        perror("Thread2 creation failed");
        exit(EXIT_FAILURE);
    }
    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);

    pthread_mutex_destroy(&syn_mutex_1);
    pthread_mutex_destroy(&syn_mutex_2);
    pthread_cond_destroy(&t1_cond);
    pthread_cond_destroy(&t2_cond);
    pthread_exit(NULL);

	return 0;
}
/*
* @file parent.c
* @brief Program for profiling process creation using fork() and exec()
*
* This source file contains code for profiling process creation in user space
*
* Tools used: GCC Compiler, make
* How to compile from source: gcc -o parent parent.c
* How to run: ./parent ./child
*
* @author Rishi Soni
* @date October 5 2017
* @version 1.0
*
*/
#include <stdio.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
clock_t start_t, end_t;
double total_t;
int status;

int spawn(char *program, char **arg_list)
{
	pid_t child_pid;

	start_t = clock();
	child_pid = fork();

	if (child_pid > 0)
	{
		waitpid(child_pid, &status, 0);
		end_t = clock();
	}

	else if (child_pid < 0)
	{
		exit(EXIT_FAILURE);
	}

	else
	{
		execvp(program, arg_list);
	}
}


int main(int argc, char const *argv[])
{
	char* arg_list[] = {
		"./child",
		NULL
	};
	spawn("./child", argv);
	printf("Number of clock ticks: %ld\n", (end_t - start_t));
	return 0;
}
/*
* @file beaglebone_server.c
* @brief Server TCP/IP source file for remote device driver access
*
* This source file communicates with a remote client and sends messages to it 
* to remotely send the results of control/read operations on the LED device driver 
* through TCP/IP sockets
*
* Tools used: GCC Compiler, GDB
* Command to compile from source: gcc -g beaglebone-server.c
* Command to run: ./a.out
*
* @author Rishi Soni
* @date November 19 2017
* @version 1.0
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <fcntl.h>
#include <arpa/inet.h>  //inet_addr
#include <dirent.h>

#define MAX_MESSAGE_LEN		(50)

int main(int argc, char const *argv[])
{
	struct sockaddr_in serverAddr;
	struct sockaddr_in serverStorage;
	int addr_size;
	int port, fd;
	int welcomeSocket, newSocket;
    char* ip_address = malloc(100);
	char message[MAX_MESSAGE_LEN];
	char choice[10];
	int command;
	char data[10];
	char buffer[1024];
	char data_buffer[100];

	char *data_ptr;
	char *extract_led = malloc(100);
	char *extract_freq = malloc(100);
	char *extract_duty = malloc(100);

	int string_len;


	  /*---- Create the socket. The three arguments are: ----*/
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    if (setsockopt(welcomeSocket, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");

    /*---- Configure settings of the server address struct ----*/
    serverAddr.sin_family = AF_INET;
    /* Set port number, using htons function to use proper byte order */
    serverAddr.sin_port = htons(8888);
    /* Set IP address to localhost */
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    /* Set all bits of the padding field to 0 */
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    /*---- Bind the address struct to the socket ----*/
    if(bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) != 0)
    {
    	printf("Bind error\n");
    }

    /*---- Listen on the socket, with 1000 max connection requests queued ----*/
    listen(welcomeSocket,5);

        /*---- Accept call creates a new socket for the incoming connection ----*/
    addr_size = sizeof(struct sockaddr_in);

    printf("Before accept()\n");
    newSocket = accept(welcomeSocket, (struct sockaddr *)&serverStorage,(socklen_t*)&addr_size);
    printf("New connection accepted\n");

    //Open device file
	fd = open("/dev/led_driver_Rishi", O_RDWR);
	printf( "Value of fd is: %d", fd );
	if( fd < 0 )
	{
		printf("Cannot open device \t");
		printf(" fd = %d \n",fd);
		return 0;
	}

	memset(message, 0, MAX_MESSAGE_LEN);
	memset(buffer, 0, 1024);

    while(1)
    {
    	memset(choice, 0, 10);
		printf("Server Menu: \n");
		recv(newSocket, &choice, 10, 0);			//Receive client menu choice
		printf("Client sends:%s\n", choice);
		
		//LED Control
		if(strcmp(choice, "1") == 0)
		{
			printf("LED control\n");
			memset(data, 0, 10);
			memset(message, 0, 50);
			// memset(choice, 0, 10);
			recv(newSocket, data, 10, 0);	//Receive '1' or '0' to turn LED ON or OFF

			if(strstr(data, "1") == 0 || strstr(data, "0") == 0)
			{
				printf("Setting LED to:%s\n", data);
				sprintf(message, "%s %d %s", choice, strlen(data)+1, data);
				write(fd, message, strlen(message) + 1);
				// memset(choice, 0, 10);

			}
		}

		//Frequency control
		if(strcmp(choice, "2") == 0)
		{
			printf("Frequency control\n");
			memset(data, 0, 10);
			memset(message, 0, 50);

			recv(newSocket, data, 10, 0);	//Receive '1' or '0' to turn LED ON or OFF
			if(atoi(data) > 500000 || atoi(data) <= 0)
			{
				printf("Entered value is not allowed \n");
				// continue;
			}
			else
			{
				sprintf(message, "%s %d %s", choice, strlen(data)+1, data);
				write(fd, message, strlen(message) + 1);
			}
		}

		//Duty Cycle control
		if(strcmp(choice, "3") == 0)
		{
			printf("Duty cycle control\n");
			memset(data, 0, 10);
			memset(message, 0, 50);

			recv(newSocket, data, 10, 0);
			if(atoi(data) > 100 || atoi(data) < 0)
			{
				printf("Entered value is not allowed \n");
				// continue;
			}
			else
			{
				sprintf(message, "%s %d %s", choice, strlen(data)+1, data);
				write(fd, message, strlen(message) + 1);
			}
		}

		if(strcmp(choice, "4") == 0)
		{
			printf("Reading state variables\n");
			memset(data, 0, 10);
			memset(message, 0, 50);
			strcpy(data, "4");

			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);

			write(fd, message, strlen(message));
			printf("after write\n");
			read( fd, data_buffer, 100);
			printf("after read\n");
			data_ptr = data_buffer;
			extract_led = strsep(&data_ptr, " ");
			extract_freq = strsep(&data_ptr, " ");
			extract_duty = strsep(&data_ptr, " \n");
			printf("\nState variables status:\n");
			printf("-----------------------------\n");
			printf("LED Status : %s\n", extract_led);
			printf("Frequency value : %s Hz\n", extract_freq);
			printf("Duty Cycle : %s%\n", extract_duty);

			string_len = strlen(extract_led) + 1;
			send(newSocket, &string_len, 4, 0);
			send(newSocket, extract_led, string_len, 0);

			string_len = strlen(extract_freq) + 1;
			send(newSocket, &string_len, 4, 0);
			send(newSocket, extract_freq, string_len, 0);

			string_len = strlen(extract_duty) + 1;
			send(newSocket, &string_len, 4, 0);
			send(newSocket, extract_duty, strlen(extract_duty) + 1, 0);
		}

		//reading LED status
		if(strcmp(choice, "5") == 0)
		{
			printf("Reading LED state variable\n");
			memset(data, 0, 10);
			memset(message, 0, 50);
			strcpy(data, "5");
			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);		

			write(fd, message, strlen(message));
			read( fd, data_buffer, 100);
			data_ptr = data_buffer;
			extract_led = strsep(&data_ptr, " ");
			printf("\nLED Status : %s\n", extract_led);
		}		

		//reading frequency value
		if(strcmp(choice, "6") == 0)
		{
			printf("Reading frequnecy value\n");
			memset(data, 0, 10);
			memset(message, 0, 50);
			strcpy(data, "6");
			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);		

			write(fd, message, strlen(message));
			read( fd, data_buffer, 100);
			data_ptr = data_buffer;
			extract_freq = strsep(&data_ptr, " ");
			printf("\nFrequency value : %s Hz\n", extract_freq);

			string_len = strlen(extract_freq) + 1;
			send(newSocket, &string_len, 4, 0);
			send(newSocket, extract_freq, string_len, 0);
		}	

		//reading duty cycle
		if(strcmp(choice, "7") == 0)
		{
			printf("Reading duty cycle value\n");
			memset(data, 0, 10);
			memset(message, 0, 50);
			strcpy(data, "7");
			sprintf(message, "%s %d %s", choice, strlen(data)+1, data);		

			write(fd, message, strlen(message));
			read( fd, data_buffer, 100);
			data_ptr = data_buffer;
			extract_duty = strsep(&data_ptr, " \n");
			printf("\nDuty Cycle : %s%\n", extract_duty);

			string_len = strlen(extract_duty) + 1;
			send(newSocket, &string_len, 4, 0);
			send(newSocket, extract_duty, strlen(extract_duty) + 1, 0);
		}		

    }

	return 0;
}

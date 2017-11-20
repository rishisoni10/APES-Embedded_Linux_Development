/*
* @file pc_client.c
* @brief Client TCP/IP source file for remote device driver access
*
* This source file communicates with the Beaglebone server and sends messages to it 
* to remotely control/read the LED device driver through TCP/IP sockets
*
* Tools used: GCC Compiler, GDB
* Command to compile from source: gcc -g pc_client.c
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

int main(int argc, char const *argv[])
{
	int port;
	int clientSocket;
	socklen_t addr_size;
	struct sockaddr_in serverAddr;
	char choice[10];
    char* ip_address = malloc(100);
	int sending, receiving;
	char data[10];

	char *extract_led = malloc(100);
	char *extract_freq = malloc(100);
	char *extract_duty = malloc(100);
	int string_len;
	

    addr_size = sizeof(serverAddr);

  	clientSocket= socket(PF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("192.168.7.2");
    // memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));  
    connect(clientSocket, (struct sockaddr *)&serverAddr, addr_size);
  	
  	//Cleanly exit the program. Close all sockets
    // signal(SIGINT, signal_handler);

    while(1)
    {
    	memset(choice, 0, 10);
    	memset(data, 0, 10);
		printf("------------------------------\n");
		printf("1 for LED control\n");
		printf("2 for setting frequency\n");
		printf("3 for setting duty cycle\n");
		printf("4 for reading all state variables\n");
		printf("5 for reading LED status\n");
		printf("6 for reading frequency value\n");
		printf("7 for reading duty cycle value\n");			
		printf("8 to exit\n");

		printf("\nPlease enter choice: ");

		fgets(choice, sizeof(choice), stdin);
        choice[strcspn(choice, "\n")] = 0;
        // command = atoi(choice);
        printf("Sending entered command to server:%s\n",choice);
        sending = send(clientSocket,choice,10,0);

        if(sending < 0)
        {
            perror("Send Error");
        }

        if(strstr(choice, "1"))
        {
			printf("Enter 1 to turn ON LED\n");
			printf("Enter 0 to turn OFF LED\n");
			fgets(data, sizeof(data), stdin);
        	data[strcspn(data, "\n")] = 0;	
			sending = send(clientSocket,data,10,0);        	
        }
        if(strstr(choice, "2"))
        {
			printf("\nEnter the frequency (in Hz)\n");
			fgets(data, sizeof(data), stdin);
        	data[strcspn(data, "\n")] = 0;	
			sending = send(clientSocket,data,10,0);        	
        }

        if(strstr(choice, "3"))
        {
			printf("\nEnter the duty cycle)\n");
			fgets(data, sizeof(data), stdin);
        	data[strcspn(data, "\n")] = 0;	
			sending = send(clientSocket,data,10,0);        	
        }

        if(strstr(choice, "4"))
        {
			printf("\nReading all state variables\n");

			recv(clientSocket, &string_len, 4, 0);
			recv(clientSocket, extract_led, string_len, 0);

			recv(clientSocket, &string_len, 4, 0);
			recv(clientSocket, extract_freq, string_len, 0);

			recv(clientSocket, &string_len, 4, 0);
			recv(clientSocket, extract_duty, string_len, 0);

			printf("\nState variables status:\n");
			printf("-----------------------------\n");
			printf("LED Status : %s\n", extract_led);
			printf("Frequency value : %s Hz\n", extract_freq);
			printf("Duty Cycle : %s\n", extract_duty);
        }

        if(strstr(choice, "5"))
        {
			printf("\nReading LED state\n");

			recv(clientSocket, &string_len, 4, 0);
			recv(clientSocket, extract_led, string_len, 0);

			printf("LED value : %s Hz\n", extract_led);
        }

        if(strstr(choice, "6"))
        {
			printf("\nReading frequency value\n");

			recv(clientSocket, &string_len, 4, 0);
			recv(clientSocket, extract_freq, string_len, 0);

			printf("Frequency value : %s Hz\n", extract_freq);
        }

        if(strstr(choice, "7"))
        {
			printf("\nReading duty cycle value\n");

			recv(clientSocket, &string_len, 4, 0);
			recv(clientSocket, extract_duty, string_len, 0);

			printf("Duty cycle value : %s Hz\n", extract_duty);
        }

        if(strstr(choice, "8"))
        {
			printf("\nExiting....\n");

			break;
        }

    }

	return 0;
}
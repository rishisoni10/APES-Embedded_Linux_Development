/*
* @file circbuff.c
* @brief Circular Buffer Library
*
* This source file provides useful functions for creating and using circular 
* buffers. This code can be run on any Linux - based system
*
* Tools used: GCC Compiler, GDB
* Command to compile from source: gcc circbuff.c -o circbuff -Wall -Werror
*
* @Code re-used from ESE course. Modified for this assignment
*
* @Link to original code: https://github.com/rishisoni10/ECEN5013/blob/Project2/Sources/cirbuf.c
*
* @author Rishi Soni
* @date September 7 2017
* @version 1.0
*
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "circbuff.h"

int main(void)
{
	uint32_t data, data2, j;
	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	status stat;
	printf("Enter the size of the buffer:\n");
	scanf("%d", &data);
	stat = allocate_c(&buffer,data);
	printf("Allocate status is %d\n", stat);

	uint8_t i = add_c(&buffer, 10);
	printf("Add status0 is %d\n", i);
	
	i = add_c(&buffer, 99);
	printf("Add status1 is %d\n", i);

	i = add_c(&buffer, 101);
	printf("Add status2 is %d\n", i);

	j = size(&buffer);
	printf("Number of itmes in the buffer is %d\n",j);

	i = remove_c(&buffer, &data2);
	printf("Remove status is %d\n", i);

	dump_c(&buffer);
	return 0;
}


status add_c(circbuffer_t **cptr, uint8_t data)
{
	circbuffer_t *c = *cptr;
	uint32_t* adr;
	adr = c->head + 1;
	if(adr >= c->buff + c->size) 
	{
		adr = c->buff;
	}
	if(Is_buffer_full(&c)) 
	{
		return FAILURE;
	}
	*c->head = data;
	c->head = adr;
	c->count++;

	return SUCCESS;
}


status remove_c(circbuffer_t **cptr, uint32_t *data)
{
	circbuffer_t *c = *cptr;
	uint32_t* adr;
	if(c->count == 0) 
	{
		printf("Buffer is empty. Nothing to remove\n");
		return FAILURE;
	}
	else 
	{
		*data = *(c->tail);
		printf("Removed data is %d\n", *data);
		*(c->tail) = 0;
		adr = c->tail + 1;
		if(adr >= c->buff + c->size) 
		{
			adr = c->buff;
		}
		c->tail = adr;
		c->count--;
		return SUCCESS;
	}
	
}


status Is_buffer_Empty(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	if (c->count == 0)
		return SUCCESS;
	else 
		return FAILURE;
}


status Is_buffer_full(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	if (c->count == c->size)
		return 1;
	else 
		return 0;
}


status allocate_c(circbuffer_t **cptr, uint32_t size)
{
	(*cptr)->buff = (uint32_t*)malloc(sizeof(uint32_t) * size);
    (*cptr)->size = size;						 //total size of buffer
    (*cptr)->head = (*cptr)->buff;					 //initially head and tail are at buff
    (*cptr)->tail = (*cptr)->buff;
    (*cptr)->count = 0;			   			 //current number of items in buffer

    if ((*cptr) != NULL)
    	return SUCCESS;
    else
    	return FAILURE;
}


status destroy_c(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	free(c->buff);
	return SUCCESS;
}


uint32_t size(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	return(c->count);
}

void dump_c(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	uint32_t data = c->count;
	printf("Data dump: \n");
	if(c->count == 0) 
	{
		printf("Buffer empty. Nothing to print\n");
	}
	else 
	{
		while(data > 0)
		{
			printf("%d\n", *(c->tail));
			c->tail++;
			data--;
		}
	}
}
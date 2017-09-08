#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "circbuff.h"

int main(void)
{
	// uint8_t data = 0;
	uint32_t j;
	circbuffer_t *buffer = NULL;
	buffer= (circbuffer_t*)malloc(sizeof(circbuffer_t));

	status stat;
	stat = allocate_c(&buffer,2);
	printf("Allocate status is %d\n", stat);

	uint8_t i = add_c(&buffer, 10);
	printf("Add status0 is %d\n", i);
	
	i = add_c(&buffer, 99);
	printf("Add status1 is %d\n", i);

	j = size(&buffer);
	printf("Number of itmes in the buffer is %d\n",j);

	// i = remove_c(&buffer, &data);
	// printf("Remove status is %d\n", i);

	// i = remove_c(&buffer, &data);
	// printf("Remove status is %d\n", i);
	dump_c(&buffer);

	bool k = Is_buffer_Empty(&buffer);
	printf("Buffer empty status (bool): %d\n", k);

	k = Is_buffer_full(&buffer);
	printf("Buffer full status (bool): %d\n", k);


	return 0;

}

/*******************************************************************/
/*description: This function adds a new data to the given circular  */
/*	      buffer						   */
/*parameter: data to be added, the buffer address  	           */
/*return:    0 : if the buffer is full and a wrap fill occurs	   */
/*	     1 : otherwise					   */
/*******************************************************************/
uint8_t add_c(circbuffer_t **cptr, uint8_t data)
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

/*******************************************************************/
/*description: This function removes the oldest data from the given */
/*	      circular buffer					             */
/*parameter: the buffer address and pointer to location where the  */
/*           data should be kept.				   		 */
/*return:    0 : if the buffer is empty.			   		 */
/*	     1 : otherwise					   		 */
/*******************************************************************/
uint8_t remove_c(circbuffer_t **cptr, uint8_t *data)
{
	circbuffer_t *c = *cptr;
	uint32_t* adr;
	if(c->count == 0) 
	{
		return (0);
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
		return(1);
	}
	
}


/*******************************************************************/
/*description: This function tells if the circular buffer is empty  */
/*parameter: the buffer address 		 	           		 */
/*return:    1 : if the buffer is empty				   	 */
/*	     0 : otherwise					   		 */
/*******************************************************************/
bool Is_buffer_Empty(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	if (c->count == 0)
		return 1;
	else 
		return 0;
}

/*******************************************************************/
/*description: This function tells if the circular buffer is full   */
/*parameter: the buffer address 		 	           		 */
/*return:    1 : if the buffer is full				   	 */
/*	     0 : otherwise					    		 */
/*******************************************************************/
bool Is_buffer_full(circbuffer_t **cptr)
{
	circbuffer_t *c = *cptr;
	if (c->count == c->size)
		return 1;
	else 
		return 0;
}


/*---------------------------------------------------------------------------
 *uint8_t allocate(circbuffer_t **cptr,uint8_t size)
 *This function is can be used to initialize circular buffer of size "size"
 ---------------------------------------------------------------------------*/
status allocate_c(circbuffer_t **cptr, uint8_t size)
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

/*---------------------------------------------------------------------------
 *status destroy(circbuffer_t *cptr)
 *This function destroys or frees up the heap memory assigned to the buffer
 ---------------------------------------------------------------------------*/
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
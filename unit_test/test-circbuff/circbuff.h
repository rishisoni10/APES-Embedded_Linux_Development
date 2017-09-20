#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_

typedef struct 
{
	uint32_t* buff; //The buffer address
	uint32_t* head; //The buffer start address
	uint32_t* tail; //The buffer end address
	uint32_t size;  //The total capacity of the buffer
	uint32_t count; //Total number of elements currently in buffer
} circbuffer_t;

typedef enum
{
    SUCCESS = 1,
    FAILURE = 2, 
    BUFFER_EMPTY = 3, 
    BUFFER_NOT_EMPTY = 4,
    BUFFER_FULL = 5, 
    BUFFER_NOT_FULL = 6,
    temp = 7
}status;

/*
* @brief Adds a new data in the given circular buffer
*	    
* Given a double pointer to a circular buffer, this function
* will add a data element at the current head of the circular buffer
*
* @param **ptr Double Pointer to the circular buffer
* @param *data Pointer to the data element
*
* @return status FAILURE if the buffer is full. SUCCESS otherwise
*/
status add_c(circbuffer_t **cptr, uint8_t data);

/*
* @brief Removes oldest data in the given circular buffer
*	     
* Given a double pointer to a circular buffer, this function
* will remove the oldest data element from the circular buffer
*
* @param **ptr Double Pointer to the circular buffer
* @param *data Pointer to location where data is stored
*           
* @return status FAILURE if the buffer is empty. SUCCESS otherwise
*/
status remove_c(circbuffer_t **cptr, uint32_t *data);

/*
* @brief Circular buffer empty status
*	     
* Given a double pointer to a circular buffer, this function
* will check if the given circular buffer is empty
*
* @param **ptr Double Pointer to the circular buffer
*           
* @return status FAILURE if the buffer is not empty. SUCCESS otherwise
*/
status Is_buffer_Empty(circbuffer_t **cptr);

/*
* @brief Circular buffer full status
*	     
* Given a double pointer to a circular buffer, this function
* will check if the given circular buffer is full
*
* @param **ptr Double Pointer to the circular buffer
*           
* @return status FAILURE if the buffer is not full. SUCCESS otherwise
*/
status Is_buffer_full(circbuffer_t **cptr);

/*
* @brief Dynamic memory allocation for circular buffer
*	     
* Given a double pointer to a circular buffer, this function
* will allocate memory for a circular buffer, with a user - defined size
*
* @param **ptr Double Pointer to the circular buffer
* @param size User - defined size of circular buffer
*
* @return status FAILURE if memory allocation failed. SUCCESS otherwise
*/
status allocate_c(circbuffer_t **cptr,uint32_t size);


/*
* @brief Destroys the circular buffer
*
* Given a double pointer to a circular buffer, this function
* will delete the entire circular buffer
*
* @param **ptr Double Pointer to the circular buffer
*
* @return status Status of the destruction.
*/
status destroy_c(circbuffer_t **cptr);

/*
* @brief Curent number of items stored in the buffer
*
* Given a double pointer to a circular buffer, this function
* will return the current number of items stored in the circular buffer
*
* @param **ptr Double Pointer to the circular buffer
*
* @return count Number of items in the circular buffer
*/
uint32_t size(circbuffer_t **cptr);

/*
* @brief Dumps all circular buffer elements
*
* Given a double pointer to a circular buffer, this function
* will print all the current data elements in the circular buffer
*
* @param **ptr Double Pointer to the circular buffer
*
* @return void
*/
void dump_c(circbuffer_t **cptr);

#endif
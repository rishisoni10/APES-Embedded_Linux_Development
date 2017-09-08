#ifndef SOURCES_CIRCBUFF_H_
#define SOURCES_CIRCBUFF_H_

typedef struct 
{
	uint32_t* buff; /*The buffer address*/
	uint32_t* head; /*The buffer start address*/
	uint32_t* tail; /*The buffer end address*/
	uint32_t size; /*The total capacity of the buffer*/
	uint32_t count; /*Total number of elements currently in buffer*/
} circbuffer_t;

typedef enum
{
    SUCCESS,
    FAILURE
}status;


uint8_t add_c(circbuffer_t **cptr, uint8_t data);
uint8_t remove_c(circbuffer_t **cptr, uint8_t *data);
bool Is_buffer_Empty(circbuffer_t **cptr);
bool Is_buffer_full(circbuffer_t **cptr);
status allocate_c(circbuffer_t **cptr,uint8_t size);
status destroy_c(circbuffer_t **cptr);
uint32_t size(circbuffer_t **cptr);
void dump_c(circbuffer_t **cptr);


#endif /* SOURCES_CIRBUF_H_ */
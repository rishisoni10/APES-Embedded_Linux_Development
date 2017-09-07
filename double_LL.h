#ifndef __DOUBLE_LL_H_
#define __DOUBLE_LL_H_


struct Node
{
    uint32_t data;
    struct Node *prev;
    struct Node *next;
};

typedef enum
{
    SUCCESS,
    FAILURE
}status;

status destroy(struct Node**);

status add_node(struct Node**, uint32_t, uint8_t);

status remove_node(struct Node**, uint32_t*, uint8_t);

uint8_t * search(struct Node**, uint32_t);

uint32_t size(struct Node**);

void display(struct Node**);

#endif
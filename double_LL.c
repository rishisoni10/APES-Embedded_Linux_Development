/*
* @file double_LL.c
* @brief Doubly Linked List Library
*
* This source file provides useful functions for creating and using doubly 
* linked lists. This code can be run on any Linux - based system
*
* Tools used: GCC Compiler, GDB
* Command to compile from source: gcc double_LL.c -o double_LL -Wall -Werror
*
* Reference: http://www.geeksforgeeks.org/doubly-linked-list/
*
* @author Rishi Soni
* @date September 6 2017
* @version 1.0
*
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "double_LL.h"

int main(void)
{
    status stat;
    uint32_t *data = NULL;
    struct Node *head = NULL; 
    stat = add_node(&head, 10, 1);
   
    display(&head);
    stat = add_node(&head, 11, 1);
   
    display(&head);
    stat = add_node(&head, 20, 2);
   
    display(&head);
    stat = add_node(&head, 97, 3);
    stat = add_node(&head, 28, 4);
    display(&head);

    printf("Status: %d\n", stat);
    printf("Number of nodes is: %d\n",size(&head));
   
    remove_node(&head, data, 3);
    printf("After removing index 3, list is:\n");
    display(&head);
    
    uint8_t *index = NULL;
    index = search(&head, 11);
    printf("Node index is %d\n", *index);

    stat = destroy(&head);
    display(&head);

}

status add_node(struct Node **head, uint32_t data, uint8_t index)
{
    //If no node exists in the D_LL, then add first node
    if(*head == NULL)
    {
        (*head) = (struct Node*)malloc(sizeof(struct Node));
        (*head)->data = data;
        (*head)->next = NULL;
        (*head)->prev = NULL;
        return SUCCESS;
    }
    
    //Nodes exist in the D_LL
    else
    {
        struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
        temp->data = data;
        temp->next = NULL;
        temp->prev = NULL;
        //Adding node at the beginning of the LL
        if (index == 1)
        {
            temp->next = *head;   //New node points to first (old) node
            temp->prev = NULL;
            *head = temp;         //head points to new node, now the first  
        }
        else
        {
            struct Node *temp2 = *head;
            while(index - 1 > 1)
            {
                temp2 = temp2->next;
                index--;
            }
            temp->next = temp2->next;
            temp->prev = temp2;
            temp2->next = temp;
        }
        
    }
   
    return SUCCESS;     
}

uint32_t size(struct Node **head)
{
    uint32_t num;
    struct Node *temp = *head;
    while(temp != NULL)
    {
        temp = temp->next;
        num++;
    }
    return num;
}

uint8_t * search(struct Node**head, uint32_t data)
{
    struct Node *temp = *head;
    uint8_t *index = malloc(sizeof(*index));
    *index = 1;
    while(temp != NULL)
    {
        if(temp->data == data)
        {
            printf("Found the fucking number\n");
            break;          
        }
        temp = temp->next;
        *index = *index + 1;
    }
    return index;
}

void display(struct Node **head)
{
    struct Node *temp = *head;
    if (temp == NULL)
    {
        printf("No nodes exist\n");
    }
    while(temp != NULL)
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


status remove_node(struct Node** head, uint32_t* data, uint8_t index)
{
    struct Node *temp  = *head;
    uint32_t i = size(head);
    if (index == 1)
    {
        *data = temp->data;
        *head = temp->next;
        free(temp);
    }

    else
    {
        struct Node *prev_node = *head;
        struct Node *temp2 = *head;

        while(index > 1)
        {
            prev_node = temp;
            temp = temp->next;
            temp2 = temp->next;
            index--;
        }
        prev_node->next = temp2;
        temp2->prev = prev_node;
        free(temp);
    }

    if (i > size(head))
        return SUCCESS;
    else 
        return FAILURE;
}


status destroy(struct Node **head)
{
    struct Node *temp = *head;
    struct Node *temp2;

    while(temp != NULL)
    {
        temp2 = temp->next;
        free(temp);
        temp = temp2;
    }
    *head = NULL;
    return SUCCESS;
}
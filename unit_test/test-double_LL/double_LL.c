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

status search(struct Node**head, uint32_t data, uint32_t *index)
{
    struct Node *temp = *head;
    uint32_t pos = 1, flag = 0;
    while(temp != NULL)
    {
        if(temp->data == data)
        {
            flag = 1;
            *index = pos;
            break;          
        }
        temp = temp->next;
        pos++;
    }

    if(flag)
        return DATA_FOUND;
    else
        return DATA_NOT_FOUND;
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
    uint32_t length = size(head);

    if (length == 0)
        return EMPTY_LL;

    if(index > length + 1 || index < 1)
        return OUT_OF_BOUNDS;

    if (index == 1)
    {
        *head = temp->next;
        (temp->next)->prev = NULL;
        *data = temp->data;
        free(temp);
        return HEAD_REMOVE_SUCCESS;
    }

    else
    {
        struct Node *prev_node = *head;
        struct Node *temp2 = *head;

        while(index > 1 && temp2 != NULL)
        {
            prev_node = temp;
            temp = temp->next;
            temp2 = temp->next;
            index--;
        }

        if(temp2 == NULL)
        {
            prev_node->next = NULL;
            free(temp);
            return TAIL_REMOVE_SUCCESS;
        }
        else
        {
            prev_node->next = temp2;
            temp2->prev = prev_node;
            free(temp);
        }
    }

    if (length > size(head))
        return REMOVE_SUCCESS;
    else 
        return REMOVE_FAILURE;
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
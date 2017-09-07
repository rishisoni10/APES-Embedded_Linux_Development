/*
* @file double_LL.h
* @brief Doubly Linked List Library
*
* This header file provides function declarations for the functions used to create 
* the doubly linked list library
*
* Tools used: GCC Compiler, GDB
* Command to compile from source: gcc double_LL.c -o double_LL -Wall -Werror
* @author Rishi Soni
* @date September 6 2017
* @version 1.0
*
*/

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

/**
* @brief Destroys the linked list
*
* Given a double pointer to the head of the linked list, this function
* will delete all the nodes in the linked list
*
* @param **ptr Double Pointer to the head of the linked list
*
* @return status Status of the destruction.
*/
status destroy(struct Node**);

/**
* @brief Adds a node to the linked list
*
* Given a double pointer to the head of the linked list, this function
* will add a node at the required index (starting from 1) in the linked list
*
* @param **ptr  Double Pointer to the head of the linked list\
* @param data   Data that needs to be in the new node
* @param index  Position in the linked list where the new node should be added
*
* @return status Status of the new node addition
*/
status add_node(struct Node**, uint32_t, uint8_t);

/**
* @brief Removes a node from the linked list
*
* Given a double pointer to the head of the linked list, this function
* will remove a node at the required index (starting from 1) in the linked list
*
* @param **ptr  Double Pointer to the head of the linked list\
* @param ptr    Deleted data stored in a data pointer
* @param index  Position (node) in the linked list which is to be deleted
*
* @return status Status of the new node addition
*/
status remove_node(struct Node**, uint32_t*, uint8_t);

/**
* @brief Searches for data in the linked list
*
* Given a double pointer to the head of the linked list, this function
* will search for the first instance of the required data in the linked list.
*
* @param **ptr  Double Pointer to the head of the linked list
* @param data   Data item to be searched
*
* @return ptr   Index of the node through a pointer
*/
uint8_t * search(struct Node**, uint32_t);

/**
* @brief Reports the size of the linked list
*
* Given a double pointer to the head of the linked list, this function
* will return the current number of nodes in the linked list
*
* @param **ptr  Double Pointer to the head of the linked list\
*
* @return num   Number of nodes in the linked list
*/
uint32_t size(struct Node**);

/**
* @brief Prints the contents of the linked list
*
* Given a double pointer to the head of the linked list, this function
* will print the contents of the nodes in the linked list
*
* @param **ptr  Double Pointer to the head of the linked list\
*
* @return void 
*/
void display(struct Node**);

#endif
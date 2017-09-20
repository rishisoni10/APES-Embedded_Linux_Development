#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "double_LL.h"

void test_add_node_multiple(void **state)
{
	status stat;
	uint32_t data;
    struct Node *head = NULL; 
    for (uint8_t i = 1; i < 10; i++)
    {
    	data = i + 33;
    	stat = add_node(&head, data, i);
    }
    display(&head);
    assert_int_equal(stat,SUCCESS);
}


void test_search_data_exist(void **state)
{
	status stat;
	uint32_t index;
    struct Node *head = NULL; 
    for (uint8_t i = 1; i < 10; i++)
    {
    	add_node(&head, i + 33, i);
    }
    stat = search(&head, 40, &index);
    assert_int_equal(stat,DATA_FOUND);	
}

void test_search_data_not_exist(void **state)
{
	status stat;
	uint32_t index;
    struct Node *head = NULL; 
    for (uint8_t i = 1; i < 10; i++)
    {
    	add_node(&head, i + 33, i);
    }
    stat = search(&head, 100, &index);
    assert_int_equal(stat,DATA_NOT_FOUND);	
}

void test_add_node_head(void **state)
{
	status stat;
	uint32_t index; 
    struct Node *head = NULL; 

    //Populating the D_LL
  	for (uint8_t i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    
    //Adding element in the beginning (head) and checking its status
    stat = add_node(&head, 10, 1);
    assert_int_equal(stat, SUCCESS);
    //Searching the added data in the D_LL
    stat = search(&head, 10, &index);
    //Check if data found at index => head
    assert_int_equal(1, index);
    //Check if return status of search function is correct
    assert_int_equal(stat,DATA_FOUND);
}

void test_add_node_tail(void **state)
{
	status stat;
	uint32_t index, length; 
    struct Node *head = NULL; 

    //Populating the D_LL
  	for (uint8_t i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    

    //Checking number of nodes in the D_LL
    length = size(&head);
    //Adding element in the end (tail) and checking its status
    stat = add_node(&head, 10, length+1);
    assert_int_equal(stat, SUCCESS);
    display(&head);
    //Searching the added data in the D_LL
    stat = search(&head, 10, &index);
    //Check if data found at index => head
    assert_int_equal(length+1, index);
    //Check if return status of search function is correct
    assert_int_equal(stat,DATA_FOUND);
}

void test_add_node_middle(void **state)
{
	status stat;
	uint32_t index, length; 
    struct Node *head = NULL; 

    //Populating the D_LL
  	for (uint8_t i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    

    //Checking number of nodes in the D_LL
    length = size(&head);
    //Adding element anywhere in the middle (here, length - 5) and checking its status
    stat = add_node(&head, 10, length - 5);
    assert_int_equal(stat, SUCCESS);
    display(&head);
    //Searching the added data in the D_LL
    stat = search(&head, 10, &index);
    //Check if data found at index => head
    assert_int_equal(length-5, index);
    //Check if return status of search function is correct
    assert_int_equal(stat,DATA_FOUND);
}

void test_size(void **state)
{
	status stat;
	uint8_t i;
	uint32_t length; 
    struct Node *head = NULL; 

    //Populating the D_LL with 9 elements
  	for (i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    
    assert_int_equal(stat,SUCCESS);

    //Checking number of nodes in the D_LL
    length = size(&head);

    //Checking if number of added elements and return value of size() is same
    assert_int_equal(9, length);
}


void test_remove_node(void **state)
{
	status stat;
	uint32_t data;
    struct Node *head = NULL; 

    //Populating the D_LL adn checking it
  	for (uint8_t i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    
    assert_int_equal(stat,SUCCESS);

	stat = remove_node(&head, &data, 6);
	assert_int_equal(stat, REMOVE_SUCCESS);
}

void test_remove_head_node(void **state)
{
	status stat;
	uint32_t data;
    struct Node *head = NULL; 

    //Populating the D_LL adn checking it
  	for (uint8_t i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    
    assert_int_equal(stat,SUCCESS);

	stat = remove_node(&head, &data, 1);
	assert_int_equal(stat, HEAD_REMOVE_SUCCESS);
}

void test_remove_tail_node(void **state)
{
	status stat;
	uint32_t data;
	// uint32_t index; 
    struct Node *head = NULL; 

    //Populating the D_LL adn checking it
  	for (uint8_t i = 1; i < 10; i++)
    {
    	stat = add_node(&head, i + 33, i);
    }    
    assert_int_equal(stat,SUCCESS);

	stat = remove_node(&head, &data, 9);
	assert_int_equal(stat, TAIL_REMOVE_SUCCESS);
}

void test_remove_node_empty_LL(void **state)
{
	status stat;
	uint32_t data;
    struct Node *head = NULL;
	stat = remove_node(&head, &data, 1);
	assert_int_equal(stat, EMPTY_LL);
}

void test_destroy(void **state)
{
	status stat;
	uint32_t data;
    struct Node *head = NULL; 
    for (uint8_t i = 1; i < 10; i++)
    {
    	data = i + 33;
    	stat = add_node(&head, data, i);
    }
    stat = destroy(&head);
    assert_int_equal(stat,SUCCESS);
    assert_int_equal(head,NULL);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_add_node_multiple),
    cmocka_unit_test(test_search_data_exist),
    cmocka_unit_test(test_search_data_not_exist),
    cmocka_unit_test(test_size),
    cmocka_unit_test(test_add_node_head),
	cmocka_unit_test(test_add_node_tail),
	cmocka_unit_test(test_add_node_middle),
	cmocka_unit_test(test_remove_node),
	cmocka_unit_test(test_remove_head_node),
	cmocka_unit_test(test_remove_tail_node),
	cmocka_unit_test(test_remove_node_empty_LL),
	cmocka_unit_test(test_destroy),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}

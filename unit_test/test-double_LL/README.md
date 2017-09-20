#Unit Testing Doubly Linked List using cmocka

To test the DLL functions, the cmocka testing framework was used. The following tests were conducted:

* test_add_node_multiple: Adding multiple nodes at the same time
* test_search_data_exist: Check if given data exists
* test_search_data_not_exist: Check if given data does not exist
* test_size: Check if the size of the DLL returned is correct
* test_add_node_head: Add a node to the head and check if successfully added
* test_add_node_tail: Add a node to the tail and check if successfully added
* test_add_node_middle: Add a node in the middle and check if successfully added
* test_remove_node: Remove node at the corresponding index number
* test_remove_head_node: Remove the head node and verify
* test_remove_tail_node: Remove the tail node and verify
* test_remove_node_empty_LL: Check if function work correctly when trying to remove from an empty DLL
* test_destroy: Check if the memory for the DLL is deallocated successfully. 

The unit testing tutorial put up on GitHub by Professor Fosdick was used as a reference. Necessary changes were made in the Makefile for building the cmocka libraries and compiling and running the test code. 

To run the tests, run the following command in the terminal:

* Building cmocka
```SHELL
make cmocka
```
* Building and running test
```SHELL
make test
```


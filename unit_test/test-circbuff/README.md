#Unit Testing Circular Buffer using cmocka

To test the CB functions, the cmocka testing framework was used. The following tests were conducted:

* test_allocate: Verfiy memory allocation for the CB
* test_empty_buffer: Verify if an empty buffer is actually empty using the appropriate function
* test_full_buffer: Verify if a full buffer is actually full using the appropriate function
* test_add_data: Verify that data can be added in the CB
* test_add_when_buffer_full: Verify status when trying to add data to a full CB
* test_remove_data: Verify remove data operation from CB
* test_remove_empty_buff: Verify status when trying to remote data from a full CB
* test_size: Verify that the correct size is returned
* test_destroy: Verify that CB memory has been freed. 

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


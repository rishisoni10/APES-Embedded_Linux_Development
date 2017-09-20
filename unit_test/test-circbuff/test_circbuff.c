#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "circbuff.h"


void test_allocate(void **state)
{
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));
	stat = allocate_c(&buffer,5);
	assert_int_equal(stat, SUCCESS);
}

void test_empty_buffer(void **state)
{
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	stat = allocate_c(&buffer, 0);
	assert_int_equal(stat, SUCCESS);
	stat = Is_buffer_Empty(&buffer);
	assert_int_equal(stat, BUFFER_EMPTY);
}

void test_full_buffer(void **state)
{
	uint8_t i;
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	stat = allocate_c(&buffer, 5);
	assert_int_equal(stat, SUCCESS);

	for (i = 0; i < 5; ++i)
	{
		stat = add_c(&buffer, i+3);
		assert_int_equal(stat, SUCCESS);
	}
	assert_int_equal(Is_buffer_full(&buffer), BUFFER_FULL);
}

void test_add_data(void **state)
{
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	stat = allocate_c(&buffer, 5);
	assert_int_equal(stat, SUCCESS);
	stat = add_c(&buffer, 10);
	assert_int_equal(stat, SUCCESS);
}

void test_add_when_buffer_full(void **state)
{
	uint8_t i;
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	stat = allocate_c(&buffer, 5);
	assert_int_equal(stat, SUCCESS);

	for (i = 0; i < 5; ++i)
	{
		stat = add_c(&buffer, i+3);
		assert_int_equal(stat, SUCCESS);
	}
	stat = add_c(&buffer, 10);
	assert_int_equal(stat, FAILURE);
}

void test_remove_data(void **state)
{
	uint8_t i;
	uint32_t data;
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	stat = allocate_c(&buffer, 4);
	assert_int_equal(stat, SUCCESS);

	for (i = 0; i < 4; ++i)
	{
		stat = add_c(&buffer, i+3);
		assert_int_equal(stat, SUCCESS);
	}
	stat = remove_c(&buffer, &data);
	assert_int_equal(stat, SUCCESS);	
}

void test_remove_empty_buff(void **state)
{
	status stat;
	uint32_t data;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));
	stat = allocate_c(&buffer,0);
	assert_int_equal(stat, SUCCESS);
	
	stat = remove_c(&buffer, &data);
    assert_int_equal(stat,FAILURE);
}

void test_size(void **state)
{
	uint8_t i;
	uint32_t num;
	status stat;
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));

	stat = allocate_c(&buffer, 5);
	assert_int_equal(stat, SUCCESS);

	for (i = 0; i < 4; ++i)
	{
		stat = add_c(&buffer, i+3);
		assert_int_equal(stat, SUCCESS);
	}
	num = size(&buffer);
	assert_int_equal(num, 4);	
}

void test_destroy(void **state)
{
	uint8_t i;
	
 	circbuffer_t *buffer = NULL;
	buffer = (circbuffer_t*)malloc(sizeof(circbuffer_t));
	status stat;
	stat = allocate_c(&buffer, 5);
	assert_int_equal(stat, SUCCESS);

	for (i = 0; i < 4; ++i)
	{
		stat = add_c(&buffer, i+3);
		assert_int_equal(stat, SUCCESS);
	}
	assert_int_equal(stat, SUCCESS);
	stat = destroy_c(&buffer);
	assert_int_equal(buffer, NULL);
}

int main(int argc, char **argv)
{
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_allocate),
    cmocka_unit_test(test_empty_buffer),
    cmocka_unit_test(test_full_buffer),
    cmocka_unit_test(test_add_data),
    cmocka_unit_test(test_add_when_buffer_full),
    cmocka_unit_test(test_remove_data),
    cmocka_unit_test(test_remove_empty_buff),
    cmocka_unit_test(test_size),
    cmocka_unit_test(test_destroy),
  };

  return cmocka_run_group_tests(tests, NULL, NULL);
}


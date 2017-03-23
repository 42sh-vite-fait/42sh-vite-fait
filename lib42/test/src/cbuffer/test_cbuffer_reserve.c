#include "header.h"

t_cbuffer	buffer;

static void		setup(size_t len, size_t elem_size, void (*del_func)(void *))
{
	buffer.data = malloc(len * elem_size);
	buffer.len = 0;
	buffer.capacity = len;
	buffer.elem_size = elem_size;
	buffer.delete_func = del_func;
	buffer.start = 0;
	buffer.end = 0;
}

static void		teardown(void)
{
	free(buffer.data);
}

static void	test_00_cbuffer_reserveStartBeforeEnd(void)
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 10; ++i)
	{
		cbuffer_push_back(&buffer, &i);
	}

	{
		int front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(0, ==, front);

		int n = *((int*)cbuffer_get_at(&buffer, 5));
		v_assert_int(5, ==, n);

		int back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(9, ==, back);
	}

	v_assert_size_t(10, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	buffer = *cbuffer_reserve(&buffer, 10);
	{
		int front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(0, ==, front);

		int n = *((int*)cbuffer_get_at(&buffer, 5));
		v_assert_int(5, ==, n);

		int back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(9, ==, back);
	}

	v_assert_size_t(10, ==, buffer.len);
	v_assert_size_t(20, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_01_cbuffer_reserveStartAfterEnd(void)
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 8; ++i)
	{
		cbuffer_push_front(&buffer, &i);
	}

	{
		int front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(7, ==, front);

		int n = *((int*)cbuffer_get_at(&buffer, 4));
		v_assert_int(3, ==, n);

		int back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(0, ==, back);
	}

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	buffer = *cbuffer_reserve(&buffer, 10);
	{
		int front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(7, ==, front);

		int n = *((int*)cbuffer_get_at(&buffer, 4));
		v_assert_int(3, ==, n);

		int back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(0, ==, back);
	}

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(18, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_02_cbuffer_reserveEmptyBuffer(void)
{
	setup(10, sizeof(int), NULL);

	v_assert_ptr(NULL, ==, cbuffer_get_back(&buffer));

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	buffer = *cbuffer_reserve(&buffer, 20);

	v_assert_ptr(NULL, ==, cbuffer_get_back(&buffer));

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(20, ==, buffer.capacity);

	teardown();
	VTS;
}

void	suite_cbuffer_reserve(void)
{
	test_00_cbuffer_reserveStartBeforeEnd();
	test_01_cbuffer_reserveStartAfterEnd();
	test_02_cbuffer_reserveEmptyBuffer();

	VSS;
}

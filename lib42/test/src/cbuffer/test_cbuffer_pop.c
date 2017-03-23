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

static void	test_00_cbuffer_popBackInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int n = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(a, ==, n);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_back(&buffer);

	v_assert_ptr(NULL, ==, cbuffer_get_back(&buffer));
	v_assert_ptr(NULL, ==, cbuffer_get_front(&buffer));
	v_assert_ptr(NULL, ==, cbuffer_get_at(&buffer, 0));

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_01_cbuffer_popBackWithTwoInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(b, ==, back);

	v_assert_size_t(2, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_back(&buffer);
	{
		front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(a, ==, front);
		back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(a, ==, back);
	}

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_02_cbuffer_popBackEqualMaxLenInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	cbuffer_push_front(&buffer, &a);
	cbuffer_push_front(&buffer, &b);
	cbuffer_push_front(&buffer, &c);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_back(&buffer);
	cbuffer_pop_back(&buffer);
	{
		int front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(c, ==, front);
		int back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(c, ==, back);
	}

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_03_cbuffer_popBackMoreThanLenInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_back(&buffer);
	cbuffer_pop_back(&buffer);
	cbuffer_pop_back(&buffer);
	cbuffer_pop_back(&buffer);
	cbuffer_pop_back(&buffer);
	cbuffer_pop_back(&buffer);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_04_cbuffer_popFrontInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(a, ==, back);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int n = *((int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(a, ==, n);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_front(&buffer);

	v_assert_ptr(NULL, ==, cbuffer_get_back(&buffer));
	v_assert_ptr(NULL, ==, cbuffer_get_front(&buffer));
	v_assert_ptr(NULL, ==, cbuffer_get_at(&buffer, 0));

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_05_cbuffer_popFrontWithTwoInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);

	int front = *((int*)cbuffer_get_front(&buffer));
	v_assert_int(a, ==, front);

	int back = *((int*)cbuffer_get_back(&buffer));
	v_assert_int(b, ==, back);

	v_assert_size_t(2, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_front(&buffer);
	{
		front = *((int*)cbuffer_get_front(&buffer));
		back = *((int*)cbuffer_get_back(&buffer));

		v_assert_int(front, ==, back);
		v_assert_int(b, ==, front);
		v_assert_int(b, ==, back);
	}

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_05_cbuffer_popFrontEqualMaxLenInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	int b = 11;
	int c = 12;
	cbuffer_push_back(&buffer, &a);
	cbuffer_push_back(&buffer, &b);
	cbuffer_push_back(&buffer, &c);

	v_assert_size_t(3, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_front(&buffer);
	cbuffer_pop_front(&buffer);
	{
		int front = *((int*)cbuffer_get_front(&buffer));
		v_assert_int(c, ==, front);
		int back = *((int*)cbuffer_get_back(&buffer));
		v_assert_int(c, ==, back);
	}

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_07_cbuffer_popFrontMoreThanLenInt(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	cbuffer_pop_front(&buffer);
	cbuffer_pop_front(&buffer);
	cbuffer_pop_front(&buffer);
	cbuffer_pop_front(&buffer);
	cbuffer_pop_front(&buffer);
	cbuffer_pop_front(&buffer);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_08_cbuffer_popFrontCheckReturn(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int *r = cbuffer_pop_front(&buffer);
	v_assert_int(a, ==, *r);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_09_cbuffer_popBackCheckReturn(void)
{
	setup(3, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int a = 10;
	cbuffer_push_back(&buffer, &a);

	v_assert_size_t(1, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	int *r = cbuffer_pop_back(&buffer);
	v_assert_int(a, ==, *r);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(3, ==, buffer.capacity);

	teardown();
	VTS;
}

void	suite_cbuffer_pop(void)
{
	test_00_cbuffer_popBackInt();
	test_01_cbuffer_popBackWithTwoInt();
	test_02_cbuffer_popBackEqualMaxLenInt();
	test_03_cbuffer_popBackMoreThanLenInt();

	test_04_cbuffer_popFrontInt();
	test_05_cbuffer_popFrontWithTwoInt();
	test_05_cbuffer_popFrontEqualMaxLenInt();
	test_07_cbuffer_popFrontMoreThanLenInt();

	test_08_cbuffer_popFrontCheckReturn();
	test_09_cbuffer_popBackCheckReturn();

	VSS;
}

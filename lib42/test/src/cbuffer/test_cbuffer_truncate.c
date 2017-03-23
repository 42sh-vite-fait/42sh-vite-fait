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

static void	test_00_cbuffer_truncateFromBack(void)
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 8; ++i)
	{
		cbuffer_push_back(&buffer, &i);
	}

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_ptr(NULL, !=, cbuffer_truncate_from_front(&buffer, 4));

	v_assert_size_t(4, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_int(4, ==, *(int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(5, ==, *(int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(6, ==, *(int*)cbuffer_get_at(&buffer, 2));
	v_assert_int(7, ==, *(int*)cbuffer_get_at(&buffer, 3));
	v_assert_ptr(NULL, ==, cbuffer_get_at(&buffer, 4));

	teardown();
	VTS;
}

static void	test_01_cbuffer_truncateFromFront(void)
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 8; ++i)
	{
		cbuffer_push_back(&buffer, &i);
	}

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_ptr(NULL, !=, cbuffer_truncate_from_back(&buffer, 4));

	v_assert_size_t(4, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_int(0, ==, *(int*)cbuffer_get_at(&buffer, 0));
	v_assert_int(1, ==, *(int*)cbuffer_get_at(&buffer, 1));
	v_assert_int(2, ==, *(int*)cbuffer_get_at(&buffer, 2));
	v_assert_int(3, ==, *(int*)cbuffer_get_at(&buffer, 3));
	v_assert_ptr(NULL, ==, cbuffer_get_at(&buffer, 4));

	teardown();
	VTS;
}

static void	test_01_cbuffer_truncateToManyFromBack()
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 8; ++i)
	{
		cbuffer_push_back(&buffer, &i);
	}

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_ptr(NULL, ==, cbuffer_truncate_from_back(&buffer, 10));

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_01_cbuffer_truncateToManyFromFront()
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 8; ++i)
	{
		cbuffer_push_back(&buffer, &i);
	}

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_ptr(NULL, ==, cbuffer_truncate_from_front(&buffer, 10));

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	teardown();
	VTS;
}

void	suite_cbuffer_truncate(void)
{
	test_00_cbuffer_truncateFromBack();
	test_01_cbuffer_truncateFromFront();
	test_01_cbuffer_truncateToManyFromBack();
	test_01_cbuffer_truncateToManyFromFront();

	VSS;
}

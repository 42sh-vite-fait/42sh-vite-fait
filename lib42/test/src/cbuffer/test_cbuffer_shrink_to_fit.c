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

static void	test_00_cbuffer_shrink_to_fit_Simple(void)
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

	v_assert_ptr(NULL, !=, cbuffer_shrink_to_fit(&buffer));

	v_assert_size_t(8, ==, buffer.len);
	v_assert_size_t(8, ==, buffer.capacity);

	teardown();
	VTS;
}

static void	test_01_cbuffer_shrink_to_fit_Equal(void)
{
	setup(10, sizeof(int), NULL);

	v_assert_size_t(0, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	for (int i = 0; i < 10; ++i)
	{
		cbuffer_push_back(&buffer, &i);
	}

	v_assert_size_t(10, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	v_assert_ptr(NULL, !=, cbuffer_shrink_to_fit(&buffer));

	v_assert_size_t(10, ==, buffer.len);
	v_assert_size_t(10, ==, buffer.capacity);

	teardown();
	VTS;
}

void	suite_cbuffer_shrink_to_fit(void)
{
	test_00_cbuffer_shrink_to_fit_Simple();
	test_01_cbuffer_shrink_to_fit_Equal();

	VSS;
}

#include "header.h"

static t_array	array;

static void	setup(void *data, size_t elem_size, size_t len)
{
	unsigned char	*p;
	unsigned char	*d;

	array_init(&array, elem_size);
	if (data != NULL)
	{
		p = array.data;
		d = data;
		for (size_t i = 0; i < len; ++i)
			memcpy(p + (elem_size * i), d + (elem_size * i), elem_size);
		array.len = len;
	}
}

static void	teardown(void)
{
	free(array.data);
}

static void	test_00_array_swap_Int(void)
{
	int	data[4] = {11, 22, 33, 44};
	setup(data, sizeof(int), ARR_SIZ_MAX(data));

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		int *value = array_get_at(&array, i);
		v_assert_int(data[i], ==, *value);
	}

	// swap first with last
	void	*ret = array_swap(&array, 0, 3);
	v_assert_ptr(NULL, !=, ret);
	v_assert_int(44, ==, *(int*)array_get_at(&array, 0));
	v_assert_int(11, ==, *(int*)array_get_at(&array, 3));

	// swap middle
	ret = array_swap(&array, 1, 2);
	v_assert_ptr(NULL, !=, ret);
	v_assert_int(33, ==, *(int*)array_get_at(&array, 1));
	v_assert_int(22, ==, *(int*)array_get_at(&array, 2));

	teardown();
	VTS;
}

static void	test_01_array_swap_String(void)
{
	char		*data[] = {
		"hello",
		"world",
		"and",
		"good",
		"morning",
	};
	setup(data, sizeof(char*), ARR_SIZ_MAX(data));

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		char	**value = array_get_at(&array, i);
		v_assert_str(data[i], *value);
	}

	// swap first with last
	void	*ret = array_swap(&array, 0, 4);
	v_assert_ptr(NULL, !=, ret);
	v_assert_str(data[4], *(char**)array_get_at(&array, 0));
	v_assert_str(data[0], *(char**)array_get_at(&array, 4));

	// swap middle
	ret = array_swap(&array, 1, 2);
	v_assert_ptr(NULL, !=, ret);
	v_assert_str(data[1], *(char**)array_get_at(&array, 2));
	v_assert_str(data[2], *(char**)array_get_at(&array, 1));

	teardown();
	VTS;
}

static void	test_02_array_swap_Struct(void)
{
	struct s_test {
		void	*e;
		int		i;
		char	c;
		char	padding[3];
	} data[3] = {
		{ NULL, 42, 'a', {0} },
		{ (void*)0xdeadbeef, 8, 'z', {0} },
		{ (void*)0xabcdef, -1, '*', {0} },
	};
	setup(data, sizeof(struct s_test), ARR_SIZ_MAX(data));

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		struct s_test value = *(struct s_test*)array_get_at(&array, i);
		v_assert_ptr(data[i].e, ==, value.e);
		v_assert_int(data[i].i, ==, value.i);
		v_assert_char(data[i].c, ==, value.c);
	}

	// swap first with last
	void	*ret = array_swap(&array, 0, 2);
	v_assert_ptr(NULL, !=, ret);
	struct s_test old_first = *(struct s_test*)array_get_at(&array, 0);
	struct s_test old_last = *(struct s_test*)array_get_at(&array, 2);
	v_assert_ptr(data[2].e, ==, old_first.e);
	v_assert_int(data[2].i, ==, old_first.i);
	v_assert_char(data[2].c, ==, old_first.c);
	v_assert_ptr(data[0].e, ==, old_last.e);
	v_assert_int(data[0].i, ==, old_last.i);
	v_assert_char(data[0].c, ==, old_last.c);

	// swap middle, with itself
	ret = array_swap(&array, 0, 2);
	v_assert_ptr(NULL, !=, ret);
	ret = array_swap(&array, 1, 1);
	v_assert_ptr(NULL, !=, ret);
	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		struct s_test value = *(struct s_test*)array_get_at(&array, i);
		v_assert_ptr(data[i].e, ==, value.e);
		v_assert_int(data[i].i, ==, value.i);
		v_assert_char(data[i].c, ==, value.c);
	}

	teardown();
	VTS;
}

static void	test_03_array_swap_OutOfRange(void)
{
	int	data[4] = {11, 22, 33, 44};
	setup(data, sizeof(int), ARR_SIZ_MAX(data));

	v_assert_ptr(NULL, ==, array_swap(&array, 4, 0));

	// check integrity
	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		int value = *(int*)array_get_at(&array, i);
		v_assert_int(data[i], ==, value);
	}

	teardown();
	VTS;
}

void	suite_array_swap(void)
{
	test_00_array_swap_Int();
	test_01_array_swap_String();
	test_02_array_swap_Struct();
	test_03_array_swap_OutOfRange();

	VSS;
}

#include "header.h"

static t_array		array;

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

static void	test_00_array_push_Int(void)
{
	int	data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	setup(NULL, sizeof(int), 0);

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		int	value = data[i];
		array_push(&array, &value);
		if (i < 8)
			v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
		else
			v_assert_size_t(16, ==, array.capacity);
		v_assert_size_t(i + 1, ==, array.len);
		int	*res = array_get_at(&array, i);
		v_assert_int(value, ==, *res);
	}

	teardown();
	VTS;
}

static void	test_01_array_push_String(void)
{
	char		*data[] = {
		"hello",
		"world",
		"and",
		"good",
		"morning",
	};
	setup(NULL, sizeof(char*), 0);

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		char	*value = data[i];
		array_push(&array, &value);
		if (i < 7)
			v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
		else
			v_assert_size_t(16, ==, array.capacity);
		v_assert_size_t(i + 1, ==, array.len);
		char	**res = array_get_at(&array, i);
		v_assert_str(value, *res);
	}

	teardown();
	VTS;
}

static void	test_02_array_push_Struct(void)
{
	struct s_test {
		void	*e;
		int		i;
		char	c[4];
	} data[3] = {
		{ NULL, 42, {'a', 'b', 'c', 'd'} },
		{ (void*)0xdeadbeef, 8, {'z', 'y', 'x', 'w'} },
		{ (void*)0xabcdef, -1, {'*', '&', '^', '%'} }
	};
	setup(NULL, sizeof(struct s_test), 0);

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		struct s_test value = data[i];
		array_push(&array, &value);

		if (i < 7)
			v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
		else
			v_assert_size_t(16, ==, array.capacity);

		struct s_test *res = array_get_at(&array, i);
		v_assert_ptr(value.e, ==, res->e);
		v_assert_int(value.i, ==, res->i);
	}

	teardown();
	VTS;
}

void	suite_array_push(void)
{
	test_00_array_push_Int();
	test_01_array_push_String();
	test_02_array_push_Struct();

	VSS;
}

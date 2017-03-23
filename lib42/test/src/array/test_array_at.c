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

static void	test_00_array_at_Int(void)
{
	int	data[4] = {11, 22, 33, 44};
	setup(data, sizeof(int), ARR_SIZ_MAX(data));

	for (size_t i = 0; i < ARR_SIZ_MAX(data); ++i)
	{
		int *value = array_get_at(&array, i);
		v_assert_int(data[i], ==, *value);
	}

	// set
	int	new = 8;
	int *value = array_get_at(&array, 3);
	array_set_at(&array, 3, &new);
	v_assert_int(8, ==, *value);

	teardown();
	VTS;
}

static void	test_01_array_at_String(void)
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

	// set
	char	*s = "zut";
	char	**value = array_get_at(&array, 2);
	array_set_at(&array, 2, &s);
	v_assert_ptr(s, ==, *value);
	v_assert_str(s, *value);

	teardown();
	VTS;
}

static void	test_02_array_at_Struct(void)
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

	// set
	struct s_test new = { (void*)0x1234, 1 << 31, 'X', {0} };
	array_set_at(&array, 0, &new);
	struct s_test value = *(struct s_test*)array_get_at(&array, 0);
	v_assert_ptr(new.e, ==, value.e);
	v_assert_int(new.i, ==, value.i);
	v_assert_char(new.c, ==, value.c);

	teardown();
	VTS;
}

static void	test_03_array_at_OutOfRange(void)
{
	int	data[4] = {11, 22, 33, 44};
	setup(data, sizeof(int), ARR_SIZ_MAX(data));

	v_assert_ptr(NULL, ==, array_get_at(&array, 4));

	teardown();
	VTS;
}

static void	test_04_array_get_last_Int(void)
{
	int data[4] = {1, 2, 3, 4};
	setup(data, sizeof(int), ARR_SIZ_MAX(data));

	int *value = array_get_last(&array);
	v_assert_int(data[3], ==, *value);

	array.len -= 1;

	value = array_get_last(&array);
	v_assert_int(data[2], ==, *value);

	array.len -= 1;

	value = array_get_last(&array);
	v_assert_int(data[1], ==, *value);

	array.len -= 1;

	value = array_get_last(&array);
	v_assert_int(data[0], ==, *value);

	array.len -= 1;

	int *empty = array_get_last(&array);
	v_assert_size_t(0, ==, array.len);
	v_assert_ptr(NULL, ==, empty);

	teardown();
	VTS;
}

static void	test_05_array_get_first_Int(void)
{
	int data[4] = {1, 2, 3, 4};
	setup(data, sizeof(int), ARR_SIZ_MAX(data));

	int *value = array_get_first(&array);
	v_assert_int(data[0], ==, *value);

	array.len = 0;

	int *empty = array_get_first(&array);
	v_assert_size_t(0, ==, array.len);
	v_assert_ptr(NULL, ==, empty);

	teardown();
	VTS;
}

void	suite_array_at(void)
{
	test_00_array_at_Int();
	test_01_array_at_String();
	test_02_array_at_Struct();
	test_03_array_at_OutOfRange();
	test_04_array_get_last_Int();
	test_05_array_get_first_Int();

	VSS;
}

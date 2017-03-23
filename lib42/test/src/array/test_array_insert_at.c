#include "header.h"

static t_array		array;
static char			*str[] = {
	"hello",
	"world",
	"and",
	"good",
	"morning",
};

static void	setup(void)
{
	array_init(&array, sizeof(char*));
	for (size_t i = 0; i < ARR_SIZ_MAX(str); ++i)
		array_push(&array, &str[i]);
}

static void	teardown(void)
{
	free(array.data);
}

static void	test_00_array_insert_at_FirstPlace(void)
{
	char	*s1 = "zut";
	char	*value;
	size_t	index = 0;

	setup();

	array_insert_at(&array, index, &s1);

	// Check array integrity
	v_assert_size_t(6, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0, j = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);
		if (i == index)
		{
			v_assert_ptr(s1, ==, value);
			v_assert_str(s1, value);
		}
		else
		{
			v_assert_ptr(str[j], ==, value);
			v_assert_str(str[j], value);
			++j;
		}
	}

	// last, unassigned
	value = array_get_at(&array, array.len);
	v_assert_ptr(NULL, ==, value);

	teardown();
	VTS;
}

static void	test_01_array_insert_at_LastPlace(void)
{
	char	*s1 = "zut";
	char	*value;
	size_t	index;

	setup();

	index = array.len - 1;
	array_insert_at(&array, index, &s1);

	// Check array integrity
	v_assert_size_t(6, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0, j = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);

		if (i == index)
		{
			v_assert_ptr(s1, ==, value);
			v_assert_str(s1, value);
		}
		else
		{
			v_assert_ptr(str[j], ==, value);
			v_assert_str(str[j], value);
			++j;
		}
	}

	// last, unassigned
	value = array_get_at(&array, array.len);
	v_assert_ptr(NULL, ==, value);

	teardown();
	VTS;
}

static void	test_02_array_insert_at_MiddlePlace(void)
{
	char	*s1 = "zut";
	char	*value;
	size_t	index;

	setup();

	index = array.len / 2;
	array_insert_at(&array, index, &s1);

	// Check array integrity
	v_assert_size_t(6, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0, j = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);

		if (i == index)
		{
			v_assert_ptr(s1, ==, value);
			v_assert_str(s1, value);
		}
		else
		{
			v_assert_ptr(str[j], ==, value);
			v_assert_str(str[j], value);
			++j;
		}
	}

	// last, unassigned
	value = array_get_at(&array, array.len);
	v_assert_ptr(NULL, ==, value);

	teardown();
	VTS;
}

static void	test_03_array_insert_at_Resize(void)
{
	char	*s1 = "zut1";
	char	*s2 = "zut2";
	char	*s3 = "zut3";
	char	*value;
	size_t	index;

	setup();

	array_insert_at(&array, array.len, &s1);
	array_insert_at(&array, array.len, &s2);
	array_insert_at(&array, array.len, &s3);

	// Check array integrity
	v_assert_size_t(8, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0; i < array.len - 3; ++i)
	{
		value = *(char**)array_get_at(&array, i);
		v_assert_ptr(str[i], ==, value);
		v_assert_str(str[i], value);
	}

	index = array.len - 1;
	value = *(char**)array_get_at(&array, index);
	v_assert_ptr(s3, ==, value);
	v_assert_str(s3, value);

	index = array.len - 2;
	value = *(char**)array_get_at(&array, index);
	v_assert_ptr(s2, ==, value);
	v_assert_str(s2, value);

	index = array.len - 3;
	value = *(char**)array_get_at(&array, index);
	v_assert_ptr(s1, ==, value);
	v_assert_str(s1, value);

	// last, unassigned
	value = array_get_at(&array, array.len);
	v_assert_ptr(NULL, ==, value);

	teardown();
	VTS;
}

void	suite_array_insert_at(void)
{
	test_00_array_insert_at_FirstPlace();
	test_01_array_insert_at_LastPlace();
	test_02_array_insert_at_MiddlePlace();
	test_03_array_insert_at_Resize();

	VSS;
}

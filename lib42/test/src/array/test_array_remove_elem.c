#include "header.h"

static t_array		array;
static char			*str[] = {
	"hello",
	"world",
	"and",
	"good",
	"morning",
	"string",
	"padding",
	"enable",
};

static void	setup(void)
{
	array_init(&array, sizeof(char*));
	for (size_t i = 0; i < ARR_SIZ_MAX(str); ++i)
	{
		array_push(&array, &str[i]);
	}
}

static void	teardown(void)
{
	free(array.data);
}

static void	test_00_array_remove_elem_FirstItem(void)
{
	void	*ptr;
	char	*value;
	size_t	index;

	setup();
	v_assert_size_t(ARR_SIZ_MAX(str), ==, array.len);

	// remove first elem
	ptr = array_remove_elem(&array, array.data);

	v_assert_ptr(NULL, !=, ptr);

	// Check array integrity
	v_assert_size_t(ARR_SIZ_MAX(str) - 1, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);
		v_assert_ptr(str[i + 1], ==, value);
		v_assert_str(str[i + 1], value);
	}

	// last, unassigned
	v_assert_ptr(NULL, ==, array_get_at(&array, 7));
	v_assert_ptr(NULL, ==, array_get_at(&array, 8));

	teardown();
	VTS;
}

static void	test_01_array_remove_elem_MiddleItem(void)
{
	void	*ptr;
	char	*value;

	setup();
	v_assert_size_t(ARR_SIZ_MAX(str), ==, array.len);

	size_t		index = array.len / 2;
	uintptr_t	elem = sizeof(void *) * index;
	ptr = array_remove_elem(&array, (char*)array.data + elem);

	// Check return value
	v_assert_ptr(NULL, !=, ptr);

	// Check array integrity
	v_assert_size_t(ARR_SIZ_MAX(str) - 1, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);
		if (i < index)
		{
			v_assert_ptr(str[i], ==, value);
			v_assert_str(str[i], value);
		}
		else
		{
			v_assert_ptr(str[i + 1], ==, value);
			v_assert_str(str[i + 1], value);
		}
	}

	// last, unassigned
	v_assert_ptr(NULL, ==, array_get_at(&array, 7));
	v_assert_ptr(NULL, ==, array_get_at(&array, 8));

	teardown();
	VTS;
}

static void	test_02_array_remove_elem_LastItem(void)
{
	void	*ptr;
	char	*value;

	setup();
	v_assert_size_t(ARR_SIZ_MAX(str), ==, array.len);

	size_t		index = array.len - 1;
	uintptr_t	elem = sizeof(void *) * index;
	ptr = array_remove_elem(&array, (char*)array.data + elem);

	// Check return value
	v_assert_ptr(NULL, !=, ptr);

	// Check array integrity
	v_assert_size_t(ARR_SIZ_MAX(str) - 1, ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);
		if (i < index)
		{
			v_assert_ptr(str[i], ==, value);
			v_assert_str(str[i], value);
		}
		else
		{
			v_assert_ptr(str[i + 1], ==, value);
			v_assert_str(str[i + 1], value);
		}
	}

	// last, unassigned
	v_assert_ptr(NULL, ==, array_get_at(&array, 7));
	v_assert_ptr(NULL, ==, array_get_at(&array, 8));

	teardown();
	VTS;
}

static void	test_03_array_remove_elem_OutOfRange(void)
{
	void	*ptr;
	char	*value;

	setup();
	v_assert_size_t(ARR_SIZ_MAX(str), ==, array.len);

	size_t		index = array.len;
	uintptr_t	elem = sizeof(void *) * index;
	ptr = array_remove_elem(&array, (char*)array.data + elem);

	// Check return value
	v_assert_ptr(NULL, ==, ptr);

	// Check array integrity
	v_assert_size_t(ARR_SIZ_MAX(str), ==, array.len);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0; i < array.len; ++i)
	{
		value = *(char**)array_get_at(&array, i);
		v_assert_ptr(str[i], ==, value);
		v_assert_str(str[i], value);
	}

	// last, unassigned
	v_assert_ptr(NULL, ==, array_get_at(&array, 8));

	teardown();
	VTS;
}

static void	test_04_array_remove_elem_OneItemInArrayOfSizeOne(void)
{
	array_init_with_capacity(&array, sizeof(int), 1);
	array_push(&array, &(int){42});
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(1, ==, array.len);

	array_remove_elem(&array, array.data);
	v_assert_size_t(0, ==, array.len);

	teardown();
	VTS;
}

void	suite_array_remove_elem(void)
{
	test_00_array_remove_elem_FirstItem();
	test_01_array_remove_elem_MiddleItem();
	test_02_array_remove_elem_LastItem();
	test_03_array_remove_elem_OutOfRange();
	test_04_array_remove_elem_OneItemInArrayOfSizeOne();

	VSS;
}

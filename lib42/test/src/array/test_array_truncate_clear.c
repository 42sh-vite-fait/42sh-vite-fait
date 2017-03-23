#include "header.h"

static void	test_00_array_truncate_Simple(void)
{
	t_array		arr;
	char		*s1 = "hello";
	char		*s2 = "world";
	char		*s3 = "and";
	char		*s4 = "good";
	char		*s5 = "morning";

	array_init(&arr, sizeof(char*));
	array_push(&arr, &s1);
	array_push(&arr, &s2);
	array_push(&arr, &s3);
	array_push(&arr, &s4);
	array_push(&arr, &s5);

	v_assert_size_t(ARRAY_INIT_SIZE, ==, arr.capacity);
	v_assert_size_t(5, ==, arr.len);
	v_assert_str(s1, *(char**)array_get_at(&arr, 0));
	v_assert_ptr(s1, ==, *(char**)array_get_at(&arr, 0));
	v_assert_str(s2, *(char**)array_get_at(&arr, 1));
	v_assert_ptr(s2, ==, *(char**)array_get_at(&arr, 1));
	v_assert_str(s3, *(char**)array_get_at(&arr, 2));
	v_assert_ptr(s3, ==, *(char**)array_get_at(&arr, 2));
	v_assert_str(s4, *(char**)array_get_at(&arr, 3));
	v_assert_ptr(s4, ==, *(char**)array_get_at(&arr, 3));
	v_assert_str(s5, *(char**)array_get_at(&arr, 4));
	v_assert_ptr(s5, ==, *(char**)array_get_at(&arr, 4));
	v_assert_ptr(NULL, ==, array_get_at(&arr, 5));
	v_assert_ptr(NULL, ==, array_get_at(&arr, 6));
	v_assert_ptr(NULL, ==, array_get_at(&arr, 7));

	v_assert_ptr(NULL, !=, array_truncate(&arr, 3));

	v_assert_size_t(ARRAY_INIT_SIZE, ==, arr.capacity);
	v_assert_size_t(3, ==, arr.len);
	v_assert_str(s1, *(char**)array_get_at(&arr, 0));
	v_assert_ptr(s1, ==, *(char**)array_get_at(&arr, 0));
	v_assert_str(s2, *(char**)array_get_at(&arr, 1));
	v_assert_ptr(s2, ==, *(char**)array_get_at(&arr, 1));
	v_assert_str(s3, *(char**)array_get_at(&arr, 2));
	v_assert_ptr(s3, ==, *(char**)array_get_at(&arr, 2));
	v_assert_ptr(NULL, ==, array_get_at(&arr, 3));
	v_assert_ptr(NULL, ==, array_get_at(&arr, 4));

	array_shutdown(&arr);
	VTS;
}

static void	test_01_array_truncate_Zero(void)
{
	t_array		array;
	int			n = 42;

	array_init(&array, sizeof(char));

	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);

	v_assert_ptr(NULL, !=, array_truncate(&array, 0));

	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(0, ==, array.len);

	array_shutdown(&array);
	VTS;
}

static void	test_02_array_truncate_Nothing(void)
{
	t_array		array;
	int			n = 42;

	array_init(&array, sizeof(char));

	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);

	v_assert_ptr(NULL, !=, array_truncate(&array, 5));

	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(5, ==, array.len);

	array_shutdown(&array);
	VTS;
}

static void	test_03_array_truncate_Bigger(void)
{
	t_array		array;
	int			n = 42;

	array_init(&array, sizeof(char));

	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);

	v_assert_ptr(NULL, ==, array_truncate(&array, 15));

	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(5, ==, array.len);

	array_shutdown(&array);
	VTS;
}

static void	test_04_array_clear(void)
{
	t_array		array;
	int			n = 42;

	array_init(&array, sizeof(char));

	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);
	array_push(&array, &n);

	array_clear(&array);

	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(0, ==, array.len);

	array_shutdown(&array);
	VTS;
}

void	suite_array_truncate_clear(void)
{
	test_00_array_truncate_Simple();
	test_01_array_truncate_Zero();
	test_02_array_truncate_Nothing();
	test_03_array_truncate_Bigger();
	test_04_array_clear();

	VSS;
}

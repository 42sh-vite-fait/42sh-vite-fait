#include "header.h"

static void	test_00_array_clone_Simple(void)
{
	t_array		v;
	t_array		cp;
	char		*s1 = "hello";
	char		*s2 = "world";
	char		*s3 = "and";
	char		*s4 = "good";
	char		*s5 = "morning";

	array_init(&v, sizeof(char*));
	array_push(&v, &s1);
	array_push(&v, &s2);
	array_push(&v, &s3);
	array_push(&v, &s4);
	array_push(&v, &s5);

	array_clone(&cp, &v);

	v_assert_size_t(ARRAY_INIT_SIZE, ==, cp.capacity);
	v_assert_size_t(5, ==, cp.len);
	v_assert_str(s1, *(char**)array_get_at(&cp, 0));
	v_assert_ptr(s1, ==, *(char**)array_get_at(&cp, 0));
	v_assert_str(s2, *(char**)array_get_at(&cp, 1));
	v_assert_ptr(s2, ==, *(char**)array_get_at(&cp, 1));
	v_assert_str(s3, *(char**)array_get_at(&cp, 2));
	v_assert_ptr(s3, ==, *(char**)array_get_at(&cp, 2));
	v_assert_str(s4, *(char**)array_get_at(&cp, 3));
	v_assert_ptr(s4, ==, *(char**)array_get_at(&cp, 3));
	v_assert_str(s5, *(char**)array_get_at(&cp, 4));
	v_assert_ptr(s5, ==, *(char**)array_get_at(&cp, 4));
	v_assert_ptr(NULL, ==, array_get_at(&cp, 5));
	v_assert_ptr(NULL, ==, array_get_at(&cp, 6));
	v_assert_ptr(NULL, ==, array_get_at(&cp, 7));
	v_assert_ptr(v.data, !=, cp.data);

	array_shutdown(&v);
	array_shutdown(&cp);
	VTS;
}

static void	test_01_array_clone_Empty(void)
{
	t_array		array;
	t_array		clone;

	array_init(&array, sizeof(char));

	v_assert_ptr(NULL, !=, array_clone(&clone, &array));
	v_assert_size_t(array.capacity, ==, clone.capacity);
	v_assert_size_t(array.len, ==, clone.len);
	v_assert_ptr(array.data, !=, clone.data);

	array_shutdown(&array);
	array_shutdown(&clone);

	VTS;
}

void	suite_array_clone(void)
{
	test_00_array_clone_Simple();
	test_01_array_clone_Empty();

	VSS;
}

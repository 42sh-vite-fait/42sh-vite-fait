#include "header.h"

static t_array	*a;

static void teardown(void)
{
	if (a != NULL)
	{
		free(a->data);
		free(a);
	}
	a = NULL;
}

static int	is_less_than(const void *n, const void *param) {
	return (*(const int*)n < *(const int*)param);
}

static void	test_00_array_find_from_simple(void)
{
	t_array		array;
	int			data[3][3] = {
		{1,4,-5},
		{1,-5,4},
		{-5,1,4},
	};
	int			zero = 0;

	for (int i = 0; i < 3; i++)
	{
		array_init(&array, sizeof(int));
		for (int j = 0; j < 3; j++)
			array_push(&array, &(data[i][j]));
		int ret = *(int*)array_find_from(array, 0, &is_less_than, &zero);
		v_assert_int(-5, == , ret);
		array_shutdown(&array);
	}
	VTS;
}

static void test_01_array_find_from_empty(void)
{
	t_array	array;
	int		zero = 0;

	array_init(&array, sizeof(int));
	void *ret = array_find_from(array, 0, &is_less_than, &zero);
	v_assert_ptr(NULL, ==, ret);
	array_shutdown(&array);
	VTS;
}

static void test_02_array_find_from_no_matches(void) {

	t_array	array;
	int		zero = 0;
	int		ref = 1;

	array_init(&array, sizeof(int));
	array_push(&array, &ref);
	void *ret = array_find_from(array, 0, &is_less_than, &zero);
	v_assert_ptr(NULL, ==, ret);
	array_shutdown(&array);
	VTS;
}

static void	test_03_array_find_from_n(void) {

	t_array	array;
	int		zero = 0;
	int		ref[] = {-5, -42};

	array_init(&array, sizeof(int));
	array_push(&array, ref);
	array_push(&array, ref + 1);
	void *ret = array_find_from(array, 1, &is_less_than, &zero);
	v_assert_int(-42, ==, *(int*)ret);
	array_shutdown(&array);
	VTS;
}

static void	test_04_array_find_from_param(void) {

	t_array	array;
	int		four = 4;
	int		five = 5;
	int		six = 6;

	array_init(&array, sizeof(int));
	array_push(&array, &five);
	void *ret1 = array_find_from(array, 0, &is_less_than, &four);
	void *ret2 = array_find_from(array, 0, &is_less_than, &six);
	v_assert_ptr(ret1, !=, ret2);
	array_shutdown(&array);
	VTS;
}

void		suite_array_find_from(void)
{
	test_00_array_find_from_simple();
	test_01_array_find_from_empty();
	test_02_array_find_from_no_matches();
	test_03_array_find_from_n();
	test_04_array_find_from_param();
	VSS;
}

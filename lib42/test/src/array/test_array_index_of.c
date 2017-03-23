#include "header.h"

static t_array	array;
static int		tab[7] = {
	1, 2, 3, 4, 5, 6, 7
};

static void	setup(void)
{
	array_init(&array, sizeof(int));
	for (size_t i = 0; i < ARR_SIZ_MAX(tab); ++i)
		array_push(&array, tab + i);
}

static void	teardown(void)
{
	free(array.data);
}

static void	test_00_array_index_of_CheckAllValue(void)
{
	setup();

	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);

	for (size_t i = 0; i < 7; ++i)
	{
		int	*value = array_get_at(&array, i);
		int	index = (int)array_index_of(&array, value);
		v_assert_int(i, ==, index);
	}

	// Last index
	int	*value = array_get_at(&array, array.len);
	int	index = (int)array_index_of(&array, value);
	v_assert_int(-1, ==, index);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(7, ==, array.len);

	teardown();
	VTS;
}

static void	test_01_array_index_of_NotInArray(void)
{
	setup();

	int value;
	int	index = (int)array_index_of(&array, &value);
	v_assert_size_t(ARRAY_INIT_SIZE, ==, array.capacity);
	v_assert_size_t(7, ==, array.len);
	v_assert_int(-1, ==, index);

	teardown();
	VTS;
}

void	suite_array_index_of(void)
{
	test_00_array_index_of_CheckAllValue();
	test_01_array_index_of_NotInArray();

	VSS;
}

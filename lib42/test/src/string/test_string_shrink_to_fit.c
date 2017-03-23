#include "header.h"

static t_string		string;

static void	teardown(void)
{
	string_shutdown(&string);
}

static void		test_00_string_reserve_DontNeedShrinking(void)
{
	char		*before_shrink;

	string_init_with_capacity(&string, 4);
	before_shrink = string.str;
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);

	string_shrink_to_fit(&string);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_ptr(before_shrink, ==, string.str);

	teardown();
	VTS;
}

static void		test_01_string_reserve_NeedShrinking(void)
{
	string_init_with_capacity(&string, 255);
	v_assert_size_t(256, ==, string.capacity);

	string_shrink_to_fit(&string);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);

	teardown();
	VTS;
}

void			suite_string_shrink_to_fit(void)
{
	test_00_string_reserve_DontNeedShrinking();
	test_01_string_reserve_NeedShrinking();

	VSS;
}

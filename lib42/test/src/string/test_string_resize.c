#include "header.h"

static t_string	*string;

static void	teardown(void)
{
	free(TBUFFER_GET(string));
	free(string);
}

static void	test_00_string_resize_ExpandNotMuch(void)
{
	string = string_new(4);
	v_assert_size_t(STRING_INIT_SIZE, ==, TBUFFER_MAX(string));

	string = string_resize(string, 7);
	v_assert_size_t(STRING_INIT_SIZE * 2, ==, TBUFFER_MAX(string));

	teardown();
	VTS;
}

static void	test_01_string_resize_ExpandMoreThan2(void)
{
	string = string_new(1111);
	v_assert_size_t(2048, ==, TBUFFER_MAX(string));

	string = string_resize(string, 5555);
	v_assert_size_t(8192, ==, TBUFFER_MAX(string));

	teardown();
	VTS;
}

static void	test_02_string_resize_ExpandPowerOf2(void)
{
	string = string_new(256);
	v_assert_size_t(512, ==, TBUFFER_MAX(string));

	string = string_resize(string, 256);
	v_assert_size_t(1024, ==, TBUFFER_MAX(string));

	teardown();
	VTS;
}

void	suite_string_resize(void)
{
	test_00_string_resize_ExpandNotMuch();
	test_01_string_resize_ExpandMoreThan2();
	test_02_string_resize_ExpandPowerOf2();

	VSS;
}

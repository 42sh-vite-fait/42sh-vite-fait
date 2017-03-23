#include "header.h"

static t_string		string;

static void	test_00_string_truncate_SimpleSize(void)
{
	t_string *res;
	string_init_dup(&string, "Hello World!");

	res = string_truncate(&string, 9);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_size_t(9, ==, string.len);
	v_assert_str("Hello Wor", string.str);
	v_assert_ptr(NULL, !=, res);

	string_shutdown(&string);
	VTS;
}

static void	test_01_string_truncate_ZeroSize(void)
{
	t_string *res;
	string_init_dup(&string, "Hello World!");

	res = string_truncate(&string, string.len);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_size_t(12, ==, string.len);
	v_assert_str("Hello World!", string.str);
	v_assert_ptr(NULL, !=, res);

	string_shutdown(&string);
	VTS;
}

static void	test_02_string_truncate_FullSize(void)
{
	t_string *res;
	string_init_dup(&string, "Hello World!");

	res = string_truncate(&string, 0);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_size_t(0, ==, string.len);
	v_assert_str("", string.str);
	v_assert_ptr(NULL, !=, res);

	string_shutdown(&string);
	VTS;
}

static void	test_03_string_truncate_SizeOverflow(void)
{
	t_string *res;
	string_init_dup(&string, "Hello World!");

	res = string_truncate(&string, 42);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_size_t(12, ==, string.len);
	v_assert_str("Hello World!", string.str);
	v_assert_ptr(NULL, ==, res);

	string_shutdown(&string);
	VTS;
}

void	suite_string_truncate(void)
{
	test_00_string_truncate_SimpleSize();
	test_01_string_truncate_ZeroSize();
	test_02_string_truncate_FullSize();
	test_03_string_truncate_SizeOverflow();

	VSS;
}

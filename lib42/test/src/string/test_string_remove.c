#include "header.h"

void	test_00_string_remove_Middle(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 5, 5);

	v_assert_size_t(5, ==, ret);
	v_assert_size_t(6, ==, string.len);
	v_assert_str("hellod", string.str);

	free(string.str);
	VTS;
}

void	test_01_string_remove_OutOfRange(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 11, 1);

	v_assert_size_t(0, ==, ret);
	v_assert_size_t(len, ==, string.len);
	v_assert_str(s, string.str);

	free(string.str);
	VTS;
}

void	test_02_string_remove_MiddleLongRange(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 5, 20);

	v_assert_size_t(6, ==, ret);
	v_assert_size_t(5, ==, string.len);
	v_assert_str("hello", string.str);

	free(string.str);
	VTS;
}

void	test_03_string_remove_Head(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 0, 6);

	v_assert_size_t(6, ==, ret);
	v_assert_size_t(5, ==, string.len);
	v_assert_str("world", string.str);

	free(string.str);
	VTS;
}

void	test_04_string_remove_HeadLongRange(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 0, 20);

	v_assert_size_t(11, ==, ret);
	v_assert_size_t(0, ==, string.len);
	v_assert_str("", string.str);

	free(string.str);
	VTS;
}

void	test_05_string_remove_Tail(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 10, 1);

	v_assert_size_t(1, ==, ret);
	v_assert_size_t(10, ==, string.len);
	v_assert_str("hello worl", string.str);

	free(string.str);
	VTS;
}

void	test_06_string_remove_TailLongRange(void)
{
	t_string	string;
	char	*s = "hello world";
	size_t	len = strlen(s);
	size_t	ret;

	string_init(&string);
	string_ncat(&string, s, len);
	ret = string_remove(&string, 10, 20);

	v_assert_size_t(1, ==, ret);
	v_assert_size_t(10, ==, string.len);
	v_assert_str("hello worl", string.str);

	free(string.str);
	VTS;
}

void	suite_string_remove(void)
{
	test_00_string_remove_Middle();
	test_01_string_remove_OutOfRange();
	test_02_string_remove_MiddleLongRange();
	test_03_string_remove_Head();
	test_04_string_remove_HeadLongRange();
	test_05_string_remove_Tail();
	test_06_string_remove_TailLongRange();

	VSS;
}

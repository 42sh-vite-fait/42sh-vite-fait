#include "header.h"

void	test_00_string_set_simple(void)
{
	t_string	string;
	char	*s = "**********";
	char	*s2 = "#*********";

	string_init(&string);
	string_set(&string, 0, 10, '*');
	v_assert_str(s, string.str);
	v_assert_size_t(strlen(s), ==, string.len);

	string_set(&string, 0, 1, '#');
	v_assert_str(s2, string.str);
	v_assert_size_t(strlen(s), ==, string.len);

	free(string.str);
	VTS;
}

void	test_01_string_set_fromSimple(void)
{
	t_string	string;
	char	*s = "**********";
	char	*s2 = "***######*";

	string_init(&string);
	string_set(&string, 0, 10, '*');
	v_assert_str(s, string.str);
	v_assert_size_t(strlen(s), ==, string.len);

	string_set(&string, 3, 6, '#');
	v_assert_str(s2, string.str);
	v_assert_size_t(strlen(s), ==, string.len);

	free(string.str);
	VTS;
}

void	test_02_string_set_ofLenZero(void)
{
	t_string	string;
	char	*s = "**********";
	char	*s2 = "**********";

	string_init(&string);
	string_set(&string, 0, 10, '*');
	v_assert_str(s, string.str);
	v_assert_size_t(strlen(s), ==, string.len);

	string_set(&string, 3, 0, '#');
	v_assert_str(s2, string.str);
	v_assert_size_t(strlen(s), ==, string.len);

	free(string.str);
	VTS;
}

void	suite_string_set(void)
{
	test_00_string_set_simple();
	test_01_string_set_fromSimple();
	test_02_string_set_ofLenZero();

	VSS;
}

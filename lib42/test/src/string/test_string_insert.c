#include "header.h"

void	test_00_string_insert_AddStringMiddle(void)
{
	t_string	string;
	char	*s = "docfolamour";
	char	*good = "docteur folamour";
	size_t	len_good = strlen(good);

	string_init(&string);
	string_ncat(&string, s, strlen(s));
	string_insert(&string, 3, "teur ", 5);
	v_assert_str(good, string.str);
	v_assert_size_t(len_good, ==, string.len);

	free(string.str);
	VTS;
}

void	test_01_string_insert_AddStringHead(void)
{
	t_string	string;
	char	*s = "folamour";
	char	*good = "docteur folamour";
	size_t	len_good = strlen(good);

	string_init(&string);
	string_ncat(&string, s, strlen(s));
	string_insert(&string, 0, "docteur ", 8);
	v_assert_str(good, string.str);
	v_assert_size_t(len_good, ==, string.len);

	free(string.str);
	VTS;
}

void	test_02_string_insert_AddStringTail(void)
{
	t_string	string;
	char	*s = "docteur";
	char	*good = "docteur folamour";
	size_t	len_good = strlen(good);

	string_init(&string);
	string_ncat(&string, s, strlen(s));
	string_insert(&string, string.len, " folamour", 9);

	v_assert_str(good, string.str);
	v_assert_size_t(len_good, ==, string.len);

	free(string.str);
	VTS;
}

void	suite_string_insert(void)
{
	test_00_string_insert_AddStringMiddle();
	test_01_string_insert_AddStringHead();
	test_02_string_insert_AddStringTail();

	VSS;
}

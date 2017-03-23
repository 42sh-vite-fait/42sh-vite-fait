#include "header.h"

#define MAX_CTYPE 255

static void	test_ctype_off(void)
{
	int	i = 0;

	while (i <= MAX_CTYPE)
	{
		v_assert_int(!!FT_ISASCII(i), ==, !!isascii(i));
		v_assert_int(!!FT_ISBLANK(i), ==, !!isblank(i));
		v_assert_int(!!FT_ISSPACE(i), ==, !!isspace(i));
		v_assert_int(!!FT_ISLOWER(i), ==, !!islower(i));
		v_assert_int(!!FT_ISUPPER(i), ==, !!isupper(i));
		v_assert_int(!!FT_ISDIGIT(i), ==, !!isdigit(i));
		v_assert_int(!!FT_ISALPHA(i), ==, !!isalpha(i));
		v_assert_int(!!FT_ISALNUM(i), ==, !!isalnum(i));
		v_assert_int(!!FT_ISCNTRL(i), ==, !!iscntrl(i));
		v_assert_int(!!FT_ISPRINT(i), ==, !!isprint(i));
		v_assert_int(!!FT_ISPUNCT(i), ==, !!ispunct(i));
		v_assert_int(!!FT_ISGRAPH(i), ==, !!isgraph(i));
		v_assert_int(!!FT_TOLOWER(i), ==, !!tolower(i));
		v_assert_int(!!FT_TOUPPER(i), ==, !!toupper(i));
		v_assert_int(!!FT_ISXDIGIT(i), ==, !!isxdigit(i));
		++i;
	}
	v_test_success("Ctype");
}

static void	test_ctype_perso(void)
{
	int	i = 0;

	while (i <= MAX_CTYPE)
	{
		if (i == '\n' || isblank(i))
			v_assert_int(FT_ISWHITESPACE(i), ==, 1);
		else
			v_assert_int(FT_ISWHITESPACE(i), ==, 0);
		++i;
	}
	v_test_success("Ctype perso");
}

void	suite_ctype(void)
{
	test_ctype_off();
	test_ctype_perso();

	v_suite_success("Ctype");
}

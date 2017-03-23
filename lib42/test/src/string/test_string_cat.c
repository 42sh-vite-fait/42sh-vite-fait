#include "header.h"

static void	test_00_string_cat_Simple(void)
{
	t_string	string;
	char		*s = "Hello World!";
	size_t		l = strlen(s);

	string_init_with_capacity(&string, 4);
	string_cat(&string, s);

	v_assert_size_t(l, ==, string.len);
	v_assert_size_t(64, ==, string.capacity);
	v_assert_str(s, string.str);

	free(string.str);

	VTS;
}

static void	test_01_string_cat_NeedResize(void)
{
	t_string	string;
	char		*s = "Hello World!";
	size_t		l = strlen(s);

	string_init_with_capacity(&string, 12);
	string_cat(&string, s);

	v_assert_size_t(l, ==, string.len);
	v_assert_size_t(64, ==, string.capacity);
	v_assert_str(s, string.str);

	free(string.str);

	VTS;
}

static void	test_02_string_cat_BigConcatenation(void)
{
	t_string	string;
	char		a[300];
	char		m[3000];
	char		am[4000];
	size_t		alen;
	size_t		mlen;

	string_init_with_capacity(&string, 8);

	memset(a, 'a', sizeof(a));
	a[sizeof(a) - 1] = '\0';
	alen = strlen(a);
	string_ncat(&string, a, alen);
	v_assert_size_t(alen, ==, string.len);
	v_assert_size_t(512, ==, string.capacity);
	v_assert_str(a, string.str);

	memset(m, 'm', sizeof(m));
	m[sizeof(m) - 1] = '\0';
	mlen = strlen(m);
	memset(am, 0, sizeof(am));
	strcat(am, a);
	strcat(am + sizeof(a) - 1, m);
	string_ncat(&string, m, mlen);
	v_assert_size_t(alen + mlen, ==, string.len);
	v_assert_size_t(4096, ==, string.capacity);
	v_assert_str(am, string.str);

	free(string.str);

	VTS;
}

static void	test_03_string_cat_Empty(void)
{
	t_string	string;
	char		*s = "Hello";

	string_init(&string);

	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	string_cat(&string, s);

	v_assert_size_t(5, ==, string.len);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_str(s, string.str);

	string_shutdown(&string);
}

static void	test_04_string_ncat_Simple(void)
{
	t_string	string;
	char		*s = " World!";

	string_init_dup(&string, "Hello");

	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	string_ncat(&string, s, 7);

	v_assert_size_t(12, ==, string.len);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_str("Hello World!", string.str);

	string_shutdown(&string);
}

static void	test_05_string_ncat_Empty(void)
{
	t_string	string;
	char		*s = "Hello World!";

	string_init(&string);

	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	string_ncat(&string, s, 5);

	v_assert_size_t(5, ==, string.len);
	v_assert_size_t(STRING_INIT_SIZE, ==, string.capacity);
	v_assert_str("Hello", string.str);

	string_shutdown(&string);
}

void	suite_string_cat(void)
{
	test_00_string_cat_Simple();
	test_01_string_cat_NeedResize();
	test_02_string_cat_BigConcatenation();
	test_03_string_cat_Empty();

	test_04_string_ncat_Simple();
	test_05_string_ncat_Empty();

	VSS;
}

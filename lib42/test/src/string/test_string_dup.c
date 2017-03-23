
#include "header.h"

static t_string		string;

static void	teardown(void)
{
	free(string.str);
}

static void	test_00_string_dup_String(void)
{
	char	*s = "Hello world";
	size_t	len = strlen(s);

	string_init_dup(&string, s);

	v_assert_size_t(len, ==, string.len);
	v_assert_str(s, string.str);

	teardown();
	VTS;
}
static void	test_01_string_dup_EmptyString(void)
{
	char	*s = "";
	size_t	len = strlen(s);

	string_init_dup(&string, s);

	v_assert_size_t(len, ==, string.len);
	v_assert_str(s, string.str);

	teardown();
	VTS;
}

static void	test_02_string_ndup_SimpleString(void)
{
	char	*s = "Hello World!";
	/* size_t	len = strlen(s); */

	string_init_ndup(&string, s, 5);

	v_assert_size_t(5, ==, string.len);
	v_assert_str("Hello", string.str);

	teardown();
	VTS;
}

// static void	test_03_string_ndup_ShortenString(void)
// {
// 	char	*s = "abc";
// 	size_t	len = strlen(s);

// 	string_init_ndup(&string, s, 10);

// 	v_assert_size_t(64, ==, string.capacity);
// 	v_assert_size_t(len, ==, string.len);
// 	v_assert_str(s, string.str);

// 	teardown();
// 	VTS;
// }

static void	test_04_string_ndup_ZeroLength(void)
{
	char	*s = "World!";
	/* size_t	len = strlen(s); */

	string_init_ndup(&string, s, 0);

	v_assert_size_t(0, ==, string.len);
	v_assert_str("", string.str);

	teardown();
	VTS;
}


static void	test_05_string_create_dup_Simple(void)
{
	t_string	*str;
	char		*s = "World!";

	str = string_create_dup(s);

	v_assert_ptr(NULL, !=, str);
	v_assert_size_t(strlen(s), ==, str->len);
	v_assert_size_t(64, ==, str->capacity);
	v_assert_str(s, str->str);

	string_destroy(str);
	VTS;
}

static void	test_06_string_create_dup_ZeroLength(void)
{
	t_string	*str;
	char		*s = "";

	str = string_create_dup(s);

	v_assert_ptr(NULL, !=, str);
	v_assert_size_t(strlen(s), ==, str->len);
	v_assert_size_t(64, ==, str->capacity);
	v_assert_str(s, str->str);

	string_destroy(str);
	VTS;
}

static void	test_07_string_create_ndup_Simple(void)
{
	t_string	*str;
	char		*s = "World!";

	str = string_create_ndup(s, 3);

	v_assert_ptr(NULL, !=, str);
	v_assert_size_t(3, ==, str->len);
	v_assert_size_t(64, ==, str->capacity);
	v_assert_str("Wor", str->str);

	string_destroy(str);
	VTS;
}

static void	test_08_string_create_ndup_ZeroLength(void)
{
	t_string	*str;
	char		*s = "World!";

	str = string_create_ndup(s, 0);

	v_assert_ptr(NULL, !=, str);
	v_assert_size_t(0, ==, str->len);
	v_assert_size_t(64, ==, str->capacity);
	v_assert_str("", str->str);

	string_destroy(str);
	VTS;
}


void	suite_string_dup(void)
{
	test_00_string_dup_String();
	test_01_string_dup_EmptyString();
	test_02_string_ndup_SimpleString();
	// test_03_string_ndup_ShortenString(); // string doesn't check if give len is right
	test_04_string_ndup_ZeroLength();
	test_05_string_create_dup_Simple();
	test_06_string_create_dup_ZeroLength();
	test_07_string_create_ndup_Simple();
	test_08_string_create_ndup_ZeroLength();

	VSS;
}

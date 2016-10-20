#include "header.h"

static void		test_00_string_escape(void)
{
	t_string	str;

	string_dup(&str, "Hello World");
	string_escape_chars(&str, 'l');
	v_assert_str("He\\l\\lo Wor\\ld", str.str);

	VTS;
}

static void		test_01_string_unescape(void)
{
	t_string	str;

	string_dup(&str, "He\\l\\lo Wor\\ld");
	string_unescape_chars(&str, 'l');
	v_assert_str("Hello World", str.str);

	VTS;
}

static void		test_02_string_unescape_no_match(void)
{
	t_string	str;

	string_dup(&str, "He\\\\l\\lo Wor\\ld");
	string_unescape_chars(&str, 'l');
	v_assert_str("He\\\\llo World", str.str);

	VTS;
}

static void		test_03_string_escape_Newline(void)
{
	t_string	str;

	string_dup(&str, "Hello World\nAnd good morning!\n");
	string_escape_chars(&str, '\n');
	v_assert_str("Hello World\\\nAnd good morning!\\\n", str.str);

	VTS;
}

void			suite_string_escape(void)
{
	test_00_string_escape();
	test_01_string_unescape();
	test_02_string_unescape_no_match();
	test_03_string_escape_Newline();

	VSS;
}

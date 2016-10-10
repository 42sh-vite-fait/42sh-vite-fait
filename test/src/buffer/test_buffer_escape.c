#include "header.h"

static void		test_00_buffer_escape(void)
{
	t_buffer	*str;

	str = buffer_dup("Hello World");
	str = buffer_escape(str, 'l');
	v_assert_str("He\\l\\lo Wor\\ld", str->str);

	VTS;
}

static void		test_01_buffer_unescape(void)
{
	t_buffer	*str;

	str = buffer_dup("He\\l\\lo Wor\\ld");
	str = buffer_unescape(str, 'l');
	v_assert_str("Hello World", str->str);

	VTS;
}

static void		test_02_buffer_unescape_no_match(void)
{
	t_buffer	*str;

	str = buffer_dup("He\\\\l\\lo Wor\\ld");
	str = buffer_unescape(str, 'l');
	v_assert_str("He\\\\llo World", str->str);

	VTS;
}

void			suite_buffer_escape(void)
{
	test_00_buffer_escape();
	test_01_buffer_unescape();
	test_02_buffer_unescape_no_match();

	VSS;
}

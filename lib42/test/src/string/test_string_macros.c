#include "header.h"

static void	test_00_string_RESET_InIfStatement(void)
{
	t_string	*buf;

	buf = string_new(8);
	string_cat(buf, "hello");
	if (1)
		TBUFFER_RESET(buf);

	v_assert_size_t(0, ==, buf->len);
	v_assert_str("", buf->str);

	free(TBUFFER_GET(buf));
	free(buf);
	VTS;
}

static void	test_01_string_RESET_NotInBlockStatement(void)
{
	t_string	*buf;

	buf = string_new(8);
	string_cat(buf, "world");

	TBUFFER_RESET(buf);

	v_assert_size_t(0, ==, buf->len);
	v_assert_str("", buf->str);

	free(TBUFFER_GET(buf));
	free(buf);
	VTS;
}

void	suite_string_macros(void)
{
	test_00_string_RESET_InIfStatement();
	test_01_string_RESET_NotInBlockStatement();

	VSS;
}

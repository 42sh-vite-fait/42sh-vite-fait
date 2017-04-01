#include "header.h"
#include "criterion/criterion.h"

//static void setup(void) { }

TestSuite(LineContinuation, .init = NULL, .fini = NULL);

Test(LineContinuation, OnlyBackslashNewline)
{
	t_string	str;
	int			ret;

	string_init_dup(&str, "\\\n");
	ret = remove_escaped_newline(&str);
	cr_assert_eq(ret , LINE_INCOMPLETE);
	cr_assert_str_eq(str.str, "");
}

Test(LineContinuation, BackslashesTrueLineContinuation)
{
	t_string	str;
	int			ret;

	string_init_dup(&str, "\\\\\\\\\\\n");
	ret = remove_escaped_newline(&str);
	cr_assert_eq(ret , LINE_INCOMPLETE);
	cr_assert_str_eq(str.str, "\\\\\\\\");
}

Test(LineContinuation, BackslashesFalseLineContinuation)
{
	t_string	str;
	int			ret;

	string_init_dup(&str, "\\\\\\\\\\\\\n");
	ret = remove_escaped_newline(&str);
	cr_assert_eq(ret , LINE_COMPLETE);
	cr_assert_str_eq(str.str, "\\\\\\\\\\\\\n");
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * linebreak        : newline_list
 *                  | * empty *
 */

Test(Parser, Linebreak_OnlyNewlineList)
{
	int tokens[] = {
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_linebreak(&parser);
	int		ret = predict_linebreak(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, Linebreak_Empty)
{
	int tokens[] = {
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_linebreak(&parser);
	int		ret = predict_linebreak(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

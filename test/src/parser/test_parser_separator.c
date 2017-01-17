#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * separator        : separator_op linebreak
 *                  | newline_list
 */

Test(Parser, Separator_OnlyNewlineList)
{
	int tokens[] = {
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_SEMI,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_separator(&parser);
	int		ret = predict_separator(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, Separator_SepOpWithLinebreakEmptyAndWordNext)
{
	int tokens[] = {
		E_TOKEN_SEMI,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_separator(&parser);
	int		ret = predict_separator(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, Separator_SepOpWithLinebreakNewline)
{
	int tokens[] = {
		E_TOKEN_SEMI,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_separator(&parser);
	int		ret = predict_separator(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, Separator_OnlyWord)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_separator(&parser);
	int		ret = predict_separator(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_WORD);
}

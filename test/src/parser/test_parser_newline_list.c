#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * newline_list     :              NEWLINE
 *                  | newline_list NEWLINE
 */

Test(Parser, NewlineList_OneNewline)
{
	int tokens[] = {
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_newline_list(&parser);
	int ret = predict_newline_list(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, NewlineList_MultiplesNewlineWithWordBetween)
{
	int tokens[] = {
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_newline_list(&parser);
	int ret = predict_newline_list(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, NewlineList_NoNewline)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_newline_list(&parser);
	int ret = predict_newline_list(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_WORD);
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * separator_op     : '&'
 *                  | ';'
 */

Test(Parser, SeparatorOp_SemiAnd)
{
	int tokens[] = {
		E_TOKEN_AND,
		E_TOKEN_SEMI,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_separator_op(&parser);
	int ret = predict_separator_op(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, SeparatorOp_AndSemi)
{
	int tokens[] = {
		E_TOKEN_SEMI,
		E_TOKEN_AND,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_separator_op(&parser);
	int ret = predict_separator_op(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_AND);
}

Test(Parser, SeparatorOp_MultipleAnd)
{
	int tokens[] = {
		E_TOKEN_AND,
		E_TOKEN_AND,
		E_TOKEN_AND,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_separator_op(&parser);
	int ret = predict_separator_op(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	cr_assert_eq(1, parser.index);
	test_current_token(E_TOKEN_AND);
}

Test(Parser, SeparatorOp_MultipleSemi)
{
	int tokens[] = {
		E_TOKEN_SEMI,
		E_TOKEN_SEMI,
		E_TOKEN_SEMI,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_separator_op(&parser);
	int ret = predict_separator_op(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	cr_assert_eq(1, parser.index);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, SeparatorOp_NoAndOrSemi)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool req = check_requirements_separator_op(&parser);
	int ret = predict_separator_op(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_WORD);
}

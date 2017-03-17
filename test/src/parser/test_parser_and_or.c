#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * and_or           :                         pipe_sequence
 *                  | and_or AND_IF linebreak pipe_sequence
 *                  | and_or OR_IF  linebreak pipe_sequence
 */

Test(Parser, AndOr_OnlyAnd)
{
	// (file name|grep type) 2>&1 >/dev/null && cat name && rm name&
	int	tokens[] = {
		E_TOKEN_LPAREN,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_RPAREN,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_AND_IF,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_AND_IF,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_AND,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_and_or(&parser);
	int		ret = predict_and_or(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_AND);
}

Test(Parser, AndOr_OnlyOr)
{
	// (file name|grep type) 2>&1 >/dev/null || cat name || rm name;
	int	tokens[] = {
		E_TOKEN_LPAREN,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_RPAREN,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_OR_IF,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_OR_IF,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_SEMI,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_and_or(&parser);
	int		ret = predict_and_or(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, AndOr_WithLinebreak)
{
	// cmd1 && \n cmd2 | cmd3 || \n cmd4
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_AND_IF,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_OR_IF,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_and_or(&parser);
	int		ret = predict_and_or(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, AndOr_ErrorWithLinebreak)
{
	// cmd1 && \n cmd2 | cmd3 \n || cmd4 \n
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_AND_IF,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_OR_IF,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_and_or(&parser);
	int		ret = predict_and_or(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_OR_IF);
	cr_assert_eq(parser.index, 7);
}

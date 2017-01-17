#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * io_redirect      :           io_file
 *                  | IO_NUMBER io_file
 *                  |           io_redirect
 *                  | IO_NUMBER io_redirect
 */

/*
 * Tester:
 * - IO_NUMBER
 * - Operator
 * - Words
 */
#define test_redirect(R, I, O, W)			\
	do										\
	{										\
		cr_assert_eq(I, (R).io_number);		\
		cr_assert_eq(O, (R).operator);		\
		cr_assert_eq(W, (R).word->type);	\
	} while (0);							\

struct s_redirection	redir;

Test(Parser, IORedirect_Correct)
{
	/* < file < file */
	int tokens[] = {
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser, &redir);

	// Check Parser
	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_LESS);
	cr_assert_eq(parser.index, 2);

	// Check Redirections
	test_redirect(redir, 0, E_TOKEN_LESS, E_TOKEN_WORD);
}

Test(Parser, IORedirect_CorrectWithIONumber)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 3);
}

Test(Parser, IORedirect_MultipleIONumber)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IORedirect_NoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, IORedirect_WrongTokenForWordAfterRedirection)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_LESS);
	cr_assert_eq(parser.index, 2);
}

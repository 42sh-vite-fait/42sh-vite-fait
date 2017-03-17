#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * redirect_list    :               io_redirect
 *                  | redirect_list io_redirect
 */

Test(Parser, RedirectList_OneValidRedirection)
{
	int tokens[] = {
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, RedirectList_OneValidRedirectionWithIONumber)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, RedirectList_OneInvalidRedirection)
{
	int tokens[] = {
		E_TOKEN_GREAT,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_LESS);
	cr_assert(parser.index, 1);
}

Test(Parser, RedirectList_OneInvalidRedirectionWithIONumber)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREAT,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_LESS);
	cr_assert(parser.index, 2);
}


Test(Parser, RedirectList_MultiplesValidRedirection)
{
	int tokens[] = {
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_LESS,
		E_TOKEN_WORD
		E_TOKEN_DLESS,
		E_TOKEN_WORD
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, RedirectList_MultiplesValidRedirectionWithIONumber)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_LESS,
		E_TOKEN_WORD
		E_TOKEN_DLESS,
		E_TOKEN_WORD
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, RedirectList_AllRedirection)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD
		E_TOKEN_LESSAND,
		E_TOKEN_WORD
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_LESSGREAT,
		E_TOKEN_WORD,
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_CLOBBER,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_redirect(&parser);
	int		ret = predict_io_redirect(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);

}

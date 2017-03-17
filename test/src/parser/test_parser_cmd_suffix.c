#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * cmd_suffix       :            io_redirect
 *                  | cmd_suffix io_redirect
 *                  |            WORD
 *                  | cmd_suffix WORD
 */


Test(Parser, CmdSuffix_OneWord)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdSuffix_MultiplesWord)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdSuffix_OneIORedirect)
{
	int tokens[] = {
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdSuffix_MultiplesIORedirect)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_CLOBBER,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdSuffix_OneWordOneRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdSuffix_MultiplesWordMultiplesRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdSuffix_ErrorAfterSuffixEnd)
{
	// >>file cmd arg|<file2
	int tokens[] = {
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_suffix(&parser);
	int		ret = predict_cmd_suffix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_PIPE);
	cr_assert_eq(parser.index, 4);
}

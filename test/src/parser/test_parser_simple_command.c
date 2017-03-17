#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * simple_command   : cmd_prefix cmd_word cmd_suffix
 *                  | cmd_prefix cmd_word
 *                  | cmd_prefix
 *                  | cmd_name cmd_suffix
 *                  | cmd_name
 *
 * cmd_name         : WORD                   * Apply rule 7a *
 *
 * cmd_word         : WORD                   * Apply rule 7b *
 */


Test(Parser, SimpleCommand_OneWord)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, SimpleCommand_MultiplesWord)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, SimpleCommand_ErrorAssignmentAfterCmdWord)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_ASSIGNMENT_WORD);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, SimpleCommand_MutiplesRedirectionAssignmentAndWord)
{
	// A=B 1<<-file C=D cmd >file2 arg1 arg2 >|file3 arg3;cmd2 2>|file4
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_CLOBBER,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_SEMI,
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_CLOBBER,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, SimpleCommand_NoPrefix)
{
	// cmd 1<<-file >file2 arg1 arg2 >|file3 arg3;cmd2 2>|file4
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_CLOBBER,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_SEMI,
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_CLOBBER,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

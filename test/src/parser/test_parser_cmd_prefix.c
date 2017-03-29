#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * cmd_prefix       :            io_redirect
 *                  | cmd_prefix io_redirect
 *                  |            ASSIGNMENT_WORD
 *                  | cmd_prefix ASSIGNMENT_WORD
 */


Test(Parser, CmdPrefix_OneAssignment)
{
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdPrefix_MultiplesAssignment)
{
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdPrefix_OneIORedirect)
{
	int tokens[] = {
		E_TOKEN_LESS,
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

Test(Parser, CmdPrefix_MultiplesIORedirect)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_GREATAND,
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

Test(Parser, CmdPrefix_OneAssignmentOneRedirection)
{
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
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

Test(Parser, CmdPrefix_MultiplesAssignmentMultiplesRedirection)
{
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, CmdPrefix_RedirectionAfterWord)
{
	// A=B 2>&file C=D cmd >>file2
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_WORD,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 5);
}

Test(Parser, CmdPrefix_ErrorAfterPrefixEnd)
{
	// A=B >> C=D
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_LESSAND,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 3);
}

Test(Parser, CmdPrefix_AssignmentWordAfterRedirection)
{
	// A=B >> C=D
	int tokens[] = {
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_ASSIGNMENT_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_cmd_prefix(&parser);
	int		ret = predict_cmd_prefix(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 2);
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * command          : simple_command
 *                  | subshell
 *                  | subshell redirect_list
 */

Test(Parser, Command_SimpleSubshell)
{
	// (ls 2>&1|grep error && echo 'no error' || echo 'errors';)
	int tokens[] = {
		E_TOKEN_LPAREN,		// (
		E_TOKEN_WORD,		// ls
		E_TOKEN_IO_NUMBER,	// 2
		E_TOKEN_GREATAND,	// >&
		E_TOKEN_WORD,		// 1
		E_TOKEN_PIPE,		// |
		E_TOKEN_WORD,		// grep
		E_TOKEN_WORD,		// error
		E_TOKEN_AND_IF,		// &&
		E_TOKEN_WORD,		// echo
		E_TOKEN_WORD,		// 'no error'
		E_TOKEN_OR_IF,		// ||
		E_TOKEN_WORD,		// echo
		E_TOKEN_WORD,		// 'errors'
		E_TOKEN_SEMI,		// ;
		E_TOKEN_RPAREN,		// )
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_command(&parser);
	int		ret = predict_command(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_END_OF_INPUT);
}

Test(Parser, Command_ErrorEmptySubshell)
{
	// ( )
	int tokens[] = {
		E_TOKEN_LPAREN,
		E_TOKEN_RPAREN,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_command(&parser);
	int		ret = predict_command(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_RPAREN);
}

Test(Parser, Command_SubshellInSubshellWithRedirection)
{
	// (cat (echo $(name))|uniq|grep name) 2>&1 /dev/null;
	int tokens[] = {
		E_TOKEN_LPAREN,		// (
		E_TOKEN_WORD,		// cat
		E_TOKEN_LPAREN,		// (
		E_TOKEN_WORD,		// echo
		E_TOKEN_WORD,		// $(name)
		E_TOKEN_RPAREN,		// )
		E_TOKEN_PIPE,		// |
		E_TOKEN_WORD,		// uniq
		E_TOKEN_PIPE,		// |
		E_TOKEN_WORD,		// grep
		E_TOKEN_WORD,		// name
		E_TOKEN_RPAREN,		// )
		E_TOKEN_IO_NUMBER,	// 2
		E_TOKEN_GREATAND,	// >&
		E_TOKEN_WORD,		// 1
		E_TOKEN_GREAT,		// >
		E_TOKEN_WORD,		// /dev/null
		E_TOKEN_SEMI,		// ;
	};

	setup_tokens(tokens);
	bool	req = check_requirements_command(&parser);
	int		ret = predict_command(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, Command_SimpleCommandFollowingBySubshell)
{
	// cmd1 arg1 >file (ls)
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_LPAREN,
		E_TOKEN_WORD,
		E_TOKEN_RPAREN,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_command(&parser);
	int		ret = predict_command(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_LPAREN);
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * pipe_sequence    :                             command
 *                  | pipe_sequence '|' linebreak command
 */

Test(Parser, PipeSequence_MultiplesSimpleCommandWithoutLinebreak)
{
	// cmd arg|cmd2 1<<file |cmd3 arg3 \n
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_pipe_sequence(&parser);
	int		ret = predict_pipe_sequence(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_NEWLINE);
}

Test(Parser, PipeSequence_MultiplesSimpleCommandWithLinebreak)
{
	// cmd arg|\n\n\n cmd2 1<<file |\n\n cmd3 arg3 ;
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_NEWLINE,
		E_TOKEN_NEWLINE,
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_SEMI,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_pipe_sequence(&parser);
	int		ret = predict_pipe_sequence(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, PipeSequence_ErrorNoCommandAfterLinebreak)
{
	// cmd arg| \n ;
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_NEWLINE,
		E_TOKEN_SEMI,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_pipe_sequence(&parser);
	int		ret = predict_pipe_sequence(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, PipeSequence_SeparatorPrecedence)
{
	// cmd arg; cmd2 | cmd3\n ;
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_WORD,
		E_TOKEN_SEMI,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_pipe_sequence(&parser);
	int		ret = predict_pipe_sequence(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_SEMI);
}

Test(Parser, PipeSequence_ErrorBeginWithPipe)
{
	// | cmd | cmd2
	int	tokens[] = {
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_pipe_sequence(&parser);
	int		ret = predict_pipe_sequence(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_PIPE);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, PipeSequence_ErrorSeparatorBetweenCommand)
{
	// cmd | ; cmd2
	int	tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_PIPE,
		E_TOKEN_SEMI,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};

	setup_tokens(tokens);
	bool	req = check_requirements_pipe_sequence(&parser);
	int		ret = predict_pipe_sequence(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_SEMI);
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * io_file          : '<'       filename
 *                  | LESSAND   filename
 *                  | '>'       filename
 *                  | GREATAND  filename
 *                  | DGREAT    filename
 *                  | LESSGREAT filename
 *
 * filename         : WORD                      * Apply rule 2 *
 */

/*
 * Tout les tests sont de la forme:
 * - <op> <word> <op> <word>
 * - <op> <op> <word> <newline>
 * - <word>
 * - <io_number> <op> <word>
 */

// LESS
Test(Parser, IOFile_LessWithWord)
{
	int tokens[] = {
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_LESS);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOFile_DoubleLess)
{
	int tokens[] = {
		E_TOKEN_LESS,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_LESS);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOFile_LessNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, IOFile_LessIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 0);
}


// LESSAND
Test(Parser, IOFile_LessandWithWord)
{
	int tokens[] = {
		E_TOKEN_LESSAND,
		E_TOKEN_WORD,
		E_TOKEN_LESSAND,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_LESSAND);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOFile_DoubleLessand)
{
	int tokens[] = {
		E_TOKEN_LESSAND,
		E_TOKEN_LESSAND,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_LESSAND);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOFile_LessandNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, IOFile_LessandIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESSAND,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 0);
}


// GREAT
Test(Parser, IOFile_GreatWithWord)
{
	int tokens[] = {
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_GREAT);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOFile_DoubleGreat)
{
	int tokens[] = {
		E_TOKEN_GREAT,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_GREAT);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOFile_GreatNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, IOFile_GreatIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 0);
}


// GREATAND
Test(Parser, IOFile_GreatandWithWord)
{
	int tokens[] = {
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_GREATAND);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOFile_DoubleGreatand)
{
	int tokens[] = {
		E_TOKEN_GREATAND,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_GREATAND);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOFile_GreatandNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, IOFile_GreatandIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_GREATAND,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 0);
}


// DGREAT
Test(Parser, IOFile_DgreatWithWord)
{
	int tokens[] = {
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_DGREAT);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOFile_DoubleDgreat)
{
	int tokens[] = {
		E_TOKEN_DGREAT,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_DGREAT);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOFile_DgreatNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, IOFile_DgreatIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DGREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_IO_NUMBER);
}


// LESSGREAT
Test(Parser, IOFile_LessgreatWithWord)
{
	int tokens[] = {
		E_TOKEN_LESSGREAT,
		E_TOKEN_WORD,
		E_TOKEN_LESSGREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, OK_);
	test_current_token(E_TOKEN_LESSGREAT);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOFile_DoubleLessgreat)
{
	int tokens[] = {
		E_TOKEN_LESSGREAT,
		E_TOKEN_LESSGREAT,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_LESSGREAT);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOFile_LessgreatNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_WORD);
}

Test(Parser, IOFile_LessgreatIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_LESSGREAT,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_file(&parser);
	int		ret = predict_io_file(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERROR_);
	test_current_token(E_TOKEN_IO_NUMBER);
}

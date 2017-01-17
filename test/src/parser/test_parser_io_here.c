#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

/*
 * io_here          : DLESS     here_end
 *                  | DLESSDASH here_end
 *
 * here_end         : WORD          	* Apply rule 3 *
 */

/*
 * Tout les tests sont de la forme:
 * - <op> <word> <op> <word>
 * - <op> <op> <word> <newline>
 * - <word>
 * - <io_number> <op> <word>
 */

// DLESS
Test(Parser, IOHere_DlessWithWord)
{
	int tokens[] = {
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_DLESS);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOHere_DoubleDless)
{
	int tokens[] = {
		E_TOKEN_DLESS,
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_DLESS);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOHere_DlessNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, IOHere_DlessIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESS,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 0);
}


// DLESSDASH
Test(Parser, IOHere_DlessdashWithWord)
{
	int tokens[] = {
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert(req);
	cr_assert_eq(ret, NO_ERROR);
	test_current_token(E_TOKEN_DLESSDASH);
	cr_assert_eq(parser.index, 2);
}

Test(Parser, IOHere_DoubleDlessdash)
{
	int tokens[] = {
		E_TOKEN_DLESSDASH,
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_NEWLINE,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_DLESSDASH);
	cr_assert_eq(parser.index, 1);
}

Test(Parser, IOHere_DlessdasNoRedirection)
{
	int tokens[] = {
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_WORD);
	cr_assert_eq(parser.index, 0);
}

Test(Parser, IOHere_DlessdasIONumberFirst)
{
	int tokens[] = {
		E_TOKEN_IO_NUMBER,
		E_TOKEN_DLESSDASH,
		E_TOKEN_WORD,
		E_TOKEN_END_OF_INPUT,
	};
	setup_tokens(tokens);
	bool	req = check_requirements_io_here(&parser);
	int		ret = predict_io_here(&parser);

	cr_assert_not(req);
	cr_assert_eq(ret, ERR_PARSING);
	test_current_token(E_TOKEN_IO_NUMBER);
	cr_assert_eq(parser.index, 0);
}

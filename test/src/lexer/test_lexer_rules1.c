#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * If the end of input is recognized,
 * the current token (if any) shall be delimited.
 */

TestSuite(LexerRules1, .init = setup, .fini = teardown);

Test(LexerRules1, EmptyString)
{
	char	*input = "";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(0, tokens.len);
}

Test(LexerRules1, OneNewline)
{
	char	*input = "\n";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_NEWLINE, 0, 1, "\n");
}

Test(LexerRules1, MultiNewline)
{
	char	*input = "\n\n\n\n\n\n";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(6, tokens.len);
	test_token(E_TOKEN_NEWLINE, 0, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 1, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 2, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 3, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 4, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 5, 1, "\n");
}

Test(LexerRules1, SimpleCommand)
{
	char	*input = "hello world\n";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(3, tokens.len);
	test_token(E_TOKEN_WORD, 0, 5, "hello");
	test_token(E_TOKEN_WORD, 6, 5, "world");
	test_token(E_TOKEN_NEWLINE, 11, 1, "\n");
}

Test(LexerRules1, EndingWithBackslash)
{
	char	*input = "hello\\";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_WORD, 0, 6, "hello\\");
}

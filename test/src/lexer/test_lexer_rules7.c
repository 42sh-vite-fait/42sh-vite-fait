#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * If the current character is an unquoted <blank>,
 * any token containing the previous character is delimited and the current character shall be discarded.
 */

TestSuite(LexerRules7, .init = setup, .fini = teardown);

Test(LexerRules7, BlankTabulation)
{
	test_lexer("a\tb\t\t\tc", LEXER_INPUT_COMPLETE, 3);

	test_token(E_TOKEN_WORD, 0, 1, "a");
	test_token(E_TOKEN_WORD, 2, 1, "b");
	test_token(E_TOKEN_WORD, 6, 1, "c");
}

Test(LexerRules7, BlankNewline)
{
	test_lexer("a\nb\n\n\nc", LEXER_INPUT_COMPLETE, 7);

	test_token(E_TOKEN_WORD, 0, 1, "a");
	test_token(E_TOKEN_NEWLINE, 1, 1, "\n");
	test_token(E_TOKEN_WORD, 2, 1, "b");
	test_token(E_TOKEN_NEWLINE, 3, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 4, 1, "\n");
	test_token(E_TOKEN_NEWLINE, 5, 1, "\n");
	test_token(E_TOKEN_WORD, 6, 1, "c");
}

Test(LexerRules7, MultipleBlanks)
{
	test_lexer("\t    \t zut\t \t rezut \n  \t\t", LEXER_INPUT_COMPLETE, 3);

	test_token(E_TOKEN_WORD, 7, 3, "zut");
	test_token(E_TOKEN_WORD, 14, 5, "rezut");
	test_token(E_TOKEN_NEWLINE, 20, 1, "\n");
}

Test(LexerRules7, OnlyBlanks)
{
	test_lexer(" \t \t\n", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_NEWLINE, 4, 1, "\n");
}

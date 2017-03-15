#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * If the current character is a '#',
 * it and all subsequent characters up to,
 * but excluding, the next <newline> shall be discarded as a comment.
 * The <newline> that ends the line is not considered part of the comment.
 */

TestSuite(LexerRules9, .init = setup, .fini = teardown);

Test(LexerRules9, SimpleComment)
{
	test_lexer("hello #comment\nworld", LEXER_INPUT_COMPLETE, 3);

	test_token(E_TOKEN_WORD, 0, 5, "hello");
	test_token(E_TOKEN_NEWLINE, 14, 1, "\n");
	test_token(E_TOKEN_WORD, 15, 5, "world");
}

Test(LexerRules9, LineBeginWithComment)
{
	test_lexer("#comment\nworld", LEXER_INPUT_COMPLETE, 2);

	test_token(E_TOKEN_NEWLINE, 8, 1, "\n");
	test_token(E_TOKEN_WORD, 9, 5, "world");
}

Test(LexerRules9, OnlyComment)
{
	test_lexer("#comment", LEXER_INPUT_COMPLETE, 0);
}

Test(LexerRules9, EscapedNewlineInComment)
{
	test_lexer("#comment #com2 #com3\\\n", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_NEWLINE, 21, 1, "\n");
}

Test(LexerRules9, EscapedComment)
{
	test_lexer("\\#comment\n#comment2", LEXER_INPUT_COMPLETE, 2);

	test_token(E_TOKEN_WORD, 0, 9, "\\#comment");
	test_token(E_TOKEN_NEWLINE, 9, 1, "\n");
}

Test(LexerRules9, LowerPrecedenceThanRule8)
{
	test_lexer("abc#def abc #def $(ls#sl)", LEXER_INPUT_COMPLETE, 2);

	test_token(E_TOKEN_WORD, 0, 7, "abc#def");
	test_token(E_TOKEN_WORD, 8, 3, "abc");
}

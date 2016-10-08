#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * ! BANG
 * { LBRACE
 * } RBRACE
 * case
 * esac
 * do
 * done
 * if
 * elif
 * else
 * fi
 * for
 * in
 * then
 * until
 * while
 */

TestSuite(LexerReservedWords, .init = setup, .fini = teardown);

Test(LexerReservedWords, KeywordBang)
{
	test_lexer("! ! x !", LEXER_INPUT_COMPLETE, 4);
	test_token(E_TOKEN_BANG, 0, 1, "!");
	test_token(E_TOKEN_BANG, 2, 1, "!");
	test_token(E_TOKEN_WORD, 4, 1, "x");
	test_token(E_TOKEN_WORD, 6, 1, "!");
}

Test(LexerReservedWords, KeywordLeftBrace)
{
	test_lexer("{", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_LBRACE, 0, 1, "{");
}

Test(LexerReservedWords, KeywordRightBrace)
{
	test_lexer("}", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_RBRACE, 0, 1, "}");
}

Test(LexerReservedWords, KeywordCase)
{
	test_lexer("case", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_CASE, 0, 4, "case");
}

Test(LexerReservedWords, KeywordEsac)
{
	test_lexer("esac", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_ESAC, 0, 4, "esac");
}

Test(LexerReservedWords, KeywordDo)
{
	test_lexer("do", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_DO, 0, 2, "do");
}

Test(LexerReservedWords, KeywordDone)
{
	test_lexer("done", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_DONE, 0, 4, "done");
}

Test(LexerReservedWords, KeywordIf)
{
	test_lexer("if", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_IF, 0, 2, "if");
}

Test(LexerReservedWords, KeywordElif)
{
	test_lexer("elif", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_ELIF, 0, 4, "elif");
}

Test(LexerReservedWords, KeywordElse)
{
	test_lexer("else", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_ELSE, 0, 4, "else");
}

Test(LexerReservedWords, KeywordFi)
{
	test_lexer("fi", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_FI, 0, 2, "fi");
}

Test(LexerReservedWords, KeywordFor)
{
	test_lexer("for", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_FOR, 0, 3, "for");
}

Test(LexerReservedWords, KeywordIn)
{
	test_lexer("in", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_IN, 0, 2, "in");
}

Test(LexerReservedWords, KeywordThen)
{
	test_lexer("then", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_THEN, 0, 4, "then");
}

Test(LexerReservedWords, KeywordUntil)
{
	test_lexer("until", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_UNTIL, 0, 5, "until");
}

Test(LexerReservedWords, KeywordWhile)
{
	test_lexer("while", LEXER_INPUT_COMPLETE, 1);
	test_token(E_TOKEN_WHILE, 0, 5, "while");
}

Test(LexerReservedWords, UncompleteCompoundListWithBrace)
{
	test_lexer("{echo a}\n", LEXER_INPUT_INCOMPLETE, 4);
	test_token(E_TOKEN_LBRACE, 0, 1, "{");
	test_token(E_TOKEN_WORD, 1, 4, "echo");
	test_token(E_TOKEN_WORD, 6, 2, "a}");
	test_token(E_TOKEN_NEWLINE, 8, 1, "\n");

	test_lexer("}\n", LEXER_INPUT_COMPLETE, 6);
	test_token(E_TOKEN_RBRACE, 9, 1, "}");
	test_token(E_TOKEN_NEWLINE, 10, 1, "\n");
}

Test(LexerReservedWords, BashAuthorForFor)
{
	test_lexer("for for in for; do for=for; done; echo $for", LEXER_INPUT_COMPLETE, 12);

	test_token(E_TOKEN_FOR, 0, 3, "for");
	test_token(E_TOKEN_WORD, 4, 3, "for");
	test_token(E_TOKEN_IN, 8, 2, "in");
	test_token(E_TOKEN_WORD, 11, 3, "for");
	test_token(E_TOKEN_SEMI, 14, 1, ";");
	test_token(E_TOKEN_DO, 16, 2, "do");
	test_token(E_TOKEN_ASSIGNEMENT_WORD, 19, 7, "for=for");
	test_token(E_TOKEN_SEMI, 26, 1, ";");
	test_token(E_TOKEN_DONE, 28, 4, "done");
	test_token(E_TOKEN_SEMI, 32, 1, ";");
	test_token(E_TOKEN_WORD, 34, 4, "echo");
	test_token(E_TOKEN_WORD, 39, 4, "$for");
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * If the current character is <backslash>, single-quote, or double-quote and
 * it is not quoted, it shall affect quoting for subsequent characters
 * up to the end of the quoted text.
 * The rules for quoting are as described in Quoting.
 * During token recognition no substitutions shall be actually performed,
 * and the result token shall contain exactly the characters that appear
 * in the input (except for <newline> joining), unmodified,
 * including any embedded or enclosing quotes or substitution operators,
 * between the <quotation-mark> and the end of the quoted text.
 * The token shall not be delimited by the end of the quoted field.
 */

TestSuite(LexerRules4, .init = setup, .fini = teardown);

Test(LexerRules4, QuotedBackslash)
{
	char	*input = "\\\\ '\\' \\\\\\";
	// [\\] [\] [\\\]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(3, tokens.len);
	test_token(E_TOKEN_WORD, 0, 2, "\\\\");
	test_token(E_TOKEN_WORD, 3, 3, "'\\'");
	test_token(E_TOKEN_WORD, 7, 3, "\\\\\\");
}

Test(LexerRules4, UnquotedBackslash)
{
	char	*input = "\\&\\$\\ \\\"";
	// [&$ "]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_WORD, 0, 8, "\\&\\$\\ \\\"");
}

Test(LexerRules4, UnquotedSingleQuote)
{
	char	*input = "'a'b c'd'e f'g '' 'h 'i j' ";
	// [ab] [cde] [fg  h] [i j]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(4, tokens.len);
	test_token(E_TOKEN_WORD, 0, 4, "'a'b");
	test_token(E_TOKEN_WORD, 5, 5, "c'd'e");
	test_token(E_TOKEN_WORD, 11, 9, "f'g '' 'h");
	test_token(E_TOKEN_WORD, 21, 5, "'i j'");
}

Test(LexerRules4, QuotedSingleQuote)
{
	char	*input = "\\' a\\' b\"'\\'\"c d";
	// [\'] [a\'] [b"\"c] [d]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(4, tokens.len);
	test_token(E_TOKEN_WORD, 0, 2, "\\'");
	test_token(E_TOKEN_WORD, 3, 3, "a\\'");
	test_token(E_TOKEN_WORD, 7, 7, "b\"'\\'\"c");
	test_token(E_TOKEN_WORD, 15, 1, "d");
}

Test(LexerRules4, UnquotedDoubleQuote)
{
	char	*input = "\"a\"b c\"d\"e f\"g \"\" \"h \"i j\"";
	// [ab] [cde] [fg  h] [i j]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(4, tokens.len);
	test_token(E_TOKEN_WORD, 0, 4, "\"a\"b");
	test_token(E_TOKEN_WORD, 5, 5, "c\"d\"e");
	test_token(E_TOKEN_WORD, 11, 9, "f\"g \"\" \"h");
	test_token(E_TOKEN_WORD, 21, 5, "\"i j\"");
}

Test(LexerRules4, QuotedDoubleQuote)
{
	char	*input = "\\\" a\\\" b'\"\\\"'c d";
	// [\"] [a\"] [b"\"c] [d]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(4, tokens.len);
	test_token(E_TOKEN_WORD, 0, 2, "\\\"");
	test_token(E_TOKEN_WORD, 3, 3, "a\\\"");
	test_token(E_TOKEN_WORD, 7, 7, "b'\"\\\"'c");
	test_token(E_TOKEN_WORD, 15, 1, "d");
}

Test(LexerRules4, QuoteInsideQuoteEmpty)
{
	char	*input = "\"'\"'\"'";
	// ['"]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_WORD, 0, 6, "\"'\"'\"'");
}

Test(LexerRules4, QuoteInsideQuoteFilled)
{
	char	*input = "a\"b'c\"d'e\"f'g";
	// [ab'cde"fg]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_WORD, 0, 13, "a\"b'c\"d'e\"f'g");
}

Test(LexerRules4, QuotedSimpleCommand)
{
	char	*input = "cat<<'EOF'>\"file 'random\"a\n";
	// [cat] [<<] [EOF] [>] [file 'randoma] [\n]

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(6, tokens.len);
	test_token(E_TOKEN_WORD, 0, 3, "cat");
	test_token(E_TOKEN_DLESS, 3, 2, "<<");
	test_token(E_TOKEN_WORD, 5, 5, "'EOF'");
	test_token(E_TOKEN_GREAT, 10, 1, ">");
	test_token(E_TOKEN_WORD, 11, 15, "\"file 'random\"a");
	test_token(E_TOKEN_NEWLINE, 26, 1, "\n");
}

/*
 * 2.2.1 Escape Character (Backslash)
 * A <backslash> that is not quoted shall preserve the literal value of
 * the following character, with the exception of a <newline>.
 * If a <newline> follows the <backslash>,
 * the shell shall interpret this as line continuation.
 * The <backslash> and <newline> shall be removed before splitting
 * the input into tokens.
 * Since the escaped <newline> is removed entirely from the input
 * and is not replaced by any white space, it cannot serve as a token separator.
 */

Test(LexerRules4, NewlineJoiningBackslash)
{
	char	*input = "abc\\\n";
	// [abc\\ndef] [ghi\\] [jkl]

	t_string string;
	string_init_dup(&string, input);

	int ret = remove_trailing_escaped_newline(&string);
	cr_assert_eq(ret, LINE_INCOMPLETE);

	input = "def ghi\\\\\njkl";
	string_cat(&string, input);
	ret = remove_trailing_escaped_newline(&string);
	cr_assert_eq(ret, LINE_COMPLETE);

	int res = lexer_lex(&lexer, &tokens, string.str);
	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(4, tokens.len, "len %zu", tokens.len);
	test_token(E_TOKEN_WORD, 0, 6, "abcdef");
	test_token(E_TOKEN_WORD, 7, 5, "ghi\\\\");
	test_token(E_TOKEN_NEWLINE, 12, 1, "\n");
	test_token(E_TOKEN_WORD, 13, 3, "jkl");
}

Test(LexerRules4, NewlineJoiningSingleQuote)
{
	char	*input = "a'";

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_INCOMPLETE);
	cr_assert_eq(0, tokens.len);
	/* test_token(E_TOKEN_WORD, 0, 2, "a'"); */

	input = "b\n";
	res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_INCOMPLETE);
	cr_assert_eq(0, tokens.len);
	/* test_token(E_TOKEN_WORD, 0, 4, "a'b\n"); */

	input = "\nc'";
	res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_WORD, 0, 7, "a'b\n\nc'");
}

Test(LexerRules4, QuoteIONumber)
{
	char	*input = "1>'2'>\\3>\"4\">5\\>6'>'7\">\" a8> 10<";

	int res = lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(13, tokens.len);
	test_token(E_TOKEN_IO_NUMBER, 0, 1, "1");
	test_token(E_TOKEN_GREAT, 1, 1, ">");
	test_token(E_TOKEN_WORD, 2, 3, "'2'");
	test_token(E_TOKEN_GREAT, 5, 1, ">");
	test_token(E_TOKEN_WORD, 6, 2, "\\3");
	test_token(E_TOKEN_GREAT, 8, 1, ">");
	test_token(E_TOKEN_WORD, 9, 3, "\"4\"");
	test_token(E_TOKEN_GREAT, 12, 1, ">");
	test_token(E_TOKEN_WORD, 13, 11, "5\\>6'>'7\">\"");
	test_token(E_TOKEN_WORD, 25, 2, "a8");
	test_token(E_TOKEN_GREAT, 27, 1, ">");
	test_token(E_TOKEN_WORD, 29, 2, "10");
	test_token(E_TOKEN_LESS, 31, 1, "<");
}

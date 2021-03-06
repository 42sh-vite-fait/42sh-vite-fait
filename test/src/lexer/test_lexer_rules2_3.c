#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * Rules2:
 * If the previous character was used as part of an operator and
 * the current character is not quoted and
 * can be used with the previous characters to form an operator,
 * it shall be used as part of that (operator) token.
 *
 * Rules3:
 * If the previous character was used as part of an operator and
 * the current character cannot be used with the previous characters
 * to form an operator,
 * the operator containing the previous character shall be delimited.
 */

TestSuite(LexerRules2_3, .init = setup, .fini = teardown);

Test(LexerRules2_3, RedirectionOpLess)
{
	char	*input = "<";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_LESS, 0, 1, "<");
}

Test(LexerRules2_3, RedirectionOpDLess)
{
	char	*input = "<<";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_DLESS, 0, 2, "<<");
}

Test(LexerRules2_3, RedirectionOpGreat)
{
	char	*input = ">";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_GREAT, 0, 1, ">");
}

Test(LexerRules2_3, RedirectionOpDGreat)
{
	char	*input = ">>";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_DGREAT, 0, 2, ">>");
}

Test(LexerRules2_3, RedirectionOpLessAnd)
{
	char	*input = "<&";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_LESSAND, 0, 2, "<&");
}

Test(LexerRules2_3, RedirectionOpGreatAnd)
{
	char	*input = ">&";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_GREATAND, 0, 2, ">&");
}

Test(LexerRules2_3, RedirectionOpLessGreat)
{
	char	*input = "<>";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_LESSGREAT, 0, 2, "<>");
}

Test(LexerRules2_3, ControlOpSemi)
{
	char	*input = ";";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_SEMI, 0, 1, ";");
}

Test(LexerRules2_3, ControlOpPipe)
{
	char	*input = "|";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_PIPE, 0, 1, "|");
}

Test(LexerRules2_3, ControlOpOrIf)
{
	char	*input = "||";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_OR_IF, 0, 2, "||");
}

Test(LexerRules2_3, ControlOpAnd)
{
	char	*input = "&";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_AND, 0, 1, "&");
}

Test(LexerRules2_3, ControlOpAndIf)
{
	char	*input = "&&";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_AND_IF, 0, 2, "&&");
}

Test(LexerRules2_3, ControlOpLParen)
{
	char	*input = "(";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_LPAREN, 0, 1, "(");
}

Test(LexerRules2_3, ControlOpRParen)
{
	char	*input = ")";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(1, tokens.len);
	test_token(E_TOKEN_RPAREN, 0, 1, ")");
}

Test(LexerRules2_3, AllOperatorWithSep)
{
	char	*input = "< > << >> <& >& <> ; | || & && ( )";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(14, tokens.len);
	test_token(E_TOKEN_LESS, 0, 1, "<");
	test_token(E_TOKEN_GREAT, 2, 1, ">");
	test_token(E_TOKEN_DLESS, 4, 2, "<<");
	test_token(E_TOKEN_DGREAT, 7, 2, ">>");
	test_token(E_TOKEN_LESSAND, 10, 2, "<&");
	test_token(E_TOKEN_GREATAND, 13, 2, ">&");
	test_token(E_TOKEN_LESSGREAT, 16, 2, "<>");
	test_token(E_TOKEN_SEMI, 19, 1, ";");
	test_token(E_TOKEN_PIPE, 21, 1, "|");
	test_token(E_TOKEN_OR_IF, 23, 2, "||");
	test_token(E_TOKEN_AND, 26, 1, "&");
	test_token(E_TOKEN_AND_IF, 28, 2, "&&");
	test_token(E_TOKEN_LPAREN, 31, 1, "(");
	test_token(E_TOKEN_RPAREN, 33, 1, ")");
}

Test(LexerRules2_3, AllOpAmbigous)
{
	char	*input = "<>>><<<>>|<&&>&)();;;|||>||&&&&&>&&&";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(24, tokens.len);
	test_token(E_TOKEN_LESSGREAT, 0, 2, "<>");
	test_token(E_TOKEN_DGREAT, 2, 2, ">>");
	test_token(E_TOKEN_DLESS, 4, 2, "<<");
	test_token(E_TOKEN_LESSGREAT, 6, 2, "<>");
	test_token(E_TOKEN_GREAT, 8, 1, ">");
	test_token(E_TOKEN_PIPE, 9, 1, "|");
	test_token(E_TOKEN_LESSAND, 10, 2, "<&");
	test_token(E_TOKEN_AND, 12, 1, "&");
	test_token(E_TOKEN_GREATAND, 13, 2, ">&");
	test_token(E_TOKEN_RPAREN, 15, 1, ")");
	test_token(E_TOKEN_LPAREN, 16, 1, "(");
	test_token(E_TOKEN_RPAREN, 17, 1, ")");
	test_token(E_TOKEN_SEMI, 18, 1, ";");
	test_token(E_TOKEN_SEMI, 19, 1, ";");
	test_token(E_TOKEN_SEMI, 20, 1, ";");
	test_token(E_TOKEN_OR_IF, 21, 2, "||");
	test_token(E_TOKEN_PIPE, 23, 1, "|");
	test_token(E_TOKEN_GREAT, 24, 1, ">");
	test_token(E_TOKEN_OR_IF, 25, 2, "||");
	test_token(E_TOKEN_AND_IF, 27, 2, "&&");
	test_token(E_TOKEN_AND_IF, 29, 2, "&&");
	test_token(E_TOKEN_AND, 31, 1, "&");
	test_token(E_TOKEN_GREATAND, 32, 2, ">&");
	test_token(E_TOKEN_AND_IF, 34, 2, "&&");
}

Test(LexerRules2_3, QuotedOp)
{
	char	*input = "\\&&>\\>'|'|<<\\-\">\"";

	int res = the_true_lexer_lex(&lexer, &tokens, input);

	cr_assert_eq(res, LEXER_INPUT_COMPLETE);
	cr_assert_eq(7, tokens.len);
	test_token(E_TOKEN_WORD, 0, 2, "\\&");
	test_token(E_TOKEN_AND, 2, 1, "&");
	test_token(E_TOKEN_GREAT, 3, 1, ">");
	test_token(E_TOKEN_WORD, 4, 5, "\\>'|'");
	test_token(E_TOKEN_PIPE, 9, 1, "|");
	test_token(E_TOKEN_DLESS, 10, 2, "<<");
	test_token(E_TOKEN_WORD, 12, 5, "\\-\">\"");
}

#include "header.h"
#include "criterion/criterion.h"
#include "test_lexer_utils.c"

/*
 * If the current character is an unquoted <blank>,
 * any token containing the previous character is delimited and the current character shall be discarded.
 */

TestSuite(LexerRules8, .init = setup, .fini = teardown);

Test(LexerRules8, WordAppending)
{
	test_lexer("a\\ b", LEXER_INPUT_COMPLETE, 1);

	test_token(E_TOKEN_WORD, 0, 4, "a\\ b");
}

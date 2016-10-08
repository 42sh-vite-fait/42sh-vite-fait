#include "header.h"
#include "utils.c"

static void	test_02_tokenizer_WordsBlanksOperators(void)
{
	char	*input = "   echo 0ab1>file 2>>merde|<input cat -;<&4 zzz1>&2\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(19, ==, tokens.len);

	test_token(E_TOKEN_WORD, 3, 4, "echo");
	test_token(E_TOKEN_WORD, 8, 4, "0ab1");
	test_token(E_TOKEN_GREAT, 12, 1, ">");
	test_token(E_TOKEN_WORD, 13, 4, "file");
	test_token(E_TOKEN_WORD, 18, 1, "2");
	test_token(E_TOKEN_DGREAT, 19, 2, ">>");
	test_token(E_TOKEN_WORD, 21, 5, "merde");
	test_token(E_TOKEN_PIPE, 26, 1, "|");
	test_token(E_TOKEN_LESS, 27, 1, "<");
	test_token(E_TOKEN_WORD, 28, 5, "input");
	test_token(E_TOKEN_WORD, 34, 3, "cat");
	test_token(E_TOKEN_WORD, 38, 1, "-");
	test_token(E_TOKEN_SEMICOLON, 39, 1, ";");
	test_token(E_TOKEN_LESSAND, 40, 2, "<&");
	test_token(E_TOKEN_WORD, 42, 1, "4");
	test_token(E_TOKEN_WORD, 44, 4, "zzz1");
	test_token(E_TOKEN_GREATAND, 48, 2, ">&");
	test_token(E_TOKEN_WORD, 50, 1, "2");
	test_token(E_TOKEN_NEWLINE, 51, 1, "\n");

	teardown();
	VTS;
}

static void	test_11_tokenizer_BeginWithClosedQuote(void)
{
	char	*input = ") cat";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(2, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 1, "]");
	test_token(E_TOKEN_WORD, 2, 3, "cat");

	teardown();
	VTS;
}

static void	test_16_tokenizer_Assignement(void)
{
	char	*input = "a=b c= d='e' cmd f=g'h' i'=j' 'k=l'";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(7, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 3, "a=b");
	test_token(E_TOKEN_WORD, 4, 2, "c=");
	test_token(E_TOKEN_WORD, 7, 5, "d='e'");
	test_token(E_TOKEN_WORD, 13, 3, "cmd");
	test_token(E_TOKEN_WORD, 17, 6, "f=g'h'");
	test_token(E_TOKEN_WORD, 24, 5, "i'=j'");
	test_token(E_TOKEN_WORD, 30, 5, "'k=l'");

	teardown();
	VTS;
}

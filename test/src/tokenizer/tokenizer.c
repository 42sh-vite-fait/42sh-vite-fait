#include "header.h"

static t_lexer	lexer;
static t_array	tokens;
static t_token	*token;
static size_t	next_token;

static void setup(void)
{
	lexer_init(&lexer);
	array_init(&tokens, sizeof(t_token));
	next_token = 0;
}

static void teardown(void)
{
	lexer_shutdown(&lexer);
	array_shutdown(&tokens);
	next_token = 0;
}

#if 0
static void test_token(uint32_t type, size_t start, size_t len, char *value)
{
	// Récupère le token à tester
	token = array_get_at(&tokens, next_token);

	/* ft_printf("Token: [%s]\n", value); */
	v_assert_uint(type, ==, token->type);
	v_assert_size_t(start, ==, token->start);
	v_assert_size_t(len, ==, token->len);

	(void)value;
	/* int string_cmp = strncmp(lexer->input_str + start, value, len); */
	/* printf("#### input_str: [%s]\n", lexer->input_str + start); */
	/* printf("#### value: [%s]\n", value); */
	/* v_assert_int(0, ==, string_cmp); */

	// La prochaine fois on récupère le token suivant
	next_token += 1;
}
#endif

#define test_token(TYPE, START, LEN, VALUE)			\
	{												\
		token = array_get_at(&tokens, next_token);	\
		v_assert_uint(TYPE, ==, token->type);		\
		v_assert_size_t(START, ==, token->start);	\
		v_assert_size_t(LEN, ==, token->len);		\
		(void)VALUE;								\
		next_token += 1;							\
	}

static void	test_00_tokenizer_SimpleString(void)
{
	char	*input = "hello world\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(3, ==, tokens.len);

	token = array_get_at(&tokens, 0);
	printf("token = %zu %zu %d\n", token->start, token->len, token->type);
	test_token(E_TOKEN_WORD, 0, 5, "hello");
	test_token(E_TOKEN_WORD, 6, 5, "world");
	test_token(E_TOKEN_NEWLINE, 11, 1, "\n");

	teardown();
	VTS;
}

static void	test_01_tokenizer_SimpleStringManyBlanks(void)
{
	char	*input = "\t    \t zut\t \t rezut \t  \t\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(3, ==, tokens.len);

	test_token(E_TOKEN_WORD, 7, 3, "zut");
	test_token(E_TOKEN_WORD, 14, 5, "rezut");
	test_token(E_TOKEN_NEWLINE, 24, 1, "\n");

	teardown();
	VTS;
}

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

static void	test_03_tokenizer_OnlyBlanks(void)
{
	char	*input = " \t \t\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(1, ==, tokens.len);

	test_token(E_TOKEN_NEWLINE, 4, 1, "\n");

	teardown();
	VTS;
}

static void	test_04_tokenizer_EmptyLine(void)
{
	char	*input = "";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(0, ==, tokens.len);

	teardown();
	VTS;
}

static void	test_05_tokenizer_NewlineOnly(void)
{
	char	*input = "\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(1, ==, tokens.len);

	test_token(E_TOKEN_NEWLINE, 0, 1, "\n");

	teardown();
	VTS;
}

static void	test_06_tokenizer_ClosedQuote(void)
{
	/* char	*input = "cat<<'EOF'>`file '\"random`[]a\n"; */
	char	*input = "cat<<'EOF'>\"file 'random\"[]a\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(6, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 3, "cat");
	test_token(E_TOKEN_DLESS, 3, 2, "<<");
	test_token(E_TOKEN_WORD, 5, 5, "'EOF'");
	test_token(E_TOKEN_GREAT, 10, 1, ">");
	test_token(E_TOKEN_WORD, 11, 17, "\"file 'random\"[]a");
	test_token(E_TOKEN_NEWLINE, 28, 1, "\n");

	teardown();
	VTS;
}

static void test_06_5_tokenizer_RequestInput(void)
{
	char	*input = "a";
	char	*input2 = "'";
	int		ret;

	setup();

	ret = lexer_tokenize(&lexer, &tokens, input);
	v_assert_int(LEXER_INPUT_COMPLETE, ==, ret);
	ret = lexer_tokenize(&lexer, &tokens, input2);
	v_assert_int(LEXER_INPUT_INCOMPLETE, ==, ret);

	teardown();
	VTS;
}

#if 1
static void	test_07_tokenizer_UnclosedQuote(void)
{
	char	*input = "'abcdef\n";
	char	*input2 = "ghi'\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);
	lexer_tokenize(&lexer, &tokens, input2);

	v_assert_size_t(2, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 12, "'abcdef\nghi'");
	test_token(E_TOKEN_NEWLINE, 12, 1, "\n");

	teardown();
	VTS;
}

static void	test_08_tokenizer_UnclosedQuoteEmpty(void)
{
	char	*input = "'\n";
	char	*input2 = "long test'\n";

	setup();

	lexer_tokenize(&lexer, &tokens, input);
	lexer_tokenize(&lexer, &tokens, input2);

	v_assert_size_t(2, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 12, "'\nlong test'");
	test_token(E_TOKEN_NEWLINE, 12, 1, "\n");

	teardown();
	VTS;
}
#endif

static void test_09_tokenizer_ClosedQuoteStuckWithWord(void)
{
	char	*input = "a'bc'3>";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(2, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 6, "a'bc'3");
	test_token(E_TOKEN_GREAT, 6, 1, ">");

	teardown();
	VTS;
}

#if 1
static void	test_10_tokenizer_UnclosedQuoteMultiLines(void)
{
	char	*input = "'abc\n";
	char	*input2 = "def\"zzz\"\n";
	char	*input3 = "ghi'\n";
	int		ret;

	setup();

	lexer_tokenize(&lexer, &tokens, input);
	lexer_tokenize(&lexer, &tokens, input2);
	ret = lexer_tokenize(&lexer, &tokens, input3);

	v_assert_int(LEXER_INPUT_COMPLETE, ==, ret);
	v_assert_size_t(2, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 18, "'abc\ndef\"zzz\"\nghi'");
	test_token(E_TOKEN_NEWLINE, 18, 1, "\n");

	teardown();
	VTS;
}
#endif

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

static void	test_12_tokenizer_IOnumber(void)
{
	char	*input = "123a>0;x1<2;88>/dev/null";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(11, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 4, "123a");
	test_token(E_TOKEN_GREAT, 4, 1, ">");
	test_token(E_TOKEN_WORD, 5, 1, "0");
	test_token(E_TOKEN_SEMICOLON, 6, 1, ";");
	test_token(E_TOKEN_WORD, 7, 2, "x1");
	test_token(E_TOKEN_LESS, 9, 1, "<");
	test_token(E_TOKEN_WORD, 10, 1, "2");
	test_token(E_TOKEN_SEMICOLON, 11, 1, ";");
	test_token(E_TOKEN_WORD, 12, 2, "88");
	test_token(E_TOKEN_GREAT, 14, 1, ">");
	test_token(E_TOKEN_WORD, 15, 9, "/dev/null");

	teardown();
	VTS;
}

static void	test_13_tokenizer_Rules4QuoteNumberAndRedirection(void)
{
	char	*input = "ls 'merde'2>&1";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(4, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 2, "ls");
	test_token(E_TOKEN_WORD, 3, 8, "'merde'2");
	test_token(E_TOKEN_GREATAND, 11, 2, ">&");
	test_token(E_TOKEN_WORD, 13, 1, "1");

	teardown();
	VTS;
}

static void	test_14_tokenizer_Rules2OperatorAndQuote(void)
{
	char	*input = "cmd>'>' \"<\"<";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(5, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 3, "cmd");
	test_token(E_TOKEN_GREAT, 3, 1, ">");
	test_token(E_TOKEN_WORD, 4, 3, "'>'");
	test_token(E_TOKEN_WORD, 8, 3, "\"<\"");
	test_token(E_TOKEN_LESS, 11, 1, "<");

	teardown();
	VTS;
}

static void	test_15_tokenizer_Rules7Newline(void)
{
	char	*input = "cmd arg\narg2";

	setup();

	lexer_tokenize(&lexer, &tokens, input);

	v_assert_size_t(4, ==, tokens.len);

	test_token(E_TOKEN_WORD, 0, 3, "cmd");
	test_token(E_TOKEN_WORD, 4, 3, "arg");
	test_token(E_TOKEN_NEWLINE, 7, 1, "\n");
	test_token(E_TOKEN_WORD, 8, 4, "arg2");

	teardown();
	VTS;
}

#if 1
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
#endif

void	suite_tokenizer(void)
{
	test_00_tokenizer_SimpleString();
	test_01_tokenizer_SimpleStringManyBlanks();
	test_02_tokenizer_WordsBlanksOperators();
	test_03_tokenizer_OnlyBlanks();
	test_04_tokenizer_EmptyLine();
	test_05_tokenizer_NewlineOnly();
	test_06_5_tokenizer_RequestInput();
	test_06_tokenizer_ClosedQuote();
	test_07_tokenizer_UnclosedQuote();
	test_08_tokenizer_UnclosedQuoteEmpty();
	test_09_tokenizer_ClosedQuoteStuckWithWord();
	test_10_tokenizer_UnclosedQuoteMultiLines();
	test_11_tokenizer_BeginWithClosedQuote();
	test_12_tokenizer_IOnumber();
	test_13_tokenizer_Rules4QuoteNumberAndRedirection();
	test_14_tokenizer_Rules2OperatorAndQuote();
	test_15_tokenizer_Rules7Newline();
	test_16_tokenizer_Assignement();

	VSS;
}

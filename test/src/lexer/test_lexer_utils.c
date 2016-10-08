#include "header.h"

#define test_token(TYPE, START, LEN, VALUE)					\
	do {													\
		t_token *token = array_get_at(&tokens, next_token);	\
		cr_assert_eq(TYPE, token->type);					\
		cr_assert_eq(START, token->start, "start: %zu\n", token->start);					\
		cr_assert_eq(LEN, token->len);						\
		(void)VALUE;										\
		next_token += 1;									\
	} while(0);

#define test_lexer(INPUT, COMPLETE, LEN)					\
	do {													\
		int res = lexer_lex(&lexer, &tokens, INPUT);		\
		cr_assert_eq(res, COMPLETE);						\
		cr_assert_eq(LEN, tokens.len);						\
	} while(0);												\


static t_lexer	lexer;
static t_array	tokens;
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
	memset(&lexer, 0, sizeof(lexer));
	memset(&tokens, 0, sizeof(tokens));
}

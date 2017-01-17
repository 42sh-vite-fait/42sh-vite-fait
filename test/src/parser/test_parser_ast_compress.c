#include "header.h"
#include "criterion/criterion.h"
#include "test_parser_utils.c"

#define MAX_PIPE (10000)

TestSuite(AST);

static int	tokens_pipe[MAX_PIPE + 1];

Test(AST, Compress10000Pipe, .signal = 0, .fini = teardown)
{
	size_t	i;;
	for (i = 0; i < MAX_PIPE; i += 2)
	{
		tokens_pipe[i] = E_TOKEN_WORD;
		tokens_pipe[i + 1] = E_TOKEN_PIPE;
	}
	tokens_pipe[i] = E_TOKEN_WORD;

	setup_tokens(tokens_pipe);
	ast_init(&parser.ast);

	int ret = parser_parse(&parser);
	cr_assert_eq(ret, NO_ERROR, "index: %zu", parser.index);

	ast_shutdown(&parser.ast);
}

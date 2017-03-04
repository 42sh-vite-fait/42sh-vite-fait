#include <stdio.h>
#include "ft_printf.h"
#include "ast.h"

struct s_ast_debug_print
{
	const char	*name;
	void		(*print_node)(const char*, t_ast_node*, unsigned);
};

static void	ast_debug_print_node_generic(const char *input, t_ast_node *node, unsigned padding);
static void	ast_debug_print_node_redirections(const char *input, t_array redirections, unsigned padding);
static void ast_debug_print_node_simple_command(const char *input, t_ast_node *node, unsigned padding);
static void	ast_debug_print_node_subshell(const char *input, t_ast_node *node, unsigned padding);

static const struct s_ast_debug_print	g_ast_print_node[] = {
	[E_AST_NONE] = {
		"NONE",
		&ast_debug_print_node_generic
	},
	[E_AST_PROGRAM] = {
		"PROGRAM",
		&ast_debug_print_node_generic
	},
	[E_AST_COMPLETE_COMMANDS] = {
		"COMPLETE_COMMANDS",
		&ast_debug_print_node_generic
	},
	[E_AST_COMPLETE_COMMAND] = {
		"COMPLETE_COMMAND",
		&ast_debug_print_node_generic
	},
	[E_AST_LIST] = {
		"LIST",
		&ast_debug_print_node_generic
	},
	[E_AST_AND_OR] = {
		"AND_OR",
		&ast_debug_print_node_generic
	},
	[E_AST_PIPE_SEQUENCE] = {
		"PIPE_SEQUENCE",
		&ast_debug_print_node_generic
	},
	[E_AST_COMMAND] = {
		"COMMAND",
		&ast_debug_print_node_generic
	},
	[E_AST_SUBSHELL] = {
		"SUBSHELL",
		&ast_debug_print_node_subshell,
	},
	[E_AST_COMPOUND_LIST] = {
		"COMPOUND_LIST",
		&ast_debug_print_node_generic
	},
	[E_AST_TERM] = {
		"TERM",
		&ast_debug_print_node_generic
	},
	[E_AST_SIMPLE_COMMAND] = {
		"SIMPLE_COMMAND",
		&ast_debug_print_node_simple_command
	},
};

static void	ast_debug_print_padding(unsigned padding)
{
	char	pad[128];

	ft_memset(pad, '\t', padding);
	pad[padding] = '\0';
	write(1, pad, padding);
}

static void	ast_debug_print_node_redirections(const char *input, t_array redirections, unsigned padding)
{
	for (size_t i = 0; i < redirections.len; ++i)
	{
		ast_debug_print_padding(padding);
		printf("redirections#%zu: ", i);
		struct s_redirection *redir = array_get_at(&redirections, i);
		printf("IO=%zu, ", redir->io_number);
		printf("Operator=%s, ", lexer_debug_get_token_name(redir->operator));
		printf("Word=%.*s\n", (int)redir->word->len, input + redir->word->start);
	}
}

static void ast_debug_print_node_simple_command(const char *input, t_ast_node *node, unsigned padding)
{
	printf("%s: ", g_ast_print_node[node->type].name); // AST node name
	t_token	*token = array_get_first(&node->command.words);
	printf("%.*s\n", (int)token->len, input + token->start);
	padding += 1;

	// redirections
	ast_debug_print_node_redirections(input, node->command.redirections, padding);

	// args
	for (size_t i = 1; i < node->command.words.len; ++i)
	{
		ast_debug_print_padding(padding);
		token = array_get_at(&node->command.words, i);
		printf("args#%zu: %.*s\n", i, (int)token->len, input + token->start);
	}
}

static void	ast_debug_print_node_subshell(const char *input, t_ast_node *node, unsigned padding)
{
	printf("%s: ()\n", g_ast_print_node[node->type].name); // AST node name
	padding += 1;

	// redirections
	ast_debug_print_node_redirections(input, node->command.redirections, padding);
}

static void	ast_debug_print_node_generic(const char *input, t_ast_node *node, unsigned padding)
{
	(void)padding;
	printf("%s: ", g_ast_print_node[node->type].name); // AST node name
	if (node->token  == NULL)
		printf("\n");
	else if (input[node->token->start] == '\n')
		printf("\\n\n");
	else
		printf("%.*s\n", (int)node->token->len, input + node->token->start); // Token symbol
}

static void	ast_debug_print_recursive(const char *input, t_ast_node *node, unsigned padding)
{
	ast_debug_print_padding(padding);
	g_ast_print_node[node->type].print_node(input, node, padding);
	if (node->left != NULL)
		ast_debug_print_recursive(input, node->left, padding + 1);
	if (node->right != NULL)
		ast_debug_print_recursive(input, node->right, padding + 1);
}

void	ast_debug_print(const t_ast *ast, const char *input)
{
	setbuf(stdout, NULL);
	printf("AST:\n");
	ast_debug_print_recursive(input, ast->root, 0);
}

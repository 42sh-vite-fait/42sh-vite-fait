#ifndef AST_H
# define AST_H

# include "array_42.h"
# include "lexer.h"

enum e_ast_node_type
{
	E_AST_NONE,
	E_AST_PROGRAM,
	E_AST_COMPLETE_COMMANDS,
	E_AST_COMPLETE_COMMAND,
	E_AST_LIST,
	E_AST_AND_OR,
	E_AST_PIPE_SEQUENCE,
	E_AST_COMMAND,
	E_AST_SUBSHELL,
	E_AST_COMPOUND_LIST,
	E_AST_TERM,
	E_AST_SIMPLE_COMMAND,
};

typedef struct s_command	t_command;
typedef struct s_ast_node	t_ast_node;
typedef struct s_ast		t_ast;

struct	s_redirection
{
	const t_token	*word;
	size_t	io_number;
	int		operator;
	char	*heredoc_filename;
};

struct	s_command
{
	t_array	words;
	t_array	redirections;
	t_array	assignments;
};

struct	s_ast_node
{
	t_ast_node		*left;
	t_ast_node		*right;
	const t_token	*token;
	t_command		command;
	int				type;
};

struct	s_ast
{
	t_pool		pool;
	t_ast_node	*root;
};

t_ast		*ast_init(t_ast *ast);
void		ast_clear(t_ast *ast);
void		ast_shutdown(t_ast *ast);
void		ast_compress(t_ast *ast);
t_ast_node	*ast_node_create(t_ast *ast);
void		ast_node_remove(t_ast *ast, t_ast_node *node);
void		ast_node_command_init(t_ast_node *node);
void		ast_node_command_shutdown(t_ast_node *node);
void		ast_nodes_clear(t_ast *ast);
void		ast_debug_print(t_ast *ast);

#endif

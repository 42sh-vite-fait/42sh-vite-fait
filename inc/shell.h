#ifndef SHELL_H
# define SHELL_H

#include "string_42.h"
#include "array_42.h"
#include "parser.h"

# define BIN_NAME "42sh"
# define SHELL_PS1 "42sh> "
# define SHELL_PS2 "> "

enum e_shell_errors
{
	SHELL_NO_ERROR = NO_ERROR,
	ERR_SHELL,
	ERR_END_OF_INPUT,
};

int	shell_loop(void);
int	shell_input(t_string *input, const char *prompt);
int	shell_lexer(t_string *input, t_array *tokens);
int	shell_parser(const t_string *input, t_parser *parser, const t_array *tokens);
int	shell_exec(t_ast ast);

#endif

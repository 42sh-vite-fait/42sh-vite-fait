#ifndef SHELL_H
# define SHELL_H

#include "string_42.h"
#include "array_42.h"
#include "parser.h"

# define SHELL_PS1 "42sh> "
# define SHELL_PS2 "> "


void	shell_loop(void);
void	shell_input(t_string *input);
int		shell_lexer(t_string *input, t_array *tokens);
int		shell_parser(t_parser *parser, const t_array *tokens);

#endif

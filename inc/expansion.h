#ifndef EXPANSION_H
# define EXPANSION_H

# include <stddef.h>

t_array	expand_tokens_to_argv(t_array tokens);
char	*expand_quote_removal(const char *s, size_t len);

#endif

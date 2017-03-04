#ifndef EXPANSION_H
# define EXPANSION_H

# include <stddef.h>
# include "array_42.h"

t_array	expand_tokens_to_argv(t_array tokens, const t_string *input);
char	*expand_quote_removal(const char *s, size_t len);

#endif

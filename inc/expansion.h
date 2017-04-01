/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 17:00:15 by djean             #+#    #+#             */
/*   Updated: 2017/03/30 17:00:17 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include <stddef.h>
# include "array_42.h"

t_array	expand_tokens_to_argv(t_array tokens, const t_string *input);
char	*expand_quote_removal(const char *s, size_t len);
int		expand_history(t_string *input);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 20:21:34 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 20:21:36 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*lexer_init(t_lexer *lexer)
{
	if (lexer_init_automaton(&lexer->tokenizer) == NULL)
		return (NULL);
	lexer->input_current_index = 0;
	lexer->token_begin_index = 0;
	return (lexer);
}

void	lexer_shutdown(t_lexer *lexer)
{
	automaton_shutdown(&lexer->tokenizer);
}

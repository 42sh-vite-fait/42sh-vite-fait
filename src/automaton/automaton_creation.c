/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automaton_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:52:30 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 19:52:32 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automaton.h"

t_automaton		*automaton_init(t_automaton *automaton,
								const t_3d_array transition_table)
{
	if (array_init(&automaton->state_stack, sizeof(t_state)) == NULL)
		return (NULL);
	automaton->transition_table = transition_table;
	automaton->current_state = START_STATE;
	return (automaton);
}

void			automaton_shutdown(t_automaton *automaton)
{
	array_shutdown(&automaton->state_stack);
}

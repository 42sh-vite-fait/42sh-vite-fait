/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automaton_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:52:30 by djean             #+#    #+#             */
/*   Updated: 2017/04/02 12:16:34 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "automaton.h"

t_automaton		*automaton_init(t_automaton *automaton,
								const t_3d_array transition_table)
{
	fatal_malloc(array_init(&automaton->state_stack, sizeof(t_state)));
	automaton->transition_table = transition_table;
	automaton->current_state = START_STATE;
	return (automaton);
}

void			automaton_shutdown(t_automaton *automaton)
{
	array_shutdown(&automaton->state_stack);
}

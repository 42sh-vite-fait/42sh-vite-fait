/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   automaton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djean <djean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 19:52:30 by djean             #+#    #+#             */
/*   Updated: 2017/04/01 19:52:32 by djean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "array_42.h"
#include "automaton.h"

#define NOTHING ((void)0)

static t_state		get_stack_state(const t_array *stack)
{
	if (ARRAY_IS_EMPTY(stack))
		return (EMPTY_STACK);
	else
		return (*(t_state *)array_get_last(stack));
}

static t_transition	get_transition(const t_automaton *a, t_symbol s)
{
	t_state			stack_state;
	t_transition	trans;
	uint32_t		x;
	uint32_t		y;

	stack_state = get_stack_state(&a->state_stack);
	x = a->transition_table.size_x;
	y = a->transition_table.size_y;
	trans = ((const t_transition (*)[y][x])a->transition_table.data)
		[a->current_state]
		[stack_state]
		[s];
	return (trans);
}

bool				is_automaton_next_state_error(t_automaton *a, t_symbol s)
{
	return (get_transition(a, s).next_state == ERROR_STATE);
}

void				automaton_step(t_automaton *a, t_symbol s)
{
	t_transition		trans;

	trans = get_transition(a, s);
	if (trans.stack_action == E_PUSH)
		fatal_malloc(array_push(&a->state_stack, &trans.pushed_state));
	else if (trans.stack_action == E_POP)
		array_pop(&a->state_stack, NULL);
	else if (trans.stack_action == E_NO_ACTION)
		NOTHING;
	a->current_state = trans.next_state;
}

void				automaton_reset(t_automaton *a)
{
	a->current_state = START_STATE;
	array_clear(&a->state_stack);
}

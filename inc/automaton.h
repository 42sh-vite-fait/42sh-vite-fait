#ifndef AUTOMATON_H
# define AUTOMATON_H

# include <limits.h>
# include <stdint.h>
# include <stdbool.h>
# include "array_42.h"
# include "array_3d.h"

/*
** The automaton module is an implementation of
** a pushdown automaton.
** And automaton possesses a stack of symbols, a current
** state, and a transition table. Given an input symbol,
** its current state and its stack top symbol, the automaton
** will make a transition to a new state, and optionaly
** manipulate the stack (push or pop).
*/

# define EMPTY_STACK 0U
# define ERROR_STATE 0U
# define START_STATE 1U

# define TRANS_AND_PUSH(N,P){.stack_action=E_PUSH,.pushed_state=P,.next_state=N}
# define TRANS_AND_POP(N) {.stack_action=E_POP, .next_state=N}
# define TRANS(N) {.stack_action=E_NO_ACTION, .next_state=N}

enum	e_stack_action
{
	E_NO_ACTION,
	E_PUSH,
	E_POP,
};

typedef enum e_stack_action		t_stack_action;
typedef uint32_t				t_state;
typedef uint32_t				t_symbol;
typedef struct s_transition		t_transition;
typedef struct s_automaton		t_automaton;

struct		s_transition
{
	t_stack_action	stack_action;
	t_state			next_state;
	t_state			pushed_state;
};

struct		s_automaton
{
	t_array				state_stack;
	t_3d_array			transition_table;
	t_state				current_state;
	uint8_t				pad[4];
};

/*
** `automaton_init` initializes a given automaton
** with a given transition table and sets its current
** state to START_STATE.
**
** `automaton_shutdown` release the resources of an
** automaton initialized with `automaton_init`
*/
t_automaton	*automaton_init(t_automaton *automaton,
		const t_3d_array transition_table);
void		automaton_shutdown(t_automaton *automaton);

/*
** `automaton_step` makes one transition according to
** a given symbol.
**
** `is_automaton_next_state_error` returns true if a
** transition according to a given symbol results in an
** error state, false otherwise.
**
** `automaton_reset` empties the stack and sets the
** current state to START_STATE.
*/
void		automaton_step(t_automaton *a, t_symbol s);
bool		is_automaton_next_state_error(t_automaton *a, t_symbol s);
void		automaton_reset(t_automaton *a);

#endif

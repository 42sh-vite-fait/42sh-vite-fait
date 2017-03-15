#include "history_expansion.h"

static enum e_state		get_state(enum e_state state, char c)
{
	if (state == E_START)
	{
		if (c == '-' || c == '!')
			return (E_BACK_NUM);
		if (c >= '0' && c <= '9')
			return (E_NUM);
		if (FT_ISALNUM(c))
			return (E_STRING);
	}
	else if (state == E_NUM || state == E_BACK_NUM)
	{
		if (!(c >= '0' && c <= '9'))
			return (E_FINISHED);
		else
			return (state);
	}
	else if (state == E_STRING)
	{
		if (!(FT_ISALNUM(c)))
			return (E_FINISHED);
		else
			return (state);
	}
	return (E_FINISHED);
}

static enum e_state		apply_char(t_exp *outexp, enum e_state state,
							char c, size_t *j)
{
	if ((state == E_BACK_NUM || state == E_NUM) && c >= '0' && c <= '9')
	{
		outexp->n_back = outexp->n_back * 10 + (c - '0');
		return (state);
	}
	if (state == E_STRING)
	{
		fatal_malloc(string_insert(&outexp->string, outexp->string.len, &c, 1));
	}
	if (state == E_BACK_NUM && c == '!' && outexp->n_back == 0)
	{
		outexp->n_back = 1;
		(*j)++;
		return (E_FINISHED);
	}
	return (state);
}

size_t					identify_expansion(t_exp *outexp,
							t_string command, size_t i)
{
	size_t				j;
	enum e_state		state;

	state = E_START;
	outexp->offset = i;
	outexp->n_back = 0;
	fatal_malloc(string_init(&(outexp->string)));
	j = 1;
	while (i + j < command.len && state != E_FINISHED)
	{
		state = get_state(state, command.str[j + i]);
		if (state == E_NUM)
			outexp->type = E_TYPE_NUM;
		if (state == E_STRING)
			outexp->type = E_TYPE_STRING;
		if (state == E_BACK_NUM)
			outexp->type = E_TYPE_BACK_NUM;
		state = apply_char(outexp, state, command.str[j + i], &j);
		j++;
	}
	outexp->size = j - 1;
	return (j - 1);
}

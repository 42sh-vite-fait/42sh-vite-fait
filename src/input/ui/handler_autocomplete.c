#include "ctype_42.h"
#include "autocompletion.h"
#include "user_interface.h"

static size_t	word_backward(const t_term_line *line)
{
	size_t	i;
	int		tmp;

	i = 0;
	tmp = (int)line->string_index - 1;
	while (tmp >= 0 && !FT_ISBLANK(line->str->str[tmp]))
	{
		i += 1;
		tmp -= 1;
	}
	return (i);
}

static size_t	word_forward(const t_term_line *line)
{
	size_t	i;
	int		tmp;

	i = 0;
	tmp = (int)line->string_index;
	while (tmp < (int)line->str->len && !FT_ISBLANK(line->str->str[tmp]))
	{
		i += 1;
		tmp += 1;
	}
	return (i);
}

void			ui_handler_autocomplete(t_term_env *env, char c)
{
	char		*new_word;
	const char	*word;
	size_t		word_len;

	(void)c;
	if (env->autocomplete_state == E_NO_AUTOCOMPLETE)
	{
		env->autocomplete_index = 0;
		word_len = word_backward(&env->line) + word_forward(&env->line);
		word = env->line.str->str + env->line.string_index
			- word_backward(&env->line);
		array_clear(&env->autocomplete_matches);
		autocomplete(&env->autocomplete_matches, word, word_len);
	}
	if (env->autocomplete_matches.len == 0)
		return ;
	line_move_cursor(&env->line, -(int)word_backward(&env->line));
	env->line.string_index -= word_backward(&env->line);
	new_word = *(char **)array_get_at(&env->autocomplete_matches,
							env->autocomplete_index);
	line_remove_right(&env->line, word_forward(&env->line));
	line_insert(&env->line, new_word, ft_strlen(new_word));
	env->autocomplete_index += 1;
	env->autocomplete_index %= env->autocomplete_matches.len;
	env->autocomplete_state = E_LAST_CMD_REALLY_WAS_AUTOCOMPLETE;
}

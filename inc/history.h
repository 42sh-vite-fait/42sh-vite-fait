#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <stdbool.h>
# include "typedefs_42.h"
# include "cbuffer_42.h"

struct		s_history
{
	t_cbuffer	cbuffer;
	size_t		last_id;
};

struct		s_result
{
	size_t	command_id;
	size_t	offset;
};

typedef struct s_history	t_history;
typedef struct s_result		t_result;

t_history		*history_new(size_t limit);
t_history		*history_init(t_history *history, size_t limit);

size_t			history_push(t_history *history, const char *command);

const char		*history_get_id(t_history const *history, size_t id);

bool			history_contains(t_history const *history, size_t id);

// TODO think about the t_result*
t_result		*history_search_first(t_history const *hist, const char *patt);
// t_result		*history_search_next(t_history const *hist, t_result result,
// 										const char *patt);

#endif

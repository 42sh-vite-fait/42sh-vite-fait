#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include "typedefs_42.h"
# include "cbuffer_42.h"

struct		s_history
{
	t_cbuffer	cbuffer;
	size_t		last_id;
};

typedef struct s_history	t_history;

// # define HISTORY_CONTAIN();

t_history		*history_new(size_t limit);
t_history		*history_init(t_history *history, size_t limit);

size_t			history_push(t_history *history, char const *command);

char const		*history_get_id(t_history const *history, size_t id);

#endif

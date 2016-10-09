#ifndef HISTORY_H
# define HISTORY_H

# include <stdlib.h>
# include <stdbool.h>
# include "typedefs_42.h"
# include "structs_42.h"
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

# define WRITE_BUFF_LEN 4096 // TODO get_page_size

t_history	*history_new(size_t limit);
t_history	*history_init(t_history *history, size_t limit);

int			history_save_into_file(t_history const *history, int fd);
int			history_load_from_file(t_history *history, int fd);

size_t		history_push(t_history *history, const char *command);

const char	*history_get_id(t_history const *history, size_t id);

bool		history_contains(t_history const *history, size_t id);

bool		history_find(t_result *ret, t_history const *h, const char *patt);
bool		history_find_from(t_result *ret, t_history const *history,
								const char *pattern, t_result from);
bool		history_find_start_with(t_result *res, t_history const *history,
									const char *pattern);

#endif

#include <stdbool.h>
#include <stdlib.h>
#include "history.h"

bool	history_contains(t_history const *hist, size_t id)
{
	return (id <= hist->last_id && id > hist->last_id - hist->cbuffer.len);
}

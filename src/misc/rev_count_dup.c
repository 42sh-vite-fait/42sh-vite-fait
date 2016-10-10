#include <unistd.h>
#include "misc.h"

// TODO better name ?
size_t		rev_count_dup(const char *from, const char *to, int c)
{
	size_t		count;

	count = 0;
	while (from >= to && *from == (char)c)
	{
		++count;
		--from;
	}
	return (count);
}

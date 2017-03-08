#include <unistd.h>
#include "string_42.h"
#include "misc.h"

t_string	*string_read_from_fd(t_string *s, int fd)
{
	char		buff[MEM_PAGE_SIZE];
	ssize_t		ret;

	while ((ret = read(fd, buff, MEM_PAGE_SIZE)) > 0)
		fatal_malloc(string_ncat(s, buff, (size_t)ret));
	if (ret == -1)
		return (NULL);
	return (s);
}

int			string_write_to_fd(const t_string *s, int fd)
{
	ssize_t		ret;
	size_t		offset;

	offset = 0;
	while ((ret = write(fd, s->str + offset, s->len - offset)) > 0)
		offset += (size_t)ret;
	return ((int)ret);
}

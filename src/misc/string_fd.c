#include <unistd.h>
#include "memory_42.h"
#include "string_42.h"
#include "misc.h"

t_string	*string_read_from_fd(t_string *s, int fd)
{
	char		buff[MEM_PAGE_SIZE];
	ssize_t		ret;

	if (string_init_with_capacity(s, MEM_PAGE_SIZE) == NULL)
		return (NULL);
	while ((ret = read(fd, buff, MEM_PAGE_SIZE)) == MEM_PAGE_SIZE)
	{
		if (string_ncat(s, buff, (size_t)ret) == NULL)
		{
			string_shutdown(s);
			return (NULL);
		}
	}
	if (string_ncat(s, buff, (size_t)ret) == NULL)
	{
		string_shutdown(s);
		return (NULL);
	}
	return (s);
}

int			string_write_to_fd(const t_string *s, int fd)
{
	ssize_t		ret;

	ret = 0;
	while ((ret = write(fd, s->str + (size_t)ret, s->len - (size_t)ret)) > 0)
	{
		if (ret == -1)
			return (-1);
	}
	return (0);
}

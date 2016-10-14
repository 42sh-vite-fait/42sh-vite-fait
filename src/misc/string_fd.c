#include <unistd.h>
#include "memory_42.h"
#include "string_42.h"
#include "misc.h"

t_string	*string_read_from_fd(t_string *buffer, int fd)
{
	char		buff[MEM_PAGE_SIZE];
	ssize_t		ret;

	string_init(buffer, MEM_PAGE_SIZE);
	while ((ret = read(fd, buff, MEM_PAGE_SIZE)) == MEM_PAGE_SIZE)
	{
		if (string_ncat(buffer, buff, (size_t)ret) == NULL)
		{
			free(buffer->str);
			return (NULL);
		}
	}
	if (string_ncat(buffer, buff, (size_t)ret) == NULL)
	{
		free(buffer->str);
		return (NULL);
	}
	return (buffer);
}

int			string_write_to_fd(const t_string *b, int fd)
{
	ssize_t		ret;

	ret = 0;
	while ((ret = write(fd, b->str + (size_t)ret, b->len - (size_t)ret)) > 0)
	{
		if (ret == -1)
			return (-1);
	}
	return (0);
}

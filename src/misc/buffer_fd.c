#include <unistd.h>
#include "memory_42.h"
#include "buffer_42.h"
#include "misc.h"

t_buffer	*buffer_read_from_fd(t_buffer *buffer, int fd)
{
	char		buff[MEM_PAGE_SIZE];
	ssize_t		ret;

	buffer_init(buffer, MEM_PAGE_SIZE);
	while ((ret = read(fd, buff, MEM_PAGE_SIZE)) == MEM_PAGE_SIZE)
	{
		if (buffer_ncat(buffer, buff, (size_t)ret) == NULL)
		{
			free(buffer->str);
			return (NULL);
		}
	}
	if (buffer_ncat(buffer, buff, (size_t)ret) == NULL)
	{
		free(buffer->str);
		return (NULL);
	}
	return (buffer);
}

int			buffer_write_to_fd(const t_buffer *b, int fd)
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

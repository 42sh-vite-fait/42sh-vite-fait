#include <unistd.h>
#include "memory_42.h"
#include "buffer_42.h"
#include "misc.h"

t_buffer	*buffer_read_from_fd(int fd)
{
	char		buff[MEM_PAGE_SIZE];
	t_buffer	*buffer;
	ssize_t		ret;

	buffer = buffer_new(MEM_PAGE_SIZE);
	while ((ret = read(fd, buff, MEM_PAGE_SIZE)) == MEM_PAGE_SIZE)
	{
		if (buffer_insert(buffer, buffer->len, buff, (size_t)ret) == NULL)
		{
			buffer_destroy(buffer);
			return (NULL);
		}
	}
	if (buffer_insert(buffer, buffer->len, buff, (size_t)ret) == NULL)
	{
		buffer_destroy(buffer);
		return (NULL);
	}
	return (buffer);
}

int			buffer_write_to_fd(t_buffer *b, int fd)
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

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

static bool	is_fd_open(int fd)
{
	errno = 0;
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

int main(void)
{
	for (size_t i = 0; i < 1024; ++i)
		if (is_fd_open(i))
			printf("fd %zu is open\n", i);
}

#include <sys/syslimits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>

/*
** Source: http://stackoverflow.com/questions/1188757/getting-filename-from-file-descriptor-in-c
*/
static void	print_fd_info(int fd)
{
	char filePath[PATH_MAX];

	printf("fd %d is open, ", fd);
	if (fcntl(fd, F_GETPATH, filePath) != -1)
		printf("filename [%s]\n", filePath);
	else
		printf("no filename\n");
}

static bool	is_fd_open(int fd)
{
	errno = 0;
	return (fcntl(fd, F_GETFD) != -1 || errno != EBADF);
}

int main(void)
{
	for (size_t i = 0; i < 1024; ++i)
		if (is_fd_open(i))
			print_fd_info(i);
}

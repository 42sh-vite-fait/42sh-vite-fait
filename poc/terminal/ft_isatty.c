#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	int	fd;

	if (argc < 2)
		exit(1);
	fd = atoi(argv[1]);
	if (isatty(fd))
		printf("%d is a tty\n", fd);
	else
		printf("%d is not a tty\n", fd);
}

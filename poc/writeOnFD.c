#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, const char *argv[])
{
	if (argc > 1)
	{
		int fd = open("writed", O_WRONLY | O_CREAT, 0644);
		int duped = atoi(argv[1]);
		char c[2] = {argv[1][0], '\n'};
		assert(fd != -1);
		dup2(fd, duped);
		write(duped, c, 2);
	}
}

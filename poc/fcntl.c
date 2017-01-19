#include <fcntl.h>
#include <stdio.h>

#define O_FLAGS (O_RDWR)

int main(void)
{
	int fd = open("fcntl.c", O_FLAGS);
	if (fd == -1)
		printf("open error\n");
	int flags = fcntl(fd, F_GETFL);
	if (flags == -1)
		printf("fcntl error\n");
	printf("flags[%d] | orig[%d]\n", flags, O_FLAGS);
	printf("O_RDWR: %d | O_RDONLY: %d | O_WRONLY: %d\n", O_RDWR, O_RDONLY, O_WRONLY);
}

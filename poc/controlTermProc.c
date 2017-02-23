#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	printf("ctermid: %s\n", ctermid(NULL));
	int fd = open("/dev/tty", O_RDWR);
	dprintf(fd, "fd: %d\n", fd);
	dprintf(fd, "ttyname(0): %s\n", ttyname(0));
	dprintf(fd, "ttyname(fd): %s\n", ttyname(fd));
}

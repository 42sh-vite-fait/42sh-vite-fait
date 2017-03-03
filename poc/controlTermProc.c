#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <signal.h>

void print_tty(void)
{
	printf("ctermid: %s\n", ctermid(NULL));
	int fd = open("/dev/tty", O_RDWR);
	dprintf(fd, "fd: %d\n", fd);
	dprintf(fd, "ttyname(0): %s\n", ttyname(0));
	dprintf(fd, "ttyname(fd): %s\n", ttyname(fd));
}

void conflict_grab_controlling_term(void)
{
	pid_t	pid;
	int		ret;

	signal(SIGTTOU, SIG_IGN);
	switch (pid = fork())
	{
		case -1:
			abort();
			break;
		case 0:
			// create process group
			ret = setpgid(0, 0);
			assert(ret != -1);

			signal(SIGTTOU, SIG_DFL);

			// grab the controlling term
			ret = tcsetpgrp(0, getpid());
			assert(ret != -1);

			execlp("cat", "cat", NULL);
			abort();
			break;
		default:
			// create child process group
			ret = setpgid(pid, pid);
			assert(ret != -1);

			// give away the controlling term to the child
			ret = tcsetpgrp(0, pid);
			assert(ret != -1);

			// wait for it
			wait(NULL);

			// grab back the controlling term
			ret = tcsetpgrp(0, getpid());
			assert(ret != -1);

			printf("everything went fine\n");
			exit(0);
	}
}

int main(void)
{
	conflict_grab_controlling_term();
}

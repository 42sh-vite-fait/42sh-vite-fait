#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void print_info(const char *name)
{
	printf("%s\n", name);
	printf("SID: %d\n", getsid(0));
	printf("PGID: %d\n", getpgrp());
	printf("PID: %d\n", getpid());
	printf("PPID: %d\n", getppid());
	puts("");
}

void print_parent_info()
{
	printf("Parent (shell)\n");
	pid_t	ppid = getppid();
	printf("SID: %d\n", getsid(ppid));
	printf("PGID: %d\n", getpgid(ppid));
	printf("PID: %d\n", ppid);
	puts("");
}

int main(void)
{
	print_info("Current (before fork)");
	print_parent_info();
	puts("fork()");
	if (fork() == 0)
		print_info("child");
	else
	{
		print_info("parent of fork");
		wait(0);
	}
}

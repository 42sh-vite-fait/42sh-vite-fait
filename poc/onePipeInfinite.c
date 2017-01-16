#include <unistd.h>
#include <sys/wait.h>

/*
 * cmd: cat /dev/random | head -c8
 */

int main(void)
{
	int	p[2];

	pipe(p);
	if (fork() == 0)
	{
		/* cat /dev/random */
		close(p[0]); // read end
		dup2(p[1], STDOUT_FILENO); // write end
		execlp("cat", "cat", "/dev/random", (char*)0);
	}
	close(p[1]); // write end
	if (fork() == 0)
	{
		/* head -c 1 */
		dup2(p[0], STDIN_FILENO); // read end
		execlp("head", "head", "-c1", (char*)0);
	}
	close(p[0]);
	wait(NULL);
	wait(NULL);
}

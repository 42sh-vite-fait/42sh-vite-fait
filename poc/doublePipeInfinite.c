#include <unistd.h>
#define STDIN (0)
#define STDOUT (1)

/*
 * cmd: cat /dev/random | base64 | head -c8
 */

int main(void)
{
	int	p[2];
	int	q[2];

	pipe(p);
	pipe(q);

	if (fork() == 0)
	{
		/* cat /dev/random */
		dup2(p[1], STDOUT);
		execlp("cat", "cat", "/dev/random", (char*)0);
	}
	if (fork() == 0)
	{
		/* base64 */
		dup2(p[0], STDIN);
		dup2(q[1], STDOUT);
		execlp("base64", "base64", (char*)0);
	}
	if (fork() == 0)
	{
		/* head -c 8 */
		dup2(q[0], STDIN);
		execlp("head", "head", "-c8", (char*)0);
	}
}

#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	enable_rawmode(void);
void	disable_rawmode(void);

int main(void)
{
	char c[1024];

	memset(c, 'a', sizeof(c));
	c[sizeof(c) - 1] = '\0';
	enable_rawmode();
	setbuf(stdout, NULL);

	printf("%s", c);
	printf("\x1b[4A");
	printf("HERE");
	printf("\x1b[2B");
	printf("HERE");

	disable_rawmode();
	pause();
}

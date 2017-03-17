#include <unistd.h>
#include <stdio.h>

/*
 * Comment se comporte 'write' en cas de 'cmd >&-'
 */

int main(void)
{
	dprintf(0, "ret: %zd\n", write(1, "stdout\n", 7));
	dprintf(0, "ret: %zd\n", write(2, "stderr\n", 7));
}

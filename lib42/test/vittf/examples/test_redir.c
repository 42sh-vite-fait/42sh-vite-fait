#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "vittf.h"

#define BUFFER_SIZE 64

static void	test_redirection_stderr(void)
{
	char	buf[BUFFER_SIZE];
	char	s[] = "Hello World";

	v_redirect_setup(2);
	fprintf(stderr, "%s", s);
	v_redirect_read(buf, BUFFER_SIZE);
	v_redirect_teardown();

	assert(strcmp(buf, s) == 0);
}

static void	test_redirection_stdout(void)
{
	char	buf[BUFFER_SIZE];
	char	s[] = "Hello World";

	v_redirect_setup(1);
	printf("%s", s);
	v_redirect_read(buf, BUFFER_SIZE);
	v_redirect_teardown();

	assert(strcmp(buf, s) == 0);
}

int	main(void)
{
	test_redirection_stdout();
	test_redirection_stderr();

	printf("===> Test redirection Ok");
}

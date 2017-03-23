#include "header.h"

void	test_realloc(void)
{
	size_t	size;
	void	*buf;
	void	*buf2;

	size = 1024;
	buf = malloc(size);
	buf2 = malloc(size);
	memset(buf, 'a', size);
	memset(buf2, 'a', size);
	buf = ft_realloc(buf, size << 1, size);
	v_assert(memcmp(buf, buf2, size) == 0);
	memset(buf, 'b', size << 1);
	free(buf);
	free(buf2);

	v_test_success(__func__);
}

void	suite_realloc(void)
{
	test_realloc();

	v_suite_success(__func__);
}

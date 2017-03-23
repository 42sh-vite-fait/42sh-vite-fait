#include "header.h"

static void	test_00_memccpy_AlignedCharInString(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*res;
	char	c = '$';

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	off_src[index] = c;
	ft_src[index] = c;

	memccpy(off_dst, off_src, c, buf_size);
	res = ft_memccpy(ft_dst, ft_src, c, buf_size);

	v_assert_ptr(res, ==, ft_dst + index + 1);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_01_memccpy_MisalignedCharInString(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*res;
	char	c = '$';

	// setup
	--buf_size;
	off_src++;
	off_dst++;
	ft_src++;
	ft_dst++;
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	off_src[index] = c;
	ft_src[index] = c;

	memccpy(off_dst, off_src, c, buf_size);
	res = ft_memccpy(ft_dst, ft_src, c, buf_size);

	v_assert_ptr(res, ==, ft_dst + index + 1);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src - 1);
	free(off_dst - 1);
	free(ft_src - 1);
	free(ft_dst - 1);
	VTS;
}

static void	test_02_memccpy_AlignedCharNotInString(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*off_res;
	void	*ft_res;
	char	c = '$';

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	off_res = memccpy(off_dst, off_src, c, buf_size);
	ft_res = ft_memccpy(ft_dst, ft_src, c, buf_size);

	v_assert_ptr(NULL, ==, off_res);
	v_assert_ptr(off_res, ==, ft_res);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_03_memccpy_MisalignedCharNotInString(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*off_res;
	void	*ft_res;
	char	c = '$';

	// setup
	--buf_size;
	off_src++;
	off_dst++;
	ft_src++;
	ft_dst++;
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	off_res = memccpy(off_dst, off_src, c, buf_size);
	ft_res = ft_memccpy(ft_dst, ft_src, c, buf_size);

	v_assert_ptr(NULL, ==, off_res);
	v_assert_ptr(off_res, ==, ft_res);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src - 1);
	free(off_dst - 1);
	free(ft_src - 1);
	free(ft_dst - 1);
	VTS;
}

static void	test_04_memccpy_AlignedCharAfterSizemax(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*off_res;
	void	*ft_res;
	char	c = '$';

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);
	off_src[index] = c;
	ft_src[index] = c;

	off_res = memccpy(off_dst, off_src, c, index);
	ft_res = ft_memccpy(ft_dst, ft_src, c, index);

	v_assert_ptr(NULL, ==, off_res);
	v_assert_ptr(off_res, ==, ft_res);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_05_memccpy_MisalignedCharAfterSizemax(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*off_res;
	void	*ft_res;
	char	c = '$';

	// setup
	--buf_size;
	off_src++;
	off_dst++;
	ft_src++;
	ft_dst++;
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);
	off_src[index] = c;
	ft_src[index] = c;

	off_res = memccpy(off_dst, off_src, c, index);
	ft_res = ft_memccpy(ft_dst, ft_src, c, index);

	v_assert_ptr(NULL, ==, off_res);
	v_assert_ptr(off_res, ==, ft_res);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src - 1);
	free(off_dst - 1);
	free(ft_src - 1);
	free(ft_dst - 1);
	VTS;
}

static void	test_06_memccpy_SizeOfZero(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	size_t	index = 10;
	void	*off_res;
	void	*ft_res;
	char	c = '$';

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);
	off_src[index] = c;
	ft_src[index] = c;

	off_res = memccpy(off_dst, off_src, c, 0);
	ft_res = ft_memccpy(ft_dst, ft_src, c, 0);

	v_assert_ptr(NULL, ==, off_res);
	v_assert_ptr(off_res, ==, ft_res);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

void		suite_memccpy(void)
{
	test_00_memccpy_AlignedCharInString();
	test_01_memccpy_MisalignedCharInString();
	test_02_memccpy_AlignedCharNotInString();
	test_03_memccpy_MisalignedCharNotInString();
	test_04_memccpy_AlignedCharAfterSizemax();
	test_05_memccpy_MisalignedCharAfterSizemax();
	test_06_memccpy_SizeOfZero();

	VSS;
}

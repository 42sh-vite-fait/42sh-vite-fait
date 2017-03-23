#include "header.h"

static void	test_00_memcpy_AlignedSizeOfZero(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	memcpy(off_dst, off_src, 0);
	res = ft_memcpy(ft_dst, ft_src, 0);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_01_memcpy_MisalignedSizeOfZero(void)
{
	size_t	buf_size = 20;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

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

	memcpy(off_dst, off_src, 0);
	res = ft_memcpy(ft_dst, ft_src, 0);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(--off_src);
	free(--off_dst);
	free(--ft_src);
	free(--ft_dst);
	VTS;
}

static void	test_02_memcpy_AlignedSizeLessThanWord(void)
{
	size_t	buf_size = 5;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_03_memcpy_MisalignedSizeLessThanWord(void)
{
	size_t	buf_size = 6;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

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

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(--off_src);
	free(--off_dst);
	free(--ft_src);
	free(--ft_dst);
	VTS;
}

static void	test_04_memcpy_AlignedSizeGreaterThanWord(void)
{
	size_t	buf_size = 13;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_05_memcpy_MisalignedSizeGreaterThanWord(void)
{
	size_t	buf_size = 14;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

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

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(--off_src);
	free(--off_dst);
	free(--ft_src);
	free(--ft_dst);
	VTS;
}

static void	test_06_memcpy_AlignedSizeEqualToWord(void)
{
	size_t	buf_size = 8;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_07_memcpy_MisalignedSizeEqualToWord(void)
{
	size_t	buf_size = 8;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

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

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(--off_src);
	free(--off_dst);
	free(--ft_src);
	free(--ft_dst);
	VTS;
}

static void	test_08_memcpy_AlignedBigSize(void)
{
	size_t	buf_size = BIG_CHUNKS;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

	// setup
	memset(off_src, '*', buf_size);
	memset(ft_src, '*', buf_size);
	memset(off_dst, '#', buf_size);
	memset(ft_dst, '#', buf_size);

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(off_src);
	free(off_dst);
	free(ft_src);
	free(ft_dst);
	VTS;
}

static void	test_09_memcpy_MisalignedBigSize(void)
{
	size_t	buf_size = 8;
	char	*off_src = malloc(buf_size);
	char	*off_dst = malloc(buf_size);
	char	*ft_src = malloc(buf_size);
	char	*ft_dst = malloc(buf_size);
	void	*res;

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

	memcpy(off_dst, off_src, buf_size);
	res = ft_memcpy(ft_dst, ft_src, buf_size);

	v_assert_ptr(res, ==, ft_dst);
	v_assert(memcmp(off_src, ft_src, buf_size) == 0);
	v_assert(memcmp(off_dst, ft_dst, buf_size) == 0);

	free(--off_src);
	free(--off_dst);
	free(--ft_src);
	free(--ft_dst);
	VTS;
}

void		suite_memcpy(void)
{
	test_00_memcpy_AlignedSizeOfZero();
	test_01_memcpy_MisalignedSizeOfZero();
	test_02_memcpy_AlignedSizeLessThanWord();
	test_03_memcpy_MisalignedSizeLessThanWord();
	test_04_memcpy_AlignedSizeGreaterThanWord();
	test_05_memcpy_MisalignedSizeGreaterThanWord();
	test_06_memcpy_AlignedSizeEqualToWord();
	test_07_memcpy_MisalignedSizeEqualToWord();
	test_08_memcpy_AlignedBigSize();
	test_09_memcpy_MisalignedBigSize();

	VSS;
}

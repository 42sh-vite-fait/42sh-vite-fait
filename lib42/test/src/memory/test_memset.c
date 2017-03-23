#include "header.h"

static void	test_00_memset_AlignedLessThanWordSize(void)
{
	size_t	size = 16;
	int		s = 'a';
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);

	// call
	memset(off, s, 5);
	ft_memset(ft, s, 5);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_01_memset_UnalignedLessThanWordSize(void)
{
	size_t	size = 16;
	int		s = 'b';
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);
	off[0] = 'x';
	ft[0] = 'x';

	// call
	memset(off + 1, s, 5);
	ft_memset(ft + 1, s, 5);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_02_memset_AlignedOneWordSize(void)
{
	size_t	size = 16;
	size_t	set_size = 8;
	int		s = 'c';
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);

	// call
	memset(off, s, set_size);
	ft_memset(ft, s, set_size);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_03_memset_UnalignedOneWordSize(void)
{
	size_t	size = 16;
	size_t	set_size = 8;
	int		s = 'd';
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);

	// call
	memset(off + 1, s, set_size);
	ft_memset(ft + 1, s, set_size);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_04_memset_AlignedMultiplesWordSize(void)
{
	size_t	size = 256;
	size_t	set_size = 128;
	int		s = 'e';
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);

	// call
	memset(off, s, set_size);
	ft_memset(ft, s, set_size);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_05_memset_UnalignedMultiplesWordSize(void)
{
	size_t	size = 256;
	size_t	set_size = 128;
	int		s = 'f';
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);

	// call
	memset(off + 1, s, set_size);
	ft_memset(ft + 1, s, set_size);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_06_memset_AlignedBigChunks(void)
{
	size_t	size = BIG_CHUNKS;
	size_t	set_size = BIG_CHUNKS;
	int		s = 'g';
	char	*off;
	char	*ft;

	// setup
	off = calloc(size, 1);
	ft = calloc(size, 1);

	// call
	memset(off, s, set_size);
	ft_memset(ft, s, set_size);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_07_memset_UnalignedBigChunks(void)
{
	size_t	size = BIG_CHUNKS;
	size_t	set_size = BIG_CHUNKS;
	int		s = 'g';
	char	*off;
	char	*ft;

	// setup
	off = calloc(size, 1);
	ft = calloc(size, 1);

	// call
	memset(off + 1, s, set_size - 1);
	ft_memset(ft + 1, s, set_size - 1);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

static void	test_08_memset_BigInt(void)
{
	size_t	size = 16;
	int		s = -1;
	char	*off = malloc(size);
	char	*ft = malloc(size);

	// setup
	memset(off, '*', size);
	memset(ft, '*', size);

	// call
	memset(off, s, 5);
	ft_memset(ft, s, 5);

	// test
	int	res = memcmp(off, ft, size);
	v_assert_int(0, ==, res);

	free(off);
	free(ft);
	VTS;
}

void		suite_memset(void)
{
	test_00_memset_AlignedLessThanWordSize();
	test_01_memset_UnalignedLessThanWordSize();
	test_02_memset_AlignedOneWordSize();
	test_03_memset_UnalignedOneWordSize();
	test_04_memset_AlignedMultiplesWordSize();
	test_05_memset_UnalignedMultiplesWordSize();
	test_06_memset_AlignedBigChunks();
	test_07_memset_UnalignedBigChunks();
	test_08_memset_BigInt();

	VSS;
}

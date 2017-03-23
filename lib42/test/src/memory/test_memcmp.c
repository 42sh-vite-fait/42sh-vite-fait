#include "header.h"

static char	*s = "Hello World!";

static void	test_00_memcmp_AlignedZeroLen(void)
{
	char	*s1 = s;
	char	*s2 = s;
	size_t	n = 0;
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1, s2, n);
	ft_res = ft_memcmp(s1, s2, n);

	v_assert_int(off_res, ==, ft_res);

	VTS;
}

static void	test_01_memcmp_MisalignedZeroLen(void)
{
	char	*s1 = s;
	char	*s2 = s;
	size_t	n = 0;
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1 + 1, s2 + 2, n);
	ft_res = ft_memcmp(s1 + 1, s2 + 2, n);

	v_assert_int(off_res, ==, ft_res);

	VTS;
}

static void	test_02_memcmp_AlignedLenOne(void)
{
	char	*s1 = s;
	char	*s2 = s;
	size_t	n = 1;
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1, s2, n);
	ft_res = ft_memcmp(s1, s2, n);

	v_assert_int(off_res, ==, ft_res);

	VTS;
}

static void	test_03_memcmp_MisalignedLenOne(void)
{
	char	*s1 = s;
	char	*s2 = s;
	size_t	n = 1;
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1 + 1, s2 + 2, n);
	ft_res = ft_memcmp(s1 + 1, s2 + 2, n);

	v_assert_int(off_res, ==, ft_res);

	VTS;
}

static void	test_04_memcmp_AlignedFullLen(void)
{
	char	*s1 = s;
	char	*s2 = s;
	size_t	n = strlen(s);
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1, s2, n);
	ft_res = ft_memcmp(s1, s2, n);

	v_assert_int(off_res, ==, ft_res);

	VTS;
}

static void	test_05_memcmp_MisalignedFullLen(void)
{
	char	*s1 = s;
	char	*s2 = s;
	size_t	n = strlen(s) - 2;
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1 + 1, s2 + 1, n);
	ft_res = ft_memcmp(s1 + 1, s2 + 1, n);

	v_assert_int(off_res, ==, ft_res);

	VTS;
}

static void	test_06_memcmp_AlignedNonMatch(void)
{
	char	*s1 = s;
	char	*s2 = "Hello world!";
	size_t	n = strlen(s);
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1, s2, n);
	ft_res = ft_memcmp(s1, s2, n);

/* #if defined(__APPLE__) */
	/* v_assert_int(off_res, ==, ft_res); */
/* #else */
	v_assert_int(0, !=, off_res);
	v_assert_int(0, !=, ft_res);
/* #endif */

	VTS;
}

static void	test_07_memcmp_MisalignedNonMatch(void)
{
	char	*s1 = s;
	char	*s2 = "Hello world!";
	size_t	n = strlen(s) - 2;
	int		off_res;
	int		ft_res;

	off_res = memcmp(s1 + 1, s2 + 2, n);
	ft_res = ft_memcmp(s1 + 1, s2 + 2, n);

/* #if defined(__APPLE__) */
/* 	v_assert_int(off_res, ==, ft_res); */
/* #else */
	v_assert_int(0, !=, off_res);
	v_assert_int(0, !=, ft_res);
/* #endif */

	VTS;
}

static void	test_08_memcmp_AlignedLongStringMatch(void)
{
	size_t	size = 4096;
	char	*s1 = malloc(size);
	char	*s2 = malloc(size);
	int		off_res;
	int		ft_res;

	// setup
	memset(s1, '*', size);
	memset(s2, '*', size);

	// test
	off_res = memcmp(s1, s2, size);
	ft_res = ft_memcmp(s1, s2, size);

	v_assert_int(off_res, ==, ft_res);

	free(s1);
	free(s2);
	VTS;
}

static void	test_09_memcmp_MisalignedLongStringMatch(void)
{
	size_t	size = 4096;
	char	*s1 = malloc(size);
	char	*s2 = malloc(size);
	int		off_res;
	int		ft_res;

	// setup
	memset(s1, '*', size);
	memset(s2, '*', size);

	// test
	off_res = memcmp(s1 + 1, s2 + 2, size - 2);
	ft_res = ft_memcmp(s1 + 1, s2 + 2, size - 2);

	v_assert_int(off_res, ==, ft_res);

	free(s1);
	free(s2);
	VTS;
}

static void	test_10_memcmp_AlignedLongStringMatch(void)
{
	size_t	size = 4096;
	char	*s1 = malloc(size);
	char	*s2 = malloc(size);
	int		off_res;
	int		ft_res;

	// setup
	memset(s1, '*', size);
	memset(s2, '*', size);
	s1[3888] = '$';

	// test
	off_res = memcmp(s1, s2, size);
	ft_res = ft_memcmp(s1, s2, size);

/* #if defined(__APPLE__) */
/* 	v_assert_int(off_res, ==, ft_res); */
/* #else */
	v_assert_int(0, !=, off_res);
	v_assert_int(0, !=, ft_res);
/* #endif */

	free(s1);
	free(s2);
	VTS;
}

static void	test_11_memcmp_MisalignedLongStringMatch(void)
{
	size_t	size = 4096;
	char	*s1 = malloc(size);
	char	*s2 = malloc(size);
	int		off_res;
	int		ft_res;

	// setup
	memset(s1, '*', size);
	memset(s2, '*', size);
	s1[3888] = '$';

	// test
	off_res = memcmp(s1 + 1, s2 + 2, size - 2);
	ft_res = ft_memcmp(s1 + 1, s2 + 2, size - 2);

/* #if defined(__APPLE__) */
/* 	v_assert_int(off_res, ==, ft_res); */
/* #else */
	v_assert_int(0, !=, off_res);
	v_assert_int(0, !=, ft_res);
/* #endif */

	free(s1);
	free(s2);
	VTS;
}

void		suite_memcmp(void)
{
	test_00_memcmp_AlignedZeroLen();
	test_01_memcmp_MisalignedZeroLen();
	test_02_memcmp_AlignedLenOne();
	test_03_memcmp_MisalignedLenOne();
	test_04_memcmp_AlignedFullLen();
	test_05_memcmp_MisalignedFullLen();
	test_06_memcmp_AlignedNonMatch();
	test_07_memcmp_MisalignedNonMatch();
	test_08_memcmp_AlignedLongStringMatch();
	test_09_memcmp_MisalignedLongStringMatch();
	test_10_memcmp_AlignedLongStringMatch();
	test_11_memcmp_MisalignedLongStringMatch();

	VSS;
}

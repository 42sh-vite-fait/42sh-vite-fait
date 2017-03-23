#include "header.h"

static char	c = 60; // '<'

// HAS_ZERO
static void	test_00_memchr_MacroHAS_ZERO_ValidZeroInFirstPlace(void)
{
	unsigned long	n;
	unsigned long	res;

	n = 0x00020304a0b0c0d0UL;
	res = HAS_ZERO(n);
	v_assert(res > 0);

	VTS;
}

static void	test_01_memchr_MacroHAS_ZERO_ValidZeroInMiddlePlace(void)
{
	unsigned long	n;
	unsigned long	res;

	n = 0x01020300a0b0c0d0UL;
	res = HAS_ZERO(n);
	v_assert(res > 0);

	VTS;
}

static void	test_02_memchr_MacroHAS_ZERO_ValidZeroInLastPlace(void)
{
	unsigned long	n;
	unsigned long	res;

	n = 0x01020304a0b0c000UL;
	res = HAS_ZERO(n);
	v_assert(res > 0);

	VTS;
}

static void	test_03_memchr_MacroHAS_ZERO_InvalidNoZero(void)
{
	unsigned long	n;
	unsigned long	res;

	n = 0x01020304a0b0c0d0UL;
	res = HAS_ZERO(n);
	v_assert(res == 0);

	VTS;
}

// HAS_BYTE
static void	test_00_memchr_MacroHAS_BYTE_ValidCharInFirstPlace(void)
{
	unsigned long	n;
	unsigned long	res;
	unsigned long	cccc;

	n = 0x01020304a0b0c0d0UL;
	cccc = 0x0101010101010101UL;
	res = HAS_BYTE(n, cccc);
	v_assert(res > 0);

	VTS;
}

static void	test_01_memchr_MacroHAS_BYTE_ValidCharInMiddlePlace(void)
{
	unsigned long	n;
	unsigned long	res;
	unsigned long	cccc;

	n = 0x01020304a0b0c0d0UL;
	cccc = 0x0404040404040404UL;
	res = HAS_BYTE(n, cccc);
	v_assert(res > 0);

	VTS;
}

static void	test_02_memchr_MacroHAS_BYTE_ValidCharInLastPlace(void)
{
	unsigned long	n;
	unsigned long	res;
	unsigned long	cccc;

	n = 0x01020304a0b0c0d0UL;
	cccc = 0xd0d0d0d0d0d0d0d0UL;
	res = HAS_BYTE(n, cccc);
	v_assert(res > 0);

	VTS;
}

static void	test_03_memchr_MacroHAS_BYTE_InvalidNoChar(void)
{
	unsigned long	n;
	unsigned long	res;
	unsigned long	cccc;

	n = 0x01020304a0b0c0d0UL;
	cccc = 0xb1b1b1b1b1b1b1b1UL;
	res = HAS_BYTE(n, cccc);
	v_assert(res == 0);

	VTS;
}

// ft_memchr
static void	test_00_memchr_AlignedCharPastSize(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(30);

	memset(p, 0, 30);
	p[20] = c;

	off = memchr(p, c, 20);
	ft = ft_memchr(p, c, 20);

	v_assert_ptr(NULL, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_01_memchr_MisalignedCharPastSize(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(30);

	memset(p, 0, 30);
	p[20] = c;

	off = memchr(p + 2, c, 18);
	ft = ft_memchr(p + 2, c, 18);

	v_assert_ptr(NULL, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_02_memchr_AlignedFindChar(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(30);

	memset(p, 0, 30);
	p[20] = c;

	off = memchr(p, c, 21);
	ft = ft_memchr(p, c, 21);

	v_assert_ptr(NULL, !=, off);
	v_assert_ptr(p + 20, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_03_memchr_MisalignedFindChar(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(30);
	size_t	location = 18;

	memset(p, 0, 30);
	p[location] = c;

	off = memchr(p + 2, c, location);
	ft = ft_memchr(p + 2, c, location);

	v_assert_ptr(NULL, !=, off);
	v_assert_ptr(p + location, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_04_memchr_AlignedNullInString(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(30);
	char	*s = "Hello World!";
	size_t	len = strlen(s);

	memset(p, 0, 30);
	memcpy(p, s, len);

	off = memchr(p, '\0', ~0UL);
	ft = ft_memchr(p, '\0', ~0UL);

	v_assert_ptr(NULL, !=, off);
	v_assert_ptr(p + len, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_05_memchr_MisalignedNullInString(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(30);
	char	*s = "Hello World!";
	size_t	len = strlen(s);

	memset(p, 0, 30);
	memcpy(p, s, len);

	off = memchr(p + 2, '\0', ~0UL);
	ft = ft_memchr(p + 2, '\0', ~0UL);

	v_assert_ptr(NULL, !=, off);
	v_assert_ptr(p + len, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_06_memchr_AlignedBigChunk(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(BIG_CHUNKS);

	memset(p, 0, BIG_CHUNKS);
	p[BIG_CHUNKS - 1] = '*';

	off = memchr(p, '*', BIG_CHUNKS);
	ft = ft_memchr(p, '*', BIG_CHUNKS);

	v_assert_ptr(NULL, !=, off);
	v_assert_ptr(p + BIG_CHUNKS - 1, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

static void	test_07_memchr_MisalignedBigChunk(void)
{
	void	*off;
	void	*ft;
	char	*p = malloc(BIG_CHUNKS);

	memset(p, 0, BIG_CHUNKS);
	p[BIG_CHUNKS - 1] = '*';

	off = memchr(p + 2, '*', BIG_CHUNKS);
	ft = ft_memchr(p + 2, '*', BIG_CHUNKS);

	v_assert_ptr(NULL, !=, off);
	v_assert_ptr(p + BIG_CHUNKS - 1, ==, off);
	v_assert_ptr(off, ==, ft);

	free(p);
	VTS;
}

void		suite_memchr(void)
{
	test_00_memchr_MacroHAS_ZERO_ValidZeroInFirstPlace();
	test_01_memchr_MacroHAS_ZERO_ValidZeroInMiddlePlace();
	test_02_memchr_MacroHAS_ZERO_ValidZeroInLastPlace();
	test_03_memchr_MacroHAS_ZERO_InvalidNoZero();

	test_00_memchr_MacroHAS_BYTE_ValidCharInFirstPlace();
	test_01_memchr_MacroHAS_BYTE_ValidCharInMiddlePlace();
	test_02_memchr_MacroHAS_BYTE_ValidCharInLastPlace();
	test_03_memchr_MacroHAS_BYTE_InvalidNoChar();

	test_00_memchr_AlignedCharPastSize();
	test_01_memchr_MisalignedCharPastSize();
	test_02_memchr_AlignedFindChar();
	test_03_memchr_MisalignedFindChar();
	test_04_memchr_AlignedNullInString();
	test_05_memchr_MisalignedNullInString();
	test_06_memchr_AlignedBigChunk();
	test_07_memchr_MisalignedBigChunk();

	VSS;
}

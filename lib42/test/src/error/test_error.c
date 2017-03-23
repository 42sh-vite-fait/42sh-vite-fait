#include "header.h"

enum e_errnum {
	ERROR_0,
	ERROR_1,
	ERROR_2,
	ERROR_3,
};

char	*errlist[] = {
	[ERROR_0] = "err num 0",
	[ERROR_1] = "err num 1",
	[ERROR_2] = "err num 2",
	[ERROR_3] = "err num 3",
};

static void	setup_error(const char *name)
{
	register_errlist((char*)name, errlist, ARR_SIZ_MAX(errlist));
}

static void teardown_error(void)
{
	register_errlist(NULL, NULL, 0);
}

static void	test_00_ft_strerror_IndexInRange(void)
{
	char	*ret;

	setup_error(__func__);

	for (size_t i = 0; i < ARR_SIZ_MAX(errlist) - 1; ++i)
	{
		ret = ft_strerror(i);
		v_assert_str(errlist[i], ret);
	}

	teardown_error();

	VTS;
}

static void	test_01_ft_strerror_IndexOutOfRange(void)
{
	char	*ret;

	setup_error(__func__);

	ret = ft_strerror(ARR_SIZ_MAX(errlist));
	v_assert_str(UNKNOWN_ERROR, ret);

	teardown_error();

	VTS;
}

void	suite_error(void)
{
	test_00_ft_strerror_IndexInRange();
	test_01_ft_strerror_IndexOutOfRange();

	VSS;
}

#include "header.h"

#define ASSERT_OPT_STRUCT(o, a, c, e, u, p)\
	do{\
		v_assert_ptr(a, ==, o.arg);\
		v_assert_size_t(c, ==, o.current);\
		v_assert_size_t(e, ==, o.end);\
		v_assert_int(u, ==, o.unknown_opt);\
		v_assert(p == o.print_errmsg);\
	} while(0);\

static void	test_00_getopt_OPT_INIT(void)
{
	t_opt	o;

	memset(&o, '*', sizeof(t_opt));
	OPT_INIT(o);
	ASSERT_OPT_STRUCT(o, NULL, 1, 1, -1, false);

	VTS;
}

static void	test_01_getopt_no_opts(void)
{
	const char	*const av[] = {
		"cmd",
		"arg1",
		NULL,
	};
	t_opt	opt;

	OPT_INIT(opt);
	int ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 1, 1, -1, false);
	v_assert_str("arg1", av[opt.end]);

	VTS;
}

static void	test_02_getopt_no_opts_no_args(void)
{
	const char	*const av[] = {
		"cmd",
		NULL,
	};
	t_opt	opt;

	OPT_INIT(opt);
	int ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 1, 1, -1, false);
	v_assert_ptr(NULL, ==, av[opt.end]);

	VTS;
}

static void	test_03_getopt_basic_opt(void)
{
	const char	*const av[] = {
		"cmd",
		"-a",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('a', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 2, 2, -1, false);
	v_assert_ptr(NULL, ==, av[opt.end]);

	VTS;
}

static void	test_04_getopt_multiple_basic_opts(void)
{
	const char	*const av[] = {
		"cmd",
		"-b",
		"-c",
		"-a",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('b', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('c', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('a', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 4, 4, -1, false);
	v_assert_ptr(NULL, ==, av[opt.end]);

	VTS;
}

static void	test_05_getopt_unknown_opt(void)
{
	const char	*const av[] = {
		"cmd",
		"-b",
		"-c",
		"-f",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('b', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('c', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('?', ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 4, 1, 'f', false);

	VTS;
}

static void	test_06_getopt_unknown_opt_and_valid_one(void)
{
	const char	*const av[] = {
		"cmd",
		"-f",
		"-c",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('?', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 1, 'f', false);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('c', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 3, 3, -1, false);

	VTS;
}

static void	test_07_getopt_opt_with_arg(void)
{
	const char	*fmt = "a:bc";
	const char	*const av[] = {
		"cmd",
		"-a",
		"value1",
		"-a",
		"value2",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);
	v_assert_str("value1", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[2], 3, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);
	v_assert_str("value2", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[4], 5, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 5, 5, -1, false);

	VTS;
}

static void	test_08_getopt_multiple_opts_with_args(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-c",
		"value1",
		"-b",
		"value2",
		"-a",
		"arg1",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('c', ==, ret);
	v_assert_str("value1", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[2], 3, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('b', ==, ret);
	v_assert_str("value2", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[4], 5, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 6, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);

	v_assert_str("arg1", av[opt.end]);
	ASSERT_OPT_STRUCT(opt, NULL, 6, 6, -1, false);

	VTS;
}

static void	test_09_getopt_identical_opt_and_arg(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-c",
		"-a",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('c', ==, ret);
	v_assert_str("-a", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[2], 3, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);

	ASSERT_OPT_STRUCT(opt, NULL, 3, 3, -1, false);

	VTS;
}

static void	test_10_getopt_unknown_first(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-z",
		"-a",
		"-b",
		"value1",
		"arg1",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('?', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 1, 'z', false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 3, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('b', ==, ret);
	v_assert_str("value1", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[4], 5, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("arg1", av[opt.end]);
	ASSERT_OPT_STRUCT(opt, NULL, 5, 5, -1, false);

	VTS;
}

static void	test_11_getopt_unknown_first_with_arg(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-z",
		"arg1",
		"-b",
		"value1",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('?', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 1, 'z', false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("arg1", av[opt.end]);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 2, -1, false);

	VTS;
}

static void	test_12_getopt_arg_missing(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-b",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(':', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_ptr(NULL, ==, av[opt.end]);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 2, -1, false);

	VTS;
}

static void	test_13_getopt_arg_missing_with_ddash(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-b",
		"--",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(':', ==, ret);
	ASSERT_OPT_STRUCT(opt, av[2], 2, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("--", av[opt.end - 1]);
	ASSERT_OPT_STRUCT(opt, NULL, 3, 3, -1, false);

	VTS;
}

static void	test_14_getopt_double_dash(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-c",
		"value1",
		"--",
		"arg1",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('c', ==, ret);
	v_assert_str("value1", opt.arg);
	ASSERT_OPT_STRUCT(opt, av[2], 3, 1, -1, false);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("--", av[opt.end - 1]);
	ASSERT_OPT_STRUCT(opt, NULL, 4, 4, -1, false);

	VTS;
}

static void	test_15_getopt_print_errmsg_unknown_opt(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-z",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);
	opt.print_errmsg = true;

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('?', ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 1, 'z', true);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 2, 2, -1, true);

	VTS;
}

static void	test_16_getopt_print_errmsg_missing_arg(void)
{
	const char	*fmt = "ab:c:";
	const char	*const av[] = {
		"cmd",
		"-b",
		"--",
		"value1",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);
	opt.print_errmsg = true;

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(':', ==, ret);
	ASSERT_OPT_STRUCT(opt, av[2], 2, 1, -1, true);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	ASSERT_OPT_STRUCT(opt, NULL, 3, 3, -1, true);

	VTS;
}

void suite_getopt(void)
{
	test_00_getopt_OPT_INIT();
	test_01_getopt_no_opts();
	test_02_getopt_no_opts_no_args();
	test_03_getopt_basic_opt();
	test_04_getopt_multiple_basic_opts();
	test_05_getopt_unknown_opt();
	test_06_getopt_unknown_opt_and_valid_one();
	test_07_getopt_opt_with_arg();
	test_08_getopt_multiple_opts_with_args();
	test_09_getopt_identical_opt_and_arg();
	test_10_getopt_unknown_first();
	test_11_getopt_unknown_first_with_arg();
	test_12_getopt_arg_missing();
	test_13_getopt_arg_missing_with_ddash();
	test_14_getopt_double_dash();
	test_15_getopt_print_errmsg_unknown_opt();
	test_16_getopt_print_errmsg_missing_arg();

	VSS;
}

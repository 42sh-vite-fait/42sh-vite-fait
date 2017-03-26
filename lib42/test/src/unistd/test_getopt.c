#include "header.h"

#define ASSERT_OPT_STRUCT(o, a, ca, co, e, u, p)\
	do{\
		v_assert_ptr(a, ==, o.arg);\
		v_assert_size_t(ca, ==, o.current_arg);\
		v_assert_size_t(co, ==, o.current_opt);\
		v_assert_size_t(e, ==, o.end);\
		v_assert_int(u, ==, o.unknown_opt);\
		v_assert(p == o.print_errmsg);\
	} while(0);\

static void	test_00_getopt_OPT_INIT(void)
{
	t_opt	o;

	memset(&o, '*', sizeof(t_opt));
	OPT_INIT(o);
	ASSERT_OPT_STRUCT(o, NULL, 1, 1, 1, -1, false);

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

	/* ASSERT_OPT_STRUCT(opt, NULL, 1, 1, 1, -1, false); */
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

	/* ASSERT_OPT_STRUCT(opt, NULL, 1, 1, 1, -1, false); */
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

	/* ASSERT_OPT_STRUCT(opt, NULL, 4, 4, -1, false); */
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
	v_assert_int('f', ==, opt.unknown_opt);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);
	v_assert_ptr(NULL, ==, av[opt.end]);

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
	v_assert_int('f', ==, opt.unknown_opt);
	/* ASSERT_OPT_STRUCT(opt, NULL, 2, 1, 'f', false); */

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int('c', ==, ret);

	ret = ft_getopt(av, "abc", &opt);
	v_assert_int(-1, ==, ret);

	/* ASSERT_OPT_STRUCT(opt, NULL, 3, 3, -1, false); */
	v_assert_ptr(NULL, ==, av[opt.end]);

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
	v_assert_ptr(av[2], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);
	v_assert_str("value2", opt.arg);
	v_assert_ptr(av[4], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_ptr(NULL, ==, av[opt.end]);

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
	v_assert_ptr(av[2], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('b', ==, ret);
	v_assert_str("value2", opt.arg);
	v_assert_ptr(av[4], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("arg1", av[opt.end]);
	v_assert_ptr(av[6], ==, av[opt.end]);

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
	v_assert_int(':', ==, ret);

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
	v_assert_int('z', ==, opt.unknown_opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('b', ==, ret);
	v_assert_str("value1", opt.arg);
	v_assert_ptr(av[4], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("arg1", av[opt.end]);

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
	v_assert_int('z', ==, opt.unknown_opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("arg1", av[opt.end]);

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
	v_assert_ptr(av[2], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("arg1", av[opt.end]);

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
	v_assert_int('z', ==, opt.unknown_opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_ptr(NULL, ==, av[opt.end]);

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

	VTS;
}

static void	test_17_getopt_arg_is_dash(void)
{
	const char	*fmt = "fo:";
	const char	*const av[] = {
		"cmd",
		"-o",
		"-",
		"-f",
		"file",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('o', ==, ret);
	v_assert_str("-", opt.arg);
	v_assert_ptr(av[2], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('f', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("file", av[opt.end]);
	v_assert_ptr(av[4], ==, av[opt.end]);

	VTS;
}

static void	test_18_getopt_invalid_order(void)
{
	const char	*fmt = "a:b";
	const char	*const av[] = {
		"cmd",
		"-ab",
		"opt_arg",
		"cmd_arg",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);
	opt.print_errmsg = true;

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(':', ==, ret);

	VTS;
}

static void	test_19_getopt_multiple_opts(void)
{
	const char	*fmt = "f:edcba";
	const char	*const av[] = {
		"cmd",
		"-abcdef",
		"opt_arg",
		"cmd_arg",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('a', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('b', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('c', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('d', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('e', ==, ret);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int('f', ==, ret);
	v_assert_str("opt_arg", opt.arg);
	v_assert_ptr(av[2], ==, opt.arg);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("cmd_arg", av[opt.end]);

	VTS;
}

static void	test_20_getopt_only_dash(void)
{
	const char	*fmt = "f:edcba";
	const char	*const av[] = {
		"cmd",
		"-",
		"cmd_arg",
		NULL,
	};
	t_opt	opt;
	int		ret;

	OPT_INIT(opt);

	ret = ft_getopt(av, fmt, &opt);
	v_assert_int(-1, ==, ret);
	v_assert_str("-", av[opt.end]);
	v_assert_str("cmd_arg", av[opt.end + 1]);

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
	test_17_getopt_arg_is_dash();
	test_18_getopt_invalid_order();
	test_19_getopt_multiple_opts();
	test_20_getopt_only_dash();

	VSS;
}

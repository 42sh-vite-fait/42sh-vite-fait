#include <assert.h>
#include "builtins.h"
#include "exec.h"
#include "var.h"
#include "misc.h"
#include "str_42.h"
#include "ft_printf.h"
#include "sig.h"
#include "exit_status.h"

static const char	*g_backup_paths_value;
static const char	*g_usage = "env: illegal option -- %c\n"
"usage: env [-i] [name=value]... [utility [argument...]]\n";

static int	env_add_args(char *const *argv, int optind)
{
	char	*name;
	char	*value;
	ssize_t	offset;

	while (argv[optind])
	{
		offset = ft_strchrpos(argv[optind], '=');
		if (offset == -1)
			break ;
		argv[optind][offset] = '\0';
		name = argv[optind];
		value = argv[optind] + offset + 1;
		if (name[0] && is_valid_name(name, offset))
			var_set(name, value, VAR_ATTR_EXPORT);
		else
		{
			error_set_context("%s: not a valid identifier", name);
			return (-1);
		}
		optind += 1;
	}
	return (optind);
}

static void	env_clean_environ(void)
{
	int	ret;

	ret = var_get("PATH", &g_backup_paths_value);
	if (ret == ERR_VAR_NOT_FOUND)
		g_backup_paths_value = "";
	var_clear();
}

static int	env_parse_args(int argc, const char *const *argv)
{
	t_opt	opt;
	int		c;
	int		pos;

	OPT_INIT(opt);
	while ((c = ft_getopt(argc, argv, "i", &opt)) != -1)
	{
		if (c == 'i')
			env_clean_environ();
		else
		{
			ft_dprintf(2, g_usage, opt.optopt);
			_exit(1);
		}
	}
	pos = env_add_args((char *const *)argv, opt.optind);
	if (pos == -1)
		error_print("env");
	return (pos);
}

static void	env_exec_utility(int argc, const char *const *argv, int pos)
{
	const char	*paths;
	char *const	*envp;

	envp = var_get_environ();
	if (pos == argc)
	{
		while (*envp)
		{
			ft_printf("%s\n", *envp);
			envp += 1;
		}
		_exit(0);
	}
	else
	{
		if (var_get("PATH", &paths) != NO_ERROR)
			paths = g_backup_paths_value;
		exec_with_path(paths, (char *const *)argv + pos, envp);
		_exit(-1);
	}
}

int			builtin_env(int argc, const char *const *argv)
{
	pid_t	child;
	int		status;
	int		pos;

	if (exec_fork(&child) != NO_ERROR)
	{
		error_print("env");
		return (-1);
	}
	if (child == 0)
	{
		pos = env_parse_args(argc, argv);
		if (pos != -1)
			env_exec_utility(argc, argv, pos);
		_exit(1);
	}
	else
	{
		signal_set_ignored_signals_to_ignore();
		status = wait_child_process_group(child, child);
		exit_status_set_last(status);
	}
	return (status);
}
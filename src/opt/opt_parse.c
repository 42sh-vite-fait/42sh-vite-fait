#include "unistd_42.h"
#include "opt.h"
#include "shell.h"

unsigned			g_opt_shell;
static const char	*g_opt_command_line;

static void	usage(void)
{
	const char	*usage =
		"usage:  %s [option] [cstring]\n"
		"        %s -d {ast,lexer,input}\n";

	ft_dprintf(2, usage, BIN_NAME, BIN_NAME);
	exit(1);
}

static unsigned	get_debug_option(const char *optarg)
{
	unsigned	options;

	options = OPT_NO_OPT;
	if (!ft_strcmp(optarg, "ast"))
		options = OPT_DEBUG_AST;
	else if (!ft_strcmp(optarg, "lexer"))
		options = OPT_DEBUG_LEXER;
	else if (!ft_strcmp(optarg, "input"))
		options = OPT_DEBUG_INPUT;
	else if (!ft_strcmp(optarg, "exec"))
		options = OPT_DEBUG_EXEC;
	else
		usage();
	return (options);
}

const char	*opt_get_command_line(void)
{
	return (g_opt_command_line);
}

void		opt_parse(int argc, char *argv[])
{
	t_opt	opt;
	int 	ch;

	OPT_INIT(opt);
	while ((ch = ft_getopt(argc, argv, "c:d:i", &opt)) != -1)
	{
		if (ch == 'd')
			g_opt_shell |= get_debug_option(opt.optarg);
		else if (ch == 'c')
		{
			g_opt_command_line = opt.optarg;
			g_opt_shell |= (OPT_CMD_STRING);
		}
		else if (ch == 'i')
			g_opt_shell |= OPT_INTERACTIVE;
		else
			usage();
	}
	if (!opt_is_set(OPT_CMD_STRING) && isatty(STDIN_FILENO))
		g_opt_shell |= OPT_INTERACTIVE;
}

#include "input.h"
#include "user_interface.h"
#include "lexer.h"
#include "parser.h"
#include "ft_printf.h"
#include "unistd_42.h"
#include "array_42.h"
#include <history.h>

#define SHELL_PROMPT 		"42sh> "
#define DEBUG_PRINT_AST		(1U << 1)
#define DEBUG_PRINT_LEXER	(1U << 2)
#define DEBUG_PRINT_INPUT	(1U << 3)

static unsigned		g_debug_opt;
static const char	*g_command_line;

static void	usage(const char *name)
{
	ft_dprintf(2, "usage:  %s [option] [cstring]\n"
				  "        %s -d {ast,lexer,input}\n", name, name);
	exit(1);
}

static void	shell_debug_parse_options(int argc, char *argv[])
{
	t_opt	opt;
	int ch;

	OPT_INIT(opt);
	while ((ch = ft_getopt(argc, argv, "c:d:", &opt)) != -1)
	{
		switch (ch) {
			case 'd':
				if (!ft_strcmp(opt.optarg, "ast"))
					g_debug_opt |= DEBUG_PRINT_AST;
				else if (!ft_strcmp(opt.optarg, "lexer"))
					g_debug_opt |= DEBUG_PRINT_LEXER;
				else if (!ft_strcmp(opt.optarg, "input"))
					g_debug_opt |= DEBUG_PRINT_INPUT;
				else
					usage(argv[0]);
				break;
			case 'c':
				g_command_line = opt.optarg;
				break;
			default:
				usage(argv[0]);
				break;
		}
	}
}

int		main(int argc, char *argv[])
{
	t_lexer		lexer;
	t_array		tokens;
	t_string	input;
	t_parser	parser;
	int			status;

	// should we run in debug mode ?
	if (argc > 1)
		shell_debug_parse_options(argc, argv);

	lexer_init(&lexer);
	array_init(&tokens, sizeof(t_token));
	history_init(4096);
	while (42)
	{
		// Interactive ?
		if (g_command_line == NULL)
		{
			input = input_get_line(SHELL_PROMPT);
			while (remove_trailing_escaped_newline(&input))
				input = input_get_line(SHELL_PROMPT);
			if (input.len > 1)
				history_add(string_create_dup(input.str));
		}
		else
			string_init_dup(&input, g_command_line);

		// lexer
		status = lexer_lex(&lexer, &tokens, input.str);
		while (true)
		{
			if (status == LEXER_ERROR)
				return (ft_printf("LEXING ERROR\n"), 1);
			else if (status == LEXER_INPUT_COMPLETE)
				break ;
			else if (status == LEXER_INPUT_INCOMPLETE)
			{
				t_string tmp = input_get_line("> ");
				if (input.len > 1)
					history_add(string_create_dup(tmp.str));
				status = lexer_lex(&lexer, &tokens, tmp.str);
				string_append(&input, &tmp);
				string_shutdown(&tmp);
			}
		}

		// parser
		parser_init(&parser, &tokens);
		if (parser_parse(&parser) != PARSER_NO_ERROR)
			return error_print("parser"), (1);

		// debug
		if (g_debug_opt & DEBUG_PRINT_INPUT)
			ft_printf("INPUT: %s\n", input.str);
		if (g_debug_opt & DEBUG_PRINT_LEXER)
			lexer_debug_print_tokens(&tokens);
		if (g_debug_opt & DEBUG_PRINT_AST)
			ast_debug_print(&parser.ast);

		// reset struct
		array_clear(&tokens);
		parser_shutdown(&parser);

		// shall we exit ?
		if (ft_strcmp(input.str, "exit") == 0
				|| g_command_line != NULL)
		{
			string_shutdown(&input);
			break ;
		}
	}
	array_shutdown(&tokens);
	lexer_shutdown(&lexer);
}

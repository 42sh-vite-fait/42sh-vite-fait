#include "string_42.h"
#include "array_42.h"
#include "history.h"
#include "parser.h"
#include "shell.h"
#include "opt.h"
#include "input.h"
#include "ft_printf.h"

int shell_loop(void)
{
	t_string	input_;
	t_array		tokens_;
	t_parser	parser_;
	t_lexer		lexer_;
	t_string	*input;
	t_array		*tokens;
	t_parser	*parser;
	t_lexer		*lexer;
	int			ret;
	t_string	line;

	fatal_malloc(string_init(&input_));
	fatal_malloc(array_init(&tokens_, sizeof(t_token)));
	fatal_malloc(parser_init(&parser_));
	fatal_malloc(lexer_init(&lexer_));

	fatal_malloc(string_init(&line));

	input = &input_;
	tokens = &tokens_;
	parser = &parser_;
	lexer = &lexer_;

	int	input_status;
	int	lexer_status;
	const char	*prompt;

	input_status = E_INPUT_OK;
	if (opt_is_set(OPT_INTERACTIVE))
	{
		while (1)
		{
			string_truncate(input, 0);
			string_truncate(&line, 0);
			string_shrink_to_fit(input);
			array_clear(tokens);
			parser_clear(parser);

			// While input is incomplete
			lexer_status = LEXER_INPUT_INCOMPLETE;
			prompt = SHELL_PS1;
			while (1)
			{
				input_status = input_get_line(&line, prompt);
				prompt = SHELL_PS2;
				if (input_status == E_INPUT_ERROR) // Quit on error
					exit(1);
				if (input_status == E_INPUT_EOF) // No more input
				{
					if (!assert_stack_is_empty(lexer)) // Unfinished lexing
						error_print("lexer");
					exit(0);
				}
//				if (line.len == 0) // If the input is empty, loop
//					continue ;
				if (remove_trailing_escaped_newline(&line) != LINE_COMPLETE)
					continue ;
				lexer_status = lexer_lex(lexer, tokens, &line);
				if (lexer_status != LEXER_ERROR)
				{
					string_append(input, &line);
					string_truncate(&line, 0);
					// TODO: cut lines multiple lines before pushing in history
					history_add(fatal_malloc(string_create_dup(input->str)));
				}
				if (lexer_status != LEXER_INPUT_INCOMPLETE)
					break ;
			}
			if (opt_is_set(OPT_DEBUG_INPUT))
				ft_printf("INPUT: [%s]\n", input->str);
			if (lexer_status == LEXER_ERROR)
			{
				error_set_context("lexing error !");
				error_print("lexer");
				continue ;
			}
			else
			{
				categorize_tokens(input, tokens);
				lexer_clear_tokens(tokens);
				if (opt_is_set(OPT_DEBUG_LEXER))
					lexer_debug_print_tokens(input, tokens);
			}
			if (shell_parser(input, parser, tokens) != PARSER_NO_ERROR)
			{
				parser_init_with_tokens(input, parser, tokens);
				ret = parser_parse(parser);
				if (ret != PARSER_NO_ERROR)
				{
					error_print("parser");
					continue ;
				}
				else if (opt_is_set(OPT_DEBUG_AST))
					ast_debug_print(&parser->ast, input->str);
			}
				
		}
		/* if (shell_exec(parser->ast) != EXEC_NO_ERROR) */
		/*	return (EXIT_FAILURE); */
	}



	else if (!opt_is_set(OPT_CMD_STRING))
	{
		while (1)
		{
			string_truncate(input, 0);
			string_truncate(&line, 0);
			string_shrink_to_fit(input);
			array_clear(tokens);
			parser_clear(parser);

			// While input is incomplete
			lexer_status = LEXER_INPUT_INCOMPLETE;
			while (1)
			{
				// TODO: replace with input_notty_get_line
				input_status = input_get_line(&line, "");
				if (input_status == E_INPUT_ERROR) // Quit on error
					exit(1);
				if (input_status == E_INPUT_EOF) // No more input
				{
					if (!assert_stack_is_empty(lexer)) // Unfinished lexing
						error_print("lexer");
					exit(0);
				}
//				if (line.len == 0) // If the input is empty, loop
//					continue ;
				if (remove_trailing_escaped_newline(&line) != LINE_COMPLETE)
					continue ;
				lexer_status = lexer_lex(lexer, tokens, &line);
				if (lexer_status != LEXER_ERROR)
				{
					string_append(input, &line);
					string_truncate(&line, 0);
				}
				if (lexer_status != LEXER_INPUT_INCOMPLETE)
					break ;
			}
			if (opt_is_set(OPT_DEBUG_INPUT))
				ft_printf("INPUT: [%s]\n", input->str);
			if (lexer_status == LEXER_ERROR)
			{
				error_set_context("lexing error !");
				error_print("lexer");
				break ;
			}
			categorize_tokens(input, tokens);
			lexer_clear_tokens(tokens);
			if (opt_is_set(OPT_DEBUG_LEXER))
				lexer_debug_print_tokens(input, tokens);
			// ???
			if (shell_parser(input, parser, tokens) != PARSER_NO_ERROR)
			{
				parser_init_with_tokens(input, parser, tokens);
				ret = parser_parse(parser);
				if (ret != PARSER_NO_ERROR)
				{
					error_print("parser");
					break ;
				}
				else if (opt_is_set(OPT_DEBUG_AST))
					ast_debug_print(&parser->ast, input->str);
			}
		}
		/* if (shell_exec(parser->ast) != EXEC_NO_ERROR) */
		/*	return (EXIT_FAILURE); */
	}


	
	ret = 0;

	string_shutdown(&input_);
	array_shutdown(&tokens_);
	parser_shutdown(&parser_);
	return (ret);
}

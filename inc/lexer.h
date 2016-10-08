#ifndef LEXER_H
# define LEXER_H

# include "array_42.h"
# include "automaton.h"

/*
** The lexer module implements an utility that
** currently splits an input string into labelized
** syntactic atoms called tokens, according to
** the shell lexical rules. It handles tokens split
** into multiple input strings.
*/

# define LEXER_INPUT_COMPLETE 0
# define LEXER_INPUT_INCOMPLETE 1
# define LEXER_ERROR 2

# define LINE_COMPLETE 0
# define LINE_INCOMPLETE 1

typedef struct s_lexer	t_lexer;
typedef struct s_token	t_token;

enum		e_char_type {
	E_SYMBOL_NONE = 0,
	E_SYMBOL_BLANK,
	E_SYMBOL_LETTER,
	E_SYMBOL_SQUOTE,
	E_SYMBOL_DQUOTE,
	E_SYMBOL_PIPE,
	E_SYMBOL_SEMICOLON,
	E_SYMBOL_LESS,
	E_SYMBOL_GREAT,
	E_SYMBOL_AND,
	E_SYMBOL_NEWLINE,
	E_SYMBOL_LPAREN,
	E_SYMBOL_RPAREN,
	E_SYMBOL_DASH,
	E_SYMBOL_DOLLAR,
	E_SYMBOL_BSLASH,
	E_SYMBOL_LBRACE,
	E_SYMBOL_RBRACE,
	E_SYMBOL_BQUOTE,
	E_SYMBOL_HASH,
	E_SYMBOL_MAX_CHAR_TYPE,
	E_MAX_SYMBOL,
};

enum		e_states {
	E_STATE_ERR = ERROR_STATE,
	E_STATE_START = START_STATE,
	E_STATE_BLANK,
	E_STATE_WORD,
	E_STATE_PIPE,
	E_STATE_SEMICOLON,
	E_STATE_LESS,
	E_STATE_DLESS,
	E_STATE_LESSAND,
	E_STATE_GREAT,
	E_STATE_DGREAT,
	E_STATE_GREATAND,
	E_STATE_NEWLINE,
	E_STATE_LESSGREAT,
	E_STATE_DLESSDASH,
	E_STATE_CLOBBER,
	E_STATE_AND,
	E_STATE_AND_IF,
	E_STATE_DSEMI,
	E_STATE_OR_IF,
	E_STATE_LPAREN,
	E_STATE_RPAREN,
	E_STATE_BSLASH,
	E_STATE_DOLLAR,
	E_STATE_COMMENT,
	E_MAX_STATE,
};

enum		e_stack_state {
	E_STACK_EMPTY = EMPTY_STACK,
	E_STACK_SQUOTE,
	E_STACK_DQUOTE,
	E_STACK_BQUOTE,
	E_STACK_PAREN,
	E_STACK_PARAM_EXP,
	E_STACK_CMD_SUBST,
	E_MAX_STACK_STATE,
};

enum		e_token_type
{
	E_TOKEN_WORD,
	E_TOKEN_PIPE,
	E_TOKEN_SEMICOLON,
	E_TOKEN_LESS,
	E_TOKEN_DLESS,
	E_TOKEN_LESSAND,
	E_TOKEN_GREAT,
	E_TOKEN_DGREAT,
	E_TOKEN_GREATAND,
	E_TOKEN_NEWLINE,
	E_TOKEN_LESSGREAT,
	E_TOKEN_DLESSDASH,
	E_TOKEN_CLOBBER,
	E_TOKEN_AND,
	E_TOKEN_AND_IF,
	E_TOKEN_DSEMI,
	E_TOKEN_OR_IF,
	E_TOKEN_LPAREN,
	E_TOKEN_RPAREN,
	E_TOKEN_IO_NUMBER,
	E_TOKEN_COMMENT,
	E_TOKEN_BLANK,
};

struct		s_lexer
{
	t_automaton		tokenizer;
	size_t			input_current_index;
	size_t			token_begin_index;
};

struct		s_token
{
	size_t				start;
	size_t				len;
	enum e_token_type	type;
};

/*
** `lexer_init_automaton` initializes the tokenizer
** automaton with the shell grammar.
*/
t_automaton	*lexer_init_automaton(t_automaton *a);

/*
** `lexer_tokenize` reads a given input, tokenizes it
** according to the lexer's grammar, updates the given
** t_lexer and adds tokens resulting from input splitting
** to the given array of tokens. If a token cannot be
** completed at the end of the input, it is not added
** to the array, LEXER_INPUT_INCOMPLETE is returned,
** and a subsequent call to this function must be done.
** LEXER_INPUT_COMPLETE is returned otherwise.
*/
int			lexer_lex(t_lexer *l, t_array *tokens, const char *input);

/*
** `lexer_init` initializes a given t_lexer ready to
** tokenize input according to the shell grammar.
**
** `lexer_shutdown` releases the resources of a
** t_lexer initialized with `lexer_init`.
*/
t_lexer		*lexer_init(t_lexer *lexer);
void		lexer_shutdown(t_lexer *lexer);

/*
** `lexer_tokenize` generates tokens from input
** according to grammar rules.
** Takes an `input`, modifies the states of a `lexer`,
** push the resulting tokens to a t_array `tokens`.
*/
int			lexer_tokenize(t_lexer *lexer, t_array *tokens, const char *input);

/*
** `lexer_clear_tokens` removes from a t_array of tokens
** `tokens` the tokens unused by the shell grammar.
*/
int			lexer_clear_tokens(t_array *tokens);

/*
** Remove potential trailing escaped newline and the
** escaping backslash.
** Returns LINE_INCOMPLETE if a removing is performed,
** LINE_COMPLETE otherwise.
*/
int			remove_trailing_escaped_newline(t_string *input);

/*
** Categorize token according to POSIX rules
*/
void		categorize_tokens(t_array *tokens, const char *input);
void		categorize_io_number(t_array *tokens, const char *input);

/*
** Debug
** Print the tokens list
*/
void		lexer_debug_print_tokens(const t_array *tokens, const char *line);

#endif

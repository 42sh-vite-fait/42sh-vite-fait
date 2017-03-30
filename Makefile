NAME   = 42sh
CC     ?= clang # Need autoconf

CFLAGS = -Wall -Werror -Wextra
CFLAGS += -std=c11 -pedantic -pedantic-errors
CFLAGS += -D_POSIX_C_SOURCE=200809L
ifeq ($(DEBUG),yes)
	CFLAGS += -g3 -O0 -fno-inline
else
	CFLAGS += -O2 -DNDEBUG
endif
ifeq ($(PROF),yes)
	CFLAGS += -pg
endif
ifeq ($(SAN),yes)
	LDFLAGS += -fsanitize=address
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# Headers
CFLAGS     += -I./inc

# Sources
SRC_PATH   += src
SOURCES    += main.c

# Init
SRC_SUBDIR += init
SOURCES += init_shell.c

# Shell
SRC_SUBDIR += shell
SOURCES += shell_loop.c
SOURCES += shell_input.c
SOURCES += shell_history.c

# Errors
SRC_SUBDIR += error
SOURCES    += errors.c

# Misc
SRC_SUBDIR += misc
SOURCES    += string_escape.c
SOURCES    += string_fd.c
SOURCES    += is_valid_name.c
SOURCES    += is_valid_alias_name.c
SOURCES    += path_scanning.c
SOURCES	   += str_token.c

# History
SRC_SUBDIR += history
SOURCES    += history_get.c
SOURCES    += history_init.c
SOURCES    += history_add.c
SOURCES    += history_find.c
SOURCES    += history_save.c
SOURCES    += history_load.c
SOURCES    += history_clear.c

# Alias
SRC_SUBDIR += alias
SOURCES    += alias_init.c
SOURCES    += alias_getset.c
SOURCES    += alias_get_all.c
SOURCES    += alias_clear.c

# Input
SRC_SUBDIR += input
SOURCES    += input_get_line.c

# UI
SRC_SUBDIR += input/ui
SOURCES += terminal_init.c
SOURCES += terminal_caps.c
SOURCES += terminal_get_winsize.c
SOURCES += ui_get_line.c
SOURCES += input_handling.c
SOURCES += line.c
SOURCES += line_cursor.c
SOURCES += line_words.c
SOURCES += handler_move.c
SOURCES += handler_edition.c
SOURCES += handler_kill_yank.c
SOURCES += handler_jump.c
SOURCES += handler_history.c
SOURCES += handler_autocomplete.c
SOURCES += init_shutdown_term_env.c

# Variable
SRC_SUBDIR += var
SOURCES += var_init.c
SOURCES += var_get.c
SOURCES += var_set.c

# Automaton
SRC_SUBDIR += automaton
SOURCES += automaton.c
SOURCES += automaton_creation.c

# History expansion
SRC_SUBDIR += history_expansion
SOURCES += history_expansion.c
SOURCES += history_expansion_parse.c
SOURCES += history_expansion_substitute.c
SOURCES += history_expansion_error.c

# Lexer
SRC_SUBDIR += lexer
SOURCES += lexer_table.c
SOURCES += lexer.c
SOURCES += lexer_creation.c
SOURCES += lexer_tokenize.c
SOURCES += lexer_clear_tokens.c
SOURCES += lexer_line_continuation.c
SOURCES += lexer_debug.c
SOURCES += categorize_token.c
SOURCES += categorize_io_number.c
LEXER_TABLE = src/lexer/lexer_table.c
CONTRIB = contrib
RULES_XML = $(CONTRIB)/lexing_rules.xml
PYTHON_GEN_TABLE = $(CONTRIB)/gen_transtable.py
LEXER_TEMPLATE = $(CONTRIB)/lexer_table.c.template

# Quoting
SOURCES += quoting.c

# Parser
SRC_SUBDIR += parser
SOURCES += parser.c
SOURCES += parser_init.c
SOURCES += parser_utils.c
SOURCES += predict_and_or.c
SOURCES += predict_cmd_prefix.c
SOURCES += predict_cmd_suffix.c
SOURCES += predict_command.c
SOURCES += predict_complete_command.c
SOURCES += predict_complete_commands.c
SOURCES += predict_compound_list.c
SOURCES += predict_io_file.c
SOURCES += predict_io_here.c
SOURCES += predict_io_redirect.c
SOURCES += predict_linebreak.c
SOURCES += predict_list.c
SOURCES += predict_newline_list.c
SOURCES += predict_pipe_sequence.c
SOURCES += predict_program.c
SOURCES += predict_redirect_list.c
SOURCES += predict_separator.c
SOURCES += predict_simple_command.c
SOURCES += predict_subshell.c
SOURCES += predict_term.c
# Heredoc
SRC_SUBDIR += parser/heredoc
SOURCES += heredoc.c
SOURCES += heredoc_shutdown.c
SOURCES += ft_tmpfile.c

# AST
SRC_SUBDIR += parser/ast
SOURCES += ast_node.c
SOURCES += ast_command.c
SOURCES += ast_compress.c
SOURCES += ast_debug_print.c

# Expansion
SRC_SUBDIR += expansion
SOURCES += expand_tokens_to_argv.c
SOURCES += quote_removal.c

# Exit status
SRC_SUBDIR += exit_status
SOURCES += exit_status.c

# Builtins
SRC_SUBDIR += builtins
SOURCES += builtin_history.c
SOURCES += builtin_exit.c
SOURCES += builtin_echo.c
SOURCES += builtin_env.c
SOURCES += builtin_setenv.c
SOURCES += builtin_unsetenv.c
SOURCES += builtin_cd.c
SOURCES += builtin_cd_utils.c
SOURCES += builtin_cd_utils2.c

# Opt
SRC_SUBDIR += opt
SOURCES += opt_parse.c
SOURCES += opt_is_set.c

# Execution
SRC_SUBDIR += exec
SOURCES += exec.c
SOURCES += exec_init.c
SOURCES += exec_binary.c
SOURCES += exec_io_utils.c
SOURCES += exec_node_utils.c
SOURCES += exec_process_utils.c
SOURCES += exec_process_group_utils.c
SOURCES += exec_with_path.c
SOURCES += exec_fallback_sh.c
SOURCES += exec_backup_fd.c
# Complete Command
SRC_SUBDIR += exec/complete_command
SOURCES += exec_node_complete_command.c
# List
SRC_SUBDIR += exec/list
SOURCES += exec_node_list.c
# Subshell
SRC_SUBDIR += exec/subshell
SOURCES += exec_node_subshell.c
SOURCES += exec_node_term.c
# And_Or
SRC_SUBDIR += exec/and_or
SOURCES += exec_node_and_or.c
# Pipe
SRC_SUBDIR += exec/pipe
SOURCES += exec_node_pipe.c
SOURCES += exec_pipe_command.c
SOURCES += exec_pipe_sequence.c
SOURCES += exec_pipe_utils.c
# Simple Command
SRC_SUBDIR += exec/simple_command
SOURCES += exec_node_simple_command.c
SOURCES += exec_simple_command.c
# Builtins
SRC_SUBDIR += exec/builtins
SOURCES += builtin_manager.c
# Redirection
SRC_SUBDIR += exec/redirection
SOURCES += exec_redirection.c
SOURCES += exec_redirection_dup.c
SOURCES += exec_redirection_file.c
SOURCES += exec_redirection_undo.c

# Signal
SRC_SUBDIR += signal
SOURCES += signal.c
SOURCES += signal_blocked.c
SOURCES += signal_ignored.c
SOURCES += signal_exit.c

# Autocompletion
SRC_SUBDIR += autocompletion
SOURCES += autocomplete.c
SOURCES += autocomplete_builtin.c
SOURCES += autocomplete_binary.c

# Generation
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))
OBJ_PATH   = .obj
OBJECTS    = $(SOURCES:%.c=$(OBJ_PATH)/%.o)
DEP_PATH   = .dep
DEPS       = $(SOURCES:%.c=$(DEP_PATH)/%.d)
BUILD_DIR  = $(OBJ_PATH) $(DEP_PATH)

# Lib tierces
LIB42_PATH = lib42
LIB42      = $(LIB42_PATH)/lib42.a
CFLAGS     += -I$(LIB42_PATH)/inc -I$(LIB42_PATH)/debug
LDFLAGS    += -L $(LIB42_PATH) -l42

# Termcap Multi-OS
UNAME_S    := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -l termcap
else
	LDFLAGS += -l ncurses
endif

# Test
TEST_PATH  = test
TEST_EXEC  = $(TEST_PATH)/test_$(NAME).out

# Core rules
.SECONDARY: $(OBJECTS)

all: $(DEPS) $(LEXER_TABLE) $(NAME) $(SCRIPT)

-include $(DEPS)

$(NAME): $(OBJECTS) | $(LIB42)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIB42):
	$(MAKE) -C $(LIB42_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: %.c | $(DEP_PATH)
	$(CC) $(CFLAGS) -MM $< -MT $(OBJ_PATH)/$*.o -MF $@

$(BUILD_DIR):
	@-mkdir -p $@

$(LEXER_TABLE): $(RULES_XML) $(PYTHON_GEN_TABLE) $(LEXER_TEMPLATE)
	python3 $(PYTHON_GEN_TABLE) $(RULES_XML)  $(LEXER_TEMPLATE) $@

check: $(NAME)
	make check_unit
	make check_diff
	@# make check_leaks

check_unit:
	@cd $(TEST_PATH) && $(MAKE)
	@./$(TEST_EXEC)

check_diff:
	@zsh $(TEST_PATH)/shellscript/use_case_diff_mksh_tests.sh $(SUITE) $(CASE)

check_valgrind:
	@zsh $(TEST_PATH)/leaks/run_valgrind.sh $(SUITE) $(CASE)

check_leaks:
	@$(MAKE) -C . DEBUG=yes re
	@zsh $(TEST_PATH)/leaks/run_leaks.sh

clean:
	$(RM) -r $(OBJ_PATH)
	$(MAKE) -C $(LIB42_PATH) clean
	$(MAKE) -C $(TEST_PATH) clean

fclean:
	$(RM) $(NAME)
	$(RM) -rf $(DEP_PATH) $(OBJ_PATH)
	$(MAKE) -C $(TEST_PATH) fclean

re: fclean all

# Tool rules

sanitize:
	$(MAKE) re SAN=yes DEBUG=yes

unsanitize:
	$(MAKE) re DEBUG=yes

sub-init:
	git submodule update --init --recursive

sub-update:
	git submodule update --remote --recursive

norme:
	@ ! norminette -R CheckTopCommentHeader $(SRC_PATH) | grep -v -B 1 "^Norme"
	@ ! norminette -R CheckTopCommentHeader $(INC_PATH) | grep -v -B 1 "^Norme"

valgrind:
	valgrind --leak-check=full ./$(NAME)

callgrind:
	valgrind --tool=callgrind --callgrind-out-file=$(CG_OUTPUT_FILE) ./$(NAME)
	callgrind_annotate --auto=yes $(CG_OUTPUT_FILE)

ctags:
	ctags -R --tag-relative=yes --exclude='.git*' --exclude='test' --exclude='*.o' --exclude='*dSYM' --exclude='doc' --exclude='exercices'

clean-tools:
	$(RM) -r *.dSYM/

.PHONY: all $(LIB42) clean fclean re sanitize unsanitize sub-update sub-init check norme valgrind callgrind ctags clean-tools

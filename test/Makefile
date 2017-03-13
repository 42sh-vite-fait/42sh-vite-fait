NAME = test_42sh.out
CC ?= clang
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c11 -pedantic-errors -Wno-unused-variable -Wno-unused-function

#Debug
ifeq ($(DEBUG),yes)
	CFLAGS += -g3 -O0 -fno-inline
endif

# Profile
ifeq ($(PROF),yes)
	CFLAGS += -pg
endif

# Opti
ifeq ($(PROD),yes)
	CFLAGS += -O2
endif

# Sanitize
ifeq ($(SAN),yes)
	LDFLAGS += -fsanitize=address
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls -DSANITIZE
endif

# Headers
INC_PATH = inc
INC_FILES = header.h
HEADERS = $(INC_FILES:%.h=$(INC_PATH)/%.h)
CFLAGS += $(addprefix -I,$(INC_PATH))

# History
SRC_SUBDIR += history
SOURCES += test_history.c

# Alias
SRC_SUBDIR += alias
SOURCES += test_alias.c

# String
SRC_SUBDIR += string
SOURCES += test_string_escape.c

# Variable
SRC_SUBDIR += var
SOURCES += test_var.c

# Misc
SRC_SUBDIR += misc
SOURCES += is_valid_name.c
SOURCES += is_valid_alias_name.c
SOURCES += test_path_scanning.c

# Lexer
SRC_SUBDIR += lexer
SOURCES += test_lexer_rules1.c
SOURCES += test_lexer_rules2_3.c
SOURCES += test_lexer_rules4.c
SOURCES += test_lexer_rules5.c
SOURCES += test_lexer_rules7.c
SOURCES += test_lexer_rules8.c
SOURCES += test_lexer_rules9.c
SOURCES += test_line_continuation.c

# Parser
SRC_SUBDIR += parser
SOURCES += test_parser_io_file.c
# SOURCES += test_parser_io_here.c
SOURCES += test_parser_linebreak.c
SOURCES += test_parser_newline_list.c
SOURCES += test_parser_separator.c
SOURCES += test_parser_separator_op.c
SOURCES += test_parser_ast_compress.c

# Expansion
SRC_SUBDIR += expansion
SOURCES += quote_removal.c

# Builtins
SRC_SUBDIR += builtins
SOURCES += test_builtins.c
SOURCES += test_builtin_history.c

SRC_PATH = src
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

# Objects
OBJ_PATH = .obj
OBJECTS = $(addprefix $(OBJ_PATH)/,$(SOURCES:%.c=%.o))

# Criterion
CRITERION_PATH = criterion
CRITERION_FULL_PATH = $(PWD)/$(CRITERION_PATH)
CRITERION = $(CRITERION_FULL_PATH)/build/libcriterion.dylib
CRITERION_INC = $(CRITERION_FULL_PATH)/include
CRITERION_FLAGS = -Wl,-rpath,$(CRITERION_FULL_PATH)/build -L$(CRITERION_FULL_PATH)/build -lcriterion
LDFLAGS += $(CRITERION_FLAGS)
CFLAGS += -I$(CRITERION_INC)

# BSD Libc
UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S), Darwin)
	LDFLAGS += -lbsd
endif

# lib42
LIB42_PATH = ../lib42
LIB42 = $(LIB42_PATH)/lib42.a
CFLAGS += -I$(LIB42_PATH)/inc
LDFLAGS += -L$(LIB42_PATH) -l42

# Debug
CFLAGS += -I$(LIB42_PATH)/debug

# Project to test
PROJECT_PATH = ..
CFLAGS += $(addprefix -I,$(PROJECT_PATH)/inc)
PROJECT_OBJ_PATH := $(PROJECT_PATH)/.obj
PROJECT_OBJ := $(wildcard $(PROJECT_OBJ_PATH)/*.o)
PROJECT_OBJ := $(filter-out $(PROJECT_OBJ_PATH)/main.o, $(PROJECT_OBJ))
TEST_PATH = .
TEST_EXEC = $(TEST_PATH)/test_$(NAME)

# Termcap Multi-OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -ltermcap
else
	LDFLAGS += -lncurses
endif

# Rules
.PHONY: all script

all: $(CRITERION) $(PROJECT_OBJ_PATH) $(NAME)

$(PROJECT_OBJ_PATH):
	$(MAKE) -C $(PROJECT_PATH) re

$(LIB42):
	$(MAKE) -C $(LIB42_PATH) all

$(NAME): $(OBJECTS) $(PROJECT_OBJ) | $(LIB42)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(HEADERS) | $(OBJ_PATH)
$(OBJECTS): $(OBJ_PATH)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PATH):
	@-mkdir -p $@

.PHONY: clean fclean re before_test

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(CRITERION):
	cd $(CRITERION_PATH) && mkdir -p build && cd build && sh -c "exec >/dev/null; unset CC && unset CFLAGS && cmake .. && cmake --build ."

before_test: $(CRITERION)

# Submodule
.PHONY: sub-update sub-init

sub-init:
	git submodule update --init

sub-update:
	git submodule update --remote


# Tools
.PHONY: norme valgrind ctags clean-tools

norme:
	@norminette $(SRC_PATH)
	@norminette $(INC_PATH)

valgrind:
	valgrind --leak-check=full ./$(NAME)

callgrind:
	valgrind --tool=callgrind ./$(NAME)
	callgrind_annotate callgrind*.out

ctags:
	ctags -R --tag-relative=yes --exclude='.git*' --exclude='test' --exclude='*.o' --exclude='*dSYM' --exclude='doc'

clean-tools:
	$(RM) -r *.dSYM/

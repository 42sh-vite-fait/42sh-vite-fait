NAME = 42sh
CC ?= clang
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -std=c99 -pedantic -pedantic-errors
CFLAGS += -Weverything -Wno-missing-noreturn

# Debug
ifeq ($(DEBUG),yes)
	CFLAGS += -g -O0 -fno-inline
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
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# Header path
INC_PATH = include

# Sources
SRC_PATH = src
# SOURCES += main.c

# Dependencies
DEP_PATH = .dep
DEPS = $(SOURCES:%.c=$(DEP_PATH)/%.d)

# $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))
vpath %.c $(SRC_PATH)

# Debug
# DEBUG_PATH = debug
# HEADERS += $(DEBUG_PATH)/debug.h
# SOURCES += debug_lexer.c
# SOURCES += debug_input.c
# vpath %.c $(DEBUG_PATH)

# Generation
CFLAGS += $(addprefix -I,$(INC_PATH))

# TODO clean rule
OBJ_PATH = .obj
OBJECTS = $(SOURCES:%.c=$(OBJ_PATH)/%.o)

BUILD_DIR = $(OBJ_PATH) $(DEP_PATH)

# Lib tierces
LIB42_PATH = lib42
LIB42 = $(LIB42_PATH)/lib42.a
CFLAGS += -I $(LIB42_PATH)/inc
LDFLAGS += -L $(LIB42_PATH) -l42

# Termcap Multi-OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	LDFLAGS += -l termcap
else
	LDFLAGS += -l ncurses
endif

# Test
TEST_PATH = test
TEST_EXEC = $(TEST_PATH)/test_$(NAME)
GIT_CLEAN = git clean -fd

# Rules
.PHONY: all

.SECONDARY: $(OBJECTS)

all: $(DEPS) $(NAME)

-include $(DEPS)

$(LIB42):
	$(MAKE) -C $(LIB42_PATH) all

$(NAME): $(OBJECTS) | $(LIB42)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -o $@ -c $<

$(DEP_PATH)/%.d: %.c | $(DEP_PATH)
	$(CC) $(CFLAGS) -MM $< -MT $(OBJ_PATH)/$*.o -MF $@

$(BUILD_DIR):
	@-mkdir -p $@

.PHONY: clean fclean re sanitize unsanitize

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

sanitize:
	$(MAKE) -C ./ re SAN=yes DEBUG=yes

unsanitize:
	$(MAKE) -C ./ re DEBUG=yes

# Submodule
.PHONY: sub-update sub-init

sub-init:
	git submodule update --init --recursive

sub-update:
	git submodule update --remote --recursive

# Tests
.PHONY: check test-cleanup

check: all
	@$(MAKE) -C $(TEST_PATH) all
	@./$(TEST_EXEC)

# Tools
.PHONY: norme valgrind ctags clean-tools

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

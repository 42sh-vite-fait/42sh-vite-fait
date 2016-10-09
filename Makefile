NAME = 42sh
CC ?= clang
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -std=c99 -pedantic -pedantic-errors
ifeq ($(shell readlink $(shell command -v $(CC))),clang)
	CFLAGS += -Weverything -Wno-missing-noreturn
endif
CFLAGS += -fno-strict-aliasing

# Debug
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
	CFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
endif

# Root
SOURCES += main.c

# History
SRC_SUBDIR += history
SOURCES += history_contains.c
SOURCES += history_get.c
SOURCES += history_new.c
SOURCES += history_push.c
SOURCES += history_search.c
SOURCES += history_save_load.c

# Root
SOURCES += main.c

# Generation
INC_PATH = inc $(LIB42_PATH)/inc
SRC_PATH = src
CFLAGS += $(addprefix -I,$(INC_PATH))
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

# Lib tierces
LIB42_PATH = lib42
LIB42 = $(LIB42_PATH)/lib42.a
CFLAGS += -I $(LIB42_PATH)/inc
LDFLAGS += -L $(LIB42_PATH) -l42

# Object files
OBJ_PATH = .obj
OBJECTS = $(SOURCES:%.c=$(OBJ_PATH)/%.o)

# Dependencies
DEP_PATH = .dep
DEPS = $(SOURCES:%.c=$(DEP_PATH)/%.d)

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
TEST_EXEC = $(TEST_PATH)/test_$(NAME).out

# Rules
.PHONY: all

.SECONDARY: $(OBJECTS)

all: $(LIB42) $(DEPS) $(NAME)

-include $(DEPS)

$(NAME): $(OBJECTS) | $(LIB42)
	$(CC) -o $@ $^ $(LDFLAGS)

$(LIB42):
	$(MAKE) -C $(LIB42_PATH) all

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
	$(RM) -rf $(DEP_PATH)

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
	@$(MAKE) -C $(TEST_PATH) re
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

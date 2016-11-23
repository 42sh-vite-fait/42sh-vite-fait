NAME   = 42sh
CC     ?= clang # Need autoconf

CFLAGS = -Wall -Werror -Wextra
CFLAGS += -std=c11 -pedantic -pedantic-errors
ifeq ($(DEBUG),yes)
	CFLAGS += -g3 -O0 -fno-inline
endif
ifeq ($(PROF),yes)
	CFLAGS += -pg
endif
ifeq ($(PROD),yes)
	CFLAGS += -O2
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

# Input
SRC_SUBDIR += input
SOURCES    += readline.c

# Misc
SRC_SUBDIR += misc
SOURCES    += string_escape.c
SOURCES    += string_fd.c

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
SOURCES += alias_init.c
SOURCES += alias_getset.c
SOURCES += alias_get_all.c
SOURCES += alias_clear.c

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
CFLAGS     += -I$(LIB42_PATH)/inc
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

all: $(DEPS) $(NAME)

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

check: $(OBJECTS)
	@cd $(TEST_PATH) && $(MAKE)
	@./$(TEST_EXEC) --verbose

clean:
	$(RM) -r $(OBJ_PATH)
	$(MAKE) -C $(LIB42_PATH) clean
	$(MAKE) -C $(TEST_PATH) clean

fclean:
	$(RM) $(NAME)
	$(RM) -rf $(DEP_PATH) $(OBJ_PATH)
	$(MAKE) -C $(LIB42_PATH) fclean
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

NAME = test_42sh.out
CC ?= clang
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c99 -pedantic-errors -Wno-unused-variable -Wno-unused-function

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

# Root
SOURCES += main.c

# History
SRC_SUBDIR += history
SOURCES += test_history.c

# Buffer
SRC_SUBDIR += string
SOURCES += test_string_escape.c

SRC_PATH = src
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

# Objects
OBJ_PATH = .obj
OBJECTS = $(addprefix $(OBJ_PATH)/,$(SOURCES:%.c=%.o))

# Vittf
VITTF_PATH = vittf
CFLAGS += -I$(VITTF_PATH)

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
.PHONY: all

all: $(PROJECT_OBJ_PATH) $(NAME)

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

.PHONY: clean fclean re

clean:
	$(RM) -r $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all


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

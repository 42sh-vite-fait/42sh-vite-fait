NAME = test_lib42.out
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


# Sources
SOURCES += main.c
SOURCES += ctype.c

# Array
SRC_SUBDIR += array
SOURCES += test_array_find_from.c
SOURCES += test_array_create.c
SOURCES += test_array_init.c
SOURCES += test_array_at.c
SOURCES += test_array_reserve.c
SOURCES += test_array_shrink.c
SOURCES += test_array_push.c
SOURCES += test_array_pop.c
SOURCES += test_array_index_of.c
SOURCES += test_array_replace_at.c
SOURCES += test_array_insert_at.c
SOURCES += test_array_remove_at.c
SOURCES += test_array_remove_elem.c
SOURCES += test_array_clone.c
SOURCES += test_array_truncate_clear.c
SOURCES += test_array_get_available.c
SOURCES += test_array_swap.c

# Cbuffer
SRC_SUBDIR += cbuffer
SOURCES += test_cbuffer_push.c
SOURCES += test_cbuffer_pop.c
SOURCES += test_cbuffer_reserve.c
SOURCES += test_cbuffer_truncate.c
SOURCES += test_cbuffer_shrink_to_fit.c

# String
SRC_SUBDIR += string
SOURCES += test_string_create_init.c
SOURCES += test_string_cat.c
SOURCES += test_string_dup.c
SOURCES += test_string_reserve.c
SOURCES += test_string_shrink_to_fit.c
SOURCES += test_string_insert.c
SOURCES += test_string_remove.c
SOURCES += test_string_set.c
SOURCES += test_string_truncate.c
SOURCES += test_string_remove_back.c
SOURCES += test_string_remove_back_chr.c
SOURCES += test_string_append.c
SOURCES += test_string_replace.c
SOURCES += test_string_clone.c
SOURCES += test_string_merge.c

# Memory
SRC_SUBDIR += memory
SOURCES += test_memset.c
SOURCES += test_memcpy.c
SOURCES += test_memccpy.c
SOURCES += test_memmove.c
SOURCES += test_memchr.c
SOURCES += test_memcmp.c

# Stdlib
SRC_SUBDIR += stdlib
SOURCES += test_realloc.c
SOURCES += test_toa_base.c
SOURCES += test_next_power2.c
SOURCES += test_ato_base.c

# Str
SRC_SUBDIR += str
SOURCES += test_strcmp.c
SOURCES += test_strlen.c
SOURCES += test_strnlen.c
SOURCES += test_strdup.c
SOURCES += test_strndup.c
SOURCES += test_strchr.c
SOURCES += test_strrchr.c
SOURCES += test_strrev.c
SOURCES += test_strstr.c

# Pool
SRC_SUBDIR += pool
SOURCES += test_pool_macros.c
SOURCES += test_pool_init.c
SOURCES += test_pool_obtain_node.c
SOURCES += test_pool_release_node.c
SOURCES += test_pool_shutdown.c

# Error
SRC_SUBDIR += error
SOURCES += test_error.c

# Getopt
SRC_SUBDIR += unistd
SOURCES += test_getopt.c

SRC_PATH = src
vpath %.c $(SRC_PATH) $(addprefix $(SRC_PATH)/,$(SRC_SUBDIR))

# Objects
OBJ_PATH = obj
OBJECTS = $(addprefix $(OBJ_PATH)/,$(SOURCES:%.c=%.o))


# Lib42
LIB42_PATH = ..
LIB42 = $(LIB42_PATH)/lib42.a
CFLAGS += -I$(LIB42_PATH)/inc
LDFLAGS += -L$(LIB42_PATH) -l42

# Vittf
VITTF_PATH = vittf
CFLAGS += -I$(VITTF_PATH)

# BSD Libc
UNAME_S := $(shell uname -s)
ifneq ($(UNAME_S), Darwin)
	LDFLAGS += -lbsd
endif


# Rules
.PHONY: all

all: $(NAME)

$(LIB42):
	$(MAKE) -C $(LIB42_PATH) all

$(NAME): $(OBJECTS) | $(LIB42)
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

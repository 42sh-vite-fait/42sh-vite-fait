#ifndef VITTF_H
#define VITTF_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/*
 * Colors
 */
#define COLOR_RESET	"\x1b[0m"
#define BG_RED		"\x1b[41m"
#define FG_BLUE		"\x1b[34m"
#define FG_GREEN	"\x1b[32m"

/*
 * Strings
 */
#define FAILED_STR		printf(BG_RED "FAILED !!!\t" COLOR_RESET)
#define FAILED_FILE		printf("FILE(%s)", __FILE__)
#define FAILED_LINE		printf(" | LINE(%d)", __LINE__)
#define FAILED_FUNCTION	printf(" | FUNCTION(%s)", __func__)
#define PRINTF_FAILED	FAILED_STR; FAILED_FILE; FAILED_LINE; FAILED_FUNCTION;

/*
 * Assertions
 */
#define v_assert_type(fmt, expected, op, actual) \
	do { \
		if (!(expected op actual)) { \
			PRINTF_FAILED; \
			printf("\n\tEXPRESSION\t>>> " #expected " " #op " " #actual); \
			printf("\n\tVALUES\t\t>>> " fmt " " #op " " fmt, (expected), (actual)); \
			printf("\n"); \
			exit(1); \
		} \
	} while (0)

#define v_assert_type_pass(fmt, expected, op, actual) \
	do { \
		if (!(expected op actual)) { \
			PRINTF_FAILED; \
			printf("\n\tEXPRESSION\t>>> " #expected " " #op " " #actual); \
			printf("\n\tVALUES\t\t>>> " fmt " " #op " " fmt, (expected), (actual)); \
			printf("\n"); \
			return ; \
		} \
	} while (0)

#define v_assert_int(expected, op, actual) \
	v_assert_type("%d", (int)expected, op, (int)actual)
#define v_assert_uint(expected, op, actual) \
	v_assert_type("%u", (unsigned)(expected), op, (unsigned)(actual))
#define v_assert_long(expected, op, actual) \
	v_assert_type("%ld", (long)(expected), op, (long)(actual))
#define v_assert_size_t(expected, op, actual) \
	v_assert_type("%zu", (size_t)(expected), op, (size_t)(actual))
#define v_assert_ptr(expected, op, actual) \
	v_assert_type("%p", (void*)(expected), op, (void*)(actual))
#define v_assert_char(expected, op, actual) \
	v_assert_type("%c", (char)expected, op, (char)actual)
#define v_assert_uintptr(expected, op, actual) \
	v_assert_type("%tx", (uintptr_t)expected, op, (uintptr_t)actual)

#define v_assert_int_pass(expected, op, actual) \
	v_assert_type_pass("%d", (int)expected, op, (int)actual)
#define v_assert_uint_pass(expected, op, actual) \
	v_assert_type_pass("%u", (unsigned)(expected), op, (unsigned)(actual))
#define v_assert_long_pass(expected, op, actual) \
	v_assert_type_pass("%ld", (long)(expected), op, (long)(actual))
#define v_assert_size_t_pass(expected, op, actual) \
	v_assert_type_pass("%zu", (size_t)(expected), op, (size_t)(actual))
#define v_assert_ptr_pass(expected, op, actual) \
	v_assert_type_pass("%p", (void*)(expected), op, (void*)(actual))
#define v_assert_char_pass(expected, op, actual) \
	v_assert_type_pass("%c", (char)expected, op, (char)actual)
#define v_assert_uintptr_pass(expected, op, actual) \
	v_assert_type_pass("%tx", (uintptr_t)expected, op, (uintptr_t)actual)

#define v_assert(expression) \
	do { \
		if (!(expression)) {\
			PRINTF_FAILED; \
			printf("\n\tExpression(%s)\n", #expression); \
			exit(1); \
		} \
	} while (0)

#define v_assert_str(expected, actual) \
	do { \
		if (strcmp((expected), (actual)) != 0) {\
			PRINTF_FAILED; \
			printf("\n\tStrcmp >>>\n\tExpected\t--> [%s]\n\tActual\t\t--> [%s]\n", (char*)(expected), (char*)(actual)); \
			exit(1);\
		}\
	} while (0)

#define v_assert_pass(expression) \
	do { \
		if (!(expression)) {\
			PRINTF_FAILED; \
			printf("\n\tExpression(%s)\n", #expression); \
			return ;\
		} \
	} while (0)

#define v_assert_str_pass(expected, actual) \
	do { \
		if (strcmp((expected), (actual)) != 0) {\
			PRINTF_FAILED; \
			printf("\n\tExpression >>> (Expected) %s != %s (Actual)\n", (char*)(expected), (char*)(actual)); \
			return ;\
		}\
	} while (0)

#define v_test_success(name) \
	(printf("%s ✓\n", (name)))
#define v_suite_success(suite) \
	(printf("---> Suite %s ✓\n\n", (suite)))
#define v_full_success(test) \
	(printf("=========\n\x1b[32mFULL TEST FOR %s ✓\x1b[0m\n", (test)))
#define VTS v_test_success(__func__)
#define VSS v_suite_success(__func__)

static int	v_pipe_redirect[2];
static int	v_fd_ref;
static int	v_fd_pipe;
static FILE *v_redirect_stream;

static void	v_redirect_error(char *msg)
{
	fprintf(stderr, "%s", msg);
	exit(1);
}

inline static void	v_redirect_setup(int fd)
{
	v_fd_ref = fd;

	// do not buffer line
	if (fd == 1)
		setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	else if (fd == 2)
		setvbuf(stderr, NULL, _IONBF, BUFSIZ);

	v_fd_pipe = dup(fd);
	if (pipe(v_pipe_redirect) == -1)
		v_redirect_error("setup pipe error");
	if (dup2(v_pipe_redirect[1], fd) == -1)
		v_redirect_error("setup dup2 error");
}

inline static ssize_t	v_redirect_read(char *buffer, size_t size)
{
	ssize_t	ret;

	ret = read(v_pipe_redirect[0], buffer, size - 1);
	if (ret == -1)
		v_redirect_error("read error");
	buffer[ret] = '\0';
	return (ret);
}

inline static void	v_redirect_teardown(void)
{
	if ((dup2(v_fd_pipe, v_fd_ref)) == -1)
		v_redirect_error("teardown dup2 error");
	close(v_pipe_redirect[0]);
	close(v_pipe_redirect[1]);
	close(v_fd_pipe);

	// restore buffering line
	if (v_fd_ref == 1)
		setvbuf(stdout, (char *)NULL, _IOLBF, 0);
	else if (v_fd_ref == 2)
		setvbuf(stderr, (char *)NULL, _IOLBF, 0);
}

#endif

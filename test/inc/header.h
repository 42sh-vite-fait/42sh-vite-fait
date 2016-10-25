#ifndef TEST_LIB42_H
#define TEST_LIB42_H

#define _XOPEN_SOURCE 700
#define _DEFAUTL_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#if !defined(__APPLE__)
#include <bsd/string.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include "history.h"
#include "misc.h"
#include "lib42.h"
#include "vittf.h"

// History
void	suite_history(void);

// String un/escape
void	suite_string_escape(void);

#endif
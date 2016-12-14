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
#include <limits.h>
#include <stdint.h>
#if !defined(__APPLE__)
#include <bsd/string.h>
#endif
#include <stdint.h>
#include <stdio.h>
#include "history.h"
#include "alias.h"
#include "misc.h"
#include "var.h"
#include "errors.h"
#include "lib42.h"
#include "lexer.h"
#include "automaton.h"
#include "user_interface.h"

#endif

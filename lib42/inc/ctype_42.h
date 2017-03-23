#ifndef FT_CTYPE_H
# define FT_CTYPE_H

# define FT_ISASCII(c) (((c) & 0x80) == 0)
# define FT_ISBLANK(c) ((c) == ' ' || (c) == '\t')
# define FT_ISWHITESPACE(c) (FT_ISBLANK(c) || ((c) == '\n'))
# define FT_ISSPACE(c) ((c) == ' ' || ((unsigned)(c) - '\t') < 5U)
# define FT_ISCNTRL(c) (((c) < 0x20) || ((c) == 0x7F))
# define FT_ISDIGIT(c) ((unsigned)(c) - '0' < 10U)
# define FT_ISLOWER(c) ((unsigned)(c) - 'a' < 26U)
# define FT_ISUPPER(c) ((unsigned)(c) - 'A' < 26U)
# define FT_ISGRAPH(c) ((unsigned)(c) - '!' < 94U)
# define FT_ISPRINT(c) ((unsigned)(c) - ' ' < 95U)
# define FT_ISALPHA(c) (FT_ISLOWER(c) || FT_ISUPPER(c))
# define FT_ISALNUM(c) (FT_ISALPHA(c) || FT_ISDIGIT(c))
# define FT_ISPUNCT(c) (FT_ISGRAPH(c) && !FT_ISALNUM(c))
# define FT_TOUPPER(c) ((FT_ISLOWER(c)) ? ((c) & 0x5F) : (c))
# define FT_TOLOWER(c) ((FT_ISUPPER(c)) ? ((c) | 0x20) : (c))
# define FT_ISXDIGIT(c) (FT_ISDIGIT(c) || ((unsigned)(c) | 0x20) - 'a' < 6U)

#endif

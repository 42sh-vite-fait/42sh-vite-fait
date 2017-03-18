#include <ctype.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>

static struct termios backup;
void	enable_rawmode(void);
void	disable_rawmode(void);
int		get_winsize(struct winsize *ws);
void	move_cursor(int x, int y);
int		get_cursor_pos(size_t *x, size_t *y);
void	execute_caps(char *cap);

/*
** Input flags
** 	~IXON: Les chars STOP/START ne sont pas interprétés.
** ##########################################################################
** Local flags (stty -a pour voir le binding des touches)
** 	~ISIG: Désactivation des signaux dus aux chars INTR, QUIT, SUSP, DSUSP
** 	~ICANON: Désactive le mode canonique
** 	~ECHO: Désactive l'écho des chars saisis.
** 	~IEXTEN: Désactive le mode étendu du traitement des entrées
*/

void	enable_rawmode(void)
{
	struct termios	raw;

	tgetent(NULL, getenv("TERM"));
	if (tcgetattr(STDIN_FILENO, &backup) < 0)
		exit(1);
	raw = backup;
	raw.c_iflag &= ~(unsigned)IXON;
	raw.c_lflag &= ~(unsigned)(ICANON | ECHO | IEXTEN | ISIG);
	raw.c_cc[VMIN] = 1;
	raw.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0)
	{
		disable_rawmode();
		exit(1);
	}
}

void	disable_rawmode(void)
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &backup) < 0)
		exit(1);
}

int		get_winsize(struct winsize *ws)
{
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, ws) == -1)
		return (-1);
	return (1);
}

static int	wrap_putchar(int c)
{
	return (write(1, &c, 1));
}

void	move_cursor(int x, int y)
{
	char	*ret;

	ret = tgoto(tgetstr("cm", NULL), x - 1, y - 1);
	tputs(ret, 1, &wrap_putchar);
}

static int	read_cursor_pos(char *buf, size_t size)
{
	size_t	i;

	write(STDOUT_FILENO, "\x1b[6n", 4);
	i = 0;
	while (i < (size - 1))
	{
		if (read(STDIN_FILENO, buf + i, 1) != 1)
			break ;
		if (buf[i] == 'R')
			break ;
		++i;
	}
	buf[++i] = '\0';
	return (i);
}

int			get_cursor_pos(size_t *x, size_t *y)
{
	char	buf[16];
	size_t	i;

	read_cursor_pos(buf, sizeof(buf));
	i = 0;
	if (buf[i] != '\x1b' && buf[i + 1] != '[')
		return (1);
	i += 2;
	*y = 0;
	while (isdigit(buf[i]))
		*y = *y * 10 + (buf[i++] - '0');
	if (buf[i++] != ';')
		return (1);
	*x = 0;
	while (isdigit(buf[i]))
		*x = *x * 10 + (buf[i++] - '0');
	if (buf[i] != 'R')
		return (1);
	return (0);
}

void		execute_caps(char *cap)
{
	tputs(tgetstr(cap, NULL), 1, &wrap_putchar);
}

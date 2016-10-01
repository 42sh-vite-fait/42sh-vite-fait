# include <ftsh.h>

int 	stop_termcap()
{
	struct termios term;

	term_command("ve");
	if (tcgetattr(0, &term) == -1)
	return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
   		return (-1);
   	return (1);
}

int 	start_termcap()
{
  char           	*name_term;
  struct termios 	term;
 
	if ((name_term = getenv("TERM")) == NULL)
 		return (-1);
	if (tgetent(NULL, name_term) == -1)
    	return (-1);
 	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (1);
}

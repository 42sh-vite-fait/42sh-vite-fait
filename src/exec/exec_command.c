#include "exec.h"
#include "ast.h"
#include "errors.h"

/*
 * //- fork
 * - perform redirections
 * - récupère le chemin complet du binaire
 * - construit le tableau des argv
 * - set les signaux pour une command
 * - cloture des fichiers inutiles
 * - execve
 */

void exec_simple_command(t_command command, const char *binary_path)
{
	int	ret;

	(void)binary_path;
	ret = exec_redirection(command.redirections);
	if (ret != NO_ERROR)
		_exit(EXIT_FAILURE);
}

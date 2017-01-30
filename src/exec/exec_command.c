#include "exec.h"
#include "ast.h"

/*
 * - perform redirections
 * - récupère le chemin complet du binaire
 * - set les signaux pour une command
 * - cloture des fichiers inutiles
 * - execve
 * - _exit(-1)
 */

void exec_binary(const t_command command)
{
	if (exec_redirection(command.redirections) != NO_ERROR)
	{
		error_print("execution");
		_exit(-1);
	}
}

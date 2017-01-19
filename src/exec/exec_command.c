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

	ret = exec_redirection(command.redirections);
	if (ret != NO_ERROR)
		return (ret);


}

/*
 * Ajoute un NULL à la fin du tableau
 * Recherche le binaire dans le PATH
 */

int ft_execvp(const char *binary, t_array *argv)
{
	execve()
}
